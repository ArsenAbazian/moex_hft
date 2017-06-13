//
// Created by root on 12.04.17.
//

#ifndef HFT_ROBOT_HASHTABLE_H
#define HFT_ROBOT_HASHTABLE_H

#include "../Settings.h"
#include "PointerList.h"
#include "StringIdComparer.h"
#include "HrPointerList.h"
#include "../Converters/ItoaConverter.h"
#include <string.h>

class HashTableTester;
template <typename T> class HashTable {
    friend class HashTableTester;

    static const int m_itemsCount = 1024 * 1024 + 1;
    HrLinkedPointer<T>                                      **m_bucket;
    ItoaConverter                                           *m_converter;
    int                                                     m_count;
    int                                                     m_paddingBytes;

    inline void Remove(HrLinkedPointer<T> *node) { // not bidirectional
        HrLinkedPointer<T> *prev = node->PrevHash();
        HrLinkedPointer<T> *next = node->NextHash();
        prev->ConnectHash(next);
    }
    inline void AddPointer(HrLinkedPointer<T> *newNode, UINT64 hash) {
        this->m_count++;

        HrLinkedPointer<T> *start = this->m_bucket[ConstrainHash(hash)];
        newNode->NextHash(start);
        newNode->Id(hash);
        if(start != 0) start->PrevHash(newNode);
        this->m_bucket[ConstrainHash(hash)] = newNode;
    }
public:
    HashTable(int m_poolSize) :
            m_bucket(0),
            m_count(0),
            m_converter(0),
            m_paddingBytes(0) {
        this->m_bucket = new HrLinkedPointer<T>*[HashTable<T>::m_itemsCount];
        memset(this->m_bucket, 0, sizeof(HrLinkedPointer<T>*) * HashTable<T>::m_itemsCount);
        this->m_converter = new ItoaConverter();
    }
    HashTable() : HashTable(m_itemsCount / 2) { }
    ~HashTable() {
        if(this->m_bucket != 0)
            delete this->m_bucket;
    }

    void Clear() {
        this->m_count = 0;
        memset(this->m_bucket, 0, sizeof(HrLinkedPointer<T>*) * HashTable<T>::m_itemsCount);
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
    }

    inline HrLinkedPointer<T>* FindPointer(HrLinkedPointer<T>* start, void *owner, UINT64 id) {
        while(start != 0) {
            if(start->Owner() == owner && start->Id() == id)
                return start;
            start = start->NextHash();
        }
        return 0;
    }
    __attribute_noinline__
    void* RemovePointer(HrLinkedPointer<T> *start, void *owner, UINT64 hash) {
        start = start->NextHash();
        while(start != 0) {
            if(start->Owner() == owner && start->Id() == hash) {
                this->Remove(start);
                this->m_count--;
                return start;
            }
            start = start->NextHash();
        }
        return 0;
    }
    inline void* RemovePointer(void *owner, const char *stringId, int length) {
        UINT64 hash = this->CalcHashNoConstrain(stringId, length);
        UINT64 chash = this->ConstrainHash(hash);
        HrLinkedPointer<T> *start = this->m_bucket[chash];

        if(start->Owner() == owner && start->Id() == hash) {
            this->m_bucket[chash] = start->NextHash();
            this->m_count--;
            return start;
        }
        return this->RemovePointer(start, owner, hash);
    }

    inline HrLinkedPointer<T>* GetPointer(void *owner, const char *stringId, int length) {
        UINT64 hash = this->CalcHashNoConstrain(stringId, length);
        HrLinkedPointer<T> *start = this->m_bucket[this->ConstrainHash(hash)];
        return this->FindPointer(start, owner, hash);
    }

    inline HrLinkedPointer<T>* GetPointer(void *owner, UINT64 id) {
        HrLinkedPointer<T> *start = this->m_bucket[this->ConstrainHash(id)];
        return this->FindPointer(start, owner, id);
    }

    inline void RemovePointer(UINT64 hash, HrLinkedPointer<T> *ptr) {
        HrLinkedPointer<T> **start = this->m_bucket + hash;
        if((*start) == ptr) // first item
            (*start) = ptr->NextHash();
        else
            this->Remove(ptr);
        this->m_count--;
    }

    inline void RemovePointer(HrLinkedPointer<T> *ptr) {
        this->RemovePointer(this->ConstrainHash(ptr->Id()), ptr);
    }

    inline void Remove(void *owner, const char *stringId, int length) {
        UINT64 hash = this->CalcHashNoConstrain(stringId, length);
        UINT64 hash2 = this->ConstrainHash(hash);
        HrLinkedPointer<T> *info = this->FindPointer(this->m_bucket[hash2], owner, hash);
        RemovePointer(hash2, info);
    }

    inline void Remove(void *owner, UINT64 id) {
        UINT64 hash = this->ConstrainHash(id);
        HrLinkedPointer<T> *info = this->FindPointer(this->m_bucket[hash], owner, id);
        RemovePointer(hash, info);
    }

    inline void Add(HrLinkedPointer<T> *ptr, UINT64 hash) {
        this->AddPointer(ptr, hash);
    }

    inline void Add(HrLinkedPointer<T> *ptr, void *owner, UINT64 hash) {
        this->AddPointer(ptr, hash);
        ptr->Owner(owner);
    }

    inline void Add(HrLinkedPointer<T> *ptr, const char *stringId, int length) {
        this->Add(ptr, this->CalcHashNoConstrain(stringId, length));
    }

    inline void Add(HrLinkedPointer<T> *ptr, void *owner, const char *stringId, int length) {
        this->Add(ptr, this->CalcHashNoConstrain(stringId, length));
        ptr->Owner(owner);
    }

    inline HrLinkedPointer<T> **Bucket() const { return this->m_bucket; }
};

#endif //HFT_ROBOT_HASHTABLE_H
