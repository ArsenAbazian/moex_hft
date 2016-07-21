#pragma once

#include <cstdint>

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
};

int RobotSettings::SocketBuffersMaxCount = 256; // they are created only when needed
unsigned int RobotSettings::DefaultFeedConnectionSendBufferSize = 8 * 1024 * 1024;
unsigned int RobotSettings::DefaultFeedConnectionRecvBufferSize = 64 * 1024 * 1024;
unsigned int RobotSettings::DefaultFeedConnectionSendItemsCount = 20000;    // I think that we most will listen data - no to send
unsigned int RobotSettings::DefaultFeedConnectionRecvItemsCount = 200000;   // I don't know yet how much items needed


