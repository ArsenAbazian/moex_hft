//
// Created by root on 10.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTEST_H
#define HFT_ROBOT_FEEDCONNECTIONTEST_H

#include "../FeedConnection.h"
#include <stdio.h>

class TestTemplateItemInfo {
public:
    MDUpdateAction  m_action;
    const char*     m_symbol;
    const char*     m_tradingSession;
    MDEntryType     m_entryType;
    const char*     m_entryId;
    Decimal         m_entryPx;
    Decimal         m_entrySize;
    int             m_rptSeq;

    TestTemplateItemInfo(MDUpdateAction action, MDEntryType entryType, const char *symbol, const char *sessionId, const char *entryId, int rptSeq, int pxm, INT64 pxe, int sizem, INT64 sizee) {
        this->m_action = action;
        this->m_entryType = entryType;
        this->m_symbol = symbol;
        this->m_tradingSession = sessionId;
        this->m_entryPx.Set(pxm, pxe);
        this->m_entrySize.Set(sizem, sizee);
        this->m_rptSeq = rptSeq;
    }
    TestTemplateItemInfo(const char *symbol, const char *entryId, int rptSeq) {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_symbol = symbol;
        this->m_tradingSession = "session1";
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
        this->m_rptSeq = rptSeq;
    }
};

class TestTemplateInfo {
public:
    FeedConnectionMessage   m_templateId;
    int                     m_msgSeqNo;
    bool                    m_routeFirst;
    bool                    m_lastMessage;
    int                     m_itemsCount;
    int                     m_rptSec;
    TestTemplateItemInfo*   m_items[8];

    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo) {
        this->m_templateId = templateId;
        this->m_msgSeqNo = msgSeqNo;
        this->m_itemsCount = 0;
    }
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, TestTemplateItemInfo **items, int itemCount) : TestTemplateInfo(templateId, msgSeqNo) {
        this->m_itemsCount = itemCount;
        for(int i = 0; i < itemCount; i++)
            this->m_items[i] = items[i];
    }
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, TestTemplateItemInfo **items, int itemCount, int rptSeq) : TestTemplateInfo(templateId, msgSeqNo, items, itemCount) {
        this->m_rptSec = rptSeq;
    }
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, bool routeFirst, bool lastMessage, TestTemplateItemInfo **items, int itemCount, int rptSeq) :
            TestTemplateInfo(templateId, msgSeqNo, items, itemCount, rptSeq) {
        this->m_routeFirst = routeFirst;
        this->m_lastMessage = lastMessage;
    }
};

