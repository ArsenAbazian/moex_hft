#pragma once
#include "MarketServerInfo.h"

class MarketInfo {

	char name[16];

	MarketServerInfo *trade;
	MarketServerInfo *tradeCapture;
	MarketServerInfo *dropCopy;

	void Initialize(const char* name, const char *senderComputerId, const char *password,
		const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
		const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
		const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName);
public:

	MarketInfo(const char* name, const char *senderComputerId, const char *password,
		const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
		const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
		const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName);
	
	MarketInfo(const char* name, const char *senderComputedId, const char *password, const char *inetAddress, const char *astsServerName, 
		const char *tradeName, int tradePort, const char *tradeTargetCompId, 
		const char *tradeCaptureName, int tradeCapturePort, const char *tradeCaptureTargetCompId, 
		const char *tradeDropCopyName, int tradeDropCopyPort, const char *tradeDropCopyTargetCompId);
	
	~MarketInfo();

	bool Connect();
	void Run();
	bool Disconnect();
	bool Logon();
	bool Logout();

	inline MarketServerInfo* Trade() { return this->trade; }
	inline MarketServerInfo* TradeCapture() { return this->tradeCapture; }
	inline MarketServerInfo* TradeDropCopy() { return this->dropCopy; }
};

