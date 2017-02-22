//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_STATISTICINFO_H
#define HFT_ROBOT_STATISTICINFO_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "MarketDataEntryQueue.h"
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

class StatisticItemLastDealInfo{
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

class StatisticItemTotalOffer{
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

class StatisticItemTransactionsMagnitude{
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

class StatisticItemIndexList{
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
    StatisticItemAllocator() {
        this->m_decimals = new PointerList<StatisticItemDecimal>(10000, true);
        this->m_decimals2 = new PointerList<StatisticItemDecimal2>(10000, true);
        this->m_dealInfos = new PointerList<StatisticItemLastDealInfo>(10000, true);
        this->m_totalOffers = new PointerList<StatisticItemTotalOffer>(80000, true);
        this->m_totalBids = new PointerList<StatisticItemTotalBid>(80000, true);
        this->m_indexLists = new PointerList<StatisticItemIndexList>(10000, true);
        this->m_trMagnitudes = new PointerList<StatisticItemTransactionsMagnitude>(10000, true);
        this->m_booleans = new PointerList<StatisticItem<bool>>(1000, true);
    }
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

template <typename T> class MarketSymbolInfo;

template <typename T> class StatisticsInfo {
    MDEntrQueue<T>      *m_entryInfo;

    PointerListLite<StatisticItemDecimal2>                   *m_buyQuotes;
    PointerListLite<StatisticItemDecimal2>                   *m_sellQuotes;
    PointerListLite<StatisticItemLastDealInfo>              *m_lstDealInfo;
    PointerListLite<StatisticItemIndexList>                 *m_indicesList;
    PointerListLite<StatisticItemDecimal>                    *m_priceOpenFirst;
    PointerListLite<StatisticItemDecimal>                    *m_priceCloseLast;
    PointerListLite<StatisticItemDecimal>                    *m_priceMax;
    PointerListLite<StatisticItemDecimal>                    *m_priceMin;
    PointerListLite<StatisticItemDecimal>                    *m_priceAve;
    PointerListLite<StatisticItemDecimal>                    *m_disbalance;
    PointerListLite<StatisticItemTransactionsMagnitude>     *m_transactionMagnitude;
    PointerListLite<StatisticItemDecimal>                    *m_offerPriceMin;
    PointerListLite<StatisticItemDecimal>                    *m_bidPriceMax;
    PointerListLite<StatisticItemDecimal>                    *m_auctionPriceCalculated;
    PointerListLite<StatisticItemDecimal>                    *m_auctionPriceClose;

    PointerListLite<StatisticItemDecimal>                    *m_auctionMagnitudeClose;
    PointerListLite<StatisticItem<bool>>                    *m_fullCoveredDealFlag;
    PointerListLite<StatisticItemDecimal>                    *m_openCloseAuctionTradeOfferMagnitude;
    PointerListLite<StatisticItemDecimal>                    *m_openCloseAuctionTradeBidMagnitude;
    PointerListLite<StatisticItemDecimal>                    *m_openCloseAuctionTradeOffer;
    PointerListLite<StatisticItemDecimal>                    *m_openCloseAuctionTradeBid;
    PointerListLite<StatisticItemDecimal>                    *m_preTradePeriodPrice;
    PointerListLite<StatisticItemDecimal>                    *m_sessionOffer;
    PointerListLite<StatisticItemDecimal>                    *m_sessionBid;
    PointerListLite<StatisticItemDecimal>                    *m_postTradePeriodPrice;
    PointerListLite<StatisticItemDecimal>                    *m_tradePrice;
    PointerListLite<StatisticItemDecimal>                    *m_tradePrice2;
    PointerListLite<StatisticItemDecimal>                    *m_priceOpenOfficial;
    PointerListLite<StatisticItemDecimal>                    *m_priceCurrentOfficial;
    PointerListLite<StatisticItemDecimal>                    *m_legitimQuote;
    PointerListLite<StatisticItemDecimal>                    *m_priceCloseOfficial;
    PointerListLite<StatisticItemDecimal>                    *m_auctionPriceBigPackets;
    PointerListLite<StatisticItemDecimal>                    *m_duration;
    PointerListLite<StatisticItemTotalOffer>                 *m_offerTotal;
    PointerListLite<StatisticItemTotalBid>                   *m_bidTotal;
    PointerListLite<StatisticItemDecimal>                    *m_auctionMagnitudeBigPackets;
    PointerListLite<StatisticItemDecimal>                    *m_cumulativeCouponDebit;

    bool                 m_used;
    bool                 m_shouldProcessSnapshot;
    int                  m_rptSeq;
    MarketSymbolInfo<StatisticsInfo<T>>    *m_symbolInfo;
    SizedArray          *m_tradingSession;

    UINT64               m_time;
    int                  m_snapshotProcessedCount;
public:
    StatisticsInfo() {
        this->m_entryInfo = new MDEntrQueue<T>();
        this->m_tradingSession = new SizedArray();
        this->m_shouldProcessSnapshot = false;
        this->m_rptSeq = 0;
        this->m_time = 0;
        this->m_snapshotProcessedCount = 0;
        
        this->m_buyQuotes = new PointerListLite<StatisticItemDecimal2>(DefaultStatisticItemAllocator::Default->Decimals2());
        this->m_sellQuotes = new PointerListLite<StatisticItemDecimal2>(DefaultStatisticItemAllocator::Default->Decimals2());
        this->m_lstDealInfo = new PointerListLite<StatisticItemLastDealInfo>(DefaultStatisticItemAllocator::Default->LastDealInfos());
        this->m_indicesList = new PointerListLite<StatisticItemIndexList>(DefaultStatisticItemAllocator::Default->IndexLists());
        this->m_priceOpenFirst = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceCloseLast = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceMax = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceMin = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceAve = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_disbalance = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_transactionMagnitude = new PointerListLite<StatisticItemTransactionsMagnitude>(DefaultStatisticItemAllocator::Default->TransactionMagnitudes());
        this->m_offerPriceMin = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_bidPriceMax = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionPriceCalculated = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionPriceClose = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionMagnitudeClose = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_fullCoveredDealFlag = new PointerListLite<StatisticItem<bool>>(DefaultStatisticItemAllocator::Default->Booleans());
        this->m_openCloseAuctionTradeOfferMagnitude = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_openCloseAuctionTradeBidMagnitude = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_openCloseAuctionTradeOffer = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_openCloseAuctionTradeBid = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_preTradePeriodPrice = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_sessionOffer = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_sessionBid = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_postTradePeriodPrice = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_tradePrice = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_tradePrice2 = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceOpenOfficial = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceCurrentOfficial = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_legitimQuote = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_priceCloseOfficial = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_auctionPriceBigPackets = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_duration = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_offerTotal = new PointerListLite<StatisticItemTotalOffer>(DefaultStatisticItemAllocator::Default->TotalOffers());
        this->m_bidTotal = new PointerListLite<StatisticItemTotalBid>(DefaultStatisticItemAllocator::Default->TotalBids());
        this->m_auctionMagnitudeBigPackets = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_cumulativeCouponDebit = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
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
        delete this->m_offerPriceMin;
        delete this->m_bidPriceMax;
        delete this->m_auctionPriceCalculated;
        delete this->m_auctionPriceClose;
        delete this->m_auctionMagnitudeClose;
        delete this->m_fullCoveredDealFlag;
        delete this->m_openCloseAuctionTradeOfferMagnitude;
        delete this->m_openCloseAuctionTradeBidMagnitude;
        delete this->m_openCloseAuctionTradeOffer;
        delete this->m_openCloseAuctionTradeBid;
        delete this->m_preTradePeriodPrice;
        delete this->m_sessionOffer;
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
        delete this->m_offerTotal;
        delete this->m_bidTotal;
        delete this->m_auctionMagnitudeBigPackets;
        delete this->m_cumulativeCouponDebit;
    }

    inline void ResetSnasphotProcessed() { this->m_snapshotProcessedCount = 0; }
    inline void OnSnapshotProcessed() { this->m_snapshotProcessedCount++; }
    inline int SnapshotProcessedCount() { return this->m_snapshotProcessedCount; }

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
         this->m_offerPriceMin->Clear();
         this->m_bidPriceMax->Clear();
         this->m_auctionPriceCalculated->Clear();
         this->m_auctionPriceClose->Clear();
         this->m_auctionMagnitudeClose->Clear();
         this->m_fullCoveredDealFlag->Clear();
         this->m_openCloseAuctionTradeOfferMagnitude->Clear();
         this->m_openCloseAuctionTradeBidMagnitude->Clear();
         this->m_openCloseAuctionTradeOffer->Clear();
         this->m_openCloseAuctionTradeBid->Clear();
         this->m_preTradePeriodPrice->Clear();
         this->m_sessionOffer->Clear();
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
         this->m_offerTotal->Clear();
         this->m_bidTotal->Clear();
         this->m_auctionMagnitudeBigPackets->Clear();
         this->m_cumulativeCouponDebit->Clear();
        
        this->m_entryInfo->Clear();
        this->m_rptSeq = 0;
    }

