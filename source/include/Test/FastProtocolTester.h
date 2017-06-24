#pragma once
#include "../Settings.h"
#include "../Fast/FastProtocolManager.h"

#ifdef TEST
class FastProtocolTester {
    FastProtocolManager *manager;
public:
    FastProtocolTester();
    ~FastProtocolTester();

    bool CompareStrings(char* str1, const char *str2);
    void TestMessages();

    void TestStringCopy();

    void TestReadUInt64_Optional(bool use_bmi);
    void TestReadUInt64_Mandatory(bool use_bmi);
    void TestReadInt64_Optional(bool use_bmi);
    void TestReadInt64_Mandatory(bool use_bmi);

    void TestReadDecimal_Optional();
    void TestReadDecimal_Mandatory();
    void TestReadInt32_Optional(bool use_bmi);
    void TestReadInt32_Optional_Predict1(bool use_bmi);
    void TestReadInt32_Optional2(bool use_bmi);
    void TestReadInt32_Mandatory(bool use_bmi);
    void TestReadInt32_Mandatory_Predict1(bool use_bmi);
    void TestReadUInt32_Optional(bool use_bmi);
    void TestReadUInt32_Optional2(bool use_bmi);
    void TestReadUInt32_Optional_Fixed1(bool use_bmi);
    void TestReadUInt32_Mandatory(bool use_bmi);
    void TestReadUInt32_Mandatory_Predict1(bool use_bmi);
    void TestReadString_Optional();
    void TestReadString_Mandatory();

    void TestReadByteVector_Optional();
    void TestReadByteVector_Mandatory();

    void TestMessageSequenceNumber();
    void TestReadInt64();
    void TestReadUInt64();
    void TestParsePresenceMap();
    void TestPerformance();
    void TestSkipToNextField();

    void Test();
};
#endif
