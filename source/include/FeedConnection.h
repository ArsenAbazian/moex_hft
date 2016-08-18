#pragma once
#include "WinSockManager.h"
#include "FastProtocolManager.h"
#include "Types.h"
#include <sys/time.h>
#include "Stopwatch.h"

typedef enum _FeedConnectionProtocol {
	TCP_IP,
	UDP_IP
}FeedConnectionProtocol;

typedef enum _FeedConnectionState {
	fcsSuspend,
	fcsListen,
    fcsSendLogon,
    fcsResendLastMessage,
    fcsConnect
} FeedConnectionState;

typedef enum _FeedConnectionProcessMessageResultValue {
	fcMsgResProcessed,
	fcMsgResFailed,
	fcMsgResProcessedExit
}FeedConnectionProcessMessageResultValue;

class FeedConnection;
typedef bool (FeedConnection::*FeedConnectionWorkAtomPtr)();

class FeedConnection {
	const int MaxReceiveBufferSize = 1500;
protected:
	char										id[16];
	char										feedTypeName[64];

	int     									m_idLogIndex;
	int 										m_feedTypeNameLogIndex;

	char										feedTypeValue;

	FeedConnectionProtocol 						protocol;

	char										feedASourceIp[64];
	char										feedAIp[64];
	int											feedAPort;

	char										feedBSourceIp[64];
	char										feedBIp[64];
	int											feedBPort;

	int											m_msgSeqNo;

    const char                                  *m_senderCompId;
    int                                         m_senderCompIdLength;
    const char                                  *m_password;
    int                                         m_passwordLength;

	WinSockManager								*socketAManager;
	WinSockManager								*socketBManager;
	FastProtocolManager 						*m_fastProtocolManager;
    FastLogonInfo                               *m_fastLogonInfo;

	ISocketBufferProvider						*m_socketABufferProvider;
	ISocketBufferProvider						*m_socketBBufferProvider;
	SocketBuffer								*m_sendABuffer;
	SocketBuffer								*m_recvABuffer;
	SocketBuffer								*m_sendBBuffer;
	SocketBuffer								*m_recvBBuffer;

	FeedConnectionState							m_state;
	FeedConnectionWorkAtomPtr					m_workAtomPtr;

	FeedConnectionState							m_nextState;
	FeedConnectionWorkAtomPtr					m_nextWorkAtomPtr;
	bool										m_shouldUseNextState;

    struct timeval                              *m_tval;
    Stopwatch                                   *m_stopwatch;
    bool                                        m_shouldReceiveAnswer;

