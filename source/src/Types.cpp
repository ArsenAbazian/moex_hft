//
// Created by root on 22.07.16.
//
#include "Types.h"

int RobotSettings::SocketBuffersMaxCount = 256; // they are created only when needed
unsigned int RobotSettings::DefaultFeedConnectionSendBufferSize = 8 * 1024 * 1024;
unsigned int RobotSettings::DefaultFeedConnectionRecvBufferSize = 64 * 1024 * 1024;
unsigned int RobotSettings::DefaultFeedConnectionSendItemsCount = 20000;        // I think that we most will listen data - no to send
unsigned int RobotSettings::DefaultFeedConnectionRecvItemsCount = 200000;       // I don't know yet how much items needed

unsigned int RobotSettings::DefaultMarketSendBufferSize = 16 * 1024 * 1024;     // why 16? don't know
unsigned int RobotSettings::DefaultMarketRecvBufferSize = 16 * 1024 * 1024;
unsigned int RobotSettings::DefaultMarketSendItemsCount = 4 * 1024 * 1024;
unsigned int RobotSettings::DefaultMarketRecvItemsCount = 4 * 1024 * 1024;
