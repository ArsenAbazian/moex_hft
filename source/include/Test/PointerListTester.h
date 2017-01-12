//
// Created by root on 12.01.17.
//

#ifndef HFT_ROBOT_POINTERLISTTESTER_H
#define HFT_ROBOT_POINTERLISTTESTER_H

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

    void Test() {
        TestDefault();
        TestAdditionalAllocate();
        TestClear();
    }
};

#endif //HFT_ROBOT_POINTERLISTTESTER_H
