//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDOLR_H
#define HFT_ROBOT_FONDOLR_H

#include "../FeedConnection.h"

//class OrdersFondAllocationInfo : public FastObjectsAllocationInfo {
//public:
//    OrdersFondAllocationInfo() : FastObjectsAllocationInfo(32, 32) {
//#ifndef TEST
//        this->m_oLSFONDItemsCount = 202400;
//        this->m_oLSFONDItemsAddCount = 10240;
//#else
//        this->m_oLSFONDItemsCount = 100;
//        this->m_oLSFONDItemsAddCount = 100;
//#endif
//    }
//};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
    FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrFond);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_OLR");
    }
    ~FeedConnection_FOND_OLR() {
        delete this->m_orderTableFond;
    }
    void AllocateFastObjects() {
        FastObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FastObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        FastObjectsAllocationInfo::Default->AllocateIncrementalOLRFONDInfoPoolTo(10);
#ifdef TEST
        FastObjectsAllocationInfo::Default->AllocateOLSFONDItemInfoPool(100, 100);
#else
        FastObjectsAllocationInfo::Default->AllocateOLSFONDItemInfoPool(202400, 10240);
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

#endif //HFT_ROBOT_FONDOLR_H
