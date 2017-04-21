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
    void                                        *m_object;
    void                                        *m_owner;
    union {
        struct {
            const char *m_stringId;
            unsigned int m_length;
        };
        UINT64              m_intId;
    };

    HashTableItemInfo() :
            m_object(0),
            m_owner(0),
            m_stringId(0),
            m_length(0) { }

    inline void Clear() {
        this->m_object = 0;
        this->m_intId = 0;
        this->m_owner = 0;
        this->m_stringId = 0;
        this->m_length = 0;
    }
};

class HashTable {
    static const int m_itemsCount = 1000000;
    LinkedPointer<HashTableItemInfo>                        **m_bucket;
    PointerList<HashTableItemInfo>                          *m_pool;
    int                                                     m_count;
    ItoaConverter                                           *m_converter;
    UINT64                                                  m_lastHash;

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
            start = this->m_pool->Pop();
            start->Next(0);
            this->m_bucket[hash] = start;
            return start;
        }

        LinkedPointer<HashTableItemInfo> *newNode = this->m_pool->Pop();
        newNode->Next(start);
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
            m_converter(0),
            m_lastHash(0) {
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
        this->m_lastHash = res;
        return this->CalcHash(res);
    }

    inline UINT64 CalcHash(UINT64 m_id) {
        if(m_id >= HashTable::m_itemsCount)
            this->m_lastHash = m_id % HashTable::m_itemsCount;
        else
            this->m_lastHash = m_id;
        return this->m_lastHash;
    }

    inline LinkedPointer<HashTableItemInfo>* FindPointer(LinkedPointer<HashTableItemInfo>* start, void *owner, const char *stringId, int length) {
        while(start != 0) {
            HashTableItemInfo *info = start->Data();
            if(info->m_owner == owner &&
                    StringIdComparer::Equal(info->m_stringId, info->m_length, stringId, length))
                return start;
            start = start->Next();
        }
        return 0;
    }

    inline UINT64 LastHash() const { return this->m_lastHash; }

    inline LinkedPointer<HashTableItemInfo>* FindPointer(LinkedPointer<HashTableItemInfo>* start, void *owner, UINT64 id) {
        while(start != 0) {
            HashTableItemInfo *info = start->Data();
            if(info->m_owner == owner && info->m_intId == id)
                return start;
            start = start->Next();
        }
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, const char *stringId, int length, UINT64 *hashOut) {
        UINT64 hash = this->CalcHash(stringId, length);
        if(this->m_bucket[hash] == 0) {
            *hashOut = hash;
            return 0;
        }
        LinkedPointer<HashTableItemInfo> *item = this->FindPointer(this->m_bucket[hash], owner, stringId, length);
        if(item != 0)
            return item;
        *hashOut = hash;
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, UINT64 id, UINT64 *hashOut) {
        UINT64 hash = this->CalcHash(id);
        if(this->m_bucket[hash] == 0) {
            *hashOut = hash;
            return 0;
        }
        LinkedPointer<HashTableItemInfo> *item = this->FindPointer(this->m_bucket[hash], owner, id);
        if(item != 0)
            return item;
        *hashOut = hash;
        return 0;
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, const char *stringId, int length) {
        UINT64 hash = this->CalcHash(stringId, length);
        if(this->m_bucket[hash] == 0)
            return 0;
        return this->FindPointer(this->m_bucket[hash], owner, stringId, length);
    }

    inline LinkedPointer<HashTableItemInfo>* GetPointer(void *owner, UINT64 id) {
        UINT64 hash = this->CalcHash(id);
        if(this->m_bucket[hash] == 0)
            return 0;
        return this->FindPointer(this->m_bucket[hash], owner, id);
    }

    inline void RemovePointer(UINT64 hash, LinkedPointer<HashTableItemInfo> *ptr) {
        if(this->m_bucket[hash] == ptr) { // first item
            this->m_bucket[hash] = ptr->Next();
        }
        this->Remove(ptr);
        this->m_pool->Push(ptr);
        this->m_count--;
    }

    inline void RemovePointer(LinkedPointer<HashTableItemInfo> *ptr) {
        this->RemovePointer(this->m_lastHash, ptr);
    }

    inline void Remove(void *owner, const char *stringId, int length) {
        LinkedPointer<HashTableItemInfo> *info = this->GetPointer(owner, stringId, length);
        Remove(info);
    }

    inline void Remove(void *owner, UINT64 id) {
        LinkedPointer<HashTableItemInfo> *info = this->GetPointer(owner, id);
        Remove(info);
    }

    inline LinkedPointer<HashTableItemInfo>* Add(void *owner, void *object, UINT64 hash, const char *stringId, int length) {
        LinkedPointer<HashTableItemInfo> *ptr = this->AddPointer(hash);
        HashTableItemInfo *info = ptr->Data();
        info->m_owner = owner;
        info->m_stringId = stringId;
        info->m_length = length;
        info->m_object = object;
        return ptr;
    }

    inline LinkedPointer<HashTableItemInfo>* Add(void *owner, void *object, const char *stringId, int length) {
        return this->Add(owner, object, this->CalcHash(stringId, length), stringId, length);
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
        return this->Add(owner, object, this->CalcHash(id), id);
    }
};

#endif //HFT_ROBOT_HASHTABLE_H
