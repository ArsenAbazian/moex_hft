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
    UINT64                  m_intId;

    HashTableItemInfo() :
            m_object(0),
            m_owner(0) { }

    inline void Clear() {
        this->m_object = 0;
        this->m_intId = 0;
        this->m_owner = 0;
    }
};

class HashTableTester;
class HashTable {
    friend class HashTableTester;

    static const int m_itemsCount = 1024 * 1024 + 1;
    LinkedPointer<HashTableItemInfo>                        **m_bucket;
    PointerList<HashTableItemInfo>                          *m_pool;
    int                                                     m_count;
    ItoaConverter                                           *m_converter;

    inline void Remove(LinkedPointer<HashTableItemInfo> *node) { // not bidirectional
        LinkedPointer<HashTableItemInfo> *prev = node->Prev();
        LinkedPointer<HashTableItemInfo> *next = node->Next();
        prev->Connect(next);
        //node->Data()->Clear(); there is no need clear because next initializartion rewrite data
    }
    inline LinkedPointer<HashTableItemInfo> * AddPointer(UINT64 hash) {
        this->m_count++;

        LinkedPointer<HashTableItemInfo> *start = this->m_bucket[hash];
        LinkedPointer<HashTableItemInfo> *newNode = this->m_pool->Pop();

        newNode->Next(start);
        if(start != 0) start->Prev(newNode);
        this->m_bucket[hash] = newNode;
        return newNode;

    }
public:
    static HashTable *Default;
    static void SafeCreateDefault() {
        if(HashTable::Default == 0)
            HashTable::Default = new HashTable();
    }

    HashTable(int m_poolSize) :
            m_bucket(0),
            m_pool(0),
            m_count(0),
            m_converter(0) {
        this->m_bucket = new LinkedPointer<HashTableItemInfo>*[HashTable::m_itemsCount];
        memset(this->m_bucket, 0, sizeof(LinkedPointer<HashTableItemInfo>*) * HashTable::m_itemsCount);
        this->m_pool = new PointerList<HashTableItemInfo>(m_poolSize, true, "HashTable::Pool");
        this->m_converter = new ItoaConverter();
    }
    HashTable() : HashTable(m_itemsCount / 2) { }
    ~HashTable() {
        if(this->m_bucket != 0)
            delete this->m_bucket;
        if(this->m_pool != 0)
            delete this->m_pool;
    }

    void Clear() {
        this->m_pool->Clear();
        this->m_count = 0;
        memset(this->m_bucket, 0, sizeof(LinkedPointer<HashTableItemInfo>*) * HashTable::m_itemsCount);
    }

    inline UINT64 CalcHash(const char *stringId, int length) {
        if(length == 0)
            return 0;
        UINT64 res = this->m_converter->FromStringFastUnsignedPredict67(stringId, length);
        return this->ConstrainHash(res);
    }
    inline UINT64 CalcHashNoConstrain(const char *stringId, int length) {
        if(length == 0)
            return 0;
        return this->m_converter->FromStringFastUnsignedPredict67(stringId, length);
    }

    inline UINT64 ConstrainHash(UINT64 m_id) {
        return m_id & 0x0fffff;
        //if(m_id >= HashTable::m_itemsCount)
        //    m_id = m_id % HashTable::m_itemsCount;
        return m_id;
    }

    inline LinkedPointer<HashTableItemInfo>* FindPointer(LinkedPointer<HashTableItemInfo>* start, void *owner, UINT64 id) {
        while(start != 0) {
            HashTableItemInfo *info = start->Data();
            if(info->m_owner == owner && info->m_intId == id)
                return start;
            start = start->Next();
        }
        return 0;
    }
     inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, const char *stringId, int length) {
        UINT64 hash = this->CalcHashNoConstrain(stringId, length);
        LinkedPointer<HashTableItemInfo> *start = this->m_bucket[this->ConstrainHash(hash)];
        if(start == 0)
            return 0;
        return this->FindPointer(start, owner, hash);
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, UINT64 id) {
        LinkedPointer<HashTableItemInfo> *start = this->m_bucket[this->ConstrainHash(id)];
        if(start == 0)
            return 0;
        return this->FindPointer(start, owner, id);
    }

    inline void RemovePointer(UINT64 hash, LinkedPointer<HashTableItemInfo> *ptr) {
        LinkedPointer<HashTableItemInfo> **start = this->m_bucket + hash;
        if((*start) == ptr) // first item
            (*start) = ptr->Next();
        else
            this->Remove(ptr);
        this->m_pool->PushUnsafe(ptr);
        this->m_count--;
    }

    inline void RemovePointer(LinkedPointer<HashTableItemInfo> *ptr) {
        this->RemovePointer(this->ConstrainHash(ptr->Data()->m_intId), ptr);
    }

    inline void Remove(void *owner, const char *stringId, int length) {
        UINT64 hash = this->CalcHashNoConstrain(stringId, length);
        UINT64 hash2 = this->ConstrainHash(hash);
        LinkedPointer<HashTableItemInfo> *info = this->FindPointer(this->m_bucket[hash2], owner, hash);
        RemovePointer(hash2, info);
    }

    inline void Remove(void *owner, UINT64 id) {
        UINT64 hash = this->ConstrainHash(id);
        LinkedPointer<HashTableItemInfo> *info = this->FindPointer(this->m_bucket[hash], owner, id);
        RemovePointer(hash, info);
    }

    inline LinkedPointer<HashTableItemInfo>* Add(void *owner, void *object, UINT64 hash, const char *stringId, int length) {
        LinkedPointer<HashTableItemInfo> *ptr = this->AddPointer(this->ConstrainHash(hash));
        HashTableItemInfo *info = ptr->Data();
        info->m_owner = owner;
        info->m_intId = hash;
        info->m_object = object;
        return ptr;
    }

    inline LinkedPointer<HashTableItemInfo>* Add(void *owner, void *object, const char *stringId, int length) {
        return this->Add(owner, object, this->CalcHashNoConstrain(stringId, length), stringId, length);
    }

    inline LinkedPointer<HashTableItemInfo>* Add(void *owner, void *object, UINT64 hash, UINT64 id) {
        LinkedPointer<HashTableItemInfo> *ptr = this->AddPointer(hash);
        HashTableItemInfo *info = ptr->Data();
        info->m_owner = owner;
        info->m_intId = id;
        info->m_object = object;
        return ptr;
    }

    inline LinkedPointer<HashTableItemInfo>* Add(void *owner, void *object, UINT64 id) {
        return this->Add(owner, object, this->ConstrainHash(id), id);
    }
};

#endif //HFT_ROBOT_HASHTABLE_H
