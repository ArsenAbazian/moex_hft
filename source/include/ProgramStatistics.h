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
    cReadInt1Byte = 38, // read int 1 byte
    cReadInt2Byte = 39, // read int 2 byte
    cReadInt3Byte = 40, // read int 3 byte
    cReadInt4Byte = 41, // read int 4 byte
    cReadInt5Byte = 42, // read int 5 byte
    cReadInt6Byte = 43, // read int 6 byte
    cReadInt7Byte = 43, // read int 7 byte
    cReadInt8Byte = 43, // read int 8 byte
    cReadInt9Byte = 43, // read int 9 byte
    cReadInt10Byte = 43, // read int 10 byte
#pragma endregion
}Counters;

class ProgramStatistics {
    int             *m_counts;
    bool            *m_changed;
    const char     **m_names;
    int             m_itemsCount;
public:
    ProgramStatistics() {
        this->InitializeNames();
        this->Clear();
    }

    void InitializeNames() {
#pragma region ProgramStatistics_GeneratedCode
		this->m_itemsCount = 38;
		this->m_counts = new int[ this->m_itemsCount ];
		this->m_changed = new bool[ this->m_itemsCount ];
		this->m_names = new const char*[38];
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
#pragma endregion
    }

    static ProgramStatistics       *Current;
    static ProgramStatistics       *Total;

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

        this->ResetFlags();
    }

    inline void Print() {
        printf("------------------------------------\n");
        for(int i = 0; i < this->m_itemsCount; i++) {
            if(this->m_changed[i]) {
				//std::cout2 << this->m_names[i] << " = " << this->m_counts[i];
				printf("%s = %d\n", this->m_names[i], this->m_counts[i]);
			}
        }
    }

    inline void ResetFlags() {
        memset(this->m_changed, 0, sizeof(bool) * this->m_itemsCount);
    }
};

#endif //HFT_ROBOT_PROGRAMSTATISTICS_H
