//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_STATISTICINFO_H
#define HFT_ROBOT_STATISTICINFO_H

#include "../Lib/StringIdComparer.h"
#include "../FastTypes.h"
#include "../Lib/PointerList.h"
#include "MarketDataEntryQueue.h"

template <typename T> class MarketSymbolInfo;

template <typename T> class StatisticsInfo {
    MDEntrQueue<T>      *m_entryInfo;

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
    }
    ~StatisticsInfo() {
        delete this->m_entryInfo;
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
        this->m_entryInfo->Clear();
        this->m_rptSeq = 0;
    }

    inline void AddBuyQuote(T *item) { throw; }
    inline void AddSellQuote(T *item) { throw; }
    inline void AddLastDealInfo(T *item) { throw; }
    inline void AddIndicesList(T *item) { throw; }
    inline void AddPriceOpenFirst(T *item) { throw; }
    inline void AddPriceCloseLast(T *item) { throw; }
    inline void AddPriceMax(T *item) { throw; }
    inline void AddPriceMin(T *item) { throw; }
    inline void AddPriceAve(T *item) { throw; }
    inline void AddDisbalance(T *item) { throw; }
    inline void AddTransactionsMagnitude(T *item) { throw; }
    inline void AddEmptyBook(T *item) { throw; }
    inline void AddAskPriceMax(T *item) { throw; }
    inline void AddBidPriceMin(T *item) { throw; }
    inline void AddAuctionPriceCalculated(T *item) { throw; }
    inline void AddAuctionPriceClose(T *item) { throw; }
    inline void AddAuctionMagnitudeClose(T *item) { throw; }
    inline void AddMSSTradingDenyNotEnoughMoney(T *item) { throw; }
    inline void AddMSSTradeAskAuctionMagnitudeOpenClose(T *item) { throw; }
    inline void AddOLSTradeAskAuctionOpenClose(T *item) { throw; }
    inline void AddMSSTradeBidAuctionMagnitudeOpenClose(T *item) { throw; }
    inline void AddOLSTradeBidAuctionOpenClose(T *item) { throw; }
    inline void AddPreTradePeriodPrice(T *item) { throw; }
    inline void AddSessionAsk(T *item) { throw; }
    inline void AddSessionBid(T *item) { throw; }
    inline void AddPostTradePeriodPrice(T *item) { throw; }
    inline void AddTradePrice2(T *item) { throw; }
    inline void AddTradePrice(T *item) { throw; }
    inline void AddPriceOpenOfficial(T *item) { throw; }
    inline void AddPriceCurrentOfficial(T *item) { throw; }
    inline void AddLegitimQuote(T *item) { throw; }
    inline void AddPriceCloseOfficial(T *item) { throw; }
    inline void AddAuctionPriceBigPackets(T *item) { throw; }
    inline void AddDuration(T *item) { throw; }
    inline void AddAskTotal(T *item) { throw; }
    inline void AddBidTotal(T *item) { throw; }
    inline void AddAuctionMagnitudeBigPackets(T *item) { throw; }
    inline void AddCumulativeCouponDebit(T *item) { throw; }
    inline void AddAllDeals(T *item) { throw; }

    inline void ChangeBuyQuote(T *item) { throw; }
    inline void ChangeSellQuote(T *item) { throw; }
    inline void ChangeLastDealInfo(T *item) { throw; }
    inline void ChangeIndicesList(T *item) { throw; }
    inline void ChangePriceOpenFirst(T *item) { throw; }
    inline void ChangePriceCloseLast(T *item) { throw; }
    inline void ChangePriceMax(T *item) { throw; }
    inline void ChangePriceMin(T *item) { throw; }
    inline void ChangePriceAve(T *item) { throw; }
    inline void ChangeDisbalance(T *item) { throw; }
    inline void ChangeTransactionsMagnitude(T *item) { throw; }
    inline void ChangeEmptyBook(T *item) { throw; }
    inline void ChangeAskPriceMax(T *item) { throw; }
    inline void ChangeBidPriceMin(T *item) { throw; }
    inline void ChangeAuctionPriceCalculated(T *item) { throw; }
    inline void ChangeAuctionPriceClose(T *item) { throw; }
    inline void ChangeAuctionMagnitudeClose(T *item) { throw; }
    inline void ChangeMSSTradingDenyNotEnoughMoney(T *item) { throw; }
    inline void ChangeMSSTradeAskAuctionMagnitudeOpenClose(T *item) { throw; }
    inline void ChangeOLSTradeAskAuctionOpenClose(T *item) { throw; }
    inline void ChangeMSSTradeBidAuctionMagnitudeOpenClose(T *item) { throw; }
    inline void ChangeOLSTradeBidAuctionOpenClose(T *item) { throw; }
    inline void ChangePreTradePeriodPrice(T *item) { throw; }
    inline void ChangeSessionAsk(T *item) { throw; }
    inline void ChangeSessionBid(T *item) { throw; }
    inline void ChangePostTradePeriodPrice(T *item) { throw; }
    inline void ChangeTradePrice2(T *item) { throw; }
    inline void ChangeTradePrice(T *item) { throw; }
    inline void ChangePriceOpenOfficial(T *item) { throw; }
    inline void ChangePriceCurrentOfficial(T *item) { throw; }
    inline void ChangeLegitimQuote(T *item) { throw; }
    inline void ChangePriceCloseOfficial(T *item) { throw; }
    inline void ChangeAuctionPriceBigPackets(T *item) { throw; }
    inline void ChangeDuration(T *item) { throw; }
    inline void ChangeAskTotal(T *item) { throw; }
    inline void ChangeBidTotal(T *item) { throw; }
    inline void ChangeAuctionMagnitudeBigPackets(T *item) { throw; }
    inline void ChangeCumulativeCouponDebit(T *item) { throw; }
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
    inline void RemoveMSSTradingDenyNotEnoughMoney(T *item) { throw; }
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
                            this->AddMSSTradingDenyNotEnoughMoney(item);
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
                            this->ChangeMSSTradingDenyNotEnoughMoney(item);
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
                            this->RemoveMSSTradingDenyNotEnoughMoney(item);
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
        AddProperty(item->MDentryType[0], item);
    }
    inline void Change(T *item) {
        ChangeProperty(item->MDentryType[0], item);
    }
    inline void Remove(T *item) {
        RemoveProperty(item->MDentryType[0], item);
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
