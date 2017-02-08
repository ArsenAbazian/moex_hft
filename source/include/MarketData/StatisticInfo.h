//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_STATISTICINFO_H
#define HFT_ROBOT_STATISTICINFO_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "MarketDataEntryQueue.h"

class StatisticItemDouble {
protected:
    UINT64          m_time;
    Decimal         m_value;
    Decimal         *m_valuePtr;
public:
    StatisticItemDouble() {
        this->m_valuePtr = &this->m_value;
    }
    ~StatisticItemDouble() { }
    inline void Set(UINT64 time, Decimal *value) {
        this->m_time = time;
        this->m_valuePtr->Set(value);
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Value() { return this->m_valuePtr; };
};

class StatisticItemDouble2 {
protected:
    UINT64          m_time;
    Decimal         m_value;
    Decimal         m_value2;
    Decimal         *m_valuePtr;
    Decimal         *m_value2Ptr;
public:
    StatisticItemDouble2() {
        this->m_valuePtr = &this->m_value;
        this->m_value2Ptr = &this->m_value2;
    }
    ~StatisticItemDouble2() { }
    inline void Set(UINT64 time, Decimal *value, Decimal *value2) {
        this->m_time = time;
        this->m_valuePtr->Set(value);
        this->m_value2Ptr->Set(value2);
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Value() { return this->m_valuePtr; };
    inline Decimal* Value2() { return this->m_value2Ptr; };
};

template<typename T> class StatisticItemLastDealInfo{
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
    inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_pricePtr->Set(info->MDEntryPx);
        this->m_sizePtr->Set(info->MDEntrySize);
        this->m_dealTime = info->MDEntryTime;
        this->m_netChangePrevDayPtr = info->NetChgPrevDay;
        this->m_changeFromWAPrice = info->ChgFromWAPrice;
        this->m_tradeValuePtr->Set(info->TradeValue);
    }
    inline UINT64 Time() { return this->m_time; }
    inline UINT32 DealTime() { return this->m_dealTime; }
    inline Decimal* Price() { return this->m_pricePtr; };
    inline Decimal* Size() { return this->m_sizePtr; };
    inline Decimal* NetChangePrevDayPtr() { return this->m_netChangePrevDayPtr; }
    inline Decimal* ChangeFromWAPrice() { return this->m_changeFromWAPricePtr; }
    inline Decimal* TradeValue() { return this->m_tradeValuePtr; }
};

template<typename T> class StatisticItemTotalOfferInfo{
protected:
    UINT64          m_time;
    Decimal         m_size;
    int             m_offerNbOr;
    Decimal         *m_sizePtr;

public:
    StatisticItemTotalOfferInfo() {
        this->m_sizePtr = &(this->m_size);
    }
    ~StatisticItemTotalOfferInfo() { }
    inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_sizePtr->Set(info->MDEntrySize);
        this->m_offerNbOr = info->OfferNbOr;
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Size() { return this->m_sizePtr; };
    inline int OfferNbOr() { return this->m_offerNbOr; }
};

template<typename T> class StatisticItemTransactionsMagnitude{
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
    inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_sizePtr->Set(info->MDEntrySize);
        this->m_totalNumOfTrades = info->TotalNumOfTrades;
        this->m_tradeValuePtr->Set(info->TradeValue);
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Size() { return this->m_sizePtr; };
    inline int TotalNumOfTrades() { return this->m_totalNumOfTrades; }
    inline Decimal* TradeValue() { return this->m_tradeValuePtr; }
};

template<typename T> class StatisticItemIndexList{
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
    inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_pricePtr->Set(info->MDEntryPx);
        this->m_sizePtr->Set(info->MDEntrySize);
        this->m_tradeValuePtr->Set(info->TradeValue);
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Price() { return this->m_pricePtr; };
    inline Decimal* Size() { return this->m_sizePtr; };
    inline Decimal* TradeValue() { return this->m_tradeValuePtr; }
};

template<typename T> class StatisticItemTotalBid {
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
    inline void Set(UINT64 time, T *info) {
        this->m_time = time;
        this->m_sizePtr->Set(info->MDEntrySize);
        this->m_bidNbOr = info->BidNbOr;
    }
    inline UINT64 Time() { return this->m_time; }
    inline Decimal* Size() { return this->m_sizePtr; };
    inline int BidNbOr() { return this->m_bidNbOr; }
};


template <typename T> class StatisticItem {
    UINT64          m_time;
    T               m_value;
public:
    StatisticItem() { }
    ~StatisticItem() { }
};

class StatisticItemAllocator {
    PointerList<StatisticItemDouble>    *m_decimals;
    PointerList<StatisticItem<bool>>    *m_booleans;
public:
    StatisticItemAllocator(int decimalsCount, int booleansCount) {
        this->m_decimals = new PointerList<StatisticItemDouble>(decimalsCount, true);
        this->m_booleans = new PointerList<StatisticItem<bool>>(booleansCount, true);
    }
    PointerList<StatisticItemDouble>* Decimals() { return this->m_decimals; }
    PointerList<StatisticItem<bool>>* Booleans() { return this->m_booleans; }
};

class DefaultStatisticItemAllocator {
public:
    static StatisticItemAllocator* Default;
};

template <typename T> class MarketSymbolInfo;

template <typename T> class StatisticsInfo {
    MDEntrQueue<T>      *m_entryInfo;

    PointerListLite<StatisticItemDouble>    *m_buyQuotes;
    PointerListLite<StatisticItemDouble>    *m_sellQuotes;
    PointerListLite<StatisticItemDouble>    *m_lstDealInfo;
    PointerListLite<StatisticItemDouble>    *m_indicesList;
    PointerListLite<StatisticItemDouble>    *m_priceOpenFirst;
    PointerListLite<StatisticItemDouble>    *m_priceCloseLast;
    PointerListLite<StatisticItemDouble>    *m_priceMax;
    PointerListLite<StatisticItemDouble>    *m_priceMin;
    PointerListLite<StatisticItemDouble>    *m_priceAve;
    PointerListLite<StatisticItemDouble>    *m_disbalance;
    PointerListLite<StatisticItemDouble>    *m_transactionMagnitude;
    PointerListLite<StatisticItemDouble>    *m_askPriceMax;
    PointerListLite<StatisticItemDouble>    *m_bidPriceMin;
    PointerListLite<StatisticItemDouble>    *m_auctionPriceCalculated;
    PointerListLite<StatisticItemDouble>    *m_auctionPriceClose;

    PointerListLite<StatisticItemDouble>    *m_auctionMagnitudeClose;
    PointerListLite<StatisticItem<bool>>    *m_fullCoveredDealFlag;
    PointerListLite<StatisticItemDouble>    *m_openCloseAuctionTradeAskMagnitude;
    PointerListLite<StatisticItemDouble>    *m_openCloseAuctionTradeBidMagnitude;
    PointerListLite<StatisticItemDouble>    *m_openCloseAuctionTradeAsk;
    PointerListLite<StatisticItemDouble>    *m_openCloseAuctionTradeBid;
    PointerListLite<StatisticItemDouble>    *m_preTradePeriodPrice;
    PointerListLite<StatisticItemDouble>    *m_sessionAsk;
    PointerListLite<StatisticItemDouble>    *m_sessionBid;
    PointerListLite<StatisticItemDouble>    *m_postTradePeriodPrice;
    PointerListLite<StatisticItemDouble>    *m_tradePrice;
    PointerListLite<StatisticItemDouble>    *m_tradePrice2;
    PointerListLite<StatisticItemDouble>    *m_priceOpenOfficial;
    PointerListLite<StatisticItemDouble>    *m_priceCurrentOfficial;
    PointerListLite<StatisticItemDouble>    *m_legitimQuote;
    PointerListLite<StatisticItemDouble>    *m_priceCloseOfficial;
    PointerListLite<StatisticItemDouble>    *m_auctionPriceBigPackets;
    PointerListLite<StatisticItemDouble>    *m_duration;
    PointerListLite<StatisticItemDouble>    *m_askTotal;
    PointerListLite<StatisticItemDouble>    *m_bidTotal;
    PointerListLite<StatisticItemDouble>    *m_auctionMagnitudeBigPackets;
    PointerListLite<StatisticItemDouble>    *m_cumulativeCouponDebit;

    bool                 m_used;
    bool                 m_shouldProcessSnapshot;
    int                  m_rptSeq;
    MarketSymbolInfo<StatisticsInfo<T>>    *m_symbolInfo;
    SizedArray          *m_tradingSession;
public:
    StatisticsInfo() {
        this->m_entryInfo = new MDEntrQueue<T>();
        this->m_tradingSession = new SizedArray();
        this->m_shouldProcessSnapshot = false;
        this->m_rptSeq = 0;
        
        this->m_buyQuotes = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_sellQuotes = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_lstDealInfo = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_indicesList = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceOpenFirst = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceCloseLast = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceMax = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceMin = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceAve = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_disbalance = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_transactionMagnitude = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_askPriceMax = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_bidPriceMin = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionPriceCalculated = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionPriceClose = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionMagnitudeClose = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_fullCoveredDealFlag = new PointerListLite<StatisticItem<bool>>(DefaultStatisticItemAllocator::Default->Booleans());
        this->m_openCloseAuctionTradeAskMagnitude = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_openCloseAuctionTradeBidMagnitude = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_openCloseAuctionTradeAsk = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_openCloseAuctionTradeBid = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_preTradePeriodPrice = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_sessionAsk = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_sessionBid = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_postTradePeriodPrice = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_tradePrice = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_tradePrice2 = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceOpenOfficial = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceCurrentOfficial = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_legitimQuote = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceCloseOfficial = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionPriceBigPackets = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_duration = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_askTotal = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_bidTotal = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionMagnitudeBigPackets = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_cumulativeCouponDebit = new PointerListLite<StatisticItemDouble>(DefaultStatisticItemAllocator::Default->Decimals());
    }
    ~StatisticsInfo() {
        delete this->m_entryInfo;

        delete this->m_buyQuotes;
        delete this->m_sellQuotes;
        delete this->m_lstDealInfo;
        delete this->m_indicesList;
        delete this->m_priceOpenFirst;
        delete this->m_priceCloseLast;
        delete this->m_priceMax;
        delete this->m_priceMin;
        delete this->m_priceAve;
        delete this->m_disbalance;
        delete this->m_transactionMagnitude;
        delete this->m_askPriceMax;
        delete this->m_bidPriceMin;
        delete this->m_auctionPriceCalculated;
        delete this->m_auctionPriceClose;
        delete this->m_auctionMagnitudeClose;
        delete this->m_fullCoveredDealFlag;
        delete this->m_openCloseAuctionTradeAskMagnitude;
        delete this->m_openCloseAuctionTradeBidMagnitude;
        delete this->m_openCloseAuctionTradeAsk;
        delete this->m_openCloseAuctionTradeBid;
        delete this->m_preTradePeriodPrice;
        delete this->m_sessionAsk;
        delete this->m_sessionBid;
        delete this->m_postTradePeriodPrice;
        delete this->m_tradePrice;
        delete this->m_tradePrice2;
        delete this->m_priceOpenOfficial;
        delete this->m_priceCurrentOfficial;
        delete this->m_legitimQuote;
        delete this->m_priceCloseOfficial;
        delete this->m_auctionPriceBigPackets;
        delete this->m_duration;
        delete this->m_askTotal;
        delete this->m_bidTotal;
        delete this->m_auctionMagnitudeBigPackets;
        delete this->m_cumulativeCouponDebit;
    }

    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline SizedArray* Symbol() { return this->m_symbolInfo->Symbol(); }
    inline MarketSymbolInfo<StatisticsInfo<T>>* SymbolInfo() { return this->m_symbolInfo; }
    inline void SymbolInfo(MarketSymbolInfo<StatisticsInfo<T>>* symbolInfo) { this->m_symbolInfo = symbolInfo; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }

    inline MDEntrQueue<T>* EntriesQueue() { return this->m_entryInfo; }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerList<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            node->Data()->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
         this->m_buyQuotes->Clear();
         this->m_sellQuotes->Clear();
         this->m_lstDealInfo->Clear();
         this->m_indicesList->Clear();
         this->m_priceOpenFirst->Clear();
         this->m_priceCloseLast->Clear();
         this->m_priceMax->Clear();
         this->m_priceMin->Clear();
         this->m_priceAve->Clear();
         this->m_disbalance->Clear();
         this->m_transactionMagnitude->Clear();
         this->m_askPriceMax->Clear();
         this->m_bidPriceMin->Clear();
         this->m_auctionPriceCalculated->Clear();
         this->m_auctionPriceClose->Clear();
         this->m_auctionMagnitudeClose->Clear();
         this->m_fullCoveredDealFlag->Clear();
         this->m_openCloseAuctionTradeAskMagnitude->Clear();
         this->m_openCloseAuctionTradeBidMagnitude->Clear();
         this->m_openCloseAuctionTradeAsk->Clear();
         this->m_openCloseAuctionTradeBid->Clear();
         this->m_preTradePeriodPrice->Clear();
         this->m_sessionAsk->Clear();
         this->m_sessionBid->Clear();
         this->m_postTradePeriodPrice->Clear();
         this->m_tradePrice->Clear();
         this->m_tradePrice2->Clear();
         this->m_priceOpenOfficial->Clear();
         this->m_priceCurrentOfficial->Clear();
         this->m_legitimQuote->Clear();
         this->m_priceCloseOfficial->Clear();
         this->m_auctionPriceBigPackets->Clear();
         this->m_duration->Clear();
         this->m_askTotal->Clear();
         this->m_bidTotal->Clear();
         this->m_auctionMagnitudeBigPackets->Clear();
         this->m_cumulativeCouponDebit->Clear();
        
        this->m_entryInfo->Clear();
        this->m_rptSeq = 0;
    }

