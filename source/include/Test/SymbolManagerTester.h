//
// Created by root on 30.12.16.
//

#ifndef HFT_ROBOT_HASHSTRINGTESTER_H
#define HFT_ROBOT_HASHSTRINGTESTER_H
#include "../Settings.h"

#ifdef TEST

#include <stdio.h>
#include "../Lib/StringHash.h"
#include "../MarketData/SymbolManager.h"

typedef struct _hashTextInfo {
    int         lenght;
    char        text[17] __attribute__((aligned(16)));
}hashTextInfo;

class SymbolManagerTester {

    hashTextInfo    *m_items;
    int             m_itemsCount;
    int             *m_hashCount;
    int            *m_busy;

    SymbolManager   *m_manager;

    void            LoadItems() {
        const char *fileName = "/home/arsen/Documents/hft_robot/hft/test/symbols";
        FILE *fp = fopen(fileName, "rt");

        this->m_itemsCount = 0;
        while(!feof(fp)) {
            char symb = fgetc(fp);
            if(symb == 0xa)
                this->m_itemsCount++;
        }
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
                    if(index == this->m_itemsCount)
                        break;
                }
                else symbol++;
             }
        }
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
            this->m_hashCount[hash] ++;
        }
        int maxHashCollisionCount = 0;
        for(int i = 0; i < StringHash::MaxHashValue; i++) {
            if(this->m_hashCount[i] > maxHashCollisionCount)
                maxHashCollisionCount = this->m_hashCount[i];
            //printf("hash collision count for %d = %d\n", i, m_hashCount[i]);
        }

        //printf("SMB max collision count = %d\n", maxHashCollisionCount);
        if(maxHashCollisionCount > 8)
            throw; // it should be 8
    }

    void TestAddAllSymbols() {
        this->ClearBusy();
        this->m_manager->Clear();

        bool wasNewlyAdded = false;
        int dublicateItems = 0;
        int maxCollisionCount = 0;
        for(int i = 0; i < this->m_itemsCount; i++) {
            unsigned int hash = StringHash::GetHash(this->m_items[i].text, this->m_items[i].lenght);
            int poolBefore = this->m_manager->m_pool->CalcPoolCount();
            int bucketCountBefore = this->m_manager->CalcBucketCollisitonCount(hash);

            if(bucketCountBefore > this->m_hashCount[hash])
                throw;

            printf("%d  adding symbol %s with hash %d\n", i, DebugInfoManager::Default->GetString(this->m_items[i].text, this->m_items[i].lenght, 0), hash);
            printf("pool count before = %d  bucket count before = %d\n", poolBefore, bucketCountBefore);

            int index = this->m_manager->GetSymbolIndex(this->m_items[i].text, this->m_items[i].lenght, &wasNewlyAdded);

            int poolAfter =this->m_manager->m_pool->CalcPoolCount();
            int bucketCountAfter = this->m_manager->CalcBucketCollisitonCount(hash);
            if(bucketCountAfter > this->m_hashCount[hash])
                throw;

            printf("pool count after = %d  bucket count after = %d\n", poolAfter, bucketCountAfter);

            if(!wasNewlyAdded) {
                dublicateItems++;
                if(poolBefore != poolAfter)
                    throw;
            }
            else {
                this->m_busy[index]++;
                if(poolAfter != poolBefore - 1)
                    throw;
                if(index != i - dublicateItems)
                    throw;
            }
            if(this->m_busy[index] > 1)
                throw;
            if(bucketCountAfter > bucketCountBefore + 1)
                throw;
            if(bucketCountAfter > 8)
                throw;
            maxCollisionCount = maxCollisionCount < bucketCountAfter? bucketCountAfter: maxCollisionCount;
        }
        if(this->m_manager->SymbolCount() != this->m_itemsCount - dublicateItems) // sorry some m_symbols are dublicated
            throw;
        this->m_manager->Clear();
    }

    const char *AlignedString(const char *string) {
        _hashTextInfo *info = new _hashTextInfo;
        strcpy(info->text, string);
        return info->text;
    }

    void TestAddSymbols() {
        this->m_manager->Clear();

        bool wasNewlyAdded = false;
        if(this->m_manager->GetSymbolIndex(AlignedString("SYMBOL000001"), 12, &wasNewlyAdded) != 0)
            throw;
        if(!wasNewlyAdded)
            throw;
        if(this->m_manager->GetSymbolIndex(AlignedString("SYMBOL000001"), 12, &wasNewlyAdded) != 0)
            throw;
        if(wasNewlyAdded)
            throw;
        if(this->m_manager->SymbolCount() != 1)
            throw;
        if(this->m_manager->GetSymbolIndex(AlignedString("SYMBOL000002"), 12, &wasNewlyAdded) != 1)
            throw;
        if(!wasNewlyAdded)
            throw;
        if(this->m_manager->GetSymbolIndex(AlignedString("SYMBOL001002"), 12, &wasNewlyAdded) != 2)
            throw;
        if(!wasNewlyAdded)
            throw;
        if(this->m_manager->GetSymbolIndex(AlignedString("SYMB"), 4, &wasNewlyAdded) != 3)
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
        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity()) {
            delete m;
            throw;
        }

        m->GetSymbol(AlignedString("symbol1"), &isNewlyAdded);
        m->GetSymbol(AlignedString("symbol2"), &isNewlyAdded);

        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity() - 2)
            throw;

        m->Clear();
        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity()) {
            delete m;
            throw;
        }
    }

    void TestAddSymbols2() {
        this->m_manager->Clear();
        bool isNewlyAdded;
        SymbolInfo *s1 = this->m_manager->GetSymbol(AlignedString("smb1"), &isNewlyAdded);
        if(s1->m_index != 0)
            throw;
        SymbolInfo *s2 = this->m_manager->GetSymbol(AlignedString("smb2"), &isNewlyAdded);
        if(s2->m_index != 1)
            throw;
        s1 = this->m_manager->GetSymbol(AlignedString("smb1"), &isNewlyAdded);
        if(s1->m_index != 0)
            throw;
        s2 = this->m_manager->GetSymbol(AlignedString("smb2"), &isNewlyAdded);
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

#endif //TEST
#endif //HFT_ROBOT_HASHSTRINGTESTER_H
