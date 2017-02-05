//
// Created by root on 05.02.17.
//
#include "StatisticInfo.h"

StatisticItemAllocator* DefaultStatisticItemAllocator::Default = new StatisticItemAllocator(10000, 1000);
