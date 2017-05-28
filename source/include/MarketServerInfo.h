#pragma once

#include "Managers/WinSockManager.h"
#include "Fix/FixProtocolManager.h"
#include "Stopwatch.h"
#include <stdlib.h>

class MarketServerInfo;

typedef enum class _MarketServerInfoProcessMessageResultValue : uint8_t {
    msiMsgResProcessed,
    msiMsgResFailed,
    msiMsgResProcessedExit
} MsiMessageProcessResult;

typedef enum class _MarketServerState : uint8_t{
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
} MarketServerState;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
class MarketServerInfo {
    WinSockManager                          *m_socketManager;
    FixProtocolManager                      *m_fixManager;
    FixLogonInfo                            *m_logonInfo;
    Stopwatch                               *m_stopwatch;
    FixResendRequestInfo                    *m_resendRequestInfo;

    MarketServerState                       m_state;
    MarketServerState                       m_sendState;
    MarketServerState                       m_nextState;

    char                                    m_name[128];
    int                                     m_nameLogIndex;
    char                                    m_internetAddress[32];
    int                                     m_internetPort;
    char                                    m_targetComputerId[128];
    int                                     m_targetComputerIdLength;
    char                                    m_astsServerName[128];
    char                                    m_senderComputerId[128];
    int                                     m_senderComputerIdLength;
    char                                    m_password[16];
    int                                     m_passwordLength;
    int                                     m_testRequestId;

    unsigned int                            m_resendBeginSeqNo;
    unsigned int                            m_resendEndSeqNo;
    unsigned int                            m_resendCurrentSeqNo;

    bool                                    m_inSendResendRequest;
    bool                                    m_shouldRecvMessage;
    bool                                    m_shouldResendMessages;

    virtual ISocketBufferProvider*  CreateSocketBufferProvider();
    FixLogonInfo* CreateLogonInfo();
    void Clear();

    inline void ResendMessages(FixResendRequestInfo *info) {
        this->m_shouldResendMessages = true;
        this->m_resendBeginSeqNo = info->BeginSeqNo;
        this->m_resendEndSeqNo = info->EndSeqNo;
        if(this->m_resendEndSeqNo == 0)
            this->m_resendEndSeqNo = this->m_fixManager->SendMsgSeqNo();
        this->m_resendCurrentSeqNo = this->m_resendBeginSeqNo;
        this->SetState(MarketServerState::mssResendMessageSeq);
    }

    inline bool CheckNeedResendNextMessage() {
        if(this->m_resendCurrentSeqNo > this->m_resendEndSeqNo) {
            this->m_shouldResendMessages = false;
            this->SetState(MarketServerState::mssDoNothing);
            return false;
        }
        else {
            this->SetState(MarketServerState::mssResendMessageSeq);
        }
        return true;
    }

    inline void SaveSendState() { this->m_sendState = this->m_state; }
    inline bool AfterSuccessfulSend() {
        this->SaveSendState();
        this->m_fixManager->IncSendMsgSeqNo();
        this->SetState(MarketServerState::mssRecvMessage);
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool AfterFailedRecv() {
        return this->m_socketManager->Reconnect();
    }
    inline bool AfterSuccessfulRecv() {
        return true;
    }
    inline bool AfterFailedSend() {
        this->SaveSendState();
        this->SetState(MarketServerState::mssResendLastMessage);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    inline bool SendCore(bool shouldRecvAnswer) {
        this->m_shouldRecvMessage = shouldRecvAnswer;
        if(!this->m_fixManager->SendFix(this->m_socketManager))
            return this->AfterFailedSend();
        return this->AfterSuccessfulSend();
    }
    inline bool CanRecv() { return this->m_socketManager->ShouldRecv(); }
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
            if(res == MsiMessageProcessResult::msiMsgResFailed) {
                DefaultLogManager::Default->EndLog(false);
                this->SetState(MarketServerState::mssPanic);
                return false;
            }
            if(res == MsiMessageProcessResult::msiMsgResProcessedExit)
                break;
        }

        DefaultLogManager::Default->EndLog(true);
        return true;
    }
    inline bool ProcessMessages() { return this->ProcessMessages(0); }
    MsiMessageProcessResult ProcessMessageCore(char msgType, FixProtocolMessage *msg) {
        switch(msgType) {
            case MsgTypeHearthBeat:
                return OnReceiveHearthBeatMessage(msg);
            case MsgTypeResendRequest:
                return OnReceiveResendRequestMessage(msg);
            case MsgTypeLogon:
                return OnReceiveLogonMessage(msg);
            case MsgTypeLogout:
                return OnReceiveLogoutMessage(msg);
            case MsgTypeTestRequest:
                return OnReceiveTestRequestMessage(msg);
            case MsgTypeReject:
                return OnReceiveReject(msg);
            default:
                return OnReceiveUnsupportedMessage(msg);
        }
    }

