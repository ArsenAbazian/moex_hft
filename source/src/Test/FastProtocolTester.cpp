#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include <limits.h>
#include "../../include/Fast/FastProtocolManager.h"
#include "../../include/Test/FastProtocolTester.h"
#include <sys/time.h>
#include "../../include/Lib/StringIdComparer.h"
#include "../../include/Stopwatch.h"
#include "../../include/Feeds/FeedTypes.h"
#include "../../include/Managers/DebugInfoManager.h"

#ifdef TEST
FastProtocolTester::FastProtocolTester() {
    this->manager = new FastProtocolManager(new AstsObjectsAllocationInfo(128), new FortsObjectsAllocationInfo(128));
}


FastProtocolTester::~FastProtocolTester() {
    delete this->manager;
}

void FastProtocolTester::TestSkipToNextField() {
    unsigned char data[16];
    data[0] = 0xff;

    this->manager->SetNewBuffer(data, 16);
    this->manager->ResetBuffer();
    this->manager->SkipToNextField();
    if(this->manager->MessageLength() != 1)
        throw;

    for(int i = 1; i < 16; i++) {
        data[i] = 0xff;
        data[i - 1] = (unsigned char)(rand() & 0x7f);
        this->manager->ResetBuffer();
        this->manager->SkipToNextField();
        if(this->manager->MessageLength() != i + 1)
            throw;
    }

    Stopwatch *w = new Stopwatch();
    w->Start();
    for(int i = 1; i < 16; i++) {
        data[i] = 0xff;
        data[i - 1] = (unsigned char)(rand() & 0x7f);
        w->Reset();
        for(int j = 0; j < 10000000; j++) {
            this->manager->ResetBuffer();
            this->manager->SkipToNextField();
        }
        time_t mic = w->ElapsedNanosecondsSlow();

        w->Reset();
        for(int j = 0; j < 10000000; j++) {
            this->manager->ResetBuffer();
            this->manager->SkipToNextFieldSlow();
        }
        time_t mic2 = w->ElapsedNanosecondsSlow();

        printf("%d bytes fast = %" PRIu64 " slow = %" PRIu64 "\n", i, mic, mic2);
    }
}

