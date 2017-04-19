//
// Created by root on 09.02.17.
//

#ifndef HFT_ROBOT_DEBUGINFOMANAGER_H
#define HFT_ROBOT_DEBUGINFOMANAGER_H

#include "../Fast/FastProtocolManager.h"
#include "../MarketData/QuoteInfo.h"
#include "../Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "../Lib/HrPointerList.h"
#include "../Lib/StringIdComparer.h"
#include <stdio.h>
#ifndef __MACH__
#include <malloc.h>
#else
struct mallinfo {
    int arena;
    int ordblks;  /* number of free chunks */
    int smblks;   /* number of fastbin blocks */
    int hblks;    /* number of mmapped regions */
    int hblkhd;   /* space in mmapped regions */
    int usmblks;  /* maximum total allocated space */
    int fsmblks;  /* space available in freed fastbin blocks */
    int uordblks; /* total allocated space */
    int fordblks; /* total free space */
    int keepcost; /* top-most, releasable (via malloc_trim) space */
};
#endif
#include "../MarketData/MDEntryQueue.h"
#include <cstdlib>

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
class AstsFeedChannel;
class FastProtocolManager;
class FeedConnection;
class MDEntryQueue;

class DebugInfoManager {

    MDEntryType     *MDEntryTypes;
    int             *MDEntryTypeRecv;

    char            m_buffer[392];
    char            m_buffer2[392];
    char            m_tabs[32];
    int             m_tabsCount;
    FILE            *fp;
public:
    static DebugInfoManager *Default;

