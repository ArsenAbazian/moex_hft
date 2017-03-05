//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDTLR_H
#define HFT_ROBOT_FONDTLR_H

#include "../FeedConnection.h"

class TradesFondAllocationInfo : public FastObjectsAllocationInfo {
public:
    TradesFondAllocationInfo() : FastObjectsAllocationInfo(32, 32) {
#ifndef TEST
        this->m_tLSFONDItemsCount = 800000;
        this->m_tLSFONDItemsAddCount = 20000;
#else
        this->m_tLSFONDItemsCount = 100;
        this->m_tLSFONDItemsAddCount = 100;
#endif
    }
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
    FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrFond);
        this->m_fastProtocolManager = new FastProtocolManager(new TradesFondAllocationInfo());
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_TLR");
    }
    ~FeedConnection_FOND_TLR() {
        delete this->m_tradeTableFond;
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

#endif //HFT_ROBOT_FONDTLR_H