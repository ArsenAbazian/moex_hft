#pragma once

#include <cstdint>

#define ROBOT_WORK_ANYWAY
//#define TEST

#define null 0
#define BYTE unsigned char
#define UINT32 unsigned int
#define WORD unsigned short
#define DWORD uint32_t
#define INT32 int
#define UINT64 uint64_t
#define INT64 int64_t
#define UINT uint32_t

class RobotSettings {
public:
    static RobotSettings* Default;

    int SocketBuffersMaxCount;
    unsigned int DefaultFeedConnectionSendBufferSize;
    unsigned int DefaultFeedConnectionRecvBufferSize;
    unsigned int DefaultFeedConnectionSendItemsCount;
    unsigned int DefaultFeedConnectionRecvItemsCount;
    unsigned int DefaultMarketSendBufferSize;
    unsigned int DefaultMarketRecvBufferSize;
    unsigned int DefaultMarketSendItemsCount;
    unsigned int DefaultMarketRecvItemsCount;
    int MarketDataMaxSymbolsCount;
    int MarketDataMaxSessionsCount;
    int MarketDataMaxEntriesCount;
    int MaxSecurityDefinitionCount;
    int HistoricalReplayMaxMessageRequestCount;
    int MDEntryQueueItemsCount;
    int MDEntryQueueItemsAddCount;

    RobotSettings() {
        SocketBuffersMaxCount = 256; // they are created only when needed
        DefaultFeedConnectionSendBufferSize = 4 * 1024 * 1024;
        DefaultFeedConnectionRecvBufferSize = 16 * 1024 * 1024;
        DefaultFeedConnectionSendItemsCount = 20000;        // I think that we most will listen data - no to send
        DefaultFeedConnectionRecvItemsCount = 200000;       // I don't know yet how much items needed

        DefaultMarketSendBufferSize = 8 * 1024 * 1024;     // why 16? don't know
        DefaultMarketRecvBufferSize = 8 * 1024 * 1024;
        DefaultMarketSendItemsCount = 4 * 1024 * 1024;
        DefaultMarketRecvItemsCount = 4 * 1024 * 1024;

        MarketDataMaxSymbolsCount = 2600;
        MarketDataMaxSessionsCount = 8;
        MarketDataMaxEntriesCount = 1024 * 2000;
        MaxSecurityDefinitionCount = 2600;
        HistoricalReplayMaxMessageRequestCount = 1024;
        MDEntryQueueItemsCount = 10000;
        MDEntryQueueItemsAddCount = 100;
    }
};





