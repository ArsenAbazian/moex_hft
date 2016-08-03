#pragma once
#include "Types.h"
#include <stdint.h>
#include "SocketBufferManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <thread>
#include "LogManager.h"

typedef enum _WinSockConnectionType{
	wsTCP,
	wsUDP
}WinSockConnectionType;

typedef enum _WinSockStatus {
    wssOk,
    wssFailed,
    wssWaitRecv
}WinSockStatus;

typedef struct _PacketInfo {
    unsigned char*  buffer;
    unsigned int    size;
}PacketInfo;


class ISocketBufferProvider {
public:
    virtual SocketBuffer* SendBuffer() = 0;
    virtual SocketBuffer* RecvBuffer() = 0;
};

class SocketBufferProvider : public ISocketBufferProvider {
	unsigned int 			m_sendSize;
	unsigned int			m_recvSize;
	unsigned int 			m_sendItemsCount;
	unsigned int			m_recvItemsCount;
	SocketBufferManager		*m_manager;
public:
	SocketBufferProvider(SocketBufferManager *manager, unsigned int sendSize, unsigned int sendItemsCount, unsigned int recvSize, unsigned int recvItemsCount)
			: m_manager(manager),
			m_sendSize(sendSize),
			m_recvSize(recvSize),
			m_sendItemsCount(sendItemsCount),
			m_recvItemsCount(recvItemsCount) { }

	SocketBuffer *SendBuffer() { return this->m_manager->GetFreeBuffer(this->m_sendSize, this->m_sendItemsCount); }
	SocketBuffer *RecvBuffer() { return this->m_manager->GetFreeBuffer(this->m_recvSize, this->m_recvItemsCount); }
};

class WinSockManager {
	int                             m_socket;
	sockaddr_in                     m_adress;
	WinSockConnectionType           m_connectionType;
	char 							m_fullAddress[64];
	int 			                m_serverAddressLogIndex;

    bool                            m_connected;
	int                             m_sendSize;
    int                             m_sendSizeActual;
    int                             m_recvSize;
	unsigned char                   *m_recvBytes;
    unsigned char                   *m_sendBytes;

    WinSockStatus                   m_sendStatus;
    WinSockStatus                   m_recvStatus;


public:
	WinSockManager();
	~WinSockManager();

	bool Connect(char *server_address, unsigned short server_port) {
		return Connect(server_address, server_port, WinSockConnectionType::wsTCP);
	}
	bool Connect(char *server_address, unsigned short server_port, WinSockConnectionType type);
	bool Disconnect();
	bool Reconnect();
	bool TryFixSocketError(int socketError);

	inline bool Resend() { return this->Send(this->SendBytes(), this->SendSize()); }
	inline bool Send(unsigned char *buffer, int size) {
        this->m_sendBytes = buffer;
        this->m_sendSize = size;
        this->m_sendSizeActual = send(this->m_socket, this->m_sendBytes, size, 0);
        if(this->m_sendSizeActual != this->m_sendSize) {
            return false;
        }
        return true;
	}

	inline bool Recv(unsigned char *buffer) {
		this->m_recvBytes = buffer;
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
        if (this->m_recvSize < 0)
            return false;
		else if(this->m_recvSize == 0) {
			this->Reconnect();
            return false; // do nothing
		}
        return true;
	}
	inline bool IsConnected() { return this->m_connected; }
	inline int RecvSize() { return this->m_recvSize; }
	inline unsigned char* RecvBytes() { return this->m_recvBytes; }
    inline int SendSize() { return this->m_sendSize; }
    inline int ActualSendSize() { return this->m_sendSizeActual; }
    inline unsigned char* SendBytes() { return this->m_sendBytes; }
};

