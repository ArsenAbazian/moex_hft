#include "../../include/Converters/ItoaConverter.h"
#include "../../include/Test/ItoaTester.h"
#include <stdio.h>

#ifdef TEST
ItoaTester::ItoaTester()
{
}


ItoaTester::~ItoaTester()
{
}

void ItoaTester::Test() { 

	ItoaConverter conv;

	char buf[100];
	int newValue, newValueFast;
		
	for (int i = 0; i < 1000; i++) { 
		buf[conv.Convert(buf, i, 3)] = '\0';
		newValue = conv.From3SymbolUnsigned(buf);
		if (newValue != i) {
			printf("print with 3 m_symbols: expected %d but was %d", i, newValue);
			throw;
		}
	}
	
	for (int i = 0; i < 10000000; i++) { 
		buf[conv.Convert(buf, i, 0)] = '\0';
		conv.FromString(buf, &newValue, '\0');
		conv.FromStringFast(buf, &newValueFast, '\0');
		if (newValue != i) { 
			printf("FromString: expected %d but actual %d\n", i, newValue);
			throw;
		}
		if (newValueFast != i) {
			printf("FromStringFast: expected %d but actual %d\n", i, newValueFast);
			throw;
		}
	}

	for (int i = 0; i > -10000000; i--) {
		buf[conv.Convert(buf, i, 0)] = '\0';
		conv.FromString(buf, &newValue, '\0');
		conv.FromStringFast(buf, &newValueFast, '\0');
		if (newValue != i) {
			printf("FromString: expected %d but actual %d\n", i, newValue);
			throw;
		}
		if (newValueFast != i) {
			printf("FromStringFast: expected %d but actual %d\n", i, newValueFast);
			throw;
		}
	}

	for (int i = 0; i < 100; i++) { 
		conv.Convert(buf, i, 2);
		newValue = conv.From2SymbolUnsigned(buf);
		if (newValue != i) {
			printf("From2SymbolUnsigned: expected %d but actual %d\n", i, newValue);
			throw;
		}
	}

	for (int i = 0; i < 1000; i++) {
		conv.Convert(buf, i, 3);
		newValue = conv.From3SymbolUnsigned(buf);
		if (newValue != i) {
			printf("From3SymbolUnsigned: expected %d but actual %d\n", i, newValue);
			throw;
		}
	}

	for (int i = 0; i < 10000; i++) {
		conv.Convert(buf, i, 4);
		newValue = conv.From4SymbolUnsigned(buf);
		if (newValue != i) {
			printf("From4SymbolUnsigned: expected %d but actual %d\n", i, newValue);
			throw;
		}
	}

	for (int i = 0; i < 10000; i++) {
		//i = 100;
		buf[conv.ConvertPositive4DigitVaue(buf, i)] = '\0';
		conv.FromStringFast(buf, &newValue, '\0');
		if (newValue != i) {
			printf("ConvertPositive4DigitVaue: expected %d but actual %d\n", i, newValue);
			throw;
		}

		buf[conv.ConvertPositive4DigitValueMinDigitCount2(buf, i)] = '\0';
		conv.FromStringFast(buf, &newValue, '\0');
		if (newValue != i) {
			printf("ConvertPositive4DigitValueMinDigitCount2: expected %d but actual %d\n", i, newValue);
			throw;
		}

		buf[conv.ConvertPositive4DigitValueMinDigitCount3(buf, i)] = '\0';
		conv.FromStringFast(buf, &newValue, '\0');
		if (newValue != i) {
			printf("ConvertPositive4DigitValueMinDigitCount3: expected %d but actual %d\n", i, newValue);
			throw;
		}

		buf[conv.ConvertPositive4DigitValueMinDigitCount4(buf, i)] = '\0';
		conv.FromStringFast(buf, &newValue, '\0');
		if (newValue != i) {
			printf("ConvertPositive4DigitValueMinDigitCount4: expected %d but actual %d\n", i, newValue);
			throw;
		}
	}
}
#endif