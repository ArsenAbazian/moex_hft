//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURRTLR_H
#define HFT_ROBOT_CURRTLR_H

#include "../FeedConnection.h"

//class TradesCurrAllocationInfo : public AstsObjectsAllocationInfo {
//public:
//    TradesCurrAllocationInfo() : AstsObjectsAllocationInfo(32, 32) {
//#ifndef TEST
//        this->m_astsTLSCURRItemsCount = 800000;
//        this->m_astsTLSCURRItemsAddCount = 20000;
//#else
//        this->m_astsTLSCURRItemsCount = 100;
//        this->m_astsTLSCURRItemsAddCount = 100;
//#endif
//    }
//};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
    FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableCurr = new MarketDataTable<TradeInfo, AstsTLSCURRInfo, AstsTLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrCurr);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_TLR");
    }
    ~FeedConnection_CURR_TLR() {
        delete this->m_tradeTableCurr;
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateIncrementalTLRCURRInfoPoolTo(10);
#ifdef TEST
        AstsObjectsAllocationInfo::Default->AllocateTLSCURRItemInfoPool(100, 100);
#else
        AstsObjectsAllocationInfo::Default->AllocateTLSCURRItemInfoPool(800000, 20000);
#endif
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

#endif //HFT_ROBOT_CURRTLR_H