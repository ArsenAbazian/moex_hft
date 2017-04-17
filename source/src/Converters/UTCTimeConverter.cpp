#include "../../include/Converters/ItoaConverter.h"
#include "../../include/Converters/UTCTimeConverter.h"
#include <memory>
#include "../../include/Managers/DebugInfoManager.h"

CharVector4 *UTCTimeConverter::years = NULL;
CharVector2 *UTCTimeConverter::hours = NULL;
CharVector3 *UTCTimeConverter::miliseconds = NULL;


UTCTimeConverter::UTCTimeConverter() {
	if (UTCTimeConverter::years == NULL)
		Initialize();
	memset(&(this->currentTime), 0, sizeof(SYSTEMTIME));
	this->currentMs = 0;
	this->tval = new struct timeval;
	this->calendarTime = new struct tm;
	this->converter = new ItoaConverter();
}


UTCTimeConverter::~UTCTimeConverter()
{
}

void UTCTimeConverter::Initialize() { 
	UTCTimeConverter::years = new CharVector4[10000];
	UTCTimeConverter::hours = new CharVector2[61];
	UTCTimeConverter::miliseconds = new CharVector3[1000];

	CharVector4 year; Init(year, D0, D0, D0, D0);
	CharVector2 hour; Init(hour, D0, D0);
	CharVector3 milisec; Init(milisec, D0, D0, D0);

	for (int i = 0; i < 10000; i++) { 
		Copy4(UTCTimeConverter::years[i], year);
		for (int j = 3; j >= 0; j--) {
			if (year[j] < D9) {
				year[j] ++;
				break;
			}
			year[j] = D0;
		}
	}

	for (int i = 0; i < 61; i++) {
		Copy2(UTCTimeConverter::hours[i], hour);
		for (int j = 1; j >= 0; j--) {
			if (hour[j] < D9) {
				hour[j] ++;
				break;
			}
			hour[j] = D0;
		}
	}

	for (int i = 0; i < 1000; i++) {
		Copy3(UTCTimeConverter::miliseconds[i], milisec);
		for (int j = 2; j >= 0; j--) {
			if (milisec[j] < D9) {
				milisec[j] ++;
				break;
			}
			milisec[j] = D0;
		}
	}
	DebugInfoManager::Default->PrintMemoryInfo("After UTCTimeConverter::Initialize");
}

