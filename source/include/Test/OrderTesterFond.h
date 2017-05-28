//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_ORDERTESTER_H
#define HFT_ROBOT_ORDERTESTER_H
#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class OrderTesterFond {
    TestMessagesHelper      *m_helper;
    FeedConnection_FOND_OLR *incFond;
    FeedConnection_FOND_OLS *snapFond;
    MarketDataTable<OrderInfo, AstsOLSFONDInfo, AstsOLSFONDItemInfo> *m_table;
public:
    OrderTesterFond() {
        this->m_helper = new TestMessagesHelper();
        this->m_helper->SetFondMode();
        this->m_table = new MarketDataTable<OrderInfo, AstsOLSFONDInfo, AstsOLSFONDItemInfo>();
        this->m_table->InitSymbols(10, 10);
        this->incFond = new FeedConnection_FOND_OLR("OLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snapFond = new FeedConnection_FOND_OLS("OLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);
        this->m_table->InitSymbols(10, 10);
        this->incFond->SetSymbolManager(new SymbolManager(10));
        this->snapFond->SetSymbolManager(this->incFond->GetSymbolManager());
        this->incFond->OrderFond()->InitSymbols(10, 10);
        this->incFond->SetMaxLostPacketCountForStartSnapshot(1);
    }
    ~OrderTesterFond() {
        delete this->incFond;
        delete this->snapFond;
        delete this->m_helper;
        delete this->m_table;
    }

    void TestItem(OrderInfo<AstsOLSFONDItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<OrderInfo, AstsOLSFONDInfo, AstsOLSFONDItemInfo> *table) {
        for(int i = 0; i < this->m_table->SymbolsCount(); i++) {
            for(int j = 0; j < this->m_table->Symbol(i)->Count(); j++) {
                OrderInfo<AstsOLSFONDItemInfo> *item = this->m_table->Item(i, j);
                TestItem(item);
            }
        }
    }

    void Clear() {
        incFond->SetSnapshot(this->snapFond);
        incFond->OrderFond()->Clear();
        incFond->GetSymbolManager()->Clear();
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
        this->m_table->Clear();
        incFond->Start();
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Add() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

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
        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        AstsOLSFONDItemInfo *quote = obi->BuyQuotes()->Item(0);
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
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
        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Item(0);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
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
        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
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
        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "444444", 6))
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Remove() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

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
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaDelete, mdetBuyQuote, "444444", 5);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;
        if(info->GroupMDEntries[0]->Allocator->Count() != 0)
            throw;

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 6, "333333", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaDelete, mdetBuyQuote, "333333", 6);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 6, "111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaDelete, mdetBuyQuote, "222222", 7);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 6, "111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaDelete, mdetBuyQuote, "111111", 8);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Change() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<AstsOLSFONDItemInfo> *obi2 = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 6, "444444", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 6, "333333", 6))
            throw;

        AstsOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "222222", 5);

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

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");

        AstsOLSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        AstsOLSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        AstsOLSFONDItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        AstsOLSFONDItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 6, "444444", 6))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 6, "333333", 6))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item4->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item4->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

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

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_FOND() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<AstsOLSFONDItemInfo> *obi2 = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        AstsOLSFONDInfo *info2 = this->m_helper->CreateOLSFondInfo("t1s2", "ses1");
        AstsOLSFONDItemInfo *newItem1 = this->m_helper->CreateOLSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "777777");
        AstsOLSFONDItemInfo *newItem2 = this->m_helper->CreateOLSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "888888");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->OrderFond()->ObtainSnapshotItem(info2);
        this->incFond->OrderFond()->ProcessSnapshot(info2);

        if(this->incFond->OrderFond()->UsedItemCount() != 2)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi3 = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("t1s2", "ses1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        AstsOLSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        AstsOLSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);

        if(!StringIdComparer::Equal(qt1->MDEntryID, 6, "888888", 6))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 6, "777777", 6))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        AstsOLSFONDItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "111111", 6))
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
        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "111111", 6))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "222222", 6))
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
        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "111111", 6))
            throw;

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "222222", 6))
            throw;

        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "333333", 6))
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
        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "111111", 6))
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "222222", 6))
            throw;

        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "333333", 6))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "444444", 6))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

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
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaDelete, mdetSellQuote, "444444", 5);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 6,"333333", 6))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 6,"111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 6,"222222", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaDelete, mdetSellQuote, "333333", 6);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 6,"111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 6,"222222", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaDelete, mdetSellQuote, "222222", 7);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 6,"111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaDelete, mdetSellQuote, "111111", 8);

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<AstsOLSFONDItemInfo> *obi2 = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 6, "333333", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 6, "444444", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 6, "222222", 6))
            throw;

        AstsOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 24, -3, 1, 3, mduaChange, mdetSellQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");

        AstsOLSFONDItemInfo *qt1 = obi->SellQuotes()->Item(0);
        AstsOLSFONDItemInfo *qt2 = obi->SellQuotes()->Item(1);
        AstsOLSFONDItemInfo *qt3 = obi->SellQuotes()->Item(2);
        AstsOLSFONDItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incFond->OrderFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 6, "333333", 6))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 6, "444444", 6))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 6, "111111", 6))
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
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        this->incFond->OrderFond()->Clear();
        if(this->incFond->OrderFond()->UsedItemCount() != 0)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_FOND_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRFONDInfo *info = this->m_helper->CreateAstsIncrementalOLRFONDInfo();
        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_OLR_FOND(info);

        AstsOLSFONDInfo *info2 = this->m_helper->CreateOLSFondInfo("t1s2", "ses1");
        AstsOLSFONDItemInfo *newItem1 = this->m_helper->CreateOLSFondItemInfo(7,-2, 1, 2, mdetSellQuote, "777777");
        AstsOLSFONDItemInfo *newItem2 = this->m_helper->CreateOLSFondItemInfo(8,-2, 1, 2, mdetSellQuote, "888888");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->OrderFond()->ObtainSnapshotItem(info2);
        this->incFond->OrderFond()->ProcessSnapshot(info2);

        if(this->incFond->OrderFond()->UsedItemCount() != 2)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi3 = this->incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderInfo<AstsOLSFONDItemInfo> *obi = this->incFond->OrderFond()->GetItem("t1s2", "ses1");
        if(obi->SellQuotes()->Count() != 2)
            throw;

        AstsOLSFONDItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        AstsOLSFONDItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 6, "777777", 6))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 6, "888888", 6))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND() {
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_Add\n");
        Test_OnIncrementalRefresh_OLR_FOND_Add();
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_Remove\n");
        Test_OnIncrementalRefresh_OLR_FOND_Remove();
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_Change\n");
        Test_OnIncrementalRefresh_OLR_FOND_Change();
        printf("OLR FOND Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OLR_FOND_SellQuotes() {
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes();
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes();
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes();
        printf("OLR FOND Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OLR_FOND() {
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND\n");
        Test_OnIncrementalRefresh_OLR_FOND();
        printf("OLR FOND Test_OnFullRefresh_OLS_FOND\n");
        Test_OnFullRefresh_OLS_FOND();
        printf("OLR FOND Test_OnIncrementalRefresh_OLR_FOND_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_FOND_SellQuotes();
        printf("OLR FOND Test_OnFullRefresh_OLS_FOND_SellQuotes\n");
        Test_OnFullRefresh_OLS_FOND_SellQuotes();
    }

    void TestDefaults() {
        if(this->incFond->OrderFond()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incFond->OrderFond());
    }

    void TestTableItem_CorrectBegin() {
        OrderInfo<AstsOLSFONDItemInfo> *tb = new OrderInfo<AstsOLSFONDItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderInfo<AstsOLSFONDItemInfo>>("symbol1"));

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        if(!tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue() != 0)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTableItem_IncorrectBegin() {
        OrderInfo<AstsOLSFONDItemInfo> *tb = new OrderInfo<AstsOLSFONDItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderInfo<AstsOLSFONDItemInfo>>("symbol1"));

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
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
        OrderInfo<AstsOLSFONDItemInfo> *tb = new OrderInfo<AstsOLSFONDItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderInfo<AstsOLSFONDItemInfo>>("symbol1"));

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");
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

        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "333333");
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

    void ClearSymbols() {
        this->m_table->Clear();
        this->incFond->OrderFond()->Clear();
        this->incFond->GetSymbolManager()->Clear();
    }

    void AddSymbol(const char *symbol, const char *session) {
        this->incFond->GetSymbolManager()->AddSymbol(symbol);
        this->incFond->OrderFond()->Add(symbol, session);
        this->m_table->Add(symbol, session);
    }

    void AddSymbol(const char *symbol) {
        AddSymbol(symbol, "ses1");
    }

    void TestTable_Default() {
        this->ClearSymbols();

        TestTableItemsAllocator(this->m_table);
    }

    void TestTable_AfterClear() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", "111111");
        item->RptSeq = 1;

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", "111111");
        item2->RptSeq = 2;

        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", "111111");
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item, 0, item->TradingSessionIDUint);
        this->m_table->ProcessIncremental(item2, 0, item->TradingSessionIDUint);
        this->m_table->ProcessIncremental(item3, 0, item->TradingSessionIDUint);

        if(this->m_table->UsedItemCount() != 1)
            throw;
        OrderInfo<AstsOLSFONDItemInfo> *tableItem = this->m_table->GetItem("symbol1", "ses1");
        if(tableItem->EntriesQueue()->MaxIndex() != 1) // 3 is empty and 4 has value
            throw;
        this->m_table->Clear();
        if(this->m_table->UsedItemCount() != 0)
            throw;
        if(tableItem->RptSeq() != 0)
            throw;
        if(tableItem->BuyQuotes()->Count() != 0)
            throw;
        if(tableItem->EntriesQueue() != 0)
            throw;

        
    }

    void TestTable_CorrectBegin() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;
    }

    void TestTable_IncorrectBegin() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 2;

        if(this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;
    }

    void TestTable_SkipMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;
    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");
        this->AddSymbol("SYMBOL2");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("SYMBOL2", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item2->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item2, 1, item2->TradingSessionIDUint))
            throw;

        if(this->m_table->UsedItemCount() != 2)
            throw;

        
    }

    void TestTable_CorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "222222", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsOLSFONDInfo *info = this->m_helper->CreateOLSFondInfo("symbol1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 3;

        OrderInfo<AstsOLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() == 3)
            throw;
        if(!this->m_table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 3)
            throw;
        if(tb->EntriesQueue() != 0)
            throw;
    }

    void TestTable_CorrectApplySnapshot_2() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsOLSFONDInfo *info1 = this->m_helper->CreateOLSFondInfo("symbol1", "ses1");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        AstsOLSFONDInfo *info2 = this->m_helper->CreateOLSFondInfo("symbol1", "ses1");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = this->m_helper->CreateOLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        OrderInfo<AstsOLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info1);
        this->m_table->StartProcessSnapshot();
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
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item3 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "333333", 5);
        item3->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "555555", 6);
        item5->RptSeq = 2;

        AstsOLSFONDInfo *info = this->m_helper->CreateOLSFondInfo("symbol1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 2;

        OrderInfo<AstsOLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 2);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() == 2)
            throw;
        if(this->m_table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 2)
            throw;
    }

    void TestTable_IncorrectApplySnapshot_WhenMessageSkipped() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSFONDItemInfo *item1 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsOLSFONDItemInfo *item2 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item4 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsOLSFONDItemInfo *item5 = this->m_helper->CreateOLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsOLSFONDInfo *info = this->m_helper->CreateOLSFondInfo("symbol1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 3;

        OrderInfo<AstsOLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() == 3)
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

    void TestConnection_EmptyTest() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "444444", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnection_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<AstsOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("symbol1", "ses1");
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
        if(((AstsOLSFONDItemInfo*)item->EntriesQueue()->Entries()[1])->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "444444", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<AstsOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("symbol1", "ses1");
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
        if(((AstsOLSFONDItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "444444", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<AstsOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("symbol1", "ses1");
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
        if(((AstsOLSFONDItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<AstsOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("symbol1", "ses1");
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
        if(((AstsOLSFONDItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

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
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();
        this->AddSymbol("symbol1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        OrderInfo<AstsOLSFONDItemInfo> *item = incFond->OrderFond()->GetItem("symbol1", "ses1");
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMicrosecondsFast() < incFond->WaitLostIncrementalMessageMaxTimeMcs()) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        }
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

    void TestConnection_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        incFond->StartListenSnapshot();
        if(!snapFond->m_waitTimer->Active()) // start wait timer immediately
            throw;

        snapFond->ListenSnapshot(); // activate timer 2 when first time no messages recv
        //no messages
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast(2) <= snapFond->WaitAnyPacketMaxTimeMcs - 50000) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->ListenSnapshot())
                throw; // nothing should be happens
            if(!snapFond->m_waitTimer->Active(2))
                throw;
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast(2) <= snapFond->WaitAnyPacketMaxTimeMcs) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
            // just wait
        }
        if(!snapFond->m_waitTimer->Active(2))
            throw;

        if(!snapFond->ListenSnapshot()) // reconnect
            throw;
        if(snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(snapFond->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_waitTimer->Active(2))
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
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        //no messages first half time
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast() < snapFond->WaitSnapshotMaxTimeMcs() / 2) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->ListenSnapshot())
                throw; // nothing should be happens
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", false, false,
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
        if(snapFond->m_waitTimer->ElapsedMicrosecondsFast() >= snapFond->WaitAnyPacketMaxTimeMcs / 2)
            throw;

        if(!snapFond->ListenSnapshot())
            throw; // nothing should be happens
    }

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
    this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", true, false,
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

    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
    this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 1, "symbol1", "ses1", false, false,
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", false, false,
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 3, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 4, "symbol1", "ses1", false, false,
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 5, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 6, "symbol1", "ses1", true, false,
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

    void TestConnection_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 1, "symbol1", "ses1", false, true,
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

    void TestConnection_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 1, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 3, "symbol1", "ses1", false, false,
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

    void TestConnection_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 1, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 3, "symbol1", "ses1", false, false,
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

        snapFond->WaitSnapshotMaxTimeMcs(50000);
        // wait some time and then receive lost packet
        while(!snapFond->m_waitTimer->IsTimeOutFast(1, snapFond->WaitSnapshotMaxTimeMcs() / 2)) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
            snapFond->m_waitTimer->StartFast(); // reset timer 0 to avoid simulate situation when no packet received
            if(!snapFond->ListenSnapshot_Core())
                throw;
        }

        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", false, false,
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

    void TestConnection_StopTimersAfterReconnect() {
        this->Clear();
        incFond->StartListenSnapshot();

        // manually activate timer 1
        snapFond->m_waitTimer->Activate(1);
        snapFond->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
        snapFond->DoWorkAtomSnapshot();

        if(!snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_TestSnapshotCollect() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", true, true,
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
        OrderInfo<AstsOLSFONDItemInfo> *tableItem = incFond->OrderFond()->GetItem("symbol1", "ses1");

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
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        snapFond->WaitSnapshotMaxTimeMcs(100);
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 4, "symbol1", "ses1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 6),
        }, 2);

        if(snapFond->Packet(3)->m_address != 0)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;

        snapFond->ListenSnapshot_Core();
        if(snapFond->m_waitTimer->Active(1))
            throw;

        snapFond->ListenSnapshot_Core();

        if(!snapFond->m_waitTimer->Active(1))
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
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast(1) <= snapFond->WaitSnapshotMaxTimeMcs())
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
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->OrderFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 1),
                                             new TestTemplateItemInfo("symbol2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 4),
                                             new TestTemplateItemInfo("symbol2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        if(incFond->OrderFond()->UsedItemCount() != 2)
            throw;

        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMicrosecondsFast() < incFond->WaitLostIncrementalMessageMaxTimeMcs()) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        }

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_FOND, 2, "symbol1", "ses1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("111111"),
                                     }, 2, 4)
        }, 1);
        if(!snapFond->ListenSnapshot_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderInfo<AstsOLSFONDItemInfo> *item1 = incFond->OrderFond()->GetItem("symbol1", "ses1");
        OrderInfo<AstsOLSFONDItemInfo> *item2 = incFond->OrderFond()->GetItem("symbol2", "ses1");
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

    void TestConnection_SkipHearthBeatMessages_Incremental() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->incFond->StartListenSnapshot();
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incFond->Packet(4)->m_address == 0 || incFond->Packet(5)->m_address == 0 || incFond->Packet(6)->m_address == 0)
            throw;
        if(!incFond->Packet(4)->m_processed || !incFond->Packet(5)->m_processed || !incFond->Packet(6)->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapFond->Packet(1)->m_item == 0 || snapFond->Packet(2)->m_item == 0 || snapFond->Packet(3)->m_item == 0)
        //    throw;
        //if(!snapFond->Packet(1)->m_processed || !snapFond->Packet(2)->m_processed || !snapFond->Packet(3)->m_processed)
        //    throw;
    }

    void TestConnection_AllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol1 222222, olr entry symbol1 333333, olr entry symbol2 111111, olr entry symbol2 222222",
                     "",
                     30);
        if(incFond->m_orderTableFond->UsedItemCount() != 2)
            throw;
        if(incFond->m_orderTableFond->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->m_orderTableFond->Symbol(1)->Session(0)->HasEntries())
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
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, olr entry symbol1 333333, olr entry symbol2 111111, olr entry symbol2 222222",
                     "",
                     30);
        if(incFond->m_orderTableFond->UsedItemCount() != 2)
            throw;
        if(!incFond->m_orderTableFond->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->m_orderTableFond->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        this->AddSymbol("symbol3");

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 222222, olr entry symbol1 333333, olr entry symbol2 111111, olr entry symbol2 222222",
                     "",
                     30);

        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->m_orderTableFond->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol3");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111",
                     "",
                     30);
        if(incFond->HasPotentiallyLostPackets())
            throw;
        if(incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol3");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, hbeat",
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

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, hbeat, hbeat",
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

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, hbeat, hbeat, hbeat",
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
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->OrderFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    // i have commented this test because reconnect logic moved to ListenSnapshot method
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1() {
//        this->Clear();
//
//        incFond->OrderFond()->Add("s1", "ses1");
//        incFond->OrderFond()->Add("symbol3", "ses1");
//
//        if(snapFond->State() != FeedConnectionState::fcsSuspend)
//            throw;
//        SendMessages(incFond, snapFond,
//                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
//                     "",
//                     30);
//        if(incFond->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(!incFond->HasPotentiallyLostPackets())
//            throw;
//        if(!incFond->ShouldRestoreIncrementalMessages())
//            throw;
//        if(incFond->m_waitTimer->Active())
//            throw;
//        if(snapFond->State() != FeedConnectionState::fcsConnect)
//            throw;
//        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(incFond->OrderFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
//            throw;
//        if(incFond->OrderFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
//            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap",
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

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,    hbeat,                              hbeat",
                     "                                                            ols symbol3 begin rpt 1, ols symbol3 rpt 1 entry symbol3 111111, ols symbol3 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->CanStopListeningSnapshot()) // because we did not receive all snapshots for all m_symbols
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "ses1")->BuyQuotes()->Count() != 0)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "ses1")->BuyQuotes()->Count() != 1)
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

        this->AddSymbol("symbol1", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "lost olr entry symbol1 111111, lost hbeat, wait_snap",
                     "ols symbol1 begin rpt 1, ols symbol1 rpt 1 entry symbol1 111111, ols symbol1 rpt 1 end",
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
        if(incFond->m_orderTableFond->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 1)
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

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,                         hbeat,                                        hbeat",
                     "                                                            ols symbol3 begin rpt 1 end entry symbol3 111111, ols symbol1 begin rpt 2 end entry symbol1 111111, hbeat, ols symbol2 begin rpt 2 end entry symbol2 111111",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol1", "ses1")->RptSeq() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "ses1")->BuyQuotes()->Count() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "ses1")->BuyQuotes()->Count() != 1)
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

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,                         olr entry symbol2 111111,                         olr entry symbol2 222222",
                     "                                                            ols symbol3 begin rpt 1 end entry symbol3 111111, ols symbol1 begin rpt 2 end entry symbol1 111111, ols symbol2 begin rpt 2 end entry symbol2 111111 skip_if_suspend",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol1", "ses1")->RptSeq() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->m_orderTableFond->UsedItemCount() != 3)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol2", "ses1")->BuyQuotes()->Count() != 2)
            throw;
        if(incFond->m_orderTableFond->GetItem("symbol3", "ses1")->BuyQuotes()->Count() != 1)
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

        this->AddSymbol("symbol1", "ses1");

        if(!incFond->m_waitTimer->Active())
            throw;
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol1 222222, olr entry symbol1 333333, lost hbeat, wait_snap, hbeat",
                     "                                                                          ols symbol1 begin rpt 1 entry symbol1 111111 end",
                     50);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->RptSeq() != 3)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 3)
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

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol1 222222, lost olr entry symbol1 333333, olr entry symbol1 444444, lost olr entry symbol1 555555, olr entry symbol1 666666, wait_snap, ",
                     "                                                                                                                           ols symbol1 begin rpt 4 entry symbol1 444444 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->OrderFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->RptSeq() != 4)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol1 222222, lost olr entry symbol1 333333, olr entry symbol1 444444, lost olr entry symbol1 555555, olr entry symbol1 666666, wait_snap, ",
                     "                                                                                                                           ols symbol1 begin rpt 5 entry symbol1 555555 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->RptSeq() != 6)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol1 222222, lost olr entry symbol1 333333, olr entry symbol1 444444, lost olr entry symbol1 555555, olr entry symbol1 666666, wait_snap, ",
                     "                                                                                                                           ols symbol1 begin rpt 6 entry symbol1 666666 end",
                     30);
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->RptSeq() != 6)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol2 111111, lost olr entry symbol1 222222, wait_snap, hbeat                               lost olr entry symbol1 333333,               olr entry symbol1 444444",
                     "                                                                   ols symbol1 begin rpt 2 entry symbol1 222222 end, ols symbol2 begin rpt 1 entry symbol2 111111 end, hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->OrderFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incFond->OrderFond()->GetItem("symbol2", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->OrderFond()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        if(incFond->OrderFond()->Symbol(0)->Session(0)->ShouldProcessSnapshot())
            throw;
        if(incFond->OrderFond()->Symbol(1)->Session(0)->ShouldProcessSnapshot())
            throw;
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol2 111111, lost olr entry symbol1 222222, wait_snap, hbeat                               lost olr entry symbol1 333333,               olr entry symbol1 444444, hbeat ",
                     "                                                                   ols symbol1 begin rpt 2 entry symbol1 222222 end, ols symbol2 begin rpt 1 entry symbol2 111111 end, hbeat          , ols symbol1 begin rpt 3 entry symbol1 333333 end",
                     30);
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->RptSeq() != 4)
            throw;
        if(incFond->OrderFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->OrderFond()->QueueEntriesCount() != 0)
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol2 111111, lost olr entry symbol1 222222, wait_snap, olr entry symbol2 222222, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->OrderFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->OrderFond()->GetItem("symbol2", "ses1")->ShouldProcessSnapshot())
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

        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, olr entry symbol1 222222, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     ols symbol1 begin rpt 0 lastmsg 0 entry symbol1 111111 end",
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

        this->AddSymbol("symbol1", "ses1");
        incFond->OrderFond()->EnterSnapshotMode();
        if(!incFond->OrderFond()->GetItem("symbol1", "ses1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnection_ClearSnapshotMessages_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                     "                                                  ols symbol1 begin rpt 2 entry symbol1 222222 end",
                     30);
        if(snapFond->Packet(1)->m_address != 0)
            throw;
        if(snapFond->Packet(1)->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnection_ClearSnapshotMessages_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, ols symbol1 begin rpt 2 entry symbol1 222222 end",
                     30);
        if(snapFond->Packet(1)->m_address != 0 ||
           snapFond->Packet(2)->m_address != 0 ||
           snapFond->Packet(3)->m_address != 0)
            throw;
        if(snapFond->Packet(1)->m_processed != false ||
           snapFond->Packet(2)->m_processed != false ||
           snapFond->Packet(3)->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnection_ClearSnapshotMessages_3() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                     "                                                  ols symbol1 begin rpt 2 entry symbol1 222222, lost ols symbol1 rpt 2 entry symbol1 222222, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_address != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnection_ClearSnapshotMessages_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  ols symbol1 begin rpt 2 entry symbol1 222222, lost ols symbol1 rpt 2 entry symbol1 222222, hbeat, hbeat, hbeat, hbeat, hbeat, ols symbol1 rpt 2 entry symbol1 222222, ols symbol1 begin rpt 2 entry symbol1 222222 end",
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
            if(snapFond->m_packets[i]->m_address != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnection_ClearSnapshotMessages() {
        printf("OLR FOND TestConnection_ClearSnapshotMessages_1\n");
        TestConnection_ClearSnapshotMessages_1();
        printf("OLR FOND TestConnection_ClearSnapshotMessages_2\n");
        TestConnection_ClearSnapshotMessages_2();
        printf("OLR FOND TestConnection_ClearSnapshotMessages_3\n");
        TestConnection_ClearSnapshotMessages_3();
        printf("OLR FOND TestConnection_ClearSnapshotMessages_4\n");
        TestConnection_ClearSnapshotMessages_4();
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot() {
        printf("OLR FOND TestConnection_EnterSnapshotMode\n");
        TestConnection_EnterSnapshotMode();
        printf("OLR FOND TestConnection_ClearSnapshotMessages\n");
        TestConnection_ClearSnapshotMessages();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_1();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_4();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnection_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incFond->OrderFond());
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->OrderFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 1),
                                             new TestTemplateItemInfo("symbol2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 4),
                                             new TestTemplateItemInfo("symbol2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->OrderFond());

        incFond->OrderFond()->Clear();
    }

    void TestConnection() {
        printf("OLR FOND TestConnection_AllSymbolsAreOk\n");
        TestConnection_AllSymbolsAreOk();
        printf("OLR FOND TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("OLR FOND TestConnection_AllSymbolsAreOkButOneMessageLost\n");
        TestConnection_AllSymbolsAreOkButOneMessageLost();
        printf("OLR FOND TestConnection_SkipHearthBeatMessages_Incremental\n");
        TestConnection_SkipHearthBeatMessages_Incremental();
        printf("OLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot();
        printf("OLR FOND TestConnection_NotAllSymbolsAreOk\n");
        TestConnection_NotAllSymbolsAreOk();
        printf("OLR FOND TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("OLR FOND TestConnection_StopTimersAfterReconnect\n");
        TestConnection_StopTimersAfterReconnect();
        printf("OLR FOND TestConnection_SnapshotSomeMessagesReceivedLater\n");
        TestConnection_SnapshotSomeMessagesReceivedLater();
        printf("OLR FOND TestConnection_SnapshotSomeMessagesNotReceived\n");
        TestConnection_SnapshotSomeMessagesNotReceived();
        printf("OLR FOND TestConnection_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnection_LastFragmentReceivedBeforeRouteFirst();
        printf("OLR FOND TestConnection_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnection_RouteFirstReceived_AfterSomeDummyMessages();
        printf("OLR FOND TestConnection_RouteFirstReceived_Empty\n");
        TestConnection_RouteFirstReceived_Empty();
        printf("OLR FOND TestConnection_TestSnapshotNoMessagesAtAll\n");
        TestConnection_TestSnapshotNoMessagesAtAll();
        printf("OLR FOND TestConnection_OneMessageReceived\n");
        TestConnection_OneMessageReceived();
        printf("OLR FOND TestConnection_Clear_AfterIncremental\n");
        TestConnection_Clear_AfterIncremental();
        printf("OLR FOND TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("OLR FOND TestConnection_TestSnapshotCollect\n");
        TestConnection_TestSnapshotCollect();
        printf("OLR FOND TestConnection_TestSnapshotNotCollect\n");
        TestConnection_TestSnapshotMessageLostAndTimeExpired();
        printf("OLR FOND TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("OLR FOND TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("OLR FOND TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("OLR FOND TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("OLR FOND TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("OLR FOND TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("OLR FOND TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestOrderTableItem() {
        printf("OLR FOND TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("OLR FOND TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("OLR FOND TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("OLR FOND TestTable_Default\n");
        TestTable_Default();
        printf("OLR FOND TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("OLR FOND TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("OLR FOND TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("OLR FOND TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("OLR FOND Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("OLR FOND TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("OLR FOND TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("OLR FOND TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("OLR FOND TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
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

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "olr entry symbol1 111111",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "olr entry symbol1 111111, olr entry symbol1 222222",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->OrderFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_3() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "olr entry symbol1 111111, olr entry symbol1 222222, olr entry del symbol1 111111",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
        this->incFond->OrderFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_4() {
        AstsOLSFONDItemInfo *info = this->m_helper->CreateOLSFondItemInfo(1, 1, 1, 1, MDEntryType::mdetBuyQuote, "111111");
        if(info->Allocator->Count() != 1)
            throw;
        info->Used = false;
        info->ReleaseUnused();
        if(info->Allocator->Count() != 0)
            throw;
        // such situation should not be happened
        //info->ReleaseUnused();
        //if(info->Allocator->Count() != 0)
        //    throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_5() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "olr entry symbol1 111111, olr entry symbol1 222222, olr entry change symbol1 111111",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->OrderFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                           "                                                  ols begin symbol1 entry symbol1 222222 rpt 2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "olr entry symbol1 111111, lost olr entry symbol1 222222 entry symbol1 333333, wait_snap, hbeat",
                           "                                                   ols begin symbol1 entry symbol1 222222 rpt 2, ols symbol1 entry symbol1 333333 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        /*this->Clear();

        this->incFond->OrderFond()->Add("s1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        this->SendMessagesIdf(this->incFond, this->snapFond,
                           "olr entry s1 e1, olr entry s1 e2, lost olr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   ols begin s1 entry s1 e1 rpt 2, ols s1 entry s1 e2, ols s1 entry s1 e3, ols s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 3)
            throw;*/
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,                              hbeat,                              hbeat",
                     "                                                       ols symbol3 begin rpt 1 end entry symbol3 111111, ols symbol1 begin rpt 2 end entry symbol1 111111, hbeat, ols symbol2 begin rpt 2 end entry symbol2 111111",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 4)
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_5() {
        this->Clear();
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        int prevCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, olr entry symbol1 222222, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     ols symbol1 begin rpt 0 lastmsg 0 entry symbol1 111111 end",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_6() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "olr entry symbol1 111111, olr entry symbol1 222222, olr entry symbol1 333333, lost hbeat, wait_snap, hbeat",
                     "                                                                          ols symbol1 begin rpt 1 entry symbol1 111111 end",
                     50);
        int newCount = this->snapFond->m_fastProtocolManager->m_astsOLSFONDItems->Count();
        if(newCount != prevCount + 3)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond() {
        this->m_helper->SetFondMode();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_1();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_2();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_3();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_4();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_5();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_1();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_3();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_4();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_5();
        printf("OLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_6();
    }

    void Test() {
        TestDefaults();
        TestStringIdComparer();

        TestInfoAndItemInfoUsageAndAllocationFond();
        Test_OLR_FOND();

        TestOrderTableItem();
        TestConnection();
    }
};

#endif //TEST
#endif //HFT_ROBOT_ORDERTESTER_H