void FastProtocolTester::TestPerformance() {
    /*
    unsigned char** data = new unsigned char*[1024 * 1024];
    for(int i = 0; i < 1024 * 1024; i++) {
        data[i] = new unsigned char[12];
        this->manager->SetNewBuffer(data[i], 12);
        this->manager->WriteUInt32_Optional(i);
    }

    UINT32 value;
    Stopwatch *w = new Stopwatch();

    w->Start();
    for(int j = 0; j < 400; j++) {
        for(int i = 0; i < 1024 * 1024; i++) {
            this->manager->SetNewBuffer(data[i], 12);
            if(!this->manager->CheckProcessNullUInt32())
                value = this->manager->ReadUInt32_Optional();
        }
    }
    time_t t2 = w->ElapsedNanosecondsSlow();
    w->Stop();
    printf("ReadUInt32_Optional() = %" PRIu64 " ns = %" PRIu64 " mcs\n", t2, t2 / 1000);

    w->Start();
    for(int j = 0; j < 400; j++) {
        for(int i = 0; i < 1024 * 1024; i++) {
            this->manager->SetNewBuffer(data[i], 12);
            this->manager->ReadUInt32_Optional(&value);
        }
    }
    time_t t1 = w->ElapsedNanosecondsSlow();
    w->Stop();
    printf("ReadUInt32_Optional(UINT32*) = %" PRIu64 " ns = %" PRIu64 " mcs\n", t1, t1 / 1000);


    w->Start();
    for(int j = 0; j < 400; j++) {
        for(int i = 0; i < 1024 * 1024; i++) {
            this->manager->SetNewBuffer(data[i], 12);
            if(!this->manager->CheckProcessNullUInt32())
                value = this->manager->ReadUInt32_Optional();
        }
    }
    t2 = w->ElapsedNanosecondsSlow();
    w->Stop();
    printf("ReadUInt32_Optional() = %" PRIu64 " ns = %" PRIu64 " mcs\n", t2, t2 / 1000);

    w->Start();
    for(int j = 0; j < 400; j++) {
        for(int i = 0; i < 1024 * 1024; i++) {
            this->manager->SetNewBuffer(data[i], 12);
            this->manager->ReadUInt32_Optional(&value);
        }
    }
    t1 = w->ElapsedNanosecondsSlow();
    w->Stop();
    printf("ReadUInt32_Optional(UINT32*) = %" PRIu64 " ns = %" PRIu64 " mcs\n", t1, t1 / 1000);
    */
    /*
    const char **snap = new const char*[25] {
            "01 00 00 00 c0 8d 81 23 6a 19 6f 24 1f 43 f8 80 01 26 8b 97 57 42 b5 19 4a d6 80 80 8b b2 48 f2 14 18 01 92 80 fb 08 0d 8e 80 24 69 14 7b 3c 31 d8 86 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 08 0d 8e 80 25 57 22 08 5d 21 d0 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 08 10 ee 80 25 57 22 08 5d 21 d0 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 38 55 37 32 cc 80 25 57 22 08 5d 21 d0 15 95 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 08 0f e2 80 25 57 22 08 5d 21 d0 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 08 10 ee 80 25 57 22 08 5d 21 d0 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 22 08 5d 21 d0 3d d2 80 87 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 22 08 5d 21 d0 3d 80 80 8c 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 22 08 5d 21 d0 07 17 fb 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 08 11 82 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 08 11 82 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "02 00 00 00 c0 8d 82 23 6a 19 6f 24 1f 45 a5 80 9f 97 57 42 b5 19 4b 80 80 80 8a b2 48 f2 14 17 7d d4 80 fb 01 1e 58 c0 80 24 62 1b 07 28 36 ac 83 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 01 1e 58 c0 80 25 31 38 20 3e 71 b0 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 01 2c 07 b8 80 25 31 38 20 3e 71 b0 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 0a 72 5a 98 80 25 31 38 20 3e 71 b0 85 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 01 25 2f fc 80 25 31 38 20 3e 71 b0 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 01 2c 07 b8 80 25 31 38 20 3e 71 b0 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 31 38 20 3e 71 b0 83 80 82 80 80 80 80 80 f7 48 f2 80 80 80 80 25 31 38 20 3e 71 b0 83 80 82 80 80 80 80 80 c3 48 f2 80 80 80 80 25 31 38 20 3e 71 b0 01 f5 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 01 27 70 a4 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "03 00 00 00 c0 8d 83 23 6a 19 6f 24 1f 46 c5 80 03 5d 93 97 57 42 b5 19 63 d3 80 80 8b b2 48 f2 14 18 2a ec 80 fb 15 5b 74 6d e0 80 25 51 57 6e 36 4f 84 83 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 15 51 29 70 a0 80 25 57 36 6c 46 64 f4 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 15 64 3f 3e e0 80 25 57 36 6c 46 64 f4 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 01 0f 7a 26 3e 94 80 25 57 36 6c 46 64 f4 33 ea 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 15 59 7a 4e c0 80 25 57 36 6c 46 64 f4 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 15 64 3f 3e e0 80 25 57 36 6c 46 64 f4 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 36 6c 46 64 f4 14 ad 80 af 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 36 6c 46 64 f4 13 d5 80 00 c6 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 36 6c 46 64 f4 06 69 cd 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 15 65 27 20 80 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 15 65 27 20 80 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "04 00 00 00 c0 8d 84 23 6a 19 6f 24 1f 47 fa 80 1e 57 d7 97 57 42 b5 19 4b 86 80 80 8b b2 48 f2 14 18 2c ca 80 fb 02 41 63 c0 80 25 57 25 4f 1e 66 d0 a1 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 02 3e 06 f8 80 25 57 36 5b 29 40 ac 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 02 44 14 98 80 25 57 36 5b 29 40 ac 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 08 1d 68 15 62 bb 80 25 57 36 5b 29 40 ac 05 69 ab 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 02 41 1d 98 80 25 57 36 5b 29 40 ac 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 02 3e 2e 80 80 25 57 36 5b 29 40 ac 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 36 5b 29 40 ac 06 1a d3 80 05 89 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 36 5b 29 40 ac 02 35 b5 80 03 8f 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 36 5b 29 40 ac 14 26 97 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 02 3e 06 f8 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 02 3e 0e e0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "05 00 00 00 c0 8d 85 23 6a 19 6f 24 1f 49 ad 80 0b b2 97 57 42 b5 19 63 d0 80 80 8b b2 48 f2 14 14 6b d2 80 fb 00 4c 23 1e 69 c0 80 1c 07 44 23 38 58 90 83 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 00 4c 23 1e 69 c0 80 25 57 21 79 01 1e c8 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 00 4c 23 1e 69 c0 80 25 57 21 79 01 1e c8 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 13 43 31 f0 80 25 57 21 79 01 1e c8 83 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 00 4c 23 1e 69 c0 80 25 57 21 79 01 1e c8 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 00 4c 23 1e 69 c0 80 25 57 21 79 01 1e c8 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 21 79 01 1e c8 00 d8 80 91 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 21 79 01 1e c8 00 c5 80 8d 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 21 79 01 1e c8 07 81 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 00 4c 2f 14 5a 80 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 00 4c 20 6d 53 80 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "06 00 00 00 c0 8d 86 23 6a 19 6f 24 1f 4a e2 80 05 21 8c 97 57 42 b5 19 4b 89 80 80 8b b2 48 f2 14 18 2c bd 80 fb 04 72 48 19 80 80 25 56 67 0d 33 3a b4 88 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 04 71 0a 7e a0 80 25 57 0d 32 51 1d dc 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 04 77 2a 46 80 80 25 57 0d 32 51 1d dc 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 01 0a 4c 3f 34 c8 80 25 57 0d 32 51 1d dc 01 5c e2 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 04 73 66 71 c0 80 25 57 0d 32 51 1d dc 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 04 74 0b 41 80 80 25 57 0d 32 51 1d dc 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 0d 32 51 1d dc 00 7c f1 80 02 d5 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 0d 32 51 1d dc 01 4c e7 80 04 ba 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 0d 32 51 1d dc 04 55 ab 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 04 73 42 22 80 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 04 73 42 22 80 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "07 00 00 00 c0 8d 87 23 6a 19 6f 24 1f 4c 99 80 2e 1d db 97 57 42 b5 19 4a c4 80 80 8b b2 48 f2 14 18 2c c4 80 fb 15 24 15 6c c0 80 25 56 7a 56 09 1d a0 82 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 15 1b 0e 17 80 80 25 57 36 46 7a 20 9c 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 15 2c 78 72 c0 80 25 57 36 46 7a 20 9c 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 00 42 10 74 6d 24 f8 80 25 57 36 46 7a 20 9c 18 23 b6 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 15 24 0f 5f a0 80 25 57 36 46 7a 20 9c 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 15 2c 23 39 80 80 25 57 36 46 7a 20 9c 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 36 46 7a 20 9c 03 4d da 80 07 a8 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 36 46 7a 20 9c 05 56 8a 80 0d b9 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 36 46 7a 20 9c 2e 36 cf 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 15 2d 54 39 a0 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 15 2d 54 39 a0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "08 00 00 00 c0 8d 88 23 6a 19 6f 24 1f 4d d0 80 aa 97 57 42 b5 19 4a d0 80 80 89 b2 48 f2 14 15 7a c4 80 fb 03 06 50 80 80 1e 41 68 03 3c 4f 9c 82 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 03 06 50 80 80 1e 41 68 03 3c 4f 9c 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 03 18 77 e0 80 1e 41 68 03 3c 4f 9c 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 00 66 ac 80 1e 41 68 03 3c 4f 9c 83 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 03 12 6a c0 80 1e 41 68 03 3c 4f 9c 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 03 18 77 e0 80 1e 41 68 03 3c 4f 9c 80 80 80 80 80 80 80 80 c3 48 f2 80 80 80 80 1e 41 68 03 3c 4f 9c 01 99 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 03 12 6a c0 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 03 12 6a c0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "09 00 00 00 c0 8d 89 23 6a 19 6f 24 1f 4e e7 80 01 53 8d 97 57 42 b5 19 63 c5 80 80 8b b2 48 f2 14 18 18 fd 80 fb 29 16 3d 4a c0 80 25 25 7c 14 53 0a e4 83 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 28 7a 2c 41 80 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 29 32 4e 54 80 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 00 7d 0a 15 4d 96 80 25 57 2e 37 34 69 dc 15 85 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 29 1e 0e 12 c0 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 29 04 6b 24 80 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 2e 37 34 69 dc 02 95 80 9d 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 2e 37 34 69 dc 03 f7 80 9d 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 2e 37 34 69 dc 30 89 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 28 75 4a 14 80 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 28 75 4a 14 80 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "0a 00 00 00 c0 8d 8a 23 6a 19 6f 24 1f 50 9b 80 18 4c bf 97 57 42 b5 18 27 83 80 80 8b b2 48 f2 14 18 2c c9 80 fb 2a 13 34 65 c0 80 25 57 21 78 39 2e c8 82 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 29 6c 27 74 c0 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 2a 2a 26 3d c0 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 29 36 1b 43 1d 99 80 25 57 2e 37 34 69 dc 06 68 90 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 2a 13 34 65 c0 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 29 70 10 18 c0 80 25 57 2e 37 34 69 dc 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 2e 37 34 69 dc 01 23 86 80 0a 99 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 2e 37 34 69 dc 00 6a cc 80 06 88 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 2e 37 34 69 dc 06 36 f3 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 29 6d 21 7d c0 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 29 6d 21 7d c0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "0b 00 00 00 c0 8d 8b 23 6a 19 6f 24 1f 51 d1 80 09 12 a9 97 57 42 b5 19 63 cd 80 80 8b b2 48 f2 14 18 2b f8 80 fb 06 09 43 76 c0 80 25 54 48 39 49 01 d4 90 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 06 05 5b 52 c0 80 25 57 2a 39 4a 17 bc 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 06 0d 32 27 e0 80 25 57 2a 39 4a 17 bc 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 02 1a 53 2f 7f d8 80 25 57 2a 39 4a 17 bc 02 6b c5 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 06 09 43 76 c0 80 25 57 2a 39 4a 17 bc 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 06 06 00 22 80 80 25 57 2a 39 4a 17 bc 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 2a 39 4a 17 bc 01 1e fb 80 08 96 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 2a 39 4a 17 bc 01 3a c8 80 05 ff 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 2a 39 4a 17 bc 05 60 d3 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 06 05 24 5b a0 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 06 05 24 5b a0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "0c 00 00 00 c0 8d 8c 23 6a 19 6f 24 1f 53 88 80 06 63 d5 97 57 42 b5 19 63 ca 80 80 8b b2 48 f2 14 18 24 9e 80 fb 00 4c 3d 3b 61 80 80 25 43 5f 70 76 73 f8 83 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 00 4c 1a 72 5a e0 80 25 57 31 47 05 5e b0 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 00 4c 5b 22 3a a0 80 25 57 31 47 05 5e b0 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 01 13 0e 67 63 f4 80 25 57 31 47 05 5e b0 0f 84 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 00 4c 3f 6c 77 c0 80 25 57 31 47 05 5e b0 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 00 4c 1e 3c 3c c0 80 25 57 31 47 05 5e b0 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 31 47 05 5e b0 0a b7 80 01 82 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 31 47 05 5e b0 0c ec 80 00 fd 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 31 47 05 5e b0 00 5e dd 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 00 4c 14 77 62 c0 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 00 4c 1a 72 5a e0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "0d 00 00 00 c0 8d 8d 23 6a 19 6f 24 1f 54 c1 80 1a 57 a5 97 57 42 b5 19 4a f1 80 80 8b b2 48 f2 14 18 2c cb 80 fb 06 47 c4 80 25 57 2e 1c 30 61 b8 83 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 06 47 c4 80 25 57 36 51 15 3a 8c 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 06 4b 90 80 25 57 36 51 15 3a 8c 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 05 35 79 18 30 cf 80 25 57 36 51 15 3a 8c 01 6f e1 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 06 49 dc 80 25 57 36 51 15 3a 8c 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 06 4a 84 80 25 57 36 51 15 3a 8c 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 36 51 15 3a 8c 00 48 c7 80 00 eb 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 36 51 15 3a 8c 00 7b e8 80 00 f9 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 36 51 15 3a 8c 11 0b e9 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 06 49 dc 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 06 49 dc 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "0e 00 00 00 c0 8d 8e 23 6a 19 6f 24 1f 55 f0 80 02 3d a0 97 57 42 b5 19 4a e8 80 80 8b b2 48 f2 14 18 2c cd 80 fb 07 51 8e 80 25 57 32 40 55 1f 80 95 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 07 4e b0 80 25 57 36 36 0f 1a 90 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 07 53 f6 80 25 57 36 36 0f 1a 90 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 03 04 60 32 0f df 80 25 57 36 36 0f 1a 90 00 73 df 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 07 50 e6 80 25 57 36 36 0f 1a 90 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 07 4f bc 80 25 57 36 36 0f 1a 90 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 36 36 0f 1a 90 2e c8 80 ae 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 36 36 0f 1a 90 3b e9 80 b0 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 36 36 0f 1a 90 12 42 d5 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 07 4e 88 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 07 4d cc 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "0f 00 00 00 c0 8d 8f 23 6a 19 6f 24 1f 57 9e 80 01 0e 93 97 57 42 b5 19 4a cd 80 80 8b b2 48 f2 14 18 23 8c 80 fb 04 55 d4 80 25 3f 51 52 78 6e ec 92 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 04 55 d4 80 25 57 35 5a 2f 11 c0 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 04 56 e0 80 25 57 35 5a 2f 11 c0 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 00 43 44 4f 35 80 80 25 57 35 5a 2f 11 c0 20 ec 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 04 56 90 80 25 57 35 5a 2f 11 c0 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 04 56 d6 80 25 57 35 5a 2f 11 c0 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 35 5a 2f 11 c0 14 b3 80 90 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 35 5a 2f 11 c0 00 59 dc 80 8f 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 35 5a 2f 11 c0 0d 42 d9 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 04 56 b8 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 04 56 c2 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "10 00 00 00 c0 8d 90 23 6a 19 6f 24 1f 58 cc 80 4a 8f 97 57 42 b5 19 4a dc 80 80 8b b2 48 f2 14 18 2c c8 80 fb 06 08 96 80 25 57 20 7b 57 1e 80 10 ce 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 06 06 9c 80 25 57 2e 73 02 4c d4 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 06 08 96 80 25 57 2e 73 02 4c d4 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 01 61 05 39 2c 85 80 25 57 2e 73 02 4c d4 00 54 8e 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 06 07 b2 80 25 57 2e 73 02 4c d4 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 06 06 9c 80 25 57 2e 73 02 4c d4 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 2e 73 02 4c d4 2f f0 80 88 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 2e 73 02 4c d4 31 f2 80 8d 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 2e 73 02 4c d4 08 5a cd 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 06 06 ba 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 06 06 ba 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "11 00 00 00 c0 8d 91 23 6a 19 6f 24 1f 59 fa 80 02 6a ae 97 57 42 b5 19 4a f4 80 80 8b b2 48 f2 14 18 2b f1 80 fb 05 25 46 c8 80 25 54 39 65 32 6b e4 bd 80 80 80 81 80 80 b1 b8 48 f2 80 80 fb 05 23 44 e0 80 25 57 2e 1c 7b 08 b0 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 05 26 6a d0 80 25 57 2e 1c 7b 08 b0 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 01 47 50 22 24 df 80 25 57 2e 1c 7b 08 b0 00 4a b6 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 05 25 36 f8 80 25 57 2e 1c 7b 08 b0 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 05 24 41 e0 80 25 57 2e 1c 7b 08 b0 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 57 2e 1c 7b 08 b0 00 43 e0 80 b2 80 80 80 80 80 f7 48 f2 80 80 80 80 25 57 2e 1c 7b 08 b0 37 a6 80 00 c2 80 80 80 80 80 c3 48 f2 80 80 80 80 25 57 2e 1c 7b 08 b0 16 1b d1 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 05 24 0b 88 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 05 24 0b 88 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "12 00 00 00 c0 8d 92 23 6a 19 6f 24 1f 5b ac 80 18 f6 97 57 42 b5 19 4a fa 80 80 8a b2 48 f2 14 17 7b c3 80 fb 16 42 84 80 24 5d 71 6f 0b 1b b4 98 80 80 80 81 80 80 b2 b8 48 f2 80 80 fb 16 42 84 80 25 45 60 2b 77 23 c8 80 80 80 80 80 80 80 80 b7 48 f2 80 80 fb 16 64 b4 80 25 45 60 2b 77 23 c8 80 80 80 80 80 80 80 80 c2 48 f2 80 80 fe 00 6d 3d 62 87 80 25 45 60 2b 77 23 c8 a9 80 80 80 80 80 80 80 b9 48 f2 80 80 fb 16 50 dc 80 25 45 60 2b 77 23 c8 80 80 80 80 80 80 80 80 b4 48 f2 80 80 fb 16 64 b4 80 25 45 60 2b 77 23 c8 80 80 80 80 80 80 80 80 f6 48 f2 80 80 80 80 25 45 60 2b 77 23 c8 13 cb 80 85 80 80 80 80 80 f7 48 f2 80 80 80 80 25 45 60 2b 77 23 c8 00 75 88 80 87 80 80 80 80 80 c3 48 f2 80 80 80 80 25 45 60 2b 77 23 c8 2d c5 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 16 5e c6 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "13 00 00 00 c0 8d 93 23 6a 19 6f 24 1f 5c cc 80 19 ae 97 57 42 b5 19 63 db 80 80 82 f6 48 f2 80 80 80 80 25 51 58 6d 7c 23 b4 8b 80 82 80 80 80 80 80 f7 48 f2 80 80 80 80 25 51 58 6d 7c 23 b4 8b 80 82 80 80 80 80 80",
            "14 00 00 00 c0 8d 94 23 6a 19 6f 24 1f 5c cc 80 80 97 57 42 b5 19 63 d6 80 80 80",
            "15 00 00 00 c0 8d 95 23 6a 19 6f 24 1f 5c cc 80 0f d6 97 57 42 b5 19 63 c8 80 80 82 f6 48 f2 80 80 80 80 25 25 7b 7f 12 7c bc 86 80 82 80 80 80 80 80 f7 48 f2 80 80 80 80 25 25 7b 7f 12 7c bc 90 80 83 80 80 80 80 80",
            "16 00 00 00 c0 8d 96 23 6a 19 6f 24 1f 5d 86 80 02 e4 97 57 42 b5 19 4a e5 80 80 85 f6 48 f2 80 80 80 80 25 51 0e 69 2e 56 9c 01 99 80 84 80 80 80 80 80 f7 48 f2 80 80 80 80 25 51 0e 69 2e 56 9c 03 91 80 84 80 80 80 80 80 c3 48 f2 80 80 80 80 25 51 0e 69 2e 56 9c 09 bf 80 80 80 80 80 80 80 b5 48 f1 80 80 fb 33 07 94 80 17 61 51 54 48 52 c0 80 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 33 07 94 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "17 00 00 00 c0 8d 97 23 6a 19 6f 24 1f 5d e6 80 8d 97 57 42 b5 19 4a c1 80 80 83 f7 48 f2 80 80 80 80 24 40 12 2c 6b 3a e0 04 f2 80 82 80 80 80 80 80 c3 48 f2 80 80 80 80 24 40 12 2c 6b 3a e0 06 c5 80 80 80 80 80 80 80 b6 48 f1 80 80 fb 04 2c 61 d0 09 4f 0c da 2f 5f 66 7b 1c 40 80 80 80 80 80 80 80 80 80",
            "18 00 00 00 c0 88 98 23 6a 19 6f 24 1f 5e ae 23 6a 19 6f 0a 31 3d e0 23 6a 19 6f 36 7c 22 c0 80 80 85 48 f2 82 c6 84",
            "19 00 00 00 c0 87 99 23 6a 19 6f 24 1f 5f bc 81"
    };

    unsigned char ** packets = new unsigned char*[25];
    int *sizes = new int[25];
    for(int i = 0; i < 25; i++) {
        packets[i] = DebugInfoManager::Default->StringToBinary(snap[i], sizes + i);
    }

    FastProtocolManager *manager = new FastProtocolManager();
    Stopwatch *w = new Stopwatch();

// history
//    decode 100000 time = 1604000000 nanosec or 1604 ms
//    decode 100000 time = 1636000000 nanosec or 1636 ms
//    decode 100000 time = 1456000000 nanosec or 1456 ms
//    decode 100000 time = 1460000000 nanosec or 1460 ms
//    decode 100000 time = 1456000000 nanosec or 1456 ms
//    decode 100000 time = 1428000000 nanosec or 1428 ms
//    decode 100000 time = 1440000000 nanosec or 1440 ms
//    decode 100000 time = 1412000000 nanosec or 1412 ms
//    decode 100000 time = 1508000000 nanosec or 1508 ms
//    decode 100000 time = 1544000000 nanosec or 1544 ms

    UINT64 time = 0;

    for(int t = 0; t < 10; t++) {
        w->Start();
        for (int i = 0; i < 10000; i++) {
            for (int msg = 0; msg < 25; msg++) {
                manager->SetNewBuffer(packets[msg], sizes[msg]);
                manager->SkipMsgSeqNumber();
                manager->DecodeFortsHeader();
                if (manager->TemplateId() == FeedTemplateId::fortsSnapshot) {
                    ((FortsDefaultSnapshotMessageInfo *) manager->DecodeFortsDefaultSnapshotMessage())->Clear();
                }
                if (manager->TemplateId() == FeedTemplateId::fortsTradingSessionStatus) {
                    ((FortsTradingSessionStatusInfo *) manager->DecodeFortsTradingSessionStatus())->Clear();
                }
                if (manager->TemplateId() == FeedTemplateId::fortsSequenceReset) {
                    ((FortsSequenceResetInfo *) manager->DecodeFortsSequenceReset())->Clear();
                }
            }
        }

        time = w->ElapsedNanosecondsSlow();
        printf("decode 100000 time = %" PRIu64 " nanosec or %" PRIu64 " ms\n", time, time / 1000000);
    }

    getchar();*/
}

