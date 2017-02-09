//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_STATISTICINFO_H
#define HFT_ROBOT_STATISTICINFO_H

#include "../Lib/StringIdComparer.h"
#include "Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "MarketDataEntryQueue.h"

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
    inline Decimal* NetChangePrevDayPtr() { return this->m_netChangePrevDayPtr; }
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
        this->m_totalOffers = new PointerList<StatisticItemTotalOffer>(10000, true);
        this->m_totalBids = new PointerList<StatisticItemTotalBid>(10000, true);
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
    PointerListLite<StatisticItemDecimal>                    *m_offerPriceMax;
    PointerListLite<StatisticItemDecimal>                    *m_bidPriceMin;
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
public:
    StatisticsInfo() {
        this->m_entryInfo = new MDEntrQueue<T>();
        this->m_tradingSession = new SizedArray();
        this->m_shouldProcessSnapshot = false;
        this->m_rptSeq = 0;
        this->m_time = 0;
        
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
        this->m_offerPriceMax = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
        this->m_bidPriceMin = new PointerListLite<StatisticItemDecimal>(DefaultStatisticItemAllocator::Default->Decimals());
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
        delete this->m_offerPriceMax;
        delete this->m_bidPriceMin;
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
         this->m_offerPriceMax->Clear();
         this->m_bidPriceMin->Clear();
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
    inline PointerListLite<StatisticItemLastDealInfo>* ListDealInfo() { return this->m_lstDealInfo; }
    inline PointerListLite<StatisticItemIndexList>* IndicesList() { return this->m_indicesList; }
    inline PointerListLite<StatisticItemDecimal>* PriceOpenFirst() { return this->m_priceOpenFirst; }
    inline PointerListLite<StatisticItemDecimal>* PriceCloseLast() { return this->m_priceCloseLast; }
    inline PointerListLite<StatisticItemDecimal>* PriceMax() { return this->m_priceMax; }
    inline PointerListLite<StatisticItemDecimal>* PriceMin() { return this->m_priceMin; }
    inline PointerListLite<StatisticItemDecimal>* PriceAve() { return this->m_priceAve; }
    inline PointerListLite<StatisticItemDecimal>* Disbalance() { return this->m_disbalance; }
    inline PointerListLite<StatisticItemTransactionsMagnitude>* TransactionMagnitude() { return this->m_transactionMagnitude; }
    inline PointerListLite<StatisticItemDecimal>* OfferPriceMax() { return this->m_offerPriceMax; }
    inline PointerListLite<StatisticItemDecimal>* BidPriceMin() { return this->m_bidPriceMin; }
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

    inline void AddBuyQuote(T *item) { this->AddPriceSize(this->m_buyQuotes, item); }
    inline void AddSellQuote(T *item) { this->AddPriceSize(this->m_sellQuotes, item); }
    inline void AddLastDealInfo(T *item) { this->AddLastDealInfo(this->m_lstDealInfo, item); }
    inline void AddIndicesList(T *item) { this->AddIndexList(this->m_indicesList, item); }
    inline void AddPriceOpenFirst(T *item) { this->AddPrice(this->m_priceOpenFirst, item); }
    inline void AddPriceCloseLast(T *item) { this->AddPrice(this->m_priceCloseLast, item); }
    inline void AddPriceMax(T *item) { this->AddPrice(this->m_priceMax, item); }
    inline void AddPriceMin(T *item) { this->AddPrice(this->m_priceMin, item); }
    inline void AddPriceAve(T *item) { this->AddPrice(this->m_priceAve, item); }
    inline void AddDisbalance(T *item) { this->AddPrice(this->m_disbalance, item); }
    inline void AddTransactionsMagnitude(T *item) { this->AddTransactionMagnitude(this->m_transactionMagnitude, item); }
    inline void AddEmptyBook(T *item) { throw; }
    inline void AddOfferPriceMax(T *item) { this->AddPrice(this->m_offerPriceMax, item); }
    inline void AddBidPriceMin(T *item) { this->AddPrice(this->m_bidPriceMin, item); }
    inline void AddAuctionPriceCalculated(T *item) { this->AddPrice(this->m_auctionPriceCalculated, item); }
    inline void AddAuctionPriceClose(T *item) { this->AddPrice(this->m_auctionPriceClose, item); }
    inline void AddAuctionMagnitudeClose(T *item) { this->AddPrice(this->m_auctionMagnitudeClose, item); }
    inline void AddMSSFullCoveredDealFlag(T *item) { throw; }
    inline void AddMSSTradeOfferAuctionMagnitudeOpenClose(T *item) { this->AddPrice(this->m_openCloseAuctionTradeOfferMagnitude, item); }
    inline void AddOLSTradeOfferAuctionOpenClose(T *item) { this->AddPrice(this->m_openCloseAuctionTradeOffer, item); }
    inline void AddMSSTradeBidAuctionMagnitudeOpenClose(T *item) { this->AddPrice(this->m_openCloseAuctionTradeBidMagnitude, item); }
    inline void AddOLSTradeBidAuctionOpenClose(T *item) { this->AddPrice(this->m_openCloseAuctionTradeBid, item); }
    inline void AddPreTradePeriodPrice(T *item) { this->AddPrice(this->m_preTradePeriodPrice, item); }
    inline void AddSessionOffer(T *item) { this->AddPrice(this->m_sessionOffer, item); }
    inline void AddSessionBid(T *item) { this->AddPrice(this->m_sessionBid, item); }
    inline void AddPostTradePeriodPrice(T *item) { this->AddPrice(this->m_postTradePeriodPrice, item); }
    inline void AddTradePrice2(T *item) { this->AddPrice(this->m_tradePrice2, item); }
    inline void AddTradePrice(T *item) { this->AddPrice(this->m_tradePrice, item); }
    inline void AddPriceOpenOfficial(T *item) { this->AddPrice(this->m_priceOpenOfficial, item); }
    inline void AddPriceCurrentOfficial(T *item) { this->AddPrice(this->m_priceCurrentOfficial, item); }
    inline void AddLegitimQuote(T *item) { this->AddPrice(this->m_legitimQuote, item); }
    inline void AddPriceCloseOfficial(T *item) { this->AddPrice(this->m_priceCloseOfficial, item); }
    inline void AddAuctionPriceBigPackets(T *item) { this->AddPrice(this->m_auctionPriceBigPackets, item); }
    inline void AddDuration(T *item) { this->AddPrice(this->m_duration, item); }
    inline void AddOfferTotal(T *item) { this->AddTotalOffer(this->m_offerTotal, item); }
    inline void AddBidTotal(T *item) { this->AddTotalBid(this->m_bidTotal, item); }
    inline void AddAuctionMagnitudeBigPackets(T *item) { this->AddPrice(this->m_auctionMagnitudeBigPackets, item); }
    inline void AddCumulativeCouponDebit(T *item) { this->AddPrice(this->m_cumulativeCouponDebit, item); }
    inline void AddAllDeals(T *item) { throw; }

    inline void ChangeBuyQuote(T *item) { this->ChangePriceSize(this->m_buyQuotes, item); }
    inline void ChangeSellQuote(T *item) { this->ChangePriceSize(this->m_sellQuotes, item); }
    inline void ChangeLastDealInfo(T *item) { this->ChangeLastDealInfo(this->m_lstDealInfo, item); }
    inline void ChangeIndicesList(T *item) { this->ChangeIndexList(this->m_indicesList, item); }
    inline void ChangePriceOpenFirst(T *item) { this->ChangePrice(this->m_priceOpenFirst, item); }
    inline void ChangePriceCloseLast(T *item) { this->ChangePrice(this->m_priceCloseLast, item); }
    inline void ChangePriceMax(T *item) { this->ChangePrice(this->m_priceMax, item); }
    inline void ChangePriceMin(T *item) { this->ChangePrice(this->m_priceMin, item); }
    inline void ChangePriceAve(T *item) { this->ChangePrice(this->m_priceAve, item); }
    inline void ChangeDisbalance(T *item) { this->ChangePrice(this->m_disbalance, item); }
    inline void ChangeTransactionsMagnitude(T *item) { this->ChangeTransactionMagnitude(this->m_transactionMagnitude, item); }
    inline void ChangeEmptyBook(T *item) { throw; }
    inline void ChangeOfferPriceMax(T *item) { this->ChangePrice(this->m_offerPriceMax, item); }
    inline void ChangeBidPriceMin(T *item) { this->ChangePrice(this->m_bidPriceMin, item); }
    inline void ChangeAuctionPriceCalculated(T *item) { this->ChangePrice(this->m_auctionPriceCalculated, item); }
    inline void ChangeAuctionPriceClose(T *item) { this->ChangePrice(this->m_auctionPriceClose, item); }
    inline void ChangeAuctionMagnitudeClose(T *item) { this->ChangePrice(this->m_auctionMagnitudeClose, item); }
    inline void ChangeMSSFullCoveredDealFlag(T *item) { throw; }
    inline void ChangeMSSTradeOfferAuctionMagnitudeOpenClose(T *item) { this->ChangePrice(this->m_openCloseAuctionTradeOfferMagnitude, item); }
    inline void ChangeOLSTradeOfferAuctionOpenClose(T *item) { this->ChangePrice(this->m_openCloseAuctionTradeOffer, item); }
    inline void ChangeMSSTradeBidAuctionMagnitudeOpenClose(T *item) { this->ChangePrice(this->m_openCloseAuctionTradeBidMagnitude, item); }
    inline void ChangeOLSTradeBidAuctionOpenClose(T *item) { this->ChangePrice(this->m_openCloseAuctionTradeBid, item); }
    inline void ChangePreTradePeriodPrice(T *item) { this->ChangePrice(this->m_preTradePeriodPrice, item); }
    inline void ChangeSessionOffer(T *item) { this->ChangePrice(this->m_sessionOffer, item); }
    inline void ChangeSessionBid(T *item) { this->ChangePrice(this->m_sessionBid, item); }
    inline void ChangePostTradePeriodPrice(T *item) { this->ChangePrice(this->m_postTradePeriodPrice, item); }
    inline void ChangeTradePrice2(T *item) { this->ChangePrice(this->m_tradePrice2, item); }
    inline void ChangeTradePrice(T *item) { this->ChangePrice(this->m_tradePrice, item); }
    inline void ChangePriceOpenOfficial(T *item) { this->ChangePrice(this->m_priceOpenOfficial, item); }
    inline void ChangePriceCurrentOfficial(T *item) { this->ChangePrice(this->m_priceCurrentOfficial, item); }
    inline void ChangeLegitimQuote(T *item) { this->ChangePrice(this->m_legitimQuote, item); }
    inline void ChangePriceCloseOfficial(T *item) { this->ChangePrice(this->m_priceCloseOfficial, item); }
    inline void ChangeAuctionPriceBigPackets(T *item) { this->ChangePrice(this->m_auctionPriceBigPackets, item); }
    inline void ChangeDuration(T *item) { this->ChangePrice(this->m_duration, item); }
    inline void ChangeOfferTotal(T *item) { this->ChangeTotalOffer(this->m_offerTotal, item); }
    inline void ChangeBidTotal(T *item) { this->ChangeTotalBid(this->m_bidTotal, item); }
    inline void ChangeAuctionMagnitudeBigPackets(T *item) { this->ChangePrice(this->m_auctionMagnitudeBigPackets, item); }
    inline void ChangeCumulativeCouponDebit(T *item) { this->ChangePrice(this->m_cumulativeCouponDebit, item); }
    inline void ChangeAllDeals(T *item) { throw; }

    inline void RemoveBuyQuote(T*item) { throw; }
    inline void RemoveSellQuote(T*item) { throw; }
    inline void RemoveLastDealInfo(T*item) { throw; }
    inline void RemoveIndicesList(T*item) { throw; }
    inline void RemovePriceOpenFirst(T*item) { throw; }
    inline void RemovePriceCloseLast(T*item) { throw; }
    inline void RemovePriceMax(T*item) { throw; }
    inline void RemovePriceMin(T*item) { throw; }
    inline void RemovePriceAve(T*item) { throw; }
    inline void RemoveDisbalance(T*item) { throw; }
    inline void RemoveTransactionsMagnitude(T*item) { throw; }
    inline void RemoveEmptyBook(T*item) { throw; }
    inline void RemoveOfferPriceMax(T*item) { throw; }
    inline void RemoveBidPriceMin(T*item) { throw; }
    inline void RemoveAuctionPriceCalculated(T*item) { throw; }
    inline void RemoveAuctionPriceClose(T*item) { throw; }
    inline void RemoveAuctionMagnitudeClose(T*item) { throw; }
    inline void RemoveMSSFullCoveredDealFlag(T*item) { throw; }
    inline void RemoveMSSTradeOfferAuctionMagnitudeOpenClose(T*item) { throw; }
    inline void RemoveOLSTradeOfferAuctionOpenClose(T*item) { throw; }
    inline void RemoveMSSTradeBidAuctionMagnitudeOpenClose(T*item) { throw; }
    inline void RemoveOLSTradeBidAuctionOpenClose(T*item) { throw; }
    inline void RemovePreTradePeriodPrice(T*item) { throw; }
    inline void RemoveSessionOffer(T*item) { throw; }
    inline void RemoveSessionBid(T*item) { throw; }
    inline void RemovePostTradePeriodPrice(T*item) { throw; }
    inline void RemoveTradePrice2(T*item) { throw; }
    inline void RemoveTradePrice(T*item) { throw; }
    inline void RemovePriceOpenOfficial(T*item) { throw; }
    inline void RemovePriceCurrentOfficial(T*item) { throw; }
    inline void RemoveLegitimQuote(T*item) { throw; }
    inline void RemovePriceCloseOfficial(T*item) { throw; }
    inline void RemoveAuctionPriceBigPackets(T*item) { throw; }
    inline void RemoveDuration(T*item) { throw; }
    inline void RemoveOfferTotal(T*item) { throw; }
    inline void RemoveBidTotal(T*item) { throw; }
    inline void RemoveAuctionMagnitudeBigPackets(T*item) { throw; }
    inline void RemoveCumulativeCouponDebit(T*item) { throw; }
    inline void RemoveAllDeals(T*item) { throw; }

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
                    if(entryType <= MDEntryType::mdetOfferPriceMax) {
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
                            this->AddOfferPriceMax(item);
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
                    if(entryType <= MDEntryType::mdetOfferPriceMax) {
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
                            this->ChangeOfferPriceMax(item);
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
                    if(entryType <= MDEntryType::mdetOfferPriceMax) {
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
