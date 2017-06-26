//
// Created by root on 15.04.17.
//

#ifndef HFT_ROBOT_ORDEREDLISTMANAGER_H
#define HFT_ROBOT_ORDEREDLISTMANAGER_H

#include "../Lib/HrPointerList.h"
#include "../Fast/FastTypes.h"
#include "../Stopwatch.h"
#include <string.h>

typedef enum _SortType {
    stAscending,
    stDescending
} SortType;

template <template<typename DATA> class LIST, template<typename DATA> class POINTER, typename DATA>
class OrderedListManager {
public:
    __attribute_noinline__
    void DebugCheckCache() {
        if(this->m_list->Count() < 2)
            return;
        if(this->m_list->Start()->Value() == this->m_list->End()->Value())
            return;
        bool mirrored = this->m_list->Start()->Value() < this->m_list->End()->Value();
        POINTER<DATA> *node = this->m_list->Start();
        while(true) {
            if(this->m_cache[this->CalcCacheIndex(node->Value(), this->m_sortType == SortType::stAscending)] == 0)
                throw;
            if(node == this->m_list->End())
                break;
            node = node->Next();
        }
    }
    inline void OnPointerRemove(POINTER<DATA> *ptr) {
        Decimal *price = &(ptr->Data()->MDEntryPx);
        INT64 cacheIndex = this->CalcCacheIndex(price, this->m_sortType == SortType::stAscending);
        POINTER<DATA> *prev = ptr->Prev();
        POINTER<DATA> *last = this->m_cache[cacheIndex];
        if(last != ptr)
            return;
        bool updateCacheByPrev = ptr->Value() == prev->Value();
        this->m_cache[cacheIndex] = (POINTER<DATA> *) ((0 - (UINT64)updateCacheByPrev) & (UINT64)prev);
    }
    inline void ClearPointers() {
        memset(this->m_cache, 0, sizeof(POINTER<DATA>*) * this->m_cacheSize);
    }
private:
    static const int      m_cacheSize = 200000;
public:
    LIST<DATA>           *m_list;
    POINTER<DATA>        **m_cache;
    INT64                m_cacheStart;
    INT64                m_minPriceIncrement;
    int                  m_precision;
    unsigned int         g_seed;
    int                  m_LevelIndex = 0;
    int                  m_debugLevel;
    int                  m_seekCount;
    SortType             m_sortType;


    OrderedListManager(LIST<DATA> *list, SortType type) :
            m_debugLevel(0),
            g_seed(0),
            m_LevelIndex(0),
            m_list(0),
            m_seekCount(0),
            m_cache(0),
            m_cacheStart(0),
            m_precision(0),
            m_minPriceIncrement(0),
            m_sortType(type)
    {
        this->m_list = list;
        int additionalItems = 17;
        this->m_cache = new POINTER<DATA>*[this->m_cacheSize + additionalItems];
        memset(this->m_cache, 0, sizeof(POINTER<DATA>*) * this->m_cacheSize + additionalItems);
    }

    inline void MinPriceIncrement(INT64 value) { this->m_minPriceIncrement = value; }
    inline void Precision(int value) { this->m_precision = value; }

