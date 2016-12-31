//
// Created by root on 30.12.16.
//

#ifndef HFT_ROBOT_HASHSTRINGTESTER_H
#define HFT_ROBOT_HASHSTRINGTESTER_H

#include <stdio.h>
#include "../Lib/StringHash.h"

typedef struct _hashTextInfo {
    char        text[17];
    int         lenght;
}hashTextInfo;

class HashStringTester {

    hashTextInfo    *m_items;
    int             m_itemsCount;
    int             *m_hashCount;

    void            LoadItems() {
        const char *fileName = "/home/arsen/Documents/hft_robot/hft/test/symbols";
        FILE *fp = fopen(fileName, "rt");

        this->m_itemsCount = 0;
        while(!feof(fp)) {
            char symb = fgetc(fp);
            if(symb == 0xa)
                this->m_itemsCount++;
        }
        this->m_itemsCount++;
        fseek(fp, 0, SEEK_SET);

        this->m_items = new hashTextInfo[this->m_itemsCount];
        int index = 0;
        int symbol = 0;
        while(!feof(fp)) {
             if(symbol == 0) {
                 fread(this->m_items[index].text, 1, 4, fp);
                 symbol = 4;
             }
             else {
                this->m_items[index].text[symbol] = fgetc(fp);
                if(this->m_items[index].text[symbol] == 0x0a) {
                    this->m_items[index].text[symbol] = '\0';
                    this->m_items[index].lenght = symbol;
                    symbol = 0;
                    index++;
                }
                else symbol++;
             }
        }
        this->m_items[index].text[symbol] = '\0';
        this->m_items[index].lenght = symbol;
        fclose(fp);
    }
public:
    HashStringTester() {
        this->m_items = 0;
        this->m_itemsCount = 0;
        this->m_hashCount = new int[StringHash::HashArrayItemsCount];
        LoadItems();
        this->ClearHashCount();
    }
    ~HashStringTester() {
        if(this->m_items != 0)
            delete this->m_items;
        this->m_items = 0;
        this->m_itemsCount = 0;
        delete this->m_hashCount;
    }

    void TestItemsLoaded() {
        if(this->m_itemsCount < 500)
            throw;
    }

    void ClearHashCount() {
        for(int i = 0; i < StringHash::HashArrayItemsCount; i++)
            m_hashCount[i] = 0;
    }

    void TestCollisionCount() {
        this->ClearHashCount();
        for(int i = 0; i < this->m_itemsCount; i++) {
            unsigned int hash = StringHash::GetHash(this->m_items[i].text, this->m_items[i].lenght);
            if(hash >= StringHash::MaxHashValue)
                throw;
            m_hashCount[hash] ++;
        }
        int maxHashCollisionCount = 0;
        for(int i = 0; i < StringHash::MaxHashValue; i++) {
            if(m_hashCount[i] > maxHashCollisionCount)
                maxHashCollisionCount = m_hashCount[i];
            printf("i = %d\n", m_hashCount[i]);
        }

        printf("max collision count = %d\n", maxHashCollisionCount);
    }

    void Test() {
        printf("HT TestItemsLoaded\n");
        TestItemsLoaded();
        printf("HT TestCollisionCount");
        TestCollisionCount();
    }
};

#endif //HFT_ROBOT_HASHSTRINGTESTER_H
