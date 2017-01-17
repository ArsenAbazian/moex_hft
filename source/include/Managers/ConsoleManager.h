#pragma once
#include <stdio.h>
class ConsoleManager
{
public:
	ConsoleManager();
	~ConsoleManager();

	static void WaitEnter() {
		printf("\nPress Enter...\n");
		getchar();
	}

	static char buffer[1024];
	static const char* GetErrorText(int error) {
		return "";
	}

	static void Failed() { }

	static void Write(const char* message) { 
		printf("%s", message);
	}

	static void Write(const char *tabs, const char* message) {
		printf("%s%s", tabs, message);
	}

	static void WriteLine(const char *tabs, const char* message) {
		printf("%s%s\n", tabs, message);
	}

	static void WriteLine(const char* message) { 
		printf("%s\n", message);
	}
};

