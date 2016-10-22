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

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID004", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID002", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID001", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Next()->Data()->Id->Equal("ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID002", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi2 = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!obi2->BuyQuotes()->Item(0)->Id->Equal("ENTRYID002"))
            throw;
        if(!obi2->BuyQuotes()->Item(1)->Id->Equal("ENTRYID001"))
            throw;
        if(!obi2->BuyQuotes()->Item(2)->Id->Equal("ENTRYID004"))
            throw;
        if(!obi2->BuyQuotes()->Item(3)->Id->Equal("ENTRYID003"))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);

        OrderBookQuote *qt1 = obi->BuyQuotes()->Item(0);
        OrderBookQuote *qt2 = obi->BuyQuotes()->Item(1);
        OrderBookQuote *qt3 = obi->BuyQuotes()->Item(2);
        OrderBookQuote *qt4 = obi->BuyQuotes()->Item(3);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!qt1->Id->Equal("ENTRYID001", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID004", 10))
            throw;
        if(!qt3->Id->Equal("ENTRYID002", 10))
            throw;
        if(!qt4->Id->Equal("ENTRYID003", 10))
            throw;

        if(qt1->Price.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->Price.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->Price.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->Price.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        fc->OrderBookFond()->Clear();
        if(fc->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND() {
        Test_OnIncrementalRefresh_OBR_FOND_Add();
        Test_OnIncrementalRefresh_OBR_FOND_Remove();
        Test_OnIncrementalRefresh_OBR_FOND_Change();
        Test_Clear();
    }

    FastOBSFONDInfo* CreateFastOBSFondInfo(const char *symbol, const char *trading) {
        FastOBSFONDInfo *info = new FastOBSFONDInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastOBSFONDItemInfo* CreateFastOBSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        FastOBSFONDItemInfo *info = new FastOBSFONDItemInfo();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastOBSFONDItemInfo* CreateFastOBRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId) {
        FastOBSFONDItemInfo *info = CreateFastOBSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;

        return info;
    }


    FastOBSCURRInfo* CreateFastOBSCurrInfo(const char *symbol, const char *trading) {
        FastOBSCURRInfo *info = new FastOBSCURRInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastOBSCURRItemInfo* CreateFastOBSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        FastOBSCURRItemInfo *info = new FastOBSCURRItemInfo();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastOBSCURRItemInfo* CreateFastOBRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId) {
        FastOBSCURRItemInfo *info = CreateFastOBSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;

        return info;
    }


    void Test_OnFullRefresh_OBS_FOND() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SMB2", "TRADING001");
        FastOBSFONDItemInfo *newItem1 = CreateFastOBSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSFONDItemInfo *newItem2 = CreateFastOBSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        fc->OnFullRefresh_OBS_FOND(info2);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi3 = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        OrderBookQuote *qt1 = obi->BuyQuotes()->Start()->Data();
        OrderBookQuote *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!qt1->Id->Equal("ENTRYID008", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID007", 10))
            throw;
        if(!qt1->Price.Equal(8, -2))
            throw;
        if(!qt1->Size.Equal(1, 2))
            throw;
        if(!qt2->Price.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        OrderBookQuote *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->Price.Equal(4, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(2, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->Price.Equal(4, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(2, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->Price.Equal(25, -3))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID004", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->Price.Equal(4, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID003", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID001", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Next()->Data()->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID001", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change_Sellquotes() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi2 = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!obi2->SellQuotes()->Item(0)->Id->Equal("ENTRYID003"))
            throw;
        if(!obi2->SellQuotes()->Item(1)->Id->Equal("ENTRYID004"))
            throw;
        if(!obi2->SellQuotes()->Item(2)->Id->Equal("ENTRYID001"))
            throw;
        if(!obi2->SellQuotes()->Item(3)->Id->Equal("ENTRYID002"))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);

        OrderBookQuote *qt1 = obi->SellQuotes()->Item(0);
        OrderBookQuote *qt2 = obi->SellQuotes()->Item(1);
        OrderBookQuote *qt3 = obi->SellQuotes()->Item(2);
        OrderBookQuote *qt4 = obi->SellQuotes()->Item(3);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!qt1->Id->Equal("ENTRYID003", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID002", 10))
            throw;
        if(!qt3->Id->Equal("ENTRYID004", 10))
            throw;
        if(!qt4->Id->Equal("ENTRYID001", 10))
            throw;

        if(qt1->Price.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->Price.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->Price.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->Price.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_SellQuotes() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        fc->OrderBookFond()->Clear();
        if(fc->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_FOND_SellQuotes() {
        FeedConnection_FOND_OBR *fc = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_FOND(info);

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SMB2", "TRADING001");
        FastOBSFONDItemInfo *newItem1 = CreateFastOBSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSFONDItemInfo *newItem2 = CreateFastOBSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        fc->OnFullRefresh_OBS_FOND(info2);

        if(fc->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi3 = fc->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = fc->OrderBookFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        OrderBookQuote *qt1 = obi->BuyQuotes()->Start()->Data();
        OrderBookQuote *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!qt1->Id->Equal("ENTRYID007", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID008", 10))
            throw;
        if(!qt1->Price.Equal(7, -2))
            throw;
        if(!qt1->Size.Equal(1, 2))
            throw;
        if(!qt2->Price.Equal(8, -2))
            throw;
    }

    
    /***********************************/

    void Test_OnIncrementalRefresh_OBR_CURR_Add() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID004", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->Price.Equal(&price))
            throw;
        if(!quote->Size.Equal(&size))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID002", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID001", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Next()->Data()->Id->Equal("ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID002", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi2 = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!obi2->BuyQuotes()->Item(0)->Id->Equal("ENTRYID002"))
            throw;
        if(!obi2->BuyQuotes()->Item(1)->Id->Equal("ENTRYID001"))
            throw;
        if(!obi2->BuyQuotes()->Item(2)->Id->Equal("ENTRYID004"))
            throw;
        if(!obi2->BuyQuotes()->Item(3)->Id->Equal("ENTRYID003"))
            throw;

        FastOBSCURRItemInfo *item5 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        OrderBookQuote *qt1 = obi->BuyQuotes()->Item(0);
        OrderBookQuote *qt2 = obi->BuyQuotes()->Item(1);
        OrderBookQuote *qt3 = obi->BuyQuotes()->Item(2);
        OrderBookQuote *qt4 = obi->BuyQuotes()->Item(3);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!qt1->Id->Equal("ENTRYID001", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID004", 10))
            throw;
        if(!qt3->Id->Equal("ENTRYID002", 10))
            throw;
        if(!qt4->Id->Equal("ENTRYID003", 10))
            throw;

        if(qt1->Price.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->Price.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->Price.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->Price.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        fc->OrderBookCurr()->Clear();
        if(fc->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR() {
        Test_OnIncrementalRefresh_OBR_CURR_Add();
        Test_OnIncrementalRefresh_OBR_CURR_Remove();
        Test_OnIncrementalRefresh_OBR_CURR_Change();
        Test_Clear_Curr();
    }

    void Test_OnFullRefresh_OBS_CURR() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = CreateFastOBSCurrInfo("SMB2", "TRADING001");
        FastOBSCURRItemInfo *newItem1 = CreateFastOBSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSCURRItemInfo *newItem2 = CreateFastOBSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        fc->OnFullRefresh_OBS_CURR(info2);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi3 = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        OrderBookQuote *qt1 = obi->BuyQuotes()->Start()->Data();
        OrderBookQuote *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!qt1->Id->Equal("ENTRYID008", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID007", 10))
            throw;
        if(!qt1->Price.Equal(8, -2))
            throw;
        if(!qt1->Size.Equal(1, 2))
            throw;
        if(!qt2->Price.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        OrderBookQuote *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->Price.Equal(4, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(2, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->Price.Equal(4, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(fc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(fc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->Price.Equal(2, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->Price.Equal(25, -3))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID004", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->Price.Equal(3, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->Price.Equal(4, -2))
            throw;
        if(!quote->Size.Equal(1, 2))
            throw;
        if(!quote->Id->Equal("ENTRYID002", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID003", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID001", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Next()->Data()->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID001", 10))
            throw;
        if(!obi->BuyQuotes()->Start()->Next()->Data()->Id->Equal("ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!obi->BuyQuotes()->Start()->Data()->Id->Equal("ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change_Sellquotes() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi2 = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!obi2->SellQuotes()->Item(0)->Id->Equal("ENTRYID003"))
            throw;
        if(!obi2->SellQuotes()->Item(1)->Id->Equal("ENTRYID004"))
            throw;
        if(!obi2->SellQuotes()->Item(2)->Id->Equal("ENTRYID001"))
            throw;
        if(!obi2->SellQuotes()->Item(3)->Id->Equal("ENTRYID002"))
            throw;

        FastOBSCURRItemInfo *item5 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        OrderBookQuote *qt1 = obi->SellQuotes()->Item(0);
        OrderBookQuote *qt2 = obi->SellQuotes()->Item(1);
        OrderBookQuote *qt3 = obi->SellQuotes()->Item(2);
        OrderBookQuote *qt4 = obi->SellQuotes()->Item(3);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!qt1->Id->Equal("ENTRYID003", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID002", 10))
            throw;
        if(!qt3->Id->Equal("ENTRYID004", 10))
            throw;
        if(!qt4->Id->Equal("ENTRYID001", 10))
            throw;

        if(qt1->Price.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->Price.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->Price.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->Price.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr_SellQuotes() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        fc->OrderBookCurr()->Clear();
        if(fc->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes() {
        FeedConnection_CURR_OBR *fc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                                  FeedConnectionProtocol::UDP_IP,
                                                                  "10.50.129.200", "239.192.113.3", 9113,
                                                                  "10.50.129.200", "239.192.113.131", 9313);

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        fc->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = CreateFastOBSCurrInfo("SMB2", "TRADING001");
        FastOBSCURRItemInfo *newItem1 = CreateFastOBSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSCURRItemInfo *newItem2 = CreateFastOBSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        fc->OnFullRefresh_OBS_CURR(info2);

        if(fc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi3 = fc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = fc->OrderBookCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        OrderBookQuote *qt1 = obi->BuyQuotes()->Start()->Data();
        OrderBookQuote *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!qt1->Id->Equal("ENTRYID007", 10))
            throw;
        if(!qt2->Id->Equal("ENTRYID008", 10))
            throw;
        if(!qt1->Price.Equal(7, -2))
            throw;
        if(!qt1->Size.Equal(1, 2))
            throw;
        if(!qt2->Price.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_SellQuotes() {
        Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes();
        Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes();
        Test_OnIncrementalRefresh_OBR_CURR_Change_Sellquotes();
        Test_Clear_SellQuotes();
    }

    void Test_OBR_CURR() {
        Test_OnIncrementalRefresh_OBR_CURR();
        Test_OnFullRefresh_OBS_CURR();
        Test_OnIncrementalRefresh_OBR_CURR_SellQuotes();
        Test_OnFullRefresh_OBS_CURR_SellQuotes();
    }
    
    void Test_OnIncrementalRefresh_OBR_FOND_SellQuotes() {
        Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes();
        Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes();
        Test_OnIncrementalRefresh_OBR_FOND_Change_Sellquotes();
        Test_Clear_SellQuotes();
    }

    void Test_OBR_FOND() {
        Test_OnIncrementalRefresh_OBR_FOND();
        Test_OnFullRefresh_OBS_FOND();
        Test_OnIncrementalRefresh_OBR_FOND_SellQuotes();
        Test_OnFullRefresh_OBS_FOND_SellQuotes();
    }
    
    void Test() {
        Test_OBR_FOND();
        Test_OBR_CURR();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTEST_H
