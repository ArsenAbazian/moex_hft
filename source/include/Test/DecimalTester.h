//
// Created by root on 16.10.16.
//

#ifndef HFT_ROBOT_DECIMALTESTER_H
#define HFT_ROBOT_DECIMALTESTER_H

#include "../FixTypes.h"

class DecimalTester {
public:
    void Test() {
        Decimal dec;
        for(double d = 0.0; d < 1.0; d += 0.0000001) {
            dec.Mantissa = (INT64)(d * 10000000.0 + 0.5);
            dec.Exponent = -7;

            double d2 = dec.Calculate();
            if(d != d2)
                throw;
        }
    }
};

#endif //HFT_ROBOT_DECIMALTESTER_H
