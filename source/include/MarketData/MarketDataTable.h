//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include "../Lib/HashTable.h"
#include "../FastTypes.h"

#define MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH 2000

template <typename T> class MDEntrQueue {
    T           **m_incEntries;
    int         m_incEntriesCount;
    int         m_incEntriesMaxIndex;
    int         m_incStartRptSeq;

public:
    MDEntrQueue() {
        this->m_incEntries = new T*[MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH];
        this->m_incEntriesCount = MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH;
        bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }
    ~MDEntrQueue() {
        delete this->m_incEntries;
    }

    inline void StartRptSeq(int rptSeq) {
        this->m_incStartRptSeq = rptSeq;
    }

    inline int StartRptSeq() { return this->m_incStartRptSeq; }

    inline void AddEntry(T *entry) {
        int index = entry->RptSeq - this->m_incStartRptSeq;
        this->m_incEntries[index] = entry;
        if(index > this->m_incEntriesMaxIndex)
            this->m_incEntriesMaxIndex = index;
    }

    inline void Reset() {
        bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }

    inline void Clear() {
        T **ptr = this->m_incEntries;
        T *item = 0;
        for(int i = 0; i < this->m_incEntriesCount; i++) {
            item = *ptr;
            if(item != 0) item->Clear();
        }
        this->Reset();
    }

    inline int MaxIndex() { return this->m_incEntriesMaxIndex; }
    inline bool HasEntries() { return this->m_incEntriesMaxIndex != -1; };
    inline T** Entries() { return this->m_incEntries; }
    inline int RptSeq() { return this->m_incStartRptSeq; }
};

template <typename T> class MarketSymbolInfo;

