//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include "../Lib/HashTable.h"
#include "../FastTypes.h"

class OrderBookQuote {
public:
    Decimal         Price;
    Decimal         Size;
    char            Id[11];

    OrderBookQuote() {
        Price.Exponent = 0;
        Price.Mantissa = 0;
        Size.Exponent = 0;
        Size.Mantissa = 0;
        bzero(this->Id, 11);
    }
};

template <typename T> class OrderBookTableItem {
    PointerList<OrderBookQuote>      *m_bidList;
    PointerList<OrderBookQuote>      *m_askList;

    bool                              m_used;

public:
    OrderBookTableItem() {
        this->m_bidList = new PointerList<OrderBookQuote>(128);
        this->m_askList = new PointerList<OrderBookQuote>(128);
        this->m_bidList->AllocData();
        this->m_askList->AllocData();
    }
    ~OrderBookTableItem() {
        this->m_bidList->FreeData();
        this->m_askList->FreeData();
        delete this->m_bidList;
        delete this->m_askList;
    }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear() {
        this->m_bidList->Clear();
        this->m_askList->Clear();
    }

    inline void Assign(OrderBookQuote *quote, const char *id, Decimal *price, Decimal *size) {
        quote->Price.Assign(price);
        quote->Size.Assign(size);
    }

    inline void AddBuyQuote(const char *id, Decimal *price, Decimal *size) {
        LinkedPointer<OrderBookQuote> *node = this->m_askList->Start();
        double value = price->Calculate();

        while(true) {
            if(node->Data()->Price.Value < value) {
                LinkedPointer<OrderBookQuote> *curr = this->m_askList->Pop();
                this->Assign(curr->Data(), id, price, size);
                this->m_askList->Insert(node, curr);
                return;
            }
            if(node == this->m_askList->End())
                break;
            node = node->Next();
        }
        LinkedPointer<OrderBookQuote> *curr = this->m_askList->Pop();
        this->Assign(curr->Data(), id, price, size);
        this->m_askList->Add(curr);
    }

    inline void AddSellQuote(const char *id, Decimal *price, Decimal *size) {
        LinkedPointer<OrderBookQuote> *node = this->m_bidList->Start();
        double value = price->Calculate();

        while(true) {
            if(node->Data()->Price.Value > value) {
                LinkedPointer<OrderBookQuote> *curr = this->m_bidList->Pop();
                this->Assign(curr->Data(), id, price, size);
                this->m_bidList->Insert(node, curr);
                return;
            }
            if(node == this->m_bidList->End())
                break;
            node = node->Next();
        }
        LinkedPointer<OrderBookQuote> *curr = this->m_bidList->Pop();
        this->Assign(curr->Data(), id, price, size);
        this->m_bidList->Add(curr);
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
        this->m_table->RemoveUsed(tableItem);
        tableItem->Clear();
    }
    inline int SymbolsCount() { return this->m_table->SymbolsCount(); }
    inline int TradingSessionsCount() { return this->m_table->TradingSessionsCount(); }
    inline int UsedItemCount() { return this->m_table->UsedItemCount(); }
    inline OrderBookTableItem<T>* GetItem(const char *symbol, const char *tradingSession) { return this->m_table->GetItem(symbol, tradingSession);  }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
