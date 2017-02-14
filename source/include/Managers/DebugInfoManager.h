//
// Created by root on 09.02.17.
//

#ifndef HFT_ROBOT_DEBUGINFOMANAGER_H
#define HFT_ROBOT_DEBUGINFOMANAGER_H

#include <Fast/FastProtocolManager.h>
#include <MarketData/QuoteInfo.h>
#include "../Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "../Lib/StringIdComparer.h"

template <template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO> class MarketDataTable;
template <typename T> class MarketSymbolInfo;
template <typename T> class StatisticItem;
class StatisticItemDecimal;
class StatisticItemDecimal2;
class StatisticItemLastDealInfo;
class StatisticItemIndexList;
class StatisticItemTotalBid;
class StatisticItemTotalOffer;
class StatisticItemTransactionsMagnitude;
class FeedChannel;
class FastProtocolManager;
class FeedConnection;

class DebugInfoManager {

    MDEntryType MDEntryTypes[39] {
            mdetBuyQuote,
            mdetSellQuote,
            mdetLastDealInfo,
            mdetIndicesList,
            mdetPriceOpenFirst,
            mdetPriceCloseLast,
            mdetPriceMax,
            mdetPriceMin,
            mdetPriceAve,
            mdetDisbalance, // A
            mdetTransactionsMagnitude, //B
            mdetEmptyBook, // J
            mdetOfferPriceMin,
            mdetBidPriceMax,
            mdetAuctionPriceCalculated,
            mdetAuctionPriceClose,
            mdetAuctionMagnitudeClose,
            mdetMSSTradingDenyNotEnoughMoney,
            mdetMSSTradeOfferAuctionMagnitudeOpenClose,
            mdetOLSTradeOfferAuctionOpenClose,
            mdetMSSTradeBidAuctionMagnitudeOpenClose,
            mdetOLSTradeBidAuctionOpenClose,
            mdetSessionOffer,
            mdetSessionBid,
            mdetPreTradePeriodPrice,
            mdetPostTradePeriodPrice,
            mdetTradePrice2,
            mdetTradePrice,
            mdetPriceOpenOfficial,
            mdetPriceCurrentOfficial,
            mdetLegitimQuote,
            mdetPriceCloseOfficial,
            mdetOfferTotal,
            mdetBidTotal,
            mdetAuctionPriceBigPackets,
            mdetAuctionMagnitudeBigPackets,
            mdetCumulativeCouponDebit,
            mdetDuration,
            mdetAllDeals
    };

    int MDEntryTypeRecv[39] {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0 };

    char        m_buffer[392];
    char        m_buffer2[392];
    char        m_tabs[32];
    int         m_tabsCount;
public:
    static DebugInfoManager *Default;

