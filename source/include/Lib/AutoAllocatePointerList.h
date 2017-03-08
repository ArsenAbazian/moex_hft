//
// Created by root on 29.09.16.
//

#ifndef HFT_ROBOT_ORDERBOOKINFOLIST_H
#define HFT_ROBOT_ORDERBOOKINFOLIST_H

#include "Lib/PointerList.h"
#include "Fast/FastTypes.h"

template<typename T> class AutoAllocatePointerList {
    int                 m_addCapacity;
    int                 m_count;
    int                 m_capacity;
    LinkedPointer<T>    *m_head;
    LinkedPointer<T>    *m_tail;
    LinkedPointer<T>    *m_usedHead;
    LinkedPointer<T>    *m_usedTail;
    const char          *m_name;

    inline void Allocate(LinkedPointer<T> *start, LinkedPointer<T> *end) {
        while(true) {
            T *t = new T;
            t->Pointer = start;
            t->Allocator = this;
            start->Data(t);
            if(start == end)
                break;
            start = start->Next();
        }
    }

    inline LinkedPointer<T>* CreatePointer() {
        LinkedPointer<T> *node = new LinkedPointer<T>();
        T *t = new T();
        t->Pointer = node;
        t->Allocator = this;
        node->Data(t);
        return node;
    }
    inline LinkedPointer<T>* CreatePointers(LinkedPointer<T> *start, int count) {
        count--;
        for(int i = 0; i < count; i++) {
            LinkedPointer<T> *node = CreatePointer();
            start->Next(node);
            start = node;
        }
        return start;
    }
    inline void Connect(LinkedPointer<T> *prev, LinkedPointer<T> *next) {
        prev->Next(next);
        next->Prev(prev);
    }
    inline void AddUsed(LinkedPointer<T> *node) {
        this->Connect(this->m_usedTail->Prev(), node);
        this->Connect(node, this->m_usedTail);
    }
    inline void RemoveUsed(LinkedPointer<T> *node) {
        this->Connect(node->Prev(), node->Next());
    }
public:
    AutoAllocatePointerList(int capacity, int additionalCapacity) {
        this->m_count = 0;
        this->m_addCapacity = additionalCapacity;
        this->m_capacity = capacity;
        this->m_head = CreatePointer();
        this->m_tail = CreatePointers(this->m_head, capacity);
        this->m_name = "";

        this->m_usedHead = new LinkedPointer<T>();
        this->m_usedTail = new LinkedPointer<T>();
        this->Connect(this->m_usedHead, this->m_usedTail);
    }
    AutoAllocatePointerList(int capacity, int additionalCapacity, const char *name) :
            AutoAllocatePointerList(capacity, additionalCapacity) {
        this->m_name = name;
    }
    void Append(int count) {
        LinkedPointer<T> *head = CreatePointer();
        LinkedPointer<T> *tail = CreatePointers(head, count - 1);
        this->Connect(this->m_tail, head);
        this->m_tail = tail;
        this->m_capacity += count;
    }
    void AddCount(int addCount) {
        this->m_addCapacity = addCount;
    }
    inline T* NewItem() {
        this->m_count++;
        LinkedPointer<T> *node = this->m_head;
        this->m_head = this->m_head->Next();
        node->Released(false);
        this->AddUsed(node);

        if(this->m_head == 0) {
            printf("!!!unexpected append %s count = %d, additional capacity = %d!!!\n", this->m_name, this->m_count, this->m_addCapacity); //TODO remove debug info
            this->m_head = CreatePointer();
            this->m_tail = this->CreatePointers(this->m_head, this->m_addCapacity);
            this->m_capacity += this->m_addCapacity;
        }
        return node->Data();
    }
    inline void FreeItem(LinkedPointer<T> *node) {
        if(node->Data()->Used || node->Released())
            return;
        node->Released(true);
        this->m_count--;
        this->m_tail->Next(node);
        this->m_tail = node;
        this->RemoveUsed(node);
        this->m_tail->Next(0);
    }
    inline void FreeItem(T *data) {
        FreeItem(data->Pointer);
    }
    inline int Count() { return this->m_count; }
    inline int Capacity() { return this->m_capacity; }
    inline LinkedPointer<T> *Start() { return this->m_head; }
    inline LinkedPointer<T> *End() { return this->m_tail; }
    inline LinkedPointer<T> *UsedStart() { return this->m_usedHead->Next(); }
    inline LinkedPointer<T> *UsedEnd() { return this->m_usedTail; }
    inline void Clear() {
        if(this->m_count == 0)
            return;
        this->m_count = 0;
        this->m_tail->Next(this->m_usedHead->Next());
        this->m_tail = this->m_usedTail->Prev();
        this->m_tail->Next(0);
        this->Connect(this->m_usedHead, this->m_usedTail);
    }
    int CalcFreeItemsCount() {
        LinkedPointer<T> *node = this->m_head;
        int count = 0;
        while(node != 0) {
            count++;
            node = node->Next();
        }
        return count;
    }
    int CalcUsedItemsCount() {
        LinkedPointer<T> *node = this->m_usedHead->Next();
        int count = 0;
        while(node != this->m_usedTail) {
            count++;
            node = node->Next();
        }
        return count;
    }
};

#endif //HFT_ROBOT_ORDERBOOKINFOLIST_H
