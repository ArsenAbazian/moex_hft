#pragma once
#include "Types.h"
#include <stdint.h>
#include "SocketBufferManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <thread>

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
    ISocketBufferProvider           *m_bufferProvider;
    SocketBuffer                    *m_sendBuffer;
    SocketBuffer                    *m_recvBuffer;

    PacketInfo                      m_freeSendPacket;
    PacketInfo                      *m_sendPacket;

    bool                            m_connected;
	int                             m_sendSize;
    int                             m_recvSize;
	unsigned char                   *m_recvBytes;
    unsigned char                   *m_sendBytes;

    WinSockStatus                   m_sendStatus;
    WinSockStatus                   m_recvStatus;


public:
	WinSockManager(ISocketBufferProvider *provider);
	~WinSockManager();

	bool Connect(char *server_address, unsigned short server_port) {
		return Connect(server_address, server_port, WinSockConnectionType::wsTCP);
	}
	bool Connect(char *server_address, unsigned short server_port, WinSockConnectionType type);
	bool Disconnect();
	bool Reconnect();
	bool TryFixSocketError(int socketError);

    inline unsigned char* GetNextSendBuffer() {
        this->m_sendBuffer->Next(this->m_sendSize);
        return this->m_sendBuffer->CurrentPos();
    }

    inline void WorkSend() {
        if (this->m_sendPacket == NULL)
            return;
        if (!SendCore(this->m_sendPacket->buffer, this->m_sendPacket->size))
            this->m_sendStatus = WinSockStatus::wssFailed;
        this->m_sendPacket = NULL;
    }
    inline void WorkRecv() {
        if(this->m_recvStatus != WinSockStatus::wssWaitRecv)
            return;
        if(!RecvCore())
            this->m_recvStatus = WinSockStatus::wssFailed;
        else
            this->m_recvStatus = WinSockStatus::wssOk;
    }

	inline bool SendCore(unsigned char *sendBytes, int frameLength) {
        this->m_sendSize = send(this->m_socket, sendBytes, frameLength, 0);
		if (this->m_sendSize < 0) {
			if (TryFixSocketError(errno)) {
				this->m_sendSize = send(this->m_socket, sendBytes, frameLength, 0);
                if(this->m_sendSize < 0)
                    return false;
                this->m_sendBuffer->Next(this->m_sendSize);
                return true;
            }
			return false;
		}
        this->m_sendBuffer->Next(this->m_sendSize);
		return true;

	}

	inline bool RecvCore() {
        this->m_recvBytes = this->m_recvBuffer->CurrentPos();
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
        if (this->m_recvSize == 0) { // connection was gracefullty closed - try to reconnect?
            return Reconnect();
        }
        else if (this->m_recvSize < 0) {
            if (TryFixSocketError(errno)) { // ok, we miss datagramm but at least fixed socket
                this->m_recvSize = 0;
                return true;
            }
            return false;
        }
        this->m_recvBuffer->Next(this->m_recvSize);
        return true;
	}
	inline bool IsConnected() { return this->m_connected; }
	inline int RecvSize() { return this->m_recvSize; }
	inline unsigned char* RecvBytes() { return this->m_recvBytes; }
    inline int SendSize() { return this->m_sendSize; }
    inline unsigned char* SendBytes() { return this->m_sendBytes; }
};

