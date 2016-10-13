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

template<typename TableItemClassName> class HashTable {
    char                                m_symbols[MAX_SYMBOLS_COUNT][4];
    char                                m_tradingSession[MAX_TRADING_SESSIONS_COUNT][10];
    int                                 m_symbolsCount;
    int                                 m_tradingSessionsCount;

    TableItemClassName*                    m_table[MAX_SYMBOLS_COUNT][MAX_TRADING_SESSIONS_COUNT];
    PointerList<TableItemClassName>*       m_usedItems;

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
                this->m_table[i][j] = new TableItemClassName();
            }
        };
        this->m_usedItems = new PointerList<TableItemClassName>(MAX_SYMBOLS_COUNT * MAX_TRADING_SESSIONS_COUNT + 10);
    }
    ~HashTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                delete this->m_table[i][j];
            }
        };
    }

    inline int SymbolsCount() { return this->m_symbolsCount; }
    inline int TradingSessionsCount() { return this->m_tradingSessionsCount; }
    inline TableItemClassName* Item(int symbolIndex, int tradingSessionIndex) {
        return this->m_table[symbolIndex][tradingSessionIndex];
    }
    inline int UsedItemCount() { return this->m_usedItems->Count(); }

    inline TableItemClassName* GetItem(const char *symbol, const char *tradingSession) {
        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);
        return this->m_table[symbolIndex][tradingSessionIndex];
    }

    inline void Clear() {
        LinkedPointer<TableItemClassName> *node = this->m_usedItems->Start();
        while(true) {
            TableItemClassName *item = node->Data();
            item->Clear();
            if(node == this->m_usedItems->End())
                break;
            node = this->m_usedItems->Next(node);
        }
        this->m_usedItems->Clear();
    }

    inline LinkedPointer<TableItemClassName>* GetUsedItem(TableItemClassName *item) {
        LinkedPointer<TableItemClassName> *node = this->m_usedItems->Start();
        while(true) {
            if(node->Data() == item)
                return node;
            if(node == this->m_usedItems->End())
                return 0;
            node = this->m_usedItems->Next(node);
        }
        return 0;
    }

    inline void AddUsed(TableItemClassName *item) {
        LinkedPointer<TableItemClassName> *node = this->m_usedItems->Start();
        if(node->Data()->Used())
            return;
        this->m_usedItems->Add(item);
    }
    inline void RemoveUsed(TableItemClassName *item) {
        LinkedPointer<TableItemClassName> *listItem = GetUsedItem(item);
        if(listItem != 0) {
            this->m_usedItems->Remove(listItem);
            listItem->Data()->Used(false);
        }
    }
};

#endif //HFT_ROBOT_MARKETDATATABLE_H
