//
// Created by root on 12.01.17.
//

#ifndef HFT_ROBOT_POINTERLISTTESTER_H
#define HFT_ROBOT_POINTERLISTTESTER_H
#include "../Settings.h"

#ifdef TEST

#include "../Lib/PointerList.h"
#include "../Lib/AutoAllocatePointerList.h"

class SimpleData {
public:
    LinkedPointer<SimpleData>           *Pointer;
    AutoAllocatePointerList<SimpleData> *Allocator;
    int                                 a;
    bool                                Used;
    char                                m_paddingBytes[3];
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
            //ptr->Released(false);
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
        //while(ptr != list->PoolEnd()) {
        //    if(!ptr->Released())
        //        throw;
        //    ptr = ptr->Next();
        //}

        list->Add(new SimpleData());
        if(list->Count() != 1)
            throw;
        if(list->CalcPoolCount() != list->Capacity() - 1)
            throw;
        //if(list->Start()->Released())
        //    throw;

        delete list;
    }

    void TestClear() {
        PointerList<SimpleData> *list = new PointerList<SimpleData>(10);
        for(int i = 0; i < 10; i++)
            list->Add(new SimpleData());
        //for(int i = 0; i < 10; i++) {
        //    if(list->Pointer(i)->Released())
        //        throw;
        //}

        list->Clear();
        if(list->Start() != 0)
            throw;
        if(list->CalcPoolCount() != 10)
            throw;
        //for(int i = 0; i < 10; i++) {
        //    if(!list->PoolPointer(i)->Released())
        //        throw;
        //}
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

    void TestPointerList() {
        TestDefault();
        TestDispose();
        TestAdditionalAllocate();
        TestClear();
    }

    void TestDefaultAutoAllocate() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        if(list->Count() != 0)
            throw;
        if(list->Capacity() != 10)
            throw;
        if(list->End()->Next() != 0)
            throw;
        if(list->CalcFreeItemsCount() != 10)
            throw;
        if(list->CalcUsedItemsCount() != 0)
            throw;
    }

    void TestNewItem() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        SimpleData *data = list->NewItem();
        if(data->Allocator != list)
            throw;
        if(data->Pointer == 0)
            throw;
        //if(data->Pointer->Released())
        //    throw;
        if(list->Count() != 1)
            throw;
        if(list->CalcFreeItemsCount() != 9)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        for(int i = 0; i < 8; i++) {
            SimpleData *d = list->NewItem();
            if(list->Count() != 2 + i)
                throw;
            if(list->CalcFreeItemsCount() != 10 - list->Count())
                throw;
            if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
                throw;
        }
        list->NewItem();
        if(list->Count() != 10)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcFreeItemsCount() != 2)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
    }

    void TestAutoAllocate() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        for(int i = 0; i < 10; i++)
            list->NewItem();
        if(list->Count() != 10)
            throw;
        if(list->CalcFreeItemsCount() != 2)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->NewItem();
        if(list->Count() != 11)
            throw;
        if(list->CalcFreeItemsCount() != 1)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->NewItem();
        if(list->Count() != 12)
            throw;
        if(list->CalcFreeItemsCount() != 2)
            throw;
        if(list->Capacity() != 14)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->NewItem();
        if(list->Count() != 13)
            throw;
        if(list->Capacity() != 14)
            throw;
        if(list->CalcFreeItemsCount() != 1)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
    }

    void TestFree() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        SimpleData *data[10];
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        list->FreeItem(data[0]);
        //if(!data[0]->Pointer->Released())
        //    throw;
        if(list->Count() != 9)
            throw;
        if(list->CalcFreeItemsCount() != 3)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        //list->FreeItem(data[0]);
        //if(list->Count() != 9)
        //    throw;
        if(list->CalcFreeItemsCount() != 3)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        for(int i = 1; i < 10; i++) {
            list->FreeItem(data[i]);
            if(list->Capacity() != 12)
                throw;
            if(list->Count() != 9 - i)
                throw;
            if(list->CalcFreeItemsCount() != 12 - list->Count())
                throw;
            if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
                throw;
        }
    }

    void TestFree2() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        SimpleData *data[10];

        int *index = new int[10] { 5, 3, 4, 9, 6, 2, 7, 1, 0, 8 };
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        for(int i = 0; i < 10; i++) {
            list->FreeItem(data[index[i]]);
            if (list->CalcUsedItemsCount() != 9 - i)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity() - list->CalcUsedItemsCount())
                throw;
        }

        index = new int[10] { 8, 0, 5, 6, 9, 1, 2, 4, 7, 3 };
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        for(int i = 0; i < 10; i++) {
            list->FreeItem(data[index[i]]);
            if (list->CalcUsedItemsCount() != 9 - i)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity() - list->CalcUsedItemsCount())
                throw;
        }

        index = new int[10] { 5, 1, 2, 8, 4, 9, 7, 6, 0, 3 };
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        for(int i = 0; i < 10; i++) {
            list->FreeItem(data[index[i]]);
            if (list->CalcUsedItemsCount() != 9 - i)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity() - list->CalcUsedItemsCount())
                throw;
        }
    }

    void TestClearAutoAllocate() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);

        for(int j = 1; j < 100; j++) {
            for (int i = 0; i < j; i++)
                list->NewItem();

            list->Clear();

            if (list->Count() != 0)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity())
                throw;
            if (list->CalcUsedItemsCount() != 0)
                throw;
        }
    }

    void TestAutoAllocatePointerList() {
        TestDefaultAutoAllocate();
        TestNewItem();
        TestFree();
        TestFree2();
        TestAutoAllocate();
        TestClearAutoAllocate();
    }
    
    
