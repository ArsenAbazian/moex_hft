//
// Created by root on 21.09.16.
//

#ifndef HFT_ROBOT_MARKETDATATABLE_H
#define HFT_ROBOT_MARKETDATATABLE_H

class MarketDataTable {
    char        **m_symbolId;
    int           m_symbolLength;
    int           m_maxSymbolIdCount;

    char        **m_tradingSessionId;
    int           m_tradingSessionIdLength;
    int           m_maxTradingSessionIdCount;

public:
    inline int GetSymbolIndex(char *symbol) {
        return -1;
    }
    inline int GetTradingSessionIdIndex(char *tradingSessionId) {
        return -1;
    }

    MarketDataTable(int maxSymbolIdCount, int maxTradingSessionIdCount, int symbolLength, int tradingSessionLength);
    ~MarketDataTable();


};

#endif //HFT_ROBOT_MARKETDATATABLE_H