class OrderBookTester {
    FeedConnection_FOND_OBR *fcf;
    FeedConnection_FOND_OBS *fcs;
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
        this->fcs = new FeedConnection_FOND_OBS("OBS", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);

    }
    ~OrderBookTester() {
        delete this->fcf;
        delete this->fcc;
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

    void Clear() {
        this->fcf->OrderBookFond()->Clear();
        this->fcc->OrderBookCurr()->Clear();
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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

    void Test_OnFullRefresh_OBS_FOND() {
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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

    void Test_OnIncrementalRefresh_OBR_CURR_Add() {
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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
        this->Clear();
        this->TestDefaults();

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

    void TestDefaults() {
        if(this->fcf->OrderBookFond()->SymbolsCount() != 0)
            throw;
        if(this->fcf->OrderBookFond()->TradingSessionsCount() != 0)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 0)
            throw;
        if(this->fcc->OrderBookCurr()->TradingSessionsCount() != 0)
            throw;
    }

    void TestTableItem_CorrectBegin() {
        OrderBookTableItem<FastOBSFONDItemInfo> *tb = new OrderBookTableItem<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        if(!tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTableItem_IncorrectBegin() {
        OrderBookTableItem<FastOBSFONDItemInfo> *tb = new OrderBookTableItem<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
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
        OrderBookTableItem<FastOBSFONDItemInfo> *tb = new OrderBookTableItem<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID002");
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

        FastOBSFONDItemInfo *item3 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID003");
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

    void TestTableItem_CorrectApplySnapshot() {
        OrderBookTableItem<FastOBSFONDItemInfo> *tb = new OrderBookTableItem<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID002");
        item2->RptSeq = 3;
        item2->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item2))
            throw;

        FastOBSFONDItemInfo *item3 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID003");
        item3->RptSeq = 4;
        item3->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item3))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID004");
        item4->RptSeq = 5;
        item4->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID005");
        item5->RptSeq = 3;
        item5->MDUpdateAction = mduaAdd;

        tb->ProcessSnapshotMessages(&item5, 1);
        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 3)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
    }

    void TestTable_CorrectBegin() {

        MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;

        if(!table->ProcessIncremental(item1))
            throw;

        delete table;
    }

    void TestTable_IncorrectBegin() {
        MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 2;

        if(table->ProcessIncremental(item1))
            throw;

        delete table;
    }

    void TestTable_SkipMessages() {
        MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;

        if(!table->ProcessIncremental(item1))
            throw;

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item2->RptSeq = 3;

        if(table->ProcessIncremental(item2))
            throw;

        delete table;
    }

    void TestTable_CorrectApplySnapshot() {
        MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID002");
        item2->RptSeq = 3;

        if(table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID003");
        item3->RptSeq = 4;

        if(table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004");
        item4->RptSeq = 5;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID005");
        item5->RptSeq = 3;

        FastOBSFONDInfo *info = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookTableItem<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info->GroupMDEntries, 1);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(!table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 3)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
    }

    void TestTable_IncorrectApplySnapshot() {
        MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID002");
        item2->RptSeq = 4;

        if(table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID003");
        item3->RptSeq = 5;

        if(table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004");
        item4->RptSeq = 6;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID005");
        item5->RptSeq = 2;

        FastOBSFONDInfo *info = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookTableItem<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info->GroupMDEntries, 1);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 2)
            throw;
        if(table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 2)
            throw;
    }

    void TestTable_IncorrectApplySnapshot_WhenMessageSkipped() {
        MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID002");
        item2->RptSeq = 4;

        if(table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004");
        item4->RptSeq = 6;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID005");
        item5->RptSeq = 3;

        FastOBSFONDInfo *info = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookTableItem<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info->GroupMDEntries, 1);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 4)
            throw;
        if(table->EndProcessSnapshot())
            throw;
    }

    void SendHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastHeartbeatInfo *info = new FastHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeHeartbeatInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastOBSFONDItemInfo* CreateObrFondItemInfo(TestTemplateItemInfo *tmp) {
        FastOBSFONDItemInfo *info = new FastOBSFONDItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;
        info->AllowMDEntryType = true;
        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;
        info->AllowMDEntryPx = true;
        info->MDEntryPx.Assign(&tmp->m_entryPx);
        info->AllowMDEntrySize = true;
        info->MDEntrySize.Assign(&tmp->m_entrySize);
        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    void SendObrFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOBRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());

    }
    void SendObsFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOBSFONDInfo *info = new FastOBSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOBSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedConnectionMessage::fcmHeartBeat:
                SendHearthBeatMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND:
                SendObrFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OBS_FOND:
                SendObsFondMessage(conn, tmp);
            default:
                break;
        }
    }

    void SendMessages(FeedConnection *conn, TestTemplateInfo **templates, int templatesCount) {
        for(int i = 0; i < templatesCount; i++)
            SendMessage(conn, templates[i]);
    }

    void TestConnection_EmptyTest() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();

        SendMessages(fcf, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();

        SendMessages(fcf, new TestTemplateInfo*[3] {
            new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                 new TestTemplateItemInfo*[2] {
                                    new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY1", 1, 1, 1, 1, 1),
                                    new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY2", 2, 2, 1, 2, 1),
                                 }, 2),
            new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                 new TestTemplateItemInfo*[1] {
                                         new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY3", 3, 3, 1, 3, 1),
                                 }, 1),
            new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                 new TestTemplateItemInfo*[1] {
                                         new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY4", 4, 3, 1, 3, 1),
                                 }, 1)
        }, 3);


        if(!fcf->ApplyPacketSequence())
            throw;
        if(fcf->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(fcf->OrderBookFond()->GetItem("SYMBOL1", "SESSION1")->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item symbol1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnection_TestIncMessagesLost_AndWhenAppeared() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 1) // cell for rptseq 3 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1]->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry4", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(fcf->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry4", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(fcf->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(!fcf->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(fcf->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(!fcf->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(fcf->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestIncMessageLost_AndWaitTimerElapsed() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();
        fcf->WaitIncrementalMaxTimeMs(200);
        fcs->WaitSnapshotMaxTimeMs(200);
        fcs->Stop();

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        OrderBookTableItem<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(fcf->m_waitTimer->ElapsedMilliseconds() < fcf->WaitIncrementalMaxTimeMs());
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        //entering snapshot mode
        if(fcs->State() != FeedConnectionState::fcsListen)
            throw;
        // timer should be stopped
        if(fcf->m_waitTimer->Active())
            throw;
    }
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcf->ClearMessages();
        fcf->WaitIncrementalMaxTimeMs(50);

        SendMessages(fcf, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 1),
                                             new TestTemplateItemInfo("symbol2", "entry1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 4),
                                             new TestTemplateItemInfo("symbol2", "entry1", 4),
                                     }, 2)
        }, 2);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(fcf->m_waitTimer->ElapsedMilliseconds() < fcf->WaitIncrementalMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(fcs, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 2),
                                             new TestTemplateItemInfo("symbol1", "entry1", 3),
                                     }, 2, 4)
        }, 1);
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderBookTableItem<FastOBSFONDItemInfo> *item1 = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        OrderBookTableItem<FastOBSFONDItemInfo> *item2 = fcf->OrderBookFond()->GetItem("symbol2", "session1");
        if(item1->EntriesQueue()->HasEntries())
            throw;
        if(!item2->EntriesQueue()->HasEntries())
            throw;
    }
    void TestConnection() {
        printf("TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
        printf("TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();
    }

    void TestOrderBookTableItem() {
        printf("TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("TestTableItem_CorrectApplySnapshot\n");
        TestTableItem_CorrectApplySnapshot();
        printf("TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
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

    void Test() {
        TestDefaults();
        TestStringIdComparer();
        TestOrderBookTableItem();
        TestConnection();
        Test_OBR_FOND();
        Test_OBR_CURR();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTEST_H
