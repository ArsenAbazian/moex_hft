//
// Created by root on 04.01.17.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONS_H
#define HFT_ROBOT_FEEDCONNECTIONS_H

#include "FeedConnection.h"

class FeedConnection_CURR_MSR : public FeedConnection {
public:
    FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableCurr = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_CURR_MSR() : FeedConnection() {
        this->m_statTableCurr = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidMsrCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_genericCount = 1024;
        info->m_genericAddCount = 256;
        info->m_genericItemsCount = 1024;
        info->m_genericItemsAddCount = 1024;
#else
        info->m_genericCount = 100;
        info->m_genericAddCount = 100;
        info->m_genericItemsCount = 100;
        info->m_genericItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;
        info->m_incrementalMSRCURRCount = 100;
        info->m_incrementalMSRCURRAddCount = 100;

        return info;
    }
};

class FeedConnection_CURR_MSS : public FeedConnection {
public:
    FeedConnection_CURR_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_CURR_MSS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_genericCount = 1024;
        info->m_genericAddCount = 256;
        info->m_genericItemsCount = 1024;
        info->m_genericItemsAddCount = 256;
#else
        info->m_genericCount = 100;
        info->m_genericAddCount = 100;
        info->m_genericItemsCount = 100;
        info->m_genericItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
    FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_CURR_OLR() : FeedConnection() {
        this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidOlrCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ~FeedConnection_CURR_OLR() {
        delete this->m_orderTableCurr;
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_incrementalOLRCURRCount = 1024;
        info->m_incrementalOLRCURRAddCount = 256;
        info->m_oLSCURRItemsCount = 102400;
        info->m_oLSCURRItemsAddCount = 10240;
#else
        info->m_incrementalOLRCURRCount = 100;
        info->m_incrementalOLRCURRAddCount = 100;
        info->m_oLSCURRItemsCount = 100;
        info->m_oLSCURRItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_OLS : public FeedConnection {
public:
    FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_CURR_OLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_oLSCURRCount = 32;
        info->m_oLSCURRAddCount = 256;
#ifndef TEST
        info->m_oLSCURRItemsCount = 102400;
        info->m_oLSCURRItemsAddCount = 10240;
#else
        info->m_oLSCURRItemsCount = 100;
        info->m_oLSCURRItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
    FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_CURR_TLR() : FeedConnection() {
        this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidTlrCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ~FeedConnection_CURR_TLR() {
        delete this->m_tradeTableCurr;
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_incrementalTLRCURRCount = 1024;
        info->m_incrementalTLRCURRAddCount = 256;
        info->m_tLSCURRItemsCount = 2024;
        info->m_tLSCURRItemsAddCount = 256;
#else
        info->m_incrementalTLRCURRCount = 100;
        info->m_incrementalTLRCURRAddCount = 100;
        info->m_tLSCURRItemsCount = 100;
        info->m_tLSCURRItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_TLS : public FeedConnection {
public:
    FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_CURR_TLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_tLSCURRCount = 1024;
        info->m_tLSCURRAddCount = 256;
        info->m_tLSCURRItemsCount = 2024;
        info->m_tLSCURRItemsAddCount = 256;
#else
        info->m_tLSCURRCount = 100;
        info->m_tLSCURRAddCount = 100;
        info->m_tLSCURRItemsCount = 100;
        info->m_tLSCURRItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
    FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_FOND_MSR() : FeedConnection() {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_genericCount = 1024;
        info->m_genericAddCount = 256;
        info->m_genericItemsCount = 1024;
        info->m_genericItemsAddCount = 1024;
#else
        info->m_genericCount = 100;
        info->m_genericAddCount = 100;
        info->m_genericItemsCount = 100;
        info->m_genericItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;
        info->m_incrementalMSRFONDCount = 100;
        info->m_incrementalMSRFONDAddCount = 100;

        return info;
    }
};

class FeedConnection_FOND_MSS : public FeedConnection {
public:
    FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_FOND_MSS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_genericCount = 1024;
        info->m_genericAddCount = 256;
        info->m_genericItemsCount = 1024;
        info->m_genericItemsAddCount = 1024;
#else
        info->m_genericCount = 100;
        info->m_genericAddCount = 100;
        info->m_genericItemsCount = 100;
        info->m_genericItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
    FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_FOND_OLR() : FeedConnection() {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ~FeedConnection_FOND_OLR() {
        delete this->m_orderTableFond;
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_incrementalOLRFONDCount = 1024;
        info->m_incrementalOLRFONDAddCount = 256;
        info->m_oLSFONDItemsCount = 202400;
        info->m_oLSFONDItemsAddCount = 25600;
#else
        info->m_incrementalOLRFONDCount = 100;
        info->m_incrementalOLRFONDAddCount = 100;
        info->m_oLSFONDItemsCount = 100;
        info->m_oLSFONDItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_OLS : public FeedConnection {
public:
    FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_FOND_OLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_oLSFONDCount = 1024;
        info->m_oLSFONDAddCount = 256;
        info->m_oLSFONDItemsCount = 202400;
        info->m_oLSFONDItemsAddCount = 25600;
#else
        info->m_oLSFONDCount = 10;
        info->m_oLSFONDAddCount = 10;
        info->m_oLSFONDItemsCount = 100;
        info->m_oLSFONDItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
    FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_FOND_TLR() : FeedConnection() {
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidTlrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ~FeedConnection_FOND_TLR() {
        delete this->m_tradeTableFond;
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_incrementalTLRFONDCount = 1024;
        info->m_incrementalTLRFONDAddCount = 256;
        info->m_tLSFONDItemsCount = 2024;
        info->m_tLSFONDItemsAddCount = 256;
#else
        info->m_incrementalTLRFONDCount = 100;
        info->m_incrementalTLRFONDAddCount = 100;
        info->m_tLSFONDItemsCount = 100;
        info->m_tLSFONDItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_TLS : public FeedConnection {
public:
    FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    FeedConnection_FOND_TLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_tLSFONDCount = 1024;
        info->m_tLSFONDAddCount = 256;
        info->m_tLSFONDItemsCount = 2024;
        info->m_tLSFONDItemsAddCount = 256;
#else
        info->m_tLSFONDCount = 100;
        info->m_tLSFONDAddCount = 100;
        info->m_tLSFONDItemsCount = 100;
        info->m_tLSFONDItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_IDF : public FeedConnection{
public:
    FeedConnection_FOND_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_FOND_IDF() {
        DisposeSecurityDefinition();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_securityDefinitionCount = 13000;
        info->m_securityDefinitionAddCount = 256;
        info->m_securityDefinitionGroupInstrAttribItemsCount = 13000;
        info->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
#else
        info->m_securityDefinitionCount = 1000;
        info->m_securityDefinitionAddCount = 256;
        info->m_securityDefinitionGroupInstrAttribItemsCount = 100;
        info->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpItemsCount = 100;
        info->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 100;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_IDF : public FeedConnection{
public:
    FeedConnection_CURR_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_CURR_IDF() {
        DisposeSecurityDefinition();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_securityDefinitionCount = 13000;
        info->m_securityDefinitionAddCount = 256;
        info->m_securityDefinitionGroupInstrAttribItemsCount = 13000;
        info->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_ISF : public FeedConnection{
public:
    FeedConnection_FOND_ISF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentStatus);
        this->SetId(FeedConnectionId::fcidIsfFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_FOND_ISF() {
        DisposeSecurityDefinition();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_securityStatusCount = 10;
        info->m_securityStatusAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_ISF : public FeedConnection{
public:
    FeedConnection_CURR_ISF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentStatus);
        this->SetId(FeedConnectionId::fcidIsfCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_CURR_ISF() {
        DisposeSecurityDefinition();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_securityStatusCount = 10;
        info->m_securityStatusAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;

        return info;
    }
};

class FeedConnection_FOND_H : public FeedConnection{
public:
    FeedConnection_FOND_H(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *ip, int port) :
            FeedConnection(id, name, value, protocol, 0, ip, port, 0, 0, 0) {
        InitializeHistoricalReplay();
        this->m_fixProtocolManager->SetSenderComputerId(FundMarketSenderComputerId);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        PrepareLogonInfo();
        this->SetType(FeedConnectionType::HistoricalReplay);
        this->SetState(FeedConnectionState::fcsHistoricalReplay);
        this->SetHsState(FeedConnectionHistoricalReplayState::hsSuspend);
        this->SetId(FeedConnectionId::fcidHFond);
    }
    ~FeedConnection_FOND_H() {
        DisposeHistoricalReplay();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_logonCount = 10;
        info->m_logonAddCount = 10;
        info->m_logoutCount = 10;
        info->m_logoutAddCount = 10;

        return info;
    }
};

class FeedConnection_CURR_H : public FeedConnection{
public:
    FeedConnection_CURR_H(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *ip, int port) :
            FeedConnection(id, name, value, protocol, 0, ip, port, 0, 0, 0) {
        InitializeHistoricalReplay();
        this->m_fixProtocolManager->SetSenderComputerId(CurrencyMarketSenderComputerId);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        PrepareLogonInfo();
        this->SetType(FeedConnectionType::HistoricalReplay);
        this->SetState(FeedConnectionState::fcsHistoricalReplay);
        this->SetHsState(FeedConnectionHistoricalReplayState::hsSuspend);
        this->SetId(FeedConnectionId::fcidHCurr);
    }
    ~FeedConnection_CURR_H() {
        DisposeHistoricalReplay();
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_logonCount = 10;
        info->m_logonAddCount = 10;
        info->m_logoutCount = 10;
        info->m_logoutAddCount = 10;

        return info;
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONS_H
