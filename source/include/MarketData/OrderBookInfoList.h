//
// Created by root on 29.09.16.
//

#ifndef HFT_ROBOT_ORDERBOOKINFOLIST_H
#define HFT_ROBOT_ORDERBOOKINFOLIST_H

#include "../Lib/SimpleList.h"
#include "OrderBookInfo.h"

class OrderBookInfoList {
    SimpleList      *m_list;
    int             m_addCapacity;

    inline void AllocateOrderBookInfo(SimpleListNode *start, SimpleListNode *end) {
        do {
            start->Data(new OrderBookInfo());
            start = start->Next();
        }
        while(start != end);
    }
public:
    OrderBookInfoList(int capacity, int additionalCapacity) {
        this->m_addCapacity = additionalCapacity;
        this->m_list = new SimpleList(capacity);
        this->AllocateOrderBookInfo(this->m_list->PoolStart(), this->m_list->PoolEnd());
    }
    inline SimpleListNode* GetItem() {
        if(this->m_list->IsFull()) {
            SimpleListNode *node = this->m_list->Append(this->m_addCapacity);
            this->AllocateOrderBookInfo(node, this->m_list->PoolEnd());
        }
        return this->m_list->Pop();
    }
    inline void FreeItem(SimpleListNode *node) {
        this->m_list->Push(node);
    }
};

#endif //HFT_ROBOT_ORDERBOOKINFOLIST_H
