#pragma once

class SocketBuffer {
    const int           AdditionalBufferMemory = 8192;

    unsigned char       *m_buffer;
	unsigned char       *m_current;
    unsigned char       *m_end;
	unsigned int        m_maxItemsCount;
	unsigned int        m_itemsCount;
	unsigned int        m_size;
	unsigned char*      *m_items;
	unsigned int        *m_itemLength;
public:
    SocketBuffer(unsigned int bufferSize, unsigned int maxItemsCount);
    ~SocketBuffer();

    inline unsigned char* Start() { return this->m_buffer; }
    inline unsigned char* CurrentPos() { return this->m_current; }
    inline unsigned int ItemsMaxCount() { return this->m_maxItemsCount; }
    inline unsigned int ItemsCount() { return this->m_itemsCount; }
    inline unsigned int Size() { return this->m_size; }
    inline unsigned int ItemLength(int index) { return this->m_itemLength[index]; }
    inline unsigned char* Item(int index) { return this->m_items[index]; }

    inline void Next(int length) {
        int itemCount = this->itemsCount;

        this->m_itemLength[itemCount] = length;
        this->m_items[itemCount] = this->current;
        this->current += (length & 0xfffffffc) + 4; //optimization by 4

        itemCount++;
        if ((itemCount >= this->itemsMaxCount) || (this->current >= this->m_end))
            this->Reset();
        else
            this->currentBuffer->itemsCount = itemCount;
    }
    void Reset() {
        this->m_current = this->m_buffer;
        this->m_end = this->m_buffer + this->m_size;
        this->m_itemsCount = 0;
    }
};

class SocketBufferManager {
    SocketBuffer        **m_buffers;
    int                 m_maxItemsCount;
    int                 m_itemsCount;
public:
	SocketBufferManager(int maxBuffersCount);
	~SocketBufferManager() {
        for(int i = 0; i < this->m_itemsCount; i++)
            delete this->m_buffers[i];
        delete[] this->m_buffers;
        this->m_itemsCount = 0;
    }

    inline SocketBuffer* GetBuffer(unsigned int size, unsigned int maxItemsCount) {
        if(this->m_itemsCount >= this->m_maxItemsCount)
            return NULL;
        this->m_buffers[this->m_itemsCount] = new SocketBuffer(size, maxItemsCount);
        this->m_itemsCount++;
    }
};

class DefaultFixProtocolHistoryManager {
public: static SocketBufferManager *Default;
};

