//
// Created by root on 20.02.17.
//

#ifndef HFT_ROBOT_HISTORICALREPLAYTESTER_H
#define HFT_ROBOT_HISTORICALREPLAYTESTER_H

#ifdef TEST

#include "Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class HistoricalReplayTester {
public:
    HistoricalReplayTester() {}
    ~HistoricalReplayTester() {}

    void TestCorrectlyReadHearthbeatTemplateId_WhenShouldProcessMsgSeqNum() {
        // just call inline bool ProcessIncremental(FeedConnectionMessageInfo *info) {
        // info->m_requested = false;
        // check other methods using this flag
        throw;
    }

    void TestCorrectlyReadHearthbeatTemplateId_WhenShouldNotProcessMsgSeqNum() {
        // just call inline bool ProcessIncremental(FeedConnectionMessageInfo *info) {
        // info->m_requested = true;
        // check other methods using this flag
        throw;
    }

    void Test() {
        TestCorrectlyReadHearthbeatTemplateId_WhenShouldProcessMsgSeqNum();
        TestCorrectlyReadHearthbeatTemplateId_WhenShouldNotProcessMsgSeqNum();
    }
};

#endif

#endif //HFT_ROBOT_HISTORICALREPLAYTESTER_H
