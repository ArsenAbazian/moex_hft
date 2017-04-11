//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_CURROLS_H
#define HFT_ROBOT_CURROLS_H

#include "../FeedConnection.h"

class FeedConnection_CURR_OLS : public FeedConnection {
public:
    FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::fctSnapshot);
        this->SetId(FeedConnectionId::fcidOlsCurr);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_CURR_OLS");
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateOLSCURRInfoPool(10, 10);
    }
    int GetPacketsCount() {
#ifdef TEST
        return 100;
#else
        return 50000;
#endif
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_CURROLS_H