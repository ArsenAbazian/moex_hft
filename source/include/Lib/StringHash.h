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

        // since symbols are only latin capital we can use only 6 bits
        // so totally it is 18 bits for 3 last letters
        // because first chars for most of symbols are the same and starts from RU000A0
        unsigned int data1 = ((data & 0x3f000000) >> 24);
        data1 |= ((data & 0x003f0000) >> 10);
        data1 |= ((data & 0x00003f00) << 4);
        return data1;
    }
};

#endif //HFT_ROBOT_STRINGHASH_H
