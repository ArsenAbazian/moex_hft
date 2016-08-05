#include "MarketServerInfo.h"
#include <stdio.h>
#include "LogManager.h"
#include "Stopwatch.h"

MarketServerInfo::MarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) {
	strcpy(this->m_name, name);
    this->m_nameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_name);
	strcpy(this->m_internetAddress, internetAddress);
	this->m_internetPort = internetPort;
	strcpy(this->m_targetComputerId, targetComputerId);
	this->m_targetComputerIdLength = strlen(this->m_targetComputerId);
	strcpy(this->m_astsServerName, astsServerName);
	strcpy(this->m_senderComputerId, senderComputerId);
	this->m_senderComputerIdLength = strlen(this->m_senderComputerId);
	strcpy(this->m_password, password);
	this->m_passwordLength = strlen(this->m_password);
    this->m_stopwatch = new Stopwatch();
    this->m_resendRequestInfo = new FixResendRequestInfo();
    this->InitializeOnMessagePtrArray();
    this->m_inSendResendRequest = false;

    this->SetState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);

    this->m_socketManager = NULL;
    this->m_fixManager = NULL;
    this->m_logonInfo = NULL;
    this->m_shouldResendMessages = false;
}

void MarketServerInfo::InitializeOnMessagePtrArray() {
    for(int i = 0; i < 256; i++)
        this->m_onMessagePtrArray[i] = &MarketServerInfo::OnReceiveUnsupportedMessage;

    this->m_onMessagePtrArray[MsgTypeHearthBeat] = &MarketServerInfo::OnReceiveHearthBeatMessage;
    this->m_onMessagePtrArray[MsgTypeResendRequest] = &MarketServerInfo::OnReceiveResendRequestMessage;
    this->m_onMessagePtrArray[MsgTypeLogon] = &MarketServerInfo::OnReceiveLogonMessage;
    this->m_onMessagePtrArray[MsgTypeLogout] = &MarketServerInfo::OnReceiveLogoutMessage;
    this->m_onMessagePtrArray[MsgTypeTestRequest] = &MarketServerInfo::OnReceiveTestRequestMessage;
    this->m_onMessagePtrArray[MsgTypeReject] = &MarketServerInfo::OnReceiveReject;
}

MsiMessageProcessResult MarketServerInfo::OnReceiveReject(FixProtocolMessage *msg) {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveReject);

    this->SetState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);

    DefaultLogManager::Default->EndLog(true);
    return MsiMessageProcessResult::msiMsgResProcessed;
}

MsiMessageProcessResult MarketServerInfo::OnReceiveHearthBeatMessage(FixProtocolMessage *msg) {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveHearthBeatMessage);

    this->SetState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);

    DefaultLogManager::Default->EndLog(true);
    return MsiMessageProcessResult::msiMsgResProcessed;
}

MsiMessageProcessResult MarketServerInfo::OnReceiveResendRequestMessage(FixProtocolMessage *msg) {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveResendRequestMessage);

    if(!msg->CheckProcessResendRequest()) {
        DefaultLogManager::Default->EndLog(false);
        return MsiMessageProcessResult::msiMsgResFailed;
    }

    this->ResendMessages(msg->ResendRequestInfo());

    DefaultLogManager::Default->EndLog(true);
    return MsiMessageProcessResult::msiMsgResProcessed;
}

MsiMessageProcessResult MarketServerInfo::OnReceiveLogonMessage(FixProtocolMessage *msg) {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveLogonMessage);

    this->m_stopwatch->Start();
    this->SetState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);

    DefaultLogManager::Default->EndLog(true);
    return MsiMessageProcessResult::msiMsgResProcessed;
}

