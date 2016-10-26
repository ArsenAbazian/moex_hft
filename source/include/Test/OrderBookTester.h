//
// Created by root on 10.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTEST_H
#define HFT_ROBOT_FEEDCONNECTIONTEST_H

#include "../FeedConnection.h"
#include <stdio.h>

class OrderBookTester {
    FeedConnection_FOND_OBR *fcf;
    FeedConnection_CURR_OBR *fcc;
public:
    OrderBookTester() {
        this->fcf = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->fcc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
    }
    ~OrderBookTester() {
        delete this->fcf;
        delete this->fcc;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add() {
        this->fcf->OrderBookFond()->Clear();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(!item1->Used)
            throw;
        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOBSFONDItemInfo *quote = obi->BuyQuotes()->Start()->Data();
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID004", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove() {
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change() {
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi2 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOBSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOBSFONDItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOBSFONDItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID003", 10))
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
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        this->fcf->OrderBookFond()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
                item2->Allocator->Count() != 0 ||
                item3->Allocator->Count() != 0 ||
                item4->Allocator->Count() != 0)
            throw;
        if(this->fcf->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
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

        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(1, 1);
        FastOBSFONDItemInfo *info = list->NewItem();

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

        AutoAllocatePointerList<FastOBSCURRItemInfo> *list = new AutoAllocatePointerList<FastOBSCURRItemInfo>(1, 1);
        FastOBSCURRItemInfo *info = list->NewItem();

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
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SMB2", "TRADING001");
        FastOBSFONDItemInfo *newItem1 = CreateFastOBSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSFONDItemInfo *newItem2 = CreateFastOBSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OnFullRefresh_OBS_FOND(info2);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi3 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOBSFONDItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOBSFONDItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes() {
        this->fcf->OrderBookFond()->Clear();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOBSFONDItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes() {
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10,"ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 10,"ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10,"ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes() {
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi2 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetSellQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSFONDItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSFONDItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOBSFONDItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOBSFONDItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID001", 10))
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
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        this->fcf->OrderBookFond()->Clear();
        if(this->fcf->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_FOND_SellQuotes() {
        this->fcf->OrderBookFond()->Clear();

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

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SMB2", "TRADING001");
        FastOBSFONDItemInfo *newItem1 = CreateFastOBSFondItemInfo(7,-2, 1, 2, mdetSellQuote, "ENTRYID007");
        FastOBSFONDItemInfo *newItem2 = CreateFastOBSFondItemInfo(8,-2, 1, 2, mdetSellQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OnFullRefresh_OBS_FOND(info2);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi3 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->SellQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOBSFONDItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        FastOBSFONDItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }


    /***********************************/

    void Test_OnIncrementalRefresh_OBR_CURR_Add() {
        this->fcc->OrderBookCurr()->Clear();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove() {
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change() {
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi2 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        FastOBSCURRItemInfo *item5 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOBSCURRItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOBSCURRItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID003", 10))
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
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        this->fcc->OrderBookCurr()->Clear();
        if(this->fcc->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR() {
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = CreateFastOBSCurrInfo("SMB2", "TRADING001");
        FastOBSCURRItemInfo *newItem1 = CreateFastOBSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSCURRItemInfo *newItem2 = CreateFastOBSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OnFullRefresh_OBS_CURR(info2);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi3 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOBSCURRItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOBSCURRItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes() {
        this->fcc->OrderBookCurr()->Clear();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOBSCURRItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes() {
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes() {
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi2 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        FastOBSCURRItemInfo *item5 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetSellQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOBSCURRItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOBSCURRItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID001", 10))
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
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        this->fcc->OrderBookCurr()->Clear();
        if(this->fcc->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes() {
        this->fcc->OrderBookCurr()->Clear();

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

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = CreateFastOBSCurrInfo("SMB2", "TRADING001");
        FastOBSCURRItemInfo *newItem1 = CreateFastOBSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "ENTRYID007");
        FastOBSCURRItemInfo *newItem2 = CreateFastOBSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OnFullRefresh_OBS_CURR(info2);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi3 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->SellQuotes()->Count() != 0)
            throw;

        OrderBookTableItem<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOBSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND() {
        printf("Test_OnIncrementalRefresh_OBR_FOND_Add\n");
        Test_OnIncrementalRefresh_OBR_FOND_Add();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Remove\n");
        Test_OnIncrementalRefresh_OBR_FOND_Remove();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Change\n");
        Test_OnIncrementalRefresh_OBR_FOND_Change();
        printf("Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OBR_FOND_SellQuotes() {
        printf("Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes();
        printf("Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OnIncrementalRefresh_OBR_CURR() {
        printf("Test_OnIncrementalRefresh_OBR_CURR_Add\n");
        Test_OnIncrementalRefresh_OBR_CURR_Add();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Remove\n");
        Test_OnIncrementalRefresh_OBR_CURR_Remove();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Change\n");
        Test_OnIncrementalRefresh_OBR_CURR_Change();
        printf("Test_Clear_Curr\n");
        Test_Clear_Curr();
    }

    void Test_OnIncrementalRefresh_OBR_CURR_SellQuotes() {
        printf("Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes();
        printf("Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OBR_CURR() {
        printf("Test_OnIncrementalRefresh_OBR_CURR\n");
        Test_OnIncrementalRefresh_OBR_CURR();
        printf("Test_OnFullRefresh_OBS_CURR\n");
        Test_OnFullRefresh_OBS_CURR();
        printf("Test_OnIncrementalRefresh_OBR_CURR_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_SellQuotes();
        printf("Test_OnFullRefresh_OBS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OBS_CURR_SellQuotes();
    }

    void Test_OBR_FOND() {
        printf("Test_OnIncrementalRefresh_OBR_FOND\n");
        Test_OnIncrementalRefresh_OBR_FOND();
        printf("Test_OnFullRefresh_OBS_FOND\n");
        Test_OnFullRefresh_OBS_FOND();
        printf("Test_OnIncrementalRefresh_OBR_FOND_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_SellQuotes();
        printf("Test_OnFullRefresh_OBS_FOND_SellQuotes\n");
        Test_OnFullRefresh_OBS_FOND_SellQuotes();
    }

    void Test() {
        Test_OBR_FOND();
        Test_OBR_CURR();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTEST_H
