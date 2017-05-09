#pragma once
#include "../Settings.h"
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
    unsigned int            m_sendSize;
    unsigned int            m_recvSize;
    unsigned int            m_sendItemsCount;
    unsigned int            m_recvItemsCount;
    SocketBufferManager     *m_manager;
    SocketBuffer            *m_sendBuffer;
    SocketBuffer            *m_recvBuffer;

public:
    SocketBufferProvider(SocketBufferManager *manager, unsigned int sendSize, unsigned int sendItemsCount, unsigned int recvSize, unsigned int recvItemsCount)
            : m_sendSize(sendSize),
            m_recvSize(recvSize),
            m_sendItemsCount(sendItemsCount),
            m_recvItemsCount(recvItemsCount),
            m_manager(manager) {
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
    static TestMessagesHelper       *m_testHelper;
private:
#endif

    static struct pollfd            *m_pollFd;
    static int                      m_pollFdCount;
    static int                      m_registeredCount;
    static WinSockManager           **m_registeredManagers;
    static int                      m_pollRes;

    int                             m_socket;
    //bool                            m_shouldRecv;
    struct pollfd                   *m_poll;
    sockaddr_in                     m_adress;
    struct sockaddr					*m_senderAddr;
    socklen_t 						m_senderAddrLength;
    ip_mreq_source                  m_imr;
    unsigned int                    m_addressSize;
    WinSockConnectionType           m_connectionType;
    char                            m_fullAddress[64];
    int                             m_serverAddressLogIndex;

    bool                            m_connected;
    unsigned char                   *m_tempBuffer;
    int                             m_sendSize;
    int                             m_sendSizeActual;
    int                             m_recvSize;
    unsigned char                   *m_recvBytes;
    unsigned char                   *m_sendBytes;

    WinSockStatus                   m_sendStatus;
    WinSockStatus                   m_recvStatus;

    int                             m_pollIndex;

    LogMessageCode                  m_socketLogName;

    inline int GetFreePollIndex() { return WinSockManager::m_registeredCount; }
    inline void IncPollIndex() { WinSockManager::m_registeredCount++;  }
    inline void RegisterPoll() {
        this->m_pollIndex = this->GetFreePollIndex();
        this->m_poll = &(WinSockManager::m_pollFd[this->m_pollIndex]);

        this->m_poll->fd = this->m_socket;
        this->m_poll->events = POLLIN;
        WinSockManager::m_registeredManagers[this->m_pollIndex] = this;

        WinSockManager::IncPollIndex();
        return;
    }

    inline void UpdatePoll() {
        this->m_poll->fd = this->m_socket;
    }

    inline void InitializePollInfo() {
        memset(WinSockManager::m_pollFd, 0, sizeof(struct pollfd) * 256);
        memset(WinSockManager::m_registeredManagers, 0, sizeof(WinSockManager*) * 256);
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
        this->m_socket = -1;
        this->UpdatePoll();

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
        //DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Reconnect, this->m_serverAddressLogIndex);

        if(this->m_connected) {
            shutdown(this->m_socket, SHUT_RDWR);
            this->m_connected = false;
        }

        int result = close(this->m_socket);
        if (result < 0) {
            //DefaultLogManager::Default->EndLog(false, strerror(errno));
            return false;
        }

        this->m_socket = -1;
        this->UpdatePoll();

        this->m_connected = false;
        this->m_socket = socket(AF_INET,
                                SOCK_STREAM,
                                IPPROTO_TCP);
        if (this->m_socket < 0) {
            //DefaultLogManager::Default->EndLog(false, strerror(errno));
            return false;
        }

        result = connect(this->m_socket, (const sockaddr*)&(this->m_adress), sizeof(this->m_adress));
        if (result < 0) {
            //DefaultLogManager::Default->EndLog(false, strerror(errno));
            return false;
        }

        this->UpdatePoll();

        this->m_connected = true;
        //DefaultLogManager::Default->EndLog(true);
        return true;
    }

public:
    WinSockManager();
    ~WinSockManager();

    inline struct pollfd* PollFd() { return this->m_poll; }

    inline static bool UpdateManagersPollStatus() {
#ifdef TEST
        return true;
#else
        // TODO check it that we do not need to !!!!!!
        WinSockManager::m_pollRes = poll(WinSockManager::m_pollFd, WinSockManager::m_registeredCount, 0);
        /* There is no need to check this since there was no error ever after calling poll
         *
        if(WinSockManager::m_pollRes == -1) {
            DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcWinSockManager_UpdateManagersPollStatus, false)->m_errno = errno;
            return false;
        }
        else
        */
        /*
        if(WinSockManager::m_pollRes == 0)
            return true;


        WinSockManager **man = WinSockManager::m_registeredManagers;
        for(int i = 0; i < WinSockManager::m_registeredCount; i++, man++) {
            (*man)->UpdatePollStatusCore();
        }*/
        return true;
#endif
    }

    inline LogMessageCode SocketLogName() { return this->m_socketLogName; };
    inline void SocketLogName(LogMessageCode code) { this->m_socketLogName = code; }
    inline static bool HasRecvEvents() { return WinSockManager::m_pollRes > 0; }

    inline int Socket() const { return this->m_socket; }

    inline bool Connect(char *server_address, unsigned short server_port) {
        this->m_connectionType = WinSockConnectionType::wsTCP;
        sprintf(this->m_fullAddress, "%s:%d (TCP)", server_address, server_port);
        this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_fullAddress);

        //DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Connect, this->m_serverAddressLogIndex);

        this->m_connected = false;
        this->m_socket = socket(AF_INET,
                                SOCK_STREAM,
                                IPPROTO_TCP);

        if (this->m_socket < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }

        this->UpdatePoll();

        this->m_addressSize = sizeof(sockaddr_in);
        memset(&this->m_adress, 0, sizeof(sockaddr_in));
        inet_pton(AF_INET, server_address, &(this->m_adress.sin_addr));
        this->m_adress.sin_family = AF_INET;
        this->m_adress.sin_port = htons(server_port);

#ifndef TEST
        int result = connect(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress));
        if(result < 0) {
            close(this->m_socket);
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }
#endif

		//DefaultLogManager::Default->EndLog(true);
		this->m_connected = true;
		return true;
	}
    inline bool StartUdpServer(int port) {
#ifdef TEST
        return true;
#else
        this->m_connectionType = WinSockConnectionType::wsUDP;
        this->m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (this->m_socket < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }
        this->UpdatePoll();

        int flag = 1;
        if(setsockopt(this->m_socket,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }

        memset(&(this->m_adress), 0, sizeof(sockaddr_in));
        this->m_adress.sin_family = AF_INET;
        this->m_adress.sin_addr.s_addr = htonl(INADDR_ANY);
        this->m_adress.sin_port = htons((unsigned short)port);

        if(bind(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress)) < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }
        this->PrintSocketInfo();

        //DefaultLogManager::Default->EndLog(true);
        this->m_connected = true;
        return true;
#endif
    }
	inline bool ConnectMulticast(char *sourceIp, char *groupIp, unsigned short groupPort) {
#ifdef TEST
        return true;
#else
        this->m_connectionType = WinSockConnectionType::wsUDP;

        sprintf(this->m_fullAddress, "%s-%s:%d (UDP)", sourceIp, groupIp, groupPort);
        this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_fullAddress);

        //DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_ConnectFast, this->m_serverAddressLogIndex);

        this->m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (this->m_socket < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }
        this->UpdatePoll();

        int flag = 1;
        if(setsockopt(this->m_socket,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }

        this->m_addressSize = sizeof(sockaddr_in);
        memset(&this->m_adress, 0, sizeof(sockaddr_in));
        this->m_adress.sin_addr.s_addr = htonl(INADDR_ANY);
        this->m_adress.sin_family = AF_INET;
        this->m_adress.sin_port = htons(groupPort);

        if(bind(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress)) < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }

        UINT32 group = inet_addr(groupIp);
        UINT32 source = inet_addr(sourceIp);

        this->m_imr.imr_multiaddr.s_addr = group;
        this->m_imr.imr_sourceaddr.s_addr = source;
        this->m_imr.imr_interface.s_addr = INADDR_ANY;

        if(setsockopt(this->m_socket, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char*)&(this->m_imr), sizeof(this->m_imr)) < 0) {
            //DefaultLogManager::Default->EndLogErrNo(false, strerror(errno));
            return false;
        }

        //this->PrintSocketInfo();



        //DefaultLogManager::Default->EndLog(true);
        this->m_connected = true;
        return true;
