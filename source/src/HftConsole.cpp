// HftConsole.cpp : Defines the entry point for the console application.
//
#include "Types.h"
#ifdef TEST
#include "Test/ItoaTester.h"
#include "Test/UTCTimeConverterTester.h"
#include "Test/FastProtocolTester.h"
#include "Test/FixProtocolManagerTester.h"
#include "Test/FeedConnectionTester.h"
#include "Test/DecimalTester.h"
#endif //TEST

#include "Robot.h"

int main(int argc, char** argv) {

    bool test_itoa = false;
	bool test_ftoa = false;
	bool test_decimal = false;
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
		if(strcmp(argv[i], "test_decimal") == 0)
			test_decimal = true;
		if (strcmp(argv[i], "test_all") == 0)
			test_all = true;
	}

    bool hasTest = test_itoa || test_ftoa || test_time || test_all || test_fast || test_fix || test_feed || test_decimal;
#ifndef TEST
    if(hasTest) {
        printf("you are trying to run robot in 'test' mode, but TEST macros is not defined. please uncomment TEST macro in file Types.h\n!!!");
        return 0;
    }
#endif
#ifdef TEST
	if (test_itoa || test_all) {
		ItoaTester tester;
		tester.Test();
	}

	if(test_decimal || test_all) {
		DecimalTester tester;
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
		FeedConnectionTester tester2;
		tester2.Test();
	}

	if (test_itoa || test_ftoa || test_time || test_all || test_fast || test_fix || test_feed || test_decimal)
		return 1;

    printf("you are trying to run robot in 'full work' mode, but TEST macros is defined. please remove TEST macro in file Types.h\n!!!");
	return 0;
#else

	Robot *robot = new Robot();
	robot->Run();
    delete robot;

	DefaultLogManager::Default->Print();
    return 0;
#endif
}



