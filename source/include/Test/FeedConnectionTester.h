//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTESTER_H
#define HFT_ROBOT_FEEDCONNECTIONTESTER_H
#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnections.h"
#include "SecurityDefinitionTester.h"
#include "OrderTesterFond.h"
#include "OrderTesterCurr.h"
#include "TradeTesterFond.h"
#include "TradeTesterCurr.h"
#include "StatisticsTesterFond.h"
#include "StatisticsTesterCurr.h"
#include "SymbolManagerTester.h"
#include "PointerListTester.h"
#include "SecurityStatusTester.h"
#include "HistoricalReplayTester.h"
#include "FortsOrderBookTester.h"
#include "HashTableTester.h"

class TestFeedMessage{
public:
    AutoAllocatePointerList<TestFeedMessage>    *Allocator;
    LinkedPointer<TestFeedMessage>              *Pointer;
    bool                                        Used;
    char                                        Type[10];
    int                                         TemplateId;
    int                                         Count;

    unsigned char                               Bytes[1700];
    char                                        Text[1700];
};

class FeedConnectionTester {

    TestMessagesHelper                  *m_helper;
    FeedConnection_CURR_OLR             *inc;
    FeedConnection_CURR_OLS             *snap;
    FeedConnection_FORTS_OBR            *incForts;
    FeedConnection_FORTS_SNAP           *snapForts;
    FeedConnection_FORTS_INSTR_SNAP     *idfForts;
    unsigned char                       m_buffer[1000];

    bool ReadNextQuote(FILE *fp) {
        while(!feof(fp)) {
            int chr = fgetc(fp);
            if(chr == '\'')
                return true;
        }
        return false;
    }
    const char* IsFeedName(const char *feed_abr) {
        static const char* feeds[7] {
                "OBR",
                "OBS",
                "TLR",
                "TLS",
                "OLS",
                "OLR",
                "IDF"
        };

        for(int i = 0; i < 7; i++) {
            if(feeds[i][0] == feed_abr[0] && feeds[i][1] == feed_abr[1] && feeds[i][2] == feed_abr[2] && feed_abr[3] == '\'')
                return feeds[i];
        }
        return 0;
    }
    int AsciToValue(char ascii) {
        char asci_table[16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

        for(int i = 0; i < 16; i++) {
            if(ascii == asci_table[i])
                return i;
        }
        return 0;
    }
public:
    FeedConnectionTester() {
        RobotSettings::Default->DefaultFeedConnectionSendBufferSize = 1 * 1024 * 1024;
        RobotSettings::Default->DefaultFeedConnectionSendItemsCount = 100;
        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize = 2 * 1024 * 1024;
        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount = 500;

        this->m_helper = new TestMessagesHelper();
        this->m_helper->SetCurrMode();
        this->inc = new FeedConnection_CURR_OLR("OLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snap = new FeedConnection_CURR_OLS("OLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);

        this->inc->OrderCurr()->InitSymbols(10, 10);
        this->inc->SetSymbolManager(new SymbolManager(10));
        this->snap->SetSymbolManager(this->inc->GetSymbolManager());
        this->inc->SetSnapshot(this->snap);

        this->incForts = new FeedConnection_FORTS_OBR("FUT-BOOK-1 Incremental", "Refresh Incremental", 'I',
                                                      FeedConnectionProtocol::UDP_IP,
                                                      "10.50.129.200", "239.192.113.3", 9113,
                                                      "10.50.129.200", "239.192.113.131", 9313);

        this->snapForts = new FeedConnection_FORTS_SNAP("FUT_BOOK-1 Snap", "Full Refresh", 'I',
                                                        FeedConnectionProtocol::UDP_IP,
                                                        "10.50.129.200", "239.192.113.3", 9113,
                                                        "10.50.129.200", "239.192.113.131", 9313);
        this->idfForts = new FeedConnection_FORTS_INSTR_SNAP("FUT-BOOK-INFO", "Full Refresh", 'I',
                                                             FeedConnectionProtocol::UDP_IP,
                                                             "10.50.129.200", "239.192.113.3", 9113,
                                                             "10.50.129.200", "239.192.113.131", 9313);

        this->incForts->SetSymbolManager(new SymbolManager(10, true));
        this->snapForts->SetSymbolManager(this->incForts->GetSymbolManager());
        this->incForts->SetSnapshot(this->snapForts);
        this->idfForts->AddConnectionToRecvSymbol(this->incForts);
        this->incForts->SetSecurityDefinition(this->idfForts);
        this->incForts->OrderBookForts()->InitSymbols(10, 10);
        this->incForts->SetMaxLostPacketCountForStartSnapshot(1);
    }

    void TestDefaults() {
        if(this->inc->m_windowMsgSeqNum != 0)
            throw;
    }

    void TestPacketsCleared(int start, int end) {
        for(int i = start; i <= end; i++) {
            if(!this->inc->m_packets[i]->IsCleared())
                throw;
        }
    }

    void TestWindowStartMsgSeqNo_CorrectIncremental() {
        TestTemplateInfo *info = new TestTemplateInfo();
        TestTemplateItemInfo *item = new TestTemplateItemInfo();

        this->inc->GetSymbolManager()->AddSymbol("symbol1");
        this->inc->OrderCurr()->AddSymbol("symbol1");

        info->m_templateId = FeedTemplateId::fmcIncrementalRefresh_OLR_CURR;
        info->m_itemsCount = 1;
        info->m_items[0] = item;

        item->m_symbol = "symbol1";
        item->m_tradingSession = "session1";
        item->m_entryId = "111111";
        item->m_action = MDUpdateAction::mduaAdd;
        item->m_entryType = MDEntryType::mdetBuyQuote;

        for(int i = 0; i < 2000; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);
            this->inc->ListenIncremental_Core();
        }
        if(this->inc->OrderCurr()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 2000)
            throw;
        if(this->inc->m_startMsgSeqNum != 2000 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 2000)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
        TestPacketsCleared(0, 2000);
    }

