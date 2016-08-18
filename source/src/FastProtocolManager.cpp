#include "FastProtocolManager.h"


FastProtocolManager::FastProtocolManager() {
	this->m_recvMsgSeqNo = 1;
	this->m_sendMsgSeqNo = 1;
	this->InitializeConstantStrings();
	this->InitializeDecodeMethodPointers();
	this->InitializeMessageInfo();
}


FastProtocolManager::~FastProtocolManager() {
	delete[] this->buffer;
}
