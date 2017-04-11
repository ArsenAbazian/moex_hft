//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_MARKETSYMBOLINFO_H
#define HFT_ROBOT_MARKETSYMBOLINFO_H

#include "../Lib/StringIdComparer.h"
#include "../Fast/FastTypes.h"

template <typename T> class MarketSymbolInfo {
    T                                  **m_items;
    SizedArray                         *m_symbol;
    int                                 m_count;
    int                                 m_maxCount;
    int                                 m_sessionsToRecvSnapshot;
    LinkedPointer<AstsSecurityDefinitionInfo> *m_securityDefinitionPtr;
    LinkedPointer<FortsSecurityDefinitionInfo> *m_securityDefinitionFortsPtr;
    UINT64                              m_securityId;
public:
    MarketSymbolInfo() :
            m_count(0),
            m_maxCount(0),
            m_items(0),
            m_symbol(0),
            m_securityDefinitionPtr(0),
            m_securityDefinitionFortsPtr(0),
            m_securityId(0),
            m_sessionsToRecvSnapshot(0) {
        this->m_symbol = new SizedArray();
    }
    inline void InitSessions(int count) {
        Release();
        this->m_maxCount = count;
        this->m_items = new T*[this->m_maxCount];
        this->m_count = 0;
        for(int i = 0; i < this->m_maxCount; i++) {
            this->m_items[i] = new T();
            this->m_items[i]->SymbolInfo(this);
        }
    }
    inline void Release() {
        if(this->m_items == 0)
            return;
        for(int i = 0; i < this->m_maxCount; i++)
            delete this->m_items[i];
        delete this->m_items;
        this->m_securityDefinitionPtr = 0;
    }
    ~MarketSymbolInfo() {
        Release();
        delete this->m_symbol;

    }
    inline int Count() { return this->m_count; }
    inline int SessionCount() { return this->m_count; }
    inline UINT64 SecurityID() { return this->m_securityId; }
    inline int MaxSessionCount() { return this->m_maxCount; }
    inline T* Session(int index) { return this->m_items[index]; }
    inline T* GetSession(const char *session, int sessionLength) {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            if((*item)->TradingSession()->Equal(session, sessionLength))
                return *item;
        }
        T* res = this->m_items[this->m_count];
        res->TradingSession()->Set(session, sessionLength);
        this->m_count++;
        return res;
    }
    inline T* GetSession(UINT32 session) {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            if((*item)->TradingSessionInt() == session)
                return *item;
        }
        T* res = this->m_items[this->m_count];
        res->TradingSessionInt(session);
        this->m_count++;
        return res;
    }
    inline void SecurityDefinitionPtr(LinkedPointer<AstsSecurityDefinitionInfo> *ptr) {
        this->m_securityDefinitionPtr = ptr;
    }
    inline void SecurityDefinitionPtr(LinkedPointer<FortsSecurityDefinitionInfo> *ptr) {
        this->m_securityDefinitionFortsPtr = ptr;
        this->m_securityId = SecurityDefinitionForts()->SecurityID;
    }
    inline AstsSecurityDefinitionInfo* SecurityDefinitionAsts() { return this->m_securityDefinitionPtr->Data(); }
    inline FortsSecurityDefinitionInfo* SecurityDefinitionForts() { return this->m_securityDefinitionFortsPtr->Data(); }
    inline SizedArray *Symbol() { return this->m_symbol; }
    inline bool Equals(const char *symbol, int symbolLen) { return this->m_symbol->Equal(symbol, symbolLen); }
    inline void Clear() {
        T **item = this->m_items;
        for(int i = 0; i < this->m_maxCount; i++, item++) {
            (*item)->Used(false);
            (*item)->Clear();
        }
        this->m_count = 0;
    }
    inline T* AddSession(const char *session, int sessionLength) {
        return GetSession(session, sessionLength);
    }
    inline T* AddSession(const char *session) {
        return AddSession(session, strlen(session));
    }
    inline T* AddSession(UINT32 session) {
        return GetSession(session);
    }
    inline bool EnterSnapshotMode() {
        if(this->m_securityDefinitionFortsPtr != 0) {
            if(this->m_securityDefinitionFortsPtr->Data()->SecurityTradingStatus == 2)
                return false;
        }
        this->m_sessionsToRecvSnapshot = this->m_count;
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            (*item)->EnterSnapshotMode();
        }
        return true;
    }
    inline void ExitSnapshotMode() {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++)
            (*item)->ExitSnapshotMode();
    }
    inline int SessionsToRecvSnapshotCount() { return this->m_sessionsToRecvSnapshot; }
    inline bool AllSessionsRecvSnapshot() { return this->m_sessionsToRecvSnapshot == 0; }
    inline void DecSessionsToRecvSnapshotCount() { this->m_sessionsToRecvSnapshot--; }
    inline void IncSessionsToRecvSnapshotCount() { this->m_sessionsToRecvSnapshot++; }
};

#endif //HFT_ROBOT_MARKETSYMBOLINFO_H
