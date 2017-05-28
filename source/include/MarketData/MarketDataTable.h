//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include "../Managers/DebugInfoManager.h"
#include "../Lib/StringIdComparer.h"
#include "../Fast/FastTypes.h"
#include "MDEntryQueue.h"
#include "MarketSymbolInfo.h"
#include "SymbolManager.h"

template <template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO> class MarketDataTable {
    MarketSymbolInfo<TABLEITEM<ITEMINFO>>       **m_symbols;
    int                                         m_symbolsCount;
    int                                         m_symbolsMaxCount;
    TABLEITEM<ITEMINFO>                         *m_snapshotItem;
    MarketSymbolInfo<TABLEITEM<ITEMINFO>>       *m_snapshotSymbol;
    int                                         *m_ownerQueueItemsCount;
    int                                         *m_ownerSymbolsToRecvSnapshot;
    bool                                        *m_ownerTableInSnapshotMode;
    int                                         m_snapshotItemRptSeq;
    int                                         m_queueItemsCount;
    int                                         m_symbolsToRecvSnapshot;
    bool                                        m_allSessionsRecvSnapshot;
    bool                                        m_snapshotMode;
    short                                       m_paddingBytes;
public:
    inline void InitSymbols(int count) {
        this->m_symbolsMaxCount = count;
        this->m_symbols = new MarketSymbolInfo<TABLEITEM<ITEMINFO>>*[count];
        for(int i = 0; i < this->m_symbolsMaxCount; i++)
            this->m_symbols[i] = new MarketSymbolInfo<TABLEITEM<ITEMINFO>>();
    }
    inline void InitSymbols(int symbolsCount, int sessionsCount) {
        this->InitSymbols(symbolsCount);
        for(int i = 0; i < symbolsCount; i++) {
            this->m_symbols[i]->InitSessions(sessionsCount);
        }
    }
    MarketDataTable() :
            m_symbols(0),
            m_symbolsCount(0),
            m_symbolsMaxCount(0),
            m_snapshotItem(0),
            m_snapshotSymbol(0),
            m_snapshotItemRptSeq(0),
            m_queueItemsCount(0),
            m_symbolsToRecvSnapshot(0),
            m_allSessionsRecvSnapshot(false),
            m_snapshotMode(false),
            m_ownerQueueItemsCount(0),
            m_ownerSymbolsToRecvSnapshot(0),
            m_ownerTableInSnapshotMode(0),
            m_paddingBytes(0) {
        this->m_ownerSymbolsToRecvSnapshot = new int;
        this->m_ownerQueueItemsCount = new int;
        this->m_ownerTableInSnapshotMode = new bool;
        *(this->m_ownerQueueItemsCount) = 0;
        *(this->m_ownerSymbolsToRecvSnapshot) = 0;
        *(this->m_ownerTableInSnapshotMode) = false;
    }
    ~MarketDataTable() {
        this->Release();
    }
    void SetOwnerParams(int *ownerQueueItemsCount, int *ownerSymbolsToRecvSnapshot, bool *ownerTableInSnapshotMode) {
        this->m_ownerQueueItemsCount = ownerQueueItemsCount;
        this->m_ownerSymbolsToRecvSnapshot = ownerSymbolsToRecvSnapshot;
        this->m_ownerTableInSnapshotMode = ownerTableInSnapshotMode;
    }
    inline void ObtainSnapshotItem(INFO *info) {
        UINT32 tradingId = *((UINT32*)info->TradingSessionID);
        this->m_snapshotItem = this->GetItem(info->Symbol, info->SymbolLength, tradingId);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
    }
    inline void ObtainSnapshotItem(int symbolIndex, FortsSnapshotInfo *info) {
        this->m_snapshotItem = this->Symbol(symbolIndex)->Session(0);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
    }
    inline void ObtainSnapshotItem(FortsSnapshotInfo *info) {
        this->m_snapshotItem = this->GetItemBySecurityId(info->SecurityID, 0);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
    }
    inline void ObtainSnapshotItemForts(INFO *info) {
        this->m_snapshotItem = this->GetItemBySecurityId(info->SecurityID, 0);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
    }

    inline void ObtainSnapshotItem(int symbolIndex, AstsSnapshotInfo *info) {
        UINT32 tradingId = *((UINT32*)info->TradingSessionID);
        this->m_snapshotItem = this->GetItem(symbolIndex, tradingId);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
    }
    inline void ObtainSnapshotItem(AstsSnapshotInfo *info) {
        UINT32 tradingId = *((UINT32*)info->TradingSessionID);
        this->m_snapshotItem = this->GetCachedItem(info->Symbol, info->SymbolLength, tradingId);
        if(this->m_snapshotItem == 0)
            this->m_snapshotItem = this->GetItem(info->Symbol, info->SymbolLength, tradingId);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
    }
    inline void DecSymbolsToRecvSnapshotCount() {
        this->m_symbolsToRecvSnapshot--;
        *(this->m_ownerSymbolsToRecvSnapshot) = this->m_symbolsToRecvSnapshot;
    }
    inline void IncSymbolsToRecvSnapshotCount() {
        this->m_symbolsToRecvSnapshot++;
        *(this->m_ownerSymbolsToRecvSnapshot) = this->m_symbolsToRecvSnapshot;
    }
    TABLEITEM<ITEMINFO> *GetItemWithEntryInfo(MDEntryQueue *entry) {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for(int j = 0; j < this->Symbol(i)->SessionCount(); j++) {
                if(this->Symbol(i)->Session(j)->EntriesQueue() == entry)
                    return this->Symbol(i)->Session(j);
            }
        }
        return 0;
    }
    int DebugCalcEntryQueCount(MDEntryQueue *entry) {
        int count = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for(int j = 0; j < this->Symbol(i)->SessionCount(); j++) {
                if(this->Symbol(i)->Session(j)->EntriesQueue() == entry)
                    count++;
            }
        }
        return count;
    }
    bool DebugCheckQueItemsActuality() {
        if(this->DebugCalcActualQueueEntriesCount() != this->m_queueItemsCount)
            return false;
        return true;
    }
    inline bool ProcessIncremental(ITEMINFO *info, TABLEITEM<ITEMINFO> *tableItem) {
        bool prevHasEntries = tableItem->HasEntries();
        bool res = tableItem->ProcessIncrementalMessage(info);
        bool hasEntries = tableItem->HasEntries();
        if(hasEntries) {
            if(!prevHasEntries) {
                this->m_queueItemsCount++;
                *(this->m_ownerQueueItemsCount) = this->m_queueItemsCount;
            }
        }
        else {
            if(prevHasEntries) {
                this->m_queueItemsCount--;
                *(this->m_ownerQueueItemsCount) = this->m_queueItemsCount;
            }
            if(tableItem->ShouldProcessSnapshot()) {
                MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = tableItem->SymbolInfo();
                bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
                tableItem->DecSessionsToRecvSnapshotCount();
                if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
                    this->DecSymbolsToRecvSnapshotCount();
            }
        }
        return res;
    }

    inline bool ProcessIncremental(ITEMINFO *info, int index) {
        TABLEITEM<ITEMINFO> *tableItem = GetItemByIndex(index);
        return ProcessIncremental(info, tableItem);
    }
    inline bool ProcessIncremental(ITEMINFO *info, int index, UINT32 sessionId) {
        TABLEITEM<ITEMINFO> *tableItem = GetItem(index, sessionId);
        return ProcessIncremental(info, tableItem);
    }
    inline bool ShouldProcessSnapshot(INFO *info) {
        if(!this->m_snapshotItem->HasEntries())
            return this->m_snapshotItem->RptSeq() < info->RptSeq;
        return this->m_snapshotItem->EntriesQueue()->StartRptSeq() <= info->RptSeq;
    }
    inline bool CheckProcessIfSessionInActualState(INFO *info) {
        if(this->m_snapshotItem->HasEntries())
            return false;
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = this->m_snapshotItem->SymbolInfo();
        bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
        if(allItemsRecvSnapshot)
            return true;
        if(this->m_snapshotItem->RptSeq() != info->RptSeq)
            return false;
        this->m_snapshotItem->ProcessActualSnapshotState();
        if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
            this->DecSymbolsToRecvSnapshotCount();
        this->m_snapshotItem = 0;
        return true;
    }
    inline bool IsNullSnapshot(INFO *info) {
        return info->RptSeq == 0 && info->LastMsgSeqNumProcessed == 0;
    }
    inline bool CheckProcessNullSnapshot(INFO *info) {
        if(IsNullSnapshot(info)) {
            bool allItemsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
            bool prevHasEntries = this->m_snapshotItem->HasEntries();
            this->m_snapshotItem->ClearEntries();
            this->m_snapshotItem->DecSessionsToRecvSnapshotCount();
            if(prevHasEntries && !this->m_snapshotItem->HasEntries()) {
                this->m_queueItemsCount--;
                *(this->m_ownerQueueItemsCount) = this->m_queueItemsCount;
            }
            if(!allItemsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot())
                this->DecSymbolsToRecvSnapshotCount();
            this->m_snapshotItem->ProcessNullSnapshot();
            this->m_snapshotItem = 0;
            return true;
        }
        return false;
    }

    inline bool ApplyQuickSnapshot(AstsSnapshotInfo *info) {
        if(this->CheckProcessIfSessionInActualState(info->RptSeq)) {
            return true;
        }
        if(this->CheckProcessNullSnapshot(info->RptSeq, info->LastMsgSeqNumProcessed)) {
            return true;
        }
        if(!this->ShouldProcessSnapshot(info->RptSeq)) {
            return true;
        }
        return false;
    }

    inline bool ApplyQuickSnapshot(FortsSnapshotInfo *info) {
        if(this->CheckProcessIfSessionInActualState(info->RptSeq)) {
            //TODO remove debug
            //printf("  actual state\n");
            return true;
        }
        if(this->CheckProcessNullSnapshot(info->RptSeq, info->LastMsgSeqNumProcessed)) {
            //TODO remove debug
            //printf("  null snap\n");
            return true;
        }
        if(!this->ShouldProcessSnapshot(info->RptSeq)) {
            //TODO remove debug
            //printf("  should not process\n");
            return true;
        }
        return false;
    }

    inline bool ShouldProcessSnapshot(int rptSeq) {
        if(!this->m_snapshotItem->HasEntries()) {
            //TODO remove debug
            bool res = this->m_snapshotItem->RptSeq() < rptSeq;
            /*
            if(!res) {
                printf("  %s - %s  skip snapshot : item->RptSeq = %d >= snap->RptSeq = %d\n",
                       this->m_snapshotSymbol->Symbol()->m_text,
                       this->m_snapshotItem->TradingSession()->m_text,
                       this->m_snapshotItem->RptSeq(), rptSeq);
            }*/
            return res;
        }
        //TODO remove debug
        bool res = this->m_snapshotItem->EntriesQueue()->StartRptSeq() <= rptSeq;
        /*
        if(!res) {
            printf("  %s - %s  skip snapshot : que->StartRptSeq = %d >= snap->RptSeq = %d  max index = %d\n",
                   this->m_snapshotSymbol->Symbol()->m_text,
                   this->m_snapshotItem->TradingSession()->m_text,
                   this->m_snapshotItem->EntriesQueue()->StartRptSeq(),
                   rptSeq, this->m_snapshotItem->EntriesQueue()->MaxIndex());

        }*/
        return res;
    }
    inline bool CheckProcessIfSessionInActualState(int rptSeq) {
        if(this->m_snapshotItem->HasEntries())
            return false;

        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = this->m_snapshotItem->SymbolInfo();
        bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
        if(allItemsRecvSnapshot)
            return true;

        if(this->m_snapshotItem->RptSeq() != rptSeq)
            return false;

        this->m_snapshotItem->ProcessActualSnapshotState();
        if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
            this->DecSymbolsToRecvSnapshotCount();
        this->m_snapshotItem = 0;
        return true;
    }
    inline bool IsNullSnapshot(int rptSeq, int lastMsgProcessed) {
        return rptSeq == 0 && lastMsgProcessed == 0;
    }
    inline bool CheckProcessNullSnapshot(int rptSeq, int lastMsgProcessed) {
        if(IsNullSnapshot(rptSeq, lastMsgProcessed)) {
            bool allItemsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
            bool prevHasEntries = this->m_snapshotItem->HasEntries();
            this->m_snapshotItem->ClearEntries();
            this->m_snapshotItem->DecSessionsToRecvSnapshotCount();
            if(prevHasEntries && !this->m_snapshotItem->HasEntries()) {
                this->m_queueItemsCount--;
                *(this->m_ownerQueueItemsCount) = this->m_queueItemsCount;
            }
            if(!allItemsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot())
                this->DecSymbolsToRecvSnapshotCount();
            this->m_snapshotItem->ProcessNullSnapshot();
            this->m_snapshotItem = 0;
            return true;
        }
        return false;
    }

    inline void StartProcessSnapshot() {
        this->m_allSessionsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
        this->m_snapshotItem->StartProcessSnapshotMessages();
    }
    inline bool EndProcessSnapshot() {
        this->m_snapshotItem->RptSeq(this->m_snapshotItemRptSeq);
        bool prevHasEntries = this->m_snapshotItem->HasEntries();
        bool res = this->m_snapshotItem->EndProcessSnapshotMessages();
        if(prevHasEntries && !this->m_snapshotItem->HasEntries()) {
            this->m_queueItemsCount--;
            *(this->m_ownerQueueItemsCount) = this->m_queueItemsCount;
        }
        if(!this->m_allSessionsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot()) {
            this->DecSymbolsToRecvSnapshotCount();
        }
        this->m_snapshotItem->OnSnapshotProcessed();
        this->m_snapshotItem = 0;
        return res;
    }
    inline void CancelSnapshot() {
        this->m_snapshotItem->CancelSnapshotMessages();
        this->m_snapshotItem = 0;
    }
    inline int CalcTotalItemsCount() {
        int result = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            result += this->m_symbols[i]->SessionCount();
        }
        return result;
    }
    inline int CalcSnapshotProcessedItemsCount() {
        int result = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for(int j = 0; j < this->m_symbols[i]->SessionCount(); j++) {
                if(this->m_symbols[i]->Session(j)->SnapshotProcessedCount() > 0)
                    result++;
            }
        }
        return result;
    }
    inline bool DebugCheckActuality() {
        int res = DebugCalcActualQueueEntriesCount();
        if(res != this->m_queueItemsCount)
            throw;
        return true;
    }
    inline int DebugCalcActualQueueEntriesCount() {
        int count = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for (int j = 0; j < this->m_symbols[i]->SessionCount(); j++) {
                if(this->m_symbols[i]->Session(j)->HasEntries())
                    count++;
            }
        }
        return count;
    }
    inline int DebugCalcActualNonNullQueueEntriesCount() {
        int count = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for (int j = 0; j < this->m_symbols[i]->SessionCount(); j++) {
                if(this->m_symbols[i]->Session(j)->EntriesQueue() != 0)
                    count++;
            }
        }
        return count;
    }
    void DebugCheckDublicateItems() {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for (int j = 0; j < this->m_symbols[i]->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *item = this->Symbol(i)->Session(j);
                if(item->EntriesQueue() == 0)
                    continue;
                for(int k = i; k < this->SymbolsCount(); k++) {
                    for (int j = 0; j < this->m_symbols[i]->SessionCount(); j++) {
                        TABLEITEM<ITEMINFO> *item2 = this->Symbol(i)->Session(j);
                        if(item2->EntriesQueue() == 0)
                            continue;
                        if(item->EntriesQueue() == item2->EntriesQueue() && item2 != item)
                            throw;
                    }
                }
            }
        }
    }
    inline void ProcessSnapshot(ITEMINFO **item, int count, int rptSeq) {
        for(int j = 0; j < count; j++) {
            this->m_snapshotItem->ProcessSnapshotMessage(*item);
            item++;
        }
    }
    inline void ProcessSnapshotForts(INFO *info) {
        this->ProcessSnapshot(info->MDEntries, info->MDEntriesCount, info->RptSeq);
    }
    inline void ProcessSnapshot(INFO *info) {
        this->ProcessSnapshot(info->GroupMDEntries, info->GroupMDEntriesCount, info->RptSeq);
    }

    inline void Clear() {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsMaxCount; i++, s++)
            (*s)->Clear();
        this->m_symbolsCount = 0;
        this->m_queueItemsCount = 0;
        *(this->m_ownerQueueItemsCount) = this->m_queueItemsCount;
        this->m_symbolsToRecvSnapshot = 0;
        *(this->m_ownerSymbolsToRecvSnapshot) = this->m_symbolsToRecvSnapshot;
    }
    inline void Release() {
        if(this->m_symbols == 0)
            return;
        int symbCount = this->m_symbolsCount;
        this->Clear();
        for(int i = 0; i < symbCount; i++)
            delete this->m_symbols[i];
        delete this->m_symbols;
        this->m_symbols = 0;
        this->m_symbolsMaxCount = 0;
    }
    inline int SymbolsCount() { return this->m_symbolsCount; }
    inline int MaxSymbolsCount() { return this->m_symbolsMaxCount; }
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
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, int symbolLen, UINT32 tradingSession) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = GetSymbol(symbol, symbolLen);
        TABLEITEM<ITEMINFO>* res = s->GetSession(tradingSession);
        return res;
    }