    inline PointerListLite<StatisticItemDecimal2>* BuyQuotes() { return this->m_buyQuotes; }
    inline PointerListLite<StatisticItemDecimal2>* SellQuotes() { return this->m_sellQuotes; }
    inline PointerListLite<StatisticItemLastDealInfo>* LastDealInfo() { return this->m_lstDealInfo; }
    inline PointerListLite<StatisticItemIndexList>* IndicesList() { return this->m_indicesList; }
    inline PointerListLite<StatisticItemDecimal>* PriceOpenFirst() { return this->m_priceOpenFirst; }
    inline PointerListLite<StatisticItemDecimal>* PriceCloseLast() { return this->m_priceCloseLast; }
    inline PointerListLite<StatisticItemDecimal>* PriceMax() { return this->m_priceMax; }
    inline PointerListLite<StatisticItemDecimal>* PriceMin() { return this->m_priceMin; }
    inline PointerListLite<StatisticItemDecimal>* PriceAve() { return this->m_priceAve; }
    inline PointerListLite<StatisticItemDecimal>* Disbalance() { return this->m_disbalance; }
    inline PointerListLite<StatisticItemTransactionsMagnitude>* TransactionMagnitude() { return this->m_transactionMagnitude; }
    inline PointerListLite<StatisticItemDecimal>* OfferPriceMax() { return this->m_offerPriceMin; }
    inline PointerListLite<StatisticItemDecimal>* BidPriceMin() { return this->m_bidPriceMax; }
    inline PointerListLite<StatisticItemDecimal>* AuctionPriceCalculated() { return this->m_auctionPriceCalculated; }
    inline PointerListLite<StatisticItemDecimal>* AuctionPriceClose() { return this->m_auctionPriceClose; }
    inline PointerListLite<StatisticItemDecimal>* AuctionMagnitudeClose() { return this->m_auctionMagnitudeClose; }
    inline PointerListLite<StatisticItem<bool>>* FullCoveredDealFlag() { return this->m_fullCoveredDealFlag; }
    inline PointerListLite<StatisticItemDecimal>* OpenCloseAuctionTradeOfferMagnitude() { return this->m_openCloseAuctionTradeOfferMagnitude; }
    inline PointerListLite<StatisticItemDecimal>* OpenCloseAuctionTradeBidMagnitude() { return this->m_openCloseAuctionTradeBidMagnitude; }
    inline PointerListLite<StatisticItemDecimal>* OpenCloseAuctionTradeOffer() { return this->m_openCloseAuctionTradeOffer; }
    inline PointerListLite<StatisticItemDecimal>* OpenCloseAuctionTradBid() { return this->m_openCloseAuctionTradeBid; }
    inline PointerListLite<StatisticItemDecimal>* PreTradePeriodPrice() { return this->m_preTradePeriodPrice; }
    inline PointerListLite<StatisticItemDecimal>* SessionOffer() { return this->m_sessionOffer; }
    inline PointerListLite<StatisticItemDecimal>* SessionBid() { return this->m_sessionBid; }
    inline PointerListLite<StatisticItemDecimal>* PostTradePeriodPrice() { return this->m_postTradePeriodPrice; }
    inline PointerListLite<StatisticItemDecimal>* TradePrice() { return this->m_tradePrice; }
    inline PointerListLite<StatisticItemDecimal>* TradePrice2() { return this->m_tradePrice2; }
    inline PointerListLite<StatisticItemDecimal>* PriceOpenOfficial() { return this->m_priceOpenOfficial; }
    inline PointerListLite<StatisticItemDecimal>* PriceCurrentOfficial() { return this->m_priceCurrentOfficial; }
    inline PointerListLite<StatisticItemDecimal>* LegitimQuote() { return this->m_legitimQuote; }
    inline PointerListLite<StatisticItemDecimal>* PriceCloseOfficial() { return this->m_priceCloseOfficial; }
    inline PointerListLite<StatisticItemDecimal>* AuctionPriceBigPackets() { return this->m_auctionPriceBigPackets; }
    inline PointerListLite<StatisticItemDecimal>* Duration() { return this->m_duration; }
    inline PointerListLite<StatisticItemTotalOffer>* OfferTotal() { return this->m_offerTotal; }
    inline PointerListLite<StatisticItemTotalBid>* BidTotal() { return this->m_bidTotal; }
    inline PointerListLite<StatisticItemDecimal>* AuctionMagnitudeBigPackets() { return this->m_auctionMagnitudeBigPackets; }
    inline PointerListLite<StatisticItemDecimal>* CumulativeCouponDebit() { return this->m_cumulativeCouponDebit; }

