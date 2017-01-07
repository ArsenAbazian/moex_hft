#include "FixProtocolManager.h"


FixProtocolManager::FixProtocolManager(ISocketBufferProvider *provider) {
	this->messageBuffer = this->currentPos = NULL;
    this->m_sendMsgSeqNo = 1;
    this->m_recvMsgSeqNo = 1;
	this->intConverter = new ItoaConverter();
	this->doubleConverter = new DtoaConverter();
	this->timeConverter = new UTCTimeConverter();
	this->currentTime = new SYSTEMTIME;
    this->m_bufferProvider = provider;

    this->m_recvBuffer = this->m_bufferProvider->RecvBuffer();
    this->m_sendBuffer = this->m_bufferProvider->SendBuffer();
    this->m_rejectInfo = new FixRejectInfo();
    bzero(this->m_rejectInfo, sizeof(FixRejectInfo));

    for(int i = 0; i < this->m_maxRecvMessageCount; i++) {
        this->m_recvMessage[i] = new FixProtocolMessage(this->intConverter,
                                                        this->timeConverter,
                                                        this->doubleConverter,
                                                        this->m_rejectInfo);
    }
    this->m_recvMessageCount = 0;
}

FixProtocolManager::~FixProtocolManager() {
    delete this->intConverter;
    delete this->doubleConverter;
    delete this->timeConverter;
    delete this->currentTime;
}
