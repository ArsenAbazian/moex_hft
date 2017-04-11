//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDMSR_H
#define HFT_ROBOT_FONDMSR_H

#include "../FeedConnection.h"

class FeedConnection_FOND_MSR : public FeedConnection {
public:
    FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::fctIncremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrFond);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_MSR");
    }
    ~FeedConnection_FOND_MSR() {
        delete this->m_statTableFond;
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateIncrementalMSRFONDInfoPoolTo(10);
#ifdef TEST
        AstsObjectsAllocationInfo::Default->AllocateGenericItemInfoPool(102, 10);
#else
        AstsObjectsAllocationInfo::Default->AllocateGenericItemInfoPool(10240, 1024);
#endif        
    }
    int GetPacketsCount() { return 10000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_FONDMSR_H
