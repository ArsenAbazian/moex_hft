//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_ORDERINFO_H
#define HFT_ROBOT_ORDERINFO_H

#include "../Lib/StringIdComparer.h"
#include "../Lib/PointerList.h"
#include "../Lib/HashTable.h"
#include "../Fast/FastTypes.h"
#include "MDEntryQueue.h"
#include "QuoteInfo.h"
#include "../Managers/DebugInfoManager.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class OrderInfo {
    static PointerList<T>               *m_itemsPool;
    static PointerList<QuoteInfo>       *m_aggregatedItemsPool;

    PointerListLite<T>                  *m_sellQuoteList;
    PointerListLite<T>                  *m_buyQuoteList;

    PointerListLite<QuoteInfo>              *m_aggregatedSellQuoteList;
    PointerListLite<QuoteInfo>              *m_aggregatedBuyQuoteList;

    MDEntryQueue                       *m_entryInfo;

    bool                                m_used;
    bool                                m_shouldProcessSnapshot;
    int                                 m_rptSeq;
    int                                 m_savedRptSeq;
    MarketSymbolInfo<OrderInfo<T>>      *m_symbolInfo;
    SizedArray                          *m_tradingSession;
    UINT32                              m_sessionInt;

    int                                 m_snapshotProcessedCount;
