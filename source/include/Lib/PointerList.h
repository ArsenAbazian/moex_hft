//
// Created by root on 28.09.16.
//

#ifndef HFT_ROBOT_SIMPLELIST_H
#define HFT_ROBOT_SIMPLELIST_H

#define DEBUG_POINTERLIST

#include <stdio.h>

template <typename T> class PointerList;

template <typename T> class LinkedPointer {
    PointerList<T>  *m_owner;
    LinkedPointer   *m_next;
    LinkedPointer   *m_prev;
    T               *m_data;

public:
    LinkedPointer() :
            m_owner(0),
            m_next(0),
            m_prev(0),
            m_data(0) {
    }

    inline bool HasNext() { return this->m_next != 0; }
    inline LinkedPointer* Next() { return this->m_next; }
    inline void Next(LinkedPointer *node) { this->m_next = node; }
    inline LinkedPointer* Prev() { return this->m_prev; }
    inline void Prev(LinkedPointer *node) { this->m_prev = node; }
    inline T* Data() { return this->m_data; }
    inline void Data(T *data) { this->m_data = data; }
    inline PointerList<T>* Owner() { return this->m_owner; }
    inline void Owner(PointerList<T> *owner) { this->m_owner = owner; }
    inline void Connect(LinkedPointer<T> *next) {
        this->m_next = next;
        if(next != 0)
            next->m_prev = this;
    }
    inline void ConnectHash(LinkedPointer<T> *next) {
        this->m_nextHash = next;
        if(next != 0)
            next->m_prevHash = this;
    }
    inline void ConnectUnsafe(LinkedPointer<T> *next) {
        this->m_next = next;
        next->m_prev = this;
    }
};

template <typename T> class PointerListLite;
class PointerListTester;

