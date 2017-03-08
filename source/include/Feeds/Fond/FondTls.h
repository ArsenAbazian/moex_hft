//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDTLS_H
#define HFT_ROBOT_FONDTLS_H

#include "../FeedConnection.h"

class FeedConnection_FOND_TLS : public FeedConnection {
public:
    FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Snapshot);
        this->SetId(FeedConnectionId::fcidTlsFond);
        this->m_fastProtocolManager = new FastProtocolManager();
        InitializePackets(this->GetPacketsCount());
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnection_FOND_TLS");
    }
    void AllocateFastObjects() {
        FastObjectsAllocationInfo::Default->AllocateTLSFONDInfoPool(10, 10);
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

#endif //HFT_ROBOT_FONDTLS_H