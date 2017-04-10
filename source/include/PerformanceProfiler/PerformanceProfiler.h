//
// Created by root on 26.03.17.
//

#ifndef HFT_ROBOT_PERFORMANCEPROFILER_H
#define HFT_ROBOT_PERFORMANCEPROFILER_H

#include "../Stopwatch.h"
#include "PerformanceProfilerItem.h"

class PerformanceProfiler {
    const char                *m_fileName = "ppResults.xml";
    PerformanceProfilerItem   **m_items;
    int                       m_itemsCount;
    struct timespec           *m_time;
public:
    PerformanceProfiler();
    ~PerformanceProfiler();

    void SaveXml(const char *fileName);
    void SaveXml() { SaveXml(this->m_fileName); }

    inline void Start(int itemIndex) {
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_time);
        PerformanceProfilerItem *item = this->m_items[itemIndex];
        item->m_secondsStart = this->m_time->tv_sec;
        item->m_nanoSecStart = this->m_time->tv_nsec;
    }
    inline void End(int itemIndex) {
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_time);
        PerformanceProfilerItem *item = this->m_items[itemIndex];
        item->m_seconds = this->m_time->tv_sec - item->m_secondsStart;
        item->m_nanoSec = this->m_time->tv_nsec - item->m_nanoSecStart;
        item->m_count++;
    }
};


#endif //HFT_ROBOT_PERFORMANCEPROFILER_H
