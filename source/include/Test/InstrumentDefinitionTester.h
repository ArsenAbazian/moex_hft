//
// Created by root on 11.12.16.
//

#ifndef HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
#define HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H

#include "../FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class InstrumentDefinitionTester{
    FeedConnection *olr;
    FeedConnection *ols;
    FeedConnection *tlr;
    FeedConnection *tls;
    FeedConnection *msr;
    FeedConnection *mss;
    FeedConnection *idf;

    TestMessagesHelper *m_helper;

public:
    InstrumentDefinitionTester() {
        this->m_helper = new TestMessagesHelper();

        this->olr = new FeedConnection_FOND_OLR("OLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->tlr = new FeedConnection_FOND_TLR("TSR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->msr = new FeedConnection_FOND_MSR("MSR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->idf = new FeedConnection_FOND_IDF("IDF", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);

        this->idf->AddConnectionToRecvSymbol(this->olr);
        this->idf->AddConnectionToRecvSymbol(this->msr);
        this->idf->AddConnectionToRecvSymbol(this->tlr);
    }
    ~InstrumentDefinitionTester() {
        delete this->olr;
        delete this->tlr;
        delete this->msr;
        delete this->idf;
    }

    void Clear() {
        this->olr->OrderFond()->Clear();
        this->tlr->TradeFond()->Clear();
        this->msr->StatisticFond()->Clear();
    }

    void TestDefaults() {
        if(this->idf->ConnectionsToRecvSymbolsCount() != 3)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[0] != this->olr)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[1] != this->msr)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[2] != this->tlr)
            throw;
        if(this->idf->Type() != FeedConnectionType::InstrumentDefinition)
            throw;
        if(this->idf->SecurityDefinitionMode() != FeedConnectionSecurityDefinitionMode::sdmCollectData)
            throw;
        if(this->idf->m_securityDefinitionsCount != 0)
            throw;
    }

    void TestAddSymbol() {
        this->Clear();

        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");
        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddMarketSegemntGroup(info);

        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");
        this->m_helper->AddTradingSession(info, 1, "t3");
        this->m_helper->AddTradingSession(info, 1, "t4");

        if(info->MarketSegmentGrpCount != 2)
            throw;

        this->idf->BeforeProcessSecurityDefinitions();
        if(!StringIdComparer::Equal(info->Symbol, 2, "s1", 2))
            throw;
        if(!this->idf->ProcessSecurityDefinition(info))
            throw;
        if(!StringIdComparer::Equal(info->Symbol, 2, "s1", 2))
            throw;
        if(this->idf->SecurityDefinitions()[0]->Data() != info)
            throw;
        if(this->idf->SecurityDefinitionsCount() != 1)
            throw;
        if(!StringIdComparer::Equal(info->Symbol, 2, "s1", 2))
            throw;
        this->idf->AfterProcessSecurityDefinitions();

        if(this->olr->OrderFond()->SymbolsCount() != 1)
            throw;
        if(this->tlr->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->msr->StatisticFond()->SymbolsCount() != 1)
            throw;
        if(this->olr->OrderFond()->MaxSymbolsCount() != 1)
            throw;
        if(this->tlr->TradeFond()->MaxSymbolsCount() != 1)
            throw;
        if(this->msr->StatisticFond()->MaxSymbolsCount() != 1)
            throw;

        if(this->olr->OrderFond()->Symbol(0)->SessionCount() != 4)
            throw;
        if(this->tlr->TradeFond()->Symbol(0)->SessionCount() != 4)
            throw;
        if(this->msr->StatisticFond()->Symbol(0)->SessionCount() != 4)
            throw;
        if(this->olr->OrderFond()->Symbol(0)->MaxSessionCount() != 4)
            throw;
        if(this->tlr->TradeFond()->Symbol(0)->MaxSessionCount() != 4)
            throw;
        if(this->msr->StatisticFond()->Symbol(0)->MaxSessionCount() != 4)
            throw;

        if(!this->olr->OrderFond()->Symbol(0)->SecurityDefinition()->Used)
            throw;
        if(!this->tlr->TradeFond()->Symbol(0)->SecurityDefinition()->Used)
            throw;
        if(!this->msr->StatisticFond()->Symbol(0)->SecurityDefinition()->Used)
            throw;
        if(!this->olr->OrderFond()->Symbol(0)->Symbol()->Equal("s1"))
            throw;
        if(!this->tlr->TradeFond()->Symbol(0)->Symbol()->Equal("s1"))
            throw;
        if(!this->msr->StatisticFond()->Symbol(0)->Symbol()->Equal("s1"))
            throw;

        for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
            if(!this->olr->OrderFond()->Symbol(0)->SecurityDefinition()->MarketSegmentGrp[i]->Used)
                throw;
            if(!this->tlr->TradeFond()->Symbol(0)->SecurityDefinition()->MarketSegmentGrp[i]->Used)
                throw;
            if(!this->msr->StatisticFond()->Symbol(0)->SecurityDefinition()->MarketSegmentGrp[i]->Used)
                throw;
            for(int j = 0; j < info->MarketSegmentGrp[i]->TradingSessionRulesGrpCount; j++) {
                if(!this->olr->OrderFond()->Symbol(0)->SecurityDefinition()->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
                if(!this->tlr->TradeFond()->Symbol(0)->SecurityDefinition()->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
                if(!this->msr->StatisticFond()->Symbol(0)->SecurityDefinition()->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
            }
        }
    }

    void TestAddSymbol_2_Core(int symbolIndex, FastSecurityDefinitionInfo *info) {
        if(this->olr->OrderFond()->Symbol(symbolIndex)->SessionCount() != 4)
            throw;
        if(this->tlr->TradeFond()->Symbol(symbolIndex)->SessionCount() != 4)
            throw;
        if(this->msr->StatisticFond()->Symbol(symbolIndex)->SessionCount() != 4)
            throw;
        if(this->olr->OrderFond()->Symbol(symbolIndex)->MaxSessionCount() != 4)
            throw;
        if(this->tlr->TradeFond()->Symbol(symbolIndex)->MaxSessionCount() != 4)
            throw;
        if(this->msr->StatisticFond()->Symbol(symbolIndex)->MaxSessionCount() != 4)
            throw;

        if(!this->olr->OrderFond()->Symbol(symbolIndex)->SecurityDefinition()->Used)
            throw;
        if(!this->tlr->TradeFond()->Symbol(symbolIndex)->SecurityDefinition()->Used)
            throw;
        if(!this->msr->StatisticFond()->Symbol(symbolIndex)->SecurityDefinition()->Used)
            throw;

        for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
            if(!this->olr->OrderFond()->Symbol(symbolIndex)->SecurityDefinition()->MarketSegmentGrp[i]->Used)
                throw;
            if(!this->tlr->TradeFond()->Symbol(symbolIndex)->SecurityDefinition()->MarketSegmentGrp[i]->Used)
                throw;
            if(!this->msr->StatisticFond()->Symbol(symbolIndex)->SecurityDefinition()->MarketSegmentGrp[i]->Used)
                throw;
            for(int j = 0; j < info->MarketSegmentGrp[i]->TradingSessionRulesGrpCount; j++) {
                if(!this->olr->OrderFond()->Symbol(symbolIndex)->SecurityDefinition()->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
                if(!this->tlr->TradeFond()->Symbol(symbolIndex)->SecurityDefinition()->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
                if(!this->msr->StatisticFond()->Symbol(symbolIndex)->SecurityDefinition()->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
            }
        }
    }

    void TestAddSymbol_2() {
        this->Clear();
        if(this->idf->m_securityDefinitionsCount != 0)
            throw;

        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");
        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddMarketSegemntGroup(info);

        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");
        this->m_helper->AddTradingSession(info, 1, "t3");
        this->m_helper->AddTradingSession(info, 1, "t4");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s2");
        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddMarketSegemntGroup(info2);

        this->m_helper->AddTradingSession(info2, 0, "t1");
        this->m_helper->AddTradingSession(info2, 0, "t2");
        this->m_helper->AddTradingSession(info2, 1, "t3");
        this->m_helper->AddTradingSession(info2, 1, "t4");

        if(info->MarketSegmentGrpCount != 2)
            throw;

        this->idf->BeforeProcessSecurityDefinitions();
        if(!this->idf->ProcessSecurityDefinition(info))
            throw;
        if(!this->idf->ProcessSecurityDefinition(info2))
            throw;
        this->idf->AfterProcessSecurityDefinitions();

        if(this->olr->OrderFond()->SymbolsCount() != 2)
            throw;
        if(this->tlr->TradeFond()->SymbolsCount() != 2)
            throw;
        if(this->msr->StatisticFond()->SymbolsCount() != 2)
            throw;
        if(this->olr->OrderFond()->MaxSymbolsCount() != 2)
            throw;
        if(this->tlr->TradeFond()->MaxSymbolsCount() != 2)
            throw;
        if(this->msr->StatisticFond()->MaxSymbolsCount() != 2)
            throw;

        TestAddSymbol_2_Core(0, info);
        TestAddSymbol_2_Core(1, info2);
    }

    void TestClearBeforeStart() {
        this->TestAddSymbol();
        this->idf->m_securityDefinitionsCount = 5;

        FastSecurityDefinitionInfo *info = this->idf->SecurityDefinition(0);
        this->idf->BeforeProcessSecurityDefinitions();
        if(this->idf->m_securityDefinitionsCount != 0)
            throw;

        if(info->Used)
            throw;
        if(info->Allocator->Count() != 0)
            throw;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
            if(info->MarketSegmentGrp[i]->Used)
                throw;
            if(info->MarketSegmentGrp[i]->Allocator->Count() != 0)
                throw;
            for(int j = 0; j < info->MarketSegmentGrp[i]->TradingSessionRulesGrpCount; j++) {
                if(info->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Used)
                    throw;
                if(info->MarketSegmentGrp[i]->TradingSessionRulesGrp[j]->Allocator->Count() != 0)
                    throw;
            }
        }

        if(this->idf->SecurityDefinitionsCount() != 0)
            throw;
        if(this->olr->OrderFond()->SymbolsCount() != 0)
            throw;
        if(this->tlr->TradeFond()->SymbolsCount() != 0)
            throw;
        if(this->msr->StatisticFond()->SymbolsCount() != 0)
            throw;
        if(this->olr->OrderFond()->MaxSymbolsCount() != 0)
            throw;
        if(this->tlr->TradeFond()->MaxSymbolsCount() != 0)
            throw;
        if(this->msr->StatisticFond()->MaxSymbolsCount() != 0)
            throw;
    }

    void TestUpdateSecurityDefinition() {
        TestAddSymbol();

        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");
        this->m_helper->AddMarketSegemntGroup(info);

        this->m_helper->AddTradingSession(info, 0, "t11");
        this->m_helper->AddTradingSession(info, 0, "t12");

        FastSecurityDefinitionInfo *prev = this->olr->OrderFond()->Symbol(0)->SecurityDefinition();
        this->idf->UpdateSecurityDefinition(info);

        if(this->olr->OrderFond()->Symbol(0)->SecurityDefinition() != info)
            throw;
        if(this->tlr->TradeFond()->Symbol(0)->SecurityDefinition() != info)
            throw;
        if(this->msr->StatisticFond()->Symbol(0)->SecurityDefinition() != info)
            throw;

        if(prev->Used)
            throw;
        if(prev->MarketSegmentGrp[0]->Used)
            throw;
        if(prev->MarketSegmentGrp[1]->Used)
            throw;
        if(prev->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Used)
            throw;
        if(prev->MarketSegmentGrp[0]->TradingSessionRulesGrp[1]->Used)
            throw;
        if(prev->MarketSegmentGrp[1]->TradingSessionRulesGrp[0]->Used)
            throw;
        if(prev->MarketSegmentGrp[1]->TradingSessionRulesGrp[1]->Used)
            throw;
    }

    void TestInstrumentDefinitionStartInCollectDataMode() {
        this->idf->Stop();

        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->Start();
        if(this->idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(this->idf->m_idfDataCollected)
            throw;
        if(this->idf->m_securityDefinitionsCount != 0)
            throw;
        if(this->idf->m_idfMode != FeedConnectionSecurityDefinitionMode::sdmCollectData)
            throw;
    }

    void TestInstrumentDefinitionCollectDataCompleted_1_Core(FastSecurityDefinitionInfo *info) {
        if(this->idf->SecurityDefinitions()[0]->Data()->MarketSegmentGrpCount != 1)
            throw;
        if(this->idf->SecurityDefinitions()[1]->Data()->MarketSegmentGrpCount != 1)
            throw;
        if(this->idf->SecurityDefinitions()[0]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 2)
            throw;
        if(this->idf->SecurityDefinitions()[1]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 2)
            throw;
        if(!StringIdComparer::Equal(this->idf->SecurityDefinitions()[0]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionID,
                                    this->idf->SecurityDefinitions()[0]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionIDLength,
                                    "t1", 2))
            throw;
        if(!StringIdComparer::Equal(this->idf->SecurityDefinitions()[0]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[1]->TradingSessionID,
                                    this->idf->SecurityDefinitions()[0]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[1]->TradingSessionIDLength,
                                    "t2", 2))
            throw;
        if(!StringIdComparer::Equal(this->idf->SecurityDefinitions()[1]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionID,
                                    this->idf->SecurityDefinitions()[1]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionIDLength,
                                    "t1", 2))
            throw;
        if(!StringIdComparer::Equal(this->idf->SecurityDefinitions()[1]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[1]->TradingSessionID,
                                    this->idf->SecurityDefinitions()[1]->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[1]->TradingSessionIDLength,
                                    "t2", 2))
            throw;
    }

    // no packet was lost, symbol repeats, so symbols ended....
    void TestInstrumentDefinitionCollectDataCompleted_1() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->Start();

        if(this->idf->IsIdfDataCollected())
            throw;
        this->m_helper->SendMessages(this->idf, "idf s1 session t1 session t2, idf s2 session t1 session t2, idf s1 session t1 session t2", 30);
        if(this->idf->m_startMsgSeqNum != 4)
            throw;
        if(this->idf->m_endMsgSeqNum != 3)
            throw;
        if(this->idf->SecurityDefinitionsCount() != 2)
            throw;
        if(!this->idf->IsIdfDataCollected())
            throw;
    }

    void TestInstrumentDefinitionCollectDataCompleted() {
        printf("IDF FOND TestInstrumentDefinitionCollectDataCompleted_1\n");
        TestInstrumentDefinitionCollectDataCompleted_1();
    }

    void TestStart() {
        idf->Stop();
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();
        if(idf->IdfState() != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(this->idf->m_securityDefinitionsCount != 0)
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost() {
        this->Clear();
        this->idf->Stop();
        idf->Stop();
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessages(this->idf, "idf totNumReports 3 s1 session t1 session t2, lost idf totNumReports 3 s2 session t1 session t2, idf totNumReports 3 s1 session t1 session t2, msgSeqNo 1 idf totNumReports 3 s1 session t1 session t2", 30);
        if(this->idf->m_idfDataCollected)
            throw;
        if(this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        this->m_helper->SendMessages(this->idf, "lost idf totNumReports 3 s1 session t1 session t2, lost idf totNumReports 3 s2 session t1 session t2, idf totNumReports 3 s1 session t1 session t2, msgSeqNo 1 idf totNumReports 3 s1 session t1 session t2", 30);
        if(this->idf->m_idfDataCollected)
            throw;
        this->m_helper->SendMessages(this->idf, "idf totNumReports 3 s1 session t1 session t2, idf totNumReports 3 s2 session t1 session t2, idf totNumReports 3 s1 session t1 session t2, msgSeqNo 1 idf totNumReports 3 s1 session t1 session t2", 30);
        if(!this->idf->m_idfDataCollected)
            throw;
        if(this->olr->OrderFond()->SymbolsCount() != 3)
            throw;
    }

    void Test() {
        printf("IDF FOND TestInstrumentDefinitionSomeMessagesLost\n");
        TestInstrumentDefinitionSomeMessagesLost();
        printf("IDF FOND TestInstrumentDefinitionStartInCollectDataMode\n");
        TestInstrumentDefinitionStartInCollectDataMode();
        printf("IDF FOND TestInstrumentDefinitionCollectDataCompleted\n");
        TestInstrumentDefinitionCollectDataCompleted();

        printf("IDF FOND TestDefaults\n");
        TestDefaults();
        printf("IDF FOND TestAddSymbol\n");
        TestAddSymbol();
        printf("IDF FOND TestAddSymbol_2\n");
        TestAddSymbol_2();
        printf("IDF FOND TestClearBeforeStart\n");
        TestClearBeforeStart();
        printf("IDF FOND TestUpdateSecurityDefinition\n");
        TestUpdateSecurityDefinition();
        printf("IDF FOND TestStart()\n");
        TestStart();
    }
};

#endif //HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