    inline void AddPrice(PointerListLite<StatisticItemDecimal> *list, T *item) {
        LinkedPointer<StatisticItemDecimal> *node = list->Add();
        node->Data()->Set(this->m_time, &(item->MDEntryPx));
    }
    inline void ChangePrice(PointerListLite<StatisticItemDecimal> *list, T *item) {
        AddPrice(list, item);
    }

    inline void AddSize(PointerListLite<StatisticItemDecimal> *list, T *item) {
        LinkedPointer<StatisticItemDecimal> *node = list->Add();
        node->Data()->Set(this->m_time, &(item->MDEntrySize));
    }
    inline void ChangeSize(PointerListLite<StatisticItemDecimal> *list, T *item) {
        AddSize(list, item);
    }

    inline void AddPriceSize(PointerListLite<StatisticItemDecimal2> *list, T *item) {
        LinkedPointer<StatisticItemDecimal2> *node = list->Add();
        node->Data()->Set(this->m_time, &(item->MDEntryPx), &(item->MDEntrySize));
    }

    inline void ChangePriceSize(PointerListLite<StatisticItemDecimal2> *list, T *item) {
        AddPriceSize(list, item);
    }

    inline void AddLastDealInfo(PointerListLite<StatisticItemLastDealInfo> *list, T *item) {
        LinkedPointer<StatisticItemLastDealInfo> *node = list->Add();
        node->Data()->Set(this->m_time, item);
    }

