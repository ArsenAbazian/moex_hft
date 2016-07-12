#include "UTCTimeConverterTester.h"
#include "UTCTimeConverter.h"
#include <stdlib.h>
#include <stdio.h>


UTCTimeConverterTester::UTCTimeConverterTester()
{
}


UTCTimeConverterTester::~UTCTimeConverterTester()
{
}

void UTCTimeConverterTester::Test() { 
	UTCTimeConverter conv;
	
	char buf[100];
	SYSTEMTIME st, stNew;
	for (int i = 0; i < 100000; i++) {
		st.wYear = rand() % 9999;
		st.wMonth = rand() % 11 + 1;
		st.wDay = rand() % 27 + 1;
		st.wHour = rand() % 23;
		st.wMinute = rand() % 59;
		st.wSecond = rand() % 59;
		st.wMilliseconds = rand() % 999;

		buf[conv.ToString(buf, &st)] = '\0';
		conv.FromString(buf, &stNew, '\0');

		if (st.wYear != stNew.wYear ||
			st.wMonth != stNew.wMonth ||
			st.wDay != stNew.wDay ||
			st.wHour != stNew.wHour ||
			st.wMinute != stNew.wMinute ||
			st.wSecond != stNew.wSecond ||
			st.wMilliseconds != stNew.wMilliseconds) {
			
			printf("UTCTimeConverter::FromString: expected %d%d%d-%2d:%2d:%2d.%3d but was %d%d%d-%2d:%2d:%2d.%3d",
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
				stNew.wYear, stNew.wMonth, stNew.wDay, stNew.wHour, stNew.wMinute, stNew.wSecond, stNew.wMilliseconds);
			throw;
		}
	}

	for (int i = 0; i < 100000; i++) {
		st.wYear = rand() % 9999;
		st.wMonth = rand() % 11 + 1;
		st.wDay = rand() % 27 + 1;

		buf[conv.ToDateString(buf, &st)] = '\0';
		conv.FromDateString(buf, &stNew);

		if (st.wYear != stNew.wYear ||
			st.wMonth != stNew.wMonth ||
			st.wDay != stNew.wDay) {

			printf("UTCTimeConverter::FromString: expected %d%d%d but was %d%d%d",
				st.wYear, st.wMonth, st.wDay,
				stNew.wYear, stNew.wMonth);
			throw;
		}
	}
}
