// HftConsole.cpp : Defines the entry point for the console application.
//

#include <Test/HashTableTester.h>
#include "Test/ItoaTester.h"
#include "Test/UTCTimeConverterTester.h"
#include "Test/FastProtocolTester.h"
#include "Test/FixProtocolManagerTester.h"
#include "Test/FeedConnectionTester.h"
#include "Robot.h"

int main(int argc, char** argv)
{
    bool test_itoa = false;
	bool test_ftoa = false;
	bool test_all = false;
	bool test_time = false;
	bool test_fast = false;
	bool test_fix = false;
	bool test_feed = false;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "test_itoa") == 0)
			test_itoa = true;
		if (strcmp(argv[i], "test_ftoa") == 0)
			test_ftoa = true;
		if (strcmp(argv[i], "test_time") == 0)
			test_time = true;
		if (strcmp(argv[i], "test_fast") == 0)
			test_fast = true;
		if(strcmp(argv[i], "test_fix") == 0)
			test_fix = true;
		if(strcmp(argv[i], "test_feed") == 0)
			test_feed = true;
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

	if(test_fix || test_all) {
		FixProtocolManagerTester tester;
		tester.Test();
	}

	if(test_feed || test_all) {
		HashTableTester tester;
		tester.Test();

		FeedConnectionTester tester2;
		tester2.Test();
	}

	if (test_itoa || test_ftoa || test_time || test_all || test_fast || test_fix || test_feed)
		return 1;

	Robot *robot = new Robot();
	robot->Run();
    delete robot;

	DefaultLogManager::Default->Print();
    return 0;
}



