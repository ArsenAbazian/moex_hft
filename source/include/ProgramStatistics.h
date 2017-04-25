//
// Created by root on 21.02.17.
//

#ifndef HFT_ROBOT_PROGRAMSTATISTICS_H
#define HFT_ROBOT_PROGRAMSTATISTICS_H

#include <stdio.h>
#include <string.h>

#define COLLECT_STATISTICS

typedef enum _Counters {
#pragma region ProgramStatistics_Enum
	cFondOlr = 0, // fond olr
	cFondOls = 1, // fond ols
	cCurrOlr = 2, // curr olr
	cCurrOls = 3, // curr ols
	cFondIdf = 4, // fond idf
	cCurrIdf = 5, // curr idf
	cFondTlr = 6, // fond tlr
	cFondTls = 7, // fond tls
	cCurrTlr = 8, // curr tlr
	cCurrTls = 9, // curr tls
	cFondMsr = 10, // fond msr
	cFondMss = 11, // fond mss
	cCurrMsr = 12, // curr msr
	cCurrMss = 13, // curr mss
	cFondIss = 14, // fond iss
	cCurrIss = 15, // curr iss
	cFondOlrLost = 16, // fond olr lost
	cFondOlsLost = 17, // fond ols lost
	cCurrOlrLost = 18, // curr olr lost
	cCurrOlsLost = 19, // curr ols lost
	cFondIdfLost = 20, // fond idf lost
	cCurrIdfLost = 21, // curr idf lost
	cFondTlrLost = 22, // fond tlr lost
	cFondTlsLost = 23, // fond tls lost
	cCurrTlrLost = 24, // curr tlr lost
	cCurrTlsLost = 25, // curr tls lost
	cFondMsrLost = 26, // fond msr lost
	cFondMssLost = 27, // fond mss lost
	cCurrMsrLost = 28, // curr msr lost
	cCurrMssLost = 29, // curr mss lost
	cFondIssLost = 30, // fond iss lost
	cCurrIssLost = 31, // curr iss lost
	cAddOlr = 32, // add olr
	cRemoveOlr = 33, // remove olr
	cChangeOlr = 34, // change olr
	cAddObr = 35, // add obr
	cRemoveObr = 36, // add obr
	cChangeObr = 37, // change obr
	cReadInt32MandatoryEp_1Byte = 38, // read i32m ep 1 byte
	cReadInt32MandatoryEp_2Byte = 39, // read i32m ep 2 byte
	cReadInt32MandatoryEp_3Byte = 40, // read i32m ep 3 byte
	cReadInt32MandatoryEp_4Byte = 41, // read i32m ep 4 byte
	cReadInt32MandatoryEp_5Byte = 42, // read i32m ep 5 byte
	cReadInt32MandatoryEp_6Byte = 43, // read i32m ep 6 byte
	cReadInt32MandatoryEn_1Byte = 44, // read i32m en 1 byte
	cReadInt32MandatoryEn_2Byte = 45, // read i32m en 2 byte
	cReadInt32MandatoryEn_3Byte = 46, // read i32m en 3 byte
	cReadInt32MandatoryEn_4Byte = 47, // read i32m en 4 byte
	cReadInt32MandatoryEn_5Byte = 48, // read i32m en 5 byte
	cReadInt32MandatoryEn_6Byte = 49, // read i32m en 6 byte
	cReadInt32MandatorySn_1Byte = 50, // read i32m sn 1 byte
	cReadInt32MandatorySn_2Byte = 51, // read i32m sn 2 byte
	cReadInt32MandatorySn_3Byte = 52, // read i32m sn 3 byte
	cReadInt32MandatorySn_4Byte = 53, // read i32m sn 4 byte
	cReadInt32MandatorySn_5Byte = 54, // read i32m sn 5 byte
	cReadInt32MandatorySn_6Byte = 55, // read i32m sn 6 byte
	cReadInt32MandatorySp_1Byte = 56, // read i32m sp 1 byte
	cReadInt32MandatorySp_2Byte = 57, // read i32m sp 2 byte
	cReadInt32MandatorySp_3Byte = 58, // read i32m sp 3 byte
	cReadInt32MandatorySp_4Byte = 59, // read i32m sp 4 byte
	cReadInt32MandatorySp_5Byte = 60, // read i32m sp 5 byte
	cReadInt32MandatorySp_6Byte = 61, // read i32m sp 6 byte
	cReadUInt32Mandatory_1Byte = 62, // read u32m 1 byte
	cReadUInt32Mandatory_2Byte = 63, // read u32m 2 byte
	cReadUInt32Mandatory_3Byte = 64, // read u32m 3 byte
	cReadUInt32Mandatory_4Byte = 65, // read u32m 4 byte
	cReadUInt32Mandatory_5Byte = 66, // read u32m 5 byte
	cReadUInt32Mandatory_6Byte = 67, // read u32m 6 byte
	cReadInt64MandatoryEp_1Byte = 68, // read i64m ep 1 byte
	cReadInt64MandatoryEp_2Byte = 69, // read i64m ep 2 byte
	cReadInt64MandatoryEp_3Byte = 70, // read i64m ep 3 byte
	cReadInt64MandatoryEp_4Byte = 71, // read i64m ep 4 byte
	cReadInt64MandatoryEp_5Byte = 72, // read i64m ep 5 byte
	cReadInt64MandatoryEp_6Byte = 73, // read i64m ep 6 byte
	cReadInt64MandatoryEp_7Byte = 74, // read i64m ep 7 byte
	cReadInt64MandatoryEp_8Byte = 75, // read i64m ep 8 byte
	cReadInt64MandatoryEp_9Byte = 76, // read i64m ep 9 byte
	cReadInt64MandatoryEp_10Byte = 77, // read i64m ep 10 byte
	cReadInt64MandatoryEp_11Byte = 78, // read i64m ep 11 byte
	cReadInt64MandatoryEn_1Byte = 79, // read i64m en 1 byte
	cReadInt64MandatoryEn_2Byte = 80, // read i64m en 2 byte
	cReadInt64MandatoryEn_3Byte = 81, // read i64m en 3 byte
	cReadInt64MandatoryEn_4Byte = 82, // read i64m en 4 byte
	cReadInt64MandatoryEn_5Byte = 83, // read i64m en 5 byte
	cReadInt64MandatoryEn_6Byte = 84, // read i64m en 6 byte
	cReadInt64MandatoryEn_7Byte = 85, // read i64m en 7 byte
	cReadInt64MandatoryEn_8Byte = 86, // read i64m en 8 byte
	cReadInt64MandatoryEn_9Byte = 87, // read i64m en 9 byte
	cReadInt64MandatoryEn_10Byte = 88, // read i64m en 10 byte
	cReadInt64MandatoryEn_11Byte = 89, // read i64m en 11 byte
	cReadInt64MandatorySn_1Byte = 90, // read i64m sn 1 byte
	cReadInt64MandatorySn_2Byte = 91, // read i64m sn 2 byte
	cReadInt64MandatorySn_3Byte = 92, // read i64m sn 3 byte
	cReadInt64MandatorySn_4Byte = 93, // read i64m sn 4 byte
	cReadInt64MandatorySn_5Byte = 94, // read i64m sn 5 byte
	cReadInt64MandatorySn_6Byte = 95, // read i64m sn 6 byte
	cReadInt64MandatorySn_7Byte = 96, // read i64m sn 7 byte
	cReadInt64MandatorySn_8Byte = 97, // read i64m sn 8 byte
	cReadInt64MandatorySn_9Byte = 98, // read i64m sn 9 byte
	cReadInt64MandatorySn_10Byte = 99, // read i64m sn 10 byte
	cReadInt64MandatorySn_11Byte = 100, // read i64m sn 11 byte
	cReadInt64MandatorySp_1Byte = 101, // read i64m sp 1 byte
	cReadInt64MandatorySp_2Byte = 102, // read i64m sp 2 byte
	cReadInt64MandatorySp_3Byte = 103, // read i64m sp 3 byte
	cReadInt64MandatorySp_4Byte = 104, // read i64m sp 4 byte
	cReadInt64MandatorySp_5Byte = 105, // read i64m sp 5 byte
	cReadInt64MandatorySp_6Byte = 106, // read i64m sp 6 byte
	cReadInt64MandatorySp_7Byte = 107, // read i64m sp 7 byte
	cReadInt64MandatorySp_8Byte = 108, // read i64m sp 8 byte
	cReadInt64MandatorySp_9Byte = 109, // read i64m sp 9 byte
	cReadInt64MandatorySp_10Byte = 110, // read i64m sp 10 byte
	cReadInt64MandatorySp_11Byte = 111, // read i64m sp 11 byte
	cReadUInt64Mandatory_1Byte = 112, // read u64m 1 byte
	cReadUInt64Mandatory_2Byte = 113, // read u64m 2 byte
	cReadUInt64Mandatory_3Byte = 114, // read u64m 3 byte
	cReadUInt64Mandatory_4Byte = 115, // read u64m 4 byte
	cReadUInt64Mandatory_5Byte = 116, // read u64m 5 byte
	cReadUInt64Mandatory_6Byte = 117, // read u64m 6 byte
	cReadUInt64Mandatory_7Byte = 118, // read u64m 7 byte
	cReadUInt64Mandatory_8Byte = 119, // read u64m 8 byte
	cReadUInt64Mandatory_9Byte = 120, // read u64m 9 byte
	cReadUInt64Mandatory_10Byte = 121, // read u64m 10 byte
	cReadUInt64Mandatory_11Byte = 122, // read u64m 11 byte
	cOlrMDEntryCount = 123, // olr mdentry count [128]
#pragma endregion
}Counters;

