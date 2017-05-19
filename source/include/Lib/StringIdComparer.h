//
// Created by root on 21.09.16.
//

#ifndef HFT_ROBOT_MARKETDATATABLE_H
#define HFT_ROBOT_MARKETDATATABLE_H

#include "PointerList.h"
#include "../Settings.h"
#include <nmmintrin.h>
#include <string.h>

class StringIdComparer {
public:
    static inline bool IsEquals4(const char *s1, const char *s2) {
        UINT32 *u1 = (UINT32*)s1;
        UINT32 *u2 = (UINT32*)s2;
        return (*u1) == (*u2);
    }

    static inline bool IsEquals10(const char *s1, const char *s2) {
        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        if( (*u1) != (*u2) )
            return false;

        short *sh1 = (short*)(s1 + 8);
        short *sh2 = (short*)(s2 + 8);

        return (*sh1) == (*sh2);
    }

    static inline bool IsEquals12(const char *s1, const char *s2) {
        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        if( (*u1) != (*u2) )
            return false;

        UINT32 *sh1 = (UINT32*)(s1 + 8);
        UINT32 *sh2 = (UINT32*)(s2 + 8);

        return (*sh1) == (*sh2);
    }

    static inline bool Equal(const char *s1, const char *s2) {
        return Equal(s1, strlen(s1), s2, strlen(s2));
    }

    static inline bool EqualFast(const char *s1, int l1, const char *s2, int l2) {
        const int mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_BIT_MASK | _SIDD_NEGATIVE_POLARITY;
        return _mm_cmpestrc(*((__m128i*)s1), l1, *((__m128i*)s2), l2, mode) == 0;
    }

    static inline bool Equal(const char *s1, int l1, const char *s2, int l2) {
        if(l1 != l2)
            return false;

        if(l1 == 4)
            return IsEquals4(s1, s2);
        if(l1 == 10)
            return IsEquals10(s1, s2);
        if(l1 == 12)
            return IsEquals12(s1, s2);

        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        int len = l1;
        int count = len >> 3;

        if(len >= 8) {
            int i;
            for (i = 0; i < count; i ++) {
                if (*u1 != *u2)
                    return false;
                u1++;
                u2++;
            }
            len = len - (count << 3);
        }
        if(len == 0)
            return true;
        UINT32 *d1 = (UINT32*)u1;
        UINT32 *d2 = (UINT32*)u2;
        count = len >> 2;
        if(len >= 4) {
            int i;
            for (i = 0; i < count; i ++) {
                if (*d1 != *d2)
                    return false;
                d1++;
                d2++;
            }
            len = len - (count << 2);
        }
        if(len == 0)
            return true;

        short *sh1 = (short*)d1;
        short *sh2 = (short*)d2;
        count = len >> 1;
        if(len >= 2) {
            int i;
            for (i = 0; i < count; i ++) {
                if (*sh1 != *sh2)
                    return false;
                sh1++;
                sh2++;
            }
            len = len - (count << 1);
        }

        if(len == 0)
            return true;
        return s1[l1 - 1] == s2[l1 - 1];
    }

    static inline void CopyString(char *dst, const char *src, int count) {
        while(count >= 8) {
            *((UINT64*)dst) = *((UINT64*)src);
            count -= 8;
            dst += 8; src += 8;
        }
        if(count >= 4) {
            *((UINT32*)dst) = *((UINT32*)src);
            count -= 4;
            dst += 4; src += 4;
        }
        if(count >= 2) {
            *((unsigned short*)dst) = *((unsigned short*)src);
            count -= 2;
            dst += 2; src += 2;
        }
        if(count > 0)
            *dst = *src;
    }
};

class SizedArray {
public:

    const char *m_text;
    int m_length;

    SizedArray() :
            m_text(0),
            m_length(0) {
    }

    inline void Set(const char *text, int length) { this->m_text = text; this->m_length = length; }

    __attribute__((noinline))
    bool Equal(const char *text) {
        return StringIdComparer::Equal(this->m_text, this->m_length, text, strlen(text));
    }
    inline bool Equal(const char *text, int length) {
        return StringIdComparer::EqualFast(this->m_text, this->m_length, text, length);
    }
};

#endif //HFT_ROBOT_MARKETDATATABLE_H
