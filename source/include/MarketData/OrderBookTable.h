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
    SizedArray      *Id;
    int             RptSec;
    INT32           Time;
    INT32           OrigTime;

    OrderBookQuote() {
        Id = new SizedArray();
        Price.Exponent = 0;
        Price.Mantissa = 0;
        Size.Exponent = 0;
        Size.Mantissa = 0;
    }
};

template <typename T> class OrderBookTableItem {
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

    inline LinkedPointer<OrderBookQuote>* AddBuyQuote(Decimal *price) {
        LinkedPointer<OrderBookQuote> *node = this->m_buyQuoteList->Start();
        double value = price->Calculate();

        if(node != null) {
            while (true) {
                if (node->Data()->Price.Value < value) {
                    LinkedPointer<OrderBookQuote> *curr = this->m_buyQuoteList->Pop();
                    this->m_buyQuoteList->Insert(node, curr);
                    return curr;
                }
                if (node == this->m_buyQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<OrderBookQuote> *curr = this->m_buyQuoteList->Pop();
        this->m_buyQuoteList->Add(curr);
        return curr;
    }

    inline LinkedPointer<OrderBookQuote>* AddSellQuote(Decimal *price) {
        LinkedPointer<OrderBookQuote> *node = this->m_sellQuoteList->Start();
        double value = price->Calculate();

        if(node != null) {
            while (true) {
                if (node->Data()->Price.Value > value) {
                    LinkedPointer<OrderBookQuote> *curr = this->m_sellQuoteList->Pop();
                    this->m_sellQuoteList->Insert(node, curr);
                    return curr;
                }
                if (node == this->m_sellQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<OrderBookQuote> *curr = this->m_sellQuoteList->Pop();
        this->m_sellQuoteList->Add(curr);
        return curr;
    }

    inline void AssignQuote(LinkedPointer<OrderBookQuote> *ptr, T *item) {
        OrderBookQuote* ob = ptr->Data();

        ob->Id->m_text = item->MDEntryID;
        ob->Id->m_length = item->MDEntryIDLength;
        ob->Price.Assign(&(item->MDEntryPx));
        ob->Size.Assign(&(item->MDEntrySize));
        ob->RptSec = item->RptSeq;
        ob->Time = item->MDEntryTime;
        ob->OrigTime = item->OrigTime;
    }

    inline LinkedPointer<OrderBookQuote>* AddBuyQuote(T *item) {
        LinkedPointer<OrderBookQuote> *ptr = AddBuyQuote(&(item->MDEntryPx));
        this->AssignQuote(ptr, item);
        return ptr;
    }

    inline LinkedPointer<OrderBookQuote>* AddSellQuote(T *item) {
        LinkedPointer<OrderBookQuote> *ptr = AddSellQuote(&(item->MDEntryPx));
        this->AssignQuote(ptr, item);
        return ptr;
    }

    inline LinkedPointer<OrderBookQuote>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        return this->AddSellQuote(info);
    }

    inline LinkedPointer<OrderBookQuote>* GetQuote(PointerList<OrderBookQuote> *list, T *info) {
        LinkedPointer<OrderBookQuote> *node = list->Start();
        if(node == 0)
            return 0;
        while(true) {
            if(node->Data()->Id->Equal(info->MDEntryID, info->MDEntryIDLength))
                return node;
            if(node == list->End())
                return 0;
            node = node->Next();
        }
    }

    inline LinkedPointer<OrderBookQuote>* RemoveBuyQuote(T *info) {
        LinkedPointer<OrderBookQuote> *node = this->m_buyQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            if(node->Data()->Id->Equal(info->MDEntryID, info->MDEntryIDLength)) {
                this->m_buyQuoteList->Remove(node);
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline LinkedPointer<OrderBookQuote>* RemoveSellQuote(T *info) {
        LinkedPointer<OrderBookQuote> *node = this->m_sellQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            if(node->Data()->Id->Equal(info->MDEntryID, info->MDEntryIDLength)) {
                this->m_sellQuoteList->Remove(node);
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void ChangeBuyQuote(T *info) {
        this->RemoveBuyQuote(info);
        this->AddBuyQuote(info);
    }

    inline void ChangeSellQuote(T *info) {
        this->RemoveSellQuote(info);
        this->AddSellQuote(info);
    }

    inline void Remove(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->RemoveBuyQuote(info);
        else
            this->RemoveSellQuote(info);
    }

    inline void Change(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->ChangeBuyQuote(info);
        else
            this->ChangeSellQuote(info);
    }
};

template <typename INFO, typename ITEMINFO> class OrderBookTable {
    HashTable<OrderBookTableItem<ITEMINFO>>                *m_table;

public:
    OrderBookTable() {
        this->m_table = new HashTable<OrderBookTableItem<ITEMINFO>>();
    }
    ~OrderBookTable() {
        delete this->m_table;
    }
    inline void Add(const char *symbol, int symbolLen, const char *tradingSession, int tradingLen, ITEMINFO *item) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingLen);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(item);
    }
    inline void Add(const char *symbol, int symbolLen, const char *tradingSession, int tradingLen, ITEMINFO **items) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingLen);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(items);
    }
    inline void Add(ITEMINFO *info) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(info);
    }
    inline void Add(INFO *info) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        ITEMINFO **item = info->GroupMDEntries;

        for(int i = 0; i < info->GroupMDEntriesCount; i++, item++) {
            tableItem->Add(*item);
        }
    }
    inline void Remove(ITEMINFO *info) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        tableItem->Remove(info);
    }
    inline void Change(ITEMINFO *info) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        tableItem->Change(info);
    }
    inline void Clear() {
        this->m_table->Clear();
    }
    inline void ClearItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) {
        OrderBookTableItem<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingSessionLen);
        this->m_table->RemoveUsed(tableItem);
        tableItem->Clear();
    }
    inline int SymbolsCount() { return this->m_table->SymbolsCount(); }
    inline int TradingSessionsCount() { return this->m_table->TradingSessionsCount(); }
    inline int UsedItemCount() { return this->m_table->UsedItemCount(); }
    inline OrderBookTableItem<ITEMINFO>* GetItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) { return this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingSessionLen);  }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