    void TestWindowStartMsgSeqNo_MessageLost() {
        this->inc->ClearMessages();
        this->inc->OrderCurr()->Clear();
        this->inc->GetSymbolManager()->Clear();

        this->inc->GetSymbolManager()->AddSymbol("symbol1");
        this->inc->OrderCurr()->AddSymbol("symbol1");

        TestTemplateInfo *info = new TestTemplateInfo();
        TestTemplateItemInfo *item = new TestTemplateItemInfo();

        info->m_templateId = FeedTemplateId::fmcIncrementalRefresh_OLR_CURR;
        info->m_itemsCount = 1;
        info->m_items[0] = item;

        item->m_symbol = "symbol1";
        item->m_tradingSession = "session1";
        item->m_entryId = "111111";
        item->m_action = MDUpdateAction::mduaAdd;
        item->m_entryType = MDEntryType::mdetBuyQuote;

        for(int i = 0; i < 10; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);
            this->inc->ListenIncremental_Core();
        }
        TestPacketsCleared(0, 10);
        for(int i = 11; i < 20; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);
            this->inc->ListenIncremental_Core();
        }

        if(this->inc->OrderCurr()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 10)
            throw;
        if(this->inc->m_startMsgSeqNum != 10 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 20)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
        for(int i = 12; i < 20; i++)
            if(inc->m_packets[i - 11]->IsCleared())
                throw;

        item->m_rptSeq = 11; // lost message
        info->m_msgSeqNo = 11;

        this->m_helper->SendMessage(this->inc, info);
        this->inc->ListenIncremental_Core();

        TestPacketsCleared(0, 10);
        if(this->inc->m_startMsgSeqNum != 20 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 20)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
    }

    void TestWindowStartMsgSeqNo_AfterApplySnapshot() {
        this->inc->ClearMessages();
        this->inc->OrderCurr()->Clear();
        this->inc->GetSymbolManager()->Clear();

        this->inc->GetSymbolManager()->AddSymbol("symbol1");
        this->inc->OrderCurr()->AddSymbol("symbol1");

        TestTemplateInfo *info = new TestTemplateInfo();
        TestTemplateItemInfo *item = new TestTemplateItemInfo();

        info->m_templateId = FeedTemplateId::fmcIncrementalRefresh_OLR_CURR;
        info->m_itemsCount = 1;
        info->m_items[0] = item;

        item->m_symbol = "symbol1";
        item->m_tradingSession = "session1";
        item->m_entryId = "111111";
        item->m_action = MDUpdateAction::mduaAdd;
        item->m_entryType = MDEntryType::mdetBuyQuote;

        for(int i = 0; i < 10; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);

            this->inc->ListenIncremental_Core();
        }
        TestPacketsCleared(0, 10);
        for(int i = 11; i < 20; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);

            this->inc->ListenIncremental_Core();
        }

        if(this->inc->OrderCurr()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 10)
            throw;
        if(this->inc->m_startMsgSeqNum != 10 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 20)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
        for(int i = 12; i < 20; i++)
            if(inc->m_packets[i - 11]->IsCleared())
                throw;

        // lost msg 11
        TestTemplateInfo *info2 = new TestTemplateInfo();
        TestTemplateItemInfo *item2 = new TestTemplateItemInfo();

        info2->m_templateId = FeedTemplateId::fmcFullRefresh_OLS_CURR;
        info2->m_itemsCount = 1;
        info2->m_items[0] = item2;
        info2->m_symbol = "symbol1";
        info2->m_session = "session1";
        info2->m_lastMsgSeqNoProcessed = 11;
        info2->m_routeFirst = true;
        info2->m_lastFragment = true;
        info2->m_msgSeqNo = 1;
        info2->m_rptSec = 11;

        item2->m_entryId = "111111";
        item2->m_action = MDUpdateAction::mduaAdd;
        item2->m_entryType = MDEntryType::mdetBuyQuote;

        this->inc->StartListenSnapshot();
        this->m_helper->SendMessage(this->snap, info2);

        this->snap->ListenSnapshot_Core();

        this->inc->ListenIncremental_Core();

        TestPacketsCleared(0, 10);
        if(this->inc->m_startMsgSeqNum != 20 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 20)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
    }

    void TestReceivedPacketWithBigMsgSeqNo_FromStart() {
        this->inc->ClearMessages();
        this->inc->OrderCurr()->Clear();
        this->inc->GetSymbolManager()->Clear();

        TestTemplateInfo *info = new TestTemplateInfo();
        info->m_templateId = FeedTemplateId::fcmHeartBeat;
        info->m_msgSeqNo = 1000000;

        this->m_helper->SendHearthBeatMessage(this->inc, info);
        if(this->inc->m_startMsgSeqNum != 1000000)
            throw;
        if(this->inc->m_windowMsgSeqNum != 1000000)
            throw;
        if(this->inc->m_endMsgSeqNum != 1000000)
            throw;
        if(this->snap->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        this->inc->StopListenSnapshot();
        this->inc->OrderCurr()->Clear();
    }

    void TestReceivedPacketWithBigMsgSeqNo_InProcess() {
        this->inc->ClearMessages();
        this->inc->OrderCurr()->Clear();
        this->inc->GetSymbolManager()->Clear();

        this->inc->m_windowMsgSeqNum = 500000;
        this->inc->m_startMsgSeqNum = 500005;
        this->inc->m_endMsgSeqNum = 500010;
        this->inc->m_packets[5]->m_address = new unsigned char[2];
        this->inc->m_packets[6]->m_address = new unsigned char[2];
        this->inc->m_packets[7]->m_address = new unsigned char[2];
        this->inc->m_packets[8]->m_address = new unsigned char[2];
        this->inc->m_packets[9]->m_address = new unsigned char[2];
        this->inc->m_packets[10]->m_address = new unsigned char[2];

        TestTemplateInfo *info = new TestTemplateInfo();
        info->m_templateId = FeedTemplateId::fcmHeartBeat;
        info->m_msgSeqNo = 1000000;

        this->m_helper->SendHearthBeatMessage(this->inc, info);
        if(this->inc->m_startMsgSeqNum != 1000000)
            throw;
        if(this->inc->m_windowMsgSeqNum != 1000000)
            throw;
        if(this->inc->m_endMsgSeqNum != 1000000)
            throw;
        for(int i = 5; i <= 10; i++) {
            if(!this->inc->m_packets[i]->IsCleared())
                throw;
        }
        this->inc->StopListenSnapshot();
        this->inc->OrderCurr()->Clear();
    }

    void TestReceivedSnapshotMsgSeqNum_1_After_200() {
        // assumes that previous startMsgSeqNum = 200 and next msg seq num = 1
        //throw;
    }

    void TestThatAfterApplySnapshotPart_RptSeqNotChanged() {
        //throw
    }

    void TestSnapshotItemRptSeqChangedAfterEndSnapshot() {
        //throw
    }

    void TestBufferShouldNotBeResetAfterApplyingSnapshot_OnePacket() {
        //throw;
    }
    void TestBufferShouldNotBeResetAfterApplyingSnapshot_MultiplePacket() {
        //throw;
    }
    void TestBufferShouldBeResetAfterProcessingAllMessages() {
        //throw;
    }

    void TestAsts() {
        TestDefaults();
        TestWindowStartMsgSeqNo_CorrectIncremental();
        TestWindowStartMsgSeqNo_MessageLost();
        TestWindowStartMsgSeqNo_AfterApplySnapshot();
        TestReceivedPacketWithBigMsgSeqNo_FromStart();
        TestReceivedPacketWithBigMsgSeqNo_InProcess();
        TestReceivedSnapshotMsgSeqNum_1_After_200();
        TestThatAfterApplySnapshotPart_RptSeqNotChanged();
        TestSnapshotItemRptSeqChangedAfterEndSnapshot();
        TestBufferShouldNotBeResetAfterApplyingSnapshot_OnePacket();
        TestBufferShouldNotBeResetAfterApplyingSnapshot_MultiplePacket();
        TestBufferShouldBeResetAfterProcessingAllMessages();
    }

    void TestForts_Defaults() {
        if(this->incForts->m_fortsIncrementalRouteFirst != 1)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
    }

    FortsDefaultIncrementalRefreshMessageInfo* CreateFortsIncremental(int msgSeqNum, const char *symbol, UINT64 securityId, int rptSeq) {
        FortsDefaultIncrementalRefreshMessageInfo *info = new FortsDefaultIncrementalRefreshMessageInfo();

        info->MsgSeqNum = msgSeqNum;
        info->NullMap |= FortsDefaultIncrementalRefreshMessageInfoNullIndices::LastFragmentNullIndex;

        FortsDefaultSnapshotMessageMDEntriesItemInfo *item = new FortsDefaultSnapshotMessageMDEntriesItemInfo();
        item->MDUpdateAction = MDUpdateAction::mduaAdd;
        item->MDEntryType[0] = MDEntryType::mdetBuyQuote;
        item->MDEntryTypeLength = 1;
        item->MDEntryPx.Set(1, 1);
        item->MDEntrySize = 100;
        item->RptSeq = rptSeq;

        if(symbol == 0) {
            item->NullMap |= FortsDefaultIncrementalRefreshMessageMDEntriesItemInfoNullIndices::SymbolNullIndex;
        }
        else {
            strcpy(item->Symbol, symbol);
            item->SymbolLength = strlen(symbol);
        }
        if(securityId == 0) {
            item->NullMap |= FortsDefaultIncrementalRefreshMessageMDEntriesItemInfoNullIndices::SecurityIDNullIndex;
        }
        else {
            item->SecurityID = securityId;
        }

        info->MDEntriesCount = 1;
        info->MDEntries[0] = item;

        return info;
    }

    FortsDefaultIncrementalRefreshMessageInfo* CreateFortsIncremental(int msgSeqNum, const char *symbol, UINT64 securityId, int rptSeq, bool nullLastFragment) {
        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(msgSeqNum, symbol, securityId, rptSeq);
        info->LastFragment = 0;
        info->NullMap |= FortsDefaultIncrementalRefreshMessageInfoNullIndices::LastFragmentNullIndex;

        return info;
    }

    FortsDefaultIncrementalRefreshMessageInfo* CreateFortsIncremental(int msgSeqNum, const char *symbol, UINT64 securityId, int rptSeq, int isLastFragment) {
        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(msgSeqNum, symbol, securityId, rptSeq);
        info->LastFragment = isLastFragment;
        info->NullMap = 0;

        return info;
    }

    void SendProcessFortsSnapshot(FortsHeartbeatInfo *info) {
        this->snapForts->FastManager()->SetNewBuffer(this->snapForts->m_recvABuffer->CurrentPos(), 1000);
        this->snapForts->FastManager()->WriteMsgSeqNumber(info->MsgSeqNum);
        this->snapForts->FastManager()->EncodeFortsHeartbeatInfo(info);
        this->snapForts->ProcessServerCore(this->snapForts->m_fastProtocolManager->MessageLength());

        this->snapForts->ListenSnapshot_Core();
    }
    
    void SendProcessFortsIncremental(FortsDefaultIncrementalRefreshMessageInfo *info) {
        this->incForts->FastManager()->SetNewBuffer(this->incForts->m_recvABuffer->CurrentPos(), 1000);
        this->incForts->FastManager()->WriteMsgSeqNumber(info->MsgSeqNum);
        this->incForts->FastManager()->EncodeFortsDefaultIncrementalRefreshMessageInfo(info);
        this->incForts->ProcessServerCore(this->incForts->m_fastProtocolManager->MessageLength());

        this->incForts->ListenIncremental_Forts_Core();
    }

    void SendProcessFortsIncremental(FortsHeartbeatInfo *info) {
        this->incForts->FastManager()->SetNewBuffer(this->incForts->m_recvABuffer->CurrentPos(), 1000);
        this->incForts->FastManager()->WriteMsgSeqNumber(info->MsgSeqNum);
        this->incForts->FastManager()->EncodeFortsHeartbeatInfo(info);
        this->incForts->ProcessServerCore(this->incForts->m_fastProtocolManager->MessageLength());

        this->incForts->ListenIncremental_Forts_Core();
    }

    void AddSymbol(const char *symbol, UINT64 securityId) {
        FortsSecurityDefinitionInfo *info = new FortsSecurityDefinitionInfo();
        strcpy(info->Symbol, symbol);
        info->SymbolLength = strlen(symbol);
        info->SecurityID = securityId;

        LinkedPointer<FortsSecurityDefinitionInfo> *ptr = new LinkedPointer<FortsSecurityDefinitionInfo>();
        ptr->Data(info);

        SymbolInfo *s = this->incForts->GetSymbolManager()->AddSymbol(info->SecurityID);
        this->incForts->SecurityDefinition()->SymbolsForts()[s->m_index] = ptr;
        this->incForts->AddSymbol(ptr, s->m_index);
    }

    void ClearSymbolsForts() {
        this->idfForts->ClearSecurityDefinitions();
        this->incForts->OrderBookForts()->Clear();
        this->incForts->GetSymbolManager()->Clear();
    }

    void TestForts_RecvIncrementalRouteFirst_FirstMessage() {
        this->ClearSymbolsForts();
        this->AddSymbol("symbol1", 111111);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(1, "symbol1", 111111, 1);
        this->SendProcessFortsIncremental(info);

        // message with index 1 should be processed
        if(this->incForts->OrderBookForts()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 1)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 2)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
    }

    void ClearFortsIncremental() {
        this->incForts->ClearLocalPackets(0, 30);
        this->incForts->OrderBookForts()->Clear();
        this->incForts->SecurityDefinition()->GetSymbolManager()->Clear();
        this->idfForts->ClearSecurityDefinitions();
        this->incForts->m_fortsIncrementalRouteFirst = 1;
        this->incForts->m_fortsRouteFirtsSecurityId = 0;
        this->incForts->m_startMsgSeqNum = 1;
        this->incForts->m_endMsgSeqNum = 0;
        this->incForts->m_windowMsgSeqNum = 0;
    }

    void TestForts_RecvIncrementalRouteFirst_FirstMessage_NullLastFragment() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(1, "symbol2", 222222, 1, true);
        this->SendProcessFortsIncremental(info);

        // message with index 1 should be processed
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 1)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 2)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
    }

    void TestForts_RecvIncrementalRouteFirst_NotFirstMessage_RouteFirts() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(10, "symbol2", 222222, 1);
        this->SendProcessFortsIncremental(info);

        // message with index 1 should be processed
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 0)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 1)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
    }

    void TestForts_RecvIncrementalRouteFirst_InProcess_RouteFirst() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(1, "symbol2", 222222, 1);
        this->SendProcessFortsIncremental(info);

        FortsDefaultIncrementalRefreshMessageInfo *info2 = CreateFortsIncremental(2, "symbol2", 222222, 2);
        info2->MDEntries[0]->MDEntryPx.Set(2, 1);
        this->SendProcessFortsIncremental(info2);

        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 2)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 3)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        if(this->incForts->m_startMsgSeqNum != 3)
            throw;
        if(this->incForts->m_endMsgSeqNum != 2)
            throw;
        if(this->incForts->m_windowMsgSeqNum != 3)
            throw;
    }

    void TestForts_RecvIncrementalRouteFirst_InProcess_RouteFirst_NullLastFragment() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(1, "symbol2", 222222, 1, true);
        this->SendProcessFortsIncremental(info);

        FortsDefaultIncrementalRefreshMessageInfo *info2 = CreateFortsIncremental(2, "symbol2", 222222, 2, true);
        info2->MDEntries[0]->MDEntryPx.Set(2, 1);
        this->SendProcessFortsIncremental(info2);

        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 2)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 3)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        if(this->incForts->m_startMsgSeqNum != 3)
            throw;
        if(this->incForts->m_endMsgSeqNum != 2)
            throw;
        if(this->incForts->m_windowMsgSeqNum != 3)
            throw;
    }

    void TestForts_RecvIncrementalRouteFirst_FirstMessage_Fragmented() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(1, "symbol2", 222222, 1, 0);
        this->SendProcessFortsIncremental(info);

        // message with index 1 should be processed
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 1)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 1)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 222222)
            throw;

        FortsDefaultIncrementalRefreshMessageInfo *info2 = CreateFortsIncremental(2, 0, 0, 2, 0);
        info2->MDEntries[0]->MDEntryPx.Set(2, 2);
        this->SendProcessFortsIncremental(info2);

        if(this->incForts->m_fortsIncrementalRouteFirst != 1)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 222222)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 2)
            throw;

        FortsDefaultIncrementalRefreshMessageInfo *info3 = CreateFortsIncremental(3, 0, 0, 3, 1);
        info3->MDEntries[0]->MDEntryPx.Set(3, 3);
        this->SendProcessFortsIncremental(info3);

        if(this->incForts->m_fortsIncrementalRouteFirst != 4)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 3)
            throw;
    }

    FortsHeartbeatInfo* CreateFortsHearthBeat(int msgSeqNum) {
        FortsHeartbeatInfo *info = new FortsHeartbeatInfo();
        info->MsgSeqNum = msgSeqNum;
        return info;
    }

    void TestForts_RecvIncrementalRouteFirst_HearthBeat() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        FortsDefaultIncrementalRefreshMessageInfo *info = CreateFortsIncremental(1, "symbol2", 222222, 1);
        this->SendProcessFortsIncremental(info);

        // message with index 1 should be processed
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 1)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 2)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        FortsHeartbeatInfo *hbeat = CreateFortsHearthBeat(2);
        this->SendProcessFortsIncremental(hbeat);

        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->BuyQuotes()->Count() != 1)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 3)
            throw;
        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        if(this->incForts->m_startMsgSeqNum != 3)
            throw;
        if(this->incForts->m_endMsgSeqNum != 2)
            throw;
        if(this->incForts->m_windowMsgSeqNum != 3)
            throw;
    }

    void TestForts_LostMessage() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);

        this->SendProcessFortsIncremental(CreateFortsIncremental(1, "symbol2", 222222, 1));
        this->SendProcessFortsIncremental(CreateFortsIncremental(2, "symbol2", 222222, 2));
        this->SendProcessFortsIncremental(CreateFortsIncremental(3, "symbol2", 222222, 3, 0));
        // ... missed message and then received last fragment
        this->SendProcessFortsIncremental(CreateFortsIncremental(5, "symbol2", 222222, 5));
        this->SendProcessFortsIncremental(CreateFortsIncremental(6, "symbol2", 222222, 6));

        if(this->incForts->m_fortsRouteFirtsSecurityId != 222222)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 3)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->RptSeq() != 3)
            throw;
        if(this->incForts->m_endMsgSeqNum != 6)
            throw;
        if(this->incForts->m_startMsgSeqNum != 4)
            throw;
        if(this->incForts->m_windowMsgSeqNum != 4)
            throw;
    }

    // well, after starting snapshot we can process queue messages, but we should find RouteFirst
    void TestForts_LostMessageAndThenStartSnapshot_TryToProcessQueMessages() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        this->SendProcessFortsIncremental(CreateFortsIncremental(1, "symbol2", 222222, 1));
        this->SendProcessFortsIncremental(CreateFortsIncremental(2, "symbol2", 222222, 2));
        this->SendProcessFortsIncremental(CreateFortsIncremental(3, "symbol2", 222222, 3, 0));
        // ... missed message and then received last fragment
        this->SendProcessFortsIncremental(CreateFortsIncremental(5, "symbol3", 333333, 1));
        this->SendProcessFortsIncremental(CreateFortsIncremental(6, "symbol3", 333333, 2));
        this->incForts->StartListenSnapshot();

        this->incForts->ListenIncremental_Forts_Core();

        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 7)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->RptSeq() != 3)
            throw;
        // we dont know if msg seq 5 is route first so we also skip this...
        if(this->incForts->OrderBookForts()->Symbol(2)->Session(0)->RptSeq() != 2)
            throw;
        if(this->incForts->m_endMsgSeqNum != 6)
            throw;
        if(this->incForts->m_startMsgSeqNum != 4)
            throw;
        if(this->incForts->m_windowMsgSeqNum != 4)
            throw;
    }

    // well, after starting snapshot we can process queue messages, but we should find RouteFirst
    void TestForts_LostMessageAndThenStartSnapshot_TryToProcessQueMessages2() {
        this->ClearSymbolsForts();
        this->ClearFortsIncremental();
        this->AddSymbol("symbol1", 111111);
        this->AddSymbol("symbol2", 222222);
        this->AddSymbol("symbol3", 333333);

        this->SendProcessFortsIncremental(CreateFortsIncremental(1, "symbol2", 222222, 1));
        this->SendProcessFortsIncremental(CreateFortsIncremental(2, "symbol2", 222222, 2));
        this->SendProcessFortsIncremental(CreateFortsIncremental(3, "symbol2", 222222, 3, 0));
        // ... missed message and then received last fragment
        this->SendProcessFortsIncremental(CreateFortsIncremental(5, "symbol2", 222222, 5, 0));
        this->SendProcessFortsIncremental(CreateFortsIncremental(6, "symbol2", 222222, 6, 1));
        this->SendProcessFortsIncremental(CreateFortsIncremental(7, "symbol3", 333333, 1));
        this->incForts->StartListenSnapshot();

        this->incForts->ListenIncremental_Forts_Core();

        if(this->incForts->m_fortsRouteFirtsSecurityId != 0)
            throw;
        if(this->incForts->m_fortsIncrementalRouteFirst != 8)
            throw;
        if(this->incForts->OrderBookForts()->Symbol(1)->Session(0)->RptSeq() != 3)
            throw;
        // we dont know if msg seq 5 is route first so we also skip this...
        // but msg seq 6 we can process
        if(this->incForts->OrderBookForts()->Symbol(2)->Session(0)->RptSeq() != 1)
            throw;
        if(this->incForts->m_endMsgSeqNum != 7)
            throw;
        if(this->incForts->m_startMsgSeqNum != 4)
            throw;
        if(this->incForts->m_windowMsgSeqNum != 4)
            throw;
    }

    void TestForts_NextSnapshotIsHearthBeat() {
        this->SendProcessFortsSnapshot(CreateFortsHearthBeat(1));
        if(this->snapForts->m_packets[1]->m_address != 0)
            throw;
        if(this->snapForts->m_startMsgSeqNum != 2)
            throw;
        if(this->snapForts->m_endMsgSeqNum != 1)
            throw;
        if(this->snapForts->m_nextFortsSnapshotRouteFirst != 2)
            throw;
        if(this->snapForts->m_snapshotRouteFirst != -1)
            throw;
        this->SendProcessFortsSnapshot(CreateFortsHearthBeat(2));
        if(this->snapForts->m_packets[2]->m_address != 0)
            throw;
        if(this->snapForts->m_startMsgSeqNum != 3)
            throw;
        if(this->snapForts->m_endMsgSeqNum != 2)
            throw;
        if(this->snapForts->m_nextFortsSnapshotRouteFirst != 3)
            throw;
        if(this->snapForts->m_snapshotRouteFirst != -1)
            throw;
    }

    void TestForts() {
        TestForts_Defaults();
        TestForts_RecvIncrementalRouteFirst_FirstMessage();
        TestForts_RecvIncrementalRouteFirst_FirstMessage_NullLastFragment();
        TestForts_RecvIncrementalRouteFirst_NotFirstMessage_RouteFirts();
        TestForts_RecvIncrementalRouteFirst_InProcess_RouteFirst();
        TestForts_RecvIncrementalRouteFirst_InProcess_RouteFirst_NullLastFragment();
        TestForts_RecvIncrementalRouteFirst_FirstMessage_Fragmented();
        TestForts_RecvIncrementalRouteFirst_HearthBeat();
        TestForts_LostMessage();
        TestForts_LostMessageAndThenStartSnapshot_TryToProcessQueMessages();
        TestForts_LostMessageAndThenStartSnapshot_TryToProcessQueMessages2();
        TestForts_NextSnapshotIsHearthBeat();
    }

    void TestFeedConnectionBase() {
        TestForts();
        TestAsts();
    }

    void TestStopwatchPerformance() {
        Stopwatch *w = new Stopwatch();
        w->Start();
        for(int i = 0; i < 10000000; i++) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        }
        int ms = w->ElapsedMillisecondsSlow();
        printf("stopwatch fast = %d\n", ms);
        w->Stop();
        w->Start();
        for(int i = 0; i < 10000000; i++) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobalSlow();
        }
        ms = w->ElapsedMillisecondsSlow();
        printf("stopwatch slow = %d\n", ms);

        Stopwatch::Default->Start();
        w->Stop();
        w->Start();
        for(int i = 0; i < 10000000; i++) {
            Stopwatch::Default->ElapsedMillisecondsSlow();
        }
        ms = w->ElapsedMillisecondsSlow();
        printf("stopwatch elapsed slow = %d\n", ms);

        Stopwatch::Default->Start();
        w->Stop();
        w->Start();
        for(int i = 0; i < 10000000; i++) {
            Stopwatch::Default->ElapsedMicrosecondsFast();
        }
        ms = w->ElapsedMillisecondsSlow();
        printf("stopwatch elapsed fast = %d\n", ms);
    }

    void Test() {
        RobotSettings::Default->MarketDataMaxSymbolsCount = 10;
        RobotSettings::Default->MarketDataMaxSessionsCount = 32;
        RobotSettings::Default->MarketDataMaxEntriesCount = 32 * 10;
        RobotSettings::Default->MDEntryQueueItemsCount = 100;

        TestStopwatchPerformance();

        PointerListTester *pt = new PointerListTester();
        pt->Test();
        delete pt;

        HashTableTester *htt = new HashTableTester();
        htt->Test();
        delete htt;

        SymbolManagerTester *ht = new SymbolManagerTester();
        ht->Test();
        delete ht;

        TradeTesterCurr *ttCurr = new TradeTesterCurr();
        ttCurr->Test();
        delete ttCurr;
        TradeTesterFond *ttFond = new TradeTesterFond();
        ttFond->Test();
        delete ttFond;

        OrderTesterCurr *otCurr = new OrderTesterCurr();
        otCurr->Test();
        delete otCurr;
        OrderTesterFond *otFond = new OrderTesterFond();
        otFond->Test();
        delete otFond;

        OrderBookTesterForts *fob = new OrderBookTesterForts();
        fob->Test();
        delete fob;

        SecurityDefinitionTester *ids = new SecurityDefinitionTester();
        ids->Test();
        delete ids;

        SecurityStatusTester *ist = new SecurityStatusTester();
        ist->Test();
        delete ist;

        HistoricalReplayTester *hrt = new HistoricalReplayTester();
        hrt->Test();
        delete hrt;

        TestFeedConnectionBase();

        StatisticsTesterFond *stFond = new StatisticsTesterFond();
        stFond->Test();
        delete stFond;
    }
};

#endif
#endif //HFT_ROBOT_FEEDCONNECTIONTESTER_H