    inline PointerListLite<StatisticItemDouble>* BuyQuotes() { return this->m_buyQuotes; }
    inline PointerListLite<StatisticItemDouble>* SellQuotes() { return this->m_sellQuotes; }
    inline PointerListLite<StatisticItemDouble>* ListDealInfo() { return this->m_lstDealInfo; }
    inline PointerListLite<StatisticItemDouble>* IndicesList() { return this->m_indicesList; }
    inline PointerListLite<StatisticItemDouble>* PriceOpenFirst() { return this->m_priceOpenFirst; }
    inline PointerListLite<StatisticItemDouble>* PriceCloseLast() { return this->m_priceCloseLast; }
    inline PointerListLite<StatisticItemDouble>* PriceMax() { return this->m_priceMax; }
    inline PointerListLite<StatisticItemDouble>* PriceMin() { return this->m_priceMin; }
    inline PointerListLite<StatisticItemDouble>* PriceAve() { return this->m_priceAve; }
    inline PointerListLite<StatisticItemDouble>* Disbalance() { return this->m_disbalance; }
    inline PointerListLite<StatisticItemDouble>* TransactionMagnitude() { return this->m_transactionMagnitude; }
    inline PointerListLite<StatisticItemDouble>* AskPriceMax() { return this->m_askPriceMax; }
    inline PointerListLite<StatisticItemDouble>* BidPriceMin() { return this->m_bidPriceMin; }
    inline PointerListLite<StatisticItemDouble>* AuctionPriceCalculated() { return this->m_auctionPriceCalculated; }
    inline PointerListLite<StatisticItemDouble>* AuctionPriceClose() { return this->m_auctionPriceClose; }
    inline PointerListLite<StatisticItemDouble>* AuctionMagnitudeClose() { return this->m_auctionMagnitudeClose; }
    inline PointerListLite<StatisticItem<bool>>* FullCoveredDealFlag() { return this->m_fullCoveredDealFlag; }
    inline PointerListLite<StatisticItemDouble>* OpenCloseAuctionTradeAskMagnitude() { return this->m_openCloseAuctionTradeAskMagnitude; }
    inline PointerListLite<StatisticItemDouble>* OpenCloseAuctionTradeBidMagnitude() { return this->m_openCloseAuctionTradeBidMagnitude; }
    inline PointerListLite<StatisticItemDouble>* OpenCloseAuctionTradeAsk() { return this->m_openCloseAuctionTradeAsk; }
    inline PointerListLite<StatisticItemDouble>* OpenCloseAuctionTradBid() { return this->m_openCloseAuctionTradeBid; }
    inline PointerListLite<StatisticItemDouble>* PreTradePeriodPrice() { return this->m_preTradePeriodPrice; }
    inline PointerListLite<StatisticItemDouble>* SessionAsk() { return this->m_sessionAsk; }
    inline PointerListLite<StatisticItemDouble>* SessionBid() { return this->m_sessionBid; }
    inline PointerListLite<StatisticItemDouble>* PostTradePeriodPrice() { return this->m_postTradePeriodPrice; }
    inline PointerListLite<StatisticItemDouble>* TradePrice() { return this->m_tradePrice; }
    inline PointerListLite<StatisticItemDouble>* TradePrice2() { return this->m_tradePrice2; }
    inline PointerListLite<StatisticItemDouble>* PriceOpenOfficial() { return this->m_priceOpenOfficial; }
    inline PointerListLite<StatisticItemDouble>* PriceCurrentOfficial() { return this->m_priceCurrentOfficial; }
    inline PointerListLite<StatisticItemDouble>* LegitimQuote() { return this->m_legitimQuote; }
    inline PointerListLite<StatisticItemDouble>* PriceCloseOfficial() { return this->m_priceCloseOfficial; }
    inline PointerListLite<StatisticItemDouble>* AuctionPriceBigPackets() { return this->m_auctionPriceBigPackets; }
    inline PointerListLite<StatisticItemDouble>* Duration() { return this->m_duration; }
    inline PointerListLite<StatisticItemDouble>* AskTotal() { return this->m_askTotal; }
    inline PointerListLite<StatisticItemDouble>* BidTotal() { return this->m_bidTotal; }
    inline PointerListLite<StatisticItemDouble>* AuctionMagnitudeBigPackets() { return this->m_auctionMagnitudeBigPackets; }
    inline PointerListLite<StatisticItemDouble>* CumulativeCouponDebit() { return this->m_cumulativeCouponDebit; }

