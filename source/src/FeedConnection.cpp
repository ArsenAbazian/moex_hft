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
    this->m_type = FeedConnectionType::Incremental;

	this->SetState(FeedConnectionState::fcsSuspend, &FeedConnection::Suspend_Atom);

    this->obrLogFile = fopen("~Documents/hft_robot/logs/obr_log_file.txt", "wt");
}

FeedConnection::FeedConnection() {
    this->m_packets = 0;

    this->m_fastProtocolManager = new FastProtocolManager();
    this->m_fastProtocolManager->SkipTemplateId(fcmHeartBeat);
    this->m_fastLogonInfo = new FastLogonInfo();

    this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();

    this->m_tval = new struct timeval;

    this->m_waitingSnapshot = false;
    this->m_currentMsgSeqNum = 1;
    this->m_maxRecvMsgSeqNum = 0;
    this->m_listenPtr = &FeedConnection::Listen_Atom_Incremental;
    this->m_type = FeedConnectionType::Incremental;

    this->SetState(FeedConnectionState::fcsSuspend, &FeedConnection::Suspend_Atom);
}

FeedConnection::~FeedConnection() {
    if(this->m_packets != 0)
        delete this->m_packets;
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

    bool recv = this->ProcessServerA();
    recv |= this->ProcessServerB();

    if(!recv) {
        this->m_waitTimer->Activate(1);
        if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
            DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_Incremental, false);
            return false;
        }
    }
    else {
        this->m_waitTimer->Stop(1);
    }

    if(this->WaitingSnapshot()) {
		if(this->m_snapshot->SnapshotAvailable()) {
			this->m_snapshot->ApplySnapshot();
			this->m_currentMsgSeqNum = this->m_snapshot->LastMsgSeqNumProcessed() + 1;
            printf("snapshot applied. new expected message %d. max received msg %d\n", this->m_currentMsgSeqNum, this->m_maxRecvMsgSeqNum);
            printf("start apply inc packets after snapshot\n");
            this->ApplyPacketSequence();
            printf("end apply inc packets after snapshot\n");
            if(!this->StopListenSnapshot())
                return false;
            this->StartWaitIncremental();
		}
	}
	else {
        if(this->ApplyPacketSequence()) {
            this->m_waitTimer->Stop();
            return true;
        }
        /* TODO REMOVE!!!! */
        this->m_waitTimer->Activate();
        if(this->m_waitTimer->ElapsedSeconds() > 3) {
            printf("inc no message apply. time expired\n");
            if(!this->StartListenSnapshot())
                return false;
            this->m_waitTimer->Stop();
        }
		return true;
	}
	return true;
}

bool FeedConnection::Listen_Atom_Snapshot() {
    if(this->m_snapshotAvailable)
        return true;

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

    if(this->m_snapshotStartMsgSeqNum == -1)
        return true;

    while(this->m_snapshotStartMsgSeqNum <= this->m_snapshotEndMsgSeqNum) {
        if(this->m_packets[this->m_snapshotStartMsgSeqNum] == 0) {
            if (!this->m_waitTimer->Active()) {
                this->m_waitTimer->Start();
            }
            if (this->m_waitTimer->ElapsedSeconds() > 3) {
                printf("  snapshot has empty packets.\n");
                this->m_waitTimer->Stop();
                this->StartNewSnapshot();
            }
            return true;
        }
        FastSnapshotInfo *info = this->GetSnapshotInfo(this->m_snapshotStartMsgSeqNum);
        if(info == 0) {
            this->m_snapshotStartMsgSeqNum++;
            continue;
        }
        printf("\t\t  message -> MsgSeqNum = %d, TemplateId = %d, SendingTime = %lu IsRouteFirst = %d, IsLastFragment = %d, LastMsgSeqProcessed = %d, RptSeq = %d\n",
               this->m_snapshotStartMsgSeqNum,
               info->TemplateId,
               info->SendingTime,
               info->RouteFirst,
               info->LastFragment, info->LastMsgSeqNumProcessed, info->RptSeq);
        if(this->m_snapshotRouteFirst == -1) {
            if (info->RouteFirst == 1) {
                this->m_snapshotRouteFirst = this->m_snapshotStartMsgSeqNum;
            }
            else {
                this->m_snapshotStartMsgSeqNum++;
                continue;
            }
        }
        if (info->LastFragment == 0) {
            this->m_snapshotStartMsgSeqNum++;
            continue;
        }
        this->m_snapshotLastFragment = this->m_snapshotStartMsgSeqNum;
        this->m_snapshotStartMsgSeqNum++;
        printf("\t\tFound Snapshot -> MsgSeqNum = %d, TemplateId = %d, SendingTime = %lu RouteFirst = %d, LastFragment = %d, LastMsgSeqProcessed = %d, RptSeq = %d\n",
               this->m_snapshotStartMsgSeqNum - 1,
               info->TemplateId,
               info->SendingTime,
               this->m_snapshotRouteFirst,
               this->m_snapshotLastFragment, info->LastMsgSeqNumProcessed, info->RptSeq);
        if (info->LastMsgSeqNumProcessed == 0 && info->RptSeq == 0) {
            printf("\t\tEmpty Snapshot -> Apply\n");
            this->m_waitTimer->Stop();
            this->m_snapshotAvailable = true;
            return true;
        }
        if (info->LastMsgSeqNumProcessed < this->m_incremental->m_currentMsgSeqNum) {
            printf("\t\tOutdated Snapshot. Need %d vs %d -> Continue\n",
                   this->m_incremental->m_currentMsgSeqNum,
                   info->LastMsgSeqNumProcessed);
            this->m_snapshotRouteFirst = -1;
            this->m_snapshotLastFragment = -1;
            continue;
        }
        printf("\t\tCorrect Snapshot. Need %d vs %d - > Apply\n",
               this->m_incremental->m_currentMsgSeqNum,
               info->LastMsgSeqNumProcessed);

        this->m_lastMsgSeqNumProcessed = info->LastMsgSeqNumProcessed;
        this->m_rptSeq = info->RptSeq;

        this->m_waitTimer->Stop();
        this->m_snapshotAvailable = true;

        return true;
    }

	return true;
}