#endif
    }
    inline bool Disconnect() {
#ifdef TEST
        return true;
#else

        if (this->m_socket == -1)
            return true;

        //DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Close, this->m_serverAddressLogIndex);
        if (this->m_connected) {
            shutdown(this->m_socket, SHUT_RDWR);
            this->m_connected = false;
        }

        int result = close(this->m_socket);
        if (result != 0) {
            //DefaultLogManager::Default->EndLog(false, strerror(errno));
            return false;
        }
        this->m_socket = -1;
        this->UpdatePoll();

        //DefaultLogManager::Default->EndLog(true);
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
    inline bool SendTo(struct sockaddr *target, socklen_t targetLength, unsigned char *buffer, int size) {
        this->m_sendBytes = buffer;
        this->m_sendSize = size;
#ifdef TEST
        this->m_sendSizeActual = this->m_sendSize;
        this->SendTest();
#else
        this->m_sendSizeActual = sendto(this->m_socket, this->m_sendBytes, size, 0, target, targetLength);
        if(this->m_sendSizeActual != this->m_sendSize) {
            return false;
        }
#endif
        return true;
    }

//#ifdef TEST
    void SendTest();
//#endif

    inline void UpdatePollStatus() {
        poll(this->m_poll, 1, 0);
    }
    inline bool ShouldRecv() {
#ifdef TEST
        return ShouldRecvTest();
#else
        return this->m_poll->revents & (POLLIN | POLLPRI);
#endif
    }
#ifdef TEST
    bool ShouldRecvTest();
#endif
    inline void OnRecv() {
        this->m_poll->revents = 0;
    }

    bool RecvTest(unsigned char *buffer);

    inline bool RecvFrom(unsigned char *buffer, struct sockaddr *senderAddr, socklen_t *length) {
        if(!this->ShouldRecv()) {
            this->m_recvSize = 0;
            return true;
        }
#ifdef TEST
        return RecvTest(buffer);
#else
        if(this->m_connectionType == WinSockConnectionType::wsTCP)
            return this->RecvFromTCP(buffer, senderAddr, length);
        return this->RecvUDP(buffer, senderAddr, length);
#endif
    }

	inline bool Recv(unsigned char *buffer) {
		if(!this->ShouldRecv()) {
			this->m_recvSize = 0;
			return true;
		}
#ifdef TEST
        return RecvTest(buffer);
#else
        if(this->m_connectionType == WinSockConnectionType::wsTCP)
            return this->RecvTCPCore(buffer);
        return this->RecvUDPCore(buffer);
#endif
    }

    inline bool RecvTCP(unsigned char *buffer) {
        if(!this->ShouldRecv()) {
            this->m_recvSize = 0;
            return true;
        }
#ifdef TEST
        return RecvTest(buffer);
#else
        return this->RecvTCPCore(buffer);
#endif
    }

    inline bool RecvUDP(unsigned char *buffer) {
        if(!this->ShouldRecv()) {
            this->m_recvSize = 0;
            return true;
        }
#ifdef TEST
        return RecvTest(buffer);
#else
        return this->RecvUDPCore(buffer);
#endif
    }

    inline void FlushUDP() {
        if(!this->ShouldRecv())
            return;
        this->FlushUDPCore();
    }

    inline bool RecvTCPCore(unsigned char *buffer) {
        this->m_recvBytes = buffer;
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
        if(this->m_recvSize < 0)
            return false;
        this->OnRecv();
        return this->m_recvSize != 0;
    }
    inline bool RecvFromTCP(unsigned char *buffer, struct sockaddr *senderAddr, socklen_t *length) {
        this->m_recvBytes = buffer;
        *length = sizeof(struct sockaddr);
        this->m_recvSize = recvfrom(this->m_socket, this->m_recvBytes, 8192, 0, senderAddr, length);
        if(this->m_recvSize < 0)
            return false;
        this->OnRecv();
        return this->m_recvSize != 0;
    }
    inline bool RecvUDP(unsigned char *buffer, struct sockaddr *senderAddr, socklen_t *length) {
        this->m_recvBytes = buffer;
        *length = sizeof(struct sockaddr);
        this->m_recvSize = recvfrom(this->m_socket, this->m_recvBytes, 8192, 0, (struct sockaddr *)senderAddr, length);
        if(this->m_recvSize > 0) {
            this->OnRecv();
            return true;
        }
        return false;
    }
    inline void FlushUDPCore() {
        recvfrom(this->m_socket, this->m_tempBuffer, 8192, 0, 0, 0);
        this->OnRecv();
    }
    inline bool RecvUDPCore(unsigned char *buffer) {
        this->m_recvBytes = buffer;
        this->m_recvSize = recv(this->m_socket, this->m_recvBytes, 8192, 0);
        if(this->m_recvSize > 0) {
            this->OnRecv();
            return true;
        }
        return false;
    }
    inline struct sockaddr* SenderAddress() const { return this->m_senderAddr; }
    inline bool IsConnected() const { return this->m_connected; }
    inline int RecvSize() const { return this->m_recvSize; }
    inline unsigned char* RecvBytes() { return this->m_recvBytes; }
    inline int SendSize() const { return this->m_sendSize; }
    inline int ActualSendSize() const { return this->m_sendSizeActual; }
    inline unsigned char* SendBytes() { return this->m_sendBytes; }
};

