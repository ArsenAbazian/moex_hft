//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_ORDERTESTER_H
#define HFT_ROBOT_ORDERTESTER_H

#include "../FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class OrderTester {
    TestMessagesHelper      *m_helper;
    FeedConnection_FOND_OLR *incFond;
    FeedConnection_FOND_OLS *snapFond;
    FeedConnection_CURR_OLR *incCurr;
    FeedConnection_CURR_OLS *snapCurr;
    MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo> *m_table_fond;
public:
    OrderTester() {
        this->m_helper = new TestMessagesHelper();
        this->m_table_fond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->incFond = new FeedConnection_FOND_OLR("OLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->incCurr = new FeedConnection_CURR_OLR("OLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snapFond = new FeedConnection_FOND_OLS("OLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);
        this->snapCurr = new FeedConnection_CURR_OLS("OLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);

        this->snapFond->m_fakeConnect = true;
        this->incFond->m_fakeConnect = true;
        this->incCurr->m_fakeConnect = true;
        this->snapCurr->m_fakeConnect = true;

    }
    ~OrderTester() {
        delete this->incFond;
        delete this->incCurr;
        delete this->snapFond;
        delete this->snapCurr;
        delete this->m_helper;
        delete this->m_table_fond;
    }

    void TestItem(OrderInfo<FastOLSFONDItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo> *table) {
        for(int i = 0; i < this->m_table_fond->SymbolsCount(); i++) {
            for(int j = 0; j < this->m_table_fond->Symbol(i)->Count(); j++) {
                OrderInfo<FastOLSFONDItemInfo> *item = this->m_table_fond->Item(i, j);
                TestItem(item);
            }
        }
    }

    void Clear() {
        incFond->SetSnapshot(this->snapFond);
        incFond->OrderFond()->Clear();
        incCurr->OrderCurr()->Clear();
        incFond->ClearMessages();
        incFond->WaitIncrementalMaxTimeMs(50);
        incFond->m_waitTimer->Stop();
        incFond->m_waitTimer->Stop(1);
        snapFond->ClearMessages();
        snapFond->WaitSnapshotMaxTimeMs(50);
        incFond->StartListenSnapshot();
        snapFond->m_waitTimer->Stop();
        snapFond->Stop();
        incFond->Stop();

        this->m_helper->Clear();
        incFond->Start();
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(!item1->Used)
            throw;
        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOLSFONDItemInfo *quote = obi->BuyQuotes()->Item(0);
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

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e4", 2))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "e3", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi2 = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 2, "e4", 2))
            throw;

        FastOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");

        FastOLSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOLSFONDItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOLSFONDItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e4", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        this->incFond->OrderFond()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incFond->OrderFond()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_FOND() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi2 = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        FastOLSFONDInfo *info2 = this->m_helper->CreateFastOLSFondInfo("t1s2", "t1");
        FastOLSFONDItemInfo *newItem1 = this->m_helper->CreateFastOLSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "e7");
        FastOLSFONDItemInfo *newItem2 = this->m_helper->CreateFastOLSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "e8");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->OrderFond()->ObtainSnapshotItem(info2);
        this->incFond->OrderFond()->ProcessSnapshot(info2);

        if(this->incFond->OrderFond()->UsedItemCount() != 2)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi3 = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("t1s2", 4, "t1", 2);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOLSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);

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

    void Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOLSFONDItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Item(0);
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

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e4", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2,"e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 2,"e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2,"e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi2 = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 2, "e4", 2))
            throw;

        FastOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetSellQuote, "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");

        FastOLSFONDItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOLSFONDItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOLSFONDItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOLSFONDItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e4", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        this->incFond->OrderFond()->Clear();
        if(this->incFond->OrderFond()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_FOND_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "e1", 1);
        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "e2", 2);
        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "e3", 3);
        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        FastOLSFONDInfo *info2 = this->m_helper->CreateFastOLSFondInfo("t1s2", "t1");
        FastOLSFONDItemInfo *newItem1 = this->m_helper->CreateFastOLSFondItemInfo(7,-2, 1, 2, mdetSellQuote, "e7");
        FastOLSFONDItemInfo *newItem2 = this->m_helper->CreateFastOLSFondItemInfo(8,-2, 1, 2, mdetSellQuote, "e8");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->OrderFond()->ObtainSnapshotItem(info2);
        this->incFond->OrderFond()->ProcessSnapshot(info2);

        if(this->incFond->OrderFond()->UsedItemCount() != 2)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi3 = this->incFond->OrderFond()->GetItem("s1", "t1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("t1s2", 4, "t1", 2);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOLSFONDItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        FastOLSFONDItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

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

    void Test_OnIncrementalRefresh_OLR_CURR_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;

        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e4", 4);

        item1->RptSeq = 1;
        item2->RptSeq = 2;
        item3->RptSeq = 3;
        item4->RptSeq = 4;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOLSCURRItemInfo *quote = obi->BuyQuotes()->Start()->Data();
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

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e2", 2))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e4", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 2, "e4", 2))
            throw;

        FastOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetBuyQuote,
                                                           "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");

        FastOLSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOLSCURRItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOLSCURRItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e4", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        this->incCurr->OrderCurr()->Clear();
        if(this->incCurr->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        FastOLSCURRInfo *info2 = this->m_helper->CreateFastOLSCurrInfo("t1s2", "t1");
        FastOLSCURRItemInfo *newItem1 = this->m_helper->CreateFastOLSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "e7");
        FastOLSCURRItemInfo *newItem2 = this->m_helper->CreateFastOLSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "e8");

        info2->RptSeq = 5;
        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderCurr()->ObtainSnapshotItem(info2);
        this->incCurr->OrderCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 2)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi3 = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("t1s2", 4, "t1", 2);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOLSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);

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

    void Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;

        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOLSCURRItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
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

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e3", 2))
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "e4", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 2, "e4", 2))
            throw;

        FastOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange,
                                                           mdetSellQuote, "e2", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");

        FastOLSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOLSCURRItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOLSCURRItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "e1", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "e2", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "e3", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "e4", 2))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        this->incCurr->OrderCurr()->Clear();
        if(this->incCurr->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e1", 1);
        FastOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e2", 2);
        FastOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e3", 3);
        FastOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote,
                                                           "e4", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        FastOLSCURRInfo *info2 = this->m_helper->CreateFastOLSCurrInfo("t1s2", "t1");
        FastOLSCURRItemInfo *newItem1 = this->m_helper->CreateFastOLSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "e7");
        FastOLSCURRItemInfo *newItem2 = this->m_helper->CreateFastOLSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "e8");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi3 = this->incCurr->OrderCurr()->GetItem("s1", "t1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("t1s2", 4, "t1", 2);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOLSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);

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

    void Test_OnIncrementalRefresh_OLR_FOND() {
        printf("Test_OnIncrementalRefresh_OLR_FOND_Add\n");
        Test_OnIncrementalRefresh_OLR_FOND_Add();
        printf("Test_OnIncrementalRefresh_OLR_FOND_Remove\n");
        Test_OnIncrementalRefresh_OLR_FOND_Remove();
        printf("Test_OnIncrementalRefresh_OLR_FOND_Change\n");
        Test_OnIncrementalRefresh_OLR_FOND_Change();
        printf("Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OLR_FOND_SellQuotes() {
        printf("Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes();
        printf("Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes();
        printf("Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes();
        printf("Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OnIncrementalRefresh_OLR_CURR() {
        printf("Test_OnIncrementalRefresh_OLR_CURR_Add\n");
        Test_OnIncrementalRefresh_OLR_CURR_Add();
        printf("Test_OnIncrementalRefresh_OLR_CURR_Remove\n");
        Test_OnIncrementalRefresh_OLR_CURR_Remove();
        printf("Test_OnIncrementalRefresh_OLR_CURR_Change\n");
        Test_OnIncrementalRefresh_OLR_CURR_Change();
        printf("Test_Clear_Curr\n");
        Test_Clear_Curr();
    }

    void Test_OnIncrementalRefresh_OLR_CURR_SellQuotes() {
        printf("Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes();
        printf("Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes();
        printf("Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes();
        printf("Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OLR_CURR() {
        printf("Test_OnIncrementalRefresh_OLR_CURR\n");
        Test_OnIncrementalRefresh_OLR_CURR();
        printf("Test_OnFullRefresh_OLS_CURR\n");
        Test_OnFullRefresh_OLS_CURR();
        printf("Test_OnIncrementalRefresh_OLR_CURR_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_SellQuotes();
        printf("Test_OnFullRefresh_OLS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OLS_CURR_SellQuotes();
    }

    void Test_OLR_FOND() {
        printf("Test_OnIncrementalRefresh_OLR_FOND\n");
        Test_OnIncrementalRefresh_OLR_FOND();
        printf("Test_OnFullRefresh_OLS_FOND\n");
        Test_OnFullRefresh_OLS_FOND();
        printf("Test_OnIncrementalRefresh_OLR_FOND_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_SellQuotes();
        printf("Test_OnFullRefresh_OLS_FOND_SellQuotes\n");
        Test_OnFullRefresh_OLS_FOND_SellQuotes();
    }

    void TestDefaults() {
        if(this->incFond->OrderFond()->SymbolsCount() != 0)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incFond->OrderFond());
        //this->TestTableItemsAllocator(incCurr->OrderCurr());
    }

    void TestTableItem_CorrectBegin() {
        OrderInfo<FastOLSFONDItemInfo> *tb = new OrderInfo<FastOLSFONDItemInfo>();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e1");
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
        OrderInfo<FastOLSFONDItemInfo> *tb = new OrderInfo<FastOLSFONDItemInfo>();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e1");
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
        OrderInfo<FastOLSFONDItemInfo> *tb = new OrderInfo<FastOLSFONDItemInfo>();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e1");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e2");
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

        FastOLSFONDItemInfo *item3 = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e3");
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

        this->m_table_fond->Clear();

        TestTableItemsAllocator(this->m_table_fond);

        
    }

    void TestTable_AfterClear() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item = this->m_helper->CreateFastOLRFondItemInfo("s1", "session1", "e1");
        item->RptSeq = 1;

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateFastOLRFondItemInfo("s1", "session1", "e1");
        item2->RptSeq = 2;

        FastOLSFONDItemInfo *item3 = this->m_helper->CreateFastOLRFondItemInfo("s1", "session1", "e1");
        item3->RptSeq = 4;

        this->m_table_fond->ProcessIncremental(item);
        this->m_table_fond->ProcessIncremental(item2);
        this->m_table_fond->ProcessIncremental(item3);

        if(this->m_table_fond->UsedItemCount() != 1)
            throw;
        OrderInfo<FastOLSFONDItemInfo> *tableItem = this->m_table_fond->GetItem("s1", "session1");
        if(tableItem->EntriesQueue()->MaxIndex() != 1) // 3 is empty and 4 has value
            throw;
        this->m_table_fond->Clear();;
        if(this->m_table_fond->UsedItemCount() != 0)
            throw;
        if(tableItem->RptSeq() != 0)
            throw;
        if(tableItem->BuyQuotes()->Count() != 0)
            throw;
        if(tableItem->EntriesQueue()->MaxIndex() != -1)
            throw;

        
    }

    void TestTable_CorrectBegin() {

        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        if(!this->m_table_fond->ProcessIncremental(item1))
            throw;

        
    }

    void TestTable_IncorrectBegin() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 2;

        if(this->m_table_fond->ProcessIncremental(item1))
            throw;

        
    }

    void TestTable_SkipMessages() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        if(!this->m_table_fond->ProcessIncremental(item1))
            throw;

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 3);
        item2->RptSeq = 3;

        if(this->m_table_fond->ProcessIncremental(item2))
            throw;

        
    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        if(!this->m_table_fond->ProcessIncremental(item1))
            throw;

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("SYMBOL2", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item2->RptSeq = 1;

        if(!this->m_table_fond->ProcessIncremental(item2))
            throw;

        if(this->m_table_fond->UsedItemCount() != 2)
            throw;

        
    }

    void TestTable_CorrectApplySnapshot() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table_fond->ProcessIncremental(item1);

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e2", 3);
        item2->RptSeq = 3;

        if(this->m_table_fond->ProcessIncremental(item2))
            throw;

        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e3", 4);
        item3->RptSeq = 4;

        if(this->m_table_fond->ProcessIncremental(item3))
            throw;

        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e4", 5);
        item4->RptSeq = 5;

        if(this->m_table_fond->ProcessIncremental(item4))
            throw;

        FastOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e5", 3);
        item5->RptSeq = 3;

        FastOLSFONDInfo *info = this->m_helper->CreateFastOLSFondInfo("s1", "session1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderInfo<FastOLSFONDItemInfo> *tb = this->m_table_fond->GetItem("s1", "session1");

        this->m_table_fond->ObtainSnapshotItem(info);
        this->m_table_fond->StartProcessSnapshot(info);
        if(tb != this->m_table_fond->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table_fond->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(!this->m_table_fond->EndProcessSnapshot())
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

        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table_fond->ProcessIncremental(item1);

        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e3", 4);
        item3->RptSeq = 4;

        if(this->m_table_fond->ProcessIncremental(item3))
            throw;

        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e4", 5);
        item4->RptSeq = 5;

        if(this->m_table_fond->ProcessIncremental(item4))
            throw;

        FastOLSFONDInfo *info1 = this->m_helper->CreateFastOLSFondInfo("s1", "session1");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e2");

        FastOLSFONDInfo *info2 = this->m_helper->CreateFastOLSFondInfo("s1", "session1");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = this->m_helper->CreateFastOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "e2");

        OrderInfo<FastOLSFONDItemInfo> *tb = this->m_table_fond->GetItem("s1", "session1");

        this->m_table_fond->ObtainSnapshotItem(info1);
        this->m_table_fond->StartProcessSnapshot(info1);
        if(tb != this->m_table_fond->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table_fond->ProcessSnapshot(info1);
        this->m_table_fond->ProcessSnapshot(info2);
        if(!this->m_table_fond->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 4)
            throw;
    }

    void TestTable_IncorrectApplySnapshot() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table_fond->ProcessIncremental(item1);

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e2", 4);
        item2->RptSeq = 4;

        if(this->m_table_fond->ProcessIncremental(item2))
            throw;

        FastOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e3", 5);
        item3->RptSeq = 5;

        if(this->m_table_fond->ProcessIncremental(item3))
            throw;

        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e4", 6);
        item4->RptSeq = 6;

        if(this->m_table_fond->ProcessIncremental(item4))
            throw;

        FastOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e5", 2);
        item5->RptSeq = 2;

        FastOLSFONDInfo *info = this->m_helper->CreateFastOLSFondInfo("s1", "session1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderInfo<FastOLSFONDItemInfo> *tb = this->m_table_fond->GetItem("s1", "session1");

        this->m_table_fond->ObtainSnapshotItem(info);
        this->m_table_fond->StartProcessSnapshot(info);
        if(tb != this->m_table_fond->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table_fond->ProcessSnapshot(info->GroupMDEntries, 1, 2);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 2)
            throw;
        if(this->m_table_fond->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 2)
            throw;
    }

    void TestTable_IncorrectApplySnapshot_WhenMessageSkipped() {
        this->m_table_fond->Clear();

        FastOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e1", 1);
        item1->RptSeq = 1;

        this->m_table_fond->ProcessIncremental(item1);

        FastOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e2", 4);
        item2->RptSeq = 4;

        if(this->m_table_fond->ProcessIncremental(item2))
            throw;

        FastOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e4", 6);
        item4->RptSeq = 6;

        if(this->m_table_fond->ProcessIncremental(item4))
            throw;

        FastOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("s1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "e5", 3);
        item5->RptSeq = 3;

        FastOLSFONDInfo *info = this->m_helper->CreateFastOLSFondInfo("s1", "session1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderInfo<FastOLSFONDItemInfo> *tb = this->m_table_fond->GetItem("s1", "session1");

        this->m_table_fond->ObtainSnapshotItem(info);
        this->m_table_fond->StartProcessSnapshot(info);
        if(tb != this->m_table_fond->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table_fond->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(this->m_table_fond->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 4)
            throw;
        this->m_table_fond->ObtainSnapshotItem(info);
        if(this->m_table_fond->EndProcessSnapshot())
            throw;
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        this->m_helper->SendMessages(fci, fcs, inc, snap, delay);
        this->TestSnapshotPacketsCleared();
    }

    void SendMessages(FeedConnection *c, TestTemplateInfo **items, int count) {
        this->m_helper->SendMessages(c, items, count);
    }

    void TestConnection_EmptyTest() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnection_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<FastOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("s1", "session1");
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
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<FastOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("s1", "session1");
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
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e4", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<FastOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("s1", "session1");
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
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

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
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<FastOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("s1", "session1");
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
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

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
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "session1", "e5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<FastOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("s1", "session1");
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

    void TestConnection_TestSnapshotNoMessagesAtAll() {
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

    void TestConnection_OneMessageReceived() {
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
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", false, false,
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

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", true, false,
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

    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 1, "s1", "session1", false, false,
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
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", false, false,
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
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 3, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 4, "s1", "session1", false, false,
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
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 5, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 6, "s1", "session1", true, false,
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

    void TestConnection_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 1, "s1", "session1", false, true,
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

    void TestConnection_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapFond->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 3, "s1", "session1", false, false,
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

    void TestConnection_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 1, "s1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4)
        }, 1);

        snapFond->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 3, "s1", "session1", false, false,
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
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", false, false,
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

    void TestConnection_StopTimersAfterReconnect() {
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

    void TestConnection_TestSnapshotCollect() {
        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", true, true,
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
        OrderInfo<FastOLSFONDItemInfo> *tableItem = incFond->OrderFond()->GetItem("s1", "session1");

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->OrderFond()->UsedItemCount() != 1)
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

    void TestConnection_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        snapFond->WaitSnapshotMaxTimeMs(100);
        incFond->StartListenSnapshot();

        if(!snapFond->m_waitTimer->Active())
            throw;

        snapFond->m_waitTimer->Stop();
        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 4, "s1", "session1", false, true,
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
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->OrderFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 1),
                                             new TestTemplateItemInfo("symbol2", "e1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 4),
                                             new TestTemplateItemInfo("symbol2", "e1", 4),
                                     }, 2)
        }, 2);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->OrderFond()->UsedItemCount() != 2)
            throw;

        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMilliseconds() < incFond->WaitIncrementalMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OLS_FOND, 2, "s1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("e1"),
                                             new TestTemplateItemInfo("e1"),
                                     }, 2, 4)
        }, 1);
        if(!snapFond->Listen_Atom_Snapshot_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderInfo<FastOLSFONDItemInfo> *item1 = incFond->OrderFond()->GetItem("s1", "session1");
        OrderInfo<FastOLSFONDItemInfo> *item2 = incFond->OrderFond()->GetItem("symbol2", "session1");
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

    void TestConnection_SkipHearthBeatMessages_Incremental() {
        this->Clear();

        this->incFond->OrderFond()->Add("s1", "session1");
        this->incFond->StartListenSnapshot();
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, wait_snap, hbeat, hbeat, hbeat",
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

    void TestConnection_AllSymbolsAreOk() {
        this->Clear();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s1 e2, olr entry s1 e3, olr entry symbol2 e1, olr entry symbol2 e2",
                     "",
                     30);
        if(incFond->m_orderTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_orderTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->m_orderTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_NotAllSymbolsAreOk() {
        this->Clear();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, olr entry s1 e3, olr entry symbol2 e1, olr entry symbol2 e2",
                     "",
                     30);
        if(incFond->m_orderTableFond->UsedItemCount() != 2)
            throw;
        if(!incFond->m_orderTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->m_orderTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e2, olr entry s1 e3, olr entry symbol2 e1, olr entry symbol2 e2",
                     "",
                     30);

        if(incFond->m_orderTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_orderTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(incFond->m_orderTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!incFond->ShouldStartSnapshot())
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1",
                     "",
                     30);
        if(incFond->HasPotentiallyLostPackets())
            throw;
        if(incFond->ShouldStartSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat",
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

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat, hbeat",
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
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat, hbeat, hbeat",
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
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
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
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, wait_snap",
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
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol2", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, wait_snap, olr entry s1 e3,    hbeat,                              hbeat",
                     "                                                            ols symbol3 begin rpt 1, ols symbol3 rpt 1 entry symbol3 e1, ols symbol3 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->CanStopListeningSnapshot()) // because we did not receive all snapshots for all symbols
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 0)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "lost olr entry s1 e1, lost hbeat, wait_snap",
                     "ols s1 begin rpt 1, ols s1 rpt 1 entry s1 e1, ols s1 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol2", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, wait_snap, olr entry s1 e3,                         hbeat,                                        hbeat",
                     "                                                            ols symbol3 begin rpt 1 end entry symbol3 e1, ols s1 begin rpt 2 end entry s1 e1, hbeat, ols symbol2 begin rpt 2 end entry symbol2 e1",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_orderTableFond->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "session1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
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
    // almost the same as TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("symbol2", "session1");
        incFond->OrderFond()->Add("symbol3", "session1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry symbol3 e1, wait_snap, olr entry s1 e3,                         olr entry symbol2 e1,                         olr entry symbol2 e2",
                     "                                                            ols symbol3 begin rpt 1 end entry symbol3 e1, ols s1 begin rpt 2 end entry s1 e1, ols symbol2 begin rpt 2 end entry symbol2 e1 skip_if_suspend",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_orderTableFond->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "session1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->GetItem("s1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");

        if(!incFond->m_waitTimer->Active())
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s1 e2, olr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          ols s1 begin rpt 1 entry s1 e1 end",
                     50);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->RptSeq() != 3)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 3)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s1 e2, lost olr entry s1 e3, olr entry s1 e4, lost olr entry s1 e5, olr entry s1 e6, wait_snap, ",
                     "                                                                                                                           ols s1 begin rpt 4 entry s1 e4 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s1 e2, lost olr entry s1 e3, olr entry s1 e4, lost olr entry s1 e5, olr entry s1 e6, wait_snap, ",
                     "                                                                                                                           ols s1 begin rpt 5 entry s1 e5 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s1 e2, lost olr entry s1 e3, olr entry s1 e4, lost olr entry s1 e5, olr entry s1 e6, wait_snap, ",
                     "                                                                                                                           ols s1 begin rpt 6 entry s1 e6 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incFond->WaitIncrementalMaxTimeMs(500);
        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("s2", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s2 e1, lost olr entry s1 e2, wait_snap, hbeat                               lost olr entry s1 e3,               olr entry s1 e4",
                     "                                                                   ols s1 begin rpt 2 entry s1 e2 end, ols s2 begin rpt 1 entry s2 e1 end, hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(!incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incFond->OrderFond()->GetItem("s2", "session1")->RptSeq() != 1)
            throw;
        if(incFond->OrderFond()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("s2", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s2 e1, lost olr entry s1 e2, wait_snap, hbeat                               lost olr entry s1 e3,               olr entry s1 e4, hbeat ",
                     "                                                                   ols s1 begin rpt 2 entry s1 e2 end, ols s2 begin rpt 1 entry s2 e1 end, hbeat          , ols s1 begin rpt 3 entry s1 e3 end",
                     30);
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(incFond->OrderFond()->GetItem("s1", "session1")->EntriesQueue()->HasEntries())
            throw;
        if(incFond->OrderFond()->QueueEntriesCount() != 0)
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->Add("s2", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, olr entry s2 e1, lost olr entry s1 e2, wait_snap, olr entry s2 e2, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->GetItem("s2", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // we have received twice the same snapshot (rpt seq num = the same value) which means that item did not receive incremental message so item state is actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7() {
        // do nothing. lets consider that after receiving snapshot item will be in actual state if there is no queue entries
    }
    // we can receive null snapshot i.e. snapshot with LastMsgSeqNumProcessed = 0 RptSeq = 0
    // this means that item has NO DATA
    // so just clear queue entries and decrease session to recv snapshot value
    void TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived() {
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

        incFond->OrderFond()->Add("s1", "session1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, olr entry s1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     ols s1 begin rpt 0 lastmsg 0 entry s1 e1 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnection_EnterSnapshotMode() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        incFond->OrderFond()->EnterSnapshotMode();
        if(!incFond->OrderFond()->GetItem("s1", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnection_ClearSnapshotMessages_1() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, wait_snap, hbeat",
                     "                                                  ols s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapFond->m_packets[1]->m_item != 0)
            throw;
        if(snapFond->m_packets[1]->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnection_ClearSnapshotMessages_2() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, ols s1 begin rpt 2 entry s1 e2 end",
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
    void TestConnection_ClearSnapshotMessages_3() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        snapFond->WaitSnapshotMaxTimeMs(50);
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, wait_snap, hbeat",
                     "                                                  ols s1 begin rpt 2 entry s1 e2, lost ols s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_item != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnection_ClearSnapshotMessages_4() {
        this->Clear();

        incFond->OrderFond()->Add("s1", "session1");
        snapFond->WaitSnapshotMaxTimeMs(50);
        SendMessages(incFond, snapFond,
                     "olr entry s1 e1, lost olr entry s1 e2, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  ols s1 begin rpt 2 entry s1 e2, lost ols s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat, ols s1 rpt 2 entry s1 e2, ols s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(incFond->OrderFond()->UsedItemCount() != 1)
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
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnection_ClearSnapshotMessages() {
        printf("TestConnection_ClearSnapshotMessages_1\n");
        TestConnection_ClearSnapshotMessages_1();
        printf("TestConnection_ClearSnapshotMessages_2\n");
        TestConnection_ClearSnapshotMessages_2();
        printf("TestConnection_ClearSnapshotMessages_3\n");
        TestConnection_ClearSnapshotMessages_3();
        printf("TestConnection_ClearSnapshotMessages_4\n");
        TestConnection_ClearSnapshotMessages_4();
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot() {
        printf("TestConnection_EnterSnapshotMode\n");
        TestConnection_EnterSnapshotMode();
        printf("TestConnection_ClearSnapshotMessages\n");
        TestConnection_ClearSnapshotMessages();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_4();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnection_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incFond->OrderFond());
        this->Clear();
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->OrderFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 1),
                                             new TestTemplateItemInfo("symbol2", "e1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "e1", 4),
                                             new TestTemplateItemInfo("symbol2", "e1", 4),
                                     }, 2)
        }, 2);

        if(!incFond->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        incFond->OrderFond()->Clear();
    }

    void TestConnection() {
        printf("TestConnection_AllSymbolsAreOk\n");
        TestConnection_AllSymbolsAreOk();
        printf("TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("TestConnection_AllSymbolsAreOkButOneMessageLost\n");
        TestConnection_AllSymbolsAreOkButOneMessageLost();
        printf("TestConnection_SkipHearthBeatMessages_Incremental\n");
        TestConnection_SkipHearthBeatMessages_Incremental();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot();
        printf("TestConnection_NotAllSymbolsAreOk\n");
        TestConnection_NotAllSymbolsAreOk();
        printf("TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("TestConnection_StopTimersAfterReconnect\n");
        TestConnection_StopTimersAfterReconnect();
        printf("TestConnection_SnapshotSomeMessagesReceivedLater\n");
        TestConnection_SnapshotSomeMessagesReceivedLater();
        printf("TestConnection_SnapshotSomeMessagesNotReceived\n");
        TestConnection_SnapshotSomeMessagesNotReceived();
        printf("TestConnection_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnection_LastFragmentReceivedBeforeRouteFirst();
        printf("TestConnection_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnection_RouteFirstReceived_AfterSomeDummyMessages();
        printf("TestConnection_RouteFirstReceived_Empty\n");
        TestConnection_RouteFirstReceived_Empty();
        printf("TestConnection_TestSnapshotNoMessagesAtAll\n");
        TestConnection_TestSnapshotNoMessagesAtAll();
        printf("TestConnection_OneMessageReceived\n");
        TestConnection_OneMessageReceived();
        printf("TestConnection_Clear_AfterIncremental\n");
        TestConnection_Clear_AfterIncremental();
        printf("TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("TestConnection_TestSnapshotCollect\n");
        TestConnection_TestSnapshotCollect();
        printf("TestConnection_TestSnapshotNotCollect\n");
        TestConnection_TestSnapshotMessageLostAndTimeExpired();
        printf("TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestOrderTableItem() {
        printf("TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("TestTable_Default\n");
        TestTable_Default();
        printf("TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
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

    void Test() {
        TestDefaults();
        TestStringIdComparer();
        Test_OLR_FOND();
        Test_OLR_CURR();
        TestOrderTableItem();
        TestConnection();
    }
};

#endif //HFT_ROBOT_ORDERTESTER_H
