#pragma once

#include <time.h>
#include <error.h>
#include <string.h>
#include "ConsoleManager.h"
#include "LogErrorMessageCodes.h"

#define BINARY_LOG_MANAGER_ALLOW_PRINT

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
    int                 m_bytesCount;       // for fix and fast protocol - bytes count;
    int                 m_errno;            // error number
    bool                m_result;           // method result - fail or success
    int                 m_index;            //
    union {
        int m_startIndex;
        int m_endIndex;
    };
}BinaryLogItem;

class LogManager
{
public:
    virtual void Write(const char* message) = 0;
	virtual void Write(const char* message, const char* message2) = 0;
	virtual BinaryLogItem* WriteFix(int messageIndex, int bufferIndex, int itemIndex) = 0;
    virtual BinaryLogItem* WriteFast(int messageIndex, int bufferIndex, int itemIndex, int size) = 0;
    virtual void WriteLine(const char* message) = 0;
	virtual void WriteSuccess(bool condition) = 0;
	virtual void WriteSuccess(const char* message, bool condition) = 0;
	virtual void WriteSuccess(const char* message, const char* message2, bool condition) = 0;
	virtual void StartLog(const char* message) = 0;
	virtual void StartLog(const char* message, const char* message2) = 0;
	virtual void EndLog(bool condition, const char *errorMessage) = 0;
    virtual void EndLogErrNo(bool condition, int errno) = 0;
    virtual void EndLogErrNo(bool condition, const char *errText) = 0;

    virtual void Write(int messageCode) = 0;
    virtual void Write(int messageCode, int messageCode2) = 0;
    virtual void WriteLine(int messageCode) = 0;
    virtual void WriteSuccess(int messageCode, bool condition) = 0;
    virtual void WriteSuccess(int messageCode, int messageCode2, bool condition) = 0;
    virtual void StartLog(int messageCode) = 0;
    virtual void StartLog(int messageCode, int messageCode2) = 0;
    virtual void EndLog(bool condition, int messageCode) = 0;

    virtual void EndLog(bool condition) { EndLog(condition, (const char*)NULL); }
    virtual void Print() = 0;
};

class BinaryLogManager : public LogManager {
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
        if(this->m_stackTop > -1)
            TopStack()->m_type = BinaryLogItemType::NodeStart;
        this->m_stackTop++;
        this->m_stack[this->m_stackTop] = item;
    }

    inline BinaryLogItem* Pop() {
        BinaryLogItem *top = this->TopStack();
        if(top->m_type == BinaryLogItemType::NodeStart) {
            BinaryLogItem *end = Next();
            end->m_type = BinaryLogItemType::NodeEnd;
            end->m_startIndex = top->m_index;
            top->m_endIndex = end->m_index;
            top = end;
        }
        this->m_stackTop--;
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
            this->m_items[i].m_result = true;
            this->m_items[i].m_index = i;
            this->m_items[i].m_message2 = -1;
            this->m_items[i].m_message = -1;
            this->m_items[i].m_bytesCount = 0;
        }
        this->m_itemIndex = 0;
        this->m_stackTop = -1;
    }
    ~BinaryLogManager() {
        delete[] this->m_items;
    }

    inline void Write(int messageCode, int messageCode2) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_message2 = messageCode2;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
    }
    inline void Write(int messageCode) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
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
    inline BinaryLogItem* WriteFast(int messageCode, int bufferIndex, int itemIndex, int size) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_bufferIndex = bufferIndex;
        item->m_itemIndex = itemIndex;
        item->m_type = BinaryLogItemType::NodeFast;
        item->m_bytesCount = size;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
        return item;
    }

    inline void WriteLine(int messageCode) {
        Write(messageCode);
    }
    inline void WriteSuccess(bool condition) {
        Write(condition? LogMessageCode::lmcSuccess: LogMessageCode::lmcFailed);
    }
    inline void WriteSuccess(int messageCode, bool condition) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_result = condition;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
    }
    inline void WriteSuccess(int messageCode, int messageCode2, bool condition) {
        BinaryLogItem *item = this->Next();

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, (struct timespec*)item);
        item->m_message = messageCode;
        item->m_message = messageCode2;
        item->m_result = condition;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        Print(item);
