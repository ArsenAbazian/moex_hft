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
    static int SocketBuffersMaxCount = 3 * 2 + 2 * 11 * 2; // 2 * 3 Fix servers and 2 * 11 * 2 fast servers
};



