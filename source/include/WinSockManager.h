#pragma once
#include "Types.h"
#include <stdint.h>
#include "SocketBufferManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

typedef enum _WinSockConnectionType{
	wsTCP,
	wsUDP
}WinSockConnectionType;

class WinSockManager
{
	static int ManagersCount;

	int             m_socket;
	sockaddr_in     m_adress;
	WinSockConnectionType m_connectionType;
	int 			m_serverAddressLogIndex;

    bool connected;
	int lastReceivedBytes;
	char *receivedBytes;
public:
	WinSockManager();
	~WinSockManager();

	bool Connect(char *server_address, unsigned short server_port) {
		return Connect(server_address, server_port, WinSockConnectionType::wsTCP);
	}
	bool Connect(char *server_address, unsigned short server_port, WinSockConnectionType type);
	bool Disconnect();
	void WaitEnter();
	void Failed();
	void Done(); 
	bool Reconnect();

	bool TryFixSocketError(int socketError);

	inline bool Send(char *frame, int frameLength) { 
        int bytesSend = send(this->m_socket, frame, frameLength, 0);
		if (bytesSend < 0) {
			if (TryFixSocketError(errno))
				return send(this->m_socket, frame, frameLength, 0) >= 0;
			return false;
		}
		return true;

	}
	inline bool Recv(char *frame, int maxFrameLength) {
		this->lastReceivedBytes = recv(this->m_socket, frame, maxFrameLength, 0);
		if (this->lastReceivedBytes == 0) { // connection was gracefullty closed - try to reconnect?
			return Reconnect();
		}
		else if (this->lastReceivedBytes < 0) {
			if (TryFixSocketError(errno)) { // ok, we miss datagramm but at least fixed socket
				this->receivedBytes = 0;
				return true;
			}
			return false;
		}
		return true;
	}
	
	inline bool Recv() {
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

