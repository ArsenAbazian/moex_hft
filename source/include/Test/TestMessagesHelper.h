//
// Created by root on 15.12.16.
//

#ifndef HFT_ROBOT_TESTMESSAGESHELPER_H
#define HFT_ROBOT_TESTMESSAGESHELPER_H

#include "TestTemplateInfo.h"
#include "../FeedConnection.h"
#include <stdio.h>
#include <memory.h>

class TestMessagesHelper {
    const char *symbols[100];
    int rptSeq[100];
    int symbolsCount = 0;

    int CalcMsgCount(const char *msg) {
        int len = strlen(msg);
        if(len == 0)
            return 0;
        int res = 0;
        for(int i = 0; i < len; i++) {
            if(msg[i] == ',')
                res++;
        }
        return res + 1;
    }

    int CalcWordLength(const char *msg, int startIndex) {
        int res = 0;
        for(int i = startIndex; msg[i] != ',' && msg[i] != '\0'; i++)
            res++;
        return res;
    }

    void TrimWord(const char *msg, int startIndex, int len, int *start, int *end) {
        *start = startIndex;
        *end = startIndex + len - 1;

        while(msg[*start] == ' ')
            (*start)++;
        while(msg[*end] == ' ')
            (*end)--;
        return ;
    }

    int SkipToNextWord(const char *msg, int start) {
        while(msg[start] == ' ')
            start++;
        return start;
    }

    char** Split(const char *msg, int start, int end, int *count) {
        char **keys = new char*[100];
        *count = 0;
        for(int i = start; i <= end; i++) {
            if(msg[i] == ' ' || i == end) {
                if(i == end) i++;
                keys[*count] = new char[i - start + 1];
                memcpy(keys[*count], &msg[start], i - start);
                keys[*count][i-start] = '\0';
                if(i == end)
                    break;
                (*count)++;
                start = SkipToNextWord(msg, i);
                i = start - 1;
            }
        }
        return keys;
    }

    int KeyIndex(char **keys, int keysCount, const char *key) {
        for(int i = 0; i < keysCount; i++) {
            if(StringIdComparer::Equal(keys[i], key))
                return i;
        }
        return -1;
    }

    int KeyIndex(char **keys, int keysCount, const char *key, int startIndex) {
        for(int i = startIndex; i < keysCount; i++) {
            if(StringIdComparer::Equal(keys[i], key))
                return i;
        }
        return -1;
    }

    bool HasKey(char **keys, int keysCount, const char *key) {
        return KeyIndex(keys, keysCount, key) != -1;
    }

    TestTemplateInfo *CreateTemplate(char **keys, int keysCount) {
        TestTemplateInfo *info = new TestTemplateInfo();

        info->m_lost = HasKey(keys, keysCount, "lost");
        info->m_skip = HasKey(keys, keysCount, "skip_if_suspend");
        if(HasKey(keys, keysCount, "obr")) {
            info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND;
        }
        else if(HasKey(keys, keysCount, "olr")) {
            info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND;
        }
        else if(HasKey(keys, keysCount, "tlr")) {
            info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND;
        }
        else if(HasKey(keys, keysCount, "obs")) {
            info->m_templateId = FeedConnectionMessage::fmcFullRefresh_OBS_FOND;
            info->m_symbol = keys[KeyIndex(keys, keysCount, "obs") + 1];
        }
        else if(HasKey(keys, keysCount, "ols")) {
            info->m_templateId = FeedConnectionMessage::fmcFullRefresh_OLS_FOND;
            info->m_symbol = keys[KeyIndex(keys, keysCount, "ols") + 1];
        }
        else if(HasKey(keys, keysCount, "tls")) {
            info->m_templateId = FeedConnectionMessage::fmcFullRefresh_TLS_FOND;
            info->m_symbol = keys[KeyIndex(keys, keysCount, "tls") + 1];
        }
        else if(HasKey(keys, keysCount, "wait_snap")) {
            info->m_templateId = FeedConnectionMessage::fcmHeartBeat;
            info->m_wait = true;
            return info;
        }
        else if(HasKey(keys, keysCount, "hbeat")) {
            info->m_templateId = FeedConnectionMessage::fcmHeartBeat;
            return info;
        }

        bool isSnap = HasKey(keys, keysCount, "obs") || HasKey(keys, keysCount, "ols") || HasKey(keys, keysCount, "tls");
        if(isSnap) {
            info->m_session = "session1";
            if(HasKey(keys, keysCount, "begin")) {
                info->m_routeFirst = true;
            }
            if(HasKey(keys, keysCount, "rpt")) {
                info->m_rptSec = atoi((const char *)(keys[KeyIndex(keys, keysCount, "rpt") + 1]));
            }
            if(HasKey(keys, keysCount, "lastmsg")) {
                info->m_lastMsgSeqNoProcessed = atoi((const char *)(keys[KeyIndex(keys, keysCount, "lastmsg") + 1]));
            }
            else info->m_lastMsgSeqNoProcessed = 1;
            if(HasKey(keys, keysCount, "end"))
                info->m_lastFragment = true;
        }

        int entryIndex = -1;
        int itemIndex = 0;
        while((entryIndex = KeyIndex(keys, keysCount, "entry", entryIndex + 1)) != -1) {
            TestTemplateItemInfo *item = new TestTemplateItemInfo();
            item->m_tradingSession = "session1";
            item->m_action = MDUpdateAction::mduaAdd;
            if(StringIdComparer::Equal("del", keys[entryIndex + 1])) {
                item->m_action = MDUpdateAction::mduaDelete;
                entryIndex++;
            }
            else if(StringIdComparer::Equal("change", keys[entryIndex + 1])) {
                item->m_action = MDUpdateAction::mduaDelete;
                entryIndex++;
            }
            item->m_symbol = keys[entryIndex + 1];
            item->m_entryId = keys[entryIndex + 2];
            item->m_entryType = MDEntryType::mdetBuyQuote;
            item->m_entryPx.Set(1, 1);
            item->m_entrySize.Set(1, 1);
            info->m_items[itemIndex] = item;
            info->m_itemsCount++;

            itemIndex++;
        }

        return info;
    }

