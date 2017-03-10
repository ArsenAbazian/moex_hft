//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDHR_H
#define HFT_ROBOT_FONDHR_H

#include "../FeedConnection.h"

class FeedConnection_FOND_H : public FeedConnection{
public:
    FeedConnection_FOND_H(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *ip, int port) :
            FeedConnection(id, name, value, protocol, 0, ip, port, 0, 0, 0) {
        InitializeHistoricalReplay();
        this->m_fixProtocolManager->SetSenderComputerId(FundMarketSenderComputerId);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        PrepareLogonInfo();
        this->SetType(FeedConnectionType::HistoricalReplay);
        this->SetState(FeedConnectionState::fcsHistoricalReplay);
        this->SetHsState(FeedConnectionHistoricalReplayState::hsSuspend);
        this->SetId(FeedConnectionId::fcidHFond);
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_H");
    }
    ~FeedConnection_FOND_H() {
        DisposeHistoricalReplay();
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateLogonInfoPoolTo(10);
        AstsObjectsAllocationInfo::Default->AllocateLogoutInfoPoolTo(10);
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_FONDHR_H