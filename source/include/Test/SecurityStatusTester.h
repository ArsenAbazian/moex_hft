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

    void InitSecurityDefinitionCore() {
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
    }

    void Clear() {
        this->idf->m_startMsgSeqNum = 1;
        this->idf->m_endMsgSeqNum = 0;
        this->isf->m_startMsgSeqNum = 1;
        this->isf->m_endMsgSeqNum = 0;
        this->idf->Stop();
        this->idf->ClearPackets(0, 100);
        this->isf->ClearPackets(0, 100);
        this->isf->Stop();
    }

    void TestReceiveExistingSymbol() {
        this->Clear();
        this->InitSecurityDefinitionCore();

        FastSecurityDefinitionInfo *info1 = this->idf->Symbol(0);
        FastSecurityDefinitionInfo *info2 = this->idf->Symbol(1);
        this->isf->Start();
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

    void TestCallHistoricalReplayWhenLostMessage_1() {
        this->Clear();
        this->InitSecurityDefinitionCore();

        FastSecurityDefinitionInfo *info1 = this->idf->Symbol(0);
        FastSecurityDefinitionInfo *info2 = this->idf->Symbol(1);
        this->isf->Start();
        this->m_helper->SendMessagesIsf_Hr(this->isf,
                                           this->hr,
                                           "     msgSeqNo 1 hbeat,"
                                                   "     msgSeqNo 2 hbeat,"
                                                   "     msgSeqNo 3 isf smb1 trd1 NA 118 0,"
                                                   "lost msgSeqNo 4 isf smb1 trd2 O 130 0,"
                                                   "     msgSeqNo 5 isf smb2 trd1 C 17  0,"
                                                   "     msgSeqNo 6 isf smb2 trd2 N 102 0",
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

    void TestCallHistoricalReplayWhenLostMessage_2() {
        this->Clear();
        this->InitSecurityDefinitionCore();

        FastSecurityDefinitionInfo *info1 = this->idf->Symbol(0);
        FastSecurityDefinitionInfo *info2 = this->idf->Symbol(1);
        this->isf->Start();
        this->m_helper->SendMessagesIsf_Hr(this->isf,
                                           this->hr,
                                           "     msgSeqNo 1 hbeat,"
                                           "     msgSeqNo 2 hbeat,"
                                           "     msgSeqNo 3 isf smb1 trd1 NA 118 0,"
                                           "lost msgSeqNo 4 isf smb1 trd2 O 130 0,"
                                           "lost msgSeqNo 5 isf smb2 trd1 C 17  0,"
                                           "     msgSeqNo 6 isf smb2 trd2 N 102 0",
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

    void TestCallHistoricalReplayWhenLostMessage_3() {
        this->Clear();

        this->idf->Stop();
        this->idf->Start();
        if(this->idf->m_symbolManager->SymbolCount() != 0)
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                                "msgSeqNo 1 totNumReports 7 idf smb1 session trd1, "
                                                "msgSeqNo 2 totNumReports 7 idf smb2 session trd1, "
                                                "msgSeqNo 3 totNumReports 7 idf smb3 session trd1, "
                                                "msgSeqNo 4 totNumReports 7 idf smb4 session trd1, "
                                                "msgSeqNo 5 totNumReports 7 idf smb5 session trd1, "
                                                "msgSeqNo 6 totNumReports 7 idf smb6 session trd1, "
                                                "msgSeqNo 7 totNumReports 7 idf smb7 session trd1, "
                                                "msgSeqNo 1 totNumReports 7 idf smb1 session trd1  ", 30);

        if(!this->idf->IsIdfDataCollected())
            throw;

        this->isf->Start();
        this->m_helper->SendMessagesIsf_Hr(this->isf,
                                           this->hr,
                                           "     msgSeqNo 1 hbeat,"
                                           "     msgSeqNo 2 hbeat,"
                                           "     msgSeqNo 3 isf smb1 trd1 NA 118 0, "
                                           "lost msgSeqNo 4 isf smb2 trd1 O  130 0, "
                                           "lost msgSeqNo 5 isf smb3 trd1 C  17  0, "
                                           "lost msgSeqNo 6 isf smb4 trd1 N  102 0, "
                                           "lost msgSeqNo 7 isf smb5 trd1 N  102 0, "
                                           "lost msgSeqNo 8 isf smb6 trd1 C  17  0, "
                                           "lost msgSeqNo 9 isf smb7 trd1 O  17  0, "
                                           "     msgSeqNo 10 hbeat",
                                           30);

        if(TradingSession(this->idf->Symbol(0), 0, 0)->SecurityTradingStatus != 118)
            throw;
        if(TradingSession(this->idf->Symbol(1), 0, 0)->SecurityTradingStatus != 130)
            throw;
        if(TradingSession(this->idf->Symbol(2), 0, 0)->SecurityTradingStatus != 17)
            throw;
        if(TradingSession(this->idf->Symbol(3), 0, 0)->SecurityTradingStatus != 102)
            throw;
        if(TradingSession(this->idf->Symbol(4), 0, 0)->SecurityTradingStatus != 102)
            throw;
        if(TradingSession(this->idf->Symbol(5), 0, 0)->SecurityTradingStatus != 17)
            throw;
        if(TradingSession(this->idf->Symbol(6), 0, 0)->SecurityTradingStatus != 17)
            throw;
    }

    void TestCallHistoricalReplayWhenLostMessage() {
        TestCallHistoricalReplayWhenLostMessage_1();
        TestCallHistoricalReplayWhenLostMessage_2();
        TestCallHistoricalReplayWhenLostMessage_3();
    }

    void Test() {
        printf("ISF TestDefaults");
        TestDefaults();
        printf("ISF TestReceiveExistingSymbol");
        TestReceiveExistingSymbol();
        printf("ISF Call TestCallHistoricalReplayWhenLostMessage");
        TestCallHistoricalReplayWhenLostMessage();
    }
};

#endif //HFT_ROBOT_SECURITYSTATUSTESTER_H
