//
// Created by root on 27.10.16.
//

#ifndef HFT_ROBOT_TRADETESTER_H
#define HFT_ROBOT_TRADETESTER_H

#include "../FeedConnection.h"
#include <stdio.h>

class TradeTester {
    FeedConnection_FOND_TLR *fcf;
    FeedConnection_CURR_TLR *fcc;
public:

    TradeTester() {
        this->fcf = new FeedConnection_FOND_TLR("TLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->fcc = new FeedConnection_CURR_TLR("TLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
    }
    ~TradeTester() {
        delete this->fcf;
        delete this->fcc;
    }

    FastTLSFONDInfo* CreateFastTLSFondInfo(const char *symbol, const char *trading) {
        FastTLSFONDInfo *info = new FastTLSFONDInfo();

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

    FastTLSFONDItemInfo* CreateFastTLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastTLSFONDItemInfo> *list = new AutoAllocatePointerList<FastTLSFONDItemInfo>(1, 1);
        FastTLSFONDItemInfo *info = list->NewItem();

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

    FastTLSFONDItemInfo* CreateFastTLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId) {
        FastTLSFONDItemInfo *info = CreateFastTLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

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


    FastTLSCURRInfo* CreateFastTLSCurrInfo(const char *symbol, const char *trading) {
        FastTLSCURRInfo *info = new FastTLSCURRInfo();

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

    FastTLSCURRItemInfo* CreateFastTLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastTLSCURRItemInfo> *list = new AutoAllocatePointerList<FastTLSCURRItemInfo>(1, 1);
        FastTLSCURRItemInfo *info = list->NewItem();

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

    FastTLSCURRItemInfo* CreateFastTLRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId) {
        FastTLSCURRItemInfo *info = CreateFastTLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

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
        this->fcf->TradeFond()->Clear();
        this->fcc->TradeCurr()->Clear();
    }

    void Test_OnIncrementalRefresh_TLR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalTLRFONDInfo *info = new FastIncrementalTLRFONDInfo;

        FastTLSFONDItemInfo *item1 = CreateFastTLRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastTLSFONDItemInfo *item2 = CreateFastTLRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastTLSFONDItemInfo *item3 = CreateFastTLRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastTLSFONDItemInfo *item4 = CreateFastTLRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_TLR_FOND(info);

        if(this->fcf->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        TradeSession<FastTLSFONDItemInfo> *obi = this->fcf->TradeFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 1)
            throw;
        FastTLSFONDItemInfo *quote = obi->Trades()->Start()->Data();
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

        this->fcf->OnIncrementalRefresh_TLR_FOND(info);

        if(this->fcf->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->TradeFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 2)
            throw;
        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_TLR_FOND(info);

        if(this->fcf->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->TradeFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 3)
            throw;

        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->Trades()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_TLR_FOND(info);

        if(this->fcf->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->TradeFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 4)
            throw;

        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->Trades()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;

        quote = obi->Trades()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID004", 10))
            throw;
    }

    void Test_Clear() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalTLRFONDInfo *info = new FastIncrementalTLRFONDInfo;
        FastTLSFONDItemInfo *item1 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastTLSFONDItemInfo *item2 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastTLSFONDItemInfo *item3 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastTLSFONDItemInfo *item4 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_TLR_FOND(info);

        this->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->fcf->TradeFond()->UsedItemCount() != 0)
            throw;

        TradeSession<FastTLSFONDItemInfo> *obi = this->fcf->TradeFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->Trades()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_TLS_FOND() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalTLRFONDInfo *info = new FastIncrementalTLRFONDInfo;
        FastTLSFONDItemInfo *item1 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastTLSFONDItemInfo *item2 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastTLSFONDItemInfo *item3 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastTLSFONDItemInfo *item4 = CreateFastTLRFondItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_TLR_FOND(info);

        FastTLSFONDInfo *info2 = CreateFastTLSFondInfo("SMB2", "TRADING001");
        FastTLSFONDItemInfo *newItem1 = CreateFastTLSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastTLSFONDItemInfo *newItem2 = CreateFastTLSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OnFullRefresh_TLS_FOND(info2);

        if(this->fcf->TradeFond()->UsedItemCount() != 1)
            throw;

