#pragma once
typedef enum _HistoryItemType {
	FixMessage,
	LogMessage,
	FastMesssage,
}HistoryItemType;

typedef struct _FixProtocolHistoryBufferInfo {
	char *Buffer;
	char *Current;
	int ItemsMaxCount;
	int ItemCount;
	int BufferCapacity;
	int *ItemOffset;
	int *ItemLength;
	HistoryItemType *ItemType;
	int CurrentIndex;
}FixProtocolHistoryBufferInfo;

class FixProtocolHistoryManager
{
	FixProtocolHistoryBufferInfo *buffer;
	FixProtocolHistoryBufferInfo *currentBuffer;
	char			*currentItem;
	int				bufferIndex;
	const int		bufferCount = 2;
	const int		AdditionalBufferMemory = 8192;
public:
	FixProtocolHistoryManager(int bufferCapacity);
	~FixProtocolHistoryManager();

	inline char*	Buffer() { return this->currentItem; }
	inline void		Increment(int length, HistoryItemType itemType) {
		int itemCount = this->currentBuffer->ItemCount;
		
		this->currentBuffer->ItemLength[itemCount] = length;
		this->currentBuffer->ItemOffset[itemCount] = this->currentBuffer->Current - this->currentBuffer->Buffer;
		this->currentBuffer->ItemType[itemCount] = itemType;
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
public: static FixProtocolHistoryManager *defaultManager;
};

