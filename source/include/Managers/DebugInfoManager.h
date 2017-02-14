//
// Created by root on 09.02.17.
//

#ifndef HFT_ROBOT_DEBUGINFOMANAGER_H
#define HFT_ROBOT_DEBUGINFOMANAGER_H

#include <Fast/FastProtocolManager.h>
#include "../Fast/FastTypes.h"
#include "../Lib/PointerList.h"
#include "../Lib/StringIdComparer.h"

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
};

#endif //HFT_ROBOT_DEBUGINFOMANAGER_H