    inline void ChangeLastDealInfo(PointerListLite<StatisticItemLastDealInfo> *list, T *item) {
        AddLastDealInfo(list, item);
    }

    inline void AddIndexList(PointerListLite<StatisticItemIndexList> *list, T *item) {
        LinkedPointer<StatisticItemIndexList> *node = list->Add();
        node->Data()->Set(this->m_time, item);
    }

    inline void ChangeIndexList(PointerListLite<StatisticItemIndexList> *list, T *item) {
        AddIndexList(list, item);
    }

    inline void AddTransactionMagnitude(PointerListLite<StatisticItemTransactionsMagnitude> *list, T *item) {
        LinkedPointer<StatisticItemTransactionsMagnitude> *node = list->Add();
        node->Data()->Set(this->m_time, item);
    }

    inline void ChangeTransactionMagnitude(PointerListLite<StatisticItemTransactionsMagnitude> *list, T *item) {
        AddTransactionMagnitude(list, item);
    }

    inline void AddTotalOffer(PointerListLite<StatisticItemTotalOffer> *list, T *item) {
        LinkedPointer<StatisticItemTotalOffer> *node = list->Add();
        node->Data()->Set(this->m_time, item);
    }

    inline void ChangeTotalOffer(PointerListLite<StatisticItemTotalOffer> *list, T *item) {
        AddTotalOffer(list, item);
    }

    inline void AddTotalBid(PointerListLite<StatisticItemTotalBid> *list, T *item) {
        LinkedPointer<StatisticItemTotalBid> *node = list->Add();
        node->Data()->Set(this->m_time, item);
    }

    inline void ChangeTotalBid(PointerListLite<StatisticItemTotalBid> *list, T *item) {
        AddTotalBid(list, item);
    }