template <typename T> class OrderBookInfo {
    PointerList<T>      *m_sellQuoteList;
    PointerList<T>      *m_buyQuoteList;

    MDEntrQueue<T>      *m_entryInfo;

    bool                 m_used;
    bool                 m_shouldProcessSnapshot;
    int                  m_rptSeq;

    SizedArray          *m_tradingSession;
    MarketSymbolInfo<OrderBookInfo<T>>    *m_symbolInfo;
public:
    OrderBookInfo() {
        this->m_entryInfo = new MDEntrQueue<T>();
        this->m_sellQuoteList = new PointerList<T>(128);
        this->m_buyQuoteList = new PointerList<T>(128);
        this->m_rptSeq = 0;
        this->m_used = false;
        this->m_tradingSession = new SizedArray();
        this->m_shouldProcessSnapshot = false;
    }
    ~OrderBookInfo() {
        delete this->m_entryInfo;
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline SizedArray* Symbol() { return this->m_symbolInfo->Symbol(); }
    inline MarketSymbolInfo<OrderBookInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<OrderBookInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }

    inline PointerList<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerList<T>* BuyQuotes() { return this->m_buyQuoteList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }

    inline int RptSeq() { return this->m_rptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline void Clear(PointerList<T> *list) {
        this->m_rptSeq = 0;
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
        this->m_entryInfo->Clear();
        this->m_rptSeq = 0;
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
        item->Used = true;
        res->Data(item);
        return res;
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        LinkedPointer<T> *res = AddSellQuote(&(item->MDEntryPx));
        item->Used = true;
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
            if(node == this->m_sellQuoteList->End())
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

    inline MDEntrQueue<T>* EntriesQueue() { return this->m_entryInfo; }

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void PushMessageToQueue(T *info) {
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info);
    }

    inline void ForceProcessMessage(T *info) {
        if(info->MDUpdateAction == mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == mduaChange)
            this->Change(info);
        else
            this->Remove(info);
    }

    inline bool ProcessIncrementalMessage(T *info) {
        if(!this->IsNextMessage(info)) {
            this->PushMessageToQueue(info);
            return false;
        }
        this->m_rptSeq = info->RptSeq;
        this->ForceProcessMessage(info);
        if(this->m_entryInfo->HasEntries())
            return this->ProcessQueueMessages();
        return true;
    }

    inline void StartProcessSnapshotMessages() {
        this->BuyQuotes()->Clear();
        this->SellQuotes()->Clear();
    }

    inline void ProcessSnapshotMessage(T *info) {
        this->ForceProcessMessage(info);
    }

    inline bool ProcessQueueMessages() {
        if(!this->m_entryInfo->HasEntries())
            return true;
        T **entry = this->m_entryInfo->Entries();
        int incRptSeq = this->m_entryInfo->RptSeq();
        int maxIndex = this->m_entryInfo->MaxIndex();
        if(this->m_rptSeq + 1 < incRptSeq)
            return false;
        int startIndex = this->m_rptSeq + 1 - incRptSeq;
        for(int i = 0; i < startIndex; i++, entry++) {
            if((*entry) != 0) (*entry)->Clear();
        }
        for(int index = startIndex; index <= maxIndex; index++) {
            if((*entry) == 0)
                return false;
            ForceProcessMessage(*entry);
            this->m_rptSeq = (*entry)->RptSeq;
            entry++;
        }
        this->m_entryInfo->Reset();
        return true;
    }

    inline void DecSessionsToRecvSnapshotCount() {
        if(this->m_shouldProcessSnapshot) {
            SymbolInfo()->DecSessionsToRecvSnapshotCount();
            this->m_shouldProcessSnapshot = false;
        }
    }

    inline bool EndProcessSnapshotMessages() {
        bool res = this->ProcessQueueMessages();
        if(res)
            this->DecSessionsToRecvSnapshotCount();
        return res;
    }

    inline void EnterSnapshotMode() {
        this->m_shouldProcessSnapshot = true;
    }

    inline void ExitSnapshotMode() {
        this->m_shouldProcessSnapshot = false;
    }

    inline bool ShouldProcessSnapshot() { return this->m_shouldProcessSnapshot; }

    inline void ProcessActualSnapshotState() {
        if(!this->m_shouldProcessSnapshot)
            return;
        this->m_shouldProcessSnapshot = false;
        SymbolInfo()->DecSessionsToRecvSnapshotCount();
    }
};

template <typename T> class OrderInfo {
    PointerList<T>      *m_sellQuoteList;
    PointerList<T>      *m_buyQuoteList;

    MDEntrQueue<T>      *m_entryInfo;

    bool                 m_used;
    bool                 m_shouldProcessSnapshot;
    int                  m_rptSeq;
    MarketSymbolInfo<OrderInfo<T>>    *m_symbolInfo;
    SizedArray          *m_tradingSession;
public:
    OrderInfo() {
        this->m_entryInfo = new MDEntrQueue<T>();
        this->m_sellQuoteList = new PointerList<T>(128);
        this->m_buyQuoteList = new PointerList<T>(128);
        this->m_tradingSession = new SizedArray();
        this->m_shouldProcessSnapshot = false;
        this->m_rptSeq = 0;
    }
    ~OrderInfo() {
        delete this->m_entryInfo;
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline SizedArray* Symbol() { return this->m_symbolInfo->Symbol(); }
    inline MarketSymbolInfo<OrderInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<OrderInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline MDEntrQueue<T>* EntriesQueue() { return this->m_entryInfo; }

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
        this->m_entryInfo->Clear();
        this->m_rptSeq = 0;
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        item->Used = true;
        return this->m_buyQuoteList->Add(item);
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        item->Used = true;
        return this->m_sellQuoteList->Add(item);
    }

    inline LinkedPointer<T>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            return this->AddSellQuote(info);
        return 0;
    }

    inline LinkedPointer<T>* GetQuote(PointerList<T> *list, T *info) {
        LinkedPointer<T> *node = list->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *info2 = node->Data();
            if(StringIdComparer::Equal(info2->MDEntryID, info2->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength))
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
            if(node == this->m_sellQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void ChangeBuyQuote(T *info) {
        LinkedPointer<T> *ptr = GetQuote(this->m_buyQuoteList, info);
        info->Used = true;
        ptr->Data()->Clear();
        ptr->Data(info);
    }

    inline void ChangeSellQuote(T *info) {
        LinkedPointer<T> *ptr = GetQuote(this->m_sellQuoteList, info);
        info->Used = true;
        ptr->Data()->Clear();
        ptr->Data(info);
    }

    inline void Remove(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->RemoveBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            this->RemoveSellQuote(info);
    }

    inline void Change(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->ChangeBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            this->ChangeSellQuote(info);
    }

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void PushMessageToQueue(T *info) {
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info);
    }

    inline void ForceProcessMessage(T *info) {
        if(info->MDUpdateAction == mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == mduaChange)
            this->Change(info);
        else
            this->Remove(info);
    }

    inline bool ProcessIncrementalMessage(T *info) {
        if(!this->IsNextMessage(info)) {
            this->PushMessageToQueue(info);
            return false;
        }
        this->m_rptSeq = info->RptSeq;
        this->ForceProcessMessage(info);
        if(this->m_entryInfo->HasEntries())
            return this->ProcessQueueMessages();
        return true;
    }

    inline void StartProcessSnapshotMessages() {
        this->BuyQuotes()->Clear();
        this->SellQuotes()->Clear();
    }

    inline void ProcessSnapshotMessage(T *info) {
        this->ForceProcessMessage(info);
    }

    inline bool ProcessQueueMessages() {
        if(!this->m_entryInfo->HasEntries())
            return true;
        T **entry = this->m_entryInfo->Entries();
        int incRptSeq = this->m_entryInfo->RptSeq();
        int maxIndex = this->m_entryInfo->MaxIndex();
        if(this->m_rptSeq + 1 < incRptSeq)
            return false;
        int startIndex = this->m_rptSeq + 1 - incRptSeq;
        for(int i = 0; i < startIndex; i++, entry++) {
            if((*entry) != 0) (*entry)->Clear();
        }
        for(int index = startIndex; index <= maxIndex; index++) {
            if((*entry) == 0)
                return false;
            ForceProcessMessage(*entry);
            this->m_rptSeq = (*entry)->RptSeq;
            entry++;
        }
        this->m_entryInfo->Reset();
        return true;
    }

    inline void DecSessionsToRecvSnapshotCount() {
        if(this->m_shouldProcessSnapshot) {
            SymbolInfo()->DecSessionsToRecvSnapshotCount();
            this->m_shouldProcessSnapshot = false;
        }
    }

    inline bool EndProcessSnapshotMessages() {
        bool res = this->ProcessQueueMessages();
        if(res)
            this->DecSessionsToRecvSnapshotCount();
        return res;
    }

    inline void EnterSnapshotMode() {
        this->m_shouldProcessSnapshot = true;
    }

    inline void ExitSnapshotMode() {
        this->m_shouldProcessSnapshot = false;
    }

    inline bool ShouldProcessSnapshot() { return this->m_shouldProcessSnapshot; }

    inline void ProcessActualSnapshotState() {
        if(!this->m_shouldProcessSnapshot)
            return;
        this->m_shouldProcessSnapshot = false;
        SymbolInfo()->DecSessionsToRecvSnapshotCount();
    }
};

template <typename T> class TradeInfo {
    PointerList<T>                      *m_tradeList;

    bool                                m_used;
    bool                                m_shouldProcessSnapshot;
    int                                 m_rptSeq;
    MarketSymbolInfo<TradeInfo<T>>    *m_symbolInfo;
    SizedArray                          *m_tradingSession;
public:
    TradeInfo() {
        this->m_tradeList = new PointerList<T>(128);
        this->m_shouldProcessSnapshot = false;
        this->m_rptSeq = 0;
    }
    ~TradeInfo() {
        delete this->m_tradeList;
    }

    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline SizedArray* Symbol() { return this->m_symbolInfo->Symbol(); }
    inline MarketSymbolInfo<TradeInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<TradeInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline PointerList<T>* Trades() { return this->m_tradeList; }
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
        Clear(this->m_tradeList);
    }

    inline LinkedPointer<T>* Add(T *info) {
        return this->m_tradeList->Add(info);
    }
    inline void EnterSnapshotMode() {
        this->m_shouldProcessSnapshot = true;
    }

    inline bool ShouldProcessSnapshot() { return this->m_shouldProcessSnapshot; }

    inline void ExitSnapshotMode() {
        this->m_shouldProcessSnapshot = false;
    }

    inline void ProcessSnapshotMessage(T *info) { }

    inline void ProcessActualSnapshotState() {
        if(!this->m_shouldProcessSnapshot)
            return;
        this->m_shouldProcessSnapshot = false;
        SymbolInfo()->DecSessionsToRecvSnapshotCount();
    }
};