void FastProtocolTester::TestMessages() {
    unsigned char *message = 0;
    int msgSeqNo = 0;

    message = new unsigned char[103] {
            0xc3    ,0xf6   ,0x02   ,0x00   ,0xc0   ,0x8c   ,0x0b   ,0x6d
            ,0xc3   ,0x23   ,0x6a   ,0x19   ,0x54   ,0x78   ,0x37   ,0x13
            ,0xfb   ,0x82   ,0x82   ,0x82   ,0xb1   ,0x19   ,0x4a   ,0xc4
            ,0x80   ,0x80   ,0x48   ,0xec   ,0x03   ,0x04   ,0x87   ,0x82
            ,0x82   ,0x80   ,0xfb   ,0x15   ,0x6f   ,0x28   ,0x7e   ,0xc0
            ,0x81   ,0x80   ,0x15   ,0x3e   ,0x7b   ,0x1e   ,0x10   ,0x32
            ,0xec   ,0x80   ,0x80   ,0x80   ,0x80   ,0x80   ,0x80   ,0x0f
            ,0x30   ,0x2b   ,0x6e   ,0xc7   ,0x80   ,0x80   ,0xb1   ,0x19
            ,0x4a   ,0xc4   ,0x80   ,0x80   ,0x48   ,0xec   ,0x03   ,0x04
            ,0x88   ,0x82   ,0x82   ,0x80   ,0xfb   ,0x15   ,0x6f   ,0x3b
            ,0x26   ,0xa0   ,0x94   ,0x80   ,0x15   ,0x3e   ,0x7b   ,0x1e
            ,0x10   ,0x32   ,0xec   ,0x80   ,0x80   ,0x80   ,0x80   ,0x80
            ,0x80   ,0x0f   ,0x30   ,0x2b   ,0x6e   ,0xcd   ,0x80
    };

    manager->SetNewBuffer(message, 103);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeFortsHeader();
    FortsDefaultIncrementalRefreshMessageInfo *fr = (FortsDefaultIncrementalRefreshMessageInfo*)manager->DecodeFortsDefaultIncrementalRefreshMessage();
    if(fr->MDEntriesCount != 2)
        throw;
    if(fr->MDEntries[0]->SecurityID != 419139)
        throw;
    if(fr->MDEntries[1]->SecurityID != 419139)
        throw;
    manager->PrintFortsDefaultIncrementalRefreshMessage(fr);


    message = new unsigned char[77] {
            0x09, 0x63, 0x0d, 0x00, 0xc0, 0x1c, 0x9d, 0x35, 0x46, 0x89,
            0x02, 0x2e, 0x45, 0x19, 0x0e, 0x64, 0x66, 0x3e, 0xba, 0x02,
            0x2e, 0x45, 0x19, 0x0e, 0x64, 0x65, 0x4c, 0xb7, 0x81, 0x82,
            0xf6, 0x80, 0x43, 0x4e, 0x59, 0x52, 0x55, 0x42, 0x54, 0x4f,
            0x44, 0x54, 0x4f, 0xcd, 0x00, 0x6b, 0xc0, 0x80, 0x81, 0x08,
            0x41, 0xdc, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x04, 0x9e, 0x80, 0x80,
            0x80, 0x80, 0x43, 0x45, 0x54, 0xd3, 0x80 };

    manager->SetNewBuffer(message, 77);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    AstsIncrementalMSRCURRInfo *mm = (AstsIncrementalMSRCURRInfo*)manager->LastDecodeInfo();

    message = new unsigned char[963] {
            0x8f, 0x01, 0x00, 0x00, 0xc0, 0x1c, 0x90, 0x03, 0x8f, 0x02, 0x2e, 0x42, 0x75, 0x3f, 0x41, 0x65, 0x0f, 0x9a,
            0x30, 0x46, 0xb9, 0x01, 0x36, 0x9e, 0x81, 0x82, 0x00, 0xe5, 0x43, 0x45, 0x54, 0xd3, 0x48, 0x4b, 0x44, 0x52,
            0x55, 0x42, 0x5f, 0x54, 0x4f, 0xcd, 0x92, 0xac, 0x5f, 0xc0, 0xb0, 0x37, 0x39, 0x39, 0x32, 0x33, 0xb3, 0x58,
            0x24, 0x15, 0xf1, 0x34, 0x04, 0xc7, 0xfc, 0x05, 0x2f, 0xeb, 0x81, 0x01, 0xd9, 0xcf, 0xce, 0xde, 0xb1, 0x37,
            0x39, 0x39, 0x33, 0x36, 0xb1, 0x58, 0x24, 0x44, 0xe1, 0x16, 0x02, 0x96, 0xfc, 0x05, 0x59, 0x9b, 0x81, 0x00,
            0xd1, 0xde, 0xb0, 0x37, 0x39, 0x39, 0x34, 0x32, 0xb0, 0x58, 0x24, 0x5c, 0x99, 0x07, 0x29, 0x82, 0xfc, 0x05,
            0x33, 0x8d, 0x81, 0x03, 0x84, 0x9e, 0x37, 0x39, 0x39, 0x36, 0x37, 0xb3, 0x58, 0x25, 0x1a, 0xd9, 0x34, 0x63,
            0xe2, 0xfc, 0x05, 0x21, 0xbb, 0x81, 0x00, 0xf4, 0x9e, 0x37, 0x39, 0x39, 0x38, 0x39, 0xb8, 0x58, 0x28, 0x11,
            0xd9, 0x2f, 0x27, 0xcd, 0xfc, 0x05, 0x28, 0x89, 0x81, 0x02, 0x89, 0xde, 0xb1, 0x38, 0x30, 0x30, 0x32, 0x35,
            0xb7, 0x58, 0x28, 0x7f, 0x89, 0x18, 0x24, 0xa7, 0xfc, 0x05, 0x58, 0xd4, 0x81, 0x03, 0xb7, 0x9e, 0x38, 0x30,
            0x30, 0x33, 0x34, 0xb3, 0x58, 0x29, 0x16, 0xc1, 0x09, 0x5e, 0xfc, 0xfc, 0x05, 0x5f, 0xc0, 0x81, 0x02, 0x8a,
            0xce, 0xb0, 0x38, 0x30, 0x30, 0x33, 0x34, 0xb5, 0x11, 0x1a, 0xb4, 0xfc, 0x05, 0x21, 0xaa, 0x81, 0x03, 0x8d,
            0x9e, 0x38, 0x30, 0x30, 0x34, 0x32, 0xb9, 0x58, 0x29, 0x2d, 0xf9, 0x18, 0x24, 0xc0, 0xfc, 0x05, 0x2a, 0x8f,
            0x81, 0x00, 0xce, 0xde, 0xb1, 0x38, 0x30, 0x30, 0x34, 0x39, 0xb1, 0x58, 0x29, 0x3d, 0xc9, 0x28, 0x5f, 0xc3,
            0xfc, 0x05, 0x6b, 0xf1, 0x81, 0x02, 0xf4, 0x9e, 0x38, 0x30, 0x30, 0x35, 0x39, 0xb0, 0x58, 0x29, 0x55, 0x81,
            0x36, 0x7b, 0xb1, 0xfc, 0x05, 0x5d, 0x99, 0x81, 0x02, 0x9e, 0x9e, 0x38, 0x30, 0x30, 0x36, 0x35, 0xb6, 0x58,
            0x29, 0x6c, 0xb9, 0x0a, 0x5c, 0xb7, 0xfc, 0x05, 0x5e, 0xaf, 0x81, 0x03, 0xcb, 0x8e, 0x38, 0x30, 0x30, 0x36,
            0x36, 0xb0, 0x12, 0x0f, 0x94, 0xfc, 0x05, 0x70, 0xff, 0x81, 0x01, 0x8a, 0x9e, 0x38, 0x30, 0x30, 0x38, 0x31,
            0xb3, 0x58, 0x2a, 0x13, 0xc1, 0x31, 0x10, 0x87, 0xfc, 0x05, 0x6b, 0xf9, 0x81, 0x02, 0xd2, 0xde, 0xb0, 0x38,
            0x30, 0x30, 0x39, 0x39, 0xb0, 0x58, 0x2a, 0x52, 0x81, 0x38, 0x62, 0xb1, 0xfd, 0x00, 0x43, 0xc7, 0x81, 0x02,
            0xc4, 0xde, 0xb1, 0x38, 0x30, 0x31, 0x30, 0x30, 0xb1, 0x58, 0x2a, 0x59, 0xe9, 0x19, 0x62, 0xa7, 0xfc, 0x05,
            0x74, 0xa6, 0x81, 0x01, 0x94, 0xde, 0xb0, 0x38, 0x30, 0x31, 0x30, 0x36, 0xb8, 0x58, 0x2a, 0x69, 0xb9, 0x2a,
            0x44, 0xeb, 0xfd, 0x00, 0x44, 0xef, 0x81, 0x02, 0xec, 0xce, 0xb1, 0x38, 0x30, 0x31, 0x30, 0x37, 0xb2, 0x31,
            0x5e, 0xaa, 0xfc, 0x05, 0x71, 0xdc, 0x81, 0x01, 0x90, 0x9e, 0x38, 0x30, 0x31, 0x31, 0x33, 0xb6, 0x58, 0x2b,
            0x00, 0xf1, 0x38, 0x64, 0xbf, 0xfc, 0x05, 0x5f, 0xa0, 0x81, 0x02, 0xe5, 0x9e, 0x38, 0x30, 0x31, 0x32, 0x31,
            0xb4, 0x58, 0x2b, 0x18, 0xa9, 0x13, 0x5b, 0xca, 0xfc, 0x05, 0x75, 0x81, 0x81, 0x01, 0xb2, 0xde, 0xb0, 0x38,
            0x30, 0x31, 0x33, 0x30, 0xb0, 0x58, 0x2b, 0x27, 0xf9, 0x39, 0x52, 0x8c, 0xfc, 0x05, 0x27, 0xc2, 0x81, 0x03,
            0xa2, 0xde, 0xb1, 0x38, 0x30, 0x31, 0x36, 0x37, 0xb1, 0x58, 0x2e, 0x4d, 0xe9, 0x33, 0x1e, 0xd1, 0xfc, 0x05,
            0x63, 0xde, 0x81, 0x01, 0xf4, 0x9e, 0x38, 0x30, 0x31, 0x37, 0x36, 0xb6, 0x58, 0x2e, 0x65, 0xa1, 0x3a, 0x15,
            0xb1, 0xfc, 0x05, 0x69, 0xd8, 0x82, 0x81, 0xde, 0xb0, 0x38, 0x30, 0x31, 0x38, 0x30, 0xb4, 0x58, 0x2e, 0x7c,
            0xd9, 0x0e, 0x21, 0xd0, 0xfc, 0x05, 0x34, 0xf0, 0x81, 0x01, 0x92, 0x8e, 0x38, 0x30, 0x31, 0x38, 0x30, 0xb7,
            0x14, 0x77, 0xc8, 0xfc, 0x05, 0x3c, 0x90, 0x81, 0x00, 0xfa, 0xde, 0xb1, 0x38, 0x30, 0x31, 0x38, 0x36, 0xb4,
            0x58, 0x2f, 0x0c, 0xa9, 0x3a, 0x5b, 0xb2, 0xff, 0x00, 0xe1, 0x81, 0x01, 0x8a, 0x9e, 0x38, 0x30, 0x31, 0x38,
            0x38, 0xb3, 0x58, 0x2f, 0x14, 0x91, 0x1c, 0x12, 0x81, 0xfc, 0x05, 0x5e, 0xc5, 0x81, 0x03, 0xa0, 0x9e, 0x38,
            0x30, 0x32, 0x30, 0x37, 0xb5, 0x58, 0x2f, 0x52, 0xd1, 0x0f, 0x16, 0xc8, 0xfc, 0x05, 0x70, 0x93, 0x81, 0x02,
            0xe6, 0x9e, 0x38, 0x30, 0x32, 0x33, 0x31, 0xb1, 0x58, 0x30, 0x11, 0x91, 0x1d, 0x42, 0x90, 0xfc, 0x05, 0x72,
            0xe6, 0x81, 0x01, 0xcc, 0xde, 0xb0, 0x38, 0x30, 0x32, 0x37, 0x39, 0xb5, 0x58, 0x31, 0x25, 0xc9, 0x2f, 0x26,
            0x9b, 0xfc, 0x05, 0x35, 0xb7, 0x81, 0x01, 0x92, 0x9e, 0x38, 0x30, 0x32, 0x38, 0x35, 0xb9, 0x58, 0x33, 0x75,
            0xc1, 0x3c, 0x3a, 0xb0, 0xfc, 0x05, 0x2e, 0xdd, 0x81, 0x03, 0xc9, 0x9e, 0x38, 0x30, 0x33, 0x31, 0x30, 0xb3,
            0x58, 0x34, 0x34, 0x81, 0x35, 0x63, 0x8b, 0xfc, 0x05, 0x23, 0x83, 0x81, 0xa1, 0x9e, 0x38, 0x30, 0x33, 0x31,
            0x33, 0xb6, 0x58, 0x34, 0x4b, 0xb9, 0x1f, 0x24, 0x93, 0xfc, 0x05, 0x24, 0xde, 0x81, 0x03, 0xb6, 0x9e, 0x38,
            0x30, 0x33, 0x34, 0x38, 0xb9, 0x58, 0x35, 0x38, 0xe9, 0x12, 0x28, 0xa0, 0xfc, 0x05, 0x30, 0x8b, 0x81, 0xbd,
            0xde, 0xb1, 0x38, 0x30, 0x33, 0x36, 0x34, 0xb3, 0x58, 0x35, 0x5f, 0xf1, 0x31, 0x03, 0x92, 0xfc, 0x05, 0x60,
            0xb5, 0x81, 0x03, 0xe3, 0x9e, 0x38, 0x30, 0x33, 0x39, 0x33, 0xb7, 0x58, 0x36, 0x4d, 0xa1, 0x21, 0x2b, 0xce,
            0xfd, 0x00, 0x4a, 0xff, 0x81, 0x01, 0xdd, 0xde, 0xb0, 0x38, 0x30, 0x33, 0x39, 0x35, 0xb1, 0x58, 0x36, 0x55,
            0x89, 0x02, 0x18, 0xd6, 0xfc, 0x05, 0x28, 0xc3, 0x81, 0x00, 0xdb, 0x9e, 0x38, 0x30, 0x34, 0x30, 0x32, 0xb3,
            0x58, 0x36, 0x64, 0xd9, 0x13, 0x4a, 0xef, 0xfc, 0x05, 0x21, 0xbf, 0x81, 0x02, 0xeb, 0x9c, 0x38, 0x30, 0x34,
            0x30, 0x38, 0xb2, 0x58, 0x36, 0x7c, 0x91, 0x21, 0x0a, 0x82, 0xfc, 0x05, 0x33, 0xb7, 0x9e, 0x38, 0x30, 0x34,
            0x34, 0x39, 0xb5, 0x58, 0x3a, 0x39, 0xb9, 0x03, 0x26, 0x80, 0xfc, 0x05, 0x3c, 0xb6, 0x81, 0x90, 0x9e, 0x38,
            0x30, 0x34, 0x36, 0x30, 0xb3, 0x58, 0x3a, 0x60, 0xc1, 0x21, 0x7a, 0xaa, 0xfd, 0x00, 0x43, 0xc9, 0x82, 0xb0,
            0x9e, 0x38, 0x30, 0x34, 0x36, 0x34, 0xb8, 0x58, 0x3a, 0x70, 0x91, 0x39, 0x10, 0xa4, 0xfc, 0x05, 0x21, 0xfb,
            0x81, 0x02, 0xe6, 0x9e, 0x38, 0x30, 0x34, 0x37, 0x32, 0xb9, 0x58, 0x3b, 0x0f, 0xb1, 0x03, 0x60, 0xe1, 0xfc,
            0x05, 0x39, 0xd8, 0x82, 0x91, 0xde, 0xb1, 0x38, 0x30, 0x34, 0x39, 0x34, 0xb9, 0x58, 0x3b, 0x46, 0x89, 0x39,
            0x62, 0x80, 0xfc, 0x05, 0x5b, 0x9e, 0x81, 0x00, 0xc4
    };
    manager->SetNewBuffer(message, 963);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    AstsOLSCURRInfo *oc = (AstsOLSCURRInfo*)manager->LastDecodeInfo();
    for(int i = 0; i < oc->GroupMDEntriesCount; i++) {
        if(oc->GroupMDEntries[i]->MDEntryType[0] != '0')
            throw;
    }

    int msgSize = 0;
    message = DebugInfoManager::Default->StringToBinary("0f 50 05 00 c0 1c 9a 15 20 8f 02 2e 2d 43 6f 62 77 6c 86 84 77 98 83 b1 32 39 34 39 34 b1 45 55 52 5f 52 55 42 5f 5f 54 4f cd 08 5a fc 3e 06 50 a1 1e 1d ed fe 37 aa 43 45 54 d3 ce 82 32 39 34 39 34 b4 08 5a fd 1e 24 d4 53 e0 81 33 33 31 32 32 b7 48 4b 44 52 55 42 5f 54 4f cd 00 41 8d 1e 47 f9 fc 08 13 dc 81 01 ea cf 13 c0 33 33 31 32 32 b8 47 4c 44 52 55 42 54 4f 44 54 4f cd 27 ba 1f 64 a8 fc 01 04 a1 81 02 93", &msgSize);
    manager->SetNewBuffer(message, msgSize);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsIncrementalOLRCURRInfo *olsCurr2 = (AstsIncrementalOLRCURRInfo*)manager->DecodeAsts();
    if(olsCurr2->GroupMDEntries[1]->MDEntryType != olsCurr2->GroupMDEntries[0]->MDEntryType)
        throw;

    message = new unsigned char[94] {
            0x9f, 0xa4, 0x04, 0x00, 0xc0, 0x1c, 0x9a, 0x12, 0x49, 0x9f,
            0x02, 0x2e, 0x2d, 0x43, 0x4c, 0x22, 0x74, 0x16, 0xbb, 0x82,
            0x77, 0x98, 0x83, 0xb0, 0x32, 0x35, 0x32, 0x31, 0x37, 0xb4,
            0x43, 0x4e, 0x59, 0x52, 0x55, 0x42, 0x54, 0x4f, 0x44, 0x54,
            0x4f, 0xcd, 0x1f, 0xe6, 0x39, 0x41, 0x02, 0xf9, 0x07, 0xa6,
            0xfa, 0x3a, 0x91, 0x43, 0x45, 0x54, 0xd3, 0xce, 0x57, 0xe0,
            0x81, 0x32, 0x39, 0x30, 0x39, 0x37, 0xb3, 0x43, 0x48, 0x46,
            0x52, 0x55, 0x42, 0x5f, 0x54, 0x4f, 0xc4, 0x37, 0xff, 0x39,
            0x40, 0x7b, 0x91, 0x3c, 0x50, 0x81, 0xfe, 0x00, 0x4e, 0xac,
            0x81, 0x01, 0xe9, 0xcf
    };

    manager->SetNewBuffer(message, 130);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsIncrementalOLRCURRInfo *olsCurr1 = (AstsIncrementalOLRCURRInfo*)manager->DecodeAsts();
    if(!StringIdComparer::Equal(olsCurr1->GroupMDEntries[0]->TradingSessionID,
                                olsCurr1->GroupMDEntries[0]->TradingSessionIDLength, "CETS", 4))
        throw;

    message = new unsigned char[130] {
            0x89, 0x30, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x61, 0x89, 0x02,
            0x16, 0x48, 0x54, 0x42, 0x3c, 0x26, 0xb9, 0x00, 0x65, 0xa7,
            0x4d, 0x4f, 0x45, 0x58, 0x52, 0x45, 0x50, 0xcf, 0x80, 0x80,
            0x88, 0x87, 0x4d, 0x52, 0x49, 0x58, 0x58, 0x58, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x94, 0x4d, 0x4f,
            0x45, 0x58, 0x52, 0x45, 0x50, 0x4f, 0x20, 0x42, 0x6f, 0x6e,
            0x64, 0x20, 0x31, 0x32, 0x3a, 0x33, 0x30, 0x96, 0x4d, 0x4f,
            0x45, 0x58, 0x52, 0x45, 0x50, 0x4f, 0x20, 0xd0, 0xbe, 0xd0,
            0xb1, 0xd0, 0xbb, 0x20, 0x31, 0x32, 0x3a, 0x33, 0x30, 0x80,
            0x82, 0x9b, 0x82, 0x32, 0x80, 0x82, 0x80, 0x82, 0x54, 0x51,
            0x42, 0xd2, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x87, 0x4d,
            0x58, 0x52, 0x45, 0x50, 0x4f, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
    };

    manager->SetNewBuffer(message, 130);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsSecurityDefinitionInfo *sec = (AstsSecurityDefinitionInfo*)manager->DecodeAsts();
    manager->PrintAstsSecurityDefinition(sec);

    if(sec->MarketSegmentGrpCount != 1)
        throw;
    if(sec->MarketSegmentGrp[0]->TradingSessionRulesGrpCount != 1)
        throw;
    if(!StringIdComparer::Equal(
            sec->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionID,
            sec->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->TradingSessionIDLength,
            "TQBR",
            4)) throw;

    message = new unsigned char[138] {
            0x8a, 0x30, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x61, 0x8a, 0x02,
            0x16, 0x48, 0x54, 0x42, 0x3c, 0x5c, 0xfb, 0x00, 0x65, 0xa7,
            0x4d, 0x4f, 0x45, 0x58, 0x52, 0x45, 0x50, 0x4f, 0x31, 0xd7,
            0x80, 0x80, 0x88, 0x87, 0x4d, 0x52, 0x49, 0x58, 0x58, 0x58,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x96,
            0x4d, 0x4f, 0x45, 0x58, 0x52, 0x45, 0x50, 0x4f, 0x31, 0x57,
            0x20, 0x42, 0x6f, 0x6e, 0x64, 0x20, 0x31, 0x32, 0x3a, 0x33,
            0x30, 0x98, 0x4d, 0x4f, 0x45, 0x58, 0x52, 0x45, 0x50, 0x4f,
            0x31, 0x57, 0x20, 0xd0, 0xbe, 0xd0, 0xb1, 0xd0, 0xbb, 0x20,
            0x31, 0x32, 0x3a, 0x33, 0x30, 0x80, 0x82, 0x9b, 0x82, 0x32,
            0x80, 0x82, 0x80, 0x82, 0x54, 0x51, 0x42, 0xd2, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x89, 0x4d, 0x58, 0x52, 0x45, 0x50,
            0x4f, 0x31, 0x57, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
    };

    manager->SetNewBuffer(message, 138);
    msgSeqNo = manager->ReadMsgSeqNumber();
    sec = (AstsSecurityDefinitionInfo*)manager->DecodeAsts();
    manager->PrintAstsSecurityDefinition(sec);

    message = new unsigned char[194] {
            0x93, 0x30, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x61, 0x93, 0x02,
            0x16, 0x48, 0x54, 0x42, 0x41, 0x06, 0x87, 0x00, 0x65, 0xa7,
            0x4d, 0x52, 0x4b, 0xc3, 0x8d, 0x52, 0x55, 0x30, 0x30, 0x30,
            0x41, 0x30, 0x4a, 0x50, 0x50, 0x4c, 0x38, 0x82, 0x34, 0x86,
            0x87, 0x45, 0x53, 0x58, 0x58, 0x58, 0x58, 0x83, 0x43, 0x53,
            0x80, 0x09, 0x4e, 0x45, 0xcc, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x8c, 0x4d, 0x52, 0x53, 0x4b, 0x20, 0x43, 0x65, 0x6e,
            0x74, 0x72, 0x61, 0xa4, 0x27, 0xd0, 0x9c, 0xd0, 0xa0, 0xd0,
            0xa1, 0xd0, 0x9a, 0x20, 0xd0, 0xa6, 0xd0, 0xb5, 0xd0, 0xbd,
            0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xb0, 0x27, 0x20, 0xd0, 0x9f,
            0xd0, 0x90, 0xd0, 0x9e, 0x20, 0xd0, 0xb0, 0xd0, 0xbe, 0x80,
            0x83, 0x9b, 0x82, 0x34, 0x88, 0x82, 0x30, 0x52, 0x55, 0xc2,
            0x82, 0x84, 0x81, 0x82, 0x54, 0x51, 0x42, 0xd2, 0xce, 0x92,
            0x82, 0x52, 0x55, 0xc2, 0x83, 0x31, 0x2d, 0x30, 0x31, 0x2d,
            0x31, 0x30, 0x32, 0x31, 0x34, 0x2d, 0xc1, 0x94, 0xd0, 0x9c,
            0xd0, 0xa0, 0xd0, 0xa1, 0xd0, 0x9a, 0x20, 0xd0, 0xa6, 0xd0,
            0xb5, 0xd0, 0xbd, 0xd1, 0x82, 0xd1, 0x80, 0x85, 0x46, 0x4e,
            0x44, 0x54, 0xfc, 0x85, 0x80, 0x80, 0x80, 0x80, 0xff, 0x81,
            0x80, 0x80, 0x80, 0x80, 0x81, 0x01, 0x1d, 0x23, 0x0a, 0x53,
            0xdc, 0x80, 0x80, 0x80
    };

    manager->SetNewBuffer(message, 194);
    msgSeqNo = manager->ReadMsgSeqNumber();
    sec = (AstsSecurityDefinitionInfo*)manager->DecodeAsts();
    manager->PrintAstsSecurityDefinition(sec);
    
    message = new unsigned char[182] {
            0x4f, 0x9f, 0x03, 0x00, 0xc0, 0x13, 0xdb, 0x0e, 0x3e, 0xcf,
            0x02, 0x15, 0x55, 0x15, 0x12, 0x1c, 0x55, 0x88, 0x83, 0x83,
            0xb1, 0x80, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30, 0x4a,
            0x56, 0x56, 0x4c, 0xb4, 0x15, 0x80, 0xfe, 0x00, 0x5b, 0xc5,
            0x81, 0x20, 0xf8, 0x80, 0x80, 0x80, 0xc3, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x45, 0x51, 0x44,
            0xc2, 0x80, 0x82, 0xf7, 0x80, 0x52, 0x55, 0x30, 0x30, 0x30,
            0x41, 0x30, 0x4a, 0x56, 0x56, 0x4c, 0xb4, 0x15, 0x81, 0x80,
            0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x45, 0x51, 0x44, 0xc2,
            0x80, 0x83, 0xea, 0x80, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41,
            0x30, 0x4a, 0x56, 0x56, 0x4c, 0xb4, 0x15, 0x82, 0xfe, 0x00,
            0x5b, 0xc5, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x45, 0x51, 0x44,
            0xc2, 0xce
    };

    manager->SetNewBuffer(message, 225);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsIncrementalMSRFONDInfo *msr = (AstsIncrementalMSRFONDInfo*)manager->DecodeAsts();
    manager->PrintAstsIncrementalMSRFOND(msr);

    if(msr->GroupMDEntries[0]->MDUpdateAction != MDUpdateAction::mduaDelete)
        throw;
    if(msr->GroupMDEntries[0]->MDEntryType[0] != MDEntryType::mdetSellQuote)
        throw;
    if(msr->GroupMDEntries[0]->MDEntryID[0] != '\0')
        throw;
    if(!StringIdComparer::Equal(msr->GroupMDEntries[0]->Symbol, msr->GroupMDEntries[0]->SymbolLength, "RU000A0JVVL4", 12))
        throw;
    if(msr->GroupMDEntries[0]->RptSeq != 2687)
        throw;
    if(msr->GroupMDEntries[0]->QuoteCondition[0] != 'C')
        throw;
    if(msr->GroupMDEntries[0]->QuoteConditionLength != 1)
        throw;
    if(!StringIdComparer::Equal(msr->GroupMDEntries[0]->TradingSessionID, msr->GroupMDEntries[0]->TradingSessionIDLength, "EQDB", 4))
        throw;

    message = new unsigned char[18] {
            0x4c, 0x9f, 0x03, 0x00, 0xc0, 0x10, 0xbc, 0x0e, 0x3e, 0xcc,
            0x02, 0x15, 0x55, 0x15, 0x10, 0x77, 0x61, 0x90
    };
    manager->SetNewBuffer(message, 18);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsHeartbeatInfo *hb = (AstsHeartbeatInfo*)manager->DecodeAsts();
    manager->PrintAstsHeartbeat(hb);

    message = new unsigned char[225] {
            0x8d, 0x23, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x47, 0x8d, 0x23,
            0x68, 0x05, 0x17, 0x15, 0x66, 0x29, 0xad, 0x00, 0x5e, 0xed,
            0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30, 0x4a, 0x55, 0x36,
            0x4e, 0xb4, 0x8d, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30,
            0x4a, 0x55, 0x36, 0x4e, 0x34, 0x82, 0x34, 0x8c, 0x87, 0x44,
            0x42, 0x58, 0x58, 0x58, 0x58, 0x85, 0x4d, 0x55, 0x4e, 0x49,
            0x09, 0x4f, 0x5f, 0xc1, 0x09, 0x4e, 0x42, 0xb8, 0x80, 0x87,
            0x83, 0x09, 0x4e, 0x43, 0x95, 0xf0, 0x31, 0x4d, 0x76, 0x4e,
            0x13, 0x51, 0xba, 0x80, 0x80, 0x92, 0x4b, 0x6f, 0x73, 0x74,
            0x72, 0x6f, 0x6d, 0x61, 0x20, 0x72, 0x65, 0x67, 0x2e, 0x2d,
            0x30, 0x30, 0x37, 0xaa, 0xd0, 0x9a, 0xd0, 0xbe, 0xd1, 0x81,
            0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xbe, 0xd0, 0xbc, 0xd1, 0x81,
            0xd0, 0xba, 0xd0, 0xb0, 0xd1, 0x8f, 0x20, 0xd0, 0xbe, 0xd0,
            0xb1, 0xd0, 0xbb, 0x2e, 0x20, 0xd0, 0xb2, 0xd1, 0x8b, 0xd0,
            0xbf, 0x2e, 0x30, 0x30, 0x37, 0x80, 0x83, 0x9b, 0x82, 0x34,
            0x88, 0x83, 0x39, 0x31, 0x52, 0x55, 0xc2, 0x82, 0x81, 0x81,
            0x82, 0x52, 0x50, 0x4d, 0xcf, 0x4e, 0xc1, 0x93, 0x82, 0x52,
            0x55, 0xc2, 0x82, 0x52, 0x55, 0x33, 0x34, 0x30, 0x30, 0x37,
            0x4b, 0x4f, 0x53, 0xb0, 0x94, 0xd0, 0x9a, 0xd0, 0xbe, 0xd1,
            0x81, 0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xbe, 0xd0, 0xbc, 0xd0,
            0x9e, 0xd0, 0xb1, 0x37, 0x84, 0x52, 0x50, 0x53, 0xfc, 0x81,
            0x80, 0x80, 0x80, 0x80, 0x82, 0xb7, 0x80, 0x80, 0x80, 0x80,
            0x87, 0x84, 0x80, 0x80, 0x80
    };

    manager->SetNewBuffer(message, 225);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsSecurityDefinitionInfo *sd = (AstsSecurityDefinitionInfo*)manager->DecodeAsts();
    manager->PrintAstsSecurityDefinition(sd);
    if(manager->MessageLength() != 225)
        throw;
    if(!CompareStrings(sd->StateSecurityID, "RU34007KOS0"))
        throw;
    if(sd->SettlDate != 20160823)
        throw;

    if(sd->FaceValue.Mantissa != 55 || sd->FaceValue.Exponent != 1)
        throw;
    if(sd->NoSharesIssued.Mantissa != 4 || sd->NoSharesIssued.Exponent != 6)
        throw;
    manager->PrintAstsSecurityDefinition(sd);

    message = new unsigned char[171] {
            0x46, 0x20, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x40, 0xc6, 0x23,
            0x68, 0x05, 0x17, 0x03, 0x01, 0x50, 0xd9, 0x00, 0x5e, 0xed,
            0x58, 0x53, 0x30, 0x39, 0x33, 0x35, 0x33, 0x31, 0x31, 0x32,
            0x34, 0xb0, 0x8d, 0x58, 0x53, 0x30, 0x39, 0x33, 0x35, 0x33,
            0x31, 0x31, 0x32, 0x34, 0x30, 0x82, 0x34, 0x84, 0x87, 0x44,
            0x42, 0x58, 0x58, 0x58, 0x58, 0x85, 0x43, 0x4f, 0x52, 0x50,
            0x09, 0x52, 0x62, 0xfc, 0x09, 0x4e, 0x42, 0xb8, 0x80, 0x80,
            0x09, 0x4e, 0x44, 0xe4, 0xfb, 0x14, 0xc1, 0x80, 0x80, 0x86,
            0x53, 0x42, 0x2d, 0x32, 0x33, 0x9e, 0x53, 0x42, 0x20, 0x43,
            0x41, 0x50, 0x49, 0x54, 0x41, 0x4c, 0x20, 0x53, 0x2e, 0x41,
            0x2e, 0x20, 0x35, 0x2e, 0x32, 0x35, 0x20, 0x32, 0x33, 0x2f,
            0x30, 0x35, 0x2f, 0x32, 0x33, 0x80, 0x83, 0x9b, 0x82, 0x36,
            0x88, 0x84, 0x31, 0x38, 0x34, 0x55, 0x53, 0xc4, 0x82, 0x81,
            0x81, 0x82, 0x52, 0x50, 0x45, 0xd5, 0xce, 0x92, 0x80, 0x55,
            0x53, 0xc4, 0x82, 0x80, 0x86, 0x53, 0x42, 0x2d, 0x32, 0x33,
            0x84, 0x52, 0x50, 0x53, 0xfa, 0x81, 0x80, 0x80, 0x80, 0x80,
            0x84, 0x81, 0x80, 0x80, 0x80, 0x80, 0x87, 0x81, 0x80, 0x80,
            0x80};


    manager->SetNewBuffer(message, 171);
    msgSeqNo = manager->ReadMsgSeqNumber();
    sd = (AstsSecurityDefinitionInfo*)manager->DecodeAsts();
    manager->PrintAstsSecurityDefinition(sd);
    if(manager->MessageLength() != 171)
        throw;

    message = new unsigned char[241] {
            0x7c, 0x2e, 0x00, 0x00, 0xe0, 0x12, 0xec, 0x5c, 0xfc, 0x23,
            0x68, 0x07, 0x6d, 0x66, 0x66, 0x4a, 0xe3, 0x11, 0x32, 0x86,
            0x03, 0x9c, 0x00, 0xe5, 0x54, 0x51, 0x49, 0xc6, 0x52, 0x55,
            0x30, 0x30, 0x30, 0x41, 0x30, 0x4a, 0x54, 0x38, 0x55, 0xb8,
            0x82, 0x82, 0x92, 0x80, 0x87, 0xb0, 0x42, 0x30, 0x30, 0x30,
            0x30, 0x31, 0x31, 0x30, 0x36, 0xb6, 0xff, 0x00, 0x56, 0xba,
            0x81, 0x00, 0xc5, 0x49, 0x3a, 0x3b, 0xd1, 0x04, 0x07, 0x97,
            0x80, 0x80, 0x80, 0x80, 0xb0, 0x42, 0x30, 0x30, 0x30, 0x30,
            0x31, 0x31, 0x30, 0x36, 0xb7, 0xff, 0x00, 0x56, 0xbb, 0x81,
            0xa6, 0x49, 0x51, 0x15, 0xf1, 0x1e, 0x34, 0x8f, 0x80, 0x80,
            0x80, 0x80, 0xb0, 0x42, 0x30, 0x30, 0x30, 0x30, 0x31, 0x31,
            0x30, 0x36, 0xb8, 0xff, 0x00, 0x56, 0xbc, 0x81, 0xb5, 0x48,
            0x1a, 0x46, 0xf1, 0x31, 0x57, 0xeb, 0x80, 0x80, 0x80, 0x80,
            0xb0, 0x42, 0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x36,
            0xb9, 0xff, 0x00, 0x56, 0xbd, 0x81, 0x83, 0x48, 0x76, 0x7b,
            0x81, 0x1b, 0x55, 0xb5, 0x80, 0x80, 0x80, 0x80, 0xb1, 0x53,
            0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x37, 0xb0, 0x81,
            0x08, 0xd3, 0x81, 0x9d, 0x49, 0x4d, 0x0a, 0xb9, 0x12, 0x7d,
            0xb6, 0x80, 0x80, 0x80, 0x80, 0xb1, 0x53, 0x30, 0x30, 0x30,
            0x30, 0x31, 0x31, 0x30, 0x37, 0xb1, 0xff, 0x00, 0x56, 0xbf,
            0x81, 0xac, 0x49, 0x40, 0x77, 0xe1, 0x1c, 0x51, 0x8a, 0x80,
            0x80, 0x80, 0x80, 0xb1, 0x53, 0x30, 0x30, 0x30, 0x30, 0x31,
            0x31, 0x30, 0x37, 0xb2, 0xff, 0x00, 0x56, 0xc0, 0x81, 0x97,
            0x49, 0x3e, 0x4e, 0xf1, 0x0d, 0x76, 0xf8, 0x80, 0x80, 0x80,
            0x80 };

    manager->SetNewBuffer(message, 241);
    msgSeqNo = manager->ReadMsgSeqNumber();
    AstsSnapshotInfo *snap = (AstsSnapshotInfo*)manager->GetAstsSnapshotInfo();
    if(snap->LastMsgSeqNumProcessed != 284933)
        throw;

    message = new unsigned char[18] {
            0x00, 0x8d, 0x03, 0x00, 0xc0, 0x10, 0xbc, 0x0e, 0x1a, 0x80,
            0x23, 0x68, 0x08, 0x12, 0x7f, 0x4c, 0x4f, 0xfa
    };
    manager->SetNewBuffer(message, 18);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    manager->PrintAsts();

    message = new unsigned char[65] {
            0x05, 0x8d, 0x03, 0x00, 0xe0, 0x12, 0xf6, 0x0e, 0x1a, 0x85,
            0x23, 0x68, 0x08, 0x12, 0x7f, 0x4c, 0x66, 0xd1, 0x81, 0x83,
            0xb0, 0x42, 0x30, 0x30, 0x30, 0x30, 0x32, 0x37, 0x35, 0x37,
            0xb1, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30, 0x4a, 0x50,
            0x4b, 0x4a, 0xb3, 0x03, 0xb2, 0xff, 0x01, 0x57, 0xb3, 0x80,
            0x57, 0x6d, 0x1e, 0xd1, 0x1e, 0x28, 0xeb, 0x80, 0x80, 0x80,
            0x54, 0x51, 0x49, 0xc6, 0x80
    };
    manager->SetNewBuffer(message, 65);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    manager->PrintAsts();
    
    message = new unsigned char[55] {
            0x25, 0x29, 0x04, 0x00, 0xe0, 0x12, 0xf4, 0x10, 0x52, 0xa5,
            0x23, 0x68, 0x0b, 0x0f, 0x04, 0x7e, 0x58, 0xa2, 0x81, 0x80,
            0x83, 0xb1, 0x33, 0x35, 0x35, 0x31, 0x34, 0xb8, 0x42, 0x47,
            0x44, 0xc5, 0x26, 0xee, 0x80, 0x5f, 0x6d, 0x15, 0x91, 0x34,
            0x1d, 0xf4, 0xfe, 0x05, 0xc5, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x54, 0x51, 0x44, 0xc5, 0xce
    };

    manager->SetNewBuffer(message, 55);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    manager->PrintAsts();

    if(manager->TemplateId() != 2420)
        throw;

    AstsIncrementalOLRFONDInfo *olrfondInfo = (AstsIncrementalOLRFONDInfo*)manager->LastDecodeInfo();
    if(olrfondInfo->GroupMDEntriesCount != 1)
        throw;
    if(manager->MessageLength() != 55)
        throw;

    message = new unsigned char[57] {
            0x64, 0x0c, 0x04, 0x00, 0xe0, 0x12, 0xf4, 0x10, 0x18, 0xe4,
            0x23, 0x68, 0x0b, 0x12, 0x63, 0x2e, 0x2d, 0xc4, 0x81, 0x80,
            0x81, 0xb1, 0x33, 0x36, 0x30, 0x38, 0x36, 0xb0, 0x55, 0x54,
            0x53, 0xd9, 0x1d, 0xef, 0x80, 0x61, 0x31, 0x59, 0xb1, 0x1d,
            0x01, 0x9e, 0xfe, 0x03, 0xbc, 0x81, 0x0d, 0x9d, 0x80, 0xcf,
            0x80, 0x80, 0x54, 0x51, 0x44, 0xc5, 0xce
    };

    manager->SetNewBuffer(message, 57);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    manager->PrintAsts();

    olrfondInfo = (AstsIncrementalOLRFONDInfo*)manager->LastDecodeInfo();
    if(olrfondInfo->GroupMDEntriesCount != 1)
        throw;
    if(manager->MessageLength() != 57)
        throw;

    message = new unsigned char[18] {
            0x32, 0x77, 0x03, 0x00, 0xe0, 0x12, 0xf4, 0x0d, 0x6e, 0xb2,
            0x23, 0x68, 0x0d, 0x26, 0x2f, 0x55, 0x09, 0x83
    };

    manager->SetNewBuffer(message, 18);
    manager->SetNewBuffer(message, 18);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->DecodeAsts();
    manager->PrintAsts();
}

