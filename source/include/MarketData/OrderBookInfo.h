//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_ORDERBOOKINFO_H
#define HFT_ROBOT_ORDERBOOKINFO_H

#include "../Lib/StringIdComparer.h"
#include "../Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "../Lib/HashTable.h"
#include "MDEntryQueue.h"
#include "QuoteInfo.h"
#include "../Managers/DebugInfoManager.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class OrderBookInfo {
    static PointerList<T>               *m_itemsPool;

    PointerListLite<T>                  *m_sellQuoteList;
    PointerListLite<T>                  *m_buyQuoteList;
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
    unsigned int                        g_seed;
    void init_fast_srand() {
        g_seed = (DefaultStopwatch::Default->ElapsedNanoseconds() & 0xffffffff);
    }
public:
    OrderBookInfo();
    ~OrderBookInfo() {
        ReleaseEntryQue();
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline void SetDebugFastRandSeed(int seed) {
        this->g_seed = seed;
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

    inline PointerListLite<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerListLite<T>* BuyQuotes() { return this->m_buyQuoteList; }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerListLite<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
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

    /*
    inline LinkedPointer<T>* GetBuyQuoteCore1(double value, LinkedPointer<T> *start, LinkedPointer<T> *end) {
        LinkedPointer<T> *node = start;
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

    inline LinkedPointer<T>* GetBuyQuoteCore2(double value, LinkedPointer<T> *start, LinkedPointer<T> *end) {
        LinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                start = node->Prev2();
                LinkedPointer<T> *newNode = GetBuyQuoteCore1(value, start, node);
                if(this->m_buyQuoteListLevel >= 2)
                    this->m_buyQuoteList->Insert2(start, newNode, node);
                return newNode;
            }
            if(val == value)
                return node;
            node = node->Next2();
        }
    }

    inline LinkedPointer<T>* GetBuyQuoteCore3(double value, LinkedPointer<T> *start, LinkedPointer<T> *end) {
        LinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                start = node->Prev3();
                LinkedPointer<T> *newNode = GetBuyQuoteCore2(value, start, node);
                if(this->m_buyQuoteListLevel >= 3)
                    this->m_buyQuoteList->Insert3(start, newNode, node);
                return newNode;
            }
            if(val == value)
                return node;
            node = node->Next3();
        }
    }

    inline LinkedPointer<T>* GetBuyQuoteCore4(double value, LinkedPointer<T> *start, LinkedPointer<T> *end) {
        LinkedPointer<T> *node = start;
        while(true) {
            double val = (&(node->Data()->MDEntryPx))->Value;
            if(val < value) {
                start = node->Prev4();
                LinkedPointer<T> *newNode = GetBuyQuoteCore3(value, start, node);
                if(this->m_buyQuoteListLevel >= 4)
                    this->m_buyQuoteList->Insert4(start, newNode, node);
                return newNode;
            }
            if(val == value)
                return node;
            node = node->Next4();
        }
    }

    inline LinkedPointer<T>* GetBuyQuoteCore5(double value, LinkedPointer<T> *start, LinkedPointer<T> *end) {
        LinkedPointer<T> *node = start;
        LinkedPointer<T> *newNode;
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
            this->m_buyQuoteList->InsertAfterByLevel(CalcLevel(), newNode, start);
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
        end->Prev5()->Connect5(newNode);
        end->Prev4()->Connect4(newNode);
        end->Prev3()->Connect3(newNode);
        end->Prev2()->Connect2(newNode);
        end->AllPrev(0);
        end->AllNext(0);
        this->m_buyQuoteList->InsertBeforeByLevel(this->CalcLevel(), end, newNode);
        return newNode;
    }

    // Compute a pseudorandom integer.
    // Output value in range [0, 32767]
    inline int fast_rand(void) {
        g_seed = (214013 * g_seed + 2531011);
        return (g_seed >> 16) & 0x7fff;
    }

    inline int CalcLevel() {
        //const int level2P = 32767 >> 2;
        //const int level3P = 32767 >> 3;
        //const int level4P = 32767 >> 4;
        //const int level5P = 32767 >> 6;

        const int level2P = 32767 >> 2;
        const int level3P = 32767 >> 3;
        const int level4P = 32767 >> 4;
        const int level5P = 32767 >> 5;
#ifdef TEST
        if (this->m_debugLevel != 0) {
            int res = this->m_debugLevel;
            this->m_debugLevel = 0;
            return res;
        }
#endif
        int p = fast_rand();
        if (p < level4P) {
            if (p < level5P)
                return 5;
            return 4;
        } else {
            if (p < level3P)
                return 3;
            if (p < level2P)
                return 2;
            return 1;
        }
    }
    inline LinkedPointer<T>* GetBuyQuoteEx(Decimal *price) {
        this->m_buyQuoteListLevel = 0;
        return this->GetBuyQuoteCore5(price->Calculate(), this->m_buyQuoteList->Start(), this->m_buyQuoteList->End());
    }
    */
    inline LinkedPointer<T>* GetBuyQuote(Decimal *price) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        double value = price->Calculate();

        if(node != 0) {
            while (true) {
                T *quote = node->Data();
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

    inline LinkedPointer<T>* GetSellQuote(Decimal *price) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        double value = price->Calculate();

        if(node != 0) {
            while (true) {
                T *quote = node->Data();
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
    /*
    inline void RemoveBuyQuoteEx(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Remove BuyQuoteEx", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        LinkedPointer<T> *node = this->GetBuyQuote(&(info->MDEntryPx));
        this->m_buyQuoteList->Remove(node);
        node->Data()->Clear();
        //TODO remove debug
        //printf("ERROR: %" PRIu64 " entry not found\n", info->MDEntryID);
        return ;
    }
    */
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
    inline LinkedPointer<HashTableItemInfo>* AddPointer(PointerListLite<T> *list, T *info) {
        LinkedPointer<T> *item = list->Add(info);
        return HashTable::Default->Add(this, item, info->MDEntryID);
    }
    inline LinkedPointer<HashTableItemInfo>* AddPointer(LinkedPointer<T> *ptr, T *info) {
        return HashTable::Default->Add(this, ptr, info->MDEntryID);
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
        LinkedPointer<T> *ptr;
        if(hashItem != 0) {
            ptr = static_cast<LinkedPointer<T>*>(hashItem->Data()->m_object);
            this->m_buyQuoteList->Remove(ptr);
            ptr->Data()->Clear();

            info->Used = true;
            ptr = GetBuyQuote(&(info->MDEntryPx));
            ptr->Data(info);
            HashTableItemInfo *h = hashItem->Data();
            h->m_object = ptr;
            h->m_intId = info->MDEntryID;
            return;
        }
        info->Used = true;
        ptr = GetBuyQuote(&(info->MDEntryPx));
        hashItem = AddPointer(ptr, info);
    }

    inline void ChangeSellQuote(T *info) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Change SellQuote", info->MDEntryID, &(info->MDEntryPx), info->MDEntrySize);
        LinkedPointer<HashTableItemInfo> *hashItem = this->GetPointer(info);
        LinkedPointer<T> *ptr;
        if(hashItem != 0) {
            ptr = static_cast<LinkedPointer<T>*>(hashItem->Data()->m_object);
            this->m_sellQuoteList->Remove(ptr);
            ptr->Data()->Clear();

            info->Used = true;
            ptr = GetSellQuote(&(info->MDEntryPx));
            ptr->Data(info);
            HashTableItemInfo *h = hashItem->Data();
            h->m_object = ptr;
            h->m_intId = info->MDEntryID;
            return;
        }
        info->Used = true;
        ptr = GetSellQuote(&(info->MDEntryPx));
        hashItem = AddPointer(ptr, info);
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Add BuyQuote", item->MDEntryID, &(item->MDEntryPx), item->MDEntrySize);
        item->Used = true;
        LinkedPointer<T> *ptr = GetBuyQuote(&(item->MDEntryPx));
        AddPointer(ptr, item);
        ptr->Data(item);
        return ptr;
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        DebugInfoManager::Default->Log(this->m_symbolInfo->Symbol(), this->m_sessionInt, "Add SellQuote", item->MDEntryID, &(item->MDEntryPx), item->MDEntrySize);
        item->Used = true;
        LinkedPointer<T> *ptr = GetSellQuote(&(item->MDEntryPx));
        AddPointer(ptr, item);
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

template <typename T> PointerList<T>* OrderBookInfo<T>::m_itemsPool = 0;

template <typename T> OrderBookInfo<T>::OrderBookInfo() :
        m_sellQuoteList(0),
        m_buyQuoteList(0),
        m_tradingSession(0),
        m_shouldProcessSnapshot(false),
        m_rptSeq(0),
        m_savedRptSeq(0),
        m_snapshotProcessedCount(0),
        m_used(0),
        m_buyQuoteListLevel(0),
        m_symbolInfo(0),
        m_entryInfo(0),
        m_sessionInt(0),
#ifdef TEST
        m_debugLevel(0),
#endif
        g_seed(0) {
    if(OrderBookInfo::m_itemsPool == 0)
        OrderBookInfo::m_itemsPool = new PointerList<T>(RobotSettings::Default->MarketDataMaxEntriesCount, false);

    HashTable::SafeCreateDefault();

    this->init_fast_srand();
    this->m_sellQuoteList = new PointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
    this->m_buyQuoteList = new PointerListLite<T>(OrderBookInfo<T>::m_itemsPool);
}

#endif //HFT_ROBOT_ORDERINFO_H
