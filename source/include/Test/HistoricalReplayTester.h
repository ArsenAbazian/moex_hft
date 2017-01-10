//
// Created by root on 04.01.17.
//

#ifndef HFT_ROBOT_HISTORICALREPLAYTESTER_H
#define HFT_ROBOT_HISTORICALREPLAYTESTER_H

#include "../FeedConnections.h"
#include "TestMessagesHelper.h"

class HistoricalReplayTester{
    FeedConnection          *m_conn;
    FeedConnection          *m_hr;
    TestMessagesHelper      *m_helper;
public:
    HistoricalReplayTester() {
        this->m_conn = new FeedConnection_FOND_OLR("OLR", "Refresh Incremental", 'I',
                                                   FeedConnectionProtocol::UDP_IP,
                                                   "10.50.129.200", "239.192.113.3", 9113,
                                                   "10.50.129.200", "239.192.113.131", 9313);
        this->m_hr = new FeedConnection_FOND_H("H", "Historical Replay", 'H',
                                                    FeedConnectionProtocol::TCP_IP,
                                                    "1.1.7.200", 20000);
        this->m_hr->SetSenderCompId("MyComp");

        this->m_conn->SetHistoricalReplay(this->m_hr);
        this->m_helper = new TestMessagesHelper();

    }
    ~HistoricalReplayTester() {
        delete this->m_conn;
        delete this->m_hr;
    }

    // conection should be always HistoricalReplay state
    // because it only in connect state when retrieving message
    void TestDefaults() {
        //after construct
        if(this->m_hr->State() != FeedConnectionState::fcsHistoricalReplay)
            throw;
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsSuspend)
            throw;
        this->m_hr->Stop();
        if(this->m_hr->State() != FeedConnectionState::fcsHistoricalReplay)
            throw;
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsSuspend)
            throw;
        this->m_hr->Start();
        if(this->m_hr->State() != FeedConnectionState::fcsHistoricalReplay)
            throw;
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsSuspend)
            throw;
    }

    void TestAddMessageWithOneRequest_1() {
        this->m_hr->HrRequestMessage(this->m_conn, 1);

        if(this->m_hr->State() != FeedConnectionState::fcsHistoricalReplay)
            throw;
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsSuspend)
            throw;

        this->m_hr->DoWorkAtom();
        if(this->m_hr->State() != FeedConnectionState::fcsHistoricalReplay)
            throw;
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsWaitLogon)
            throw;
        if(this->m_hr->m_fixProtocolManager->SendMsgSeqNo() != 2)
            throw;

        this->m_helper->ClearPoll();

        this->m_helper->EncodeMessage(this->m_hr, "logon sender MOEX pass 1 msgSeqNo 1");
        this->m_helper->SetRecvFastFor(this->m_hr);

        this->m_hr->DoWorkAtom();
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsRecvMessage)
            throw;

        if(this->m_hr->m_fixProtocolManager->SendMsgSeqNo() != 3)
            throw;
        if(this->m_hr->m_fixProtocolManager->RecvMsgSeqNo() != 2)
            throw;

        this->m_helper->ClearPoll();

        this->m_helper->EncodeMessage(this->m_hr, "olr entry s1 e1 msgSeqNo 2");
        this->m_helper->SetRecvFastFor(this->m_hr);

        this->m_hr->DoWorkAtom();
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsWaitLogout)
            throw;
        if(this->m_hr->m_fixProtocolManager->SendMsgSeqNo() != 3)
            throw;
        if(this->m_hr->m_fixProtocolManager->RecvMsgSeqNo() != 3)
            throw;

        this->m_helper->ClearPoll();

        this->m_helper->EncodeMessage(this->m_hr, "logout msgSeqNo 3");
        this->m_helper->SetRecvFastFor(this->m_hr);

        this->m_hr->DoWorkAtom();
        if(this->m_hr->m_hsState != FeedConnectionHistoricalReplayState::hsSuspend)
            throw;
        if(this->m_hr->m_fixProtocolManager->SendMsgSeqNo() != 4)
            throw;
        if(this->m_hr->m_fixProtocolManager->RecvMsgSeqNo() != 4)
            throw;
    }

    void Test() {
        printf("H TestDefaults\n");
        TestDefaults();
        printf("H TestAddMessageWithOneRequest_1\n");
        TestAddMessageWithOneRequest_1();
    }
};

#endif //HFT_ROBOT_HISTORICALREPLAYTESTER_H
