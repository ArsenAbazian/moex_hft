//
// Created by root on 26.03.17.
//

#ifndef HFT_ROBOT_PERFORMANCEPROFILERITEM_H
#define HFT_ROBOT_PERFORMANCEPROFILERITEM_H

#include "../Settings.h"

#ifdef __MACH__
typedef time_t __time_t;
typedef long int __syscall_slong_t;
#endif

class PerformanceProfilerItem {
public:
    PerformanceProfilerItem    *m_items[64];
    int                         m_itemsCount;

    int                         m_id;
    int                         m_count;
    __time_t                    m_secondsStart;
    __syscall_slong_t           m_nanoSecStart;
    __time_t                    m_seconds;
    __syscall_slong_t           m_nanoSec;

    void AddChild(PerformanceProfilerItem *item) {
        this->m_items[this->m_itemsCount] = item;
        this->m_itemsCount++;
    }
};

#endif //HFT_ROBOT_PERFORMANCEPROFILERITEM_H
