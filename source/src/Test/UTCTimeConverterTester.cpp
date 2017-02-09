#include "Test/UTCTimeConverterTester.h"
#include "Converters/UTCTimeConverter.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef TEST

UTCTimeConverterTester::UTCTimeConverterTester()
{
}


UTCTimeConverterTester::~UTCTimeConverterTester()
{
}

void UTCTimeConverterTester::Test() { 
	UTCTimeConverter conv;
    SYSTEMTIME st, stNew;
    char buf[100];

    buf[conv.GetCurrentTimeString(buf)] = '\0';
    printf("today is  (in UTC) %s\n", buf);
    if(buf[8] != '-' || buf[11] != ':' || buf[14] != ':' || buf[17] != '.')
        throw;

    printf("checking years.\n");
    for(int i = 0; i < 9999; i++) {
        st.wYear = i;
        st.wMonth = 0;
        st.wDay = 0;
        st.wHour = 0;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = 0;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
        if(buf[8] != '-' || buf[11] != ':' || buf[14] != ':' || buf[17] != '.')
            throw;
    }

    printf("checking months.\n");
    for(int i = 1; i < 13; i++) {
        st.wYear = 2016;
        st.wMonth = i;
        st.wDay = 0;
        st.wHour = 0;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = 0;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
    }

    printf("checking days.\n");
    for(int i = 1; i < 31; i++) {
        st.wYear = 2016;
        st.wMonth = 1;
        st.wDay = i;
        st.wHour = 0;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = 0;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
    }

    printf("checking hours.\n");
    for(int i = 0; i < 24; i++) {
        st.wYear = 2016;
        st.wMonth = 1;
        st.wDay = 1;
        st.wHour = i;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = 0;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
    }

    printf("checking minutes.\n");
    for(int i = 0; i < 60; i++) {
        st.wYear = 2016;
        st.wMonth = 1;
        st.wDay = 1;
        st.wHour = 0;
        st.wMinute = i;
        st.wSecond = 0;
        st.wMilliseconds = 0;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
    }

    printf("checking seconds.\n");
    for(int i = 0; i < 60; i++) {
        st.wYear = 2016;
        st.wMonth = 1;
        st.wDay = 1;
        st.wHour = i;
        st.wMinute = 0;
        st.wSecond = i;
        st.wMilliseconds = 0;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
    }

    printf("checking milliseconds.\n");
    for(int i = 0; i < 1000; i++) {
        st.wYear = 2016;
        st.wMonth = 1;
        st.wDay = 1;
        st.wHour = 0;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = i;

        buf[conv.ToString(buf, &st)] = '\0';
        conv.FromString(buf, &stNew, '\0');

        if (st.wYear != stNew.wYear || st.wMonth != stNew.wMonth || st.wDay != stNew.wDay ||
            st.wHour != stNew.wHour || st.wMinute != stNew.wMinute || st.wSecond != stNew.wSecond ||
            st.wMilliseconds != stNew.wMilliseconds) {
            throw;
        }
    }



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
		buf[conv.GetCurrentTimeString(buf)] = '\0';
		conv.FromString(buf, &stNew, '\0');

		if (conv.CalendarTime()->tm_year != stNew.wYear ||
				conv.CalendarTime()->tm_mon != stNew.wMonth ||
				conv.CalendarTime()->tm_mday != stNew.wDay ||
				conv.CalendarTime()->tm_hour != stNew.wHour ||
				conv.CalendarTime()->tm_min != stNew.wMinute ||
				conv.CalendarTime()->tm_sec != stNew.wSecond ||
			conv.TimeVal()->tv_usec / 1000 != stNew.wMilliseconds) {

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

			printf("UTCTimeConverter::FromString: expected %u%u%u but was %u%u%u",
				st.wYear, st.wMonth, st.wDay,
				stNew.wYear, stNew.wMonth, stNew.wDay);
			throw;
		}
	}
}

#endif //TEST