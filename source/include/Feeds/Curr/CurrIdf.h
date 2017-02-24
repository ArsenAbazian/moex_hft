//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURRIDF_H
#define HFT_ROBOT_CURRIDF_H

#include "../FeedConnection.h"

class FeedConnection_CURR_IDF : public FeedConnection{
public:
    FeedConnection_CURR_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfCurr);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_CURR_IDF() {
        DisposeSecurityDefinition();
    }
    int GetPacketsCount() { return RobotSettings::Default->DefaultFeedConnectionPacketCount; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

        info->m_securityDefinitionCount = 13000;
        info->m_securityDefinitionAddCount = 256;
        info->m_securityDefinitionGroupInstrAttribItemsCount = 13000;
        info->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

#endif //HFT_ROBOT_CURRIDF_H