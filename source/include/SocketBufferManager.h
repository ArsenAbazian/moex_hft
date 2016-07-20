#pragma once
typedef struct _SocketBufferInfo {
	char *Buffer;
	char *Current;
	int ItemsMaxCount;
	int ItemCount;
	int BufferCapacity;
	int *ItemOffset;
	int *ItemLength;
	int CurrentIndex;
}SocketBufferInfo;

class SocketBufferManager {
	SocketBufferInfo *buffer;
	SocketBufferInfo *currentBuffer;
	char			*currentItem;
	int				bufferIndex;
	const int		bufferCount = 2;
	const int		AdditionalBufferMemory = 8192;
public:
	SocketBufferManager(int bufferCapacity);
	~SocketBufferManager();

	inline char*	Buffer() { return this->currentItem; }
	inline void		Increment(int length) {
		int itemCount = this->currentBuffer->ItemCount;
		
		this->currentBuffer->ItemLength[itemCount] = length;
		this->currentBuffer->ItemOffset[itemCount] = this->currentBuffer->Current - this->currentBuffer->Buffer;
		this->currentBuffer->Current += (length & 0xfffffffc) + 4; //optimization by 4

		itemCount++;
		if ((itemCount > this->currentBuffer->ItemsMaxCount) || 
			(this->currentBuffer->Current - this->currentBuffer->Buffer) >= this->currentBuffer->BufferCapacity) { 
			this->bufferIndex = (this->bufferIndex) % this->bufferCount;
			this->bufferIndex++;
			this->currentBuffer = &(this->buffer[this->bufferIndex]);
			this->currentBuffer->ItemCount = 0;
			this->currentBuffer->Current = this->currentBuffer->Buffer;
		}
		else { 
			this->currentBuffer->ItemCount = itemCount;
		}
		this->currentItem = this->currentBuffer->Current;
	}
};

static const int FixProtocolHistoryBufferLength = 64 * 1024 * 1024; // 64 mb
class DefaultFixProtocolHistoryManager {
public: static SocketBufferManager *defaultManager;
};

