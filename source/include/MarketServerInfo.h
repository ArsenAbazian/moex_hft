#pragma once

#include "WinSockManager.h"
#include "FixProtocolManager.h"
#include "Stopwatch.h"

class MarketServerInfo;
typedef bool (MarketServerInfo::*MarketServerInfoWorkAtomPtr)();

typedef enum _MarketServerState {
	mssSendLogon,
	mssSendLogonRepeat,
	mssRecvLogon,
	mssRecvLogonRepeat,
	mssPanic
}MarketServerState;

class MarketServerInfo {
	char							m_name[128];
	int     						m_nameLogIndex;
	char							m_internetAddress[32];
	int								m_internetPort;
	char							m_targetComputerId[128];
	int								m_targetComputerIdLength;
	char							m_astsServerName[128];
	char							m_senderComputerId[128];
	int								m_senderComputerIdLength;
	char							m_password[16];
	int								m_passwordLength;
	MarketServerState				m_state;
	MarketServerInfoWorkAtomPtr		m_workAtomPtr;
	WinSockManager					*m_socketManager;
	FixProtocolManager				*m_fixManager;
	FixLogonInfo					*m_logonInfo;
	Stopwatch						*m_stopwatch;

	virtual WinSockManager*	CreateSocketManager();
	FixLogonInfo* CreateLogonInfo();
	void Clear();

	bool SendLogon_Atom();
	bool RepeatSendLogon_Atom();
	bool RecvLogon_Atom();
	bool RepeatRecvLogon_Atom();
	bool Logout_Atom();
	bool Panic_Atom();
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

	bool Connect();
	bool Disconnect();

	inline void SetState(MarketServerState state, MarketServerInfoWorkAtomPtr funcPtr) {
		this->m_state = state;
		this->m_workAtomPtr = funcPtr;
	}

	inline bool DoWorkAtom() {
#ifdef ROBOT_WORK_ANYWAY
		if(!this->m_socketManager->IsConnected())
			return true;
#endif
		return (this->*m_workAtomPtr)();
	}
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