    inline void GetCurrentTime(UINT64 *time) {
        gettimeofday(this->m_tval, NULL);
        *time = this->m_tval->tv_usec / 1000;
    }
	inline bool CanListen() { return this->socketAManager->ShouldRecv() || this->socketBManager->ShouldRecv(); }
	inline void IncrementMsgSeqNo() { this->m_msgSeqNo++; }
	bool InitializeSockets();
	virtual ISocketBufferProvider* CreateSocketBufferProvider() {
			return new SocketBufferProvider(DefaultSocketBufferManager::Default,
											RobotSettings::DefaultFeedConnectionSendBufferSize,
											RobotSettings::DefaultFeedConnectionSendItemsCount,
											RobotSettings::DefaultFeedConnectionRecvBufferSize,
											RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
	inline void SetState(FeedConnectionState state, FeedConnectionWorkAtomPtr funcPtr) {
		this->m_state = state;
		this->m_workAtomPtr = funcPtr;
	}
	inline void SetNextState(FeedConnectionState state, FeedConnectionWorkAtomPtr funcPtr) {
		this->m_nextState = state;
		this->m_nextWorkAtomPtr = funcPtr;
		this->m_shouldUseNextState = true;
	}

	bool Suspend_Atom();
	bool Listen_Atom();
    bool SendLogon_Atom();
    bool ResendLastMessage_Atom();
    bool Reconnect_Atom();

    inline void ReconnectSetNextState(FeedConnectionState state, FeedConnectionWorkAtomPtr funcPtr) {
        this->SetNextState(state, funcPtr);
        this->SetState(FeedConnectionState::fcsConnect, &FeedConnection::Reconnect_Atom);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState, this->m_nextWorkAtomPtr);
    }

    inline bool SendCore() {
        this->m_sendABuffer->SetCurrentItemSize(this->m_fastProtocolManager->MessageLength());
        DefaultLogManager::Default->WriteFast(LogMessageCode::lmcFeedConnection_SendCore, this->m_sendABuffer->BufferIndex(), this->m_sendABuffer->CurrentItemIndex());
        if(!this->socketAManager->Send(this->m_fastProtocolManager->Buffer(), this->m_fastProtocolManager->MessageLength())) {
            this->SetState(FeedConnectionState::fcsResendLastMessage, &FeedConnection::ResendLastMessage_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }

        this->m_sendABuffer->Next(this->m_fastProtocolManager->MessageLength());
        this->SetState(FeedConnectionState::fcsListen, &FeedConnection::Listen_Atom);
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

	inline bool ProcessMessage(SocketBuffer *buffer, int size) {
		this->m_fastProtocolManager->SetNewBuffer(buffer->CurrentPos(), size);
        buffer->Next(size);
        DefaultLogManager::Default->WriteFast(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_ProcessMessage, buffer->BufferIndex(), buffer->CurrentItemIndex() - 1);
        int msgSeqNo = this->m_fastProtocolManager->ReadMsgSeqNumber();
		//if(msgSeqNo == this->ExpectedMsgSeqNo()) {
			this->Decode();
            return true;
		//}
		//return true;
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	~FeedConnection();

	bool Connect();
	bool Disconnect();

    void SetSenderCompId(const char *senderCompId) {
        this->m_senderCompId = senderCompId;
        if(this->m_senderCompId == NULL)
            this->m_senderCompIdLength = 0;
        else
            this->m_senderCompIdLength = strlen(this->m_senderCompId);
    }
    void SetPassword(const char *password) {
        this->m_password = password;
        this->m_passwordLength = strlen(this->m_password);
    }

    inline char* Id() { return this->id; }

	inline virtual void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_Generic();
		DefaultLogManager::Default->EndLog(true);
	}

	inline int MsgSeqNo() { return this->m_msgSeqNo; }
	inline int ExpectedMsgSeqNo() { return this->m_msgSeqNo + 1; }

	inline bool DoWorkAtom() {
		return (this->*m_workAtomPtr)();
	}
	inline void Listen() {
		if(this->m_state == FeedConnectionState::fcsSuspend)
			this->SetState(FeedConnectionState::fcsListen, &FeedConnection::Listen_Atom);
		else
			this->SetNextState(FeedConnectionState::fcsListen, &FeedConnection::Listen_Atom);
	}
    inline void Start() {
        if(this->m_state != FeedConnectionState::fcsSuspend)
            return;
        this->Listen();
        //this->SetState(FeedConnectionState::fcsSendLogon, &FeedConnection::SendLogon_Atom);
    }
};

class FeedConnection_CURR_OBR : public FeedConnection {
public:
	FeedConnection_CURR_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OBR_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OBS : public FeedConnection {
public:
	FeedConnection_CURR_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OBS_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSR : public FeedConnection {
public:
	FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_MSR_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSS : public FeedConnection {
public:
	FeedConnection_CURR_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
	FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OLR_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLS : public FeedConnection {
public:
	FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OLS_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
	FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_TLR_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLS : public FeedConnection {
public:
	FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_TLS_CURR();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBR : public FeedConnection {
public:
	FeedConnection_FOND_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OBR_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBS : public FeedConnection {
public:
	FeedConnection_FOND_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OBS_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
	FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_MSR_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSS : public FeedConnection {
public:
	FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
	FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OLR_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLS : public FeedConnection {
public:
	FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_OLS_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
	FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_TLR_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLS : public FeedConnection {
public:
	FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode_TLS_FOND();
		DefaultLogManager::Default->EndLog(true);
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