    MsiMessageProcessResult ProcessMessage(int index) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ProcessMessage);
        FixProtocolMessage *msg = this->m_fixManager->Message(index);

        if(!msg->ProcessCheckHeader()) {
            DefaultLogManager::Default->EndLog(false);
            return MsiMessageProcessResult::msiMsgResFailed;
        }

        MsiMessageProcessResult res = this->ProcessMessageCore(msg->Header()->msgType, msg);
        if(res == MsiMessageProcessResult::msiMsgResFailed) {
            DefaultLogManager::Default->EndLog(false);
            return res;
        }

        this->m_fixManager->IncRecvMsgSeqNo();
        DefaultLogManager::Default->EndLog(true);
        return res;
    }

    inline MsiMessageProcessResult OnReceiveUnsupportedMessage(FixProtocolMessage *msg) {
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

    inline MsiMessageProcessResult OnReceiveReject(FixProtocolMessage *msg) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveReject);

        this->SetState(MarketServerState::mssDoNothing);

        DefaultLogManager::Default->EndLog(true);
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

    inline MsiMessageProcessResult OnReceiveHearthBeatMessage(FixProtocolMessage *msg) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveHearthBeatMessage);

        this->SetState(MarketServerState::mssDoNothing);

        DefaultLogManager::Default->EndLog(true);
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

    inline MsiMessageProcessResult OnReceiveResendRequestMessage(FixProtocolMessage *msg) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveResendRequestMessage);

        if(!msg->CheckProcessResendRequest()) {
            DefaultLogManager::Default->EndLog(false);
            return MsiMessageProcessResult::msiMsgResFailed;
        }

        this->ResendMessages(msg->ResendRequestInfo());

        DefaultLogManager::Default->EndLog(true);
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

    inline MsiMessageProcessResult OnReceiveLogonMessage(FixProtocolMessage *msg) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveLogonMessage);
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->m_stopwatch->StartFast();
        this->SetState(MarketServerState::mssDoNothing);

        DefaultLogManager::Default->EndLog(true);
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

    inline MsiMessageProcessResult OnReceiveLogoutMessage(FixProtocolMessage *msg) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveLogoutMessage);

        if(this->m_sendState == MarketServerState::mssSendLogout) {
            this->SetState(MarketServerState::mssEnd);
        }
        else if(this->m_sendState == MarketServerState::mssSendLogon) {
            int msgSeqNumber = 1;
            if(msg->CheckDetectCorrectMsgSeqNumber(&msgSeqNumber)) {
                this->m_fixManager->SetRecvMsgSeqNo(msgSeqNumber - 1); // Oh nooo!!! Stupid code due to IncMsgSeqNo later... TODO refactor later
                this->m_logonInfo->MsgStartSeqNo = msgSeqNumber;
                this->ReconnectSetNextState(MarketServerState::mssSendLogon);
                DefaultLogManager::Default->EndLog(true);
                return MsiMessageProcessResult::msiMsgResProcessedExit;
            }
            else {
                this->SetState(MarketServerState::mssPanic);
                DefaultLogManager::Default->EndLog(false);
                return MsiMessageProcessResult::msiMsgResProcessed;
            }
        }

        DefaultLogManager::Default->EndLog(true);
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

    inline MsiMessageProcessResult OnReceiveTestRequestMessage(FixProtocolMessage *msg) {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveTestRequestMessage);



        DefaultLogManager::Default->EndLog(true);
        return MsiMessageProcessResult::msiMsgResProcessed;
    }