MsiMessageProcessResult MarketServerInfo::OnReceiveLogoutMessage(FixProtocolMessage *msg) {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveLogoutMessage);

    if(this->m_sendState == MarketServerState::mssSendLogout) {
        this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
    }
    else if(this->m_sendState == MarketServerState::mssSendLogon) {
        int msgSeqNumber = 1;
        if(msg->CheckDetectCorrectMsgSeqNumber(&msgSeqNumber)) {
            this->m_fixManager->SetSendMsgSeqNumber(msgSeqNumber);
            this->m_logonInfo->MsgStartSeqNo = msgSeqNumber;
            this->ReconnectSetNextState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
            DefaultLogManager::Default->EndLog(true);
            return MsiMessageProcessResult::msiMsgResProcessedExit;
        }
        else {
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            DefaultLogManager::Default->EndLog(false);
            return MsiMessageProcessResult::msiMsgResProcessed;
        }
    }

    DefaultLogManager::Default->EndLog(true);
    return MsiMessageProcessResult::msiMsgResProcessed;
}

MsiMessageProcessResult MarketServerInfo::OnReceiveTestRequestMessage(FixProtocolMessage *msg) {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_OnReceiveTestRequestMessage);



    DefaultLogManager::Default->EndLog(true);
    return MsiMessageProcessResult::msiMsgResProcessed;
}

bool MarketServerInfo::ResendMessageSeq_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ResendMessageSeq_Atom);

    char *msgBuffer = 0;
    int msgSize = 0;

    if(!this->m_fixManager->FindSendMessageInHistory(this->m_resendCurrentSeqNo, &msgBuffer, &msgSize)) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->WriteFix(LogMessageCode::lmcMarketServerInfo_ResendMessageSeq_Atom, this->m_fixManager->SendSocketBuffer()->BufferIndex(), this->m_resendCurrentSeqNo - 1);
    if(!this->m_socketManager->Send((unsigned char*)msgBuffer, msgSize)) {
        this->ReconnectSetNextState(MarketServerState::mssResendMessageSeq, &MarketServerInfo::ResendMessageSeq_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    if(this->m_shouldRecvMessage) {
        this->SetState(MarketServerState::mssRecvMessage, &MarketServerInfo::RecvMessage_Atom);
        this->m_shouldRecvMessage = false;
    }
    else {
        this->m_resendCurrentSeqNo++;
        this->CheckNeedResendNextMessage();
    }

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::ResendLastMessage_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_ResendLastMessage_Atom);

    if(!this->m_socketManager->Resend()) {
        this->ReconnectSetNextState(MarketServerState::mssResendLastMessage, &MarketServerInfo::ResendLastMessage_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    if(this->m_shouldRecvMessage) {
        this->SetState(MarketServerState::mssRecvMessage, &MarketServerInfo::RecvMessage_Atom);
        this->m_shouldRecvMessage = false;
    }
    else
        this->SetState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);

    this->m_fixManager->IncSendMsgSeqNumber();
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvMessage_Atom() {
    if(!this->CanRecv())
        return true;

    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvMessage_Atom);

    if(!this->RecvCore()) {
        this->ReconnectSetNextState(MarketServerState::mssResendLastMessage, &MarketServerInfo::ResendLastMessage_Atom);
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

void MarketServerInfo::Clear() { 
	if (this->m_fixManager != NULL)
		delete this->m_fixManager;
	if (this->m_socketManager != NULL)
		delete this->m_socketManager;
	if (this->m_logonInfo != NULL)
		delete this->m_logonInfo;
	this->m_logonInfo = NULL;
	this->m_fixManager = NULL;
	this->m_socketManager = NULL;
    delete this->m_stopwatch;
}

FixLogonInfo* MarketServerInfo::CreateLogonInfo() { 
	FixLogonInfo* res = new FixLogonInfo();
	
	strcpy(res->SenderCompID, SenderComputerId());
	res->SenderCompIDLength = strlen(res->SenderCompID);
	strcpy(res->Password, Password());
	res->PassLength = strlen(res->Password);
	res->HearthBtInt = 60;
	res->ShouldResetSeqNum = false;
	res->MsgStartSeqNo = 1;

	return res;
}

bool MarketServerInfo::Reconnect_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Reconnect_Atom);

    if(!this->m_socketManager->Reconnect()) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }

    this->SetState(this->m_nextState, this->m_nextWorkAtomPtr);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::SendLogon_Atom() {

    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendLogon_Atom);

    this->m_fixManager->PrepareSendBuffer();
    this->m_fixManager->CreateLogonMessage(this->m_logonInfo);
    return this->SendCore(true);
}

