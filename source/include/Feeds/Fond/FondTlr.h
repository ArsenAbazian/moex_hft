//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDTLR_H
#define HFT_ROBOT_FONDTLR_H

#include "../FeedConnection.h"

//class TradesFondAllocationInfo : public AstsObjectsAllocationInfo {
//public:
//    TradesFondAllocationInfo() : AstsObjectsAllocationInfo(32, 32) {
//#ifndef TEST
//        this->m_astsTLSFONDItemsCount = 800000;
//        this->m_astsTLSFONDItemsAddCount = 20000;
//#else
//        this->m_astsTLSFONDItemsCount = 100;
//        this->m_astsTLSFONDItemsAddCount = 100;
//#endif
//    }
//};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
    FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::fctIncremental);
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, AstsTLSFONDInfo, AstsTLSFONDItemInfo>();
        this->m_tradeTableFond->SetOwnerParams(&(this->m_queueItemsCount), &(this->m_symbolsToRecvSnapshot), &(this->m_tableInSnapshotMode));
        this->SetId(FeedConnectionId::fcidTlrFond);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_TLR");
    }
    ~FeedConnection_FOND_TLR() {
        delete this->m_tradeTableFond;
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateIncrementalTLRFONDInfoPoolTo(10);
#ifdef TEST
        AstsObjectsAllocationInfo::Default->AllocateTLSFONDItemInfoPool(100, 100);
#else
        AstsObjectsAllocationInfo::Default->AllocateTLSFONDItemInfoPool(800000, 20000);
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

#endif //HFT_ROBOT_FONDTLR_H