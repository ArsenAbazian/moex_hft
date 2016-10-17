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

class OrderBookTableItem {
    PointerList<OrderBookQuote>      *m_sellQuoteList;
    PointerList<OrderBookQuote>      *m_buyQuoteList;

    bool                              m_used;

public:
    OrderBookTableItem() {
        this->m_sellQuoteList = new PointerList<OrderBookQuote>(128);
        this->m_buyQuoteList = new PointerList<OrderBookQuote>(128);
        this->m_sellQuoteList->AllocData();
        this->m_buyQuoteList->AllocData();
    }
    ~OrderBookTableItem() {
        this->m_sellQuoteList->FreeData();
        this->m_buyQuoteList->FreeData();
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline PointerList<OrderBookQuote>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerList<OrderBookQuote>* BuyQuotes() { return this->m_buyQuoteList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear() {
        this->m_sellQuoteList->Clear();
        this->m_buyQuoteList->Clear();
    }

    inline void Assign(OrderBookQuote *quote, const char *id, Decimal *price, Decimal *size) {
        quote->Price.Assign(price);
        quote->Size.Assign(size);
    }

    inline void AddBuyQuote(const char *id, Decimal *price, Decimal *size) {
        LinkedPointer<OrderBookQuote> *node = this->m_buyQuoteList->Start();
        double value = price->Calculate();

        while(true) {
            if(node->Data()->Price.Value < value) {
                LinkedPointer<OrderBookQuote> *curr = this->m_buyQuoteList->Pop();
                this->Assign(curr->Data(), id, price, size);
                this->m_buyQuoteList->Insert(node, curr);
                return;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        LinkedPointer<OrderBookQuote> *curr = this->m_buyQuoteList->Pop();
        this->Assign(curr->Data(), id, price, size);
        this->m_buyQuoteList->Add(curr);
    }

    inline void AddSellQuote(const char *id, Decimal *price, Decimal *size) {
        LinkedPointer<OrderBookQuote> *node = this->m_sellQuoteList->Start();
        double value = price->Calculate();

        while(true) {
            if(node->Data()->Price.Value > value) {
                LinkedPointer<OrderBookQuote> *curr = this->m_sellQuoteList->Pop();
                this->Assign(curr->Data(), id, price, size);
                this->m_sellQuoteList->Insert(node, curr);
                return;
            }
            if(node == this->m_sellQuoteList->End())
                break;
            node = node->Next();
        }
        LinkedPointer<OrderBookQuote> *curr = this->m_sellQuoteList->Pop();
        this->Assign(curr->Data(), id, price, size);
        this->m_sellQuoteList->Add(curr);
    }
};

template <typename T> class OrderBookTable {
    HashTable<T>                *m_table;

public:
    OrderBookTable() {
        this->m_table = new HashTable<OrderBookTableItem>();
    }
    ~OrderBookTable() {
        delete this->m_table;
    }

    inline void Add(const char *symbol, const char *tradingSession, T *item) {
        T *tableItem = this->m_table->GetItem(symbol, tradingSession);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(item);
    }
    inline void Add(const char *symbol, const char *tradingSession, T **items) {
        T *tableItem = this->m_table->GetItem(symbol, tradingSession);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(items);
    }
    inline void Clear() {
        this->m_table->Clear();
    }
    inline void ClearItem(const char *symbol, const char *tradingSession) {
        T *tableItem = this->m_table->GetItem(symbol, tradingSession);
        this->m_table->RemoveUsed(tableItem);
        tableItem->Clear();
    }
    inline int SymbolsCount() { return this->m_table->SymbolsCount(); }
    inline int TradingSessionsCount() { return this->m_table->TradingSessionsCount(); }
    inline int UsedItemCount() { return this->m_table->UsedItemCount(); }
    inline T* GetItem(const char *symbol, const char *tradingSession) { return this->m_table->GetItem(symbol, tradingSession);  }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