class ProgramStatistics {
	int             *m_counts;
    bool            *m_changed;
    const char     **m_names;
    int             m_itemsCount;
#pragma region ProgramStatistics_GeneratedFields
	int			m_cOlrMDEntryCount[128];
#pragma endregion
public:
    ProgramStatistics() {
        this->InitializeNames();
        this->Clear();
    }

    void InitializeNames() {
#pragma region ProgramStatistics_GeneratedCode
		this->m_itemsCount = 124;
		this->m_counts = new int[ this->m_itemsCount ];
		this->m_changed = new bool[ this->m_itemsCount ];
		this->m_names = new const char*[124];
		memset(this->m_cOlrMDEntryCount, 0, sizeof(int) * 128);
		this->m_names[0] = "fond olr";
		this->m_names[1] = "fond ols";
		this->m_names[2] = "curr olr";
		this->m_names[3] = "curr ols";
		this->m_names[4] = "fond idf";
		this->m_names[5] = "curr idf";
		this->m_names[6] = "fond tlr";
		this->m_names[7] = "fond tls";
		this->m_names[8] = "curr tlr";
		this->m_names[9] = "curr tls";
		this->m_names[10] = "fond msr";
		this->m_names[11] = "fond mss";
		this->m_names[12] = "curr msr";
		this->m_names[13] = "curr mss";
		this->m_names[14] = "fond iss";
		this->m_names[15] = "curr iss";
		this->m_names[16] = "fond olr lost";
		this->m_names[17] = "fond ols lost";
		this->m_names[18] = "curr olr lost";
		this->m_names[19] = "curr ols lost";
		this->m_names[20] = "fond idf lost";
		this->m_names[21] = "curr idf lost";
		this->m_names[22] = "fond tlr lost";
		this->m_names[23] = "fond tls lost";
		this->m_names[24] = "curr tlr lost";
		this->m_names[25] = "curr tls lost";
		this->m_names[26] = "fond msr lost";
		this->m_names[27] = "fond mss lost";
		this->m_names[28] = "curr msr lost";
		this->m_names[29] = "curr mss lost";
		this->m_names[30] = "fond iss lost";
		this->m_names[31] = "curr iss lost";
		this->m_names[32] = "add olr";
		this->m_names[33] = "remove olr";
		this->m_names[34] = "change olr";
		this->m_names[35] = "add obr";
		this->m_names[36] = "add obr";
		this->m_names[37] = "change obr";
		this->m_names[38] = "read i32m ep 1 byte";
		this->m_names[39] = "read i32m ep 2 byte";
		this->m_names[40] = "read i32m ep 3 byte";
		this->m_names[41] = "read i32m ep 4 byte";
		this->m_names[42] = "read i32m ep 5 byte";
		this->m_names[43] = "read i32m ep 6 byte";
		this->m_names[44] = "read i32m en 1 byte";
		this->m_names[45] = "read i32m en 2 byte";
		this->m_names[46] = "read i32m en 3 byte";
		this->m_names[47] = "read i32m en 4 byte";
		this->m_names[48] = "read i32m en 5 byte";
		this->m_names[49] = "read i32m en 6 byte";
		this->m_names[50] = "read i32m sn 1 byte";
		this->m_names[51] = "read i32m sn 2 byte";
		this->m_names[52] = "read i32m sn 3 byte";
		this->m_names[53] = "read i32m sn 4 byte";
		this->m_names[54] = "read i32m sn 5 byte";
		this->m_names[55] = "read i32m sn 6 byte";
		this->m_names[56] = "read i32m sp 1 byte";
		this->m_names[57] = "read i32m sp 2 byte";
		this->m_names[58] = "read i32m sp 3 byte";
		this->m_names[59] = "read i32m sp 4 byte";
		this->m_names[60] = "read i32m sp 5 byte";
		this->m_names[61] = "read i32m sp 6 byte";
		this->m_names[62] = "read u32m 1 byte";
		this->m_names[63] = "read u32m 2 byte";
		this->m_names[64] = "read u32m 3 byte";
		this->m_names[65] = "read u32m 4 byte";
		this->m_names[66] = "read u32m 5 byte";
		this->m_names[67] = "read u32m 6 byte";
		this->m_names[68] = "read i64m ep 1 byte";
		this->m_names[69] = "read i64m ep 2 byte";
		this->m_names[70] = "read i64m ep 3 byte";
		this->m_names[71] = "read i64m ep 4 byte";
		this->m_names[72] = "read i64m ep 5 byte";
		this->m_names[73] = "read i64m ep 6 byte";
		this->m_names[74] = "read i64m ep 7 byte";
		this->m_names[75] = "read i64m ep 8 byte";
		this->m_names[76] = "read i64m ep 9 byte";
		this->m_names[77] = "read i64m ep 10 byte";
		this->m_names[78] = "read i64m ep 11 byte";
		this->m_names[79] = "read i64m en 1 byte";
		this->m_names[80] = "read i64m en 2 byte";
		this->m_names[81] = "read i64m en 3 byte";
		this->m_names[82] = "read i64m en 4 byte";
		this->m_names[83] = "read i64m en 5 byte";
		this->m_names[84] = "read i64m en 6 byte";
		this->m_names[85] = "read i64m en 7 byte";
		this->m_names[86] = "read i64m en 8 byte";
		this->m_names[87] = "read i64m en 9 byte";
		this->m_names[88] = "read i64m en 10 byte";
		this->m_names[89] = "read i64m en 11 byte";
		this->m_names[90] = "read i64m sn 1 byte";
		this->m_names[91] = "read i64m sn 2 byte";
		this->m_names[92] = "read i64m sn 3 byte";
		this->m_names[93] = "read i64m sn 4 byte";
		this->m_names[94] = "read i64m sn 5 byte";
		this->m_names[95] = "read i64m sn 6 byte";
		this->m_names[96] = "read i64m sn 7 byte";
		this->m_names[97] = "read i64m sn 8 byte";
		this->m_names[98] = "read i64m sn 9 byte";
		this->m_names[99] = "read i64m sn 10 byte";
		this->m_names[100] = "read i64m sn 11 byte";
		this->m_names[101] = "read i64m sp 1 byte";
		this->m_names[102] = "read i64m sp 2 byte";
		this->m_names[103] = "read i64m sp 3 byte";
		this->m_names[104] = "read i64m sp 4 byte";
		this->m_names[105] = "read i64m sp 5 byte";
		this->m_names[106] = "read i64m sp 6 byte";
		this->m_names[107] = "read i64m sp 7 byte";
		this->m_names[108] = "read i64m sp 8 byte";
		this->m_names[109] = "read i64m sp 9 byte";
		this->m_names[110] = "read i64m sp 10 byte";
		this->m_names[111] = "read i64m sp 11 byte";
		this->m_names[112] = "read u64m 1 byte";
		this->m_names[113] = "read u64m 2 byte";
		this->m_names[114] = "read u64m 3 byte";
		this->m_names[115] = "read u64m 4 byte";
		this->m_names[116] = "read u64m 5 byte";
		this->m_names[117] = "read u64m 6 byte";
		this->m_names[118] = "read u64m 7 byte";
		this->m_names[119] = "read u64m 8 byte";
		this->m_names[120] = "read u64m 9 byte";
		this->m_names[121] = "read u64m 10 byte";
		this->m_names[122] = "read u64m 11 byte";
		this->m_names[123] = "olr mdentry count ";
#pragma endregion
    }