#pragma region Hr
/*
    void TestHrAdditionalAllocate() {
        HrPointerList<SimpleData> *list = new HrPointerList<SimpleData>(10);
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
        HrLinkedPointer<SimpleData> *ptr = list->m_poolHead;
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

    void TestHrDispose() {
        HrPointerList<SimpleData> *list = new HrPointerList<SimpleData>(10);
        delete list;

        list = new HrPointerList<SimpleData>(10);
        for(int i = 0; i < 5; i++)
            list->Add(new SimpleData());
        delete list;

        list = new HrPointerList<SimpleData>(10);
        list->Append(10);
        HrLinkedPointer<SimpleData> *ptr = list->m_poolHead;
        int index = 0;
        while(ptr != list->m_poolTail) {
            ptr->Released(false);
            ptr = ptr->Next();
            index++;
        }
        delete list;
    }

    void TestHrDefault() {
        HrPointerList<SimpleData> *list = new HrPointerList<SimpleData>(10);
        if(list->Capacity() != 10)
            throw;
        if(list->CalcPoolCount() != 10)
            throw;
        if(list->Count() != 0)
            throw;
        HrLinkedPointer<SimpleData> *ptr = list->PoolStart();
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

    void TestHrClear() {
        HrPointerList<SimpleData> *list = new HrPointerList<SimpleData>(10);
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

    void TestHrPointerListLiteAddRemove() {
        HrPointerList<SimpleData> *pool = new HrPointerList<SimpleData>(100, true);
        HrPointerListLite<SimpleData> *list = new HrPointerListLite<SimpleData>(pool);

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

        HrLinkedPointer<SimpleData> *i0 = list->Start();
        HrLinkedPointer<SimpleData> *i1 = list->Start()->Next();
        HrLinkedPointer<SimpleData> *i2 = list->Start()->Next()->Next();

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

    void TestHrPointerListLiteInsert() {
        HrPointerList<SimpleData> *pool = new HrPointerList<SimpleData>(100, false);
        HrPointerListLite<SimpleData> *list = new HrPointerListLite<SimpleData>(pool);

        list->Add();
        HrLinkedPointer<SimpleData> *i0 = list->Start();
        HrLinkedPointer<SimpleData> *newi0 = list->Insert(list->Start());

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

        HrLinkedPointer<SimpleData> *i1 = list->Insert(i0);
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

    void TestHrPointerListLiteClear() {
        HrPointerList<SimpleData> *pool = new HrPointerList<SimpleData>(100, false);
        HrPointerListLite<SimpleData> *list = new HrPointerListLite<SimpleData>(pool);

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

    void TestHrPointerListLiteAppend() {
        HrPointerList<SimpleData> *pool = new HrPointerList<SimpleData>(10000, true);
        HrPointerListLite<SimpleData> *list = new HrPointerListLite<SimpleData>(pool);

        HrLinkedPointer<SimpleData> *ptr = pool->m_poolHead;
        while(ptr != 0) {
            if(ptr->Data() == 0)
                throw;
            ptr = ptr->Next();
        }
        while(pool->m_poolHead != pool->m_poolTail) {
            list->Add();
        }
        HrLinkedPointer<SimpleData> *ptr2 = list->Add();
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

    void TestHrPointerListLiteAppend2() {
        HrPointerList<SimpleData> *pool = new HrPointerList<SimpleData>(10000, true);
        HrPointerListLite<SimpleData> *list = new HrPointerListLite<SimpleData>(pool);

        for(int i = 0; i < 30000; i++) {
            HrLinkedPointer<SimpleData> *ptr = list->Add();
            if(ptr->Data() == 0)
                throw;
        }
        delete list;
        delete pool;
    }

    void TestHrPointerListLite() {
        TestHrPointerListLiteAddRemove();
        TestHrPointerListLiteInsert();
        TestHrPointerListLiteClear();
        TestHrPointerListLiteAppend();
        TestHrPointerListLiteAppend2();
    }

    void TestHrPointerList() {
        TestHrDefault();
        TestHrDispose();
        TestHrAdditionalAllocate();
        TestHrClear();
    }

    void TestHrDefaultAutoAllocate() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        if(list->Count() != 0)
            throw;
        if(list->Capacity() != 10)
            throw;
        if(list->End()->Next() != 0)
            throw;
        if(list->CalcFreeItemsCount() != 10)
            throw;
        if(list->CalcUsedItemsCount() != 0)
            throw;
    }

    void TestHrNewItem() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        SimpleData *data = list->NewItem();
        if(data->Allocator != list)
            throw;
        if(data->Pointer == 0)
            throw;
        if(data->Pointer->Released())
            throw;
        if(list->Count() != 1)
            throw;
        if(list->CalcFreeItemsCount() != 9)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        for(int i = 0; i < 8; i++) {
            SimpleData *d = list->NewItem();
            if(list->Count() != 2 + i)
                throw;
            if(list->CalcFreeItemsCount() != 10 - list->Count())
                throw;
            if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
                throw;
        }
        list->NewItem();
        if(list->Count() != 10)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcFreeItemsCount() != 2)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
    }

    void TestHrAutoAllocate() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        for(int i = 0; i < 10; i++)
            list->NewItem();
        if(list->Count() != 10)
            throw;
        if(list->CalcFreeItemsCount() != 2)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->NewItem();
        if(list->Count() != 11)
            throw;
        if(list->CalcFreeItemsCount() != 1)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->NewItem();
        if(list->Count() != 12)
            throw;
        if(list->CalcFreeItemsCount() != 2)
            throw;
        if(list->Capacity() != 14)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->NewItem();
        if(list->Count() != 13)
            throw;
        if(list->Capacity() != 14)
            throw;
        if(list->CalcFreeItemsCount() != 1)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
    }

    void TestHrFree() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        SimpleData *data[10];
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        list->FreeItem(data[0]);
        if(!data[0]->Pointer->Released())
            throw;
        if(list->Count() != 9)
            throw;
        if(list->CalcFreeItemsCount() != 3)
            throw;
        if(list->Capacity() != 12)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        list->FreeItem(data[0]);
        if(list->Count() != 9)
            throw;
        if(list->CalcFreeItemsCount() != 3)
            throw;
        if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
            throw;
        for(int i = 1; i < 10; i++) {
            list->FreeItem(data[i]);
            if(list->Capacity() != 12)
                throw;
            if(list->Count() != 9 - i)
                throw;
            if(list->CalcFreeItemsCount() != 12 - list->Count())
                throw;
            if(list->CalcUsedItemsCount() != list->Capacity() - list->CalcFreeItemsCount())
                throw;
        }
    }

    void TestHrFree2() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);
        SimpleData *data[10];

        int *index = new int[10] { 5, 3, 4, 9, 6, 2, 7, 1, 0, 8 };
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        for(int i = 0; i < 10; i++) {
            list->FreeItem(data[index[i]]);
            if (list->CalcUsedItemsCount() != 9 - i)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity() - list->CalcUsedItemsCount())
                throw;
        }

        index = new int[10] { 8, 0, 5, 6, 9, 1, 2, 4, 7, 3 };
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        for(int i = 0; i < 10; i++) {
            list->FreeItem(data[index[i]]);
            if (list->CalcUsedItemsCount() != 9 - i)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity() - list->CalcUsedItemsCount())
                throw;
        }

        index = new int[10] { 5, 1, 2, 8, 4, 9, 7, 6, 0, 3 };
        for(int i = 0; i < 10; i++)
            data[i] = list->NewItem();
        for(int i = 0; i < 10; i++) {
            list->FreeItem(data[index[i]]);
            if (list->CalcUsedItemsCount() != 9 - i)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity() - list->CalcUsedItemsCount())
                throw;
        }
    }

    void TestHrClearAutoAllocate() {
        AutoAllocatePointerList<SimpleData> *list = new AutoAllocatePointerList<SimpleData>(10, 2);

        for(int j = 1; j < 100; j++) {
            for (int i = 0; i < j; i++)
                list->NewItem();

            list->Clear();

            if (list->Count() != 0)
                throw;
            if (list->CalcFreeItemsCount() != list->Capacity())
                throw;
            if (list->CalcUsedItemsCount() != 0)
                throw;
        }
    }

    void TestHrAutoAllocatePointerList() {
        TestHrDefaultAutoAllocate();
        TestHrNewItem();
        TestHrFree();
        TestHrFree2();
        TestHrAutoAllocate();
        TestHrClearAutoAllocate();
    }
    */
#pragma endregion

    void TestCore() {
        TestPointerList();
        TestPointerListLite();
        TestAutoAllocatePointerList();
    }

    //void TestCoreHr() {
    //    TestHrPointerList();
    //    TestHrPointerListLite();
    //}

    void Test() {
        TestCore();
        //TestCoreHr();
    }
};

#endif //TEST
#endif //HFT_ROBOT_POINTERLISTTESTER_H
