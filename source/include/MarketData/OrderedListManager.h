//
// Created by root on 15.04.17.
//

#ifndef HFT_ROBOT_ORDEREDLISTMANAGER_H
#define HFT_ROBOT_ORDEREDLISTMANAGER_H

#include "../Lib/HrPointerList.h"
#include "../Fast/FastTypes.h"
#include "../Stopwatch.h"

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
    inline void OnPointerRemove(POINTER<DATA> *ptr) {
        Decimal *price = &(ptr->Data()->MDEntryPx);
        UINT64 cacheIndex = this->CalcCacheIndex(price);
        if(!this->IsItemCached(cacheIndex))
            return;
        POINTER<DATA> *prev = this->m_cache[cacheIndex]->Prev();
        this->m_cache[cacheIndex] = (POINTER<DATA> *)((0 - (prev->Prev2() == 0)) & (UINT64)prev);

        this->m_lastPtr2 = (POINTER<DATA>*)((0 - (ptr != this->m_lastPtr2)) & ((UINT64)this->m_lastPtr2));
        this->m_lastPtr3 = (POINTER<DATA>*)((0 - (ptr != this->m_lastPtr3)) & ((UINT64)this->m_lastPtr3));
        this->m_lastPtr4 = (POINTER<DATA>*)((0 - (ptr != this->m_lastPtr4)) & ((UINT64)this->m_lastPtr4));
        this->m_lastPtr5 = (POINTER<DATA>*)((0 - (ptr != this->m_lastPtr5)) & ((UINT64)this->m_lastPtr5));
    }
    inline void ClearPointers() {
        this->m_lastPtr2 = 0;
        this->m_lastPtr3 = 0;
        this->m_lastPtr4 = 0;
        this->m_lastPtr5 = 0;
    }
