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

    this->m_incremental = 0;
    this->m_snapshot = 0;
    this->m_connectionsToRecvSymbolsCount = 0;

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

    //this->obrLogFile = fopen("~Documents/hft_robot/logs/obr_log_file.txt", "wt"); TODO remove!
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

    this->m_incremental = 0;
    this->m_snapshot = 0;
    this->m_connectionsToRecvSymbolsCount = 0;

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


