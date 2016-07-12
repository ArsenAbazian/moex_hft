#pragma once
#include <memory.h>

#define ITOA_LIST_COUNT 100000
#define D0 '0'
#define D1 '1'
#define D2 '2'
#define D3 '3'
#define D4 '4'
#define D5 '5'
#define D6 '6'
#define D7 '7'
#define D8 '8'
#define D9 '9'

typedef char DigitString[6];
typedef char DigitString4[4];

class ItoaConverter
{
	static DigitString	*digitStringList;
	static DigitString4 *digitString4List;
	static DigitString4 *digitString4List2;
	static DigitString4 *digitString4List3;
	static DigitString4 *digitString4List4;
	static int			*digitCount;
	static int			*charDigit3;
	static int			*charDigit2;

	inline void Init(DigitString s, char d0, char d1, char d2, char d3, char d4, char d5) { 
		s[0] = d0;
		s[1] = d1;
		s[2] = d2;
		s[3] = d3;
		s[4] = d4;
		s[5] = d5;
	}
	inline void Copy(DigitString dst, DigitString src) {  memcpy(dst, src, 10);	}
	void Initialize();
	void InitializePositive4DigitMinCount1();
	void InitializePositive4DigitMinCount2();
	void InitializePositive4DigitMinCount3();
	void InitializePositive4DigitMinCount4();
public:
	ItoaConverter();
	~ItoaConverter();
	
	inline int ConvertPositive4DigitVaue(char *buffer, int value) {
		*((int*)buffer) = ((int*)ItoaConverter::digitString4List)[value];
		return ItoaConverter::digitCount[value];
	}
	inline int ConvertPositive4DigitValueMinDigitCount3(char *buffer, int value) { 
		*((int*)buffer) = ((int*)ItoaConverter::digitString4List3)[value];
		return value > 99? ItoaConverter::digitCount[value]: 3;
	}
	inline int ConvertPositive4DigitValueMinDigitCount2(char *buffer, int value) {
		*((int*)buffer) = ((int*)ItoaConverter::digitString4List2)[value];
		return value > 9? ItoaConverter::digitCount[value]: 2;
	}
	inline int ConvertPositive4DigitValueMinDigitCount4(char *buffer, int value) {
		*((int*)buffer) = ((int*)ItoaConverter::digitString4List4)[value];
		return 4;
	}

	inline int Convert4DigitValue(char *buffer, register int value) { 
		if (value < 0) { 
			*buffer = '-'; buffer++;
			value = -value;
			return this->ConvertPositive4DigitVaue(buffer, value) + 1;
		}
		return this->ConvertPositive4DigitVaue(buffer, value);
	}

	inline int Convert4DigitValueMinDigitCount2(char *buffer, register int value) {
		if (value < 0) {
			*buffer = '-'; buffer++;
			value = -value;
			return this->ConvertPositive4DigitValueMinDigitCount2(buffer, value) + 1;
		}
		return this->ConvertPositive4DigitValueMinDigitCount2(buffer, value);
	}

	inline int Convert4DigitValueMinDigitCount3(char *buffer, register int value) {
		if (value < 0) {
			*buffer = '-'; buffer++;
			value = -value;
			return this->ConvertPositive4DigitValueMinDigitCount3(buffer, value) + 1;
		}
		return this->ConvertPositive4DigitValueMinDigitCount3(buffer, value);
	}

	inline int Convert4DigitValueMinDigitCount4(char *buffer, register int value) {
		if (value < 0) {
			*buffer = '-'; buffer++;
			value = -value;
			return this->ConvertPositive4DigitValueMinDigitCount4(buffer, value) + 1;
		}
		return this->ConvertPositive4DigitValueMinDigitCount4(buffer, value);
	}

	inline int ConvertPositive(char *buffer, int value) { 
		int count = 0;
		if (value < 10000)
			return count + ConvertPositive4DigitVaue(buffer, value);
		int value1 = 0;
		int value2 = value;
		if (value >= ITOA_LIST_COUNT) {
			value1 = value / ITOA_LIST_COUNT;
			value2 = value % ITOA_LIST_COUNT;
		}
		int count1 = ItoaConverter::digitCount[value1];
		int count2 = count1 > 0 ? 5 : ItoaConverter::digitCount[value2];
		count += count1 + count2;

		if (count1 > 0) {
			memcpy(buffer, &(this->digitStringList[value1][6 - count1]), count1);
			buffer += count1;
		}
		if (count2 > 0)
			memcpy(buffer, &(this->digitStringList[value2][6 - count2]), count2);
		else if (count == 0) {
			*buffer++ = '0';
			return 1;
		}

		return count;
	}

