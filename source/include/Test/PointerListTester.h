//
// Created by root on 12.01.17.
//

#ifndef HFT_ROBOT_POINTERLISTTESTER_H
#define HFT_ROBOT_POINTERLISTTESTER_H
#include "../Types.h"

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

    void TestPointerListLite() {
        TestPointerListLiteAddRemove();
        TestPointerListLiteInsert();
        TestPointerListLiteClear();
    }

    void Test() {
        TestDefault();
        TestAdditionalAllocate();
        TestClear();

        TestPointerListLite();
    }
};

#endif //TEST
#endif //HFT_ROBOT_POINTERLISTTESTER_H
