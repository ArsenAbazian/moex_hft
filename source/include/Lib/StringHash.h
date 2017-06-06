//
// Created by root on 31.12.16.
//

#ifndef HFT_ROBOT_STRINGHASH_H
#define HFT_ROBOT_STRINGHASH_H

#include "AutoAllocatePointerList.h"

class StringHash {
    
public:
    static const int MaxHashValue  = 0x0003ffff;
    static const int HashArrayItemsCount = (0x0003ffff + 1);
    inline static unsigned int GetHash(const char *str, int length) {
        unsigned int data = *((unsigned int*)(str + length - 4));
        data -= 0x30303030;

        // since m_symbols are only latin capital we can use only 6 bits
        // so totally it is 18 bits for 3 last letters
        // because first chars for most of m_symbols are the same and starts from RU000A0
        unsigned int data1 = ((data & 0x3f000000) >> 24);
        data1 |= ((data & 0x003f0000) >> 10);
        data1 |= ((data & 0x00003f00) << 4);
        return data1;
    }
    inline static unsigned int GetHash2(const char *str, int length) {
        unsigned int hash = 2166136261;

        if(length >= 10) {
            hash = (hash * 16777619) ^ str[0];
            hash = (hash * 16777619) ^ str[1];
            hash = (hash * 16777619) ^ str[2];
            hash = (hash * 16777619) ^ str[3];
            hash = (hash * 16777619) ^ str[4];
            hash = (hash * 16777619) ^ str[5];
            hash = (hash * 16777619) ^ str[6];
            hash = (hash * 16777619) ^ str[7];
            hash = (hash * 16777619) ^ str[8];
            hash = (hash * 16777619) ^ str[9];
            if(length == 12) {
                hash = (hash * 16777619) ^ str[10];
                hash = (hash * 16777619) ^ str[11];
            }
            if(length == 11) {
                hash = (hash * 16777619) ^ str[10];
            }
        }
        else {
            for(int i = 0; i < length; i++) {
                hash = (hash * 16777619) ^ str[i];
            }
        }
        hash &= 0x0003ffff;
        return hash;

        //unsigned int data = *((unsigned int*)(str + length - 4));
        //data -= 0x30303030;

        // since m_symbols are only latin capital we can use only 6 bits
        // so totally it is 18 bits for 3 last letters
        // because first chars for most of m_symbols are the same and starts from RU000A0
        //unsigned int data1 = ((data & 0x3f000000) >> 24);
        //data1 |= ((data & 0x003f0000) >> 10);
        //data1 |= ((data & 0x00003f00) << 4);
        //return data1;
    }
};

#endif //HFT_ROBOT_STRINGHASH_H
