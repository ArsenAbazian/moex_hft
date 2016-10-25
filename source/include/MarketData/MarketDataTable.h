//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include "../Lib/HashTable.h"
#include "../FastTypes.h"

template <typename T> class OrderBookTableItem {
    PointerList<T>      *m_sellQuoteList;
    PointerList<T>      *m_buyQuoteList;

    bool                 m_used;

public:
    OrderBookTableItem() {
        this->m_sellQuoteList = new PointerList<T>(128);
        this->m_buyQuoteList = new PointerList<T>(128);
    }
    ~OrderBookTableItem() {
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline PointerList<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerList<T>* BuyQuotes() { return this->m_buyQuoteList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerList<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            node->Data()->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
        Clear(this->m_sellQuoteList);
        Clear(this->m_buyQuoteList);
    }

    inline LinkedPointer<T>* AddBuyQuote(Decimal *price) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        double value = price->Calculate();

        if(node != null) {
            while (true) {
                if (node->Data()->MDEntryPx.Value < value) {
                    LinkedPointer<T> *curr = this->m_buyQuoteList->Pop();
                    this->m_buyQuoteList->Insert(node, curr);
                    return curr;
                }
                if (node == this->m_buyQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<T> *curr = this->m_buyQuoteList->Pop();
        this->m_buyQuoteList->Add(curr);
        return curr;
    }

    inline LinkedPointer<T>* AddSellQuote(Decimal *price) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        double value = price->Calculate();

        if(node != null) {
            while (true) {
                if (node->Data()->MDEntryPx.Value > value) {
                    LinkedPointer<T> *curr = this->m_sellQuoteList->Pop();
                    this->m_sellQuoteList->Insert(node, curr);
                    return curr;
                }
                if (node == this->m_sellQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<T> *curr = this->m_sellQuoteList->Pop();
        this->m_sellQuoteList->Add(curr);
        return curr;
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        LinkedPointer<T> *res = AddBuyQuote(&(item->MDEntryPx));
        res->Data(item);
        return res;
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        LinkedPointer<T> *res = AddSellQuote(&(item->MDEntryPx));
        res->Data(item);
        return res;
    }

    inline LinkedPointer<T>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        return this->AddSellQuote(info);
    }

    inline LinkedPointer<T>* GetQuote(PointerList<T> *list, T *info) {
        LinkedPointer<T> *node = list->Start();
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

    inline LinkedPointer<T>* RemoveBuyQuote(T *info) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_buyQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline LinkedPointer<T>* RemoveSellQuote(T *info) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_sellQuoteList->Remove(node);
                data->Clear();
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



template <typename T> class OrderTableItem {
    PointerList<T>      *m_sellQuoteList;
    PointerList<T>      *m_buyQuoteList;

    bool                 m_used;

public:
    OrderTableItem() {
        this->m_sellQuoteList = new PointerList<T>(128);
        this->m_buyQuoteList = new PointerList<T>(128);
    }
    ~OrderTableItem() {
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline PointerList<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerList<T>* BuyQuotes() { return this->m_buyQuoteList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerList<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            node->Data()->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
        Clear(this->m_sellQuoteList);
        Clear(this->m_buyQuoteList);
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        return this->m_buyQuoteList->Add(item);
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        return this->m_sellQuoteList->Add(item);
    }

    inline LinkedPointer<T>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        return this->AddSellQuote(info);
    }

    inline LinkedPointer<T>* GetQuote(PointerList<T> *list, T *info) {
        LinkedPointer<T> *node = list->Start();
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

    inline LinkedPointer<T>* RemoveBuyQuote(T *info) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_buyQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline LinkedPointer<T>* RemoveSellQuote(T *info) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_sellQuoteList->Remove(node);
                data->Clear();
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


template <template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO> class MarketDataTable {
    HashTable<TABLEITEM<ITEMINFO>>                *m_table;

public:
    MarketDataTable() {
        this->m_table = new HashTable<TABLEITEM<ITEMINFO>>();
    }
    ~MarketDataTable() {
        delete this->m_table;
    }
    inline void Add(const char *symbol, int symbolLen, const char *tradingSession, int tradingLen, ITEMINFO *item) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingLen);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(item);
    }
    inline void Add(const char *symbol, int symbolLen, const char *tradingSession, int tradingLen, ITEMINFO **items) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingLen);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(items);
    }
    inline void Add(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(info);
    }
    inline void Add(INFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        ITEMINFO **item = info->GroupMDEntries;

        for(int i = 0; i < info->GroupMDEntriesCount; i++, item++) {
            tableItem->Add(*item);
        }
    }
    inline void Remove(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        tableItem->Remove(info);
    }
    inline void Change(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        tableItem->Change(info);
    }
    inline void Clear() {
        this->m_table->Clear();
    }
    inline void ClearItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingSessionLen);
        this->m_table->RemoveUsed(tableItem);
        tableItem->Clear();
    }
    inline int SymbolsCount() { return this->m_table->SymbolsCount(); }
    inline int TradingSessionsCount() { return this->m_table->TradingSessionsCount(); }
    inline int UsedItemCount() { return this->m_table->UsedItemCount(); }
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) { return this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingSessionLen);  }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
