#include "SocketBufferManager.h"
#include <memory.h>


SocketBufferManager::SocketBufferManager(int bufferCapaticy)  {
	this->buffer = new SocketBufferInfo[this->bufferCount];
	this->bufferIndex = 0;

	for (int i = 0; i < this->bufferCount; i++) { 
		this->buffer[i].size = bufferCapaticy;
		this->buffer[i].buffer = new char[bufferCapaticy + this->AdditionalBufferMemory];
		memset(this->buffer[i].buffer, bufferCapaticy + this->AdditionalBufferMemory, sizeof(char));
		this->buffer[i].current = this->buffer[i].buffer;
		this->buffer[i].currentIndex = 0;
		this->buffer[i].itemsCount = 0;
		this->buffer[i].itemsMaxCount = bufferCapaticy / 20;
		this->buffer[i].itemLength = new int[this->buffer[i].itemsMaxCount];
		this->buffer[i].itemOffset = new int[this->buffer[i].itemsMaxCount];
		memset(this->buffer[i].itemLength, this->buffer[i].itemsMaxCount, sizeof(int));
		memset(this->buffer[i].itemOffset, this->buffer[i].itemsMaxCount, sizeof(int));
	}

	this->currentBuffer = &(this->buffer[this->bufferIndex]);
	this->currentItem = this->currentBuffer->buffer;
}


SocketBufferManager::~SocketBufferManager()
{
	for (int i = 0; i < this->bufferCount; i++) { 
		delete[] this->buffer[i].buffer;
		delete[] this->buffer[i].itemLength;
		delete[] this->buffer[i].itemOffset;
	}
	delete[] this->buffer;
}

SocketBufferManager* DefaultFixProtocolHistoryManager::defaultManager = new SocketBufferManager(FixProtocolHistoryBufferLength);
