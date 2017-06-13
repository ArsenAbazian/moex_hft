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

class HashTableTesterItem {
public:
    int value;
};

class HashTableTester {
    HashTable<HashTableTesterItem> *m_table;
public:
    HashTableTester() {
        this->m_table = new HashTable<HashTableTesterItem>();
    }
    ~HashTableTester() {
        delete this->m_table;
    }

    void TestCalcHashString() {
        char buf[10];
        int *owner = new int;
        int *object = new int;
        for(int i = 0; i < 10000000; i++) {
            sprintf(buf, "%d", i);
            int length = strlen(buf);
            UINT64 hash = this->m_table->CalcHashNoConstrain(buf, length);
            this->m_table->Add(new HrLinkedPointer<HashTableTesterItem>(), owner, buf, length);
            HrLinkedPointer<HashTableTesterItem> *ptr = this->m_table->GetPointer(owner, buf, length);
            if(ptr->Id() != hash)
                throw;
        }
        this->m_table->Clear();
    }

    void TestAdd() {
        const char *id = "123456";
        int idLength = 6;
        int *owner = new int;
        int *object = new int;

        HrLinkedPointer<HashTableTesterItem> *ptr = new HrLinkedPointer<HashTableTesterItem>();
        this->m_table->Add(ptr, owner, id, idLength);
        if(ptr->Owner() != owner)
            throw;
        if(ptr->Id() != atoi(id))
            throw;
        if(ptr->NextHash() != 0)
            throw;

        if(this->m_table->m_bucket[123456] != ptr)
            throw;

        int *owner2 = new int;
        int *object2 = new int;


        HrLinkedPointer<HashTableTesterItem> *ptr2 = new HrLinkedPointer<HashTableTesterItem>();
        this->m_table->Add(ptr2, owner2, id, idLength);

        if(this->m_table->m_bucket[123456] != ptr2)
            throw;

        if(ptr2->NextHash() != ptr)
            throw;
        if(ptr->PrevHash() != ptr2)
            throw;
        if(ptr->NextHash() != 0)
            throw;

        if(ptr2->Owner() != owner2)
            throw;
        if(ptr2->Id() != atoi(id))
            throw;

        int *owner3 = new int;
        int *object3 = new int;

        HrLinkedPointer<HashTableTesterItem> *ptr3 = new HrLinkedPointer<HashTableTesterItem>();
        this->m_table->Add(ptr3, owner3, id, idLength);

        if(this->m_table->m_bucket[123456] != ptr3)
            throw;

        if(ptr3->NextHash() != ptr2)
            throw;
        if(ptr2->PrevHash() != ptr3)
            throw;
        if(ptr2->NextHash() != ptr)
            throw;
        if(ptr->PrevHash() != ptr2)
            throw;
        if(ptr->NextHash() != 0)
            throw;

        if(ptr3->Owner() != owner3)
            throw;
        if(ptr3->Id() != atoi(id))
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

        HrLinkedPointer<HashTableTesterItem> *ptr = new HrLinkedPointer<HashTableTesterItem>();

        this->m_table->Add(ptr, owner, id, idLength);
        this->m_table->Remove(owner, id, idLength);
        if(this->m_table->m_bucket[123456] != 0)
            throw;

        ptr = new HrLinkedPointer<HashTableTesterItem>();
        HrLinkedPointer<HashTableTesterItem> *ptr2 = new HrLinkedPointer<HashTableTesterItem>();
        HrLinkedPointer<HashTableTesterItem> *ptr3 = new HrLinkedPointer<HashTableTesterItem>();
        HrLinkedPointer<HashTableTesterItem> *ptr4 = new HrLinkedPointer<HashTableTesterItem>();
        HrLinkedPointer<HashTableTesterItem> *ptr5 = new HrLinkedPointer<HashTableTesterItem>();
        this->m_table->Add(ptr, owner, id, idLength);
        this->m_table->Add(ptr2, owner2, id, idLength);
        this->m_table->Add(ptr3, owner3, id, idLength);
        this->m_table->Add(ptr4, owner4, id, idLength);
        this->m_table->Add(ptr5, owner5, id, idLength);

        this->m_table->Remove(owner3, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr5)
            throw;
        if(ptr5->NextHash() != ptr4)
            throw;
        if(ptr4->PrevHash() != ptr5)
            throw;
        if(ptr4->NextHash() != ptr2)
            throw;
        if(ptr2->PrevHash() != ptr4)
            throw;
        if(ptr2->NextHash() != ptr)
            throw;
        if(ptr->PrevHash() != ptr2)
            throw;

        this->m_table->Remove(owner, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr5)
            throw;
        if(ptr5->NextHash() != ptr4)
            throw;
        if(ptr4->PrevHash() != ptr5)
            throw;
        if(ptr4->NextHash() != ptr2)
            throw;
        if(ptr2->PrevHash() != ptr4)
            throw;
        if(ptr2->NextHash() != 0)
            throw;

        this->m_table->Remove(owner5, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr4)
            throw;
        if(ptr4->NextHash() != ptr2)
            throw;
        if(ptr2->PrevHash() != ptr4)
            throw;
        if(ptr2->NextHash() != 0)
            throw;
        this->m_table->Remove(owner4, id, idLength);
        if(this->m_table->m_bucket[123456] != ptr2)
            throw;
        if(ptr2->NextHash() != 0)
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
