#pragma once

#include "WinSockManager.h"
#include "FixProtocolManager.h"
#include "Stopwatch.h"

class MarketServerInfo;

typedef enum _MarketServerInfoProcessMessageResultValue {
	msiMsgResProcessed,
	msiMsgResFailed,
	msiMsgResProcessedExit
}MsiMessageProcessResult;

typedef bool (MarketServerInfo::*MarketServerInfoWorkAtomPtr)();
typedef MsiMessageProcessResult (MarketServerInfo::*MarketServerInfoOnReceiveMessagePtr)(FixProtocolMessage *msg);

typedef enum _MarketServerState {
    mssConnect,
    mssSendLogon,
	mssSendLogonRepeat,
	mssSendLogout,
    mssSendTestRequest,
	mssSendResendRequest,
	mssRecvMessage,
	mssResendLastMessage,
    mssResendMessageSeq,
    mssEnd,
	mssDoNothing,
	mssPanic
}MarketServerState;

class MarketServerInfo {
	char									m_name[128];
	int     								m_nameLogIndex;
	char									m_internetAddress[32];
	int										m_internetPort;
	char									m_targetComputerId[128];
	int										m_targetComputerIdLength;
	char									m_astsServerName[128];
	char									m_senderComputerId[128];
	int										m_senderComputerIdLength;
	char									m_password[16];
	int										m_passwordLength;
    int                             		m_testRequestId;
	MarketServerState						m_state;
	MarketServerState						m_sendState;
	MarketServerInfoWorkAtomPtr				m_workAtomPtr;
	MarketServerInfoOnReceiveMessagePtr		m_onMessagePtrArray[256];

    MarketServerState						m_nextState;
    MarketServerInfoWorkAtomPtr				m_nextWorkAtomPtr;
	bool									m_shouldRecvMessage;

    bool                                    m_shouldResendMessages;
    unsigned int                            m_resendBeginSeqNo;
    unsigned int                            m_resendEndSeqNo;
    unsigned int                            m_resendCurrentSeqNo;

    bool                                    m_inSendResendRequest;

    WinSockManager					        *m_socketManager;
	FixProtocolManager				        *m_fixManager;
	FixLogonInfo					        *m_logonInfo;
	Stopwatch						        *m_stopwatch;
	FixResendRequestInfo			        *m_resendRequestInfo;

	virtual ISocketBufferProvider*	CreateSocketBufferProvider();
	FixLogonInfo* CreateLogonInfo();
	void Clear();

    inline void ResendMessages(FixResendRequestInfo *info) {
        this->m_shouldResendMessages = true;
        this->m_resendBeginSeqNo = info->BeginSeqNo;
        this->m_resendEndSeqNo = info->EndSeqNo;
        if(this->m_resendEndSeqNo == 0)
            this->m_resendEndSeqNo = this->m_fixManager->SendMsgSeqNumber();
        this->m_resendCurrentSeqNo = this->m_resendBeginSeqNo;
        this->SetState(MarketServerState::mssResendMessageSeq, &MarketServerInfo::ResendMessageSeq_Atom);
    }

