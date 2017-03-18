//
// Created by root on 11.03.17.
//

#ifndef HFT_ROBOT_SPECTRAMARKETDATAGROUP_H
#define HFT_ROBOT_SPECTRAMARKETDATAGROUP_H

#include "../FeedConnection.h"

typedef enum _MarketDataGroupId {
    mdgidNone = 0,
    mdgidFutBook1 = 1,
    mdgidFutBook5 = 2,
    mdgidFutBook20 = 3,
    mdgidFutBook50 = 4,
    mdgidFutTrades = 5,
    mdgidFutInfo = 6,
    mdgidIndex = 7,
    mdgidNews = 8,
    mdgidNewsSkrin = 9,
    mdgidOptBook1 = 10,
    mdgidOptBook5 = 11,
    mdgidOptBook20 = 12,
    mdgidOptBook50 = 13,
    mdgidOptTrades = 14,
    mdgidOptInfo = 15,
    mdgidOtcTrades = 16,
    mdgidOtcIssues = 17,
    mdgidCount = 18
}MarketDataGroupId;

class FortsMarketDataGroup {
    FeedConnection          *m_incremental;
    FeedConnection          *m_instrumentIncremental;
    FeedConnection          *m_snapshot;
    FeedConnection          *m_instrumentReplay;

    FeedConnection          *m_hr;

    MarketDataGroupId       m_id;
    const char              *m_marketId;
    int                     m_marketDepth;
    const char              *m_label;

public:
    FortsMarketDataGroup(MarketDataGroupId id, const char *marketId, int marketDepth, const char *label) : FortsMarketDataGroup() {
        this->m_id = id;
        this->m_marketId = marketId;
        this->m_marketDepth = marketDepth;
        this->m_label = label;
    }
    FortsMarketDataGroup() {
        this->m_incremental = 0;
        this->m_snapshot = 0;
        this->m_instrumentIncremental = 0;
        this->m_instrumentReplay = 0;
        this->m_hr = 0;
        this->m_id = mdgidNone;
        this->m_marketId = "";
        this->m_label = "";
        this->m_marketDepth = 0;
    }
    ~FortsMarketDataGroup() {
        if(this->m_incremental != 0)
            delete this->m_incremental;
        if(this->m_snapshot != 0)
            delete this->m_snapshot;
        if(this->m_instrumentIncremental != 0)
            delete this->m_instrumentIncremental;
        if(this->m_instrumentReplay != 0)
            delete this->m_instrumentReplay;
        if(this->m_hr != 0)
            delete this->m_hr;
    }

    inline FeedConnection* Inc() { return this->m_incremental; }
    inline FeedConnection* Snap() { return this->m_snapshot; }
    inline FeedConnection* Hr() { return this->m_hr; }
    inline FeedConnection* InstrInc() { return this->m_instrumentIncremental;}
    inline FeedConnection* InstrReplay() { return this->m_instrumentReplay; }

    inline void Inc(FeedConnection *conn) { this->m_incremental = conn; }
    inline void Snap(FeedConnection *conn) { this->m_snapshot = conn; }
    inline void Hr(FeedConnection *conn) { this->m_hr = conn; }
    inline void InstrInc(FeedConnection *conn) { this->m_instrumentIncremental = conn; }
    inline void InstrReplay(FeedConnection *conn) { this->m_instrumentReplay = conn; }

    inline void Id(MarketDataGroupId id) { this->m_id = id; }
    inline MarketDataGroupId Id() { return this->m_id; }

    inline void MarketId(const char *id) { this->m_marketId = id; }
    inline const char *MarketId() { return this->m_marketId; }

    inline int MarketDepth() { return this->m_marketDepth; }
    inline void MarketDepth(int depth) { this->m_marketDepth = depth; }

    inline const char *Label() { return this->m_label; }
    inline void Label(const char *label) { this->m_label = label; }

    void AllowSaveSecurityDefinitions(bool value) {
        if(this->m_instrumentReplay != 0)
            this->m_instrumentReplay->AllowSaveSecurityDefinitions(value);
    }

    void Prepare() {
        if(this->m_incremental != 0 && this->m_snapshot != 0)
            this->m_incremental->SetSnapshot(this->m_snapshot);
    }
    void SetSecurityDefinition(FeedConnection *conn) {
        if(this->m_incremental != 0)
            this->m_incremental->SetSecurityDefinition(conn);
        if(this->m_snapshot != 0)
            this->m_snapshot->SetSecurityDefinition(conn);
    }
};


#endif //HFT_ROBOT_SPECTRAMARKETDATAGROUP_H
