#include "WinSockManager.h"

int WinSockManager::m_pollFdCount = 256;
struct pollfd* WinSockManager::m_pollFd = new struct pollfd[256];
int* WinSockManager::m_recvCount = new int[256];
int WinSockManager::m_registeredCount = 0;
WinSockManager** WinSockManager::m_registeredManagers = new WinSockManager*[256];
int WinSockManager::m_pollRes = 0;

void WinSockManager::InitializePollInfo() {
	bzero(WinSockManager::m_pollFd, sizeof(struct pollfd) * 256);
	bzero(WinSockManager::m_recvCount, sizeof(int) * 256);
	bzero(WinSockManager::m_registeredManagers, sizeof(WinSockManager*) * 256);
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

bool WinSockManager::ConnectMulticast(char *sourceIp, char *groupIp, unsigned short groupPort) {
	this->m_connectionType = WinSockConnectionType::wsUDP;

	sprintf(this->m_fullAddress, "%s-%s:%d (UDP)", sourceIp, groupIp, groupPort);
	this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_fullAddress);

	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_ConnectFast, this->m_serverAddressLogIndex);

	this->m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->m_socket < 0) {
		DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
		return false;
	}

	this->m_addressSize = sizeof(sockaddr_in);
	bzero(&this->m_adress, sizeof(sockaddr_in));
	this->m_adress.sin_addr.s_addr = htonl(INADDR_ANY);
	this->m_adress.sin_family = AF_INET;
	this->m_adress.sin_port = htons(groupPort);

	if(bind(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress)) < 0) {
		DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
		return false;
	}

	UINT32 group = inet_addr(groupIp);
	UINT32 source = inet_addr(sourceIp);

	this->m_imr.imr_multiaddr.s_addr = group;
	this->m_imr.imr_sourceaddr.s_addr = source;
	this->m_imr.imr_interface.s_addr = INADDR_ANY;

	if(setsockopt(this->m_socket, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char*)&(this->m_imr), sizeof(this->m_imr)) < 0) {
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

bool WinSockManager::Connect(char *server_address, unsigned short server_port) {
	this->m_connectionType = WinSockConnectionType::wsTCP;
	sprintf(this->m_fullAddress, "%s:%d (TCP)", server_address, server_port);
	this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_fullAddress);

	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Connect, this->m_serverAddressLogIndex);

    this->m_connected = false;
	this->m_socket = socket(AF_INET,
							SOCK_STREAM,
							IPPROTO_TCP);

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

bool WinSockManager::TryFixSocketError(int errorCode) {

	return this->Reconnect();
}
