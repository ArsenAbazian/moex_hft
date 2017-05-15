//
// Created by root on 20.02.17.
//

#ifndef HFT_ROBOT_HISTORICALREPLAYTESTER_H
#define HFT_ROBOT_HISTORICALREPLAYTESTER_H

#ifdef TEST

#include "../Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class HistoricalReplayTester {
    TestMessagesHelper          *m_helper;
    unsigned char               m_buffer[1024];
    FeedConnection_CURR_OLR     *olr;
    FeedConnection_CURR_H       *hr;
public:
    HistoricalReplayTester() {
        m_helper = new TestMessagesHelper();
        this->olr = new FeedConnection_CURR_OLR("OLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->hr = new FeedConnection_CURR_H("H", "Historical Replay", 'H',
                                                        FeedConnectionProtocol::TCP_IP,
                                                        "1.1.7.200", 20000);
        this->hr->SetTestMessagesHelper(this->m_helper);
    }
    ~HistoricalReplayTester() {
        delete this->olr;
        delete this->m_helper;
        delete this->hr;
    }

    // just call inline bool ProcessIncrementalAsts(FeedConnectionMessageInfo *info) {
    // info->m_requested = false;
    // check other methods using this flag
    void TestCorrectlyReadHearthbeatTemplateId_WhenShouldProcessMsgSeqNum() {
        int reservedForMsgSeqNum = 4;
        this->m_helper->m_fastManager->SetNewBuffer(this->m_buffer, 1024);
        this->m_helper->m_fastManager->EncodeAstsHeartbeatInfo(new AstsHeartbeatInfo());
        FeedConnectionMessageInfo *info = new FeedConnectionMessageInfo();
        info->m_requested = false;
        info->m_address = this->m_buffer;
        this->olr->ProcessIncrementalAsts(info);
    }

    // just call inline bool ProcessIncrementalAsts(FeedConnectionMessageInfo *info) {
    // info->m_requested = true;
    // check other methods using this flag
    void TestCorrectlyReadHearthbeatTemplateId_WhenShouldNotProcessMsgSeqNum() {
        int reservedForMsgSeqNum = 0;
        this->m_helper->m_fastManager->SetNewBuffer(this->m_buffer + reservedForMsgSeqNum, 1024);
        this->m_helper->m_fastManager->EncodeAstsHeartbeatInfo(new AstsHeartbeatInfo());
        FeedConnectionMessageInfo *info = new FeedConnectionMessageInfo();
        info->m_requested = true;
        info->m_address = this->m_buffer;
        this->olr->ProcessIncrementalAsts(info);
    }

    // because if no - then will be close tcp socket immediately
    void TestTimerDeactivatedAfterSendLogonMessageAndMarketDataRequest() {
        this->hr->HrRequestMessage(this->olr, 1, 1);
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->hr->m_waitTimer->StartFast(2);
        this->hr->HistoricalReplay_SendLogon();
        if(this->hr->m_waitTimer->Active(2))
            throw;

        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->hr->m_waitTimer->StartFast(2);
        this->hr->HistoricalReplay_SendMarketDataRequest();
        if(this->hr->m_waitTimer->Active(2))
            throw;
    }

    void Test() {
        TestCorrectlyReadHearthbeatTemplateId_WhenShouldProcessMsgSeqNum();
        TestCorrectlyReadHearthbeatTemplateId_WhenShouldNotProcessMsgSeqNum();
        TestTimerDeactivatedAfterSendLogonMessageAndMarketDataRequest();
    }
};

#endif

#endif //HFT_ROBOT_HISTORICALREPLAYTESTER_H
