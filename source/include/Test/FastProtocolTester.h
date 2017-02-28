#pragma once
#include "Settings.h"

#ifdef TEST
class FastProtocolTester
{
public:
	FastProtocolTester();
	~FastProtocolTester();

	void Test() {
        TestStringCopy();
        TestReadString_Optional();
		TestReadString_Mandatory();
        TestReadByteVector_Optional();
        TestReadByteVector_Mandatory();
        TestReadInt32_Optional();
        TestReadInt32_Mandatory();
        TestReadUInt32_Optional();
		TestReadUInt32_Mandatory();
		TestReadUInt64_Optional();
		TestReadUInt64_Mandatory();
		TestReadInt64_Optional();
		TestReadInt64_Mandatory();
		TestReadDecimal_Optional();
		TestReadDecimal_Mandatory();
		TestMessageSequenceNumber();
		TestParsePresenceMap();
		TestMessages();
	}

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
	void TestReadInt32_Mandatory();
	void TestReadUInt32_Optional();
	void TestReadUInt32_Mandatory();
	void TestReadString_Optional();
	void TestReadString_Mandatory();

	void TestReadByteVector_Optional();
	void TestReadByteVector_Mandatory();

	void TestMessageSequenceNumber();
	void TestReadInt64();
	void TestReadUInt64();
	void TestParsePresenceMap();
};
#endif
