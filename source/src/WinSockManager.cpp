#include <stdio.h>
#include <thread>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include "WinSockManager.h"
#include "LogManager.h"
#include <arpa/inet.h>

int WinSockManager::ManagersCount = 0;
WinSockManager::WinSockManager() {
	this->m_socket = -1;
    WinSockManager::ManagersCount++;
}


WinSockManager::~WinSockManager() {
	WinSockManager::ManagersCount--;
}

bool WinSockManager::Connect(char *server_address, unsigned short server_port) {
	DefaultLogManager::Default->StartLog("WinSockManager::Initialize");

    this->connected = false;
    this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (this->m_socket < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

	bzero(&this->m_adress, sizeof(sockaddr_in));
    inet_pton(AF_INET, server_address, &(this->m_adress.sin_addr));
    this->m_adress.sin_family = AF_INET;
	this->m_adress.sin_port = htons(server_port);

	int result = connect(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress));
	if(result < 0) {
        close(this->m_socket);
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

	DefaultLogManager::Default->EndLog(true);
	this->connected = true;
	return true;
}

bool WinSockManager::Disconnect() {
	DefaultLogManager::Default->StartLog("WinSockManager::Close");
    if(this->m_socket == -1) {
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    if(this->connected) {
        shutdown(this->m_socket, SHUT_RDWR);
        this->connected = false;
    }

	int result = close(this->m_socket);
	if (result != 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

void WinSockManager::Run()
{
	//std::thread tr = std::thread(&WinSockManager::RunCore, this);
}
void WinSockManager::RunCore()
{
	/*
	std::thread tr = std::thread(&WinSockManager::ProcessMessageCore, this);
	char message[10000];
	while (true){
		int data_length = Recv(message, 10000);
		if (data_length <= 0) continue;

		unsigned int i = 0;
		while (i < (unsigned int)data_length)
		{
			char* res = &(message[i]);
			i += strlen(res);
			SetMessage(res);
		}
	}
	*/
}

void WinSockManager::SetMessage(char* res){
	messages[lastMessageIndex] = res;
	lastMessageIndex = (lastMessageIndex + 1) % 100; // 100 = array length
}

void WinSockManager::ProcessMessageCore(){
	/*
	int lastProcessedMessageIndex = 0;
	while (true)
	{
		if (lastMessageIndex == lastProcessedMessageIndex) continue;
		char* income = messages[lastProcessedMessageIndex];
		char* answer = "Answer";
		Send(answer, strlen(answer));
		lastProcessedMessageIndex = (lastProcessedMessageIndex + 1) % 100; // 100 = array length
	}
	*/
}

bool WinSockManager::Reconnect() { 
	DefaultLogManager::Default->StartLog("WinSockManager::Reconnect");

    if(this->connected) {
        shutdown(this->m_socket, SHUT_RDWR);
        this->connected = false;
    }

    int result = close(this->m_socket);
	if (result < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

    this->connected = false;
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

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool WinSockManager::TryFixSocketError(int errorCode) {

	return this->Reconnect();
}