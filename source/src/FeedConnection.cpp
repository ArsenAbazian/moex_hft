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
	this->m_fastProtocolManager = new FastProtocolManager();
    this->m_fastLogonInfo = new FastLogonInfo();
	this->m_socketABufferProvider = CreateSocketBufferProvider();
	this->m_sendABuffer = this->m_socketABufferProvider->SendBuffer();
	this->m_recvABuffer = this->m_socketABufferProvider->RecvBuffer();

    this->socketAManager = NULL;
    this->socketBManager = NULL;

	this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();

    this->m_tval = new struct timeval;
	this->m_packets = new BinaryLogItem*[RobotSettings::DefaultFeedConnectionPacketCount];
	bzero(this->m_packets, sizeof(BinaryLogItem*) * RobotSettings::DefaultFeedConnectionPacketCount);

	this->m_waitingSnapshot = false;
	this->m_currentMsgSeqNum = 1;
	this->m_maxRecvMsgSeqNum = 0;
    this->m_listenPtr = &FeedConnection::Listen_Atom_Incremental;

	this->SetState(FeedConnectionState::fcsSuspend, &FeedConnection::Suspend_Atom);
}

FeedConnection::~FeedConnection() {

}

bool FeedConnection::InitializeSockets() {
	if(this->socketAManager != NULL)
		return true;
	DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_InitializeSockets);

	this->socketAManager = new WinSockManager();
	this->socketBManager = new WinSockManager();

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedConnection::Connect() {
	if(this->socketAManager == NULL && !this->InitializeSockets())
		return false;
	DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Connect);
    if(this->protocol == FeedConnectionProtocol::UDP_IP) {
        if (!this->socketAManager->ConnectMulticast(this->feedASourceIp, this->feedAIp, this->feedAPort)) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if (!this->socketBManager->ConnectMulticast(this->feedBSourceIp, this->feedBIp, this->feedBPort)) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
    }
    else {
        if(!this->socketAManager->Connect(this->feedAIp, this->feedAPort)) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
    }
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedConnection::Disconnect() {
    DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Disconnect);

    bool result = true;
    if(this->socketAManager != NULL)
        result &= this->socketAManager->Disconnect();
    if(this->socketBManager != NULL)
	    result &= this->socketBManager->Disconnect();

    DefaultLogManager::Default->EndLog(result);
    return result;
}

bool FeedConnection::Suspend_Atom() {
	return true;
}

bool FeedConnection::SendLogon_Atom() {
    DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_SendLogon_Atom);

    this->m_fastLogonInfo->AllowPassword = true;
    this->m_fastLogonInfo->AllowUsername = true;
    this->m_fastLogonInfo->SenderCompID = (char*)this->m_senderCompId;
    this->m_fastLogonInfo->SenderCompIDLength = this->m_senderCompIdLength;
    this->m_fastLogonInfo->Password = (char*)this->m_password;
    this->m_fastLogonInfo->PasswordLength = this->m_passwordLength;
    this->m_fastLogonInfo->HeartBtInt = 60;
    this->m_fastLogonInfo->MsgSeqNum = this->m_fastProtocolManager->SendMsgSeqNo();
    this->GetCurrentTime(&(this->m_fastLogonInfo->SendingTime));

    this->m_fastProtocolManager->SetNewBuffer(this->m_sendABuffer->CurrentPos(), 8192);
    this->m_fastProtocolManager->ResetBuffer();
    this->m_fastProtocolManager->EncodeLogonInfo(this->m_fastLogonInfo);

	this->m_stopwatch->Start();
	this->m_shouldReceiveAnswer = true;
	this->m_fastProtocolManager->IncSendMsgSeqNo();

	return this->SendCore();
}

bool FeedConnection::ResendLastMessage_Atom() {
    DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_ResendLastMessage_Atom);

    if(!this->socketAManager->Resend()) {
        this->ReconnectSetNextState(FeedConnectionState::fcsResendLastMessage, &FeedConnection::ResendLastMessage_Atom);
        DefaultLogManager::Default->EndLog(false);
        return true;
    }
    this->SetState(FeedConnectionState::fcsListen, this->m_listenPtr);
	if(this->m_shouldReceiveAnswer)
		this->m_stopwatch->Start();
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool FeedConnection::Reconnect_Atom() {
    DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Reconnect_Atom);

    if(!this->socketAManager->Reconnect()) {
        DefaultLogManager::Default->EndLog(false);
        return true;
    }

    this->SetState(this->m_nextState, this->m_nextWorkAtomPtr);
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool FeedConnection::Listen_Atom_Incremental() {

	if(this->WaitingSnapshot()) {
		this->ProcessServerA();
		this->ProcessServerB();

		if(this->SnapshotAvailable()) {
			this->ApplySnapshot();
			this->ApplyPacketSequence();
            this->StopListenSnapshot();
			this->StartWaitIncremental();
			this->ResetWaitTime();
		}
	}
	else {
		if(!this->ProcessServerA() && !this->ProcessServerB()) {
			if (this->WaitTimeExpired()) {
				this->StartListenSnapshot();
			}
			return true;
		}
		this->ApplyPacketSequence();
		if(!this->ActualMsgSeqNum()) {
			if(this->WaitTimeExpired())
				this->StartListenSnapshot();
		}
		this->ResetWaitTime();
		return true;
	}

	return false;
}

bool FeedConnection::Listen_Atom_Snapshot() {

    this->ProcessServerA();
    this->ProcessServerB();

    if(this->m_snapshotStartMsgSeqNum == -1) {
        this->m_snapshotStartMsgSeqNum = this->CheckForRouteFirst();
    }
    else {

    }

	return false;
}
