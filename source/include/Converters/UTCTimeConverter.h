#pragma once
#include "../Settings.h"
#include "ItoaConverter.h"
#include <sys/time.h>
#include <time.h>

typedef  struct _SYSTEMTIME  {
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
}SYSTEMTIME;

#define UTCTimeStampLength (4 + 2 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 3)

typedef char CharVector4[4];
typedef char CharVector2[2];
typedef char CharVector3[3];
class UTCTimeConverter
{
    ItoaConverter           *converter;
    static CharVector4      *years;
    static CharVector2      *hours;
    static CharVector3      *miliseconds;
    struct timeval          *tval;
    struct tm               *calendarTime;
    int                     currentMs;
    int                     paddingBytes;

    inline void Init(CharVector4 v, char p1, char p2, char p3, char p4) { v[0] = p1; v[1] = p2; v[2] = p3; v[3] = p4; }
    inline void Init(CharVector3 v, char p1, char p2, char p3) { v[0] = p1; v[1] = p2; v[2] = p3; }
    inline void Init(CharVector2 v, char p1, char p2) { v[0] = p1; v[1] = p2; }
    inline void Copy4(CharVector4 dst, CharVector4 src) { memcpy(dst, src, 4); }
    inline void Copy2(CharVector2 dst, CharVector2 src) { memcpy(dst, src, 2); }
    inline void Copy3(CharVector3 dst, CharVector3 src) { memcpy(dst, src, 3); }
public:
    UTCTimeConverter();
    ~UTCTimeConverter();

    void Initialize();
    inline int GetCurrentTimeString(char *buffer) {
        gettimeofday(this->tval, NULL);
        gmtime_r(&(this->tval->tv_sec), this->calendarTime);
        this->calendarTime->tm_year += 1900; //strange why?
        return ToString(buffer, this->calendarTime, tval->tv_usec / 1000);
    }
    inline struct tm* CalendarTime() { return this->calendarTime; }
    inline struct timeval* TimeVal() { return this->tval; }
    inline int ToString(char *buffer, struct tm *t, int ms) {
        *((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[t->tm_year]));
        buffer += 4;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[t->tm_mon]));
        buffer += 2;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[t->tm_mday]));
        buffer += 2;

        *((DWORD*)buffer) = 0x3a00002d; // -00:  reversed
        buffer++;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[t->tm_hour]));
        buffer += 3;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[t->tm_min]));
        buffer += 2;

        *((DWORD*)buffer) = 0x2e00003a; // :00.  reversed
        buffer++;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[t->tm_sec]));
        buffer += 3;

        char *v = (char*)(UTCTimeConverter::miliseconds[ms]);
        *((DWORD*)buffer) = *((DWORD*)v);

        //       y   m   d   -   h   :   m   :   s   .  ms
        //return 4 + 2 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 3;
        return UTCTimeStampLength;
    }
    inline int ToString(char *buffer, SYSTEMTIME *st) { 

        *((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[st->wYear]));
        buffer += 4;
        
        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wMonth]));
        buffer += 2;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wDay]));
        buffer += 2;

        *((DWORD*)buffer) = 0x3a00002d; // -00:  reversed
        buffer++;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wHour]));
        buffer += 3;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wMinute]));
        buffer += 2;

        *((DWORD*)buffer) = 0x2e00003a; // :00.  reversed
        buffer++;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wSecond]));
        buffer += 3;

        char *v = (char*)(UTCTimeConverter::miliseconds[st->wMilliseconds]);
        *((DWORD*)buffer) = *((DWORD*)v);

        //       y   m   d   -   h   :   m   :   s   .  ms
        //return 4 + 2 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 3;
        return UTCTimeStampLength;
    }

    inline int ToDateString(char *buffer, SYSTEMTIME *st) { 
        *((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[st->wYear]));
        buffer += 4;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wMonth]));
        buffer += 2;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wDay]));

        //     y   m   d 
        return 4 + 2 + 2;
    }

    inline int ToDateString(char *buffer, int year, int month, int day) {
        *((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[year]));
        buffer += 4;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[month]));
        buffer += 2;

        *((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[day]));

        //     y   m   d 
        return 4 + 2 + 2;
    }

    inline int FromString(char *buffer, SYSTEMTIME *st, char stopSymbol) {
        char *start = buffer;
        st->wYear = this->converter->From4SymbolUnsigned(buffer);
        buffer += 4;
        st->wMonth = this->converter->From2SymbolUnsigned(buffer);
        buffer += 2;
        st->wDay = this->converter->From2SymbolUnsigned(buffer);
        buffer += 3; 
        st->wHour = this->converter->From2SymbolUnsigned(buffer);
        buffer += 3;
        st->wMinute = this->converter->From2SymbolUnsigned(buffer);
        buffer += 3;
        st->wSecond = this->converter->From2SymbolUnsigned(buffer);
        buffer += 3;
        int outValue;
        int len = this->converter->FromStringFast(buffer, &outValue, stopSymbol);
        st->wMilliseconds = outValue;
        return buffer - start + len;
    }

    inline int FromDateString(char *buffer, SYSTEMTIME *st) { 
        st->wYear = this->converter->From4SymbolUnsigned(buffer);
        buffer += 4;
        st->wMonth = this->converter->From2SymbolUnsigned(buffer);
        buffer += 2;
        st->wDay = this->converter->From2SymbolUnsigned(buffer);
        return 8;
    }
};

