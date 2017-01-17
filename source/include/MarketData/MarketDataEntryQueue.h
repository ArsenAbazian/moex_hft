//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_MARKETDATAENTRYQUEUE_H
#define HFT_ROBOT_MARKETDATAENTRYQUEUE_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"

#define MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH 2000

template <typename T> class MDEntrQueue {
    T           **m_incEntries;
    int         m_incEntriesCount;
    int         m_incEntriesMaxIndex;
    int         m_incStartRptSeq;

public:
    MDEntrQueue() {
        this->m_incEntries = new T*[MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH];
        this->m_incEntriesCount = MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH;
        bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }
    ~MDEntrQueue() {
        delete this->m_incEntries;
    }

    inline void StartRptSeq(int rptSeq) {
        this->m_incStartRptSeq = rptSeq;
    }

    inline int StartRptSeq() { return this->m_incStartRptSeq; }

    inline void AddEntry(T *entry) {
        int index = entry->RptSeq - this->m_incStartRptSeq;
        this->m_incEntries[index] = entry;
        if(index > this->m_incEntriesMaxIndex)
            this->m_incEntriesMaxIndex = index;
    }

    inline void Reset() {
        bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
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

    inline int MaxIndex() { return this->m_incEntriesMaxIndex; }
    inline bool HasEntries() { return this->m_incEntriesMaxIndex != -1; };
    inline T** Entries() { return this->m_incEntries; }
    inline int RptSeq() { return this->m_incStartRptSeq; }
};

#endif //HFT_ROBOT_MARKETDATAENTRYQUEUE_H
