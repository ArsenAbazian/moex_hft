#include "ProtocolHistoryManager.h"
#include <memory.h>


FixProtocolHistoryManager::FixProtocolHistoryManager(int bufferCapaticy)  {
	this->buffer = new FixProtocolHistoryBufferInfo[this->bufferCount];
	this->bufferIndex = 0;

	for (int i = 0; i < this->bufferCount; i++) { 
		this->buffer[i].BufferCapacity = bufferCapaticy;
		this->buffer[i].Buffer = new char[bufferCapaticy + this->AdditionalBufferMemory];
		memset(this->buffer[i].Buffer, bufferCapaticy + this->AdditionalBufferMemory, sizeof(char));
		this->buffer[i].Current = this->buffer[i].Buffer;
		this->buffer[i].CurrentIndex = 0;
		this->buffer[i].ItemCount = 0;
		this->buffer[i].ItemsMaxCount = bufferCapaticy / 20;
		this->buffer[i].ItemLength = new int[this->buffer[i].ItemsMaxCount];
		this->buffer[i].ItemOffset = new int[this->buffer[i].ItemsMaxCount];
		this->buffer[i].ItemType = new HistoryItemType[this->buffer[i].ItemsMaxCount];
		memset(this->buffer[i].ItemLength, this->buffer[i].ItemsMaxCount, sizeof(int));
		memset(this->buffer[i].ItemOffset, this->buffer[i].ItemsMaxCount, sizeof(int));
		memset(this->buffer[i].ItemType, this->buffer[i].ItemsMaxCount, sizeof(HistoryItemType));
	}

	this->currentBuffer = &(this->buffer[this->bufferIndex]);
	this->currentItem = this->currentBuffer->Buffer;
}


FixProtocolHistoryManager::~FixProtocolHistoryManager()
{
	for (int i = 0; i < this->bufferCount; i++) { 
		delete[] this->buffer[i].Buffer;
		delete[] this->buffer[i].ItemLength;
		delete[] this->buffer[i].ItemOffset;
	}
	delete[] this->buffer;
}

FixProtocolHistoryManager* DefaultFixProtocolHistoryManager::defaultManager = new FixProtocolHistoryManager(FixProtocolHistoryBufferLength);
