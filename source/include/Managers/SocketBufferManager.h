#pragma once
#include "../Settings.h"
#include <cstddef>

class INextIndexProvider {
public:
    virtual inline unsigned int NextIndex() = 0;
};

class SocketBuffer {
    unsigned char       *m_buffer;
    unsigned char       *m_current;
    unsigned char       *m_end;
    unsigned char*      *m_items;
    unsigned int        *m_itemLength;
    unsigned int         m_bufferIndex;
    unsigned int        m_maxItemsCount;
    unsigned int        m_itemsCount;
    unsigned int        m_size;

    static const int           AdditionalBufferMemory = 8192;
public:
    SocketBuffer(unsigned int bufferSize, unsigned int maxItemsCount, unsigned int bufferIndex);
    ~SocketBuffer();

    inline unsigned int BufferIndex() const { return this->m_bufferIndex; }
    inline unsigned char* Start() { return this->m_buffer; }
    inline unsigned char* CurrentPos() { return this->m_current; }
    inline unsigned int ItemsMaxCount() const { return this->m_maxItemsCount; }
    inline unsigned int ItemsCount() const { return this->m_itemsCount; }
    inline unsigned int CurrentItemIndex() const { return this->m_itemsCount; }
    inline void SetCurrentItemSize(int size) { this->m_itemLength[this->m_itemsCount] = size; }
    inline unsigned int Size() const { return this->m_size; }
    inline unsigned int ItemLength(int index) const { return this->m_itemLength[index]; }
    inline unsigned char* Item(int index) { return this->m_items[index]; }

    // there is no need to check buffer - because resetting buffer leads to incorrect results after.
    // better segmentation fault
    inline void Next(int length) {
        this->m_itemLength[this->m_itemsCount] = length;
        this->m_current += (length & 0xfffffffc) + 8; //optimization by 4 + additional 4 bytes for zero string
        this->m_itemsCount++;
        this->m_items[this->m_itemsCount] = this->m_current;
    }
    inline void NextExact(int length) {
        this->m_itemLength[this->m_itemsCount] = length;
        this->m_current += length; //NO OPTIMIZE

        this->m_itemsCount++;
        this->m_items[this->m_itemsCount] = this->m_current;
    }
    inline void Init() {
        this->m_current = this->m_buffer;
        this->m_end = this->m_buffer + this->m_size;
        this->m_itemsCount = 0;

        this->m_items[0] = this->m_current;
    }
    inline void Reset() {
        this->m_current = this->m_buffer;
        this->m_itemsCount = 0;
    }
    inline double CalcMemoryUsagePercentage() {
        if(this->m_size == 0)
            return 0.0;
        unsigned int used = this->m_current - this->m_buffer;
        return ((double)used) / this->m_size * 100.0;
    }
    inline double CalcItemsUsagePercentage() const {
        if(this->m_maxItemsCount == 0)
            return 0.0;
        return this->m_itemsCount / (double)this->m_maxItemsCount * 100.0;
    }
};

class SocketBufferManager : public INextIndexProvider {
    SocketBuffer        **m_buffers;
    int                 m_maxItemsCount;
    int                 m_itemsCount;
    unsigned int        m_globalIndex;
    int                 m_paddingBytes;

    void PrintMemoryInfo(const char *string);
public:
    SocketBufferManager(int maxBuffersCount);
    ~SocketBufferManager() {
        for(int i = 0; i < this->m_itemsCount; i++)
            delete this->m_buffers[i];
        delete[] this->m_buffers;
        this->m_itemsCount = 0;
    }

    inline SocketBuffer* GetFreeBuffer(unsigned int size, unsigned int maxItemsCount) {
        if(this->m_itemsCount >= this->m_maxItemsCount)
            return NULL;
        this->m_buffers[this->m_itemsCount] = new SocketBuffer(size, maxItemsCount, this->m_itemsCount);
        this->m_itemsCount++;
        PrintMemoryInfo("After SocketBufferManager::GetFreeBuffer");
        return this->m_buffers[this->m_itemsCount - 1];
    }
    inline unsigned int NextIndex() { unsigned int res = this->m_globalIndex; this->m_globalIndex++; return res; }
    inline SocketBuffer* Buffer(int index) { return this->m_buffers[index]; }
};

class DefaultSocketBufferManager {
public: static SocketBufferManager *Default;
};