    DebugInfoManager() { }
    ~DebugInfoManager() { }
    template<typename T> void PrintStatisticsOnce(FastProtocolManager *manager, T *info) {
        bool shouldPrint = false;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            for (int e = 0; e < 39; e++) {
                if (this->MDEntryTypes[e] != info->GroupMDEntries[i]->MDEntryType[0])
                    continue;

                if (this->MDEntryTypeRecv[e] > 0)
                    continue;

                this->MDEntryTypeRecv[e]++;
                shouldPrint = true;
                break;
            }
        }
        if(shouldPrint)
            PrintFastProtocolManager(manager);
    }
    void PrintFastProtocolManager(FastProtocolManager *manager);

    const char* BinaryToString(unsigned char *buffer, int size) {
        for(int i = 0; i < size; i++) {
            sprintf(this->m_buffer + i * 3, "%2.2x ", buffer[i]);
        }
        return this->m_buffer;
    }
    const char* GetString(SizedArray *array, int index) {
        char *buf = this->m_buffer + index * 100;
        memcpy(buf, array->m_text, array->m_length);
        buf[array->m_length] = '\0';
        return buf;
    }
    const char* GetString(char *text, int length, int index) {
        char *buf = this->m_buffer + index * 100;
        memcpy(buf, text, length);
        buf[length] = '\0';
        return buf;
    }
    int AsciToValue(char ascii) {
        char asci_table[16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

        for(int i = 0; i < 16; i++) {
            if(ascii == asci_table[i])
                return i;
        }
        return 0;
    }
    int AsciiToByte(const char *ascii) {
        return this->AsciToValue(ascii[0]) * 16 + this->AsciToValue(ascii[1]);
    }
    unsigned char* StringToBinary(const char *str, int *sizeOut) {
        int len = strlen(str);
        int bytesCount = 1;
        for(int i = 1; i < len; i++) {
            if(str[i] == 0x20 && str[i-1] != 0x20)
                bytesCount++;
        }

        unsigned char *res = new unsigned char[bytesCount];
        int byteIndex = 0;
        for(int i = 0; i < len; ) {
            if(str[i] != 0x20) {
                res[byteIndex] = AsciiToByte(str + i);
                byteIndex++;
                i += 3;
            }
        }
        *sizeOut = bytesCount;
        return res;
    }

    void ResetTabs() { this->m_tabs[0] = '\0'; }
    void AddTabs() { this->m_tabs[this->m_tabsCount] = '\t'; this->m_tabsCount++; }
    void RemoveTabs() {
        if(this->m_tabsCount == 0)
            return;
        this->m_tabs[this->m_tabsCount - 1] = '\0'; this->m_tabsCount--;
    }

    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemDecimal> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemDecimal2> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemLastDealInfo> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemIndexList> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTotalBid> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTotalOffer> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTransactionsMagnitude> *list);
    void Log(SizedArray *symbol, SizedArray *trading, const char *string, char *entryId, int entryIdLength, Decimal *price, Decimal *size);
    void PrintStatistics(FeedConnection *conn);
    void PrintStatistics(FeedChannel *channel);
    void PrintStatisticsIncremental(FeedConnection *conn);
    void PrintStatisticsSnapshot(FeedConnection *conn);
    void PrintStatisticsInstrumentDefinition(FeedConnection *conn);
    void PrintStatisticsInstrumentStatus(FeedConnection *conn);
    void PrintStatisticsHistoricalReplay(FeedConnection *conn);
    void PrintStatistics(FastProtocolManager *manager);
    template<typename T> void PrintQuotes(const char *quotesName, PointerList<T> *quotes) {
        printf("Start %s\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            T *info = quotes->Item(quoteIndex);
            printf("Quote %s Price %g Size %g\n", this->GetString(info->MDEntryID, info->MDEntryIDLength, 0), info->MDEntryPx.Value, info->MDEntrySize.Value);
        }
        this->RemoveTabs();
        printf("End %s\n", quotesName);
    }
    void PrintStatistics(const char *quotesName, PointerList<QuoteInfo> *quotes) {
        printf("Start %s\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            QuoteInfo *info = quotes->Item(quoteIndex);
            printf("Price %g Size %d\n", info->Price()->Value, info->Size());
        }
        this->RemoveTabs();
        printf("End %s\n", quotesName);
    }
    template<template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO>void PrintOrderTable(const char *name, MarketDataTable<TABLEITEM, INFO, ITEMINFO> *table) {
        printf("Start %s Table\n", name);
        this->AddTabs();
        printf("Symbols Count = %d\n", table->SymbolsCount());
        this->AddTabs();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbol = table->Symbol(i);
            printf("Symbol %s\n", this->GetString(symbol->Symbol(), 0));
            printf("Sessions Count = %d\n", symbol->SessionCount());
            this->AddTabs();
            for(int j = 0; j < symbol->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *session = symbol->Session(j);
                printf("Session %s Buy Quotes %d Sell Quotes %d Agg. Buy Quotes %d Agg. Sell Quotes %d\n",
                       this->GetString(session->TradingSession(), 0),
                       session->BuyQuotes()->Count(),
                       session->SellQuotes()->Count(),
                       session->AggregatedBuyQuotes()->Count(),
                       session->AggregatedSellQuotes()->Count());
                printf("Queued Messages Count = %d\n", session->EntriesQueue()->MaxIndex() + 1);
                this->PrintQuotes<ITEMINFO>("Buy Quotes", session->BuyQuotes());
                this->PrintQuotes<ITEMINFO>("Sell Quotes", session->SellQuotes());
                this->PrintStatistics("Aggregated Buy Quotes", session->AggregatedBuyQuotes());
                this->PrintStatistics("Aggregated Sell Quotes", session->AggregatedSellQuotes());
            }
            this->RemoveTabs();
        }
        this->RemoveTabs();
        this->RemoveTabs();
        printf("End %s Table\n", name);
    };

    template<template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO>void PrintTradeTable(const char *name, MarketDataTable<TABLEITEM, INFO, ITEMINFO> *table) {
        printf("Start %s Table\n", name);
        this->AddTabs();
        printf("Symbols Count = %d\n", table->SymbolsCount());
        this->AddTabs();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbol = table->Symbol(i);
            printf("Symbol %s\n", this->GetString(symbol->Symbol(), 0));
            printf("Sessions Count = %d\n", symbol->SessionCount());
            this->AddTabs();
            for(int j = 0; j < symbol->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *session = symbol->Session(j);
                printf("Session %s Trades %d \n",
                       this->GetString(session->TradingSession(), 0),
                       session->Trades()->Count());
                printf("Queued Messages Count = %d\n", session->EntriesQueue()->MaxIndex() + 1);
                this->PrintQuotes<ITEMINFO>("Trades", session->Trades());
            }
            this->RemoveTabs();
        }
        this->RemoveTabs();
        this->RemoveTabs();
        printf("End %s Table\n", name);
    };

    void PrintDecimal2List(const char *name, PointerListLite<StatisticItemDecimal2> *list);
    void PrintDecimalList(const char *name, PointerListLite<StatisticItemDecimal> *list);
    void PrintLastDealInfoList(const char *name, PointerListLite<StatisticItemLastDealInfo> *list);
    void PrintIndicesList(const char *name, PointerListLite<StatisticItemIndexList> *list);
    void PrintTransactionMagnitude(const char *name, PointerListLite<StatisticItemTransactionsMagnitude> *list);
    void PrintBooleanList(const char *name, PointerListLite<StatisticItem<bool>> *list);
    void PrintTotalOfferList(const char *name, PointerListLite<StatisticItemTotalOffer> *list);
    void PrintTotalBidList(const char *name, PointerListLite<StatisticItemTotalBid> *list);

    template<template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO>void PrintStatisticsTable(const char *name, MarketDataTable<TABLEITEM, INFO, ITEMINFO> *table) {
        printf("Start %s Table\n", name);
        this->AddTabs();
        printf("Symbols Count = %d\n", table->SymbolsCount());
        this->AddTabs();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbol = table->Symbol(i);
            printf("Symbol %s\n", this->GetString(symbol->Symbol(), 0));
            printf("Sessions Count = %d\n", symbol->SessionCount());
            this->AddTabs();
            for(int j = 0; j < symbol->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *session = symbol->Session(j);
                printf("Session %s\n",
                       this->GetString(session->TradingSession(), 0));
                printf("Queued Messages Count = %d\n", session->EntriesQueue()->MaxIndex() + 1);

                this->PrintDecimal2List("Buy Quotes", session->BuyQuotes());
                this->PrintDecimal2List("Sell Quotes", session->SellQuotes());
                this->PrintLastDealInfoList("Last Deal Info", session->LastDealInfo());
                this->PrintIndicesList("Indices List", session->IndicesList());
                this->PrintDecimalList("PriceOpenFirst", session->PriceOpenFirst());
                this->PrintDecimalList("PriceCloseLast" , session->PriceCloseLast());
                this->PrintDecimalList("PriceMax", session->PriceMax());
                this->PrintDecimalList("PriceMin", session->PriceMin());
                this->PrintDecimalList("PriceAve", session->PriceAve());
                this->PrintDecimalList("Disbalance", session->Disbalance());
                this->PrintTransactionMagnitude("TransactionMagnitude", session->TransactionMagnitude());
                this->PrintDecimalList("OfferPriceMax", session->OfferPriceMax());
                this->PrintDecimalList("BidPriceMin", session->BidPriceMin());
                this->PrintDecimalList("AuctionPriceCalculated", session->AuctionPriceCalculated());
                this->PrintDecimalList("AuctionPriceClose", session->AuctionPriceClose());
                this->PrintDecimalList("AuctionMagnitudeClose", session->AuctionMagnitudeClose());
                this->PrintBooleanList("FullCoveredDealFlag", session->FullCoveredDealFlag());
                this->PrintDecimalList("OpenCloseAuctionTradeOfferMagnitude", session->OpenCloseAuctionTradeOfferMagnitude());
                this->PrintDecimalList("OpenCloseAuctionTradeBidMagnitude", session->OpenCloseAuctionTradeBidMagnitude());
                this->PrintDecimalList("OpenCloseAuctionTradeOffer", session->OpenCloseAuctionTradeOffer());
                this->PrintDecimalList("OpenCloseAuctionTradBid", session->OpenCloseAuctionTradBid());
                this->PrintDecimalList("PreTradePeriodPrice", session->PreTradePeriodPrice());
                this->PrintDecimalList("SessionOffer", session->SessionOffer());
                this->PrintDecimalList("SessionBid", session->SessionBid());
                this->PrintDecimalList("PostTradePeriodPrice", session->PostTradePeriodPrice());
                this->PrintDecimalList("TradePrice", session->TradePrice());
                this->PrintDecimalList("TradePrice2", session->TradePrice2());
                this->PrintDecimalList("PriceOpenOfficial", session->PriceOpenOfficial());
                this->PrintDecimalList("PriceCurrentOfficial", session->PriceCurrentOfficial());
                this->PrintDecimalList("LegitimQuote", session->LegitimQuote());
                this->PrintDecimalList("PriceCloseOfficial", session->PriceCloseOfficial());
                this->PrintDecimalList("AuctionPriceBigPackets", session->AuctionPriceBigPackets());
                this->PrintDecimalList("Duration", session->Duration());
                this->PrintTotalOfferList("OfferTotal", session->OfferTotal());
                this->PrintTotalBidList("BidTotal", session->BidTotal());
                this->PrintDecimalList("AuctionMagnitudeBigPackets", session->AuctionMagnitudeBigPackets());
                this->PrintDecimalList("CumulativeCouponDebit", session->CumulativeCouponDebit());
            }
            this->RemoveTabs();
        }
        this->RemoveTabs();
        this->RemoveTabs();
        printf("End %s Table\n", name);
    }
};

#endif //HFT_ROBOT_DEBUGINFOMANAGER_H
