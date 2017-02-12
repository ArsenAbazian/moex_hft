//
// Created by root on 09.02.17.
//
#include "DebugInfoManager.h"
#include "../MarketData/StatisticInfo.h"

DebugInfoManager* DebugInfoManager::Default = new DebugInfoManager();

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemDecimal> *list) {
    StatisticItemDecimal *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Value = %g. %d Items \n", value->Time(), value->Value()->Calculate(), list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemDecimal2> *list) {
    StatisticItemDecimal2 *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Px = %g Size = %g. %d Items \n", value->Time(), value->Value()->Calculate(), value->Value2()->Calculate(), list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemLastDealInfo> *list) {
    StatisticItemLastDealInfo *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Px = %g Size = %g DealTime = %u TradeValue = %g NetChangePrevDayPtr = %g ChangeFromWAPrice = %g. %d Items \n",
           value->Time(),
           value->Price()->Calculate(),
           value->Size()->Calculate(),
           value->DealTime(),
           value->TradeValue()->Calculate(),
           value->NetChangePrevDay()->Calculate(),
           value->ChangeFromWAPrice()->Calculate(),
           list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemIndexList> *list) {
    StatisticItemIndexList *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Px = %g Size = %g TradeValue = %g. %d Items \n",
           value->Time(),
           value->Price()->Calculate(),
           value->Size()->Calculate(),
           value->TradeValue()->Calculate(),
           list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTotalBid> *list) {
    StatisticItemTotalBid *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Value = %g BidNbOr = %d. %d Items \n", value->Time(), value->Size()->Calculate(), value->BidNbOr(), list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTotalOffer> *list) {
    StatisticItemTotalOffer *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Value = %g OfferNbOr = %d. %d Items \n", value->Time(), value->Size()->Calculate(), value->OfferNbOr(), list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTransactionsMagnitude> *list) {
    StatisticItemTransactionsMagnitude *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Size = %g TotalNumOfTrades = %u TradeValue = %g. %d Items \n",
           value->Time(),
           value->Size()->Calculate(),
           value->TotalNumOfTrades(),
           value->TradeValue()->Calculate(),
           list->Count());
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, char *entryId, int entryIdLength, Decimal *price, Decimal *size) {
    printf("%s %s %s %s Price = %g Size = %g\n", GetString(symbol, 0), GetString(trading, 1), string, GetString(entryId, entryIdLength, 2), price->Calculate(), size->Calculate());
}