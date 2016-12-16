#pragma once

#include <cstdint>

#define ROBOT_WORK_ANYWAY

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
    static int SocketBuffersMaxCount;
    static unsigned int DefaultFeedConnectionSendBufferSize;
    static unsigned int DefaultFeedConnectionRecvBufferSize;
    static unsigned int DefaultFeedConnectionSendItemsCount;
    static unsigned int DefaultFeedConnectionRecvItemsCount;
    static unsigned int DefaultMarketSendBufferSize;
    static unsigned int DefaultMarketRecvBufferSize;
    static unsigned int DefaultMarketSendItemsCount;
    static unsigned int DefaultMarketRecvItemsCount;
    static unsigned int DefaultFeedConnectionPacketCount;
    static int MarketDataMaxSymbolsCount;
    static int MarketDataMaxSessionsCount;
    static int MarketDataMaxEntriesCount;
};




