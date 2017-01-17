//
// Created by root on 29.07.16.
//

#include "Test/FixProtocolManagerTester.h"
#include "Fix/FixProtocolManager.h"

void FixProtocolManagerTester::TestMoreThanOneMessageReceived() {
    const char *recvString = "8=FIX.4.49=6735=049=MFIXTradeID56=MU903370000334=3252=20160729-11:41:38.06010=0928=FIX.4.49=7735=249=MFIXTradeID56=MU903370000334=3352=20160729-11:41:38.0617=1016=010=012";
    const char *recvMsg1 = "8=FIX.4.49=6735=049=MFIXTradeID56=MU903370000334=3252=20160729-11:41:38.06010=092";
    const char *recvMsg2 = "8=FIX.4.49=7735=249=MFIXTradeID56=MU903370000334=3352=20160729-11:41:38.0617=1016=010=012";
    FixProtocolManager *manager = new FixProtocolManager(
            new SocketBufferProvider(DefaultSocketBufferManager::Default, 10000, 1000, 10000, 1000));

    manager->PrepareRecvBuffer();
    memcpy(manager->RecvBuffer(), recvString, strlen(recvString));
    manager->SetRecvBufferSize(strlen(recvString));

    if(manager->RecvMessageCount() != 2)
        throw;
    manager->SelectRecvMessage(0);
    if(!manager->Message(0)->ProcessCheckHeader())
        throw;
    if(!manager->Message(1)->ProcessCheckHeader())
        throw;
    int msgSize1 = manager->Message(0)->Size();
    int msgExpSize1 = strlen(recvMsg1);
    if( msgSize1 != msgExpSize1)
        throw;
    if(manager->Message(1)->Size() != strlen(recvMsg2))
        throw;
    if(manager->Message(0)->TagsCount() != 8)
        throw;
    if(manager->Message(1)->TagsCount() != 10)
        throw;
    if(manager->Message(0)->Header()->msgType != MsgTypeHearthBeat)
        throw;
    if(manager->Message(1)->Header()->msgType != MsgTypeResendRequest)
        throw;

    delete manager;
}
