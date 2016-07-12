#pragma once
#include "ItoaConverter.h"
#include <math.h>

class DtoaConverter
{
	ItoaConverter	converter;
	
public:
	
	DtoaConverter();
	~DtoaConverter();

	inline int ToString(double value, char *buffer) { 
		char* start = buffer;
		int sign = 1;
		if (value < 0) {
			sign = -1;
			value = -value;
		}
		double intFloat = floor(value);
		double precFloat = value - intFloat;

		int intValue = (int)intFloat;
		int precValue = precFloat * 1000000000.0;

		if (sign == -1) *buffer++ = '-';

		buffer += converter.Convert(buffer, intValue, 0);
		*buffer++ = '.';
		buffer += converter.Convert(buffer, precValue, 0);

		return buffer - start;
	}
};