#endif
    }
    inline void StartLog(int messageCode) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;

        this->Push(item);
    }
    inline void StartLog(int messageCode, int messageCode2) {
        BinaryLogItem *item = this->Next();

        GetStartClock(item);
        item->m_message = messageCode;
        item->m_message2 = messageCode2;

        this->Push(item);
    }

    inline void EndLog(bool condition) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = condition;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        if(item->m_type == BinaryLogItemType::NodeEnd)
            item = &(this->m_items[item->m_startIndex]);
        Print(item);
#endif
    }

    inline void EndLog(bool condition, int messageCode) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = condition;
        item->m_message = messageCode;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        if(item->m_type == BinaryLogItemType::NodeEnd)
            item = &(this->m_items[item->m_startIndex]);
        Print(item);
#endif
    }
    inline void EndLogErrNo(bool condition, int errno) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = condition;
        item->m_errno = errno;
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        if(item->m_type == BinaryLogItemType::NodeEnd)
            item = &(this->m_items[item->m_startIndex]);
        Print(item);
#endif
    }
    inline void EndLogErrNo(bool condition, const char *errText) {
        BinaryLogItem *item = Pop();
        GetEndClock(item);
        item->m_result = condition;
        item->m_errno = DefaultLogMessageProvider::Default->RegisterText(errText);
#ifdef BINARY_LOG_MANAGER_ALLOW_PRINT
        if(item->m_type == BinaryLogItemType::NodeEnd)
            item = &(this->m_items[item->m_startIndex]);
        Print(item);
#endif
    }

    void Write(const char* message) {
        throw;
    }
    void Write(const char* message, const char* message2) {
        throw;
    }
    void WriteLine(const char* message) {
        throw;
    }
    void WriteSuccess(const char* message, bool condition) {
        throw;
    }
    void WriteSuccess(const char* message, const char* message2, bool condition) {
        throw;
    }
    void StartLog(const char* message) {
        throw;
    }
    void StartLog(const char* message, const char* message2) {
        throw;
    }
    void EndLog(bool condition, const char *errorMessage) {
        EndLog(condition, DefaultLogMessageProvider::Default->RegisterText(errorMessage));
    }

    void Print();
    void Print(BinaryLogItem *item);
};

class ConsoleLogManager : public LogManager {
	const int messagesCount = 2048;
	const char *messages[2048];
	const char *messages2[2048];
	bool repeatMessage[2048];
	int messageIndex;
	char tabs[256];
	int tabsCount;
	bool shouldStartNewLine;
    LogMessageProvider *logMessageProvider;

public:
	ConsoleLogManager() { 
		this->messageIndex = -1;
		this->tabs[0] = '\0';
		this->tabsCount = 0;
		this->shouldStartNewLine = false;
        this->logMessageProvider = DefaultLogMessageProvider::Default;
	}

	void Write(const char* message) { ConsoleManager::Write(this->tabs, message); }
	void Write(const char* message, const char* message2) { 
		ConsoleManager::Write(this->tabs, message); 
		ConsoleManager::Write("->", message2);
	}
	void WriteLine(const char* message) { ConsoleManager::WriteLine(this->tabs, message); }
	void WriteSuccess(bool condition) { ConsoleManager::WriteLine(this->tabs, (condition ? "success." : "failed")); }
	void WriteSuccess(const char * message, const char* message2, bool condition) { 
		ConsoleManager::Write(tabs, message);
		ConsoleManager::Write("->", message2);
		ConsoleManager::Write(" - ");
		ConsoleManager::WriteLine(condition ? "success." : "failed.");
	}
	void WriteSuccess(const char * message, bool condition) { 
		ConsoleManager::Write(tabs, message);
		ConsoleManager::Write(" - ");
		ConsoleManager::WriteLine(condition ? "success." : "failed.");
	}
	void StartLog(const char* message) {
		StartLog(message, NULL);
	}
	void StartLog(const char* message, const char* message2) { 
		if(this->shouldStartNewLine)
			WriteLine("");
		if (this->messageIndex >= 0)
			this->repeatMessage[this->messageIndex] = true;
		this->messageIndex++;
		this->repeatMessage[this->messageIndex] = false;
		this->messages[this->messageIndex] = message;
		this->messages2[this->messageIndex] = message2;
		if (message2 != NULL)
			Write(message, message2); 
		else 
			Write(message);
		this->tabs[this->tabsCount] = ' ';
		this->tabs[this->tabsCount + 1] = ' ';
		this->tabsCount +=2;
		this->tabs[this->tabsCount] = '\0';
		this->shouldStartNewLine = true;
	}

