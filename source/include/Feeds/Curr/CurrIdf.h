//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURRIDF_H
#define HFT_ROBOT_CURRIDF_H

#include "../FeedConnection.h"

class SecurityDefinitionCurrAllocationInfo : public FastObjectsAllocationInfo {
public:
    SecurityDefinitionCurrAllocationInfo() : FastObjectsAllocationInfo(32, 32) {
#ifndef TEST
        this->m_securityDefinitionCount = 6000;
        this->m_securityDefinitionAddCount = 256;
        this->m_securityDefinitionGroupInstrAttribItemsCount = 13000;
        this->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        this->m_securityDefinitionMarketSegmentGrpItemsCount = 13000;
        this->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 13000;
        this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
#else
        this->m_securityDefinitionCount = 60;
        this->m_securityDefinitionAddCount = 256;
        this->m_securityDefinitionGroupInstrAttribItemsCount = 130;
        this->m_securityDefinitionGroupInstrAttribItemsAddCount = 256;
        this->m_securityDefinitionMarketSegmentGrpItemsCount = 130;
        this->m_securityDefinitionMarketSegmentGrpItemsAddCount = 256;
        this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 130;
        this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 256;
#endif
    }
};

class FeedConnection_CURR_IDF : public FeedConnection{
public:
    FeedConnection_CURR_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfCurr);
        this->m_fastProtocolManager = new FastProtocolManager(new SecurityDefinitionCurrAllocationInfo());
        InitializeSecurityDefinition();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_IDF");
    }
    ~FeedConnection_CURR_IDF() {
        DisposeSecurityDefinition();
    }
    int GetPacketsCount() { return 1000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_CURRIDF_H