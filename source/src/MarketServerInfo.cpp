#include "MarketServerInfo.h"
#include <stdio.h>
#include "LogManager.h"


MarketServerInfo::MarketServerInfo()
{
	this->internetAddress[0] = '\0';
	this->internetPort = 0;
	this->targetComputerId[0] = '\0';
	this->targetComputerIdLength = 0;
	this->astsServerName[0] = '\0';
	this->socketManager = NULL;
	this->fixManager = NULL;
	this->logonInfo = NULL;
}

MarketServerInfo::MarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) {
	strcpy(this->name, name);
	strcpy(this->internetAddress, internetAddress);
	this->internetPort = internetPort;
	strcpy(this->targetComputerId, targetComputerId);
	this->targetComputerIdLength = strlen(this->targetComputerId);
	strcpy(this->astsServerName, astsServerName);
	strcpy(this->senderComputerId, senderComputerId);
	this->senderComputerIdLength = strlen(this->senderComputerId);
	strcpy(this->password, password);
	this->passwordLength = strlen(this->password);
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
	this->fixManager->CreateLogonMessage(this->logonInfo);
	if (!this->socketManager->Send(this->fixManager->Message(), this->fixManager->MessageLength()))
		return false;

	printf("SEND %s\n\n", this->fixManager->Message());
	if (!this->socketManager->Recv(FixMessage))
		return false;

	printf("RECV %s\n\n", this->socketManager->ReceivedBytes());
	this->fixManager->IncMessageSequenceNumber();

	return true;
}

bool MarketServerInfo::Logout() { 
	this->fixManager->CreateLogoutMessage("Good Bye!", 9);
	if (!this->socketManager->Send(this->fixManager->Message(), this->fixManager->MessageLength()))
		return false;

	printf("SEND %s\n\n", this->fixManager->Message());
	if (!this->socketManager->Recv(FixMessage))
		return false;

	printf("RECV %s\n\n", this->socketManager->ReceivedBytes());
	this->fixManager->IncMessageSequenceNumber();

	return true;
}

bool MarketServerInfo::Connect() {
	DefaultLogManager::Default->StartLog(this->name, "Connect");
	if (this->fixManager == NULL) {
		this->fixManager = new FixProtocolManager(DefaultFixProtocolHistoryManager::defaultManager);
		this->fixManager->SetTargetComputerId((char*)TargetComputerId());
		this->fixManager->SetMessageSequenceNumber(1);
	}
	if (this->logonInfo == NULL) {
		this->logonInfo = CreateLogonInfo();
	}
	
	this->socketManager = new WinSockManager();
	bool result = this->socketManager->Connect(this->internetAddress, this->internetPort);
	
	DefaultLogManager::Default->EndLog(result);
	return result;
}

bool MarketServerInfo::Disconnect() { 
	if (this->socketManager != NULL && this->socketManager->IsConnected())
		return this->socketManager->Disconnect() == 0;
	return true;
}

MarketServerInfo::~MarketServerInfo() {
	Clear();
}