	void EndLog(bool condition, const char *errorText) {
		if (!condition) {
			bool dummy = true;
		}
		if (this->messageIndex == -1)
			return;
		this->tabsCount -=2;
		this->tabs[this->tabsCount] = '\0';
		if (this->repeatMessage[this->messageIndex]) {
			ConsoleManager::Write(tabs, this->messages[this->messageIndex]);
			if (this->messages2[this->messageIndex] != NULL) {
				ConsoleManager::Write("->", this->messages2[this->messageIndex]);
			}
		}
		
		ConsoleManager::Write(" - ");
		ConsoleManager::Write(condition ? "success." : "failed.");
		if (errorText != NULL) {
			ConsoleManager::Write("(");
			ConsoleManager::Write(errorText);
			ConsoleManager::Write(")");
		}
		ConsoleManager::WriteLine("");
		
		this->messageIndex--;
		this->shouldStartNewLine = false;
	}
    void EndLogErrNo(bool condition, int errno) {
        EndLog(condition, strerror(errno));
    }

    void Write(int messageCode, int messageCode2) {
        Write(logMessageProvider->Message(messageCode), logMessageProvider->Message(messageCode2));
    }
    void Write(int messageCode) {
		Write(logMessageProvider->Message(messageCode));
    }
    void WriteLine(int messageCode) {
		WriteLine(logMessageProvider->Message(messageCode));
    }
    void WriteSuccess(int messageCode, bool condition) {
		WriteSuccess(logMessageProvider->Message(messageCode), condition);
    }
    void WriteSuccess(int messageCode, int messageCode2, bool condition) {
		WriteSuccess(logMessageProvider->Message(messageCode), logMessageProvider->Message(messageCode2), condition);
    }
    void StartLog(int messageCode) {
		StartLog(logMessageProvider->Message(messageCode));
    }
    void StartLog(int messageCode, int messageCode2) {
		StartLog(logMessageProvider->Message(messageCode), logMessageProvider->Message(messageCode2));
    }
    void EndLog(bool condition, int errorCode) {
		EndLog(condition, logMessageProvider->Message(errorCode));
    }
    BinaryLogItem* WriteFix(int messageIndex, int bufferIndex, int itemIndex) { return NULL; }
    BinaryLogItem* WriteFast(int messageIndex, int bufferIndex, int itemIndex, int size) { return NULL; }
    void Print() { }
};

class EmptylogManager : public LogManager {
	void Write(const char* message) {}
	void Write(const char* message, const char* message2) {}
	void WriteLine(const char* message) {}
	void WriteSuccess(bool condition) {}
	void WriteSuccess(const char* message, bool condition) {}
	void WriteSuccess(const char* message, const char* message2, bool condition) {}
	void StartLog(const char* message) {}
	void StartLog(const char* message, const char* message2) {}
	void EndLog(bool condition, const char *errorMessage) {}

    BinaryLogItem* WriteFix(int messageIndex, int bufferIndex, int itemIndex) { return NULL; }
    BinaryLogItem* WriteFast(int messageIndex, int bufferIndex, int itemIndex, int size) { return NULL; }
    void Write(int messageCode, int messageCode2) { }
    void Write(int messageCode) { }
    void WriteLine(int messageCode) { }
    void WriteSuccess(int messageCode, bool condition) { }
    void WriteSuccess(int messageCode, int messageCode2, bool condition) { }
    void StartLog(int messageCode) { }
    void StartLog(int messageCode, int messageCode2) { }
    void EndLog(bool condition, int messageCode) { }
    void EndLogErrNo(bool condition, int errno) { }
    void Print() { }
};

class DefaultLogManager {
public:
	static LogManager *Default;
};