    static ProgramStatistics       *Current;
    static ProgramStatistics       *Total;

#pragma region ProgramStatistics_GeneratedMethods
	inline int* CounterIndex(Counters c) {
		if(c == Counters::cOlrMDEntryCount)
			return (int*)this->m_cOlrMDEntryCount;
		return 0;
	}
	inline int CounterSize(Counters c) {
		if(c == Counters::cOlrMDEntryCount)
			return 128;
		return 0;
	}
#pragma endregion

	inline int Counter(Counters c, int index) {
		return this->CounterIndex(c)[index];
	}
	inline void Set(Counters c, int index, int value) {
		this->CounterIndex(c)[index] = value;
		this->m_changed[c] = true;
	}
	inline void IncIndex(Counters c, int index) {
		this->CounterIndex(c)[index]++;
		this->m_changed[c] = true;
	}
	inline void Inc(Counters c, int index, int value) {
		this->CounterIndex(c)[index] += value;
		this->m_changed[c] = true;
	}
	inline void Max(Counters c, int index, int value) {
		int *array = this->CounterIndex(c);
		if(array[index] < value) {
			array[index] = value;
			m_changed[c] = true;
		}
	}

    inline int Counter(Counters c) { return this->m_counts[c]; }
    inline void Set(Counters c, int value) {
        if(this->m_counts[c] == value)
            return;
        this->m_counts[c] = value;
        this->m_changed[c] = true;
    }
    inline void Inc(Counters c) {
        this->m_counts[c]++;
        this->m_changed[c] = true;
    }
    inline void Inc(Counters c, int value) {
        this->m_counts[c] += value;
        this->m_changed[c] = true;
    }
    inline void Max(Counters c, int value) {
        if(this->m_counts[c] < value) {
            this->m_counts[c] = value;
            this->m_changed[c] = true;
        }
    }
    inline void Clear() {
        memset(this->m_counts, 0, sizeof(int) * this->m_itemsCount);
#pragma region ProgramStatistics_GeneratedClearCode
		memset(this->m_cOlrMDEntryCount, 0, sizeof(int) * 128);
#pragma endregion
        this->ResetFlags();
    }

    inline void Print() {
        for(int i = 0; i < this->m_itemsCount; i++) {
            if(this->m_changed[i]) {
				if(CounterIndex((Counters)i) != 0) {
					printf("%s = ", this->m_names[i]);
					for(int j = 0; j < this->CounterSize((Counters)i); j++) {
						printf("%d = %d  ", j, this->Counter((Counters)i, j));
					}
					printf("\n");
				}
				else
					printf("%s = %d\n", this->m_names[i], this->m_counts[i]);
            }
        }
    }

	inline int WriteToBuffer(unsigned char *buffer) {
		int index = 0;
		for(int i = 0; i < this->m_itemsCount; i++) {
			if (!this->m_changed[i]) continue;
			*((unsigned short*)(buffer + index)) = (unsigned short)i;
			*((int*)(buffer + index + sizeof(unsigned short))) = this->m_counts[i];
			index += sizeof(unsigned short) + sizeof(int);
		}
		return index;
	}

    inline void ResetFlags() {
        memset(this->m_changed, 0, sizeof(bool) * this->m_itemsCount);
    }
};

#endif //HFT_ROBOT_PROGRAMSTATISTICS_H
