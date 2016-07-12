#include <stdio.h>
#include <thread>
#include <cstring>
#include "WinSockManager.h"
#include "LogManager.h"

int WinSockManager::ManagersCount = 0;
WinSockManager::WinSockManager()
{
	/*
	if (WinSockManager::ManagersCount == 0) { 
		DefaultLogManager::Default->StartLog("Initializing Winsock");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
			DefaultLogManager::Default->EndLog(false);
			throw;
		}
		DefaultLogManager::Default->EndLog(true);
	} */
	WinSockManager::ManagersCount++;
}


WinSockManager::~WinSockManager()
{
	WinSockManager::ManagersCount--;
	/*
	if (WinSockManager::ManagersCount == 0)
		WSACleanup();
	*/
}

int WinSockManager::Initialize(char *server_address, u_short server_port) { 

	/*
	DefaultLogManager::Default->StartLog("WinSockManager::Initialize");
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		int error = WSAGetLastError();
		DefaultLogManager::Default->EndLog(false, ConsoleManager::GetErrorText(error));
		return error;
	}

	ZeroMemory(&sin, sizeof(sockaddr_in));

	int result = inet_pton(AF_INET, server_address, &(sin.sin_addr));
	if (result != 1) {
		int error = WSAGetLastError();
		DefaultLogManager::Default->EndLog(false, ConsoleManager::GetErrorText(error));
		return error;
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(server_port);

	result = connect(s, (const sockaddr*)&sin, sizeof(sin));
	if (result < 0) {
		int error = WSAGetLastError();
		DefaultLogManager::Default->EndLog(false, ConsoleManager::GetErrorText(error));
		return error;
	}

	DefaultLogManager::Default->EndLog(true);
	this->connected = true;
	 */
	return 0;
}

int WinSockManager::Close() {
	/*
	int result = closesocket(s);
	if (result != 0) {
		return WSAGetLastError();
	}
	this->connected = false;
	 */
	return 0;
}

void WinSockManager::Run()
{
	std::thread tr = std::thread(&WinSockManager::RunCore, this);
}
void WinSockManager::RunCore()
{
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
}

void WinSockManager::SetMessage(char* res){
	messages[lastMessageIndex] = res;
	lastMessageIndex = (lastMessageIndex + 1) % 100; // 100 = array length
}

void WinSockManager::ProcessMessageCore(){
	int lastProcessedMessageIndex = 0;
	while (true)
	{
		if (lastMessageIndex == lastProcessedMessageIndex) continue;
		char* income = messages[lastProcessedMessageIndex];
		char* answer = "Answer";
		Send(answer, strlen(answer));
		lastProcessedMessageIndex = (lastProcessedMessageIndex + 1) % 100; // 100 = array length
	}
}

bool WinSockManager::Reconnect() { 
	/*
	int result = closesocket(this->s);
	if (result == SOCKET_ERROR) {
		int error = WSAGetLastError();
		DefaultLogManager::Default->EndLog(false, ConsoleManager::GetErrorText(error));
		return false;
	}

	this->s = socket(AF_INET, SOCK_STREAM, 0);
	if (this->s == INVALID_SOCKET) {
		int error = WSAGetLastError();
		DefaultLogManager::Default->EndLog(false, ConsoleManager::GetErrorText(error));
		return false;
	}
	
	result = connect(this->s, (const sockaddr*)&(this->sin), sizeof(this->sin));
	if (result == SOCKET_ERROR) {
		int error = WSAGetLastError();
		DefaultLogManager::Default->EndLog(false, ConsoleManager::GetErrorText(error));
		return false;
	}
	*/
	return true;
}

bool WinSockManager::TryFixSocketError(int errorCode) {
	return true;
}