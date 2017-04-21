//
// Created by root on 22.04.17.
//

#ifndef HFT_ROBOT_HASHTABLETESTER_H
#define HFT_ROBOT_HASHTABLETESTER_H

#include "../Settings.h"
#ifdef TEST
#include "../Lib/HashTable.h"
#include <string.h>
#include <stdio.h>

class HashTableTester {
public:

    void TestCalcHashString() {
        HashTable *h = new HashTable();
        char buf[10];
        for(int i = 0; i < 10000000; i++) {
            sprintf(buf, "%d", i);
            UINT64 hash = h->CalcHash(buf, strlen(buf));
            if(hash != (i % 1000000))
                throw;
        }

        delete h;
    }
    void Test() {
        TestCalcHashString();
    }
};

#endif

#endif //HFT_ROBOT_HASHTABLETESTER_H
