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

#ifdef TEST
public:
	static TestMessagesHelper		*m_testHelper;
private:
#endif

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
	unsigned char					*m_tempBuffer;
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
	inline void RegisterPoll() {
		this->m_pollIndex = this->GetFreePollIndex();

		WinSockManager::m_pollFd[this->m_pollIndex].fd = this->m_socket;
		WinSockManager::m_pollFd[this->m_pollIndex].events = POLLIN;
		WinSockManager::m_registeredManagers[this->m_pollIndex] = this;

		WinSockManager::IncPollIndex();
		return;
	}

	inline void UpdatePoll() {
		WinSockManager::m_pollFd[this->m_pollIndex].fd = this->m_socket;
	}

	inline void InitializePollInfo() {
		bzero(WinSockManager::m_pollFd, sizeof(struct pollfd) * 256);
		bzero(WinSockManager::m_recvCount, sizeof(int) * 256);
		bzero(WinSockManager::m_registeredManagers, sizeof(WinSockManager*) * 256);
	}
	inline void PrintSocketInfo() {
		struct sockaddr_in sin;
		socklen_t  len = sizeof(sin);
		if(getsockname(this->m_socket, (struct sockaddr*)&sin, &len) == -1)
			printf("error getting socket info\n");
		else
			printf("socket %d port %d\n", this->m_socket, sin.sin_port);
	}
	inline bool ReconnectMulticast() {
		DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Reconnect, this->m_serverAddressLogIndex);

		if(this->m_connected) {
			shutdown(this->m_socket, SHUT_RDWR);
			this->m_connected = false;
		}

		int result = close(this->m_socket);
		if (result < 0) {
			DefaultLogManager::Default->Write(LogMessageCode::lmcsocket_close);
			DefaultLogManager::Default->EndLog(false, strerror(errno));
			return false;
		}

		this->m_connected = false;

		this->m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->m_socket < 0) {
			DefaultLogManager::Default->Write(LogMessageCode::lmcsocket_socket);
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		int flag = 1;
		if(setsockopt(this->m_socket,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		if(bind(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress)) < 0) {
			DefaultLogManager::Default->Write(LogMessageCode::lmcsocket_bind);
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		if(setsockopt(this->m_socket, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char*)&(this->m_imr), sizeof(this->m_imr)) < 0) {
			DefaultLogManager::Default->Write(LogMessageCode::lmcsocket_setsockopt);
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		//this->PrintSocketInfo();

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

	inline void UpdatePollStatus() {
		if(poll(&(WinSockManager::m_pollFd[this->m_pollIndex]), 1, 0) == 0)
			return;
		WinSockManager::m_recvCount[this->m_pollIndex] = (WinSockManager::m_pollFd + this->m_pollIndex)->revents;
	}

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

	inline int Socket() { return this->m_socket; }

	inline bool Connect(char *server_address, unsigned short server_port) {
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

#ifndef TEST
		int result = connect(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress));
		if(result < 0) {
			close(this->m_socket);
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}
#endif

		if(this->m_pollIndex == -1)
			this->RegisterPoll();
		else
			this->UpdatePoll();

		DefaultLogManager::Default->EndLog(true);
		this->m_connected = true;
		return true;
	}
	inline bool ConnectMulticast(char *sourceIp, char *groupIp, unsigned short groupPort) {
#ifdef TEST
		return true;
#else
		this->m_connectionType = WinSockConnectionType::wsUDP;

		sprintf(this->m_fullAddress, "%s-%s:%d (UDP)", sourceIp, groupIp, groupPort);
		this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_fullAddress);

		DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_ConnectFast, this->m_serverAddressLogIndex);

		this->m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->m_socket < 0) {
			DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
			return false;
		}

		int flag = 1;
		if(setsockopt(this->m_socket,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
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

		//this->PrintSocketInfo();

		if(this->m_pollIndex == -1)
			this->RegisterPoll();
		else
			this->UpdatePoll();

		DefaultLogManager::Default->EndLog(true);
		this->m_connected = true;
		return true;
#endif
	}
	inline bool Disconnect() {
#ifdef TEST
		return true;
#else
		DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Close, this->m_serverAddressLogIndex);
		if(this->m_socket == -1) {
			DefaultLogManager::Default->EndLog(true);
			return true;
		}

		if(this->m_connected) {
			shutdown(this->m_socket, SHUT_RDWR);
			this->m_connected = false;
		}

//		while(this->ShouldRecv()) {
//			if(!this->Recv(this->m_tempBuffer) || this->m_recvSize == 0)
//				break;
//			// TODO remoove debug
//			printf("has %d bytes after shutdown.\n", this->m_recvSize);
//			this->UpdatePollStatus();
//		}

		int result = close(this->m_socket);
		if (result != 0) {
			DefaultLogManager::Default->EndLog(false, strerror(errno));
			return false;
		}
		DefaultLogManager::Default->EndLog(true);
		return true;
#endif
	}

	inline bool Reconnect() {
		if(this->m_connectionType == WinSockConnectionType::wsTCP)
			return this->ReconnectTcp();
		return this->ReconnectMulticast();
	}

	bool TryFixSocketError(int socketError);

	inline bool Resend() { return this->Send(this->SendBytes(), this->SendSize()); }
	inline bool Send(unsigned char *buffer, int size) {
        this->m_sendBytes = buffer;
        this->m_sendSize = size;
#ifdef TEST
		this->m_sendSizeActual = this->m_sendSize;
		this->SendTest();
#else
		this->m_sendSizeActual = send(this->m_socket, this->m_sendBytes, size, 0);
		if(this->m_sendSizeActual != this->m_sendSize) {
            return false;
        }
#endif
        return true;
	}

//#ifdef TEST
    void SendTest();
//#endif

	inline bool ShouldRecv() {
#ifdef TEST
        return ShouldRecvTest();
#else
		return WinSockManager::m_recvCount[this->m_pollIndex] > 0;
#endif
	}
#ifdef TEST
	bool ShouldRecvTest();
#endif
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

