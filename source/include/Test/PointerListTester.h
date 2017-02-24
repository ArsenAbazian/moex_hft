//
// Created by root on 12.01.17.
//

#ifndef HFT_ROBOT_POINTERLISTTESTER_H
#define HFT_ROBOT_POINTERLISTTESTER_H
#include "Settings.h"

#ifdef TEST

#include "../Lib/PointerList.h"

class SimpleData {
public:
    int a;
};

class PointerListTester {
public:

    void TestAdditionalAllocate() {
        PointerList<SimpleData> *list = new PointerList<SimpleData>(10);
        for(int i = 0; i < 10; i++)
            list->Add(new SimpleData());
        if(list->Capacity() != 10)
            throw;
        list->Add(new SimpleData());
        if(list->Capacity() != 20)
            throw;

        if(list->m_poolTail->Next() != 0)
            throw;

        int index = 0;
        LinkedPointer<SimpleData> *ptr = list->m_poolHead;
        while(ptr != list->m_poolTail) {
            index++;
            ptr = ptr->Next();
            if(ptr == 0)
                throw;
        }

        list->Clear();
        ptr = list->m_poolHead;
        while(ptr != list->m_poolTail) {
            index++;
            ptr = ptr->Next();
            if(ptr == 0)
                throw;
        }

        delete list;
    }

    void TestDispose() {
        PointerList<SimpleData> *list = new PointerList<SimpleData>(10);
        delete list;

        list = new PointerList<SimpleData>(10);
        for(int i = 0; i < 5; i++)
            list->Add(new SimpleData());
        delete list;

        list = new PointerList<SimpleData>(10);
        list->Append(10);
        LinkedPointer<SimpleData> *ptr = list->m_poolHead;
        int index = 0;
        while(ptr != list->m_poolTail) {
            ptr->Released(false);
            ptr = ptr->Next();
            index++;
        }
        delete list;
    }

    void TestDefault() {
        PointerList<SimpleData> *list = new PointerList<SimpleData>(10);
        if(list->Capacity() != 10)
            throw;
        if(list->CalcPoolCount() != 10)
            throw;
        if(list->Count() != 0)
            throw;
        LinkedPointer<SimpleData> *ptr = list->PoolStart();
        while(ptr != list->PoolEnd()) {
            if(!ptr->Released())
                throw;
            ptr = ptr->Next();
        }

        list->Add(new SimpleData());
        if(list->Count() != 1)
            throw;
        if(list->CalcPoolCount() != list->Capacity() - 1)
            throw;
        if(list->Start()->Released())
            throw;

        delete list;
    }

    void TestClear() {
        PointerList<SimpleData> *list = new PointerList<SimpleData>(10);
        for(int i = 0; i < 10; i++)
            list->Add(new SimpleData());
        for(int i = 0; i < 10; i++) {
            if(list->Pointer(i)->Released())
                throw;
        }

        list->Clear();
        for(int i = 0; i < 10; i++) {
            if(!list->PoolPointer(i)->Released())
                throw;
        }
    }

    void TestPointerListLiteAddRemove() {
        PointerList<SimpleData> *pool = new PointerList<SimpleData>(100, true);
        PointerListLite<SimpleData> *list = new PointerListLite<SimpleData>(pool);

        if(list->Count() != 0)
            throw;
        if(list->Start() != 0)
            throw;
        if(pool->Count() != 1)
            throw;
        if(pool->CalcPoolCount() != 99)
            throw;
        if(list->End()->Next() != 0)
            throw;

        list->Add();
        if(list->Count() != 1)
            throw;
        if(list->Start() == 0)
            throw;
        if(pool->Count() != 2)
            throw;
        if(pool->CalcPoolCount() != 98)
            throw;
        if(list->End()->Next() != 0)
            throw;

        list->Add();
        if(list->Count() != 2)
            throw;
        if(list->Start() == 0)
            throw;
        if(pool->Count() != 3)
            throw;
        if(pool->CalcPoolCount() != 97)
            throw;
        if(list->End()->Next() != 0)
            throw;

        list->Add();
        if(list->Count() != 3)
            throw;
        if(list->End()->Next() != 0)
            throw;

        LinkedPointer<SimpleData> *i0 = list->Start();
        LinkedPointer<SimpleData> *i1 = list->Start()->Next();
        LinkedPointer<SimpleData> *i2 = list->Start()->Next()->Next();

        list->Remove(list->Start()->Next());
        if(list->Count() != 2)
            throw;
        if(pool->Count() != 3)
            throw;
        if(pool->CalcPoolCount() != 97)
            throw;
        if(list->Start() != i0)
            throw;
        if(list->Start()->Next() != i2)
            throw;
        if(list->End() != i2)
            throw;
        if(list->End()->Next() != 0)
            throw;

        list->Remove(list->End());
        if(list->Count() != 1)
            throw;
        if(pool->Count() != 2)
            throw;
        if(pool->CalcPoolCount() != 98)
            throw;
        if(list->Start() != i0)
            throw;
        if(list->End()->Next() != 0)
            throw;

        list->Remove(i0);
        if(list->Count() != 0)
            throw;
        if(pool->Count() != 1)
            throw;
        if(pool->CalcPoolCount() != 99)
            throw;
        if(list->Start() != 0)
            throw;
        if(list->End()->Next() != 0)
            throw;
    }