/*
template <typename T> class StatisticsTableItem {
    bool            m_used;
    Decimal         *m_buyQuote;
    Decimal         *m_sellQuote;

public:
    StatisticsTableItem() {
        this->m_used = false;
    }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }

    inline void SetProperty(MDEntryType entryType, T *item) {
        if(entryType <= MDEntryType::mdetOLSTradeAskAuctionOpenClose) {
            if(entryType <= MDEntryType::mdetDisbalance) {
                if(entryType <= MDEntryType::mdetPriceOpenFirst) {
                    if(entryType <= MDEntryType::mdetLastDealInfo) {
                        if(entryType <= MDEntryType::mdetSellQuote) {
                            if(entryType == MDEntryType::mdetBuyQuote) {
                                this->m_buyQuote->Assign(item->MDEntryPx);
                            }
                            else { // mdetSellQuote
                                this->m_sellQuote->Assign(item->MDEntryPx);
                            }
                        }
                        else {
                            // mdetLastDealInfo

                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetIndicesList) {
                        }
                        else { // mdetPriceOpenFirst
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetPriceMin) {
                        if(entryType <= MDEntryType::mdetPriceMax) {
                            if(entryType == MDEntryType::mdetPriceCloseLast) {
                            }
                            else { // mdetPriceMax
                            }
                        }
                        else {
                            // mdetPriceMin
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceAve) {
                        }
                        else { // mdetDisbalance
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAuctionPriceCalculated) {
                    if(entryType <= MDEntryType::mdetAskPriceMax) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                            }
                            else { // mdetEmptyBook
                            }
                        }
                        else {
                            // mdetAskPriceMax
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMin) {
                        }
                        else { // mdetAuctionPriceCalculated
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetMSSTradingDenyNotEnoughMoney) {
                        if(entryType <= MDEntryType::mdetAuctionMagnitudeClose) {
                            if(entryType == MDEntryType::mdetAuctionPriceClose) {
                            }
                            else { // mdetAuctionMagnitudeClose
                            }
                        }
                        else {
                            // mdetMSSTradingDenyNotEnoughMoney
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetMSSTradeAskAuctionMagnitudeOpenClose) {
                        }
                        else { // mdetOLSTradeAskAuctionOpenClose
                        }
                    }
                }
            }
        }
        else {
            if(entryType <= MDEntryType::mdetPriceCurrentOfficial) {
                if(entryType <= MDEntryType::mdetSessionBid) {
                    if(entryType <= MDEntryType::mdetPreTradePeriodPrice) {
                        if(entryType <= MDEntryType::mdetOLSTradeBidAuctionOpenClose) {
                            if(entryType == MDEntryType::mdetMSSTradeBidAuctionMagnitudeOpenClose) {
                            }
                            else { // mdetOLSTradeBidAuctionOpenClose
                            }
                        }
                        else {
                            // mdetPreTradePeriodPrice
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetSessionAsk) {
                        }
                        else { // mdetSessionBid
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetTradePrice) {
                        if(entryType <= MDEntryType::mdetTradePrice2) {
                            if(entryType == MDEntryType::mdetPostTradePeriodPrice) {
                            }
                            else { // mdetTradePrice2
                            }
                        }
                        else {
                            // mdetTradePrice
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceOpenOfficial) {
                        }
                        else { // mdetPriceCurrentOfficial
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAskTotal) {
                    if(entryType <= MDEntryType::mdetAuctionPriceBigPackets) {
                        if(entryType <= MDEntryType::mdetPriceCloseOfficial) {
                            if(entryType == MDEntryType::mdetLegitimQuote) {
                            }
                            else { // mdetPriceCloseOfficial
                            }
                        }
                        else {
                            // mdetAuctionPriceBigPackets
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetDuration) {
                        }
                        else { // mdetAskTotal
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetAuctionMagnitudeBigPackets) {
                        if(entryType == MDEntryType::mdetBidTotal) {
                        }
                        else { // mdetAuctionMagnitudeBigPackets
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetCumulativeCouponDebit) {
                        }
                        else { // mdetAllDeals
                        }
                    }
                }
            }
        }
    }
    
    inline void Add(T *item) {
        SetProperty(item->MDentryType[0], item);
    }
    inline void Change(T *item) {
        SetProperty(item->MDentryType[0], item);
    }
    inline void Remove(T *item) {

    }
};
*/

