#pragma once
#include "Types.h"
#include "ItoaConverter.h"

typedef  struct _SYSTEMTIME  {
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
}SYSTEMTIME;

#define UTCTimeStampLength (4 + 2 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 3)

typedef char CharVector4[4];
typedef char CharVector2[2];
typedef char CharVector3[3];
class UTCTimeConverter
{
	static CharVector4		*years;
	static CharVector2		*hours;
	static CharVector3		*miliseconds;

	ItoaConverter			*converter;

	inline void Init(CharVector4 v, char p1, char p2, char p3, char p4) { v[0] = p1; v[1] = p2; v[2] = p3; v[3] = p4; }
	inline void Init(CharVector3 v, char p1, char p2, char p3) { v[0] = p1; v[1] = p2; v[2] = p3; }
	inline void Init(CharVector2 v, char p1, char p2) { v[0] = p1; v[1] = p2; }
	inline void Copy4(CharVector4 dst, CharVector4 src) { memcpy(dst, src, 4); }
	inline void Copy2(CharVector2 dst, CharVector2 src) { memcpy(dst, src, 2); }
	inline void Copy3(CharVector3 dst, CharVector3 src) { memcpy(dst, src, 3); }
public:
	UTCTimeConverter();
	~UTCTimeConverter();

	void Initialize();
	inline int ToString(char *buffer, SYSTEMTIME *st) { 

		*((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[st->wYear]));
		buffer += 4;
		
		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wMonth]));
		buffer += 2;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wDay]));
		buffer += 2;

		*buffer = '-';
		buffer++;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wHour]));
		buffer += 2;

		*buffer = ':';
		buffer++;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wMinute]));
		buffer += 2;

		*buffer = ':';
		buffer++;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wSecond]));
		buffer += 2;

		*buffer = '.';
		buffer++;

		char *v = (char*)(UTCTimeConverter::miliseconds + st->wMilliseconds);
		buffer[0] = v[0]; buffer[1] = v[1]; buffer[2] = v[2]; //TODO Optimize

		//     y   m   d   -   h   :   m   :   s   .  ms
		return 4 + 2 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 3;
	}

	inline int ToDateString(char *buffer, SYSTEMTIME *st) { 
		*((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[st->wYear]));
		buffer += 4;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wMonth]));
		buffer += 2;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[st->wDay]));
		buffer += 2;

		//     y   m   d 
		return 4 + 2 + 2;
	}

	inline int ToDateString(char *buffer, int year, int month, int day) {
		*((DWORD*)buffer) = *((DWORD*)&(UTCTimeConverter::years[year]));
		buffer += 4;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[month]));
		buffer += 2;

		*((WORD*)buffer) = *((WORD*)&(UTCTimeConverter::hours[day]));
		buffer += 2;

		//     y   m   d 
		return 4 + 2 + 2;
	}

	inline int FromString(char *buffer, SYSTEMTIME *st, char stopSymbol) {
		char *start = buffer;
		st->wYear = this->converter->From4SymbolUnsigned(buffer);
		buffer += 4;
		st->wMonth = this->converter->From2SymbolUnsigned(buffer);
		buffer += 2;
		st->wDay = this->converter->From2SymbolUnsigned(buffer);
		buffer += 3; 
		st->wHour = this->converter->From2SymbolUnsigned(buffer);
		buffer += 3;
		st->wMinute = this->converter->From2SymbolUnsigned(buffer);
		buffer += 3;
		st->wSecond = this->converter->From2SymbolUnsigned(buffer);
		buffer += 3;
		int outValue;
		int len = this->converter->FromStringFast(buffer, &outValue, stopSymbol);
		st->wMilliseconds = outValue;
		return buffer - start + len;
	}

	inline int FromDateString(char *buffer, SYSTEMTIME *st) { 
		st->wYear = this->converter->From4SymbolUnsigned(buffer);
		buffer += 4;
		st->wMonth = this->converter->From2SymbolUnsigned(buffer);
		buffer += 2;
		st->wDay = this->converter->From2SymbolUnsigned(buffer);
		return 8;
	}
};

