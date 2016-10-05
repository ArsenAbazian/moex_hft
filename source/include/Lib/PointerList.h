//
// Created by root on 28.09.16.
//

#ifndef HFT_ROBOT_SIMPLELIST_H
#define HFT_ROBOT_SIMPLELIST_H

class PointerList;

class LinkedPointer {
    PointerList     *m_owner;
    LinkedPointer   *m_next;
    LinkedPointer   *m_prev;
    void            *m_data;
public:
    LinkedPointer() {
        this->m_next = 0;
        this->m_data = 0;
        this->m_prev = 0;
    }

    inline LinkedPointer* Next() { return this->m_next; }
    inline void Next(LinkedPointer *node) { this->m_next = node; }
    inline LinkedPointer* Prev() { return this->m_prev; }
    inline void Prev(LinkedPointer *node) { this->m_prev = node; }
    inline void* Data() { return this->m_data; }
    inline void Data(void *data) { this->m_data = data; }
    inline PointerList* Owner() { return this->m_owner; }
    inline void Owner(PointerList *owner) { this->m_owner = owner; }
};

class PointerList {
    int             m_capacity;

    LinkedPointer *m_poolHead;
    LinkedPointer *m_poolTail;

    LinkedPointer *m_head;
    LinkedPointer *m_tail;
    int             m_count;

public:
    inline LinkedPointer* Pop() {
        LinkedPointer *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();

        return node;
    }

    inline void Push(LinkedPointer *node) {
        this->m_poolTail->Next(node);
        this->m_poolTail = node;
    }
    PointerList(int capacity) {
        this->m_capacity = capacity;
        this->m_count = 0;

        this->m_poolHead = new LinkedPointer;
        this->m_poolTail = this->m_poolHead;

        for(int i = 0; i < this->m_capacity; i++) {
            LinkedPointer *ptr = new LinkedPointer;
            ptr->Owner(this);
            this->Push(ptr);
        }

        this->m_tail = this->m_head = this->Pop();
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_head->Data(this);
    }
    ~PointerList() {
        while(this->m_head != this->m_tail)
            this->Remove(this->m_head->Next());

        LinkedPointer *node = this->m_poolHead;
        do {
            delete node;
            node = node->Next();
        }
        while(node != this->m_tail);
    }

    inline void Add(void *data) {
        LinkedPointer *node = this->Pop();
        node->Data(data);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        this->m_count++;
    }

    inline void Insert(LinkedPointer *before, void *data) {
        LinkedPointer *node = this->Pop();
        LinkedPointer *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
    }

    inline LinkedPointer* Get(void *data) {
        LinkedPointer *node = this->m_head;
        while(node != this->m_tail) {
            if(node->Data() == data)
                return node;
        }
        return 0;
    }

    inline void Remove(LinkedPointer *node) {
        LinkedPointer *prev = node->Prev();
        LinkedPointer *next = node->Next();
        prev->Next(next);
        next->Prev(prev);
        this->Push(node);
        this->m_count--;
    }

    inline void Remove(void *data) {
        LinkedPointer *node = this->Get(data);
        this->Remove(node);
    }

    inline bool IsFull() { return this->m_poolHead == this->m_poolTail; }
    inline LinkedPointer* Append(int capacity) {
        this->m_capacity += capacity;
        LinkedPointer *start = new LinkedPointer();
        LinkedPointer *node = start;
        for(int i = 0; i < capacity; i++) {
            LinkedPointer *ptr = new LinkedPointer;
            ptr->Owner(this);
            node->Next(ptr);
            node = node->Next();
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        return start;
    }
    inline LinkedPointer* Start() { return this->m_head->Next(); }
    inline LinkedPointer* End() { return this->m_tail; }
    inline LinkedPointer* Next(LinkedPointer *node) { return node->Next(); }
    inline LinkedPointer* PoolStart() { return this->m_poolHead; }
    inline LinkedPointer* PoolEnd() { return this->m_poolTail; }

    inline void Clear() {
        if(this->m_head == this->m_tail)
            return;
        LinkedPointer *st = this->m_head->Next();
        LinkedPointer *end = this->m_tail;
        this->m_poolTail->Next(st);
        this->m_poolTail = end;
        this->m_count = 0;
    }
};

#endif //HFT_ROBOT_SIMPLELIST_H