    inline void AddDecimalItem(PointerListLite<StatisticItemDouble> *list, Decimal *value, UINT32 time, UINT32 origTime) {
        LinkedPointer<StatisticItemDouble> *node = list->Add();
        node->Data()->Set(time, origTime, value);
    }
    inline void ChangeDecimalItem(PointerListLite<StatisticItemDouble> *list, Decimal *value, UINT32 time, UINT32 origTime) {
        LinkedPointer<StatisticItemDouble> *node = list->Add();
        node->Data()->Set(time, origTime, value);
    }

    inline void AddBuyQuote(T *item) { this->AddDecimalItem(this->m_buyQuotes, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddSellQuote(T *item) { this->AddDecimalItem(this->m_sellQuotes, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddLastDealInfo(T *item) { this->AddDecimalItem(this->m_lstDealInfo, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddIndicesList(T *item) { this->AddDecimalItem(this->m_indicesList, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceOpenFirst(T *item) { this->AddDecimalItem(this->m_priceOpenFirst, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceCloseLast(T *item) { this->AddDecimalItem(this->m_priceCloseLast, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceMax(T *item) { this->AddDecimalItem(this->m_priceMax, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceMin(T *item) { this->AddDecimalItem(this->m_priceMin, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceAve(T *item) { this->AddDecimalItem(this->m_priceAve, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddDisbalance(T *item) { this->AddDecimalItem(this->m_disbalance, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddTransactionsMagnitude(T *item) { this->AddDecimalItem(this->m_transactionMagnitude, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddEmptyBook(T *item) { throw; }
    inline void AddAskPriceMax(T *item) { this->AddDecimalItem(this->m_askPriceMax, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddBidPriceMin(T *item) { this->AddDecimalItem(this->m_bidPriceMin, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAuctionPriceCalculated(T *item) { this->AddDecimalItem(this->m_auctionPriceCalculated, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAuctionPriceClose(T *item) { this->AddDecimalItem(this->m_auctionPriceClose, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAuctionMagnitudeClose(T *item) { this->AddDecimalItem(this->m_auctionMagnitudeClose, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddMSSFullCoveredDealFlag(T *item) { throw; }
    inline void AddMSSTradeAskAuctionMagnitudeOpenClose(T *item) { this->AddDecimalItem(this->m_openCloseAuctionTradeAskMagnitude, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddOLSTradeAskAuctionOpenClose(T *item) { this->AddDecimalItem(this->m_openCloseAuctionTradeAsk, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddMSSTradeBidAuctionMagnitudeOpenClose(T *item) { this->AddDecimalItem(this->m_openCloseAuctionTradeBidMagnitude, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddOLSTradeBidAuctionOpenClose(T *item) { this->AddDecimalItem(this->m_openCloseAuctionTradeBid, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPreTradePeriodPrice(T *item) { this->AddDecimalItem(this->m_preTradePeriodPrice, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddSessionAsk(T *item) { this->AddDecimalItem(this->m_sessionAsk, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddSessionBid(T *item) { this->AddDecimalItem(this->m_sessionBid, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPostTradePeriodPrice(T *item) { this->AddDecimalItem(this->m_postTradePeriodPrice, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddTradePrice2(T *item) { this->AddDecimalItem(this->m_tradePrice2, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddTradePrice(T *item) { this->AddDecimalItem(this->m_tradePrice, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceOpenOfficial(T *item) { this->AddDecimalItem(this->m_priceOpenOfficial, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceCurrentOfficial(T *item) { this->AddDecimalItem(this->m_priceCurrentOfficial, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddLegitimQuote(T *item) { this->AddDecimalItem(this->m_legitimQuote, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddPriceCloseOfficial(T *item) { this->AddDecimalItem(this->m_priceCloseOfficial, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAuctionPriceBigPackets(T *item) { this->AddDecimalItem(this->m_auctionPriceBigPackets, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddDuration(T *item) { this->AddDecimalItem(this->m_duration, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAskTotal(T *item) { this->AddDecimalItem(this->m_askTotal, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddBidTotal(T *item) { this->AddDecimalItem(this->m_bidTotal, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAuctionMagnitudeBigPackets(T *item) { this->AddDecimalItem(this->m_auctionMagnitudeBigPackets, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddCumulativeCouponDebit(T *item) { this->AddDecimalItem(this->m_cumulativeCouponDebit, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void AddAllDeals(T *item) { throw; }

    inline void ChangeBuyQuote(T *item) { this->ChangeDecimalItem(this->m_buyQuotes, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeSellQuote(T *item) { this->ChangeDecimalItem(this->m_sellQuotes, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeLastDealInfo(T *item) { this->ChangeDecimalItem(this->m_lstDealInfo, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeIndicesList(T *item) { this->ChangeDecimalItem(this->m_indicesList, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceOpenFirst(T *item) { this->ChangeDecimalItem(this->m_priceOpenFirst, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceCloseLast(T *item) { this->ChangeDecimalItem(this->m_priceCloseLast, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceMax(T *item) { this->ChangeDecimalItem(this->m_priceMax, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceMin(T *item) { this->ChangeDecimalItem(this->m_priceMin, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceAve(T *item) { this->ChangeDecimalItem(this->m_priceAve, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeDisbalance(T *item) { this->ChangeDecimalItem(this->m_disbalance, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeTransactionsMagnitude(T *item) { this->ChangeDecimalItem(this->m_transactionMagnitude, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeEmptyBook(T *item) { throw; }
    inline void ChangeAskPriceMax(T *item) { this->ChangeDecimalItem(this->m_askPriceMax, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeBidPriceMin(T *item) { this->ChangeDecimalItem(this->m_bidPriceMin, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAuctionPriceCalculated(T *item) { this->ChangeDecimalItem(this->m_auctionPriceCalculated, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAuctionPriceClose(T *item) { this->ChangeDecimalItem(this->m_auctionPriceClose, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAuctionMagnitudeClose(T *item) { this->ChangeDecimalItem(this->m_auctionMagnitudeClose, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeMSSFullCoveredDealFlag(T *item) { throw; }
    inline void ChangeMSSTradeAskAuctionMagnitudeOpenClose(T *item) { this->ChangeDecimalItem(this->m_openCloseAuctionTradeAskMagnitude, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeOLSTradeAskAuctionOpenClose(T *item) { this->ChangeDecimalItem(this->m_openCloseAuctionTradeAsk, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeMSSTradeBidAuctionMagnitudeOpenClose(T *item) { this->ChangeDecimalItem(this->m_openCloseAuctionTradeBidMagnitude, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeOLSTradeBidAuctionOpenClose(T *item) { this->ChangeDecimalItem(this->m_openCloseAuctionTradeBid, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePreTradePeriodPrice(T *item) { this->ChangeDecimalItem(this->m_preTradePeriodPrice, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeSessionAsk(T *item) { this->ChangeDecimalItem(this->m_sessionAsk, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeSessionBid(T *item) { this->ChangeDecimalItem(this->m_sessionBid, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePostTradePeriodPrice(T *item) { this->ChangeDecimalItem(this->m_postTradePeriodPrice, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeTradePrice2(T *item) { this->ChangeDecimalItem(this->m_tradePrice2, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeTradePrice(T *item) { this->ChangeDecimalItem(this->m_tradePrice, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceOpenOfficial(T *item) { this->ChangeDecimalItem(this->m_priceOpenOfficial, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceCurrentOfficial(T *item) { this->ChangeDecimalItem(this->m_priceCurrentOfficial, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeLegitimQuote(T *item) { this->ChangeDecimalItem(this->m_legitimQuote, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangePriceCloseOfficial(T *item) { this->ChangeDecimalItem(this->m_priceCloseOfficial, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAuctionPriceBigPackets(T *item) { this->ChangeDecimalItem(this->m_auctionPriceBigPackets, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeDuration(T *item) { this->ChangeDecimalItem(this->m_duration, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAskTotal(T *item) { this->ChangeDecimalItem(this->m_askTotal, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeBidTotal(T *item) { this->ChangeDecimalItem(this->m_bidTotal, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAuctionMagnitudeBigPackets(T *item) { this->ChangeDecimalItem(this->m_auctionMagnitudeBigPackets, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeCumulativeCouponDebit(T *item) { this->ChangeDecimalItem(this->m_cumulativeCouponDebit, &(item->MDEntryPx), item->MDEntryTime, item->OrigTime); }
    inline void ChangeAllDeals(T *item) { throw; }

    inline void RemoveBuyQuote(T *item) { throw; }
    inline void RemoveSellQuote(T *item) { throw; }
    inline void RemoveLastDealInfo(T *item) { throw; }
    inline void RemoveIndicesList(T *item) { throw; }
    inline void RemovePriceOpenFirst(T *item) { throw; }
    inline void RemovePriceCloseLast(T *item) { throw; }
    inline void RemovePriceMax(T *item) { throw; }
    inline void RemovePriceMin(T *item) { throw; }
    inline void RemovePriceAve(T *item) { throw; }
    inline void RemoveDisbalance(T *item) { throw; }
    inline void RemoveTransactionsMagnitude(T *item) { throw; }
    inline void RemoveEmptyBook(T *item) { throw; }
    inline void RemoveAskPriceMax(T *item) { throw; }
    inline void RemoveBidPriceMin(T *item) { throw; }
    inline void RemoveAuctionPriceCalculated(T *item) { throw; }
    inline void RemoveAuctionPriceClose(T *item) { throw; }
    inline void RemoveAuctionMagnitudeClose(T *item) { throw; }
    inline void RemoveMSSFullCoveredDealFlag(T *item) { throw; }
    inline void RemoveMSSTradeAskAuctionMagnitudeOpenClose(T *item) { throw; }
    inline void RemoveOLSTradeAskAuctionOpenClose(T *item) { throw; }
    inline void RemoveMSSTradeBidAuctionMagnitudeOpenClose(T *item) { throw; }
    inline void RemoveOLSTradeBidAuctionOpenClose(T *item) { throw; }
    inline void RemovePreTradePeriodPrice(T *item) { throw; }
    inline void RemoveSessionAsk(T *item) { throw; }
    inline void RemoveSessionBid(T *item) { throw; }
    inline void RemovePostTradePeriodPrice(T *item) { throw; }
    inline void RemoveTradePrice2(T *item) { throw; }
    inline void RemoveTradePrice(T *item) { throw; }
    inline void RemovePriceOpenOfficial(T *item) { throw; }
    inline void RemovePriceCurrentOfficial(T *item) { throw; }
    inline void RemoveLegitimQuote(T *item) { throw; }
    inline void RemovePriceCloseOfficial(T *item) { throw; }
    inline void RemoveAuctionPriceBigPackets(T *item) { throw; }
    inline void RemoveDuration(T *item) { throw; }
    inline void RemoveAskTotal(T *item) { throw; }
    inline void RemoveBidTotal(T *item) { throw; }
    inline void RemoveAuctionMagnitudeBigPackets(T *item) { throw; }
    inline void RemoveCumulativeCouponDebit(T *item) { throw; }
    inline void RemoveAllDeals(T *item) { throw; }

    inline void AddProperty(MDEntryType entryType, T *item) {
        if(entryType <= MDEntryType::mdetOLSTradeAskAuctionOpenClose) {
            if(entryType <= MDEntryType::mdetDisbalance) {
                if(entryType <= MDEntryType::mdetPriceOpenFirst) {
                    if(entryType <= MDEntryType::mdetLastDealInfo) {
                        if(entryType <= MDEntryType::mdetSellQuote) {
                            if(entryType == MDEntryType::mdetBuyQuote) {
                                this->AddBuyQuote(item);
                            }
                            else { // mdetSellQuote
                                this->AddSellQuote(item);
                            }
                        }
                        else { // mdetLastDealInfo
                            this->AddLastDealInfo(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetIndicesList) {
                            this->AddIndicesList(item);
                        }
                        else { // mdetPriceOpenFirst
                            this->AddPriceOpenFirst(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetPriceMin) {
                        if(entryType <= MDEntryType::mdetPriceMax) {
                            if(entryType == MDEntryType::mdetPriceCloseLast) {
                                this->AddPriceCloseLast(item);
                            }
                            else { // mdetPriceMax
                                this->AddPriceMax(item);
                            }
                        }
                        else {
                            // mdetPriceMin
                            this->AddPriceMin(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceAve) {
                            this->AddPriceAve(item);
                        }
                        else { // mdetDisbalance
                            this->AddDisbalance(item);
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAuctionPriceCalculated) {
                    if(entryType <= MDEntryType::mdetAskPriceMax) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                                this->AddTransactionsMagnitude(item);
                            }
                            else { // mdetEmptyBook
                                this->AddEmptyBook(item);
                            }
                        }
                        else {
                            // mdetAskPriceMax
                            this->AddAskPriceMax(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMin) {
                            this->AddBidPriceMin(item);
                        }
                        else { // mdetAuctionPriceCalculated
                            this->AddAuctionPriceCalculated(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetMSSTradingDenyNotEnoughMoney) {
                        if(entryType <= MDEntryType::mdetAuctionMagnitudeClose) {
                            if(entryType == MDEntryType::mdetAuctionPriceClose) {
                                this->AddAuctionPriceClose(item);
                            }
                            else { // mdetAuctionMagnitudeClose
                                this->AddAuctionMagnitudeClose(item);
                            }
                        }
                        else {
                            // mdetMSSTradingDenyNotEnoughMoney
                            this->AddMSSFullCoveredDealFlag(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetMSSTradeAskAuctionMagnitudeOpenClose) {
                            this->AddMSSTradeAskAuctionMagnitudeOpenClose(item);
                        }
                        else { // mdetOLSTradeAskAuctionOpenClose
                            this->AddOLSTradeAskAuctionOpenClose(item);
                        }
                    }
                }
            }
        }
        else {
            if(entryType <= MDEntryType::mdetPriceCurrentOfficial) {
                if(entryType <= MDEntryType::mdetSessionBid) {
                    if(entryType <= MDEntryType::mdetPreTradePeriodPrice) {
                        if(entryType <= MDEntryType::mdetOLSTradeBidAuctionOpenClose) {
                            if(entryType == MDEntryType::mdetMSSTradeBidAuctionMagnitudeOpenClose) {
                                this->AddMSSTradeBidAuctionMagnitudeOpenClose(item);
                            }
                            else { // mdetOLSTradeBidAuctionOpenClose
                                this->AddOLSTradeBidAuctionOpenClose(item);
                            }
                        }
                        else {
                            // mdetPreTradePeriodPrice
                            this->AddPreTradePeriodPrice(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetSessionAsk) {
                            this->AddSessionAsk(item);
                        }
                        else { // mdetSessionBid
                            this->AddSessionBid(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetTradePrice) {
                        if(entryType <= MDEntryType::mdetTradePrice2) {
                            if(entryType == MDEntryType::mdetPostTradePeriodPrice) {
                                this->AddPostTradePeriodPrice(item);
                            }
                            else { // mdetTradePrice2
                                this->AddTradePrice2(item);
                            }
                        }
                        else {
                            // mdetTradePrice
                            this->AddTradePrice(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceOpenOfficial) {
                            this->AddPriceOpenOfficial(item);
                        }
                        else { // mdetPriceCurrentOfficial
                            this->AddPriceCurrentOfficial(item);
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAskTotal) {
                    if(entryType <= MDEntryType::mdetAuctionPriceBigPackets) {
                        if(entryType <= MDEntryType::mdetPriceCloseOfficial) {
                            if(entryType == MDEntryType::mdetLegitimQuote) {
                                this->AddLegitimQuote(item);
                            }
                            else { // mdetPriceCloseOfficial
                                this->AddPriceCloseOfficial(item);
                            }
                        }
                        else {
                            // mdetAuctionPriceBigPackets
                            this->AddAuctionPriceBigPackets(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetDuration) {
                            this->AddDuration(item);
                        }
                        else { // mdetAskTotal
                            this->AddAskTotal(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetAuctionMagnitudeBigPackets) {
                        if(entryType == MDEntryType::mdetBidTotal) {
                            this->AddBidTotal(item);
                        }
                        else { // mdetAuctionMagnitudeBigPackets
                            this->AddAuctionMagnitudeBigPackets(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetCumulativeCouponDebit) {
                            this->AddCumulativeCouponDebit(item);
                        }
                        else { // mdetAllDeals
                            this->AddAllDeals(item);
                        }
                    }
                }
            }
        }
    }

    inline void ChangeProperty(MDEntryType entryType, T *item) {
        if(entryType <= MDEntryType::mdetOLSTradeAskAuctionOpenClose) {
            if(entryType <= MDEntryType::mdetDisbalance) {
                if(entryType <= MDEntryType::mdetPriceOpenFirst) {
                    if(entryType <= MDEntryType::mdetLastDealInfo) {
                        if(entryType <= MDEntryType::mdetSellQuote) {
                            if(entryType == MDEntryType::mdetBuyQuote) {
                                this->ChangeBuyQuote(item);
                            }
                            else { // mdetSellQuote
                                this->ChangeSellQuote(item);
                            }
                        }
                        else { // mdetLastDealInfo
                            this->ChangeLastDealInfo(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetIndicesList) {
                            this->ChangeIndicesList(item);
                        }
                        else { // mdetPriceOpenFirst
                            this->ChangePriceOpenFirst(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetPriceMin) {
                        if(entryType <= MDEntryType::mdetPriceMax) {
                            if(entryType == MDEntryType::mdetPriceCloseLast) {
                                this->ChangePriceCloseLast(item);
                            }
                            else { // mdetPriceMax
                                this->ChangePriceMax(item);
                            }
                        }
                        else {
                            // mdetPriceMin
                            this->ChangePriceMin(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceAve) {
                            this->ChangePriceAve(item);
                        }
                        else { // mdetDisbalance
                            this->ChangeDisbalance(item);
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAuctionPriceCalculated) {
                    if(entryType <= MDEntryType::mdetAskPriceMax) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                                this->ChangeTransactionsMagnitude(item);
                            }
                            else { // mdetEmptyBook
                                this->ChangeEmptyBook(item);
                            }
                        }
                        else {
                            // mdetAskPriceMax
                            this->ChangeAskPriceMax(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMin) {
                            this->ChangeBidPriceMin(item);
                        }
                        else { // mdetAuctionPriceCalculated
                            this->ChangeAuctionPriceCalculated(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetMSSTradingDenyNotEnoughMoney) {
                        if(entryType <= MDEntryType::mdetAuctionMagnitudeClose) {
                            if(entryType == MDEntryType::mdetAuctionPriceClose) {
                                this->ChangeAuctionPriceClose(item);
                            }
                            else { // mdetAuctionMagnitudeClose
                                this->ChangeAuctionMagnitudeClose(item);
                            }
                        }
                        else {
                            // mdetMSSTradingDenyNotEnoughMoney
                            this->ChangeMSSFullCoveredDealFlag(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetMSSTradeAskAuctionMagnitudeOpenClose) {
                            this->ChangeMSSTradeAskAuctionMagnitudeOpenClose(item);
                        }
                        else { // mdetOLSTradeAskAuctionOpenClose
                            this->ChangeOLSTradeAskAuctionOpenClose(item);
                        }
                    }
                }
            }
        }
        else {
            if(entryType <= MDEntryType::mdetPriceCurrentOfficial) {
                if(entryType <= MDEntryType::mdetSessionBid) {
                    if(entryType <= MDEntryType::mdetPreTradePeriodPrice) {
                        if(entryType <= MDEntryType::mdetOLSTradeBidAuctionOpenClose) {
                            if(entryType == MDEntryType::mdetMSSTradeBidAuctionMagnitudeOpenClose) {
                                this->ChangeMSSTradeBidAuctionMagnitudeOpenClose(item);
                            }
                            else { // mdetOLSTradeBidAuctionOpenClose
                                this->ChangeOLSTradeBidAuctionOpenClose(item);
                            }
                        }
                        else {
                            // mdetPreTradePeriodPrice
                            this->ChangePreTradePeriodPrice(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetSessionAsk) {
                            this->ChangeSessionAsk(item);
                        }
                        else { // mdetSessionBid
                            this->ChangeSessionBid(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetTradePrice) {
                        if(entryType <= MDEntryType::mdetTradePrice2) {
                            if(entryType == MDEntryType::mdetPostTradePeriodPrice) {
                                this->ChangePostTradePeriodPrice(item);
                            }
                            else { // mdetTradePrice2
                                this->ChangeTradePrice2(item);
                            }
                        }
                        else {
                            // mdetTradePrice
                            this->ChangeTradePrice(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceOpenOfficial) {
                            this->ChangePriceOpenOfficial(item);
                        }
                        else { // mdetPriceCurrentOfficial
                            this->ChangePriceCurrentOfficial(item);
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAskTotal) {
                    if(entryType <= MDEntryType::mdetAuctionPriceBigPackets) {
                        if(entryType <= MDEntryType::mdetPriceCloseOfficial) {
                            if(entryType == MDEntryType::mdetLegitimQuote) {
                                this->ChangeLegitimQuote(item);
                            }
                            else { // mdetPriceCloseOfficial
                                this->ChangePriceCloseOfficial(item);
                            }
                        }
                        else {
                            // mdetAuctionPriceBigPackets
                            this->ChangeAuctionPriceBigPackets(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetDuration) {
                            this->ChangeDuration(item);
                        }
                        else { // mdetAskTotal
                            this->ChangeAskTotal(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetAuctionMagnitudeBigPackets) {
                        if(entryType == MDEntryType::mdetBidTotal) {
                            this->ChangeBidTotal(item);
                        }
                        else { // mdetAuctionMagnitudeBigPackets
                            this->ChangeAuctionMagnitudeBigPackets(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetCumulativeCouponDebit) {
                            this->ChangeCumulativeCouponDebit(item);
                        }
                        else { // mdetAllDeals
                            this->ChangeAllDeals(item);
                        }
                    }
                }
            }
        }
    }

    inline void RemoveProperty(MDEntryType entryType, T *item) {
        if(entryType <= MDEntryType::mdetOLSTradeAskAuctionOpenClose) {
            if(entryType <= MDEntryType::mdetDisbalance) {
                if(entryType <= MDEntryType::mdetPriceOpenFirst) {
                    if(entryType <= MDEntryType::mdetLastDealInfo) {
                        if(entryType <= MDEntryType::mdetSellQuote) {
                            if(entryType == MDEntryType::mdetBuyQuote) {
                                this->RemoveBuyQuote(item);
                            }
                            else { // mdetSellQuote
                                this->RemoveSellQuote(item);
                            }
                        }
                        else { // mdetLastDealInfo
                            this->RemoveLastDealInfo(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetIndicesList) {
                            this->RemoveIndicesList(item);
                        }
                        else { // mdetPriceOpenFirst
                            this->RemovePriceOpenFirst(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetPriceMin) {
                        if(entryType <= MDEntryType::mdetPriceMax) {
                            if(entryType == MDEntryType::mdetPriceCloseLast) {
                                this->RemovePriceCloseLast(item);
                            }
                            else { // mdetPriceMax
                                this->RemovePriceMax(item);
                            }
                        }
                        else {
                            // mdetPriceMin
                            this->RemovePriceMin(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceAve) {
                            this->RemovePriceAve(item);
                        }
                        else { // mdetDisbalance
                            this->RemoveDisbalance(item);
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAuctionPriceCalculated) {
                    if(entryType <= MDEntryType::mdetAskPriceMax) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                                this->RemoveTransactionsMagnitude(item);
                            }
                            else { // mdetEmptyBook
                                this->RemoveEmptyBook(item);
                            }
                        }
                        else {
                            // mdetAskPriceMax
                            this->RemoveAskPriceMax(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMin) {
                            this->RemoveBidPriceMin(item);
                        }
                        else { // mdetAuctionPriceCalculated
                            this->RemoveAuctionPriceCalculated(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetMSSTradingDenyNotEnoughMoney) {
                        if(entryType <= MDEntryType::mdetAuctionMagnitudeClose) {
                            if(entryType == MDEntryType::mdetAuctionPriceClose) {
                                this->RemoveAuctionPriceClose(item);
                            }
                            else { // mdetAuctionMagnitudeClose
                                this->RemoveAuctionMagnitudeClose(item);
                            }
                        }
                        else {
                            // mdetMSSTradingDenyNotEnoughMoney
                            this->RemoveMSSFullCoveredDealFlag(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetMSSTradeAskAuctionMagnitudeOpenClose) {
                            this->RemoveMSSTradeAskAuctionMagnitudeOpenClose(item);
                        }
                        else { // mdetOLSTradeAskAuctionOpenClose
                            this->RemoveOLSTradeAskAuctionOpenClose(item);
                        }
                    }
                }
            }
        }
        else {
            if(entryType <= MDEntryType::mdetPriceCurrentOfficial) {
                if(entryType <= MDEntryType::mdetSessionBid) {
                    if(entryType <= MDEntryType::mdetPreTradePeriodPrice) {
                        if(entryType <= MDEntryType::mdetOLSTradeBidAuctionOpenClose) {
                            if(entryType == MDEntryType::mdetMSSTradeBidAuctionMagnitudeOpenClose) {
                                this->RemoveMSSTradeBidAuctionMagnitudeOpenClose(item);
                            }
                            else { // mdetOLSTradeBidAuctionOpenClose
                                this->RemoveOLSTradeBidAuctionOpenClose(item);
                            }
                        }
                        else {
                            // mdetPreTradePeriodPrice
                            this->RemovePreTradePeriodPrice(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetSessionAsk) {
                            this->RemoveSessionAsk(item);
                        }
                        else { // mdetSessionBid
                            this->RemoveSessionBid(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetTradePrice) {
                        if(entryType <= MDEntryType::mdetTradePrice2) {
                            if(entryType == MDEntryType::mdetPostTradePeriodPrice) {
                                this->RemovePostTradePeriodPrice(item);
                            }
                            else { // mdetTradePrice2
                                this->RemoveTradePrice2(item);
                            }
                        }
                        else {
                            // mdetTradePrice
                            this->RemoveTradePrice(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceOpenOfficial) {
                            this->RemovePriceOpenOfficial(item);
                        }
                        else { // mdetPriceCurrentOfficial
                            this->RemovePriceCurrentOfficial(item);
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAskTotal) {
                    if(entryType <= MDEntryType::mdetAuctionPriceBigPackets) {
                        if(entryType <= MDEntryType::mdetPriceCloseOfficial) {
                            if(entryType == MDEntryType::mdetLegitimQuote) {
                                this->RemoveLegitimQuote(item);
                            }
                            else { // mdetPriceCloseOfficial
                                this->RemovePriceCloseOfficial(item);
                            }
                        }
                        else {
                            // mdetAuctionPriceBigPackets
                            this->RemoveAuctionPriceBigPackets(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetDuration) {
                            this->RemoveDuration(item);
                        }
                        else { // mdetAskTotal
                            this->RemoveAskTotal(item);
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetAuctionMagnitudeBigPackets) {
                        if(entryType == MDEntryType::mdetBidTotal) {
                            this->RemoveBidTotal(item);
                        }
                        else { // mdetAuctionMagnitudeBigPackets
                            this->RemoveAuctionMagnitudeBigPackets(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetCumulativeCouponDebit) {
                            this->RemoveCumulativeCouponDebit(item);
                        }
                        else { // mdetAllDeals
                            this->RemoveAllDeals(item);
                        }
                    }
                }
            }
        }
    }

    inline void Add(T *item) {
        AddProperty((MDEntryType)(item->MDEntryType[0]), item);
    }
    inline void Change(T *item) {
        ChangeProperty((MDEntryType)(item->MDEntryType[0]), item);
    }
    inline void Remove(T *item) {
        RemoveProperty((MDEntryType)(item->MDEntryType[0]), item);
    }

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void PushMessageToQueue(T *info) {
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info);
    }

    inline void ForceProcessMessage(T *info) {
        if(info->MDUpdateAction == mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == mduaChange)
            this->Change(info);
        else
            this->Remove(info);
    }

    inline bool ProcessIncrementalMessage(T *info) {
        if(!this->IsNextMessage(info)) {
            this->PushMessageToQueue(info);
            return false;
        }
        this->m_rptSeq = info->RptSeq;
        this->ForceProcessMessage(info);
        if(this->m_entryInfo->HasEntries())
            return this->ProcessQueueMessages();
        return true;
    }

    inline void StartProcessSnapshotMessages() {

    }

    inline void ProcessSnapshotMessage(T *info) {
        this->ForceProcessMessage(info);
    }

    inline bool ProcessQueueMessages() {
        if(!this->m_entryInfo->HasEntries())
            return true;
        T **entry = this->m_entryInfo->Entries();
        int incRptSeq = this->m_entryInfo->RptSeq();
        int maxIndex = this->m_entryInfo->MaxIndex();
        if(this->m_rptSeq + 1 < incRptSeq)
            return false;
        int startIndex = this->m_rptSeq + 1 - incRptSeq;
        for(int i = 0; i < startIndex; i++, entry++) {
            if((*entry) != 0) (*entry)->Clear();
        }
        for(int index = startIndex; index <= maxIndex; index++) {
            if((*entry) == 0)
                return false;
            ForceProcessMessage(*entry);
            this->m_rptSeq = (*entry)->RptSeq;
            entry++;
        }
        this->m_entryInfo->Reset();
        return true;
    }

    inline void DecSessionsToRecvSnapshotCount() {
        if(this->m_shouldProcessSnapshot) {
            SymbolInfo()->DecSessionsToRecvSnapshotCount();
            this->m_shouldProcessSnapshot = false;
        }
    }

    inline bool EndProcessSnapshotMessages() {
        bool res = this->ProcessQueueMessages();
        if(res)
            this->DecSessionsToRecvSnapshotCount();
        return res;
    }

    inline void EnterSnapshotMode() {
        this->m_shouldProcessSnapshot = true;
    }

    inline void ExitSnapshotMode() {
        this->m_shouldProcessSnapshot = false;
    }

    inline bool ShouldProcessSnapshot() {
        return this->m_shouldProcessSnapshot;
    }

    inline void ProcessActualSnapshotState() {
        if(!this->m_shouldProcessSnapshot)
            return;
        this->m_shouldProcessSnapshot = false;
        SymbolInfo()->DecSessionsToRecvSnapshotCount();
    }
};

#endif //HFT_ROBOT_STATISTICINFO_H
