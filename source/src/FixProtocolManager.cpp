#include "FixProtocolManager.h"


FixProtocolManager::FixProtocolManager() {
	this->messageBuffer = this->currentPos = NULL;
    this->messageSequenceNumber = 0;
	this->intConverter = new ItoaConverter();
	this->doubleConverter = new DtoaConverter();
	this->timeConverter = new UTCTimeConverter();
	this->currentTime = new SYSTEMTIME;
    this->m_headerInfo = new FixHeaderInfo();
    bzero(this->m_headerInfo, sizeof(FixHeaderInfo));
}

FixProtocolManager::~FixProtocolManager() {
    delete this->intConverter;
    delete this->doubleConverter;
    delete this->timeConverter;
    delete this->currentTime;
}
