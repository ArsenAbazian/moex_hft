//
// Created by root on 19.12.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTESTERCURR_H
#define HFT_ROBOT_ORDERBOOKTESTERCURR_H

#include "../FeedConnection.h"
#include "TestTemplateInfo.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class OrderBookTesterCurr {
    FeedConnection_CURR_OBR *incCurr;
    FeedConnection_CURR_OBS *snapCurr;
    TestMessagesHelper      *m_helper;
    MarketDataTable<OrderBookInfo, FastOBSCURRInfo, FastOBSCURRItemInfo> *m_table;

public:
    OrderBookTesterCurr() {
        this->m_helper = new TestMessagesHelper();
        this->m_helper->SetCurrMode();
        this->m_table = new MarketDataTable<OrderBookInfo, FastOBSCURRInfo, FastOBSCURRItemInfo>();
        this->incCurr = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snapCurr = new FeedConnection_CURR_OBS("OBS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);

        this->incCurr->m_fakeConnect = true;
        this->snapCurr->m_fakeConnect = true;

    }
    ~OrderBookTesterCurr() {
        delete this->incCurr;
        delete this->snapCurr;
        delete this->m_helper;
        delete this->m_table;
    }

    void TestItem(OrderBookInfo<FastOBSFONDItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestItem(OrderBookInfo<FastOBSCURRItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table) {
        for(int i = 0; i < table->SymbolsCount(); i++) {
            for(int j = 0; j < table->Symbol(i)->Count(); j++) {
                OrderBookInfo<FastOBSFONDItemInfo> *item = table->Item(i, j);
                TestItem(item);
            }
        }
    }

    void TestTableItemsAllocator(MarketDataTable<OrderBookInfo, FastOBSCURRInfo, FastOBSCURRItemInfo> *table) {
        for(int i = 0; i < table->SymbolsCount(); i++) {
            for(int j = 0; j < table->Symbol(i)->Count(); j++) {
                OrderBookInfo<FastOBSCURRItemInfo> *item = table->Item(i, j);
                TestItem(item);
            }
        }
    }

    void Clear() {
        incFond->SetSnapshot(this->snapFond);
        incCurr->SetSnapshot(this->snapCurr);
        incFond->OrderBookFond()->Clear();
        incCurr->OrderBookCurr()->Clear();
        incFond->ClearMessages();
        incCurr->ClearMessages();
        incFond->WaitIncrementalMaxTimeMs(50);
        incCurr->WaitIncrementalMaxTimeMs(50);
        incFond->m_waitTimer->Stop();
        incCurr->m_waitTimer->Stop();
        incFond->m_waitTimer->Stop(1);
        incCurr->m_waitTimer->Stop(1);
        snapFond->ClearMessages();
        snapCurr->ClearMessages();
        snapFond->WaitSnapshotMaxTimeMs(50);
        snapCurr->WaitSnapshotMaxTimeMs(50);
        incFond->StartListenSnapshot();
        incCurr->StartListenSnapshot();
        snapFond->m_waitTimer->Stop();
        snapCurr->m_waitTimer->Stop();
        snapFond->Stop();
        snapCurr->Stop();
        incFond->Stop();
        incCurr->Stop();

        this->m_helper->Clear();
        incFond->Start();
        incCurr->Start();
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(!item1->Used)
            throw;
        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOBSFONDItemInfo *quote = obi->BuyQuotes()->Item(0);
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e4", 2))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e3", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(item1->Allocator->Count() != 1)
            throw;
        if(item2->Allocator->Count() != 1)
            throw;
        if(item3->Allocator->Count() != 1)
            throw;
        if(item4->Allocator->Count() != 1)
            throw;

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi2 = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 2, "e3", 2))
            throw;

        FastOBSFONDItemInfo *item5 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");

        FastOBSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOBSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOBSFONDItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOBSFONDItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e3", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        this->incFond->OrderBookFond()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incFond->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_FOND() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi2 = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        FastOBSFONDInfo *info2 = this->m_helper->CreateOBSFondInfo("t1s2", "t1");
        FastOBSFONDItemInfo *newItem1 = this->m_helper->CreateOBSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "e7");
        FastOBSFONDItemInfo *newItem2 = this->m_helper->CreateOBSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "e8");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->OrderBookFond()->ObtainSnapshotItem(info2);
        this->incFond->OrderBookFond()->ProcessSnapshot(info2);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi3 = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("t1s2", 4, "t1", 2);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOBSFONDItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOBSFONDItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e8", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e7", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOBSFONDItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e4", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2,"e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 2,"e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2,"e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi2 = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 2, "e2", 2))
            throw;

        FastOBSFONDItemInfo *item5 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetSellQuote, "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");

        FastOBSFONDItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSFONDItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOBSFONDItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOBSFONDItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e1", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item3->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item3->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        this->incFond->OrderBookFond()->Clear();
        if(this->incFond->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_FOND_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OBR_FOND(info);

        FastOBSFONDInfo *info2 = this->m_helper->CreateOBSFondInfo("t1s2", "t1");
        FastOBSFONDItemInfo *newItem1 = this->m_helper->CreateOBSFondItemInfo(7,-2, 1, 2, mdetSellQuote, "e7");
        FastOBSFONDItemInfo *newItem2 = this->m_helper->CreateOBSFondItemInfo(8,-2, 1, 2, mdetSellQuote, "e8");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->OrderBookFond()->ObtainSnapshotItem(info2);
        this->incFond->OrderBookFond()->ProcessSnapshot(info2);

        if(this->incFond->OrderBookFond()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi3 = this->incFond->OrderBookFond()->GetItem("s1", "t1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->incFond->OrderBookFond()->GetItem("t1s2", 4, "t1", 2);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOBSFONDItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        FastOBSFONDItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e7", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e8", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e4", 4);

        item1->RptSeq = 1;
        item2->RptSeq = 2;
        item3->RptSeq = 3;
        item4->RptSeq = 4;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOBSCURRItemInfo *quote = obi->BuyQuotes()->Start()->Data();
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e4", 2))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi2 = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 2, "e3", 2))
            throw;

        FastOBSCURRItemInfo *item5 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetBuyQuote,
                                                                           "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");

        FastOBSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOBSCURRItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOBSCURRItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e3", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        this->incCurr->OrderBookCurr()->Clear();
        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = this->m_helper->CreateOBSCurrInfo("t1s2", "t1");
        FastOBSCURRItemInfo *newItem1 = this->m_helper->CreateOBSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "e7");
        FastOBSCURRItemInfo *newItem2 = this->m_helper->CreateOBSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "e8");

        info2->RptSeq = 5;
        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderBookCurr()->ObtainSnapshotItem(info2);
        this->incCurr->OrderBookCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi3 = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("t1s2", 4, "t1", 2);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOBSCURRItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOBSCURRItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e8", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e7", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOBSCURRItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e4", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi2 = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 2, "e2", 2))
            throw;

        FastOBSCURRItemInfo *item5 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange,
                                                                           mdetSellQuote, "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");

        FastOBSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOBSCURRItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOBSCURRItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e4", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e1", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item3->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item3->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        this->incCurr->OrderBookCurr()->Clear();
        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e1", 1);
        FastOBSCURRItemInfo *item2 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e2", 2);
        FastOBSCURRItemInfo *item3 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e3", 3);
        FastOBSCURRItemInfo *item4 = this->m_helper->CreateOBRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = this->m_helper->CreateOBSCurrInfo("t1s2", "t1");
        FastOBSCURRItemInfo *newItem1 = this->m_helper->CreateOBSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "e7");
        FastOBSCURRItemInfo *newItem2 = this->m_helper->CreateOBSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "e8");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderBookCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi3 = this->incCurr->OrderBookCurr()->GetItem("s1", "t1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->incCurr->OrderBookCurr()->GetItem("t1s2", 4, "t1", 2);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOBSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e7", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e8", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND() {
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_Add\n");
        Test_OnIncrementalRefresh_OBR_FOND_Add();
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_Remove\n");
        Test_OnIncrementalRefresh_OBR_FOND_Remove();
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_Change\n");
        Test_OnIncrementalRefresh_OBR_FOND_Change();
        printf("OBR Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OBR_FOND_SellQuotes() {
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes();
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes();
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes();
        printf("OBR Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OnIncrementalRefresh_OBR_CURR() {
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_Add\n");
        Test_OnIncrementalRefresh_OBR_CURR_Add();
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_Remove\n");
        Test_OnIncrementalRefresh_OBR_CURR_Remove();
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_Change\n");
        Test_OnIncrementalRefresh_OBR_CURR_Change();
        printf("OBR Test_Clear_Curr\n");
        Test_Clear_Curr();
    }

    void Test_OnIncrementalRefresh_OBR_CURR_SellQuotes() {
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes();
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes();
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes();
        printf("OBR Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OBR_CURR() {
        this->m_helper->SetCurrMode();
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR\n");
        Test_OnIncrementalRefresh_OBR_CURR();
        printf("OBR Test_OnFullRefresh_OBS_CURR\n");
        Test_OnFullRefresh_OBS_CURR();
        printf("OBR Test_OnIncrementalRefresh_OBR_CURR_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_SellQuotes();
        printf("OBR Test_OnFullRefresh_OBS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OBS_CURR_SellQuotes();
    }

    void Test_OBR_FOND() {
        this->m_helper->SetFondMode();
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND\n");
        Test_OnIncrementalRefresh_OBR_FOND();
        printf("OBR Test_OnFullRefresh_OBS_FOND\n");
        Test_OnFullRefresh_OBS_FOND();
        printf("OBR Test_OnIncrementalRefresh_OBR_FOND_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_SellQuotes();
        printf("OBR Test_OnFullRefresh_OBS_FOND_SellQuotes\n");
        Test_OnFullRefresh_OBS_FOND_SellQuotes();
    }

    void TestDefaults() {
        if(this->incFond->OrderBookFond()->SymbolsCount() != 0)
            throw;
        if(this->incCurr->OrderBookCurr()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incFond->OrderBookFond());
        this->TestTableItemsAllocator(incCurr->OrderBookCurr());
    }

    void TestTableItem_CorrectBegin() {
        OrderBookInfo<FastOBSFONDItemInfo> *tb = new OrderBookInfo<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e1");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        if(!tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTableItem_IncorrectBegin() {
        OrderBookInfo<FastOBSFONDItemInfo> *tb = new OrderBookInfo<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e1");
        item1->RptSeq = 2;
        item1->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(tb->EntriesQueue()->StartRptSeq() != 1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 1)
            throw;
        if(tb->RptSeq() != 0)
            throw;

        delete tb;
    }

    void TestTableItem_SkipMessage() {
        OrderBookInfo<FastOBSFONDItemInfo> *tb = new OrderBookInfo<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e1");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e2");
        item2->RptSeq = 3;
        item2->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item2))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 2)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e3");
        item3->RptSeq = 4;
        item3->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item3))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 2)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTable_Default() {

        this->m_table->Clear();

        TestTableItemsAllocator(this->m_table);


    }

    void TestTable_AfterClear() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item = this->m_helper->CreateOBRFondItemInfo("s1", "session1", "e1");
        item->RptSeq = 1;

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "session1", "e1");
        item2->RptSeq = 2;

        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "session1", "e1");
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item);
        this->m_table->ProcessIncremental(item2);
        this->m_table->ProcessIncremental(item3);

        if(this->m_table->UsedItemCount() != 1)
            throw;
        OrderBookInfo<FastOBSFONDItemInfo> *tableItem = this->m_table->GetItem("s1", "session1");
        if(tableItem->EntriesQueue()->MaxIndex() != 1) // 3 is empty and 4 has value
            throw;
        this->m_table->Clear();
        if(this->m_table->UsedItemCount() != 0)
            throw;
        if(tableItem->RptSeq() != 0)
            throw;
        if(tableItem->BuyQuotes()->Count() != 0)
            throw;
        if(tableItem->EntriesQueue()->MaxIndex() != -1)
            throw;


    }

    void TestTable_CorrectBegin() {

        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1))
            throw;


    }

    void TestTable_IncorrectBegin() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 2;

        if(this->m_table->ProcessIncremental(item1))
            throw;


    }

    void TestTable_SkipMessages() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1))
            throw;

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2))
            throw;


    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1))
            throw;

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s2", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item2->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item2))
            throw;

        if(this->m_table->UsedItemCount() != 2)
            throw;


    }

    void TestTable_CorrectApplySnapshot() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e2", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e3", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e4", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e5", 3);
        item5->RptSeq = 3;

        FastOBSFONDInfo *info = this->m_helper->CreateOBSFondInfo("s1", "session");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookInfo<FastOBSFONDItemInfo> *tb = this->m_table->GetItem("s1", "session");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot(info);
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(!this->m_table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 3)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
    }

    void TestTable_CorrectApplySnapshot_2() {

        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e3", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e4", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        FastOBSFONDInfo *info1 = this->m_helper->CreateOBSFondInfo("s1", "session");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e2");

        FastOBSFONDInfo *info2 = this->m_helper->CreateOBSFondInfo("s1", "session");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = this->m_helper->CreateOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e2");

        OrderBookInfo<FastOBSFONDItemInfo> *tb = this->m_table->GetItem("s1", "session");

        this->m_table->ObtainSnapshotItem(info1);
        this->m_table->StartProcessSnapshot(info1);
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info1);
        this->m_table->ProcessSnapshot(info2);
        if(!this->m_table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 4)
            throw;
    }

    void TestTable_IncorrectApplySnapshot() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e2", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item3 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e3", 5);
        item3->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e4", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e5", 2);
        item5->RptSeq = 2;

        FastOBSFONDInfo *info = this->m_helper->CreateOBSFondInfo("s1", "session");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookInfo<FastOBSFONDItemInfo> *tb = this->m_table->GetItem("s1", "session");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot(info);
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 2);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 2)
            throw;
        if(this->m_table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 2)
            throw;
    }

    void TestTable_IncorrectApplySnapshot_WhenMessageSkipped() {
        this->m_table->Clear();

        FastOBSFONDItemInfo *item1 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e2", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item4 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e4", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = this->m_helper->CreateOBRFondItemInfo("s1", "session", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "e5", 3);
        item5->RptSeq = 3;

        FastOBSFONDInfo *info = this->m_helper->CreateOBSFondInfo("s1", "session");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookInfo<FastOBSFONDItemInfo> *tb = this->m_table->GetItem("s1", "session");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot(info);
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(this->m_table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 4)
            throw;
        this->m_table->ObtainSnapshotItem(info);
        if(this->m_table->EndProcessSnapshot())
            throw;
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        this->m_helper->SendMessages(fci, fcs, inc, snap, delay);
        this->TestSnapshotPacketsCleared();
    }

    void SendMessages(FeedConnection *c, TestTemplateInfo **items, int count) {
        this->m_helper->SendMessages(c, items, count);
    }

    void TestConnectionFond_EmptyTest() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 3)}, 3);

    }

    void TestConnectionFond_TestCorrectIncMessages() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnectionFond_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = incFond->OrderBookFond()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 1) // cell for rptseq 3 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1]->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnectionFond_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = incFond->OrderBookFond()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = incFond->OrderBookFond()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(!incFond->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = incFond->OrderBookFond()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(!incFond->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnectionFond_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = incFond->OrderBookFond()->GetItem("s1", "session1");
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMilliseconds() < incFond->WaitIncrementalMaxTimeMs());
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;
        //entering snapshot mode
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        // timer should be stopped
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_startMsgSeqNum != -1)
            throw;
        if(snapFond->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnectionFond_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        incFond->StartListenSnapshot();
        if(!snapFond->m_waitTimer->Active()) // start wait timer immediately
            throw;

        //no messages
        while(snapFond->m_waitTimer->ElapsedMilliseconds() <= snapFond->WaitSnapshotMaxTimeMs()) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->Listen_Atom_Snapshot_Core())
                throw; // nothing should be happens
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }

        if(!snapFond->Listen_Atom_Snapshot_Core()) // reconnect
            throw;
        if(snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(snapFond->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;

        // now we should restart?
        if(!snapFond->Reconnect_Atom())
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_startMsgSeqNum != -1)
            throw;
        if(snapFond->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnectionFond_OneMessageReceived() {
        this->Clear();
        incFond->StartListenSnapshot();

        //no messages first half time
        while(snapFond->m_waitTimer->ElapsedMilliseconds() < snapFond->WaitSnapshotMaxTimeMs() / 2) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->Listen_Atom_Snapshot_Core())
                throw; // nothing should be happens
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(snapFond->m_waitTimer->ElapsedMilliseconds() >= snapFond->WaitSnapshotMaxTimeMs() / 2)
            throw;

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw; // nothing should be happens
    }

    void TestConnectionFond_RouteFirstReceived_Empty() {

        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;

        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;

        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
    }

    void TestConnectionFond_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 1)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 4, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 2);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 5)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 5, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 6, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 2);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 7)
            throw;
        if(snapFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_snapshotRouteFirst != 6)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;

        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 7)
            throw;
        if(snapFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_snapshotRouteFirst != 6)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
    }

    void TestConnectionFond_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 1)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
    }

    void TestConnectionFond_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapFond->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapFond->Listen_Atom_Snapshot_Core();

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        snapFond->m_waitTimer->Stop(); // reset timer 0 to avoid simulate situation when no packet received
        // now wait some time and after that we have to skip lost message to get other snapshot
        while(!snapFond->m_waitTimer->IsElapsedMilliseconds(1, snapFond->WaitSnapshotMaxTimeMs())) {
            snapFond->Listen_Atom_Snapshot_Core();
            if(!snapFond->m_waitTimer->Active(1))
                break;
        }

        snapFond->Listen_Atom_Snapshot_Core();
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }

    void TestConnectionFond_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapFond->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        // wait some time and then receive lost packet
        while(!snapFond->m_waitTimer->IsElapsedMilliseconds(1, snapFond->WaitSnapshotMaxTimeMs() / 2)) {
            snapFond->m_waitTimer->Start(); // reset timer 0 to avoid simulate situation when no packet received
            if(!snapFond->Listen_Atom_Snapshot_Core())
                throw;
        }

        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;
    }

    void TestConnectionFond_StopTimersAfterReconnect() {
        this->Clear();
        incFond->StartListenSnapshot();

        // manually activate timer 1
        snapFond->m_waitTimer->Activate(1);
        snapFond->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
        snapFond->DoWorkAtom();

        if(!snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }

    void TestConnectionFond_TestSnapshotCollect() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;

        snapFond->Listen_Atom_Snapshot_Core();
        //snapshot received and should be applied
        OrderBookInfo<FastOBSFONDItemInfo> *tableItem = incFond->OrderBookFond()->GetItem("s1", "session1");

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;

        if(tableItem->BuyQuotes()->Count() != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
    }

    void TestConnectionFond_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        snapFond->WaitSnapshotMaxTimeMs(100);
        incFond->StartListenSnapshot();

        if(!snapFond->m_waitTimer->Active())
            throw;

        snapFond->m_waitTimer->Stop();
        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 4, "s1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 6),
        }, 2);

        if(snapFond->m_packets[3]->m_item != 0)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        snapFond->m_waitTimer->Reset();
        snapFond->Listen_Atom_Snapshot_Core();

        if(!snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_snapshotRouteFirst != 2)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;

        snapFond->Listen_Atom_Snapshot_Core();
        if(!snapFond->m_waitTimer->Active(1))
            throw;
        snapFond->m_waitTimer->Stop(); //TODO check!!!!
        while(snapFond->m_waitTimer->ElapsedMilliseconds(1) <= snapFond->WaitSnapshotMaxTimeMs())
            snapFond->Listen_Atom_Snapshot_Core();

        snapFond->Listen_Atom_Snapshot_Core();
        // reset
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnectionFond_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 1),
                                             new TestTemplateItemInfo("s2", "e1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 4),
                                             new TestTemplateItemInfo("s2", "e1", 4),
                                     }, 2)
        }, 2);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        if(incFond->OrderBookFond()->UsedItemCount() != 2)
            throw;

        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMilliseconds() < incFond->WaitIncrementalMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e1"),
                                     }, 2, 4)
        }, 1);
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderBookInfo<FastOBSFONDItemInfo> *item1 = incFond->OrderBookFond()->GetItem("s1", "session1");
        OrderBookInfo<FastOBSFONDItemInfo> *item2 = incFond->OrderBookFond()->GetItem("s2", "session1");
        if(item1->EntriesQueue()->HasEntries())
            throw;
        if(!item2->EntriesQueue()->HasEntries())
            throw;

        for(int i = 0; i < item1->BuyQuotes()->Count(); i++)
            if(item1->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < item2->BuyQuotes()->Count(); i++)
            if(item2->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
    }



    void TestConnectionFond_SkipHearthBeatMessages_Incremental() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        this->incFond->StartListenSnapshot();
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incFond->m_packets[4]->m_item == 0 || incFond->m_packets[5]->m_item == 0 || incFond->m_packets[6]->m_item == 0)
            throw;
        if(!incFond->m_packets[4]->m_processed || !incFond->m_packets[5]->m_processed || !incFond->m_packets[6]->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapFond->m_packets[1]->m_item == 0 || snapFond->m_packets[2]->m_item == 0 || snapFond->m_packets[3]->m_item == 0)
        //    throw;
        //if(!snapFond->m_packets[1]->m_processed || !snapFond->m_packets[2]->m_processed || !snapFond->m_packets[3]->m_processed)
        //    throw;
    }

    void TestConnectionFond_AllSymbolsAreOk() {
        this->Clear();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, obr entry s2 e1, obr entry s2 e2",
                     "",
                     30);
        if(incFond->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_orderBookTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->m_orderBookTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnectionFond_NotAllSymbolsAreOk() {
        this->Clear();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, obr entry s1 e3, obr entry s2 e1, obr entry s2 e2",
                     "",
                     30);
        if(incFond->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(!incFond->m_orderBookTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->m_orderBookTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnectionFond_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e2, obr entry s1 e3, obr entry s2 e1, obr entry s2 e2",
                     "",
                     30);

        if(incFond->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_orderBookTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->m_orderBookTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
    }

    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1",
                     "",
                     30);
        if(incFond->HasPotentiallyLostPackets())
            throw;
        if(incFond->ShouldStartSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat",
                     "",
                     30);
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(!incFond->m_waitTimer->Active())
            throw;
        if(incFond->m_waitTimer->IsElapsedMilliseconds(incFond->m_waitIncrementalMaxTimeMs))
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat, hbeat",
                     "",
                     30);
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderBookFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderBookFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3_1() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsConnect)
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderBookFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }

    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap",
                     "",
                     30);
        if(incFond->m_waitTimer->Active())
            throw;
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,    hbeat,                              hbeat",
                     "                                                            obs symbol3 begin rpt 1, obs symbol3 rpt 1 entry symbol3 e1, obs symbol3 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->CanStopListeningSnapshot()) // because we did not receive all snapshots for all symbols
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderBookTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s2", "session1")->BuyQuotes()->Count() != 0)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 2)
            throw;
        if(incFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
    }
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "lost obr entry s1 e1, lost hbeat, wait_snap",
                     "obs s1 begin rpt 1, obs s1 rpt 1 entry s1 e1, obs s1 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 4)
            throw;
        if(incFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderBookFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                         hbeat,                                        hbeat",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, hbeat, obs s2 begin rpt 2 end entry s2 e1",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s2", "session1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderBookTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s2", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 7)
            throw;
        if(incFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_startMsgSeqNum != 5)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    // almost the same as TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderBookFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                         obr entry s2 e1,                         obr entry s2 e2",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, obs s2 begin rpt 2 end entry s2 e1 skip_if_suspend",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s2", "session1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderBookTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_orderBookTableFond->GetItem("s2", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_orderBookTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 7)
            throw;
        if(incFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
    }
    // we receive snapshot which rpt seq is less than incremental actual rpt seq
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");

        if(!incFond->m_waitTimer->Active())
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 3)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 3)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 1)
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(snapFond->m_startMsgSeqNum != 2) // detect that
            throw;
    }
    // we received snapshot for item but item has 2 gaps and snapshot is partially actual
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 4 entry s1 e4 end",
                     30);
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 5 entry s1 e5 end",
                     30);
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 6 entry s1 e6 end",
                     30);
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(!incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incFond->OrderBookFond()->GetItem("s2", "session1")->RptSeq() != 1)
            throw;
        if(incFond->OrderBookFond()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4, hbeat ",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat          , obs s1 begin rpt 3 entry s1 e3 end",
                     30);
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(incFond->OrderBookFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderBookFond()->QueueEntriesCount() != 0)
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, obr entry s2 e2, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderBookFond()->GetItem("s2", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // we have received twice the same snapshot (rpt seq num = the same value) which means that item did not receive incremental message so item state is actual
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_7() {
        // do nothing. lets consider that after receiving snapshot item will be in actual state if there is no queue entries
    }
    // we can receive null snapshot i.e. snapshot with LastMsgSeqNumProcessed = 0 RptSeq = 0
    // this means that item has NO DATA
    // so just clear queue entries and decrease session to recv snapshot value
    void TestConnectionFond_ResetEntriesQueueIfNullSnapshotIsReceived() {
        this->Clear();

        /*
        unsigned char *msg = new unsigned char[52] {
                0x65, 0x23, 0x00, 0x00, 0xe0, 0x12, 0xec, 0x46, 0xe5, 0x23,
                0x68, 0x08, 0x12, 0x7f, 0x4c, 0x74, 0xc0, 0x81, 0x80, 0x00,
                0xe5, 0x52, 0x50, 0x4d, 0xcf, 0x52, 0x55, 0x30, 0x30, 0x30,
                0x41, 0x30, 0x4a, 0x54, 0x5a, 0x46, 0xb1, 0x82, 0x82, 0x93,
                0x80, 0x81, 0xca, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                0x80, 0x80
        };
        incFond->m_fastProtocolManager->SetNewBuffer(msg, 52);
        incFond->m_fastProtocolManager->ReadMsgSeqNumber();
        incFond->m_fastProtocolManager->Decode();
        incFond->m_fastProtocolManager->Print();
        */


        if(incFond->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnectionFond_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnectionFond_EnterSnapshotMode() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->EnterSnapshotMode();
        if(!incFond->OrderBookFond()->GetItem("s1", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnectionFond_ClearSnapshotMessages_1() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapFond->m_packets[1]->m_item != 0)
            throw;
        if(snapFond->m_packets[1]->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnectionFond_ClearSnapshotMessages_2() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapFond->m_packets[1]->m_item != 0 ||
           snapFond->m_packets[2]->m_item != 0 ||
           snapFond->m_packets[3]->m_item != 0)
            throw;
        if(snapFond->m_packets[1]->m_processed != false ||
           snapFond->m_packets[2]->m_processed != false ||
           snapFond->m_packets[3]->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnectionFond_ClearSnapshotMessages_3() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        snapFond->WaitSnapshotMaxTimeMs(50);
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_item != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnectionFond_ClearSnapshotMessages_4() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        snapFond->WaitSnapshotMaxTimeMs(50);
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat, obs s1 rpt 2 entry s1 e2, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(incFond->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_item != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
        for(int i = 1; i < 100; i++) {
            if(snapCurr->m_packets[i]->m_item != 0 || snapCurr->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnectionFond_ClearSnapshotMessages() {
        printf("OBR TestConnectionFond_ClearSnapshotMessages_1\n");
        TestConnectionFond_ClearSnapshotMessages_1();
        printf("OBR TestConnectionFond_ClearSnapshotMessages_2\n");
        TestConnectionFond_ClearSnapshotMessages_2();
        printf("OBR TestConnectionFond_ClearSnapshotMessages_3\n");
        TestConnectionFond_ClearSnapshotMessages_3();
        printf("OBR TestConnectionFond_ClearSnapshotMessages_4\n");
        TestConnectionFond_ClearSnapshotMessages_4();
    }
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot() {
        printf("OBR TestConnectionFond_EnterSnapshotMode\n");
        TestConnectionFond_EnterSnapshotMode();
        printf("OBR TestConnectionFond_ClearSnapshotMessages\n");
        TestConnectionFond_ClearSnapshotMessages();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_1();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_4();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnectionFond_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incFond->OrderBookFond());
        this->Clear();
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 1),
                                             new TestTemplateItemInfo("s2", "e1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 4),
                                             new TestTemplateItemInfo("s2", "e1", 4),
                                     }, 2)
        }, 2);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderBookFond());

        incFond->OrderBookFond()->Clear();
    }

    void TestConnectionFond() {
        this->m_helper->SetFondMode();
        printf("OBR TestConnectionFond_AllSymbolsAreOk\n");
        TestConnectionFond_AllSymbolsAreOk();
        printf("OBR TestConnectionFond_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnectionFond_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("OBR TestConnectionFond_AllSymbolsAreOkButOneMessageLost\n");
        TestConnectionFond_AllSymbolsAreOkButOneMessageLost();
        printf("OBR TestConnectionFond_SkipHearthBeatMessages_Incremental\n");
        TestConnectionFond_SkipHearthBeatMessages_Incremental();
        printf("OBR TestConnectionFond_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot();
        printf("OBR TestConnectionFond_NotAllSymbolsAreOk\n");
        TestConnectionFond_NotAllSymbolsAreOk();
        printf("OBR TestConnectionFond_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnectionFond_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("OBR TestConnectionFond_StopTimersAfterReconnect\n");
        TestConnectionFond_StopTimersAfterReconnect();
        printf("OBR TestConnectionFond_SnapshotSomeMessagesReceivedLater\n");
        TestConnectionFond_SnapshotSomeMessagesReceivedLater();
        printf("OBR TestConnectionFond_SnapshotSomeMessagesNotReceived\n");
        TestConnectionFond_SnapshotSomeMessagesNotReceived();
        printf("OBR TestConnectionFond_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnectionFond_LastFragmentReceivedBeforeRouteFirst();
        printf("OBR TestConnectionFond_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnectionFond_RouteFirstReceived_AfterSomeDummyMessages();
        printf("OBR TestConnectionFond_RouteFirstReceived_Empty\n");
        TestConnectionFond_RouteFirstReceived_Empty();
        printf("OBR TestConnectionFond_TestSnapshotNoMessagesAtAll\n");
        TestConnectionFond_TestSnapshotNoMessagesAtAll();
        printf("OBR TestConnectionFond_OneMessageReceived\n");
        TestConnectionFond_OneMessageReceived();
        printf("OBR TestConnectionFond_Clear_AfterIncremental\n");
        TestConnectionFond_Clear_AfterIncremental();
        printf("OBR TestConnectionFond_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnectionFond_TestIncMessageLost_AndWaitTimerElapsed();
        printf("OBR TestConnectionFond_TestSnapshotCollect\n");
        TestConnectionFond_TestSnapshotCollect();
        printf("OBR TestConnectionFond_TestSnapshotNotCollect\n");
        TestConnectionFond_TestSnapshotMessageLostAndTimeExpired();
        printf("OBR TestConnectionFond_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnectionFond_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("OBR TestConnectionFond_EmptyTest\n");
        TestConnectionFond_EmptyTest();
        printf("OBR TestConnectionFond_TestCorrectIncMessages\n");
        TestConnectionFond_TestCorrectIncMessages();
        printf("OBR TestConnectionFond_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnectionFond_TestIncMessagesLost_AndWhenAppeared();
        printf("OBR TestConnectionFond_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnectionFond_TestInc2MessagesLost_AppearedThen2Messages();
        printf("OBR TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("OBR TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestConnectionCurr_EmptyTest() {
        this->Clear();

        SendMessages(incCurr, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 3)}, 3);

    }

    void TestConnectionCurr_TestCorrectIncMessages() {
        this->Clear();

        SendMessages(incCurr, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnectionCurr_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        OrderBookInfo<FastOBSCURRItemInfo> *item = incCurr->OrderBookCurr()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 1) // cell for rptseq 3 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1]->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnectionCurr_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        OrderBookInfo<FastOBSCURRItemInfo> *item = incCurr->OrderBookCurr()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnectionCurr_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        OrderBookInfo<FastOBSCURRItemInfo> *item = incCurr->OrderBookCurr()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(!incCurr->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnectionCurr_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        OrderBookInfo<FastOBSCURRItemInfo> *item = incCurr->OrderBookCurr()->GetItem("s1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(!incCurr->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnectionCurr_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        OrderBookInfo<FastOBSCURRItemInfo> *item = incCurr->OrderBookCurr()->GetItem("s1", "session1");
        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incCurr->m_waitTimer->ElapsedMilliseconds() < incCurr->WaitIncrementalMaxTimeMs());
        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;
        //entering snapshot mode
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
        // timer should be stopped
        if(incCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->m_startMsgSeqNum != -1)
            throw;
        if(snapCurr->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnectionCurr_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        incCurr->StartListenSnapshot();
        if(!snapCurr->m_waitTimer->Active()) // start wait timer immediately
            throw;

        //no messages
        while(snapCurr->m_waitTimer->ElapsedMilliseconds() <= snapCurr->WaitSnapshotMaxTimeMs()) {
            if(!snapCurr->m_waitTimer->Active())
                throw;
            if(!snapCurr->Listen_Atom_Snapshot_Core())
                throw; // nothing should be happens
            if(snapCurr->m_endMsgSeqNum != -1)
                throw;
            if(snapCurr->m_startMsgSeqNum != -1)
                throw;
        }

        if(!snapCurr->Listen_Atom_Snapshot_Core()) // reconnect
            throw;
        if(snapCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(snapCurr->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;

        // now we should restart?
        if(!snapCurr->Reconnect_Atom())
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->m_startMsgSeqNum != -1)
            throw;
        if(snapCurr->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnectionCurr_OneMessageReceived() {
        this->Clear();
        incCurr->StartListenSnapshot();

        //no messages first half time
        while(snapCurr->m_waitTimer->ElapsedMilliseconds() < snapCurr->WaitSnapshotMaxTimeMs() / 2) {
            if(!snapCurr->m_waitTimer->Active())
                throw;
            if(!snapCurr->Listen_Atom_Snapshot_Core())
                throw; // nothing should be happens
            if(snapCurr->m_endMsgSeqNum != -1)
                throw;
            if(snapCurr->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(snapCurr->m_waitTimer->ElapsedMilliseconds() >= snapCurr->WaitSnapshotMaxTimeMs() / 2)
            throw;

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw; // nothing should be happens
    }

    void TestConnectionCurr_RouteFirstReceived_Empty() {

        this->Clear();
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
        if(snapCurr->m_snapshotRouteFirst != 2)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;

        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;

        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
        if(snapCurr->m_snapshotRouteFirst != 2)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
    }

    void TestConnectionCurr_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 1)
            throw;
        if(snapCurr->m_snapshotRouteFirst != -1)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
        if(snapCurr->m_snapshotRouteFirst != -1)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;

        SendMessages(snapCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 4, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 2);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 5)
            throw;
        if(snapCurr->m_endMsgSeqNum != 4)
            throw;
        if(snapCurr->m_snapshotRouteFirst != -1)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;

        SendMessages(snapCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 5, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 6, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 2);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 7)
            throw;
        if(snapCurr->m_endMsgSeqNum != 6)
            throw;
        if(snapCurr->m_snapshotRouteFirst != 6)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;

        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 7)
            throw;
        if(snapCurr->m_endMsgSeqNum != 6)
            throw;
        if(snapCurr->m_snapshotRouteFirst != 6)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
    }

    void TestConnectionCurr_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 1)
            throw;
        if(snapCurr->m_snapshotRouteFirst != -1)
            throw;
        if(snapCurr->m_snapshotLastFragment != -1)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
    }

    void TestConnectionCurr_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapCurr->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapCurr->Listen_Atom_Snapshot_Core();

        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
        if(!snapCurr->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        snapCurr->m_waitTimer->Stop(); // reset timer 0 to avoid simulate situation when no packet received
        // now wait some time and after that we have to skip lost message to get other snapshot
        while(!snapCurr->m_waitTimer->IsElapsedMilliseconds(1, snapCurr->WaitSnapshotMaxTimeMs())) {
            snapCurr->Listen_Atom_Snapshot_Core();
            if(!snapCurr->m_waitTimer->Active(1))
                break;
        }

        snapCurr->Listen_Atom_Snapshot_Core();
        if(snapCurr->m_startMsgSeqNum != 4)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_waitTimer->Active(1))
            throw;
    }

    void TestConnectionCurr_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapCurr->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;

        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
        if(!snapCurr->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        // wait some time and then receive lost packet
        while(!snapCurr->m_waitTimer->IsElapsedMilliseconds(1, snapCurr->WaitSnapshotMaxTimeMs() / 2)) {
            snapCurr->m_waitTimer->Start(); // reset timer 0 to avoid simulate situation when no packet received
            if(!snapCurr->Listen_Atom_Snapshot_Core())
                throw;
        }

        if(!snapCurr->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;
        if(snapCurr->m_startMsgSeqNum != 4)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;
    }

    void TestConnectionCurr_StopTimersAfterReconnect() {
        this->Clear();
        incCurr->StartListenSnapshot();

        // manually activate timer 1
        snapCurr->m_waitTimer->Activate(1);
        snapCurr->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
        snapCurr->DoWorkAtom();

        if(!snapCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->m_waitTimer->Active(1))
            throw;
    }

    void TestConnectionCurr_TestSnapshotCollect() {
        this->Clear();
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;

        snapCurr->Listen_Atom_Snapshot_Core();
        //snapshot received and should be applied
        OrderBookInfo<FastOBSCURRItemInfo> *tableItem = incCurr->OrderBookCurr()->GetItem("s1", "session1");

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        if(tableItem->BuyQuotes()->Count() != 2)
            throw;
        if(snapCurr->m_snapshotRouteFirst != -1)
            throw;
        if(snapCurr->m_snapshotLastFragment != -1)
            throw;
        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
    }

    void TestConnectionCurr_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        snapCurr->WaitSnapshotMaxTimeMs(100);
        incCurr->StartListenSnapshot();

        if(!snapCurr->m_waitTimer->Active())
            throw;

        snapCurr->m_waitTimer->Stop();
        SendMessages(snapCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 4, "s1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 6),
        }, 2);

        if(snapCurr->m_packets[3]->m_item != 0)
            throw;
        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 4)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;

        snapCurr->m_waitTimer->Reset();
        snapCurr->Listen_Atom_Snapshot_Core();

        if(!snapCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->m_waitTimer->Active(1))
            throw;
        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_snapshotRouteFirst != 2)
            throw;
        if(snapCurr->m_snapshotLastFragment != -1)
            throw;

        snapCurr->Listen_Atom_Snapshot_Core();
        if(!snapCurr->m_waitTimer->Active(1))
            throw;
        snapCurr->m_waitTimer->Stop(); //TODO check!!!!
        while(snapCurr->m_waitTimer->ElapsedMilliseconds(1) <= snapCurr->WaitSnapshotMaxTimeMs())
            snapCurr->Listen_Atom_Snapshot_Core();

        snapCurr->Listen_Atom_Snapshot_Core();
        // reset
        if(snapCurr->m_snapshotRouteFirst != -1)
            throw;
        if(snapCurr->m_snapshotLastFragment != -1)
            throw;
        if(snapCurr->m_waitTimer->Active(1))
            throw;
    }
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnectionCurr_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        incCurr->StartListenSnapshot();

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        SendMessages(incCurr, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 1),
                                             new TestTemplateItemInfo("s2", "e1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 4),
                                             new TestTemplateItemInfo("s2", "e1", 4),
                                     }, 2)
        }, 2);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        if(incCurr->OrderBookCurr()->UsedItemCount() != 2)
            throw;

        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incCurr->m_waitTimer->ElapsedMilliseconds() < incCurr->WaitIncrementalMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapCurr, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "s1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e1"),
                                     }, 2, 4)
        }, 1);
        if(!snapCurr->Listen_Atom_Snapshot_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderBookInfo<FastOBSCURRItemInfo> *item1 = incCurr->OrderBookCurr()->GetItem("s1", "session1");
        OrderBookInfo<FastOBSCURRItemInfo> *item2 = incCurr->OrderBookCurr()->GetItem("s2", "session1");
        if(item1->EntriesQueue()->HasEntries())
            throw;
        if(!item2->EntriesQueue()->HasEntries())
            throw;

        for(int i = 0; i < item1->BuyQuotes()->Count(); i++)
            if(item1->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < item2->BuyQuotes()->Count(); i++)
            if(item2->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
    }



    void TestConnectionCurr_SkipHearthBeatMessages_Incremental() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        this->incCurr->StartListenSnapshot();
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incCurr->m_packets[4]->m_item == 0 || incCurr->m_packets[5]->m_item == 0 || incCurr->m_packets[6]->m_item == 0)
            throw;
        if(!incCurr->m_packets[4]->m_processed || !incCurr->m_packets[5]->m_processed || !incCurr->m_packets[6]->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapCurr->m_packets[1]->m_item == 0 || snapCurr->m_packets[2]->m_item == 0 || snapCurr->m_packets[3]->m_item == 0)
        //    throw;
        //if(!snapCurr->m_packets[1]->m_processed || !snapCurr->m_packets[2]->m_processed || !snapCurr->m_packets[3]->m_processed)
        //    throw;
    }

    void TestConnectionCurr_AllSymbolsAreOk() {
        this->Clear();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, obr entry s2 e1, obr entry s2 e2",
                     "",
                     30);
        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 2)
            throw;
        if(incCurr->m_orderBookTableCurr->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->m_orderBookTableCurr->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
    }

    void TestConnectionCurr_NotAllSymbolsAreOk() {
        this->Clear();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, obr entry s1 e3, obr entry s2 e1, obr entry s2 e2",
                     "",
                     30);
        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 2)
            throw;
        if(!incCurr->m_orderBookTableCurr->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->m_orderBookTableCurr->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
        if(incCurr->CanStopListeningSnapshot())
            throw;
    }

    void TestConnectionCurr_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e2, obr entry s1 e3, obr entry s2 e1, obr entry s2 e2",
                     "",
                     30);

        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 2)
            throw;
        if(incCurr->m_orderBookTableCurr->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->m_orderBookTableCurr->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
    }

    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1",
                     "",
                     30);
        if(incCurr->HasPotentiallyLostPackets())
            throw;
        if(incCurr->ShouldStartSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat",
                     "",
                     30);
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
        if(!incCurr->m_waitTimer->Active())
            throw;
        if(incCurr->m_waitTimer->IsElapsedMilliseconds(incCurr->m_waitIncrementalMaxTimeMs))
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat, hbeat",
                     "",
                     30);
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
        if(incCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
        if(incCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_3_1() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
        if(incCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsConnect)
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }

    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap",
                     "",
                     30);
        if(incCurr->m_waitTimer->Active())
            throw;
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incCurr->ShouldStartSnapshot())
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderBookCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,    hbeat,                              hbeat",
                     "                                                            obs symbol3 begin rpt 1, obs symbol3 rpt 1 entry symbol3 e1, obs symbol3 rpt 1 end",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->CanStopListeningSnapshot()) // because we did not receive all snapshots for all symbols
            throw;
        if(snapCurr->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 3)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s2", "session1")->BuyQuotes()->Count() != 0)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incCurr->m_startMsgSeqNum != 2)
            throw;
        if(incCurr->m_endMsgSeqNum != 6)
            throw;
        if(snapCurr->m_startMsgSeqNum != 4)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
    }
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "lost obr entry s1 e1, lost hbeat, wait_snap",
                     "obs s1 begin rpt 1, obs s1 rpt 1 entry s1 e1, obs s1 rpt 1 end",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incCurr->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 1)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incCurr->m_startMsgSeqNum != 4)
            throw;
        if(incCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_startMsgSeqNum != 4)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderBookCurr()->UsedItemCount() != 3)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                         hbeat,                                        hbeat",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, hbeat, obs s2 begin rpt 2 end entry s2 e1",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s2", "session1")->RptSeq() != 2)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 3)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s2", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incCurr->m_startMsgSeqNum != 7)
            throw;
        if(incCurr->m_endMsgSeqNum != 6)
            throw;
        if(snapCurr->m_startMsgSeqNum != 5)
            throw;
        if(snapCurr->m_endMsgSeqNum != 4)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    // almost the same as TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderBookCurr()->UsedItemCount() != 3)
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                         obr entry s2 e1,                         obr entry s2 e2",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, obs s2 begin rpt 2 end entry s2 e1 skip_if_suspend",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s2", "session1")->RptSeq() != 2)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderBookTableCurr->UsedItemCount() != 3)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("s2", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incCurr->m_orderBookTableCurr->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incCurr->m_startMsgSeqNum != 7)
            throw;
        if(incCurr->m_endMsgSeqNum != 6)
            throw;
        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
    }
    // we receive snapshot which rpt seq is less than incremental actual rpt seq
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");

        if(!incCurr->m_waitTimer->Active())
            throw;
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->RptSeq() != 3)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->BuyQuotes()->Count() != 3)
            throw;
        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 1)
            throw;
        if(snapCurr->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(snapCurr->m_startMsgSeqNum != 2) // detect that
            throw;
    }
    // we received snapshot for item but item has 2 gaps and snapshot is partially actual
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        incCurr->WaitIncrementalMaxTimeMs(500);
        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 4 entry s1 e4 end",
                     30);
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incCurr->WaitIncrementalMaxTimeMs(500);
        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 5 entry s1 e5 end",
                     30);
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incCurr->HasQueueEntries())
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incCurr->WaitIncrementalMaxTimeMs(500);
        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 6 entry s1 e6 end",
                     30);
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incCurr->HasQueueEntries())
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incCurr->WaitIncrementalMaxTimeMs(500);
        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat",
                     30);
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(!incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s2", "session1")->RptSeq() != 1)
            throw;
        if(incCurr->OrderBookCurr()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4, hbeat ",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat          , obs s1 begin rpt 3 entry s1 e3 end",
                     30);
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incCurr->OrderBookCurr()->QueueEntriesCount() != 0)
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, obr entry s2 e2, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderBookCurr()->GetItem("s2", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // we have received twice the same snapshot (rpt seq num = the same value) which means that item did not receive incremental message so item state is actual
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_7() {
        // do nothing. lets consider that after receiving snapshot item will be in actual state if there is no queue entries
    }
    // we can receive null snapshot i.e. snapshot with LastMsgSeqNumProcessed = 0 RptSeq = 0
    // this means that item has NO DATA
    // so just clear queue entries and decrease session to recv snapshot value
    void TestConnectionCurr_ResetEntriesQueueIfNullSnapshotIsReceived() {
        this->Clear();

        /*
        unsigned char *msg = new unsigned char[52] {
                0x65, 0x23, 0x00, 0x00, 0xe0, 0x12, 0xec, 0x46, 0xe5, 0x23,
                0x68, 0x08, 0x12, 0x7f, 0x4c, 0x74, 0xc0, 0x81, 0x80, 0x00,
                0xe5, 0x52, 0x50, 0x4d, 0xcf, 0x52, 0x55, 0x30, 0x30, 0x30,
                0x41, 0x30, 0x4a, 0x54, 0x5a, 0x46, 0xb1, 0x82, 0x82, 0x93,
                0x80, 0x81, 0xca, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                0x80, 0x80
        };
        incCurr->m_fastProtocolManager->SetNewBuffer(msg, 52);
        incCurr->m_fastProtocolManager->ReadMsgSeqNumber();
        incCurr->m_fastProtocolManager->Decode();
        incCurr->m_fastProtocolManager->Print();
        */


        if(incCurr->OrderBookCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnectionCurr_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnectionCurr_EnterSnapshotMode() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->EnterSnapshotMode();
        if(!incCurr->OrderBookCurr()->GetItem("s1", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnectionCurr_ClearSnapshotMessages_1() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapCurr->m_packets[1]->m_item != 0)
            throw;
        if(snapCurr->m_packets[1]->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnectionCurr_ClearSnapshotMessages_2() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapCurr->m_packets[1]->m_item != 0 ||
           snapCurr->m_packets[2]->m_item != 0 ||
           snapCurr->m_packets[3]->m_item != 0)
            throw;
        if(snapCurr->m_packets[1]->m_processed != false ||
           snapCurr->m_packets[2]->m_processed != false ||
           snapCurr->m_packets[3]->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnectionCurr_ClearSnapshotMessages_3() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        snapCurr->WaitSnapshotMaxTimeMs(50);
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapCurr->m_packets[i]->m_item != 0 || snapCurr->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnectionCurr_ClearSnapshotMessages_4() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        snapCurr->WaitSnapshotMaxTimeMs(50);
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat, obs s1 rpt 2 entry s1 e2, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(incCurr->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotCurrPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(snapCurr->m_packets[i]->m_item != 0 || snapCurr->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnectionCurr_ClearSnapshotMessages() {
        printf("OBR TestConnectionCurr_ClearSnapshotMessages_1\n");
        TestConnectionCurr_ClearSnapshotMessages_1();
        printf("OBR TestConnectionCurr_ClearSnapshotMessages_2\n");
        TestConnectionCurr_ClearSnapshotMessages_2();
        printf("OBR TestConnectionCurr_ClearSnapshotMessages_3\n");
        TestConnectionCurr_ClearSnapshotMessages_3();
        printf("OBR TestConnectionCurr_ClearSnapshotMessages_4\n");
        TestConnectionCurr_ClearSnapshotMessages_4();
    }
    void TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot() {
        printf("OBR TestConnectionCurr_EnterSnapshotMode\n");
        TestConnectionCurr_EnterSnapshotMode();
        printf("OBR TestConnectionCurr_ClearSnapshotMessages\n");
        TestConnectionCurr_ClearSnapshotMessages();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_1();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_2();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_3();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_4();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnectionCurr_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incCurr->OrderBookCurr());
        this->Clear();
        incCurr->StartListenSnapshot();

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        SendMessages(incCurr, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 1),
                                             new TestTemplateItemInfo("s2", "e1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 4),
                                             new TestTemplateItemInfo("s2", "e1", 4),
                                     }, 2)
        }, 2);

        if(!incCurr->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderBookCurr());

        incCurr->OrderBookCurr()->Clear();
    }

    void TestConnectionCurr() {
        this->m_helper->SetCurrMode();
        printf("OBR TestConnectionCurr_AllSymbolsAreOk\n");
        TestConnectionCurr_AllSymbolsAreOk();
        printf("OBR TestConnectionCurr_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnectionCurr_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("OBR TestConnectionCurr_AllSymbolsAreOkButOneMessageLost\n");
        TestConnectionCurr_AllSymbolsAreOkButOneMessageLost();
        printf("OBR TestConnectionCurr_SkipHearthBeatMessages_Incremental\n");
        TestConnectionCurr_SkipHearthBeatMessages_Incremental();
        printf("OBR TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnectionCurr_ParallelWorkingIncrementalAndSnapshot();
        printf("OBR TestConnectionCurr_NotAllSymbolsAreOk\n");
        TestConnectionCurr_NotAllSymbolsAreOk();
        printf("OBR TestConnectionCurr_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnectionCurr_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("OBR TestConnectionCurr_StopTimersAfterReconnect\n");
        TestConnectionCurr_StopTimersAfterReconnect();
        printf("OBR TestConnectionCurr_SnapshotSomeMessagesReceivedLater\n");
        TestConnectionCurr_SnapshotSomeMessagesReceivedLater();
        printf("OBR TestConnectionCurr_SnapshotSomeMessagesNotReceived\n");
        TestConnectionCurr_SnapshotSomeMessagesNotReceived();
        printf("OBR TestConnectionCurr_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnectionCurr_LastFragmentReceivedBeforeRouteFirst();
        printf("OBR TestConnectionCurr_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnectionCurr_RouteFirstReceived_AfterSomeDummyMessages();
        printf("OBR TestConnectionCurr_RouteFirstReceived_Empty\n");
        TestConnectionCurr_RouteFirstReceived_Empty();
        printf("OBR TestConnectionCurr_TestSnapshotNoMessagesAtAll\n");
        TestConnectionCurr_TestSnapshotNoMessagesAtAll();
        printf("OBR TestConnectionCurr_OneMessageReceived\n");
        TestConnectionCurr_OneMessageReceived();
        printf("OBR TestConnectionCurr_Clear_AfterIncremental\n");
        TestConnectionCurr_Clear_AfterIncremental();
        printf("OBR TestConnectionCurr_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnectionCurr_TestIncMessageLost_AndWaitTimerElapsed();
        printf("OBR TestConnectionCurr_TestSnapshotCollect\n");
        TestConnectionCurr_TestSnapshotCollect();
        printf("OBR TestConnectionCurr_TestSnapshotNotCollect\n");
        TestConnectionCurr_TestSnapshotMessageLostAndTimeExpired();
        printf("OBR TestConnectionCurr_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnectionCurr_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("OBR TestConnectionCurr_EmptyTest\n");
        TestConnectionCurr_EmptyTest();
        printf("OBR TestConnectionCurr_TestCorrectIncMessages\n");
        TestConnectionCurr_TestCorrectIncMessages();
        printf("OBR TestConnectionCurr_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnectionCurr_TestIncMessagesLost_AndWhenAppeared();
        printf("OBR TestConnectionCurr_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnectionCurr_TestInc2MessagesLost_AppearedThen2Messages();
        printf("OBR TestConnectionCurr_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnectionCurr_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("OBR TestConnectionCurr_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnectionCurr_TestInc2MessagesLost_AppearedSeparately_2_1();
    }





    void TestOrderBookTableItem() {
        printf("OBR TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("OBR TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("OBR TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("OBR TestTable_Default\n");
        TestTable_Default();
        printf("OBR TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("OBR TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("OBR TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("OBR TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("OBR Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("OBR TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("OBR TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("OBR TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("OBR TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
        TestTable_IncorrectApplySnapshot_WhenMessageSkipped();
    }

    void TestStringIdComparer() {
        char buf[128];
        for(int i = 1; i < 128; i++) {
            buf[i] = (char)(0x30 + i);
        }
        for(int i = 1; i < 128; i++) {
            if(!StringIdComparer::Equal(buf, i, buf, i))
                throw;
        }
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_1() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_2() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->OrderBookFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_3() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2, obr entry del s1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
        this->incFond->OrderBookFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_4() {
        FastOBSFONDItemInfo *info = this->m_helper->CreateOBSFondItemInfo(1, 1, 1, 1, MDEntryType::mdetBuyQuote, "e1");
        if(info->Allocator->Count() != 1)
            throw;
        info->Used = false;
        info->ReleaseUnused();
        if(info->Allocator->Count() != 0)
            throw;
        info->ReleaseUnused();
        if(info->Allocator->Count() != 0)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_5() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2, obr entry change s1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->OrderBookFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_1() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                           "                                                  obs begin s1 entry s1 e2 rpt 2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2() {
        this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, lost obr entry s1 e2 entry s1 e3, wait_snap, hbeat",
                           "                                                   obs begin s1 entry s1 e2 rpt 2, obs s1 entry s1 e3 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        /*this->Clear();

        this->incFond->OrderBookFond()->Add("s1", "session1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   obs begin s1 entry s1 e1 rpt 2, obs s1 entry s1 e2, obs s1 entry s1 e3, obs s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 3)
            throw;*/
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_4() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->OrderBookFond()->Add("s2", "session1");
        incFond->OrderBookFond()->Add("symbol3", "session1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                              hbeat,                              hbeat",
                     "                                                       obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, hbeat, obs s2 begin rpt 2 end entry s2 e1",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_5() {
        this->Clear();
        incFond->OrderBookFond()->Add("s1", "session1");
        incFond->Start();

        int prevCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, obr entry s1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     obs s1 begin rpt 0 lastmsg 0 entry s1 e1 end",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_6() {
        this->Clear();

        incFond->OrderBookFond()->Add("s1", "session1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        int newCount = this->snapFond->m_fastProtocolManager->m_oBSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond() {
        this->m_helper->SetFondMode();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_1();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_2();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_3();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_4();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_5();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_1();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_3();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_4();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_5();
        printf("TestInfoAndItemInfoUsageAndAllocationFond_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_6();
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1, obr entry s1 e2",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incCurr->OrderBookCurr()->Clear();
        newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1, obr entry s1 e2, obr entry del s1 e1",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 1)
            throw;
        this->incCurr->OrderBookCurr()->Clear();
        newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4() {
        FastOBSCURRItemInfo *info = this->m_helper->CreateOBSCurrItemInfo(1, 1, 1, 1, MDEntryType::mdetBuyQuote, "e1");
        if(info->Allocator->Count() != 1)
            throw;
        info->Used = false;
        info->ReleaseUnused();
        if(info->Allocator->Count() != 0)
            throw;
        info->ReleaseUnused();
        if(info->Allocator->Count() != 0)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1, obr entry s1 e2, obr entry change s1 e1",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incCurr->OrderBookCurr()->Clear();
        newCount = this->incCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                           "                                                  obs begin s1 entry s1 e2 rpt 2 end",
                           30);

        int newCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2() {
        this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1, lost obr entry s1 e2 entry s1 e3, wait_snap, hbeat",
                           "                                                   obs begin s1 entry s1 e2 rpt 2, obs s1 entry s1 e3 end",
                           30);

        int newCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        /*this->Clear();

        this->incCurr->OrderBookCurr()->Add("s1", "session1");
        int prevCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   obs begin s1 entry s1 e1 rpt 2, obs s1 entry s1 e2, obs s1 entry s1 e3, obs s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 3)
            throw;*/
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->OrderBookCurr()->Add("s2", "session1");
        incCurr->OrderBookCurr()->Add("symbol3", "session1");

        int prevCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                              hbeat,                              hbeat",
                     "                                                       obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, hbeat, obs s2 begin rpt 2 end entry s2 e1",
                     30);
        int newCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5() {
        this->Clear();
        incCurr->OrderBookCurr()->Add("s1", "session1");
        incCurr->Start();

        int prevCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, lost obr entry s1 e2, obr entry s1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     obs s1 begin rpt 0 lastmsg 0 entry s1 e1 end",
                     30);
        int newCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6() {
        this->Clear();

        incCurr->OrderBookCurr()->Add("s1", "session1");

        int prevCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        SendMessages(incCurr, snapCurr,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        int newCount = this->snapCurr->m_fastProtocolManager->m_oBSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr() {
        this->m_helper->SetCurrMode();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5();
        printf("TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6();
    }



    void Test() {
        TestDefaults();
        TestInfoAndItemInfoUsageAndAllocationFond();
        TestInfoAndItemInfoUsageAndAllocationCurr();
        TestStringIdComparer();
        Test_OBR_FOND();
        Test_OBR_CURR();
        TestOrderBookTableItem();
        TestConnectionFond();
        TestConnectionCurr();
    }
};

#endif //HFT_ROBOT_ORDERBOOKTESTERCURR_H
