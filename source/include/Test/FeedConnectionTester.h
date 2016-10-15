//
// Created by root on 10.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTEST_H
#define HFT_ROBOT_FEEDCONNECTIONTEST_H

#include "../FeedConnection.h"
#include <stdio.h>

class FeedConnectionTester {
public:
    FeedConnectionTester() { }
    ~FeedConnectionTester() { }
    /*
    void Test_OnIncrementalRefresh_OBR_FOND_Add() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        AutoAllocatePointerList<FastOBSFONDItemInfo> *itemInfoList = new AutoAllocatePointerList<FastOBSFONDItemInfo>(10, 10);

        char symbol[5];
        char trading[11];

        sprintf(symbol, "SMB1");
        sprintf(trading, "TRADING001");

        FastOBSFONDInfo *info = new FastOBSFONDInfo;
        FastOBSFONDItemInfo *item1 = itemInfoList->NewItem();
        item1->MDUpdateAction = MDUpdateAction::mduaAdd;

        item1->Symbol = symbol;
        item1->TradingSessionID = trading;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;

        FastOBSFONDItemInfo *item2 = itemInfoList->NewItem();
        item2->MDUpdateAction = MDUpdateAction::mduaAdd;

        item2->Symbol = symbol;
        item2->TradingSessionID = trading;

        FastOBSFONDItemInfo *item3 = itemInfoList->NewItem();
        item3->MDUpdateAction = MDUpdateAction::mduaAdd;

        item3->Symbol = symbol;
        item3->TradingSessionID = trading;

        info->GroupMDEntriesCount = 2;
        info->GroupMDEntries[0] = item2;
        info->GroupMDEntries[1] = item3;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *hs = fc->m_orderBookTableFond->GetItem(symbol, trading);
        if(hs->Count() != 3)
            throw;

        if(!item1->Used || !item2->Used || !item3->Used)
            throw;
        sprintf(symbol, "SMB2");

        fc->OnIncrementalRefresh_OBR_FOND(info);
        if(fc->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 2)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;

        hs = fc->m_orderBookTableFond->GetItem(symbol, trading);
        if(hs->Count() != 2)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND() {
        Test_OnIncrementalRefresh_OBR_FOND_Add();
    }

    void Test_OBR_FOND() {
        Test_OnIncrementalRefresh_OBR_FOND();
    }
    */
    void Test() {
        //Test_OBR_FOND();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTEST_H