public:
    MarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName);
    ~MarketServerInfo();

    inline const char*  Name() { return this->m_name; }
    inline const char*  InternetAddress() { return this->m_internetAddress; }
    inline const int    InternetPort() { return this->m_internetPort; }
    inline const char*  TargetComputerId() { return this->m_targetComputerId; }
    inline const int    TargetComputerIdLength() { return this->m_targetComputerIdLength; }
    inline const char*  SenderComputerId() { return this->m_senderComputerId; }
    inline const int    SenderComputerIdLength() { return this->m_senderComputerIdLength; }
    inline const char*  Password() { return this->m_password; }
    inline const int    PasswordLength() { return this->m_passwordLength; }
    inline const char*  ASTSServerName() { return this->m_astsServerName; }

    inline WinSockManager* SocketManager() { return this->m_socketManager; }
    inline FixProtocolManager* FixManager() { return this->m_fixManager; }
    inline MarketServerState State() { return this->m_state; }

    bool Connect();
    bool Disconnect();

    inline void SetState(MarketServerState state) {
        this->m_state = state;
    }

    inline void SetNextState(MarketServerState state) {
        this->m_nextState = state;
    }

    inline void ReconnectSetNextState(MarketServerState state) {
        this->SetNextState(state);
        this->SetState(MarketServerState::mssConnect);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState);
    }

    inline bool ResendMessageSeq_Atom() {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ResendMessageSeq_Atom);

        char *msgBuffer = 0;
        int msgSize = 0;

        if(!this->m_fixManager->FindSendMessageInHistory(this->m_resendCurrentSeqNo, &msgBuffer, &msgSize)) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        DefaultLogManager::Default->WriteFix(LogMessageCode::lmcMarketServerInfo_ResendMessageSeq_Atom, this->m_fixManager->SendSocketBuffer()->BufferIndex(), this->m_resendCurrentSeqNo - 1);
        if(!this->m_socketManager->Send((unsigned char*)msgBuffer, msgSize)) {
            this->ReconnectSetNextState(MarketServerState::mssResendMessageSeq);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        if(this->m_shouldRecvMessage) {
            this->SetState(MarketServerState::mssRecvMessage);
            this->m_shouldRecvMessage = false;
        }
        else {
            this->m_resendCurrentSeqNo++;
            this->CheckNeedResendNextMessage();
        }

        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool ResendLastMessage_Atom() {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ResendLastMessage_Atom);

        if(!this->m_socketManager->Resend()) {
            this->ReconnectSetNextState(MarketServerState::mssResendLastMessage);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        if(this->m_shouldRecvMessage) {
            this->SetState(MarketServerState::mssRecvMessage);
            this->m_shouldRecvMessage = false;
        }
        else
            this->SetState(MarketServerState::mssDoNothing);

        this->m_fixManager->IncSendMsgSeqNo();
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool RecvMessage_Atom() {
        if(!this->CanRecv())
            return true;

        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvMessage_Atom);

        if(!this->RecvCore()) {
            this->ReconnectSetNextState(MarketServerState::mssResendLastMessage);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        this->m_fixManager->ProcessSplitRecvMessages();

        if(!this->ProcessMessages()) {
            DefaultLogManager::Default->EndLog(false);
            return true;
        }

        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool Reconnect_Atom() {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Reconnect_Atom);

        if(!this->m_socketManager->Reconnect()) {
            DefaultLogManager::Default->EndLog(false);
            return true;
        }

        this->SetState(this->m_nextState);
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool SendLogon_Atom() {

        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendLogon_Atom);

        this->m_fixManager->PrepareSendBuffer();
        this->m_fixManager->CreateLogonMessage(this->m_logonInfo);
        return this->SendCore(true);
    }

    inline bool SendResendRequest_Atom(){

        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendResendRequest_Atom);

        this->m_fixManager->PrepareSendBuffer();
        this->m_inSendResendRequest = true;
        this->m_fixManager->CreateResendRequestMessage(this->m_resendRequestInfo->BeginSeqNo, this->m_resendRequestInfo->EndSeqNo);
        return this->SendCore(true);
    }

    inline bool SendLogout_Atom() {

        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendLogout_Atom);

        this->m_fixManager->PrepareSendBuffer();
        this->m_fixManager->CreateLogoutMessage("Hasta la vista baby!");
        return this->SendCore(true);
    }

    inline bool SendTestRequest_Atom() {
        DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendTestRequest_Atom);

        this->m_fixManager->PrepareSendBuffer();
        this->m_testRequestId = rand();
        this->m_fixManager->CreateTestRequestMessage();
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->m_stopwatch->StartFast();
        return this->SendCore(true);
    }

    inline bool End_Atom() {
        return true;
    }

    inline bool DoNothing_Atom() {
        if(this->m_shouldResendMessages) {
            this->m_resendCurrentSeqNo++;
            if(this->CheckNeedResendNextMessage())
                return true;
        }
        if(this->CanRecv()) {
            this->SetState(MarketServerState::mssRecvMessage);
            return true;
        }
        if(this->m_stopwatch->ElapsedSeconds() > 30) {
            this->SetNextState(MarketServerState::mssDoNothing);
            this->SetState(MarketServerState::mssSendTestRequest);
        }
        return true;
    }

    inline bool Panic_Atom() {
        return true;
    }

    inline bool DoWorkAtom() {
#ifdef ROBOT_WORK_ANYWAY
        if(!this->m_socketManager->IsConnected())
            return true;
#endif
        switch(this->m_state) {
            case MarketServerState::mssDoNothing:
                return DoNothing_Atom();
            case MarketServerState::mssSendTestRequest:
                return SendTestRequest_Atom();
            case MarketServerState::mssRecvMessage:
                return RecvMessage_Atom();
            case MarketServerState::mssConnect:
                return Reconnect_Atom();
            case MarketServerState::mssEnd:
                return End_Atom();
            case MarketServerState::mssPanic:
                return Panic_Atom();
            case MarketServerState::mssResendLastMessage:
                return ResendLastMessage_Atom();
            case MarketServerState::mssResendMessageSeq:
                return ResendMessageSeq_Atom();
            case MarketServerState::mssSendLogon:
                return SendLogon_Atom();
            case MarketServerState::mssSendLogout:
                return SendLogout_Atom();
            case MarketServerState::mssSendResendRequest:
                return SendResendRequest_Atom();
            default:
                return true;
            //case MarketServerState::mssSendLogonRepeat:

        }
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

#pragma clang diagnostic pop
