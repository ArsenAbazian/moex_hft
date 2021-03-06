#include "../../include/Fix/FixProtocolManager.h"


FixProtocolManager::FixProtocolManager(ISocketBufferProvider *provider, const char *protocolVersion) {
    this->messageBuffer = this->currentPos = 0;
    this->m_sendMsgSeqNo = 1;
    this->m_recvMsgSeqNo = 1;
    this->intConverter = new ItoaConverter();
    this->doubleConverter = new DtoaConverter();
    this->timeConverter = new UTCTimeConverter();
    this->currentTime = new SYSTEMTIME;
    this->m_bufferProvider = provider;
    this->m_protocolVersion = protocolVersion;
    this->m_protocolVersionLength = strlen(protocolVersion);
    this->m_paddingBytes = 0;

    memset(this->senderComputerId, 0, 100);
    this->senderComputerIdLength = 0;
    memset(this->targetComputerId, 0, 100);
    this->targetComputerIdLength = 0;
    this->receivedMessageLength = 0;
    this->m_sendMessageBuffer = 0;
    this->m_sendItemStartIndex = 0;
    this->messageBufferSize = 0;
    this->m_currMsg = 0;
    this->currentPos = 0;

    this->m_recvBuffer = this->m_bufferProvider->RecvBuffer();
    this->m_sendBuffer = this->m_bufferProvider->SendBuffer();
    this->m_rejectInfo = new FixRejectInfo();
    memset(this->m_rejectInfo, 0, sizeof(FixRejectInfo));

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