	inline int Convert(char *buffer, int value) { 
		int count = 0;
		if (value < 0) {
			*buffer++ = '-';
			value = -value;
			count++;
		}
		if (value < 10000)
			return count + ConvertPositive4DigitVaue(buffer, value);
		int value1 = 0;
		int value2 = value;
		if (value >= ITOA_LIST_COUNT) {
			value1 = value / ITOA_LIST_COUNT;
			value2 = value % ITOA_LIST_COUNT;
		}
		int count1 = ItoaConverter::digitCount[value1];
		int count2 = count1 > 0 ? 5 : ItoaConverter::digitCount[value2];
		count += count1 + count2;

		if (count1 > 0) {
			memcpy(buffer, &(this->digitStringList[value1][6 - count1]), count1);
			buffer += count1;
		}
		if (count2 > 0)
			memcpy(buffer, &(this->digitStringList[value2][6 - count2]), count2);
		else if (count == 0) {
			*buffer++ = '0';
			return 1;
		}

		return count;
	}
	inline int Convert(char *buffer, int value, int minDigitCount) { 
		int count = 0;
		if (value < 0) { 
			*buffer++ = '-';
			value = -value;
			count++;
		}
		int value1 = 0; 
		int value2 = value; 
		if (value >= ITOA_LIST_COUNT) { 
			value1 = value / ITOA_LIST_COUNT;
			value2 = value % ITOA_LIST_COUNT;
		}
		int count1 = value1 == 0? 0: ItoaConverter::digitCount[value1];
		int count2 = count1 > 0? 5: ItoaConverter::digitCount[value2];
		count += count1 + count2;

		if (minDigitCount > count) { 
			int addCount = minDigitCount - count;
			memset(buffer, 0x30, addCount);
			buffer += addCount;
			count += addCount;
		}
		if (count1 > 0) {
			memcpy(buffer, &(this->digitStringList[value1][6 - count1]), count1);
			buffer += count1;
		}
		if (count2 > 0)
			memcpy(buffer, &(this->digitStringList[value2][6 - count2]), count2);
		else if (count == 0 && minDigitCount == 0) { 
			*buffer++ = '0';
			return 1;
		}

		return count;
	}
	inline int FromString(char *buffer, int *outValue, char stopSymbol) { 
		char *start = buffer;
		int result = 0;

		if (*buffer == '-') {  // yes stupid but optimized
			buffer++;
			while (*buffer != stopSymbol) {
				result = result * 10 + (*buffer - 0x30);
				buffer++;
			}
			*outValue = -result;
		}
		else {
			while (*buffer != stopSymbol) {
				result = result * 10 + (*buffer - 0x30);
				buffer++;
			}
			*outValue = result;
		}
		return buffer - start;
	}
	inline int From2SymbolUnsigned(char *buffer) {
		return ItoaConverter::charDigit2[((*(int*)buffer) & 0x0000ffff) - 0x00003030];
	}
	inline int From3SymbolUnsigned(char *buffer) {
		return ItoaConverter::charDigit3[((*(int*)buffer) & 0x00ffffff) - 0x00303030];
	}
	inline int From4SymbolUnsigned(char *buffer) { 
		return (int)(*buffer - 0x30) * 1000 + From3SymbolUnsigned(&(buffer[1]));
	}
	inline int FromStringFast(char *buffer, int *outValue, char stopSymbol) { 
		char *start = buffer;
		char *digitStart = buffer;
		int result = 0;

		if (*buffer == '-') { 
			buffer++;
			while (*buffer != stopSymbol) {
				digitStart = buffer;
				buffer++;
				if (*buffer != stopSymbol) {
					buffer++;
					if (*buffer != stopSymbol) {
						buffer++;
						result = result * 1000 + ItoaConverter::charDigit3[((*(int*)digitStart) & 0x00ffffff) - 0x00303030];
					}
					else {
						result = result * 100 + ItoaConverter::charDigit2[((*(int*)digitStart) & 0x0000ffff) - 0x00003030];
					}
				}
				else {
					result = result * 10 + *digitStart - D0;
				}
			}
			*outValue = -result;
		}
		else {
			while (*buffer != stopSymbol) {
				digitStart = buffer;
				buffer++;
				if (*buffer != stopSymbol) {
					buffer++;
					if (*buffer != stopSymbol) { 
						buffer++;
						result = result * 1000 + ItoaConverter::charDigit3[((*(int*)digitStart) & 0x00ffffff) - 0x00303030];
					}
					else { 
						result = result * 100 + ItoaConverter::charDigit2[((*(int*)digitStart) & 0x0000ffff) - 0x00003030];
					}
				}
				else {
					result = result * 10 + *digitStart - D0;
				}
			}
			*outValue = result;
		}
		return buffer - start;
	}
};

