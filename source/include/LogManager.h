#pragma once

#include <time.h>
#include <error.h>
#include <string.h>
#include "ConsoleManager.h"
#include "LogErrorMessageCodes.h"

#define BINARY_LOG_MANAGER_ALLOW_PRINT

typedef enum _NullableBoolean{
    nbNull = -1,
    nbFalse = 0,
    nbTrue = 1
}NullableBoolean;

// Flags
typedef  enum _BinaryLogItemType {
    NodeItem = 0,
    NodeStart = 1,
    NodeEnd = 2,
    NodeFix = 3,
    NodeFast = 4
}BinaryLogItemType;

typedef struct _BinaryLogItem {
    struct timespec     m_startTime;        // timestamp DO NOT MOVE THIS FIELD!!!!!
    struct timespec     m_endTime;          // end timestamp
    int                 m_message;          // char message code - optimize - do not copy string - usually name of object
    int                 m_message2;         // char message code2 - usually - method name
    BinaryLogItemType   m_type;             // by default (do not set) is NodeItem
    int                 m_bufferIndex;      //
    int                 m_itemIndex;        //
    int                 m_errno;            // error number
    NullableBoolean     m_result;           // method result - 0 - fail, 1 - success, -1 - no value
    int                 m_index;            // global index
    union {
        int m_startIndex;
        int m_endIndex;
    };
}BinaryLogItem;

class BinaryLogManager {
    BinaryLogItem       *m_stack[256];
    int                 m_stackTop;

    BinaryLogItem       *m_items;
    const int           m_itemsCount = 200000;  // set 200000 for a while
    int                 m_itemIndex;

    char                m_tabs[64];
    int                 m_tabsCount;

    inline void AddTab() {
        this->m_tabs[this->m_tabsCount] = '\t';
        this->m_tabsCount++;
        this->m_tabs[this->m_tabsCount] = '\0';
    }
    inline void RemoveTab() {
        this->m_tabsCount--;
        this->m_tabs[this->m_tabsCount] = '\0';
    }

    inline BinaryLogItem* TopStack() { return this->m_stack[this->m_stackTop]; }

    inline void Push(BinaryLogItem *item) {
        this->m_stackTop++;
        this->m_stack[this->m_stackTop] = item;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
#endif
    }

    inline BinaryLogItem* Pop() {
        BinaryLogItem *top = this->TopStack();
        if(top->m_index != (this->m_itemIndex - 1)) {
            BinaryLogItem *end = Next();
            top->m_type = BinaryLogItemType::NodeStart;
            end->m_type = BinaryLogItemType::NodeEnd;
            end->m_startIndex = top->m_index;
            top->m_endIndex = end->m_index;
            top = end;
        }
        this->m_stackTop--;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
#endif
        return top;
    }

    inline BinaryLogItem* Next() {
        BinaryLogItem *item = &(this->m_items[this->m_itemIndex]);
        this->m_itemIndex++;
        return item;
    }

    inline void GetStartClock(BinaryLogItem *item) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, (struct timespec*)item);
    }

    inline void GetEndClock(BinaryLogItem *item) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, (struct timespec*)&(item->m_endTime));
    }

