//
// Created by root on 15.12.16.
//

#ifndef HFT_ROBOT_TESTMESSAGESHELPER_H
#define HFT_ROBOT_TESTMESSAGESHELPER_H
#include "../Settings.h"

#ifdef TEST

#include "../Managers/WinSockManager.h"
#include "TestTemplateInfo.h"
#include "../Feeds/FeedConnection.h"
#include <stdio.h>
#include <memory.h>

class WinSockManager;
class SocketMessageInfo {
public:
    WinSockManager      *m_manager;
    bool                m_canRecv;
    unsigned char       m_buffer[512];
    int                 m_bufferLength;
};

class TestFeedMessageInfo {
public:
    FeedConnection      *m_feed;
    int                  m_templatesCount;
    TestTemplateInfo    **m_templates;
};

typedef enum _TestMessagesHelperMode {
    tmhmFond,
    tmhmCurr,
    tmhmForts
}TestMessagesHelperMode;

class TestMessagesHelper {
public:
    static PointerList<SocketMessageInfo> *m_sockMessages;
    static bool             SkipTimeOutCheck;

    char                    **m_keys;
    int                     m_keysCount;

    TestFeedMessageInfo     m_feedInfo[10];
    int                     m_feedInfoCount;

    const char              *m_symbols[100];
    int                     m_rptSeq[100];
    int                     m_symbolsCount;
    TestMessagesHelperMode  m_mode;

    FixProtocolManager      *m_fixManager;
    FastProtocolManager     *m_fastManager;
    SocketBuffer            *m_buffer;
    char                    m_applVerId[10];
    char                    m_msgType[10];
    char                    m_protocolVersion[10];
    char                    m_senderCompId[10];
    char                    m_targetCompId[10];

private:
void AddFeedInfo(FeedConnection *feed, TestTemplateInfo **tmp, int templatesCount) {
        this->m_feedInfo[this->m_feedInfoCount].m_feed = feed;
        this->m_feedInfo[this->m_feedInfoCount].m_templates = tmp;
        this->m_feedInfo[this->m_feedInfoCount].m_templatesCount = templatesCount;
        this->m_feedInfoCount++;
    }

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

    void Split(const char *msg, int start, int end) {
        this->m_keys = new char*[100];
        this->m_keysCount = 0;
        for(int i = start; i <= end; i++) {
            if(msg[i] == ' ' || i == end) {
                if(i == end) i++;
                this->m_keys[this->m_keysCount] = new char[i - start + 1];
                memcpy(this->m_keys[this->m_keysCount], &msg[start], i - start);
                this->m_keys[this->m_keysCount][i-start] = '\0';
                if(i == end)
                    break;
                this->m_keysCount++;
                start = SkipToNextWord(msg, i);
                i = start - 1;
            }
        }
    }

    int KeyIndex(const char *key) {
        for(int i = 0; i < this->m_keysCount; i++) {
            if(StringIdComparer::Equal(this->m_keys[i], key))
                return i;
        }
        return -1;
    }

    int KeyIndex(const char *key, int startIndex) {
        for(int i = startIndex; i < this->m_keysCount; i++) {
            if(StringIdComparer::Equal(this->m_keys[i], key))
                return i;
        }
        return -1;
    }

    bool HasKey(const char *key) {
        return KeyIndex(key) != -1;
    }
    bool StartKey(const char *key) {
        return KeyIndex(key) == 0;
    }

    TestTemplateInfo *CreateTemplate() {
        TestTemplateInfo *info = new TestTemplateInfo();
        if(this->m_keysCount == 0)
            return info;

        info->m_msgSeqNo = 0;
        info->m_lost = HasKey("lost");
        info->m_skip = HasKey("skip_if_suspend");
        if(HasKey("msgSeqNo")) {
            info->m_msgSeqNo = atoi(this->m_keys[KeyIndex("msgSeqNo") + 1]);
        }
        if(HasKey("logout")) {
            info->m_templateId = FeedTemplateId::fmcLogout;
            return info;
        }
        else if(HasKey("logon")) {
            info->m_templateId = FeedTemplateId::fmcLogon;
            if(HasKey("sender"))
                info->m_senderId = this->m_keys[KeyIndex("sender") + 1];
            else
                info->m_senderId = 0;
            if(HasKey("pass"))
                info->m_pass = this->m_keys[KeyIndex("pass") + 1];
            else
                info->m_pass = 0;
            return info;
        }
        else if(HasKey("olr")) {
            info->m_templateId = this->IsCurr()? FeedTemplateId::fmcIncrementalRefresh_OLR_CURR:
                                 FeedTemplateId::fmcIncrementalRefresh_OLR_FOND;
        }
        else if(HasKey("obr")) {
            if(this->IsForts())
                info->m_templateId = FeedTemplateId::fortsIncremental;
            else
                throw;
        }
        else if(HasKey("tlr")) {
            info->m_templateId = this->IsCurr()? FeedTemplateId::fmcIncrementalRefresh_TLR_CURR:
                                 FeedTemplateId::fmcIncrementalRefresh_TLR_FOND;
        }
        else if(HasKey("obs")) {
            if(this->IsForts())
                info->m_templateId = FeedTemplateId::fortsSnapshot;
            else
                throw;
            int snapIndex = KeyIndex("obs");
            if(KeyIndex("begin") == snapIndex + 1)
                snapIndex++;
            info->m_symbol = this->m_keys[snapIndex + 1];
            if(KeyIndex("sid") == snapIndex + 2)
                snapIndex++;
            info->m_securityId = atoi(this->m_keys[snapIndex + 2]);
        }
        else if(HasKey("ols")) {
            info->m_templateId = this->IsCurr()? FeedTemplateId::fmcFullRefresh_OLS_CURR:
                                 FeedTemplateId::fmcFullRefresh_OLS_FOND;
            int snapIndex = KeyIndex("ols");
            if(KeyIndex("begin") == snapIndex + 1)
                snapIndex++;
            info->m_symbol = this->m_keys[snapIndex + 1];
        }
        else if(HasKey("tls")) {
            info->m_templateId = this->IsCurr() ? FeedTemplateId::fmcFullRefresh_TLS_CURR :
                                 FeedTemplateId::fmcFullRefresh_TLS_FOND;
            int snapIndex = KeyIndex("tls");
            if (KeyIndex("begin") == snapIndex + 1)
                snapIndex++;
            info->m_symbol = this->m_keys[snapIndex + 1];
        }
        else if(HasKey("idf")) {
            info->m_templateId = FeedTemplateId::fmcSecurityDefinition;
            int idfIndex = KeyIndex("idf");
            if (HasKey("totNumReports"))
                info->m_totNumReports = atoi(this->m_keys[KeyIndex("totNumReports") + 1]);
            info->m_symbol = this->m_keys[idfIndex + 1];
        }
        else if(HasKey("isf")) {
            info->m_templateId = FeedTemplateId::fmcSecurityStatus;
            int isfIndex = KeyIndex("isf");
            info->m_symbol = this->m_keys[isfIndex + 1];
            info->m_session = this->m_keys[isfIndex + 2];
            info->m_sessionSubId = this->m_keys[isfIndex + 3];
            info->m_sessionStatus = (SecurityStatus)atoi(this->m_keys[isfIndex + 4]);
            info->m_auctionIndicator = atoi(this->m_keys[isfIndex + 5]);

            return info;
        }
        else if(HasKey("wait_snap")) {
            if(IsForts())
                info->m_templateId = FeedTemplateId::fortsHearthBeat;
            else
                info->m_templateId = FeedTemplateId::fcmHeartBeat;
            info->m_wait = true;
            return info;
        }
        else if(HasKey("hbeat")) {
            if(IsForts())
                info->m_templateId = FeedTemplateId::fortsHearthBeat;
            else
                info->m_templateId = FeedTemplateId::fcmHeartBeat;
            return info;
        }

        bool isSnap = HasKey("obs") || HasKey("ols") || HasKey("tls") || HasKey("mss");
        bool isIdf = HasKey("idf");
        if(isSnap) {
            info->m_session = "session1";
            if(HasKey("begin")) {
                info->m_routeFirst = true;
            }
            if(HasKey("rpt")) {
                info->m_rptSec = atoi((const char *)(this->m_keys[KeyIndex("rpt") + 1]));
            }
            if(HasKey("lastmsg")) {
                info->m_lastMsgSeqNoProcessed = atoi((const char *)(this->m_keys[KeyIndex("lastmsg") + 1]));
            }
            else info->m_lastMsgSeqNoProcessed = 1;
            if(HasKey("end"))
                info->m_lastFragment = true;
        }

        if(isIdf) {
            int entryIndex = 0;
            int itemIndex = 0;

            while((entryIndex = KeyIndex("session", entryIndex)) != -1) {
                TestTemplateItemInfo *item = new TestTemplateItemInfo();
                entryIndex++;
                item->m_tradingSession = this->m_keys[entryIndex];
                entryIndex++;
                if(KeyIndex("status", entryIndex) == entryIndex) {
                    entryIndex++;
                    item->m_sessionStatus = atoi(this->m_keys[entryIndex]);
                    entryIndex++;
                }

                info->m_items[itemIndex] = item;
                info->m_itemsCount++;

                itemIndex++;
            }
            return info;
        }

        int entryIndex = -1;
        int itemIndex = 0;
        while((entryIndex = KeyIndex("entry", entryIndex + 1)) != -1) {
            TestTemplateItemInfo *item = new TestTemplateItemInfo();
            item->m_tradingSession = "session1";
            item->m_action = MDUpdateAction::mduaAdd;
            if(StringIdComparer::Equal("del", this->m_keys[entryIndex + 1])) {
                item->m_action = MDUpdateAction::mduaDelete;
                entryIndex++;
            }
            else if(StringIdComparer::Equal("change", this->m_keys[entryIndex + 1])) {
                item->m_action = MDUpdateAction::mduaChange;
                entryIndex++;
            }
            item->m_symbol = this->m_keys[entryIndex + 1];
            if(IsForts()) {
                if(KeyIndex("sid", entryIndex + 2) != entryIndex + 2)
                    throw;
                item->m_securityId = atoi(this->m_keys[entryIndex + 3]);
                entryIndex+=2;
            }
            if(IsForts())
                item->m_entryIdInt = atoi(this->m_keys[entryIndex + 2]);
            else
                item->m_entryId = this->m_keys[entryIndex + 2];
            item->m_entryPx.Set(2, 1);
            if(KeyIndex("px", entryIndex + 3) == entryIndex + 3)
                item->m_entryPx.Set(atoi(this->m_keys[entryIndex + 4]), 0);
            item->m_entryType = MDEntryType::mdetBuyQuote;
            item->m_entrySize.Set(2, 1);
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
            Split(msg, start, end);
            temp[i] = CreateTemplate();
            startIndex += len + 1;
        }
    }

