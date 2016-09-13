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

typedef enum _FeedConnectionType {
    Incremental,
    Snapshot
}FeedConnectionType;

class FeedConnection {
	const int MaxReceiveBufferSize = 1500;
    const int WaitIncrementalMaxTimeSec         = 5;
    const int WaitAnyPacketMaxTimeSec           = 10;
protected:
	char										id[16];
	char										feedTypeName[64];

    FeedConnectionType                          m_type;
    FeedConnection                              *m_incremental;
    FeedConnection                              *m_snapshot;
	int 										m_snapshotStartMsgSeqNum;
	int											m_snapshotEndMsgSeqNum;
    int                                         m_snapshotRouteFirst;
    int                                         m_snapshotLastFragment;
    int                                         m_lastMsgSeqNumProcessed;
    int                                         m_snapshotAvailable;

    BinaryLogItem                               **m_packets;

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

	int											m_currentMsgSeqNum;
    int                                         m_maxRecvMsgSeqNum;

    const char                                  *m_senderCompId;
    int                                         m_senderCompIdLength;
    const char                                  *m_password;
    int                                         m_passwordLength;

    bool                                        m_waitingSnapshot;

	WinSockManager								*socketAManager;
	WinSockManager								*socketBManager;
	FastProtocolManager 						*m_fastProtocolManager;
    FastLogonInfo                               *m_fastLogonInfo;

	ISocketBufferProvider						*m_socketABufferProvider;
	SocketBuffer								*m_sendABuffer;
	SocketBuffer								*m_recvABuffer;

	FeedConnectionState							m_state;
	FeedConnectionWorkAtomPtr					m_workAtomPtr;

	FeedConnectionState							m_nextState;
	FeedConnectionWorkAtomPtr					m_nextWorkAtomPtr;
	bool										m_shouldUseNextState;

	FeedConnectionWorkAtomPtr					m_listenPtr;

    struct timeval                              *m_tval;
    Stopwatch                                   *m_stopwatch;
    Stopwatch                                   *m_waitTimer;
    bool                                        m_shouldReceiveAnswer;

    inline void GetCurrentTime(UINT64 *time) {
        gettimeofday(this->m_tval, NULL);
        *time = this->m_tval->tv_usec / 1000;
    }

	inline bool CanListen() { return this->socketAManager->ShouldRecv() || this->socketBManager->ShouldRecv(); }

