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

    this->m_fastProtocolManager->SkipTemplateId(fcmHeartBeat);
    this->m_waitIncrementalMaxTimeMs = 3000;
    this->m_snapshotMaxTimeMs = 3000;

    this->socketAManager = NULL;
    this->socketBManager = NULL;

	this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();

    this->m_tval = new struct timeval;
	this->m_packets = new FeedConnectionMessageInfo*[RobotSettings::DefaultFeedConnectionPacketCount];
	for(int i = 0; i < RobotSettings::DefaultFeedConnectionPacketCount; i++)
        this->m_packets[i] = new FeedConnectionMessageInfo();

	this->m_startMsgSeqNum = 1;
	this->m_endMsgSeqNum = 0;
    this->m_type = FeedConnectionType::Incremental;

	this->SetState(FeedConnectionState::fcsSuspend);

    this->obrLogFile = fopen("~Documents/hft_robot/logs/obr_log_file.txt", "wt");
}

FeedConnection::FeedConnection() {
    for(int i = 0; i < RobotSettings::DefaultFeedConnectionPacketCount; i++)
        this->m_packets[i] = new FeedConnectionMessageInfo();

    this->m_fastProtocolManager = new FastProtocolManager();
    this->m_fastProtocolManager->SkipTemplateId(fcmHeartBeat);
    this->m_fastLogonInfo = new FastLogonInfo();

    this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();
    this->m_waitIncrementalMaxTimeMs = 3000;
    this->m_snapshotMaxTimeMs = 3000;

    this->m_tval = new struct timeval;

    this->m_startMsgSeqNum = 1;
    this->m_endMsgSeqNum = 0;
    this->m_type = FeedConnectionType::Incremental;

    this->SetState(FeedConnectionState::fcsSuspend);
}

FeedConnection::~FeedConnection() {
    if(this->m_packets != 0) {
        for(int i = 0; i < RobotSettings::DefaultFeedConnectionPacketCount; i++)
            delete this->m_packets[i];
        delete this->m_packets;
    }
    if(this->m_fastProtocolManager != 0)
        delete this->m_fastProtocolManager;
    if(this->m_stopwatch != 0)
        delete this->m_stopwatch;
    if(this->m_waitTimer != 0)
        delete this->m_waitTimer;
    if(this->m_fastLogonInfo != 0)
        delete this->m_fastLogonInfo;
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

bool FeedConnection::Suspend_Atom() {
	return true;
}

/*
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
*/
bool FeedConnection::Reconnect_Atom() {
    DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Reconnect_Atom);

    if(!this->m_fakeConnect) {
        if(!this->socketAManager->Reconnect()) {
            DefaultLogManager::Default->EndLog(false);
            return true;
        }
    }

    this->SetState(this->m_nextState);
    this->m_waitTimer->Start();
    this->m_waitTimer->Stop(1);
    this->m_startMsgSeqNum = -1;
    this->m_endMsgSeqNum = -1;
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool FeedConnection::Listen_Atom_Incremental() {

    bool recv = this->ProcessServerA();
    recv |= this->ProcessServerB();
    this->m_isLastIncrementalRecv = recv;

    if(!this->m_isLastIncrementalRecv) {
        this->m_waitTimer->Activate(1);
        if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
            this->StartListenSnapshot();
            return true;
        }
    }
    else {
        this->m_waitTimer->Stop(1);
    }

    return this->Listen_Atom_Incremental_Core();
}

bool FeedConnection::Listen_Atom_Snapshot() {
    bool recv = this->ProcessServerA();
    recv |= this->ProcessServerB();

    if(!recv) {
        if(!this->m_waitTimer->Active(1)) {
            this->m_waitTimer->Start(1);
        }
        else {
            if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_Snapshot, false);
                return false;
            }
        }
    }
    else {
        this->m_waitTimer->Stop(1);
    }

    return this->Listen_Atom_Snapshot_Core();
}
