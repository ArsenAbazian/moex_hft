#include "LogManager.h"


LogManager::LogManager()
{
}


LogManager::~LogManager()
{
}

void BinaryLogManager::Print() {
    for(int i = 0; i < this->m_itemIndex; i++) {
        BinaryLogItem *item = &this->m_items[i];
        Print(item);
        if(item->m_type == BinaryLogItemType::NodeStart)
            AddTab();
        else if(item->m_type == BinaryLogItemType::NodeEnd)
            RemoveTab();
    }
}

void BinaryLogManager::Print(BinaryLogItem *item) {
    if(item->m_type == BinaryLogItemType::NodeEnd)
        return;
    printf("%s", this->m_tabs);
    if(item->m_message != -1)
        printf("%s", DefaultLogMessageProvider::Default->Message(item->m_message));
    if(item->m_message2 != -1)
        printf("->%s", DefaultLogMessageProvider::Default->Message(item->m_message2));
    if(item->m_type != BinaryLogItemType::NodeStart) {
        printf(" - %s. ", item->m_result? DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcSuccess):
                      DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcFailed));
        if(item->m_errno != 0)
            printf("(%s)", strerror(item->m_errno));
    }
    if(item->m_type == BinaryLogItemType::NodeStart) {
        BinaryLogItem *end = &(this->m_items[item->m_endIndex]);
        printf(" - %s. ", end->m_result? DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcSuccess):
                          DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcFailed));
        if(end->m_errno != 0)
            printf("(%s)", strerror(item->m_errno));
    }
    printf("\n");
}

LogManager* DefaultLogManager::Default = new BinaryLogManager();
//LogManager* DefaultLogManager::Default = new ConsoleLogManager();
