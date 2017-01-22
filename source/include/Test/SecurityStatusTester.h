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
    FeedConnection          *hr;
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
        this->hr = new FeedConnection_FOND_H("H", "Historical Replay", 'H',
                                               FeedConnectionProtocol::TCP_IP,
                                               "1.1.7.200", 20000);
        this->hr->SetSenderCompId("MyComp");

        this->isf->SetHistoricalReplay(this->hr);
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
        if(this->idf->m_symbolManager->SymbolCount() != 0)
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "msgSeqNo 1 totNumReports 2 idf smb1 session trd1 session trd2, "
                                                "msgSeqNo 2 totNumReports 2 idf smb2 session trd1 session trd2, "
                                                "msgSeqNo 1 totNumReports 2 idf smb1 session trd1 session trd2", 30);

        if(!this->idf->IsIdfDataCollected())
            throw;
        if(this->idf->m_symbolManager->SymbolCount() != 2)
            throw;
        bool newlyAdded = false;
        SymbolInfo *s1 = this->idf->m_symbolManager->GetSymbol("smb1", &newlyAdded);
        if(s1->m_index != 0 || newlyAdded)
            throw;
        SymbolInfo *s2 = this->idf->m_symbolManager->GetSymbol("smb2", &newlyAdded);
        if(s2->m_index != 1 || newlyAdded)
            throw;
        if(this->idf->m_symbolManager->SymbolCount() != 2)
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
                                                "msgSeqNo 3 isf smb1 trd1 NA 118 0,"
                                                "msgSeqNo 4 isf smb1 trd2 O 130 0,"
                                                "msgSeqNo 5 isf smb2 trd1 C 17  0,"
                                                "msgSeqNo 6 isf smb2 trd2 N 102 0",
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

    void TestCallHistoricalReplayWhenLostMessage() {
        throw;
    }

    void Test() {
        printf("ISF TestDefaults");
        TestDefaults();
        printf("ISF TestReceiveExistingSymbol");
        TestReceiveExistingSymbol();
        printf("ISF Call HistoricalReplay when lost message");
        TestCallHistoricalReplayWhenLostMessage();
    }
};

#endif //HFT_ROBOT_SECURITYSTATUSTESTER_H
