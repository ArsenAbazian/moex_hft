#include "FastProtocolManager.h"


FastProtocolManager::FastProtocolManager() {
	this->buffer = new BYTE[this->maxBufferLength];
	this->currentPos = buffer;
	this->m_recvMsgSeqNo = 1;
	this->m_sendMsgSeqNo = 1;
}


FastProtocolManager::~FastProtocolManager() {
	delete[] this->buffer;
}
