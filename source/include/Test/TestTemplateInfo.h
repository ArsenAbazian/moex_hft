//
// Created by root on 11.12.16.
//

#ifndef HFT_ROBOT_TESTTEMPLATEINFO_H
#define HFT_ROBOT_TESTTEMPLATEINFO_H

#include "../FeedConnection.h"

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

    TestTemplateItemInfo() { }

    TestTemplateItemInfo(MDUpdateAction action, MDEntryType entryType, const char *symbol, const char *sessionId, const char *entryId, int rptSeq, int pxm, INT64 pxe, int sizem, INT64 sizee) {
        this->m_action = action;
        this->m_entryType = entryType;
        this->m_symbol = symbol;
        this->m_tradingSession = sessionId;
        this->m_entryId = entryId;
        this->m_entryPx.Set(pxm, pxe);
        this->m_entrySize.Set(sizem, sizee);
        this->m_rptSeq = rptSeq;
    }
    TestTemplateItemInfo(const char *symbol, const char *entryId, int rptSeq) {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_symbol = symbol;
        this->m_tradingSession = "session1";
        this->m_entryId = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
        this->m_rptSeq = rptSeq;
    }
    TestTemplateItemInfo(const char *entryId) {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_entryId = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
    }
};

class TestTemplateInfo {
public:
    FeedConnectionMessage   m_templateId;
    int                     m_msgSeqNo;
    bool                    m_routeFirst;
    bool                    m_lastFragment;
    int                     m_itemsCount;
    int                     m_rptSec;
    int                     m_lastMsgSeqNoProcessed;
    TestTemplateItemInfo*   m_items[8];
    const char              *m_symbol;
    const char              *m_session;
    const char              *m_sessionSubId;
    char                    *m_senderId;
    char                    *m_pass;
    bool                    m_lost;
    bool                    m_wait;
    bool                    m_skip;
    int                     m_totNumReports;
    SecurityStatus          m_sessionStatus;
    int                     m_auctionIndicator;

    TestTemplateInfo() {
        this->m_templateId = FeedConnectionMessage::fcmHeartBeat;
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

    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo) : TestTemplateInfo() {
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
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, const char *symbol, const char *session, bool routeFirst, bool lastMessage, TestTemplateItemInfo **items, int itemCount, int rptSeq) :
            TestTemplateInfo(templateId, msgSeqNo, items, itemCount, rptSeq) {
        this->m_symbol = symbol;
        this->m_session = session;
        this->m_routeFirst = routeFirst;
        this->m_lastFragment = lastMessage;
    }
};

#endif //HFT_ROBOT_TESTTEMPLATEINFO_H
