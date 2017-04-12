//
// Created by root on 12.04.17.
//

#ifndef HFT_ROBOT_HASHTABLE_H
#define HFT_ROBOT_HASHTABLE_H

#include "../Settings.h"
#include "PointerList.h"
#include "StringIdComparer.h"
#include "AutoAllocatePointerList.h"
#include "../Converters/ItoaConverter.h"
#include <string.h>

class HashTableItemInfo {
public:
    void                    *m_object;
    void                    *m_owner;
    LinkedPointer<HashTableItemInfo>    *Pointer;
    union {
        SizedArray          *m_stringId;
        UINT64              m_intId;
    };

    HashTableItemInfo() :
            m_object(0),
            m_intId(0),
            m_stringId(0),
            m_owner(0),
            Pointer(0) { }

    inline void Clear() {
        this->m_object = 0;
        this->m_intId = 0;
        this->m_owner = 0;
    }
};

class HashTable {
    static const int m_itemsCount = 1000000;
    LinkedPointer<HashTableItemInfo>                        **m_bucket;
    AutoAllocatePointerList<HashTableItemInfo>             *m_pool;
    int                                                     m_count;
    ItoaConverter                                           *m_converter;

    inline void Remove(LinkedPointer<HashTableItemInfo> *node) { // not bidirectional
        LinkedPointer<HashTableItemInfo> *prev = node->Prev();
        LinkedPointer<HashTableItemInfo> *next = node->Next();
        if(prev != 0) prev->Next(next);
        node->Data()->Clear();
    }
    inline LinkedPointer<HashTableItemInfo> * AddPointer(UINT64 hash) {
        this->m_count++;

        LinkedPointer<HashTableItemInfo> *start = this->m_bucket[hash];
        if(start == 0) {
            start = this->m_pool->NewPointer();
            this->m_bucket[hash] = start;
            return start;
        }

        LinkedPointer<HashTableItemInfo> *newNode = this->m_pool->NewPointer();
        newNode->Next(start);
        this->m_bucket[hash] = newNode;
        return newNode;

    }
public:
    static HashTable *Default;
    void SafeCreateDefault() {
        if(HashTable::Default == 0)
            HashTable::Default = new HashTable();
    }

    HashTable(int m_poolSize) :
            m_bucket(0),
            m_pool(0),
            m_count(0),
            m_converter(0) {
        this->m_bucket = new LinkedPointer<HashTableItemInfo>*[HashTable::m_itemsCount];
        memset(this->m_bucket, sizeof(LinkedPointer<HashTableItemInfo>*) * HashTable::m_itemsCount, 0);
        this->m_pool = new AutoAllocatePointerList<HashTableItemInfo>(m_poolSize, m_poolSize / 20);
        this->m_converter = new ItoaConverter();
    }
    HashTable() : HashTable(m_itemsCount / 2) { }
    ~HashTable() {
        if(this->m_bucket != 0)
            delete this->m_bucket;
        if(this->m_pool != 0)
            delete this->m_pool;
    }

    inline UINT64 CalcHash(SizedArray *m_stringId) {
        if(m_stringId->m_length == 0)
            return 0;
        UINT64 res = this->m_converter->FromStringFastUnsigned(m_stringId->m_text, m_stringId->m_length);
        return this->CalcHash(res);
    }

    inline UINT64 CalcHash(UINT64 m_id) {
        if(m_id > HashTable::m_itemsCount)
            return m_id % HashTable::m_itemsCount;
        return m_id;
    }

    inline LinkedPointer<HashTableItemInfo>* FindPointer(LinkedPointer<HashTableItemInfo>* start, void *owner, SizedArray *m_stringId) {
        while(start != 0) {
            HashTableItemInfo *info = start->Data();
            if(info->m_owner == owner &&
                    StringIdComparer::Equal(info->m_stringId->m_text, info->m_stringId->m_length, m_stringId->m_text, m_stringId->m_length))
                return start;
            start = start->Next();
        }
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* FindPointer(LinkedPointer<HashTableItemInfo>* start, void *owner, UINT64 *m_id) {
        while(start != 0) {
            HashTableItemInfo *info = start->Data();
            if(info->m_owner == owner && info->m_intId == m_id)
                return start;
            start = start->Next();
        }
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, SizedArray *m_stringId, UINT64 *hashOut) {
        UINT64 hash = this->CalcHash(m_stringId);
        if(this->m_bucket[hash] == 0) {
            *hashOut = hash;
            return 0;
        }
        LinkedPointer<HashTableItemInfo> *item = this->FindPointer(this->m_bucket[hash], owner, m_stringId);
        if(item != 0)
            return item;
        *hashOut = hash;
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, UINT64 m_id, UINT64 *hashOut) {
        UINT64 hash = this->CalcHash(m_id);
        if(this->m_bucket[hash] == 0) {
            *hashOut = hash;
            return 0;
        }
        LinkedPointer<HashTableItemInfo> *item = this->FindPointer(this->m_bucket[hash], owner, m_id);
        if(item != 0)
            return item;
        *hashOut = hash;
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, SizedArray *m_stringId) {
        UINT64 hash = this->CalcHash(m_stringId);
        if(this->m_bucket[hash] == 0)
            return 0;
        return this->FindPointer(this->m_bucket[hash], owner, m_stringId);
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, UINT64 m_id) {
        UINT64 hash = this->CalcHash(m_id);
        if(this->m_bucket[hash] == 0)
            return 0;
        return this->FindPointer(this->m_bucket[hash], owner, m_id);
    }

    inline void RemovePointer(UINT64 hash, LinkedPointer<HashTableItemInfo> *ptr) {
        if(this->m_bucket[hash] == ptr) { // first item
            this->m_bucket[hash] = ptr->Next();
        }
        this->Remove(ptr);
        this->m_pool->FreeItem(ptr);
        this->m_count--;
    }

    inline void Add(void *owner, void *object, UINT64 hash, SizedArray *stringId) {
        HashTableItemInfo *info = this->AddPointer(hash)->Data();
        info->m_owner = owner;
        info->m_stringId = stringId;
        info->m_object = object;
    }

    inline void Add(void *owner, void *object, UINT64 hash, UINT64 id) {
        HashTableItemInfo *info = this->AddPointer(hash)->Data();
        info->m_owner = owner;
        info->m_intId = id;
        info->m_object = object;
    }
};

#endif //HFT_ROBOT_HASHTABLE_H