    inline bool CheckNeedResendNextMessage() {
        if(this->m_resendCurrentSeqNo > this->m_resendEndSeqNo) {
            this->m_shouldResendMessages = false;
            this->SetState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);
            return false;
        }
        else {
            this->SetState(MarketServerState::mssResendMessageSeq, &MarketServerInfo::ResendMessageSeq_Atom);
        }
        return true;
    }

	inline void SaveSendState() { this->m_sendState = this->m_state; }
	inline bool AfterSuccessfulSend() {
		this->SaveSendState();
		this->m_fixManager->IncSendMsgSeqNumber();
		this->SetState(MarketServerState::mssRecvMessage, &MarketServerInfo::RecvMessage_Atom);
		DefaultLogManager::Default->EndLog(true);
		return true;
	}

    inline bool AfterFailedRecv() {
        return true;
    }
    inline bool AfterSuccessfulRecv() {
        return true;
    }
	inline bool AfterFailedSend() {
		this->SaveSendState();
		this->SetState(MarketServerState::mssResendLastMessage, &MarketServerInfo::ResendLastMessage_Atom);
		DefaultLogManager::Default->EndLog(false);
		return true;
	}
	inline bool SendCore(bool shouldRecvAnswer) {
		this->m_shouldRecvMessage = shouldRecvAnswer;
		if(!this->m_fixManager->SendFix(this->m_socketManager))
			return this->AfterFailedSend();
		return this->AfterSuccessfulSend();
	}
    inline bool RecvCore() {
        if(!this->m_fixManager->RecvFix(this->m_socketManager))
            return this->AfterFailedRecv();
        return this->AfterSuccessfulRecv();
    }

	void InitializeOnMessagePtrArray();
	inline bool ProcessMessages(int startIndex) {
		if(startIndex >= this->m_fixManager->RecvMessageCount())
			return true;

		DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ProcessMessages);
		for(int i = startIndex; i < this->m_fixManager->RecvMessageCount(); i++) {
			MsiMessageProcessResult res = ProcessMessage(i);
			if(res == msiMsgResFailed) {
				DefaultLogManager::Default->EndLog(false);
				this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
				return false;
			}
			if(res == msiMsgResProcessedExit)
				break;
		}

		DefaultLogManager::Default->EndLog(true);
		return true;
	}
	inline bool ProcessMessages() { return this->ProcessMessages(0); }
	MsiMessageProcessResult ProcessMessage(int index) {
		DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ProcessMessage);
		FixProtocolMessage *msg = this->m_fixManager->Message(index);

		if(!msg->ProcessCheckHeader()) {
			DefaultLogManager::Default->EndLog(false);
			return msiMsgResFailed;
		}

		MarketServerInfoOnReceiveMessagePtr  funcPtr = this->m_onMessagePtrArray[(unsigned int)msg->Header()->msgType];
		MsiMessageProcessResult res = (this->*funcPtr)(msg);
		if(res == msiMsgResFailed) {
			DefaultLogManager::Default->EndLog(false);
			return res;
		}

		this->m_fixManager->IncRecvMsgSeqNumber();
		DefaultLogManager::Default->EndLog(true);
		return res;
	}

	MsiMessageProcessResult OnReceiveUnsupportedMessage(FixProtocolMessage *msg) {
		return MsiMessageProcessResult::msiMsgResProcessed;
	}
	MsiMessageProcessResult OnReceiveHearthBeatMessage(FixProtocolMessage *msg);
	MsiMessageProcessResult OnReceiveLogoutMessage(FixProtocolMessage *msg);
	MsiMessageProcessResult OnReceiveLogonMessage(FixProtocolMessage *msg);
	MsiMessageProcessResult OnReceiveResendRequestMessage(FixProtocolMessage *msg);
	MsiMessageProcessResult OnReceiveTestRequestMessage(FixProtocolMessage *msg);

    bool Reconnect_Atom();
    bool ResendLastMessage_Atom();
	bool ResendMessageSeq_Atom();
    bool RecvMessage_Atom();
	bool SendResendRequest_Atom();
    bool SendTestRequest_Atom();
	bool SendLogon_Atom();
	bool Panic_Atom();
    bool DoNothing_Atom();
	bool SendLogout_Atom();
public:
	MarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName);
	~MarketServerInfo();

	inline const char*	Name() { return this->m_name; }
	inline const char*	InternetAddress() { return this->m_internetAddress; }
	inline const int	InternetPort() { return this->m_internetPort; }
	inline const char*	TargetComputerId() { return this->m_targetComputerId; }
	inline const int	TargetComputerIdLength() { return this->m_targetComputerIdLength; }
	inline const char*	SenderComputerId() { return this->m_senderComputerId; }
	inline const int	SenderComputerIdLength() { return this->m_senderComputerIdLength; }
	inline const char*	Password() { return this->m_password; }
	inline const int	PasswordLength() { return this->m_passwordLength; }
	inline const char*	ASTSServerName() { return this->m_astsServerName; }

	inline WinSockManager* SocketManager() { return this->m_socketManager; }
	inline FixProtocolManager* FixManager() { return this->m_fixManager; }
    inline MarketServerState State() { return this->m_state; }

    bool End_Atom();

    bool Connect();
	bool Disconnect();

	inline void SetState(MarketServerState state, MarketServerInfoWorkAtomPtr funcPtr) {
		this->m_state = state;
		this->m_workAtomPtr = funcPtr;
	}

    inline void SetNextState(MarketServerState state, MarketServerInfoWorkAtomPtr funcPtr) {
        this->m_nextState = state;
        this->m_nextWorkAtomPtr = funcPtr;
    }

    inline void ReconnectSetNextState(MarketServerState state, MarketServerInfoWorkAtomPtr funcPtr) {
        this->SetNextState(state, funcPtr);
        this->SetState(MarketServerState::mssConnect, &MarketServerInfo::Reconnect_Atom);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState, this->m_nextWorkAtomPtr);
    }

	inline bool DoWorkAtom() {
#ifdef ROBOT_WORK_ANYWAY
		if(!this->m_socketManager->IsConnected())
			return true;
#endif
		return (this->*m_workAtomPtr)();
	}

	inline bool Working() { return this->m_state != MarketServerState::mssEnd; }
};

class TradeMarketServerInfo : public MarketServerInfo {
public:
	TradeMarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) :
			MarketServerInfo(name, internetAddress, internetPort, senderComputerId, password, targetComputerId, astsServerName) {}
};

class TradeCaptureMarketServerInfo : public MarketServerInfo {
public:
	TradeCaptureMarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) :
			MarketServerInfo(name, internetAddress, internetPort, senderComputerId, password, targetComputerId, astsServerName) {}
};

class TradeDropCopyMarketServerInfo : public MarketServerInfo {
public:
	TradeDropCopyMarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) :
			MarketServerInfo(name, internetAddress, internetPort, senderComputerId, password, targetComputerId, astsServerName) { }
};