bool MarketServerInfo::SendResendRequest_Atom(){

    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendResendRequest_Atom);

    this->m_fixManager->PrepareSendBuffer();
    this->m_inSendResendRequest = true;
    this->m_fixManager->CreateResendRequestMessage(this->m_resendRequestInfo->BeginSeqNo, this->m_resendRequestInfo->EndSeqNo);
    return this->SendCore(true);
}

/*
bool MarketServerInfo::RepeatSendLogon_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendLogon_Atom);
    if(!this->m_socketManager->Send(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->SetState(MarketServerState::mssRecvLogon, &MarketServerInfo::RecvLogon_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RepeatSendResendRequest_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendResendRequest_Atom);
    if(!this->m_socketManager->Send(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->SetState(MarketServerState::mssRecvResendRequest, &MarketServerInfo::RecvResendRequest_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvResendRequest_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvResendRequest_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->RecvFix()) {
        this->ReconnectSetNextState(MarketServerState::mssSendLogon, &MarketServerInfo::RepeatSendResendRequest_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvLogon_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvLogon_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->RecvFix()) {
        this->ReconnectSetNextState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->SetRecvMessageBuffer((char*)this->m_socketManager->RecvBytes(), this->m_socketManager->RecvSize());
    if(!this->m_fixManager->ProcessCheckHeader()) {
        this->ReconnectSetNextState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    if(this->m_fixManager->Header()->msgType == MsgTypeLogout) {
        if(this->m_fixManager->CheckDetectCorrectMsgSeqNumber()) {
            this->m_logonInfo->MsgStartSeqNo = this->m_fixManager->SendMsgSeqNumber();
            this->ReconnectSetNextState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        else {
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
    }

    this->m_fixManager->IncRecvMsgSeqNumber();
    DefaultLogManager::Default->EndLog(true);
    this->m_stopwatch->Start();
    this->SetState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);
    return true;
}

bool MarketServerInfo::WaitRecvLogon_Atom() {
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_stopwatch->ElapsedSeconds() > 10) {
            this->SetState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
            DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom, false);
            return true;
        }
        if(this->m_socketManager->RecvSize() == 0) {
            this->ReconnectSetNextState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
            return true;
        }
        else {
            DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom, false);
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            return true;
        }
    }
    DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom, true);
    this->m_fixManager->IncRecvMsgSeqNumber();
    this->SetState(MarketServerState::mssSendLogout, &MarketServerInfo::SendLogout_Atom);
    return true;
}
*/
bool MarketServerInfo::SendLogout_Atom() {

    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendLogout_Atom);

    this->m_fixManager->PrepareSendBuffer();
    this->m_fixManager->CreateLogoutMessage("Hasta la vista baby!");
    return this->SendCore(true);
}
/*
bool MarketServerInfo::RepeatSendLogout_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendLogout_Atom);
    if(!this->m_socketManager->Send(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncSendMsgSeqNumber();
    this->SetState(MarketServerState::mssRecvLogout, &MarketServerInfo::RecvLogout_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvLogout_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvLogout_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_socketManager->RecvSize() == 0) {
            this->ReconnectSetNextState(MarketServerState::mssSendLogout, &MarketServerInfo::SendLogout_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        else {
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
    }
    this->m_fixManager->IncRecvMsgSeqNumber();
    DefaultLogManager::Default->EndLog(true);
    this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
    return true;
}

bool MarketServerInfo::WaitRecvLogout_Atom() {
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_stopwatch->ElapsedSeconds() > 10) {
            DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom, false);
            this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
            return true;
        }
        if(this->m_socketManager->RecvSize() == 0) {
            this->ReconnectSetNextState(MarketServerState::mssSendLogout, &MarketServerInfo::SendLogout_Atom);
            return true;
        }
        else {
            DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom, false);
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            return true;
        }
    }
    DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom, true);
    this->m_fixManager->IncRecvMsgSeqNumber();
    this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
    return true;
}
*/

