//
// Created by root on 21.02.17.
//

#ifndef HFT_ROBOT_PROGRAMSTATISTICS_H
#define HFT_ROBOT_PROGRAMSTATISTICS_H

#include <stdio.h>

#define COLLECT_STATISTICS

class ProgramStatistics {
    int     m_fondOlrProcessedCount;
    int     m_fondOlsProcessedCount;
    int     m_currOlrProcessedCount;
    int     m_currOlsProcessedCount;
    int     m_fondIdfProcessedCount;
    int     m_currIdfProcessedCount;

    bool    m_fondOlrProcessedCountChanged;
    bool    m_fondOlsProcessedCountChanged;
    bool    m_currOlrProcessedCountChanged;
    bool    m_currOlsProcessedCountChanged;
    bool    m_fondIdfProcessedCountChanged;
    bool    m_currIdfProcessedCountChanged;
public:
    ProgramStatistics() {
        this->Clear();
    }

    static ProgramStatistics       *Current;
    static ProgramStatistics       *Total;

    inline int FondOlrProcessedCount() { return this->m_fondOlrProcessedCount; }
    inline int FondOlsProcessedCount() { return this->m_fondOlsProcessedCount; }
    inline int CurrOlrProcessedCount() { return this->m_currOlrProcessedCount; }
    inline int CurrOlsProcessedCount() { return this->m_currOlsProcessedCount; }
    inline int FondIdfProcessedCount() { return this->m_fondIdfProcessedCount; }
    inline int CurrIdfProcessedCount() { return this->m_currIdfProcessedCount; }

    inline void FondOlrProcessedCount(int value) {
        if(this->m_fondOlrProcessedCount == value)
            return;
        this->m_fondOlrProcessedCount = value;
        this->m_fondOlrProcessedCountChanged = true;
    }
    inline void FondOlsProcessedCount(int value) {
        if(this->m_fondOlsProcessedCount == value)
            return;
        this->m_fondOlsProcessedCount = value;
        this->m_fondOlsProcessedCountChanged = true;
    }
    inline void CurrOlrProcessedCount(int value) {
        if(this->m_currOlrProcessedCount == value)
            return;
        this->m_currOlrProcessedCount = value;
        this->m_currOlrProcessedCountChanged = true;
    }
    inline void CurrOlsProcessedCount(int value) {
        if(this->m_currOlsProcessedCount == value)
            return;
        this->m_currOlsProcessedCount = value;
        this->m_currOlsProcessedCountChanged = true;
    }
    inline void FondIdfProcessedCount(int value) {
        if(this->m_fondIdfProcessedCount == value)
            return;
        this->m_fondIdfProcessedCount = value;
        this->m_fondIdfProcessedCountChanged = true;
    }
    inline void CurrIdfProcessedCount(int value) {
        if(this->m_currIdfProcessedCount == value)
            return;
        this->m_currIdfProcessedCount = value;
        this->m_currIdfProcessedCountChanged = true;
    }

    inline void IncFondOlrProcessedCount() {
        this->m_fondOlrProcessedCount++;
        this->m_fondOlrProcessedCountChanged = true;
    }
    inline void IncFondOlsProcessedCount() {
        this->m_fondOlsProcessedCount++;
        this->m_fondOlsProcessedCountChanged = true;
    }
    inline void IncCurrOlrProcessedCount() {
        this->m_currOlrProcessedCount++;
        this->m_currOlrProcessedCountChanged = true;
    }
    inline void IncCurrOlsProcessedCount() {
        this->m_currOlsProcessedCount++;
        this->m_currOlsProcessedCountChanged = true;
    }
    inline void IncFondIdfProcessedCount() {
        this->m_fondIdfProcessedCount++;
        this->m_fondIdfProcessedCountChanged = true;
    }
    inline void IncCurrIdfProcessedCount() {
        this->m_currIdfProcessedCount++;
        this->m_currIdfProcessedCountChanged = true;
    }

    inline void Clear() {
        this->m_fondOlrProcessedCount = 0;
        this->m_fondOlsProcessedCount = 0;
        this->m_currOlrProcessedCount = 0;
        this->m_currOlsProcessedCount = 0;
        this->m_fondIdfProcessedCount = 0;
        this->m_currIdfProcessedCount = 0;

        this->ResetFlags();
    }

    inline void Print() {
        if(this->m_fondOlrProcessedCountChanged)
            printf("fond olr processed messages count = %d\n", this->m_fondOlrProcessedCount);
        if(this->m_fondOlsProcessedCountChanged)
            printf("fond ols processed messages count = %d\n", this->m_fondOlsProcessedCount);
        if(this->m_fondIdfProcessedCountChanged)
            printf("fond idf processed messages count = %d\n", this->m_fondIdfProcessedCount);

        if(this->m_currOlrProcessedCountChanged)
            printf("curr olr processed messages count = %d\n", this->m_currOlrProcessedCount);
        if(this->m_currOlsProcessedCountChanged)
            printf("curr ols processed messages count = %d\n", this->m_currOlsProcessedCount);
        if(this->m_currIdfProcessedCountChanged)
            printf("curr idf processed messages count = %d\n", this->m_currIdfProcessedCount);
    }

    inline void ResetFlags() {
        this->m_fondOlrProcessedCountChanged = false;
        this->m_fondOlsProcessedCountChanged = false;
        this->m_currOlrProcessedCountChanged = false;
        this->m_currOlsProcessedCountChanged = false;
        this->m_fondIdfProcessedCountChanged = false;
        this->m_currIdfProcessedCountChanged = false;
    }
};

#endif //HFT_ROBOT_PROGRAMSTATISTICS_H
