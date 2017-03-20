//
// Created by root on 19.03.17.
//

#ifndef HFT_ROBOT_FORTSORDERBOOKTESTER_H
#define HFT_ROBOT_FORTSORDERBOOKTESTER_H

#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnection.h"
#include "../Feeds/Forts/FortsFeeds.h"
#include "TestMessagesHelper.h"
#include "../MarketData/OrderBookInfo.h"
#include "../Fast/FastProtocolManager.h"
#include <stdio.h>

class OrderBookTesterForts {
    TestMessagesHelper          *m_helper;
    FeedConnection_FORTS_OBR    *incForts;
    FeedConnection_FORTS_SNAP   *snapForts;
    FeedConnection_FORTS_INSTR_SNAP *idfForts;
    MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo> *m_table;
public:
    OrderBookTesterForts() {
        this->m_helper = new TestMessagesHelper();
        this->m_helper->SetFortsMode();
        this->m_table = new MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        this->incForts = new FeedConnection_FORTS_OBR("FUT-BOOK-1 Incremental", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);

        this->snapForts = new FeedConnection_FORTS_SNAP("FUT_BOOK-1 Snap", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);
        this->idfForts = new FeedConnection_FORTS_INSTR_SNAP("FUT-BOOK-INFO", "Full Refresh", 'I',
                                                             FeedConnectionProtocol::UDP_IP,
                                                             "10.50.129.200", "239.192.113.3", 9113,
                                                             "10.50.129.200", "239.192.113.131", 9313);
        this->m_table->InitSymbols(10, 10);
        this->incForts->SetSymbolManager(new SymbolManager(10, true));
        this->snapForts->SetSymbolManager(this->incForts->GetSymbolManager());
        this->idfForts->AddConnectionToRecvSymbol(this->incForts);
        this->incForts->SetSecurityDefinition(this->idfForts);
        this->incForts->OrderBookForts()->InitSymbols(10, 10);
        this->incForts->SetMaxLostPacketCountForStartSnapshot(1);
    }
    ~OrderBookTesterForts() {
        delete this->incForts;
        delete this->snapForts;
        delete this->m_helper;
        delete this->m_table;
        delete this->idfForts;
    }

    void TestItem(OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo> *table) {
        for(int i = 0; i < this->m_table->SymbolsCount(); i++) {
            for(int j = 0; j < this->m_table->Symbol(i)->Count(); j++) {
                OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = this->m_table->Item(i, j);
                TestItem(item);
            }
        }
    }

