//
// Created by root on 19.12.16.
//

#ifndef HFT_ROBOT_ORDERTABLECURR_H
#define HFT_ROBOT_ORDERTABLECURR_H
#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class OrderTesterCurr {
    TestMessagesHelper      *m_helper;
    FeedConnection_CURR_OLR *incCurr;
    FeedConnection_CURR_OLS *snapCurr;
    MarketDataTable<OrderInfo, AstsOLSCURRInfo, AstsOLSCURRItemInfo> *m_table;
public:
    OrderTesterCurr() {
        this->m_helper = new TestMessagesHelper();
        this->m_helper->SetCurrMode();
        this->m_table = new MarketDataTable<OrderInfo, AstsOLSCURRInfo, AstsOLSCURRItemInfo>();
        this->incCurr = new FeedConnection_CURR_OLR("OLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);

        this->snapCurr = new FeedConnection_CURR_OLS("OLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);
        this->m_table->InitSymbols(10, 10);
        this->incCurr->SetSymbolManager(new SymbolManager(10));
        this->snapCurr->SetSymbolManager(this->incCurr->GetSymbolManager());
        this->incCurr->OrderCurr()->InitSymbols(10, 10);
        this->incCurr->SetMaxLostPacketCountForStartSnapshot(1);
    }
    ~OrderTesterCurr() {
        delete this->incCurr;
        delete this->snapCurr;
        delete this->m_helper;
        delete this->m_table;
    }

    void TestItem(OrderInfo<AstsOLSCURRItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<OrderInfo, AstsOLSCURRInfo, AstsOLSCURRItemInfo> *table) {
        for(int i = 0; i < this->m_table->SymbolsCount(); i++) {
            for(int j = 0; j < this->m_table->Symbol(i)->Count(); j++) {
                OrderInfo<AstsOLSCURRItemInfo> *item = this->m_table->Item(i, j);
                TestItem(item);
            }
        }
    }

    void Clear() {
        incCurr->SetSnapshot(this->snapCurr);
        incCurr->OrderCurr()->Clear();
        incCurr->GetSymbolManager()->Clear();
        incCurr->ClearMessages();
        incCurr->WaitLostIncrementalMessageMaxTimeMs(50);
        incCurr->m_waitTimer->Stop();
        incCurr->m_waitTimer->Stop(1);
        snapCurr->ClearMessages();
        snapCurr->WaitSnapshotMaxTimeMs(50);
        incCurr->StartListenSnapshot();
        snapCurr->m_waitTimer->Stop();
        snapCurr->Stop();
        incCurr->Stop();

        this->m_helper->Clear();
        this->m_table->Clear();
        incCurr->Start();
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Add() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(!item1->Used)
            throw;
        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        AstsOLSCURRItemInfo *quote = obi->BuyQuotes()->Item(0);
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

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Item(0);
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

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "444444", 6))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

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
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 6, "333333", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 6, "222222", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 6, "111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 6, "333333", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 6, "444444", 6))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");

        AstsOLSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        AstsOLSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        AstsOLSCURRItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        AstsOLSCURRItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 6, "333333", 6))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 6, "444444", 6))
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
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        this->incCurr->OrderCurr()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incCurr->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        AstsOLSCURRInfo *info2 = this->m_helper->CreateOLSCurrInfo("t1s2", "session1");
        AstsOLSCURRItemInfo *newItem1 = this->m_helper->CreateOLSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "777777");
        AstsOLSCURRItemInfo *newItem2 = this->m_helper->CreateOLSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "888888");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderCurr()->ObtainSnapshotItem(info2);
        this->incCurr->OrderCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 2)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi3 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("t1s2", "session1");
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        AstsOLSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        AstsOLSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);

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

    void Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        AstsOLSCURRItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "111111", 6))
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
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

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "333333", 6))
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "333333", 6))
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 6, "444444", 6))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

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

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 6,"111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 6,"222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 6,"333333", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 6,"111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 6,"222222", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 6,"111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 6, "333333", 6))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 6, "444444", 6))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 24, -3, 1, 3, mduaChange, mdetSellQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");

        AstsOLSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        AstsOLSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);
        AstsOLSCURRItemInfo *qt3 = obi->SellQuotes()->Item(2);
        AstsOLSCURRItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 6, "111111", 6))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 6, "222222", 6))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 6, "333333", 6))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 6, "444444", 6))
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
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        this->incCurr->OrderCurr()->Clear();
        if(this->incCurr->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        AstsOLSCURRInfo *info2 = this->m_helper->CreateOLSCurrInfo("t1s2", "session1");
        AstsOLSCURRItemInfo *newItem1 = this->m_helper->CreateOLSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "777777");
        AstsOLSCURRItemInfo *newItem2 = this->m_helper->CreateOLSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "888888");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderCurr()->ObtainSnapshotItem(info2);
        this->incCurr->OrderCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 2)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi3 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("t1s2", "session1");
        if(obi->SellQuotes()->Count() != 2)
            throw;

        AstsOLSCURRItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        AstsOLSCURRItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

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

    void Test_OnIncrementalRefresh_OLR_CURR() {
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Add\n");
        Test_OnIncrementalRefresh_OLR_CURR_Add();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Remove\n");
        Test_OnIncrementalRefresh_OLR_CURR_Remove();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Change\n");
        Test_OnIncrementalRefresh_OLR_CURR_Change();
        printf("OLR CURR Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OLR_CURR_SellQuotes() {
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes();
        printf("OLR CURR Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OLR_CURR() {
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR\n");
        Test_OnIncrementalRefresh_OLR_CURR();
        printf("OLR CURR Test_OnFullRefresh_OLS_CURR\n");
        Test_OnFullRefresh_OLS_CURR();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_SellQuotes();
        printf("OLR CURR Test_OnFullRefresh_OLS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OLS_CURR_SellQuotes();
    }

    void TestDefaults() {
        if(this->incCurr->OrderCurr()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incCurr->OrderCurr());
    }

    void TestTableItem_CorrectBegin() {
        OrderInfo<AstsOLSCURRItemInfo> *tb = new OrderInfo<AstsOLSCURRItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderInfo<AstsOLSCURRItemInfo>>("symbol1"));

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
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
        OrderInfo<AstsOLSCURRItemInfo> *tb = new OrderInfo<AstsOLSCURRItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderInfo<AstsOLSCURRItemInfo>>("symbol1"));

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
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
        OrderInfo<AstsOLSCURRItemInfo> *tb = new OrderInfo<AstsOLSCURRItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderInfo<AstsOLSCURRItemInfo>>("symbol1"));

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");
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

        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "333333");
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
        this->ClearSymbols();

        TestTableItemsAllocator(this->m_table);
    }

    void AddSymbol(const char *symbol, const char *session) {
        this->incCurr->GetSymbolManager()->AddSymbol(symbol);
        this->incCurr->OrderFond()->Add(symbol, session);
        this->m_table->Add(symbol, session);
    }

    void AddSymbol(const char *symbol) {
        AddSymbol(symbol, "session1");
    }

    void ClearSymbols() {
        this->m_table->Clear();
        this->incCurr->OrderCurr()->Clear();
        this->incCurr->GetSymbolManager()->Clear();
    }

    void TestTable_AfterClear() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSCURRItemInfo *item = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", "111111");
        item->RptSeq = 1;

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", "111111");
        item2->RptSeq = 2;

        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", "111111");
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item, 0, item->TradingSessionID, item->TradingSessionIDLength);
        this->m_table->ProcessIncremental(item2, 0, item->TradingSessionID, item->TradingSessionIDLength);
        this->m_table->ProcessIncremental(item3, 0, item->TradingSessionID, item->TradingSessionIDLength);

        if(this->m_table->UsedItemCount() != 1)
            throw;
        OrderInfo<AstsOLSCURRItemInfo> *tableItem = this->m_table->GetItem("symbol1", "session1");
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

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength))
            throw;
    }

    void TestTable_IncorrectBegin() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 2;

        if(this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength))
            throw;
    }

    void TestTable_SkipMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionID, item2->TradingSessionIDLength))
            throw;

        
    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol2", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item2->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item2, 1, item2->TradingSessionID, item2->TradingSessionIDLength))
            throw;

        if(this->m_table->UsedItemCount() != 2)
            throw;

        
    }

    void TestTable_CorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength);

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "222222", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionID, item2->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionID, item3->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionID, item4->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsOLSCURRInfo *info = this->m_helper->CreateOLSCurrInfo("symbol1", "session1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 3;

        OrderInfo<AstsOLSCURRItemInfo> *tb = this->m_table->GetItem("symbol1", "session1");

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

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength);

        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionID, item3->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionID, item4->TradingSessionIDLength))
            throw;

        AstsOLSCURRInfo *info1 = this->m_helper->CreateOLSCurrInfo("symbol1", "session1");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        AstsOLSCURRInfo *info2 = this->m_helper->CreateOLSCurrInfo("symbol1", "session1");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = this->m_helper->CreateOLSCurrItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        OrderInfo<AstsOLSCURRItemInfo> *tb = this->m_table->GetItem("symbol1", "session1");

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

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength);

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionID, item2->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "333333", 5);
        item3->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionID, item3->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionID, item4->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "555555", 6);
        item5->RptSeq = 2;

        AstsOLSCURRInfo *info = this->m_helper->CreateOLSCurrInfo("symbol1", "session1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 2;

        OrderInfo<AstsOLSCURRItemInfo> *tb = this->m_table->GetItem("symbol1", "session1");

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

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionID, item1->TradingSessionIDLength);

        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionID, item2->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionID, item4->TradingSessionIDLength))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsOLSCURRInfo *info = this->m_helper->CreateOLSCurrInfo("symbol1", "session1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 3;

        OrderInfo<AstsOLSCURRItemInfo> *tb = this->m_table->GetItem("symbol1", "session1");

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

        SendMessages(incCurr, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incCurr, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "222222", 6, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "444444", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 4)
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

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "222222", 6, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        OrderInfo<AstsOLSCURRItemInfo> *item = incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(((AstsOLSCURRItemInfo*)item->EntriesQueue()->Entries()[1])->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "444444", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "222222", 6, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        OrderInfo<AstsOLSCURRItemInfo> *item = incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(((AstsOLSCURRItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "444444", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "222222", 6, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        OrderInfo<AstsOLSCURRItemInfo> *item = incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(((AstsOLSCURRItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(!incCurr->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
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

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "222222", 6, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        OrderInfo<AstsOLSCURRItemInfo> *item = incCurr->OrderCurr()->GetItem("symbol1", "session1");
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
        if(((AstsOLSCURRItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(!incCurr->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(incCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
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

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "222222", 6, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        OrderInfo<AstsOLSCURRItemInfo> *item = incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incCurr->m_waitTimer->ElapsedMilliseconds() < incCurr->WaitLostIncrementalMessageMaxTimeMs());
        if(!incCurr->ListenIncremental_Core())
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

    void TestConnection_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        incCurr->StartListenSnapshot();
        if(!snapCurr->m_waitTimer->Active()) // start wait timer immediately
            throw;

        snapCurr->ListenSnapshot(); // activate timer 2 when first time no messages recv
        //no messages
        while(snapCurr->m_waitTimer->ElapsedMilliseconds(2) <= snapCurr->WaitAnyPacketMaxTimeMs - 50) {
            if(!snapCurr->m_waitTimer->Active())
                throw;
            if(!snapCurr->ListenSnapshot())
                throw; // nothing should be happens
            if(!snapCurr->m_waitTimer->Active(2))
                throw;
            if(snapCurr->m_endMsgSeqNum != -1)
                throw;
            if(snapCurr->m_startMsgSeqNum != -1)
                throw;
        }
        while(snapCurr->m_waitTimer->ElapsedMilliseconds(2) <= snapCurr->WaitAnyPacketMaxTimeMs) {
            int a = 5;
            // just wait
        }
        if(!snapCurr->m_waitTimer->Active(2))
            throw;

        if(!snapCurr->ListenSnapshot()) // reconnect
            throw;
        if(snapCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(snapCurr->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapCurr->m_waitTimer->Active(2))
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

    void TestConnection_OneMessageReceived() {
        this->Clear();
        this->AddSymbol("symbol1");
        incCurr->StartListenSnapshot();

        //no messages first half time
        while(snapCurr->m_waitTimer->ElapsedMilliseconds() < snapCurr->WaitSnapshotMaxTimeMs() / 2) {
            if(!snapCurr->m_waitTimer->Active())
                throw;
            if(!snapCurr->ListenSnapshot())
                throw; // nothing should be happens
            if(snapCurr->m_endMsgSeqNum != -1)
                throw;
            if(snapCurr->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;
        if(!snapCurr->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(snapCurr->m_waitTimer->ElapsedMilliseconds() >= snapCurr->WaitAnyPacketMaxTimeMs / 2)
            throw;

        if(!snapCurr->ListenSnapshot())
            throw; // nothing should be happens
    }

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
        this->AddSymbol("symbol1");
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->ListenSnapshot_Core())
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
        if(!snapCurr->ListenSnapshot_Core())
            throw;
        if(!snapCurr->ListenSnapshot_Core())
            throw;
        if(!snapCurr->ListenSnapshot_Core())
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

    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        this->AddSymbol("symbol1");

        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 1, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 3, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 4, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 2);

        if(!snapCurr->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 5, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 6, "symbol1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 2);

        if(!snapCurr->ListenSnapshot_Core())
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
        if(!snapCurr->ListenSnapshot_Core())
            throw;
        if(!snapCurr->ListenSnapshot_Core())
            throw;
        if(!snapCurr->ListenSnapshot_Core())
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

    void TestConnection_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        this->AddSymbol("symbol1");

        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 1, "symbol1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->ListenSnapshot_Core())
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

    void TestConnection_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        this->AddSymbol("symbol1");
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 1, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapCurr->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 3, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapCurr->ListenSnapshot_Core();

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
            snapCurr->ListenSnapshot_Core();
            if(!snapCurr->m_waitTimer->Active(1))
                break;
        }

        snapCurr->ListenSnapshot_Core();
        if(snapCurr->m_startMsgSeqNum != 4)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        this->AddSymbol("symbol1");
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 1, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapCurr->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 3, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->ListenSnapshot_Core())
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
            if(!snapCurr->ListenSnapshot_Core())
                throw;
        }

        if(!snapCurr->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapCurr->ListenSnapshot_Core())
            throw;
        if(snapCurr->m_startMsgSeqNum != 4)
            throw;
        if(snapCurr->m_endMsgSeqNum != 3)
            throw;
        if(snapCurr->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;
    }

    void TestConnection_StopTimersAfterReconnect() {
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

    void TestConnection_TestSnapshotCollect() {
        this->Clear();
        this->AddSymbol("symbol1");
        incCurr->StartListenSnapshot();

        SendMessages(snapCurr, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 2)
            throw;

        snapCurr->ListenSnapshot_Core();
        //snapshot received and should be applied
        OrderInfo<AstsOLSCURRItemInfo> *tableItem = incCurr->OrderCurr()->GetItem("symbol1", "session1");

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->OrderCurr()->UsedItemCount() != 1)
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

    void TestConnection_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        this->AddSymbol("symbol1");
        incCurr->StartListenSnapshot();

        snapCurr->WaitSnapshotMaxTimeMs(100);
        if(!snapCurr->m_waitTimer->Active())
            throw;

        SendMessages(snapCurr, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 4, "symbol1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 6),
        }, 2);

        if(snapCurr->Packet(3)->m_address != 0)
            throw;
        if(snapCurr->m_startMsgSeqNum != 2)
            throw;
        if(snapCurr->m_endMsgSeqNum != 4)
            throw;
        if(snapCurr->m_waitTimer->Active(1))
            throw;

        snapCurr->ListenSnapshot_Core();
        if(snapCurr->m_waitTimer->Active(1))
            throw;

        snapCurr->ListenSnapshot_Core();

        if(!snapCurr->m_waitTimer->Active(1))
            throw;
        if(snapCurr->m_startMsgSeqNum != 3)
            throw;
        if(snapCurr->m_snapshotRouteFirst != 2)
            throw;
        if(snapCurr->m_snapshotLastFragment != -1)
            throw;

        snapCurr->ListenSnapshot_Core();
        if(!snapCurr->m_waitTimer->Active(1))
            throw;
        while(snapCurr->m_waitTimer->ElapsedMilliseconds(1) <= snapCurr->WaitSnapshotMaxTimeMs())
            snapCurr->ListenSnapshot_Core();

        snapCurr->ListenSnapshot_Core();
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
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        incCurr->StartListenSnapshot();

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        SendMessages(incCurr, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 1),
                                             new TestTemplateItemInfo("symbol2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 4),
                                             new TestTemplateItemInfo("symbol2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        if(incCurr->OrderCurr()->UsedItemCount() != 2)
            throw;

        if(!incCurr->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incCurr->m_waitTimer->ElapsedMilliseconds() < incCurr->WaitLostIncrementalMessageMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapCurr, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_OLS_CURR, 2, "symbol1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("111111"),
                                     }, 2, 4)
        }, 1);
        if(!snapCurr->ListenSnapshot_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderInfo<AstsOLSCURRItemInfo> *item1 = incCurr->OrderCurr()->GetItem("symbol1", "session1");
        OrderInfo<AstsOLSCURRItemInfo> *item2 = incCurr->OrderCurr()->GetItem("symbol2", "session1");
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

        this->AddSymbol("symbol1", "session1");
        this->incCurr->StartListenSnapshot();
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incCurr->Packet(4)->m_address == 0 || incCurr->Packet(5)->m_address == 0 || incCurr->Packet(6)->m_address == 0)
            throw;
        if(!incCurr->Packet(4)->m_processed || !incCurr->Packet(5)->m_processed || !incCurr->Packet(6)->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapCurr->Packet(1)->m_address == 0 || snapCurr->Packet(2)->m_address == 0 || snapCurr->Packet(3)->m_address == 0)
        //    throw;
        //if(!snapCurr->Packet(1)->m_processed || !snapCurr->Packet(2)->m_processed || !snapCurr->Packet(3)->m_processed)
        //    throw;
    }

    void TestConnection_AllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol1 222222, olr entry symbol1 333333, olr entry symbol2 111111, olr entry symbol2 222222",
                     "",
                     30);
        if(incCurr->m_orderTableCurr->UsedItemCount() != 2)
            throw;
        if(incCurr->m_orderTableCurr->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incCurr->m_orderTableCurr->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_NotAllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, olr entry symbol1 333333, olr entry symbol2 111111, olr entry symbol2 222222",
                     "",
                     30);
        if(incCurr->m_orderTableCurr->UsedItemCount() != 2)
            throw;
        if(!incCurr->m_orderTableCurr->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incCurr->m_orderTableCurr->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incCurr->ShouldRestoreIncrementalMessages())
            throw;
        if(incCurr->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        this->AddSymbol("symbol3");

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 222222, olr entry symbol1 333333, olr entry symbol2 111111, olr entry symbol2 222222",
                     "",
                     30);

        if(incCurr->m_orderTableCurr->UsedItemCount() != 2)
            throw;
        if(incCurr->m_orderTableCurr->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incCurr->m_orderTableCurr->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incCurr->ShouldRestoreIncrementalMessages())
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol3");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111",
                     "",
                     30);
        if(incCurr->HasPotentiallyLostPackets())
            throw;
        if(incCurr->ShouldRestoreIncrementalMessages())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol3");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, hbeat",
                     "",
                     30);
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldRestoreIncrementalMessages())
            throw;
        if(!incCurr->m_waitTimer->Active())
            throw;
        if(incCurr->m_waitTimer->IsElapsedMilliseconds(incCurr->m_waitLostIncrementalMessageMaxTimeMs))
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, hbeat, hbeat",
                     "",
                     30);
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldRestoreIncrementalMessages())
            throw;
        if(incCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderCurr()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incCurr->HasPotentiallyLostPackets())
            throw;
        if(!incCurr->ShouldRestoreIncrementalMessages())
            throw;
        if(incCurr->m_waitTimer->Active())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderCurr()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1() {
//        this->Clear();
//
//        incCurr->OrderCurr()->Add("s1", "session1");
//        incCurr->OrderCurr()->Add("symbol3", "session1");
//
//        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
//            throw;
//        SendMessages(incCurr, snapCurr,
//                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
//                     "",
//                     30);
//        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(!incCurr->HasPotentiallyLostPackets())
//            throw;
//        if(!incCurr->ShouldRestoreIncrementalMessages())
//            throw;
//        if(incCurr->m_waitTimer->Active())
//            throw;
//        if(snapCurr->State() != FeedConnectionState::fcsConnect)
//            throw;
//        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(incCurr->OrderCurr()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
//            throw;
//        if(incCurr->OrderCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
//            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap",
                     "",
                     30);
        if(incCurr->m_waitTimer->Active())
            throw;
        if(incCurr->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incCurr->ShouldRestoreIncrementalMessages())
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incCurr->OrderCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderCurr()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        this->AddSymbol("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,    hbeat,                              hbeat",
                     "                                                            ols symbol3 begin rpt 1, ols symbol3 rpt 1 entry symbol3 111111, ols symbol3 rpt 1 end",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->CanStopListeningSnapshot()) // because we did not receive all snapshots for all m_symbols
            throw;
        if(snapCurr->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderTableCurr->UsedItemCount() != 3)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 0)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incCurr, snapCurr,
                     "lost olr entry symbol1 111111, lost hbeat, wait_snap",
                     "ols symbol1 begin rpt 1, ols symbol1 rpt 1 entry symbol1 111111, ols symbol1 rpt 1 end",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incCurr->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderTableCurr->UsedItemCount() != 1)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 1)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        this->AddSymbol("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderCurr()->UsedItemCount() != 3)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,                         hbeat,                                        hbeat",
                     "                                                            ols symbol3 begin rpt 1 end entry symbol3 111111, ols symbol1 begin rpt 2 end entry symbol1 111111, hbeat, ols symbol2 begin rpt 2 end entry symbol2 111111",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol1", "session1")->RptSeq() != 2)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol2", "session1")->RptSeq() != 2)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderTableCurr->UsedItemCount() != 3)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
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
    // almost the same as TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        this->AddSymbol("symbol3", "session1");

        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderCurr()->UsedItemCount() != 3)
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,                         olr entry symbol2 111111,                         olr entry symbol2 222222",
                     "                                                            ols symbol3 begin rpt 1 end entry symbol3 111111, ols symbol1 begin rpt 2 end entry symbol1 111111, ols symbol2 begin rpt 2 end entry symbol2 111111 skip_if_suspend",
                     30);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol1", "session1")->RptSeq() != 2)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol2", "session1")->RptSeq() != 2)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->m_orderTableCurr->UsedItemCount() != 3)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(incCurr->m_orderTableCurr->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");

        if(!incCurr->m_waitTimer->Active())
            throw;
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol1 222222, olr entry symbol1 333333, lost hbeat, wait_snap, hbeat",
                     "                                                                          ols symbol1 begin rpt 1 entry symbol1 111111 end",
                     50);
        if(incCurr->HasQueueEntries())
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->RptSeq() != 3)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 3)
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
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        incCurr->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol1 222222, lost olr entry symbol1 333333, olr entry symbol1 444444, lost olr entry symbol1 555555, olr entry symbol1 666666, wait_snap, ",
                     "                                                                                                                           ols symbol1 begin rpt 4 entry symbol1 444444 end",
                     30);
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incCurr->OrderCurr()->GetItem("symbol1", "session1")->HasEntries())
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->RptSeq() != 4)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incCurr->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol1 222222, lost olr entry symbol1 333333, olr entry symbol1 444444, lost olr entry symbol1 555555, olr entry symbol1 666666, wait_snap, ",
                     "                                                                                                                           ols symbol1 begin rpt 5 entry symbol1 555555 end",
                     30);
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incCurr->HasQueueEntries())
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->HasEntries())
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->RptSeq() != 6)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incCurr->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol1 222222, lost olr entry symbol1 333333, olr entry symbol1 444444, lost olr entry symbol1 555555, olr entry symbol1 666666, wait_snap, ",
                     "                                                                                                                           ols symbol1 begin rpt 6 entry symbol1 666666 end",
                     30);
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incCurr->HasQueueEntries())
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->HasEntries())
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->RptSeq() != 6)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incCurr->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol2 111111, lost olr entry symbol1 222222, wait_snap, hbeat                               lost olr entry symbol1 333333,               olr entry symbol1 444444",
                     "                                                                   ols symbol1 begin rpt 2 entry symbol1 222222 end, ols symbol2 begin rpt 1 entry symbol2 111111 end, hbeat",
                     30);
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->RptSeq() != 2)
            throw;
        if(!incCurr->OrderCurr()->GetItem("symbol1", "session1")->HasEntries())
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol2", "session1")->RptSeq() != 1)
            throw;
        if(incCurr->OrderCurr()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        if(incCurr->OrderCurr()->Symbol(0)->Session(0)->ShouldProcessSnapshot())
            throw;
        if(incCurr->OrderCurr()->Symbol(1)->Session(0)->ShouldProcessSnapshot())
            throw;
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol2 111111, lost olr entry symbol1 222222, wait_snap, hbeat                                         lost olr entry symbol1 333333,               olr entry symbol1 444444, hbeat ",
                     "                                                                                  ols symbol1 begin rpt 2 entry symbol1 222222 end, ols symbol2 begin rpt 1 entry symbol2 111111 end, hbeat          , ols symbol1 begin rpt 3 entry symbol1 333333 end",
                     30);
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->RptSeq() != 4)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol1", "session1")->HasEntries())
            throw;
        if(incCurr->OrderCurr()->QueueEntriesCount() != 0)
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol2 111111, lost olr entry symbol1 222222, wait_snap, olr entry symbol2 222222, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incCurr->OrderCurr()->GetItem("symbol2", "session1")->ShouldProcessSnapshot())
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
        incCurr->m_fastProtocolManager->SetNewBuffer(msg, 52);
        incCurr->m_fastProtocolManager->ReadMsgSeqNumber();
        incCurr->m_fastProtocolManager->Decode();
        incCurr->m_fastProtocolManager->Print();
        */

        this->AddSymbol("symbol1", "session1");
        incCurr->Start();

        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, olr entry symbol1 222222, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     ols symbol1 begin rpt 0 lastmsg 0 entry symbol1 111111 end",
                     30);
        if(incCurr->OrderCurr()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnection_EnterSnapshotMode() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        incCurr->OrderCurr()->EnterSnapshotMode();
        if(!incCurr->OrderCurr()->GetItem("symbol1", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnection_ClearSnapshotMessages_1() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                     "                                                  ols symbol1 begin rpt 2 entry symbol1 222222 end",
                     30);
        if(snapCurr->Packet(1)->m_address != 0)
            throw;
        if(snapCurr->Packet(1)->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnection_ClearSnapshotMessages_2() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, ols symbol1 begin rpt 2 entry symbol1 222222 end",
                     30);
        if(snapCurr->Packet(1)->m_address != 0 ||
           snapCurr->Packet(2)->m_address != 0 ||
           snapCurr->Packet(3)->m_address != 0)
            throw;
        if(snapCurr->Packet(1)->m_processed != false ||
           snapCurr->Packet(2)->m_processed != false ||
           snapCurr->Packet(3)->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnection_ClearSnapshotMessages_3() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        snapCurr->WaitSnapshotMaxTimeMs(50);
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                     "                                                  ols symbol1 begin rpt 2 entry symbol1 222222, lost ols symbol1 rpt 2 entry symbol1 222222, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapCurr->m_packets[i]->m_address != 0 ||
                    snapCurr->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnection_ClearSnapshotMessages_4() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        snapCurr->WaitSnapshotMaxTimeMs(50);
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  ols symbol1 begin rpt 2 entry symbol1 222222, lost ols symbol1 rpt 2 entry symbol1 222222, hbeat, hbeat, hbeat, hbeat, hbeat, ols symbol1 rpt 2 entry symbol1 222222, ols symbol1 begin rpt 2 entry symbol1 222222 end",
                     30);
        if(incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(snapCurr->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incCurr->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(snapCurr->m_packets[i]->m_address != 0 || snapCurr->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnection_ClearSnapshotMessages() {
        printf("OLR CURR TestConnection_ClearSnapshotMessages_1\n");
        TestConnection_ClearSnapshotMessages_1();
        printf("OLR CURR TestConnection_ClearSnapshotMessages_2\n");
        TestConnection_ClearSnapshotMessages_2();
        printf("OLR CURR TestConnection_ClearSnapshotMessages_3\n");
        TestConnection_ClearSnapshotMessages_3();
        printf("OLR CURR TestConnection_ClearSnapshotMessages_4\n");
        TestConnection_ClearSnapshotMessages_4();
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot() {
        printf("OLR CURR TestConnection_EnterSnapshotMode\n");
        TestConnection_EnterSnapshotMode();
        printf("OLR CURR TestConnection_ClearSnapshotMessages\n");
        TestConnection_ClearSnapshotMessages();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_1();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_4();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnection_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incCurr->OrderCurr());
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        incCurr->StartListenSnapshot();

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        SendMessages(incCurr, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 1),
                                             new TestTemplateItemInfo("symbol2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_OLR_CURR, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 4),
                                             new TestTemplateItemInfo("symbol2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incCurr->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incCurr->OrderCurr());

        incCurr->OrderCurr()->Clear();
    }

    void TestConnection() {
        printf("OLR CURR TestConnection_AllSymbolsAreOk\n");
        TestConnection_AllSymbolsAreOk();
        printf("OLR CURR TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("OLR CURR TestConnection_AllSymbolsAreOkButOneMessageLost\n");
        TestConnection_AllSymbolsAreOkButOneMessageLost();
        printf("OLR CURR TestConnection_SkipHearthBeatMessages_Incremental\n");
        TestConnection_SkipHearthBeatMessages_Incremental();
        printf("OLR CURR TestConnection_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot();
        printf("OLR CURR TestConnection_NotAllSymbolsAreOk\n");
        TestConnection_NotAllSymbolsAreOk();
        printf("OLR CURR TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("OLR CURR TestConnection_StopTimersAfterReconnect\n");
        TestConnection_StopTimersAfterReconnect();
        printf("OLR CURR TestConnection_SnapshotSomeMessagesReceivedLater\n");
        TestConnection_SnapshotSomeMessagesReceivedLater();
        printf("OLR CURR TestConnection_SnapshotSomeMessagesNotReceived\n");
        TestConnection_SnapshotSomeMessagesNotReceived();
        printf("OLR CURR TestConnection_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnection_LastFragmentReceivedBeforeRouteFirst();
        printf("OLR CURR TestConnection_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnection_RouteFirstReceived_AfterSomeDummyMessages();
        printf("OLR CURR TestConnection_RouteFirstReceived_Empty\n");
        TestConnection_RouteFirstReceived_Empty();
        printf("OLR CURR TestConnection_TestSnapshotNoMessagesAtAll\n");
        TestConnection_TestSnapshotNoMessagesAtAll();
        printf("OLR CURR TestConnection_OneMessageReceived\n");
        TestConnection_OneMessageReceived();
        printf("OLR CURR TestConnection_Clear_AfterIncremental\n");
        TestConnection_Clear_AfterIncremental();
        printf("OLR CURR TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("OLR CURR TestConnection_TestSnapshotCollect\n");
        TestConnection_TestSnapshotCollect();
        printf("OLR CURR TestConnection_TestSnapshotNotCollect\n");
        TestConnection_TestSnapshotMessageLostAndTimeExpired();
        printf("OLR CURR TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("OLR CURR TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("OLR CURR TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("OLR CURR TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("OLR CURR TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("OLR CURR TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("OLR CURR TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestOrderTableItem() {
        printf("OLR CURR TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("OLR CURR TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("OLR CURR TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("OLR CURR TestTable_Default\n");
        TestTable_Default();
        printf("OLR CURR TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("OLR CURR TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("OLR CURR TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("OLR CURR TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("OLR CURR Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("OLR CURR TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("OLR CURR TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("OLR CURR TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("OLR CURR TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
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

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "olr entry symbol1 111111",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "olr entry symbol1 111111, olr entry symbol1 222222",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incCurr->OrderCurr()->Clear();
        newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "olr entry symbol1 111111, olr entry symbol1 222222, olr entry del symbol1 111111",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 1)
            throw;
        this->incCurr->OrderCurr()->Clear();
        newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4() {
        AstsOLSCURRItemInfo *info = this->m_helper->CreateOLSCurrItemInfo(1, 1, 1, 1, MDEntryType::mdetBuyQuote, "111111");
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

        this->AddSymbol("symbol1", "session1");
        int prevCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "olr entry symbol1 111111, olr entry symbol1 222222, olr entry change symbol1 111111",
                           "",
                           30);

        int newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incCurr->OrderCurr()->Clear();
        newCount = this->incCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        int prevCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "olr entry symbol1 111111, lost olr entry symbol1 222222, wait_snap, hbeat",
                           "                                                  ols begin symbol1 entry symbol1 222222 rpt 2 end",
                           30);

        int newCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        int prevCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessages(this->incCurr, this->snapCurr,
                           "olr entry symbol1 111111, lost olr entry symbol1 222222 entry symbol1 333333, wait_snap, hbeat",
                           "                                                   ols begin symbol1 entry symbol1 222222 rpt 2, ols symbol1 entry symbol1 333333 end",
                           30);

        int newCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        /*this->Clear();

        this->incCurr->OrderCurr()->Add("s1", "session1");
        int prevCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        this->SendMessagesIdf(this->incCurr, this->snapCurr,
                           "olr entry s1 e1, olr entry s1 e2, lost olr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   ols begin s1 entry s1 e1 rpt 2, ols s1 entry s1 e2, ols s1 entry s1 e3, ols s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 3)
            throw;*/
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");
        this->AddSymbol("symbol2", "session1");
        this->AddSymbol("symbol3", "session1");

        int prevCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol3 111111, wait_snap, olr entry symbol1 333333,                              hbeat,                              hbeat",
                     "                                                       ols symbol3 begin rpt 1 end entry symbol3 111111, ols symbol1 begin rpt 2 end entry symbol1 111111, hbeat, ols symbol2 begin rpt 2 end entry symbol2 111111",
                     30);
        int newCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 4) // was 2
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5() {
        this->Clear();
        this->AddSymbol("symbol1", "session1");
        incCurr->Start();

        int prevCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, lost olr entry symbol1 222222, olr entry symbol1 222222, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     ols symbol1 begin rpt 0 lastmsg 0 entry symbol1 111111 end",
                     30);
        int newCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6() {
        this->Clear();

        this->AddSymbol("symbol1", "session1");

        int prevCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        SendMessages(incCurr, snapCurr,
                     "olr entry symbol1 111111, olr entry symbol1 222222, olr entry symbol1 333333, lost hbeat, wait_snap, hbeat",
                     "                                                                          ols symbol1 begin rpt 1 entry symbol1 111111 end",
                     50);
        int newCount = this->snapCurr->m_fastProtocolManager->m_astsOLSCURRItems->Count();
        if(newCount != prevCount + 3)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr() {
        this->m_helper->SetCurrMode();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5();
        printf("OLR CURR TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6();
    }



    void Test_OnIncrementalRefresh_OLR_CURR_Add_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(!item1->Used)
            throw;
        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedBuyQuotes()->Count() != 1)
            throw;
        QuoteInfo *quote = obi->AggregatedBuyQuotes()->Item(0);
        Decimal price(3, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedBuyQuotes()->Count() != 2)
            throw;
        quote = obi->AggregatedBuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedBuyQuotes()->Count() != 3)
            throw;

        quote = obi->AggregatedBuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;

        quote = obi->AggregatedBuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;

        quote = obi->AggregatedBuyQuotes()->Last()->Data();
        price.Set(2, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedBuyQuotes()->Count() != 4)
            throw;

        quote = obi->AggregatedBuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;

        quote = obi->AggregatedBuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;

        quote = obi->AggregatedBuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;

        quote = obi->AggregatedBuyQuotes()->Last()->Data();
        price.Set(2, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(item1->Allocator->Count() != 1)
            throw;
        if(item2->Allocator->Count() != 1)
            throw;
        if(item3->Allocator->Count() != 1)
            throw;
        if(item4->Allocator->Count() != 1)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *ob = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(!ob->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!ob->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!ob->AggregatedBuyQuotes()->Item(2)->Price()->Equal(25, -3))
            throw;
        if(!ob->AggregatedBuyQuotes()->Item(3)->Price()->Equal(2, -2))
            throw;

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedBuyQuotes()->Count() != 3)
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(2)->Price()->Equal(2, -2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedBuyQuotes()->Count() != 2)
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(0)->Price()->Equal(3, -2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedBuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(!obi2->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!obi2->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!obi2->AggregatedBuyQuotes()->Item(2)->Price()->Equal(25, -3))
            throw;
        if(!obi2->AggregatedBuyQuotes()->Item(3)->Price()->Equal(2, -2))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");

        QuoteInfo *qt1 = obi->AggregatedBuyQuotes()->Item(0);
        QuoteInfo *qt2 = obi->AggregatedBuyQuotes()->Item(1);
        QuoteInfo *qt3 = obi->AggregatedBuyQuotes()->Item(2);
        QuoteInfo *qt4 = obi->AggregatedBuyQuotes()->Item(3);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->AggregatedBuyQuotes()->Count() != 4)
            throw;
        if(!qt1->Price()->Equal(3, -2))
            throw;
        if(!qt2->Price()->Equal(25, -3))
            throw;
        if(!qt3->Price()->Equal(24, -3))
            throw;
        if(!qt4->Price()->Equal(2, -2))
            throw;
    }

    void Test_Clear_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        this->incCurr->OrderCurr()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incCurr->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedBuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi2->AggregatedBuyQuotes()->Count() != 4)
            throw;

        AstsOLSCURRInfo *info2 = this->m_helper->CreateOLSCurrInfo("t1s2", "session1");
        AstsOLSCURRItemInfo *newItem1 = this->m_helper->CreateOLSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "777777");
        AstsOLSCURRItemInfo *newItem2 = this->m_helper->CreateOLSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "888888");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderCurr()->ObtainSnapshotItem(info2);
        this->incCurr->OrderCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 2)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi3 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi3->AggregatedBuyQuotes()->Count() != 4)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("t1s2", "session1");
        if(obi->AggregatedBuyQuotes()->Count() != 2)
            throw;

        QuoteInfo *qt1 = obi->AggregatedBuyQuotes()->Start()->Data();
        QuoteInfo *qt2 = obi->AggregatedBuyQuotes()->Start()->Next()->Data();

        if(!qt1->Price()->Equal(8, -2))
            throw;
        if(!qt2->Price()->Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();

        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->incCurr->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedSellQuotes()->Count() != 1)
            throw;
        QuoteInfo *quote = obi->AggregatedSellQuotes()->Start()->Data();
        if(!quote->Price()->Equal(3, -2))
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedSellQuotes()->Count() != 2)
            throw;
        quote = obi->AggregatedSellQuotes()->Start()->Data();
        if(!quote->Price()->Equal(3, -2))
            throw;

        quote = obi->AggregatedSellQuotes()->Item(1);
        if(!quote->Price()->Equal(4, -2))
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedSellQuotes()->Count() != 3)
            throw;

        quote = obi->AggregatedSellQuotes()->Start()->Data();
        if(!quote->Price()->Equal(2, -2))
            throw;

        quote = obi->AggregatedSellQuotes()->Start()->Next()->Data();
        if(!quote->Price()->Equal(3, -2))
            throw;

        quote = obi->AggregatedSellQuotes()->Last()->Data();
        if(!quote->Price()->Equal(4, -2))
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
        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi == 0)
            throw;
        if(obi->AggregatedSellQuotes()->Count() != 4)
            throw;

        quote = obi->AggregatedSellQuotes()->Start()->Data();
        if(!quote->Price()->Equal(2, -2))
            throw;

        quote = obi->AggregatedSellQuotes()->Start()->Next()->Data();
        if(!quote->Price()->Equal(25, -3))
            throw;

        quote = obi->AggregatedSellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->Price()->Equal(3, -2))
            throw;

        quote = obi->AggregatedSellQuotes()->Last()->Data();
        if(!quote->Price()->Equal(4, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

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

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedSellQuotes()->Count() != 3)
            throw;

        if(!obi->AggregatedSellQuotes()->Item(0)->Price()->Equal(2, -2))
            throw;
        if(!obi->AggregatedSellQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!obi->AggregatedSellQuotes()->Item(2)->Price()->Equal(4, -2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedSellQuotes()->Count() != 2)
            throw;
        if(!obi->AggregatedSellQuotes()->Item(0)->Price()->Equal(3, -2))
            throw;
        if(!obi->AggregatedSellQuotes()->Item(1)->Price()->Equal(4, -2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedSellQuotes()->Count() != 1)
            throw;
        if(!obi->AggregatedSellQuotes()->Item(0)->Price()->Equal(3, -2))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedSellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi2 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(!obi2->AggregatedSellQuotes()->Item(0)->Price()->Equal(2, -2))
            throw;
        if(!obi2->AggregatedSellQuotes()->Item(1)->Price()->Equal(25, -3))
            throw;
        if(!obi2->AggregatedSellQuotes()->Item(2)->Price()->Equal(3, -2))
            throw;
        if(!obi2->AggregatedSellQuotes()->Item(3)->Price()->Equal(4, -2))
            throw;

        AstsOLSCURRItemInfo *item5 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 24, -3, 1, 3, mduaChange, mdetSellQuote, "222222", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");

        QuoteInfo *qt1 = obi->AggregatedSellQuotes()->Item(0);
        QuoteInfo *qt2 = obi->AggregatedSellQuotes()->Item(1);
        QuoteInfo *qt3 = obi->AggregatedSellQuotes()->Item(2);
        QuoteInfo *qt4 = obi->AggregatedSellQuotes()->Item(3);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->AggregatedSellQuotes()->Count() != 4)
            throw;
        if(!qt1->Price()->Equal(2, -2))
            throw;
        if(!qt2->Price()->Equal(24, -3))
            throw;
        if(!qt3->Price()->Equal(25, -3))
            throw;
        if(!qt4->Price()->Equal(3, -2))
            throw;
    }

    void Test_Clear_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        this->incCurr->OrderCurr()->Clear();
        if(this->incCurr->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi->AggregatedSellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1");

        AstsIncrementalOLRCURRInfo *info = this->m_helper->CreateAstsIncrementalOLRCURRInfo();
        AstsOLSCURRItemInfo *item1 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "111111", 1);
        AstsOLSCURRItemInfo *item2 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "222222", 2);
        AstsOLSCURRItemInfo *item3 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "333333", 3);
        AstsOLSCURRItemInfo *item4 = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incCurr->OnIncrementalRefresh_OLR_CURR(info);

        AstsOLSCURRInfo *info2 = this->m_helper->CreateOLSCurrInfo("t1s2", "session1");
        AstsOLSCURRItemInfo *newItem1 = this->m_helper->CreateOLSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "777777");
        AstsOLSCURRItemInfo *newItem2 = this->m_helper->CreateOLSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "888888");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incCurr->OrderCurr()->ObtainSnapshotItem(info2);
        this->incCurr->OrderCurr()->ProcessSnapshot(info2);

        if(this->incCurr->OrderCurr()->UsedItemCount() != 2)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi3 = this->incCurr->OrderCurr()->GetItem("symbol1", "session1");
        if(obi3->AggregatedSellQuotes()->Count() != 4)
            throw;

        OrderInfo<AstsOLSCURRItemInfo> *obi = this->incCurr->OrderCurr()->GetItem("t1s2", "session1");
        if(obi->AggregatedSellQuotes()->Count() != 2)
            throw;

        QuoteInfo *qt1 = obi->AggregatedSellQuotes()->Start()->Data();
        QuoteInfo *qt2 = obi->AggregatedSellQuotes()->Start()->Next()->Data();

        if(!qt1->Price()->Equal(7, -2))
            throw;
        if(!qt2->Price()->Equal(8, -2))
            throw;
    }


    void Test_OnIncrementalRefresh_OLR_CURR_Aggregated() {
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Add_Aggregated\n");
        Test_OnIncrementalRefresh_OLR_CURR_Add_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Remove_Aggregated\n");
        Test_OnIncrementalRefresh_OLR_CURR_Remove_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Change_Aggregated\n");
        Test_OnIncrementalRefresh_OLR_CURR_Change_Aggregated();
        printf("OLR CURR Test_Clear_Aggregated\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OLR_CURR_SellQuotes_Aggregated() {
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes_Aggregated();
        printf("OLR CURR Test_Clear_SellQuotes_Aggregated\n");
        Test_Clear_SellQuotes();
    }

    void Test_Aggregation_Logic() {
        this->Clear();
        this->AddSymbol("symbol1");

        OrderInfo<AstsOLSCURRItemInfo> *item = this->m_table->Symbol(0)->Session(0);

        AstsOLSCURRItemInfo *info = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 100, 0, 200, 0, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "111111", 1);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 200)
            throw;

        info = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 100, 0, 100, 0, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "222222", 2);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 300)
            throw;

        info = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 100, 0, 50, 0, MDUpdateAction::mduaDelete, MDEntryType::mdetBuyQuote, "222222", 3);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 250)
            throw;

        info = this->m_helper->CreateOLRCurrItemInfo("symbol1", "session1", 100, 0, 50, 0, MDUpdateAction::mduaChange, MDEntryType::mdetBuyQuote, "111111", 4);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 50)
            throw;
    }

    void Test_Aggregated() {
        this->m_helper->SetCurrMode();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR\n");
        Test_OnIncrementalRefresh_OLR_CURR_Aggregated();
        printf("OLR CURR Test_OnFullRefresh_OBS_CURR\n");
        Test_OnFullRefresh_OBS_CURR_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_OLR_CURR_SellQuotes\n");
        Test_OnIncrementalRefresh_OLR_CURR_SellQuotes_Aggregated();
        printf("OLR CURR Test_OnFullRefresh_OBS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OBS_CURR_SellQuotes_Aggregated();
        printf("OLR CURR Test_Aggregation_Logic\n");
        Test_Aggregation_Logic();
    }
    
    
    
    void Test() {
        TestDefaults();
        TestStringIdComparer();
        TestInfoAndItemInfoUsageAndAllocationCurr();
        Test_OLR_CURR();
        Test_Aggregated();
        TestOrderTableItem();
        TestConnection();
    }
};

#endif
#endif //HFT_ROBOT_ORDERTABLECURR_H
