//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTESTER_H
#define HFT_ROBOT_FEEDCONNECTIONTESTER_H

#include "OrderBookTester.h"
#include "OrderTester.h"

class FeedConnectionTester {
public:
    void Test() {
        OrderTester ot;
        ot.Test();
        OrderBookTester obt;
        obt.Test();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTESTER_H
