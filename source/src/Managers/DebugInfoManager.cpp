//
// Created by root on 09.02.17.
//
#include "DebugInfoManager.h"
#include "../MarketData/StatisticInfo.h"
#include "../FeedChannel.h"

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

void DebugInfoManager::PrintStatistics(FeedChannel *channel) {
    printf("Start FeedChannel %s\n", channel->Name());
    this->AddTabs();
    this->PrintStatistics(channel->OrdersIncremental());
    this->PrintStatistics(channel->OrdersSnapshot());
    this->PrintStatistics(channel->TradesIncremental());
    this->PrintStatistics(channel->TradesSnapshot());
    this->PrintStatistics(channel->StatisticsIncremental());
    this->PrintStatistics(channel->StatisticsSnapshot());
    this->PrintStatistics(channel->InstrumentDefinition());
    this->PrintStatistics(channel->InstrumentStatus());
    this->RemoveTabs();
    printf("End FeedChannel %s\n", channel->Name());
}

void DebugInfoManager::PrintStatisticsIncremental(FeedConnection *conn) {
    printf("Type Incremental\n");
}
void DebugInfoManager::PrintStatisticsSnapshot(FeedConnection *conn) {
    printf("Type Snapshot\n");
}
void DebugInfoManager::PrintStatisticsInstrumentDefinition(FeedConnection *conn) {
    printf("Type SecurityDefinition\n");
}
void DebugInfoManager::PrintStatisticsInstrumentStatus(FeedConnection *conn) {
    printf("Type SecurityStatus\n");
}
void DebugInfoManager::PrintStatisticsHistoricalReplay(FeedConnection *conn) {
    printf("Type HistoricalReplay\n");
}

void DebugInfoManager::PrintStatistics(FeedConnection *conn) {
    if(conn == 0)
        return;
    printf("Start FeedConnection %s\n", conn->IdName());
    this->AddTabs();
    printf("State %d\n", conn->State());
    switch(conn->Type()) {
        case FeedConnectionType::Incremental:
            PrintStatisticsIncremental(conn);
            break;
        case FeedConnectionType::Snapshot:
            PrintStatisticsSnapshot(conn);
            break;
        case FeedConnectionType::InstrumentDefinition:
            PrintStatisticsInstrumentDefinition(conn);
            break;
        case FeedConnectionType::InstrumentStatus:
            PrintStatisticsInstrumentStatus(conn);
            break;
        case FeedConnectionType::HistoricalReplay:
            PrintStatisticsHistoricalReplay(conn);
            break;
    }
    this->RemoveTabs();
}

void DebugInfoManager::PrintStatistics(FastProtocolManager *manager) {
    printf("Start FastProtocolManager\n");
    this->AddTabs();
    printf("HeartbeatInfo Used %d of %d", manager->GetHeartbeatInfoPool()->Count(), manager->GetHeartbeatInfoPool()->Capacity());
    printf("LogonInfo Used %d of %d", manager->GetLogonInfoPool()->Count(), manager->GetLogonInfoPool()->Capacity());
    printf("LogoutInfo Used %d of %d", manager->GetLogoutInfoPool()->Count(), manager->GetLogoutInfoPool()->Capacity());

    printf("GenericInfo Used %d of %d", manager->GetGenericInfoPool()->Count(), manager->GetGenericInfoPool()->Capacity());
    printf("GenericItemInfo Used %d of %d", manager->GetGenericItemInfoPool()->Count(), manager->GetGenericItemInfoPool()->Capacity());
    printf("IncrementalGenericInfo Used %d of %d", manager->GetIncrementalGenericInfoPool()->Count(), manager->GetIncrementalGenericInfoPool()->Capacity());
    printf("IncrementalMSRCURRInfo Used %d of %d", manager->GetIncrementalMSRCURRInfoPool()->Count(), manager->GetIncrementalMSRCURRInfoPool()->Capacity());
    printf("IncrementalMSRFONDInfo Used %d of %d", manager->GetIncrementalMSRFONDInfoPool()->Count(), manager->GetIncrementalMSRFONDInfoPool()->Capacity());

    printf("OLSFONDInfo Used %d of %d", manager->GetOLSFONDInfoPool()->Count(), manager->GetOLSFONDInfoPool()->Capacity());
    printf("OLSFONDItemInfo Used %d of %d", manager->GetOLSFONDItemInfoPool()->Count(), manager->GetOLSFONDItemInfoPool()->Capacity());
    printf("IncrementalOLRFONDInfo Used %d of %d", manager->GetIncrementalOLRFONDInfoPool()->Count(), manager->GetIncrementalOLRFONDInfoPool()->Capacity());
    
    printf("OLSCURRInfo Used %d of %d", manager->GetOLSCURRInfoPool()->Count(), manager->GetOLSCURRInfoPool()->Capacity());
    printf("OLSCURRItemInfo Used %d of %d", manager->GetOLSCURRItemInfoPool()->Count(), manager->GetOLSCURRItemInfoPool()->Capacity());
    printf("IncrementalOLRCURRInfo Used %d of %d", manager->GetIncrementalOLRCURRInfoPool()->Count(), manager->GetIncrementalOLRCURRInfoPool()->Capacity());

    printf("TLSFONDInfo Used %d of %d", manager->GetTLSFONDInfoPool()->Count(), manager->GetTLSFONDInfoPool()->Capacity());
    printf("TLSFONDItemInfo Used %d of %d", manager->GetTLSFONDItemInfoPool()->Count(), manager->GetTLSFONDItemInfoPool()->Capacity());
    printf("IncrementalTLRFONDInfo Used %d of %d", manager->GetIncrementalTLRFONDInfoPool()->Count(), manager->GetIncrementalTLRFONDInfoPool()->Capacity());

    printf("TLSCURRInfo Used %d of %d", manager->GetTLSCURRInfoPool()->Count(), manager->GetTLSCURRInfoPool()->Capacity());
    printf("TLSCURRItemInfo Used %d of %d", manager->GetTLSCURRItemInfoPool()->Count(), manager->GetTLSCURRItemInfoPool()->Capacity());
    printf("IncrementalTLRCURRInfo Used %d of %d", manager->GetIncrementalTLRCURRInfoPool()->Count(), manager->GetIncrementalTLRCURRInfoPool()->Capacity());

    this->RemoveTabs();
    printf("End FastProtocolManager\n");
}

void DebugInfoManager::PrintFastProtocolManager(FastProtocolManager *manager) {
    manager->Print();
}