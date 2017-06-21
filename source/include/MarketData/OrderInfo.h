//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_ORDERINFO_H
#define HFT_ROBOT_ORDERINFO_H

#include "../Lib/StringIdComparer.h"
#include "../Lib/HrPointerList.h"
#include "../Lib/HashTable.h"
#include "../Fast/FastTypes.h"
#include "MDEntryQueue.h"
#include "QuoteInfo.h"
#include "../Managers/DebugInfoManager.h"
#include "../ProgramStatistics.h"
#include "OrderedListManager.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class OrderInfo {
    static HrPointerList<T>               *m_itemsPool;
    static HashTable<T>                   *m_hashTable;

    HrPointerListLite<T>                  *m_sellQuoteList;
    HrPointerListLite<T>                  *m_buyQuoteList;

    UINT32                              m_sessionInt;
    int                                 m_rptSeq;

    OrderedListManager<HrPointerListLite, HrLinkedPointer, T>   *m_buyQuoteManager;
    OrderedListManager<HrPointerListLite, HrLinkedPointer, T>   *m_sellQuoteManager;

    MDEntryQueue                       *m_entryInfo;
    MarketSymbolInfo<OrderInfo<T>>      *m_symbolInfo;
    SizedArray                          *m_tradingSession;
    int                                 m_savedRptSeq;
    int                                 m_snapshotProcessedCount;

    bool                                m_shouldProcessSnapshot;
#ifdef TEST
    char                                m_paddingBytes[7];
#else
    char                                m_paddingBytes[7];
#endif

