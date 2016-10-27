//
// Created by root on 27.10.16.
//

#ifndef HFT_ROBOT_TRADETESTER_H
#define HFT_ROBOT_TRADETESTER_H

#include "../FeedConnection.h"
#include <stdio.h>

class TradeTester {
    FeedConnection_FOND_TLR *fcf;
    FeedConnection_CURR_TLR *fcc;
public:

    TradeTester() {

    }
    ~TradeTester() {
        delete this->fcf;
        delete this->fcc;
    }
    void Test() {

    }
};

#endif //HFT_ROBOT_TRADETESTER_H
