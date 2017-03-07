//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_MARKETDATAENTRYQUEUE_H
#define HFT_ROBOT_MARKETDATAENTRYQUEUE_H

#include <Managers/DebugInfoManager.h>
#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"

#define MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH 500

//typedef enum _TableItemState {
//    tisNone,
//    tisInCheckActualState,
//    tisInIncrementalProcess,
//    tisStartApplySnapshot,
//    tisEndApplySnapshot,
//    tisApplySnapshotPart,
//    tisInApplySnapshot
//}TableItemState;


class MDEntryQueue {
    const int                                           m_incEntriesCount = MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH;
    void                                                **m_incEntries;
    int                                                 m_incEntriesMaxIndex;
    int                                                 m_incStartRptSeq;

    static AutoAllocatePointerList<MDEntryQueue>* CreatePool();
public:
    static AutoAllocatePointerList<MDEntryQueue>        *Pool;

    AutoAllocatePointerList<MDEntryQueue>               *Allocator;
    LinkedPointer<MDEntryQueue>                         *Pointer;
    bool                                                Used;

    MDEntryQueue() {
        this->Used = false;
        this->Pointer = 0;
        this->m_incEntries = new void *[MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH];
        bzero(this->m_incEntries, sizeof(void *) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }
    ~MDEntryQueue() {
        delete this->m_incEntries;
    }

    int GetFirstNonEmptyEntry() {
        for(int i = 0; i < this->m_incEntriesCount; i++) {
            if (this->m_incEntries[i] != 0)
                return i;
        }
        return -1;
    }

    inline bool IsCleared() {
        if(this->m_incStartRptSeq != 0)
            return false;
        if(this->m_incEntriesMaxIndex != -1)
            return false;
        for(int i = 0; i < this->m_incEntriesCount; i++) {
            if (this->m_incEntries[i] != 0)
                return false;
        }
        return true;
    }

    inline void StartRptSeq(int rptSeq) {
        this->m_incStartRptSeq = rptSeq;
    }

    inline int StartRptSeq() { return this->m_incStartRptSeq; }

    inline MDEntryQueue* GetNonEmptyInfoInPool() {
        LinkedPointer<MDEntryQueue> *start = MDEntryQueue::Pool->Start();
        while(start != 0) {
            MDEntryQueue *data = start->Data();
            if(!data->IsCleared())
                return data;
            if(start == MDEntryQueue::Pool->End())
                break;
            start = start->Next();
        }
        return 0;
    }

    inline void AddEntry(void *entry, int entryRptSec) {
        int index = entryRptSec - this->m_incStartRptSeq;
        if(index >= this->m_incEntriesCount) {
            if(this->HasEntries())
                return;
            this->m_incStartRptSeq = entryRptSec;
            index = 0;
        }
        this->m_incEntries[index] = entry;
        if(index > this->m_incEntriesMaxIndex) {
            this->m_incEntriesMaxIndex = index;
        }
    }

    inline void Reset() {
        if(this->m_incEntriesMaxIndex >= 0)
            bzero(this->m_incEntries, sizeof(void*) * (this->m_incEntriesMaxIndex + 1));
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }

    inline void Clear() {
        void **ptr = this->m_incEntries;
        void *item = 0;
        for(int i = 0; i < this->m_incEntriesCount; i++) {
            item = *ptr;
            //if(item != 0) item->Clear();
            throw;
        }
        this->Reset();
    }

    inline int MaxIndex() { return this->m_incEntriesMaxIndex; }
    inline bool HasEntries() { return this->m_incEntriesMaxIndex != -1; };
    inline void** Entries() { return this->m_incEntries; }
    inline int RptSeq() { return this->m_incStartRptSeq; }
    inline int Capacity() { return this->m_incEntriesCount; }
};

#endif //HFT_ROBOT_MARKETDATAENTRYQUEUE_H
