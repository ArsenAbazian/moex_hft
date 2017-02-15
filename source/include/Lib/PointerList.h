//
// Created by root on 28.09.16.
//

#ifndef HFT_ROBOT_SIMPLELIST_H
#define HFT_ROBOT_SIMPLELIST_H

#include <stdio.h>

template <typename T> class PointerList;

template <typename T> class LinkedPointer {
    PointerList<T>  *m_owner;
    LinkedPointer   *m_next;
    LinkedPointer   *m_prev;
    T               *m_data;
    bool             m_released;
public:
    LinkedPointer() {
        this->m_next = 0;
        this->m_data = 0;
        this->m_prev = 0;
        this->m_released = true;
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
    inline bool Released() { return this->m_released; }
    inline void Released(bool released) { this->m_released = released; }
};

template <typename T> class PointerListLite;

template <typename T> class PointerList {
    friend  class PointerListLite<T>;
    int             m_capacity;

    LinkedPointer<T> *m_poolHead;
    LinkedPointer<T> *m_poolTail;

    LinkedPointer<T> *m_head;
    LinkedPointer<T> *m_tail;
    int              m_count;
    bool             m_autoAllocate;

public:
    inline LinkedPointer<T>* Pop() {
        if(this->m_poolHead == this->m_poolTail) {
            this->Append(this->m_capacity);
        }
        LinkedPointer<T> *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();
        this->m_count++;
        node->Released(false);
        return node;
    }

    inline void Push(LinkedPointer<T> *node) {
        if(node->Released())
            return;
        node->Released(true);
        this->m_poolTail->Next(node);
        this->m_poolTail = node;
        this->m_count--;
    }
    PointerList(int capacity, bool autoAllocate) {
        this->m_capacity = capacity;
        this->m_count = 0;
        this->m_autoAllocate = autoAllocate;

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
    PointerList(int capacity) : PointerList(capacity, false) { }
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
            delete node;
            node = node->Next();
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
    inline LinkedPointer<T>* Append(int capacity) {
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
        printf("!!!unexpected append!!!\n"); //TODO remove debug info
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
        while(true) {
            node->Released(true);
            if(node == end)
                break;
            node = node->Next();
        }
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
public:
    PointerListLite(PointerList<T> *globalPool) {
        this->m_pool = globalPool;
        this->m_head = this->m_tail = this->m_pool->Pop();
        this->m_tail->Next(0);
        this->m_head->Prev(0);
        this->m_count = 0;
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
    inline LinkedPointer<T>* Next(LinkedPointer<T> *node) { return node->Next(); }
    inline int Count() { return this->m_count; }

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
};

#endif //HFT_ROBOT_SIMPLELIST_H
