#pragma once
#include "WinSockManager.h"
#include "FastProtocolManager.h"
#include "Types.h"

typedef enum _FeedConnectionProtocol {
	TCP_IP,
	UDP_IP
}FeedConnectionProtocol;

typedef enum _FeedConnectionErrorCode{
	Success = 0,
	NoBytesReceived = 1
}FeedConnectionErrorCode;

typedef enum _FeedConnectionState {
	Normal,
}FeedConnectionState;

class FeedConnection {
	const int MaxReceiveBufferSize = 1500;
protected:
	FeedConnectionState 		state;

	char						id[16];
	char						feedTypeName[64];

	int     					m_idLogIndex;
	int 						m_feedTypeNameLogIndex;

	char						feedTypeValue;

	FeedConnectionProtocol 		protocol;

	char						feedASourceIp[64];
	char						feedAIp[64];
	int							feedAPort;

	char						feedBSourceIp[64];
	char						feedBIp[64];
	int							feedBPort;

	int							messageSeqNumber;

	WinSockManager				*socketAManager;
	WinSockManager				*socketBManager;
	FastProtocolManager 		*fastProtocolManager;
	
	FeedConnectionErrorCode 	ListenNormal();

	inline void IncrementMessageSeqNumber() { this->messageSeqNumber++; }
	inline int ReadMessageSequenceNumber(BYTE *buffer) {
		this->fastProtocolManager->SetNewBuffer(buffer, MaxReceiveBufferSize);
		return this->fastProtocolManager->ReadMsgSeqNumber();
	}
	FeedConnectionErrorCode CheckReceivedBytes(BYTE *buffer);
	bool InitializeSockets();
	virtual ISocketBufferProvider* CreateSocketBufferProvider() {
			return new SocketBufferProvider(DefaultSocketBufferManager::Default,
											RobotSettings::DefaultFeedConnectionSendBufferSize,
											RobotSettings::DefaultFeedConnectionSendItemsCount,
											RobotSettings::DefaultFeedConnectionRecvBufferSize,
											RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	~FeedConnection();

	bool Connect();
	bool Disconnect();

	char* Id() { return this->id; }

	inline bool Logon() {
		return true;
	}

	inline bool Logout() {
		return true;
	}

	inline virtual void Decode() { this->fastProtocolManager->Decode_Generic(); }

	inline int MesssageSeqNumber() { return this->messageSeqNumber; }
	inline int ExpectedMessageSeqNumber() { return this->messageSeqNumber + 1; }
	FeedConnectionErrorCode Listen();

	inline bool DoWorkAtom() {
		return true;
	}
};

class FeedConnection_CURR_OBR : public FeedConnection {
public:
	FeedConnection_CURR_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OBR_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OBS : public FeedConnection {
public:
	FeedConnection_CURR_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OBS_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSR : public FeedConnection {
public:
	FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_MSR_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSS : public FeedConnection {
public:
	FeedConnection_CURR_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
	FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OLR_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLS : public FeedConnection {
public:
	FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OLS_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
	FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_TLR_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLS : public FeedConnection {
public:
	FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_TLS_CURR(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBR : public FeedConnection {
public:
	FeedConnection_FOND_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OBR_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBS : public FeedConnection {
public:
	FeedConnection_FOND_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OBS_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
	FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_MSR_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSS : public FeedConnection {
public:
	FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
	FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OLR_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLS : public FeedConnection {
public:
	FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_OLS_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
	FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_TLR_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLS : public FeedConnection {
public:
	FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
	inline void Decode() { this->fastProtocolManager->Decode_TLS_FOND(); }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

