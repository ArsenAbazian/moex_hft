//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_MARKETDATAENTRYQUEUE_H
#define HFT_ROBOT_MARKETDATAENTRYQUEUE_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"

#define MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH 2000

template <typename T> class MDEntryQueue {
    T                                                   **m_incEntries;
    int                                                 m_incEntriesCount;
    int                                                 m_incEntriesMaxIndex;
    int                                                 m_incStartRptSeq;
    bool                                                m_shouldProcess;
public:
    static AutoAllocatePointerList<MDEntryQueue<T>>     *Pool;

    AutoAllocatePointerList<MDEntryQueue<T>>            *Allocator;
    LinkedPointer<MDEntryQueue<T>>                      *Pointer;
    bool                                                Used;

    MDEntryQueue();
    ~MDEntryQueue() {
        delete this->m_incEntries;
    }

    inline static AutoAllocatePointerList<MDEntryQueue<T>>* CreatePool() {
        return new AutoAllocatePointerList<MDEntryQueue<T>>(RobotSettings::Default->MDEntryQueueItemsCount, RobotSettings::Default->MDEntryQueueItemsAddCount, "Some of MDEntryQueuePool");
    }

    inline void StartRptSeq(int rptSeq) {
        this->m_incStartRptSeq = rptSeq;
    }

    inline int StartRptSeq() { return this->m_incStartRptSeq; }

    inline void AddEntry(T *entry) {
        int index = entry->RptSeq - this->m_incStartRptSeq;
        if(index >= this->m_incEntriesCount) {
            if(this->HasEntries())
                return;
            this->m_incStartRptSeq = entry->RptSeq;
            index = 0;
        }
        this->m_shouldProcess = false; // reset flag because we will process
        this->m_incEntries[index] = entry;
        if(index > this->m_incEntriesMaxIndex)
            this->m_incEntriesMaxIndex = index;
    }

    inline void Reset() {
        if(this->m_incEntriesMaxIndex >= 0)
            bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesMaxIndex);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
        this->m_shouldProcess = false;
    }

    inline void Clear() {
        T **ptr = this->m_incEntries;
        T *item = 0;
        for(int i = 0; i < this->m_incEntriesCount; i++) {
            item = *ptr;
            if(item != 0) item->Clear();
        }
        this->Reset();
    }

    inline void ShouldProcess(bool value) {
        if(this->HasEntries())
            return;
        this->m_shouldProcess = value;
    }
    inline int MaxIndex() { return this->m_incEntriesMaxIndex; }
    inline bool HasEntries() { return this->m_incEntriesMaxIndex != -1 || this->m_shouldProcess; };
    inline T** Entries() { return this->m_incEntries; }
    inline int RptSeq() { return this->m_incStartRptSeq; }
    inline int Capacity() { return this->m_incEntriesCount; }
};

template <typename T> AutoAllocatePointerList<MDEntryQueue<T>>* MDEntryQueue<T>::Pool = 0;

template <typename T> MDEntryQueue<T>::MDEntryQueue() {
    this->Used = false;
    this->Pointer = 0;
    this->m_incEntries = new T *[MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH];
    this->m_incEntriesCount = MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH;
    bzero(this->m_incEntries, sizeof(T *) * this->m_incEntriesCount);
    this->m_incEntriesMaxIndex = -1;
    this->m_incStartRptSeq = 0;
    this->m_shouldProcess = false;
}

#endif //HFT_ROBOT_MARKETDATAENTRYQUEUE_H
