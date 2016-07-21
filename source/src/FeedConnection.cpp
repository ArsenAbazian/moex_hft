#include "FeedConnection.h"
#include "LogManager.h"

FeedConnection::FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) {
	strcpy(this->id, id);
	strcpy(this->feedTypeName, name);

	this->m_idLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->id);
	this->m_feedTypeNameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->feedTypeName);

	this->feedTypeValue = value;
	this->protocol = protocol;
	
	strcpy(this->feedASourceIp, aSourceIp);
	strcpy(this->feedAIp, aIp);
	this->feedAPort = aPort;

	strcpy(this->feedBSourceIp, bSourceIp);
	strcpy(this->feedBIp, bIp);
	this->feedBPort = bPort;
	this->fastProtocolManager = new FastProtocolManager();
	this->state = FeedConnectionState::Normal;
}


FeedConnection::~FeedConnection() {

}

bool FeedConnection::InitializeSockets() {
	if(this->socketAManager != NULL)
		return true;
	DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_InitializeSockets);

	this->socketAManager = new WinSockManager(this->CreateSocketBufferProvider());
	this->socketBManager = new WinSockManager(this->CreateSocketBufferProvider());

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedConnection::Connect() {
	if(this->socketAManager == NULL && !this->InitializeSockets())
		return false;
	DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Connect);
	WinSockConnectionType connType = this->protocol == FeedConnectionProtocol::TCP_IP? WinSockConnectionType::wsTCP: WinSockConnectionType::wsUDP;
    if (!this->socketAManager->Connect(this->feedASourceIp, this->feedAPort, connType)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->socketBManager->Connect(this->feedBSourceIp, this->feedBPort, connType)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedConnection::Disconnect() {
    DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Disconnect);

    bool result = this->socketAManager->Disconnect();
	result &= this->socketBManager->Disconnect();

    DefaultLogManager::Default->EndLog(result);
    return result;
}

FeedConnectionErrorCode FeedConnection::CheckReceivedBytes(BYTE *buffer) { 
	int receivedMsgSeqNumber = this->ReadMessageSequenceNumber(buffer);
	int delta = receivedMsgSeqNumber - ExpectedMessageSeqNumber();
	if (delta < 0) { 
		return FeedConnectionErrorCode::Success; // just skip previous message
	}
	else if (delta > 0) { // received future message
		
	}
	else { 
		IncrementMessageSeqNumber();
		Decode();
	}
	return FeedConnectionErrorCode::Success;
}

FeedConnectionErrorCode FeedConnection::ListenNormal() {
	return FeedConnectionErrorCode::Success;
	/*
	BYTE *buffer = CurrentBuffer();
	bool result = this->socketAManager->Recv((char*)buffer, FEED_CONNECTION_MAX_BUFFER_LENGTH);
	if (!result || this->socketAManager->ReceivedBytesCount() == 0) { 
		result = this->socketBManager->Recv((char*)buffer, FEED_CONNECTION_MAX_BUFFER_LENGTH);
		if (!result || this->socketBManager->ReceivedBytesCount() == 0) { 
			return FeedConnectionErrorCode::NoBytesReceived;
		}
		else { 
			IncrementBufferIndex();
			return CheckReceivedBytes(buffer);
		}
	}
	else { 
		IncrementBufferIndex();
		return CheckReceivedBytes(buffer);
	}
	*/
}

FeedConnectionErrorCode FeedConnection::Listen() {
	
	switch (state) {
	case FeedConnectionState::Normal:
		return this->ListenNormal();
	}

	return FeedConnectionErrorCode::Success;
}
