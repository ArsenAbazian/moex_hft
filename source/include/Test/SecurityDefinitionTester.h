//
// Created by root on 11.12.16.
//

#ifndef HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
#define HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
#include "Settings.h"

#ifdef TEST

#include "Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include "SymbolManagerTester.h"
#include <stdio.h>

class SecurityDefinitionTester{
    FeedConnection *olr;
    FeedConnection *ols;
    FeedConnection *tlr;
    FeedConnection *tls;
    FeedConnection *msr;
    FeedConnection *mss;
    FeedConnection *idf;

    TestMessagesHelper *m_helper;

public:
    SecurityDefinitionTester() {
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
        this->idf = new FeedConnection_FOND_IDF("IDF", "Full Refresh", 'S',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);

        this->idf->AddConnectionToRecvSymbol(this->olr);
        this->idf->AddConnectionToRecvSymbol(this->msr);
        this->idf->AddConnectionToRecvSymbol(this->tlr);
        this->idf->IdfAllowGenerateSecurityDefinitions(true);
    }
    ~SecurityDefinitionTester() {
        delete this->olr;
        delete this->tlr;
        delete this->msr;
        delete this->idf;
    }

    void Clear() {
        this->olr->OrderFond()->Clear();
        this->tlr->TradeFond()->Clear();
        this->msr->StatisticFond()->Clear();
        this->idf->ClearSecurityDefinitions();
        this->idf->m_symbolManager->Clear();
    }

