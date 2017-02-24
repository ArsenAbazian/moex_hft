//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURRMSR_H
#define HFT_ROBOT_CURRMSR_H

#include "../FeedConnection.h"

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
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
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

#endif //HFT_ROBOT_CURRMSR_H
