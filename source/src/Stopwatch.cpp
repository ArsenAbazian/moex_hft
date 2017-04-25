//
// Created by root on 26.07.16.
//

#include "../include/Stopwatch.h"

__syscall_slong_t  Stopwatch::ElapsedMicroseconds = 0;
Stopwatch* Stopwatch::Default = new Stopwatch();