public:

    BinaryLogManager() {
        this->m_items = new BinaryLogItem[this->m_itemsCount];
        for(int i = 0; i < this->m_itemsCount; i++) {
            this->m_items[i].m_result = NullableBoolean::nbNull;
            this->m_items[i].m_index = i;
            this->m_items[i].m_message2 = -1;
            this->m_items[i].m_message = -1;
            this->m_items[i].m_startIndex = -1;
            this->m_items[i].m_endIndex = -1;
        }
        this->m_itemIndex = 0;
        this->m_stackTop = -1;
    }
    ~BinaryLogManager() {
        delete[] this->m_items;
    }

    inline BinaryLogItem* Write(int messageCode, int messageCode2) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_message2 = messageCode2;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }
    inline BinaryLogItem* Write(int messageCode) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }

    inline BinaryLogItem* WriteFix(int messageCode, int bufferIndex, int itemIndex) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_bufferIndex = bufferIndex;
        item->m_itemIndex = itemIndex;
        item->m_type = BinaryLogItemType::NodeFix;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }
    inline BinaryLogItem* WriteFast(int messageCode, int bufferIndex, int itemIndex) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_bufferIndex = bufferIndex;
        item->m_itemIndex = itemIndex;
        item->m_type = BinaryLogItemType::NodeFast;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }

    inline BinaryLogItem* WriteFast(int messageCode, int messageCode2, int bufferIndex, int itemIndex) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_message2 = messageCode2;
        item->m_bufferIndex = bufferIndex;
        item->m_itemIndex = itemIndex;
        item->m_type = BinaryLogItemType::NodeFast;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }

    inline BinaryLogItem* WriteLine(int messageCode) {
        return Write(messageCode);
    }
    inline BinaryLogItem* WriteSuccess(bool condition) {
        return Write(condition? LogMessageCode::lmcSuccess: LogMessageCode::lmcFailed);
    }
    inline BinaryLogItem* WriteSuccess(int messageCode, bool condition, int errno) {
        BinaryLogItem *item = WriteSuccess(messageCode, condition);
        item->m_errno = errno;
        return item;
    }
    inline BinaryLogItem* WriteSuccess(int messageCode, bool condition) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_result = (NullableBoolean)condition;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }
    inline BinaryLogItem* WriteSuccess(int messageCode, int messageCode2, bool condition) {
        BinaryLogItem *item = this->Next();

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, (struct timespec*)item);
        item->m_message = messageCode;
        item->m_message = messageCode2;
        item->m_result = (NullableBoolean)condition;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }
    inline BinaryLogItem* StartLog(int messageCode) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;

        this->Push(item);
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        if(item->m_type == BinaryLogItemType::NodeEnd)
            item = &(this->m_items[item->m_startIndex]);
        Print(item);
        AddTab();
#endif
        return item;
    }
    inline BinaryLogItem* StartLog(int messageCode, int messageCode2) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_message2 = messageCode2;

        this->Push(item);
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        if(item->m_type == BinaryLogItemType::NodeEnd)
            item = &(this->m_items[item->m_startIndex]);
        Print(item);
        AddTab();
#endif
        return item;
    }

    inline BinaryLogItem* EndLog(bool condition) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = (NullableBoolean)condition;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        RemoveTab();
        Print(item);
#endif
        return item;
    }

    inline BinaryLogItem* EndLog(bool condition, int messageCode) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = (NullableBoolean)condition;
        item->m_message = messageCode;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        RemoveTab();
        Print(item);
#endif
        return item;
    }
    inline BinaryLogItem* EndLogErrNo(bool condition, int errno) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = (NullableBoolean)condition;
        item->m_errno = errno;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        RemoveTab();
        Print(item);
#endif
        return item;
    }
    inline BinaryLogItem* EndLogErrNo(bool condition, const char *errText) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = (NullableBoolean)condition;
        item->m_errno = DefaultLogMessageProvider::Default->RegisterText(errText);
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        RemoveTab();
        Print(item);
#endif
        return item;
    }

    BinaryLogItem* Write(const char* message) {
        throw;
    }
    BinaryLogItem* Write(const char* message, const char* message2) {
        throw;
    }
    BinaryLogItem* WriteLine(const char* message) {
        throw;
    }
    BinaryLogItem* WriteSuccess(const char* message, bool condition) {
        throw;
    }
    BinaryLogItem* WriteSuccess(const char* message, const char* message2, bool condition) {
        throw;
    }
    BinaryLogItem* StartLog(const char* message) {
        throw;
    }
    BinaryLogItem* StartLog(const char* message, const char* message2) {
        throw;
    }
    BinaryLogItem* EndLog(bool condition, const char *errorMessage) {
        return EndLog(condition, DefaultLogMessageProvider::Default->RegisterText(errorMessage));
    }

    void Print();
    void Print(BinaryLogItem *item);
};

class DefaultLogManager {
public:
	static BinaryLogManager *Default;
};
