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
    this->m_inSendResendRequest = false;

    this->SetState(MarketServerState::mssSendLogon);

    this->m_socketManager = NULL;
    this->m_fixManager = NULL;
    this->m_logonInfo = NULL;
    this->m_shouldResendMessages = false;
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

/*
bool MarketServerInfo::RepeatSendLogout_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendLogout_Atom);
    if(!this->m_socketManager->Send(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncMsgSeqNo();
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

/*
bool MarketServerInfo::RepeatSendTestRequest_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendTestRequest_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->Send(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncMsgSeqNo();
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
        this->m_fixManager->SetSendMsgSeqNo(1);
		this->m_fixManager->SetRecvMsgSeqNo(1);
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
