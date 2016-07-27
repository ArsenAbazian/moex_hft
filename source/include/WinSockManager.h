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
    ISocketBufferProvider           *m_bufferProvider;
    SocketBuffer                    *m_sendBuffer;
    SocketBuffer                    *m_recvBuffer;

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

	inline bool SendFix(int size) {
        BinaryLogItem *item = DefaultLogManager::Default->WriteFix(LogMessageCode::lmcWinSockManager_SendFix, this->m_sendBuffer->BufferIndex(), this->m_sendBuffer->CurrentItemIndex());
        this->m_sendBytes = this->m_sendBuffer->CurrentPos();
        this->m_sendSize = send(this->m_socket, this->m_sendBytes, size, 0);
		if (this->m_sendSize < 0) {
            item->m_result = false;
            item->m_errno = errno;
            return false;
		}
        item->m_result = true;
        this->m_sendBuffer->Next(this->m_sendSize);
		return true;
	}

	inline bool RecvFix() {
		BinaryLogItem *item = NULL;
		this->m_recvBytes = this->m_recvBuffer->CurrentPos();
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
        if (this->m_recvSize < 0) {
			item = DefaultLogManager::Default->WriteFix(LogMessageCode::lmcWinSockManager_RecvFix, -1, -1);
			item->m_errno = errno;
            item->m_result = false;
            return false;
        }
		else if(this->m_recvSize == 0) {
			return false; // do nothing
		}
		item = DefaultLogManager::Default->WriteFix(LogMessageCode::lmcWinSockManager_RecvFix, this->m_recvBuffer->BufferIndex(), this->m_recvBuffer->CurrentItemIndex());
        item->m_result = true;
        this->m_recvBuffer->Next(this->m_recvSize);
        return true;
	}
	inline bool IsConnected() { return this->m_connected; }
	inline int RecvSize() { return this->m_recvSize; }
	inline unsigned char* RecvBytes() { return this->m_recvBytes; }
    inline int SendSize() { return this->m_sendSize; }
    inline unsigned char* SendBytes() { return this->m_sendBytes; }
};