#ifdef TEST
    inline TABLEITEM<ITEMINFO>* GetItem(int symbolIndex, const char *tradingSession) {
        return this->GetItem(symbolIndex, *((UINT32*)tradingSession));
    }
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, const char *tradingSession) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = GetSymbol(SymbolManager::AlignedString(symbol), strlen(symbol));
        TABLEITEM<ITEMINFO>* res = s->GetSession(*((UINT32*)tradingSession));
        return res;
    }
    void Add(const char *symbol, const char *session) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = AddSymbol(symbol);
        s->GetSession(*((UINT32*)session));
    }
#endif
    inline TABLEITEM<ITEMINFO>* GetItem(int symbolIndex, UINT32 tradingSession) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = this->m_symbols[symbolIndex];
        TABLEITEM<ITEMINFO>* res = s->GetSession(tradingSession);
        return res;
    }
    inline TABLEITEM<ITEMINFO>* GetItemByIndex(int symbolIndex, UINT32 tradingSession) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = this->m_symbols[symbolIndex];
        TABLEITEM<ITEMINFO>* res = s->Session(0);
        return res;
    }
    inline TABLEITEM<ITEMINFO>* GetItemByIndex(int symbolIndex) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *s = this->m_symbols[symbolIndex];
        TABLEITEM<ITEMINFO>* res = s->Session(0);
        return res;
    }
    inline TABLEITEM<ITEMINFO>* GetItemBySecurityId(UINT64 securityId, UINT32 tradingSession) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++) {
            if((*s)->SecurityID() == securityId) {
                TABLEITEM<ITEMINFO>* res = (*s)->Session(tradingSession);
                return res;
            }
        }
        return 0;
    }
    inline TABLEITEM<ITEMINFO>* GetItemBySecurityId(UINT64 securityId) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++) {
            if((*s)->SecurityID() == securityId) {
                TABLEITEM<ITEMINFO>* res = (*s)->Session(0);
                return res;
            }
        }
        return 0;
    }

    inline int UsedItemCount() {
        int res = 0;
        for(int i = 0; i < this->m_symbolsCount; i++)
            res += this->m_symbols[i]->Count();
        return res;
    }
    inline TABLEITEM<ITEMINFO>* SnapshotItem() { return this->m_snapshotItem; }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* SnapshotSymbol() { return this->m_snapshotSymbol; }
    inline bool HasQueueEntries() {
        return this->m_queueItemsCount > 0;
    }
    inline int QueueEntriesCount() { return this->m_queueItemsCount; }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol, int symbolLength, int index) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *newItem = this->m_symbols[index];
        newItem->Symbol()->Set(symbol, symbolLength);
        this->m_symbolsCount = this->m_symbolsCount < index + 1? index + 1: this->m_symbolsCount;
        return newItem;
    }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol, int symbolLength) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *newItem = this->m_symbols[this->m_symbolsCount];
        newItem->Symbol()->Set(symbol, symbolLength);
        this->m_symbolsCount++;
        return newItem;
    }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol) {
        return AddSymbol(SymbolManager::AlignedString(symbol), strlen(symbol));
    }
    inline void EnterSnapshotMode() {
        this->m_symbolsToRecvSnapshot = 0; //this->m_symbolsCount;
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++) {
            if((*s)->EnterSnapshotMode())
                this->m_symbolsToRecvSnapshot++;
        }
        *(this->m_ownerSymbolsToRecvSnapshot) = this->m_symbolsToRecvSnapshot;
        this->m_snapshotMode = true;
        *(this->m_ownerTableInSnapshotMode) = this->m_snapshotMode;
    }
    inline void ExitSnapshotMode() {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++)
            (*s)->ExitSnapshotMode();
        this->m_snapshotMode = false;
        *(this->m_ownerTableInSnapshotMode) = this->m_snapshotMode;
    }
    inline bool SnapshotMode() { return this->m_snapshotMode; }
    inline int SymbolsToRecvSnapshotCount() { return this->m_symbolsToRecvSnapshot; }
    inline bool IsAllSymbolsRecvSnapshot() { return this->m_symbolsToRecvSnapshot == 0; }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
