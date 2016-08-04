#include <stdio.h>
#include <thread>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include "WinSockManager.h"
#include "LogManager.h"
#include <arpa/inet.h>
#include "SocketThreadManager.h"

int WinSockManager::m_pollFdCount = 128;
struct pollfd* WinSockManager::m_pollFd = new struct pollfd[128];
int* WinSockManager::m_recvCount = new int[128];
int WinSockManager::m_registeredCount = 0;
WinSockManager** WinSockManager::m_registeredManagers = new WinSockManager*[128];
int WinSockManager::m_pollRes = 0;

void WinSockManager::InitializePollInfo() {
	bzero(WinSockManager::m_pollFd, sizeof(struct pollfd) * 128);
	bzero(WinSockManager::m_recvCount, sizeof(int) * 128);
	bzero(WinSockManager::m_registeredManagers, sizeof(WinSockManager*) * 128);
}

WinSockManager::WinSockManager() {
	if(WinSockManager::m_registeredCount == 0)
		this->InitializePollInfo();

	this->m_socket = -1;
	this->m_serverAddressLogIndex = LogMessageCode::lmcNone;
    this->m_sendStatus = WinSockStatus::wssOk;
    this->m_recvStatus = WinSockStatus::wssOk;
    this->m_sendSize = 0;
    this->m_recvSize = 0;
	this->m_pollIndex = -1;
}


WinSockManager::~WinSockManager() {
	this->Disconnect();
}

bool WinSockManager::Connect(char *server_address, unsigned short server_port, WinSockConnectionType connType) {
	sprintf(this->m_fullAddress, "%s:%d (%s)", server_address, server_port, (connType == WinSockConnectionType::wsTCP? "TCP": "UDP"));
	this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_fullAddress);

	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Connect, this->m_serverAddressLogIndex);

    this->m_connected = false;
    this->m_connectionType = connType;
	this->m_socket = socket(AF_INET,
							this->m_connectionType == WinSockConnectionType::wsTCP? SOCK_STREAM: SOCK_DGRAM,
							this->m_connectionType == WinSockConnectionType::wsTCP? IPPROTO_TCP: IPPROTO_UDP);

	if (this->m_socket < 0) {
		DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
		return false;
	}

	this->m_addressSize = sizeof(sockaddr_in);
	bzero(&this->m_adress, sizeof(sockaddr_in));
    inet_pton(AF_INET, server_address, &(this->m_adress.sin_addr));
    this->m_adress.sin_family = AF_INET;
	this->m_adress.sin_port = htons(server_port);

	int result = connect(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress));
	if(result < 0) {
        close(this->m_socket);
		DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
		return false;
	}

	if(this->m_pollIndex == -1)
		this->RegisterPoll();
	else
		this->UpdatePoll();

	DefaultLogManager::Default->EndLog(true);
	this->m_connected = true;
	return true;
}

void WinSockManager::RegisterPoll() {

	this->m_pollIndex = this->GetFreePollIndex();

	WinSockManager::m_pollFd[this->m_pollIndex].fd = this->m_socket;
	WinSockManager::m_pollFd[this->m_pollIndex].events = POLLIN;
	WinSockManager::m_registeredManagers[this->m_pollIndex] = this;

	WinSockManager::IncPollIndex();

	return;
}

bool WinSockManager::Disconnect() {
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Close, this->m_serverAddressLogIndex);
    if(this->m_socket == -1) {
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    if(this->m_connected) {
        shutdown(this->m_socket, SHUT_RDWR);
        this->m_connected = false;
    }

	int result = close(this->m_socket);
	if (result != 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool WinSockManager::Reconnect() {
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Reconnect, this->m_serverAddressLogIndex);

    if(this->m_connected) {
        shutdown(this->m_socket, SHUT_RDWR);
        this->m_connected = false;
    }

    int result = close(this->m_socket);
	if (result < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

    this->m_connected = false;
	this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->m_socket < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}
	
	result = connect(this->m_socket, (const sockaddr*)&(this->m_adress), sizeof(this->m_adress));
	if (result < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

	this->UpdatePoll();

	this->m_connected = true;
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool WinSockManager::TryFixSocketError(int errorCode) {

	return this->Reconnect();
}
