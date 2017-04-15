//
// Created by root on 19.03.17.
//

#ifndef HFT_ROBOT_FORTSORDERBOOKTESTER_H
#define HFT_ROBOT_FORTSORDERBOOKTESTER_H

#include "../Settings.h"

#ifdef TEST
#define USE_SKIP_LIST

#include "../Feeds/FeedConnection.h"
#include "../Feeds/Forts/FortsFeeds.h"
#include "TestMessagesHelper.h"
#include "../MarketData/OrderBookInfo.h"
#include "../Fast/FastProtocolManager.h"
#include <stdarg.h>
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
        this->idfForts->AddConnectionToRecvSymbol(this->incForts);
        this->incForts->SetSecurityDefinition(this->idfForts);
        this->incForts->OrderBookForts()->InitSymbols(10, 10);
        this->incForts->SetMaxLostPacketCountForStartSnapshot(1);
        this->incForts->SetSymbolManager(this->idfForts->GetSymbolManager());
        this->snapForts->SetSymbolManager(this->idfForts->GetSymbolManager());
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
        this->ClearSymbols();
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
        quote = obi->BuyQuotes()->Item(0);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;
        if(obi->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 3)
            throw;
        if(obi->BuyQuotes()->Item(1)->MDEntryID != 111111)
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

        quote = obi->BuyQuotes()->Item(0);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->BuyQuotes()->Item(1);
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

        quote = obi->BuyQuotes()->Item(0);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 444444)
            throw;

        quote = obi->BuyQuotes()->Item(3);
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
        if(obi->BuyQuotes()->Item(0)->MDEntryID != 222222)
            throw;
        if(obi->BuyQuotes()->Item(1)->MDEntryID != 111111)
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
        if(obi->BuyQuotes()->Item(0)->MDEntryID != 222222)
            throw;
        if(obi->BuyQuotes()->Item(1)->MDEntryID != 111111)
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
        if(obi2->BuyQuotes()->Item(0)->MDEntryID != 222222)
            throw;
        if(obi2->BuyQuotes()->Item(1)->MDEntryID != 111111)
            throw;
        if(obi2->BuyQuotes()->Item(2)->MDEntryID != 444444)
            throw;
        if(obi2->BuyQuotes()->Item(3)->MDEntryID != 333333)
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
        if(qt2->MDEntryID != 444444)
            throw;
        if(qt3->MDEntryID != 222222)
            throw;
        if(qt4->MDEntryID != 333333)
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

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemByIndex(0, 0);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("t1s2", 121212);

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

        if(qt2->MDEntryID != 777777)
            throw;
        if(qt1->MDEntryID != 888888)
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
        if(qt2->MDEntrySize != 100)
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
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

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 111111)
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 222222)
            throw;

        quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(quote->MDEntrySize != 100)
            throw;
        if(quote->MDEntryID != 333333)
            throw;

        quote = obi->SellQuotes()->Item(1);
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

        if(obi->SellQuotes()->Item(1)->MDEntryID != 111111)
            throw;
        if(obi->SellQuotes()->Item(2)->MDEntryID != 222222)
            throw;
        if(obi->SellQuotes()->Item(0)->MDEntryID != 333333)
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
        if(obi2->SellQuotes()->Item(2)->MDEntryID != 111111)
            throw;
        if(obi2->SellQuotes()->Item(3)->MDEntryID != 222222)
            throw;
        if(obi2->SellQuotes()->Item(0)->MDEntryID != 333333)
            throw;
        if(obi2->SellQuotes()->Item(1)->MDEntryID != 444444)
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
        if(qt1->MDEntryID != 333333)
            throw;
        if(qt2->MDEntryID != 222222)
            throw;
        if(qt3->MDEntryID != 444444)
            throw;
        if(qt4->MDEntryID != 111111)
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

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemByIndex(0);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("t1s2", 121212);

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
        if(qt1->MDEntrySize != 100)
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_FORTS_OBR() {
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Add\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Remove\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Change\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change();
        printf("OBR FORTS Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes() {
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes();
        printf("OBR FORTS Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OLR_CURR() {
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR\n");
        Test_OnIncrementalRefresh_FORTS_OBR();
        printf("OBR FORTS Test_OnFullRefresh_OLS_CURR\n");
        Test_OnFullRefresh_OLS_CURR();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes();
        printf("OBR FORTS Test_OnFullRefresh_OLS_CURR_SellQuotes\n");
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
        HashTable::Default->Clear();
    }

    void TestTable_AfterClear() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 111111);
        item->RptSeq = 1;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 222222);
        item2->RptSeq = 2;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 333333);
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item, 0);
        this->m_table->ProcessIncremental(item2, 0);
        this->m_table->ProcessIncremental(item3, 0);

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *tableItem = this->m_table->GetItemBySecurityId(111111, 0);
        if(tableItem->EntriesQueue()->MaxIndex() != 1) // 3 is empty and 4 has value
            throw;
        this->m_table->Clear();
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
    }

    void TestTable_CorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item1 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 8, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 111111, 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item2 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 9, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 222222, 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 10, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 333333, 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 11, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 444444, 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item5 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 12, 1, 80, MDUpdateAction::mduaAdd,
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

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item3 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 9, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 333333, 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0))
            throw;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item4 = this->m_helper->CreateFortsOBRItemInfo("symbol1", 111111, 10, 1, 80, MDUpdateAction::mduaAdd,
                                                           MDEntryType::mdetBuyQuote, 444444, 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0))
            throw;

        FortsDefaultSnapshotMessageInfo *info1 = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info1->MDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->MDEntries[0] = this->m_helper->CreateFortsOBSItemInfo(11, 1, 80, MDEntryType::mdetBuyQuote, 222222);

        FortsDefaultSnapshotMessageInfo *info2 = this->m_helper->CreateFortsSnapshotInfo("symbol1", 111111);
        info2->MDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->MDEntries[0] = this->m_helper->CreateFortsOBSItemInfo(12, 1, 80, MDEntryType::mdetBuyQuote, 222222);

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

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay, bool checkPacketsCleared) {
        this->m_helper->SendMessages(fci, fcs, inc, snap, delay);
        if(checkPacketsCleared)
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 100, 0, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 200, 0, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 300, 0, 1),
                                     }, 1),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 444444, 4, 400, 0, 1),
                                     }, 1)
        }, 3);


        if(!incForts->ListenIncremental_Forts_Core())
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
        this->snapForts->Start();

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 100, 0, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 200, 0, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 4, 400, 0, 1),
                                     }, 1)
        }, 2);
        if(!incForts->ListenIncremental_Forts_Core())
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 444444, 3, 300, 0, 1),
                                     }, 1)
        }, 1);

        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->snapForts->Start();

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 100, 0, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 200, 0, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 500, 0, 1),
                                     }, 1)
        }, 2);
        if(!incForts->ListenIncremental_Forts_Core())
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 300, 0, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 444444, 4, 400, 0, 1),
                                     }, 2)
        }, 1);

        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->snapForts->Start();

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 100, 0, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 200, 0, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 500, 0, 1),
                                     }, 1)
        }, 2);
        if(!incForts->ListenIncremental_Forts_Core())
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 300, 0, 1),
                                     }, 1)
        }, 1);

        if(!incForts->ListenIncremental_Forts_Core())
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 4, 400, 0, 1),
                                     }, 1)
        }, 1);

        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

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
        this->snapForts->Start();

        SendMessages(incForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 111111, 1, 100, 0, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 222222, 2, 200, 0, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 555555, 5, 500, 0, 1),
                                     }, 1)
        }, 2);
        if(!incForts->ListenIncremental_Forts_Core())
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 4, 400, 0, 1),
                                     }, 1)
        }, 1);

        if(!incForts->ListenIncremental_Forts_Core())
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
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", 111111, 333333, 3, 300, 0, 1),
                                     }, 1)
        }, 1);

        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

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
        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = incForts->OrderBookForts()->GetItemBySecurityId(111111, 0);
        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incForts->m_waitTimer->ElapsedMilliseconds() < incForts->WaitLostIncrementalMessageMaxTimeMs());
        if(!incForts->ListenIncremental_Forts_Core())
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

        snapForts->ListenSnapshot(); // activate timer 2 when first time no messages recv
        //no messages
        while(snapForts->m_waitTimer->ElapsedMilliseconds(2) <= snapForts->WaitAnyPacketMaxTimeMs - 50) {
            if(!snapForts->m_waitTimer->Active())
                throw;
            if(!snapForts->ListenSnapshot())
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

        if(!snapForts->ListenSnapshot()) // reconnect
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
            if(!snapForts->ListenSnapshot())
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

        if(!snapForts->ListenSnapshot())
            throw; // nothing should be happens
    }

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 7, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 8, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 5)
        }, 1);

        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 9)
            throw;
        if(snapForts->m_endMsgSeqNum != 8)
            throw;
        if(snapForts->m_snapshotRouteFirst != 8)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(!snapForts->ListenSnapshot_Core())
            throw;

        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;

        if(snapForts->m_startMsgSeqNum != 9)
            throw;
        if(snapForts->m_endMsgSeqNum != 8)
            throw;
        if(snapForts->m_snapshotRouteFirst != 8)
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;
    }

    // there is no route first field in FORTS messages
    // but msgSeq = 1 is route firts, so in this test msgSeq = 2
    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);

        incForts->StartListenSnapshot();

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 2)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_nextFortsSnapshotRouteFirst != -1) // we do not know what message is route firts - until we receive last fragment
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 4)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_nextFortsSnapshotRouteFirst != -1) // we do not know what message is route firts - until we receive last fragment
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 4, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 5, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 2);

        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 6)
            throw;
        if(snapForts->m_endMsgSeqNum != 5)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_nextFortsSnapshotRouteFirst != 6) // we do not know what message is route firts - until we receive last fragment
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        SendMessages(snapForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 6, "symbol1", 111111, false, false, // a-ha we received last fragment
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 7, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 2);

        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 8)
            throw;
        if(snapForts->m_endMsgSeqNum != 7)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_nextFortsSnapshotRouteFirst != 8) // we do not know next route firts but it should remain prev route first
            throw;
        if(!snapForts->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(!snapForts->ListenSnapshot_Core())
            throw;
        if(!snapForts->ListenSnapshot_Core())
            throw;

        if(snapForts->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapForts->m_startMsgSeqNum != 8)
            throw;
        if(snapForts->m_endMsgSeqNum != 7)
            throw;
        if(snapForts->m_snapshotRouteFirst != -1)
            throw;
        if(snapForts->m_nextFortsSnapshotRouteFirst != 8) // we do not know next route firts but it should remain prev route first
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

        if(!snapForts->ListenSnapshot_Core())
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

        snapForts->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        snapForts->ListenSnapshot_Core();

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
            snapForts->ListenSnapshot_Core();
            if(!snapForts->m_waitTimer->Active(1))
                break;
        }

        snapForts->ListenSnapshot_Core();
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

        snapForts->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4)
        }, 1);

        if(!snapForts->ListenSnapshot_Core())
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
            if(!snapForts->ListenSnapshot_Core())
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

        if(!snapForts->ListenSnapshot_Core())
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
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 2, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111, 100),
                                             new TestTemplateItemInfo(222222, 200),
                                     }, 2, 4)
        }, 1);

        snapForts->ListenSnapshot_Core();
        SendMessages(snapForts, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111, 300),
                                             new TestTemplateItemInfo(222222, 400),
                                     }, 2, 5)
        }, 1);
        if(snapForts->m_startMsgSeqNum != 3)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
            throw;

        snapForts->ListenSnapshot_Core();
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
        if(snapForts->m_startMsgSeqNum != 4)
            throw;
        if(snapForts->m_endMsgSeqNum != 3)
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
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 6, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 3)
        } , 1); // for route firts
        snapForts->ListenSnapshot_Core();

        SendMessages(snapForts, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 7, "symbol1", 111111, true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 9, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(222222),
                                     }, 2, 6)
        }, 2);

        if(snapForts->Packet(8)->m_address != 0)
            throw;
        if(snapForts->m_startMsgSeqNum != 7)
            throw;
        if(snapForts->m_endMsgSeqNum != 9)
            throw;
        if(snapForts->m_waitTimer->Active(1))
            throw;

        snapForts->ListenSnapshot_Core();
        if(snapForts->m_waitTimer->Active(1))
            throw;

        snapForts->ListenSnapshot_Core();

        if(!snapForts->m_waitTimer->Active(1))
            throw;
        if(snapForts->m_startMsgSeqNum != 8)
            throw;
        if(snapForts->m_snapshotRouteFirst != 7)
            throw;
        if(snapForts->m_snapshotLastFragment != -1)
            throw;

        snapForts->ListenSnapshot_Core();
        if(!snapForts->m_waitTimer->Active(1))
            throw;
        while(snapForts->m_waitTimer->ElapsedMilliseconds(1) <= snapForts->WaitSnapshotMaxTimeMs())
            snapForts->ListenSnapshot_Core();

        snapForts->ListenSnapshot_Core();
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
                                             new TestTemplateItemInfo("symbol1", 111111, 111111, 1),
                                             new TestTemplateItemInfo("symbol2", 222222, 111111, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", 111111, 111111, 4),
                                             new TestTemplateItemInfo("symbol2", 222222, 111111, 4),
                                     }, 2)
        }, 2);

        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        if(incForts->OrderBookForts()->UsedItemCount() != 2)
            throw;

        if(!incForts->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incForts->m_waitTimer->ElapsedMilliseconds() < incForts->WaitLostIncrementalMessageMaxTimeMs());

        SendMessages(snapForts, new TestTemplateInfo*[4] { // for route firts - this message will not be applied
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 3, "symbol1", 111111, false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(111111),
                                     }, 2, 4)
        }, 1);
        if(!snapForts->ListenSnapshot_Core())
            throw;

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapForts, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fortsSnapshot, 4, "symbol1", 111111, true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(111111),
                                             new TestTemplateItemInfo(111111),
                                     }, 2, 4)
        }, 1);
        if(!snapForts->ListenSnapshot_Core())
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 222222 px 200, obr entry symbol1 sid 111111 333333 px 300, obr entry symbol2 sid 222222 111111 px 100, obr entry symbol2 sid 222222 222222 px 200",
                     "",
                     30);

        if(incForts->OrderBookForts()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incForts->OrderBookForts()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incForts->ShouldRestoreIncrementalMessages())
            throw;
        if(this->BuyQuotes(0)->Count() != 2)
            throw;
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 300)
            throw;
        if(this->BuyQuotes(0)->Item(1)->MDEntryPx.Mantissa != 100)
            throw;
        if(this->BuyQuotes(1)->Count() != 2)
            throw;
        if(this->BuyQuotes(1)->Item(0)->MDEntryPx.Mantissa != 200)
            throw;
        if(this->BuyQuotes(1)->Item(1)->MDEntryPx.Mantissa != 100)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol3", 333333);

        if(snapForts->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, hbeat",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, hbeat, hbeat",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, hbeat, hbeat, hbeat",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, wait_snap",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, wait_snap, obr entry symbol1 sid 111111 333333,       hbeat,                                             hbeat",
                     "                                                                                                        obs begin symbol3 sid 333333 rpt 1, obs symbol3 rpt 1 entry symbol3 sid 333333 111111 px 100, obs symbol3 rpt 1 end",
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
                     "obs begin symbol1 sid 111111 rpt 1, obs symbol1 rpt 1 entry symbol1 sid 111111 111111, obs symbol1 rpt 1 end",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, wait_snap, "
                             "obr entry symbol1 sid 111111 333333 px 300,                                    hbeat,                                                                         hbeat",
                             "obs begin symbol3 sid 333333 rpt 1 end entry symbol3 sid 333333 111111 px 100, obs begin symbol1 sid 111111 rpt 2 end entry symbol1 sid 111111 111111 px 100, hbeat, obs begin symbol2 sid 222222 rpt 2 end entry symbol2 sid 222222 111111 px 100",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, wait_snap, obr entry symbol1 sid 111111 333333 px 300,                                    obr entry symbol2 sid 222222 111111 px 100,                                    obr entry symbol2 sid 222222 222222 px 200",
                     "                                                                                                        obs begin symbol3 sid 333333 rpt 1 end entry symbol3 sid 333333 111111 px 100, obs begin symbol1 sid 111111 rpt 2 end entry symbol1 sid 111111 111111 px 100, obs begin symbol2 sid 222222 rpt 2 end entry symbol2 sid 222222 111111 px 100 skip_if_suspend",
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
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 300)
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
                     "obr entry symbol1 sid 111111 111111 px 100, obr entry symbol1 sid 111111 222222 px 200, obr entry symbol1 sid 111111 333333 px 300, lost hbeat, wait_snap, hbeat",
                     "                                                                                                                                                           obs begin symbol1 sid 111111 rpt 1 entry symbol1 sid 111111 111111 px 100 end",
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
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 300)
            throw;
        if(this->BuyQuotes(0)->Item(1)->MDEntryPx.Mantissa != 200)
            throw;
        if(this->BuyQuotes(0)->Item(2)->MDEntryPx.Mantissa != 100)
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
                     "obr entry symbol1 sid 111111 111111 px 100, "
                             "obr entry symbol1 sid 111111 222222 px 200, "
                             "lost obr entry symbol1 sid 111111 333333 px 300, "
                             "obr entry symbol1 sid 111111 444444 px 400, "
                             "lost obr entry symbol1 sid 111111 555555 px 500, "
                             "obr entry symbol1 sid 111111 666666 px 600, "
                             "wait_snap",
                     "hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, obs begin symbol1 sid 111111 rpt 4 entry symbol1 sid 111111 444444 px 400 end",
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
                     "obr entry symbol1 sid 111111 111111 px 100, "
                             "obr entry symbol1 sid 111111 222222 px 200, "
                             "lost obr entry symbol1 sid 111111 333333 px 300, "
                             "obr entry symbol1 sid 111111 444444 px 400, "
                             "lost obr entry symbol1 sid 111111 555555 px 500, "
                             "obr entry symbol1 sid 111111 666666 px 600, "
                             "wait_snap",
                     "obs begin symbol1 sid 111111 rpt 5 entry symbol1 sid 111111 555555 px 500 end",
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
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 600)
            throw;
        if(this->BuyQuotes(0)->Item(1)->MDEntryPx.Mantissa != 500)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incForts->WaitLostIncrementalMessageMaxTimeMs(500);
        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111 px 100, "
                             "obr entry symbol1 sid 111111 222222 px 200, "
                             "lost obr entry symbol1 sid 111111 333333 px 300, "
                             "obr entry symbol1 sid 111111 444444 px 400, "
                             "lost obr entry symbol1 sid 111111 555555 px 500, "
                             "obr entry symbol1 sid 111111 666666 px 600, "
                             "wait_snap",
                     "obs begin symbol1 sid 111111 rpt 6 entry symbol1 sid 111111 666666 px 600 end",
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
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 600)
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
                     "obr entry symbol1 sid 111111 111111, obr entry symbol2 sid 222222 111111, lost obr entry symbol1 sid 111111 222222,"
                             "wait_snap, lost obr entry symbol1 sid 111111 333333,                               obr entry symbol1 sid 111111 444444",
                     "        hbeat,     obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 end, obs symbol2 begin rpt 1 entry symbol2 sid 222222 111111 end, hbeat",
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
                     "obr entry symbol1 sid 111111 111111 px 100, "
                             "obr entry symbol2 sid 222222 111111 px 100, "
                             "lost obr entry symbol1 sid 111111 222222 px 200, "
                             "wait_snap,                                                                     lost obr entry symbol1 sid 111111 333333,                                      obr entry symbol1 sid 111111 444444, hbeat ",
                             "obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 px 200 end, obs begin symbol2 sid 222222 rpt 1 entry symbol2 sid 222222 111111 px 100 end, hbeat,                               obs begin symbol1 sid 111111 rpt 3 entry symbol1 sid 111111 333333 px 300 end",
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
                     "                                                                                                                               hbeat, hbeat, obs begin symbol1 sid 111111 rpt 0 lastmsg 0 entry symbol1 sid 111111 111111 end",
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
                     "                                                  obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 end",
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
                     "                                                  hbeat, hbeat, obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 end",
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
                     "obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222, "
                             "lost obs symbol1 rpt 2 entry symbol1 sid 111111 222222, "
                             "hbeat, "
                             "hbeat, "
                             "hbeat, "
                             "hbeat, "
                             "hbeat",
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
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol1 sid 111111 222222 px 200, wait_snap, "
                     "hbeat                                                                      hbeat,                                                  hbeat,                                                        hbeat, hbeat, hbeat, hbeat, hbeat",
                     "obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 px 200, lost obs symbol1 rpt 2 entry symbol1 sid 111111 222222, obs symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 end, obs begin symbol1 sid 111111 rpt 2 entry symbol1 sid 111111 222222 px 200 end",
                     30);
        if(this->BuyQuotes(0)->Count() != 1)
            throw;
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 200)
            throw;
        if(this->Symbol(0)->RptSeq() != 2)
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
        printf("OBR FORTS TestConnection_ClearSnapshotMessages_1\n");
        TestConnection_ClearSnapshotMessages_1();
        printf("OBR FORTS TestConnection_ClearSnapshotMessages_2\n");
        TestConnection_ClearSnapshotMessages_2();
        printf("OBR FORTS TestConnection_ClearSnapshotMessages_3\n");
        TestConnection_ClearSnapshotMessages_3();
        printf("OBR FORTS TestConnection_ClearSnapshotMessages_4\n");
        TestConnection_ClearSnapshotMessages_4();
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot() {
        printf("OBR FORTS TestConnection_EnterSnapshotMode\n");
        TestConnection_EnterSnapshotMode();
        printf("OBR FORTS TestConnection_ClearSnapshotMessages\n");
        TestConnection_ClearSnapshotMessages();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_1();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_4();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7\n");
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
                                             new TestTemplateItemInfo("symbol1", 111111, 111111, 1),
                                             new TestTemplateItemInfo("symbol2", 222222, 111111, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fortsIncremental, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", 111111, 111111, 4),
                                             new TestTemplateItemInfo("symbol2", 222222, 111111, 4),
                                     }, 2)
        }, 2);

        if(!incForts->ListenIncremental_Forts_Core())
            throw;

        this->TestTableItemsAllocator(incForts->OrderBookForts());

        incForts->OrderBookForts()->Clear();
    }

    void TestConnection() {
        printf("OBR FORTS TestConnection_AllSymbolsAreOk\n");
        TestConnection_AllSymbolsAreOk();
        printf("OBR FORTS TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("OBR FORTS TestConnection_AllSymbolsAreOkButOneMessageLost\n");
        TestConnection_AllSymbolsAreOkButOneMessageLost();
        printf("OBR FORTS TestConnection_SkipHearthBeatMessages_Incremental\n");
        TestConnection_SkipHearthBeatMessages_Incremental();
        printf("OBR FORTS TestConnection_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot();
        printf("OBR FORTS TestConnection_NotAllSymbolsAreOk\n");
        TestConnection_NotAllSymbolsAreOk();
        printf("OBR FORTS TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("OBR FORTS TestConnection_StopTimersAfterReconnect\n");
        TestConnection_StopTimersAfterReconnect();
        printf("OBR FORTS TestConnection_SnapshotSomeMessagesReceivedLater\n");
        TestConnection_SnapshotSomeMessagesReceivedLater();
        printf("OBR FORTS TestConnection_SnapshotSomeMessagesNotReceived\n");
        TestConnection_SnapshotSomeMessagesNotReceived();
        printf("OBR FORTS TestConnection_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnection_LastFragmentReceivedBeforeRouteFirst();
        printf("OBR FORTS TestConnection_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnection_RouteFirstReceived_AfterSomeDummyMessages();
        printf("OBR FORTS TestConnection_RouteFirstReceived_Empty\n");
        TestConnection_RouteFirstReceived_Empty();
        printf("OBR FORTS TestConnection_TestSnapshotNoMessagesAtAll\n");
        TestConnection_TestSnapshotNoMessagesAtAll();
        printf("OBR FORTS TestConnection_OneMessageReceived\n");
        TestConnection_OneMessageReceived();
        printf("OBR FORTS TestConnection_Clear_AfterIncremental\n");
        TestConnection_Clear_AfterIncremental();
        printf("OBR FORTS TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("OBR FORTS TestConnection_TestSnapshotCollect\n");
        TestConnection_TestSnapshotCollect();
        printf("OBR FORTS TestConnection_TestSnapshotNotCollect\n");
        TestConnection_TestSnapshotMessageLostAndTimeExpired();
        printf("OBR FORTS TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("OBR FORTS TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("OBR FORTS TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("OBR FORTS TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("OBR FORTS TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("OBR FORTS TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("OBR FORTS TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestOrderTableItem() {
        printf("OBR FORTS TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("OBR FORTS TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("OBR FORTS TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("OBR FORTS TestTable_Default\n");
        TestTable_Default();
        printf("OBR FORTS TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("OBR FORTS TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("OBR FORTS TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("OBR FORTS TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("OBR FORTS Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("OBR FORTS TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("OBR FORTS TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("OBR FORTS TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("OBR FORTS TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
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

        SymbolInfo *s = this->incForts->GetSymbolManager()->AddSymbol(info->SecurityID);
        this->incForts->SecurityDefinition()->SymbolsForts()[s->m_index] = ptr;
        this->incForts->AddSymbol(ptr, s->m_index);

        this->m_table->AddSymbol(symbol, strlen(symbol), s->m_index)->SecurityDefinitionPtr(ptr);
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
                           "obr entry symbol1 sid 111111 111111 px 100, obr entry symbol1 sid 111111 222222 px 200",
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
                           "obr entry symbol1 sid 111111 111111 px 100, obr entry symbol1 sid 111111 222222 px 200, obr entry del symbol1 sid 111111 222222 px 200",
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
                           "obr entry symbol1 sid 111111 111111 px 100, obr entry symbol1 sid 111111 222222 px 200, obr entry change symbol1 sid 111111 222222 px 200",
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
                           "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol1 sid 111111 222222 px 200, wait_snap, hbeat",
                           "                                                  obs begin symbol1 sid 111111 entry symbol1 sid 111111 222222 px 200 rpt 2 end",
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
                           "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol1 sid 111111 222222 px 200 entry symbol1 sid 111111 333333 px 300, wait_snap, hbeat",
                           "                                                                                                                                    obs begin symbol1 sid 111111 entry symbol1 sid 111111 222222 px 200 rpt 2, obs symbol1 sid 111111 entry symbol1 sid 111111 333333 px 300 end",
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
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4_1() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        if(this->incForts->m_symbolManager->SymbolCount() != 3)
            throw;
        if(this->incForts->m_symbolManager->GetSymbol(333333)->m_index != 2)
            throw;
        if(this->incForts->m_symbolManager->GetSymbol(222222)->m_index != 1)
            throw;
        if(this->incForts->m_symbolManager->GetSymbol(111111)->m_index != 0)
            throw;

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, wait_snap, obr entry symbol1 sid 111111 333333 px 300,                                  hbeat,                                                              hbeat",
                     "                                                                                                        obs begin symbol3 sid 333333 rpt 1 end entry symbol3 sid 333333 111111 px 100",
                     30);
        if(this->incForts->OrderBookForts()->Symbol(2)->Session(0)->BuyQuotes()->Count() != 1)
            throw;
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 3) // was 2
            throw;
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4_2() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol3 sid 333333 111111 px 100, wait_snap, obr entry symbol1 sid 111111 333333 px 300,                         hbeat,                                                              hbeat",
                     "                                                                                                        obs symbol3 sid 333333 begin rpt 1 end entry symbol3 sid 333333 111111 px 100, obs symbol1 sid 111111 begin rpt 2 end entry symbol1 sid 111111 111111 px 100, hbeat, obs symbol2 sid 222222 begin rpt 2 end entry symbol2 sid 222222 111111 px 100",
                     30, false);
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 4) // was 2
            throw;
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4() {
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4_1();
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4_2();
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5() {
        this->Clear();
        this->AddSymbol("symbol1", 111111);
        incForts->Start();

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111 px 100, lost obr entry symbol1 sid 111111 222222 px 200, obr entry symbol1 sid 111111 222222 px 200, wait_snap, hbeat",
                     "                                                                                                                                                    hbeat, hbeat, obs begin symbol1 sid 111111 rpt 0 lastmsg 0 entry symbol1 sid 111111 111111 px 100 end",
                     30);
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount)
            throw;
        if(incForts->OrderBookForts()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 0)
            throw;
    }

    HrPointerListLite<FortsDefaultSnapshotMessageMDEntriesItemInfo>* BuyQuotes(int symbolIndex) {
        return incForts->OrderBookForts()->Symbol(symbolIndex)->Session(0)->BuyQuotes();
    }

    OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>* Symbol(int index) {
        return incForts->OrderBookForts()->GetItemByIndex(index);
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6() {
        this->Clear();

        this->AddSymbol("symbol1", 111111);

        int prevCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        SendMessages(incForts, snapForts,
                     "obr entry symbol1 sid 111111 111111 px 100, obr entry symbol1 sid 111111 222222 px 200, obr entry symbol1 sid 111111 333333 px 300, lost hbeat, wait_snap, hbeat",
                     "                                                                                                                                                           obs begin symbol1 sid 111111 rpt 1 entry symbol1 sid 111111 111111 px 100 end",
                     50);
        int newCount = this->snapForts->m_fastProtocolManager->m_fortsDefaultSnapshotMessageMDEntriesItems->Count();
        if(newCount != prevCount + 3)
            throw;
        if(this->BuyQuotes(0)->Count() != 3)
            throw;
        if(this->BuyQuotes(0)->Item(0)->MDEntryPx.Mantissa != 300)
            throw;
        if(this->BuyQuotes(0)->Item(1)->MDEntryPx.Mantissa != 200)
            throw;
        if(this->BuyQuotes(0)->Item(2)->MDEntryPx.Mantissa != 100)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationCurr() {
        this->m_helper->SetFortsMode();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_1();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_2();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_3();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_4();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Inc_5();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_1();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_2();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_3();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_4();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_5();
        printf("OBR FORTS TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationCurr_Snap_6();
    }

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
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FortsDefaultSnapshotMessageMDEntriesItemInfo *quote = obi->BuyQuotes()->Item(0);
        Decimal price(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
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
        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
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

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;

        quote = obi->BuyQuotes()->Last()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
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

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
            throw;

        quote = obi->BuyQuotes()->Last()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(quote->MDEntrySize != 100)
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
        if(!ob->BuyQuotes()->Item(0)->MDEntryPx.Equal(4, -2))
            throw;
        if(!ob->BuyQuotes()->Item(1)->MDEntryPx.Equal(3, -2))
            throw;
        if(!ob->BuyQuotes()->Item(2)->MDEntryPx.Equal(25, -3))
            throw;
        if(!ob->BuyQuotes()->Item(3)->MDEntryPx.Equal(2, -2))
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
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!obi->BuyQuotes()->Item(0)->MDEntryPx.Equal(4, -2))
            throw;
        if(!obi->BuyQuotes()->Item(1)->MDEntryPx.Equal(3, -2))
            throw;
        if(!obi->BuyQuotes()->Item(2)->MDEntryPx.Equal(2, -2))
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
        if(!obi->BuyQuotes()->Item(0)->MDEntryPx.Equal(4, -2))
            throw;
        if(!obi->BuyQuotes()->Item(1)->MDEntryPx.Equal(3, -2))
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
        if(!obi->BuyQuotes()->Item(0)->MDEntryPx.Equal(3, -2))
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
        if(!obi2->BuyQuotes()->Item(0)->MDEntryPx.Equal(4, -2))
            throw;
        if(!obi2->BuyQuotes()->Item(1)->MDEntryPx.Equal(3, -2))
            throw;
        if(!obi2->BuyQuotes()->Item(2)->MDEntryPx.Equal(25, -3))
            throw;
        if(!obi2->BuyQuotes()->Item(3)->MDEntryPx.Equal(2, -2))
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

        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemByIndex(0);

        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->incForts->OrderBookForts()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!qt1->MDEntryPx.Equal(3, -2))
            throw;
        if(!qt2->MDEntryPx.Equal(25, -3))
            throw;
        if(!qt3->MDEntryPx.Equal(24, -3))
            throw;
        if(!qt4->MDEntryPx.Equal(2, -2))
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
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("t1s2", 121212);

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

        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FortsDefaultSnapshotMessageMDEntriesItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
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
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = this->incForts->OrderBookForts()->GetItemBySecurityId(111111);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FortsDefaultSnapshotMessageMDEntriesItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
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
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
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
        obi = this->incForts->OrderBookForts()->GetItemByIndex(0);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;

        quote = obi->SellQuotes()->Last()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
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

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;

        quote = obi->SellQuotes()->Last()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
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
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!obi->SellQuotes()->Item(0)->MDEntryPx.Equal(2, -2))
            throw;
        if(!obi->SellQuotes()->Item(1)->MDEntryPx.Equal(3, -2))
            throw;
        if(!obi->SellQuotes()->Item(2)->MDEntryPx.Equal(4, -2))
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
        if(!obi->SellQuotes()->Item(0)->MDEntryPx.Equal(3, -2))
            throw;
        if(!obi->SellQuotes()->Item(1)->MDEntryPx.Equal(4, -2))
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
        if(!obi->SellQuotes()->Item(0)->MDEntryPx.Equal(3, -2))
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
        if(!obi2->SellQuotes()->Item(0)->MDEntryPx.Equal(2, -2))
            throw;
        if(!obi2->SellQuotes()->Item(1)->MDEntryPx.Equal(25, -3))
            throw;
        if(!obi2->SellQuotes()->Item(2)->MDEntryPx.Equal(3, -2))
            throw;
        if(!obi2->SellQuotes()->Item(3)->MDEntryPx.Equal(4, -2))
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
        if(!qt1->MDEntryPx.Equal(2, -2))
            throw;
        if(!qt2->MDEntryPx.Equal(24, -3))
            throw;
        if(!qt3->MDEntryPx.Equal(25, -3))
            throw;
        if(!qt4->MDEntryPx.Equal(3, -2))
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
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes_Aggregated() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("t1s2", 121212);

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

        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }


    void Test_OnIncrementalRefresh_FORTS_OBR_Aggregated() {
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Add_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add_Aggregated();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Remove_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove_Aggregated();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Change_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change_Aggregated();
        printf("OBR FORTS Test_Clear_Aggregated\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes_Aggregated() {
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Add_SellQuotes_Aggregated();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Remove_SellQuotes_Aggregated();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes_Aggregated\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Change_SellQuotes_Aggregated();
        printf("OBR FORTS Test_Clear_SellQuotes_Aggregated\n");
        Test_Clear_SellQuotes();
    }

    void Test_Aggregated() {
        this->m_helper->SetFortsMode();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR\n");
        Test_OnIncrementalRefresh_FORTS_OBR_Aggregated();
        printf("OBR FORTS Test_OnFullRefresh_OBS_CURR\n");
        Test_OnFullRefresh_OBS_CURR_Aggregated();
        printf("OBR FORTS Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes\n");
        Test_OnIncrementalRefresh_FORTS_OBR_SellQuotes_Aggregated();
        printf("OBR FORTS Test_OnFullRefresh_OBS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OBS_CURR_SellQuotes_Aggregated();
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreatePerformanceItem(int price) {
        AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo> *list = new AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>(2, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo* item = list->NewItem();
        item->MDEntryPx.Set(price, 0);
        item->MDEntryType[0] = MDEntryType::mdetBuyQuote;
        item->MDEntryTypeLength = 1;
        item->MDEntryID = price;
        return item;
    }

#ifdef USE_SKIP_LIST
template <typename T>
    void TestLevelsDescending(HrPointerListLite<T> *list) {

        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            if(node == list->End())
                break;
            if(node->Next5()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                throw;
            if(node != list->Start()) {
                if(node->Prev4()->Data()->MDEntryPx.Mantissa < node->Data()->MDEntryPx.Mantissa)
                    throw;
                if(node->Next4()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                    throw;
            }

            node = node->Next5();
        }

        node = list->Start();
        while(true) {
            if(node == list->End())
                break;
            if(node->Next4()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                throw;
            if(node != list->Start()) {
                if(node->Prev3()->Data()->MDEntryPx.Mantissa < node->Data()->MDEntryPx.Mantissa)
                    throw;
                if(node->Next3()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                    throw;
            }

            node = node->Next4();
        }

        node = list->Start();
        while(true) {
            if(node == list->End())
                break;
            if(node->Next3()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                throw;
            if(node != list->Start()) {
                if(node->Prev2()->Data()->MDEntryPx.Mantissa < node->Data()->MDEntryPx.Mantissa)
                    throw;
                if(node->Next2()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                    throw;
            }

            node = node->Next3();
        }

        node = list->Start();
        while(true) {
            if(node == list->End())
                break;
            if(node->Next2()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                throw;
            if(node != list->Start()) {
                if(node->Prev()->Data()->MDEntryPx.Mantissa < node->Data()->MDEntryPx.Mantissa)
                    throw;
                if(node->Next()->Data()->MDEntryPx.Mantissa > node->Data()->MDEntryPx.Mantissa)
                    throw;
            }

            node = node->Next2();
        }
    }

    void TestPerformance(int itemsCount) {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *obi = new OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        obi->ListMode(ListType::ltSkipList);
        obi->BuyQuoteManager()->SetDebugFastRandSeed(2006221698);
        obi->SymbolInfo(new MarketSymbolInfo<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>>());
        obi->BuyQuoteManager()->SetDebugLevel(0);
        FortsDefaultSnapshotMessageMDEntriesItemInfo **items = new FortsDefaultSnapshotMessageMDEntriesItemInfo*[itemsCount];
        int startMantissa = 1000;
        for(int i = 0; i < itemsCount * 3; i++) {
            int val = rand() % itemsCount;
            FortsDefaultSnapshotMessageMDEntriesItemInfo *item = CreatePerformanceItem(startMantissa + val * 5);
            items[i] = item;
            obi->AddBuyQuote(item);
            this->TestLevelsDescending(obi->BuyQuotes());
            if(obi->BuyQuotes()->Count() == itemsCount)
                break;
        }
        printf("items count = %d\n", obi->BuyQuotes()->Count());

        printf("%s\n", this->GetLevelMap(obi->BuyQuotes(), 5));
        printf("%s\n", this->GetLevelMap(obi->BuyQuotes(), 4));
        printf("%s\n", this->GetLevelMap(obi->BuyQuotes(), 3));
        printf("%s\n", this->GetLevelMap(obi->BuyQuotes(), 2));
        printf("%s\n", this->GetLevelMap(obi->BuyQuotes(), 1));

        Stopwatch *w = new Stopwatch();
        int count = 30000;

        itemsCount = obi->BuyQuotes()->Count();
        int index[7] = { itemsCount / 10, itemsCount / 5, itemsCount / 3, itemsCount / 2, itemsCount / 4 * 3, itemsCount / 5 * 4, itemsCount / 10 * 9};

        for(int i = 0; i < 7; i++) {
            FortsDefaultSnapshotMessageMDEntriesItemInfo *it = obi->BuyQuotes()->Item(index[i]);
            int price = it->MDEntryPx.Mantissa + 1;
            FortsDefaultSnapshotMessageMDEntriesItemInfo *item50 = CreatePerformanceItem(price);
            obi->ListMode(ListType::ltSkipList);
            w->Start();
            for (int i = 0; i < count; i++) {
                HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *ptr = obi->AddBuyQuote(item50);
                obi->RemoveBuyQuote(ptr->Data());

                if(obi->BuyQuotes()->Count() != itemsCount)
                    throw;
            }
            UINT64 en = w->ElapsedNanoseconds();
            w->Stop();

            if(obi->BuyQuotes()->Count() != itemsCount)
                throw;

            obi->ListMode(ListType::ltSimple);
            w->Start();
            for (int i = 0; i < count; i++) {
                HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *ptr = obi->AddBuyQuote(item50);
                obi->RemoveBuyQuote(ptr->Data());
            }
            UINT64 en2 = w->ElapsedNanoseconds();
            w->Stop();

            printf("performance %d items: insert before %d. ave Ex = %" PRIu64 "  vs  Sm = %" PRIu64 " nanosec, optimization = %g times\n", itemsCount, index[i], en / count, en2 / count, ((double)en2) / en);
        }
    }

    void TestPerformance() {
        TestPerformance(1000);
        TestPerformance(800);
        TestPerformance(600);
        TestPerformance(400);
        TestPerformance(200);
        TestPerformance(100);
        TestPerformance(50);
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateHrItem(int price) {
        AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo> *list = new AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>(2, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo* item = list->NewItem();
        item->MDEntryType[0] = MDEntryType::mdetBuyQuote;
        item->MDEntryPx.Set(price, 0);
        item->MDEntryID = price;
        return item;
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateHrItem(int price, int entryId) {
        AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo> *list = new AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>(2, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo* item = list->NewItem();
        item->MDEntryType[0] = MDEntryType::mdetBuyQuote;
        item->MDEntryPx.Set(price, 0);
        item->MDEntryID = entryId;
        return item;
    }

    OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *CreateOrderBook() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = new OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        MarketSymbolInfo<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>> *s = new MarketSymbolInfo<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>>();
        item->SymbolInfo(s);
        item->ListMode(ListType::ltSkipList);
        return item;
    }

    void TestHrAddBuyQuote1() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        if(item->BuyQuotes()->Start() == 0)
            throw;
        if(item->BuyQuotes()->Count() != 1)
            throw;
        if(item->BuyQuotes()->Start()->Data()->MDEntryPx.Mantissa != 100)
            throw;
    }

    void TestHrAddBuyQuote2() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(90));
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(item->BuyQuotes()->Start()->Data()->MDEntryPx.Mantissa != 100)
            throw;
        if(item->BuyQuotes()->End()->Data()->MDEntryPx.Mantissa != 90)
            throw;
        if(item->BuyQuotes()->Start()->Next() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next2() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next3() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next4() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next5() != item->BuyQuotes()->End())
            throw;
    }

    void TestHrAddBuyQuote3() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(110));
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(item->BuyQuotes()->Start()->Data()->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->End()->Data()->MDEntryPx.Mantissa != 100)
            throw;
        if(item->BuyQuotes()->Start()->Next() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next2() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next3() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next4() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next5() != item->BuyQuotes()->End())
            throw;
    }

    void TestHrAddBuyQuote4() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(110));

        item->SetDebugLevel(3);

        item->AddBuyQuote(CreateHrItem(120));
        if(item->BuyQuotes()->Count() != 3)
            throw;
        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 120)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 100)
            throw;

        if(item->BuyQuotes()->Start()->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Start()->Next2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Start()->Next3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Start()->Next4() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next5() != item->BuyQuotes()->End())
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != 0)
            throw;

        if(item->BuyQuotes()->End()->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->End()->Prev2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->End()->Prev3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->End()->Prev4() != item->BuyQuotes()->Start())
            throw;
        if(item->BuyQuotes()->End()->Prev5() != item->BuyQuotes()->Start())
            throw;
    }

    void TestHrAddBuyQuote5() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(110));

        item->SetDebugLevel(3);

        item->AddBuyQuote(CreateHrItem(90));
        if(item->BuyQuotes()->Count() != 3)
            throw;
        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 100)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 90)
            throw;

        if(item->BuyQuotes()->Start()->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Start()->Next2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Start()->Next3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Start()->Next4() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Start()->Next5() != item->BuyQuotes()->End())
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != item->BuyQuotes()->End())
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != 0)
            throw;

        if(item->BuyQuotes()->End()->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->End()->Prev2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->End()->Prev3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->End()->Prev4() != item->BuyQuotes()->Start())
            throw;
        if(item->BuyQuotes()->End()->Prev5() != item->BuyQuotes()->Start())
            throw;
    }

    void TestHrInsertByLevel0() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = item->BuyQuotes()->Add();

        start->AllConnect(end);
        item->BuyQuotes()->InsertByLevel(0, start, node, end);

        if(start->Next() != node)
            throw;
        if(start->Next2() != end)
            throw;
        if(start->Next3() != end)
            throw;
        if(start->Next4() != end)
            throw;
        if(start->Next5() != end)
            throw;

        if(end->Prev() != node)
            throw;
        if(end->Prev2() != start)
            throw;
        if(end->Prev3() != start)
            throw;
        if(end->Prev4() != start)
            throw;
        if(end->Prev5() != start)
            throw;

        if(node->Prev() != start)
            throw;
        if(node->Prev2() != 0)
            throw;
        if(node->Prev3() != 0)
            throw;
        if(node->Prev4() != 0)
            throw;
        if(node->Prev5() != 0)
            throw;

        if(node->Next() != end)
            throw;
        if(node->Next2() != 0)
            throw;
        if(node->Next3() != 0)
            throw;
        if(node->Next4() != 0)
            throw;
        if(node->Next5() != 0)
            throw;
    }

    void TestHrInsertByLevel1() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = item->BuyQuotes()->Add();

        start->AllConnect(end);
        item->BuyQuotes()->InsertByLevel(1, start, node, end);

        if(start->Next() != node)
            throw;
        if(start->Next2() != end)
            throw;
        if(start->Next3() != end)
            throw;
        if(start->Next4() != end)
            throw;
        if(start->Next5() != end)
            throw;

        if(end->Prev() != node)
            throw;
        if(end->Prev2() != start)
            throw;
        if(end->Prev3() != start)
            throw;
        if(end->Prev4() != start)
            throw;
        if(end->Prev5() != start)
            throw;

        if(node->Prev() != start)
            throw;
        if(node->Prev2() != 0)
            throw;
        if(node->Prev3() != 0)
            throw;
        if(node->Prev4() != 0)
            throw;
        if(node->Prev5() != 0)
            throw;

        if(node->Next() != end)
            throw;
        if(node->Next2() != 0)
            throw;
        if(node->Next3() != 0)
            throw;
        if(node->Next4() != 0)
            throw;
        if(node->Next5() != 0)
            throw;
    }

    void TestHrInsertByLevel2() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = item->BuyQuotes()->Add();

        start->AllConnect(end);
        item->BuyQuotes()->InsertByLevel(2, start, node, end);

        if(start->Next() != node)
            throw;
        if(start->Next2() != node)
            throw;
        if(start->Next3() != end)
            throw;
        if(start->Next4() != end)
            throw;
        if(start->Next5() != end)
            throw;

        if(end->Prev() != node)
            throw;
        if(end->Prev2() != node)
            throw;
        if(end->Prev3() != start)
            throw;
        if(end->Prev4() != start)
            throw;
        if(end->Prev5() != start)
            throw;

        if(node->Prev() != start)
            throw;
        if(node->Prev2() != start)
            throw;
        if(node->Prev3() != 0)
            throw;
        if(node->Prev4() != 0)
            throw;
        if(node->Prev5() != 0)
            throw;

        if(node->Next() != end)
            throw;
        if(node->Next2() != end)
            throw;
        if(node->Next3() != 0)
            throw;
        if(node->Next4() != 0)
            throw;
        if(node->Next5() != 0)
            throw;
    }

    void TestHrInsertByLevel3() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = item->BuyQuotes()->Add();

        start->AllConnect(end);
        item->BuyQuotes()->InsertByLevel(3, start, node, end);

        if(start->Next() != node)
            throw;
        if(start->Next2() != node)
            throw;
        if(start->Next3() != node)
            throw;
        if(start->Next4() != end)
            throw;
        if(start->Next5() != end)
            throw;

        if(end->Prev() != node)
            throw;
        if(end->Prev2() != node)
            throw;
        if(end->Prev3() != node)
            throw;
        if(end->Prev4() != start)
            throw;
        if(end->Prev5() != start)
            throw;

        if(node->Prev() != start)
            throw;
        if(node->Prev2() != start)
            throw;
        if(node->Prev3() != start)
            throw;
        if(node->Prev4() != 0)
            throw;
        if(node->Prev5() != 0)
            throw;

        if(node->Next() != end)
            throw;
        if(node->Next2() != end)
            throw;
        if(node->Next3() != end)
            throw;
        if(node->Next4() != 0)
            throw;
        if(node->Next5() != 0)
            throw;
    }

    void TestHrInsertByLevel4() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = item->BuyQuotes()->Add();

        start->AllConnect(end);
        item->BuyQuotes()->InsertByLevel(4, start, node, end);

        if(start->Next() != node)
            throw;
        if(start->Next2() != node)
            throw;
        if(start->Next3() != node)
            throw;
        if(start->Next4() != node)
            throw;
        if(start->Next5() != end)
            throw;

        if(end->Prev() != node)
            throw;
        if(end->Prev2() != node)
            throw;
        if(end->Prev3() != node)
            throw;
        if(end->Prev4() != node)
            throw;
        if(end->Prev5() != start)
            throw;

        if(node->Prev() != start)
            throw;
        if(node->Prev2() != start)
            throw;
        if(node->Prev3() != start)
            throw;
        if(node->Prev4() != start)
            throw;
        if(node->Prev5() != 0)
            throw;

        if(node->Next() != end)
            throw;
        if(node->Next2() != end)
            throw;
        if(node->Next3() != end)
            throw;
        if(node->Next4() != end)
            throw;
        if(node->Next5() != 0)
            throw;
    }

    void TestHrInsertByLevel5() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Add();
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = item->BuyQuotes()->Add();

        start->AllConnect(end);
        item->BuyQuotes()->InsertByLevel(5, start, node, end);

        if(start->Next() != node)
            throw;
        if(start->Next2() != node)
            throw;
        if(start->Next3() != node)
            throw;
        if(start->Next4() != node)
            throw;
        if(start->Next5() != node)
            throw;

        if(end->Prev() != node)
            throw;
        if(end->Prev2() != node)
            throw;
        if(end->Prev3() != node)
            throw;
        if(end->Prev4() != node)
            throw;
        if(end->Prev5() != node)
            throw;

        if(node->Prev() != start)
            throw;
        if(node->Prev2() != start)
            throw;
        if(node->Prev3() != start)
            throw;
        if(node->Prev4() != start)
            throw;
        if(node->Prev5() != start)
            throw;

        if(node->Next() != end)
            throw;
        if(node->Next2() != end)
            throw;
        if(node->Next3() != end)
            throw;
        if(node->Next4() != end)
            throw;
        if(node->Next5() != end)
            throw;
    }

    void TestHrInsertBuyQuote1() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->SetDebugLevel(1);
        item->AddBuyQuote(CreateHrItem(110));

        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 120)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 100)
            throw;

        if(item->BuyQuotes()->Node(0)->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next2() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(0)->Next3() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(0)->Next4() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(0)->Next5() != item->BuyQuotes()->Node(2))
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != 0)
            throw;

        if(item->BuyQuotes()->Node(1)->Prev() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev2() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Prev3() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Prev4() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Prev5() != 0)
            throw;

        if(item->BuyQuotes()->Node(2)->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev2() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev3() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev4() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev5() != item->BuyQuotes()->Node(0))
            throw;
    }

    void TestHrInsertBuyQuote2() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->SetDebugLevel(2);
        item->AddBuyQuote(CreateHrItem(110));

        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 120)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 100)
            throw;

        if(item->BuyQuotes()->Node(0)->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next3() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(0)->Next4() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(0)->Next5() != item->BuyQuotes()->Node(2))
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != 0)
            throw;

        if(item->BuyQuotes()->Node(1)->Prev() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev2() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev3() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Prev4() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Prev5() != 0)
            throw;

        if(item->BuyQuotes()->Node(2)->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev3() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev4() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev5() != item->BuyQuotes()->Node(0))
            throw;
    }

    void TestHrInsertBuyQuote3() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->SetDebugLevel(3);
        item->AddBuyQuote(CreateHrItem(110));

        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 120)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 100)
            throw;

        if(item->BuyQuotes()->Node(0)->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next4() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(0)->Next5() != item->BuyQuotes()->Node(2))
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != 0)
            throw;

        if(item->BuyQuotes()->Node(1)->Prev() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev2() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev3() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev4() != 0)
            throw;
        if(item->BuyQuotes()->Node(1)->Prev5() != 0)
            throw;

        if(item->BuyQuotes()->Node(2)->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev4() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev5() != item->BuyQuotes()->Node(0))
            throw;
    }

    void TestHrInsertBuyQuote4() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->SetDebugLevel(4);
        item->AddBuyQuote(CreateHrItem(110));

        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 120)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 100)
            throw;

        if(item->BuyQuotes()->Node(0)->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next4() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next5() != item->BuyQuotes()->Node(2))
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != 0)
            throw;

        if(item->BuyQuotes()->Node(1)->Prev() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev2() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev3() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev4() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev5() != 0)
            throw;

        if(item->BuyQuotes()->Node(2)->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev4() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev5() != item->BuyQuotes()->Node(0))
            throw;
    }

    void TestHrInsertBuyQuote5() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();
        if(item->BuyQuotes()->Start() != 0)
            throw;
        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->SetDebugLevel(5);
        item->AddBuyQuote(CreateHrItem(110));

        if(item->BuyQuotes()->Item(0)->MDEntryPx.Mantissa != 120)
            throw;
        if(item->BuyQuotes()->Item(1)->MDEntryPx.Mantissa != 110)
            throw;
        if(item->BuyQuotes()->Item(2)->MDEntryPx.Mantissa != 100)
            throw;

        if(item->BuyQuotes()->Node(0)->Next() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next4() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(0)->Next5() != item->BuyQuotes()->Node(1))
            throw;

        if(item->BuyQuotes()->Node(1)->Next() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next2() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next3() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next4() != item->BuyQuotes()->Node(2))
            throw;
        if(item->BuyQuotes()->Node(1)->Next5() != item->BuyQuotes()->Node(2))
            throw;

        if(item->BuyQuotes()->Node(1)->Prev() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev2() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev3() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev4() != item->BuyQuotes()->Node(0))
            throw;
        if(item->BuyQuotes()->Node(1)->Prev5() != item->BuyQuotes()->Node(0))
            throw;

        if(item->BuyQuotes()->Node(2)->Prev() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev2() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev3() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev4() != item->BuyQuotes()->Node(1))
            throw;
        if(item->BuyQuotes()->Node(2)->Prev5() != item->BuyQuotes()->Node(1))
            throw;
    }

    void TestRemoveBuyQuote1() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->RemoveBuyQuote(CreateHrItem(100));

        if(item->BuyQuotes()->Count() != 0)
            throw;
    }

    void AssertNextEqual(HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *next2,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *next3,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *next4,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *next5) {

        if(node->Next2() != next2)
            throw;
        if(node->Next3() != next3)
            throw;
        if(node->Next4() != next4)
            throw;
        if(node->Next5() != next5)
            throw;
    }

    void AssertPrevEqual(HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *prev2,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *prev3,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *prev4,
                   HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *prev5) {

        if(node->Prev2() != prev2)
            throw;
        if(node->Prev3() != prev3)
            throw;
        if(node->Prev4() != prev4)
            throw;
        if(node->Prev5() != prev5)
            throw;
    }

    void TestRemoveBuyQuote21() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->RemoveBuyQuote(CreateHrItem(100));

        if(item->BuyQuotes()->Count() != 1)
            throw;

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Node(0);
        if(node->Next() != 0)
            throw;
        this->AssertNextEqual(node, 0, 0, 0, 0);
        this->AssertPrevEqual(node, 0, 0, 0, 0);
    }

    void TestRemoveBuyQuote22() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));

        item->RemoveBuyQuote(CreateHrItem(120));

        if(item->BuyQuotes()->Count() != 1)
            throw;

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = item->BuyQuotes()->Node(0);
        if(node->Next() != 0)
            throw;
        this->AssertNextEqual(node, 0, 0, 0, 0);
        this->AssertPrevEqual(node, 0, 0, 0, 0);
    }

    void TestRemoveBuyQuote31() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));
        item->SetDebugLevel(1);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node =  item->AddBuyQuote(CreateHrItem(110));

        item->RemoveBuyQuote(CreateHrItem(110));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end =  item->BuyQuotes()->Node(1);

        this->AssertNextEqual(start, end, end, end, end);
        this->AssertPrevEqual(end, start, start, start, start);
    }

    void TestRemoveBuyQuote32() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));
        item->SetDebugLevel(2);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node =  item->AddBuyQuote(CreateHrItem(110));

        item->RemoveBuyQuote(CreateHrItem(110));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end =  item->BuyQuotes()->Node(1);

        this->AssertNextEqual(start, end, end, end, end);
        this->AssertPrevEqual(end, start, start, start, start);
    }

    void TestRemoveBuyQuote33() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));
        item->SetDebugLevel(3);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node =  item->AddBuyQuote(CreateHrItem(110));

        item->RemoveBuyQuote(CreateHrItem(110));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end =  item->BuyQuotes()->Node(1);

        this->AssertNextEqual(start, end, end, end, end);
        this->AssertPrevEqual(end, start, start, start, start);
    }

    void TestRemoveBuyQuote34() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));
        item->SetDebugLevel(4);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node =  item->AddBuyQuote(CreateHrItem(110));

        item->RemoveBuyQuote(CreateHrItem(110));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end =  item->BuyQuotes()->Node(1);

        this->AssertNextEqual(start, end, end, end, end);
        this->AssertPrevEqual(end, start, start, start, start);
    }

    void TestRemoveBuyQuote35() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(100));
        item->AddBuyQuote(CreateHrItem(120));
        item->SetDebugLevel(5);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node =  item->AddBuyQuote(CreateHrItem(110));

        item->RemoveBuyQuote(CreateHrItem(110));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end =  item->BuyQuotes()->Node(1);

        this->AssertNextEqual(start, end, end, end, end);
        this->AssertPrevEqual(end, start, start, start, start);
    }

    void TestRemoveBuyQuote411() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(1);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(1);
        item->AddBuyQuote(CreateHrItem(120));

        item->RemoveBuyQuote(CreateHrItem(110));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *i0 =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *i1 =  item->BuyQuotes()->Node(1);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *i2 =  item->BuyQuotes()->Node(2);

        this->AssertNextEqual(i0, i2, i2, i2, i2);
        this->AssertPrevEqual(i2, i0, i0, i0, i0);
    }

    void TestRemoveBuyQuote412() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(1);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(1);
        item->AddBuyQuote(CreateHrItem(120));

        item->RemoveBuyQuote(CreateHrItem(120));

        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *i0 =  item->BuyQuotes()->Node(0);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *i1 =  item->BuyQuotes()->Node(1);
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *i2 =  item->BuyQuotes()->Node(2);

        this->AssertNextEqual(i0, i2, i2, i2, i2);
        this->AssertPrevEqual(i2, i0, i0, i0, i0);
    }

    template <typename T>
    const char* GetLevelMap(HrPointerListLite<T> *list, int level) {
        char *buf = new char[list->Count() + 1];
        memset(buf, ' ', list->Count());
        buf[list->Count()] = '\0';

        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            int index = list->IndexOf(node);
            buf[index] = '*';
            if(node == list->End())
                break;
            HrLinkedPointer<T> *next = node->NextByLevel(level);
            if(next == 0)
                throw;
            node = next;
        }
        return buf;
    }

    template <typename T>
    void PrintLevelItems(HrPointerListLite<T> *list, int level) {
        HrLinkedPointer<T> *node = list->Start();
        while(true) {
            printf("%" PRIi64 " ", node->Data()->MDEntryPx.Mantissa);
            if(node == list->End())
                break;
            node = node->NextByLevel(level);
        }
        printf("\n");
    }

    template <typename T>
    void AssertSequence(HrPointerListLite<T> *list, int level, const char *itemsPresenceMap) {

        int length = strlen(itemsPresenceMap);
        if(length != list->Count())
            throw;
        HrLinkedPointer<T> **items = new HrLinkedPointer<T>*[length];
        HrLinkedPointer<T> *node = list->Start();
        int count = 0;
        for(int i = 0; i < length; i++) {
            if(itemsPresenceMap[i] != ' ') {
                items[count] = node;
                count++;
            }

            node = node->Next();
        }

        if(count == 0) {
            if(list->Start()->NextByLevel(level) != 0)
                throw;
            if(level != 1 && list->Start()->PrevByLevel(level) != 0)
                throw;
            return;
        }
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *start = items[0];
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *end = items[count - 1];

        node = start;
        for(int i = 0; i < count; i++) {
            if(node != items[i]) {
                printf("expected: |%s|\n", itemsPresenceMap);
                printf("actual  : |%s|\n", GetLevelMap(list, level));
                this->PrintLevelItems(list, level);
                throw;
            }
            node = node->NextByLevel(level);
        }
        if(node != 0)
            throw;

        node = end;
        for(int i = count - 1; i >= 0; i--) {
            if(node != items[i]) {
                printf("expected: |%s|\n", itemsPresenceMap);
                printf("actual  : |%s|\n", GetLevelMap(list, level));
                this->PrintLevelItems(list, level);
                throw;
            }
            node = node->PrevByLevel(level);
        }
        if(level == 1) {
            if(node != list->Start()->Prev())
                throw;
        }
        else {
            if (node != 0)
                throw;
        }
    }

    void AssertPrices(HrPointerListLite<FortsDefaultSnapshotMessageMDEntriesItemInfo> *list, int prices, ...) {
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> **items = new HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *[list->Count()];
        HrLinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo> *node = list->Start();

        if(node->Data()->MDEntryPx.Mantissa != prices)
            throw;
        node = node->Next();

        va_list ap;
        va_start(ap, prices);
        for (int i = 1; i < list->Count(); i++) {
            int mantissa = va_arg(ap, int);
            if (node->Data()->MDEntryPx.Mantissa != mantissa)
                throw;
            node = node->Next();
        }
        va_end(ap);
    }

    void TestRemoveBuyQuote421() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(2);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(2);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "* *");
        this->AssertSequence(item->BuyQuotes(), 3, "* *");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote422() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(2);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(2);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "* *");
        this->AssertSequence(item->BuyQuotes(), 3, "* *");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote431() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(3);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(3);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "* *");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote432() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(3);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(3);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "* *");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote441() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(4);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(4);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "****");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "***");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote442() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(4);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(4);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "****");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "***");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote451() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(5);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(5);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "****");
        this->AssertSequence(item->BuyQuotes(), 4, "****");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "***");
        this->AssertSequence(item->BuyQuotes(), 4, "***");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void TestRemoveBuyQuote452() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->AddBuyQuote(CreateHrItem(130));
        item->AddBuyQuote(CreateHrItem(100));
        item->SetDebugLevel(5);
        item->AddBuyQuote(CreateHrItem(110));
        item->SetDebugLevel(5);
        item->AddBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "****");
        this->AssertSequence(item->BuyQuotes(), 4, "****");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "***");
        this->AssertSequence(item->BuyQuotes(), 4, "***");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");
    }

    void AddBuyQuote(OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item, int price, int level) {
        item->SetDebugLevel(level);
        item->AddBuyQuote(CreateHrItem(price));
    }

    void TestRemoveBuyQuote511() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 140, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AddBuyQuote(item, 110, 4);
        this->AddBuyQuote(item, 120, 3);
        this->AddBuyQuote(item, 130, 2);

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*   *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  **");
        this->AssertSequence(item->BuyQuotes(), 3, "* ***");
        this->AssertSequence(item->BuyQuotes(), 2, "*****");
        this->AssertSequence(item->BuyQuotes(), 1, "*****");

        item->RemoveBuyQuote(CreateHrItem(140));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "* **");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "***");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");
        this->AssertSequence(item->BuyQuotes(), 4, "**");
        this->AssertSequence(item->BuyQuotes(), 3, "**");
        this->AssertSequence(item->BuyQuotes(), 2, "**");
        this->AssertSequence(item->BuyQuotes(), 1, "**");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 100);
        this->AssertSequence(item->BuyQuotes(), 5, " ");
        this->AssertSequence(item->BuyQuotes(), 4, " ");
        this->AssertSequence(item->BuyQuotes(), 3, " ");
        this->AssertSequence(item->BuyQuotes(), 2, " ");
        this->AssertSequence(item->BuyQuotes(), 1, "*");
    }

    void TestRemoveBuyQuote513() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 140, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AddBuyQuote(item, 110, 4);
        this->AddBuyQuote(item, 120, 3);
        this->AddBuyQuote(item, 130, 2);

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*   *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  **");
        this->AssertSequence(item->BuyQuotes(), 3, "* ***");
        this->AssertSequence(item->BuyQuotes(), 2, "*****");
        this->AssertSequence(item->BuyQuotes(), 1, "*****");

        item->RemoveBuyQuote(CreateHrItem(100));

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120, 110);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *");
        this->AssertSequence(item->BuyQuotes(), 3, "* **");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "* *");
        this->AssertSequence(item->BuyQuotes(), 3, "* *");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 140, 130);
        this->AssertSequence(item->BuyQuotes(), 5, "**");
        this->AssertSequence(item->BuyQuotes(), 4, "**");
        this->AssertSequence(item->BuyQuotes(), 3, "**");
        this->AssertSequence(item->BuyQuotes(), 2, "**");
        this->AssertSequence(item->BuyQuotes(), 1, "**");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 140);
        this->AssertSequence(item->BuyQuotes(), 5, " ");
        this->AssertSequence(item->BuyQuotes(), 4, " ");
        this->AssertSequence(item->BuyQuotes(), 3, " ");
        this->AssertSequence(item->BuyQuotes(), 2, " ");
        this->AssertSequence(item->BuyQuotes(), 1, "*");
    }

    void TestRemoveBuyQuote512() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 140, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AddBuyQuote(item, 110, 2);
        this->AddBuyQuote(item, 120, 3);
        this->AddBuyQuote(item, 130, 4);

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*   *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*** *");
        this->AssertSequence(item->BuyQuotes(), 2, "*****");
        this->AssertSequence(item->BuyQuotes(), 1, "*****");

        item->RemoveBuyQuote(CreateHrItem(100));

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120, 110);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "** *");
        this->AssertSequence(item->BuyQuotes(), 3, "****");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");


        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "***");
        this->AssertSequence(item->BuyQuotes(), 3, "***");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 140, 130);
        this->AssertSequence(item->BuyQuotes(), 5, "**");
        this->AssertSequence(item->BuyQuotes(), 4, "**");
        this->AssertSequence(item->BuyQuotes(), 3, "**");
        this->AssertSequence(item->BuyQuotes(), 2, "**");
        this->AssertSequence(item->BuyQuotes(), 1, "**");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 140);
        this->AssertSequence(item->BuyQuotes(), 5, " ");
        this->AssertSequence(item->BuyQuotes(), 4, " ");
        this->AssertSequence(item->BuyQuotes(), 3, " ");
        this->AssertSequence(item->BuyQuotes(), 2, " ");
        this->AssertSequence(item->BuyQuotes(), 1, "*");
    }

    void TestRemoveBuyQuote514() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 140, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AddBuyQuote(item, 110, 2);
        this->AddBuyQuote(item, 120, 3);
        this->AddBuyQuote(item, 130, 4);

        this->AssertPrices(item->BuyQuotes(), 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*   *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*** *");
        this->AssertSequence(item->BuyQuotes(), 2, "*****");
        this->AssertSequence(item->BuyQuotes(), 1, "*****");

        item->RemoveBuyQuote(CreateHrItem(140));

        this->AssertPrices(item->BuyQuotes(), 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *");
        this->AssertSequence(item->BuyQuotes(), 3, "** *");
        this->AssertSequence(item->BuyQuotes(), 2, "****");
        this->AssertSequence(item->BuyQuotes(), 1, "****");


        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* *");
        this->AssertSequence(item->BuyQuotes(), 4, "* *");
        this->AssertSequence(item->BuyQuotes(), 3, "* *");
        this->AssertSequence(item->BuyQuotes(), 2, "***");
        this->AssertSequence(item->BuyQuotes(), 1, "***");

        item->RemoveBuyQuote(CreateHrItem(120));

        this->AssertPrices(item->BuyQuotes(), 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");
        this->AssertSequence(item->BuyQuotes(), 4, "**");
        this->AssertSequence(item->BuyQuotes(), 3, "**");
        this->AssertSequence(item->BuyQuotes(), 2, "**");
        this->AssertSequence(item->BuyQuotes(), 1, "**");

        item->RemoveBuyQuote(CreateHrItem(110));

        this->AssertPrices(item->BuyQuotes(), 100);
        this->AssertSequence(item->BuyQuotes(), 5, " ");
        this->AssertSequence(item->BuyQuotes(), 4, " ");
        this->AssertSequence(item->BuyQuotes(), 3, " ");
        this->AssertSequence(item->BuyQuotes(), 2, " ");
        this->AssertSequence(item->BuyQuotes(), 1, "*");
    }

    void TestRemoveBuyQuote611() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 160, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");


        this->AddBuyQuote(item, 150, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "***");

        this->AddBuyQuote(item, 110, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "****");

        this->AddBuyQuote(item, 130, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*****");

        this->AddBuyQuote(item, 140, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "** ***");

        this->AddBuyQuote(item, 120, 1);

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "** * **");
        this->AssertSequence(item->BuyQuotes(), 4, "** * **");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**  **");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**   **");
        this->AssertSequence(item->BuyQuotes(), 4, "** * **");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**  **");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**   **");
        this->AssertSequence(item->BuyQuotes(), 4, "**   **");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**  **");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**   **");
        this->AssertSequence(item->BuyQuotes(), 4, "**   **");
        this->AssertSequence(item->BuyQuotes(), 3, "**   **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**  **");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**   **");
        this->AssertSequence(item->BuyQuotes(), 4, "**   **");
        this->AssertSequence(item->BuyQuotes(), 3, "**   **");
        this->AssertSequence(item->BuyQuotes(), 2, "**   **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**  **");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");
    }

    void TestRemoveBuyQuote612() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 160, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");


        this->AddBuyQuote(item, 150, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 100);
        this->AssertSequence(item->BuyQuotes(), 4, "***");

        this->AddBuyQuote(item, 110, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 4, "****");

        this->AddBuyQuote(item, 130, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* * *");
        this->AssertSequence(item->BuyQuotes(), 4, "*****");

        this->AddBuyQuote(item, 140, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 4, "** ***");

        this->AddBuyQuote(item, 120, 1);

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 4, "** * **");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "** * **");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "**   **");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "**   **");
        this->AssertSequence(item->BuyQuotes(), 3, "**   **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "**   **");
        this->AssertSequence(item->BuyQuotes(), 3, "**   **");
        this->AssertSequence(item->BuyQuotes(), 2, "**   **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "**  **");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");
    }

    void TestRemoveBuyQuote613() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 160, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");


        this->AddBuyQuote(item, 150, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 100);
        this->AssertSequence(item->BuyQuotes(), 3, "***");

        this->AddBuyQuote(item, 110, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 3, "****");

        this->AddBuyQuote(item, 130, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* * *");
        this->AssertSequence(item->BuyQuotes(), 3, "*****");

        this->AddBuyQuote(item, 140, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 3, "** ***");

        this->AddBuyQuote(item, 120, 1);

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "** * **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "**   **");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "**   **");
        this->AssertSequence(item->BuyQuotes(), 2, "**   **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "**  **");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");
    }

    void TestRemoveBuyQuote614() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 160, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");


        this->AddBuyQuote(item, 150, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 100);
        this->AssertSequence(item->BuyQuotes(), 2, "***");

        this->AddBuyQuote(item, 110, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 2, "****");

        this->AddBuyQuote(item, 130, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* * *");
        this->AssertSequence(item->BuyQuotes(), 2, "*****");

        this->AddBuyQuote(item, 140, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 2, "** ***");

        this->AddBuyQuote(item, 120, 1);

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "*     *");
        this->AssertSequence(item->BuyQuotes(), 2, "** * **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "*     *");
        this->AssertSequence(item->BuyQuotes(), 2, "**   **");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "**  **");
        this->AssertSequence(item->BuyQuotes(), 1, "******");
    }

    void TestRemoveBuyQuote615() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        this->AddBuyQuote(item, 160, 5);
        this->AddBuyQuote(item, 100, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "**");


        this->AddBuyQuote(item, 150, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 100);
        this->AssertSequence(item->BuyQuotes(), 1, "***");

        this->AddBuyQuote(item, 110, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 1, "****");

        this->AddBuyQuote(item, 130, 5);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "* * *");
        this->AssertSequence(item->BuyQuotes(), 1, "*****");

        this->AddBuyQuote(item, 140, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 120, 1);

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 2, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "*    *");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 4);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 2, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "*    *");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 3);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 2, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "*    *");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 2);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "*     *");
        this->AssertSequence(item->BuyQuotes(), 2, "*  *  *");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "*    *");
        this->AssertSequence(item->BuyQuotes(), 1, "******");

        this->AddBuyQuote(item, 130, 1);
        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 130, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*     *");
        this->AssertSequence(item->BuyQuotes(), 4, "*     *");
        this->AssertSequence(item->BuyQuotes(), 3, "*     *");
        this->AssertSequence(item->BuyQuotes(), 2, "*     *");
        this->AssertSequence(item->BuyQuotes(), 1, "*******");

        item->RemoveBuyQuote(CreateHrItem(130));

        this->AssertPrices(item->BuyQuotes(), 160, 150, 140, 120, 110, 100);
        this->AssertSequence(item->BuyQuotes(), 5, "*    *");
        this->AssertSequence(item->BuyQuotes(), 4, "*    *");
        this->AssertSequence(item->BuyQuotes(), 3, "*    *");
        this->AssertSequence(item->BuyQuotes(), 2, "*    *");
        this->AssertSequence(item->BuyQuotes(), 1, "******");
    }

    void TestAddBuyQuote4TimesAscending() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->SetDebugLevel(0);

        this->AddBuyQuote(item, 1000, 5);
        this->AddBuyQuote(item, 1002, 5);
        this->AssertPrices(item->BuyQuotes(), 1002, 1000);
        this->AssertSequence(item->BuyQuotes(), 5, "**");

        this->AddBuyQuote(item, 1004, 5);
        this->AssertPrices(item->BuyQuotes(), 1004, 1002, 1000);
        this->TestLevelsDescending(item->BuyQuotes());

        this->AddBuyQuote(item, 1006, 5);
        this->AssertPrices(item->BuyQuotes(), 1006, 1004, 1002, 1000);
        this->TestLevelsDescending(item->BuyQuotes());

        this->AddBuyQuote(item, 1008, 5);
        this->AssertPrices(item->BuyQuotes(), 1008, 1006, 1004, 1002, 1000);
        this->TestLevelsDescending(item->BuyQuotes());
    }

    void TestAddBuyQuote4TimesDescending() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item = CreateOrderBook();

        item->SetDebugLevel(0);

        this->AddBuyQuote(item, 1008, 5);
        this->AddBuyQuote(item, 1006, 5);
        this->AssertPrices(item->BuyQuotes(), 1008, 1006);
        this->AssertSequence(item->BuyQuotes(), 5, "**");

        this->AddBuyQuote(item, 1004, 5);
        this->AssertPrices(item->BuyQuotes(), 1008, 1006, 1004);
        this->TestLevelsDescending(item->BuyQuotes());

        this->AddBuyQuote(item, 1002, 5);
        this->AssertPrices(item->BuyQuotes(), 1008, 1006, 1004, 1002);
        this->TestLevelsDescending(item->BuyQuotes());

        this->AddBuyQuote(item, 1000, 5);
        this->AssertPrices(item->BuyQuotes(), 1008, 1006, 1004, 1002, 1000);
        this->TestLevelsDescending(item->BuyQuotes());
    }

    void TestHrBuyQuotes() {
        TestHrAddBuyQuote1();
        TestHrAddBuyQuote2();
        TestHrAddBuyQuote3();
        TestHrAddBuyQuote4();
        TestHrAddBuyQuote5();

        TestHrInsertByLevel0();
        TestHrInsertByLevel1();
        TestHrInsertByLevel2();
        TestHrInsertByLevel3();
        TestHrInsertByLevel4();
        TestHrInsertByLevel5();

        TestHrInsertBuyQuote1();
        TestHrInsertBuyQuote2();
        TestHrInsertBuyQuote3();
        TestHrInsertBuyQuote4();
        TestHrInsertBuyQuote5();

        TestRemoveBuyQuote1();
        TestRemoveBuyQuote21();
        TestRemoveBuyQuote22();

        TestRemoveBuyQuote31();
        TestRemoveBuyQuote32();
        TestRemoveBuyQuote33();
        TestRemoveBuyQuote34();
        TestRemoveBuyQuote35();

        TestRemoveBuyQuote411();
        TestRemoveBuyQuote412();
        TestRemoveBuyQuote421();
        TestRemoveBuyQuote422();
        TestRemoveBuyQuote431();
        TestRemoveBuyQuote432();
        TestRemoveBuyQuote441();
        TestRemoveBuyQuote442();
        TestRemoveBuyQuote451();
        TestRemoveBuyQuote452();

        TestRemoveBuyQuote511();
        TestRemoveBuyQuote512();
        TestRemoveBuyQuote513();
        TestRemoveBuyQuote514();

        TestRemoveBuyQuote611();
        TestRemoveBuyQuote612();
        TestRemoveBuyQuote613();
        TestRemoveBuyQuote614();
        TestRemoveBuyQuote615();

        TestAddBuyQuote4TimesAscending();
        TestAddBuyQuote4TimesDescending();
    }

    void TestRandomGenerator() {
        OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *info = new OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>();
        int count[6] = {0, 0, 0, 0, 0, 0};
        for(int i = 0; i < 10000; i++) {
            int level = info->BuyQuoteManager()->CalcLevel();
            count[level]++;
        }
        printf("levels = %d %d %d %d %d\n", count[1], count[2], count[3], count[4], count[5]);
    }

    void TestHr() {
        TestRandomGenerator();
        TestHrBuyQuotes();
    }
#endif

    void Test() {
        TestDefaults();
        TestStringIdComparer();
#ifdef USE_SKIP_LIST
        TestHr();
        TestPerformance();
#endif
        TestOrderTableItem();
        TestConnection();
        TestInfoAndItemInfoUsageAndAllocationCurr();
        Test_OLR_CURR();
        Test_Aggregated();
    }
};

#endif

#endif //HFT_ROBOT_FORTSORDERBOOKTESTER_H
