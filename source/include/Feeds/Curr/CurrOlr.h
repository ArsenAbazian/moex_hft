//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURROLR_H
#define HFT_ROBOT_CURROLR_H

#include "../FeedConnection.h"

class OrdersCurrAllocationInfo : public FastObjectsAllocationInfo {
public:
    OrdersCurrAllocationInfo() : FastObjectsAllocationInfo(32, 32) {
#ifndef TEST
        this->m_oLSCURRItemsCount = 102400;
        this->m_oLSCURRItemsAddCount = 10240;
#else
        this->m_oLSCURRItemsCount = 100;
        this->m_oLSCURRItemsAddCount = 100;
#endif
    }
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
    FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->SetId(FeedConnectionId::fcidOlrCurr);

        this->m_fastProtocolManager = new FastProtocolManager(new OrdersCurrAllocationInfo());

        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_OLR");
    }
    ~FeedConnection_CURR_OLR() {
        delete this->m_orderTableCurr;
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