    void TestPointerListLiteInsert() {
        PointerList<SimpleData> *pool = new PointerList<SimpleData>(100, false);
        PointerListLite<SimpleData> *list = new PointerListLite<SimpleData>(pool);

        list->Add();
        LinkedPointer<SimpleData> *i0 = list->Start();
        LinkedPointer<SimpleData> *newi0 = list->Insert(list->Start());

        if(list->Start() != newi0)
            throw;
        if(list->Count() != 2)
            throw;
        if(pool->Count() != 3)
            throw;
        if(pool->CalcPoolCount() != 97)
            throw;
        if(newi0->Next() != i0)
            throw;
        if(i0->Prev() != newi0)
            throw;
        if(list->End() != i0)
            throw;
        if(list->End()->Next() != 0)
            throw;

        LinkedPointer<SimpleData> *i1 = list->Insert(i0);
        if(list->Count() != 3)
            throw;
        if(pool->Count() != 4)
            throw;
        if(pool->CalcPoolCount() != 96)
            throw;
        if(list->Start() != newi0)
            throw;
        if(newi0->Next() != i1)
            throw;
        if(i1->Prev() != newi0)
            throw;
        if(list->End() != i0)
            throw;
        if(i0->Prev() != i1)
            throw;
        if(i1->Next() != i0)
            throw;
        if(list->End()->Next() != 0)
            throw;
    }

    void TestPointerListLiteClear() {
        PointerList<SimpleData> *pool = new PointerList<SimpleData>(100, false);
        PointerListLite<SimpleData> *list = new PointerListLite<SimpleData>(pool);

        list->Clear();
        if(list->Start() != 0)
            throw;
        if(list->Count() != 0)
            throw;
        if(list->End() == 0)
            throw;
        if(pool->Count() != 1)
            throw;
        if(pool->CalcPoolCount() != 99)
            throw;

        list->Add();
        list->Clear();

        if(list->Start() != 0)
            throw;
        if(list->Count() != 0)
            throw;
        if(list->End() == 0)
            throw;
        if(pool->Count() != 1)
            throw;
        if(pool->CalcPoolCount() != 99)
            throw;

        list->Add();
        list->Add();
        list->Clear();

        if(list->Start() != 0)
            throw;
        if(list->Count() != 0)
            throw;
        if(list->End() == 0)
            throw;
        if(pool->Count() != 1)
            throw;
        if(pool->CalcPoolCount() != 99)
            throw;

        list->Add();
        list->Insert(list->Start());
        list->Insert(list->Start());
        list->Clear();

        if(list->Start() != 0)
            throw;
        if(list->Count() != 0)
            throw;
        if(list->End() == 0)
            throw;
        if(pool->Count() != 1)
            throw;
        if(pool->CalcPoolCount() != 99)
            throw;
    }

    void TestPointerListLiteAppend() {
        PointerList<SimpleData> *pool = new PointerList<SimpleData>(10000, true);
        PointerListLite<SimpleData> *list = new PointerListLite<SimpleData>(pool);

        LinkedPointer<SimpleData> *ptr = pool->m_poolHead;
        while(ptr != 0) {
            if(ptr->Data() == 0)
                throw;
            ptr = ptr->Next();
        }
        while(pool->m_poolHead != pool->m_poolTail) {
            list->Add();
        }
        LinkedPointer<SimpleData> *ptr2 = list->Add();
        if(pool->Capacity() != 20000)
            throw;
        if(ptr2->Data() == 0)
            throw;

        ptr = pool->m_poolHead;
        int index = 0;
        while(ptr != 0) {
            if(ptr->Data() == 0)
                throw;
            ptr = ptr->Next();
            index++;
        }

        while(pool->m_poolHead != pool->m_poolTail) {
            list->Add();
        }

        ptr2 = list->Add();
        if(pool->Capacity() != 40000)
            throw;

        ptr = pool->m_poolHead;
        while(ptr != 0) {
            if(ptr->Data() == 0)
                throw;
            ptr = ptr->Next();
        }
    }

    void TestPointerListLiteAppend2() {
        PointerList<SimpleData> *pool = new PointerList<SimpleData>(10000, true);
        PointerListLite<SimpleData> *list = new PointerListLite<SimpleData>(pool);

        for(int i = 0; i < 30000; i++) {
            LinkedPointer<SimpleData> *ptr = list->Add();
            if(ptr->Data() == 0)
                throw;
        }
        delete list;
        delete pool;
    }

    void TestPointerListLite() {
        TestPointerListLiteAddRemove();
        TestPointerListLiteInsert();
        TestPointerListLiteClear();
        TestPointerListLiteAppend();
        TestPointerListLiteAppend2();
    }

    void Test() {
        TestDefault();
        TestDispose();
        TestAdditionalAllocate();
        TestClear();
        TestPointerListLite();
    }
};

#endif //TEST
#endif //HFT_ROBOT_POINTERLISTTESTER_H
