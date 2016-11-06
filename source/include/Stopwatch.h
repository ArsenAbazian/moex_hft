//
// Created by root on 26.07.16.
//

#ifndef HFT_ROBOT_STOPWATCH_H
#define HFT_ROBOT_STOPWATCH_H

#include <time.h>
#include <memory.h>

class Stopwatch {
    struct timespec *m_specStart[10];
    struct timespec *m_specEnd;
    bool            m_enabled[10];
public:
    Stopwatch() {
        for(int i = 0; i < 10; i++) {
            this->m_specStart[i] = new struct timespec;
            bzero(this->m_specStart[i], sizeof(struct timespec));
            this->m_enabled[i] = false;
        }
        this->m_specEnd = new struct timespec;
        bzero(this->m_specEnd, sizeof(struct timespec));
    }
    ~Stopwatch() {
        for(int i = 0; i < 10; i++)
            delete this->m_specStart[i];
        delete this->m_specEnd;
    }
    inline void Start(int index) {
        clock_gettime(CLOCK_REALTIME, this->m_specStart[index]);
        this->m_enabled[index] = true;
    }
    inline void Start() {
        clock_gettime(CLOCK_REALTIME, this->m_specStart[0]);
        this->m_enabled[0] = true;
    }
    inline void Activate(int index) {
        if(this->Active(index))
            return;
        this->Start(index);
    }
    inline void Activate() {
        if(this->Active())
            return;
        this->Start();
    }
    inline void Stop(int index) {
        this->m_enabled[index] = false;
    }
    inline void Stop() {
        this->m_enabled[0] = false;
    }
    inline time_t ElapsedMilliseconds() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  (this->m_specEnd->tv_nsec - (*(this->m_specStart))->tv_nsec) * 1000000;
    }
    inline time_t ElapsedMicroseconds() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  (this->m_specEnd->tv_nsec - (*(this->m_specStart))->tv_nsec) * 1000;
    }
    inline time_t ElapsedSeconds() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  this->m_specEnd->tv_sec - (*(this->m_specStart))->tv_sec;
    }
    inline time_t ElapsedMilliseconds(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  (this->m_specEnd->tv_nsec - this->m_specStart[index]->tv_nsec) * 1000000;
    }
    inline time_t ElapsedMicroseconds(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  (this->m_specEnd->tv_nsec - this->m_specStart[index]->tv_nsec) * 1000;
    }
    inline time_t ElapsedSeconds(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return  this->m_specEnd->tv_sec - this->m_specStart[index]->tv_sec;
    }
    inline time_t NowSeconds() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME, this->m_specEnd);
        return this->m_specEnd->tv_sec;
    }
    inline bool Active(int index) { return this->m_enabled[index]; }
    inline bool Active() { return this->m_enabled[0]; }
};

class DefaultStopwatch {
public:
    static Stopwatch *Default;

};

#endif //HFT_ROBOT_STOPWATCH_H
