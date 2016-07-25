#include "MarketServerInfo.h"
#include <stdio.h>
#include "LogManager.h"
#include "Stopwatch.h"

MarketServerInfo::MarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) {
	strcpy(this->name, name);
    this->m_nameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->name);
	strcpy(this->internetAddress, internetAddress);
	this->internetPort = internetPort;
	strcpy(this->targetComputerId, targetComputerId);
	this->targetComputerIdLength = strlen(this->targetComputerId);
	strcpy(this->astsServerName, astsServerName);
	strcpy(this->senderComputerId, senderComputerId);
	this->senderComputerIdLength = strlen(this->senderComputerId);
	strcpy(this->password, password);
	this->passwordLength = strlen(this->password);

    this->socketManager = NULL;
    this->fixManager = NULL;
    this->logonInfo = NULL;
}

void MarketServerInfo::Clear() { 
	if (this->fixManager != NULL)
		delete this->fixManager;
	if (this->socketManager != NULL)
		delete this->socketManager;
	if (this->logonInfo != NULL)
		delete this->logonInfo;
	this->logonInfo = NULL;
	this->fixManager = NULL;
	this->socketManager = NULL;
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

bool MarketServerInfo::Logon() { 
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Logon);

	this->fixManager->SetMessageBuffer((char*)this->socketManager->GetNextSendBuffer());
	this->fixManager->CreateLogonMessage(this->logonInfo);
#ifdef ROBOT_WORK_ANYWAY
	if(this->socketManager->IsConnected()) {
#endif
		DefaultStopwatch::Default->Start();
        while(DefaultStopwatch::Default->ElapsedSeconds() < 45) {
			if (!this->socketManager->SendCore((unsigned char *) this->fixManager->Message(), this->fixManager->MessageLength())) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}

			if (!this->socketManager->RecvCore()) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}

			if(this->socketManager->RecvSize() == 0)
				continue;

			this->socketManager->RecvBytes()[this->socketManager->RecvSize()] = '\0';
			this->fixManager->SetMessageBuffer((char *) this->socketManager->RecvBytes());
			if (!this->fixManager->ProcessCheckLogonMessage()) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}

			break;
		}

		this->fixManager->IncMessageSequenceNumber();
#ifdef ROBOT_WORK_ANYWAY
	}
#endif
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool MarketServerInfo::Logout() {
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
	return true;
}

WinSockManager* MarketServerInfo::CreateSocketManager() {
    return new WinSockManager(new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                                       RobotSettings::DefaultMarketSendBufferSize, RobotSettings::DefaultMarketSendItemsCount,
                                                       RobotSettings::DefaultMarketRecvBufferSize, RobotSettings::DefaultMarketRecvItemsCount));
}

bool MarketServerInfo::Connect() {
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Connect);
	if (this->fixManager == NULL) {
		this->fixManager = new FixProtocolManager();
		this->fixManager->SetTargetComputerId((char*)TargetComputerId());
		this->fixManager->SetMessageSequenceNumber(1);
	}
	if (this->logonInfo == NULL) {
		this->logonInfo = CreateLogonInfo();
	}
	
	this->socketManager = CreateSocketManager();
	bool result = this->socketManager->Connect(this->internetAddress, this->internetPort);
	
	DefaultLogManager::Default->EndLog(result);
	return result;
}

bool MarketServerInfo::Disconnect() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketServerInfo_Disconnect);
	if (this->socketManager != NULL && this->socketManager->IsConnected()) {
        bool result = this->socketManager->Disconnect();
        DefaultLogManager::Default->EndLog(result);
        return result;
    }
    DefaultLogManager::Default->EndLog(true);
	return true;
}

MarketServerInfo::~MarketServerInfo() {
	Clear();
}
