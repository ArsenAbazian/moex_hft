//
// Created by root on 09.02.17.
//

#ifndef HFT_ROBOT_DEBUGINFOMANAGER_H
#define HFT_ROBOT_DEBUGINFOMANAGER_H

#include "../Fast/FastTypes.h"
#include "../Fast/FastProtocolManager.h"
#include "../Lib/PointerList.h"

class StatisticItemDecimal;
class StatisticItemDecimal2;
class StatisticItemLastDealInfo;
class StatisticItemIndexList;
class StatisticItemTotalBid;
class StatisticItemTotalOffer;
class StatisticItemTransactionsMagnitude;

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

    char m_buffer[392];
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
            manager->Print();
    }

    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemDecimal> *list);
    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemDecimal2> *list);
    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemLastDealInfo> *list);
    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemIndexList> *list);
    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemTotalBid> *list);
    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemTotalOffer> *list);
    void Log(const char *symbol, const char *trading, const char *string, PointerListLite<StatisticItemTransactionsMagnitude> *list);
};

#endif //HFT_ROBOT_DEBUGINFOMANAGER_H
