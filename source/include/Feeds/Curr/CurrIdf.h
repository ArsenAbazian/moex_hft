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
        this->SetType(FeedConnectionType::fctInstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfCurr);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializeSecurityDefinition();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_IDF");
    }
    ~FeedConnection_CURR_IDF() {
        DisposeSecurityDefinition();
    }
    void AllocateFastObjects() {
#ifdef TEST
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(60, 10);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(130, 10);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(130, 10);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(130, 10);
#else
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(6000, 500);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(13000, 500);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(13000, 500);
        AstsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(13000, 500);
#endif
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