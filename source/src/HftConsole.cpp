// HftConsole.cpp : Defines the entry point for the console application.
//
#include "../include/Settings.h"
#ifdef TEST
#include "../include/Test/ItoaTester.h"
#include "../include/Test/UTCTimeConverterTester.h"
#include "../include/Test/FastProtocolTester.h"
#include "../include/Test/FixProtocolManagerTester.h"
#include "../include/Test/FeedConnectionTester.h"
#include "../include/Test/DecimalTester.h"
#endif //TEST

#include "../include/Robot.h"

int main(int argc, char** argv) {

    bool test_itoa = false;
	bool test_ftoa = false;
	bool test_decimal = false;
	bool test_all = false;
	bool test_time = false;
	bool test_fast = false;
	bool test_fix = false;
	bool test_feed = false;
    bool decode_forts = false;
    bool decode_asts = false;
    const char *decode_string = 0;

	for (int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "test_itoa") == 0)
            test_itoa = true;
        if(strcmp(argv[i], "test_ftoa") == 0)
            test_ftoa = true;
        if(strcmp(argv[i], "test_time") == 0)
            test_time = true;
        if(strcmp(argv[i], "test_fast") == 0)
            test_fast = true;
        if(strcmp(argv[i], "test_fix") == 0)
            test_fix = true;
        if(strcmp(argv[i], "test_feed") == 0)
            test_feed = true;
        if(strcmp(argv[i], "test_decimal") == 0)
            test_decimal = true;
        if(strcmp(argv[i], "test_all") == 0)
            test_all = true;
        if(strcmp(argv[i], "decode_forts") == 0) {
            decode_forts = true;
            decode_string = argv[i+1];
        }
        if(strcmp(argv[i], "decode_asts") == 0) {
            decode_asts = true;
            decode_string = argv[i+1];
        }
    }

    if(decode_forts || decode_asts) {
        FastProtocolManager *manager = new FastProtocolManager(AstsObjectsAllocationInfo::Default, FortsObjectsAllocationInfo::Default);
        int sizeOut = 0;
        unsigned char *msg = DebugInfoManager::Default->StringToBinary(decode_string, &sizeOut);
        manager->SetNewBuffer(msg, sizeOut);
        manager->ReadMsgSeqNumber();
        if(decode_forts) {
            manager->DecodeForts();
            manager->PrintForts();
        }
        else {
            manager->DecodeAsts();
            manager->PrintAsts();
        }
        delete manager;
        delete[] msg;
        return 0;
    }

    bool hasTest = test_itoa || test_ftoa || test_time || test_all || test_fast || test_fix || test_feed || test_decimal;
#ifndef TEST
    if(hasTest) {
        printf("you are trying to run robot in 'test' mode, but TEST macros is not defined. please uncomment TEST macro in file Settings.h\n!!!");
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

    DebugInfoManager::Default->PrintMemoryInfo("Before Robot::Robot");
	Robot *robot = new Robot();
	robot->AllowFortsMarket(false);
	robot->AllowFondMarket(false);
	robot->AllowCurrMarket(true);
	robot->AllowFutures(false);
	robot->AllowOptions(false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook1, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook5, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook20, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook50, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidFutTrades, true     );
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook1, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook5, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook20, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook50, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOptTrades, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOtcTrades, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidOtcIssues, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidNews, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidNewsSkrin, false);
	robot->AllowMarketDataGroup(MarketDataGroupId::mdgidIndex, false);
	robot->Run();
    delete robot;

	DefaultLogManager::Default->Print();

	return 0;
#endif
}



