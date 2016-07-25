//
// Created by root on 26.07.16.
//

#ifndef HFT_ROBOT_STOPWATCH_H
#define HFT_ROBOT_STOPWATCH_H

#include <time.h>
#include <memory.h>

class Stopwatch {
    struct timespec *m_specStart;
    struct timespec *m_specEnd;
    bool            m_enabled;
public:
    Stopwatch() {
        this->m_specStart = new struct timespec;
        this->m_specEnd = new struct timespec;
        this->m_enabled = false;
        bzero(this->m_specStart, sizeof(struct timespec));
        bzero(this->m_specEnd, sizeof(struct timespec));
    }
    ~Stopwatch() {
        delete this->m_specStart;
        delete this->m_specEnd;
    }
    inline void Start() {
        clock_gettime(CLOCK_REALTIME, this->m_specStart);
        this->m_enabled = true;
    }
    inline void Stop() {
        clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        this->m_enabled = false;
    }
    inline time_t ElapsedMilliseconds() {
        if(this->m_enabled)
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  (this->m_specEnd->tv_nsec - this->m_specStart->tv_nsec) * 1000000;
    }
    inline time_t ElapsedMicroseconds() {
        if(this->m_enabled)
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  (this->m_specEnd->tv_nsec - this->m_specStart->tv_nsec) * 1000;
    }
    inline time_t ElapsedSeconds() {
        if(this->m_enabled)
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  this->m_specEnd->tv_sec - this->m_specStart->tv_sec;
    }
};

class DefaultStopwatch {
public:
    static Stopwatch *Default;

};

#endif //HFT_ROBOT_STOPWATCH_H