typedef enum _MarketSessionInfoFlags {
    msfUseOrderBookInfo = 1,
    msfUseOrderInfo = 2,
    msfUseTradeInfo = 4
}MarketSessionInfoFlags;

template <typename OBR, typename OBS, typename OLR, typename OLS, typename TLR, typename TLS, typename MSS> class MarketSessionInfo {
    OrderBookInfo<OBR>          *m_orderBookInfo;
    OrderInfo<OLR>              *m_orderInfo;
    TradeInfo<TLR>              *m_tradeInfo;
public:
    MarketSessionInfo(MarketSessionInfoFlags flags) {
        this->m_orderBookInfo = 0;
        this->m_orderInfo = 0;
        this->m_tradeInfo = 0;
        if((flags & msfUseOrderBookInfo) != 0)
            this->m_orderBookInfo = new ::OrderBookInfo<OBR>();
        if((flags & msfUseOrderInfo) != 0)
            this->m_orderInfo = new ::OrderInfo<OLR>();
        if((flags & msfUseTradeInfo) != 0)
            this->m_tradeInfo = new ::TradeInfo<TLR>();
    }
    ~MarketSessionInfo() {
        if(this->m_orderBookInfo != 0)
            delete this->m_orderBookInfo;
        if(this->m_orderInfo != 0)
            delete this->m_orderInfo;
        if(this->m_tradeInfo != 0)
            delete this->m_tradeInfo;
    }

    OrderBookInfo<OBR>* OrderBookInfo() { return this->m_orderBookInfo; }
    OrderInfo<OLR>* OrderInfo() { return this->m_orderInfo; }
    TradeInfo<TLR>* TradeInfo() { return this->m_tradeInfo; }
};

