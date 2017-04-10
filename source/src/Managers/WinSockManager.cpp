#include "../../include/Managers/WinSockManager.h"
#include "../../include/Lib/PointerList.h"
#include "../../include/Test/TestMessagesHelper.h"

int 				WinSockManager::m_pollFdCount = 256;
struct pollfd* 		WinSockManager::m_pollFd = new struct pollfd[256];
int 				WinSockManager::m_registeredCount = 0;
WinSockManager** 	WinSockManager::m_registeredManagers = new WinSockManager*[256];
int 				WinSockManager::m_pollRes = 0;
#ifdef TEST
TestMessagesHelper* WinSockManager::m_testHelper = 0;
#endif

WinSockManager::WinSockManager() {
	if(WinSockManager::m_registeredCount == 0)
		this->InitializePollInfo();

	this->m_socket = -1;
	this->m_serverAddressLogIndex = LogMessageCode::lmcNone;
    this->m_sendStatus = WinSockStatus::wssOk;
    this->m_recvStatus = WinSockStatus::wssOk;
    this->m_sendSize = 0;
    this->m_recvSize = 0;
	this->m_pollIndex = -1;
    this->m_shouldRecv = false;
    this->m_tempBuffer = new unsigned char[2000];
    this->RegisterPoll();
}


WinSockManager::~WinSockManager() {
	this->Disconnect();
    delete this->m_tempBuffer;
}

#ifdef TEST
bool WinSockManager::ShouldRecvTest() {
    LinkedPointer<SocketMessageInfo> *ptr = TestMessagesHelper::m_sockMessages->Start();
    if(ptr == 0)
        return false;
    while(true) {
        if (ptr->Data()->m_manager == this)
            return true;
        if(!ptr->HasNext())
            break;
        ptr = ptr->Next();
    }
    return false;
}

bool WinSockManager::RecvTest(unsigned char *buffer) {
	LinkedPointer<SocketMessageInfo> *ptr = TestMessagesHelper::m_sockMessages->Start();
	while(true) {
		if(ptr->Data()->m_manager == this) {
			this->m_recvSize  = ptr->Data()->m_bufferLength;
			this->m_recvBytes = buffer;
			memcpy(buffer, ptr->Data()->m_buffer, this->m_recvSize);
            TestMessagesHelper::m_sockMessages->Remove(ptr);
            WinSockManager::m_registeredManagers[this->m_pollIndex]->m_shouldRecv = false;
            return true;
		}
        if(!ptr->HasNext())
            break;
		ptr = ptr->Next();
	}
	return false;
}

void WinSockManager::SendTest() {
	WinSockManager::m_testHelper->OnRecvData(this, this->m_sendBytes, this->m_sendSize);
}
#endif