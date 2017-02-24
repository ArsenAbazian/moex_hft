#include "Managers/SocketBufferManager.h"
#include <memory.h>

SocketBuffer::SocketBuffer(INextIndexProvider *provider, unsigned int bufferSize, unsigned int maxItemsCount, unsigned int bufferIndex) {

    this->m_bufferIndex = bufferIndex;
    this->m_indexProvider = provider;
    this->m_size = bufferSize;
    this->m_maxItemsCount = maxItemsCount;
    this->m_buffer = new unsigned char[this->m_size + this->AdditionalBufferMemory];
    this->m_items = new unsigned char*[this->m_maxItemsCount];
    this->m_itemLength = new unsigned int[this->m_maxItemsCount];
    this->m_index = new unsigned int[this->m_maxItemsCount];
    bzero(this->m_buffer, this->m_size + this->AdditionalBufferMemory);
    bzero(this->m_items, this->m_maxItemsCount * sizeof(unsigned char*));
    bzero(this->m_itemLength, this->m_maxItemsCount * sizeof(unsigned int));
    this->Reset();
}

SocketBuffer::~SocketBuffer() {
    delete[] this->m_buffer;
    delete[] this->m_items;
    delete[] this->m_itemLength;
    delete[] this->m_index;
}

SocketBufferManager* DefaultSocketBufferManager::Default = new SocketBufferManager(RobotSettings::Default->SocketBuffersMaxCount);