template <typename T> class MarketSymbolInfo {
    T                                  *m_items[MAX_TRADING_SESSIONS_COUNT];
    SizedArray                         *m_symbol;
    int                                 m_count;
    int                                 m_sessionsToRecvSnapshot;
public:
    MarketSymbolInfo() {
        this->m_count = 0;
        for(int i = 0; i < MAX_TRADING_SESSIONS_COUNT; i++) {
            this->m_items[i] = new T();
            this->m_items[i]->SymbolInfo(this);
        }
        this->m_symbol = new SizedArray();
    }
    ~MarketSymbolInfo() {
        for(int i = 0; i < MAX_TRADING_SESSIONS_COUNT; i++)
            delete this->m_items[i];
        delete this->m_symbol;
    }
    inline int Count() { return this->m_count; }
    inline T* Session(int index) { return this->m_items[index]; }
    inline T* GetSession(const char *session, int sessionLength) {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            if((*item)->TradingSession()->Equal(session, sessionLength))
                return *item;
        }
        T* res = this->m_items[this->m_count];
        res->TradingSession()->Set(session, sessionLength);
        this->m_count++;
        return res;
    }
    inline SizedArray *Symbol() { return this->m_symbol; }
    inline bool Equals(const char *symbol, int symbolLen) { return this->m_symbol->Equal(symbol, symbolLen); }
    inline void Clear() {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            (*item)->Used(false);
            (*item)->Clear();
        }
        this->m_count = 0;
    }
    inline T* AddSession(const char *session, int sessionLength) {
        return GetSession(session, sessionLength);
    }
    inline T* AddSession(const char *session) {
        return AddSession(session, strlen(session));
    }
    inline void EnterSnapshotMode() {
        this->m_sessionsToRecvSnapshot = this->m_count;
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++)
            (*item)->EnterSnapshotMode();
    }
    inline void ExitSnapshotMode() {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++)
            (*item)->ExitSnapshotMode();
    }
    inline int SessionsToRecvSnapshotCount() { return this->m_sessionsToRecvSnapshot; }
    inline bool AllSessionsRecvSnapshot() { return this->m_sessionsToRecvSnapshot == 0; }
    inline void DecSessionsToRecvSnapshotCount() { this->m_sessionsToRecvSnapshot--; }
};

