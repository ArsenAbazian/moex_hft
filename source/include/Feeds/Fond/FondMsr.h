//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDMSR_H
#define HFT_ROBOT_FONDMSR_H

#include "../FeedConnection.h"

class StatisticsFondAllocationInfo : public FastObjectsAllocationInfo {
public:
    StatisticsFondAllocationInfo() : FastObjectsAllocationInfo(32, 32) {
#ifndef TEST
        this->m_genericItemsCount = 10240;
        this->m_genericItemsAddCount = 1024;
#else
        this->m_genericItemsCount = 100;
        this->m_genericItemsAddCount = 100;
#endif
    }
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
    FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetId(FeedConnectionId::fcidMsrFond);
        this->m_fastProtocolManager = new FastProtocolManager(new StatisticsFondAllocationInfo());
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_MSR");
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
