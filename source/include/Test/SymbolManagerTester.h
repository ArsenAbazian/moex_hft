//
// Created by root on 30.12.16.
//

#ifndef HFT_ROBOT_HASHSTRINGTESTER_H
#define HFT_ROBOT_HASHSTRINGTESTER_H

#include <stdio.h>
#include "../Lib/StringHash.h"
#include "../MarketData/SymbolManager.h"

typedef struct _hashTextInfo {
    char        text[17];
    int         lenght;
}hashTextInfo;

class SymbolManagerTester {

    hashTextInfo    *m_items;
    int             m_itemsCount;
    int             *m_hashCount;
    int            *m_busy;

    SymbolManager   *m_manager;

    void            LoadItems() {
        const char *fileName = "/home/arsen/Documents/hft_robot/hft/test/m_symbols";
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
    void ClearBusy() {
        for(int i = 0; i < this->m_itemsCount; i++)
            this->m_busy[i] = 0;
    }
public:
    SymbolManagerTester() {
        this->m_items = 0;
        this->m_itemsCount = 0;
        this->m_hashCount = new int[StringHash::HashArrayItemsCount];
        LoadItems();
        this->m_manager = new SymbolManager(this->m_itemsCount);
        this->m_busy = new int[this->m_itemsCount];
        this->ClearBusy();
        this->ClearHashCount();
    }
    ~SymbolManagerTester() {
        if(this->m_items != 0)
            delete this->m_items;
        this->m_items = 0;
        this->m_itemsCount = 0;
        delete this->m_hashCount;
        delete this->m_manager;
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
            //printf("i = %d\n", m_hashCount[i]);
        }

        printf("SMB max collision count = %d\n", maxHashCollisionCount);
    }

    void TestAddAllSymbols() {
        this->ClearBusy();
        this->m_manager->Clear();

        bool wasNewlyAdded = false;
        int dublicateItems = 0;
        for(int i = 0; i < this->m_itemsCount; i++) {
            int index = this->m_manager->GetSymbolIndex(this->m_items[i].text, this->m_items[i].lenght, &wasNewlyAdded);
            if(!wasNewlyAdded)
                dublicateItems++;
            else
                this->m_busy[index]++;

            if(this->m_busy[index] > 1)
                throw;
        }
        if(this->m_manager->SymbolCount() != this->m_itemsCount - dublicateItems) // sorry some m_symbols are dublicated
            throw;
    }

    void TestAddSymbols() {
        this->m_manager->Clear();

        bool wasNewlyAdded = false;
        if(this->m_manager->GetSymbolIndex("SYMBOL000001", 12, &wasNewlyAdded) != 0)
            throw;
        if(!wasNewlyAdded)
            throw;
        if(this->m_manager->GetSymbolIndex("SYMBOL000001", 12, &wasNewlyAdded) != 0)
            throw;
        if(wasNewlyAdded)
            throw;
        if(this->m_manager->SymbolCount() != 1)
            throw;
        if(this->m_manager->GetSymbolIndex("SYMBOL000002", 12, &wasNewlyAdded) != 1)
            throw;
        if(!wasNewlyAdded)
            throw;
        if(this->m_manager->GetSymbolIndex("SYMBOL001002", 12, &wasNewlyAdded) != 2)
            throw;
        if(!wasNewlyAdded)
            throw;
        if(this->m_manager->GetSymbolIndex("SYMB", 4, &wasNewlyAdded) != 3)
            throw;
        if(!wasNewlyAdded)
            throw;
    }

    void TestClear() {
        this->m_manager->Clear();
        TestAddAllSymbols();
        this->m_manager->Clear();
        if(this->m_manager->SymbolCount() != 0)
            throw;
        if(this->m_manager->m_pool->Count() != 0)
            throw;
        if(this->m_manager->m_pool->CalcPoolCount() != this->m_manager->m_pool->Capacity())
            throw;
        if(this->m_manager->m_capacity == 0)
            throw;
        if(this->m_manager->m_freeIndex != -1)
            throw;
        for(int i = 0; i < StringHash::MaxHashValue; i++)
            if(this->m_manager->m_bucketList[i] != 0)
                throw;
    }

    void TestClear2() {
        SymbolManager *m = new SymbolManager(40);
        bool isNewlyAdded = false;

        // IT IS IMPORTANT!!!! To preven PointerList from appending new items...
        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity())
            throw;

        m->GetSymbol("s1", 2, &isNewlyAdded);
        m->GetSymbol("s2", 2, &isNewlyAdded);

        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity() - 2)
            throw;

        m->Clear();
        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity())
            throw;
    }

    void TestAddSymbols2() {
        this->m_manager->Clear();
        bool isNewlyAdded;
        SymbolInfo *s1 = this->m_manager->GetSymbol("smb1", &isNewlyAdded);
        if(s1->m_index != 0)
            throw;
        SymbolInfo *s2 = this->m_manager->GetSymbol("smb2", &isNewlyAdded);
        if(s2->m_index != 1)
            throw;
        s1 = this->m_manager->GetSymbol("smb1", &isNewlyAdded);
        if(s1->m_index != 0)
            throw;
        s2 = this->m_manager->GetSymbol("smb2", &isNewlyAdded);
        if(s2->m_index != 1)
            throw;
    }

    void Test() {
        printf("SMB TestClear2");
        TestClear2();
        printf("SMB TestItemsLoaded\n");
        TestItemsLoaded();
        printf("SMB TestCollisionCount\n");
        TestCollisionCount();
        printf("SMB TestAddAllSymbols\n");
        TestAddAllSymbols();
        printf("SMB TestAddSymbols\n");
        TestAddSymbols();
        printf("SMB TestAddSymbols2\n");
        TestAddSymbols2();
        printf("SMB TestClear\n");
        TestClear();
    }
};

#endif //HFT_ROBOT_HASHSTRINGTESTER_H
