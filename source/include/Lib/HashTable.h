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

class StringIdComparer {
public:
    static inline bool IsEquals4(const char *s1, const char *s2) {
        UINT32 *u1 = (UINT32*)s1;
        UINT32 *u2 = (UINT32*)s2;
        return (*u1) == (*u2);
    }

    static inline bool IsEquals10(const char *s1, const char *s2) {
        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        if( (*u1) != (*u2) )
            return false;

        short *sh1 = (short*)(s1 + 8);
        short *sh2 = (short*)(s2 + 8);

        return (*sh1) == (*sh2);
    }

    static inline bool IsEquals12(const char *s1, const char *s2) {
        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        if( (*u1) != (*u2) )
            return false;

        UINT32 *sh1 = (UINT32*)(s1 + 8);
        UINT32 *sh2 = (UINT32*)(s2 + 8);

        return (*sh1) == (*sh2);
    }

    static inline bool Equal(const char *s1, int l1, const char *s2, int l2) {
        if(l1 != l2)
            return false;

        if(l1 == 4)
            return IsEquals4(s1, s2);
        if(l1 == 10)
            return IsEquals10(s1, s2);
        if(l1 == 12)
            return IsEquals12(s1, s2);

        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        int len = l1;
        int count = len >> 3;

        if(len >= 8) {
            int i;
            for (i = 0; i < count; i ++) {
                if (*u1 != *u2)
                    return false;
                u1++;
                u2++;
            }
            len = len - (count << 3);
        }
        if(len == 0)
            return true;
        UINT32 *d1 = (UINT32*)u1;
        UINT32 *d2 = (UINT32*)u2;
        count = len >> 2;
        if(len >= 4) {
            int i;
            for (i = 0; i < count; i ++) {
                if (*d1 != *d2)
                    return false;
                d1++;
                d2++;
            }
            len = len - (count << 2);
        }
        if(len == 0)
            return true;

        short *sh1 = (short*)d1;
        short *sh2 = (short*)d2;
        count = len >> 1;
        if(len >= 2) {
            int i;
            for (i = 0; i < count; i ++) {
                if (*sh1 != *sh2)
                    return false;
                sh1++;
                sh2++;
            }
            len = len - (count << 1);
        }

        if(len == 0)
            return true;
        return s1[l1 - 1] == s2[l1 - 1];
    }
};

class SizedArray {
public:

    const char *m_text;
    int m_length;

    SizedArray() {
        this->m_length = 0;
    }

    inline bool Equal(const char *text) {
        return StringIdComparer::Equal(this->m_text, this->m_length, text, strlen(text));
    }
    inline bool Equal(const char *text, int length) {
        return StringIdComparer::Equal(this->m_text, this->m_length, text, length);
    }
};

template<typename TableItemClassName> class HashTable {

    SizedArray*                         m_symbols[MAX_SYMBOLS_COUNT];
    SizedArray*                         m_tradingSession[MAX_TRADING_SESSIONS_COUNT];
    int                                 m_symbolsCount;
    int                                 m_tradingSessionsCount;

    TableItemClassName*                    m_table[MAX_SYMBOLS_COUNT][MAX_TRADING_SESSIONS_COUNT];
    PointerList<TableItemClassName>*       m_usedItems;

public:
    inline int GetSymbolIndex(const char *symbol, int length) {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            if(this->m_symbols[i]->Equal(symbol, length))
                return i;
        }
        this->m_symbols[this->m_symbolsCount]->m_text = symbol;
        this->m_symbols[this->m_symbolsCount]->m_length = length;
        this->m_symbolsCount++;
        return this->m_symbolsCount - 1;
    }
    inline int GetTradingSessionIdIndex(const char *tradingSessionId, int length) {
        for(int i = 0; i < this->m_tradingSessionsCount; i++) {
            if(this->m_tradingSession[i]->Equal(tradingSessionId, length))
                return i;
        }
        this->m_tradingSession[this->m_tradingSessionsCount]->m_text = tradingSessionId;
        this->m_tradingSession[this->m_tradingSessionsCount]->m_length = length;
        this->m_tradingSessionsCount++;
        return this->m_tradingSessionsCount - 1;
    }

    HashTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++)
            this->m_symbols[i] = new SizedArray();
        for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++)
            this->m_tradingSession[j] = new SizedArray();
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                this->m_table[i][j] = new TableItemClassName();
            }
        };
        this->m_symbolsCount = 0;
        this->m_tradingSessionsCount = 0;
        this->m_usedItems = new PointerList<TableItemClassName>(MAX_SYMBOLS_COUNT * MAX_TRADING_SESSIONS_COUNT + 10);
    }
    ~HashTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++)
            delete this->m_symbols[i];
        for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++)
            delete this->m_tradingSession[j];
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

    inline TableItemClassName* GetItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) {
        int symbolIndex = GetSymbolIndex(symbol, symbolLen);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession, tradingSessionLen);
        return this->m_table[symbolIndex][tradingSessionIndex];
    }

    inline void Clear() {
        this->m_symbolsCount = 0;
        this->m_tradingSessionsCount = 0;
        if(this->m_usedItems->Count() == 0)
            return;
        LinkedPointer<TableItemClassName> *node = this->m_usedItems->Start();
        while(true) {
            TableItemClassName *item = node->Data();
            item->Used(false);
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
    }

    inline void AddUsed(TableItemClassName *item) {
        if(item->Used())
            return;
        item->Used(true);
        this->m_usedItems->Add(item);
    }
    inline void RemoveUsed(TableItemClassName *item) {
        if(item->Used())
            return;
        item->Used(false);
        this->m_usedItems->Remove(item);
    }
};

#endif //HFT_ROBOT_MARKETDATATABLE_H
