#include "../include/Feeds/FeedConnection.h"

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

    this->m_fastLogonInfo = new AstsLogonInfo();
    this->m_socketABufferProvider = CreateSocketBufferProvider();
    this->m_sendABuffer = this->m_socketABufferProvider->SendBuffer();
    this->m_recvABuffer = this->m_socketABufferProvider->RecvBuffer();

    this->m_waitLostIncrementalMessageMaxTimeMcs = 100000;
    this->m_waitIncrementalMessageMaxTimeMcs = this->WaitAnyPacketMaxTimeMcs;
    this->m_snapshotMaxTimeMcs = 30000;
    this->m_maxLostPacketCountForStartSnapshot = 2000;

    this->m_astsSnapshotInfo = 0;
    this->m_fortsSnapshotInfo = 0;
    this->m_fortsTradingSessionStatus = 0;

    this->m_incremental = 0;
    this->m_snapshot = 0;
    this->m_connectionsToRecvSymbolsCount = 0;
    this->m_connToRecvHistoricalReplayCount = 0;
    this->m_enableHistoricalReplay = true;
    this->m_reconnectCount = 0;
    this->m_maxReconnectCount = 20;

    this->socketAManager = NULL;
    this->socketBManager = NULL;

    this->m_stopwatch = new Stopwatch();
    this->m_waitTimer = new Stopwatch();

    this->m_tval = new struct timeval;

    this->m_marketType = FeedMarketType::fmtAsts;
    this->m_windowMsgSeqNum = 0;
    this->m_startMsgSeqNum = 1;
    this->m_endMsgSeqNum = 0;
    this->m_requestMessageStartIndex = -1;
    this->m_securityStatusSnapshotActive = false;
    this->m_idfStopAfterUpdateAllMessages = false;
    this->m_allowGenerateSecurityDefinitions = false;
    this->m_isfStartSnapshotCount = 0;
    this->m_packetsCount = 0;
    this->m_packets = 0;
    this->m_hrUnsuccessfulConnectCount = 0;

    this->m_fortsIncrementalRouteFirst = 1;
    this->m_fortsRouteFirtsSecurityId = 0;
    this->m_nextFortsSnapshotRouteFirst = 0;

    this->SetState(FeedConnectionState::fcsSuspend);

    strcpy(this->m_channelName, "");
    this->m_orderTableFond = 0;
    this->m_orderTableCurr = 0;
    this->m_tradeTableFond = 0;
    this->m_tradeTableCurr = 0;
    this->m_statTableFond = 0;
    this->m_statTableCurr = 0;
    this->m_fortsOrderBookTable = 0;
    this->m_fortsTradeBookTable = 0;
}

FeedConnection::~FeedConnection() {
    if(this->m_packets != 0) {
        for(int i = 0; i < this->m_packetsCount; i++)
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