template <typename T> class PointerList {
    friend  class PointerListLite<T>;
    friend  class PointerListTester;

    LinkedPointer<T> *m_poolHead;
    LinkedPointer<T> *m_poolTail;

    LinkedPointer<T> *m_head;
    LinkedPointer<T> *m_tail;
    const char       *m_name;

    int              m_capacity;
    int              m_count;
    bool             m_autoAllocate;
    char             m_paddingBytes[7];
public:
    PointerList(int capacity, bool autoAllocate) :
            m_capacity(capacity),
            m_poolHead(0),
            m_poolTail(0),
            m_head(0),
            m_tail(0),
            m_count(0),
            m_autoAllocate(autoAllocate),
            m_name("") {
        this->m_poolHead = new LinkedPointer<T>;
        this->m_poolTail = this->m_poolHead;

        for(int i = 0; i < this->m_capacity + 1; i++) {
            LinkedPointer<T> *ptr = new LinkedPointer<T>;
            ptr->Owner(this);

            this->m_poolTail->Next(ptr);
            this->m_poolTail = ptr;
        }

        this->m_tail = this->m_head = this->Pop();
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_head->Data(0);
        this->m_count = 0;

        if(this->m_autoAllocate)
            AllocData();
    }
    PointerList(int capacity, bool autoAllocate, const char *name) : PointerList(capacity, autoAllocate) {
        this->m_name = name;
    }
    PointerList(int capacity) : PointerList(capacity, false) { }
    PointerList(int capacity, const char *name) : PointerList(capacity, false, name) {
        this->m_name = name;
    }

    inline LinkedPointer<T>* Pop(const char *name) {
        if(this->m_poolHead == this->m_poolTail) {
            this->Append(this->m_capacity, name);
        }
        LinkedPointer<T> *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();
        this->m_count++;
        return node;
    }
    inline LinkedPointer<T>* Pop() {
        if(this->m_poolHead == this->m_poolTail) {
            this->Append(this->m_capacity);
        }
        LinkedPointer<T> *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();
        this->m_count++;
        return node;
    }

    inline void Push(LinkedPointer<T> *node) {
        node->Next(this->m_poolHead);
        this->m_poolHead = node;
        this->m_count--;
#ifdef TEST_CHECK_LIST
        if(this->m_count < 0)
            throw;
#endif
    }

    inline void PushUnsafe(LinkedPointer<T> *node) {
        node->Next(this->m_poolHead);
        this->m_poolHead = node;
        this->m_count--;
#ifdef TEST_CHECK_LIST
        if(this->m_count < 0)
            throw;
#endif
    }

    inline void FreeData() {
        LinkedPointer<T> *s = this->m_poolHead;
        while(true) {
            delete s->Data();
            if(s == this->m_poolTail)
                break;
            s = s->Next();
        }
    }
    inline void AllocData() {
        LinkedPointer<T> *s = this->m_poolHead;
        while(true) {
            s->Data(new T());
            if(s == this->m_poolTail)
                break;
            s = s->Next();
        }
    }
    ~PointerList() {
        this->Clear();

        LinkedPointer<T> *node = this->m_poolHead;
        do {
            if(this->m_autoAllocate)
                delete node->Data();
            LinkedPointer<T> *nextNode = node->Next();
            delete node;
            node = nextNode;
        }
        while(node != this->m_poolTail);
    }

    inline LinkedPointer<T>* Add(T *data) {
        LinkedPointer<T> *node = this->Pop();
        node->Data(data);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        this->m_tail->Next(0);
        return node;
    }

    inline LinkedPointer<T>* Add(LinkedPointer<T> *node) {
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        this->m_tail->Next(0);
        return node;
    }

    inline LinkedPointer<T>* Insert(LinkedPointer<T> *before, T *data) {
        LinkedPointer<T> *node = this->Pop();
        LinkedPointer<T> *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
        return node;
    }

    inline void Insert(LinkedPointer<T> *before, LinkedPointer<T> *node) {
        LinkedPointer<T> *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
    }

    inline LinkedPointer<T> *Pointer(int index) {
        LinkedPointer<T> *node = this->Start();
        while(index > 0) {
            if(node == this->End())
                return 0;
            node = node->Next();
            index--;
        }
        return node;
    }

    inline LinkedPointer<T> *PoolPointer(int index) {
        LinkedPointer<T> *node = this->PoolStart();
        while(index > 0) {
            if(node == this->PoolEnd())
                return 0;
            node = node->Next();
            index--;
        }
        return node;
    }

    inline T* Item(int index) {
        LinkedPointer<T> *node = this->Start();
        while(index > 0) {
            if(node == this->End())
                return 0;
            node = node->Next();
            index--;
        }
        return node->Data();
    }

    inline LinkedPointer<T>* Get(T *data) {
        LinkedPointer<T> *node = this->m_head;
        while(true) {
            if(node->Data() == data)
                return node;
            if(node == this->m_tail)
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void Remove(LinkedPointer<T> *node) {
        LinkedPointer<T> *prev = node->Prev();
        LinkedPointer<T> *next = node->Next();
        if(node == this->m_tail) {
            prev->Next(0);
            this->m_tail = prev;
        }
        else {
            prev->Next(next);
            next->Prev(prev);
        }
        this->Push(node);
    }

    inline void Remove(T *data) {
        LinkedPointer<T> *node = this->Get(data);
        this->Remove(node);
    }

    inline bool IsFull() { return this->m_poolHead == this->m_poolTail; }

    inline LinkedPointer<T>* Append(int capacity, const char *name) {
        printf("!!!unexpected append %s count = %d, additional capacity = %d!!!\n", name, this->m_count, capacity); //TODO remove debug info
        this->m_capacity += capacity;
        LinkedPointer<T> *start = new LinkedPointer<T>();
        LinkedPointer<T> *node = start;
        for(int i = 0; i < capacity; i++) {
            LinkedPointer<T> *ptr = new LinkedPointer<T>;
            ptr->Owner(this);
            node->Next(ptr);
            node = node->Next();
        }
        LinkedPointer<T> *curr = start;
        if(this->m_autoAllocate) {
            for(int i = 0; i < capacity; i++) {
                curr->Data(new T());
                curr = curr->Next();
            }
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        return start;
    }

    __attribute__((noinline))
    LinkedPointer<T>* Append(int capacity) {
        printf("!!!unexpected append %s count = %d, additional capacity = %d!!!\n", this->m_name, this->m_count, capacity); //TODO remove debug info
        this->m_capacity += capacity;
        LinkedPointer<T> *start = new LinkedPointer<T>();
        start->Owner(this);
        LinkedPointer<T> *node = start;
        for(int i = 0; i < capacity - 1; i++) {
            LinkedPointer<T> *next = new LinkedPointer<T>();
            next->Owner(this);
            node->Next(next);
            node = next;
        }

        LinkedPointer<T> *curr = start;
        if(this->m_autoAllocate) {
            for(int i = 0; i < capacity; i++) {
                curr->Data(new T());
                curr = curr->Next();
            }
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        this->m_poolTail->Next(0);
#ifdef  TEST_CHECK_LIST
        if(this->m_autoAllocate) {
            LinkedPointer<T> *ptr = this->m_poolHead;
            while (ptr != 0) {
                if (ptr->Data() == 0)
                    throw;
                ptr = ptr->Next();
            }
        }
#endif
        return start;
    }
    inline LinkedPointer<T>* Start() { return this->m_head->Next(); }
    inline LinkedPointer<T>* End() { return this->m_tail; }
    inline LinkedPointer<T>* Next(LinkedPointer<T> *node) { return node->Next(); }
    inline LinkedPointer<T>* PoolStart() { return this->m_poolHead; }
    inline LinkedPointer<T>* PoolEnd() { return this->m_poolTail; }
    inline int Count() { return this->m_count; }
    inline int Capacity() { return this->m_capacity; }

    inline void Clear() {
        if(this->m_head == this->m_tail)
            return;
        LinkedPointer<T> *st = this->Start();
        LinkedPointer<T> *end = this->End();
        LinkedPointer<T> *node = st;
        this->m_poolTail->Next(st);
        this->m_poolTail = end;
        this->m_tail = this->m_head;
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_count = 0;
    }

    int CopyToArray(T *array) {
        LinkedPointer<T> *node = this->Start();
        if(node == 0)
            return 0;
        int index = 0;
        while(true) {
            array[index] = node->Data();
            index++;
            if(node == this->End())
                return index;
            node = node->Next();
        }
    }
    inline int CalcPoolCount() {
        int sum = 0;
        LinkedPointer<T> *ptr = this->m_poolHead;
        while(true) {
            sum++;
            if(ptr == this->m_poolTail)
                break;
            ptr = ptr->Next();
        }
        // why - 1? becasue capacity = + 1 see constructor
        return sum - 1;
    }
};

template <typename T> class PointerListLite {
    PointerList<T>      *m_pool;

    LinkedPointer<T>    *m_head;
    LinkedPointer<T>    *m_tail;
    int                 m_count;
    int                 m_paddingBytes;
public:
    PointerListLite(PointerList<T> *globalPool) {
        this->m_pool = globalPool;
        this->m_head = this->m_tail = this->m_pool->Pop();
        this->m_tail->Next(0);
        this->m_head->Prev(0);
        this->m_count = 0;
        this->m_paddingBytes = 0;
    }
    ~PointerListLite() {
        Clear();
    }
    inline void Clear() {
        if(this->m_count == 0)
            return;
        this->m_pool->m_poolTail->Next(this->m_head->Next());
        this->m_head->Prev(this->m_pool->m_poolTail);
        this->m_pool->m_poolTail = this->m_tail;
        this->m_pool->m_count -= this->m_count;
        this->m_count = 0;
        this->m_tail = this->m_head;
        this->m_head->Next(0);
    }
    inline LinkedPointer<T>* Start() { return this->m_head->Next(); }
    inline LinkedPointer<T>* End() { return this->m_tail; }
    inline LinkedPointer<T>* Last() { return this->m_tail; }
    inline LinkedPointer<T>* Next(LinkedPointer<T> *node) { return node->Next(); }
    inline int Count() { return this->m_count; }

    inline LinkedPointer<T>* Add(const char *name) {
        LinkedPointer<T> *node = this->m_pool->Pop(name);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        node->Next(0);
        this->m_count++;
        return node;
    }
    inline LinkedPointer<T>* Add(T *data, const char *name) {
        LinkedPointer<T> *node = this->Add(name);
        node->Data(data);
        return node;
    }

    inline LinkedPointer<T>* Add() {
        LinkedPointer<T> *node = this->m_pool->Pop();
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        node->Next(0);
        this->m_count++;
        return node;
    }
    inline LinkedPointer<T>* Add(T *data) {
        LinkedPointer<T> *node = this->Add();
        node->Data(data);
        return node;
    }

    inline LinkedPointer<T>* Insert(LinkedPointer<T> *insertBefore, const char *name) {
        LinkedPointer<T> *node = this->m_pool->Pop(name);
        LinkedPointer<T> *prev = insertBefore->Prev();
        node->Prev(prev);
        prev->Next(node);
        node->Next(insertBefore);
        insertBefore->Prev(node);
        this->m_count++;
        return node;
    }
    inline LinkedPointer<T>* Insert(LinkedPointer<T> *insertBefore, T *data, const char *name) {
        LinkedPointer<T> *node = this->Insert(insertBefore, name);
        node->Data(data);
        return node;
    }

    inline LinkedPointer<T>* Insert(LinkedPointer<T> *insertBefore) {
        LinkedPointer<T> *node = this->m_pool->Pop();
        LinkedPointer<T> *prev = insertBefore->Prev();
        node->Prev(prev);
        prev->Next(node);
        node->Next(insertBefore);
        insertBefore->Prev(node);
        this->m_count++;
        return node;
    }
    inline LinkedPointer<T>* Insert(LinkedPointer<T> *insertBefore, T *data) {
        LinkedPointer<T> *node = this->Insert(insertBefore);
        node->Data(data);
        return node;
    }
    inline void Remove(LinkedPointer<T> *node) {
        LinkedPointer<T> *prev = node->Prev();
        LinkedPointer<T> *next = node->Next();
        prev->Next(next);
        if(next != 0) {
            next->Prev(prev);
        }
        else {
            this->m_tail = prev;
        }
        this->m_count--;
        this->m_pool->Push(node);
#ifdef TEST_CHECK_LIST
        if(this->m_count < 0)
            throw;
#endif
    }
    inline T* Item(int index) {
        LinkedPointer<T> *node = this->Start();
        while(index > 0) {
            if(node == this->End())
                return 0;
            node = node->Next();
            index--;
        }
        return node->Data();
    }

    inline LinkedPointer<T>* Get(T *data) {
        LinkedPointer<T> *node = this->m_head;
        while(true) {
            if(node->Data() == data)
                return node;
            if(node == this->m_tail)
                break;
            node = node->Next();
        }
        return 0;
    }

    inline int IndexOf(LinkedPointer<T> *item) {
        LinkedPointer<T> *node = this->Start();
        int index = 0;
        while(true) {
            if(node == item)
                return index;
            if(node == this->m_tail)
                break;
            node = node->Next();
            index++;
        }
        return -1;
    }
};

#endif //HFT_ROBOT_SIMPLELIST_H