    void TestDefaults() {
        if(!this->idf->IdfAllowGenerateSecurityDefinitions())
            throw;
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
        if(this->idf->m_symbolsCount != 0)
            throw;
        if(this->idf->m_idfDataCollected)
            throw;
        if(this->idf->m_idfMode != FeedConnectionSecurityDefinitionMode::sdmCollectData)
            throw;
        if(this->idf->m_idfStartMsgSeqNo != 0)
            throw;
        if(this->idf->m_idfMaxMsgSeqNo != 0)
            throw;
        if(this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(this->idf->m_idfAllowUpdateData == true)
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
        if(this->idf->Symbols()[0]->Data() != info)
            throw;
        if(this->idf->SymbolCount() != 1)
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
        if(this->idf->m_symbolsCount != 0)
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

    void TestBeforeProcessSecurityDefinitions() {
        this->TestAddSymbol();
        if(this->idf->m_symbolsCount == 0)
            throw;

        FastSecurityDefinitionInfo *info = this->idf->Symbol(0);
        this->idf->BeforeProcessSecurityDefinitions();
        if(this->idf->m_symbolsCount != 0)
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

        if(this->idf->SymbolCount() != 0)
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

        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

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
        if(!prev->MarketSegmentGrp[1]->Used)
            throw;
        if(!info->MarketSegmentGrp[0]->Used)
            throw;
        if(prev->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Used)
            throw;
        if(prev->MarketSegmentGrp[0]->TradingSessionRulesGrp[1]->Used)
            throw;
        if(!prev->MarketSegmentGrp[1]->TradingSessionRulesGrp[0]->Used)
            throw;
        if(!prev->MarketSegmentGrp[1]->TradingSessionRulesGrp[1]->Used)
            throw;
    }

    // no packet was lost, symbol repeats, so m_symbols ended....
    void TestInstrumentDefinitionCollectDataCompleted_1() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->Start();

        if(this->idf->IsIdfDataCollected())
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "totNumReports 2 idf s1 session t1 session t2, totNumReports 2 idf s2 session t1 session t2, msgSeqNo 1 totNumReports 2 idf s1 session t1 session t2",
                                        30);
        if(this->idf->m_startMsgSeqNum != 0)
            throw;
        if(this->idf->m_idfStartMsgSeqNo != 0)
            throw;
        if(this->idf->m_endMsgSeqNum != 1)
            throw;
        if(this->idf->m_idfMaxMsgSeqNo != 2)
            throw;
        if(this->idf->SymbolCount() != 2)
            throw;
        if(!this->idf->IsIdfDataCollected())
            throw;
        if(this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    // same as TestInstrumentDefinitionCollectDataCompleted_1
    // but message begins from 2 msg THE LAST MESSAGE
    void TestInstrumentDefinitionCollectDataCompleted_2() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->Start();

        if(this->idf->IsIdfDataCollected())
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "msgSeqNo 2 totNumReports 2 idf s1 session t1 session t2, msgSeqNo 1 totNumReports 2 idf s2 session t1 session t2, msgSeqNo 2 totNumReports 2 idf s1 session t1 session t2",
                                        30);
        if(this->idf->m_startMsgSeqNum != 0)
            throw;
        if(this->idf->m_idfStartMsgSeqNo != 0)
            throw;
        if(this->idf->m_endMsgSeqNum != 2)
            throw;
        if(this->idf->m_idfMaxMsgSeqNo != 2)
            throw;
        if(this->idf->SymbolCount() != 2)
            throw;
        if(!this->idf->IsIdfDataCollected())
            throw;
        if(this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestInstrumentDefinitionCollectDataCompleted() {
        printf("IDF FOND TestInstrumentDefinitionCollectDataCompleted_1\n");
        TestInstrumentDefinitionCollectDataCompleted_1();
        printf("IDF FOND TestInstrumentDefinitionCollectDataCompleted_2\n");
        TestInstrumentDefinitionCollectDataCompleted_2();
    }

    void TestSymbolManagerCleared() {
        SymbolManager *m = this->idf->m_symbolManager;
        if(m->SymbolCount() != 0)
            throw;
        for(int i = 0; i < m->BucketListCount(); i++)
            if(m->m_bucketList[i] != 0)
                throw;
        if(m->m_pool->CalcPoolCount() != m->m_pool->Capacity())
            throw;
    }

    void TestSecondStart() {
        idf->Stop(); // by the way - make stop. if it is already stopped it will skip
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();
        if(this->idf->State() == FeedConnectionState::fcsSuspend)
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "idf s1 totNumReports 3 session t1 session t2, idf s2 totNumReports 3 session t1 session t2, idf s3 totNumReports 3 session t1 session t2, msgSeqNo 1 idf s1 totNumReports 3 session t1 session t2",
                                        30);
        // check - stop called? but i dont know if we should stop connection
        if(this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        // test correct initialization
        if(this->idf->SymbolCount() != 3)
            throw;
        if(this->olr->OrderFond()->SymbolsCount() != 3)
            throw;
        if(!this->idf->m_idfDataCollected)
            throw;
        // again collect data
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();
        if(this->idf->m_idfDataCollected)
            throw;
        if(this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(this->idf->m_idfStartMsgSeqNo != 0)
            throw;
        if(this->idf->m_idfMaxMsgSeqNo != 0)
            throw;
        if(this->idf->m_endMsgSeqNum != 0)
            throw;
        if(this->idf->m_startMsgSeqNum != 0)
            throw;
        this->TestSymbolManagerCleared();
    }

    void TestInstrumentDefinitionSomeMessagesLost_1() {
        this->Clear();
        idf->Stop();
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "idf s1 totNumReports 3 session t1 session t2, lost idf s2 totNumReports 3 session t1 session t2, idf s3 totNumReports 3 session t1 session t2, msgSeqNo 1 idf s1 totNumReports 3 session t1 session t2",
                                        30);
        if(this->idf->m_idfDataCollected)
            throw;
        if(this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "lost idf s1 totNumReports 3  session t1 session t2, lost idf s2 totNumReports 3  session t1 session t2, idf s3 totNumReports 3 session t1 session t2, msgSeqNo 1 idf s1 totNumReports 3 session t1 session t2",
                                        30);
        if(this->idf->m_idfDataCollected)
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "idf s1 totNumReports 3 session t1 session t2, idf s2 totNumReports 3 session t1 session t2, idf s3 totNumReports 3 session t1 session t2, msgSeqNo 1 idf s1 totNumReports 3 session t1 session t2",
                                        30);
        if(!this->idf->m_idfDataCollected)
            throw;
        if(this->olr->OrderFond()->SymbolsCount() != 3)
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost_2() {
        this->Clear();
        idf->Stop();
        idf->m_idfAllowUpdateData = false;
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2", 30);
        if(idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(idf->IsIdfDataCollected())
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2", 30);
        if(idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessFromStart)
            throw;
        if(idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(idf->IsIdfDataCollected())
            throw;
        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2", 30);
        if(idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!idf->IsIdfDataCollected())
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost_3() {
        this->Clear();
        idf->Stop();
        idf->m_idfAllowUpdateData = false;
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2", 30);
        if(idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(idf->IsIdfDataCollected())
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost_4() {
        this->Clear();
        idf->Stop();
        idf->m_idfAllowUpdateData = false;
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2", 30);
        if(idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(idf->IsIdfDataCollected())
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost_5() {
        this->Clear();
        idf->Stop();
        idf->m_idfAllowUpdateData = false;
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2", 30);
        if(idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(idf->IsIdfDataCollected())
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost_6() {
        this->Clear();
        idf->Stop();
        idf->m_idfAllowUpdateData = false;
        idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2"
                                                "lost msgSeqNo 3 idf s2 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 4 idf s3 totNumReports 4 session t1 session t2,"
                                                "lost msgSeqNo 1 idf s1 totNumReports 4 session t1 session t2,"
                                                "     msgSeqNo 2 idf s1 totNumReports 4 session t1 session t2,", 30);
        if(idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!idf->IsIdfDataCollected())
            throw;
        if(idf->SymbolCount() != 3)
            throw;
    }

    void TestInstrumentDefinitionSomeMessagesLost() {
        TestInstrumentDefinitionSomeMessagesLost_1();
        TestInstrumentDefinitionSomeMessagesLost_2();
        TestInstrumentDefinitionSomeMessagesLost_3();
        TestInstrumentDefinitionSomeMessagesLost_4();
        TestInstrumentDefinitionSomeMessagesLost_5();
        TestInstrumentDefinitionSomeMessagesLost_6();
    }

    void TestPacketsAreClear() {
        for(int i = 0; i < RobotSettings::Default->DefaultFeedConnectionPacketCount; i++) {
            if(this->idf->m_packets[i]->m_address != 0 ||
                    this->idf->m_packets[i]->m_processed ||
                    this->idf->m_packets[i]->m_requested)
                throw;
        }
    }

    void TestSecurityDefinitionsAreClear() {
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++) {
            if(this->idf->m_symbols[i]->Data() != 0)
                throw;
        }
    }

    void TestFirstStart() {
        this->idf->Start();
        if(this->idf->m_idfMaxMsgSeqNo != 0)
            throw;
        if(this->idf->m_idfStartMsgSeqNo != 0)
            throw;
        if(this->idf->m_symbolsCount != 0)
            throw;
        if(this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
        if(this->idf->m_startMsgSeqNum != 0)
            throw;
        if(this->idf->m_endMsgSeqNum != 0)
            throw;
        if(this->idf->m_idfMode != FeedConnectionSecurityDefinitionMode::sdmCollectData)
            throw;
        if(this->idf->m_idfDataCollected)
            throw;
        this->TestPacketsAreClear();
        this->TestSecurityDefinitionsAreClear();
    }

    // do not allow update data so just stop
    void TestSwitchToUpdateDataModeAfterDataCompleted_1() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->m_idfAllowUpdateData = false;
        this->idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "totNumReports 2 idf s1 session t1 session t2, totNumReports 2 idf s2 session t1 session t2, msgSeqNo 1 totNumReports 2 idf s1 session t1 session t2",
                                        30);
        if(this->idf->m_idfMode != FeedConnectionSecurityDefinitionMode::sdmCollectData)
            throw;
        if(this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(this->idf->SymbolCount() != 2)
            throw;
    }
    // switch to update mode
    void TestSwitchToUpdateDataModeAfterDataCompleted_2() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->m_idfAllowUpdateData = true;
        this->idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "totNumReports 2 idf s1 session t1 session t2, totNumReports 2 idf s2 session t1 session t2, msgSeqNo 1 totNumReports 2 idf s1 session t1 session t2",
                                        30);
        if(this->idf->m_idfMode != FeedConnectionSecurityDefinitionMode::sdmUpdateData)
            throw;
        if(this->idf->State() != FeedConnectionState::fcsListenSecurityDefinition)
            throw;
        if(this->idf->SymbolCount() != 2)
            throw;
    }
    // continue update security definitions data, do not update trading sessions...
    void TestSwitchToUpdateDataModeAfterDataCompleted_3() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->m_idfAllowUpdateData = true;
        this->idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "msgSeqNo 1 totNumReports 4 idf s1 session t1,"
                                                "msgSeqNo 2 totNumReports 4 idf s2 session t1,"
                                                "msgSeqNo 3 totNumReports 4 idf s1 session t2,"
                                                "msgSeqNo 4 totNumReports 4 idf s2 session t2,"
                                                "msgSeqNo 1 totNumReports 4 idf s1 session t1,"
                                                "msgSeqNo 2 totNumReports 4 idf s2 session t1",
                                        30);
        if(this->idf->m_idfMode != FeedConnectionSecurityDefinitionMode::sdmUpdateData)
            throw;
        if(this->idf->SymbolCount() != 2)
            throw;
        if(this->idf->Symbol(0)->MarketSegmentGrpCount != 2)
            throw;
        if(this->idf->Symbol(1)->MarketSegmentGrpCount != 2)
            throw;
        if(this->idf->Symbol(0)->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 1)
            throw;
        if(this->idf->Symbol(1)->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 1)
            throw;
        if(this->idf->Symbol(0)->MarketSegmentGrp[1]->TradingSessionRulesGrpCount != 1)
            throw;
        if(this->idf->Symbol(1)->MarketSegmentGrp[1]->TradingSessionRulesGrpCount != 1)
            throw;

        FastSecurityDefinitionMarketSegmentGrpItemInfo *m = this->idf->Symbol(0)->MarketSegmentGrp[0];
        if(!StringIdComparer::Equal(m->TradingSessionRulesGrp[0]->TradingSessionID, m->TradingSessionRulesGrp[0]->TradingSessionIDLength, "t1", 2))
            throw;
        m = this->idf->Symbol(0)->MarketSegmentGrp[1];
        if(!StringIdComparer::Equal(m->TradingSessionRulesGrp[0]->TradingSessionID, m->TradingSessionRulesGrp[0]->TradingSessionIDLength, "t2", 2))
            throw;

        m = this->idf->Symbol(1)->MarketSegmentGrp[0];
        if(!StringIdComparer::Equal(m->TradingSessionRulesGrp[0]->TradingSessionID, m->TradingSessionRulesGrp[0]->TradingSessionIDLength, "t1", 2))
            throw;
        m = this->idf->Symbol(1)->MarketSegmentGrp[1];
        if(!StringIdComparer::Equal(m->TradingSessionRulesGrp[0]->TradingSessionID, m->TradingSessionRulesGrp[0]->TradingSessionIDLength, "t2", 2))
            throw;
    }

    void TestSwitchToUpdateDataModeAfterDataCompleted() {
        printf("TestSwitchToUpdateDataModeAfterDataCompleted_1\n");
        TestSwitchToUpdateDataModeAfterDataCompleted_1();
        printf("TestSwitchToUpdateDataModeAfterDataCompleted_2\n");
        TestSwitchToUpdateDataModeAfterDataCompleted_2();
        printf("TestSwitchToUpdateDataModeAfterDataCompleted_3\n");
        TestSwitchToUpdateDataModeAfterDataCompleted_3();
    }

    void TestMergeSecurityDefinitions_1() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");
        this->m_helper->AddMarketSegemntGroup(info);

        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");
        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddMarketSegemntGroup(info2);

        this->m_helper->AddTradingSession(info2, 0, "t3");
        this->m_helper->AddTradingSession(info2, 0, "t4");

        this->m_helper->AddTradingSession(info2, 1, "t5");
        this->m_helper->AddTradingSession(info2, 1, "t6");

        this->idf->MergeSecurityDefinition(info, info2);

        if(info->MarketSegmentGrpCount != 3)
            throw;
        if(info->MarketSegmentGrp[1] != info2->MarketSegmentGrp[0])
            throw;
        if(info->MarketSegmentGrp[2] != info2->MarketSegmentGrp[1])
            throw;
        if(info->MarketSegmentGrp[1] == 0)
            throw;
        if(info->MarketSegmentGrp[2] == 0)
            throw;
    }

    void TestMergeSecurityDefinitions_2() {
        this->idf->Stop();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->m_idfAllowUpdateData = false;
        this->idf->Start();

        this->m_helper->SendMessagesIdf(this->idf,
                                        "msgSeqNo 1 totNumReports 4 idf s1 session t1,"
                                                "msgSeqNo 2 totNumReports 4 idf s2 session t1,"
                                                "msgSeqNo 3 totNumReports 4 idf s1 session t2,"
                                                "msgSeqNo 4 totNumReports 4 idf s2 session t2,"
                                                "msgSeqNo 1 totNumReports 4 idf s1 session t1",
                                        30);
        if(this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(this->idf->SymbolCount() != 2)
            throw;
        FastSecurityDefinitionInfo *info1 = this->idf->Symbol(0);
        if(info1->MarketSegmentGrpCount != 2)
            throw;
        if(info1->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 1)
            throw;
        if(info1->MarketSegmentGrp[1]->TradingSessionRulesGrpCount != 1)
            throw;
        if(!StringIdComparer::Equal(info1->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionID, 2, "t1", 2))
            throw;
        if(!StringIdComparer::Equal(info1->MarketSegmentGrp[1]->TradingSessionRulesGrp[0]->TradingSessionID, 2, "t2", 2))
            throw;

        FastSecurityDefinitionInfo *info2 = this->idf->Symbol(1);
        if(info2->MarketSegmentGrpCount != 2)
            throw;
        if(info2->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 1)
            throw;
        if(info2->MarketSegmentGrp[1]->TradingSessionRulesGrpCount != 1)
            throw;
        if(!StringIdComparer::Equal(info2->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionID, 2, "t1", 2))
            throw;
        if(!StringIdComparer::Equal(info2->MarketSegmentGrp[1]->TradingSessionRulesGrp[0]->TradingSessionID, 2, "t2", 2))
            throw;
    }

    void TestMergeSecurityDefinitions() {
        TestMergeSecurityDefinitions_1();
        TestMergeSecurityDefinitions_2();
    }

    void TestReplaceMarketSegmentGroupBy_1() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t1");

        this->idf->ReplaceMarketSegmentGroupById(info, info2->MarketSegmentGrp[0]);
        if(info->MarketSegmentGrp[0] != info2->MarketSegmentGrp[0])
            throw;
    }

    void TestReplaceMarketSegmentGroupBy_2() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t1");
        this->m_helper->AddTradingSession(info2, 0, "t2");

        this->idf->ReplaceMarketSegmentGroupById(info, info2->MarketSegmentGrp[0]);
        if(info->MarketSegmentGrp[0] != info2->MarketSegmentGrp[0])
            throw;
    }

    void TestReplaceMarketSegmentGroupBy_3() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t1");

        this->idf->ReplaceMarketSegmentGroupById(info, info2->MarketSegmentGrp[0]);
        if(info->MarketSegmentGrp[0] == info2->MarketSegmentGrp[0])
            throw;
    }

    void TestReplaceMarketSegmentGroupBy_4() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t1");
        this->m_helper->AddTradingSession(info2, 0, "t2");

        this->idf->ReplaceMarketSegmentGroupById(info, info2->MarketSegmentGrp[0]);
        if(info->MarketSegmentGrp[0] == info2->MarketSegmentGrp[0])
            throw;
    }

    void TestReplaceMarketSegmentGroupBy_5() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t2");
        this->m_helper->AddTradingSession(info2, 0, "t1");

        this->idf->ReplaceMarketSegmentGroupById(info, info2->MarketSegmentGrp[0]);
        if(info->MarketSegmentGrp[0] == info2->MarketSegmentGrp[0])
            throw;
    }

