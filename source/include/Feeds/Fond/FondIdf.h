//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDIDF_H
#define HFT_ROBOT_FONDIDF_H

#include "../FeedConnection.h"

class FeedConnection_FOND_IDF : public FeedConnection{
public:
    FeedConnection_FOND_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets();
    }
    ~FeedConnection_FOND_IDF() {
        DisposeSecurityDefinition();
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
        info->m_securityDefinitionCount = 13000;
        info->m_securityDefinitionAddCount = 256;
        info->m_securityDefinitionGroupInstrAttribItemsCount = 13000;
        info->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 13000;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
#else
        info->m_securityDefinitionCount = 1000;
        info->m_securityDefinitionAddCount = 256;
        info->m_securityDefinitionGroupInstrAttribItemsCount = 100;
        info->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpItemsCount = 100;
        info->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 100;
        info->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
#endif
        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

#endif //HFT_ROBOT_FONDIDF_H