    __attribute_noinline__
    INT64 CalcCacheStartValue(INT64 value) {
        INT64 percent = (INT64)(0.40 * this->m_cacheSize);
        INT64 delta = this->m_minPriceIncrement * percent;
        return value - delta;
    }
    inline INT64 MinPrice() const { return this->m_cacheStart; }
    inline INT64 MaxPrice() const { return this->m_cacheStart + this->m_minPriceIncrement * this->m_cacheSize; }
    inline INT64 CalcValue(Decimal *price) {
        return price->Mantissa * price->CalcPowOf10(this->m_precision + price->Exponent);
    }
    inline INT64 CalcCacheIndex(Decimal *price) {
        INT64 value = price->Mantissa * price->CalcPowOf10(this->m_precision + price->Exponent); // correct cents
        if(this->m_cacheStart == 0)
            this->m_cacheStart = this->CalcCacheStartValue(value);
        return (value - this->m_cacheStart) / this->m_minPriceIncrement;
    }
    inline INT64 CalcCacheIndex(Decimal *price, bool ascending) {
        INT64 value = price->Mantissa * price->CalcPowOf10(this->m_precision + price->Exponent); // correct cents
        return this->CalcCacheIndex(value, ascending);
    }
    inline INT64 CalcCacheIndex(INT64 value, bool ascending) {
        INT64 res = CalcCacheIndex(value);
        INT64 res2 = this->m_cacheSize - res - 1;
        return ((((UINT64)0) - ascending) & res2) | ((((UINT64)ascending) - 1) & res);
    }
    inline INT64 CalcCacheIndex(INT64 value) {
        if(this->m_cacheStart == 0)
            this->m_cacheStart = this->CalcCacheStartValue(value);
        return (value - this->m_cacheStart) / this->m_minPriceIncrement;
    }
    inline INT64 CalcCacheIndexMirrored(INT64 value) {
        INT64 res = CalcCacheIndex(value);
        res++;
        return this->m_cacheSize - res;
    }
    inline POINTER<DATA>* GetLastCachedItem(Decimal *price) {
        INT64 cacheIndex = CalcCacheIndex(price);
        if(((UINT64)cacheIndex) >= this->m_cacheSize)
            return 0;
        return this->m_cache[cacheIndex];
    }
    inline bool IsItemCached(INT64 cacheIndex) {
        return ((UINT64)cacheIndex) < this->m_cacheSize && this->m_cache[cacheIndex] != 0;
    }
    inline INT64 FindNextItem(INT64 cacheIndex) {
        int i = cacheIndex + 1;
        for(; i < this->m_cacheSize - 8;) {
            __builtin_prefetch(this->m_cache + i + 8, 0, _MM_HINT_T0);
            for(int j = 0; j < 8; j++, i++) {
                if(this->m_cache[i] != 0)
                    return i;
            }
        }
        for(;i < this->m_cacheSize; i++) {
            if(this->m_cache[i] != 0)
                return i;
        }
        return -1;
    }
    inline POINTER<DATA>* InsertDescending(Decimal *price) {
        INT64 value = this->CalcValue(price);
        INT64 cacheIndex = this->CalcCacheIndex(value);
        POINTER<DATA> *newNode;
        if(this->m_list->Count() == 0)
            newNode = this->m_list->Add();
        else if(value > this->m_list->Start()->Value())
            newNode = this->m_list->InsertFirst();
        else {
            INT64 insertAfterIndex = cacheIndex;
            if(!this->IsItemCached(cacheIndex))
                insertAfterIndex = this->FindNextItem(cacheIndex);
            POINTER<DATA> *node = this->m_cache[insertAfterIndex];
            newNode = this->m_list->InsertAfter(node);
        }
        newNode->Value(value);
        this->m_cache[cacheIndex] = newNode;
        //this->DebugCheckCache();
        return newNode;
    }
    inline POINTER<DATA>* InsertAscending(Decimal *price) {
        INT64 value = this->CalcValue(price);
        INT64 cacheIndex = this->CalcCacheIndexMirrored(value);
        POINTER<DATA> *newNode;
        if(this->m_list->Count() == 0)
            newNode = this->m_list->Add();
        else if(value < this->m_list->Start()->Value())
            newNode = this->m_list->InsertFirst();
        else {
            INT64 insertAfterIndex = cacheIndex;
            if(!this->IsItemCached(cacheIndex))
                insertAfterIndex = this->FindNextItem(cacheIndex);
            POINTER<DATA> *node = this->m_cache[insertAfterIndex];
            newNode = this->m_list->InsertAfter(node);
        }
        newNode->Value(value);
        this->m_cache[cacheIndex] = newNode;
        //this->DebugCheckCache();
        return newNode;
    }
};

#endif //HFT_ROBOT_ORDEREDLISTMANAGER_H
