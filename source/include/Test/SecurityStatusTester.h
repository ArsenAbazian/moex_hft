//
// Created by root on 20.01.17.
//

#ifndef HFT_ROBOT_SECURITYSTATUSTESTER_H
#define HFT_ROBOT_SECURITYSTATUSTESTER_H

#include "../FeedConnection.h"
#include "../FeedConnections.h"
#include "TestMessagesHelper.h"
#include "SymbolManagerTester.h"
#include <stdio.h>


class SecurityStatusTester{
    FeedConnection          *idf;
    FeedConnection          *isf;
    TestMessagesHelper      *m_helper;
public:
    SecurityStatusTester() {
        this->m_helper = new TestMessagesHelper();

        this->idf = new FeedConnection_FOND_IDF("IDF", "Full Refresh", 'S',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);

        this->isf = new FeedConnection_FOND_ISF("ISF", "Full Refresh", 'I',
                                               FeedConnectionProtocol::UDP_IP,
                                               "10.50.129.200", "239.192.113.3", 9113,
                                               "10.50.129.200", "239.192.113.131", 9313);
        this->isf->SetSecurityDefinition(this->idf);

    }
    ~SecurityStatusTester() {
        delete this->m_helper;
        delete this->idf;
        delete this->isf;
    }

    FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *TradingSession(FastSecurityDefinitionInfo *info, int marketIndex, int sessionIndex) {
        return info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrp[sessionIndex];
    }

    void TestDefaults() {
        if(this->isf->Type() != FeedConnectionType::InstrumentStatus)
            throw;
        if(this->isf->SecurityDefinition() != this->idf)
            throw;
    }

    //Can be length of 1 or 2.
    bool EqualsTradingSessionSubId(FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *t, const char *tradingSessionSubId) {
        if(strlen(tradingSessionSubId) == 2)
            return t->TradingSessionSubID[0] == tradingSessionSubId[0] && t->TradingSessionSubID[1] == tradingSessionSubId[1];
        return t->TradingSessionSubID[0] == tradingSessionSubId[0];
    }

    void TestReceiveExistingSymbol() {
        this->idf->Stop();
        this->idf->Start();
        this->m_helper->SendMessagesIdf(this->idf,
                                        "msgSeqNo 1 totNumReports 2 idf s1 session t1 session t2, "
                                                "msgSeqNo 2 totNumReports 2 idf s2 session t1 session t2, "
                                                "msgSeqNo 1 totNumReports 2 idf s1 session t1 session t2", 30);

        if(!this->idf->IsIdfDataCollected())
            throw;

        FastSecurityDefinitionInfo *info1 = this->idf->Symbol(0);
        FastSecurityDefinitionInfo *info2 = this->idf->Symbol(1);
        if(TradingSession(info1, 0, 0)->SecurityTradingStatus != SecurityStatus::ssUndefined)
            throw;
        if(TradingSession(info1, 0, 1)->SecurityTradingStatus != SecurityStatus::ssUndefined)
            throw;
        if(TradingSession(info2, 0, 0)->SecurityTradingStatus != SecurityStatus::ssUndefined)
            throw;
        if(TradingSession(info2, 0, 1)->SecurityTradingStatus != SecurityStatus::ssUndefined)
            throw;

        this->m_helper->SendMessagesIsf(this->isf,
                                                "msgSeqNo 1 hbeat,"
                                                "msgSeqNo 2 hbeat,"
                                                "msgSeqNo 3 isf s1 t1 NA 118 0,"
                                                "msgSeqNo 4 isf s1 t2 O 130 0,"
                                                "msgSeqNo 5 isf s2 t1 C 17  0,"
                                                "msgSeqNo 6 isf s2 t2 N 102 0",
                                        30);

        if(!EqualsTradingSessionSubId(TradingSession(info1, 0, 0), "NA"))
            throw;
        if(!EqualsTradingSessionSubId(TradingSession(info1, 0, 1), "O"))
            throw;
        if(!EqualsTradingSessionSubId(TradingSession(info2, 0, 0), "C"))
            throw;
        if(!EqualsTradingSessionSubId(TradingSession(info2, 0, 1), "N"))
            throw;

        if(TradingSession(info1, 0, 0)->SecurityTradingStatus != 118)
            throw;
        if(TradingSession(info1, 0, 1)->SecurityTradingStatus != 130)
            throw;
        if(TradingSession(info2, 0, 0)->SecurityTradingStatus != 17)
            throw;
        if(TradingSession(info2, 0, 1)->SecurityTradingStatus != 102)
            throw;
    }

    void Test() {
        printf("ISF TestDefaults");
        TestDefaults();
        printf("ISF TestReceiveExistingSymbol");
        TestReceiveExistingSymbol();
    }
};

#endif //HFT_ROBOT_SECURITYSTATUSTESTER_H
