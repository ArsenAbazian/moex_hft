//
// Created by root on 07.01.17.
//
#include "../../include/Test/TestMessagesHelper.h"

#ifdef TEST
PointerList<SocketMessageInfo>* TestMessagesHelper::m_sockMessages = new PointerList<SocketMessageInfo>(32);
bool TestMessagesHelper::SkipTimeOutCheck = false;
#endif //TEST