    void TestReplaceMarketSegmentGroupBy_6() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 1, "t2");
        this->m_helper->AddTradingSession(info, 1, "t1");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t2");
        this->m_helper->AddTradingSession(info2, 0, "t1");

        this->idf->ReplaceMarketSegmentGroupById(info, info2->MarketSegmentGrp[0]);
        if(info->MarketSegmentGrp[0] == info2->MarketSegmentGrp[0])
            throw;
        if(info->MarketSegmentGrp[1] != info2->MarketSegmentGrp[0])
            throw;
    }

    void TestReplaceMarketSegmentGroupBy() {
        TestReplaceMarketSegmentGroupBy_1();
        TestReplaceMarketSegmentGroupBy_2();
        TestReplaceMarketSegmentGroupBy_3();
        TestReplaceMarketSegmentGroupBy_4();
        TestReplaceMarketSegmentGroupBy_5();
        TestReplaceMarketSegmentGroupBy_6();
    }

    void TestUpdateSecurityDefinition2() {
        FastSecurityDefinitionInfo *info = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 0, "t1");
        this->m_helper->AddTradingSession(info, 0, "t2");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 1, "t3");
        this->m_helper->AddTradingSession(info, 1, "t4");

        this->m_helper->AddMarketSegemntGroup(info);
        this->m_helper->AddTradingSession(info, 2, "t5");
        this->m_helper->AddTradingSession(info, 2, "t6");

        FastSecurityDefinitionInfo *info2 = this->m_helper->CreateSecurityDefinitionInfo("s1");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 0, "t1");
        this->m_helper->AddTradingSession(info2, 0, "t2");

        this->m_helper->AddMarketSegemntGroup(info2);
        this->m_helper->AddTradingSession(info2, 1, "t3");
        this->m_helper->AddTradingSession(info2, 1, "t4");

        LinkedPointer<FastSecurityDefinitionInfo> *ptr = new LinkedPointer<FastSecurityDefinitionInfo>();
        ptr->Data(info);
        this->idf->UpdateSecurityDefinition(ptr, info2);
        if(ptr->Data() != info2)
            throw;
        if(info2->MarketSegmentGrpCount != 3)
            throw;
        if(info2->MarketSegmentGrp[0] == info->MarketSegmentGrp[0])
            throw;
        if(info2->MarketSegmentGrp[1] == info->MarketSegmentGrp[1])
            throw;
        if(info2->MarketSegmentGrp[2] != info->MarketSegmentGrp[2])
            throw;
    }

    void Test() {
        //DONT CHANGE ORDER
        printf("IDF FOND TestDefaults\n");
        TestDefaults();
        printf("IDF FOND TestFirstStart\n");
        TestFirstStart();
        printf("IDF FOND TestSecondStart()\n");
        TestSecondStart();
        // UNTIL THIS

        printf("IDF FOND TestReplaceMarketSegmentGroupBy\n");
        TestReplaceMarketSegmentGroupBy();
        printf("IDF FOND TestUpdateSecurityDefinition2\n");
        TestUpdateSecurityDefinition2();


        printf("IDF FOND TestAddSymbol\n");
        TestAddSymbol();
        printf("IDF FOND TestAddSymbol_2\n");
        TestAddSymbol_2();
        printf("IDF FOND TestBeforeProcessSecurityDefinitions\n");
        TestBeforeProcessSecurityDefinitions();
        printf("IDF FOND TestUpdateSecurityDefinition\n");
        TestUpdateSecurityDefinition();

        printf("TestMergeSecurityDefinitions\n");
        TestMergeSecurityDefinitions();

        printf("IDF FOND TestInstrumentDefinitionSomeMessagesLost\n");
        TestInstrumentDefinitionSomeMessagesLost();
        printf("IDF FOND TestInstrumentDefinitionCollectDataCompleted\n");
        TestInstrumentDefinitionCollectDataCompleted();
        printf("IDF FOND TestSwitchToUpdateDataModeAfterDataCompleted\n");
        TestSwitchToUpdateDataModeAfterDataCompleted();
    }
};

#endif
#endif //HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