public:
    OrderInfo();
    ~OrderInfo() {
        ReleaseEntryQue();
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
        delete this->m_buyQuoteManager;
        delete this->m_sellQuoteManager;
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
    inline MarketSymbolInfo<OrderInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<OrderInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline int SavedRptSeq() { return this->m_savedRptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline bool HasEntries() { return this->m_entryInfo == 0? false: this->m_entryInfo->HasEntries(); }
    inline void ClearEntries() { this->ReleaseEntryQue(); }
    inline MDEntryQueue* EntriesQueue() { return this->m_entryInfo; }

    inline HrPointerListLite<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline HrPointerListLite<T>* BuyQuotes() { return this->m_buyQuoteList; }

    inline void DebugCheckHashTable(HrPointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            T *data = node->Data();
            HrLinkedPointer<T> *ptr = OrderInfo<T>::m_hashTable->GetPointer(list, data->MDEntryID, data->MDEntryIDLength);
            if(ptr == 0) {
                printf("error: there is no HashTableItem for %s\n", DebugInfoManager::Default->GetString(data->MDEntryID, data->MDEntryIDLength, 0));
                DebugInfoManager::Default->PrintQuotes("BuyQuotes", list);
                throw;
            }
            if(node == list->End())
                break;
            node = node->Next();
        }
    }

    inline void Clear(HrPointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            T *data = node->Data();
            FreePointer(data, list);
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
    inline HrLinkedPointer<T>* RemovePointer(T *info, HrPointerListLite<T> *list) {
        return static_cast<HrLinkedPointer<T>*>(OrderInfo<T>::m_hashTable->RemovePointer(list, info->MDEntryID, info->MDEntryIDLength));
    }
    inline HrLinkedPointer<T>* GetPointer(T *info, HrPointerListLite<T> *list) {
        return OrderInfo<T>::m_hashTable->GetPointer(list, info->MDEntryID, info->MDEntryIDLength);
    }
    inline void FreePointer(HrLinkedPointer<T> *hashItem) {
        OrderInfo<T>::m_hashTable->RemovePointer(hashItem);
    }
    inline void FreePointer(T *data, HrPointerListLite<T> *list) {
        OrderInfo<T>::m_hashTable->Remove(list, data->MDEntryID, data->MDEntryIDLength);
    }
    inline void AddPointer(HrLinkedPointer<T> *ptr, HrPointerListLite<T> *list, T *info) {
        OrderInfo<T>::m_hashTable->Add(ptr, list, info->MDEntryID, info->MDEntryIDLength);
    }
    inline HrLinkedPointer<T>* GetQuote(HrPointerListLite<T> *list, T *info) {
        HrLinkedPointer<T> *res = this->GetPointer(info);
        if(res != 0) return res;
        // such thing could happen because of some packet lost
        // so please do not return null :)
        res = list->Add(info);
        this->AddPointer(res, info, list);
        return res;
    }

    __attribute__((noinline))
    void OnQuoteNotFound(T *info) {
        // such thing could happen because of some packet lost
        // so please do not return null :)
        //TODO remove debug
        info->MDEntryID[info->MDEntryIDLength] = '\0';
        printf("ERROR: %s entry not found\n", info->MDEntryID);
        return;
    }

    inline void RemoveQuote(OrderedListManager<HrPointerListLite, HrLinkedPointer, T> *manager, T *info) {
        HrLinkedPointer<T> *node = this->RemovePointer(info, manager->m_list);
        if(node == 0) {
            this->OnQuoteNotFound(info);
            return;
        }
        node->Data()->Clear();
        manager->m_list->Remove(node);
        manager->OnPointerRemove(node);
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
    inline void Remove(T *info) {
        /*
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cRemoveOlr);
        ProgramStatistics::Total->Inc(Counters::cRemoveOlr);
#endif*/
        UINT64 buy = info->MDEntryType[0] == mdetBuyQuote;
        OrderedListManager<HrPointerListLite, HrLinkedPointer, T> *manager =
                (OrderedListManager<HrPointerListLite, HrLinkedPointer, T>*)(
                        ((0 - buy) & (UINT64)this->m_buyQuoteManager) +
                        ((buy - 1) & (UINT64)this->m_sellQuoteManager)
                );
        this->RemoveQuote(manager, info);
    }

    inline void Change(T *info) {
/*#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cChangeOlr);
        ProgramStatistics::Total->Inc(Counters::cChangeOlr);
#endif*/
        UINT64 buy = info->MDEntryType[0] == mdetBuyQuote;
        HrPointerListLite<T> *list =
                (HrPointerListLite<T>*)(
                        ((0 - buy) & (UINT64)this->m_buyQuoteList) +
                        ((buy - 1) & (UINT64)this->m_sellQuoteList)
                );
        this->ChangeQuote(list, info);
    }

    void DebugCheckActualityBuyQuote() {
        HrLinkedPointer<T> *node = this->m_buyQuoteList->Start();
        while(node != this->m_buyQuoteList->End()) {
            if(node->Value() < node->Next()->Value())
                throw;
            node = node->Next();
        }
    }

    void DebugCheckActualitySellQuote() {
        HrLinkedPointer<T> *node = this->m_sellQuoteList->Start();
        while(node != this->m_sellQuoteList->End()) {
            if(node->Value() > node->Next()->Value())
                throw;
            node = node->Next();
        }
    }

    inline HrLinkedPointer<T>* Add(T *info) {
/*#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cAddOlr);
        ProgramStatistics::Total->Inc(Counters::cAddOlr);
#endif*/
        HrLinkedPointer<T> *ptr;
        HrPointerListLite<T> *owner;
        if(info->MDEntryType[0] == MDEntryType::mdetBuyQuote) {
            ptr = this->InsertBuyQuote(&(info->MDEntryPx));
            owner = this->m_buyQuoteList;
        }
        else {
            ptr = this->InsertSellQuote(&(info->MDEntryPx));
            owner = this->m_sellQuoteList;
        }
        this->AddPointer(ptr, owner, info);
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

    void PushMessageToQueue(T *info) {
        this->ObtainEntriesQueue();
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info, info->RptSeq);
    }

    inline void ForceProcessMessage(T *info) {
        //printf("op =  %d\n", info->MDUpdateAction);
        if(info->MDUpdateAction == MDUpdateAction::mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == MDUpdateAction::mduaDelete)
            this->Remove(info);
        else
            this->Change(info);
    }

    inline bool IsOutdatedMessage(T *info) {
        return info->RptSeq <= this->m_rptSeq;
    }

    inline void DebugCheckHashTable() {
        this->DebugCheckHashTable(this->m_buyQuoteList); // TODO remove debu
        this->DebugCheckHashTable(this->m_sellQuoteList);
    }

    __attribute__((noinline))
    bool OnProcessNonActualMessage(T *info) {
        if(this->IsOutdatedMessage(info))
            return false;
        //printf("current = %d   info = %d\n", this->m_rptSeq, info->RptSeq);
        this->PushMessageToQueue(info);
        return false;
    }

    inline bool ProcessIncrementalMessage(T *info) {
        if(!this->IsNextMessage(info))
            return OnProcessNonActualMessage(info);
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

template <typename T> HrPointerList<T>* OrderInfo<T>::m_itemsPool = 0;
template <typename T> HashTable<T>* OrderInfo<T>::m_hashTable = 0;

template <typename T> OrderInfo<T>::OrderInfo() :
        m_entryInfo(0),
        m_shouldProcessSnapshot(false),
        m_rptSeq(0),
        m_savedRptSeq(0),
        m_symbolInfo(0),
        m_sessionInt(0),
        m_snapshotProcessedCount(0)
    {
    if(OrderInfo::m_itemsPool == 0)
        OrderInfo::m_itemsPool = new HrPointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);
    if(OrderInfo::m_hashTable == 0)
        OrderInfo::m_hashTable = new HashTable<T>();

    this->m_sellQuoteList = new HrPointerListLite<T>(OrderInfo<T>::m_itemsPool);
    this->m_buyQuoteList = new HrPointerListLite<T>(OrderInfo<T>::m_itemsPool);

    this->m_sellQuoteManager = new OrderedListManager<HrPointerListLite, HrLinkedPointer, T>(this->m_sellQuoteList);
    this->m_buyQuoteManager = new OrderedListManager<HrPointerListLite, HrLinkedPointer, T>(this->m_buyQuoteList);

    this->m_tradingSession = new SizedArray();
}

#endif //HFT_ROBOT_ORDERINFO_H
