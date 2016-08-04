#pragma once
#include "Types.h"
#include <stdint.h>
#include "SocketBufferManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <thread>
#include "LogManager.h"
#include <sys/poll.h>

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

class WinSockManager;
class WinSockManager {
	static struct pollfd			*m_pollFd;
	static int 						*m_recvCount;
	static int 						m_pollFdCount;
	static int						m_registeredCount;
	static WinSockManager			**m_registeredManagers;
	static int 						m_pollRes;

	int                             m_socket;
	sockaddr_in                     m_adress;
	unsigned int					m_addressSize;
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

	int								m_pollIndex;

	inline int GetFreePollIndex() { return WinSockManager::m_registeredCount; }
	inline void IncPollIndex() { WinSockManager::m_registeredCount++;  }
	void RegisterPoll();

	inline void UpdatePoll() {
		WinSockManager::m_pollFd[this->m_pollIndex].fd = this->m_socket;
	}

	void InitializePollInfo();

public:
	WinSockManager();
	~WinSockManager();

	inline static bool UpdateManagersPollStatus() {
		WinSockManager::m_pollRes = poll(WinSockManager::m_pollFd, WinSockManager::m_registeredCount, 0);
		if(WinSockManager::m_pollRes == -1) {
			DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcWinSockManager_UpdateManagersPollStatus, false)->m_errno = errno;
			return false;
		}
		else if(WinSockManager::m_pollRes == 0)
			return true;
		for(int i = 0; i < WinSockManager::m_pollFdCount; i++) {
			WinSockManager::m_recvCount[i] += WinSockManager::m_pollFd[i].revents;
			WinSockManager::m_pollFd[i].revents = 0;
		}
		return true;
	}

	inline static bool HasRecvEvents() { return WinSockManager::m_pollRes > 0; }

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

	inline bool ShouldRecv() { return WinSockManager::m_recvCount[this->m_pollIndex] > 0; }
	inline void OnRecv() {
		if(this->ShouldRecv())
			WinSockManager::m_recvCount[this->m_pollIndex]--;
	}

	inline bool Recv(unsigned char *buffer) {
		if(!this->ShouldRecv()) {
			this->m_recvSize = 0;
			return true;
		}
		if(this->m_connectionType == WinSockConnectionType::wsTCP)
			return this->RecvTCP(buffer);
		return this->RecvUDP(buffer);
	}

	inline bool RecvTCP(unsigned char *buffer) {
		this->m_recvBytes = buffer;
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
		if (this->m_recvSize < 0)
            return false;
		if(this->m_recvSize == 0) {
			this->Reconnect();
            return false; // do nothing
		}
		this->OnRecv();
        return true;
	}
	inline bool RecvUDP(unsigned char *buffer) {
		this->m_recvBytes = buffer;
		this->m_addressSize = sizeof(sockaddr_in);
		this->m_recvSize = recvfrom(this->m_socket, this->m_recvBytes, 8192, 0, (struct sockaddr*)&(this->m_adress), &(this->m_addressSize));
		if(this->m_recvSize > 0) {
			this->OnRecv();
			return true;
		}
		return false;
	}
	inline bool IsConnected() { return this->m_connected; }
	inline int RecvSize() { return this->m_recvSize; }
	inline unsigned char* RecvBytes() { return this->m_recvBytes; }
    inline int SendSize() { return this->m_sendSize; }
    inline int ActualSendSize() { return this->m_sendSizeActual; }
    inline unsigned char* SendBytes() { return this->m_sendBytes; }
};

