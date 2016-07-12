#include "FeedConnection.h"
#include "LogManager.h"

FeedConnection::FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) {
	strcpy(this->id, id);
	strcpy(this->feedTypeName, name);
	this->feedTypeValue = value;
	this->protocol = protocol;
	
	strcpy(this->feedASourceIp, aSourceIp);
	strcpy(this->feedAIp, aIp);
	this->feedAPort = aPort;

	strcpy(this->feedBSourceIp, bSourceIp);
	strcpy(this->feedBIp, bIp);
	this->feedBPort = bPort;

	this->socketAManager = new WinSockManager();
	this->socketBManager = new WinSockManager();
	this->fastProtocolManager = new FastProtocolManager();

	this->receiveBufferPlain = null;
	this->receiveBufferList = null;
	this->messageSeqNumberList = null;

	InitializeReceiveBuffer(FEED_CONNECTION_MAX_BUFFERS_COUNT);

	this->state = FeedConnectionState::Normal;
	this->currentReceiveBufferIndex = 0;
}


FeedConnection::~FeedConnection() {
	ClearReceiveBuffers();
}

bool FeedConnection::Connect() {
	DefaultLogManager::Default->StartLog("FeedConnection::Connect");
	if (this->socketAManager->Initialize(this->feedAIp, this->feedAPort) != 0) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (this->socketBManager->Initialize(this->feedBIp, this->feedBPort) != 0) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedConnection::Disconnect() {
	if (this->socketAManager->Close() != 0)
		return false;
	if (this->socketBManager->Close() != 0)
		return false;
	return true;
}

void FeedConnection::ClearReceiveBuffers() { 
	
	if (this->receiveBufferPlain != null) {
		delete[] this->receiveBufferPlain;
		delete[] this->receiveBufferList;
		delete[] this->messageSeqNumberList;
	}

	this->receiveBufferPlain = null;
	this->receiveBufferList = null;
	this->messageSeqNumberList = null;
} 

void FeedConnection::InitializeReceiveBuffer(int maxBuffersCount) {

	ClearReceiveBuffers();
	
	this->maxReceiveBufferCount = maxBuffersCount;
	this->receiveBufferPlain = new BYTE[FEED_CONNECTION_MAX_BUFFER_LENGTH * maxBuffersCount];
	this->receiveBufferList = new BYTE*[this->maxReceiveBufferCount];
	this->messageSeqNumberList = new int[this->maxReceiveBufferCount];
	
	BYTE *address = this->receiveBufferPlain;
	for (int i = 0; i < this->maxReceiveBufferCount; i++) {
		this->receiveBufferList[i] = address;
		address += FEED_CONNECTION_MAX_BUFFER_LENGTH;
	}
	memset(this->messageSeqNumberList, 0, sizeof(int) * this->maxReceiveBufferCount);
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
	
	return FeedConnectionErrorCode::Success;
}

FeedConnectionErrorCode FeedConnection::Listen() {
	
	switch (state) {
	case FeedConnectionState::Normal:
		return this->ListenNormal();
	}

	return FeedConnectionErrorCode::Success;
}