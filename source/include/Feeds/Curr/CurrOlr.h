//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURROLR_H
#define HFT_ROBOT_CURROLR_H

#include "../FeedConnection.h"

class FeedConnection_CURR_OLR : public FeedConnection {
public:
    FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableCurr = new MarketDataTable<OrderInfo, AstsOLSCURRInfo, AstsOLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrCurr);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_OLR");
    }
    ~FeedConnection_CURR_OLR() {
        delete this->m_orderTableCurr;
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateIncrementalOLRCURRInfoPoolTo(10);
#ifdef TEST
        AstsObjectsAllocationInfo::Default->AllocateOLSCURRItemInfoPool(100, 100);
#else
        AstsObjectsAllocationInfo::Default->AllocateOLSCURRItemInfoPool(102400, 10240);
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

#endif //HFT_ROBOT_CURROLR_H
