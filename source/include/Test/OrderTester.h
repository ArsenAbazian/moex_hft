//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_ORDERTESTER_H
#define HFT_ROBOT_ORDERTESTER_H

#include "../FeedConnection.h"
#include <stdio.h>

class OrderTester {
    FeedConnection_FOND_OLR *fcf;
    FeedConnection_CURR_OLR *fcc;
public:
    OrderTester() {
        this->fcf = new FeedConnection_FOND_OLR("OLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->fcc = new FeedConnection_CURR_OLR("OLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
    }
    ~OrderTester() {
        delete this->fcf;
        delete this->fcc;
    }

    FastOLSFONDInfo* CreateFastOLSFondInfo(const char *symbol, const char *trading) {
        FastOLSFONDInfo *info = new FastOLSFONDInfo();

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

    FastOLSFONDItemInfo* CreateFastOLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastOLSFONDItemInfo> *list = new AutoAllocatePointerList<FastOLSFONDItemInfo>(1, 1);
        FastOLSFONDItemInfo *info = list->NewItem();

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

    FastOLSFONDItemInfo* CreateFastOLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId) {
        FastOLSFONDItemInfo *info = CreateFastOLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

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


    FastOLSCURRInfo* CreateFastOLSCurrInfo(const char *symbol, const char *trading) {
        FastOLSCURRInfo *info = new FastOLSCURRInfo();

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

    FastOLSCURRItemInfo* CreateFastOLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastOLSCURRItemInfo> *list = new AutoAllocatePointerList<FastOLSCURRItemInfo>(1, 1);
        FastOLSCURRItemInfo *info = list->NewItem();

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

    FastOLSCURRItemInfo* CreateFastOLRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId) {
        FastOLSCURRItemInfo *info = CreateFastOLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

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

    void Clear() { 
        this->fcf->OrderFond()->Clear();
        this->fcc->OrderCurr()->Clear();
    }
    
    void Test_OnIncrementalRefresh_OLR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;

        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOLSFONDItemInfo *quote = obi->BuyQuotes()->Start()->Data();
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

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID004", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);
        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi2 = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        FastOLSFONDItemInfo *item5 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOLSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOLSFONDItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOLSFONDItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID004", 10))
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
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        this->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
                item2->Allocator->Count() != 0 ||
                item3->Allocator->Count() != 0 ||
                item4->Allocator->Count() != 0)
            throw;
        if(this->fcf->OrderFond()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_FOND() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        FastOLSFONDInfo *info2 = CreateFastOLSFondInfo("SMB2", "TRADING001");
        FastOLSFONDItemInfo *newItem1 = CreateFastOLSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOLSFONDItemInfo *newItem2 = CreateFastOLSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OrderFond()->ProcessSnapshot(info2);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi3 = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOLSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);

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

    void Test_OnIncrementalRefresh_OLR_FOND_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;

        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOLSFONDItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Item(0);
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

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10,"ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 10,"ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10,"ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_FOND_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi2 = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        FastOLSFONDItemInfo *item5 = CreateFastOLRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetSellQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOLSFONDItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOLSFONDItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOLSFONDItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOLSFONDItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID004", 10))
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
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        this->Clear();
        if(this->fcf->OrderFond()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_FOND_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo;
        FastOLSFONDItemInfo *item1 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSFONDItemInfo *item2 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSFONDItemInfo *item3 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSFONDItemInfo *item4 = CreateFastOLRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OLR_FOND(info);

        FastOLSFONDInfo *info2 = CreateFastOLSFondInfo("SMB2", "TRADING001");
        FastOLSFONDItemInfo *newItem1 = CreateFastOLSFondItemInfo(7,-2, 1, 2, mdetSellQuote, "ENTRYID007");
        FastOLSFONDItemInfo *newItem2 = CreateFastOLSFondItemInfo(8,-2, 1, 2, mdetSellQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OrderFond()->ProcessSnapshot(info2);

        if(this->fcf->OrderFond()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi3 = this->fcf->OrderFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->SellQuotes()->Count() != 0)
            throw;

        OrderInfo<FastOLSFONDItemInfo> *obi = this->fcf->OrderFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOLSFONDItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        FastOLSFONDItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

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

    void Test_OnIncrementalRefresh_OLR_CURR_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;

        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOLSCURRItemInfo *quote = obi->BuyQuotes()->Item(0);
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

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
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
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->BuyQuotes()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi2 = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        FastOLSCURRItemInfo *item5 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOLSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOLSCURRItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOLSCURRItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID004", 10))
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
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        this->Clear();
        if(this->fcc->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        FastOLSCURRInfo *info2 = CreateFastOLSCurrInfo("SMB2", "TRADING001");
        FastOLSCURRItemInfo *newItem1 = CreateFastOLSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOLSCURRItemInfo *newItem2 = CreateFastOLSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OrderCurr()->ProcessSnapshot(info2);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi3 = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOLSCURRItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOLSCURRItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

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

    void Test_OnIncrementalRefresh_OLR_CURR_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;

        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOLSCURRItemInfo *quote = obi->SellQuotes()->Item(0);
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Item(0);
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

        quote = obi->SellQuotes()->Item(2);
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Item(3);
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OLR_CURR_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi2 = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        FastOLSCURRItemInfo *item5 = CreateFastOLRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetSellQuote, "ENTRYID002");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOLSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOLSCURRItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOLSCURRItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID004", 10))
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
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        this->Clear();
        if(this->fcc->OrderCurr()->UsedItemCount() != 0)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OLS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo;
        FastOLSCURRItemInfo *item1 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001");
        FastOLSCURRItemInfo *item2 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002");
        FastOLSCURRItemInfo *item3 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003");
        FastOLSCURRItemInfo *item4 = CreateFastOLRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OLR_CURR(info);

        FastOLSCURRInfo *info2 = CreateFastOLSCurrInfo("SMB2", "TRADING001");
        FastOLSCURRItemInfo *newItem1 = CreateFastOLSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "ENTRYID007");
        FastOLSCURRItemInfo *newItem2 = CreateFastOLSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OrderCurr()->ProcessSnapshot(info2);

        if(this->fcc->OrderCurr()->UsedItemCount() != 1)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi3 = this->fcc->OrderCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->SellQuotes()->Count() != 0)
            throw;

        OrderInfo<FastOLSCURRItemInfo> *obi = this->fcc->OrderCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOLSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOLSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);

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
        if(this->fcf->OrderFond()->SymbolsCount() != 0)
            throw;
        if(this->fcc->OrderCurr()->SymbolsCount() != 0)
            throw;
    }
    
    void Test() {
        TestDefaults();
        Test_OLR_FOND();
        Test_OLR_CURR();
    }
};

#endif //HFT_ROBOT_ORDERTESTER_H
