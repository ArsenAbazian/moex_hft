//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_ORDERBOOKINFO_H
#define HFT_ROBOT_ORDERBOOKINFO_H

#include "../Lib/StringIdComparer.h"
#include "../Fast/FastTypes.h"
#include "../Lib/HrPointerList.h"
#include "../Lib/HashTable.h"
#include "MDEntryQueue.h"
#include "QuoteInfo.h"
#include "../Managers/DebugInfoManager.h"
#include "../ProgramStatistics.h"
#include "OrderedListManager.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class OrderBookInfo {
    static HrPointerList<T>               *m_itemsPool;

    OrderedListManager<HrPointerListLite, HrLinkedPointer, T>   *m_sellQuoteManager;
    OrderedListManager<HrPointerListLite, HrLinkedPointer, T>   *m_buyQuoteManager;
    HrPointerListLite<T>                  *m_sellQuoteList;
    HrPointerListLite<T>                  *m_buyQuoteList;

    MDEntryQueue                       *m_entryInfo;

    bool                                m_used;
    bool                                m_shouldProcessSnapshot;
    int                                 m_rptSeq;
    int                                 m_savedRptSeq;
    MarketSymbolInfo<OrderBookInfo<T>>  *m_symbolInfo;
    SizedArray                          *m_tradingSession;
    UINT32                              m_sessionInt;

    int                                 m_snapshotProcessedCount;
#ifdef TEST
    ListType                            m_listMode;
#endif
public:
    OrderBookInfo();
    ~OrderBookInfo() {
        ReleaseEntryQue();
        delete this->m_sellQuoteManager;
        delete this->m_buyQuoteManager;
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

#ifdef  TEST
    inline ListType ListMode() const { return this->m_listMode; }
    inline void ListMode(ListType listType) { this->m_listMode = listType; }
    inline void SetDebugLevel(int level) {
        this->m_buyQuoteManager->SetDebugLevel(level);
        this->m_sellQuoteManager->SetDebugLevel(level);
    }
#endif

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
    inline MarketSymbolInfo<OrderBookInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<OrderBookInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline int SavedRptSeq() { return this->m_savedRptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline bool HasEntries() { return this->m_entryInfo == 0? false: this->m_entryInfo->HasEntries(); }
    inline void ClearEntries() { this->ReleaseEntryQue(); }
    inline MDEntryQueue* EntriesQueue() { return this->m_entryInfo; }

    inline HrPointerListLite<T>* SellQuotes() const { return this->m_sellQuoteList; }
    inline HrPointerListLite<T>* BuyQuotes() const { return this->m_buyQuoteList; }
    inline OrderedListManager<HrPointerListLite, HrLinkedPointer, T> *SellQuoteManager() const { return this->m_sellQuoteManager; }
    inline OrderedListManager<HrPointerListLite, HrLinkedPointer, T> *BuyQuoteManager() const { return this->m_buyQuoteManager; }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(HrPointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            T *data = node->Data();
            this->FreePointer(data);
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
        this->ClearEntries();
        this->m_rptSeq = 0;
        this->m_savedRptSeq = 0;
        this->m_shouldProcessSnapshot = false;
        this->m_snapshotProcessedCount = 0;
    }

    inline HrLinkedPointer<T>* InsertBuyQuote(Decimal *price) {
#ifdef TEST
        if(this->m_listMode == ListType::ltSimple)
            return this->m_buyQuoteManager->SimpleInsertBeforeDescending(price);
        return this->m_buyQuoteManager->HrInsertBeforeDescending(price);
#else
        return this->m_buyQuoteManager->HrInsertBeforeDescending(price);
#endif
    }
    inline HrLinkedPointer<T>* InsertSellQuote(Decimal *price) {
#ifdef TEST
        if(this->m_listMode == ListType::ltSimple)
            return this->m_sellQuoteManager->SimpleInsertBeforeAscending(price);
        return this->m_sellQuoteManager->HrInsertBeforeAscending(price);
#else
        return this->m_sellQuoteManager->HrInsertBeforeAscending(price);
#endif
    }
    inline LinkedPointer<HashTableItemInfo>* GetPointer(T *info) {
        return HashTable::Default->GetPointer(this, info->MDEntryID);
    }
    inline void FreePointer(LinkedPointer<HashTableItemInfo> *hashItem) {
        HashTable::Default->RemovePointer(hashItem);
    }
    inline void FreePointer(T *data) {
        HashTable::Default->Remove(this, data->MDEntryID);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(T *info) {
        return HashTable::Default->Add(this, 0, info->MDEntryID);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(HrPointerListLite<T> *list, T *info) {
        LinkedPointer<T> *item = list->Add(info);
        return HashTable::Default->Add(this, item, info->MDEntryID);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(HrLinkedPointer<T> *ptr, T *info) {
        return HashTable::Default->Add(this, ptr, info->MDEntryID);
    }
    inline HrLinkedPointer<T>* GetQuote(HrPointerListLite<T> *list, T *info) {
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        if(hashItem == 0) {
            // such thing could happen because of some packet lost
            // so please do not return null :)
            HrLinkedPointer<T> *res = list->Add(info);
            hashItem = AddPointer(list, info);
            return res;
        }
        return static_cast<HrLinkedPointer<T>*>(hashItem->Data()->m_object);
    }

    inline void RemoveQuote(HrPointerListLite<T> *list, T *info) {
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        if(hashItem == 0) {
            // such thing could happen because of some packet lost
            // so please do not return null :)
            //TODO remove debug
            printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
            return;
        }
        HrLinkedPointer<T> *node = static_cast<HrLinkedPointer<T>*>(hashItem->Data()->m_object);
        T *data = node->Data();
        data->Clear();
        list->Remove(node);
        this->FreePointer(hashItem);
    }

    inline void RemoveBuyQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Remove BuyQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        RemoveQuote(this->m_buyQuoteList, info);
    }

    inline void RemoveSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Remove SellQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        RemoveQuote(this->m_sellQuoteList, info);
    }

    inline void ChangeBuyQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Change BuyQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);

        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        HrLinkedPointer<T> *ptr;
        if(hashItem != 0) {
            ptr = static_cast<HrLinkedPointer<T>*>(hashItem->Data()->m_object);
            this->m_buyQuoteList->Remove(ptr);
            ptr->Data()->Clear();

            info->Used = true;
            ptr = InsertBuyQuote(&(info->MDEntryPx));
            ptr->Data(info);
            HashTableItemInfo *h = hashItem->Data();
            h->m_object = ptr;
            h->m_intId = info->MDEntryID;
            return;
        }
        //TODO remove debug
        printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
        info->Used = true;
        ptr = InsertBuyQuote(&(info->MDEntryPx));
        hashItem = AddPointer(ptr, info);
    }

    inline void ChangeSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Change SellQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        HrLinkedPointer<T> *ptr;
        if(hashItem != 0) {
            ptr = static_cast<HrLinkedPointer<T>*>(hashItem->Data()->m_object);
            this->m_sellQuoteList->Remove(ptr);
            ptr->Data()->Clear();

            info->Used = true;
            ptr = InsertSellQuote(&(info->MDEntryPx));
            ptr->Data(info);
            HashTableItemInfo *h = hashItem->Data();
            h->m_object = ptr;
            h->m_intId = info->MDEntryID;
            return;
        }
        //TODO remove debug
        printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
        info->Used = true;
        ptr = InsertSellQuote(&(info->MDEntryPx));
        hashItem = AddPointer(ptr, info);
    }

    inline HrLinkedPointer<T>* AddBuyQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Add BuyQuote", item->MDEntryID, &(item->MDEntryPx), item->MDEntrySize);
        item->Used = true;
        HrLinkedPointer<T> *ptr = InsertBuyQuote(&(item->MDEntryPx));
        AddPointer(ptr, item);
        ptr->Data(item);
        return ptr;
    }

    inline HrLinkedPointer<T>* AddSellQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Add SellQuote", item->MDEntryID, &(item->MDEntryPx), item->MDEntrySize);
        item->Used = true;
        HrLinkedPointer<T> *ptr = InsertSellQuote(&(item->MDEntryPx));
        AddPointer(ptr, item);
        ptr->Data(item);
        return ptr;
    }

    inline void Remove(T *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cRemoveObr);
        ProgramStatistics::Total->Inc(Counters::cRemoveObr);
