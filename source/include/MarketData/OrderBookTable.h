//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include "../Lib/HashTable.h"

template <typename T> class OrderBookTableItem {
    PointerList<T>      *m_bidList;
    PointerList<T>      *m_askList;
    bool                m_used;

    inline void Clear(PointerList<T> *list) {
        LinkedPointer<T> *node = list->Start();
        while(true) {
            T *item = node->Data();
            item->Clear();
            if(node == list->End())
                break;
            node = list->Next(node);
        }
    }
public:
    OrderBookTableItem() {
        this->m_bidList = new PointerList<T>(128);
        this->m_askList = new PointerList<T>(128);
    }
    ~OrderBookTableItem() {
        delete this->m_bidList;
        delete this->m_askList;
    }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear() {
        Clear(this->m_bidList);
        Clear(this->m_askList);
    }
    inline void Add(T *item) {

    }
};

template <typename T> class OrderBookTable {
    HashTable<OrderBookTableItem<T>>                *m_table;

public:
    OrderBookTable() {
        this->m_table = new HashTable<OrderBookTableItem<T>>();
    }
    ~OrderBookTable() {
        delete this->m_table;
    }

    inline void Add(const char *symbol, const char *tradingSession, T *item) {
        OrderBookTableItem<T> *tableItem = this->m_table->GetItem(symbol, tradingSession);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(item);
    }
    inline void Add(const char *symbol, const char *tradingSession, T **items) {
        OrderBookTableItem<T> *tableItem = this->m_table->GetItem(symbol, tradingSession);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(items);
    }
    inline void Clear() {
        this->m_table->Clear();
    }
    inline void ClearItem(const char *symbol, const char *tradingSession) {
        OrderBookTableItem<T> *tableItem = this->m_table->GetItem(symbol, tradingSession);
        this->m_table->FreeItem(tableItem);
        tableItem->Clear();
    }
    inline int SymbolsCount() { return this->m_table->SymbolsCount(); }
    inline int TradingSessionsCount() { return this->m_table->TradingSessionsCount(); }
    inline int UsedItemCount() { return this->m_table->UsedItemCount(); }
    inline OrderBookTableItem<T>* GetItem(const char *symbol, const char *tradingSession) { return this->m_table->GetItem(symbol, tradingSession);  }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
