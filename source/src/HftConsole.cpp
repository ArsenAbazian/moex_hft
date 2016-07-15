// HftConsole.cpp : Defines the entry point for the console application.
//

#include "ItoaTester.h"
#include "UTCTimeConverterTester.h"
#include "FastProtocolTester.h"
#include "Robot.h"

int main(int argc, char** argv)
{
    bool test_itoa = false;
	bool test_ftoa = false;
	bool test_all = false;
	bool test_time = false;
	bool test_fast = false;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "test_itoa") == 0)
			test_itoa = true;
		if (strcmp(argv[i], "test_ftoa") == 0)
			test_ftoa = true;
		if (strcmp(argv[i], "test_time") == 0)
			test_time = true;
		if (strcmp(argv[i], "test_fast") == 0)
			test_fast = true;
		if (strcmp(argv[i], "test_all") == 0)
			test_all = true;
	}


	if (test_itoa || test_all) {
		ItoaTester tester;
		tester.Test();
	}

	if (test_time || test_all) {
		UTCTimeConverterTester tester;
		tester.Test();
	}

	if (test_fast || test_all) {
		FastProtocolTester tester;
		tester.Test();
	}

	if (test_itoa || test_ftoa || test_time || test_all || test_fast)
		return 1;

	Robot *robot = new Robot();
	robot->Run();
    delete robot;

	/*if (!robot->AddDefaultTestMarkets()) {
		ConsoleManager::WaitEnter();
		return 0;
	}
	if (!robot->AddDefaultTestChannels()) {
		ConsoleManager::WaitEnter();
		return 0;
	}*/

	/*if (!manager->ConnectMarkets()) {
		ConsoleManager::WaitEnter();
		return 0;
	}
	if (!manager->ConnectChannels()) {
		ConsoleManager::WaitEnter();
		return 0;
	}
	
	ConsoleManager::WaitEnter();
	manager->LogonMarkets();
	ConsoleManager::WaitEnter();
	manager->LogoutMarkets();
	ConsoleManager::WaitEnter();
	manager->DisconnectMarkets();*/


	ConsoleManager::WaitEnter();
    return 0;
}