#endif
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->RemoveBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            this->RemoveSellQuote(info);
    }

    inline void Change(T *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cChangeObr);
        ProgramStatistics::Total->Inc(Counters::cChangeObr);
#endif
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->ChangeBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            this->ChangeSellQuote(info);
    }

    inline HrLinkedPointer<T>* Add(T *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cAddObr);
        ProgramStatistics::Total->Inc(Counters::cAddObr);
#endif
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
    }

    inline void ProcessNullSnapshot() {
        this->Clear(this->BuyQuotes());
        this->Clear(this->SellQuotes());
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

template <typename T> HrPointerList<T>* OrderBookInfo<T>::m_itemsPool = 0;

template <typename T> OrderBookInfo<T>::OrderBookInfo() :
        m_sellQuoteList(0),
        m_buyQuoteList(0),
        m_buyQuoteManager(0),
        m_sellQuoteManager(0),
        m_tradingSession(0),
        m_shouldProcessSnapshot(false),
        m_rptSeq(0),
        m_savedRptSeq(0),
        m_snapshotProcessedCount(0),
        m_used(0),
        m_symbolInfo(0),
        m_entryInfo(0),
        m_sessionInt(0),
#ifdef TEST
        m_listMode(ListType::ltSkipList),
#endif
        m_entryInfo(0) {
    if(OrderBookInfo::m_itemsPool == 0)
        OrderBookInfo::m_itemsPool = new HrPointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);

    HashTable::SafeCreateDefault();

    this->m_sellQuoteList = new HrPointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
    this->m_buyQuoteList = new HrPointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
    this->m_sellQuoteManager = new OrderedListManager<HrPointerListLite, HrLinkedPointer, T>(this->m_sellQuoteList);
    this->m_buyQuoteManager = new OrderedListManager<HrPointerListLite, HrLinkedPointer, T>(this->m_buyQuoteList);
}

#endif //HFT_ROBOT_ORDERINFO_H
