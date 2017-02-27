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

    int     m_fondOlrLostCount;
    int     m_fondOlsLostCount;
    int     m_currOlrLostCount;
    int     m_currOlsLostCount;
    int     m_fondIdfLostCount;
    int     m_currIdfLostCount;
    int     m_fondTlrLostCount;
    int     m_fondTlsLostCount;
    int     m_fondMsrLostCount;
    int     m_fondMssLostCount;
    int     m_currTlrLostCount;
    int     m_currTlsLostCount;
    int     m_currMsrLostCount;
    int     m_currMssLostCount;
    int     m_fondIssLostCount;
    int     m_currIssLostCount;    

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

    bool    m_fondOlrLostCountChanged;
    bool    m_fondOlsLostCountChanged;
    bool    m_currOlrLostCountChanged;
    bool    m_currOlsLostCountChanged;
    bool    m_fondIdfLostCountChanged;
    bool    m_currIdfLostCountChanged;
    bool    m_fondTlrLostCountChanged;
    bool    m_fondTlsLostCountChanged;
    bool    m_fondMsrLostCountChanged;
    bool    m_fondMssLostCountChanged;
    bool    m_currTlrLostCountChanged;
    bool    m_currTlsLostCountChanged;
    bool    m_currMsrLostCountChanged;
    bool    m_currMssLostCountChanged;
    bool    m_fondIssLostCountChanged;
    bool    m_currIssLostCountChanged;
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




    inline int FondOlrLostCount() { return this->m_fondOlrLostCount; }
    inline int FondOlsLostCount() { return this->m_fondOlsLostCount; }
    inline int CurrOlrLostCount() { return this->m_currOlrLostCount; }
    inline int CurrOlsLostCount() { return this->m_currOlsLostCount; }
    inline int FondIdfLostCount() { return this->m_fondIdfLostCount; }
    inline int CurrIdfLostCount() { return this->m_currIdfLostCount; }
    inline int FondTlrLostCount() { return this->m_fondTlrLostCount; }
    inline int FondTlsLostCount() { return this->m_fondTlsLostCount; }
    inline int FondMsrLostCount() { return this->m_fondMsrLostCount; }
    inline int FondMssLostCount() { return this->m_fondMssLostCount; }
    inline int CurrTlrLostCount() { return this->m_currTlrLostCount; }
    inline int CurrTlsLostCount() { return this->m_currTlsLostCount; }
    inline int CurrMsrLostCount() { return this->m_currMsrLostCount; }
    inline int CurrMssLostCount() { return this->m_currMssLostCount; }
    inline int FondIssLostCount() { return this->m_fondIssLostCount; }
    inline int CurrIssLostCount() { return this->m_currIssLostCount; }

    inline void FondOlrLostCount(int value) {
        if(this->m_fondOlrLostCount == value)
            return;
        this->m_fondOlrLostCount = value;
        this->m_fondOlrLostCountChanged = true;
    }
    inline void FondOlsLostCount(int value) {
        if(this->m_fondOlsLostCount == value)
            return;
        this->m_fondOlsLostCount = value;
        this->m_fondOlsLostCountChanged = true;
    }
    inline void CurrOlrLostCount(int value) {
        if(this->m_currOlrLostCount == value)
            return;
        this->m_currOlrLostCount = value;
        this->m_currOlrLostCountChanged = true;
    }
    inline void CurrOlsLostCount(int value) {
        if(this->m_currOlsLostCount == value)
            return;
        this->m_currOlsLostCount = value;
        this->m_currOlsLostCountChanged = true;
    }
    inline void FondIdfLostCount(int value) {
        if(this->m_fondIdfLostCount == value)
            return;
        this->m_fondIdfLostCount = value;
        this->m_fondIdfLostCountChanged = true;
    }
    inline void CurrIdfLostCount(int value) {
        if(this->m_currIdfLostCount == value)
            return;
        this->m_currIdfLostCount = value;
        this->m_currIdfLostCountChanged = true;
    }
    inline void FondTlrLostCount(int value) {
        if(this->m_fondTlrLostCount == value)
            return;
        this->m_fondTlrLostCount = value;
        this->m_fondTlrLostCountChanged = true;
    }
    inline void CurrTlrLostCount(int value) {
        if(this->m_currTlrLostCount == value)
            return;
        this->m_currTlrLostCount = value;
        this->m_currTlrLostCountChanged = true;
    }
    inline void FondTlsLostCount(int value) {
        if(this->m_fondTlsLostCount == value)
            return;
        this->m_fondTlsLostCount = value;
        this->m_fondTlsLostCountChanged = true;
    }
    inline void CurrTlsLostCount(int value) {
        if(this->m_currTlsLostCount == value)
            return;
        this->m_currTlsLostCount = value;
        this->m_currTlsLostCountChanged = true;
    }
    inline void FondMsrLostCount(int value) {
        if(this->m_fondMsrLostCount == value)
            return;
        this->m_fondMsrLostCount = value;
        this->m_fondMsrLostCountChanged = true;
    }
    inline void CurrMsrLostCount(int value) {
        if(this->m_currMsrLostCount == value)
            return;
        this->m_currMsrLostCount = value;
        this->m_currMsrLostCountChanged = true;
    }
    inline void FondMssLostCount(int value) {
        if(this->m_fondMssLostCount == value)
            return;
        this->m_fondMssLostCount = value;
        this->m_fondMssLostCountChanged = true;
    }
    inline void CurrMssLostCount(int value) {
        if(this->m_currMssLostCount == value)
            return;
        this->m_currMssLostCount = value;
        this->m_currMssLostCountChanged = true;
    }
    inline void FondIssLostCount(int value) {
        if(this->m_fondIssLostCount == value)
            return;
        this->m_fondIssLostCount = value;
        this->m_fondIssLostCountChanged = true;
    }
    inline void CurrIssLostCount(int value) {
        if(this->m_currIssLostCount == value)
            return;
        this->m_currIssLostCount = value;
        this->m_currIssLostCountChanged = true;
    }

    inline void IncFondOlrLostCount() {
        this->m_fondOlrLostCount++;
        this->m_fondOlrLostCountChanged = true;
    }
    inline void IncFondOlsLostCount() {
        this->m_fondOlsLostCount++;
        this->m_fondOlsLostCountChanged = true;
    }
    inline void IncCurrOlrLostCount() {
        this->m_currOlrLostCount++;
        this->m_currOlrLostCountChanged = true;
    }
    inline void IncCurrOlsLostCount() {
        this->m_currOlsLostCount++;
        this->m_currOlsLostCountChanged = true;
    }
    inline void IncFondIdfLostCount() {
        this->m_fondIdfLostCount++;
        this->m_fondIdfLostCountChanged = true;
    }
    inline void IncCurrIdfLostCount() {
        this->m_currIdfLostCount++;
        this->m_currIdfLostCountChanged = true;
    }
    inline void IncFondTlrLostCount() {
        this->m_fondTlrLostCount++;
        this->m_fondTlrLostCountChanged = true;
    }
    inline void IncCurrTlrLostCount() {
        this->m_currTlrLostCount++;
        this->m_currTlrLostCountChanged = true;
    }
    inline void IncFondTlsLostCount() {
        this->m_fondTlsLostCount++;
        this->m_fondTlsLostCountChanged = true;
    }
    inline void IncCurrTlsLostCount() {
        this->m_currTlsLostCount++;
        this->m_currTlsLostCountChanged = true;
    }
    inline void IncFondMsrLostCount() {
        this->m_fondMsrLostCount++;
        this->m_fondMsrLostCountChanged = true;
    }
    inline void IncCurrMsrLostCount() {
        this->m_currMsrLostCount++;
        this->m_currMsrLostCountChanged = true;
    }
    inline void IncFondMssLostCount() {
        this->m_fondMssLostCount++;
        this->m_fondMssLostCountChanged = true;
    }
    inline void IncCurrMssLostCount() {
        this->m_currMssLostCount++;
        this->m_currMssLostCountChanged = true;
    }
    inline void IncFondIssLostCount() {
        this->m_fondIssLostCount++;
        this->m_fondIssLostCountChanged = true;
    }
    inline void IncCurrIssLostCount() {
        this->m_currIssLostCount++;
        this->m_currIssLostCountChanged = true;
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

        this->m_fondOlrLostCount = 0;
        this->m_fondOlsLostCount = 0;
        this->m_currOlrLostCount = 0;
        this->m_currOlsLostCount = 0;
        this->m_fondIdfLostCount = 0;
        this->m_currIdfLostCount = 0;
        this->m_fondTlrLostCount = 0;
        this->m_fondTlsLostCount = 0;
        this->m_fondMsrLostCount = 0;
        this->m_fondMssLostCount = 0;
        this->m_fondIssLostCount = 0;
        this->m_currTlrLostCount = 0;
        this->m_currTlsLostCount = 0;
        this->m_currMsrLostCount = 0;
        this->m_currMssLostCount = 0;
        this->m_currIssLostCount = 0;

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


        if(this->m_fondOlrLostCountChanged)
            printf("fond olr lost messages count = %d\n", this->m_fondOlrLostCount);
        if(this->m_fondTlrLostCountChanged)
            printf("fond tlr lost messages count = %d\n", this->m_fondTlrLostCount);
        if(this->m_fondMsrLostCountChanged)
            printf("fond msr lost messages count = %d\n", this->m_fondMsrLostCount);

        if(this->m_fondOlsLostCountChanged)
            printf("fond ols lost messages count = %d\n", this->m_fondOlsLostCount);
        if(this->m_fondTlsLostCountChanged)
            printf("fond tls lost messages count = %d\n", this->m_fondTlsLostCount);
        if(this->m_fondMssLostCountChanged)
            printf("fond mss lost messages count = %d\n", this->m_fondMssLostCount);

        if(this->m_fondIdfLostCountChanged)
            printf("fond idf lost messages count = %d\n", this->m_fondIdfLostCount);
        if(this->m_fondIssLostCountChanged)
            printf("fond iss lost messages count = %d\n", this->m_fondIssLostCount);

        if(this->m_currOlrLostCountChanged)
            printf("curr olr lost messages count = %d\n", this->m_currOlrLostCount);
        if(this->m_currTlrLostCountChanged)
            printf("curr tlr lost messages count = %d\n", this->m_currTlrLostCount);
        if(this->m_currMsrLostCountChanged)
            printf("curr msr lost messages count = %d\n", this->m_currMsrLostCount);

        if(this->m_currOlsLostCountChanged)
            printf("curr ols lost messages count = %d\n", this->m_currOlsLostCount);
        if(this->m_currTlsLostCountChanged)
            printf("curr tls lost messages count = %d\n", this->m_currTlsLostCount);
        if(this->m_currMssLostCountChanged)
            printf("curr mss lost messages count = %d\n", this->m_currMssLostCount);

        if(this->m_currIdfLostCountChanged)
            printf("curr idf lost messages count = %d\n", this->m_currIdfLostCount);
        if(this->m_currIssLostCountChanged)
            printf("curr iss lost messages count = %d\n", this->m_currIssLostCount);

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

        this->m_fondOlrLostCountChanged = false;
        this->m_fondOlsLostCountChanged = false;
        this->m_currOlrLostCountChanged = false;
        this->m_currOlsLostCountChanged = false;
        this->m_fondIdfLostCountChanged = false;
        this->m_currIdfLostCountChanged = false;
        this->m_fondTlrLostCountChanged = false;
        this->m_fondTlsLostCountChanged = false;
        this->m_fondMsrLostCountChanged = false;
        this->m_fondMssLostCountChanged = false;
        this->m_fondIssLostCountChanged = false;
        this->m_currTlrLostCountChanged = false;
        this->m_currTlsLostCountChanged = false;
        this->m_currMsrLostCountChanged = false;
        this->m_currMssLostCountChanged = false;
        this->m_currIssLostCountChanged = false;
    }
};

#endif //HFT_ROBOT_PROGRAMSTATISTICS_H
