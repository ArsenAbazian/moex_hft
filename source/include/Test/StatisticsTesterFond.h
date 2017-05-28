//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_STATISTICSTESTER_H
#define HFT_ROBOT_STATISTICSTESTER_H
#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class StatisticsTesterFond {
    FeedConnection_FOND_MSR *incFond;
    FeedConnection_FOND_MSS *snapFond;
    TestMessagesHelper      *m_helper;
    MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo> *m_table;

public:
    StatisticsTesterFond() {
        this->m_helper = new TestMessagesHelper();
        this->m_table = new MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo>();
        this->incFond = new FeedConnection_FOND_MSR("MSR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snapFond = new FeedConnection_FOND_MSS("MSS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);
        this->m_table->InitSymbols(10, 10);
        this->incFond->StatisticFond()->InitSymbols(10, 10);
        this->incFond->SetMaxLostPacketCountForStartSnapshot(1);

    }
    ~StatisticsTesterFond() {
        delete this->incFond;
        delete this->snapFond;
        delete this->m_helper;
        delete this->m_table;
    }

    void TestItem(StatisticsInfo<AstsGenericItemInfo> *tableItem) {
//        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
//            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
//                throw;
//        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
//            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
//                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo> *table) {
        for(int i = 0; i < table->SymbolsCount(); i++) {
            for(int j = 0; j < table->Symbol(i)->Count(); j++) {
                StatisticsInfo<AstsGenericItemInfo> *item = table->Item(i, j);
                TestItem(item);
            }
        }
    }

    void Clear() {
        incFond->SetSnapshot(this->snapFond);
        incFond->StatisticFond()->Clear();
        incFond->ClearMessages();
        incFond->WaitLostIncrementalMessageMaxTimeMcs(50000);
        incFond->m_waitTimer->Stop();
        incFond->m_waitTimer->Stop(1);
        snapFond->ClearMessages();
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        incFond->StartListenSnapshot();
        snapFond->m_waitTimer->Stop();
        snapFond->Stop();
        incFond->Stop();

        this->m_helper->Clear();
        incFond->Start();
    }
