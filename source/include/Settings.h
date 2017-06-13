#pragma once

#include <cstdint>

#define ROBOT_WORK_ANYWAY
#define TEST
#ifdef TEST
//#define TEST_LIST
#endif

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
    int MarketDataMaxSymbolsCountForts;
    int MarketDataMaxSessionsCount;
    int MarketDataMaxEntriesCount;
    int MaxSecurityDefinitionCount;
    int HistoricalReplayMaxMessageRequestCount;
    int MDEntryQueueItemsCount;
    int MDEntryQueueItemsAddCount;

    RobotSettings() {
        SocketBuffersMaxCount = 256; // they are created only when needed


        DefaultFeedConnectionSendItemsCount = 2000;        // I think that we most will listen data - no to send
#ifdef TEST
        DefaultFeedConnectionSendBufferSize = 4 * 1024 * 1024;
        DefaultFeedConnectionRecvBufferSize = 4 * 1024 * 1024;
        DefaultFeedConnectionRecvItemsCount = 2000;       // I don't know yet how much items needed
#else
        DefaultFeedConnectionSendBufferSize = 4 * 1024 * 1024;
        DefaultFeedConnectionRecvBufferSize = 16 * 1024 * 1024;
        DefaultFeedConnectionRecvItemsCount = 20000;       // I don't know yet how much items needed
#endif

        DefaultMarketSendBufferSize = 8 * 1024 * 1024;     // why 16? don't know
        DefaultMarketRecvBufferSize = 8 * 1024 * 1024;
        DefaultMarketSendItemsCount = 4 * 1024 * 1024;
        DefaultMarketRecvItemsCount = 4 * 1024 * 1024;

        MarketDataMaxSymbolsCount = 2600;
        MarketDataMaxSymbolsCountForts = 500;
        MarketDataMaxSessionsCount = 8;
        MarketDataMaxEntriesCount = 1024 * 2000;
            MaxSecurityDefinitionCount = 2600;
        HistoricalReplayMaxMessageRequestCount = 1024;
#ifdef TEST
        MDEntryQueueItemsCount = 100;
        MDEntryQueueItemsAddCount = 100;
#else
        MDEntryQueueItemsCount = 10000;
        MDEntryQueueItemsAddCount = 100;
#endif
    }
};





