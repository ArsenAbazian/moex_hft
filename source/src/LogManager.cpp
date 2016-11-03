#include <SocketBufferManager.h>
#include "LogManager.h"

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
    /*
    printf("%s", this->m_tabs);
    printf("%d: ", item->m_index);

    if(item->m_type == BinaryLogItemType::NodeEnd && item->m_startIndex != -1) {
        BinaryLogItem *start = &(this->m_items[item->m_startIndex]);
        if(start->m_message != -1)
            printf("'%s'", DefaultLogMessageProvider::Default->Message(start->m_message));
        if(start->m_message2 != -1)
            printf(" -> %s", DefaultLogMessageProvider::Default->Message(start->m_message2));
    }
    else {
        if(item->m_message != -1)
            printf("'%s'", DefaultLogMessageProvider::Default->Message(item->m_message));
        if(item->m_message2 != -1)
            printf(" -> %s", DefaultLogMessageProvider::Default->Message(item->m_message2));
    }

    if(item->m_type == BinaryLogItemType::NodeFix) {
        if(item->m_bufferIndex == -1)
            printf(" null");
        else {
            char *itemText = (char*)DefaultSocketBufferManager::Default->Buffer(item->m_bufferIndex)->Item(item->m_itemIndex);
            int itemSize = DefaultSocketBufferManager::Default->Buffer(item->m_bufferIndex)->ItemLength(item->m_itemIndex);

            char prevChar = itemText[itemSize]; itemText[itemSize] = '\0';
            printf(" '%s'", itemText);
            itemText[itemSize] = prevChar;
        }
    }
    else if(item->m_type == BinaryLogItemType::NodeFast) {
        if(item->m_bufferIndex == -1)
            printf("null");
        else {
            unsigned char *itemText = DefaultSocketBufferManager::Default->Buffer(item->m_bufferIndex)->Item(item->m_itemIndex);
            int itemSize = DefaultSocketBufferManager::Default->Buffer(item->m_bufferIndex)->ItemLength(item->m_itemIndex);
            printf("  %d", *((int*)itemText));
            printf(" '");
            for(int i = 0; i < itemSize; i++) {
                if(i == itemSize - 1)
                    printf("%2.2x", (unsigned int)itemText[i]);
                else
                    printf("%2.2x ", (unsigned int)itemText[i]);
            }
            printf("'");
        }
    }
    else if(item->m_type != BinaryLogItemType::NodeStart) {
        if(item->m_result != NullableBoolean::nbNull) {
            printf(" - %s. ", item->m_result == NullableBoolean::nbTrue?
                              DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcSuccess):
                              DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcFailed));
            if(item->m_errno != 0)
                printf("(%s)", strerror(item->m_errno));
        }
    }
    else if(item->m_type == BinaryLogItemType::NodeStart && item->m_endIndex != -1) {
        BinaryLogItem *end = &(this->m_items[item->m_endIndex]);
        if(end->m_result != NullableBoolean::nbNull) {
            printf(" - %s. ", end->m_result == NullableBoolean::nbTrue?
                              DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcSuccess):
                              DefaultLogMessageProvider::Default->Message(LogMessageCode::lmcFailed));
            if(end->m_errno != 0)
                printf("(%s)", strerror(item->m_errno));
        }
    }

    printf("\n");*/
}

BinaryLogManager* DefaultLogManager::Default = new BinaryLogManager();
//LogManager* DefaultLogManager::Default = new ConsoleLogManager();
