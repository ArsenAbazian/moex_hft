//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_TRADEINFO_H
#define HFT_ROBOT_TRADEINFO_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "MDEntryQueue.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class TradeInfo {
    static PointerList<T>               *m_itemsPool;

    PointerListLite<T>      *m_trades;
    MDEntryQueue      *m_entryInfo;

    bool                 m_used;
    bool                 m_shouldProcessSnapshot;
    int                  m_rptSeq;
    int                  m_savedRptSeq;
    MarketSymbolInfo<TradeInfo<T>>    *m_symbolInfo;
    SizedArray          *m_tradingSession;
    int                  m_snapshotProcessedCount;

public:
    TradeInfo();
    ~TradeInfo() {
        ReleaseEntryQue();
        delete this->m_trades;
    }

    inline void ReleaseEntryQue() {
        if(this->m_entryInfo != 0) {
            this->m_entryInfo->Reset();
            if(!this->m_entryInfo->IsCleared())
                throw; //TODO remove degbug
            MDEntryQueue::Pool->FreeItem(this->m_entryInfo->Pointer);
            int index = DebugInfoManager::Default->CheckIsFriedMDEntryQueryCleared();
            if(index != -1) {
                MDEntryQueue *queue = DebugInfoManager::Default->GetFirstMDEntryQueue();
                int entryIndex = DebugInfoManager::Default->GetFirstNonEmptyEntry();
                throw;
            }
        }
        this->m_entryInfo = 0;
    }
    inline void ResetSnasphotProcessed() { this->m_snapshotProcessedCount = 0; }
    inline void OnSnapshotProcessed() { this->m_snapshotProcessedCount++; }
    inline int SnapshotProcessedCount() { return this->m_snapshotProcessedCount; }
    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline SizedArray* Symbol() { return this->m_symbolInfo->Symbol(); }
    inline MarketSymbolInfo<TradeInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<TradeInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline int SavedRptSeq() { return this->m_savedRptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline bool HasEntries() { return this->m_entryInfo == 0? false: this->m_entryInfo->HasEntries(); }
    inline void ClearEntries() { this->ReleaseEntryQue(); }
    inline MDEntryQueue* EntriesQueue() { return this->m_entryInfo; }

    inline PointerListLite<T>* Trades() { return this->m_trades; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerListLite<T> *list) {
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
        Clear(this->m_trades);
        this->ClearEntries();
        this->m_rptSeq = 0;
        this->m_savedRptSeq = 0;
        this->m_shouldProcessSnapshot = false;
        this->m_snapshotProcessedCount = 0;
    }

    inline LinkedPointer<T>* AddTrade(T *item) {
        item->Used = true;
        return this->m_trades->Add(item);
    }

    inline LinkedPointer<T>* Add(T *info) {
        return this->AddTrade(info);
    }

    inline LinkedPointer<T>* GetTrade(PointerList<T> *list, T *info) {
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

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void ObtainEntriesQueue() {
        if(this->m_entryInfo == 0) {
            this->m_entryInfo = MDEntryQueue::Pool->NewItem();
            //TODO remove debug
            if(!this->m_entryInfo->IsCleared())
                throw;
            this->m_entryInfo->Owner(this);
        }
    }

    inline void PushMessageToQueue(T *info) {
        this->ObtainEntriesQueue();
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info, info->RptSeq);
    }

    inline void ForceProcessMessage(T *info) {
        this->Add(info);
    }

    inline bool ProcessIncrementalMessage(T *info) {
        //TODO remove debug
        if(this->m_entryInfo != 0 && !this->m_entryInfo->HasEntries())
            throw;
        if(!this->IsNextMessage(info)) {
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
        this->Trades()->Clear();
    }

    inline void ProcessSnapshotMessage(T *info) {
        this->ForceProcessMessage(info);
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
        }
        for(int index = startIndex; index <= maxIndex; index++) {
            if((*entry) == 0)
                return false;
            ForceProcessMessage(*entry);
            this->m_rptSeq = (*entry)->RptSeq;
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

template <typename T> PointerList<T>* TradeInfo<T>::m_itemsPool = 0;

template <typename T> TradeInfo<T>::TradeInfo(){
    if(TradeInfo::m_itemsPool == 0)
        TradeInfo::m_itemsPool = new PointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);

    this->m_entryInfo = 0;
    this->m_trades = new PointerListLite<T>(TradeInfo::m_itemsPool);
    this->m_tradingSession = new SizedArray();
    this->m_shouldProcessSnapshot = false;
    this->m_rptSeq = 0;
    this->m_savedRptSeq = 0;
    this->m_snapshotProcessedCount = 0;
}

#endif //HFT_ROBOT_TRADEINFO_H
