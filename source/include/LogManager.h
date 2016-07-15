#pragma once

#include "ConsoleManager.h"

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
	void EndLog(bool condition) { EndLog(condition, NULL); }
	virtual void EndLog(bool condition, char *errorMessage) = 0;
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

	void EndLog(bool condition, char *errorText) { 
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
	void EndLog(bool condition, char *errorMessage) {}
};

class DefaultLogManager {
public:
	static LogManager *Default;
};