/*
    void Test_OnIncrementalRefresh_MSR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(!item1->Used)
            throw;
        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        StatisticItemDouble *quote = obi->BuyQuotes()->Item(0);
        Decimal price(3, -2);
        Decimal size(1, 2);
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "444444", 6))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
            throw;
    }

    void Test_OnIncrementalRefresh_MSR_FOND_Remove() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

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

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "222222", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "111111", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 2, "333333", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "222222", 2))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 2, "111111", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 2, "111111", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_MSR_FOND_Change() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        StatisticsInfo<AstsGenericItemInfo> *obi2 = this->incFond->StatisticFond()->GetItemByIndex("s1", "t1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 2, "222222", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 2, "111111", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 2, "444444", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 2, "333333", 2))
            throw;

        AstsGenericItemInfo *item5 = this->m_helper->CreateGenericItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");

        AstsGenericItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        AstsGenericItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        AstsGenericItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        AstsGenericItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "111111", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "444444", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "222222", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "333333", 2))
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

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        this->incFond->StatisticFond()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incFond->StatisticFond()->UsedItemCount() != 0)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_MSS_FOND() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        StatisticsInfo<AstsGenericItemInfo> *obi2 = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        AstsGenericInfo *info2 = this->m_helper->CreateMSSFondInfo("t1s2", "t1");
        AstsGenericItemInfo *newItem1 = this->m_helper->CreateGenericItemInfo(7,-2, 1, 2, mdetBuyQuote, "777777");
        AstsGenericItemInfo *newItem2 = this->m_helper->CreateGenericItemInfo(8,-2, 1, 2, mdetBuyQuote, "888888");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->StatisticFond()->ObtainSnapshotItem(info2);
        this->incFond->StatisticFond()->ProcessSnapshot(info2);

        if(this->incFond->StatisticFond()->UsedItemCount() != 2)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi3 = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("t1s2", 4, "t1", 2);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        AstsGenericItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        AstsGenericItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "888888", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "777777", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_MSR_FOND_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        StatisticItemDouble *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "111111", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "111111", 2))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "222222", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "333333", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "111111", 2))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "222222", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->StatisticFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "333333", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "444444", 2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "111111", 2))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 2, "222222", 2))
            throw;
    }

    void Test_OnIncrementalRefresh_MSR_FOND_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItemBySecurityId("s1", "t1");
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"333333", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2,"111111", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 2,"222222", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"111111", 2))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 2,"222222", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 2,"111111", 2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_MSR_FOND_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        StatisticsInfo<AstsGenericItemInfo> *obi2 = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 2, "333333", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 2, "444444", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 2, "111111", 2))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 2, "222222", 2))
            throw;

        AstsGenericItemInfo *item5 = this->m_helper->CreateGenericItemInfo("s1", "t1", 24, -3, 1, 3, mduaChange, mdetSellQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");

        AstsGenericItemInfo *qt1 = obi->SellQuotes()->Item(0);
        AstsGenericItemInfo *qt2 = obi->SellQuotes()->Item(1);
        AstsGenericItemInfo *qt3 = obi->SellQuotes()->Item(2);
        AstsGenericItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "333333", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "222222", 2))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 2, "444444", 2))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 2, "111111", 2))
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

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        this->incFond->StatisticFond()->Clear();
        if(this->incFond->StatisticFond()->UsedItemCount() != 0)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_MSS_FOND_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        AstsIncrementalMSRFONDInfo *info = new AstsIncrementalMSRFONDInfo;
        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "t1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "t1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "t1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "t1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_MSR_FOND(info);

        AstsGenericInfo *info2 = this->m_helper->CreateMSSFondInfo("t1s2", "t1");
        AstsGenericItemInfo *newItem1 = this->m_helper->CreateGenericItemInfo(7,-2, 1, 2, mdetSellQuote, "777777");
        AstsGenericItemInfo *newItem2 = this->m_helper->CreateGenericItemInfo(8,-2, 1, 2, mdetSellQuote, "888888");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->StatisticFond()->ObtainSnapshotItem(info2);
        this->incFond->StatisticFond()->ProcessSnapshot(info2);

        if(this->incFond->StatisticFond()->UsedItemCount() != 2)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi3 = this->incFond->StatisticFond()->GetItem("s1", "t1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        StatisticsInfo<AstsGenericItemInfo> *obi = this->incFond->StatisticFond()->GetItem("t1s2", 4, "t1", 2);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        AstsGenericItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        AstsGenericItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "777777", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "888888", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_MSR_FOND() {
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_Add\n");
        Test_OnIncrementalRefresh_MSR_FOND_Add();
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_Remove\n");
        Test_OnIncrementalRefresh_MSR_FOND_Remove();
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_Change\n");
        Test_OnIncrementalRefresh_MSR_FOND_Change();
        printf("MSR FOND Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_MSR_FOND_SellQuotes() {
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_MSR_FOND_Add_SellQuotes();
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_MSR_FOND_Remove_SellQuotes();
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_MSR_FOND_Change_SellQuotes();
        printf("MSR FOND Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_MSR_FOND() {
        this->m_helper->SetFondMode();
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND\n");
        Test_OnIncrementalRefresh_MSR_FOND();
        printf("MSR FOND Test_OnFullRefresh_MSS_FOND\n");
        Test_OnFullRefresh_MSS_FOND();
        printf("MSR FOND Test_OnIncrementalRefresh_MSR_FOND_SellQuotes\n");
        Test_OnIncrementalRefresh_MSR_FOND_SellQuotes();
        printf("MSR FOND Test_OnFullRefresh_MSS_FOND_SellQuotes\n");
        Test_OnFullRefresh_MSS_FOND_SellQuotes();
    }

    void TestDefaults() {
        if(this->incFond->StatisticFond()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incFond->StatisticFond());
    }

    void TestTableItem_CorrectBegin() {
        StatisticsInfo<AstsGenericItemInfo> *tb = new StatisticsInfo<AstsGenericItemInfo>();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
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
        StatisticsInfo<AstsGenericItemInfo> *tb = new StatisticsInfo<AstsGenericItemInfo>();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
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
        StatisticsInfo<AstsGenericItemInfo> *tb = new StatisticsInfo<AstsGenericItemInfo>();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");
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

        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "333333");
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

        AstsGenericItemInfo *item = this->m_helper->CreateGenericItemInfo("s1", "ses1", "111111");
        item->RptSeq = 1;

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "ses1", "111111");
        item2->RptSeq = 2;

        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "ses1", "111111");
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item);
        this->m_table->ProcessIncremental(item2);
        this->m_table->ProcessIncremental(item3);

        if(this->m_table->UsedItemCount() != 1)
            throw;
        StatisticsInfo<AstsGenericItemInfo> *tableItem = this->m_table->GetItem("s1", "ses1");
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

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1))
            throw;


    }

    void TestTable_IncorrectBegin() {
        this->m_table->Clear();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 2;

        if(this->m_table->ProcessIncremental(item1))
            throw;


    }

    void TestTable_SkipMessages() {
        this->m_table->Clear();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1))
            throw;

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2))
            throw;


    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->m_table->Clear();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1))
            throw;

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s2", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item2->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item2))
            throw;

        if(this->m_table->UsedItemCount() != 2)
            throw;


    }

    void TestTable_CorrectApplySnapshot() {
        this->m_table->Clear();

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "222222", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2))
            throw;

        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3))
            throw;

        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        AstsGenericItemInfo *item5 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsGenericInfo *info = this->m_helper->CreateMSSFondInfo("s1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        StatisticsInfo<AstsGenericItemInfo> *tb = this->m_table->GetItem("s1", "ses1");

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

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3))
            throw;

        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        AstsGenericInfo *info1 = this->m_helper->CreateMSSFondInfo("s1", "ses1");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        AstsGenericInfo *info2 = this->m_helper->CreateMSSFondInfo("s1", "ses1");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = this->m_helper->CreateGenericItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        StatisticsInfo<AstsGenericItemInfo> *tb = this->m_table->GetItem("s1", "ses1");

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

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2))
            throw;

        AstsGenericItemInfo *item3 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "333333", 5);
        item3->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item3))
            throw;

        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        AstsGenericItemInfo *item5 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "555555", 2);
        item5->RptSeq = 2;

        AstsGenericInfo *info = this->m_helper->CreateMSSFondInfo("s1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        StatisticsInfo<AstsGenericItemInfo> *tb = this->m_table->GetItem("s1", "ses1");

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

        AstsGenericItemInfo *item1 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1);

        AstsGenericItemInfo *item2 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2))
            throw;

        AstsGenericItemInfo *item4 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4))
            throw;

        AstsGenericItemInfo *item5 = this->m_helper->CreateGenericItemInfo("s1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsGenericInfo *info = this->m_helper->CreateMSSFondInfo("s1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        StatisticsInfo<AstsGenericItemInfo> *tb = this->m_table->GetItem("s1", "ses1");

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
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 3)}, 3);

    }

    void TestConnectionFond_TestCorrectIncMessages() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "444444", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(incFond->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incFond->StatisticFond()->GetItemByIndex("s1", "ses1")->BuyQuotes()->Count() != 4)
            throw;
    }

     *
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * *
    void TestConnectionFond_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        StatisticsInfo<AstsGenericItemInfo> *item = incFond->StatisticFond()->GetItem("s1", "ses1");
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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "444444", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        StatisticsInfo<AstsGenericItemInfo> *item = incFond->StatisticFond()->GetItem("s1", "ses1");
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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "444444", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        StatisticsInfo<AstsGenericItemInfo> *item = incFond->StatisticFond()->GetItem("s1", "ses1");
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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(!incFond->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        StatisticsInfo<AstsGenericItemInfo> *item = incFond->StatisticFond()->GetItem("s1", "ses1");
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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(!incFond->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnectionFond_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "s1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        StatisticsInfo<AstsGenericItemInfo> *item = incFond->StatisticFond()->GetItem("s1", "ses1");
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMillisecondsSlow() < incFond->WaitLostIncrementalMessageMaxTimeMcs());
        if(!incFond->ListenIncremental_Core())
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
        while(snapFond->m_waitTimer->ElapsedMillisecondsSlow() <= snapFond->WaitSnapshotMaxTimeMcs()) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->ListenSnapshot_Core())
                throw; // nothing should be happens
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }

        if(!snapFond->ListenSnapshot_Core()) // reconnect
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
        while(snapFond->m_waitTimer->ElapsedMillisecondsSlow() < snapFond->WaitSnapshotMaxTimeMcs() / 2) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->ListenSnapshot_Core())
                throw; // nothing should be happens
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(snapFond->m_waitTimer->ElapsedMillisecondsSlow() >= snapFond->WaitSnapshotMaxTimeMcs() / 2)
            throw;

        if(!snapFond->ListenSnapshot_Core())
            throw; // nothing should be happens
    }

    void TestConnectionFond_RouteFirstReceived_Empty() {

        this->Clear();
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
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
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 1, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 3, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 4, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 2);

        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 5, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 6, "s1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 2);

        if(!snapFond->ListenSnapshot_Core())
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
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 1, "s1", "ses1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 1, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 3, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

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
        while(!snapFond->m_waitTimer->IsTimeOutFast(1, snapFond->WaitSnapshotMaxTimeMcs())) {
            snapFond->ListenSnapshot_Core();
            if(!snapFond->m_waitTimer->Active(1))
                break;
        }

        snapFond->ListenSnapshot_Core();
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 1, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 3, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
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
        while(!snapFond->m_waitTimer->IsTimeOutFast(1, snapFond->WaitSnapshotMaxTimeMcs() / 2)) {
            snapFond->m_waitTimer->Start(); // reset timer 0 to avoid simulate situation when no packet received
            if(!snapFond->ListenSnapshot_Core())
                throw;
        }

        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;

        snapFond->ListenSnapshot_Core();
        //snapshot received and should be applied
        StatisticsInfo<AstsGenericItemInfo> *tableItem = incFond->StatisticFond()->GetItem("s1", "ses1");

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(incFond->StatisticFond()->UsedItemCount() != 1)
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
        snapFond->WaitSnapshotMaxTimeMcs(100);
        incFond->StartListenSnapshot();

        if(!snapFond->m_waitTimer->Active())
            throw;

        snapFond->m_waitTimer->Stop();
        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 4, "s1", "ses1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 6),
        }, 2);

        if(snapFond->m_packets[3]->m_address != 0)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        snapFond->m_waitTimer->Reset();
        snapFond->ListenSnapshot_Core();

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

        snapFond->ListenSnapshot_Core();
        if(!snapFond->m_waitTimer->Active(1))
            throw;
        snapFond->m_waitTimer->Stop(); //TODO check!!!!
        while(snapFond->m_waitTimer->ElapsedMillisecondsSlow(1) <= snapFond->WaitSnapshotMaxTimeMcs())
            snapFond->ListenSnapshot_Core();

        snapFond->ListenSnapshot_Core();
        // reset
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }
     *
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     *
    void TestConnectionFond_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->StatisticFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "111111", 1),
                                             new TestTemplateItemInfo("s2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "111111", 4),
                                             new TestTemplateItemInfo("s2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        if(incFond->StatisticFond()->UsedItemCount() != 2)
            throw;

        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMillisecondsSlow() < incFond->WaitLostIncrementalMessageMaxTimeMcs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_Generic, 2, "s1", "ses1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("111111"),
                                     }, 2, 4)
        }, 1);
        if(!snapFond->ListenSnapshot_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        StatisticsInfo<AstsGenericItemInfo> *item1 = incFond->StatisticFond()->GetItem("s1", "ses1");
        StatisticsInfo<AstsGenericItemInfo> *item2 = incFond->StatisticFond()->GetItem("s2", "ses1");
        if(item1->HasEntries())
            throw;
        if(!item2->HasEntries())
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

        this->incFond->StatisticFond()->Add("s1", "ses1");
        this->incFond->StartListenSnapshot();
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incFond->m_packets[4]->m_address == 0 || incFond->m_packets[5]->m_address == 0 || incFond->m_packets[6]->m_address == 0)
            throw;
        if(!incFond->m_packets[4]->m_processed || !incFond->m_packets[5]->m_processed || !incFond->m_packets[6]->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapFond->m_packets[1]->m_address == 0 || snapFond->m_packets[2]->m_address == 0 || snapFond->m_packets[3]->m_address == 0)
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
        if(incFond->m_statTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_statTableFond->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->m_statTableFond->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 0)
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
        if(incFond->m_statTableFond->UsedItemCount() != 2)
            throw;
        if(!incFond->m_statTableFond->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->m_statTableFond->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
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

        if(incFond->m_statTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_statTableFond->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->m_statTableFond->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
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
        if(incFond->ShouldRestoreIncrementalMessages())
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
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(!incFond->m_waitTimer->Active())
            throw;
        if(incFond->m_waitTimer->IsTimeOutFast(incFond->m_waitLostIncrementalMessageMaxTimeMcs))
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

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
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->StatisticFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->StatisticFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

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
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->StatisticFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->StatisticFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3_1() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

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
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsConnect)
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->StatisticFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->StatisticFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }

    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

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
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->StatisticFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->StatisticFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,    hbeat,                              hbeat",
                     "                                                            obs symbol3 begin rpt 1, obs symbol3 rpt 1 entry symbol3 e1, obs symbol3 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->CanStopListeningSnapshot()) // because we did not receive all snapshots for all m_symbols
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_statTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_statTableFond->GetItem("s1", "ses1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_statTableFond->GetItem("s2", "ses1")->BuyQuotes()->Count() != 0)
            throw;
        if(incFond->m_statTableFond->GetItem("symbol3", "ses1")->BuyQuotes()->Count() != 1)
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

        incFond->StatisticFond()->Add("s1", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "lost obr entry s1 e1, lost hbeat, wait_snap",
                     "obs s1 begin rpt 1, obs s1 rpt 1 entry s1 e1, obs s1 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_statTableFond->UsedItemCount() != 1)
            throw;
        if(incFond->m_statTableFond->GetItem("s1", "ses1")->BuyQuotes()->Count() != 1)
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

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->StatisticFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                         hbeat,                                        hbeat",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, hbeat, obs s2 begin rpt 2 end entry s2 e1",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_statTableFond->GetItem("s1", "ses1")->RptSeq() != 2)
            throw;
        if(incFond->m_statTableFond->GetItem("symbol3", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->m_statTableFond->GetItem("s2", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_statTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_statTableFond->GetItem("s1", "ses1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_statTableFond->GetItem("s2", "ses1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_statTableFond->GetItem("symbol3", "ses1")->BuyQuotes()->Count() != 1)
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

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->StatisticFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                         obr entry s2 e1,                         obr entry s2 e2",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, obs s2 begin rpt 2 end entry s2 e1 skip_if_suspend",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_statTableFond->GetItem("s1", "ses1")->RptSeq() != 2)
            throw;
        if(incFond->m_statTableFond->GetItem("symbol3", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->m_statTableFond->GetItem("s2", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_statTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_statTableFond->GetItem("s1", "ses1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_statTableFond->GetItem("s2", "ses1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_statTableFond->GetItem("symbol3", "ses1")->BuyQuotes()->Count() != 1)
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

        incFond->StatisticFond()->Add("s1", "ses1");

        if(!incFond->m_waitTimer->Active())
            throw;
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->RptSeq() != 3)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->BuyQuotes()->Count() != 3)
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

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 4 entry s1 e4 end",
                     30);
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->StatisticFond()->GetItem("s1", "ses1")->HasEntries())
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->RptSeq() != 4)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 5 entry s1 e5 end",
                     30);
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->HasEntries())
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->RptSeq() != 6)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 6 entry s1 e6 end",
                     30);
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->HasEntries())
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->RptSeq() != 6)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->StatisticFond()->GetItem("s1", "ses1")->HasEntries())
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incFond->StatisticFond()->GetItem("s2", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->StatisticFond()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4, hbeat ",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat          , obs s1 begin rpt 3 entry s1 e3 end",
                     30);
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->RptSeq() != 4)
            throw;
        if(incFond->StatisticFond()->GetItem("s1", "ses1")->HasEntries())
            throw;
        if(incFond->StatisticFond()->QueueEntriesCount() != 0)
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, obr entry s2 e2, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->StatisticFond()->GetItem("s2", "ses1")->ShouldProcessSnapshot())
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

        *
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



        if(incFond->StatisticFond()->SymbolsToRecvSnapshotCount() != 0)
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

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->EnterSnapshotMode();
        if(!incFond->StatisticFond()->GetItem("s1", "ses1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnectionFond_ClearSnapshotMessages_1() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapFond->m_packets[1]->m_address != 0)
            throw;
        if(snapFond->m_packets[1]->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnectionFond_ClearSnapshotMessages_2() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(snapFond->m_packets[1]->m_address != 0 ||
           snapFond->m_packets[2]->m_address != 0 ||
           snapFond->m_packets[3]->m_address != 0)
            throw;
        if(snapFond->m_packets[1]->m_processed != false ||
           snapFond->m_packets[2]->m_processed != false ||
           snapFond->m_packets[3]->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnectionFond_ClearSnapshotMessages_3() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_address != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnectionFond_ClearSnapshotMessages_4() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat, obs s1 rpt 2 entry s1 e2, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(incFond->StatisticFond()->UsedItemCount() != 1)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_address != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnectionFond_ClearSnapshotMessages() {
        printf("MSR FOND TestConnectionFond_ClearSnapshotMessages_1\n");
        TestConnectionFond_ClearSnapshotMessages_1();
        printf("MSR FOND TestConnectionFond_ClearSnapshotMessages_2\n");
        TestConnectionFond_ClearSnapshotMessages_2();
        printf("MSR FOND TestConnectionFond_ClearSnapshotMessages_3\n");
        TestConnectionFond_ClearSnapshotMessages_3();
        printf("MSR FOND TestConnectionFond_ClearSnapshotMessages_4\n");
        TestConnectionFond_ClearSnapshotMessages_4();
    }
    void TestConnectionFond_ParallelWorkingIncrementalAndSnapshot() {
        printf("MSR FOND TestConnectionFond_EnterSnapshotMode\n");
        TestConnectionFond_EnterSnapshotMode();
        printf("MSR FOND TestConnectionFond_ClearSnapshotMessages\n");
        TestConnectionFond_ClearSnapshotMessages();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_1();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_4();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnectionFond_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incFond->StatisticFond());
        this->Clear();
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->StatisticFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "111111", 1),
                                             new TestTemplateItemInfo("s2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_MSR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("s1", "111111", 4),
                                             new TestTemplateItemInfo("s2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->StatisticFond());

        incFond->StatisticFond()->Clear();
    }

    void TestConnectionFond() {
        this->m_helper->SetFondMode();
        printf("MSR FOND TestConnectionFond_AllSymbolsAreOk\n");
        TestConnectionFond_AllSymbolsAreOk();
        printf("MSR FOND TestConnectionFond_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnectionFond_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("MSR FOND TestConnectionFond_AllSymbolsAreOkButOneMessageLost\n");
        TestConnectionFond_AllSymbolsAreOkButOneMessageLost();
        printf("MSR FOND TestConnectionFond_SkipHearthBeatMessages_Incremental\n");
        TestConnectionFond_SkipHearthBeatMessages_Incremental();
        printf("MSR FOND TestConnectionFond_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnectionFond_ParallelWorkingIncrementalAndSnapshot();
        printf("MSR FOND TestConnectionFond_NotAllSymbolsAreOk\n");
        TestConnectionFond_NotAllSymbolsAreOk();
        printf("MSR FOND TestConnectionFond_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnectionFond_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("MSR FOND TestConnectionFond_StopTimersAfterReconnect\n");
        TestConnectionFond_StopTimersAfterReconnect();
        printf("MSR FOND TestConnectionFond_SnapshotSomeMessagesReceivedLater\n");
        TestConnectionFond_SnapshotSomeMessagesReceivedLater();
        printf("MSR FOND TestConnectionFond_SnapshotSomeMessagesNotReceived\n");
        TestConnectionFond_SnapshotSomeMessagesNotReceived();
        printf("MSR FOND TestConnectionFond_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnectionFond_LastFragmentReceivedBeforeRouteFirst();
        printf("MSR FOND TestConnectionFond_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnectionFond_RouteFirstReceived_AfterSomeDummyMessages();
        printf("MSR FOND TestConnectionFond_RouteFirstReceived_Empty\n");
        TestConnectionFond_RouteFirstReceived_Empty();
        printf("MSR FOND TestConnectionFond_TestSnapshotNoMessagesAtAll\n");
        TestConnectionFond_TestSnapshotNoMessagesAtAll();
        printf("MSR FOND TestConnectionFond_OneMessageReceived\n");
        TestConnectionFond_OneMessageReceived();
        printf("MSR FOND TestConnectionFond_Clear_AfterIncremental\n");
        TestConnectionFond_Clear_AfterIncremental();
        printf("MSR FOND TestConnectionFond_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnectionFond_TestIncMessageLost_AndWaitTimerElapsed();
        printf("MSR FOND TestConnectionFond_TestSnapshotCollect\n");
        TestConnectionFond_TestSnapshotCollect();
        printf("MSR FOND TestConnectionFond_TestSnapshotNotCollect\n");
        TestConnectionFond_TestSnapshotMessageLostAndTimeExpired();
        printf("MSR FOND TestConnectionFond_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnectionFond_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("MSR FOND TestConnectionFond_EmptyTest\n");
        TestConnectionFond_EmptyTest();
        printf("MSR FOND TestConnectionFond_TestCorrectIncMessages\n");
        TestConnectionFond_TestCorrectIncMessages();
        printf("MSR FOND TestConnectionFond_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnectionFond_TestIncMessagesLost_AndWhenAppeared();
        printf("MSR FOND TestConnectionFond_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnectionFond_TestInc2MessagesLost_AppearedThen2Messages();
        printf("MSR FOND TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("MSR FOND TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnectionFond_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestOrderBookTableItem() {
        printf("MSR FOND TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("MSR FOND TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("MSR FOND TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("MSR FOND TestTable_Default\n");
        TestTable_Default();
        printf("MSR FOND TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("MSR FOND TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("MSR FOND TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("MSR FOND TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("MSR FOND Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("MSR FOND TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("MSR FOND TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("MSR FOND TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("MSR FOND TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
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

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_2() {
        this->Clear();

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->StatisticFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_3() {
        this->Clear();

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2, obr entry del s1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 1)
            throw;
        this->incFond->StatisticFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_4() {
        AstsGenericItemInfo *info = this->m_helper->CreateGenericItemInfo(1, 1, 1, 1, MDEntryType::mdetBuyQuote, "111111");
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

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2, obr entry change s1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->StatisticFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_1() {
        this->Clear();

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                           "                                                  obs begin s1 entry s1 e2 rpt 2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2() {
        this->Clear();

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "obr entry s1 e1, lost obr entry s1 e2 entry s1 e3, wait_snap, hbeat",
                           "                                                   obs begin s1 entry s1 e2 rpt 2, obs s1 entry s1 e3 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        *this->Clear();

        this->incFond->StatisticFond()->Add("s1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        this->SendMessagesIdf(this->incFond, this->snapFond,
                           "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   obs begin s1 entry s1 e1 rpt 2, obs s1 entry s1 e2, obs s1 entry s1 e3, obs s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 3)
            throw;*
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_4() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->StatisticFond()->Add("s2", "ses1");
        incFond->StatisticFond()->Add("symbol3", "ses1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry symbol3 e1, wait_snap, obr entry s1 e3,                              hbeat,                              hbeat",
                     "                                                       obs symbol3 begin rpt 1 end entry symbol3 e1, obs s1 begin rpt 2 end entry s1 e1, hbeat, obs s2 begin rpt 2 end entry s2 e1",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_5() {
        this->Clear();
        incFond->StatisticFond()->Add("s1", "ses1");
        incFond->Start();

        int prevCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, lost obr entry s1 e2, obr entry s1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     obs s1 begin rpt 0 lastmsg 0 entry s1 e1 end",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_6() {
        this->Clear();

        incFond->StatisticFond()->Add("s1", "ses1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        SendMessages(incFond, snapFond,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        int newCount = this->snapFond->m_fastProtocolManager->m_genericItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond() {
        this->m_helper->SetFondMode();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_1();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_2();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_3();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_4();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_5();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_1();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_3();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_4();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_5();
        printf("MSR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_6();
    }
    */
    void Test() {
        /*TestDefaults();
        TestInfoAndItemInfoUsageAndAllocationFond();
        TestStringIdComparer();
        Test_MSR_FOND();
        TestOrderBookTableItem();
        TestConnectionFond();*/
    }
};

#endif //TEST
#endif //HFT_ROBOT_STATISTICSTESTER_H
