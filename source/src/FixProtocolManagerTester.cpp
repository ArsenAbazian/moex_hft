//
// Created by root on 29.07.16.
//

#include "FixProtocolManagerTester.h"
#include "FixProtocolManager.h"

void FixProtocolManagerTester::TestMoreThanOneMessageReceived() {
    const char *recvString = "8=FIX.4.49=6735=049=MFIXTradeID56=MU903370000334=3252=20160729-11:41:38.06010=0928=FIX.4.49=7735=249=MFIXTradeID56=MU903370000334=3352=20160729-11:41:38.0617=1016=010=012";
    FixProtocolManager *manager = new FixProtocolManager();

    manager->SetMessageBuffer((char*)recvString);

    delete manager;
}
