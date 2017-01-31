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
        if(this->isf->MaxLostPacketCountForStartSnapshot() != 0)
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
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
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
        this->hr->m_hsRequestList->Clear();
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
        this->isf->SetMaxLostPacketCountForStartSnapshot(100); // do not start snapshot.... :)
        TestCallHistoricalReplayWhenLostMessage_1();
        TestCallHistoricalReplayWhenLostMessage_2();
        TestCallHistoricalReplayWhenLostMessage_3();
    }

    void TestStartSnapshotInstedOfHistoricalReplay_1() {
        this->Clear();
        this->InitSecurityDefinitionCore();

        if (this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        this->isf->SetMaxLostPacketCountForStartSnapshot(0);
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
        if (this->idf->State() != FeedConnectionState::fcsListenSecurityDefinition) // start snapshot mode...
            throw;
        if (this->idf->SecurityDefinitionMode() != FeedConnectionSecurityDefinitionMode::sdmUpdateData)
            throw;
        // some idf values should be reset for correct start
        if (this->idf->m_idfStartMsgSeqNo != 0)
            throw;
        if (this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            throw;
    }
    // assume that SecurityDefinition is started already
    // do not start it again and!!! do not use historical replay
    void TestStartSnapshotInstedOfHistoricalReplay_2() {
        this->Clear();
        this->InitSecurityDefinitionCore();

        if (this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;

        this->idf->Start();
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmUpdateData;
        this->idf->m_idfStartMsgSeqNo = 1;
        this->idf->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessFromStart;
        this->idf->m_idfMaxMsgSeqNo = 2;

        this->isf->SetMaxLostPacketCountForStartSnapshot(0);
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
        if(this->idf->State() != FeedConnectionState::fcsListenSecurityDefinition) // start snapshot mode...
            throw;
        if(this->idf->SecurityDefinitionMode() != FeedConnectionSecurityDefinitionMode::sdmUpdateData)
            throw;
        if(this->idf->m_idfStartMsgSeqNo == 0)
            throw;
        if(this->idf->m_idfState != FeedConnectionSecurityDefinitionState::sdsProcessFromStart)
            throw;
        if(this->hr->m_hsRequestList->Count() > 0)
            throw;
    }

    // security definition and security status works in parallel
    // after complete all symbols security status should start from current msg_index
    // without any hr request or start snapshot
    // security definition not collect all the data
    // isf was started earlier
    void TestStartSnapshotInstedOfHistoricalReplay_3() {
        this->Clear();

        this->isf->SetMaxLostPacketCountForStartSnapshot(100);
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->m_idfAllowUpdateData = false;
        this->idf->Start();
        this->m_helper->SendMessagesIsf_Idf_Hr(
                this->isf, this->idf, this->hr,
                        "msgSeqNo 1 totNumReports 3 idf smb1 session trd1, "
                        "msgSeqNo 2 totNumReports 3 idf smb2 session trd1, "
                        "msgSeqNo 3 totNumReports 3 idf smb3 session trd1, "
                        "msgSeqNo 1 totNumReports 3 idf smb1 session trd1, "
                        "msgSeqNo 2 totNumReports 3 idf smb2 session trd1, "
                        "msgSeqNo 3 totNumReports 3 idf smb3 session trd1, "
                        "msgSeqNo 1 totNumReports 3 idf smb1 session trd1, "
                        "msgSeqNo 2 totNumReports 3 idf smb2 session trd1, "
                        "msgSeqNo 3 totNumReports 3 idf smb3 session trd1  "
                        ,
                        "msgSeqNo 1 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 2 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 3 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 4 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 5 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 6 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 7 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 8 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 9 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 10 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 11 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 12 hbeat  "
                ,
                30,
        true);
        if(!this->idf->IsIdfDataCollected())
            throw;
        if(this->idf->SymbolCount() != 3)
            throw;
        if(this->idf->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(this->isf->State() != FeedConnectionState::fcsListenSecurityStatus)
            throw;
        if(this->isf->m_endMsgSeqNum != 12)
            throw;
        if(this->isf->m_startMsgSeqNum != 12)
            throw;
        if(this->hr->m_hsRequestList->Count() != 0)
            throw;
        if(TradingSession(this->idf->Symbol(0), 0, 0)->SecurityTradingStatus != 118)
            throw;
    }

    // security definition and security status works in parallel
    // after complete all symbols security status should start from current msg_index
    // without any hr request or start snapshot
    // security definition not collect all the data
    // isf not started
    void TestStartSnapshotInstedOfHistoricalReplay_4() {
        printf("TODO Test Please Starting SecurityStatus after SecurityDefinition");
        /*this->Clear();

        this->isf->SetMaxLostPacketCountForStartSnapshot(100);
        this->idf->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->idf->m_idfAllowUpdateData = false;
        this->idf->Start();
        this->isf->Start();
        this->m_helper->SendMessagesIsf_Idf_Hr(
                this->isf, this->idf, this->hr,
                "msgSeqNo 1 totNumReports 3 idf smb1 session trd1, "
                        "msgSeqNo 2 totNumReports 3 idf smb2 session trd1, "
                        "msgSeqNo 3 totNumReports 3 idf smb3 session trd1, "
                        "msgSeqNo 1 totNumReports 3 idf smb1 session trd1, "
                        "msgSeqNo 2 totNumReports 3 idf smb2 session trd1, "
                        "msgSeqNo 3 totNumReports 3 idf smb3 session trd1, "
                        "msgSeqNo 1 totNumReports 3 idf smb1 session trd1, "
                        "msgSeqNo 2 totNumReports 3 idf smb2 session trd1, "
                        "msgSeqNo 3 totNumReports 3 idf smb3 session trd1  "
                ,
                "msgSeqNo 1 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 2 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 3 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 4 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 5 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 6 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 7 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 8 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 9 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 10 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 11 isf smb1 trd1 NA 118 0, "
                        "msgSeqNo 12 hbeat  "
                ,
                30);*/

    }

    // when security definition should stop?
    // lets try appreach when security definition is process one circle and then stop
    void TestStartSnapshotInstedOfHistoricalReplay_5() {
        throw;
    }

    void TestStartSnapshotInstedOfHistoricalReplay() {
        printf("ISF TestStartSnapshotInstedOfHistoricalReplay_1\n");
        TestStartSnapshotInstedOfHistoricalReplay_1();
        printf("ISF TestStartSnapshotInstedOfHistoricalReplay_2\n");
        TestStartSnapshotInstedOfHistoricalReplay_2();
        printf("ISF TestStartSnapshotInstedOfHistoricalReplay_3\n");
        TestStartSnapshotInstedOfHistoricalReplay_3();
        printf("ISF TestStartSnapshotInstedOfHistoricalReplay_4\n");
        TestStartSnapshotInstedOfHistoricalReplay_4();
        printf("ISF TestStartSnapshotInstedOfHistoricalReplay_5\n");
        TestStartSnapshotInstedOfHistoricalReplay_5();
    }

    // default
    void TestRequestLostMessagesLogic_1() {
        this->isf->m_startMsgSeqNum = 1;
        this->isf->m_endMsgSeqNum = 0;
        this->isf->ClearPackets(1, 1);
        this->isf->ProcessSecurityStatusMessages();
        if(this->isf->m_packets[1]->m_requested)
            throw;
    }

    // do not request
    void TestRequestLostMessagesLogic_2() {
        this->isf->m_startMsgSeqNum = 3;
        this->isf->m_endMsgSeqNum = 2;
        this->isf->ClearPackets(1, 5);
        this->isf->ProcessSecurityStatusMessages();
        if(this->isf->m_packets[3]->m_requested)
            throw;
    }

    unsigned char *CreateHearthBeatMessage(int msgIndex) {
        this->m_helper->m_fastManager->SetNewBuffer(this->m_helper->m_buffer->CurrentPos(), 1000);
        this->m_helper->EncodeHearthBeatMessage(new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, msgIndex));
        unsigned char *address = this->m_helper->m_buffer->CurrentPos();
        this->m_helper->m_buffer->Next(this->m_helper->m_fastManager->MessageLength());
        return address;
    }

    bool TestRequestedOnly(int startIndex, int endIndex) {
        for(int i = startIndex; i <= endIndex; i++) {
            if(!this->isf->m_packets[i]->m_requested)
                return false;
        }
        return true;
    }

    bool TestRequested(int startIndex, int endIndex) {
        for(int i = startIndex; i <= endIndex; i++) {
            if(!this->isf->m_packets[i]->m_requested)
                return false;
        }
        for(int i = 0; i < startIndex; i++) {
            if(this->isf->m_packets[i]->m_requested)
                return false;
        }
        for(int i = endIndex + 1; i < 1000; i++) {
            if(this->isf->m_packets[i]->m_requested)
                return false;
        }
        return true;
    }

    bool TestNotRequested(int startIndex, int endIndex) {
        for(int i = startIndex; i <= endIndex; i++) {
            if(this->isf->m_packets[i]->m_requested)
                return false;
        }
        return true;
    }

    // do not request
    void TestRequestLostMessagesLogic_3() {
        this->isf->ClearPackets(1, 100);
        this->isf->m_startMsgSeqNum = 3;
        this->isf->m_endMsgSeqNum = 3;
        this->isf->m_packets[3]->m_address = this->CreateHearthBeatMessage(3);
        this->isf->ProcessSecurityStatusMessages();
        if(!TestNotRequested(1, 10))
            throw;
    }

    void FillMessages(int startIndex, int endIndex) {
        this->m_helper->m_buffer->Reset();
        for(int i = startIndex; i <= endIndex; i++)
            this->isf->m_packets[i]->m_address = this->CreateHearthBeatMessage(i);
    }

    bool CheckRequestInfo(int index, FeedConnection *conn, int start, int end) {
        FeedConnectionRequestMessageInfo *info = this->hr->m_hsRequestList->Item(index);
        if(info->m_conn != conn)
            return false;
        if(info->m_requestCount != 0)
            return false;
        if(info->StartMsgSeqNo() != start)
            return false;
        if(info->EndMsgSeqNo() != end)
            return false;
        return true;
    }

    // request one message
    void TestRequestLostMessagesLogic_4() {
        this->isf->ClearPackets(1, 100);
        this->isf->m_startMsgSeqNum = 3;
        this->isf->m_endMsgSeqNum = 4;
        this->FillMessages(4, 4);
        this->isf->ProcessSecurityStatusMessages();
        if(!TestRequested(3,3))
            throw;
        if(this->hr->m_hsRequestList->Count() != 1)
            throw;
        if(!CheckRequestInfo(0, this->isf, 3, 3))
            throw;
    }

    // request some messages
    void TestRequestLostMessagesLogic_5() {
        this->isf->ClearPackets(1, 100);
        this->hr->m_hsRequestList->Clear();
        this->isf->m_startMsgSeqNum = 4;
        this->isf->m_endMsgSeqNum = 21;
        this->FillMessages(4, 10);
        this->FillMessages(20, 21);
        this->isf->ProcessSecurityStatusMessages();
        if(!TestRequested(11,19))
            throw;
        if(!TestNotRequested(4, 10))
            throw;
        if(!TestNotRequested(20, 21))
            throw;
        if(this->hr->m_hsRequestList->Count() != 1)
            throw;
        if(!CheckRequestInfo(0, this->isf, 11, 19))
            throw;
    }

    // two GAPs
    void TestRequestLostMessagesLogic_6() {
        this->isf->ClearPackets(1, 100);
        this->hr->m_hsRequestList->Clear();
        this->isf->m_startMsgSeqNum = 4;
        this->isf->m_endMsgSeqNum = 24;
        this->FillMessages(4, 10);
        this->FillMessages(20, 21);
        this->FillMessages(23, 24);
        this->isf->ProcessSecurityStatusMessages();
        if(!TestRequestedOnly(11,19))
            throw;
        if(!TestRequestedOnly(22,22))
            throw;
        if(!TestNotRequested(4, 10))
            throw;
        if(!TestNotRequested(20, 21))
            throw;
        if(this->hr->m_hsRequestList->Count() != 2)
            throw;
        if(!CheckRequestInfo(0, this->isf, 11, 19))
            throw;
        if(!CheckRequestInfo(1, this->isf, 22, 22))
            throw;
    }

    // two GAPs and called twice
    // avoid of dublicate requests
    void TestRequestLostMessagesLogic_7() {
        this->isf->ClearPackets(1, 100);
        this->hr->m_hsRequestList->Clear();
        this->isf->m_startMsgSeqNum = 4;
        this->isf->m_endMsgSeqNum = 24;
        this->FillMessages(4, 10);
        this->FillMessages(20, 21);
        this->FillMessages(23, 24);
        this->isf->ProcessSecurityStatusMessages();
        if(this->hr->m_hsRequestList->Count() != 2)
            throw;
        if(!CheckRequestInfo(0, this->isf, 11, 19))
            throw;
        if(!CheckRequestInfo(1, this->isf, 22, 22))
            throw;
        this->isf->ProcessSecurityStatusMessages();
        if(this->hr->m_hsRequestList->Count() != 2)
            throw;
    }

    void TestRequestLostMessagesLogic() {
        TestRequestLostMessagesLogic_1();
        TestRequestLostMessagesLogic_2();
        TestRequestLostMessagesLogic_3();
        TestRequestLostMessagesLogic_4();
        TestRequestLostMessagesLogic_5();

        // TODO try append additional messages - NO!
        // There is no situation when we need append additional messages,
        // because we can request lost message when we receive at least one and detect GAP
        TestRequestLostMessagesLogic_6();
        TestRequestLostMessagesLogic_7();
    }

    void Test() {
        printf("ISF TestDefaults\n");
        TestDefaults();
        printf("ISF TestReceiveExistingSymbol\n");
        TestReceiveExistingSymbol();
        printf("ISF TestCallHistoricalReplayWhenLostMessage\n");
        TestCallHistoricalReplayWhenLostMessage();
        printf("ISF TestRequestLostMessagesLogic\n");
        TestRequestLostMessagesLogic();
        printf("ISF TestStartSnapshotInstedOfHistoricalReplay\n");
        TestStartSnapshotInstedOfHistoricalReplay();
    }
};

#endif //HFT_ROBOT_SECURITYSTATUSTESTER_H
