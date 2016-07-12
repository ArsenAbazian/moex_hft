#pragma once
#include "Types.h"
#include <stdint.h>
#include "ProtocolHistoryManager.h"

class WinSockManager
{
	static int ManagersCount;

	//WSADATA wsa;
	//SOCKET s;
	//sockaddr_in sin;
	bool connected;
	int lastReceivedBytes;
	char *receivedBytes;
public:
	WinSockManager();
	~WinSockManager();

	int Initialize(char *server_adress, unsigned short server_port);
	int Close();
	void WaitEnter();
	void Failed();
	void Done(); 
	bool Reconnect();

	bool TryFixSocketError(int socketError);

	inline bool Send(char *frame, int frameLength) { 
		/*
		register int bytesSend = send(s, frame, frameLength, 0);
		if (bytesSend == SOCKET_ERROR) { 
			if (TryFixSocketError(WSAGetLastError()))
				return send(s, frame, frameLength, 0) != SOCKET_ERROR;
			return false;
		}*/
		return true;

	}
	inline bool Recv(char *frame, int maxFrameLength) {
		/*
		this->lastReceivedBytes = recv(s, frame, maxFrameLength, 0);
		if (this->lastReceivedBytes == 0) { // connection was gracefullty closed - try to reconnect?
			return Reconnect();
		}
		else if (this->lastReceivedBytes == SOCKET_ERROR) {
			if (TryFixSocketError(WSAGetLastError())) { // ok, we miss datagramm but at least fixed socket
				this->receivedBytes = 0;
				return true;
			}
			return false;
		}*/
		return true;
	}
	
	inline bool Recv(HistoryItemType receivedItemType) { 
		/*
		this->receivedBytes = DefaultFixProtocolHistoryManager::defaultManager->Buffer();
		register bool result = Recv(this->receivedBytes, 128000);
		if (result) { 
			this->receivedBytes[this->ReceivedBytesCount()] = '\0';
			DefaultFixProtocolHistoryManager::defaultManager->Increment(this->ReceivedBytesCount(), receivedItemType);
		}*/
		//return result;
		return true;
	}
	inline bool IsConnected() { return this->connected; }
	inline int ReceivedBytesCount() { return this->lastReceivedBytes; }
	inline char* ReceivedBytes() { return this->receivedBytes; }

	void Run();
	void RunCore();
	void SetMessage(char* message);
	void ProcessMessageCore();
	int lastMessageIndex = 0;
	char* messages[100];
};

