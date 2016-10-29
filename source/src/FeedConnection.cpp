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
    this->m_type = FeedConnectionType::Incremental;

	this->SetState(FeedConnectionState::fcsSuspend, &FeedConnection::Suspend_Atom);

    this->obrLogFile = fopen("~Documents/hft_robot/logs/obr_log_file.txt", "wt");
}

FeedConnection::FeedConnection() {
    this->m_packets = 0;

    this->m_fastProtocolManager = new FastProtocolManager();
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

    bool recv = this->ProcessServerA();
    recv |= this->ProcessServerB();

    if(!recv) {
        if(!this->m_waitTimer->Active(1)) {
            this->m_waitTimer->Start(1);
        }
        else {
            if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_Incremental, false);
                return false;
            }
        }
    }
    else {
        this->m_waitTimer->Stop(1);
    }

    if(this->WaitingSnapshot()) {
		if(this->m_snapshot->SnapshotAvailable()) {
			this->m_snapshot->ApplySnapshot();
			this->m_currentMsgSeqNum = this->m_snapshot->LastMsgSeqNumProcessed() + 1;
            this->ApplyPacketSequence();
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
        if(!this->m_waitTimer->Active()) {
            this->m_waitTimer->Start();
        }
        else {
            if(this->m_waitTimer->ElapsedSeconds() > 3) {
                if(!this->StartListenSnapshot())
                    return false;
                this->m_waitTimer->Stop();
            }
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
    for(int i = this->m_snapshotStartMsgSeqNum; i <= this->m_snapshotEndMsgSeqNum; i++) {
        FastSnapshotInfo *info = this->GetSnapshotInfo(i);
        if(info == NULL)
            continue;
        if(this->m_snapshotRouteFirst == -1) {
            this->m_snapshotStartMsgSeqNum = i + 1;
            if(info->RouteFirst == 1)
                this->m_snapshotRouteFirst = i;
            else
                continue;
        }
        if(info->LastFragment == 1) {
            this->m_snapshotLastFragment = i;
            printf("\t\tFound Snapshot -> MsgSeqNum = %d, TemplateId = %d, SendingTime = %lu RouteFirst = %d, LastFragment = %d, LastMsgSeqProcessed = %d, RptSeq = %d\n",
                   i,
                   info->TemplateId,
                   info->SendingTime,
                   this->m_snapshotRouteFirst,
                   this->m_snapshotLastFragment, info->LastMsgSeqNumProcessed, info->RptSeq);
            if(info->LastMsgSeqNumProcessed == 0 && info->RptSeq == 0) { //empty snapshot - no data
                this->m_waitTimer->Stop();
                this->m_snapshotAvailable = true;
                return true;
            }
            if(info->LastMsgSeqNumProcessed < this->m_incremental->m_currentMsgSeqNum) {
                this->m_snapshotRouteFirst = -1;
                this->m_snapshotLastFragment = -1;
                this->m_snapshotStartMsgSeqNum = i + 1;
                continue;
            }
            this->m_lastMsgSeqNumProcessed = info->LastMsgSeqNumProcessed;
            this->m_rptSeq = info->RptSeq;

            break;
        }
    }

    if(this->m_snapshotRouteFirst != -1 && this->m_snapshotLastFragment != -1) {
        for(int i = this->m_snapshotRouteFirst + 1; i < this->m_snapshotLastFragment; i++) {
            if(this->m_packets[i] == NULL) {
                if(!this->m_waitTimer->Active()) {
                    this->m_waitTimer->Start();
                    return true;
                }
                if(this->m_waitTimer->ElapsedSeconds() > 2) {
                    this->m_waitTimer->Stop();
                    this->StartNewSnapshot();
                }
                return true;
            }
        }
        this->m_waitTimer->Stop();
        this->m_snapshotAvailable = true;
    }

	return true;
}
