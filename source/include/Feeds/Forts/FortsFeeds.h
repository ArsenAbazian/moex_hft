//
// Created by root on 12.03.17.
//

#ifndef HFT_ROBOT_FORTSFEEDS_H
#define HFT_ROBOT_FORTSFEEDS_H

#include "../FeedConnection.h"

class FeedConnection_FORTS_INC : public FeedConnection {
public:
    FeedConnection_FORTS_INC(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::fctIncrementalForts;
        this->m_id = FeedConnectionId::fcidIncForts;
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_INC");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultIncrementalRefreshMessageInfoPool(10, 10);
#ifdef TEST
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(100, 500);
#else
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(300000, 500);
#endif
    }
    int GetPacketsCount() {
#ifdef TEST
        return 100;
#else
        return 10000;
#endif
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_INDEX : public FeedConnection {
public:
    FeedConnection_FORTS_INDEX(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::fctIncrementalForts;
        this->m_id = FeedConnectionId::fcidIndexForts;
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_INDEX");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultIncrementalRefreshMessageInfoPool(10, 10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(300000, 500);
    }
    int GetPacketsCount() { return 10000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_NEWS : public FeedConnection {
public:
    FeedConnection_FORTS_NEWS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::fctIncrementalForts;
        this->m_id = FeedConnectionId::fcidNewsForts;
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_NEWS");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultIncrementalRefreshMessageInfoPool(10, 10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(300000, 500);
    }
    int GetPacketsCount() { return 10000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_NEWS_SKRIN : public FeedConnection {
public:
    FeedConnection_FORTS_NEWS_SKRIN(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::fctIncrementalForts;
        this->m_id = FeedConnectionId::fcidNewsSkrinForts;
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_NEWS_SKRIN");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultIncrementalRefreshMessageInfoPool(10, 10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(300000, 500);
    }
    int GetPacketsCount() { return 10000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_OBR : public FeedConnection {
public:
    FeedConnection_FORTS_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::fctIncrementalForts;
        this->m_id = FeedConnectionId::fcidObrForts;
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_fortsOrderBookTable = new MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        this->m_fortsOrderBookTable->SetOwnerParams(&(this->m_queueItemsCount), &(this->m_symbolsToRecvSnapshot), &(this->m_tableInSnapshotMode));
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_OBR");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultIncrementalRefreshMessageInfoPool(10, 10);
#ifdef TEST
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(100, 500);
#else
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(100);
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(300000, 500);
#endif
    }
    int GetPacketsCount() {
#ifdef TEST
        return 100;
#else
        return 10000;
#endif
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_TLR : public FeedConnection {
public:
    FeedConnection_FORTS_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_type = FeedConnectionType::fctIncrementalForts;
        this->m_id = FeedConnectionId::fcidTlrForts;
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_fortsTradeBookTable = new MarketDataTable<TradeInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        this->m_fortsTradeBookTable->SetOwnerParams(&(this->m_queueItemsCount), &(this->m_symbolsToRecvSnapshot), &(this->m_tableInSnapshotMode));
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_TLR");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultIncrementalRefreshMessageInfoPool(10, 10);
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(300000, 500);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(100);
    }
    int GetPacketsCount() { return 10000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_SNAP : public FeedConnection {
public:
    FeedConnection_FORTS_SNAP(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_marketType = FeedMarketType::fmtForts;
        this->SetType(FeedConnectionType::fctSnapshot);
        this->m_id = FeedConnectionId::fcidSnapForts;
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_SNAP");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateDefaultSnapshotMessageInfoPool(10, 10);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(100);
    }
    int GetPacketsCount() {
#ifdef TEST
        return 100;
#else
        return 50000;
#endif
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_HR : public FeedConnection {
public:
    FeedConnection_FORTS_HR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_marketType = FeedMarketType::fmtForts;
        InitializeHistoricalReplay();
        this->m_fixProtocolManager->SetSenderComputerId(CurrencyMarketSenderComputerId);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        PrepareLogonInfo();
        this->SetType(FeedConnectionType::fctHistoricalReplay);
        this->SetState(FeedConnectionState::fcsHistoricalReplay);
        this->SetHsState(FeedConnectionHistoricalReplayState::hsSuspend);
        this->SetId(FeedConnectionId::fcidHrForts);
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_HR");
    }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateLogonInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateLogoutInfoPoolTo(10);
    }
    ~FeedConnection_FORTS_HR() {
        DisposeHistoricalReplay();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_INSTR_INC : public FeedConnection {
public:
    FeedConnection_FORTS_INSTR_INC(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_marketType = FeedMarketType::fmtForts;
        this->m_type = FeedConnectionType::fctInstrumentStatusForts;
        this->SetId(FeedConnectionId::fcidIdfIncForts);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_INSTR_INC");
    }
    int GetPacketsCount() { return 1000; }
    void AllocateFastObjects() {
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(100);
        FortsObjectsAllocationInfo::Default->AllocateSecurityStatusInfoPool(50, 10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionUpdateReportInfoPool(50, 10);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FORTS_INSTR_SNAP : public FeedConnection {
public:
    FeedConnection_FORTS_INSTR_SNAP(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->m_marketType = FeedMarketType::fmtForts;
        this->SetType(FeedConnectionType::fctInstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfForts);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializeSecurityDefinitionForts();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FORTS_INSTR_SNAP");
    }
    ~FeedConnection_FORTS_INSTR_SNAP() {
        DisposeSecurityDefinitionForts();
    }
    void AllocateFastObjects() {
        int sdSeqCount = 13000;
        int sdSeqCountAdd = 500;
#ifdef TEST
        sdSeqCount = 60;
        sdSeqCountAdd = 10;
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(60, 10);
#else
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(100);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(6000, 500);
#endif
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMDFeedTypesItemInfoPool(sdSeqCount, sdSeqCountAdd);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionUnderlyingsItemInfoPool(sdSeqCount, sdSeqCountAdd);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInstrumentLegsItemInfoPool(sdSeqCount, sdSeqCountAdd);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInstrumentAttributesItemInfoPool(sdSeqCount, sdSeqCountAdd);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionEvntGrpItemInfoPool(sdSeqCount, sdSeqCountAdd);
    }
    int GetPacketsCount() { return 1000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_FORTSFEEDS_H
