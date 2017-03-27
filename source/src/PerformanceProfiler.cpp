//
// Created by root on 26.03.17.
//

#include "PerformanceProfiler/PerformanceProfiler.h"

PerformanceProfiler::PerformanceProfiler() {
    this->m_time = new struct timespec;
#pragma region PerformanceProfiler_InitItems_GeneratedCode

#pragma endregion
}

PerformanceProfiler::~PerformanceProfiler() {
    delete this->m_time;
    for(int i = 0; i < this->m_itemsCount; i++)
        delete this->m_items[i];
    delete this->m_items;
}