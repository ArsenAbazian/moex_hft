#include "ItoaConverter.h"


DigitString* ItoaConverter::digitStringList = NULL;
DigitString4* ItoaConverter::digitString4List = NULL;
DigitString4* ItoaConverter::digitString4List2 = NULL;
DigitString4* ItoaConverter::digitString4List3 = NULL;
DigitString4* ItoaConverter::digitString4List4 = NULL;
int* ItoaConverter::digitCount = NULL;
int* ItoaConverter::charDigit2 = NULL;
int* ItoaConverter::charDigit3 = NULL;

ItoaConverter::ItoaConverter()
{
	if (ItoaConverter::digitStringList == NULL) {
		Initialize();
	}
}


ItoaConverter::~ItoaConverter()
{
}

void ItoaConverter::InitializePositive4DigitMinCount1() { 
	ItoaConverter::digitString4List = new DigitString4[10000];

	char buffer[4] = {0x30, 0, 0, 0};
    ((int*)ItoaConverter::digitString4List)[0] = *((int*)buffer);

	for (int i = 1; i < 10000; i++) {
		*((int*)buffer) = 0;
		char *digit = buffer;
		bool force = false;
		if (i / 1000 > 0) {
			*digit = i / 1000 + 0x30;
			digit++;
			force = true;
		}
		if ((i % 1000) / 100 > 0 || force) {
			*digit = (i % 1000) / 100 + 0x30;
			digit++;
			force = true;
		}
		if ((i % 100) / 10 > 0 || force) {
			*digit = (i % 100) / 10 + 0x30;
			digit++;
			force = true;
		}
		*digit = (i % 10) + 0x30;
		((int*)ItoaConverter::digitString4List)[i] = *((int*)buffer);
	}
}
void ItoaConverter::InitializePositive4DigitMinCount2() { 
	ItoaConverter::digitString4List2 = new DigitString4[10000];

	char buffer[4] = { 0x30, 0x30, 0, 0};

    ((int*)ItoaConverter::digitString4List2)[0] = *((int*)buffer);
	for (int i = 1; i < 10000; i++) {
		*((int*)buffer) = 0;
		char *digit = buffer;
		bool force = false;
		if (i / 1000 > 0) {
			*digit = i / 1000 + 0x30;
			digit++;
			force = true;
		}
		if ((i % 1000) / 100 > 0 || force) {
			*digit = (i % 1000) / 100 + 0x30;
			digit++;
		}
		*digit = (i % 100) / 10 + 0x30;
		digit++;
		*digit = (i % 10) + 0x30;
		((int*)ItoaConverter::digitString4List2)[i] = *((int*)buffer);
	}
}
void ItoaConverter::InitializePositive4DigitMinCount3() {
	ItoaConverter::digitString4List3 = new DigitString4[10000];

	char buffer[4] = {0x30, 0x30, 0x30, 0};
    ((int*)ItoaConverter::digitString4List3)[0] = *((int*)buffer);

	for (int i = 1; i < 10000; i++) {
		*((int*)buffer) = 0;
		char *digit = buffer;
		if (i / 1000 > 0) {
			*digit = i / 1000 + 0x30;
			digit++;
		}
		*digit = (i % 1000) / 100 + 0x30;
		digit++;
		*digit = (i % 100) / 10 + 0x30;
		digit++;
		*digit = (i % 10) + 0x30;
		((int*)ItoaConverter::digitString4List3)[i] = *((int*)buffer);
	}
}
void ItoaConverter::InitializePositive4DigitMinCount4() {
	ItoaConverter::digitString4List4 = new DigitString4[10000];
	
	char buffer[4];
	for (int i = 0; i < 10000; i++) {
		buffer[0] = i / 1000 + 0x30;
		buffer[1] = (i % 1000) / 100 + 0x30;
		buffer[2] = (i % 100) / 10 + 0x30;
		buffer[3] = (i % 10) + 0x30;
		((int*)ItoaConverter::digitString4List4)[i] = *((int*)buffer);
	}
}

void ItoaConverter::Initialize() {
	ItoaConverter::digitCount = new int[ITOA_LIST_COUNT];
	ItoaConverter::digitStringList = new DigitString[ITOA_LIST_COUNT];


	InitializePositive4DigitMinCount1();
	InitializePositive4DigitMinCount2();
	InitializePositive4DigitMinCount3();
	InitializePositive4DigitMinCount4();
	

	DigitString str; Init(str, D0, D0, D0, D0, D0, D0);
		
	int count = 0;
	for (int i = 0; i < ITOA_LIST_COUNT; i++) {
		Copy(ItoaConverter::digitStringList[i], str);
		ItoaConverter::digitCount[i] = count > 0? count: 1;
		for (int j = 5; j >= 0; j--) {
			if (str[j] < D9) {
				str[j] ++;
				count = count < 6 - j ? 6 - j : count;
				break;
			}
			str[j] = D0;
		}
	}

	int max2DigiValue = 0x3939 + 1;
	int min2DigitValue = 0x3030;

	ItoaConverter::charDigit2 = new int[max2DigiValue - min2DigitValue];
	
	char digit[2] = { 0, 0 };
	int *index = (int*)digit;
	for (int i = 0; i < 100; i++) {
		int iarr = (*index & 0x0000ffff);
		if(iarr	>= max2DigiValue - min2DigitValue)
			throw;
		ItoaConverter::charDigit2[iarr] = ((int)digit[0]) * 10 + digit[1];
		if (digit[0] < 9)
			digit[0] ++;
		else {
			digit[1] ++;
			digit[0] = 0;
			if (digit[1] > 9)
				break;
		}
	}

	char digit3[] = { 0, 0, 0 };
	int max3DigitValue = 0x393939 + 1;
	int min3DigitValue = 0x303030;

	ItoaConverter::charDigit3 = new int[max3DigitValue - min3DigitValue];
	index = (int*)digit3;
	for (int i = 0; i < 1000; i++) {
		int iarr = (*index & 0x00ffffff);
		if(iarr >= max3DigitValue - min3DigitValue)
			throw;
		ItoaConverter::charDigit3[iarr] = ((int)digit3[0]) * 100 + ((int)digit3[1]) * 10 + digit3[2];
		if (digit3[0] < 9) {
			digit3[0]++;
		}
		else {
			digit3[0] = 0;
			if (digit3[1] < 9) {
				digit3[1]++;
			}
			else {
				digit3[0] = 0;
				digit3[1] = 0;
				digit3[2]++;
				if (digit3[2] > 9)
					break;
			}
		}
	}
}
