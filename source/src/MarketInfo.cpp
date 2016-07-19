#include "MarketInfo.h"
#include "LogManager.h"

void MarketInfo::Initialize(const char* name, const char *senderComputerId, const char *password,
	const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
	const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
	const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName) {
	
	strcpy(this->name, name);
	this->trade = new MarketServerInfo(tradeName, tradeAddress, tradePort, senderComputerId, password, tradeTargetComputerId, tradeASTSServerName);
	this->tradeCapture = new MarketServerInfo(tradeCaptureName, tradeCaptureAddress, tradeCapturePort, senderComputerId, password, tradeCaptureTargetComputerId, tradeCaptureASTSServerName);
	this->dropCopy = new MarketServerInfo(tradeDropCopyName, tradeDropCopyAddress, tradeDropCopyPort, senderComputerId, password, tradeDropCopyTargetComputerId, tradeDropCopyASTSServerName);
}

MarketInfo::MarketInfo(const char* name, const char *senderComputerId, const char *password,
	const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
	const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
	const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName) {
	
	this->Initialize(name, senderComputerId, password,
		tradeName, tradeAddress, tradePort, tradeTargetComputerId, tradeASTSServerName,
		tradeCaptureName, tradeCaptureAddress, tradeCapturePort, tradeCaptureTargetComputerId, tradeCaptureASTSServerName,
		tradeDropCopyName, tradeDropCopyAddress, tradeDropCopyPort, tradeDropCopyTargetComputerId, tradeDropCopyASTSServerName);
}

MarketInfo::MarketInfo(const char* name, const char *senderComputedId, const char *password, const char *inetAddress, const char *astsServerName,
	const char *tradeName, int tradePort, const char *tradeTargetCompId,
	const char *tradeCaptureName, int tradeCapturePort, const char *tradeCaptureTargetCompId,
	const char *tradeDropCopyName, int tradeDropCopyPort, const char *tradeDropCopyTargetCompId) {
	
	this->Initialize(name, senderComputedId, password, tradeName, inetAddress, tradePort, tradeTargetCompId, astsServerName, tradeCaptureName, inetAddress, tradeCapturePort, tradeCaptureTargetCompId, astsServerName, tradeDropCopyName, inetAddress, tradeDropCopyPort, tradeDropCopyTargetCompId, astsServerName);
}

MarketInfo::~MarketInfo() { 
	if (this->trade != NULL)
		delete this->trade;
	if (this->tradeCapture != NULL)
		delete this->tradeCapture;
	if (this->dropCopy != NULL)
		delete this->dropCopy;
}

bool MarketInfo::Connect() { 
	DefaultLogManager::Default->StartLog(this->name, "MarketInfo::Connect");
	if (this->trade == NULL) {
		DefaultLogManager::Default->EndLog(true);
		return true;
	}
	if (!this->trade->Connect()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->tradeCapture->Connect()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->dropCopy->Connect()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

void MarketInfo::Run() {
	this->trade->SocketManager()->Run();
	this->tradeCapture->SocketManager()->Run();
	this->dropCopy->SocketManager()->Run();
}

bool MarketInfo::Disconnect() {
	DefaultLogManager::Default->StartLog(this->name, "MarketInfo::Disconnect");
	if (this->trade == NULL)
		return true;
	if (!this->trade->Disconnect()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->tradeCapture->Disconnect()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->dropCopy->Disconnect()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	return true;
}

bool MarketInfo::Logon() { 
	bool success = true;
	success &= this->trade->Logon();
	success &= this->tradeCapture->Logon();
	success &= this->dropCopy->Logon();

	return success;
}

bool MarketInfo::Logout() { 
	bool success = true;
	success &= this->trade->Logout();
	success &= this->tradeCapture->Logout();
	success &= this->dropCopy->Logout();
	return success;
}
		


