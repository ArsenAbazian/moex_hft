//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDMSS_H
#define HFT_ROBOT_FONDMSS_H

#include "../FeedConnection.h"

class FeedConnection_FOND_MSS : public FeedConnection {
public:
    FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidMssFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
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

#endif //HFT_ROBOT_FONDMSS_H