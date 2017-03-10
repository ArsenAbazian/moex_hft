//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDOLS_H
#define HFT_ROBOT_FONDOLS_H

#include "../FeedConnection.h"

class FeedConnection_FOND_OLS : public FeedConnection {
public:
    FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidOlsFond);
        this->m_fastProtocolManager = new FastProtocolManager();
        this->AllocateFastObjects();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_OLS");
    }
    void AllocateFastObjects() {
        AstsObjectsAllocationInfo::Default->AllocateOLSFONDInfoPool(10, 10);
    }
    int GetPacketsCount() { return 50000; }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
};

#endif //HFT_ROBOT_FONDOLS_H