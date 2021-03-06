//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURRMSR_H
#define HFT_ROBOT_CURRMSR_H

#include "../FeedConnection.h"

//class StatisticsCurrAllocationInfo : public AstsObjectsAllocationInfo {
//public:
//    StatisticsCurrAllocationInfo() : AstsObjectsAllocationInfo(32, 32) {
//#ifndef TEST
//        this->m_genericItemsCount = 10240;
//        this->m_genericItemsAddCount = 1024;
//#else
//        this->m_genericItemsCount = 100;
//        this->m_genericItemsAddCount = 100;
//#endif
//        this->AllocateHeartbeatInfoPool();
//        this->AllocateTradingSessionStatusInfoPool();
//        this->AllocateIncrementalMSRCURRInfoPool();
//        this->AllocateGenericItemInfoPool();
//    }
//};

class FeedConnection_CURR_MSR : public FeedConnection {
public:
    FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::fctIncremental);
        this->m_statTableCurr = new MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo>();
        this->m_statTableCurr->SetOwnerParams(&(this->m_queueItemsCount), &(this->m_symbolsToRecvSnapshot), &(this->m_tableInSnapshotMode));
        this->SetId(FeedConnectionId::fcidMsrCurr);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_MSR");
    }
    ~FeedConnection_CURR_MSR() {
        delete this->m_statTableCurr;
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateHeartbeatInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateTradingSessionStatusInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateIncrementalMSRCURRInfoPoolTo(10);
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

#endif //HFT_ROBOT_CURRMSR_H
