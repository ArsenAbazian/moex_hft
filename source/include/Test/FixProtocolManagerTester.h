//
// Created by root on 29.07.16.
//

#ifndef HFT_ROBOT_FIXPROTOCOLMANAGERTESTER_H
#define HFT_ROBOT_FIXPROTOCOLMANAGERTESTER_H
#include "../Types.h"

#ifdef TEST
class FixProtocolManagerTester {
public:
    void Test() {
        TestMoreThanOneMessageReceived();
    }
    void TestMoreThanOneMessageReceived();

};
#endif

#endif //HFT_ROBOT_FIXPROTOCOLMANAGERTESTER_H
