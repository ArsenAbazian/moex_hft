//
// Created by root on 28.09.16.
//

#ifndef HFT_ROBOT_SIMPLELIST_H
#define HFT_ROBOT_SIMPLELIST_H

class SimpleListNode {
    SimpleListNode *m_next;
    SimpleListNode *m_prev;
    void            *m_data;
public:
    SimpleListNode() {
        this->m_next = 0;
        this->m_data = 0;
        this->m_prev = 0;
    }

    inline SimpleListNode* Next() { return this->m_next; }
    inline void Next(SimpleListNode *node) { this->m_next = node; }
    inline SimpleListNode* Prev() { return this->m_prev; }
    inline void Prev(SimpleListNode *node) { this->m_prev = node; }
    inline void* Data() { return this->m_data; }
    inline void Data(void *data) { this->m_data = data; }
};

class SimpleList {
    int             m_capacity;

    SimpleListNode *m_poolHead;
    SimpleListNode *m_poolTail;

    SimpleListNode *m_head;
    SimpleListNode *m_tail;
    int             m_count;

public:
    inline SimpleListNode* Pop() {
        SimpleListNode *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();

        return node;
    }

    inline void Push(SimpleListNode *node) {
        this->m_poolTail->Next(node);
        this->m_poolTail = node;
    }
    SimpleList(int capacity) {
        this->m_capacity = capacity;
        this->m_count = 0;

        this->m_poolHead = new SimpleListNode;
        this->m_poolTail = this->m_poolHead;

        for(int i = 0; i < this->m_capacity; i++)
            this->Push(new SimpleListNode);

        this->m_tail = this->m_head = this->Pop();
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_head->Data(this);
    }
    ~SimpleList() {
        while(this->m_head != this->m_tail)
            this->Remove(this->m_head->Next());

        SimpleListNode *node = this->m_poolHead;
        do {
            delete node;
            node = node->Next();
        }
        while(node != this->m_tail);
    }

    inline void Add(void *data) {
        SimpleListNode *node = this->Pop();
        node->Data(data);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        this->m_count++;
    }

    inline void Insert(SimpleListNode *before, void *data) {
        SimpleListNode *node = this->Pop();
        SimpleListNode *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
    }

    inline SimpleListNode* Get(void *data) {
        SimpleListNode *node = this->m_head;
        while(node != this->m_tail) {
            if(node->Data() == data)
                return node;
        }
        return 0;
    }

    inline void Remove(SimpleListNode *node) {
        SimpleListNode *prev = node->Prev();
        SimpleListNode *next = node->Next();
        prev->Next(next);
        next->Prev(prev);
        this->Push(node);
        this->m_count--;
    }

    inline void Remove(void *data) {
        SimpleListNode *node = this->Get(data);
        this->Remove(node);
    }

    inline bool IsFull() { return this->m_poolHead == this->m_poolTail; }
    inline SimpleListNode* Append(int capacity) {
        this->m_capacity += capacity;
        SimpleListNode *start = new SimpleListNode();
        SimpleListNode *node = start;
        for(int i = 0; i < capacity; i++) {
            node->Next(new SimpleListNode());
            node = node->Next();
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        return start;
    }
    inline SimpleListNode* Start() { return this->m_head->Next(); }
    inline SimpleListNode* End() { return this->m_tail; }
    inline SimpleListNode* Next(SimpleListNode *node) { return node->Next(); }
    inline SimpleListNode* PoolStart() { return this->m_poolHead; }
    inline SimpleListNode* PoolEnd() { return this->m_poolTail; }

    inline void Clear() {
        if(this->m_head == this->m_tail)
            return;
        SimpleListNode *st = this->m_head->Next();
        SimpleListNode *end = this->m_tail;
        this->m_poolTail->Next(st);
        this->m_poolTail = end;
        this->m_count = 0;
    }
};

#endif //HFT_ROBOT_SIMPLELIST_H
