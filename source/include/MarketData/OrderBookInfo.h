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
public:
    static HrPointerList<T>               *m_itemsPool;
    static HashTable<T>                   *m_hashTable;
private:
    HrPointerListLite<T>                  *m_sellQuoteList;
    HrPointerListLite<T>                  *m_buyQuoteList;

    OrderedListManager<HrPointerListLite, HrLinkedPointer, T>   *m_sellQuoteManager;
    OrderedListManager<HrPointerListLite, HrLinkedPointer, T>   *m_buyQuoteManager;

    int                                 m_rptSeq;
    UINT32                              m_sessionInt;
    MDEntryQueue                       *m_entryInfo;
    int                                 m_savedRptSeq;
    int                                 m_snapshotProcessedCount;
    MarketSymbolInfo<OrderBookInfo<T>>  *m_symbolInfo;
    SizedArray                          *m_tradingSession;
    bool                                m_shouldProcessSnapshot;
#ifdef TEST
    char                                m_paddingBytes[7];
#else
    char                                m_paddingBytes[7];
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

    inline void ReleaseEntryQue() {
        if(this->m_entryInfo != 0) {
            for(int i = 0; i <= this->m_entryInfo->MaxIndex(); i++) {
                if(this->m_entryInfo->Entries()[i] != 0) {
                    ((T *) this->m_entryInfo->Entries()[i])->Clear();
                }
            }
            this->m_entryInfo->Reset();
            MDEntryQueue::Pool->FreeItemUnsafe(this->m_entryInfo->Pointer);
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

    inline void Clear(HrPointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            T *data = node->Data();
            this->FreePointer(data, list);
            data->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void DebugCheckHashTable() { }
    inline void Clear() {
        Clear(this->m_sellQuoteList);
        Clear(this->m_buyQuoteList);
        this->m_buyQuoteManager->ClearPointers();
        this->m_sellQuoteManager->ClearPointers();
        this->ClearEntries();
        this->m_rptSeq = 0;
        this->m_savedRptSeq = 0;
        this->m_shouldProcessSnapshot = false;
        this->m_snapshotProcessedCount = 0;
    }

    inline void MinPriceIncrement(Decimal *price) {
        this->m_buyQuoteManager->MinPriceIncrement(price->Mantissa);
        this->m_buyQuoteManager->Precision(- price->Exponent);

        this->m_sellQuoteManager->MinPriceIncrement(price->Mantissa);
        this->m_sellQuoteManager->Precision(- price->Exponent);
    }

    inline HrLinkedPointer<T>* InsertBuyQuote(Decimal *price) {
        return this->m_buyQuoteManager->InsertDescending(price);
    }
    inline HrLinkedPointer<T>* InsertSellQuote(Decimal *price) {
        return this->m_sellQuoteManager->InsertAscending(price);
    }
    inline HrLinkedPointer<T>* GetPointer(T *info, HrPointerListLite<T> *list) {
        return OrderBookInfo<T>::m_hashTable->GetPointer(list, info->MDEntryID);
    }
    inline void FreePointer(HrLinkedPointer<T> *ptr) {
        OrderBookInfo<T>::m_hashTable->RemovePointer(ptr);
    }
    inline void FreePointer(T *data, HrPointerListLite<T> *list) {
        OrderBookInfo<T>::m_hashTable->Remove(list, data->MDEntryID);
    }
    inline void AddPointer(HrLinkedPointer<T> *ptr, HrPointerListLite<T> *list, T *info) {
        OrderBookInfo<T>::m_hashTable->Add(ptr, list, info->MDEntryID);
    }
    inline HrLinkedPointer<T>* GetQuote(HrPointerListLite<T> *list, T *info) {
        HrLinkedPointer<T> *ptr = this->GetPointer(info, list);
        if(ptr != 0)
            return ptr;
        // such thing could happen because of some packet lost
        // so please do not return null :)
        ptr = list->Add(info);
        this->AddPointer(ptr, list, info);
        return ptr;
    }

    inline void DebugRemoveQuoteNoClear(HrPointerListLite<T> *list, T *info) {
        HrLinkedPointer<T> *ptr = this->GetPointer(info, list);
        if(ptr == 0) {
            // such thing could happen because of some packet lost
            // so please do not return null :)
            //TODO remove debug
            printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
            return;
        }
        list->Remove(ptr);
        this->FreePointer(ptr);
    }

    __attribute__((noinline))
    void OnQuoteNotFound(T *info) {
        // such thing could happen because of some packet lost
        // so please do not return null :)
        //TODO remove debug
        printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
        return;
    }

    inline void RemoveQuote(OrderedListManager<HrPointerListLite, HrLinkedPointer, T> *manager, T *info) {
        HrLinkedPointer<T> *ptr = this->GetPointer(info, manager->m_list);
        if(ptr == 0) {
            this->OnQuoteNotFound(info);
            return;
        }
        ptr->Data()->Clear();
        manager->OnPointerRemove(ptr);
        manager->m_list->Remove(ptr);
        this->FreePointer(ptr);
        info->Clear();
    }

    inline void RemoveBuyQuote(T *info) {
        RemoveQuote(this->m_buyQuoteManager, info);
    }

    inline void RemoveSellQuote(T *info) {
        RemoveQuote(this->m_sellQuoteManager, info);
    }

    inline void ChangeQuote(HrPointerListLite<T> *list, T *info) {
        HrLinkedPointer<T> *ptr = this->GetPointer(info, list);
        if(ptr != 0) {
            ptr->Data()->Clear();
            ptr->Data(info);
            return;
        }
        this->OnQuoteNotFound(info);
        return;
    }

    inline void ChangeBuyQuote(T *info) {
        this->ChangeQuote(this->m_buyQuoteList, info);
    }

    inline void ChangeSellQuote(T *info) {
        this->ChangeQuote(this->m_sellQuoteList, info);
    }

    inline void Remove(T *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cRemoveObr);
        ProgramStatistics::Total->Inc(Counters::cRemoveObr);
#endif
        UINT64 buy = info->MDEntryType[0] == mdetBuyQuote;
        OrderedListManager<HrPointerListLite, HrLinkedPointer, T> *manager =
                (OrderedListManager<HrPointerListLite, HrLinkedPointer, T>*)(
                        ((0 - buy) & (UINT64)this->m_buyQuoteManager) +
                        ((buy - 1) & (UINT64)this->m_sellQuoteManager)
                );
        this->RemoveQuote(manager, info);
    }

    inline void Change(T *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cChangeObr);
        ProgramStatistics::Total->Inc(Counters::cChangeObr);
#endif
        UINT64 buy = info->MDEntryType[0] == mdetBuyQuote;
        HrPointerListLite<T> *list =
                (HrPointerListLite<T>*)(
                        ((0 - buy) & (UINT64)this->m_buyQuoteList) +
                        ((buy - 1) & (UINT64)this->m_sellQuoteList)
                );
        this->ChangeQuote(list, info);
    }

    inline HrLinkedPointer<T>* Add(T *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cAddObr);
        ProgramStatistics::Total->Inc(Counters::cAddObr);
#endif
        HrLinkedPointer<T> *ptr;
        HrPointerListLite<T> *owner;
        if(info->MDEntryType[0] == mdetBuyQuote) {
            ptr = InsertBuyQuote(&(info->MDEntryPx));
            owner = this->m_buyQuoteList;
        }
        else {
            ptr = InsertSellQuote(&(info->MDEntryPx));
            owner = this->m_sellQuoteList;
        }
        AddPointer(ptr, owner, info);
        ptr->Data(info);
        return ptr;
    }

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void ObtainEntriesQueue() {
        if(this->m_entryInfo == 0)
            this->m_entryInfo = MDEntryQueue::Pool->NewItem();
    }

    __attribute__((noinline))
    void PushMessageToQueue(T *info) {
        this->ObtainEntriesQueue();
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info, info->RptSeq);
    }

    inline void ForceProcessMessage(T *info) {
        if(info->MDUpdateAction == mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == mduaDelete)
            this->Remove(info);
        else
            this->Change(info);
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
        this->m_buyQuoteManager->ClearPointers();
        this->m_sellQuoteManager->ClearPointers();
    }

    inline void ProcessNullSnapshot() {
        this->Clear(this->BuyQuotes());
        this->Clear(this->SellQuotes());
        this->m_buyQuoteManager->ClearPointers();
        this->m_sellQuoteManager->ClearPointers();
    }

    inline void ProcessSnapshotMessage(T *info) {
        this->Add(info);
    }

    __attribute__((noinline))
    bool ProcessQueueMessages() {
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
template <typename T> HashTable<T>* OrderBookInfo<T>::m_hashTable = 0;

template <typename T> OrderBookInfo<T>::OrderBookInfo() :
        m_sellQuoteManager(0),
        m_buyQuoteManager(0),
        m_sellQuoteList(0),
        m_buyQuoteList(0),
        m_entryInfo(0),
        m_shouldProcessSnapshot(false),
        m_rptSeq(0),
        m_savedRptSeq(0),
        m_symbolInfo(0),
        m_tradingSession(0),
        m_sessionInt(0),
        m_snapshotProcessedCount(0)
    {
    if(OrderBookInfo::m_itemsPool == 0)
        OrderBookInfo::m_itemsPool = new HrPointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);
    if(OrderBookInfo::m_hashTable == 0)
        OrderBookInfo::m_hashTable = new HashTable<T>();

    this->m_sellQuoteList = new HrPointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
    this->m_buyQuoteList = new HrPointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
    this->m_sellQuoteManager = new OrderedListManager<HrPointerListLite, HrLinkedPointer, T>(this->m_sellQuoteList, SortType::stAscending);
    this->m_buyQuoteManager = new OrderedListManager<HrPointerListLite, HrLinkedPointer, T>(this->m_buyQuoteList, SortType::stDescending);
}

#endif //HFT_ROBOT_ORDERINFO_H
