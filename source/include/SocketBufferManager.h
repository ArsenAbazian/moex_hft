#pragma once
#include "Types.h"
#include <cstddef>

class INextIndexProvider {
public:
    virtual inline unsigned int NextIndex() = 0;
};

class SocketBuffer {
    const int           AdditionalBufferMemory = 8192;

    unsigned int         m_bufferIndex;
    unsigned char       *m_buffer;
	unsigned char       *m_current;
    unsigned char       *m_end;
	unsigned int        m_maxItemsCount;
	unsigned int        m_itemsCount;
	unsigned int        m_size;
	unsigned char*      *m_items;
	unsigned int        *m_itemLength;
    unsigned int        *m_index;
    INextIndexProvider  *m_indexProvider;
public:
    SocketBuffer(INextIndexProvider *provider, unsigned int bufferSize, unsigned int maxItemsCount, unsigned int bufferIndex);
    ~SocketBuffer();

    inline unsigned int BufferIndex() { return this->m_bufferIndex; }
    inline unsigned char* Start() { return this->m_buffer; }
    inline unsigned char* CurrentPos() { return this->m_current; }
    inline unsigned int ItemsMaxCount() { return this->m_maxItemsCount; }
    inline unsigned int ItemsCount() { return this->m_itemsCount; }
    inline unsigned int CurrentItemIndex() { return this->m_itemsCount; }
    inline unsigned int Size() { return this->m_size; }
    inline unsigned int ItemLength(int index) { return this->m_itemLength[index]; }
    inline unsigned char* Item(int index) { return this->m_items[index]; }

    inline unsigned int NextIndex() { return this->m_indexProvider->NextIndex(); }
    inline void Next(int length) {
        int itemCount = this->m_itemsCount;

        this->m_itemLength[itemCount] = length;
        this->m_current += (length & 0xfffffffc) + 8; //optimization by 4 + additional 4 bytes for zero string

        itemCount++;
        if ((itemCount >= this->m_maxItemsCount) || (this->m_current >= this->m_end))
            this->Reset();
        else {
            this->m_itemsCount = itemCount;
            this->m_items[itemCount] = this->m_current;
            this->m_index[itemCount] = NextIndex();
        }
    }
    void Reset() {
        this->m_current = this->m_buffer;
        this->m_end = this->m_buffer + this->m_size;
        this->m_itemsCount = 0;

        this->m_items[0] = this->m_current;
        this->m_index[0] = NextIndex();
    }
};

class SocketBufferManager : public INextIndexProvider {
    SocketBuffer        **m_buffers;
    int                 m_maxItemsCount;
    int                 m_itemsCount;
    unsigned int        m_globalIndex;
public:
	SocketBufferManager(int maxBuffersCount) {
        this->m_maxItemsCount = maxBuffersCount;
        this->m_buffers = new SocketBuffer*[maxBuffersCount];
        this->m_itemsCount = 0;
    }
	~SocketBufferManager() {
        for(int i = 0; i < this->m_itemsCount; i++)
            delete this->m_buffers[i];
        delete[] this->m_buffers;
        this->m_itemsCount = 0;
    }

    inline SocketBuffer* GetFreeBuffer(unsigned int size, unsigned int maxItemsCount) {
        if(this->m_itemsCount >= this->m_maxItemsCount)
            return NULL;
        this->m_buffers[this->m_itemsCount] = new SocketBuffer(this, size, maxItemsCount, this->m_itemsCount);
        this->m_itemsCount++;
        return this->m_buffers[this->m_itemsCount - 1];
    }
    inline unsigned int NextIndex() { unsigned int res = this->m_globalIndex; this->m_globalIndex++; return res; }
    inline SocketBuffer* Buffer(int index) { return this->m_buffers[index]; }
};

class DefaultSocketBufferManager {
public: static SocketBufferManager *Default;
};