    void FillMsg(TestTemplateInfo **temp, int count, const char *msg) {
        int startIndex = 0;
        for(int i = 0; i < count; i++) {
            int len = CalcWordLength(msg, startIndex);
            int start = 0, end = 0;
            TrimWord(msg, startIndex, len, &start, &end);
            int keysCount = 0;
            char **keys = Split(msg, start, end, &keysCount);
            temp[i] = CreateTemplate(keys, keysCount);
            startIndex += len + 1;
        }
    }

    int GetRptSeqFor(const char *symbol) {
        for(int i = 0; i < this->symbolsCount; i++) {
            if(StringIdComparer::Equal(this->symbols[i], symbol)) {
                rptSeq[i]++;
                return rptSeq[i];
            }
        }
        rptSeq[symbolsCount] = 1;
        symbols[symbolsCount] = symbol;
        symbolsCount++;
        return 1;
    }

    void FillRptSeq(TestTemplateInfo **msg, int count) {
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < msg[i]->m_itemsCount; j++) {
                msg[i]->m_items[j]->m_rptSeq = GetRptSeqFor(msg[i]->m_items[j]->m_symbol);
            }
        }
    }

public:

    FastOLSFONDInfo* CreateOLSFondInfo(const char *symbol, const char *trading) {
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

    FastOLSFONDItemInfo* CreateOLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

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

    FastOLSFONDItemInfo* CreateOLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastOLSFONDItemInfo *info = CreateOLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOLSFONDItemInfo* CreateOLRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }
    FastOLSCURRInfo* CreateOLSCurrInfo(const char *symbol, const char *trading) {
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

    FastOLSCURRItemInfo* CreateOLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

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

    FastOLSCURRItemInfo* CreateOLRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastOLSCURRItemInfo *info = CreateOLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOBSFONDInfo* CreateOBSFondInfo(const char *symbol, const char *trading) {
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

    FastOBSFONDItemInfo* CreateOBSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

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

    FastOBSFONDItemInfo* CreateOBRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastOBSFONDItemInfo *info = CreateOBSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOBSFONDItemInfo* CreateOBRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOBRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }
    FastOBSCURRInfo* CreateOBSCurrInfo(const char *symbol, const char *trading) {
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

    FastOBSCURRItemInfo* CreateOBSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

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

    FastOBSCURRItemInfo* CreateOBRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastOBSCURRItemInfo *info = CreateOBSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastTLSFONDInfo* CreateTLSFondInfo(const char *symbol, const char *trading) {
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

    FastTLSFONDItemInfo* CreateTLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

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

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastTLSFONDItemInfo *info = CreateTLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateTLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateTLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    FastTLSCURRInfo* CreateTLSCurrInfo(const char *symbol, const char *trading) {
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

    FastTLSCURRItemInfo* CreateTLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId, int rptSeq) {

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
        info->RptSeq = rptSeq;

        return info;
    }

    FastTLSCURRItemInfo* CreateTLRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastTLSCURRItemInfo *info = CreateTLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId, rptSeq);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastIncrementalMSRFONDInfo* CreateMSSFondInfo(const char *symbol, const char *trading) {
        FastIncrementalMSRFONDInfo *info = new FastIncrementalMSRFONDInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        /*info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);*/

        return info;
    }

    FastIncrementalMSRFONDItemInfo* CreateMSRFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastIncrementalMSRFONDItemInfo> *list = new AutoAllocatePointerList<FastIncrementalMSRFONDItemInfo>(1, 1);
        FastIncrementalMSRFONDItemInfo *info = list->NewItem();

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

    FastIncrementalMSRFONDItemInfo* CreateMSRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastIncrementalMSRFONDItemInfo *info = CreateMSRFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastIncrementalMSRFONDItemInfo* CreateMSRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateMSRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastIncrementalMSRFONDItemInfo* CreateMSRFondItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateMSRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    FastIncrementalMSRCURRInfo* CreateMSSCurrInfo(const char *symbol, const char *trading) {
        FastIncrementalMSRCURRInfo *info = new FastIncrementalMSRCURRInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        /*info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);*/

        return info;
    }

    FastIncrementalMSRCURRItemInfo* CreateMSRCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId, int rptSeq) {

        AutoAllocatePointerList<FastIncrementalMSRCURRItemInfo> *list = new AutoAllocatePointerList<FastIncrementalMSRCURRItemInfo>(1, 1);
        FastIncrementalMSRCURRItemInfo *info = list->NewItem();

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
        info->RptSeq = rptSeq;

        return info;
    }

    FastIncrementalMSRCURRItemInfo* CreateMSRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastIncrementalMSRCURRItemInfo *info = CreateMSRCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId, rptSeq);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOLSFONDItemInfo* CreateOLRFondItemInfo(TestTemplateItemInfo *tmp) {
        FastOLSFONDItemInfo *info = new FastOLSFONDItemInfo();
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

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(TestTemplateItemInfo *tmp) {
        FastTLSFONDItemInfo *info = new FastTLSFONDItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;
        //info->AllowMDEntryType = true;
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

    void SendHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastHeartbeatInfo *info = new FastHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeHeartbeatInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
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
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOBSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendOLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOLRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());

    }

    void SendOLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOLSFONDInfo *info = new FastOLSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOLSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendTLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalTLRFONDInfo *info = new FastIncrementalTLRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalTLRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());

    }

    void SendTLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastTLSFONDInfo *info = new FastTLSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeTLSFONDInfo(info);
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
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
                SendOLRFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                SendOLSFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
                SendTLRFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                SendTLSFondMessage(conn, tmp);
                break;
            default:
                break;
        }
    }

    void SendMessages(FeedConnection *conn, TestTemplateInfo **templates, int templatesCount) {
        for(int i = 0; i < templatesCount; i++)
            SendMessage(conn, templates[i]);
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        int incMsgCount = CalcMsgCount(inc);
        int snapMsgCount = CalcMsgCount(snap);

        TestTemplateInfo **inc_msg = new TestTemplateInfo*[incMsgCount];
        TestTemplateInfo **snap_msg = new TestTemplateInfo*[snapMsgCount];

        FillMsg(inc_msg, incMsgCount, inc);
        FillMsg(snap_msg, snapMsgCount, snap);
        FillRptSeq(inc_msg, incMsgCount);

        int inc_index = 0;
        int snap_index = 0;

        Stopwatch w;
        w.Start(1);
        while(inc_index < incMsgCount || snap_index < snapMsgCount) {
            if(inc_index < incMsgCount && !inc_msg[inc_index]->m_lost) {
                inc_msg[inc_index]->m_msgSeqNo = inc_index + 1;
                SendMessage(fci, inc_msg[inc_index]);
            }
            fci->Listen_Atom_Incremental_Core();
            if(inc_index < incMsgCount && inc_msg[inc_index]->m_wait) {
                if(!fci->m_waitTimer->Active())
                    throw;
                while(!fci->m_waitTimer->IsElapsedMilliseconds(fci->WaitIncrementalMaxTimeMs()) && fcs->State() == FeedConnectionState::fcsSuspend)
                    fci->Listen_Atom_Incremental_Core();
                fci->Listen_Atom_Incremental_Core();
            }
            if(inc_index < incMsgCount)
                inc_index++;
            if(fcs->State() == FeedConnectionState::fcsListenSnapshot) {
                if (snap_index < snapMsgCount && !snap_msg[snap_index]->m_lost) {
                    snap_msg[snap_index]->m_msgSeqNo = snap_index + 1;
                    if(snap_msg[snap_index]->m_templateId != FeedConnectionMessage::fcmHeartBeat && (snap_msg[snap_index]->m_symbol == 0 || snap_msg[snap_index]->m_session == 0))
                        throw;
                    SendMessage(fcs, snap_msg[snap_index]);
                }
                if(snap_index < snapMsgCount)
                    snap_index++;
                fcs->Listen_Atom_Snapshot_Core();
            }
            else {
                if (snap_index < snapMsgCount && snap_msg[snap_index]->m_skip) {
                    snap_index++;
                }
            }
            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
        fci->Listen_Atom_Incremental_Core(); // emulate endless loop
    }

    void Clear() {
        this->symbolsCount = 0;
        for(int i = 0; i < 100; i++) {
            this->symbols[i] = 0;
            this->rptSeq[i] = 0;
        }
    }
};

#endif //HFT_ROBOT_TESTMESSAGESHELPER_H
