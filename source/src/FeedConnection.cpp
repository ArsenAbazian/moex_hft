#include "FeedConnection.h"

FeedConnection::FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) {
	strcpy(this->m_idName, id);
	strcpy(this->feedTypeName, name);

	this->m_idLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_idName);
	this->m_feedTypeNameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->feedTypeName);

	this->feedTypeValue = value;
	this->protocol = protocol;
	
	if(aSourceIp != 0)
        strcpy(this->feedASourceIp, aSourceIp);
	if(aIp != 0)
        strcpy(this->feedAIp, aIp);
	this->feedAPort = aPort;

	if(bSourceIp != 0)
        strcpy(this->feedBSourceIp, bSourceIp);
    if(bIp != 0)
	    strcpy(this->feedBIp, bIp);
	this->feedBPort = bPort;

    this->m_fastLogonInfo = new FastLogonInfo();
	this->m_socketABufferProvider = CreateSocketBufferProvider();
	this->m_sendABuffer = this->m_socketABufferProvider->SendBuffer();
	this->m_recvABuffer = this->m_socketABufferProvider->RecvBuffer();

    this->m_waitIncrementalMaxTimeMs = 3000;
    this->m_snapshotMaxTimeMs = 3000;
    this->m_maxLostPacketCountForStartSnapshot = 0; // by default immediately start snapshot

    this->m_incremental = 0;
    this->m_snapshot = 0;
    this->m_connectionsToRecvSymbolsCount = 0;

    this->socketAManager = NULL;
    this->socketBManager = NULL;

	this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();

    this->m_tval = new struct timeval;

	this->m_startMsgSeqNum = 1;
	this->m_endMsgSeqNum = 0;
    this->m_requestMessageStartIndex = -1;
    this->m_securityStatusSnapshotActive = false;
    this->m_idfStopAfterUpdateAllMessages = false;

	this->SetState(FeedConnectionState::fcsSuspend);

    this->m_orderTableFond = 0;
    this->m_orderTableCurr = 0;
    this->m_tradeTableFond = 0;
    this->m_tradeTableCurr = 0;
    this->m_statTableFond = 0;
    this->m_statTableCurr = 0;

    //this->obrLogFile = fopen("~Documents/hft_robot/logs/obr_log_file.txt", "wt"); TODO remove!
}

FeedConnection::FeedConnection() {
    for(int i = 0; i < RobotSettings::DefaultFeedConnectionPacketCount; i++)
        this->m_packets[i] = new FeedConnectionMessageInfo();

    this->m_fastLogonInfo = new FastLogonInfo();

    this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();
    this->m_waitIncrementalMaxTimeMs = 3000;
    this->m_snapshotMaxTimeMs = 3000;

    this->m_tval = new struct timeval;

    this->m_incremental = 0;
    this->m_snapshot = 0;
    this->m_connectionsToRecvSymbolsCount = 0;

    this->m_startMsgSeqNum = 1;
    this->m_endMsgSeqNum = 0;
    this->m_requestMessageStartIndex = -1;
    this->m_securityStatusSnapshotActive = false;
    this->m_idfStopAfterUpdateAllMessages = false;

    this->m_type = FeedConnectionType::Incremental;
    this->m_packets = 0;

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


