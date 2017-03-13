//
// Created by root on 12.03.17.
//

#ifndef HFT_ROBOT_FORTSFEEDS_H
#define HFT_ROBOT_FORTSFEEDS_H

#include "../FeedConnection.h"

class FeedConnection_FORTS_INC : public FeedConnection {
public:
    FeedConnection_FORTS_INC(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_SNAP : public FeedConnection {
public:
    FeedConnection_FORTS_SNAP(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_HR : public FeedConnection {
public:
    FeedConnection_FORTS_HR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_INSTR_INC : public FeedConnection {
public:
    FeedConnection_FORTS_INSTR_INC(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) { }
};

class FeedConnection_FORTS_INSTR_SNAP : public FeedConnection {
public:
    FeedConnection_FORTS_INSTR_SNAP(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->SetId(FeedConnectionId::fcidIdfForts);
        this->m_fastProtocolManager = new FastProtocolManager();
        //this->AllocateFastObjects();
        //InitializeSecurityDefinition();
        //InitializePackets(this->GetPacketsCount());
        //DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_IDF");
    }
    /*
    void AllocateFastObjects() {
#ifdef TEST
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(60, 10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(130, 10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(130, 10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(130, 10);
#else
        FortsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionInfoPool(6000, 500);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(13000, 500);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(13000, 500);
        FortsObjectsAllocationInfo::Default->AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(13000, 500);
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
    */
};

#endif //HFT_ROBOT_FORTSFEEDS_H
