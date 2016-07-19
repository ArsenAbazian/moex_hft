#pragma once

#include <time.h>
#include <error.h>
#include <string.h>
#include "ConsoleManager.h"
#include "LogErrorMessageCodes.h"

class LogManager
{
public:
	LogManager();
	~LogManager();

	virtual void Write(const char* message) = 0;
	virtual void Write(const char* message, const char* message2) = 0;
	virtual void WriteLine(const char* message) = 0;
	virtual void WriteSuccess(bool condition) = 0;
	virtual void WriteSuccess(const char* message, bool condition) = 0;
	virtual void WriteSuccess(const char* message, const char* message2, bool condition) = 0;
	virtual void StartLog(const char* message) = 0;
	virtual void StartLog(const char* message, const char* message2) = 0;
	virtual void EndLog(bool condition, const char *errorMessage) = 0;
    virtual void EndLog(bool condition, int errno) = 0;

    virtual void Write(LogMessageCode messageCode) = 0;
    virtual void Write(LogMessageCode messageCode, LogMessageCode messageCode2) = 0;
    virtual void WriteLine(LogMessageCode messageCode) = 0;
    virtual void WriteSuccess(LogMessageCode messageCode, bool condition) = 0;
    virtual void WriteSuccess(LogMessageCode messageCode, LogMessageCode messageCode2, bool condition) = 0;
    virtual void StartLog(LogMessageCode messageCode) = 0;
    virtual void StartLog(LogMessageCode messageCode, LogMessageCode messageCode2) = 0;
    virtual void EndLog(bool condition, LogMessageCode errorCode) = 0;

    void EndLog(bool condition) { EndLog(condition, (const char*)NULL); }
};

// Flags
typedef  enum _BinaryLogItemType {
    NodeItem = 0,
    NodeStart = 1,
    NodeEnd = 2
}BinaryLogItemType;

typedef struct _BinaryLogItem {
    struct timespec     m_time;             // timestamp DO NOT MOVE THIS FIELD!!!!!
    LogMessageCode      m_message;          // char message code - optimize - do not copy string - usually name of object
    LogMessageCode      m_message2;         // char message code2 - usually - method name
    BinaryLogItemType   m_type;             // by default (do not set) is NodeItem
    int                 m_bufferIndex;      // for fix and fast protocol - buffer index
    int                 m_bufferStart;      // for fix and fast protocol - message start index in buffer
    int                 m_bytesCount;       // for fix and fast protocol - bytes count;
    int                 m_errno;            // error number
    bool                m_result;           // method result - fail or success
}BinaryLogItem;

class BinaryLogManager : public LogManager {
    BinaryLogItem       *m_stack[256];
    int                 m_stackTop;

    BinaryLogItem       *m_items;
    const int           m_itemsCount = 200000;  // set 200000 for a while
    int                 m_itemIndex;

    BinaryLogManager() {
        this->m_items = new BinaryLogItem[this->m_itemsCount];
        this->m_itemIndex = 0;
        this->m_stackTop = 0;
    }
    ~BinaryLogManager() {
        delete[] this->m_items;
    }

    inline void Write(LogMessageCode messageCode, LogMessageCode messageCode2) {
        BinaryLogItem *item = &(this->m_items[this->m_itemIndex]);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, (struct timespec*)item);
        item->m_message = messageCode;
        item->m_message2 = messageCode2;

        this->m_itemIndex++;
    }
    inline void Write(LogMessageCode messageCode) {
        BinaryLogItem *item = &(this->m_items[this->m_itemIndex]);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, (struct timespec*)item);
        item->m_message = messageCode;

        this->m_itemIndex++;
    }
    inline void WriteLine(LogMessageCode messageCode) {
        Write(messageCode);
    }
    inline void WriteSuccess(bool condition) {

    }
    inline void WriteSuccess(LogMessageCode messageCode, bool condition) {

    }
    inline void WriteSuccess(LogMessageCode messageCode, LogMessageCode messageCode2, bool condition) {

    }
    inline void StartLog(LogMessageCode messageCode) {

    }
    inline void StartLog(LogMessageCode messageCode, LogMessageCode messageCode2) {

    }
    inline void EndLog(bool condition, LogMessageCode errorCode) {

    }
    inline void EndLog(bool condition, int errno) {

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
        throw;
    }
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

public:
	ConsoleLogManager() { 
		this->messageIndex = -1;
		this->tabs[0] = '\0';
		this->tabsCount = 0;
		this->shouldStartNewLine = false;
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
    void EndLog(bool condition, int errno) {
        EndLog(condition, strerror(errno));
    }

    void Write(LogMessageCode messageCode, LogMessageCode messageCode2) {
        throw;
    }
    void Write(LogMessageCode messageCode) {
        throw;
    }
    void WriteLine(LogMessageCode messageCode) {
        throw;
    }
    void WriteSuccess(LogMessageCode messageCode, bool condition) {
        throw;
    }
    void WriteSuccess(LogMessageCode messageCode, LogMessageCode messageCode2, bool condition) {
        throw;
    }
    void StartLog(LogMessageCode messageCode) {
        throw;
    }
    void StartLog(LogMessageCode messageCode, LogMessageCode messageCode2) {
        throw;
    }
    void EndLog(bool condition, LogMessageCode errorCode) {
        throw;
    }
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

    void Write(LogMessageCode messageCode, LogMessageCode messageCode2) { }
    void Write(LogMessageCode messageCode) { }
    void WriteLine(LogMessageCode messageCode) { }
    void WriteSuccess(LogMessageCode messageCode, bool condition) { }
    void WriteSuccess(LogMessageCode messageCode, LogMessageCode messageCode2, bool condition) { }
    void StartLog(LogMessageCode messageCode) { }
    void StartLog(LogMessageCode messageCode, LogMessageCode messageCode2) { }
    void EndLog(bool condition, LogMessageCode errorCode) { }
    void EndLog(bool condition, int errno) { }
};

class DefaultLogManager {
public:
	static LogManager *Default;
};