bool MarketServerInfo::SendTestRequest_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendTestRequest_Atom);

    this->m_fixManager->PrepareSendBuffer();
    this->m_testRequestId = rand();
    this->m_fixManager->CreateTestRequestMessage();
    this->m_stopwatch->Start();
    return this->SendCore(true);
}

/*
bool MarketServerInfo::RepeatSendTestRequest_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendTestRequest_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->Send(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncSendMsgSeqNumber();
    this->SetState(MarketServerState::mssRecvHearthBeat, &MarketServerInfo::RecvHearthBeat_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvHearthBeat_Atom() {
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_stopwatch->ElapsedSeconds() > 10) {
            DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvHearthBeat_Atom, false);
            this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
            return true;
        }
        if(this->m_socketManager->RecvSize() == 0) {
            this->ReconnectSetNextState(MarketServerState::mssSendTestRequest, &MarketServerInfo::SendTestRequest_Atom);
            return true;
        }
        else {
            DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvHearthBeat_Atom, false);
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            return true;
        }
    }
    DefaultLogManager::Default->WriteSuccess(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvHearthBeat_Atom, true);
    this->m_fixManager->IncRecvMsgSeqNumber();
    this->m_stopwatch->Start();
    this->JumpNextState();
    return true;
}
*/

bool MarketServerInfo::End_Atom() {
    return true;
}

bool MarketServerInfo::DoNothing_Atom() {
    if(this->m_shouldResendMessages) {
        this->m_resendCurrentSeqNo++;
        if(this->CheckNeedResendNextMessage())
            return true;
    }
    if(this->CanRecv()) {
        this->SetState(MarketServerState::mssRecvMessage, &MarketServerInfo::RecvMessage_Atom);
        return true;
    }
    if(this->m_stopwatch->ElapsedSeconds() > 30) {
        this->SetNextState(MarketServerState::mssDoNothing, &MarketServerInfo::DoNothing_Atom);
        this->SetState(MarketServerState::mssSendTestRequest, &MarketServerInfo::SendTestRequest_Atom);
    }
    return true;
}

bool MarketServerInfo::Panic_Atom() {
    return true;
}

ISocketBufferProvider* MarketServerInfo::CreateSocketBufferProvider() {
    return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                             RobotSettings::DefaultMarketSendBufferSize, RobotSettings::DefaultMarketSendItemsCount,
                             RobotSettings::DefaultMarketRecvBufferSize, RobotSettings::DefaultMarketRecvItemsCount);
}

bool MarketServerInfo::Connect() {
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Connect);
	if (this->m_fixManager == NULL) {
		this->m_fixManager = new FixProtocolManager(this->CreateSocketBufferProvider());
		this->m_fixManager->SetTargetComputerId((char*)TargetComputerId());
		this->m_fixManager->SetSendMsgSeqNumber(1);
        this->m_fixManager->SetRecvMsgSeqNumber(1);
	}
	if (this->m_logonInfo == NULL) {
		this->m_logonInfo = CreateLogonInfo();
        this->m_logonInfo->MsgStartSeqNo = 1;
	}
	
	this->m_socketManager = new WinSockManager();
	bool result = this->m_socketManager->Connect(this->m_internetAddress, this->m_internetPort);
	
	DefaultLogManager::Default->EndLog(result);
	return result;
}

bool MarketServerInfo::Disconnect() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Disconnect);
	if (this->m_socketManager != NULL && this->m_socketManager->IsConnected()) {
        bool result = this->m_socketManager->Disconnect();
        DefaultLogManager::Default->EndLog(result);
        return result;
    }
    DefaultLogManager::Default->EndLog(true);
	return true;
}

MarketServerInfo::~MarketServerInfo() {
	Clear();
}
