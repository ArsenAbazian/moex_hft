//
// Created by root on 07.10.16.
//

#ifndef HFT_ROBOT_HASHTABLETESTER_H
#define HFT_ROBOT_HASHTABLETESTER_H

#include <FastTypes.h>
#include "Lib/StringIdComparer.h"
#include "../FastTypes.h"
#include "../Lib/PointerList.h"
#include "../Lib/AutoAllocatePointerList.h"

class HashTableTester {

public:
    /*
    void TestDefaults() {
        HashTable<void> *table = new HashTable<void>();
        if(table->SymbolsCount() != 0)
            throw;
        if(table->TradingSessionsCount() != 0)
            throw;
        for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                HashTableItem<void> *item = table->Item(i, j);
                if(item->Items()->Count() != 0)
                    throw;
            }
        }
        if(table->UsedItemCount() != 0)
            throw;
    }

    void TestAddItem() {
        HashTable<FastOBSFONDItemInfo> *table = new HashTable<FastOBSFONDItemInfo>();
        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(10, 10);

        FastOBSFONDItemInfo *itemInfo = list->NewItem();
        if(itemInfo->Pointer == 0)
            throw;
        if(itemInfo->Pointer->Owner() != list->ListCore())
            throw;
        if(list->Count() != 1)
            throw;
        HashTableItem<FastOBSFONDItemInfo> *item = table->Add("SMB1", "TRADING001", itemInfo);
        if(table->UsedItemCount() != 1)
            throw;
        if(item->Items()->Count() != 1)
            throw;
        if(table->SymbolsCount() != 1)
            throw;
        if(table->TradingSessionsCount() != 1)
            throw;
        int index = table->GetSymbolIndex("SMB1");
        if(index != 0)
            throw;
        index = table->GetTradingSessionIdIndex("TRADING001");
        if(index != 0)
            throw;
        // add new symbol and trading session id
        index = table->GetSymbolIndex("SMB2");
        if(index != 1)
            throw;
        index = table->GetTradingSessionIdIndex("TRADING002");
        if(index != 1)
            throw;
        LinkedPointer<FastOBSFONDItemInfo> *ptr = item->Items()->Get(itemInfo);
        if(ptr == 0)
            throw;

        // add second item
        FastOBSFONDItemInfo *itemInfo2 = list->NewItem();
        if(itemInfo2->Pointer == 0)
            throw;
        if(itemInfo2->Pointer->Owner() != list->ListCore())
            throw;
        if(list->Count() != 2)
            throw;

        HashTableItem<FastOBSFONDItemInfo> *item2 = table->Add("SMB3", "TRADING003", itemInfo2);
        if(table->UsedItemCount() != 2)
            throw;
        if(item2->Items()->Count() != 1)
            throw;
        if(table->SymbolsCount() != 3)
            throw;
        if(table->TradingSessionsCount() != 3)
            throw;

        LinkedPointer<FastOBSFONDItemInfo> *ptr2 = item2->Items()->Get(itemInfo2);
        if(ptr2 == 0)
            throw;

        // add new item to existing list
        FastOBSFONDItemInfo *itemInfo3 = list->NewItem();

        HashTableItem<FastOBSFONDItemInfo> *item3 = table->Add("SMB1", "TRADING001", itemInfo3);
        if(item3 != item)
            throw;
        if(table->UsedItemCount() != 2)
            throw;
        if(item3->Items()->Count() != 2)
            throw;
        if(item3->Items()->Get(itemInfo) == 0)
            throw;
        if(item3->Items()->Get(itemInfo3) == 0)
            throw;
    }

    void TestAddArrayOfItems() {
        HashTable<FastOBSFONDItemInfo> *table = new HashTable<FastOBSFONDItemInfo>();
        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(10, 10);

        FastOBSFONDItemInfo* itemInfoArray[3];
        itemInfoArray[0] = list->NewItem();
        itemInfoArray[1] = list->NewItem();
        itemInfoArray[2] = list->NewItem();


        HashTableItem<FastOBSFONDItemInfo> *item = table->Add("SMB1", "TRADING001", (FastOBSFONDItemInfo**)itemInfoArray, 3);
        if(table->UsedItemCount() != 1)
            throw;
        if(item->Items()->Count() != 3)
            throw;
        if(table->SymbolsCount() != 1)
            throw;
        if(table->TradingSessionsCount() != 1)
            throw;
        if(item->Items()->Get(itemInfoArray[0]) == 0)
            throw;
        if(item->Items()->Get(itemInfoArray[1]) == 0)
            throw;
        if(item->Items()->Get(itemInfoArray[2]) == 0)
            throw;
    }

    void TestClear() {
        HashTable<FastOBSFONDItemInfo> *table = new HashTable<FastOBSFONDItemInfo>();
        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(10, 10);

        FastOBSFONDItemInfo* itemInfoArray[3];
        itemInfoArray[0] = list->NewItem();
        itemInfoArray[1] = list->NewItem();
        itemInfoArray[2] = list->NewItem();

        table->Add("SMB1", "TRADING001", (FastOBSFONDItemInfo**)itemInfoArray, 3);
        table->Add("SMB2", "TRADING001", list->NewItem());
        table->Add("SMB3", "TRADING001", list->NewItem());
        table->Add("SMB1", "TRADING002", list->NewItem());

        if(table->UsedItemCount() != 4)
            throw;
        table->Clear();
        if(table->UsedItemCount() != 0)
            throw;
        if(list->Count() != 0)
            throw;
    }

    void TestClearItem() {
        HashTable<FastOBSFONDItemInfo> *table = new HashTable<FastOBSFONDItemInfo>();
        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(10, 10);

        FastOBSFONDItemInfo* itemInfoArray[3];
        itemInfoArray[0] = list->NewItem();
        itemInfoArray[1] = list->NewItem();
        itemInfoArray[2] = list->NewItem();

        table->Add("SMB1", "TRADING001", (FastOBSFONDItemInfo**)itemInfoArray, 3);
        table->Add("SMB2", "TRADING001", list->NewItem());
        table->Add("SMB3", "TRADING001", list->NewItem());
        table->Add("SMB1", "TRADING002", list->NewItem());

        int count = list->Count();
        int usedCount = table->UsedItemCount();
        HashTableItem<FastOBSFONDItemInfo> *item = table->GetSession("SMB1", "TRADING001");
        item->Clear();
        if(list->Count() != count - 3)
            throw;
        if(table->UsedItemCount() != usedCount - 1)
            throw;
    }

    void TestRemoveItem() {
        HashTable<FastOBSFONDItemInfo> *table = new HashTable<FastOBSFONDItemInfo>();
        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(10, 10);

        FastOBSFONDItemInfo* itemInfoArray[3];
        itemInfoArray[0] = list->NewItem();
        itemInfoArray[1] = list->NewItem();
        itemInfoArray[2] = list->NewItem();

        table->Add("SMB1", "TRADING001", (FastOBSFONDItemInfo**)itemInfoArray, 3);
        table->Add("SMB2", "TRADING001", list->NewItem());
        table->Add("SMB3", "TRADING001", list->NewItem());
        table->Add("SMB1", "TRADING002", list->NewItem());

        int usedCount = table->UsedItemCount();
        HashTableItem<FastOBSFONDItemInfo> *item = table->Session("SMB1", "TRADING001");

        int count = list->Count();
        int itemCount = item->Count();
        item->Remove(item->Start());
        if(item->Count() != itemCount - 1)
            throw;
        if(table->UsedItemCount() != usedCount)
            throw;
        if(list->Count() != count - 1)
            throw;
        item->Remove(item->Start());
        if(item->Count() != itemCount - 2)
            throw;
        if(table->UsedItemCount() != usedCount)
            throw;
        if(list->Count() != count - 2)
            throw;
        item->Remove(item->Start());
        if(item->Count() != 0)
            throw;
        if(table->UsedItemCount() != usedCount - 1)
            throw;
        if(list->Count() != count - 3)
            throw;
    }
    */
    void Test() {
        //this->TestDefaults();
        //this->TestAddItem();
        //this->TestAddArrayOfItems();
        //this->TestClear();
        //this->TestClearItem();
        //this->TestRemoveItem();
    }

};


#endif //HFT_ROBOT_HASHTABLETESTER_H
