//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURRTLS_H
#define HFT_ROBOT_CURRTLS_H

#include "../FeedConnection.h"

class FeedConnection_CURR_TLS : public FeedConnection {
public:
    FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsCurr);
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
        info->m_tLSCURRCount = 1024;
        info->m_tLSCURRAddCount = 256;
        info->m_tLSCURRItemsCount = 800000;
        info->m_tLSCURRItemsAddCount = 20000;
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

#endif //HFT_ROBOT_CURRTLS_H