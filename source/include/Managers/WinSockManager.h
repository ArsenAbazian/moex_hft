#pragma once
#include "Types.h"
#include <stdint.h>
#include "SocketBufferManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <thread>
#include <stdio.h>
#include <thread>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
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
	SocketBuffer 			*m_sendBuffer;
	SocketBuffer			*m_recvBuffer;

public:
	SocketBufferProvider(SocketBufferManager *manager, unsigned int sendSize, unsigned int sendItemsCount, unsigned int recvSize, unsigned int recvItemsCount)
			: m_manager(manager),
			m_sendSize(sendSize),
			m_recvSize(recvSize),
			m_sendItemsCount(sendItemsCount),
			m_recvItemsCount(recvItemsCount) {
		this->m_sendBuffer = this->m_recvBuffer = 0;
	}
	~SocketBufferProvider() {
	}

	SocketBuffer *SendBuffer() {
		if(this->m_sendBuffer == 0)
			this->m_sendBuffer = this->m_manager->GetFreeBuffer(this->m_sendSize, this->m_sendItemsCount);
		return this->m_sendBuffer;
	}
	SocketBuffer *RecvBuffer() {
		if(this->m_recvBuffer == 0)
			this->m_recvBuffer = this->m_manager->GetFreeBuffer(this->m_recvSize, this->m_recvItemsCount);
		return this->m_recvBuffer;
	}
};

class TestMessagesHelper;
class WinSockManager {
	friend class TestMessagesHelper;

	static struct pollfd			*m_pollFd;
	static int 						*m_recvCount;
	static int 						m_pollFdCount;
	static int						m_registeredCount;
	static WinSockManager			**m_registeredManagers;
	static int 						m_pollRes;

	int                             m_socket;
	sockaddr_in                     m_adress;
	ip_mreq_source					m_imr;
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
private:

	inline int GetFreePollIndex() { return WinSockManager::m_registeredCount; }
	inline void IncPollIndex() { WinSockManager::m_registeredCount++;  }
	void RegisterPoll();

	inline void UpdatePoll() {
		WinSockManager::m_pollFd[this->m_pollIndex].fd = this->m_socket;
	}

	void InitializePollInfo();
	inline bool ReconnectFast() {
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

		this->m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->m_socket < 0) {
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		if(bind(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress)) < 0) {
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		if(setsockopt(this->m_socket, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char*)&(this->m_imr), sizeof(this->m_imr)) < 0) {
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		this->UpdatePoll();

		this->m_connected = true;
		DefaultLogManager::Default->EndLog(true);
		return true;
	}

	inline bool ReconnectTcp() {
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
		this->m_socket = socket(AF_INET,
								SOCK_STREAM,
								IPPROTO_TCP);
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

public:
	WinSockManager();
	~WinSockManager();

	inline static bool UpdateManagersPollStatus() {
#ifdef TEST
        return true;
#else
		WinSockManager::m_pollRes = poll(WinSockManager::m_pollFd, WinSockManager::m_registeredCount, 0);
		if(WinSockManager::m_pollRes == -1) {
			DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcWinSockManager_UpdateManagersPollStatus, false)->m_errno = errno;
			return false;
		}
		else if(WinSockManager::m_pollRes == 0)
			return true;

		int *recv = WinSockManager::m_recvCount;
		struct pollfd *pl = WinSockManager::m_pollFd;
		for(int i = 0; i < WinSockManager::m_registeredCount; i++, recv++, pl++) {
			*recv += pl->revents;
			pl->revents = 0;
		}
		return true;
#endif
	}

	inline static bool HasRecvEvents() { return WinSockManager::m_pollRes > 0; }

	bool Connect(char *server_address, unsigned short server_port);
	bool ConnectMulticast(char *sourceIP, char *groupIp, unsigned short groupPort);
	bool Disconnect();

	inline bool Reconnect() {
		if(this->m_connectionType == WinSockConnectionType::wsTCP)
			return this->ReconnectTcp();
		return this->ReconnectFast();
	}

	bool TryFixSocketError(int socketError);

	inline bool Resend() { return this->Send(this->SendBytes(), this->SendSize()); }
	inline bool Send(unsigned char *buffer, int size) {
        this->m_sendBytes = buffer;
        this->m_sendSize = size;
        this->m_sendSizeActual = send(this->m_socket, this->m_sendBytes, size, 0);
#ifdef TEST
		this->m_sendSizeActual = this->m_sendSize;
#else
		if(this->m_sendSizeActual != this->m_sendSize) {
            return false;
        }
#endif
        return true;
	}

	inline bool ShouldRecv() { return WinSockManager::m_recvCount[this->m_pollIndex] > 0; }
	inline void OnRecv() {
		//if(this->ShouldRecv())
		WinSockManager::m_recvCount[this->m_pollIndex] = 0;//--;
	}

	bool RecvTest(unsigned char *buffer);

	inline bool Recv(unsigned char *buffer) {
		if(!this->ShouldRecv()) {
			this->m_recvSize = 0;
			return true;
		}
#ifdef TEST
        return RecvTest(buffer);
#else
		if(this->m_connectionType == WinSockConnectionType::wsTCP)
			return this->RecvTCP(buffer);
		return this->RecvUDP(buffer);
#endif
	}

	inline bool RecvTCP(unsigned char *buffer) {
		this->m_recvBytes = buffer;
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
		if(this->m_recvSize < 0)
            return false;
		this->OnRecv();
		if(this->m_recvSize == 0) {
			//this->Reconnect();
            return false; // do nothing
		}
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

