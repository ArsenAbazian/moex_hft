#pragma once

#include "WinSockManager.h"
#include "FixProtocolManager.h"

class MarketServerInfo {
	char	name[128];
	int     m_nameLogIndex;
	char	internetAddress[32];
	int		internetPort;
	char	targetComputerId[128];
	int		targetComputerIdLength;
	char	astsServerName[128];
	char	senderComputerId[128];
	int		senderComputerIdLength;
	char	password[16];
	int		passwordLength;

	WinSockManager			*socketManager;
	FixProtocolManager		*fixManager;
	FixLogonInfo			*logonInfo;

	void Clear();
	FixLogonInfo*		CreateLogonInfo();
	virtual WinSockManager*	CreateSocketManager();
public:
	MarketServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName);
	~MarketServerInfo();

	inline const char*	Name() { return this->name; }
	inline const char*	InternetAddress() { return this->internetAddress; }
	inline const int	InternetPort() { return this->internetPort; }
	inline const char*	TargetComputerId() { return this->targetComputerId; }
	inline const int	TargetComputerIdLength() { return this->targetComputerIdLength; }
	inline const char*	SenderComputerId() { return this->senderComputerId; }
	inline const int	SenderComputerIdLength() { return this->senderComputerIdLength; }
	inline const char*	Password() { return this->password; }
	inline const int	PasswordLength() { return this->passwordLength; }
	inline const char*	ASTSServerName() { return this->astsServerName; }

	inline WinSockManager* SocketManager() { return this->socketManager; }
	inline FixProtocolManager* FixManager() { return this->fixManager; }

	bool Connect();
	bool Disconnect();
	bool Logon();
	bool Logout();
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

