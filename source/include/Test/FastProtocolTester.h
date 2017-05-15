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

    void TestReadUInt64_Optional();
    void TestReadUInt64_Mandatory();
    void TestReadInt64_Optional();
    void TestReadInt64_Mandatory();

    void TestReadDecimal_Optional();
    void TestReadDecimal_Mandatory();
    void TestReadInt32_Optional();
    void TestReadInt32_Optional_Predict1();
    void TestReadInt32_Optional2();
    void TestReadInt32_Mandatory();
    void TestReadInt32_Mandatory_Predict1();
    void TestReadUInt32_Optional();
    void TestReadUInt32_Optional2();
    void TestReadUInt32_Optional_Fixed1();
    void TestReadUInt32_Mandatory();
    void TestReadUInt32_Mandatory_Predict1();
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

    void Test() {
        TestPerformance();

        TestReadUInt32_Mandatory();
        TestReadUInt32_Optional();

        TestReadInt32_Mandatory();
        TestReadInt32_Optional();

        TestReadUInt64_Mandatory();
        TestReadUInt64_Optional();

        TestReadInt64_Mandatory();
        TestReadInt64_Optional();

        TestStringCopy();
        TestReadString_Mandatory();
        TestReadString_Optional();
        TestSkipToNextField();

        TestMessages();
        TestReadByteVector_Optional();
        TestReadByteVector_Mandatory();
        TestReadDecimal_Optional();
        TestReadDecimal_Mandatory();
        TestMessageSequenceNumber();
        TestParsePresenceMap();
    }
};
#endif
