//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDISF_H
#define HFT_ROBOT_FONDISF_H

#include "../FeedConnection.h"

class FeedConnection_FOND_ISF : public FeedConnection{
public:
    FeedConnection_FOND_ISF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentStatus);
        this->SetId(FeedConnectionId::fcidIsfFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_FOND_ISF() {
        DisposeSecurityDefinition();
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

        info->m_securityStatusCount = 10;
        info->m_securityStatusAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;

        return info;
    }
};

#endif //HFT_ROBOT_FONDISF_H
