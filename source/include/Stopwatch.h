//
// Created by root on 26.07.16.
//

#ifndef HFT_ROBOT_STOPWATCH_H
#define HFT_ROBOT_STOPWATCH_H

#include <time.h>
#include <memory.h>

#ifndef CLOCK_REALTIME_COARSE
// yes, it will slow down a little, but at least it will compile
#pragma message "CLOCK_REALTIME_COARSE does not defined, using CLOCK_REALTIME"
#define CLOCK_REALTIME_COARSE CLOCK_REALTIME
#endif

class Stopwatch {
    struct timespec     *m_specStart[10];
    __syscall_slong_t   m_startMicroseconds[10];
    struct timespec     *m_specEnd;
    bool                m_enabled[10];
public:
    static Stopwatch            *Default;
    static __syscall_slong_t    ElapsedMicroseconds;

    Stopwatch() {
        for(int i = 0; i < 10; i++) {
            this->m_specStart[i] = new struct timespec;
            memset(this->m_specStart[i], 0, sizeof(struct timespec));
            this->m_enabled[i] = false;
            this->m_startMicroseconds[i] = 0;
        }
        this->m_specEnd = new struct timespec;
        memset(this->m_specEnd, 0, sizeof(struct timespec));
    }
    ~Stopwatch() {
        for(int i = 0; i < 10; i++)
            delete this->m_specStart[i];
        delete this->m_specEnd;
    }
    inline void GetElapsedMicrosecondsGlobal() {
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        __syscall_slong_t sec = this->m_specEnd->tv_sec;
        __syscall_slong_t res = (sec << 10) - (sec << 4) - (sec << 3);
        __syscall_slong_t res2 = (res << 10) - (res << 4) - (res << 3);
        Stopwatch::ElapsedMicroseconds = res2 + (this->m_specEnd->tv_nsec >> 10);
    }
    inline void GetElapsedMicrosecondsGlobalSlow() {
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        Stopwatch::ElapsedMicroseconds = this->m_specEnd->tv_sec * 1000000 + this->m_specEnd->tv_nsec / 1000;
    }
    inline void UpdateElapsedMicrosecondsGlobal(struct timespec *ts) {
        __syscall_slong_t sec = ts->tv_sec;
        __syscall_slong_t res = (sec << 10) - (sec << 4) - (sec << 3);
        __syscall_slong_t res2 = (res << 10) - (res << 4) - (res << 3);
        Stopwatch::ElapsedMicroseconds = res2 + (this->m_specEnd->tv_nsec >> 10);
    }
    inline void Start(int index, __syscall_slong_t startMicroseconds) {
        this->m_startMicroseconds[index] = startMicroseconds;
        this->m_enabled[index] = true;
    }
    inline void Start(int index) {
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_specStart[index]);
        UpdateElapsedMicrosecondsGlobal(this->m_specStart[index]);
        this->m_enabled[index] = true;
    }
    inline void StartFast(__syscall_slong_t startMicroseconds) {
        (*(this->m_startMicroseconds)) = startMicroseconds;
        this->m_enabled[0] = true;
    }
    inline void Start() {
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_specStart[0]);
        UpdateElapsedMicrosecondsGlobal(this->m_specStart[0]);
        this->m_enabled[0] = true;
    }
    inline void StartFast(int index) {
        this->Start(index, Stopwatch::ElapsedMicroseconds);
    }
    inline void StartFast() {
        this->StartFast(Stopwatch::ElapsedMicroseconds);
    }
    inline void ActivateFast(int index) {
        if(this->Active(index))
            return;
        this->StartFast(index);
    }
    inline void ActivateFast() {
        if(this->Active())
            return;
        this->StartFast();
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
    inline time_t ElapsedMillisecondsSlow() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return  (this->m_specEnd->tv_sec - (*(this->m_specStart))->tv_sec) * 1000 + (this->m_specEnd->tv_nsec - (*(this->m_specStart))->tv_nsec) / 1000000;
    }
    inline time_t ElapsedNanosecondsSlow() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return  (this->m_specEnd->tv_sec - (*(this->m_specStart))->tv_sec) * 1000000000 + (this->m_specEnd->tv_nsec - (*(this->m_specStart))->tv_nsec);
    }
    inline time_t ElapsedNanosecondsSlow(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return  (this->m_specEnd->tv_sec - this->m_specStart[index]->tv_sec) * 1000000000 + (this->m_specEnd->tv_nsec - this->m_specStart[index]->tv_nsec);
    }
    inline bool IsElapsedMillisecondsSlow(time_t ms) {
        if(!this->m_enabled[0])
            return false;
        return this->ElapsedMillisecondsSlow() > ms;
    }
    inline bool IsElapsedMillisecondsSlow(int index, time_t ms) {
        if(!this->m_enabled[index])
            return false;
        return this->ElapsedMillisecondsSlow(index) > ms;
    }
    inline time_t ElapsedMicrosecondsSlow() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return (this->m_specEnd->tv_sec - (*(this->m_specStart))->tv_sec) * 1000000 + (this->m_specEnd->tv_nsec - (*(this->m_specStart))->tv_nsec) / 1000;
    }
    inline time_t ElapsedSeconds() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return  this->m_specEnd->tv_sec - (*(this->m_specStart))->tv_sec;
    }
    inline __syscall_slong_t ElapsedMicrosecondsFast() {
        return Stopwatch::ElapsedMicroseconds - *(this->m_startMicroseconds);
    }
    inline __syscall_slong_t ElapsedMicrosecondsFast(int index) {
        return Stopwatch::ElapsedMicroseconds - this->m_startMicroseconds[index];
    }
    inline __syscall_slong_t ElapsedMillisecondsFast() {
        return (Stopwatch::ElapsedMicroseconds - *(this->m_startMicroseconds)) >> 10;
    }
    inline __syscall_slong_t ElapsedMillisecondsFast(int index) {
        return (Stopwatch::ElapsedMicroseconds - this->m_startMicroseconds[index]) >> 10;
    }
    inline bool IsTimeOutFast(int index, __syscall_slong_t microseconds) {
        if(!this->m_enabled[index])
            return false;
        return (Stopwatch::ElapsedMicroseconds - this->m_startMicroseconds[index]) > microseconds;
    }
    inline bool IsTimeOutFast(__syscall_slong_t microseconds) {
        if(!this->m_enabled[0])
            return false;
        return (Stopwatch::ElapsedMicroseconds - *(this->m_startMicroseconds)) > microseconds;
    }
    inline bool IsTimeOutSlow(int sec, __syscall_slong_t nsec) {
        if(!this->m_enabled[0])
            return false;
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        if(this->m_specEnd->tv_sec - (*(this->m_specStart))->tv_sec > sec)
            return true;
        return this->m_specEnd->tv_nsec - (*(this->m_specStart))->tv_nsec > nsec;
    }
    inline bool IsTimeOutSlow(int index, int sec, __syscall_slong_t nsec) {
        if(!this->m_enabled[index])
            return false;
        clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        if(this->m_specEnd->tv_sec - this->m_specStart[index]->tv_sec > sec)
            return true;
        return this->m_specEnd->tv_nsec - this->m_specStart[index]->tv_nsec > nsec;
    }
    inline time_t ElapsedMillisecondsSlow(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return (this->m_specEnd->tv_sec - this->m_specStart[index]->tv_sec) * 1000 + (this->m_specEnd->tv_nsec - this->m_specStart[index]->tv_nsec) / 1000000;
    }
    inline time_t ElapsedMicrosecondsSlow(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return (this->m_specEnd->tv_sec - this->m_specStart[index]->tv_sec) * 1000000 +  (this->m_specEnd->tv_nsec - this->m_specStart[index]->tv_nsec) / 1000;
    }
    inline time_t ElapsedSeconds(int index) {
        if(this->m_enabled[index])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return  this->m_specEnd->tv_sec - this->m_specStart[index]->tv_sec;
    }
    inline time_t NowSeconds() {
        if(this->m_enabled[0])
            clock_gettime(CLOCK_REALTIME_COARSE, this->m_specEnd);
        return this->m_specEnd->tv_sec;
    }
    inline bool Active(int index) { return this->m_enabled[index]; }
    inline bool Active() { return this->m_enabled[0]; }
    inline void Reset() {
        if(Active())
            this->Start();
    }
    inline void Reset(int index) {
        if(Active(index))
            this->Start(index);
    }
    inline void ResetFast() {
        if(Active()) {
            this->GetElapsedMicrosecondsGlobal();
            this->StartFast();
        }
    }
    inline void ResetFast(int index) {
        if(Active(index)) {
            this->GetElapsedMicrosecondsGlobal();
            this->StartFast(index);
        }
    }
};

#endif //HFT_ROBOT_STOPWATCH_H