    DebugInfoManager();
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
    const char* GetString(const char *text, int length, int index) {
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
        bool isHex = str[0] == '0' && str[1] == 'x';
        for(int i = 0; i < len; ) {
            if(str[i] != 0x20) {
                if(isHex && (i == 0 || str[i - 1] == 0x20)) {
                    i += 2;
                    continue;
                }
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
    void Log(SizedArray *symbol, UINT32 trading, const char *string, UINT64 entryId, Decimal *price, INT64 size);

    void PrintStatistics(FeedConnection *conn);
    void PrintStatistics(AstsFeedChannel *channel);
    void PrintStatisticsIncremental(FeedConnection *conn);
    void PrintStatisticsSnapshot(FeedConnection *conn);
    void PrintStatisticsInstrumentDefinition(FeedConnection *conn);
    void PrintStatisticsInstrumentStatus(FeedConnection *conn);
    void PrintStatisticsHistoricalReplay(FeedConnection *conn);
    void PrintStatistics(FastProtocolManager *manager);
    template<typename T> void PrintQuotes(const char *quotesName, PointerListLite<T> *quotes) {
        printf("Start %s\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            T *info = quotes->Item(quoteIndex);
            printf("Quote %s Price %g Size %g\n", this->GetString(info->MDEntryID, info->MDEntryIDLength, 0), info->MDEntryPx.Value, info->MDEntrySize.Value);
        }
        this->RemoveTabs();
        printf("End %s\n", quotesName);
    }
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
    void PrintStatistics(const char *quotesName, PointerListLite<QuoteInfo> *quotes) {
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
                printf("Session %s Buy Quotes %d Sell Quotes %d \n",
                       this->GetString(session->TradingSession(), 0),
                       session->BuyQuotes()->Count(),
                       session->SellQuotes()->Count());
                printf("Queued Messages Count = %d\n", session->EntriesQueue()->MaxIndex() + 1);
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

    void PrintDecimal2List(const char *name, PointerListLite<StatisticItemDecimal2> *list);
    void PrintDecimalList(const char *name, PointerListLite<StatisticItemDecimal> *list);
    void PrintLastDealInfoList(const char *name, PointerListLite<StatisticItemLastDealInfo> *list);
    void PrintIndicesList(const char *name, PointerListLite<StatisticItemIndexList> *list);
    void PrintTransactionMagnitude(const char *name, PointerListLite<StatisticItemTransactionsMagnitude> *list);
    void PrintBooleanList(const char *name, PointerListLite<StatisticItem<bool>> *list);
    void PrintTotalOfferList(const char *name, PointerListLite<StatisticItemTotalOffer> *list);
    void PrintTotalBidList(const char *name, PointerListLite<StatisticItemTotalBid> *list);


    void PrintStatisticsXml(FeedConnection *conn);
    void PrintStatisticsXml(const char *fileName, AstsFeedChannel *channel);
    void PrintStatisticsIncrementalXml(FeedConnection *conn);
    void PrintStatisticsSnapshotXml(FeedConnection *conn);
    void PrintStatisticsInstrumentDefinitionXml(FeedConnection *conn);
    void PrintStatisticsInstrumentStatusXml(FeedConnection *conn);
    void PrintStatisticsHistoricalReplayXml(FeedConnection *conn);
    void PrintStatisticsXml(FastProtocolManager *manager);
    template<typename T> void PrintQuotesXml(const char *quotesName, PointerListLite<T> *quotes) {
        fprintf(fp, "<QuotesList Name=\"%s\"/>\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            T *info = quotes->Item(quoteIndex);
            fprintf(fp, "<Item Name=\"%s\" Price=\"%g\" Size=\"%g\"/>\n", this->GetString(info->MDEntryID, info->MDEntryIDLength, 0), info->MDEntryPx.Value, info->MDEntrySize.Value);
        }
        this->RemoveTabs();
        fprintf(fp, "</QuotesList>\n");
    }
    template<typename T> void PrintQuotesXml(const char *quotesName, HrPointerListLite<T> *quotes) {
        fprintf(fp, "<QuotesList Name=\"%s\"/>\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            T *info = quotes->Item(quoteIndex);
            fprintf(fp, "<Item Name=\"%s\" Price=\"%g\" Size=\"%g\"/>\n", this->GetString(info->MDEntryID, info->MDEntryIDLength, 0), info->MDEntryPx.Value, info->MDEntrySize.Value);
        }
        this->RemoveTabs();
        fprintf(fp, "</QuotesList>\n");
    }
    template<typename T> void PrintQuotesXml(const char *quotesName, PointerList<T> *quotes) {
        fprintf(fp, "<QuotesList Name=\"%s\"/>\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            T *info = quotes->Item(quoteIndex);
            fprintf(fp, "<Item Name=\"%s\" Price=\"%g\" Size=\"%g\"/>\n", this->GetString(info->MDEntryID, info->MDEntryIDLength, 0), info->MDEntryPx.Value, info->MDEntrySize.Value);
        }
        this->RemoveTabs();
        fprintf(fp, "</QuotesList>\n");
    }
    void PrintStatisticsXml(const char *quotesName, PointerListLite<QuoteInfo> *quotes) {
        fprintf(fp, "<QuotesList Name=\"%s\"/>\n", quotesName);
        this->AddTabs();
        for(int quoteIndex = 0; quoteIndex < quotes->Count(); quoteIndex++) {
            QuoteInfo *info = quotes->Item(quoteIndex);
            fprintf(fp, "<Item Price=\"%g\" Size=\"%d\"/>\n", info->Price()->Value, info->Size());
        }
        this->RemoveTabs();
        fprintf(fp, "</QuotesList>\n");
    }

    template<template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO>void PrintOrderTableXml(const char *name, MarketDataTable<TABLEITEM, INFO, ITEMINFO> *table) {
        fprintf(fp, "<Table Name=\"%s\" SymbolsCount=\"%d\">\n", name, table->SymbolsCount());
        this->AddTabs();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbol = table->Symbol(i);
            fprintf(fp, "<Symbol Name=\"%s\" SessionsCount=\"%d\">\n", this->GetString(symbol->Symbol(), 0), symbol->SessionCount());
            this->AddTabs();
            for(int j = 0; j < symbol->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *session = symbol->Session(j);
                fprintf(fp, "<Session Name=\"%s\" BuyQuotes=\"%d\" SellQuotes=\"%d\" QueuedMessagesCount=\"%d\">\n",
                       this->GetString(session->TradingSession(), 0),
                       session->BuyQuotes()->Count(),
                       session->SellQuotes()->Count(),
                       session->EntriesQueue()->MaxIndex() + 1);
                this->PrintQuotesXml<ITEMINFO>("BuyQuotes", session->BuyQuotes());
                this->PrintQuotesXml<ITEMINFO>("SellQuotes", session->SellQuotes());
                fprintf(fp, "</Session>\n");
            }
            this->RemoveTabs();
            fprintf(fp, "</Symbol>\n");
        }
        this->RemoveTabs();
        printf("</Table>\n");
    };
    template<template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO>void PrintTradeTableXml(const char *name, MarketDataTable<TABLEITEM, INFO, ITEMINFO> *table) {
        fprintf(fp, "<Table Name=\"%s\" SymbolsCount=\"%d\">\n", name, table->SymbolsCount());
        this->AddTabs();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbol = table->Symbol(i);
            fprintf(fp, "<Symbol Name=\"%s\" SessionsCount=\"%d\">\n", this->GetString(symbol->Symbol(), 0), symbol->SessionCount());
            this->AddTabs();
            for(int j = 0; j < symbol->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *session = symbol->Session(j);
                fprintf(fp, "<Session Name=\"%s\" TradesCount=\"%d\" QueuedMessagesCount=\"%d\">\n",
                       this->GetString(session->TradingSession(), 0),
                       session->Trades()->Count(),
                        session->EntriesQueue()->MaxIndex() + 1);
                this->PrintQuotesXml<ITEMINFO>("Trades", session->Trades());
                fprintf(fp, "</Session>\n");
            }
            this->RemoveTabs();
            fprintf(fp, "</Symbol>\n");
        }
        this->RemoveTabs();
        printf("</Table>\n");
    };
    template<template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO>void PrintStatisticsTableXml(const char *name, MarketDataTable<TABLEITEM, INFO, ITEMINFO> *table) {
        fprintf(fp, "<Table Name=\"%s\" SymbolsCount=\"%d\">\n", name, table->SymbolsCount());
        this->AddTabs();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<TABLEITEM<ITEMINFO>> *symbol = table->Symbol(i);
            fprintf(fp, "<Symbol Name=\"%s\" SessionsCount=\"%d\">\n", this->GetString(symbol->Symbol(), 0), symbol->SessionCount());
            this->AddTabs();
            for(int j = 0; j < symbol->SessionCount(); j++) {
                TABLEITEM<ITEMINFO> *session = symbol->Session(j);
                fprintf(fp, "<Session Name=\"%s\" QueuedMessagesCount=\"%d\">\n",
                       this->GetString(session->TradingSession(), 0), session->EntriesQueue()->MaxIndex() + 1);

                this->PrintDecimal2ListXml("BuyQuotes", session->BuyQuotes());
                this->PrintDecimal2ListXml("SellQuotes", session->SellQuotes());
                this->PrintLastDealInfoListXml("LastDealInfo", session->LastDealInfo());
                this->PrintIndicesListXml("IndicesList", session->IndicesList());
                this->PrintDecimalListXml("PriceOpenFirst", session->PriceOpenFirst());
                this->PrintDecimalListXml("PriceCloseLast" , session->PriceCloseLast());
                this->PrintDecimalListXml("PriceMax", session->PriceMax());
                this->PrintDecimalListXml("PriceMin", session->PriceMin());
                this->PrintDecimalListXml("PriceAve", session->PriceAve());
                this->PrintDecimalListXml("Disbalance", session->Disbalance());
                this->PrintTransactionMagnitudeXml("TransactionMagnitude", session->TransactionMagnitude());
                this->PrintDecimalListXml("OfferPriceMax", session->OfferPriceMax());
                this->PrintDecimalListXml("BidPriceMin", session->BidPriceMin());
                this->PrintDecimalListXml("AuctionPriceCalculated", session->AuctionPriceCalculated());
                this->PrintDecimalListXml("AuctionPriceClose", session->AuctionPriceClose());
                this->PrintDecimalListXml("AuctionMagnitudeClose", session->AuctionMagnitudeClose());
                this->PrintBooleanListXml("FullCoveredDealFlag", session->FullCoveredDealFlag());
                this->PrintDecimalListXml("OpenCloseAuctionTradeOfferMagnitude", session->OpenCloseAuctionTradeOfferMagnitude());
                this->PrintDecimalListXml("OpenCloseAuctionTradeBidMagnitude", session->OpenCloseAuctionTradeBidMagnitude());
                this->PrintDecimalListXml("OpenCloseAuctionTradeOffer", session->OpenCloseAuctionTradeOffer());
                this->PrintDecimalListXml("OpenCloseAuctionTradBid", session->OpenCloseAuctionTradBid());
                this->PrintDecimalListXml("PreTradePeriodPrice", session->PreTradePeriodPrice());
                this->PrintDecimalListXml("SessionOffer", session->SessionOffer());
                this->PrintDecimalListXml("SessionBid", session->SessionBid());
                this->PrintDecimalListXml("PostTradePeriodPrice", session->PostTradePeriodPrice());
                this->PrintDecimalListXml("TradePrice", session->TradePrice());
                this->PrintDecimalListXml("TradePrice2", session->TradePrice2());
                this->PrintDecimalListXml("PriceOpenOfficial", session->PriceOpenOfficial());
                this->PrintDecimalListXml("PriceCurrentOfficial", session->PriceCurrentOfficial());
                this->PrintDecimalListXml("LegitimQuote", session->LegitimQuote());
                this->PrintDecimalListXml("PriceCloseOfficial", session->PriceCloseOfficial());
                this->PrintDecimalListXml("AuctionPriceBigPackets", session->AuctionPriceBigPackets());
                this->PrintDecimalListXml("Duration", session->Duration());
                this->PrintTotalOfferListXml("OfferTotal", session->OfferTotal());
                this->PrintTotalBidListXml("BidTotal", session->BidTotal());
                this->PrintDecimalListXml("AuctionMagnitudeBigPackets", session->AuctionMagnitudeBigPackets());
                this->PrintDecimalListXml("CumulativeCouponDebit", session->CumulativeCouponDebit());
                fprintf(fp, "</Session>\n");
            }
            this->RemoveTabs();
            fprintf(fp, "</Symbol>\n");
        }
        this->RemoveTabs();
        printf("</Table>\n");
    }

    void PrintDecimal2ListXml(const char *name, PointerListLite<StatisticItemDecimal2> *list);
    void PrintDecimalListXml(const char *name, PointerListLite<StatisticItemDecimal> *list);
    void PrintLastDealInfoListXml(const char *name, PointerListLite<StatisticItemLastDealInfo> *list);
    void PrintIndicesListXml(const char *name, PointerListLite<StatisticItemIndexList> *list);
    void PrintTransactionMagnitudeXml(const char *name, PointerListLite<StatisticItemTransactionsMagnitude> *list);
    void PrintBooleanListXml(const char *name, PointerListLite<StatisticItem<bool>> *list);
    void PrintTotalOfferListXml(const char *name, PointerListLite<StatisticItemTotalOffer> *list);
    void PrintTotalBidListXml(const char *name, PointerListLite<StatisticItemTotalBid> *list);

    void PrintMemoryInfo(const char *string) {
        struct mallinfo mi;

        mi = mallinfo();
        printf("----------------%s -----------------\n", string);
//        printf("Total non mapped byres (arena)                           %d\n", mi.arena);
//        printf("# of free chunks (ordblks)                               %d\n", mi.ordblks);
//        printf("# of free fastbin blocks (smblks)                        %d\n", mi.smblks);
//        printf("# of mapped regions (hblks)                              %d\n", mi.hblks);
//        printf("Bytes mapped regions (hblkhd)                            %d\n", mi.hblkhd);
//        printf("Max. total allocated space mapped regions (usmblks)      %d\n", mi.usmblks);
//        printf("Free bytes held in fastbins (fsmblks)                    %d\n", mi.fsmblks);
        printf("Total allocated space in bytes (uordblks)                %d\n", mi.uordblks);
        printf("Total allocated space in mBbytes (uordblks)              %d\n", mi.uordblks / 1024 / 1024);
//        printf("Total free space in bytes (fordblks)                     %d\n", mi.fordblks);
//        printf("Total free space in mBytes (fordblks)                    %d\n", mi.fordblks / 1024 / 1024);
//        printf("Topmost releasable block (keepcost)                      %d\n", mi.keepcost);
        printf("-----------------------------------------------------------\n");
    }

    void PrintMemoryInfo() {
        PrintMemoryInfo("");
    }

    int CalcOrderFondTotalEntriesCount(FeedConnection *conn);
    int CalcOrderCurrTotalEntriesCount(FeedConnection *conn);
    int CalcTradeFondTotalEntriesCount(FeedConnection *conn);
    int CalcTradeCurrTotalEntriesCount(FeedConnection *conn);
    int CheckIsFriedMDEntryQueryCleared();
    MDEntryQueue* GetFirstMDEntryQueue();
    int GetFirstNonEmptyEntry();
    void DebugCheckForDublicateItems(AstsFeedChannel *channel);
    int CalcMDEntryQueCount(AstsFeedChannel *channel, MDEntryQueue *que);
};

#endif //HFT_ROBOT_DEBUGINFOMANAGER_H
