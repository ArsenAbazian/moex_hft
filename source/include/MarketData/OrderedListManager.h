//
// Created by root on 15.04.17.
//

#ifndef HFT_ROBOT_ORDEREDLISTMANAGER_H
#define HFT_ROBOT_ORDEREDLISTMANAGER_H

#include "../Lib/HrPointerList.h"
#include "../Fast/FastTypes.h"
#include "../Stopwatch.h"
#include <string.h>

typedef enum _ListType {
    ltSimple,
    ltSkipList
} ListType;

template <template<typename DATA> class LIST, template<typename DATA> class POINTER, typename DATA>
class OrderedListManager {
    void init_fast_srand() {
        g_seed = (Stopwatch::Default->ElapsedNanosecondsSlow() & 0xffffffff);
    }
public:
    inline bool IsLastGroupItem(POINTER<DATA> *ptr) {
        return ptr->Next() != 0 && ptr->Next()->Value() != ptr->Value();
    }
    inline void OnPointerRemove(POINTER<DATA> *ptr) {
        __builtin_prefetch(((char*)ptr->Next()), 0, _MM_HINT_T0);
        if(!this->IsLastGroupItem(ptr))
            return;
        Decimal *price = &(ptr->Data()->MDEntryPx);
        INT64 cacheIndex = this->CalcCacheIndex(price);
        if(!this->IsItemCached(cacheIndex))
            return;
        POINTER<DATA> *node = this->m_cache[cacheIndex];
        POINTER<DATA> *prev = node->Prev();
        this->m_cache[cacheIndex] = (POINTER<DATA> *)((0 - (node->Prev2() == 0)) & (UINT64)prev);
    }
    inline void ClearPointers() {
        memset(this->m_cache, 0, sizeof(POINTER<DATA>*) * this->m_cacheSize);
    }
private:
#pragma region InsertBeforeDescendingCore
    inline POINTER<DATA>* InsertBeforeDescending2(INT64 value, POINTER<DATA> *node) {
        while(node->Value() >= value) {
            node = node->Next2();
            this->m_seekCount++;
        }

        POINTER<DATA> *newNode = this->m_list->Insert(node);
        if(node->Prev2()->Value() == value) {
            this->m_LevelIndex = 1;
            return newNode;
        }
        this->m_LevelIndex = this->CalcLevel();
        this->m_list->Insert2(node->Prev2(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeDescending3(INT64 value, POINTER<DATA> *node) {
        while(node->Value() >= value) {
            node = node->Next3();
            this->m_seekCount++;
        }
        POINTER<DATA> *newNode = InsertBeforeDescending2(value, node->Prev3());
        if(this->m_LevelIndex >= 3)
            this->m_list->Insert3(node->Prev3(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeDescending4(INT64 value, POINTER<DATA> *node) {
        while(node->Value() >= value) {
            node = node->Next4();
            this->m_seekCount++;
        }
        POINTER<DATA> *newNode = InsertBeforeDescending3(value, node->Prev4());
        if(this->m_LevelIndex >= 4)
            this->m_list->Insert4(node->Prev4(), newNode, node);
        return newNode;
    }
    __attribute_noinline__
    POINTER<DATA>* OnInsertFirstSecondItemDescending(INT64 value, POINTER<DATA> *start) {
        if(this->m_list->Count() == 0)
            return this->m_list->Add();
        if(start->Value() < value) { // insert before
            POINTER<DATA> *newNode = this->m_list->Insert(start);
            newNode->AllConnect(start);
            return newNode;
        }
        else { // insert after
            POINTER<DATA> *newNode = this->m_list->Add();
            // just connect start with end
            start->AllConnect(newNode);
            return newNode;
        }
    }
    inline POINTER<DATA>* InsertBeforeDescending5(INT64 value, POINTER<DATA> *start, POINTER<DATA> *end) {
        // no items
        if (this->m_list->Count() < 2)
            return this->OnInsertFirstSecondItemDescending(value, start);

        POINTER<DATA> *node = start;
        POINTER<DATA> *newNode;

        // add before
        if(start->Value() < value) {
            newNode = this->m_list->Insert(start);
            newNode->Connect5(start->Next5());
            newNode->Connect4(start->Next4());
            newNode->Connect3(start->Next3());
            newNode->Connect2(start->Next2());
            start->AllZero();
            this->m_list->InsertAfterByLevel(this->CalcLevel(), newNode, start);
            return newNode;
        }
        if(end->Value() >= value) {
            newNode = this->m_list->Add();
            end->Prev5()->Connect5(newNode);
            end->Prev4()->Connect4(newNode);
            end->Prev3()->Connect3(newNode);
            end->Prev2()->Connect2(newNode);
            end->AllZero();
            if(end->Value() != end->Prev()->Value())
                this->m_list->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
            return newNode;
        }
        node = node->Next5();
        while(node->Value() >= value) {
            node = node->Next5();
            this->m_seekCount++;
        }

        newNode = InsertBeforeDescending4(value, node->Prev5());
        if(this->m_LevelIndex == 5)
            this->m_list->Insert5(node->Prev5(), newNode, node);
        return newNode;
    }
#pragma endregion InsertBeforeDescendingCore
#pragma region InsertBeforeAscendingCore
    inline POINTER<DATA>* InsertBeforeAscending2(INT64 value, POINTER<DATA> *node) {
        while(node->Value() <= value) {
            node = node->Next2();
            this->m_seekCount++;
        }
        POINTER<DATA> *newNode = this->m_list->Insert(node);
        if(node->Prev2()->Value() == value) {
            this->m_LevelIndex = 1;
            return newNode;
        }
        this->m_LevelIndex = this->CalcLevel();
        this->m_list->Insert2(node->Prev2(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeAscending3(INT64 value, POINTER<DATA> *node) {
        while(node->Value() <= value) {
            node = node->Next3();
            this->m_seekCount++;
        }
        POINTER<DATA> *newNode = InsertBeforeAscending2(value, node->Prev3());
        if(this->m_LevelIndex >= 3)
            this->m_list->Insert3(node->Prev3(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeAscending4(INT64 value, POINTER<DATA> *node) {
        while(node->Value() <= value) {
            node = node->Next4();
            this->m_seekCount++;
        }
        POINTER<DATA> *newNode = InsertBeforeAscending3(value, node->Prev4());
        if(this->m_LevelIndex >= 4)
            this->m_list->Insert4(node->Prev4(), newNode, node);
        return newNode;
    }
    __attribute_noinline__
    POINTER<DATA>* OnInsertFirstSecondItemAscending(INT64 value, POINTER<DATA> *start) {
        if(this->m_list->Count() == 0)
            return this->m_list->Add();
        if(start->Value() > value) { // insert before
            POINTER<DATA> *newNode = this->m_list->Insert(start);
            newNode->AllConnect(start);
            return newNode;
        }
        else { // insert after
            POINTER<DATA> *newNode = this->m_list->Add();
            // just connect start with end
            start->AllConnect(newNode);
            return newNode;
        }
    }
    inline POINTER<DATA>* InsertBeforeAscending5(INT64 value, POINTER<DATA> *start, POINTER<DATA> *end) {
        POINTER<DATA> *node = start;
        POINTER<DATA> *newNode;

        if(this->m_list->Count() < 2)
            return this->OnInsertFirstSecondItemAscending(value, start);
        // add before
        if(start->Value() > value) {
            newNode = this->m_list->Insert(start);
            newNode->Connect5(start->Next5());
            newNode->Connect4(start->Next4());
            newNode->Connect3(start->Next3());
            newNode->Connect2(start->Next2());
            start->AllZero();
            this->m_list->InsertAfterByLevel(CalcLevel(), newNode, start);
            return newNode;
        }
        if(end->Value() <= value) {
            // add after
            newNode = this->m_list->Add();
            end->Prev5()->Connect5(newNode);
            end->Prev4()->Connect4(newNode);
            end->Prev3()->Connect3(newNode);
            end->Prev2()->Connect2(newNode);
            end->AllZero();
            if(end->Value() != end->Prev()->Value())
                this->m_list->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
            return newNode;
        }
        node = node->Next5();
        while(node->Value() <= value) {
            node = node->Next5();
            this->m_seekCount++;

        }
        newNode = InsertBeforeAscending4(value, node->Prev5());
        if(this->m_LevelIndex == 5)
            this->m_list->Insert5(node->Prev5(), newNode, node);
        return newNode;
    }
#pragma endregion
    static const int      m_cacheSize = 100000;
public:
    LIST<DATA>           *m_list;
    POINTER<DATA>        **m_cache;
    INT64               m_cacheStart;
    INT64               m_minPriceIncrement;
    int                  m_precision;
    unsigned int         g_seed;
    int                  m_LevelIndex = 0;
    int                  m_debugLevel;
    int                  m_seekCount;
    int                  m_paddingBytes;

    // Compute a pseudorandom integer.
    // Output value in range [0, 32767]
    inline int fast_rand(void) {
        g_seed = (214013 * g_seed + 2531011);
        return (g_seed >> 16) & 0x7fff;
    }

    inline void SetDebugFastRandSeed(int seed) {
        this->g_seed = seed;
    }
    inline void SetDebugLevel(int level) {
        this->m_debugLevel = level;
    }

    OrderedListManager(LIST<DATA> *list) :
            m_debugLevel(0),
            g_seed(0),
            m_LevelIndex(0),
            m_list(0),
            m_seekCount(0),
            m_cache(0),
            m_cacheStart(0),
            m_precision(0),
            m_minPriceIncrement(0),
            m_paddingBytes(0)
    {
        this->m_list = list;
        this->init_fast_srand();
        this->m_cache = new POINTER<DATA>*[this->m_cacheSize];
        memset(this->m_cache, 0, sizeof(POINTER<DATA>*) * this->m_cacheSize);
    }

    inline void MinPriceIncrement(INT64 value) { this->m_minPriceIncrement = value; }
    inline void Precision(int value) { this->m_precision = value; }

    __attribute_noinline__
    INT64 CalcCacheStartValue(INT64 value) {
        INT64 percent25 = this->m_cacheSize / 4;
        INT64 delta = this->m_minPriceIncrement * percent25;
        return value > delta ? value - delta: 0;
    }
    inline INT64 CalcValue(Decimal *price) {
        return price->Mantissa * price->CalcPowOf10(this->m_precision + price->Exponent);
    }
    inline INT64 CalcCacheIndex(Decimal *price) {
        INT64 value = price->Mantissa * price->CalcPowOf10(this->m_precision + price->Exponent); // correct cents
        if(this->m_cacheStart == 0)
            this->m_cacheStart = this->CalcCacheStartValue(value);
        return (value - this->m_cacheStart) / this->m_minPriceIncrement;
    }

    inline POINTER<DATA>* GetLastCachedItem(Decimal *price) {
        INT64 cacheIndex = CalcCacheIndex(price);
        if(cacheIndex >= this->m_cacheSize || cacheIndex < 0)
            return 0;
        return this->m_cache[cacheIndex];
    }

    inline bool IsItemCached(INT64 cacheIndex) {
        return cacheIndex >= 0 && cacheIndex < this->m_cacheSize && this->m_cache[cacheIndex] != 0;
    }

    inline POINTER<DATA>* HrInsertBeforeDescending(Decimal *price) {
        INT64 cacheIndex = this->CalcCacheIndex(price);
        INT64 val = this->CalcValue(price);
        if(this->IsItemCached(cacheIndex)) {
            POINTER<DATA> *node = this->m_cache[cacheIndex];
            if(node != this->m_list->Start() && node != this->m_list->End()) {
                POINTER<DATA> *newNode = this->m_list->InsertAfter(node);
                this->m_cache[cacheIndex] = newNode;
                newNode->Value(val);
                return newNode;
            }
        }
        this->m_LevelIndex = 0;
        this->m_seekCount = 0;
        POINTER<DATA> *ptr = this->InsertBeforeDescending5(val, this->m_list->Start(), this->m_list->End());
        ptr->Value(val);
        if(cacheIndex >= 0 && cacheIndex < this->m_cacheSize)
            this->m_cache[cacheIndex] = ptr;
        return ptr;
    }

    inline POINTER<DATA>* HrInsertBeforeAscending(Decimal *price) {
        INT64 cacheIndex = this->CalcCacheIndex(price);
        INT64 val = this->CalcValue(price);
        if(this->IsItemCached(cacheIndex)) {
            POINTER<DATA> *node = this->m_cache[cacheIndex];
            if(node != this->m_list->Start() && node != this->m_list->End()) {
                POINTER<DATA> *newNode = this->m_list->InsertAfter(node);
                this->m_cache[cacheIndex] = newNode;
                newNode->Value(val);
                return newNode;
            }
        }

        this->m_LevelIndex = 0;
        this->m_seekCount = 0;
        POINTER<DATA> *ptr = this->InsertBeforeAscending5(val, this->m_list->Start(), this->m_list->End());
        ptr->Value(val);
        if(cacheIndex >= 0 && cacheIndex < this->m_cacheSize)
            this->m_cache[cacheIndex] = ptr;
        return ptr;
    }

    inline int CalcLevel() {
        const int level3P = 32767 >> 1;
        const int level4P = 32767 - (32767 >> 2);
        const int level5P = 32767 - (32767 >> 3);
#ifdef TEST
        if (this->m_debugLevel != 0) {
            int res = this->m_debugLevel;
            this->m_debugLevel = 0;
            return res;
        }
#endif
        int p = fast_rand();
        if(p < level3P)
            return 2;
        if(p < level4P)
            return 3;
        if(p < level5P)
            return 4;
        return 5;
    }
};

#endif //HFT_ROBOT_ORDEREDLISTMANAGER_H
