#include "FixProtocolManager.h"


FixProtocolManager::FixProtocolManager(FixProtocolHistoryManager *historyManager)
{
	this->historyManager = historyManager;
	this->currentPos = this->Message();
	this->messageSequenceNumber = 0;
	this->intConverter = new ItoaConverter();
	this->doubleConverter = new DtoaConverter();
	this->timeConverter = new UTCTimeConverter();
	this->currentTime = new SYSTEMTIME;
}


FixProtocolManager::~FixProtocolManager()
{
}
