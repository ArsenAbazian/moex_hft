//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_ORDERBOOKINFO_H
#define HFT_ROBOT_ORDERBOOKINFO_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "../Lib/HrPointerList.h"
#include "../Lib/HrPointerList.h"
#include "MDEntryQueue.h"
#include "QuoteInfo.h"
#include "../Managers/DebugInfoManager.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class OrderBookInfo {
    static HrPointerList<T>               *m_itemsPool;

    HrPointerListLite<T>                  *m_sellQuoteList;
    HrPointerListLite<T>                  *m_buyQuoteList;
    int                                    m_buyQuoteListLevel;

    MDEntryQueue                       *m_entryInfo;

    bool                                m_used;
    bool                                m_shouldProcessSnapshot;
    int                                 m_rptSeq;
    int                                 m_savedRptSeq;
    MarketSymbolInfo<OrderBookInfo<T>>  *m_symbolInfo;
    SizedArray                          *m_tradingSession;
    UINT32                              m_sessionInt;

    int                                 m_snapshotProcessedCount;

    int                                 m_debugLevel;
public:
    OrderBookInfo();
    ~OrderBookInfo() {
        ReleaseEntryQue();
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline void SetDebugLevel(int level) {
        this->m_debugLevel = level;
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
    inline MarketSymbolInfo<OrderBookInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<OrderBookInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline int SavedRptSeq() { return this->m_savedRptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline bool HasEntries() { return this->m_entryInfo == 0? false: this->m_entryInfo->HasEntries(); }
    inline void ClearEntries() { this->ReleaseEntryQue(); }
    inline MDEntryQueue* EntriesQueue() { return this->m_entryInfo; }

    inline HrPointerListLite<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline HrPointerListLite<T>* BuyQuotes() { return this->m_buyQuoteList; }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(HrPointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        HrLinkedPointer<T> *node = list->Start();
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
        this->ClearEntries();
        this->m_rptSeq = 0;
        this->m_savedRptSeq = 0;
        this->m_shouldProcessSnapshot = false;
        this->m_snapshotProcessedCount = 0;
    }

    inline HrLinkedPointer<T>* GetQuote(HrPointerListLite<T> *list, T *info) {
        HrLinkedPointer<T> *node = list->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *info2 = node->Data();
            if(info2->MDEntryID == info->MDEntryID)
                return node;
            if(node == list->End())
                break;
            node = node->Next();
        }
        // such thing could happen because of some packet lost
        // so please do not return null :)
        return list->Add(info);
    }

    inline HrLinkedPointer<T>* GetBuyQuoteCore1(double value, HrLinkedPointer<T> *start, HrLinkedPointer<T> *end) {
        HrLinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                this->m_buyQuoteListLevel = this->CalcLevel();
                return this->m_buyQuoteList->Insert(node);
            }
            if(val == value)
                return node;
            node = node->Next();
        }
    }

    inline HrLinkedPointer<T>* GetBuyQuoteCore2(double value, HrLinkedPointer<T> *start, HrLinkedPointer<T> *end) {
        HrLinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                start = node->Prev2();
                HrLinkedPointer<T> *newNode = GetBuyQuoteCore1(value, start, node);
                if(this->m_buyQuoteListLevel >= 2)
                    this->m_buyQuoteList->Insert2(start, newNode, node);
                return newNode;
            }
            if(val == value)
                return node;
            node = node->Next2();
        }
    }

    inline HrLinkedPointer<T>* GetBuyQuoteCore3(double value, HrLinkedPointer<T> *start, HrLinkedPointer<T> *end) {
        HrLinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                start = node->Prev3();
                HrLinkedPointer<T> *newNode = GetBuyQuoteCore2(value, start, node);
                if(this->m_buyQuoteListLevel >= 3)
                    this->m_buyQuoteList->Insert3(start, newNode, node);
                return newNode;
            }
            if(val == value)
                return node;
            node = node->Next3();
        }
    }

    inline HrLinkedPointer<T>* GetBuyQuoteCore4(double value, HrLinkedPointer<T> *start, HrLinkedPointer<T> *end) {
        HrLinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                start = node->Prev4();
                HrLinkedPointer<T> *newNode = GetBuyQuoteCore3(value, start, node);
                if(this->m_buyQuoteListLevel >= 4)
                    this->m_buyQuoteList->Insert4(start, newNode, node);
                return newNode;
            }
            if(val == value)
                return node;
            node = node->Next4();
        }
    }

    inline HrLinkedPointer<T>* GetBuyQuoteCore5(double value, HrLinkedPointer<T> *start, HrLinkedPointer<T> *end) {
        HrLinkedPointer<T> *node = start;
        HrLinkedPointer<T> *newNode;
        // no items
        if (start == 0) {
            newNode = this->m_buyQuoteList->Add();
            return newNode;
        }
        double val = (&(start->Data()->MDEntryPx))->Value;
        // add before
        if(val < value) {
            newNode = this->m_buyQuoteList->Insert(start);
            if(start == end) { // we have one item in list
                // just connect start with end
                newNode->AllConnect(start);
                return newNode;
            }
            newNode->Connect5(start->Next5());
            newNode->Connect4(start->Next4());
            newNode->Connect3(start->Next3());
            newNode->Connect2(start->Next2());
            start->AllNext(0);
            start->AllPrev(0);
            this->m_buyQuoteList->InsertByLevel(CalcLevel(), newNode, start, end);
            return newNode;
        }
        if(val == value)
            return start;

        while (true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if (val < value) {
                start = node->Prev5();
                newNode = GetBuyQuoteCore4(value, start, node);
                if (this->m_buyQuoteListLevel >= 5)
                    this->m_buyQuoteList->Insert5(start, newNode, node);
                return newNode;
            }
            if (val == value)
                return node;
            if (node == end)
                break;
            node = node->Next5();
        }

        // add after
        newNode = this->m_buyQuoteList->Add();
        if(start == end) {
            // just connect start with end
            start->AllConnect(newNode);
            return newNode;
        }
        end->Prev()->AllConnect(newNode);
        end->AllPrev(0);
        this->m_buyQuoteList->InsertByLevel(this->CalcLevel(), end->Prev(), end, newNode);
        return newNode;
    }

    inline int CalcLevel() {
        const int maxP = INT32_MAX >> 1;
#ifdef TEST
        if(this->m_debugLevel != 0) {
            int res = this->m_debugLevel;
            this->m_debugLevel = 0;
            return res;
        }
#endif
        //TODO change rand to faster method!!!!!
        if(rand() > maxP)
            return 1;
        if(rand() > maxP)
            return 2;
        if(rand() > maxP)
            return 3;
        if(rand() > maxP)
            return 4;
        return 5;
    }

    inline HrLinkedPointer<T>* GetBuyQuoteEx(Decimal *price) {
        this->m_buyQuoteListLevel = 0;
        return this->GetBuyQuoteCore5(price->Calculate(), this->m_buyQuoteList->Start(), this->m_buyQuoteList->End());
    }

    inline HrLinkedPointer<T>* GetBuyQuote(Decimal *price) {
        HrLinkedPointer<T> *node = this->m_buyQuoteList->Start();
        double value = price->Calculate();
        T *quote = 0;

        if(node != 0) {
            while (true) {
                quote = node->Data();
                Decimal *val = &(quote->MDEntryPx);
                if (val->Value < value)
                    return this->m_buyQuoteList->Insert(node);
                else if(val->Value == value)
                    return node;
                if (node == this->m_buyQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        return this->m_buyQuoteList->Add();
    }

    inline HrLinkedPointer<T>* GetSellQuote(Decimal *price) {
        HrLinkedPointer<T> *node = this->m_sellQuoteList->Start();
        double value = price->Calculate();
        T *quote = 0;

        if(node != 0) {
            while (true) {
                quote = node->Data();
                Decimal *val = &(quote->MDEntryPx);
                if (val->Value > value)
                    return this->m_sellQuoteList->Insert(node);
                else if(val->Value == value)
                    return node;
                if (node == this->m_sellQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        return this->m_sellQuoteList->Add();
    }

    inline HrLinkedPointer<T>* RemoveBuyQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Remove BuyQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        HrLinkedPointer<T> *node = this->m_buyQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(data->MDEntryID == info->MDEntryID) {
                this->m_buyQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        //TODO remove debug
        //printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);

        return 0;
    }

    inline HrLinkedPointer<T>* RemoveSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Remove SellQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        HrLinkedPointer<T> *node = this->m_sellQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(data->MDEntryID == info->MDEntryID) {
                this->m_sellQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_sellQuoteList->End())
                break;
            node = node->Next();
        }
        //TODO remove debug
        //printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
        return 0;
    }

    inline void ChangeBuyQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Change BuyQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);

        HrLinkedPointer<T> *ptr = GetQuote(this->m_buyQuoteList, info);
        //TODO remove debug
        if(ptr == 0) {
            //printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
            return;
        }
        this->m_buyQuoteList->Remove(ptr);
        AddBuyQuote(info);
        info->Used = true;
        ptr->Data()->Clear();
    }

    inline void ChangeSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Change SellQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        HrLinkedPointer<T> *ptr = GetQuote(this->m_sellQuoteList, info);
        //TODO remove debug
        if(ptr == 0) {
            //printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
            return;
        }
        this->m_sellQuoteList->Remove(ptr);
        AddSellQuote(info);
        info->Used = true;
        ptr->Data()->Clear();
    }

    inline HrLinkedPointer<T>* AddBuyQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Add BuyQuote", item->MDEntryID, &(item->MDEntryPx), item->MDEntrySize);
        item->Used = true;
        HrLinkedPointer<T> *ptr = GetBuyQuoteEx(&(item->MDEntryPx)); // TODO changed from GetBuyQuote
        ptr->Data(item);
        return ptr;
    }

    inline HrLinkedPointer<T>* AddSellQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Add SellQuote", item->MDEntryID, &(item->MDEntryPx), item->MDEntrySize);
        item->Used = true;
        HrLinkedPointer<T> *ptr = GetSellQuote(&(item->MDEntryPx));
        ptr->Data(item);
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

    inline HrLinkedPointer<T>* Add(T *info) {
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

template <typename T> OrderBookInfo<T>::OrderBookInfo() {
    if(OrderBookInfo::m_itemsPool == 0)
        OrderBookInfo::m_itemsPool = new HrPointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);

    this->m_entryInfo = 0;
#ifdef TEST
    this->m_debugLevel = 0;
#endif

    this->m_sellQuoteList = new HrPointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
    this->m_buyQuoteList = new HrPointerListLite<T>(OrderBookInfo<T>::m_itemsPool);

    this->m_tradingSession = new SizedArray();
    this->m_shouldProcessSnapshot = false;
    this->m_rptSeq = 0;
    this->m_savedRptSeq = 0;
    this->m_snapshotProcessedCount = 0;
}

#endif //HFT_ROBOT_ORDERINFO_H
