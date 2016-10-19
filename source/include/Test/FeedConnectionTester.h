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

    void Test_OnIncrementalRefresh_OBR_FOND_Add() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        char symbol[5];
        char trading[11];
        char entryId[11];
        char entryType[1];

        sprintf(symbol, "SMB1");
        sprintf(trading, "TRADING001");
        sprintf(entryId, "ENTRYID001");

        FastOBSFONDInfo *info = new FastOBSFONDInfo;
        FastOBSFONDItemInfo *item1 = new FastOBSFONDItemInfo;
        item1->MDUpdateAction = MDUpdateAction::mduaAdd;

        item1->Symbol = symbol;
        item1->SymbolLength = 4;
        item1->TradingSessionID = trading;
        item1->TradingSessionIDLength = 10;
        item1->MDEntryID = entryId;
        item1->MDEntryIDLength = 10;
        item1->MDEntryType = entryType;
        item1->MDEntryTypeLength = 1;
        item1->MDEntryType[0] = mdetBuyQuote;
        item1->MDEntryPx.Set(3, -2);
        item1->MDEntrySize.Set(1, 2);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem *obi = fc->OrderBookFond()->GetItem(symbol, 4, trading, 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        OrderBookQuote *quote = obi->BuyQuotes()->Start()->Data();
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId, 10))
            throw;


        char symbol2[5];
        char trading2[11];
        char entryId2[11];
        char entryType2[1];

        sprintf(symbol2, "SMB1");
        sprintf(trading2, "TRADING001");
        sprintf(entryId2, "ENTRYID002");
        entryType2[0] = '0';

        FastOBSFONDItemInfo *item2 = new FastOBSFONDItemInfo;
        item2->MDUpdateAction = MDUpdateAction::mduaAdd;

        item2->Symbol = symbol2;
        item2->SymbolLength = 4;
        item2->TradingSessionID = trading2;
        item2->TradingSessionIDLength = 10;
        item2->MDEntryID = entryId2;
        item2->MDEntryIDLength = 10;
        item2->MDEntryType = entryType2;
        item2->MDEntryTypeLength = 1;
        item2->MDEntryType[0] = mdetBuyQuote;
        item2->MDEntryPx.Set(4, -2);
        item2->MDEntrySize.Set(1, 2);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem(symbol2, 4, trading2, 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId2, 10))
            throw;


        char symbol3[5];
        char trading3[11];
        char entryId3[11];
        char entryType3[1];

        sprintf(symbol3, "SMB1");
        sprintf(trading3, "TRADING001");
        sprintf(entryId3, "ENTRYID003");
        entryType3[0] = '0';

        FastOBSFONDItemInfo *item3 = new FastOBSFONDItemInfo;
        item3->MDUpdateAction = MDUpdateAction::mduaAdd;

        item3->Symbol = symbol3;
        item3->SymbolLength = 4;
        item3->TradingSessionID = trading3;
        item3->TradingSessionIDLength = 10;
        item3->MDEntryID = entryId3;
        item3->MDEntryIDLength = 10;
        item3->MDEntryType = entryType3;
        item3->MDEntryTypeLength = 1;
        item3->MDEntryType[0] = mdetBuyQuote;
        item3->MDEntryPx.Set(2, -2);
        item3->MDEntrySize.Set(1, 2);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem(symbol3, 4, trading3, 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId2, 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId, 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId3, 10))
            throw;

        char symbol4[5];
        char trading4[11];
        char entryId4[11];
        char entryType4[1];

        sprintf(symbol4, "SMB1");
        sprintf(trading4, "TRADING001");
        sprintf(entryId4, "ENTRYID004");
        entryType4[0] = '0';

        FastOBSFONDItemInfo *item4 = new FastOBSFONDItemInfo;
        item4->MDUpdateAction = MDUpdateAction::mduaAdd;

        item4->Symbol = symbol4;
        item4->SymbolLength = 4;
        item4->TradingSessionID = trading4;
        item4->TradingSessionIDLength = 10;
        item4->MDEntryID = entryId4;
        item4->MDEntryIDLength = 10;
        item4->MDEntryType = entryType4;
        item4->MDEntryTypeLength = 1;
        item4->MDEntryType[0] = mdetBuyQuote;
        item4->MDEntryPx.Set(25, -3);
        item4->MDEntrySize.Set(1, 2);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->SymbolsCount() != 1)
            throw;
        if(fc->m_orderBookTableFond->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem(symbol4, 4, trading4, 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId2, 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId, 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId4, 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal(entryId3, 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove() {

    }

    void Test_OnIncrementalRefresh_OBR_FOND() {
        Test_OnIncrementalRefresh_OBR_FOND_Add();
        Test_OnIncrementalRefresh_OBR_FOND_Remove();
    }

    void Test_OBR_FOND() {
        Test_OnIncrementalRefresh_OBR_FOND();
    }

    void Test() {
        Test_OBR_FOND();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTEST_H