template <template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO> class MarketDataTable {
    MarketSymbolInfo<TABLEITEM<ITEMINFO>>       *m_symbols[MAX_SYMBOLS_COUNT];
    int                                         m_symbolsCount;
    TABLEITEM<ITEMINFO>                         *m_snapshotItem;
    TABLEITEM<ITEMINFO>                         *m_cachedItem;
    MDEntrQueue<ITEMINFO>                       *m_snapshotEntries;
    MarketSymbolInfo<TABLEITEM<ITEMINFO>>       *m_snapshotSymbol;
    int                                         m_queueItemsCount;
    int                                         m_symbolsToRecvSnapshot;
    bool                                        m_snapshotItemHasEntriesQueue;

    inline void AddUsed(TABLEITEM<ITEMINFO> *tableItem) {
        tableItem->Used(true);
    }
public:
    MarketDataTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++)
            this->m_symbols[i] = new MarketSymbolInfo<TABLEITEM<ITEMINFO>>();
        this->m_symbolsCount = 0;
        this->m_queueItemsCount = 0;
        this->m_cachedItem = 0;
    }
    ~MarketDataTable() {
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++)
            delete this->m_symbols[i];
    }
    inline TABLEITEM<ITEMINFO>* GetCachedItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) {
        if(this->m_cachedItem == 0)
            return 0;
        if(this->m_cachedItem->Symbol()->Equal(symbol, symbolLen) && this->m_cachedItem->TradingSession()->Equal(tradingSession, tradingSessionLen))
            return this->m_cachedItem;
        return 0;
    }
    inline void ObtainSnapshotItem(INFO *info) {
        this->m_snapshotItem = this->GetCachedItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        if(this->m_snapshotItem == 0)
            this->m_snapshotItem = this->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_snapshotEntries = this->m_snapshotItem->EntriesQueue();
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->AddUsed(this->m_snapshotItem);
    }
    inline bool ProcessIncremental(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->AddUsed(tableItem);
        bool prevHasEntries = tableItem->EntriesQueue()->HasEntries();
        bool res = tableItem->ProcessIncrementalMessage(info);
        bool hasEntries = tableItem->EntriesQueue()->HasEntries();
        if(hasEntries) {
            if(!prevHasEntries)
                this->m_queueItemsCount++;
        }
        else {
            if(prevHasEntries)
                this->m_queueItemsCount--;
            if(tableItem->ShouldProcessSnapshot()) {
                MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = tableItem->SymbolInfo();
                bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
                tableItem->DecSessionsToRecvSnapshotCount();
                if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
                    this->m_symbolsToRecvSnapshot--;
            }
        }

        return res;
    }
    inline bool ShouldProcessSnapshot(INFO *info) {
        if(!this->m_snapshotEntries->HasEntries())
            return this->m_snapshotItem->RptSeq() < info->RptSeq;
        return this->m_snapshotEntries->StartRptSeq() <= info->RptSeq;
    }
    inline bool CheckProcessIfSessionInActualState(INFO *info) {
        if(this->m_snapshotEntries->HasEntries())
            return false;
        if(this->m_snapshotItem->RptSeq() != info->RptSeq)
            return false;

        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = this->m_snapshotItem->SymbolInfo();
        bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
        this->m_snapshotItem->ProcessActualSnapshotState();
        if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
            this->m_symbolsToRecvSnapshot--;
        this->m_snapshotItem = 0;
        return true;
    }
    inline bool IsNullSnapshot(INFO *info) {
        return info->RptSeq == 0 && info->LastMsgSeqNumProcessed == 0;
    }
    inline bool CheckProcessNullSnapshot(INFO *info) {
        if(IsNullSnapshot(info)) {
            bool allItemsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
            this->m_snapshotItemHasEntriesQueue = this->m_snapshotEntries->HasEntries();
            this->m_snapshotEntries->Clear();
            this->m_snapshotItem->DecSessionsToRecvSnapshotCount();
            if(this->m_snapshotItemHasEntriesQueue && !this->m_snapshotEntries->HasEntries())
                this->m_queueItemsCount--;
            if(!allItemsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot())
                this->m_symbolsToRecvSnapshot--;
            this->m_snapshotItem = 0;
            return true;
        }
        return false;
    }
    inline void StartProcessSnapshot(INFO *info) {
        this->m_snapshotItemHasEntriesQueue = this->m_snapshotEntries->HasEntries();
        this->m_snapshotItem->StartProcessSnapshotMessages();
    }
    inline bool EndProcessSnapshot() {
        bool allItemsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
        bool res = this->m_snapshotItem->EndProcessSnapshotMessages();
        if(this->m_snapshotItemHasEntriesQueue && !this->m_snapshotEntries->HasEntries())
            this->m_queueItemsCount--;
        if(!allItemsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot())
            this->m_symbolsToRecvSnapshot--;
        this->m_snapshotItem = 0;
        return res;
    }
    inline void ProcessSnapshot(ITEMINFO **item, int count, int rptSeq) {
        for(int j = 0; j < count; j++) {
            this->m_snapshotItem->ProcessSnapshotMessage(*item);
            item++;
        }
        this->m_snapshotItem->RptSeq(rptSeq);
    }
    inline void ProcessSnapshot(INFO *info) {
        this->ProcessSnapshot(info->GroupMDEntries, info->GroupMDEntriesCount, info->RptSeq);
    }
    inline void Clear() {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++)
            (*s)->Clear();
        this->m_symbolsCount = 0;
        this->m_queueItemsCount = 0;
        this->m_symbolsToRecvSnapshot = 0;
    }
    inline int SymbolsCount() { return this->m_symbolsCount; }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* Symbol(int index) { return this->m_symbols[index]; }
    inline TABLEITEM<ITEMINFO>* Item(int sindex, int tindex) { return this->m_symbols[sindex]->Session(tindex); }

    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>> *GetSymbol(const char *symbol, int symbolLen) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++) {
            if((*s)->Equals(symbol, symbolLen))
                return (*s);
        }
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *res = this->m_symbols[this->m_symbolsCount];
        res->Symbol()->Set(symbol, symbolLen);
        this->m_symbolsCount++;
        return res;
    }
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) {
        TABLEITEM<ITEMINFO> *item = 0;
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = GetSymbol(symbol, symbolLen);
        TABLEITEM<ITEMINFO>* res = s->GetSession(tradingSession, tradingSessionLen);
        this->m_cachedItem = res;
        return res;
    }
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, const char *tradingSession) {
        return this->GetItem(symbol, strlen(symbol), tradingSession, strlen(tradingSession));
    }
    inline TABLEITEM<ITEMINFO>* AddItem(const char *symbol, const char *tradingSession) {
        return this->GetItem(symbol, strlen(symbol), tradingSession, strlen(tradingSession));
    }
    inline int UsedItemCount() {
        int res = 0;
        for(int i = 0; i < this->m_symbolsCount; i++)
            res += this->m_symbols[i]->Count();
        return res;
    }
    inline TABLEITEM<ITEMINFO>* SnapshotItem() { return this->m_snapshotItem; }
    inline bool HasQueueEntries() {
        return this->m_queueItemsCount > 0;
    }
    inline int QueueEntriesCount() { return this->m_queueItemsCount; }
    inline TABLEITEM<ITEMINFO>* Add(const char *symbol, const char *session) {
        return GetItem(symbol, session);
    }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol, int symbolLength) {
        return GetSymbol(symbol, symbolLength);
    }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol) {
        return AddSymbol(symbol, strlen(symbol));
    }
    inline void EnterSnapshotMode() {
        this->m_symbolsToRecvSnapshot = this->m_symbolsCount;
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++)
            (*s)->EnterSnapshotMode();
    }
    inline void ExitSnapshotMode() {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++)
            (*s)->ExitSnapshotMode();
    }
    inline int SymbolsToRecvSnapshotCount() { return this->m_symbolsToRecvSnapshot; }
    inline bool IsAllSymbolsRecvSnapshot() { return this->m_symbolsToRecvSnapshot == 0; }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
