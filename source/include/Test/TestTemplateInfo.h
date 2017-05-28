//
// Created by root on 11.12.16.
//

#ifndef HFT_ROBOT_TESTTEMPLATEINFO_H
#define HFT_ROBOT_TESTTEMPLATEINFO_H
#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnection.h"

class TestTemplateItemInfo {
public:
    const char*     m_symbol;
    const char*     m_tradingSession;
    const char*     m_entryId;
    Decimal         m_entryPx;
    Decimal         m_entrySize;
    UINT64          m_securityId;
    UINT64          m_entryIdInt;
    UINT64          m_entrySizeInt;
    MDUpdateAction  m_action;
    MDEntryType     m_entryType;
    int             m_rptSeq;
    int             m_sessionStatus;

    TestTemplateItemInfo() :
            m_action(MDUpdateAction::mduaAdd),
            m_symbol(0),
            m_securityId(0),
            m_tradingSession(0),
            m_entryType(MDEntryType::mdetBuyQuote),
            m_entryId(0),
            m_entryIdInt(0),
            m_entryPx(0,0),
            m_entrySize(0,0),
            m_entrySizeInt(0),
            m_rptSeq(0),
            m_sessionStatus(0) {

    }

    TestTemplateItemInfo(MDUpdateAction action, MDEntryType entryType, const char *symbol, UINT64 securityId, UINT64 entryId, int rptSeq, int pxm, INT64 pxe, int size) : TestTemplateItemInfo() {
        this->m_action = action;
        this->m_entryType = entryType;
        this->m_symbol = symbol;
        this->m_securityId = securityId;
        this->m_entryIdInt = entryId;
        this->m_entryPx.Set(pxm, pxe);
        this->m_entrySizeInt = size;
        this->m_rptSeq = rptSeq;
        this->m_sessionStatus = 0;
    }
    TestTemplateItemInfo(MDUpdateAction action, MDEntryType entryType, const char *symbol, const char *sessionId, const char *entryId, int rptSeq, int pxm, INT64 pxe, int sizem, INT64 sizee) : TestTemplateItemInfo() {
        this->m_action = action;
        this->m_entryType = entryType;
        this->m_symbol = symbol;
        this->m_tradingSession = sessionId;
        this->m_entryId = entryId;
        this->m_entryPx.Set(pxm, pxe);
        this->m_entrySize.Set(sizem, sizee);
        this->m_rptSeq = rptSeq;
        this->m_sessionStatus = 0;
    }
    TestTemplateItemInfo(const char *symbol, UINT64 securityId, UINT64 entryId, int rptSeq) : TestTemplateItemInfo() {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_symbol = symbol;
        this->m_securityId = securityId;
        this->m_tradingSession = "ses1";
        this->m_entryIdInt = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySizeInt = 10;
        this->m_rptSeq = rptSeq;
        this->m_sessionStatus = 0;
    }
    TestTemplateItemInfo(const char *symbol, const char *entryId, int rptSeq) : TestTemplateItemInfo() {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_symbol = symbol;
        this->m_tradingSession = "ses1";
        this->m_entryId = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
        this->m_rptSeq = rptSeq;
        this->m_sessionStatus = 0;
    }
    TestTemplateItemInfo(UINT64 entryId) : TestTemplateItemInfo() {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_entryIdInt = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySizeInt = 10;
        this->m_sessionStatus = 0;
    }
    TestTemplateItemInfo(UINT64 entryId, int price) : TestTemplateItemInfo() {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_entryIdInt = entryId;
        this->m_entryPx.Set(price, 0);
        this->m_entrySizeInt = 10;
        this->m_sessionStatus = 0;
    }
    TestTemplateItemInfo(const char *entryId) : TestTemplateItemInfo() {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_entryId = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
        this->m_sessionStatus = 0;
    }
};

class TestTemplateInfo {
public:
    TestTemplateItemInfo*   m_items[8];
    const char              *m_symbol;
    const char              *m_session;
    const char              *m_sessionSubId;
    char                    *m_senderId;
    char                    *m_pass;
    UINT64                  m_securityId;
    int                     m_msgSeqNo;
    int                     m_itemsCount;
    int                     m_rptSec;
    int                     m_lastMsgSeqNoProcessed;
    int                     m_totNumReports;
    int                     m_auctionIndicator;
    FeedTemplateId   m_templateId;
    SecurityStatus          m_sessionStatus;
    bool                    m_routeFirst;
    bool                    m_lastFragment;
    bool                    m_lost;
    bool                    m_wait;
    bool                    m_skip;
    char                    m_paddingBytes[3];

    TestTemplateInfo() {
        this->m_templateId = FeedTemplateId::fcmHeartBeat;
        this->m_msgSeqNo = 0;
        this->m_routeFirst = false;
        this->m_lastFragment = false;
        this->m_itemsCount = 0;
        this->m_rptSec = 0;
        this->m_lastMsgSeqNoProcessed = 0;
        this->m_symbol = 0;
        this->m_session = 0;
        this->m_lost = false;
        this->m_wait = false;
        this->m_skip = false;
        this->m_totNumReports = 0;
    }

    TestTemplateInfo(FeedTemplateId templateId, int msgSeqNo) : TestTemplateInfo() {
        this->m_templateId = templateId;
        this->m_msgSeqNo = msgSeqNo;
        this->m_itemsCount = 0;
    }
    TestTemplateInfo(FeedTemplateId templateId, int msgSeqNo, TestTemplateItemInfo **items, int itemCount) : TestTemplateInfo(templateId, msgSeqNo) {
        this->m_itemsCount = itemCount;
        for(int i = 0; i < itemCount; i++)
            this->m_items[i] = items[i];
    }
    TestTemplateInfo(FeedTemplateId templateId, int msgSeqNo, TestTemplateItemInfo **items, int itemCount, int rptSeq) : TestTemplateInfo(templateId, msgSeqNo, items, itemCount) {
        this->m_rptSec = rptSeq;
    }
    TestTemplateInfo(FeedTemplateId templateId, int msgSeqNo, const char *symbol, const char *session, bool routeFirst, bool lastMessage, TestTemplateItemInfo **items, int itemCount, int rptSeq) :
            TestTemplateInfo(templateId, msgSeqNo, items, itemCount, rptSeq) {
        this->m_symbol = symbol;
        this->m_session = session;
        this->m_routeFirst = routeFirst;
        this->m_lastFragment = lastMessage;
    }

    TestTemplateInfo(FeedTemplateId templateId, int msgSeqNo, const char *symbol, UINT64 securityId, bool routeFirst, bool lastMessage, TestTemplateItemInfo **items, int itemCount, int rptSeq) :
            TestTemplateInfo(templateId, msgSeqNo, items, itemCount, rptSeq) {
        this->m_symbol = symbol;
        this->m_securityId = securityId;
        this->m_routeFirst = routeFirst;
        this->m_lastFragment = lastMessage;
    }
};

#endif //TEST
#endif //HFT_ROBOT_TESTTEMPLATEINFO_H
