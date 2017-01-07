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
        InitializePackets();
    }
    FeedConnection_CURR_MSR() : FeedConnection() {
        this->m_statTableCurr = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidMsrCurr);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_CURR_MSS : public FeedConnection {
public:
    FeedConnection_CURR_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssCurr);
        InitializePackets();
    }
    FeedConnection_CURR_MSS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssCurr);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
    FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrCurr);
        InitializePackets();
    }
    FeedConnection_CURR_OLR() : FeedConnection() {
        this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidOlrCurr);
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
};

class FeedConnection_CURR_OLS : public FeedConnection {
public:
    FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsCurr);
        InitializePackets();
    }
    FeedConnection_CURR_OLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsCurr);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
    FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrCurr);
        InitializePackets();
    }
    FeedConnection_CURR_TLR() : FeedConnection() {
        this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidTlrCurr);
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
};

class FeedConnection_CURR_TLS : public FeedConnection {
public:
    FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsCurr);
        InitializePackets();
    }
    FeedConnection_CURR_TLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsCurr);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
    FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrFond);
        InitializePackets();
    }
    FeedConnection_FOND_MSR() : FeedConnection() {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrFond);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FOND_MSS : public FeedConnection {
public:
    FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssFond);
        InitializePackets();
    }
    FeedConnection_FOND_MSS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssFond);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
    FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrFond);
        InitializePackets();
    }
    FeedConnection_FOND_OLR() : FeedConnection() {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrFond);
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
};

class FeedConnection_FOND_OLS : public FeedConnection {
public:
    FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsFond);
        InitializePackets();
    }
    FeedConnection_FOND_OLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsFond);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
    FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrFond);
        InitializePackets();
    }
    FeedConnection_FOND_TLR() : FeedConnection() {
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->SetId(FeedConnectionId::fcidTlrFond);
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
};

class FeedConnection_FOND_TLS : public FeedConnection {
public:
    FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsFond);
        InitializePackets();
    }
    FeedConnection_FOND_TLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsFond);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
};

class FeedConnection_FOND_IDF : public FeedConnection{
public:
    FeedConnection_FOND_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfFond);
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
};

class FeedConnection_CURR_IDF : public FeedConnection{
public:
    FeedConnection_CURR_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfCurr);
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
};

class FeedConnection_FOND_ISF : public FeedConnection{
public:
    FeedConnection_FOND_ISF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentStatus);
        this->SetId(FeedConnectionId::fcidIsfFond);
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
};

class FeedConnection_CURR_ISF : public FeedConnection{
public:
    FeedConnection_CURR_ISF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentStatus);
        this->SetId(FeedConnectionId::fcidIsfCurr);
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
};

class FeedConnection_FOND_H : public FeedConnection{
public:
    FeedConnection_FOND_H(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *ip, int port) :
            FeedConnection(id, name, value, protocol, 0, ip, port, 0, 0, 0) {
        InitializeHistoricalReplay();
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
};

class FeedConnection_CURR_H : public FeedConnection{
public:
    FeedConnection_CURR_H(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *ip, int port) :
            FeedConnection(id, name, value, protocol, 0, ip, port, 0, 0, 0) {
        InitializeHistoricalReplay();
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
};

#endif //HFT_ROBOT_FEEDCONNECTIONS_H
