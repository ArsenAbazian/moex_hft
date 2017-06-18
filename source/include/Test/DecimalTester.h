//
// Created by root on 16.10.16.
//

#ifndef HFT_ROBOT_DECIMALTESTER_H
#define HFT_ROBOT_DECIMALTESTER_H

#include "../Settings.h"
#include "../Fix/FixTypes.h"
#include <stdio.h>
#include "../Stopwatch.h"

#ifdef TEST
class DecimalTester {
public:
    void Test() {
        printf("DECIAML Test\n");
        Decimal dec;
        Stopwatch *w = new Stopwatch();

        w->Start();
        for(int i = 0; i < 1000000; i++) {
            double d = i * 0.0000001;
            dec.Mantissa = i;
            dec.Exponent = -7;
            if(d != dec.Calculate())
                throw;
        }
        for(int i = 0; i < 10000000; i+=5) {
            double d = i * 0.00000001;
            dec.Mantissa = i;
            dec.Exponent = -8;
            if(d != dec.Calculate())
                throw;
        }
        for(int i = 0; i < 100000000; i+=53) {
            double d = i * 0.000000001;
            dec.Mantissa = i;
            dec.Exponent = -9;
            if(d != dec.Calculate())
                throw;
        }
        for(int i = 0; i < 10000; i++) {
            double d = i;
            dec.Mantissa = i;
            dec.Exponent = 0;
            if(d != dec.Calculate())
                throw;
        }
        for(int i = 0; i < 10000; i++) {
            double d = i * 10;
            dec.Mantissa = i;
            dec.Exponent = 1;
            if(d != dec.Calculate())
                throw;
        }
    }
};
#endif

#endif //HFT_ROBOT_DECIMALTESTER_H