    inline bool ProcessServerA() { return this->ProcessServer(this->socketAManager, LogMessageCode::lmcsocketA); }
    inline bool ProcessServerB() { return this->ProcessServer(this->socketBManager, LogMessageCode::lmcsocketB); }
    inline bool ProcessServer(WinSockManager *socketManager, LogMessageCode socketName) {
        if(!socketManager->ShouldRecv())
            return false;
        if(!socketManager->Recv(this->m_recvABuffer->CurrentPos())) {
            DefaultLogManager::Default->WriteSuccess(socketName,
                                                     LogMessageCode::lmcFeedConnection_Listen_Atom,
                                                     false)->m_errno = errno;
            socketManager->Reconnect();
            return false;
        }
        int size = socketManager->RecvSize();
        if(size == 0)
            return false;
        UINT msgSeqNum = *((UINT*)socketManager->RecvBytes());
        if(msgSeqNum < this->ExpectedMsgSeqNo() || this->m_packets[msgSeqNum] != 0)
            return false;

        this->m_recvABuffer->SetCurrentItemSize(size);
        BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
                                                                    this->m_recvABuffer->BufferIndex(),
                                                                    this->m_recvABuffer->CurrentItemIndex());
        if(this->m_type == FeedConnectionType::Incremental) {
            if (this->m_maxRecvMsgSeqNum < msgSeqNum)
                this->m_maxRecvMsgSeqNum = msgSeqNum;
        }
        else {
            if(this->m_snapshotStartMsgSeqNum == -1)
                this->m_snapshotStartMsgSeqNum = msgSeqNum;
            if(this->m_snapshotEndMsgSeqNum < msgSeqNum)
                this->m_snapshotEndMsgSeqNum = msgSeqNum;
        }
        this->m_packets[msgSeqNum] = item;
        this->m_recvABuffer->Next(size);
        return true;
    }
    inline bool WaitingSnapshot() { return this->m_waitingSnapshot; }
    inline bool SnapshotAvailable() { return this->m_snapshotAvailable; }
    inline bool ApplySnapshot() { throw; }
    inline bool ApplyPacketSequence() {
        int i = this->m_currentMsgSeqNum;
        bool processed = false;
        while(i <= this->m_maxRecvMsgSeqNum) {
            if(this->m_packets[i] == 0) {
                this->m_currentMsgSeqNum = i - 1;
                return processed;
            }
            this->ProcessMessage(this->m_packets[i]);
            processed = true;
            i++;
        }
        this->m_currentMsgSeqNum = i;
        return processed;
    }
    inline void StartListenSnapshot() {
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, true);
        this->m_waitingSnapshot = true;
		this->m_snapshot->Start();
		this->m_snapshot->StartNewSnapshot();
	}
	inline void StopListenSnapshot() {
		this->m_snapshot->Stop();
	}
	inline bool CheckForRouteFirst(BinaryLogItem *item) {
		unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
		this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
		FastSnapshotInfo* info = this->m_fastProtocolManager->GetSnapshotInfo();
        return info->RouteFirst == 1;
    }
    inline bool CheckForLastFragment(BinaryLogItem *item, int *refMsgSeqNum) {
        unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
        this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
        FastSnapshotInfo* info = this->m_fastProtocolManager->GetSnapshotInfo();
        *refMsgSeqNum = info->LastMsgSeqNumProcessed;
        return info->LastFragment == 1;
    }
	inline int GetRouteFirst() {
		while(this->m_snapshotStartMsgSeqNum <= this->m_snapshotEndMsgSeqNum) {
			if(this->CheckForRouteFirst(this->m_packets[this->m_currentMsgSeqNum])) {
                DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_GetRouteFirst, true);
                return this->m_snapshotStartMsgSeqNum;
            }
            this->m_snapshotStartMsgSeqNum++;
		}
		return -1;
	}
    inline int GetLastFragment(int *refMsgSeqNum) {
        while(this->m_snapshotStartMsgSeqNum <= this->m_snapshotEndMsgSeqNum) {
            if (this->CheckForLastFragment(this->m_packets[this->m_currentMsgSeqNum], refMsgSeqNum)) {
                DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_GetLastFragment, false);
                return this->m_snapshotStartMsgSeqNum;
            }
            this->m_snapshotStartMsgSeqNum++;
        }
        return -1;
    }
    inline void ResetWaitTime() { this->m_waitTimer->Start(); }
    inline void StartWaitIncremental() { this->m_waitingSnapshot = false; }
    inline bool ActualMsgSeqNum() { return this->m_currentMsgSeqNum == this->m_maxRecvMsgSeqNum; }

	inline void IncrementMsgSeqNo() { this->m_currentMsgSeqNum++; }
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
    bool Listen_Atom_Incremental();
    bool Listen_Atom_Snapshot();
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
        this->SetState(FeedConnectionState::fcsListen, this->m_listenPtr);
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

	inline bool ProcessMessage(BinaryLogItem *item) {
        unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
        this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
        this->Decode();
        return true;
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	~FeedConnection();

    inline int LastMsgSeqNumProcessed() { return this->m_lastMsgSeqNumProcessed; }

    inline void StartNewSnapshot() {
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartNewSnapshot, true);
        this->m_snapshotAvailable = false;
        this->m_snapshotEndMsgSeqNum =
        this->m_snapshotStartMsgSeqNum = -1;
        this->m_snapshotRouteFirst =
        this->m_snapshotLastFragment = -1;
    }

    inline void SetType(FeedConnectionType type) {
        this->m_type = type;
        this->m_listenPtr = this->m_type == FeedConnectionType::Incremental? &FeedConnection::Listen_Atom_Incremental: &FeedConnection::Listen_Atom_Snapshot;
    }
    inline FeedConnectionType Type() { return this->m_type; }

    inline void SetIncremental(FeedConnection *conn) {
		if(this->m_incremental == conn)
			return;
		this->m_incremental = conn;
		if(this->m_incremental != 0)
			this->m_incremental->SetSnapshot(this);
	}
    inline FeedConnection *Incremental() { return this->m_incremental; }

    inline void SetSnapshot(FeedConnection *conn) {
		if(this->m_snapshot == conn)
			return;
		this->m_snapshot = conn;
		if(this->m_snapshot != 0)
			this->m_snapshot->SetIncremental(this);
	}
    inline FeedConnection *Snapshot() { return this->m_snapshot; }

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

		DefaultLogManager::Default->EndLog(true);
	}

	inline int MsgSeqNo() { return this->m_currentMsgSeqNum; }
	inline int ExpectedMsgSeqNo() { return this->m_currentMsgSeqNum + 1; }

	inline bool DoWorkAtom() {
		return (this->*m_workAtomPtr)();
	}
	inline void Listen() {
		if(this->m_state == FeedConnectionState::fcsSuspend)
			this->SetState(FeedConnectionState::fcsListen, this->m_listenPtr);
		else
			this->SetNextState(FeedConnectionState::fcsListen, this->m_listenPtr);
	}
    inline void Start() {
        if(this->m_state != FeedConnectionState::fcsSuspend)
            return;
        this->m_waitTimer->Start();
        this->Listen();
    }
	inline void Stop() {
		this->SetState(FeedConnectionState::fcsSuspend, &FeedConnection::Suspend_Atom);
	}
};

class FeedConnection_CURR_OBR : public FeedConnection {
public:
	FeedConnection_CURR_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {

        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {

        this->m_type = FeedConnectionType::Snapshot;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Incremental;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::Snapshot;
    }
	inline void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
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

