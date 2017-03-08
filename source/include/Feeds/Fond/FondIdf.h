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
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializeSecurityDefinition();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_IDF");
    }
    ~FeedConnection_FOND_IDF() {
        DisposeSecurityDefinition();
    }
    void AllocateFastObjects() {
#ifdef TEST
        FastObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FastObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(60, 10);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(130, 10);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(130, 10);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(130, 10);
#else
        FastObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FastObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(20000, 300);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(40000, 300);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(20000, 300);
        FastObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(40000, 300);
#endif
    }
    int GetPacketsCount() { return 20000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_FONDIDF_H