bool FastProtocolTester::CompareStrings(char* str1, const char *str2) {
    int length = strlen(str2);
    for(int i = 0; i < length; i++) {
        if(str1[i] != str2[i])
            return false;
    }
    return true;
}

void FastProtocolTester::TestMessageSequenceNumber() { 

    *((int*)(manager->Buffer())) = 0x12345678;
    int seq = manager->ReadMsgSeqNumber();

    if (manager->CurrentPos() - manager->Buffer() != 4) { 
        printf("ReadMsgSeqNumber: expected 4 but was %ld", manager->CurrentPos() - manager->Buffer());
        throw;
    }
    if (seq != 0x12345678) { 
        printf("ReadMsgSeqNumber: expected 0x12345678 but was %x", seq);
        throw;
    }
}

void FastProtocolTester::TestReadInt32_Mandatory() { 
    printf("Test FastProtocolTester::TestReadInt32_Mandatory\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    INT32 value;
    for (int i = 0; i > INT32_MIN + 60; i -= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Mandatory(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Mandatory();
        if (value != i) {
            manager->ResetBuffer();
            value = manager->ReadInt32_Mandatory();
            throw;
        }
    }

    for (int i = 0; i < INT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Mandatory(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Mandatory();
        if (value != i) {
            manager->ResetBuffer();
            value = manager->ReadInt32_Mandatory();
            throw;
        }
    }
}

void FastProtocolTester::TestReadInt32_Optional() {
    printf("Test FastProtocolTester::TestReadInt32_Optional\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    INT32 value;
    for (int i = 0; i > INT32_MIN + 60; i -= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Optional(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Optional();
        if (value != i)
            throw;
    }

    for (int i = 0; i < INT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Optional(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Optional();
        if (value != i)
            throw;
    }
}

void FastProtocolTester::TestReadInt32_Optional_Predict1() {
    printf("Test FastProtocolTester::TestReadInt32_Optional_Predict1\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    INT32 value;

    for (int i = 0; i > INT32_MIN + 60; i -= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Optional(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Optional_Predict1();
        if (value != i)
            throw;
    }

    for (int i = 0; i < INT32_MAX - 60; i+= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Optional(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Optional_Predict1();
        if (value != i)
            throw;
    }
}

void FastProtocolTester::TestReadInt32_Mandatory_Predict1() {
    printf("Test FastProtocolTester::TestReadInt32_Mandatory_Predict1\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    INT32 value;

    for (int i = 0; i > INT32_MIN + 60; i -= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Mandatory(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Mandatory_Predict1();
        if (value != i)
            throw;
    }

    for (int i = 0; i < INT32_MAX- 60; i+= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Mandatory(i);
        manager->ResetBuffer();
        value = manager->ReadInt32_Mandatory_Predict1();
        if (value != i)
            throw;
    }
}

void FastProtocolTester::TestReadInt32_Optional2() {
    printf("Test FastProtocolTester::TestReadInt32_Optional2\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    INT32 value;
    manager->Buffer()[0] = 0x80;
    manager->ResetBuffer();
    if(manager->ReadInt32_Optional(&value))
        throw;

    for (int i = -1; i > INT32_MIN + 60; i -= 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Optional(i);
        manager->ResetBuffer();
        bool res = manager->ReadInt32_Optional(&value);
        if (value != i || !res) {
            manager->ResetBuffer();
            res = manager->ReadInt32_Optional(&value);
            throw;
        }
    }

    for (int i = 0; i < INT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteInt32_Optional(i);
        manager->ResetBuffer();
        bool res = manager->ReadInt32_Optional(&value);
        if (value != i || !res)
            throw;
    }
}

void FastProtocolTester::TestReadUInt32_Optional() {
    printf("Test FastProtocolTester::TestReadUInt32_Optional\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    for (UINT32 i = 0; i < UINT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteUInt32_Optional(i);
        manager->ResetBuffer();
        UINT32 value = manager->ReadUInt32_Optional();
        if (value != i)
            throw;
    }
}

void FastProtocolTester::TestReadUInt32_Optional_Fixed1() {
    printf("Test FastProtocolTester::TestReadUInt32_Optional_Fixed1\n");
    UINT32 value;

    for (UINT32 i = 0; i < 0x7f; i ++) {
        manager->ResetBuffer();
        manager->WriteUInt32_Optional(i);
        manager->ResetBuffer();
        bool res = manager->ReadUInt32_Optional_Fixed1(&value);
        if (value != i || !res)
            throw;
    }
}

void FastProtocolTester::TestReadUInt32_Optional2() {
    printf("Test FastProtocolTester::TestReadUInt32_Optional2\n");
    UINT32 value;

    manager->SetNewBuffer(new unsigned char[100], 100);
    manager->ResetBuffer();
    manager->Buffer()[0] = 0x80;
    if(manager->ReadUInt32_Optional(&value))
        throw;

    for (UINT32 i = 0; i < UINT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteUInt32_Optional(i);
        manager->ResetBuffer();
        bool res = manager->ReadUInt32_Optional(&value);
        if (value != i || !res)
            throw;
        manager->ResetBuffer();
        res = manager->ReadUInt32_Optional_Predict1(&value);
        if (value != i || !res)
            throw;
    }
}

void FastProtocolTester::TestReadUInt32_Mandatory() {
    printf("Test FastProtocolTester::TestReadUInt32_Mandatory\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    for (UINT32 i = 0; i < UINT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteUInt32_Mandatory(i);
        manager->ResetBuffer();
        UINT32 value = manager->ReadUInt32_Mandatory();
        if (value != i) {
            manager->ResetBuffer();
            value = manager->ReadUInt32_Mandatory();
            throw;
        }
    }
}

void FastProtocolTester::TestReadUInt32_Mandatory_Predict1() {
    printf("Test FastProtocolTester::TestReadUInt32_Mandatory_Predict1\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    for (UINT32 i = 0; i < UINT32_MAX - 60; i += 50) {
        manager->ResetBuffer();
        manager->WriteUInt32_Mandatory(i);
        manager->ResetBuffer();
        UINT32 value = manager->ReadUInt32_Mandatory();
        if (value != i) {
            manager->ResetBuffer();
            value = manager->ReadUInt32_Mandatory_Predict1();
            throw;
        }
    }
}

void FastProtocolTester::TestStringCopy() {
    printf("Test FastProtocolTester::TestStringCopy\n");
    manager->SetNewBuffer(new unsigned char[100], 100);

    char *buffer = new char[60];
    char *buffer2 = new char[60];
    for (int i = 0; i < 60; i++) {
        buffer[i] = (char)('A' + i);
    }

    for (int i = 1; i < 60; i++) {
        memset(buffer2, 60, 0);
        manager->CopyString(buffer2, buffer, i);
        for(int j = 0; j < i; j++) {
            if(buffer[j] != buffer2[j])
                throw;
        }
        memset(buffer2, 60, 0);

        StringIdComparer::CopyString(buffer2, buffer, i);
        for(int j = 0; j < i; j++) {
            if(buffer[j] != buffer2[j])
                throw;
        }
    }
}

void FastProtocolTester::TestReadString_Optional() { 
    printf("Test FastProtocolTester::TestReadString_Optional\n");

    manager->SetNewBuffer(new unsigned char[128], 128);
    manager->WriteString_Optional((const char*)NULL, 0);
    if (manager->MessageLength() != 1)
        throw;
    if (manager->Buffer()[0] != 0x80)
        throw;

    manager->ResetBuffer();
    manager->WriteString_Optional((char*)"", 0);
    if (manager->MessageLength() != 2)
        throw;
    if (manager->Buffer()[0] != 0x00)
        throw;
    if (manager->Buffer()[1] != 0x80)
        throw;

    char *buffer = new char[60];
    char *buffer2 = new char[60];
    for (int i = 0; i < 60; i++) { 
        buffer[i] = (char)('A' + i);
    } 

    int length = 0;
    for (int i = 1; i < 60; i++) { 
        manager->ResetBuffer();
        manager->WriteString_Optional(buffer, i);
        if (manager->MessageLength() != i)
            throw;

        manager->ResetBuffer();
        manager->ReadString_Optional(buffer2, &length);
        if (length != i)
            throw;
        for (int j = 0; j < i; j++) { 
            if (buffer2[j] != buffer[j])
                throw;
        }
    }
}

void FastProtocolTester::TestReadString_Mandatory() {
    printf("Test FastProtocolTester::TestReadString_Mandatory\n");

    manager->SetNewBuffer(new unsigned char[128], 128);
    manager->WriteString_Mandatory((char*)"", 0);
    if (manager->MessageLength() != 1)
        throw;
    if (manager->Buffer()[0] != 0x80)
        throw;

    char *buffer = new char[60];
    char *buffer2 = new char[60];
    for (int i = 0; i < 60; i++) {
        buffer[i] = (char)('A' + i);
    }

    int length = 0;
    for (int i = 1; i < 60; i++) {
        manager->ResetBuffer();
        manager->WriteString_Mandatory(buffer, i);
        if (manager->MessageLength() != i)
            throw;

        manager->ResetBuffer();
        manager->ReadString_Mandatory(buffer2, &length);
        if (length != i)
            throw;
        for (int j = 0; j < i; j++) {
            if (buffer2[j] != buffer[j])
                throw;
        }
    }
}

void FastProtocolTester::TestReadByteVector_Optional() { 
    printf("Test FastProtocolTester::TestReadByteVector_Optional\n");

    manager->SetNewBuffer(new unsigned char[1000], 1000);
    manager->ResetBuffer();
    manager->WriteByteVector_Optional(NULL, 0);
    if (manager->MessageLength() != 1)
        throw;
    if (manager->Buffer()[0] != 0x80)
        throw;

    BYTE *buffer = new BYTE[1000];
    BYTE *buffer2 = new BYTE[1000];
    for (int i = 0; i < 1000; i++) {
        buffer[i] = (char)('A' + i % 60);
    }

    int length = 0;
    for (int i = 0; i < 1000; i++) {
        manager->ResetBuffer();
        manager->WriteByteVector_Optional(buffer, i);
        
        manager->ResetBuffer();
        manager->ReadByteVector_Optional(buffer2, &length, 1000);
        if (length != i)
            throw;
        for (int j = 0; j < i; j++) {
            if (buffer2[j] != buffer[j])
                throw;
        }
    }
}

void FastProtocolTester::TestReadByteVector_Mandatory() {
    printf("Test FastProtocolTester::TestReadByteVector_Mandatory\n");

    manager->SetNewBuffer(new unsigned char[1000], 1000);

    BYTE *buffer = new BYTE[1000];
    BYTE *buffer2 = new BYTE[1000];
    for (int i = 0; i < 1000; i++) {
        buffer[i] = (char)('A' + i % 60);
    }

    int length = 0;
    for (int i = 0; i < 900; i++) {
        manager->ResetBuffer();
        manager->WriteByteVector_Mandatory(buffer, i);

        manager->ResetBuffer();
        manager->ReadByteVector_Mandatory(buffer2, &length, 900);
        if (length != i)
            throw;
        for (int j = 0; j < i; j++) {
            if (buffer2[j] != buffer[j])
                throw;
        }
    }
}

void FastProtocolTester::TestReadDecimal_Optional() { 
    printf("Test FastProtocolTester::TestReadDecimal_Optional\n");

    Decimal value(942755, 2);
    manager->WriteDecimal_Optional(&value);

    if (manager->MessageLength() != 4)
        throw;
    if (!manager->CheckBuffer(new BYTE[4] { 0x83, 0x39, 0x45, 0xa3 }, 4))
        throw;

    value.Set(-942755, -2);
    manager->ResetBuffer();
    manager->WriteDecimal_Optional(&value);

    if (manager->MessageLength() != 4)
        throw;
    if (!manager->CheckBuffer(new BYTE[4] { 0xfe, 0x46, 0x3a, 0xdd }, 4))
        throw;
    
    value.Set(-8193, -3);
    manager->ResetBuffer();
    manager->WriteDecimal_Optional(&value);

    if (manager->MessageLength() != 4)
        throw;
    if (!manager->CheckBuffer(new BYTE[4] { 0xfd, 0x7f, 0x3f, 0xff }, 4))
        throw;
}

void FastProtocolTester::TestReadDecimal_Mandatory() {
    printf("Test FastProtocolTester::TestReadDecimal_Mandatory\n");

    Decimal value = { 942755, 2 };
    manager->WriteDecimal_Mandatory(&value);

    if (manager->MessageLength() != 4)
        throw;
    if (!manager->CheckBuffer(new BYTE[4] { 0x82, 0x39, 0x45, 0xa3 }, 4))
        throw;

    value = { 9427550, 1 };
    manager->ResetBuffer();
    manager->WriteDecimal_Mandatory(&value);

    if (manager->MessageLength() != 5)
        throw;
    if (!manager->CheckBuffer(new BYTE[5] { 0x81, 0x04, 0x3f, 0x34, 0xde }, 5))
        throw;

    value = { 942755, -2 };
    manager->ResetBuffer();
    manager->WriteDecimal_Mandatory(&value);

    if (manager->MessageLength() != 4)
        throw;
    if (!manager->CheckBuffer(new BYTE[4] { 0xfe, 0x39, 0x45, 0xa3 }, 4))
        throw;
}

void FastProtocolTester::TestReadInt64_Optional() {
    printf("Test FastProtocolTester::TestReadInt64_Optional\n");

    BYTE buffer[12];
    for (int i = 1; i < 10; i++) { // extended positive
        memset(buffer, 0, 12);
        for (int j = 1; j <= i; j++) { 
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 1)
                buffer[j] |= 0x40;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);
        
        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Optional();
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Optional(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Optional();
        if (value2 != value)
            throw;
    }

    for (int i = 0; i < 9; i++) { // positive
        memset(buffer, 0, 12);
        for (int j = 0; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 0)
                buffer[j] &= 0xbf;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Optional();
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Optional(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Optional();
        if (value2 != value)
            throw;
    }

    for (int i = 1; i < 10; i++) { // extended negative
        memset(buffer, 0, 12);
        buffer[0] = 0x7f;
        for (int j = 1; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 1)
                buffer[j] &= 0xbf;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Optional();
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Optional(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Optional();
        if (value2 != value)
            throw;
    }

    for (int i = 0; i < 9; i++) { // simple negative
        memset(buffer, 0, 12);
        for (int j = 0; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 0) {
                buffer[j] |= 0x40;
                buffer[j] &= 0xfe;
            }
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Optional();
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Optional(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Optional();
        if (value2 != value)
            throw;
    }
}

void FastProtocolTester::TestReadInt64_Mandatory() {
    printf("Test FastProtocolTester::TestReadInt64_Mandatory\n");
    manager->SetNewBuffer(new unsigned char[128], 128);

    INT64 min = INT64_MIN + 10;
    /*
    for (INT64 i = 0; i > min; i -= 5) {
        manager->ResetBuffer();
        manager->WriteInt64_Mandatory(i);
        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Mandatory();
        if (value != i)
            throw;
        if ((i % 1000000) == 0)
            printf("%" PRIu64 "\n", i);
    }

    for (INT64 i = 0; i < 0x7ffffffffffffff0; i += 5) {
        manager->ResetBuffer();
        manager->WriteInt64_Mandatory(i);
        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Mandatory();
        if (value != i)
            throw;
        if ((i % 1000000) == 0)
            printf("%" PRIu64 "\n", i);
    }
    */

    BYTE buffer[12];
    for (int i = 1; i < 10; i++) { // extended positive
        memset(buffer, 0, 12);
        for (int j = 1; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 1)
                buffer[j] |= 0x40;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Mandatory();
        if(manager->MessageLength() != i + 1)
            throw;
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Mandatory(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Mandatory();
        if (value2 != value)
            throw;
    }

    for (int i = 0; i < 9; i++) { // positive
        memset(buffer, 0, 12);
        for (int j = 0; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 0)
                buffer[j] &= 0xbf;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Mandatory();
        if(manager->MessageLength() != i + 1)
            throw;
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Mandatory(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Mandatory();
        if (value2 != value)
            throw;
    }

    for (int i = 1; i < 10; i++) { // extended negative
        memset(buffer, 0, 12);
        buffer[0] = 0x7f;
        for (int j = 1; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 1)
                buffer[j] &= 0xbf;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Mandatory();
        if(manager->MessageLength() != i + 1)
            throw;
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Mandatory(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Mandatory();
        if (value2 != value)
            throw;
    }

    for (int i = 0; i < 9; i++) { // simple negative
        memset(buffer, 0, 12);
        for (int j = 0; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 0)
                buffer[j] |= 0x40;
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        INT64 value = manager->ReadInt64_Mandatory();
        if(manager->MessageLength() != i + 1)
            throw;
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteInt64_Mandatory(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        INT64 value2 = manager->ReadInt64_Mandatory();
        if (value2 != value)
            throw;
    }

    INT64 value = 0x7fffffffffffffff;
    manager->ResetBuffer();
    manager->WriteInt64_Mandatory(value);
    manager->ResetBuffer();
    INT64 value2 = manager->ReadInt64_Mandatory();
    if (value != value2)
        throw;
}

void FastProtocolTester::TestReadUInt64_Mandatory() {
    printf("Test FastProtocolTester::TestReadUInt64_Mandatory\n");

    BYTE buffer[12];

    //00 72 40 0d 6e 79 6c 21 ab
    buffer[0] = 0x01;
    buffer[1] = 0x72;
    buffer[2] = 0x0d;
    buffer[3] = 0x6e;
    buffer[4] = 0x79;
    buffer[5] = 0x6c;
    buffer[6] = 0x21;
    buffer[7] = 0xab;

    manager->ResetBuffer();
    manager->CopyToBuffer(buffer, 8);
    UINT64 v = manager->ReadUInt64_Mandatory();
    manager->ResetBuffer();
    manager->WriteUInt64_Mandatory(v);
    if (!manager->CheckBuffer(buffer, 8))
        throw;
    manager->ResetBuffer();
    UINT64 v2 = manager->ReadUInt64_Mandatory();
    if (v2 != v)
        throw;

    for (int i = 0; i < 9; i++) { // positive
        memset(buffer, 0, 12);
        for (int j = 0; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 0) {
                buffer[j] &= 0xbf;
                buffer[j] |= 0x01;
            }
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        UINT64 value = manager->ReadUInt64_Mandatory();
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteUInt64_Mandatory(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        UINT64 value2 = manager->ReadUInt64_Mandatory();
        if (value2 != value)
            throw;
    }

    UINT64 value = 0xffffffffffffffff;
    manager->ResetBuffer();
    manager->WriteUInt64_Mandatory(value);
    manager->ResetBuffer();
    UINT64 value2 = manager->ReadUInt64_Mandatory();
    if (value != value2)
        throw;
}

void FastProtocolTester::TestReadUInt64_Optional() {
    printf("Test FastProtocolTester::TestReadUInt64_Optional\n");
    manager->SetNewBuffer(new unsigned char[12], 12);

    BYTE buffer[12];

    for (int i = 0; i < 9; i++) { // positive
        memset(buffer, 0, 12);
        for (int j = 0; j <= i; j++) {
            buffer[j] = (rand() % 0xff) & 0x7f;
            if (j == 0) {
                buffer[j] &= 0xbf;
                buffer[j] |= 0x01;
            }
        }
        buffer[i] |= 0x80;
        manager->CopyToBuffer(buffer, i + 1);

        manager->ResetBuffer();
        UINT64 value = manager->ReadUInt64_Optional();
        manager->ResetBuffer();

        manager->ClearBuffer();
        manager->WriteUInt64_Optional(value);

        if (!manager->CheckBuffer(buffer, i + 1))
            throw;

        manager->ResetBuffer();
        UINT64 value2 = manager->ReadUInt64_Optional();
        if (value2 != value)
            throw;
    }

    UINT64 value = 0xfffffffffffffffe;
    manager->ResetBuffer();
    manager->WriteUInt64_Optional(value);
    manager->ResetBuffer();
    UINT64 value2 = manager->ReadUInt64_Optional();
    if (value != value2)
        throw;
}

void FastProtocolTester::TestParsePresenceMap() {
    /*FastProtocolManager *manager = new FastProtocolManager(new AstsObjectsAllocationInfo(128,128));
    
    *(manager->Buffer()) = 0x80;
    manager->ParsePresenceMap();

    if (manager->CurrentPos() - manager->Buffer() != 1) {
        printf_s("ParsePresenceMap: expected 1 but was %d", manager->CurrentPos() - manager->Buffer());
        throw;
    }
    for (int i = 0; i < 8; i++) { 
        if (manager->PresenceMap()[i] != 0) { 
            printf_s("ParsePresenceMap: expected 0 but was %d", manager->PresenceMap()[i]);
            throw;
        }
    }
    
    for (int j = 1; j < 100;  j++) {
        manager->ResetBuffer();
        for (int l = 0; l < j - 1; l++)  {
            manager->Buffer()[l] = 0x7f;
        }
        manager->Buffer()[j - 1] = 0xff;
        manager->ParsePresenceMap();
        
        if (manager->CurrentPos() - manager->Buffer() != j) {
            printf_s("ParsePresenceMap: expected %d but was %d", j, manager->CurrentPos() - manager->Buffer());
            throw;
        }

        for (int i = 0; i < 7 * j; i++) { 
            if (manager->PresenceMap()[i] != 1) {
                printf_s("ParsePresenceMap: expected 1 but was %d", manager->PresenceMap()[i]);
                throw;
            }
        }
    }
    
    delete manager;*/
}

#endif //TEST