    int GetRptSeqFor(const char *symbol) {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            if(StringIdComparer::Equal(this->m_symbols[i], symbol)) {
                m_rptSeq[i]++;
                return m_rptSeq[i];
            }
        }
        m_rptSeq[m_symbolsCount] = 1;
        m_symbols[m_symbolsCount] = symbol;
        m_symbolsCount++;
        return 1;
    }

    void FillRptSeq(TestTemplateInfo **msg, int count) {
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < msg[i]->m_itemsCount; j++) {
                msg[i]->m_items[j]->m_rptSeq = GetRptSeqFor(msg[i]->m_items[j]->m_symbol);
            }
        }
    }
    void FillSnapRptSeq(TestTemplateInfo **msg, int count) {
        int lastRptSeq = 0;
        for(int i = 0; i < count; i++) {
            if(msg[i]->m_rptSec != 0)
                lastRptSeq = msg[i]->m_rptSec;
            else
                msg[i]->m_rptSec = lastRptSeq;
        }
    }

public:

    TestMessagesHelper() {
        this->m_feedInfoCount = 0;
        this->m_symbolsCount = 0;
        this->m_mode = TestMessagesHelperMode::tmhmFond;
        this->m_fixManager = new FixProtocolManager(new SocketBufferProvider(DefaultSocketBufferManager::Default, 16000, 100, 16000, 100), FastProtocolVersion);
        this->m_fastManager = new FastProtocolManager(new AstsObjectsAllocationInfo(128), new FortsObjectsAllocationInfo(128));
        if(TestMessagesHelper::m_sockMessages->PoolStart()->Data() == 0)
            TestMessagesHelper::m_sockMessages->AllocData();
        this->m_buffer = DefaultSocketBufferManager::Default->GetFreeBuffer(10000, 100);
    }
    ~TestMessagesHelper() {
        delete this->m_fixManager;
        delete this->m_fastManager;
    }

    void ClearFeedInfo() {
        this->m_feedInfoCount = 0;
    }

    AstsLogonInfo* CreateLogonMessage(TestTemplateInfo *tmp) {
        AstsLogonInfo *info = new AstsLogonInfo();

        int sidLen = strlen(tmp->m_senderId);
        char *sid = new char[sidLen + 1];

        strcpy(sid, tmp->m_senderId);

        int pLen = strlen(tmp->m_pass);
        char *p = new char[pLen + 1];
        strcpy(p, tmp->m_pass);

        StringIdComparer::CopyString(info->SenderCompID, sid, sidLen);
        info->SenderCompIDLength = sidLen;

        StringIdComparer::CopyString(info->Password, p,  pLen);
        info->PasswordLength = pLen;

        info->MsgSeqNum = tmp->m_msgSeqNo;

        return info;
    }

    AstsOLSFONDInfo* CreateOLSFondInfo(const char *symbol, const char *trading) {
        AstsOLSFONDInfo *info = new AstsOLSFONDInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsOLSFONDItemInfo* CreateOLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsOLSFONDItemInfo> *list = new AutoAllocatePointerList<AstsOLSFONDItemInfo>(2, 1);
        AstsOLSFONDItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsIncrementalOLRFONDInfo* CreateAstsIncrementalOLRFONDInfo() {
        AutoAllocatePointerList<AstsIncrementalOLRFONDInfo> *list = new AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>(2, 1);
        return list->NewItem();
    }

    AstsIncrementalOLRCURRInfo* CreateAstsIncrementalOLRCURRInfo() {
        AutoAllocatePointerList<AstsIncrementalOLRCURRInfo> *list = new AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>(2, 1);
        return list->NewItem();
    }

    AstsIncrementalTLRFONDInfo* CreateAstsIncrementalTLRFONDInfo() {
        AutoAllocatePointerList<AstsIncrementalTLRFONDInfo> *list = new AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>(2, 1);
        return list->NewItem();
    }

    AstsIncrementalTLRCURRInfo* CreateAstsIncrementalTLRCURRInfo() {
        AutoAllocatePointerList<AstsIncrementalTLRCURRInfo> *list = new AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>(2, 1);
        return list->NewItem();
    }

    FortsDefaultIncrementalRefreshMessageInfo* CreateFortsDefaultIncrementalRefreshMessageInfo() {
        AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo> *list = new AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>(2, 1);
        return list->NewItem();
    }

    FortsDefaultIncrementalRefreshMessageInfo* CreateFortsDefaultIncrementalRefreshMessageInfo(TestTemplateInfo *tmp) {
        FortsDefaultIncrementalRefreshMessageInfo *info = new FortsDefaultIncrementalRefreshMessageInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->NullMap |= FortsDefaultIncrementalRefreshMessageInfoNullIndices::LastFragmentNullIndex;
        info->MDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->MDEntries[i] = CreateFortsOBRItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void SendFortsOBRMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FortsDefaultIncrementalRefreshMessageInfo* info = CreateFortsDefaultIncrementalRefreshMessageInfo(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeFortsDefaultIncrementalRefreshMessageInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FortsDefaultSnapshotMessageInfo* CreateFortsDefaultSnapshotMessageInfo(TestTemplateInfo *tmp) {
        FortsDefaultSnapshotMessageInfo *info = new FortsDefaultSnapshotMessageInfo();
        strcpy(info->Symbol, tmp->m_symbol);
        info->SymbolLength = strlen(tmp->m_symbol);

        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->SecurityID = tmp->m_securityId;
        info->MDEntriesCount = tmp->m_itemsCount;
        info->RptSeq = tmp->m_rptSec;
        info->LastFragment = tmp->m_lastFragment;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->MDEntries[i] = CreateFortsOBSItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void SendFortsOBSMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FortsDefaultSnapshotMessageInfo *info = CreateFortsDefaultSnapshotMessageInfo(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeFortsDefaultSnapshotMessageInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsOLSFONDItemInfo* CreateOLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        AstsOLSFONDItemInfo *info = CreateOLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsOLSFONDItemInfo* CreateOLRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }
    
    AstsOLSCURRInfo* CreateOLSCurrInfo(const char *symbol, const char *trading) {
        AstsOLSCURRInfo *info = new AstsOLSCURRInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsOLSCURRItemInfo* CreateOLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsOLSCURRItemInfo> *list = new AutoAllocatePointerList<AstsOLSCURRItemInfo>(2, 1);
        AstsOLSCURRItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsOLSCURRItemInfo* CreateOLRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        AstsOLSCURRItemInfo *info = CreateOLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsOLSCURRItemInfo* CreateOLRCurrItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOLRCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }
    
    AstsGenericInfo* CreateOBSFondInfo(const char *symbol, const char *trading) {
        AstsGenericInfo *info = new AstsGenericInfo();


        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsGenericItemInfo* CreateOBSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsGenericItemInfo> *list = new AutoAllocatePointerList<AstsGenericItemInfo>(2, 1);
        AstsGenericItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsGenericItemInfo* CreateOBRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        AstsGenericItemInfo *info = CreateOBSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsGenericItemInfo* CreateOBRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOBRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    AstsGenericInfo* CreateOBSCurrInfo(const char *symbol, const char *trading) {
        AstsGenericInfo *info = new AstsGenericInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsGenericItemInfo* CreateOBSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsGenericItemInfo> *list = new AutoAllocatePointerList<AstsGenericItemInfo>(2, 1);
        AstsGenericItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsGenericItemInfo* CreateOBRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        AstsGenericItemInfo *info = CreateOBSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsGenericItemInfo* CreateOBRCurrItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOBRCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    AstsTLSFONDInfo* CreateTLSFondInfo(const char *symbol, const char *trading) {
        AstsTLSFONDInfo *info = new AstsTLSFONDInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsTLSFONDItemInfo* CreateTLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsTLSFONDItemInfo> *list = new AutoAllocatePointerList<AstsTLSFONDItemInfo>(2, 1);
        AstsTLSFONDItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        AstsTLSFONDItemInfo *info = CreateTLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateTLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    AstsTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateTLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    AstsTLSCURRInfo* CreateTLSCurrInfo(const char *symbol, const char *trading) {
        AstsTLSCURRInfo *info = new AstsTLSCURRInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsTLSCURRItemInfo* CreateTLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsTLSCURRItemInfo> *list = new AutoAllocatePointerList<AstsTLSCURRItemInfo>(2, 1);
        AstsTLSCURRItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsTLSCURRItemInfo* CreateTLSCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        AstsTLSCURRItemInfo *info = CreateTLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsTLSCURRItemInfo* CreateTLSCurrItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateTLSCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    AstsTLSCURRItemInfo* CreateTLSCurrItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateTLSCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    AstsGenericInfo* CreateMSSFondInfo(const char *symbol, const char *trading) {
        AstsGenericInfo *info = new AstsGenericInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsGenericItemInfo* CreateGenericItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<AstsGenericItemInfo> *list = new AutoAllocatePointerList<AstsGenericItemInfo>(2, 1);
        AstsGenericItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    AstsGenericItemInfo* CreateGenericItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        AstsGenericItemInfo *info = CreateGenericItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    AstsGenericItemInfo* CreateGenericItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateGenericItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    AstsGenericItemInfo* CreateGenericItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateGenericItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    AstsGenericInfo* CreateMSSCurrInfo(const char *symbol, const char *trading) {
        AstsGenericInfo *info = new AstsGenericInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, trading, strlen(trading));
        info->TradingSessionIDLength = strlen(trading);

        return info;
    }

    AstsGenericItemInfo* CreateGenericItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId, int rptSeq) {

        AutoAllocatePointerList<AstsGenericItemInfo> *list = new AutoAllocatePointerList<AstsGenericItemInfo>(2, 1);
        AstsGenericItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        StringIdComparer::CopyString(info->MDEntryID, entryId, strlen(entryId));
        info->MDEntryIDLength = strlen(entryId);
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);
        info->RptSeq = rptSeq;

        return info;
    }

    UINT64 ConstCharToUINT64(const char *id) {
        int len = strlen(id);
        if(len > 8)
            return *(UINT64*)(id + len - 8);
        char buf[16];
        bzero(buf, 16);
        memcpy(buf + 8 - len, id, len);
        return *(UINT64*)buf;
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateFortsOBRItemInfo(INT64 priceMantissa, INT32 priceExponenta, UINT64 size, MDEntryType entryType, UINT64 entryId) {

        AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo> *list = new AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>(2, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        info->MDEntryID = entryId;

        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize = size;

        return info;
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateFortsOBRItemInfo(const char *symbol, UINT64 securityId, INT64 priceMantissa,
                                               INT32 priceExponenta, UINT64 size,
                                               MDUpdateAction updateAction, MDEntryType entryType, UINT64 entryId,
                                               int rptSeq) {
        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = CreateFortsOBRItemInfo(priceMantissa, priceExponenta, size, entryType, entryId);

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);
        info->SecurityID = securityId;

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateFortsOBRItemInfo(TestTemplateItemInfo *item) {
        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = new FortsDefaultSnapshotMessageMDEntriesItemInfo();
        strcpy(info->Symbol, item->m_symbol);
        info->RptSeq = item->m_rptSeq;
        info->SymbolLength = strlen(item->m_symbol);
        info->MDUpdateAction = item->m_action;
        info->SecurityID = item->m_securityId;
        info->MDEntryID = item->m_entryIdInt;
        info->MDEntryType[0] = item->m_entryType;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(&(item->m_entryPx));
        info->MDEntrySize = item->m_entrySizeInt;

        return info;
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateFortsOBSItemInfo(TestTemplateItemInfo *item) {
        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = new FortsDefaultSnapshotMessageMDEntriesItemInfo();

        info->MDEntryID = item->m_entryIdInt;
        info->MDEntryType[0] = item->m_entryType;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(&(item->m_entryPx));
        info->MDEntrySize = item->m_entrySizeInt;
        info->MDUpdateAction = item->m_action;

        return info;
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateFortsOBRItemInfo(const char *symbol, UINT64 securityId, UINT64 entryId) {
        return CreateFortsOBRItemInfo(symbol, securityId, 1, 1, 10, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FortsDefaultSnapshotMessageMDEntriesItemInfo* CreateFortsOBSItemInfo(INT64 priceMantissa, INT32 priceExponenta, UINT64 size, MDEntryType entryType, UINT64 entryId) {

        AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo> *list = new AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>(2, 1);
        FortsDefaultSnapshotMessageMDEntriesItemInfo *info = list->NewItem();

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDUpdateAction = MDUpdateAction::mduaAdd;
        info->MDEntryID = entryId;
        StringIdComparer::CopyString(info->MDEntryType, type, 1);
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize = size;

        return info;
    }

    FortsDefaultSnapshotMessageInfo* CreateFortsSnapshotInfo(const char *symbol, UINT64 securityId) {
        FortsDefaultSnapshotMessageInfo *info = new FortsDefaultSnapshotMessageInfo();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        info->SecurityID = securityId;

        return info;
    }

    AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* AddTradingSession(AstsSecurityDefinitionInfo *info, int marketIndex, const char *tradingSession) {
        int newIndex = info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrpCount;
        info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrpCount++;
        AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo> *list = new AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(2, 1);
        AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *item = list->NewItem();
        info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrp[newIndex] = item;

        StringIdComparer::CopyString(item->TradingSessionID, tradingSession, strlen(tradingSession));
        item->TradingSessionIDLength = strlen(tradingSession);
        return item;
    }

    void AddTradingSession(AstsSecurityDefinitionInfo *info, int marketIndex, TestTemplateItemInfo *ti) {
        AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *item = AddTradingSession(info, marketIndex, ti->m_tradingSession);
        item->SecurityTradingStatus = ti->m_sessionStatus;
    }

    void AddMarketSegemntGroup(AstsSecurityDefinitionInfo *info) {
        AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo> *list = new AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>(2, 1);
        info->MarketSegmentGrp[info->MarketSegmentGrpCount] = list->NewItem();
        info->MarketSegmentGrpCount++;
    }

    AstsSecurityDefinitionInfo* CreateSecurityDefinitionInfo(const char *symbol) {
        AutoAllocatePointerList<AstsSecurityDefinitionInfo> *list = new AutoAllocatePointerList<AstsSecurityDefinitionInfo>(2, 1);
        AstsSecurityDefinitionInfo *info = list->NewItem();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        return info;
    }

    AstsSecurityStatusInfo* CreateSecurityStatusInfo(const char *symbol, const char *session, const char *sessionSubId) {
        AutoAllocatePointerList<AstsSecurityStatusInfo> *list = new AutoAllocatePointerList<AstsSecurityStatusInfo>(2, 1);
        AstsSecurityStatusInfo *info = list->NewItem();

        StringIdComparer::CopyString(info->Symbol, symbol, strlen(symbol));
        info->SymbolLength = strlen(symbol);

        StringIdComparer::CopyString(info->TradingSessionID, session, strlen(session));
        info->TradingSessionIDLength = strlen(session);

        StringIdComparer::CopyString(info->TradingSessionSubID, sessionSubId, strlen(sessionSubId));
        info->TradingSessionSubIDLength = strlen(sessionSubId);

        return info;
    }

    AstsSecurityDefinitionInfo* CreateSecurityDefinitionInfo(TestTemplateInfo *tmp) {
        AstsSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp->m_symbol);

        info->MsgSeqNum = tmp->m_msgSeqNo;
        this->AddMarketSegemntGroup(info);
        if(tmp->m_totNumReports != 0) {
            info->TotNumReports = tmp->m_totNumReports;
        }
        else {
            info->NullMap |= AstsSecurityDefinitionInfoNullIndices::TotNumReportsNullIndex;
        }

        for(int i = 0; i < tmp->m_itemsCount; i++) {
            this->AddTradingSession(info, 0, tmp->m_items[i]);
        }
        return info;
    }

    AstsSecurityStatusInfo* CreateSecurityStatusInfo(TestTemplateInfo *tmp) {
        AstsSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp->m_symbol, tmp->m_session, tmp->m_sessionSubId);

        info->SecurityTradingStatus = tmp->m_sessionStatus;

        info->AuctionIndicator = tmp->m_auctionIndicator;

        info->MsgSeqNum = tmp->m_msgSeqNo;

        return info;
    }

    AstsOLSFONDItemInfo* CreateOLRFondItemInfo(TestTemplateItemInfo *tmp) {
        AstsOLSFONDItemInfo *info = new AstsOLSFONDItemInfo();

        info->MDUpdateAction = tmp->m_action;

        info->PresenceMap |= AstsIncrementalOLRFONDItemInfoPresenceIndices::MDEntryTypePresenceIndex;
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->PresenceMap |= AstsIncrementalOLRFONDItemInfoPresenceIndices::MDEntryPxPresenceIndex;
        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->PresenceMap |= AstsIncrementalOLRFONDItemInfoPresenceIndices::MDEntrySizePresenceIndex;
        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->PresenceMap |= AstsIncrementalOLRFONDItemInfoPresenceIndices::SymbolPresenceIndex;
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->PresenceMap |= AstsIncrementalOLRFONDItemInfoPresenceIndices::TradingSessionIDPresenceIndex;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    AstsGenericItemInfo* CreateObrFondItemInfo(TestTemplateItemInfo *tmp) {
        AstsGenericItemInfo *info = new AstsGenericItemInfo();
        info->MDUpdateAction = tmp->m_action;
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Assign(&tmp->m_entryPx);
        info->MDEntrySize.Assign(&tmp->m_entrySize);
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    AstsTLSFONDItemInfo* CreateTLRFondItemInfo(TestTemplateItemInfo *tmp) {
        AstsTLSFONDItemInfo *info = new AstsTLSFONDItemInfo();
        info->MDUpdateAction = tmp->m_action;

        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    AstsOLSCURRItemInfo* CreateOLRCurrItemInfo(TestTemplateItemInfo *tmp) {
        AstsOLSCURRItemInfo *info = new AstsOLSCURRItemInfo();
        info->PresenceMap |= AstsIncrementalOLRCURRItemInfoPresenceIndices::MDUpdateActionPresenceIndex;
        info->MDUpdateAction = tmp->m_action;

        info->PresenceMap |= AstsIncrementalOLRCURRItemInfoPresenceIndices::MDEntryTypePresenceIndex;
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->PresenceMap |= AstsIncrementalOLRCURRItemInfoPresenceIndices::MDEntryPxPresenceIndex;
        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->PresenceMap |= AstsIncrementalOLRCURRItemInfoPresenceIndices::MDEntrySizePresenceIndex;
        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->PresenceMap |= AstsIncrementalOLRCURRItemInfoPresenceIndices::SymbolPresenceIndex;
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->PresenceMap |= AstsIncrementalOLRCURRItemInfoPresenceIndices::TradingSessionIDPresenceIndex;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    AstsGenericItemInfo* CreateObrCurrItemInfo(TestTemplateItemInfo *tmp) {
        AstsGenericItemInfo *info = new AstsGenericItemInfo();
        info->MDUpdateAction = tmp->m_action;
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Assign(&tmp->m_entryPx);
        info->MDEntrySize.Assign(&tmp->m_entrySize);
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    AstsTLSCURRItemInfo* CreateTLRCurrItemInfo(TestTemplateItemInfo *tmp) {
        AstsTLSCURRItemInfo *info = new AstsTLSCURRItemInfo();
        info->MDUpdateAction = tmp->m_action;

        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    void EncodeHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsHeartbeatInfo *info = new AstsHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsHeartbeatInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeHearthBeatMessage(TestTemplateInfo *tmp) {
        AstsHeartbeatInfo *info = new AstsHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        this->m_fastManager->WriteMsgSeqNumber(info->MsgSeqNum);
        this->m_fastManager->EncodeAstsHeartbeatInfo(info);
    }

    void SendHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsHeartbeatInfo *info = new AstsHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsHeartbeatInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendHearthBeatMessageForts(FeedConnection *conn, TestTemplateInfo *tmp) {
        FortsHeartbeatInfo *info = new FortsHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeFortsHeartbeatInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeLogoutMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsLogoutInfo *info = new AstsLogoutInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsLogoutInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeLogoutMessage(TestTemplateInfo *tmp) {
        AstsLogoutInfo *info = new AstsLogoutInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        this->m_fastManager->EncodeAstsLogoutInfo(info);
    }

    void SendLogoutMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsLogoutInfo *info = new AstsLogoutInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsLogoutInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeLogonMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsLogonInfo *info = CreateLogonMessage(tmp);
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsLogonInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeLogonMessage(TestTemplateInfo *tmp) {
        AstsLogonInfo *info = CreateLogonMessage(tmp);
        info->MsgSeqNum = tmp->m_msgSeqNo;
        this->m_fastManager->EncodeAstsLogonInfo(info);
    }

    void SendLogonMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsLogonInfo *info = CreateLogonMessage(tmp);
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsLogonInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsIncrementalGenericInfo* CreateIncrementalGenericMessageCore(TestTemplateInfo *tmp) {
        AstsIncrementalGenericInfo *info = new AstsIncrementalGenericInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeAstsIncrementalGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalGenericInfo *info = CreateIncrementalGenericMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalGenericInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsIncrementalGenericMessage(TestTemplateInfo *tmp) {
        AstsIncrementalGenericInfo *info = CreateIncrementalGenericMessageCore(tmp);

        this->m_fastManager->EncodeAstsIncrementalGenericInfo(info);
    }

    void SendIncrementalGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalGenericInfo *info = CreateIncrementalGenericMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalGenericInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsGenericInfo* CreateSnapshotGenericMessageCore(TestTemplateInfo *tmp) {
        AstsGenericInfo *info = new AstsGenericInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_session);
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeSnapshotGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsGenericInfo *info = CreateSnapshotGenericMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsGenericInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeSnapshotGenericMessage(TestTemplateInfo *tmp) {
        AstsGenericInfo *info = CreateSnapshotGenericMessageCore(tmp);

        this->m_fastManager->EncodeAstsGenericInfo(info);
    }

    void SendSnapshotGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsGenericInfo *info = CreateSnapshotGenericMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsGenericInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsIncrementalOLRFONDInfo* CreateOLRFondMessageCore(TestTemplateInfo *tmp) {
        AstsIncrementalOLRFONDInfo *info = new AstsIncrementalOLRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeOLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalOLRFONDInfo *info = CreateOLRFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalOLRFONDInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeOLRFondMessage(TestTemplateInfo *tmp) {
        AstsIncrementalOLRFONDInfo *info = CreateOLRFondMessageCore(tmp);
        this->m_fastManager->EncodeAstsIncrementalOLRFONDInfo(info);
    }

    void SendOLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalOLRFONDInfo *info = CreateOLRFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalOLRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsSecurityDefinitionMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsSecurityDefinitionInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsSecurityDefinitionMessage(TestTemplateInfo *tmp) {
        AstsSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp);
        this->m_fastManager->EncodeAstsSecurityDefinitionInfo(info);
    }

    void SendSecurityDefinitionMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsSecurityDefinitionInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsSecurityStatusMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsSecurityStatusInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsSecurityStatusMessage(TestTemplateInfo *tmp) {
        AstsSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp);
        this->m_fastManager->EncodeAstsSecurityStatusInfo(info);
    }

    void SendSecurityStatusMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsSecurityStatusInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsOLSFONDInfo* CreateOLSFondMessage(TestTemplateInfo *tmp) {
        AstsOLSFONDInfo *info = new AstsOLSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_session);
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeAstsOLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsOLSFONDInfo *info = CreateOLSFondMessage(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsOLSFONDInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsOLSFondMessage(TestTemplateInfo *tmp) {
        AstsOLSFONDInfo *info = CreateOLSFondMessage(tmp);
        this->m_fastManager->EncodeAstsOLSFONDInfo(info);
    }

    void SendOLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsOLSFONDInfo *info = CreateOLSFondMessage(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsOLSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsIncrementalTLRFONDInfo* CreateTLRFondMessageCore(TestTemplateInfo *tmp) {
        AstsIncrementalTLRFONDInfo *info = new AstsIncrementalTLRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeTLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalTLRFONDInfo *info = CreateTLRFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalTLRFONDInfo(info);
        conn->m_sendABuffer->Next (conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeTLRFondMessage(TestTemplateInfo *tmp) {
        AstsIncrementalTLRFONDInfo *info = CreateTLRFondMessageCore(tmp);
        this->m_fastManager->EncodeAstsIncrementalTLRFONDInfo(info);
    }

    void SendTLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalTLRFONDInfo *info = CreateTLRFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalTLRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsTLSFONDInfo* CreateTLSFondMessageCore(TestTemplateInfo *tmp) {
        AstsTLSFONDInfo *info = new AstsTLSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_session);
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeAstsTLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsTLSFONDInfo *info = CreateTLSFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsTLSFONDInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsTLSFondMessage(TestTemplateInfo *tmp) {
        AstsTLSFONDInfo *info = CreateTLSFondMessageCore(tmp);
        this->m_fastManager->EncodeAstsTLSFONDInfo(info);
    }

    void SendTLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsTLSFONDInfo *info = CreateTLSFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsTLSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsIncrementalOLRCURRInfo* CreateOLRCurrMessageCore(TestTemplateInfo *tmp) {
        AstsIncrementalOLRCURRInfo *info = new AstsIncrementalOLRCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeOLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalOLRCURRInfo* info = CreateOLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalOLRCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeOLRCurrMessage(TestTemplateInfo *tmp) {
        AstsIncrementalOLRCURRInfo* info = CreateOLRCurrMessageCore(tmp);
        this->m_fastManager->EncodeAstsIncrementalOLRCURRInfo(info);
    }

    void SendOLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalOLRCURRInfo* info = CreateOLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalOLRCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsOLSCURRInfo* CreateOLSCurrMessageCore(TestTemplateInfo *tmp) {
        AstsOLSCURRInfo *info = new AstsOLSCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_session);
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeAstsOLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsOLSCURRInfo *info = CreateOLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsOLSCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsOLSCurrMessage(TestTemplateInfo *tmp) {
        AstsOLSCURRInfo *info = CreateOLSCurrMessageCore(tmp);
        this->m_fastManager->EncodeAstsOLSCURRInfo(info);
    }

    void SendOLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsOLSCURRInfo *info = CreateOLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsOLSCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsIncrementalTLRCURRInfo* CreateTLRCurrMessageCore(TestTemplateInfo *tmp) {
        AstsIncrementalTLRCURRInfo *info = new AstsIncrementalTLRCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeTLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalTLRCURRInfo *info = CreateTLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalTLRCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeTLRCurrMessage(TestTemplateInfo *tmp) {
        AstsIncrementalTLRCURRInfo *info = CreateTLRCurrMessageCore(tmp);
        this->m_fastManager->EncodeAstsIncrementalTLRCURRInfo(info);
    }

    void SendTLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsIncrementalTLRCURRInfo *info = CreateTLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsIncrementalTLRCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    AstsTLSCURRInfo* CreateTLSCurrMessageCore(TestTemplateInfo *tmp) {
        AstsTLSCURRInfo *info = new AstsTLSCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->TradingSessionIDLength = strlen(tmp->m_session);
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeAstsTLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsTLSCURRInfo *info = CreateTLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsTLSCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeAstsTLSCurrMessage(TestTemplateInfo *tmp) {
        AstsTLSCURRInfo *info = CreateTLSCurrMessageCore(tmp);
        this->m_fastManager->EncodeAstsTLSCURRInfo(info);
    }

    void SendTLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        AstsTLSCURRInfo *info = CreateTLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->WriteMsgSeqNumber(info->MsgSeqNum);
        conn->m_fastProtocolManager->EncodeAstsTLSCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedTemplateId::fcmHeartBeat:
                SendHearthBeatMessage(conn, tmp);
                break;
            case FeedTemplateId::fortsHearthBeat:
                SendHearthBeatMessageForts(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_Generic:
                SendIncrementalGenericMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_Generic:
                SendSnapshotGenericMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_OLR_FOND:
                SendOLRFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                SendOLSFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_TLR_FOND:
                SendTLRFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                SendTLSFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_OLR_CURR:
                SendOLRCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fortsIncremental:
                SendFortsOBRMessage(conn, tmp);
                break;
            case FeedTemplateId::fortsSnapshot:
                SendFortsOBSMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                SendOLSCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_TLR_CURR:
                SendTLRCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                SendTLSCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcSecurityDefinition:
                SendSecurityDefinitionMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcSecurityStatus:
                SendSecurityStatusMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcLogon:
                SendLogonMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcLogout:
                SendLogoutMessage(conn, tmp);
                break;
            default:
                break;
        }
    }

    void SendMessages(FeedConnection *conn, TestTemplateInfo **templates, int templatesCount) {
        for(int i = 0; i < templatesCount; i++)
            SendMessage(conn, templates[i]);
    }

    void SendMessagesIdf(FeedConnection *fif, const char *idf, int delay) {

        TestTemplateInfo **idf_msg = 0;
        int idfMsgCount = CreateTemplates(idf, &idf_msg);

        int idf_index = 0;
        Stopwatch w;
        w.Start(1);
        while(idf_index < idfMsgCount) {
            if(idf_msg[idf_index]->m_msgSeqNo == 0)
                idf_msg[idf_index]->m_msgSeqNo = idf_index + 1;
            if(!idf_msg[idf_index]->m_lost) {
                SendMessage(fif, idf_msg[idf_index]);
                if (!fif->ListenSecurityDefinition_Core())
                    throw;
            }
            idf_index++;

            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
    }

    void SendMessagesIsf(FeedConnection *fif, const char *idf, int delay) {
        int idfMsgCount = CalcMsgCount(idf);
        TestTemplateInfo **idf_msg = new TestTemplateInfo*[idfMsgCount];
        FillMsg(idf_msg, idfMsgCount, idf);

        int idf_index = 0;
        Stopwatch w;
        w.Start(1);
        while(idf_index < idfMsgCount) {
            if(idf_msg[idf_index]->m_msgSeqNo == 0)
                idf_msg[idf_index]->m_msgSeqNo = idf_index + 1;
            if(!idf_msg[idf_index]->m_lost) {
                SendMessage(fif, idf_msg[idf_index]);
                if (!fif->ListenSecurityStatus_Core())
                    throw;
            }
            idf_index++;

            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
    }

    void SetMsgSeqNumbers(TestTemplateInfo **tmp, int count) {
        for(int i = 0; i < count; i++) {
            if(tmp[i]->m_msgSeqNo == 0)
                tmp[i]->m_msgSeqNo = i + 1;
        }
    }

    void OnRecvLogon(FixProtocolMessage *msg, WinSockManager *wsManager) {

        this->m_fastManager->SetNewBuffer(this->m_buffer->CurrentPos() + 4, 1000); // overwrite msgseqno

        AstsLogonInfo info;

        strcpy(this->m_protocolVersion, FastProtocolVersion);
        strcpy(info.BeginString, this->m_protocolVersion);
        info.BeginStringLength = FastProtocolVersionLength;
        strcpy(this->m_applVerId, "9");
        strcpy(info.DefaultApplVerID, this->m_applVerId);
        info.DefaultApplVerIDLength = 1;
        strcpy(this->m_msgType, "A");
        strcpy(info.MessageType, this->m_msgType);
        info.MessageTypeLength = 1;
        info.MsgSeqNum = 1;
        info.PasswordLength = 0;
        info.UsernameLength = 0;
        sprintf(this->m_senderCompId, "MOEX");
        sprintf(this->m_targetCompId, "You!");
        strcpy(info.SenderCompID, this->m_senderCompId);
        info.SenderCompIDLength = 4;
        strcpy(info.TargetCompID, this->m_targetCompId);
        info.TargetCompIDLength = 4;

        this->m_fastManager->EncodeAstsLogonInfo(&info);
        *((int*)this->m_buffer->CurrentPos()) = this->m_fastManager->MessageLength();

        this->SetRecvFor(wsManager, (unsigned char*)this->m_buffer->CurrentPos(), this->m_fastManager->MessageLength() + 4);
        this->m_buffer->Next(this->m_fixManager->MessageLength() + 4);
    }

    void OnRecvLogout(FixProtocolMessage *msg, WinSockManager *wsManager) {
        // nothing to do
    }

    TestFeedMessageInfo *GetFeedInfo(const char *feedId, int feedIdLength) {
        for(int i = 0; i < this->m_feedInfoCount; i++) {
            if(StringIdComparer::Equal(this->m_feedInfo[i].m_feed->IdName(), strlen(this->m_feedInfo[i].m_feed->IdName()), feedId, feedIdLength))
                return &(this->m_feedInfo[i]);
        }
        return 0;
    }

    char *GetText(const char *text) {
        char *buf = new char[strlen(text) + 1];
        strcpy(buf, text);
        return buf;
    }

    void SendLogout(WinSockManager *wsManager, const char *text) {
        AstsLogoutInfo *info = new AstsLogoutInfo();
        strcpy(info->Text, text);
        info->TextLength = strlen(info->Text);

        this->m_fastManager->SetNewBuffer(this->m_buffer->CurrentPos() + 4, 10000);
        this->m_fastManager->EncodeAstsLogoutInfo(info);
        *((int*)this->m_buffer->CurrentPos()) = this->m_fastManager->MessageLength();
        SetRecvFor(wsManager, this->m_buffer->CurrentPos(), this->m_fastManager->MessageLength() + 4);
        this->m_buffer->Next(this->m_fastManager->MessageLength() + 4);
    }

    void OnRecvMarketDataRequest(FixProtocolMessage *msg, WinSockManager *wsManager) {
        if(!msg->CheckProcessMarketDataRequest())
            throw;
        TestFeedMessageInfo *feed = GetFeedInfo(msg->MarketDataRequestInfo()->FeedId, msg->MarketDataRequestInfo()->FeedIdLength);
        if(feed == 0) {
            SendLogout(wsManager, "unknown feed id.");
            return;
        }
        unsigned char *start = this->m_buffer->CurrentPos();
        for(int i = msg->MarketDataRequestInfo()->BeginSeqNo; i <= msg->MarketDataRequestInfo()->EndSeqNo; i++) {
            this->m_fastManager->SetNewBuffer(this->m_buffer->CurrentPos() + 4, 1000);
            this->EncodeMessage(feed->m_templates[i - 1]);
            *((int*)this->m_buffer->CurrentPos()) = this->m_fastManager->MessageLength();
            this->m_buffer->NextExact(this->m_fastManager->MessageLength() + 4);
        }
        int length = (int)(this->m_buffer->CurrentPos() - start);
        unsigned char *data;
        for(data = start; data <= this->m_buffer->CurrentPos();) {
            if(data + 100 <= this->m_buffer->CurrentPos()) {
                SetRecvFor(wsManager, data, 100);
                data += 100;
                continue;
            }
            else {
                SetRecvFor(wsManager, data, (int)(this->m_buffer->CurrentPos() - data));
                break;
            }
        }
        SendLogout(wsManager, "Bye!");
    }

    void OnRecvFixMessage(char msgType, FixProtocolMessage *msg, WinSockManager *wsManager) {
        switch(msgType) {
            case MsgTypeLogon:
                OnRecvLogon(msg, wsManager);
                break;
            case MsgTypeLogout:
                OnRecvLogout(msg, wsManager);
                break;
            case MsgTypeMarketDataRequest:
                OnRecvMarketDataRequest(msg, wsManager);
                break;
        }
    }

    void OnRecvData(WinSockManager *wsManager, unsigned char *data, int size) {
        this->m_fixManager->SetMessageBuffer((char*)data);
        this->m_fixManager->SetRecvBufferSize(size);
        this->m_fixManager->ProcessSplitRecvMessages();
        for(int i = 0; i < this->m_fixManager->RecvMessageCount(); i++) {
            FixProtocolMessage *msg = this->m_fixManager->Message(i);
            if(!msg->ProcessCheckHeaderFast())
                throw;
            OnRecvFixMessage(msg->Header()->msgType, msg, wsManager);
        }
    }

    int CreateTemplates(const char *msg, TestTemplateInfo ***ptr) {
        int count = CalcMsgCount(msg);
        TestTemplateInfo **tmp = new TestTemplateInfo*[count];
        FillMsg(tmp, count, msg);
        *ptr = tmp;
        return count;
    }

    void SendMessagesIsf_Idf_Hr(FeedConnection *isf, FeedConnection *idf, FeedConnection *hr, const char *stridf, const char *strisf, int delay, bool startIsfAfterIdfComplete) {
        TestTemplateInfo **tisf, **tidf;

        int idfCount = CreateTemplates(stridf, &tidf);
        int isfCount = CreateTemplates(strisf, &tisf);

        ClearFeedInfo();
        SetMsgSeqNumbers(tidf, idfCount);
        SetMsgSeqNumbers(tisf, isfCount);
        AddFeedInfo(isf, tisf, isfCount);

        hr->SetTestMessagesHelper(this);

        int idfIndex = 0, isfIndex = 0;

        Stopwatch w;
        w.Start(1);

        while(idfIndex < idfCount || isfIndex < isfCount) {
            if (isf->State() != FeedConnectionState::fcsSuspend) {
                if (isfIndex < isfCount) {
                    if (!tisf[isfIndex]->m_lost) {
                        SendMessage(isf, tisf[isfIndex]);
                        if (!isf->ListenSecurityStatus_Core())
                            throw;
                    }
                    isfIndex++;
                }
            }
            if (idf->State() != FeedConnectionState::fcsSuspend) {
                if (idfIndex < idfCount) {
                    if (!tidf[idfIndex]->m_lost) {
                        SendMessage(idf, tidf[idfIndex]);
                        if (!idf->ListenSecurityDefinition_Core())
                            throw;
                        if (idf->IsIdfDataCollected()) {
                            if (startIsfAfterIdfComplete && isf->State() == FeedConnectionState::fcsSuspend) {
                                isf->ThreatFirstMessageIndexAsStart();
                                isf->Start();
                            }
                        }
                        idfIndex++;
                    }
                }
            }
            else {
                if(isfIndex >= isfCount)
                    idfIndex = idfCount;
            }
            w.Start();
            while (!w.IsElapsedMilliseconds(delay)) {
                hr->DoWorkAtom();
            }
            w.Stop();
            hr->DoWorkAtom();

            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
    }

    void SendMessagesIsf_Hr(FeedConnection *fif, FeedConnection *hr, const char *idf, int delay) {
        int idfMsgCount = CalcMsgCount(idf);

        TestTemplateInfo **idf_msg = new TestTemplateInfo*[idfMsgCount];
        FillMsg(idf_msg, idfMsgCount, idf);

        ClearFeedInfo();
        SetMsgSeqNumbers(idf_msg, idfMsgCount);
        AddFeedInfo(fif, idf_msg, idfMsgCount);
        hr->SetTestMessagesHelper(this);

        int idf_index = 0;
        Stopwatch w;
        w.Start(1);
        while(idf_index < idfMsgCount || hr->m_hsRequestList->Count() > 0) {
            if(idf_index < idfMsgCount) {
                if (!idf_msg[idf_index]->m_lost) {
                    SendMessage(fif, idf_msg[idf_index]);
                    if (!fif->ListenSecurityStatus_Core())
                        throw;
                }
                idf_index++;
            }
            else {
                if (!fif->ListenSecurityStatus_Core())
                    throw;
            }
            w.Start();
            while (!w.IsElapsedMilliseconds(delay)) {
                hr->DoWorkAtom();
            }
            w.Stop();
            hr->DoWorkAtom();

            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
        if(!fif->ListenSecurityStatus_Core())
            throw;
    }

    void EncodeMessage(TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedTemplateId::fcmHeartBeat:
                EncodeHearthBeatMessage(tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_Generic:
                EncodeAstsIncrementalGenericMessage(tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_Generic:
                EncodeSnapshotGenericMessage(tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_OLR_FOND:
                EncodeOLRFondMessage(tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                EncodeAstsOLSFondMessage(tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_TLR_FOND:
                EncodeTLRFondMessage(tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                EncodeAstsTLSFondMessage(tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_OLR_CURR:
                EncodeOLRCurrMessage(tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                EncodeAstsOLSCurrMessage(tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_TLR_CURR:
                EncodeTLRCurrMessage(tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                EncodeAstsTLSCurrMessage(tmp);
                break;
            case FeedTemplateId::fmcSecurityDefinition:
                EncodeAstsSecurityDefinitionMessage(tmp);
                break;
            case FeedTemplateId::fmcSecurityStatus:
                EncodeAstsSecurityStatusMessage(tmp);
                break;
            case FeedTemplateId::fmcLogon:
                EncodeLogonMessage(tmp);
                break;
            case FeedTemplateId::fmcLogout:
                EncodeLogoutMessage(tmp);
                break;
            default:
                break;
        }
    }

    void EncodeMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedTemplateId::fcmHeartBeat:
                EncodeHearthBeatMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_Generic:
                EncodeAstsIncrementalGenericMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_Generic:
                EncodeSnapshotGenericMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_OLR_FOND:
                EncodeOLRFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                EncodeAstsOLSFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_TLR_FOND:
                EncodeTLRFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                EncodeAstsTLSFondMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_OLR_CURR:
                EncodeOLRCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                EncodeAstsOLSCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcIncrementalRefresh_TLR_CURR:
                EncodeTLRCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                EncodeAstsTLSCurrMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcSecurityDefinition:
                EncodeAstsSecurityDefinitionMessage(conn, tmp);
            case FeedTemplateId::fmcLogon:
                EncodeLogonMessage(conn, tmp);
                break;
            case FeedTemplateId::fmcLogout:
                EncodeLogoutMessage(conn, tmp);
                break;
            default:
                break;
        }
    }

    void EncodeMessage(FeedConnection *fc, const char *msg) {
        int incMsgCount = CalcMsgCount(msg);
        TestTemplateInfo **inc_msg = new TestTemplateInfo*[incMsgCount];
        FillMsg(inc_msg, incMsgCount, msg);
        FillRptSeq(inc_msg, incMsgCount);

        this->EncodeMessage(fc, inc_msg[0]);
    }

    void ListenAtomIncremental(FeedConnection *fci) {
        if(this->IsForts())
            fci->ListenIncremental_Forts_Core();
        else
            fci->ListenIncremental_Core();
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        int incMsgCount = CalcMsgCount(inc);
        int snapMsgCount = CalcMsgCount(snap);

        TestTemplateInfo **inc_msg = new TestTemplateInfo*[incMsgCount];
        TestTemplateInfo **snap_msg = new TestTemplateInfo*[snapMsgCount];

        FillMsg(inc_msg, incMsgCount, inc);
        FillMsg(snap_msg, snapMsgCount, snap);
        FillRptSeq(inc_msg, incMsgCount);
        FillSnapRptSeq(snap_msg, snapMsgCount);

        int inc_index = 0;
        int snap_index = 0;

        Stopwatch w;
        w.Start(1);
        bool snapshotStarterd = false;
        while(inc_index < incMsgCount || snap_index < snapMsgCount) {
            if(inc_index < incMsgCount && !inc_msg[inc_index]->m_lost) {
                inc_msg[inc_index]->m_msgSeqNo = inc_index + 1;
                SendMessage(fci, inc_msg[inc_index]);
            }
            ListenAtomIncremental(fci);
            if(snapshotStarterd && fcs->State() == FeedConnectionState::fcsSuspend && snap_index < snapMsgCount && !snap_msg[snap_index]->m_skip)
                throw;
            if(inc_index < incMsgCount && inc_msg[inc_index]->m_wait) {
                if(!fci->m_waitTimer->Active())
                    throw;
                if(fcs->State() != FeedConnectionState::fcsSuspend)
                    throw;
                while(!fci->m_waitTimer->IsElapsedMilliseconds(fci->WaitLostIncrementalMessageMaxTimeMs()) && fcs->State() == FeedConnectionState::fcsSuspend) {
                    ListenAtomIncremental(fci);
                }
                if(fcs->State() == FeedConnectionState::fcsSuspend) {
                    ListenAtomIncremental(fci);
                }
                if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
                    throw;
                snapshotStarterd = true;
            }
            if(inc_index < incMsgCount)
                inc_index++;
            if(fcs->State() == FeedConnectionState::fcsListenSnapshot) {
                if (snap_index < snapMsgCount && !snap_msg[snap_index]->m_lost) {
                    snap_msg[snap_index]->m_msgSeqNo = snap_index + 1;
                    FeedTemplateId hbeatId = IsForts()? FeedTemplateId::fortsHearthBeat: FeedTemplateId::fcmHeartBeat;
                    if(snap_msg[snap_index]->m_templateId != hbeatId && (snap_msg[snap_index]->m_symbol == 0 || snap_msg[snap_index]->m_session == 0))
                        throw;
                    SendMessage(fcs, snap_msg[snap_index]);
                }
                if(snap_index < snapMsgCount)
                    snap_index++;
                fcs->ListenSnapshot_Core();
            }
            else {
                if (snap_index < snapMsgCount && snap_msg[snap_index]->m_skip) {
                    snap_index++;
                }
            }
            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
        ListenAtomIncremental(fci); // emulate endless loop
    }

    void Clear() {
        this->m_symbolsCount = 0;
        for(int i = 0; i < 100; i++) {
            this->m_symbols[i] = 0;
            this->m_rptSeq[i] = 0;
        }
    }

    void SetCurrMode() {
        this->m_mode = TestMessagesHelperMode::tmhmCurr;
    }
    void SetFondMode() {
        this->m_mode = TestMessagesHelperMode::tmhmFond;
    }
    void SetFortsMode() {
        this->m_mode = TestMessagesHelperMode::tmhmForts;
    }
    bool IsCurr() { return this->m_mode == TestMessagesHelperMode::tmhmCurr; }
    bool IsForts() { return this->m_mode == TestMessagesHelperMode::tmhmForts; }

    void CreateFixLogonMessage(FeedConnection *fc, const char *senderId, const char *pass) {
        FixLogonInfo *lg = new FixLogonInfo;

        strcpy(lg->SenderCompID, senderId);
        lg->SenderCompIDLength = strlen(senderId);

        strcpy(lg->Password, pass);
        lg->PassLength = strlen(pass);

        fc->m_fixProtocolManager->CreateLogonMessage(lg);
    }

    void ClearPoll() {
        for(int i = 0; i < WinSockManager::m_registeredCount; i++) {
            WinSockManager::m_registeredManagers[i]->m_shouldRecv = false;
        }
    }

    void SetRecvFor(WinSockManager *m, unsigned char *buffer, int bufferLen) {
        LinkedPointer<SocketMessageInfo> *ptr = TestMessagesHelper::m_sockMessages->Pop();
        SocketMessageInfo *msg = ptr->Data();

        msg->m_manager = m;
        if(buffer != 0)
            memcpy(msg->m_buffer, buffer, bufferLen);
        msg->m_canRecv = buffer != 0;
        msg->m_bufferLength = bufferLen;

        this->m_sockMessages->Add(ptr);
        for(int i = 0; i < WinSockManager::m_registeredCount; i++) {
            if(WinSockManager::m_registeredManagers[i] == msg->m_manager) {
                WinSockManager::m_registeredManagers[i]->m_shouldRecv = msg->m_canRecv? 1: 0;
            }
        }
    }
    void SetRecvFixFor(FeedConnection *fc) {
        this->SetRecvFor(fc->socketAManager, fc->m_fixProtocolManager->SendBuffer(), fc->m_fixProtocolManager->MessageLength());
    }

    void SetRecvFastFor(FeedConnection *fc) {
        this->SetRecvFor(fc->socketAManager, fc->m_fastProtocolManager->Buffer(), fc->m_fastProtocolManager->MessageLength());
    }

    template<typename T> MarketSymbolInfo<T> *CreateSymbol(const char *str) {
        MarketSymbolInfo<T> *smb = new MarketSymbolInfo<T>();
        smb->Symbol()->m_text = str;
        smb->Symbol()->m_length = strlen(str);
        return smb;
    }
};

#endif //TEST
#endif //HFT_ROBOT_TESTMESSAGESHELPER_H
