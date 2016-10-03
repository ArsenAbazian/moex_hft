//
// Created by root on 21.09.16.
//

#ifndef HFT_ROBOT_MARKETDATATABLE_H
#define HFT_ROBOT_MARKETDATATABLE_H

#include "../Lib/SimpleList.h"
#include "../Types.h"

#define MAX_SYMBOLS_COUNT               128
#define MAX_TRADING_SESSIONS_COUNT      128
#define MAX_TABLE_LIST_COUNT            256

class MarketDataTable {
    char                m_symbols[MAX_SYMBOLS_COUNT][4];
    char                m_tradingSession[MAX_TRADING_SESSIONS_COUNT][8];
    int                 m_symbolsCount;
    int                 m_tradingSessionsCount;

    SimpleList*         m_table[MAX_SYMBOLS_COUNT][MAX_TRADING_SESSIONS_COUNT];
    int                 m_usedListsMap[MAX_SYMBOLS_COUNT][MAX_TRADING_SESSIONS_COUNT];
    SimpleList*         m_usedLists;
    SimpleList*         m_usedMapList;

    inline bool IsSymbolEquals(char *s1, char *s2) {
        UINT32 *u1 = (UINT32*)s1;
        UINT32 *u2 = (UINT32*)s2;
        return (*u1) == (*u2);
    }

    inline bool IsTradingSessionEquals(char *s1, char *s2) {
        UINT64 *u1 = (UINT64*)s1;
        UINT64 *u2 = (UINT64*)s2;

        if( (*u1) != (*u2) )
            return false;

        short *sh1 = (short*)(s1 + 8);
        short *sh2 = (short*)(s2 + 8);

        return (*sh1) == (*sh2);
    }

public:
    inline int GetSymbolIndex(char *symbol) {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            if(this->IsSymbolEquals(symbol, this->m_symbols[i]))
                return i;
        }
        *((UINT32*)this->m_symbols[this->m_symbolsCount]) = *((UINT32*)symbol);
        this->m_symbolsCount++;
        return this->m_symbolsCount - 1;
    }
    inline int GetTradingSessionIdIndex(char *tradingSessionId) {
        for(int i = 0; i < this->m_tradingSessionsCount; i++) {
            if(this->IsTradingSessionEquals(tradingSessionId, this->m_tradingSession[i]))
                return i;
        }
        *((UINT64*)this->m_tradingSession[this->m_tradingSessionsCount]) = *((UINT64*)tradingSessionId);
        *((short*)(this->m_tradingSession[this->m_tradingSessionsCount] + 8)) = *((short*)(tradingSessionId + 8));
        this->m_tradingSessionsCount++;
        return this->m_tradingSessionsCount - 1;
    }

    MarketDataTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                this->m_table[i][j] = new SimpleList(MAX_TABLE_LIST_COUNT);
                this->m_usedListsMap[i][j] = 0;
            }
        }
        this->m_usedLists = new SimpleList(MAX_SYMBOLS_COUNT * MAX_TRADING_SESSIONS_COUNT + 10);
        this->m_usedMapList = new SimpleList(MAX_SYMBOLS_COUNT * MAX_TRADING_SESSIONS_COUNT + 10);
    }
    ~MarketDataTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                delete this->m_table[i][j];
            }
        }
    }

    inline SimpleList* GetList(char *symbol, char *tradingSession) {
        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);
        return this->m_table[symbolIndex][tradingSessionIndex];
    }

    inline SimpleList* GetListAndRemoveRef(char *symbol, char *tradingSession) {
        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);

        if(this->m_usedListsMap[symbolIndex][tradingSessionIndex] > 0)
            this->m_usedListsMap[symbolIndex][tradingSessionIndex]--;

        return this->m_table[symbolIndex][tradingSessionIndex];
    }

    inline void Add(char *symbol, char *tradingSession, void *data) {
        int symbolIndex = GetSymbolIndex(symbol);
        int tradingSessionIndex = GetTradingSessionIdIndex(tradingSession);

        SimpleList *list = this->m_table[symbolIndex][tradingSessionIndex];
        list->Add(data);

        if(this->m_usedListsMap[symbolIndex][tradingSessionIndex] == 0) {
            this->m_usedLists->Add(list);
            this->m_usedMapList->Add(&(this->m_usedListsMap[symbolIndex][tradingSessionIndex]));
        }
        this->m_usedListsMap[symbolIndex][tradingSessionIndex]++;
    }

    inline void Clear() {
        SimpleListNode *node = this->m_usedLists->Start();
        while(true) {
            SimpleList *list = (SimpleList*)node->Data();
            list->Clear();
            if(node == this->m_usedLists->End())
                break;
            node = this->m_usedLists->Next(node);
        }
        this->m_usedLists->Clear();
        node = this->m_usedMapList->Start();
        while(true) {
            *((int*)node->Data()) = 0;
            if(node == this->m_usedMapList->End())
                break;
            node = this->m_usedMapList->Next(node);
        }
        this->m_usedMapList->Clear();
    }
};

#endif //HFT_ROBOT_MARKETDATATABLE_H