    // 0
    inline void AddBuyQuote(T *item) {
        this->AddPriceSize(this->m_buyQuotes, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add BuyQuote ", this->m_buyQuotes);
    }
    // 1
    inline void AddSellQuote(T *item) {
        this->AddPriceSize(this->m_sellQuotes, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add SellQuote ", this->m_sellQuotes);
    }
    // 2
    inline void AddLastDealInfo(T *item) {
        this->AddLastDealInfo(this->m_lstDealInfo, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add SellQuote ", this->m_lstDealInfo);
    }
    // 3
    inline void AddIndicesList(T *item) {
        this->AddIndexList(this->m_indicesList, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Indices List ", this->m_indicesList);
    }
    // 4
    inline void AddPriceOpenFirst(T *item) {
        this->AddPrice(this->m_priceOpenFirst, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Open Price ", this->m_priceOpenFirst);
    }
    // 5
    inline void AddPriceCloseLast(T *item) {
        this->AddPrice(this->m_priceCloseLast, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Close Price ", this->m_priceCloseLast);
    }
    // 7
    inline void AddPriceMax(T *item) {
        this->AddPrice(this->m_priceMax, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Price Max", this->m_priceMax);
    }
    // 8
    inline void AddPriceMin(T *item) {
        this->AddPrice(this->m_priceMin, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Price Min", this->m_priceMin);
    }
    // 9
    inline void AddPriceAve(T *item) {
        this->AddPrice(this->m_priceAve, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Price Ave", this->m_priceAve);
    }
    // A
    inline void AddDisbalance(T *item) {
        this->AddPrice(this->m_disbalance, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Disbalance", this->m_disbalance);
    }
    // B
    inline void AddTransactionsMagnitude(T *item) {
        this->AddTransactionMagnitude(this->m_transactionMagnitude, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Transactions Magnitude", this->m_transactionMagnitude);
    }
    // J
    inline void AddEmptyBook(T *item) {
        throw;
    }
    // N
    inline void AddBidPriceMax(T *item) {
        this->AddPrice(this->m_bidPriceMax, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Bid Max", this->m_bidPriceMax);
    }
    // O
    inline void AddOfferPriceMin(T *item) {
        this->AddPrice(this->m_offerPriceMin, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Offer Min", this->m_offerPriceMin);
    }
    // Q
    inline void AddAuctionPriceCalculated(T *item) {
        this->AddPrice(this->m_auctionPriceCalculated, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Auction Price Calc", this->m_auctionPriceCalculated);
    }
    // W
    inline void AddAuctionPriceClose(T *item) {
        this->AddPrice(this->m_auctionPriceClose, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Auction Price Close", this->m_auctionPriceClose);
    }
    // c
    inline void AddAuctionMagnitudeClose(T *item) {
        this->AddPrice(this->m_auctionMagnitudeClose, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Auction Magnitude Close", this->m_auctionMagnitudeClose);
    }
    // e
    inline void AddMSSFullCoveredDealFlag(T *item) {
        //printf("WARNING: AddMSSFullCoveredDealFlag\n");
    }
    // f
    inline void AddMSSTradeBidAuctionMagnitudeOpenClose(T *item) {
        this->AddPrice(this->m_openCloseAuctionTradeBidMagnitude, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Auction Open/Close Bid Magnitude", this->m_openCloseAuctionTradeBidMagnitude);
    }
    inline void AddOLSTradeBidAuctionOpenClose(T *item) {
        this->AddPrice(this->m_openCloseAuctionTradeBid, item);
    }
    // g
    inline void AddMSSTradeOfferAuctionMagnitudeOpenClose(T *item) {
        this->AddPrice(this->m_openCloseAuctionTradeOfferMagnitude, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Auction Open/Close Offer Magnitude", this->m_openCloseAuctionTradeOfferMagnitude);
    }
    inline void AddOLSTradeOfferAuctionOpenClose(T *item) {
        this->AddPrice(this->m_openCloseAuctionTradeOffer, item);
    }
    // i
    inline void AddSessionBid(T *item) {
        this->AddPrice(this->m_sessionBid, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Session Bid", this->m_sessionBid);
    }
    // j
    inline void AddSessionOffer(T *item) {
        this->AddPrice(this->m_sessionOffer, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Session Offer", this->m_sessionOffer);
    }
    // h
    inline void AddPreTradePeriodPrice(T *item) {
        this->AddPrice(this->m_preTradePeriodPrice, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add PreTrade Prace", this->m_preTradePeriodPrice);
    }
    // k
    inline void AddPostTradePeriodPrice(T *item) {
        this->AddPrice(this->m_postTradePeriodPrice, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add PostTrade Price", this->m_postTradePeriodPrice);
    }
    // l
    inline void AddTradePrice2(T *item) {
        this->AddPrice(this->m_tradePrice2, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Trade2 Price Calc", this->m_tradePrice2);
    }
    // m
    inline void AddTradePrice(T *item) {
        this->AddPrice(this->m_tradePrice, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Trade Price Calc", this->m_tradePrice);
    }
    // o
    inline void AddPriceOpenOfficial(T *item) {
        this->AddPrice(this->m_priceOpenOfficial, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Official Open Price", this->m_priceOpenOfficial);
    }
    // p
    inline void AddPriceCurrentOfficial(T *item) {
        this->AddPrice(this->m_priceCurrentOfficial, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Officeal Current Calc", this->m_priceCurrentOfficial);
    }
    // q
    inline void AddLegitimQuote(T *item) {
        this->AddPrice(this->m_legitimQuote, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Legitim Quote", this->m_legitimQuote);
    }
    // r
    inline void AddPriceCloseOfficial(T *item) {
        this->AddPrice(this->m_priceCloseOfficial, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Official Close Price", this->m_priceCloseOfficial);
    }
    // v
    inline void AddBidTotal(T *item) {
        this->AddTotalBid(this->m_bidTotal, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Total Bid", this->m_bidTotal);
    }
    // w
    inline void AddOfferTotal(T *item) {
        this->AddTotalOffer(this->m_offerTotal, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Total Offer", this->m_offerTotal);
    }
    // s
    inline void AddAuctionPriceBigPackets(T *item) {
        this->AddPrice(this->m_auctionPriceBigPackets, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Big Packets Auction Price", this->m_auctionMagnitudeBigPackets);
    }
    // x
    inline void AddAuctionMagnitudeBigPackets(T *item) {
        this->AddPrice(this->m_auctionMagnitudeBigPackets, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Big Packets Auction Magnitude", this->m_auctionMagnitudeBigPackets);
    }
    // y
    inline void AddCumulativeCouponDebit(T *item) {
        this->AddPrice(this->m_cumulativeCouponDebit, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Cumulative Coupon Debit", this->m_cumulativeCouponDebit);
    }
    // u
    inline void AddDuration(T *item) {
        this->AddPrice(this->m_duration, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Add Duration", this->m_duration);
    }
    // z
    inline void AddAllDeals(T *item) { throw; }

    // 0
    inline void ChangeBuyQuote(T *item) {
        this->ChangePriceSize(this->m_buyQuotes, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change BuyQuote ", this->m_buyQuotes);
    }
    // 1
    inline void ChangeSellQuote(T *item) {
        this->ChangePriceSize(this->m_sellQuotes, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change SellQuote ", this->m_sellQuotes);
    }
    // 2
    inline void ChangeLastDealInfo(T *item) {
        this->ChangeLastDealInfo(this->m_lstDealInfo, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change SellQuote ", this->m_lstDealInfo);
    }
    // 3
    inline void ChangeIndicesList(T *item) {
        this->ChangeIndexList(this->m_indicesList, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Indices List ", this->m_indicesList);
    }
    // 4
    inline void ChangePriceOpenFirst(T *item) {
        this->ChangePrice(this->m_priceOpenFirst, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Open Price ", this->m_priceOpenFirst);
    }
    // 5
    inline void ChangePriceCloseLast(T *item) {
        this->ChangePrice(this->m_priceCloseLast, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Close Price ", this->m_priceCloseLast);
    }
    // 7
    inline void ChangePriceMax(T *item) {
        this->ChangePrice(this->m_priceMax, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Price Max", this->m_priceMax);
    }
    // 8
    inline void ChangePriceMin(T *item) {
        this->ChangePrice(this->m_priceMin, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Price Min", this->m_priceMin);
    }
    // 9
    inline void ChangePriceAve(T *item) {
        this->ChangePrice(this->m_priceAve, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Price Ave", this->m_priceAve);
    }
    // A
    inline void ChangeDisbalance(T *item) {
        this->ChangePrice(this->m_disbalance, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Disbalance", this->m_disbalance);
    }
    // B
    inline void ChangeTransactionsMagnitude(T *item) {
        this->ChangeTransactionMagnitude(this->m_transactionMagnitude, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Transactions Magnitude", this->m_transactionMagnitude);
    }
    // J
    inline void ChangeEmptyBook(T *item) {
        throw;
    }
    // N
    inline void ChangeBidPriceMax(T *item) {
        this->ChangePrice(this->m_bidPriceMax, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Bid Max", this->m_bidPriceMax);
    }
    // O
    inline void ChangeOfferPriceMin(T *item) {
        this->ChangePrice(this->m_offerPriceMin, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Offer Min", this->m_offerPriceMin);
    }
    // Q
    inline void ChangeAuctionPriceCalculated(T *item) {
        this->ChangePrice(this->m_auctionPriceCalculated, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Auction Price Calc", this->m_auctionPriceCalculated);
    }
    // W
    inline void ChangeAuctionPriceClose(T *item) {
        this->ChangePrice(this->m_auctionPriceClose, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Auction Price Close", this->m_auctionPriceClose);
    }
    // c
    inline void ChangeAuctionMagnitudeClose(T *item) {
        this->ChangePrice(this->m_auctionMagnitudeClose, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Auction Magnitude Close", this->m_auctionMagnitudeClose);
    }
    // e
    inline void ChangeMSSFullCoveredDealFlag(T *item) {
        //printf("WARNING: ChangeMSSFullCoveredDealFlag\n");
    }
    // f
    inline void ChangeMSSTradeBidAuctionMagnitudeOpenClose(T *item) {
        this->ChangePrice(this->m_openCloseAuctionTradeBidMagnitude, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Auction Open/Close Bid Magnitude", this->m_openCloseAuctionTradeBidMagnitude);
    }
    inline void ChangeOLSTradeBidAuctionOpenClose(T *item) {
        this->ChangePrice(this->m_openCloseAuctionTradeBid, item);
    }
    // g
    inline void ChangeMSSTradeOfferAuctionMagnitudeOpenClose(T *item) {
        this->ChangePrice(this->m_openCloseAuctionTradeOfferMagnitude, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Auction Open/Close Offer Magnitude", this->m_openCloseAuctionTradeOfferMagnitude);
    }
    inline void ChangeOLSTradeOfferAuctionOpenClose(T *item) {
        this->ChangePrice(this->m_openCloseAuctionTradeOffer, item);
    }
    // i
    inline void ChangeSessionBid(T *item) {
        this->ChangePrice(this->m_sessionBid, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Session Bid", this->m_sessionBid);
    }
    // j
    inline void ChangeSessionOffer(T *item) {
        this->ChangePrice(this->m_sessionOffer, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Session Offer", this->m_sessionOffer);
    }
    // h
    inline void ChangePreTradePeriodPrice(T *item) {
        this->ChangePrice(this->m_preTradePeriodPrice, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change PreTrade Prace", this->m_preTradePeriodPrice);
    }
    // k
    inline void ChangePostTradePeriodPrice(T *item) {
        this->ChangePrice(this->m_postTradePeriodPrice, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change PostTrade Price", this->m_postTradePeriodPrice);
    }
    // l
    inline void ChangeTradePrice2(T *item) {
        this->ChangePrice(this->m_tradePrice2, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Trade2 Price Calc", this->m_tradePrice2);
    }
    // m
    inline void ChangeTradePrice(T *item) {
        this->ChangePrice(this->m_tradePrice, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Trade Price Calc", this->m_tradePrice);
    }
    // o
    inline void ChangePriceOpenOfficial(T *item) {
        this->ChangePrice(this->m_priceOpenOfficial, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Official Open Price", this->m_priceOpenOfficial);
    }
    // p
    inline void ChangePriceCurrentOfficial(T *item) {
        this->ChangePrice(this->m_priceCurrentOfficial, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Officeal Current Calc", this->m_priceCurrentOfficial);
    }
    // q
    inline void ChangeLegitimQuote(T *item) {
        this->ChangePrice(this->m_legitimQuote, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Legitim Quote", this->m_legitimQuote);
    }
    // r
    inline void ChangePriceCloseOfficial(T *item) {
        this->ChangePrice(this->m_priceCloseOfficial, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Official Close Price", this->m_priceCloseOfficial);
    }
    // v
    inline void ChangeBidTotal(T *item) {
        this->ChangeTotalBid(this->m_bidTotal, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Total Bid", this->m_bidTotal);
    }
    // w
    inline void ChangeOfferTotal(T *item) {
        this->ChangeTotalOffer(this->m_offerTotal, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Total Offer", this->m_offerTotal);
    }
    // s
    inline void ChangeAuctionPriceBigPackets(T *item) {
        this->ChangePrice(this->m_auctionPriceBigPackets, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Big Packets Auction Price", this->m_auctionMagnitudeBigPackets);
    }
    // x
    inline void ChangeAuctionMagnitudeBigPackets(T *item) {
        this->ChangePrice(this->m_auctionMagnitudeBigPackets, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Big Packets Auction Magnitude", this->m_auctionMagnitudeBigPackets);
    }
    // y
    inline void ChangeCumulativeCouponDebit(T *item) {
        this->ChangePrice(this->m_cumulativeCouponDebit, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Cumulative Coupon Debit", this->m_cumulativeCouponDebit);
    }
    // u
    inline void ChangeDuration(T *item) {
        this->ChangePrice(this->m_duration, item);
        DebugInfoManager::Default->Log(this->SymbolInfo()->Symbol(), this->m_tradingSession, "Change Duration", this->m_duration);
    }

    // z
    inline void ChangeAllDeals(T *item) { printf("not implemented\n"); }

    inline void RemoveBuyQuote(T*item) { printf("not implemented\n"); }
    inline void RemoveSellQuote(T*item) { printf("not implemented\n"); }
    inline void RemoveLastDealInfo(T*item) { printf("not implemented\n"); }
    inline void RemoveIndicesList(T*item) { printf("not implemented\n"); }
    inline void RemovePriceOpenFirst(T*item) { printf("not implemented\n"); }
    inline void RemovePriceCloseLast(T*item) { printf("not implemented\n"); }
    inline void RemovePriceMax(T*item) { printf("not implemented\n"); }
    inline void RemovePriceMin(T*item) { printf("not implemented\n"); }
    inline void RemovePriceAve(T*item) { printf("not implemented\n"); }
    inline void RemoveDisbalance(T*item) { printf("not implemented\n"); }
    inline void RemoveTransactionsMagnitude(T*item) { printf("not implemented\n"); }
    inline void RemoveEmptyBook(T*item) { printf("not implemented\n"); }
    inline void RemoveOfferPriceMax(T*item) { printf("not implemented\n"); }
    inline void RemoveBidPriceMin(T*item) { printf("not implemented\n"); }
    inline void RemoveAuctionPriceCalculated(T*item) { printf("not implemented\n"); }
    inline void RemoveAuctionPriceClose(T*item) { printf("not implemented\n"); }
    inline void RemoveAuctionMagnitudeClose(T*item) { printf("not implemented\n"); }
    inline void RemoveMSSFullCoveredDealFlag(T*item) { printf("not implemented\n"); }
    inline void RemoveMSSTradeOfferAuctionMagnitudeOpenClose(T*item) { printf("not implemented\n"); }
    inline void RemoveOLSTradeOfferAuctionOpenClose(T*item) { printf("not implemented\n"); }
    inline void RemoveMSSTradeBidAuctionMagnitudeOpenClose(T*item) { printf("not implemented\n"); }
    inline void RemoveOLSTradeBidAuctionOpenClose(T*item) { printf("not implemented\n"); }
    inline void RemovePreTradePeriodPrice(T*item) { printf("not implemented\n"); }
    inline void RemoveSessionOffer(T*item) { printf("not implemented\n"); }
    inline void RemoveSessionBid(T*item) { printf("not implemented\n"); }
    inline void RemovePostTradePeriodPrice(T*item) { printf("not implemented\n"); }
    inline void RemoveTradePrice2(T*item) { printf("not implemented\n"); }
    inline void RemoveTradePrice(T*item) { printf("not implemented\n"); }
    inline void RemovePriceOpenOfficial(T*item) { printf("not implemented\n"); }
    inline void RemovePriceCurrentOfficial(T*item) { printf("not implemented\n"); }
    inline void RemoveLegitimQuote(T*item) { printf("not implemented\n"); }
    inline void RemovePriceCloseOfficial(T*item) { printf("not implemented\n"); }
    inline void RemoveAuctionPriceBigPackets(T*item) { printf("not implemented\n"); }
    inline void RemoveDuration(T*item) { printf("not implemented\n"); }
    inline void RemoveOfferTotal(T*item) { printf("not implemented\n"); }
    inline void RemoveBidTotal(T*item) { printf("not implemented\n"); }
    inline void RemoveAuctionMagnitudeBigPackets(T*item) { printf("not implemented\n"); }
    inline void RemoveCumulativeCouponDebit(T*item) { printf("not implemented\n"); }
    inline void RemoveAllDeals(T*item) { printf("not implemented\n"); }

    inline void AddProperty(MDEntryType entryType, T *item) {
        if(entryType <= MDEntryType::mdetOLSTradeOfferAuctionOpenClose) {
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
                    if(entryType <= MDEntryType::mdetOfferPriceMin) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                                this->AddTransactionsMagnitude(item);
                            }
                            else { // mdetEmptyBook
                                this->AddEmptyBook(item);
                            }
                        }
                        else {
                            // mdetOfferPriceMax
                            this->AddOfferPriceMin(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMax) {
                            this->AddBidPriceMax(item);
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
                        if(entryType == MDEntryType::mdetMSSTradeOfferAuctionMagnitudeOpenClose) {
                            this->AddMSSTradeOfferAuctionMagnitudeOpenClose(item);
                        }
                        else { // mdetOLSTradeOfferAuctionOpenClose
                            this->AddOLSTradeOfferAuctionOpenClose(item);
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
                        if(entryType == MDEntryType::mdetSessionOffer) {
                            this->AddSessionOffer(item);
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
                if(entryType <= MDEntryType::mdetOfferTotal) {
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
                        else { // mdetOfferTotal
                            this->AddOfferTotal(item);
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
        if(entryType <= MDEntryType::mdetOLSTradeOfferAuctionOpenClose) {
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
                    if(entryType <= MDEntryType::mdetOfferPriceMin) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                                this->ChangeTransactionsMagnitude(item);
                            }
                            else { // mdetEmptyBook
                                this->ChangeEmptyBook(item);
                            }
                        }
                        else {
                            // mdetOfferPriceMax
                            this->ChangeOfferPriceMin(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMax) {
                            this->ChangeBidPriceMax(item);
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
                        if(entryType == MDEntryType::mdetMSSTradeOfferAuctionMagnitudeOpenClose) {
                            this->ChangeMSSTradeOfferAuctionMagnitudeOpenClose(item);
                        }
                        else { // mdetOLSTradeOfferAuctionOpenClose
                            this->ChangeOLSTradeOfferAuctionOpenClose(item);
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
                        if(entryType == MDEntryType::mdetSessionOffer) {
                            this->ChangeSessionOffer(item);
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
                if(entryType <= MDEntryType::mdetOfferTotal) {
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
                        else { // mdetOfferTotal
                            this->ChangeOfferTotal(item);
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
        if(entryType <= MDEntryType::mdetOLSTradeOfferAuctionOpenClose) {
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
                    if(entryType <= MDEntryType::mdetOfferPriceMin) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                                this->RemoveTransactionsMagnitude(item);
                            }
                            else { // mdetEmptyBook
                                this->RemoveEmptyBook(item);
                            }
                        }
                        else {
                            // mdetOfferPriceMax
                            this->RemoveOfferPriceMax(item);
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMax) {
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
                        if(entryType == MDEntryType::mdetMSSTradeOfferAuctionMagnitudeOpenClose) {
                            this->RemoveMSSTradeOfferAuctionMagnitudeOpenClose(item);
                        }
                        else { // mdetOLSTradeOfferAuctionOpenClose
                            this->RemoveOLSTradeOfferAuctionOpenClose(item);
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
                        if(entryType == MDEntryType::mdetSessionOffer) {
                            this->RemoveSessionOffer(item);
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
                if(entryType <= MDEntryType::mdetOfferTotal) {
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
                        else { // mdetOfferTotal
                            this->RemoveOfferTotal(item);
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
        this->m_entryInfo->ShouldProcess(false);
        if(!this->m_entryInfo->HasEntries())
            return true;
        T **entry = this->m_entryInfo->Entries();
        int incRptSeq = this->m_entryInfo->RptSeq();
        int maxIndex = this->m_entryInfo->MaxIndex();
        if(this->m_rptSeq + 1 < incRptSeq)
            return false;
        int startIndex = this->m_rptSeq + 1 - incRptSeq;
        for(int i = 0; i < startIndex && i < this->m_entryInfo->Capacity(); i++, entry++) {
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

    inline bool EnterSnapshotMode() {
        this->ResetSnasphotProcessed();
        this->m_shouldProcessSnapshot = true;
        return true;
    }

    inline void ExitSnapshotMode() {
        this->m_shouldProcessSnapshot = false;
    }

    inline bool ShouldProcessSnapshot() { return this->m_shouldProcessSnapshot; }

    inline void ProcessActualSnapshotState() {
        if(!this->m_shouldProcessSnapshot)
            return;
        this->m_shouldProcessSnapshot = false;
        SymbolInfo()->DecSessionsToRecvSnapshotCount();
    }
};

#endif //HFT_ROBOT_STATISTICINFO_H
