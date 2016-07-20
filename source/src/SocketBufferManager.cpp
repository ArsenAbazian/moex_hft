#include "SocketBufferManager.h"
#include <memory.h>


SocketBufferManager::SocketBufferManager(int bufferCapaticy)  {
	this->buffer = new SocketBufferInfo[this->bufferCount];
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
		memset(this->buffer[i].ItemLength, this->buffer[i].ItemsMaxCount, sizeof(int));
		memset(this->buffer[i].ItemOffset, this->buffer[i].ItemsMaxCount, sizeof(int));
	}

	this->currentBuffer = &(this->buffer[this->bufferIndex]);
	this->currentItem = this->currentBuffer->Buffer;
}


SocketBufferManager::~SocketBufferManager()
{
	for (int i = 0; i < this->bufferCount; i++) { 
		delete[] this->buffer[i].Buffer;
		delete[] this->buffer[i].ItemLength;
		delete[] this->buffer[i].ItemOffset;
	}
	delete[] this->buffer;
}

SocketBufferManager* DefaultFixProtocolHistoryManager::defaultManager = new SocketBufferManager(FixProtocolHistoryBufferLength);
