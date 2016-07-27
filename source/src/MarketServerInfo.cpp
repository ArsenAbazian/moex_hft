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

    this->SetState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);

    this->m_socketManager = NULL;
    this->m_fixManager = NULL;
    this->m_logonInfo = NULL;
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
	res->ShouldResetSeqNum = true;
	
	return res;
}

bool MarketServerInfo::SendLogon_Atom() {

    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendLogon_Atom);

    this->m_fixManager->SetMessageBuffer((char*)this->m_socketManager->GetNextSendBuffer());
    this->m_fixManager->CreateLogonMessage(this->m_logonInfo);
    if(!this->m_socketManager->SendFix(this->m_fixManager->MessageLength())) {
        this->SetState(MarketServerState::mssSendLogonRepeat, &MarketServerInfo::RepeatSendLogon_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncMessageSequenceNumber();
    this->SetState(MarketServerState::mssRecvLogon, &MarketServerInfo::RecvLogon_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RepeatSendLogon_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendLogon_Atom);
    if(!this->m_socketManager->SendFix(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncMessageSequenceNumber();
    this->SetState(MarketServerState::mssRecvLogon, &MarketServerInfo::RecvLogon_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvLogon_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvLogon_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_socketManager->RecvSize() == 0) {
            this->SetState(MarketServerState::mssRecvLogonWait, &MarketServerInfo::WaitRecvLogon_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        else {
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
    }
    this->m_fixManager->IncMessageSequenceNumber();
    DefaultLogManager::Default->EndLog(true);
    this->SetState(MarketServerState::mssSendLogout, &MarketServerInfo::SendLogout_Atom);
    return true;
}

bool MarketServerInfo::WaitRecvLogon_Atom() {
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_stopwatch->ElapsedSeconds() > 10) {
            this->SetState(MarketServerState::mssSendLogon, &MarketServerInfo::SendLogon_Atom);
            DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        if(this->m_socketManager->RecvSize() == 0) {
            return true;
        }
        else {
            DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom);
            DefaultLogManager::Default->EndLog(false);
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            return true;
        }
    }
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom);
    DefaultLogManager::Default->EndLog(true);
    this->m_fixManager->IncMessageSequenceNumber();
    this->SetState(MarketServerState::mssSendLogout, &MarketServerInfo::SendLogout_Atom);
    return true;
}

bool MarketServerInfo::SendLogout_Atom() {

    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_SendLogout_Atom);

    this->m_fixManager->SetMessageBuffer((char*)this->m_socketManager->GetNextSendBuffer());
    this->m_fixManager->CreateLogoutMessage("Hasta la vista baby!");
    if(!this->m_socketManager->SendFix(this->m_fixManager->MessageLength())) {
        this->SetState(MarketServerState::mssSendLogoutRepeat, &MarketServerInfo::RepeatSendLogout_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncMessageSequenceNumber();
    this->SetState(MarketServerState::mssRecvLogout, &MarketServerInfo::RecvLogout_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RepeatSendLogout_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RepeatSendLogout_Atom);
    if(!this->m_socketManager->SendFix(this->m_fixManager->MessageLength())) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->m_fixManager->IncMessageSequenceNumber();
    this->SetState(MarketServerState::mssRecvLogout, &MarketServerInfo::RecvLogout_Atom);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketServerInfo::RecvLogout_Atom() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_RecvLogout_Atom);
    this->m_stopwatch->Start();
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_socketManager->RecvSize() == 0) {
            this->SetState(MarketServerState::mssRecvLogoutWait, &MarketServerInfo::WaitRecvLogout_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
        else {
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
    }
    this->m_fixManager->IncMessageSequenceNumber();
    DefaultLogManager::Default->EndLog(true);
    this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
    return true;
}

bool MarketServerInfo::WaitRecvLogout_Atom() {
    if(!this->m_socketManager->RecvFix()) {
        if(this->m_stopwatch->ElapsedSeconds() > 10) {
            DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom);
            DefaultLogManager::Default->EndLog(false);
            this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
            return true;
        }
        if(this->m_socketManager->RecvSize() == 0) {
            return true;
        }
        else {
            DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom);
            DefaultLogManager::Default->EndLog(false);
            this->SetState(MarketServerState::mssPanic, &MarketServerInfo::Panic_Atom);
            return true;
        }
    }
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom);
    DefaultLogManager::Default->EndLog(true);
    this->m_fixManager->IncMessageSequenceNumber();
    this->SetState(MarketServerState::mssEnd, &MarketServerInfo::End_Atom);
    return true;
}

bool MarketServerInfo::End_Atom() {
    return true;
}

bool MarketServerInfo::DoNothing_Atom() {
    printf("%s - do nothing\n", this->m_name);
    return true;
}

bool MarketServerInfo::Panic_Atom() {
    return true;
}

bool MarketServerInfo::Logout_Atom() {
    /*
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Logout);

	this->fixManager->SetMessageBuffer((char*)this->socketManager->GetNextSendBuffer());

	// first we must be sure that there is no lost message before logout
	// so we should send TestRequest and receive HearthBeat messages
	this->fixManager->CreateTestRequestMessage(2382);
	if (!this->socketManager->SendCore((unsigned char*)this->fixManager->Message(), this->fixManager->MessageLength())) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	this->fixManager->IncMessageSequenceNumber();

	if (!this->socketManager->RecvCore()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if(!this->fixManager->CheckProcessHearthBeat(2382)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	this->fixManager->SetMessageBuffer((char*)this->socketManager->GetNextSendBuffer());
	this->fixManager->CreateLogoutMessage("Good Bye!");
	if (!this->socketManager->SendCore((unsigned char*)this->fixManager->Message(), this->fixManager->MessageLength())) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if (!this->socketManager->RecvCore()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	this->fixManager->IncMessageSequenceNumber();

	DefaultLogManager::Default->EndLog(true);
    */
	return true;
}

WinSockManager* MarketServerInfo::CreateSocketManager() {
    return new WinSockManager(new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                                       RobotSettings::DefaultMarketSendBufferSize, RobotSettings::DefaultMarketSendItemsCount,
                                                       RobotSettings::DefaultMarketRecvBufferSize, RobotSettings::DefaultMarketRecvItemsCount));
}

bool MarketServerInfo::Connect() {
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Connect);
	if (this->m_fixManager == NULL) {
		this->m_fixManager = new FixProtocolManager();
		this->m_fixManager->SetTargetComputerId((char*)TargetComputerId());
		this->m_fixManager->SetMessageSequenceNumber(1);
	}
	if (this->m_logonInfo == NULL) {
		this->m_logonInfo = CreateLogonInfo();
	}
	
	this->m_socketManager = CreateSocketManager();
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