    void Clear() {
        incForts->SetSnapshot(this->snapForts);
        incForts->OrderBookForts()->Clear();
        incForts->GetSymbolManager()->Clear();
        incForts->ClearMessages();
        incForts->WaitLostIncrementalMessageMaxTimeMs(50);
        incForts->m_waitTimer->Stop();
        incForts->m_waitTimer->Stop(1);
        snapForts->ClearMessages();
        snapForts->WaitSnapshotMaxTimeMs(50);
        incForts->StartListenSnapshot();
        snapForts->m_waitTimer->Stop();
        snapForts->Stop();
        incForts->Stop();
        idfForts->ClearSecurityDefinitions();

        this->m_helper->Clear();
        this->m_table->Clear();
        incForts->Start();
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Add() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        if(item4->Used)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(!item1->Used)
            throw;
        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FortsDefaultSnapshotMessageMDEntriesItemInfo *quote = obi->BuyQuotes()->Item(0);
        Decimal price(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 333333)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->BuyQuotes()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 444444)
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 333333)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Remove() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(obi->BuyQuotes()->Item(0)->MDEntryID != 111111)
            throw;
        if(obi->BuyQuotes()->Item(1)->MDEntryID != 222222)
            throw;
        if(obi->BuyQuotes()->Item(2)->MDEntryID != 333333)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(obi->BuyQuotes()->Item(0)->MDEntryID != 111111)
            throw;
        if(obi->BuyQuotes()->Item(1)->MDEntryID != 222222)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(obi->BuyQuotes()->Item(0)->MDEntryID != 111111)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Change() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi2 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi2->BuyQuotes()->Item(0)->MDEntryID != 111111)
            throw;
        if(obi2->BuyQuotes()->Item(1)->MDEntryID != 222222)
            throw;
        if(obi2->BuyQuotes()->Item(2)->MDEntryID != 333333)
            throw;
        if(obi2->BuyQuotes()->Item(3)->MDEntryID != 444444)
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 24, -3, 1000, mduaChange, mdetBuyQuote, 222222, 5);

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(qt1->MDEntryID != 111111)
            throw;
        if(qt2->MDEntryID != 222222)
            throw;
        if(qt3->MDEntryID != 333333)
            throw;
        if(qt4->MDEntryID != 444444)
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        this->incForts->OrderBookForts()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incForts->OrderBookForts()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi2 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        FortsDefaultSnapshotMessageInfo *info2 = this->m_helper->CreateFortsSnapshotInfo("t1s2", 121212);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem1 = this->m_helper->CreateFortsOBSItemInfo(7,-2, 100, mdetBuyQuote, 777777);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem2 = this->m_helper->CreateFortsOBSItemInfo(8,-2, 100, mdetBuyQuote, 888888);
        info2->RptSeq = 5;

        info2->MDEntriesCount = 2;
        info2->MDEntries[0] = newItem1;
        info2->MDEntries[1] = newItem2;

        this->incForts->OrderBookForts()->ObtainSnapshotItemForts(info2);
        this->incForts->OrderBookForts()->ProcessSnapshotForts(info2);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi3 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(121212, 0);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt2 = obi->BuyQuotes()->Item(1);

        if(qt1->MDEntryID != 777777)
            throw;
        if(qt2->MDEntryID != 888888)
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(qt1->MDEntrySize != 1000)
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FortsDefaultSnapshotMessageMDEntriesItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 333333)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 333333)
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 444444)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(obi->SellQuotes()->Item(0)->MDEntryID != 111111)
            throw;
        if(obi->SellQuotes()->Item(1)->MDEntryID != 222222)
            throw;
        if(obi->SellQuotes()->Item(2)->MDEntryID != 333333)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(obi->SellQuotes()->Item(0)->MDEntryID != 111111)
            throw;
        if(obi->SellQuotes()->Item(1)->MDEntryID != 222222)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(obi->SellQuotes()->Item(0)->MDEntryID != 111111)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi2 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi2->SellQuotes()->Item(0)->MDEntryID != 111111)
            throw;
        if(obi2->SellQuotes()->Item(1)->MDEntryID != 222222)
            throw;
        if(obi2->SellQuotes()->Item(2)->MDEntryID != 333333)
            throw;
        if(obi2->SellQuotes()->Item(3)->MDEntryID != 444444)
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 24, -3, 1000, mduaChange, mdetSellQuote, 222222, 5);

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(qt1->MDEntryID != 111111)
            throw;
        if(qt2->MDEntryID != 222222)
            throw;
        if(qt3->MDEntryID != 333333)
            throw;
        if(qt4->MDEntryID != 444444)
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        this->incForts->OrderBookForts()->Clear();
        if(this->incForts->OrderBookForts()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        FortsDefaultSnapshotMessageInfo *info2 = this->m_helper->CreateFortsSnapshotInfo("t1s2", 121212);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem1 = this->m_helper->CreateFortsOBSItemInfo(7,-2, 100, mdetSellQuote, 777777);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem2 = this->m_helper->CreateFortsOBSItemInfo(8,-2, 100, mdetSellQuote, 888888);

        info2->MDEntriesCount = 2;
        info2->MDEntries[0] = newItem1;
        info2->MDEntries[1] = newItem2;

        this->incForts->OrderBookForts()->ObtainSnapshotItemForts(info2);
        this->incForts->OrderBookForts()->ProcessSnapshotForts(info2);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi3 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(121212, 0);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

        if(qt1->MDEntryID != 777777)
            throw;
        if(qt2->MDEntryID != 888888)
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(qt1->MDEntrySize != 1000)
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR() {
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Add\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Remove\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Change\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change();
        printf("OLR CURR Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes() {
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes();
        printf("OLR CURR Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OLR_CURR() {
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR\n");
        Test_OnIncrementalRefresh_FORTS_OBR();
        printf("OLR CURR Test_OnFullRefresh_OLS_CURR\n");
        Test_OnFullRefresh_OLS_CURR();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes();
        printf("OLR CURR Test_OnFullRefresh_OLS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OLS_CURR_SellQuotes();
    }

    void TestDefaults() {
        if(this->incForts->OrderBookForts()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incForts->OrderBookForts());
    }

    void TestTableItem_CorrectBegin() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = new OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>>("symbol1"));

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 111111);
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
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = new OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>>("symbol1"));

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 111111);
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
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = new OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>>("symbol1"));

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 111111);
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 222222);
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

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 333333);
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

    void ClearSymbols() {
        this->m_table->Clear();
        this->idfForts->ClearSecurityDefinitions();
        this->incForts->OrderBookForts()->Clear();
        this->incForts->GetSymbolManager()->Clear();
    }

    void TestTable_AfterClear() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 111111);
        item->RptSeq = 1;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 111111);
        item2->RptSeq = 2;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 111111);
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item, 0);
        this->m_table->ProcessIncremental(item2, 0);
        this->m_table->ProcessIncremental(item3, 0);

        if(this->m_table->UsedItemCount() != 1)
            throw;
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tableItem = this->m_table->GetItemBySecurityId(111111, 0);
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0))
            throw;
    }

    void TestTable_IncorrectBegin() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 2;

        if(this->m_table->ProcessIncremental(item1, 0))
            throw;
    }

    void TestTable_SkipMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0))
            throw;

        
    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol2", 222222, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item2->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item2, 1))
            throw;

        if(this->m_table->UsedItemCount() != 2)
            throw;

        
    }

    void TestTable_CorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 222222, 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 333333, 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 444444, 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 555555, 3);
        item5->RptSeq = 3;

        FortsDefaultSnapshotMessageInfo *info = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;
        info->RptSeq = 3;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = this->m_table->GetItemBySecurityId(111111, 0);

        this->m_table->ObtainSnapshotItemForts(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->MDEntries, 1, 3);
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 333333, 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 444444, 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0))
            throw;

        FortsDefaultSnapshotMessageInfo *info1 = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info1->MDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->MDEntries[0] = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 222222);

        FortsDefaultSnapshotMessageInfo *info2 = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info2->MDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->MDEntries[0] = this->m_helper->CreateFortsOBSItemInfo(8, 1, 80, MDEntryType::mdetBuyQuote, 222222);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = this->m_table->GetItemBySecurityId(111111, 0);

        this->m_table->ObtainSnapshotItemForts(info1);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshotForts(info1);
        this->m_table->ProcessSnapshotForts(info2);
        if(!this->m_table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 4)
            throw;
    }

    void TestTable_IncorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 222222, 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 333333, 5);
        item3->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item3, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 444444, 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 555555, 2);
        item5->RptSeq = 2;

        FortsDefaultSnapshotMessageInfo *info = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;
        info->RptSeq = 2;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = this->m_table->GetItemBySecurityId(111111, 0);

        this->m_table->ObtainSnapshotItemForts(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->MDEntries, 1, 2);
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 222222, 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 444444, 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 555555, 3);
        item5->RptSeq = 3;

        FortsDefaultSnapshotMessageInfo *info = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;
        info->RptSeq = 3;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tb = this->m_table->GetItemBySecurityId(111111, 0);

        this->m_table->ObtainSnapshotItemForts(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->MDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() == 3)
            throw;
        if(this->m_table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 4)
            throw;
        this->m_table->ObtainSnapshotItemForts(info);
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

        SendMessages(incForts, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fortsHearthBeat, 1),
                new TestTemplateInfo(FeedTemplateId::fortsHearthBeat, 2),
                new TestTemplateInfo(FeedTemplateId::fortsHearthBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        SendMessages(incForts, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 2, 100, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 3, 1000, 1),
                                     }, 1),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 444444, 4, 3, 1000, 1),
                                     }, 1)
        }, 3);


        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnection_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 2, 100, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 4, 3, 1000, 1),
                                     }, 1)
        }, 2);
        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 1) // cell for rptseq 3 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(((FortsDefaultSnapshotMessageMDEntriesItemInfo*)item->EntriesQueue()->Entries()[1])->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 444444, 3, 1, 10, 1),
                                     }, 1)
        }, 1);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 2, 100, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 3, 1000, 1),
                                     }, 1)
        }, 2);
        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(((FortsDefaultSnapshotMessageMDEntriesItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 444444, 4, 1, 10, 1),
                                     }, 2)
        }, 1);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 2, 100, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 3, 1000, 1),
                                     }, 1)
        }, 2);
        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(((FortsDefaultSnapshotMessageMDEntriesItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 1, 10, 1),
                                     }, 1)
        }, 1);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(!incForts->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(incForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 4, 1, 10, 1),
                                     }, 1)
        }, 1);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
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
        this->AddSymbol("symbol1", 111111);

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 2, 100, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 3, 1000, 1),
                                     }, 1)
        }, 2);
        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(((FortsDefaultSnapshotMessageMDEntriesItemInfo*)item->EntriesQueue()->Entries()[2])->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 4, 1, 10, 1),
                                     }, 1)
        }, 1);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(!incForts->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(incForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 1, 10, 1),
                                     }, 1)
        }, 1);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
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
        this->AddSymbol("symbol1", 111111);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 1, 10, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 2, 100, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 3, 1000, 1),
                                     }, 1)
        }, 2);
        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incForts->m_waitTimer->ElapsedMilliseconds() < incForts->WaitLostIncrementalMessageMaxTimeMs());
        if(!incForts->Listen_Atom_Incremental_Core())
            throw;
        //entering snapshot mode
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
        // timer should be stopped
        if(incForts->m_waitTimer->Active())
            throw;
        if(snapForts->m_startMsgSeqNum != -1)
            throw;
        if(snapForts->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnection_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        incForts->StartListenSnapshot();
        if(!snapForts->m_waitTimer->Active()) // start wait timer immediately
            throw;

        snapForts->Listen_Atom_Snapshot(); // activate timer 2 when first time no messages recv
        //no messages
        while(snapForts->m_waitTimer->ElapsedMilliseconds(2) <= snapForts->WaitAnyPacketMaxTimeMs - 50) {
            if(!snapForts->m_waitTimer->Active())
                throw;
            if(!snapForts->Listen_Atom_Snapshot())
                throw; // nothing should be happens
            if(!snapForts->m_waitTimer->Active(2))
                throw;
            if(snapForts->m_endMsgSeqNum != -1)
                throw;
            if(snapForts->m_startMsgSeqNum != -1)
                throw;
        }
        while(snapForts->m_waitTimer->ElapsedMilliseconds(2) <= snapForts->WaitAnyPacketMaxTimeMs) {
            int a = 5;
            // just wait
        }
        if(!snapForts->m_waitTimer->Active(2))
            throw;

        if(!snapForts->Listen_Atom_Snapshot()) // reconnect
            throw;
        if(snapForts->m_waitTimer->Active())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(snapForts->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_waitTimer->Active(2))
            throw;

        // now we should restart?
        if(!snapForts->Reconnect_Atom())
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
        if(snapForts->m_startMsgSeqNum != -1)
            throw;
        if(snapForts->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnection_OneMessageReceived() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        //no messages first half time
        while(snapForts->m_waitTimer->ElapsedMilliseconds() < snapForts->WaitSnapshotMaxTimeMs() / 2) {
            if(!snapForts->m_waitTimer->Active())
                throw;
            if(!snapForts->Listen_Atom_Snapshot())
                throw; // nothing should be happens
            if(snapForts->m_endMsgSeqNum != -1)
                throw;
            if(snapForts->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(snapForts->m_waitTimer->ElapsedMilliseconds() >= snapForts->WaitAnyPacketMaxTimeMs / 2)
            throw;

        if(!snapForts->Listen_Atom_Snapshot())
            throw; // nothing should be happens
    }

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
        if(snapForts->m_snapshotRouteFirst != 2)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;

        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;

        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
        if(snapForts->m_snapshotRouteFirst != 2)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
    }

    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 1, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 1)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 4, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 2);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 5)
            throw;
        if(snapForts->m_endMsgSeqNum != 4)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 5, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 6, "symbol1", 111111, true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 2);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 7)
            throw;
        if(snapForts->m_endMsgSeqNum != 6)
            throw;
        if(snapForts->m_snapshotRouteFirst != 6)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;

        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 7)
            throw;
        if(snapForts->m_endMsgSeqNum != 6)
            throw;
        if(snapForts->m_snapshotRouteFirst != 6)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
    }

    void TestConnection_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 1, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 1)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_snapshotLastFragment != -1)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
    }

    void TestConnection_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 1, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        snapForts->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        snapForts->Listen_Atom_Snapshot_Core();

        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
        if(!snapForts->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        snapForts->m_waitTimer->Stop(); // reset timer 0 to avoid simulate situation when no packet received
        // now wait some time and after that we have to skip lost message to get other snapshot
        while(!snapForts->m_waitTimer->IsElapsedMilliseconds(1, snapForts->WaitSnapshotMaxTimeMs())) {
            snapForts->Listen_Atom_Snapshot_Core();
            if(!snapForts->m_waitTimer->Active(1))
                break;
        }

        snapForts->Listen_Atom_Snapshot_Core();
        if(snapForts->m_startMsgSeqNum != 4)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
        if(snapForts->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 1, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        snapForts->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;

        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
        if(!snapForts->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        // wait some time and then receive lost packet
        while(!snapForts->m_waitTimer->IsElapsedMilliseconds(1, snapForts->WaitSnapshotMaxTimeMs() / 2)) {
            snapForts->m_waitTimer->Start(); // reset timer 0 to avoid simulate situation when no packet received
            if(!snapForts->Listen_Atom_Snapshot_Core())
                throw;
        }

        if(!snapForts->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;
        if(snapForts->m_startMsgSeqNum != 4)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
        if(snapForts->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;
    }

    void TestConnection_StopTimersAfterReconnect() {
        this->Clear();
        incForts->StartListenSnapshot();

        // manually activate timer 1
        snapForts->m_waitTimer->Activate(1);
        snapForts->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
        snapForts->DoWorkAtom();

        if(!snapForts->m_waitTimer->Active())
            throw;
        if(snapForts->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_TestSnapshotCollect() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;

        snapForts->Listen_Atom_Snapshot_Core();
        //snapshot received and should be applied
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tableItem = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        if(tableItem->BuyQuotes()->Count() != 2)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_snapshotLastFragment != -1)
            throw;
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
    }

    void TestConnection_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        snapForts->WaitSnapshotMaxTimeMs(100);
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 4, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 6),
        }, 2);

        if(snapForts->Packet(3)->m_address != 0)
            throw;
        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 4)
            throw;
        if(snapForts->m_waitTimer->Active(1))
            throw;

        snapForts->Listen_Atom_Snapshot_Core();
        if(snapForts->m_waitTimer->Active(1))
            throw;

        snapForts->Listen_Atom_Snapshot_Core();

        if(!snapForts->m_waitTimer->Active(1))
            throw;
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_snapshotRouteFirst != 2)
            throw;
        if(snapForts->m_snapshotLastFragment != -1)
            throw;

        snapForts->Listen_Atom_Snapshot_Core();
        if(!snapForts->m_waitTimer->Active(1))
            throw;
        while(snapForts->m_waitTimer->ElapsedMilliseconds(1) <= snapForts->WaitSnapshotMaxTimeMs())
            snapForts->Listen_Atom_Snapshot_Core();

        snapForts->Listen_Atom_Snapshot_Core();
        // reset
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_snapshotLastFragment != -1)
            throw;
        if(snapForts->m_waitTimer->Active(1))
            throw;
    }
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        incForts->StartListenSnapshot();

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        SendMessages(incForts, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", 111111, 1),
                                             new TestTemplateItemInfo("symbol2", 111111, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", 111111, 4),
                                             new TestTemplateItemInfo("symbol2", 111111, 4),
                                     }, 2)
        }, 2);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;

        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incForts->m_waitTimer->ElapsedMilliseconds() < incForts->WaitLostIncrementalMessageMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapForts, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(111111),
                                     }, 2, 4)
        }, 1);
        if(!snapForts->Listen_Atom_Snapshot_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item1 = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item2 = incForts->OrderBookForts()->GetItemBySecurityId(222222, 0);
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

        this->AddSymbol("symbol1", 111111);
        this->incForts->StartListenSnapshot();
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incForts->Packet(4)->m_address == 0 || incForts->Packet(5)->m_address == 0 || incForts->Packet(6)->m_address == 0)
            throw;
        if(!incForts->Packet(4)->m_processed || !incForts->Packet(5)->m_processed || !incForts->Packet(6)->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapForts->Packet(1)->m_address == 0 || snapForts->Packet(2)->m_address == 0 || snapForts->Packet(3)->m_address == 0)
        //    throw;
        //if(!snapForts->Packet(1)->m_processed || !snapForts->Packet(2)->m_processed || !snapForts->Packet(3)->m_processed)
        //    throw;
    }

    void TestConnection_AllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, obr entry symbol1 sid 111111 333333, obr entry symbol2 sid 222222 111111, obr entry symbol2 sid 222222 222222",
                     "",
                     30);
        if(incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;
        if(incForts->OrderBookForts()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_NotAllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, obr entry symbol1 sid 111111 333333, obr entry symbol2 sid 222222 111111, obr entry symbol2 sid 222222 222222",
                     "",
                     30);
        if(incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;
        if(!incForts->OrderBookForts()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(incForts->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 222222, obr entry symbol1 sid 111111 333333, obr entry symbol2 sid 222222 111111, obr entry symbol2 sid 222222 222222",
                     "",
                     30);

        if(incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;
        if(incForts->OrderBookForts()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111",
                     "",
                     30);
        if(incForts->HasPotentiallyLostPackets())
            throw;
        if(incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, hbeat",
                     "",
                     30);
        if(!incForts->HasPotentiallyLostPackets())
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(!incForts->m_waitTimer->Active())
            throw;
        if(incForts->m_waitTimer->IsElapsedMilliseconds(incForts->m_waitLostIncrementalMessageMaxTimeMs))
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, hbeat, hbeat",
                     "",
                     30);
        if(incForts->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incForts->HasPotentiallyLostPackets())
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(incForts->m_waitTimer->Active())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incForts->OrderBookForts()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incForts->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incForts->HasPotentiallyLostPackets())
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(incForts->m_waitTimer->Active())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incForts->OrderBookForts()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1() {
//        this->Clear();
//
//        incForts->OrderBookForts()->Add("s1", "session1");
//        incForts->OrderBookForts()->Add("symbol3", "session1");
//
//        if(snapForts->State() != FeedConnectionState::fcsSuspend)
//            throw;
//        SendMessages(incForts, snapForts,
//                     "olr entry s1 e1, lost olr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
//                     "",
//                     30);
//        if(incForts->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(!incForts->HasPotentiallyLostPackets())
//            throw;
//        if(!incForts->ShouldRestoreIncrementalMessages())
//            throw;
//        if(incForts->m_waitTimer->Active())
//            throw;
//        if(snapForts->State() != FeedConnectionState::fcsConnect)
//            throw;
//        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(incForts->OrderBookForts()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
//            throw;
//        if(incForts->OrderBookForts()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
//            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, wait_snap",
                     "",
                     30);
        if(incForts->m_waitTimer->Active())
            throw;
        if(incForts->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, wait_snap, obr entry symbol1 sid 111111 333333,    hbeat,                              hbeat",
                     "                                                            obs symbol3 begin rpt 1, obs symbol3 rpt 1 entry symbol3 sid 333333 111111, obs symbol3 rpt 1 end",
                     30);
        if(incForts->HasQueueEntries())
            throw;
        if(incForts->CanStopListeningSnapshot()) // because we did not receive all snapshots for all m_symbols
            throw;
        if(snapForts->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->UsedItemCount() != 3)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 2)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->BuyQuotes()->Count() != 0)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(333333, 0)->BuyQuotes()->Count() != 1)
            throw;
        if(incForts->m_startMsgSeqNum != 2)
            throw;
        if(incForts->m_endMsgSeqNum != 6)
            throw;
        if(snapForts->m_startMsgSeqNum != 4)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "lost obr entry symbol1 sid 111111 111111, lost hbeat, wait_snap",
                     "obs symbol1 begin rpt 1, obs symbol1 rpt 1 entry symbol1 sid 111111 111111, obs symbol1 rpt 1 end",
                     30);
        if(incForts->HasQueueEntries())
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incForts->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 1)
            throw;
        if(incForts->m_startMsgSeqNum != 4)
            throw;
        if(incForts->m_endMsgSeqNum != 3)
            throw;
        if(snapForts->m_startMsgSeqNum != 4)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->UsedItemCount() != 3)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, wait_snap, obr entry symbol1 sid 111111 333333,                         hbeat,                                        hbeat",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 sid 333333 111111, obs symbol1 begin rpt 2 end entry symbol1 sid 111111 111111, hbeat, obs symbol2 begin rpt 2 end entry symbol2 sid 222222 111111",
                     30);
        if(incForts->HasQueueEntries())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 2)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(333333, 0)->RptSeq() != 1)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->RptSeq() != 2)
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->UsedItemCount() != 3)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->BuyQuotes()->Count() != 1)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(333333, 0)->BuyQuotes()->Count() != 1)
            throw;
        if(incForts->m_startMsgSeqNum != 7)
            throw;
        if(incForts->m_endMsgSeqNum != 6)
            throw;
        if(snapForts->m_startMsgSeqNum != 5)
            throw;
        if(snapForts->m_endMsgSeqNum != 4)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    // almost the same as TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->UsedItemCount() != 3)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, wait_snap, obr entry symbol1 sid 111111 333333,                         obr entry symbol2 sid 222222 111111,                         obr entry symbol2 sid 222222 222222",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 sid 333333 111111, obs symbol1 begin rpt 2 end entry symbol1 sid 111111 111111, obs symbol2 begin rpt 2 end entry symbol2 sid 222222 111111 skip_if_suspend",
                     30);
        if(incForts->HasQueueEntries())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 2)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(333333, 0)->RptSeq() != 1)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->RptSeq() != 2)
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->UsedItemCount() != 3)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->BuyQuotes()->Count() != 2)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(333333, 0)->BuyQuotes()->Count() != 1)
            throw;
        if(incForts->m_startMsgSeqNum != 7)
            throw;
        if(incForts->m_endMsgSeqNum != 6)
            throw;
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
    }
    // we receive snapshot which rpt seq is less than incremental actual rpt seq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);

        if(!incForts->m_waitTimer->Active())
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, obr entry symbol1 sid 111111 333333, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs symbol1 begin rpt 1 entry symbol1 sid 111111 111111 end",
                     50);
        if(incForts->HasQueueEntries())
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incForts->CanStopListeningSnapshot())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 3)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 3)
            throw;
        if(snapForts->m_startMsgSeqNum != 2)
            throw;
        if(snapForts->m_endMsgSeqNum != 1)
            throw;
        if(snapForts->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(snapForts->m_startMsgSeqNum != 2) // detect that
            throw;
    }
    // we received snapshot for item but item has 2 gaps and snapshot is partially actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        incForts->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, lost obr entry symbol1 sid 111111 333333, obr entry symbol1 sid 111111 444444, lost obr entry symbol1 sid 111111 555555, obr entry symbol1 sid 111111 666666, wait_snap, ",
                     "                                                                                                                           obs symbol1 begin rpt 4 entry symbol1 sid 111111 444444 end",
                     30);
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 4)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incForts->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, lost obr entry symbol1 sid 111111 333333, obr entry symbol1 sid 111111 444444, lost obr entry symbol1 sid 111111 555555, obr entry symbol1 sid 111111 666666, wait_snap, ",
                     "                                                                                                                           obs symbol1 begin rpt 5 entry symbol1 sid 111111 555555 end",
                     30);
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incForts->HasQueueEntries())
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 6)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incForts->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, lost obr entry symbol1 sid 111111 333333, obr entry symbol1 sid 111111 444444, lost obr entry symbol1 sid 111111 555555, obr entry symbol1 sid 111111 666666, wait_snap, ",
                     "                                                                                                                           obs symbol1 begin rpt 6 entry symbol1 sid 111111 666666 end",
                     30);
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incForts->HasQueueEntries())
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 6)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incForts->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol2 sid 222222 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat                               lost obr entry symbol1 sid 111111 333333,               obr entry symbol1 sid 111111 444444",
                     "                                                                   obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222 end, obs symbol2 begin rpt 1 entry symbol2 sid 222222 111111 end, hbeat",
                     30);
        if(incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 2)
            throw;
        if(!incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->RptSeq() != 1)
            throw;
        if(incForts->OrderBookForts()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        if(incForts->OrderBookForts()->Symbol(0)->Session(0)->ShouldProcessSnapshot())
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->Session(0)->ShouldProcessSnapshot())
            throw;
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol2 sid 222222 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat                               lost obr entry symbol1 sid 111111 333333,               obr entry symbol1 sid 111111 444444, hbeat ",
                     "                                                                   obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222 end, obs symbol2 begin rpt 1 entry symbol2 sid 222222 111111 end, hbeat          , obs symbol1 begin rpt 3 entry symbol1 sid 111111 333333 end",
                     30);
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->RptSeq() != 4)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->QueueEntriesCount() != 0)
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol2 sid 222222 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, obr entry symbol2 sid 222222 222222, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incForts->OrderBookForts()->GetItemBySecurityId(222222, 0)->ShouldProcessSnapshot())
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
        incForts->m_fastProtocolManager->SetNewBuffer(msg, 52);
        incForts->m_fastProtocolManager->ReadMsgSeqNumber();
        incForts->m_fastProtocolManager->Decode();
        incForts->m_fastProtocolManager->Print();
        */

        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, obr entry symbol1 sid 111111 222222, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     obs symbol1 begin rpt 0 lastmsg 0 entry symbol1 sid 111111 111111 end",
                     30);
        if(incForts->OrderBookForts()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnection_EnterSnapshotMode() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        incForts->OrderBookForts()->EnterSnapshotMode();
        if(!incForts->OrderBookForts()->GetItemBySecurityId(111111, 0)->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnection_ClearSnapshotMessages_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat",
                     "                                                  obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222 end",
                     30);
        if(snapForts->Packet(1)->m_address != 0)
            throw;
        if(snapForts->Packet(1)->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnection_ClearSnapshotMessages_2() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222 end",
                     30);
        if(snapForts->Packet(1)->m_address != 0 ||
           snapForts->Packet(2)->m_address != 0 ||
           snapForts->Packet(3)->m_address != 0)
            throw;
        if(snapForts->Packet(1)->m_processed != false ||
           snapForts->Packet(2)->m_processed != false ||
           snapForts->Packet(3)->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnection_ClearSnapshotMessages_3() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        snapForts->WaitSnapshotMaxTimeMs(50);
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat",
                     "                                                  obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222, lost obs symbol1 rpt 2 entry symbol1 sid 111111 222222, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapForts->m_packets[i]->m_address != 0 ||
                    snapForts->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnection_ClearSnapshotMessages_4() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        snapForts->WaitSnapshotMaxTimeMs(50);
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222, lost obs symbol1 rpt 2 entry symbol1 sid 111111 222222, hbeat, hbeat, hbeat, hbeat, hbeat, obs symbol1 rpt 2 entry symbol1 sid 111111 222222, obs symbol1 begin rpt 2 entry symbol1 sid 111111 222222 end",
                     30);
        if(incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incForts->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(snapForts->m_packets[i]->m_address != 0 || snapForts->m_packets[i]->m_processed != false)
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
        this->TestTableItemsAllocator(incForts->OrderBookForts());
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        incForts->StartListenSnapshot();

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        SendMessages(incForts, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", 111111, 1),
                                             new TestTemplateItemInfo("symbol2", 111111, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", 111111, 4),
                                             new TestTemplateItemInfo("symbol2", 111111, 4),
                                     }, 2)
        }, 2);

        if(!incForts->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        incForts->OrderBookForts()->Clear();
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

    void AddSymbol(const char *symbol, UINT64 securityId) {
        FortsSecurityDefinitionInfo *info = new FortsSecurityDefinitionInfo();
        strcpy(info->Symbol, symbol);
        info->SymbolLength = strlen(symbol);
        info->SecurityID = securityId;

        LinkedPointer<FortsSecurityDefinitionInfo> *ptr = new LinkedPointer<FortsSecurityDefinitionInfo>();
        ptr->Data(info);

        SymbolInfo *s = this->incForts->GetSymbolManager()->GetSymbol(info->SecurityID);
        this->incForts->SecurityDefinition()->SymbolsForts()[s->m_index] = ptr;
        this->incForts->AddSymbol(ptr, s->m_index);
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        int prevCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessages(this->incForts, this->snapForts,
                           "obr entry symbol1 sid 111111 111111",
                           "",
                           30);

        int newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        int prevCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessages(this->incForts, this->snapForts,
                           "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222",
                           "",
                           30);

        int newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incForts->OrderBookForts()->Clear();
        newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        int prevCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessages(this->incForts, this->snapForts,
                           "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, obr entry del symbol1 111111",
                           "",
                           30);

        int newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 1)
            throw;
        this->incForts->OrderBookForts()->Clear();
        newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4() {
        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = this->m_helper->CreateFortsOBSItemInfo(1, 1, 10, MDEntryType::mdetBuyQuote, 111111);
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

        this->AddSymbol("symbol1", 111111);
        int prevCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessages(this->incForts, this->snapForts,
                           "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, obr entry change symbol1 111111",
                           "",
                           30);

        int newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incForts->OrderBookForts()->Clear();
        newCount = this->incForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessages(this->incForts, this->snapForts,
                           "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, wait_snap, hbeat",
                           "                                                  obs begin symbol1 entry symbol1 sid 111111 222222 rpt 2 end",
                           30);

        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessages(this->incForts, this->snapForts,
                           "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222 entry symbol1 sid 111111 333333, wait_snap, hbeat",
                           "                                                   obs begin symbol1 entry symbol1 sid 111111 222222 rpt 2, obs symbol1 entry symbol1 sid 111111 333333 end",
                           30);

        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        /*this->Clear();

        this->incForts->OrderBookForts()->Add("s1", "session1");
        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        this->SendMessagesIdf(this->incForts, this->snapForts,
                           "olr entry s1 e1, olr entry s1 e2, lost olr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   ols begin s1 entry s1 e1 rpt 2, ols s1 entry s1 e2, ols s1 entry s1 e3, ols s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 3)
            throw;*/
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol3 sid 333333 111111, wait_snap, obr entry symbol1 sid 111111 333333,                              hbeat,                              hbeat",
                     "                                                       obs symbol3 begin rpt 1 end entry symbol3 sid 333333 111111, obs symbol1 begin rpt 2 end entry symbol1 sid 111111 111111, hbeat, obs symbol2 begin rpt 2 end entry symbol2 sid 222222 111111",
                     30);
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 4) // was 2
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, lost obr entry symbol1 sid 111111 222222, obr entry symbol1 sid 111111 222222, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     obs symbol1 begin rpt 0 lastmsg 0 entry symbol1 sid 111111 111111 end",
                     30);
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111, obr entry symbol1 sid 111111 222222, obr entry symbol1 sid 111111 333333, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs symbol1 begin rpt 1 entry symbol1 sid 111111 111111 end",
                     50);
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 3)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr() {
        this->m_helper->SetFortsMode();
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

    /*
    void Test_OnIncrementalRefresh_FORTS_OBR_Add_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        if(item4->Used)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(!item1->Used)
            throw;
        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        quote = obi->AggregatedBuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        quote = obi->AggregatedBuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price()->Equal(&price))
            throw;
        if(quote->Size() != 100)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Remove_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(item1->Allocator->Count() != 1)
            throw;
        if(item2->Allocator->Count() != 1)
            throw;
        if(item3->Allocator->Count() != 1)
            throw;
        if(item4->Allocator->Count() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *ob = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedBuyQuotes()->Count() != 3)
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(2)->Price()->Equal(2, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedBuyQuotes()->Count() != 2)
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!obi->AggregatedBuyQuotes()->Item(0)->Price()->Equal(3, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedBuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Change_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi2 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(!obi2->AggregatedBuyQuotes()->Item(0)->Price()->Equal(4, -2))
            throw;
        if(!obi2->AggregatedBuyQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!obi2->AggregatedBuyQuotes()->Item(2)->Price()->Equal(25, -3))
            throw;
        if(!obi2->AggregatedBuyQuotes()->Item(3)->Price()->Equal(2, -2))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 24, -3, 1, 3, mduaChange, mdetBuyQuote, 222222, 5);

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;
        item5->RptSeq = 5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemByIndex("symbol1", "t1");

        QuoteInfo *qt1 = obi->AggregatedBuyQuotes()->Item(0);
        QuoteInfo *qt2 = obi->AggregatedBuyQuotes()->Item(1);
        QuoteInfo *qt3 = obi->AggregatedBuyQuotes()->Item(2);
        QuoteInfo *qt4 = obi->AggregatedBuyQuotes()->Item(3);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        this->incForts->OrderBookForts()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incForts->OrderBookForts()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedBuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetBuyQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetBuyQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetBuyQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetBuyQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi2 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi2->AggregatedBuyQuotes()->Count() != 4)
            throw;

        FortsDefaultSnapshotMessageInfo *info2 = this->m_helper->CreateFortsSnapshotInfo("t1s2", 121212);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem1 = this->m_helper->CreateFortsOBSItemInfo(7,-2, 1, 2, mdetBuyQuote, "e7");
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem2 = this->m_helper->CreateFortsOBSItemInfo(8,-2, 1, 2, mdetBuyQuote, "e8");
        info2->RptSeq = 5;

        info2->MDEntriesCount = 2;
        info2->MDEntries[0] = newItem1;
        info2->MDEntries[1] = newItem2;

        this->incForts->OrderBookForts()->ObtainSnapshotItemForts(info2);
        this->incForts->OrderBookForts()->ProcessSnapshot(info2);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi3 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi3->AggregatedBuyQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(121212, 0);
        if(obi->AggregatedBuyQuotes()->Count() != 2)
            throw;

        QuoteInfo *qt1 = obi->AggregatedBuyQuotes()->Start()->Data();
        QuoteInfo *qt2 = obi->AggregatedBuyQuotes()->Start()->Next()->Data();

        if(!qt1->Price()->Equal(8, -2))
            throw;
        if(!qt2->Price()->Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId("symbol1", "t1");
        if(obi == 0)
            throw;
        if(obi->AggregatedSellQuotes()->Count() != 1)
            throw;
        QuoteInfo *quote = obi->AggregatedSellQuotes()->Start()->Data();
        if(!quote->Price()->Equal(3, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemByIndex("symbol1", "t1");
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

        quote = obi->AggregatedSellQuotes()->End()->Data();
        if(!quote->Price()->Equal(4, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->SymbolsCount() != 1)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
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

        quote = obi->AggregatedSellQuotes()->End()->Data();
        if(!quote->Price()->Equal(4, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item4;
        item4->RptSeq = 5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedSellQuotes()->Count() != 3)
            throw;

        if(!obi->AggregatedSellQuotes()->Item(0)->Price()->Equal(2, -2))
            throw;
        if(!obi->AggregatedSellQuotes()->Item(1)->Price()->Equal(3, -2))
            throw;
        if(!obi->AggregatedSellQuotes()->Item(2)->Price()->Equal(4, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item3;
        item3->RptSeq = 6;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedSellQuotes()->Count() != 2)
            throw;
        if(!obi->AggregatedSellQuotes()->Item(0)->Price()->Equal(3, -2))
            throw;
        if(!obi->AggregatedSellQuotes()->Item(1)->Price()->Equal(4, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item2;
        item2->RptSeq = 7;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedSellQuotes()->Count() != 1)
            throw;
        if(!obi->AggregatedSellQuotes()->Item(0)->Price()->Equal(3, -2))
            throw;

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item1;
        item1->RptSeq = 8;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;

        obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedSellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi2 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(!obi2->AggregatedSellQuotes()->Item(0)->Price()->Equal(2, -2))
            throw;
        if(!obi2->AggregatedSellQuotes()->Item(1)->Price()->Equal(25, -3))
            throw;
        if(!obi2->AggregatedSellQuotes()->Item(2)->Price()->Equal(3, -2))
            throw;
        if(!obi2->AggregatedSellQuotes()->Item(3)->Price()->Equal(4, -2))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 24, -3, 1, 3, mduaChange, mdetSellQuote, 222222, 5);

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item5;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);

        QuoteInfo *qt1 = obi->AggregatedSellQuotes()->Item(0);
        QuoteInfo *qt2 = obi->AggregatedSellQuotes()->Item(1);
        QuoteInfo *qt3 = obi->AggregatedSellQuotes()->Item(2);
        QuoteInfo *qt4 = obi->AggregatedSellQuotes()->Item(3);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
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
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        this->incForts->OrderBookForts()->Clear();
        if(this->incForts->OrderBookForts()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi->AggregatedSellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = this->m_helper->CreateFortsDefaultIncrementalRefreshMessageInfo();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 3, -2, 100, mduaAdd, mdetSellQuote, 111111, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 4, -2, 100, mduaAdd, mdetSellQuote, 222222, 2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 2, -2, 100, mduaAdd, mdetSellQuote, 333333, 3);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 25, -3, 100, mduaAdd, mdetSellQuote, 444444, 4);

        info->MDEntriesCount = 4;
        info->MDEntries[0] = item1;
        info->MDEntries[1] = item2;
        info->MDEntries[2] = item3;
        info->MDEntries[3] = item4;

        this->incForts->OnIncrementalRefresh_FORTS_OBR(info);

        FortsDefaultSnapshotMessageInfo *info2 = this->m_helper->CreateFortsSnapshotInfo("t1s2", 121212);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem1 = this->m_helper->CreateFortsOBSItemInfo(7,-2, 1, 2, mdetSellQuote, "e7");
        FortsDefaultSnapshotMessageMDEntriesItemInfo *newItem2 = this->m_helper->CreateFortsOBSItemInfo(8,-2, 1, 2, mdetSellQuote, "e8");

        info2->MDEntriesCount = 2;
        info2->MDEntries[0] = newItem1;
        info2->MDEntries[1] = newItem2;

        this->incForts->OrderBookForts()->ObtainSnapshotItemForts(info2);
        this->incForts->OrderBookForts()->ProcessSnapshot(info2);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi3 = this->incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(obi3->AggregatedSellQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(121212, 0);
        if(obi->AggregatedSellQuotes()->Count() != 2)
            throw;

        QuoteInfo *qt1 = obi->AggregatedSellQuotes()->Start()->Data();
        QuoteInfo *qt2 = obi->AggregatedSellQuotes()->Start()->Next()->Data();

        if(!qt1->Price()->Equal(7, -2))
            throw;
        if(!qt2->Price()->Equal(8, -2))
            throw;
    }


    void Test_OnIncrementalRefresh_FORTS_OBR_Aggregated() {
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Add_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Remove_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Change_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change_Aggregated();
        printf("OLR CURR Test_Clear_Aggregated\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes_Aggregated() {
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes_Aggregated();
        printf("OLR CURR Test_Clear_SellQuotes_Aggregated\n");
        Test_Clear_SellQuotes();
    }

    void Test_Aggregation_Logic() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = this->m_table->Symbol(0)->Session(0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 100, 0, 200, 0, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, 111111, 1);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 200)
            throw;

        info = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 100, 0, 100, 0, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, 222222, 2);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 300)
            throw;

        info = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 100, 0, 50, 0, MDUpdateAction::mduaDelete, MDEntryType::mdetBuyQuote, 222222, 3);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 200)
            throw;

        info = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 100, 0, 50, 0, MDUpdateAction::mduaChange, MDEntryType::mdetBuyQuote, 111111, 4);
        item->ProcessIncrementalMessage(info);

        if(item->AggregatedBuyQuotes()->Count() != 1)
            throw;
        if(!item->AggregatedBuyQuotes()->Item(0)->Price()->Equal(100, 0))
            throw;
        if(item->AggregatedBuyQuotes()->Item(0)->Size() != 50)
            throw;
    }

    void Test_Aggregated() {
        this->m_helper->SetFortsMode();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Aggregated();
        printf("OLR CURR Test_OnFullRefresh_OBS_CURR\n");
        Test_OnFullRefresh_OBS_CURR_Aggregated();
        printf("OLR CURR Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes_Aggregated();
        printf("OLR CURR Test_OnFullRefresh_OBS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OBS_CURR_SellQuotes_Aggregated();
        printf("OLR CURR Test_Aggregation_Logic\n");
        Test_Aggregation_Logic();
    }
    */
    
    
    void Test() {
        TestDefaults();
        TestStringIdComparer();
        TestInfoAndItemInfoUsageAndAllocationCurr();
        Test_OLR_CURR();
        //Test_Aggregated();
        TestOrderTableItem();
        TestConnection();
    }
};

#endif

#endif //HFT_ROBOT_FORTSORDERBOOKTESTER_H
