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
    int     m_fondTlrProcessedCount;
    int     m_fondTlsProcessedCount;
    int     m_fondMsrProcessedCount;
    int     m_fondMssProcessedCount;
    int     m_currTlrProcessedCount;
    int     m_currTlsProcessedCount;
    int     m_currMsrProcessedCount;
    int     m_currMssProcessedCount;
    int     m_fondIssProcessedCount;
    int     m_currIssProcessedCount;

    bool    m_fondOlrProcessedCountChanged;
    bool    m_fondOlsProcessedCountChanged;
    bool    m_currOlrProcessedCountChanged;
    bool    m_currOlsProcessedCountChanged;
    bool    m_fondIdfProcessedCountChanged;
    bool    m_currIdfProcessedCountChanged;
    bool    m_fondTlrProcessedCountChanged;
    bool    m_fondTlsProcessedCountChanged;
    bool    m_fondMsrProcessedCountChanged;
    bool    m_fondMssProcessedCountChanged;
    bool    m_currTlrProcessedCountChanged;
    bool    m_currTlsProcessedCountChanged;
    bool    m_currMsrProcessedCountChanged;
    bool    m_currMssProcessedCountChanged;
    bool    m_fondIssProcessedCountChanged;
    bool    m_currIssProcessedCountChanged;
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
    inline int FondTlrProcessedCount() { return this->m_fondTlrProcessedCount; }
    inline int FondTlsProcessedCount() { return this->m_fondTlsProcessedCount; }
    inline int FondMsrProcessedCount() { return this->m_fondMsrProcessedCount; }
    inline int FondMssProcessedCount() { return this->m_fondMssProcessedCount; }
    inline int CurrTlrProcessedCount() { return this->m_currTlrProcessedCount; }
    inline int CurrTlsProcessedCount() { return this->m_currTlsProcessedCount; }
    inline int CurrMsrProcessedCount() { return this->m_currMsrProcessedCount; }
    inline int CurrMssProcessedCount() { return this->m_currMssProcessedCount; }
    inline int FondIssProcessedCount() { return this->m_fondIssProcessedCount; }
    inline int CurrIssProcessedCount() { return this->m_currIssProcessedCount; }

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
    inline void FondTlrProcessedCount(int value) {
        if(this->m_fondTlrProcessedCount == value)
            return;
        this->m_fondTlrProcessedCount = value;
        this->m_fondTlrProcessedCountChanged = true;
    }
    inline void CurrTlrProcessedCount(int value) {
        if(this->m_currTlrProcessedCount == value)
            return;
        this->m_currTlrProcessedCount = value;
        this->m_currTlrProcessedCountChanged = true;
    }
    inline void FondTlsProcessedCount(int value) {
        if(this->m_fondTlsProcessedCount == value)
            return;
        this->m_fondTlsProcessedCount = value;
        this->m_fondTlsProcessedCountChanged = true;
    }
    inline void CurrTlsProcessedCount(int value) {
        if(this->m_currTlsProcessedCount == value)
            return;
        this->m_currTlsProcessedCount = value;
        this->m_currTlsProcessedCountChanged = true;
    }
    inline void FondMsrProcessedCount(int value) {
        if(this->m_fondMsrProcessedCount == value)
            return;
        this->m_fondMsrProcessedCount = value;
        this->m_fondMsrProcessedCountChanged = true;
    }
    inline void CurrMsrProcessedCount(int value) {
        if(this->m_currMsrProcessedCount == value)
            return;
        this->m_currMsrProcessedCount = value;
        this->m_currMsrProcessedCountChanged = true;
    }
    inline void FondMssProcessedCount(int value) {
        if(this->m_fondMssProcessedCount == value)
            return;
        this->m_fondMssProcessedCount = value;
        this->m_fondMssProcessedCountChanged = true;
    }
    inline void CurrMssProcessedCount(int value) {
        if(this->m_currMssProcessedCount == value)
            return;
        this->m_currMssProcessedCount = value;
        this->m_currMssProcessedCountChanged = true;
    }
    inline void FondIssProcessedCount(int value) {
        if(this->m_fondIssProcessedCount == value)
            return;
        this->m_fondIssProcessedCount = value;
        this->m_fondIssProcessedCountChanged = true;
    }
    inline void CurrIssProcessedCount(int value) {
        if(this->m_currIssProcessedCount == value)
            return;
        this->m_currIssProcessedCount = value;
        this->m_currIssProcessedCountChanged = true;
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
    inline void IncFondTlrProcessedCount() {
        this->m_fondTlrProcessedCount++;
        this->m_fondTlrProcessedCountChanged = true;
    }
    inline void IncCurrTlrProcessedCount() {
        this->m_currTlrProcessedCount++;
        this->m_currTlrProcessedCountChanged = true;
    }
    inline void IncFondTlsProcessedCount() {
        this->m_fondTlsProcessedCount++;
        this->m_fondTlsProcessedCountChanged = true;
    }
    inline void IncCurrTlsProcessedCount() {
        this->m_currTlsProcessedCount++;
        this->m_currTlsProcessedCountChanged = true;
    }
    inline void IncFondMsrProcessedCount() {
        this->m_fondMsrProcessedCount++;
        this->m_fondMsrProcessedCountChanged = true;
    }
    inline void IncCurrMsrProcessedCount() {
        this->m_currMsrProcessedCount++;
        this->m_currMsrProcessedCountChanged = true;
    }
    inline void IncFondMssProcessedCount() {
        this->m_fondMssProcessedCount++;
        this->m_fondMssProcessedCountChanged = true;
    }
    inline void IncCurrMssProcessedCount() {
        this->m_currMssProcessedCount++;
        this->m_currMssProcessedCountChanged = true;
    }
    inline void IncFondIssProcessedCount() {
        this->m_fondIssProcessedCount++;
        this->m_fondIssProcessedCountChanged = true;
    }
    inline void IncCurrIssProcessedCount() {
        this->m_currIssProcessedCount++;
        this->m_currIssProcessedCountChanged = true;
    }

    inline void Clear() {
        this->m_fondOlrProcessedCount = 0;
        this->m_fondOlsProcessedCount = 0;
        this->m_currOlrProcessedCount = 0;
        this->m_currOlsProcessedCount = 0;
        this->m_fondIdfProcessedCount = 0;
        this->m_currIdfProcessedCount = 0;
        this->m_fondTlrProcessedCount = 0;
        this->m_fondTlsProcessedCount = 0;
        this->m_fondMsrProcessedCount = 0;
        this->m_fondMssProcessedCount = 0;
        this->m_fondIssProcessedCount = 0;
        this->m_currTlrProcessedCount = 0;
        this->m_currTlsProcessedCount = 0;
        this->m_currMsrProcessedCount = 0;
        this->m_currMssProcessedCount = 0;
        this->m_currIssProcessedCount = 0;

        this->ResetFlags();
    }

    inline void Print() {
        if(this->m_fondOlrProcessedCountChanged)
            printf("fond olr processed messages count = %d\n", this->m_fondOlrProcessedCount);
        if(this->m_fondTlrProcessedCountChanged)
            printf("fond tlr processed messages count = %d\n", this->m_fondTlrProcessedCount);
        if(this->m_fondMsrProcessedCountChanged)
            printf("fond msr processed messages count = %d\n", this->m_fondMsrProcessedCount);
        
        if(this->m_fondOlsProcessedCountChanged)
            printf("fond ols processed messages count = %d\n", this->m_fondOlsProcessedCount);
        if(this->m_fondTlsProcessedCountChanged)
            printf("fond tls processed messages count = %d\n", this->m_fondTlsProcessedCount);
        if(this->m_fondMssProcessedCountChanged)
            printf("fond mss processed messages count = %d\n", this->m_fondMssProcessedCount);
        
        if(this->m_fondIdfProcessedCountChanged)
            printf("fond idf processed messages count = %d\n", this->m_fondIdfProcessedCount);
        if(this->m_fondIssProcessedCountChanged)
            printf("fond iss processed messages count = %d\n", this->m_fondIssProcessedCount);

        if(this->m_currOlrProcessedCountChanged)
            printf("curr olr processed messages count = %d\n", this->m_currOlrProcessedCount);
        if(this->m_currTlrProcessedCountChanged)
            printf("curr tlr processed messages count = %d\n", this->m_currTlrProcessedCount);
        if(this->m_currMsrProcessedCountChanged)
            printf("curr msr processed messages count = %d\n", this->m_currMsrProcessedCount);

        if(this->m_currOlsProcessedCountChanged)
            printf("curr ols processed messages count = %d\n", this->m_currOlsProcessedCount);
        if(this->m_currTlsProcessedCountChanged)
            printf("curr tls processed messages count = %d\n", this->m_currTlsProcessedCount);
        if(this->m_currMssProcessedCountChanged)
            printf("curr mss processed messages count = %d\n", this->m_currMssProcessedCount);

        if(this->m_currIdfProcessedCountChanged)
            printf("curr idf processed messages count = %d\n", this->m_currIdfProcessedCount);
        if(this->m_currIssProcessedCountChanged)
            printf("curr iss processed messages count = %d\n", this->m_currIssProcessedCount);

    }

    inline void ResetFlags() {
        this->m_fondOlrProcessedCountChanged = false;
        this->m_fondOlsProcessedCountChanged = false;
        this->m_currOlrProcessedCountChanged = false;
        this->m_currOlsProcessedCountChanged = false;
        this->m_fondIdfProcessedCountChanged = false;
        this->m_currIdfProcessedCountChanged = false;
        this->m_fondTlrProcessedCountChanged = false;
        this->m_fondTlsProcessedCountChanged = false;
        this->m_fondMsrProcessedCountChanged = false;
        this->m_fondMssProcessedCountChanged = false;
        this->m_fondIssProcessedCountChanged = false;
        this->m_currTlrProcessedCountChanged = false;
        this->m_currTlsProcessedCountChanged = false;
        this->m_currMsrProcessedCountChanged = false;
        this->m_currMssProcessedCountChanged = false;
        this->m_currIssProcessedCountChanged = false;
    }
};

#endif //HFT_ROBOT_PROGRAMSTATISTICS_H
