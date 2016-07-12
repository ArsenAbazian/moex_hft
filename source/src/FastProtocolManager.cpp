#include "FastProtocolManager.h"


FastProtocolManager::FastProtocolManager() {
	this->buffer = new BYTE[this->maxBufferLength];
	this->currentPos = buffer;
}


FastProtocolManager::~FastProtocolManager() {
	delete[] this->buffer;
}
