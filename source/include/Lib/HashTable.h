//
// Created by root on 21.09.16.
//

#ifndef HFT_ROBOT_MARKETDATATABLE_H
#define HFT_ROBOT_MARKETDATATABLE_H

#include "Lib/PointerList.h"
#include "Types.h"

#define MAX_SYMBOLS_COUNT               128
#define MAX_TRADING_SESSIONS_COUNT      128
#define MAX_TABLE_LIST_COUNT            256

template <typename T> class HashTableItem {
    PointerList<T>     *m_items;
    LinkedPointer<HashTableItem<T>>   *m_usedPointer;
public:
    HashTableItem() {
        this->m_items = new PointerList<T>(MAX_TABLE_LIST_COUNT);
        this->m_usedPointer = 0;
    }
    ~HashTableItem() {
        delete this->m_items;
    }

    inline PointerList<T>* Items() { return this->m_items; }
    inline LinkedPointer<HashTableItem<T>>* UsedListPointer(){ return this->m_usedPointer; }
    inline void UsedListPointer(LinkedPointer<HashTableItem<T>> *usedPointer) { this->m_usedPointer = usedPointer; }
    inline void RemoveFromUsed() {
        this->m_usedPointer->Owner()->Remove(this->m_usedPointer);
        this->m_usedPointer = 0;
    }
    inline void Clear() {
        LinkedPointer<T> *start = this->m_items->Start();
        LinkedPointer<T> *end = this->m_items->End();
        while(true) {
            start->Data()->Pointer->Owner()->Push(start->Data()->Pointer);
            if(start == end)
                break;
            start = start->Next();
        }
        this->m_items->Clear();
        this->RemoveFromUsed();
    }

    inline LinkedPointer<T>* Start() { return this->m_items->Start(); }
    inline LinkedPointer<T>* End() { return this->m_items->End(); }
    inline int Count() { return this->m_items->Count(); }
    inline void Remove(LinkedPointer<T> *item) {
        item->Data()->Pointer->Owner()->Push(item->Data()->Pointer);
        this->m_items->Remove(item);
        if(this->m_items->Count() == 0)
            this->RemoveFromUsed();
    }
};

template<typename T> class HashTable {
    char                m_symbols[MAX_SYMBOLS_COUNT][4];
    char                m_tradingSession[MAX_TRADING_SESSIONS_COUNT][10];
    int                 m_symbolsCount;
    int                 m_tradingSessionsCount;

    HashTableItem<T>*   m_table[MAX_SYMBOLS_COUNT][MAX_TRADING_SESSIONS_COUNT];
    PointerList< HashTableItem<T> >*     m_usedLists;

    inline bool IsSymbolEquals(const char *s1, const char *s2) {
        UINT32 *u1 = (UINT32*)s1;
        UINT32 *u2 = (UINT32*)s2;
        return (*u1) == (*u2);
    }

    inline bool IsTradingSessionEquals(const char *s1, const char *s2) {
        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        if( (*u1) != (*u2) )
            return false;

        short *sh1 = (short*)(s1 + 8);
        short *sh2 = (short*)(s2 + 8);

        return (*sh1) == (*sh2);
    }

public:
    inline int GetSymbolIndex(const char *symbol) {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            if(this->IsSymbolEquals(symbol, this->m_symbols[i]))
                return i;
        }
        *((UINT32*)this->m_symbols[this->m_symbolsCount]) = *((UINT32*)symbol);
        this->m_symbolsCount++;
        return this->m_symbolsCount - 1;
    }
    inline int GetTradingSessionIdIndex(const char *tradingSessionId) {
        for(int i = 0; i < this->m_tradingSessionsCount; i++) {
            if(this->IsTradingSessionEquals(tradingSessionId, this->m_tradingSession[i]))
                return i;
        }
        *((UINT64*)this->m_tradingSession[this->m_tradingSessionsCount]) = *((UINT64*)tradingSessionId);
        *((short*)(this->m_tradingSession[this->m_tradingSessionsCount] + 8)) = *((short*)(tradingSessionId + 8));
        this->m_tradingSessionsCount++;
        return this->m_tradingSessionsCount - 1;
    }

    HashTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                this->m_table[i][j] = new HashTableItem<T>();
            }
        }
        this->m_usedLists = new PointerList<HashTableItem<T>>(MAX_SYMBOLS_COUNT * MAX_TRADING_SESSIONS_COUNT + 10);
    }
    ~HashTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                delete this->m_table[i][j];
            }
        }
    }

    inline int SymbolsCount() { return this->m_symbolsCount; }
    inline int TradingSessionsCount() { return this->m_tradingSessionsCount; }
    inline HashTableItem<T>* Item(int symbolIndex, int tradingSessionIndex) {
        return this->m_table[symbolIndex][tradingSessionIndex];
    }
    inline int UsedItemCount() { return this->m_usedLists->Count(); }

    inline HashTableItem<T>* GetItem(const char *symbol, const char *tradingSession) {
        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);
        return this->m_table[symbolIndex][tradingSessionIndex];
    }

    inline HashTableItem<T>* Add(const char *symbol, const char *tradingSession, T *data) {
        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);

        HashTableItem<T> *item = this->m_table[symbolIndex][tradingSessionIndex];
        item->Items()->Add(data);

        if(item->Items()->Count() == 1) {
            item->UsedListPointer(this->m_usedLists->Add(item));
        }
        return item;
    }

    inline HashTableItem<T>* Add(const char *symbol, const char *tradingSession, T **data, int count) {
        T **item = data;

        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);

        HashTableItem<T> *mditem = this->m_table[symbolIndex][tradingSessionIndex];

        for(int i = 0; i < count; i++, item++) {
            mditem->Items()->Add(*item);
        }
        if(mditem->Items()->Count() == count) {
            mditem->UsedListPointer(this->m_usedLists->Add(mditem));
        }
        return mditem;
    }

    inline void Clear() {
        LinkedPointer<HashTableItem<T>> *node = this->m_usedLists->Start();
        while(true) {
            HashTableItem<T> *list = (HashTableItem<T>*)node->Data();
            list->Clear();
            if(node == this->m_usedLists->End())
                break;
            node = this->m_usedLists->Next(node);
        }
        this->m_usedLists->Clear();
    }
};

#endif //HFT_ROBOT_MARKETDATATABLE_H