        TradeSession<FastTLSFONDItemInfo> *obi3 = this->fcf->TradeFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->Trades()->Count() != 0)
            throw;

        TradeSession<FastTLSFONDItemInfo> *obi = this->fcf->TradeFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->Trades()->Count() != 2)
            throw;

        FastTLSFONDItemInfo *qt1 = obi->Trades()->Item(0);
        FastTLSFONDItemInfo *qt2 = obi->Trades()->Item(1);

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

    void Test_OnIncrementalRefresh_TLR_CURR_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalTLRCURRInfo *info = new FastIncrementalTLRCURRInfo;

        FastTLSCURRItemInfo *item1 = CreateFastTLRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastTLSCURRItemInfo *item2 = CreateFastTLRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastTLSCURRItemInfo *item3 = CreateFastTLRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastTLSCURRItemInfo *item4 = CreateFastTLRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_TLR_CURR(info);

        if(this->fcc->TradeCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->Symbol(0)->Count() != 1)
            throw;
        TradeSession<FastTLSCURRItemInfo> *obi = this->fcc->TradeCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 1)
            throw;
        FastTLSCURRItemInfo *quote = obi->Trades()->Item(0);
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

        this->fcc->OnIncrementalRefresh_TLR_CURR(info);

        if(this->fcc->TradeCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->TradeCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 2)
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_TLR_CURR(info);

        if(this->fcc->TradeCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->TradeCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 3)
            throw;

        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->Trades()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_TLR_CURR(info);

        if(this->fcc->TradeCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->TradeCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->TradeCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 4)
            throw;

        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->Trades()->Item(2);
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->Trades()->Item(3);
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;
    }

    void Test_Clear_Curr() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalTLRCURRInfo *info = new FastIncrementalTLRCURRInfo;
        FastTLSCURRItemInfo *item1 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastTLSCURRItemInfo *item2 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastTLSCURRItemInfo *item3 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastTLSCURRItemInfo *item4 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_TLR_CURR(info);

        this->Clear();
        if(this->fcc->TradeCurr()->UsedItemCount() != 0)
            throw;

        TradeSession<FastTLSCURRItemInfo> *obi = this->fcc->TradeCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->Trades()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_TLS_CURR() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalTLRCURRInfo *info = new FastIncrementalTLRCURRInfo;
        FastTLSCURRItemInfo *item1 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001");
        FastTLSCURRItemInfo *item2 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002");
        FastTLSCURRItemInfo *item3 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003");
        FastTLSCURRItemInfo *item4 = CreateFastTLRCurrItemInfo("SBM1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004");

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_TLR_CURR(info);

        FastTLSCURRInfo *info2 = CreateFastTLSCurrInfo("SMB2", "TRADING001");
        FastTLSCURRItemInfo *newItem1 = CreateFastTLSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastTLSCURRItemInfo *newItem2 = CreateFastTLSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OnFullRefresh_TLS_CURR(info2);

        if(this->fcc->TradeCurr()->UsedItemCount() != 1)
            throw;

        TradeSession<FastTLSCURRItemInfo> *obi3 = this->fcc->TradeCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->Trades()->Count() != 0)
            throw;

        TradeSession<FastTLSCURRItemInfo> *obi = this->fcc->TradeCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->Trades()->Count() != 2)
            throw;

        FastTLSCURRItemInfo *qt1 = obi->Trades()->Start()->Data();
        FastTLSCURRItemInfo *qt2 = obi->Trades()->Start()->Next()->Data();

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

    void Test_OnIncrementalRefresh_TLR_FOND() {
        printf("Test_OnIncrementalRefresh_TLR_FOND_Add\n");
        Test_OnIncrementalRefresh_TLR_FOND_Add();
        printf("Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_TLR_CURR() {
        printf("Test_OnIncrementalRefresh_TLR_CURR_Add\n");
        Test_OnIncrementalRefresh_TLR_CURR_Add();
        printf("Test_Clear_Curr\n");
        Test_Clear_Curr();
    }

    void Test_TLR_CURR() {
        printf("Test_OnIncrementalRefresh_TLR_CURR\n");
        Test_OnIncrementalRefresh_TLR_CURR();
        printf("Test_OnFullRefresh_TLS_CURR\n");
        Test_OnFullRefresh_TLS_CURR();
    }

    void Test_TLR_FOND() {
        printf("Test_OnIncrementalRefresh_TLR_FOND\n");
        Test_OnIncrementalRefresh_TLR_FOND();
        printf("Test_OnFullRefresh_TLS_FOND\n");
        Test_OnFullRefresh_TLS_FOND();
    }

    void TestDefaults() {
        if(this->fcf->TradeFond()->SymbolsCount() != 0)
            throw;
        if(this->fcc->TradeCurr()->SymbolsCount() != 0)
            throw;
    }

    void Test() {
        TestDefaults();
        Test_TLR_FOND();
        Test_TLR_CURR();
    }
};

#endif //HFT_ROBOT_TRADETESTER_H
