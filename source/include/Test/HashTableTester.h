//
// Created by root on 22.04.17.
//

#ifndef HFT_ROBOT_HASHTABLETESTER_H
#define HFT_ROBOT_HASHTABLETESTER_H

#include "../Settings.h"
#ifdef TEST
#include "../Lib/HashTable.h"
#include <string.h>
#include <stdio.h>

class HashTableTester {
    HashTable *m_table;
public:
    HashTableTester() {
        this->m_table = new HashTable();
    }
    ~HashTableTester() {
        delete this->m_table;
    }

    void TestCalcHashString() {
        char buf[10];
        for(int i = 0; i < 10000000; i++) {
            sprintf(buf, "%d", i);
            UINT64 hash = this->m_table->CalcHash(buf, strlen(buf));
            if(hash != (i % 1000000))
                throw;
        }
    }

    void TestAdd() {
        const char *id = "123456";
        int idLength = 6;
        int *owner = new int;
        int *object = new int;

        LinkedPointer<HashTableItemInfo> *ptr = this->m_table->Add(owner, object, id, idLength);
        if(ptr->Data()->m_owner != owner)
            throw;
        if(ptr->Data()->m_length != idLength)
            throw;
        if(ptr->Data()->m_stringId != id)
            throw;
        if(ptr->Data()->m_object != object)
            throw;
        if(ptr->Next() != 0)
            throw;

        if(this->m_table->m_bucket[123456] != ptr)
            throw;

        int *owner2 = new int;
        int *object2 = new int;


        LinkedPointer<HashTableItemInfo> *ptr2 = this->m_table->Add(owner2, object2, id, idLength);

        if(this->m_table->m_bucket[123456] != ptr2)
            throw;

        if(ptr2->Next() != ptr)
            throw;
        if(ptr->Prev() != ptr2)
            throw;
        if(ptr->Next() != 0)
            throw;

        if(ptr2->Data()->m_owner != owner2)
            throw;
        if(ptr2->Data()->m_length != idLength)
            throw;
        if(ptr2->Data()->m_stringId != id)
            throw;
        if(ptr2->Data()->m_object != object2)
            throw;

        int *owner3 = new int;
        int *object3 = new int;
        LinkedPointer<HashTableItemInfo> *ptr3 = this->m_table->Add(owner3, object3, id, idLength);

        if(this->m_table->m_bucket[123456] != ptr3)
            throw;

        if(ptr3->Next() != ptr2)
            throw;
        if(ptr2->Prev() != ptr3)
            throw;
        if(ptr2->Next() != ptr)
            throw;
        if(ptr->Prev() != ptr2)
            throw;
        if(ptr->Next() != 0)
            throw;

        if(ptr3->Data()->m_owner != owner3)
            throw;
        if(ptr3->Data()->m_length != idLength)
            throw;
        if(ptr3->Data()->m_stringId != id)
            throw;
        if(ptr3->Data()->m_object != object3)
            throw;

        this->m_table->Clear();
    }

    void TestRemove() {
        const char *id = "123456";
        int idLength = 6;

        int *owner = new int;
        int *object = new int;

        int *owner2 = new int;
        int *object2 = new int;

        int *owner3 = new int;
        int *object3 = new int;

        int *owner4 = new int;
        int *object4 = new int;

        int *owner5 = new int;
        int *object5 = new int;

        LinkedPointer<HashTableItemInfo> *ptr = this->m_table->Add(owner, object, id, idLength);
        this->m_table->Remove(owner, id, idLength);
        if(this->m_table->m_bucket[123456] != 0)
            throw;

        ptr = this->m_table->Add(owner, object, id, idLength);
        LinkedPointer<HashTableItemInfo> *ptr2 = this->m_table->Add(owner2, object2, id, idLength);
        LinkedPointer<HashTableItemInfo> *ptr3 = this->m_table->Add(owner3, object3, id, idLength);
        LinkedPointer<HashTableItemInfo> *ptr4 = this->m_table->Add(owner4, object4, id, idLength);
        LinkedPointer<HashTableItemInfo> *ptr5 = this->m_table->Add(owner5, object5, id, idLength);

        this->m_table->Remove(owner3, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr5)
            throw;
        if(ptr5->Prev() != 0)
            throw;
        if(ptr5->Next() != ptr4)
            throw;
        if(ptr4->Prev() != ptr5)
            throw;
        if(ptr4->Next() != ptr2)
            throw;
        if(ptr2->Prev() != ptr4)
            throw;
        if(ptr2->Next() != ptr)
            throw;
        if(ptr->Prev() != ptr2)
            throw;

        this->m_table->Remove(owner, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr5)
            throw;
        if(ptr5->Prev() != 0)
            throw;
        if(ptr5->Next() != ptr4)
            throw;
        if(ptr4->Prev() != ptr5)
            throw;
        if(ptr4->Next() != ptr2)
            throw;
        if(ptr2->Prev() != ptr4)
            throw;
        if(ptr2->Next() != 0)
            throw;

        this->m_table->Remove(owner5, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr4)
            throw;
        if(ptr4->Prev() != 0)
            throw;
        if(ptr4->Next() != ptr2)
            throw;
        if(ptr2->Prev() != ptr4)
            throw;
        if(ptr2->Next() != 0)
            throw;
        this->m_table->Remove(owner4, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr2)
            throw;
        if(ptr2->Prev() != 0)
            throw;
        if(ptr2->Next() != 0)
            throw;
        this->m_table->Remove(owner2, id, idLength);
        if(this->m_table->m_bucket[123456] != 0)
            throw;
    }

    void Test() {
        TestCalcHashString();
        TestAdd();
        TestRemove();
    }
};

#endif

#endif //HFT_ROBOT_HASHTABLETESTER_H