private:
#pragma region InsertBeforeDescendingCore
    inline POINTER<DATA>* InsertBeforeDescending2(double value, POINTER<DATA> *node) {
        if(this->m_lastPtr2 != 0 && this->m_lastPtr2->Value() < value && this->m_lastPtr2->Prev2()->Value() >= value)
            node = this->m_lastPtr2;
        else {
            while(node->Value() >= value) {
                node = node->Next2();
                this->m_seekCount++;
            }
            this->m_lastPtr2 = node;
        }
        bool isBeginOfNewValue = node->Prev()->Value() != value;
        POINTER<DATA> *newNode = this->m_list->Insert(node);
        if(!isBeginOfNewValue) {
            this->m_LevelIndex = 1;
            return newNode;
        }
        this->m_LevelIndex = this->CalcLevel();
        if(node->Prev3() != 0 || node->Next3() != 0)
            this->m_LevelIndex = 2;
        this->m_list->Insert2(node->Prev2(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeDescending3(double value, POINTER<DATA> *node) {
        if(this->m_lastPtr3 != 0 && this->m_lastPtr3->Value() < value && this->m_lastPtr3->Prev3()->Value() >= value) {
            node = this->m_lastPtr3;
        }
        else {
            while(node->Value() >= value) {
                node = node->Next3();
                this->m_seekCount++;
            }
            this->m_lastPtr3 = node;
        }
        POINTER<DATA> *newNode = InsertBeforeDescending2(value, node->Prev3());
        if(this->m_LevelIndex >= 3)
            this->m_list->Insert3(node->Prev3(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeDescending4(double value, POINTER<DATA> *node) {
        if(this->m_lastPtr4 != 0 && this->m_lastPtr4->Value() < value && this->m_lastPtr4->Prev4()->Value() >= value) {
            node = this->m_lastPtr4;
        }
        else {
            while(node->Value() >= value) {
                node = node->Next4();
                this->m_seekCount++;
            }
            this->m_lastPtr4 = node;
        }
        POINTER<DATA> *newNode = InsertBeforeDescending3(value, node->Prev4());
        if(this->m_LevelIndex >= 4)
            this->m_list->Insert4(node->Prev4(), newNode, node);
        return newNode;
    }
    __attribute_noinline__
    POINTER<DATA>* OnInsertFirstSecondItemDescending(double value, POINTER<DATA> *start) {
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
    inline POINTER<DATA>* InsertBeforeDescending5(double value, POINTER<DATA> *start, POINTER<DATA> *end) {
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
            this->OnPointerRemove(start);
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
            this->OnPointerRemove(end);
            if(end->Value() != end->Prev()->Value())
                this->m_list->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
            return newNode;
        }
        if(this->m_lastPtr5 != 0 && this->m_lastPtr5->Value() < value && this->m_lastPtr5->Prev5()->Value() >= value) {
            node = this->m_lastPtr5;
        }
        else {
            node = node->Next5();
            while(node->Value() >= value) {
                node = node->Next5();
                this->m_seekCount++;
            }
            this->m_lastPtr5 = node;
        }
        newNode = InsertBeforeDescending4(value, node->Prev5());
        if(this->m_LevelIndex == 5)
            this->m_list->Insert5(node->Prev5(), newNode, node);
        return newNode;
    }
#pragma endregion InsertBeforeDescendingCore
#pragma region InsertBeforeAscendingCore
    inline POINTER<DATA>* InsertBeforeAscending2(double value, POINTER<DATA> *node) {
        if(this->m_lastPtr2 != 0 && this->m_lastPtr2->Value() > value && this->m_lastPtr2->Prev2()->Value() <= value) {
            node = this->m_lastPtr2;
        }
        else {
            while(node->Value() <= value) {
                node = node->Next2();
                this->m_seekCount++;
            }
            this->m_lastPtr2 = node;
        }
        bool isBeginOfNewValue = node->Prev()->Value() != value;
        POINTER<DATA> *newNode = this->m_list->Insert(node);
        if(!isBeginOfNewValue) {
            this->m_LevelIndex = 1;
            return newNode;
        }
        this->m_LevelIndex = this->CalcLevel();
        if(node->Prev3() != 0 || node->Next3() != 0)
            this->m_LevelIndex = 2;
        this->m_list->Insert2(node->Prev2(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeAscending3(double value, POINTER<DATA> *node) {
        if(this->m_lastPtr3 != 0 && this->m_lastPtr3->Value() > value && this->m_lastPtr3->Prev3()->Value() <= value) {
            node = this->m_lastPtr3;
        }
        else {
            while(node->Value() <= value) {
                node = node->Next3();
                this->m_seekCount++;
            }
            this->m_lastPtr3 = node;
        }
        POINTER<DATA>* newNode = InsertBeforeAscending2(value, node->Prev3());
        if(this->m_LevelIndex >= 3)
            this->m_list->Insert3(node->Prev3(), newNode, node);
        return newNode;
    }
    inline POINTER<DATA>* InsertBeforeAscending4(double value, POINTER<DATA> *node) {
        if(this->m_lastPtr4 != 0 && this->m_lastPtr4->Value() > value && this->m_lastPtr4->Prev4()->Value() <= value) {
            node = this->m_lastPtr4;
        }
        else {
            while(node->Value() <= value) {
                node = node->Next4();
                this->m_seekCount++;
            }
            this->m_lastPtr4 = node;
        }
        POINTER<DATA>* newNode = InsertBeforeAscending3(value, node->Prev4());
        if(this->m_LevelIndex >= 4)
            this->m_list->Insert4(node->Prev4(), newNode, node);
        return newNode;
    }
    __attribute_noinline__
    POINTER<DATA>* OnInsertFirstSecondItemAscending(double value, POINTER<DATA> *start) {
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
    inline POINTER<DATA>* InsertBeforeAscending5(double value, POINTER<DATA> *start, POINTER<DATA> *end) {
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
            this->OnPointerRemove(start);
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
            this->OnPointerRemove(end);
            if(end->Value() != end->Prev()->Value())
                this->m_list->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
            return newNode;
        }
        if(this->m_lastPtr5 != 0 && this->m_lastPtr5->Value() > value && this->m_lastPtr5->Prev5()->Value() <= value) {
            node = this->m_lastPtr5;
        }
        else {
            node = node->Next5();
            while(node->Value() <= value) {
                node = node->Next5();
                this->m_seekCount++;

            }
            this->m_lastPtr5 = node;
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
    UINT64               m_cacheStart;
    POINTER<DATA>        *m_lastPtr2;
    POINTER<DATA>        *m_lastPtr3;
    POINTER<DATA>        *m_lastPtr4;
    POINTER<DATA>        *m_lastPtr5;
    unsigned int         g_seed;
    int                  m_LevelIndex = 0;
    int                  m_debugLevel;
    int                  m_seekCount;

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
            m_lastPtr2(0),
            m_lastPtr3(0),
            m_lastPtr4(0),
            m_lastPtr5(0),
            m_cache(0),
            m_cacheStart(0)
    {
        this->m_list = list;
        this->init_fast_srand();
        this->m_cache = new POINTER<DATA>*[this->m_cacheSize];
        memset(this->m_cacheSize, 0, sizeof(POINTER<DATA>*) * this->m_cacheSize);
    }

    inline UINT64 CalcCacheIndex(Decimal *price) {
        UINT64 value = price->Mantissa;

        if(price->Exponent > 0)
            value *= 100; // add cents 0 - 99
        else
            value *= price->CalcPowOf10(-price->Exponent); // correct cents

        if(this->m_cacheStart == 0)
            this->m_cacheStart = value - this->m_cacheSize / 4;
        return value - this->m_cacheStart;
    }

    inline POINTER<DATA>* GetLastCachedItem(Decimal *price) {
        UINT64 cacheIndex = CalcCacheIndex(price);
        if(cacheIndex >= this->m_cacheSize)
            return 0;
        return this->m_cache[cacheIndex];
    }

    inline bool IsItemCached(UINT64 cacheIndex) {
        return cacheIndex < this->m_cacheSize && this->m_cache[cacheIndex] == 0;
    }

    inline POINTER<DATA>* HrInsertBeforeDescending(Decimal *price) {
        UINT64 cacheIndex = this->CalcCacheIndex(price);
        if(this->IsItemCached(cacheIndex)) {
            POINTER<DATA> *newNode = this->m_list->Insert(this->m_cache[cacheIndex]->Next());
            this->m_cache[cacheIndex] = newNode;
        }

        this->m_LevelIndex = 0;
        this->m_seekCount = 0;
        POINTER<DATA> *ptr = this->InsertBeforeDescending5(price->Calculate(), this->m_list->Start(), this->m_list->End());
        ptr->Value(price->Value);
        return ptr;
    }

    inline POINTER<DATA>* HrInsertBeforeAscending(Decimal *price) {
        UINT64 cacheIndex = this->CalcCacheIndex(price);
        if(this->IsItemCached(cacheIndex)) {
            POINTER<DATA> *newNode = this->m_list->Insert(this->m_cache[cacheIndex]->Next());
            this->m_cache[cacheIndex] = newNode;
            return newNode;
        }

        this->m_LevelIndex = 0;
        this->m_seekCount = 0;
        POINTER<DATA> *ptr = this->InsertBeforeAscending5(price->Calculate(), this->m_list->Start(), this->m_list->End());
        ptr->Value(price->Value);
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