public:
    OrderInfo();
    ~OrderInfo() {
        ReleaseEntryQue();
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
        delete this->m_aggregatedBuyQuoteList;
        delete this->m_aggregatedSellQuoteList;
    }

    inline void ReleaseEntryQue() {
        if(this->m_entryInfo != 0) {
            this->m_entryInfo->Reset();
            MDEntryQueue::Pool->FreeItem(this->m_entryInfo->Pointer);
        }
        this->m_entryInfo = 0;
    }
    inline UINT32 TradingSessionInt() { return this->m_sessionInt; }
    inline void TradingSessionInt(UINT32 session) { this->m_sessionInt = session; }
    inline void ResetSnasphotProcessed() { this->m_snapshotProcessedCount = 0; }
    inline void OnSnapshotProcessed() { this->m_snapshotProcessedCount++; }
    inline int SnapshotProcessedCount() { return this->m_snapshotProcessedCount; }
    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline SizedArray* Symbol() { return this->m_symbolInfo->Symbol(); }
    inline MarketSymbolInfo<OrderInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<OrderInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline int SavedRptSeq() { return this->m_savedRptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline bool HasEntries() { return this->m_entryInfo == 0? false: this->m_entryInfo->HasEntries(); }
    inline void ClearEntries() { this->ReleaseEntryQue(); }
    inline MDEntryQueue* EntriesQueue() { return this->m_entryInfo; }

    inline PointerListLite<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerListLite<T>* BuyQuotes() { return this->m_buyQuoteList; }

    inline PointerListLite<QuoteInfo>* AggregatedSellQuotes() { return this->m_aggregatedSellQuoteList; }
    inline PointerListLite<QuoteInfo>* AggregatedBuyQuotes() { return this->m_aggregatedBuyQuoteList; }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            T *data = node->Data();
            FreePointer(data);
            data->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
        Clear(this->m_sellQuoteList);
        Clear(this->m_buyQuoteList);
        this->m_aggregatedBuyQuoteList->Clear();
        this->m_aggregatedSellQuoteList->Clear();
        this->ClearEntries();
        this->m_rptSeq = 0;
        this->m_savedRptSeq = 0;
        this->m_shouldProcessSnapshot = false;
        this->m_snapshotProcessedCount = 0;
    }

    inline LinkedPointer<QuoteInfo>* GetAggregatedBuyQuote(Decimal *price) {
        LinkedPointer<QuoteInfo> *node = this->m_aggregatedBuyQuoteList->Start();
        double value = price->Calculate();
        QuoteInfo *quote = 0;

        if(node != 0) {
            while (true) {
                quote = node->Data();
                if (quote->Price()->Value < value) {
                    LinkedPointer<QuoteInfo> *curr = this->m_aggregatedBuyQuoteList->Insert(node);
                    quote = curr->Data();
                    quote->Price(price);
                    quote->Size(0);
                    return curr;
                }
                else if(quote->Price()->Value == value)
                    return node;
                if (node == this->m_aggregatedBuyQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<QuoteInfo> *curr = this->m_aggregatedBuyQuoteList->Add();
        quote = curr->Data();
        quote->Price(price);
        quote->Size(0);
        return curr;
    }

    inline LinkedPointer<QuoteInfo>* GetAggregatedSellQuote(Decimal *price) {
        LinkedPointer<QuoteInfo> *node = this->m_aggregatedSellQuoteList->Start();
        double value = price->Calculate();
        QuoteInfo *quote = 0;

        if(node != 0) {
            while (true) {
                quote = node->Data();
                if (quote->Price()->Value > value) {
                    LinkedPointer<QuoteInfo> *curr = this->m_aggregatedSellQuoteList->Insert(node);
                    quote = curr->Data();
                    quote->Price(price);
                    quote->Size(0);
                    return curr;
                }
                else if(quote->Price()->Value == value) {
                    return node;
                }
                if (node == this->m_aggregatedSellQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<QuoteInfo> *curr = this->m_aggregatedSellQuoteList->Add();
        quote = curr->Data();
        quote->Price(price);
        quote->Size(0);
        return curr;
    }

    inline void UpdateAggregatedBuyQuoteCore(LinkedPointer<QuoteInfo> *ptr, int size) {
        QuoteInfo *q = ptr->Data();
        q->AddSize(size);
        if(q->Size() == 0)
            this->m_aggregatedBuyQuoteList->Remove(ptr);
    }

    inline void UpdateAggregatedSellQuoteCore(LinkedPointer<QuoteInfo> *ptr, int size) {
        QuoteInfo *q = ptr->Data();
        q->AddSize(size);
        if(q->Size() == 0)
            this->m_aggregatedSellQuoteList->Remove(ptr);
    }

    inline void RemoveAggregatedBuyQuote(T *info) {
        LinkedPointer<QuoteInfo> *ptr = GetAggregatedBuyQuote(&(info->MDEntryPx));
        UpdateAggregatedBuyQuoteCore(ptr, - info->MDEntrySize.CalculatePositiveInteger());
    }

    inline void RemoveAggregatedSellQuote(T *info) {
        LinkedPointer<QuoteInfo> *ptr = GetAggregatedSellQuote(&(info->MDEntryPx));
        UpdateAggregatedSellQuoteCore(ptr, - info->MDEntrySize.CalculatePositiveInteger());
    }

    inline void ChangeAggregatedBuyQuote(T *prev, T *curr) {
        LinkedPointer<QuoteInfo> *ptr = GetAggregatedBuyQuote(&(prev->MDEntryPx));
        UpdateAggregatedBuyQuoteCore(ptr, - prev->MDEntrySize.CalculatePositiveInteger());
        ptr = GetAggregatedBuyQuote(&(curr->MDEntryPx));
        UpdateAggregatedBuyQuoteCore(ptr, curr->MDEntrySize.CalculatePositiveInteger());
    }

    inline void ChangeAggregatedSellQuote(T *prev, T *curr) {
        LinkedPointer<QuoteInfo> *ptr = GetAggregatedSellQuote(&(prev->MDEntryPx));
        UpdateAggregatedSellQuoteCore(ptr, - prev->MDEntrySize.CalculatePositiveInteger());
        ptr = GetAggregatedSellQuote(&(curr->MDEntryPx));
        UpdateAggregatedSellQuoteCore(ptr, curr->MDEntrySize.CalculatePositiveInteger());
    }

    inline void AddAggregatedBuyQuote(T *item) {
        LinkedPointer<QuoteInfo> *ptr = GetAggregatedBuyQuote(&(item->MDEntryPx));
        ptr->Data()->AddSize(item->MDEntrySize.CalculatePositiveInteger());
    }

    inline void AddAggregatedSellQuote(T *item) {
        LinkedPointer<QuoteInfo> *ptr = GetAggregatedSellQuote(&(item->MDEntryPx));
        ptr->Data()->AddSize(item->MDEntrySize.CalculatePositiveInteger());
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(T *info) {
        return HashTable::Default->GetPointer(this, info->MDEntryID, info->MDEntryIDLength);
    }
    inline void FreePointer(LinkedPointer<HashTableItemInfo> *hashItem) {
        HashTable::Default->RemovePointer(hashItem);
    }
    inline void FreePointer(T *data) {
        HashTable::Default->Remove(this, data->MDEntryID, data->MDEntryIDLength);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(T *info) {
        return HashTable::Default->Add(this, 0, info->MDEntryID, info->MDEntryIDLength);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(PointerListLite<T> *list, T *info) {
        LinkedPointer<T> *item = list->Add(info);
        return HashTable::Default->Add(this, item, info->MDEntryID, info->MDEntryIDLength);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(LinkedPointer<T> *ptr, T *info) {
        return HashTable::Default->Add(this, ptr, info->MDEntryID, info->MDEntryIDLength);
    }
    inline LinkedPointer<T>* GetQuote(PointerListLite<T> *list, T *info) {
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        if(hashItem == 0) {
            // such thing could happen because of some packet lost
            // so please do not return null :)
            LinkedPointer<T> *res = list->Add(info);
            hashItem = AddPointer(list, info);
            return res;
        }
        return static_cast<LinkedPointer<T>*>(hashItem->Data()->m_object);
    }

    inline void RemoveQuote(PointerListLite<T> *list, T *info) {
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        if(hashItem == 0) {
            // such thing could happen because of some packet lost
            // so please do not return null :)
            //TODO remove debug
            //printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
            return;
        }
        LinkedPointer<T> *node = static_cast<LinkedPointer<T>*>(hashItem->Data()->m_object);
        T *data = node->Data();
        list->Remove(node);
        this->FreePointer(hashItem);
    }

    inline void RemoveBuyQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_tradingSession, "Remove BuyQuote", info->MDEntryID, info->MDEntryIDLength, &(info->MDEntryPx), &(info->MDEntrySize));
        RemoveQuote(this->m_buyQuoteList, info);
        RemoveAggregatedBuyQuote(info);
    }

    inline void RemoveSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_tradingSession, "Remove SellQuote", info->MDEntryID, info->MDEntryIDLength, &(info->MDEntryPx), &(info->MDEntrySize));
        RemoveQuote(this->m_sellQuoteList, info);
        RemoveAggregatedSellQuote(info);
    }

    inline void ChangeBuyQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_tradingSession, "Change BuyQuote", info->MDEntryID, info->MDEntryIDLength, &(info->MDEntryPx), &(info->MDEntrySize));

        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        LinkedPointer<T> *ptr;
        if(hashItem != 0) {
            ptr = static_cast<LinkedPointer<T>*>(hashItem->Data()->m_object);
            this->m_buyQuoteList->Remove(ptr);
            ptr->Data()->Clear();

            info->Used = true;
            LinkedPointer<T> *ptrNew = this->m_buyQuoteList->Add(info);
            HashTableItemInfo *h = hashItem->Data();
            h->m_object = ptrNew;
            h->m_stringId = info->MDEntryID;
            h->m_length = info->MDEntryIDLength;
            ChangeAggregatedBuyQuote(ptr->Data(), info);
            return;
        }
        //TODO remove debug
        info->MDEntryID[info->MDEntryIDLength] = '\0';
        printf("ERROR: %s entry not found\n", info->MDEntryID);
        return;
    }

    inline void ChangeSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_tradingSession, "Change SellQuote", info->MDEntryID, info->MDEntryIDLength, &(info->MDEntryPx), &(info->MDEntrySize));
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        LinkedPointer<T> *ptr;
        if(hashItem != 0) {
            ptr = static_cast<LinkedPointer<T>*>(hashItem->Data()->m_object);
            this->m_sellQuoteList->Remove(ptr);
            ptr->Data()->Clear();

            info->Used = true;
            LinkedPointer<T> *ptrNew = this->m_sellQuoteList->Add(info);
            HashTableItemInfo *h = hashItem->Data();
            h->m_object = ptrNew;
            h->m_stringId = info->MDEntryID;
            h->m_length = info->MDEntryIDLength;
            ChangeAggregatedSellQuote(ptr->Data(), info);
            return;
        }
        //TODO remove debug
        info->MDEntryID[info->MDEntryIDLength] = '\0';
        printf("ERROR: %s entry not found\n", info->MDEntryID);
        return;
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_tradingSession, "Add BuyQuote", item->MDEntryID, item->MDEntryIDLength, &(item->MDEntryPx), &(item->MDEntrySize));
        item->Used = true;
        LinkedPointer<T> *ptr = this->m_buyQuoteList->Add(item);
        AddPointer(ptr, item);
        AddAggregatedBuyQuote(item);
        return ptr;
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_tradingSession, "Add SellQuote", item->MDEntryID, item->MDEntryIDLength, &(item->MDEntryPx), &(item->MDEntrySize));
        item->Used = true;
        LinkedPointer<T> *ptr = this->m_sellQuoteList->Add(item);
        AddPointer(ptr, item);
        ptr->Data(item);
        AddAggregatedSellQuote(item);
        return ptr;
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

    inline LinkedPointer<T>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            return this->AddSellQuote(info);
        return 0;
    }

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void ObtainEntriesQueue() {
        if(this->m_entryInfo == 0)
            this->m_entryInfo = MDEntryQueue::Pool->NewItem();
    }

    inline void PushMessageToQueue(T *info) {
        this->ObtainEntriesQueue();
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info, info->RptSeq);
    }

    inline void ForceProcessMessage(T *info) {
        if(info->MDUpdateAction == mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == mduaChange)
            this->Change(info);
        else
            this->Remove(info);
    }

    inline bool IsOutdatedMessage(T *info) {
        return info->RptSeq <= this->m_rptSeq;
    }

    inline bool ProcessIncrementalMessage(T *info) {
        if(!this->IsNextMessage(info)) {
            if(this->IsOutdatedMessage(info))
                return false;
            this->PushMessageToQueue(info);
            return false;
        }
        this->m_rptSeq = info->RptSeq;
        this->ForceProcessMessage(info);
        if(this->HasEntries())
            return this->ProcessQueueMessages();
        return true;
    }

    inline void StartProcessSnapshotMessages() {
        this->m_savedRptSeq = this->m_rptSeq;
        this->Clear(this->BuyQuotes());
        this->Clear(this->SellQuotes());
        this->AggregatedBuyQuotes()->Clear();
        this->AggregatedSellQuotes()->Clear();
    }

    inline void ProcessNullSnapshot() {
        this->Clear(this->BuyQuotes());
        this->Clear(this->SellQuotes());
        this->AggregatedBuyQuotes()->Clear();
        this->AggregatedSellQuotes()->Clear();
    }

    inline void ProcessSnapshotMessage(T *info) {
        this->Add(info);
    }

    inline bool ProcessQueueMessages() {
        if(this->m_entryInfo == 0)
            return true;
        if(!this->m_entryInfo->HasEntries()) {
            this->ReleaseEntryQue();
            return true;
        }
        T **entry = (T**)this->m_entryInfo->Entries();
        int incRptSeq = this->m_entryInfo->RptSeq();
        int maxIndex = this->m_entryInfo->MaxIndex();
        if(this->m_rptSeq + 1 < incRptSeq)
            return false;
        int startIndex = this->m_rptSeq + 1 - incRptSeq;
        for(int i = 0; i < startIndex && i < this->m_entryInfo->Capacity(); i++, entry++) {
            if((*entry) != 0) (*entry)->Clear();
            (*entry) = 0;
        }
        for(int index = startIndex; index <= maxIndex; index++) {
            if((*entry) == 0)
                return false;
            ForceProcessMessage(*entry);
            this->m_rptSeq = (*entry)->RptSeq;
            (*entry) = 0;
            entry++;
        }
        this->ReleaseEntryQue();
        return true;
    }

    inline void DecSessionsToRecvSnapshotCount() {
        if(this->m_shouldProcessSnapshot) {
            SymbolInfo()->DecSessionsToRecvSnapshotCount();
            this->m_shouldProcessSnapshot = false;
        }
    }

    inline void IncSessionsToRecvSnapshotCount() {
        if(!this->m_shouldProcessSnapshot) {
            SymbolInfo()->IncSessionsToRecvSnapshotCount();
            this->m_shouldProcessSnapshot = true;
        }
    }

    inline void CancelSnapshotMessages() {
        this->m_rptSeq = this->m_savedRptSeq;
    }

    inline bool EndProcessSnapshotMessages() {
        bool res = this->ProcessQueueMessages();
        if(res)
            this->DecSessionsToRecvSnapshotCount();
        return res;
    }

    inline bool EnterSnapshotMode() {
        this->ResetSnasphotProcessed();
        this->m_shouldProcessSnapshot = true;
        //this->m_entryInfo->ShouldProcess(true);
        return true;
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

template <typename T> PointerList<T>* OrderInfo<T>::m_itemsPool = 0;
template <typename T> PointerList<QuoteInfo>* OrderInfo<T>::m_aggregatedItemsPool = 0;

template <typename T> OrderInfo<T>::OrderInfo() :
        m_entryInfo(0),
        m_sellQuoteList(0),
        m_buyQuoteList(0),
        m_aggregatedBuyQuoteList(0),
        m_aggregatedSellQuoteList(0),
        m_tradingSession(0),
        m_shouldProcessSnapshot(false),
        m_rptSeq(0),
        m_savedRptSeq(0),
        m_snapshotProcessedCount(0),
        m_used(0),
        m_symbolInfo(0),
        m_sessionInt(0) {
    if(OrderInfo::m_itemsPool == 0)
        OrderInfo::m_itemsPool = new PointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);
    if(OrderInfo::m_aggregatedItemsPool == 0)
        OrderInfo::m_aggregatedItemsPool = new PointerList<QuoteInfo>(RobotSettings::Default->MarketDataMaxEntriesCount, true);

    HashTable::SafeCreateDefault();

    this->m_sellQuoteList = new PointerListLite<T>(OrderInfo<T>::m_itemsPool);
    this->m_buyQuoteList = new PointerListLite<T>(OrderInfo<T>::m_itemsPool);
    this->m_aggregatedBuyQuoteList = new PointerListLite<QuoteInfo>(OrderInfo<T>::m_aggregatedItemsPool);
    this->m_aggregatedSellQuoteList = new PointerListLite<QuoteInfo>(OrderInfo<T>::m_aggregatedItemsPool);

    this->m_tradingSession = new SizedArray();
}

#endif //HFT_ROBOT_ORDERINFO_H
