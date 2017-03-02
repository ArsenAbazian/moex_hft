//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include <Managers/DebugInfoManager.h>
#include "Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "MDEntryQueue.h"
#include "MarketSymbolInfo.h"

template <template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO> class MarketDataTable {
    MarketSymbolInfo<TABLEITEM<ITEMINFO>>       **m_symbols;
    int                                         m_symbolsCount;
    int                                         m_symbolsMaxCount;
    TABLEITEM<ITEMINFO>                         *m_snapshotItem;
    TABLEITEM<ITEMINFO>                         *m_cachedItem;
    MarketSymbolInfo<TABLEITEM<ITEMINFO>>       *m_snapshotSymbol;
    int                                         m_snapshotItemRptSeq;
    int                                         m_queueItemsCount;
    int                                         m_symbolsToRecvSnapshot;
    bool                                        m_snapshotItemHasEntriesQueue;
    bool                                        m_allSessionsRecvSnapshot;
    bool                                        m_snapshotMode;

    inline void AddUsed(TABLEITEM<ITEMINFO> *tableItem) {
        tableItem->Used(true);
    }
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
    MarketDataTable() {
        this->m_symbols = 0;
        this->m_symbolsCount = 0;
        this->m_queueItemsCount = 0;
        this->m_cachedItem = 0;
        this->m_symbolsMaxCount = 0;
        this->m_snapshotMode = false;
    }
    ~MarketDataTable() {
        this->Release();
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
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
        this->AddUsed(this->m_snapshotItem);
    }
    inline void ObtainSnapshotItem(FastSnapshotInfo *info) {
        this->m_snapshotItem = this->GetCachedItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        if(this->m_snapshotItem == 0)
            this->m_snapshotItem = this->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_snapshotSymbol = this->m_snapshotItem->SymbolInfo();
        this->m_snapshotItemRptSeq = info->RptSeq;
        this->AddUsed(this->m_snapshotItem);
    }
    inline void DecSymbolsToRecvSnapshotCount() {
        this->m_symbolsToRecvSnapshot--;
    }
    inline void IncSymbolsToRecvSnapshotCount() {
        this->m_symbolsToRecvSnapshot++;
    }
    inline bool ProcessIncremental(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        //TODO remove debug
        int prevActual = this->CalcActualQueueEntriesCount();
        if(prevActual != this->m_queueItemsCount)
            throw;

        this->AddUsed(tableItem);
        bool prevHasEntries = tableItem->HasEntries();
        bool res = tableItem->ProcessIncrementalMessage(info);
        bool hasEntries = tableItem->HasEntries();
        if(hasEntries) {
            if(!prevHasEntries) {
                this->m_queueItemsCount++;
            }
        }
        else {
            if(prevHasEntries) {
                this->m_queueItemsCount--;
                //TODO remove debug
                if(tableItem->EntriesQueue() != 0)
                    throw;
            }
            if(tableItem->ShouldProcessSnapshot()) {
                MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = tableItem->SymbolInfo();
                bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
                tableItem->DecSessionsToRecvSnapshotCount();
                if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
                    this->DecSymbolsToRecvSnapshotCount();
            }
        }
        int actual = this->CalcActualQueueEntriesCount();
        //TODO remove debug
        if(actual != this->m_queueItemsCount)
            throw;
        return res;
    }

    inline bool ShouldProcessSnapshot(INFO *info) {
        if(!this->m_snapshotItem->HasEntries())
            return this->m_snapshotItem->RptSeq() < info->RptSeq;
        return this->m_snapshotItem->EntriesQueue()->StartRptSeq() <= info->RptSeq;
    }
    inline bool CheckProcessIfSessionInActualState(INFO *info) {
        if(this->m_snapshotItem->HasEntries())
            return false;
        if(this->m_snapshotItem->RptSeq() != info->RptSeq)
            return false;

        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = this->m_snapshotItem->SymbolInfo();
        bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
        this->m_snapshotItem->ProcessActualSnapshotState();
        if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
            this->DecSymbolsToRecvSnapshotCount();
        this->m_snapshotItem = 0;
        //TODO remove debug
        if(this->CalcActualQueueEntriesCount() != this->m_queueItemsCount)
            throw;
        return true;
    }
    inline bool IsNullSnapshot(INFO *info) {
        return info->RptSeq == 0 && info->LastMsgSeqNumProcessed == 0;
    }
    inline bool CheckProcessNullSnapshot(INFO *info) {
        if(IsNullSnapshot(info)) {
            bool allItemsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
            this->m_snapshotItemHasEntriesQueue = this->m_snapshotItem->HasEntries();
            this->m_snapshotItem->ClearEntries();
            this->m_snapshotItem->DecSessionsToRecvSnapshotCount();
            if(this->m_snapshotItemHasEntriesQueue && !this->m_snapshotItem->HasEntries())
                this->m_queueItemsCount--;
            //TODO remove debug
            if(this->m_snapshotItem->EntriesQueue() != 0)
                throw;
            if(!allItemsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot())
                this->DecSymbolsToRecvSnapshotCount();
            this->m_snapshotItem = 0;
            return true;
        }
        return false;
    }

    inline bool ApplyQuickSnapshot(FastSnapshotInfo *info) {
        if(this->CheckProcessIfSessionInActualState(info))
            return true;
        if(this->CheckProcessNullSnapshot(info))
            return true;
        if(!this->ShouldProcessSnapshot(info))
            return true;
        return false;
    }

    inline bool ShouldProcessSnapshot(FastSnapshotInfo *info) {
        if(!this->m_snapshotItem->HasEntries())
            return this->m_snapshotItem->RptSeq() < info->RptSeq;
        return this->m_snapshotItem->EntriesQueue()->StartRptSeq() <= info->RptSeq;
    }
    inline bool CheckProcessIfSessionInActualState(FastSnapshotInfo *info) {
        if(this->m_snapshotItem->HasEntries())
            return false;
        if(this->m_snapshotItem->RptSeq() != info->RptSeq)
            return false;

        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *smb = this->m_snapshotItem->SymbolInfo();
        bool allItemsRecvSnapshot = smb->AllSessionsRecvSnapshot();
        this->m_snapshotItem->ProcessActualSnapshotState();
        if (!allItemsRecvSnapshot && smb->AllSessionsRecvSnapshot())
            this->DecSymbolsToRecvSnapshotCount();
        this->m_snapshotItem = 0;
        return true;
    }
    inline bool IsNullSnapshot(FastSnapshotInfo *info) {
        return info->RptSeq == 0 && info->LastMsgSeqNumProcessed == 0;
    }
    inline bool CheckProcessNullSnapshot(FastSnapshotInfo *info) {
        if(IsNullSnapshot(info)) {
            bool allItemsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
            this->m_snapshotItemHasEntriesQueue = this->m_snapshotItem->HasEntries();
            this->m_snapshotItem->ClearEntries();
            this->m_snapshotItem->DecSessionsToRecvSnapshotCount();
            if(this->m_snapshotItemHasEntriesQueue && !this->m_snapshotItem->HasEntries())
                this->m_queueItemsCount--;
            //TODO remove debug
            if(this->m_snapshotItem->EntriesQueue() != 0)
                throw;
            if(!allItemsRecvSnapshot && this->m_snapshotSymbol->AllSessionsRecvSnapshot())
                this->DecSymbolsToRecvSnapshotCount();
            this->m_snapshotItem = 0;
            return true;
        }
        return false;
    }

    inline void StartProcessSnapshot() {
        this->m_snapshotItemHasEntriesQueue = this->m_snapshotItem->HasEntries();
        this->m_allSessionsRecvSnapshot = this->m_snapshotSymbol->AllSessionsRecvSnapshot();
        this->m_snapshotItem->StartProcessSnapshotMessages();
    }
    inline bool EndProcessSnapshot() {
        //TODO remove debug
        int actualPrev = this->CalcActualQueueEntriesCount();
        if(actualPrev != this->m_queueItemsCount)
            throw;
        this->m_snapshotItem->RptSeq(this->m_snapshotItemRptSeq);
        bool res = this->m_snapshotItem->EndProcessSnapshotMessages();
        if(this->m_snapshotItemHasEntriesQueue && !this->m_snapshotItem->HasEntries()) {
            this->m_queueItemsCount--;
            //TODO remove debug
            if(this->m_snapshotItem->EntriesQueue() != 0)
                throw;
            int actual = this->CalcActualQueueEntriesCount();
            if(actual != this->m_queueItemsCount)
                throw;
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
    inline int CalcActualQueueEntriesCount() {
        int count = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for (int j = 0; j < this->m_symbols[i]->SessionCount(); j++) {
                if(this->m_symbols[i]->Session(j)->HasEntries())
                    count++;
            }
        }
        return count;
    }
    inline void ProcessSnapshot(ITEMINFO **item, int count, int rptSeq) {
        for(int j = 0; j < count; j++) {
            this->m_snapshotItem->ProcessSnapshotMessage(*item);
            item++;
        }
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
        this->m_symbolsToRecvSnapshot = 0;
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
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* SnapshotSymbol() { return this->m_snapshotSymbol; }
    inline bool HasQueueEntries() {
        return this->m_queueItemsCount > 0;
    }
    inline int QueueEntriesCount() { return this->m_queueItemsCount; }
    inline TABLEITEM<ITEMINFO>* Add(const char *symbol, const char *session) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbolInfo = GetSymbol(symbol, strlen(symbol));
        return symbolInfo->GetSession(session, strlen(session));
    }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol, int symbolLength) {
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> *newItem = this->m_symbols[this->m_symbolsCount];
        newItem->Symbol()->Set(symbol, symbolLength);
        this->m_symbolsCount++;
        return newItem;
    }
    inline MarketSymbolInfo<TABLEITEM<ITEMINFO>>* AddSymbol(const char *symbol) {
        return AddSymbol(symbol, strlen(symbol));
    }
    inline void EnterSnapshotMode() {
        this->m_symbolsToRecvSnapshot = this->m_symbolsCount;
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++) {
            (*s)->EnterSnapshotMode();
        }
        this->m_snapshotMode = true;
    }
    inline void ExitSnapshotMode() {
        //TODO remove debug
        int actual = this->CalcActualQueueEntriesCount();
        MarketSymbolInfo<TABLEITEM<ITEMINFO>> **s = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, s++)
            (*s)->ExitSnapshotMode();
        this->m_snapshotMode = false;
    }
    inline bool SnapshotMode() { return this->m_snapshotMode; }
    inline int SymbolsToRecvSnapshotCount() { return this->m_symbolsToRecvSnapshot; }
    inline bool IsAllSymbolsRecvSnapshot() { return this->m_symbolsToRecvSnapshot == 0; }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
