//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDOLS_H
#define HFT_ROBOT_FONDOLS_H

#include "../FeedConnection.h"

class FeedConnection_FOND_OLS : public FeedConnection {
public:
    FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsFond);
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
        info->m_oLSFONDCount = 1024;
        info->m_oLSFONDAddCount = 256;
        info->m_oLSFONDItemsCount = 202400;
        info->m_oLSFONDItemsAddCount = 25600;
#else
        info->m_oLSFONDCount = 10;
        info->m_oLSFONDAddCount = 10;
        info->m_oLSFONDItemsCount = 100;
        info->m_oLSFONDItemsAddCount = 100;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

#endif //HFT_ROBOT_FONDOLS_H