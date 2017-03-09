//
// Created by root on 26.02.17.
//

#ifndef HFT_ROBOT_STATISTICITEM_H
#define HFT_ROBOT_STATISTICITEM_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "MDEntryQueue.h"
#include "../Managers/DebugInfoManager.h"

class StatisticItemDecimal {
protected:
    UINT64          m_time;
    Decimal         m_value;
    Decimal         *m_valuePtr;
public:
    StatisticItemDecimal() {
        this->m_valuePtr = &this->m_value;
    }
    ~StatisticItemDecimal() { }
    inline void Set(UINT64 time, Decimal *value) {
        this->m_time = time;
        this->m_valuePtr->Set(value);
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Value() { return this->m_valuePtr; };
};

class StatisticItemDecimal2 {
protected:
    UINT64          m_time;
    Decimal         m_value;
    Decimal         m_value2;
    Decimal         *m_valuePtr;
    Decimal         *m_value2Ptr;
public:
    StatisticItemDecimal2() {
        this->m_valuePtr = &this->m_value;
        this->m_value2Ptr = &this->m_value2;
    }
    ~StatisticItemDecimal2() { }
    inline void Set(UINT64 time, Decimal *value, Decimal *value2) {
        this->m_time = time;
        this->m_valuePtr->Set(value);
        this->m_value2Ptr->Set(value2);
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Value() { return this->m_valuePtr; };
    inline Decimal* Value2() { return this->m_value2Ptr; };
};

class StatisticItemLastDealInfo {
protected:
    UINT64          m_time;
    Decimal         m_price;
    Decimal         m_size;
    Decimal         m_netChangePrevDay;
    Decimal         m_changeFromWAPrice;
    Decimal         m_tradeValue;
    Decimal         *m_pricePtr;
    Decimal         *m_sizePtr;
    Decimal         *m_netChangePrevDayPtr;
    Decimal         *m_changeFromWAPricePtr;
    Decimal         *m_tradeValuePtr;
    UINT32          m_dealTime;
public:
    StatisticItemLastDealInfo() {
        this->m_pricePtr = &(this->m_price);
        this->m_sizePtr = &(this->m_size);
        this->m_netChangePrevDayPtr = &(this->m_netChangePrevDay);
        this->m_changeFromWAPricePtr = &(this->m_changeFromWAPrice);
        this->m_tradeValuePtr = &(this->m_tradeValue);
    }
    ~StatisticItemLastDealInfo() { }
    template <typename T> inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_pricePtr->Set(&(info->MDEntryPx));
        this->m_sizePtr->Set(&(info->MDEntrySize));
        this->m_dealTime = info->MDEntryTime;
        this->m_netChangePrevDayPtr->Set(&(info->NetChgPrevDay));
        this->m_changeFromWAPricePtr->Set(&(info->ChgFromWAPrice));
        this->m_tradeValuePtr->Set(&(info->TradeValue));
    }
    inline UINT64 Time() { return this->m_time; }
    inline UINT32 DealTime() { return this->m_dealTime; }
    inline Decimal* Price() { return this->m_pricePtr; };
    inline Decimal* Size() { return this->m_sizePtr; };
    inline Decimal* NetChangePrevDay() { return this->m_netChangePrevDayPtr; }
    inline Decimal* ChangeFromWAPrice() { return this->m_changeFromWAPricePtr; }
    inline Decimal* TradeValue() { return this->m_tradeValuePtr; }
};  // 2

class StatisticItemTotalOffer {
protected:
    UINT64          m_time;
    Decimal         m_size;
    int             m_offerNbOr;
    Decimal         *m_sizePtr;

public:
    StatisticItemTotalOffer() {
        this->m_sizePtr = &(this->m_size);
    }
    ~StatisticItemTotalOffer() { }
    template<typename T> inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_sizePtr->Set(&(info->MDEntrySize));
        this->m_offerNbOr = info->OfferNbOr;
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Size() { return this->m_sizePtr; };
    inline int OfferNbOr() { return this->m_offerNbOr; }
};  // w

class StatisticItemTransactionsMagnitude {
protected:
    UINT64          m_time;
    Decimal         m_size;
    Decimal         m_tradeValue;
    int             m_totalNumOfTrades;
    Decimal         *m_sizePtr;
    Decimal         *m_tradeValuePtr;
public:
    StatisticItemTransactionsMagnitude() {
        this->m_sizePtr = &(this->m_size);
        this->m_tradeValuePtr = &(this->m_tradeValue);
    }
    ~StatisticItemTransactionsMagnitude() { }
    template<typename T> inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_sizePtr->Set(&(info->MDEntrySize));
        this->m_totalNumOfTrades = info->TotalNumOfTrades;
        this->m_tradeValuePtr->Set(&(info->TradeValue));
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Size() { return this->m_sizePtr; };
    inline int TotalNumOfTrades() { return this->m_totalNumOfTrades; }
    inline Decimal* TradeValue() { return this->m_tradeValuePtr; }
};  // B

class StatisticItemIndexList {
protected:
    UINT64          m_time;
    Decimal         m_price;
    Decimal         m_size;
    Decimal         m_tradeValue;
    Decimal         *m_pricePtr;
    Decimal         *m_sizePtr;
    Decimal         *m_tradeValuePtr;
public:
    StatisticItemIndexList() {
        this->m_pricePtr = &(this->m_price);
        this->m_sizePtr = &(this->m_size);
        this->m_tradeValuePtr = &(this->m_tradeValue);
    }
    ~StatisticItemIndexList() { }
    template<typename T> inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_pricePtr->Set(&(info->MDEntryPx));
        this->m_sizePtr->Set(&(info->MDEntrySize));
        this->m_tradeValuePtr->Set(&(info->TradeValue));
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Price() { return this->m_pricePtr; };
    inline Decimal* Size() { return this->m_sizePtr; };
    inline Decimal* TradeValue() { return this->m_tradeValuePtr; }
};  // 3

class StatisticItemTotalBid {
protected:
    UINT64          m_time;
    Decimal         m_size;
    int             m_bidNbOr;
    Decimal         *m_sizePtr;

public:
    StatisticItemTotalBid() {
        this->m_sizePtr = &(this->m_size);
    }
    ~StatisticItemTotalBid() { }
    template<typename T> inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_sizePtr->Set(&(info->MDEntrySize));
        this->m_bidNbOr = info->BidNbOr;
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Size() { return this->m_sizePtr; };
    inline int BidNbOr() { return this->m_bidNbOr; }
};  // v

template <typename T> class StatisticItem {
    UINT64          m_time;
    T               m_value;
public:
    StatisticItem() { }
    ~StatisticItem() { }

    inline void Set(UINT64 time, T value) {
        this->m_time = time;
        this->m_value = value;
    }
    inline UINT64 Time() { return this->m_time; }
    inline T Value() { return this->m_value; }
};

class StatisticItemAllocator {
    PointerList<StatisticItemDecimal>                       *m_decimals;
    PointerList<StatisticItemDecimal2>                      *m_decimals2;
    PointerList<StatisticItemLastDealInfo>                  *m_dealInfos;
    PointerList<StatisticItemTotalOffer>                    *m_totalOffers;
    PointerList<StatisticItemTransactionsMagnitude>         *m_trMagnitudes;
    PointerList<StatisticItemIndexList>                     *m_indexLists;
    PointerList<StatisticItemTotalBid>                      *m_totalBids;
    PointerList<StatisticItem<bool>>                        *m_booleans;
public:
    StatisticItemAllocator();
    PointerList<StatisticItemDecimal>* Decimals() { return this->m_decimals; }
    PointerList<StatisticItemDecimal2>* Decimals2() { return this->m_decimals2; }
    PointerList<StatisticItemLastDealInfo>* LastDealInfos() { return this->m_dealInfos; }
    PointerList<StatisticItemTotalOffer>* TotalOffers() { return this->m_totalOffers; }
    PointerList<StatisticItemTransactionsMagnitude>* TransactionMagnitudes() { return this->m_trMagnitudes; }
    PointerList<StatisticItemTotalBid>* TotalBids() { return this->m_totalBids; }
    PointerList<StatisticItemIndexList>* IndexLists() { return this->m_indexLists; }

    PointerList<StatisticItem<bool>>* Booleans() { return this->m_booleans; }
};

class DefaultStatisticItemAllocator {
public:
    static StatisticItemAllocator* Default;
};

#endif //HFT_ROBOT_STATISTICITEM_H

