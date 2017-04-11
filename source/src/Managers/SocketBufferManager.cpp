#include "../../include/Managers/SocketBufferManager.h"
#include <memory.h>
#include "../../include/Managers/DebugInfoManager.h"

SocketBuffer::SocketBuffer(unsigned int bufferSize, unsigned int maxItemsCount, unsigned int bufferIndex) {

    this->m_bufferIndex = bufferIndex;
    this->m_size = bufferSize;
    this->m_maxItemsCount = maxItemsCount;
    this->m_buffer = new unsigned char[this->m_size + this->AdditionalBufferMemory];
    this->m_items = new unsigned char*[this->m_maxItemsCount];
    this->m_itemLength = new unsigned int[this->m_maxItemsCount];
    memset(this->m_buffer, this->m_size + this->AdditionalBufferMemory, 0);
    memset(this->m_items, this->m_maxItemsCount * sizeof(unsigned char*), 0);
    memset(this->m_itemLength, this->m_maxItemsCount * sizeof(unsigned int), 0);
    this->Init();
}

SocketBuffer::~SocketBuffer() {
    delete[] this->m_buffer;
    delete[] this->m_items;
    delete[] this->m_itemLength;
}

SocketBufferManager::SocketBufferManager(int maxBuffersCount) {
    this->m_maxItemsCount = maxBuffersCount;
    this->m_buffers = new SocketBuffer*[maxBuffersCount];
    this->m_itemsCount = 0;
    this->PrintMemoryInfo("After SocketBufferManager::SocketBufferManager");
}

void SocketBufferManager::PrintMemoryInfo(const char *string) {
    DebugInfoManager::Default->PrintMemoryInfo(string);
}

SocketBufferManager* DefaultSocketBufferManager::Default = new SocketBufferManager(RobotSettings::Default->SocketBuffersMaxCount);
