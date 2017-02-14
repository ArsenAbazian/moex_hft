//
// Created by root on 09.02.17.
//
#include "DebugInfoManager.h"
#include "../MarketData/StatisticInfo.h"
#include "../FeedChannel.h"

DebugInfoManager* DebugInfoManager::Default = new DebugInfoManager();

DebugInfoManager::DebugInfoManager() {
    this->MDEntryTypes = new MDEntryType[39] {
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

    this->MDEntryTypeRecv = new int[39] {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

void DebugInfoManager::PrintDecimal2List(const char *name, PointerListLite<StatisticItemDecimal2> *list) {
    printf("Start %s Decimal List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemDecimal2> *ptr = list->Start();
    while(true) {
        StatisticItemDecimal2 *value = ptr->Data();
        printf("Time = %ld Value = %g Value2 = %g\n",
               value->Time(),
               value->Value()->Calculate(),
               value->Value2()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s Decimal List\n", name);
}

void DebugInfoManager::PrintDecimalList(const char *name, PointerListLite<StatisticItemDecimal> *list) {
    printf("Start %s Decimal List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemDecimal> *ptr = list->Start();
    while(true) {
        StatisticItemDecimal *value = ptr->Data();
        printf("Time = %ld Value = %g\n",
               value->Time(),
               value->Value()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s Decimal List\n", name);
}

void DebugInfoManager::PrintLastDealInfoList(const char *name, PointerListLite<StatisticItemLastDealInfo> *list) {
    printf("Start %s LastDealInfo List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemLastDealInfo> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemLastDealInfo *value = ptr->Data();
        printf("Time = %ld Px = %g Size = %g DealTime = %u TradeValue = %g NetChangePrevDayPtr = %g ChangeFromWAPrice = %g\n",
               value->Time(),
               value->Price()->Calculate(),
               value->Size()->Calculate(),
               value->DealTime(),
               value->TradeValue()->Calculate(),
               value->NetChangePrevDay()->Calculate(),
               value->ChangeFromWAPrice()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s LastDealInfo List\n", name);
}

void DebugInfoManager::PrintIndicesList(const char *name, PointerListLite<StatisticItemIndexList> *list) {
    printf("Start %s Index List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemIndexList> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemIndexList *value = ptr->Data();
        printf("Time = %ld Px = %g Size = %g TradeValue = %g\n",
               value->Time(),
               value->Price()->Calculate(),
               value->Size()->Calculate(),
               value->TradeValue()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s Index List\n", name);
}

void DebugInfoManager::PrintTransactionMagnitude(const char *name, PointerListLite<StatisticItemTransactionsMagnitude> *list) {
    printf("Start %s TransactionMagnitude List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemTransactionsMagnitude> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemTransactionsMagnitude *value = ptr->Data();
        printf("Time = %ld Size = %g TotalNumOfTrades = %u TradeValue = %g\n",
               value->Time(),
               value->Size()->Calculate(),
               value->TotalNumOfTrades(),
               value->TradeValue()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s TransactionMagnitude List\n", name);
}

void DebugInfoManager::PrintBooleanList(const char *name, PointerListLite<StatisticItem<bool>> *list) {
    printf("Start %s Boolean List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItem<bool>> *ptr = list->Start();
    while(true) {
        StatisticItem<bool> *value = ptr->Data();
        printf("Time = %ld Value = %s\n",
               value->Time(), value->Value()? "fasle": "true");
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s Boolean List\n", name);
}

void DebugInfoManager::PrintTotalOfferList(const char *name, PointerListLite<StatisticItemTotalOffer> *list) {
    printf("Start %s TotalOffer List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemTotalOffer> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemTotalOffer *value = ptr->Data();
        printf("Time = %ld Value = %g OfferNbOr = %d\n", value->Time(), value->Size()->Calculate(), value->OfferNbOr());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s TotalOffer List\n", name);
}

void DebugInfoManager::PrintTotalBidList(const char *name, PointerListLite<StatisticItemTotalBid> *list) {
    printf("Start %s TotalBid List Count = %d\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemTotalBid> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemTotalBid *value = ptr->Data();
        printf("Time = %ld Value = %g BidNbOr = %d\n", value->Time(), value->Size()->Calculate(), value->BidNbOr());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    printf("End %s TotalBid List\n", name);
}

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
    if(conn->OrderFond() != 0)
        this->PrintOrderTable("Order Fond", conn->OrderFond());
    if(conn->OrderCurr() != 0)
        this->PrintOrderTable("Order Curr", conn->OrderCurr());
    if(conn->TradeFond() != 0)
        this->PrintTradeTable("Trade Fond", conn->TradeFond());
    if(conn->TradeCurr() != 0)
        this->PrintTradeTable("Trade Curr", conn->TradeCurr());
    if(conn->StatisticFond() != 0)
        this->PrintStatisticsTable("Statistics Fond", conn->StatisticFond());
    if(conn->StatisticCurr() != 0)
        this->PrintStatisticsTable("Statistics Curr",conn->StatisticCurr());
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
    this->PrintStatistics(conn->m_fastProtocolManager);
    this->RemoveTabs();
}

void DebugInfoManager::PrintStatistics(FastProtocolManager *manager) {
    if(manager == 0)
        return;
    printf("Start FastProtocolManager\n");
    this->AddTabs();
    printf("HeartbeatInfo Used %d of %d", manager->GetHeartbeatInfoPool()->Count(), manager->GetHeartbeatInfoPool()->Capacity());
    printf("LogonInfo Used %d of %d", manager->GetLogonInfoPool()->Count(), manager->GetLogonInfoPool()->Capacity());
    printf("LogoutInfo Used %d of %d", manager->GetLogoutInfoPool()->Count(), manager->GetLogoutInfoPool()->Capacity());

    printf("GenericInfo Used %d of %d", manager->GetGenericInfoPool()->Count(), manager->GetGenericInfoPool()->Capacity());
    printf("IncrementalGenericInfo Used %d of %d", manager->GetIncrementalGenericInfoPool()->Count(), manager->GetIncrementalGenericInfoPool()->Capacity());
    printf("IncrementalMSRCURRInfo Used %d of %d", manager->GetIncrementalMSRCURRInfoPool()->Count(), manager->GetIncrementalMSRCURRInfoPool()->Capacity());
    printf("IncrementalMSRFONDInfo Used %d of %d", manager->GetIncrementalMSRFONDInfoPool()->Count(), manager->GetIncrementalMSRFONDInfoPool()->Capacity());
    printf("GenericItemInfo Used %d of %d", manager->GetGenericItemInfoPool()->Count(), manager->GetGenericItemInfoPool()->Capacity());

    printf("OLSFONDInfo Used %d of %d", manager->GetOLSFONDInfoPool()->Count(), manager->GetOLSFONDInfoPool()->Capacity());
    printf("IncrementalOLRFONDInfo Used %d of %d", manager->GetIncrementalOLRFONDInfoPool()->Count(), manager->GetIncrementalOLRFONDInfoPool()->Capacity());
    printf("OLSFONDItemInfo Used %d of %d", manager->GetOLSFONDItemInfoPool()->Count(), manager->GetOLSFONDItemInfoPool()->Capacity());

    printf("OLSCURRInfo Used %d of %d", manager->GetOLSCURRInfoPool()->Count(), manager->GetOLSCURRInfoPool()->Capacity());
    printf("IncrementalOLRCURRInfo Used %d of %d", manager->GetIncrementalOLRCURRInfoPool()->Count(), manager->GetIncrementalOLRCURRInfoPool()->Capacity());
    printf("OLSCURRItemInfo Used %d of %d", manager->GetOLSCURRItemInfoPool()->Count(), manager->GetOLSCURRItemInfoPool()->Capacity());

    printf("TLSFONDInfo Used %d of %d", manager->GetTLSFONDInfoPool()->Count(), manager->GetTLSFONDInfoPool()->Capacity());
    printf("IncrementalTLRFONDInfo Used %d of %d", manager->GetIncrementalTLRFONDInfoPool()->Count(), manager->GetIncrementalTLRFONDInfoPool()->Capacity());
    printf("TLSFONDItemInfo Used %d of %d", manager->GetTLSFONDItemInfoPool()->Count(), manager->GetTLSFONDItemInfoPool()->Capacity());

    printf("TLSCURRInfo Used %d of %d", manager->GetTLSCURRInfoPool()->Count(), manager->GetTLSCURRInfoPool()->Capacity());
    printf("IncrementalTLRCURRInfo Used %d of %d", manager->GetIncrementalTLRCURRInfoPool()->Count(), manager->GetIncrementalTLRCURRInfoPool()->Capacity());
    printf("TLSCURRItemInfo Used %d of %d", manager->GetTLSCURRItemInfoPool()->Count(), manager->GetTLSCURRItemInfoPool()->Capacity());

    printf("SecurityDefinitionInfo Used %d of %d", manager->GetSecurityDefinitionInfoPool()->Count(), manager->GetSecurityDefinitionInfoPool()->Capacity());
    printf("SecurityDefinitionGroupInstrAttribItemInfo Used %d of %d", manager->GetSecurityDefinitionGroupInstrAttribItemInfoPool()->Count(), manager->GetSecurityDefinitionGroupInstrAttribItemInfoPool()->Capacity());
    printf("SecurityDefinitionMarketSegmentGrpItemInfo Used %d of %d", manager->GetSecurityDefinitionMarketSegmentGrpItemInfoPool()->Count(), manager->GetSecurityDefinitionMarketSegmentGrpItemInfoPool()->Capacity());
    printf("SecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo Used %d of %d", manager->GetSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Count(), manager->GetSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Capacity());

    printf("SecurityStatusInfo Used %d of %d", manager->GetSecurityStatusInfoPool()->Count(), manager->GetSecurityStatusInfoPool()->Capacity());
    printf("TradingSessionStatusInfo Used %d of %d", manager->GetTradingSessionStatusInfoPool()->Count(), manager->GetTradingSessionStatusInfoPool()->Capacity());

    this->RemoveTabs();
    printf("End FastProtocolManager\n");
}

void DebugInfoManager::PrintFastProtocolManager(FastProtocolManager *manager) {

}

void DebugInfoManager::PrintDecimal2ListXml(const char *name, PointerListLite<StatisticItemDecimal2> *list) {
    fprintf(fp, "<Decimal2List Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemDecimal2> *ptr = list->Start();
    while(true) {
        StatisticItemDecimal2 *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Value=\"%g\" Value2=\"%g\"/>\n",
               value->Time(),
               value->Value()->Calculate(),
               value->Value2()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</Decimal2List>\n");
}

void DebugInfoManager::PrintDecimalListXml(const char *name, PointerListLite<StatisticItemDecimal> *list) {
    fprintf(fp, "<DecimalList Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemDecimal> *ptr = list->Start();
    while(true) {
        StatisticItemDecimal *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Value=\"%g\"/>\n",
               value->Time(),
               value->Value()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</DecimalList>\n");
}

void DebugInfoManager::PrintLastDealInfoListXml(const char *name, PointerListLite<StatisticItemLastDealInfo> *list) {
    fprintf(fp, "<LastDealInfoList Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemLastDealInfo> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemLastDealInfo *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Px=\"%g\" Size=\"%g\" DealTime=\"%u\" TradeValue=\"%g\" NetChangePrevDayPtr=\"%g\" ChangeFromWAPrice=\"%g\"/>\n",
               value->Time(),
               value->Price()->Calculate(),
               value->Size()->Calculate(),
               value->DealTime(),
               value->TradeValue()->Calculate(),
               value->NetChangePrevDay()->Calculate(),
               value->ChangeFromWAPrice()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</LastDealInfoList>\n");
}

void DebugInfoManager::PrintIndicesListXml(const char *name, PointerListLite<StatisticItemIndexList> *list) {
    fprintf(fp, "<IndicesLis Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemIndexList> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemIndexList *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Px=\"%g\" Size=\"%g\" TradeValue=\"%g\"/>\n",
               value->Time(),
               value->Price()->Calculate(),
               value->Size()->Calculate(),
               value->TradeValue()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</IndicesLis>\n");
}

void DebugInfoManager::PrintTransactionMagnitudeXml(const char *name, PointerListLite<StatisticItemTransactionsMagnitude> *list) {
    fprintf(fp, "<TransactionMagnitudeList Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemTransactionsMagnitude> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemTransactionsMagnitude *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Size=\"%g\" TotalNumOfTrades=\"%u\" TradeValue=\"%g\"/>\n",
               value->Time(),
               value->Size()->Calculate(),
               value->TotalNumOfTrades(),
               value->TradeValue()->Calculate());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</TransactionMagnitudeList>\n");
}

void DebugInfoManager::PrintBooleanListXml(const char *name, PointerListLite<StatisticItem<bool>> *list) {
    fprintf(fp, "<BooleanList Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItem<bool>> *ptr = list->Start();
    while(true) {
        StatisticItem<bool> *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Value=\"%s\"/>\n",
               value->Time(), value->Value()? "fasle": "true");
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</BooleanList>\n");
}

void DebugInfoManager::PrintTotalOfferListXml(const char *name, PointerListLite<StatisticItemTotalOffer> *list) {
    fprintf(fp, "<TotalOfferList Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemTotalOffer> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemTotalOffer *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Value=\"%g\" OfferNbOr=\"%d\"/>\n", value->Time(), value->Size()->Calculate(), value->OfferNbOr());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</TotalOfferList>\n");
}

void DebugInfoManager::PrintTotalBidListXml(const char *name, PointerListLite<StatisticItemTotalBid> *list) {
    fprintf(fp, "<TotalBidList Name=\"%s\" Count=\"%d\">\n", name, list->Count());
    this->AddTabs();
    LinkedPointer<StatisticItemTotalBid> *ptr = list->Start();
    while(ptr != 0) {
        StatisticItemTotalBid *value = ptr->Data();
        fprintf(fp, "<Item Time=\"%ld\" Value=\"%g\" BidNbOr=\"%d\"/>\n", value->Time(), value->Size()->Calculate(), value->BidNbOr());
        if(ptr == list->End())
            break;
        ptr = ptr->Next();
    }
    this->RemoveTabs();
    fprintf(fp, "</TotalBidList>\n");
}

void DebugInfoManager::PrintStatisticsXml(const char *fileName, FeedChannel *channel) {
    this->fp = fopen(fileName, "wt");

    fprintf(fp, "<FeedChannel Name=\"%s\">\n", channel->Name());
    this->AddTabs();
    this->PrintStatisticsXml(channel->OrdersIncremental());
    this->PrintStatisticsXml(channel->OrdersSnapshot());
    this->PrintStatisticsXml(channel->TradesIncremental());
    this->PrintStatisticsXml(channel->TradesSnapshot());
    this->PrintStatisticsXml(channel->StatisticsIncremental());
    this->PrintStatisticsXml(channel->StatisticsSnapshot());
    this->PrintStatisticsXml(channel->InstrumentDefinition());
    this->PrintStatisticsXml(channel->InstrumentStatus());
    this->RemoveTabs();
    fprintf(fp, "</FeedChannel>\n");
}

void DebugInfoManager::PrintStatisticsIncrementalXml(FeedConnection *conn) {
    printf("<Type>Incremental</Type>\n");
    if(conn->OrderFond() != 0)
        this->PrintOrderTableXml("Order Fond", conn->OrderFond());
    if(conn->OrderCurr() != 0)
        this->PrintOrderTableXml("Order Curr", conn->OrderCurr());
    if(conn->TradeFond() != 0)
        this->PrintTradeTableXml("Trade Fond", conn->TradeFond());
    if(conn->TradeCurr() != 0)
        this->PrintTradeTableXml("Trade Curr", conn->TradeCurr());
    if(conn->StatisticFond() != 0)
        this->PrintStatisticsTableXml("Statistics Fond", conn->StatisticFond());
    if(conn->StatisticCurr() != 0)
        this->PrintStatisticsTableXml("Statistics Curr",conn->StatisticCurr());
}
void DebugInfoManager::PrintStatisticsSnapshotXml(FeedConnection *conn) {
    fprintf(fp, "<Type>Snapshot</Type>\n");
}
void DebugInfoManager::PrintStatisticsInstrumentDefinitionXml(FeedConnection *conn) {
    fprintf(fp, "<Type>SecurityDefinition</Type>\n");
}
void DebugInfoManager::PrintStatisticsInstrumentStatusXml(FeedConnection *conn) {
    fprintf(fp, "<Type>SecurityStatus</Type>\n");
}
void DebugInfoManager::PrintStatisticsHistoricalReplayXml(FeedConnection *conn) {
    fprintf(fp,"<Type>HistoricalReplay</Type>\n");
}

void DebugInfoManager::PrintStatisticsXml(FeedConnection *conn) {
    if(conn == 0)
        return;
    fprintf(fp, "<FeedConnection Name=\"%s\" State=\"%d\">\n", conn->IdName(), conn->State());
    this->AddTabs();
    switch(conn->Type()) {
        case FeedConnectionType::Incremental:
            PrintStatisticsIncrementalXml(conn);
            break;
        case FeedConnectionType::Snapshot:
            PrintStatisticsSnapshotXml(conn);
            break;
        case FeedConnectionType::InstrumentDefinition:
            PrintStatisticsInstrumentDefinitionXml(conn);
            break;
        case FeedConnectionType::InstrumentStatus:
            PrintStatisticsInstrumentStatusXml(conn);
            break;
        case FeedConnectionType::HistoricalReplay:
            PrintStatisticsHistoricalReplayXml(conn);
            break;
    }
    this->PrintStatisticsXml(conn->m_fastProtocolManager);
    this->RemoveTabs();
    fprintf(fp, "</FeedConnection>\n");
}

void DebugInfoManager::PrintStatisticsXml(FastProtocolManager *manager) {
    if(manager == 0)
        return;
    fprintf(fp, "<FastProtocolManager>\n");
    this->AddTabs();
    fprintf(fp, "<HeartbeatInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetHeartbeatInfoPool()->Count(), manager->GetHeartbeatInfoPool()->Capacity());
    fprintf(fp, "<LogonInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetLogonInfoPool()->Count(), manager->GetLogonInfoPool()->Capacity());
    fprintf(fp, "<LogoutInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetLogoutInfoPool()->Count(), manager->GetLogoutInfoPool()->Capacity());

    fprintf(fp, "<GenericInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetGenericInfoPool()->Count(), manager->GetGenericInfoPool()->Capacity());
    fprintf(fp, "<IncrementalGenericInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalGenericInfoPool()->Count(), manager->GetIncrementalGenericInfoPool()->Capacity());
    fprintf(fp, "<IncrementalMSRCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalMSRCURRInfoPool()->Count(), manager->GetIncrementalMSRCURRInfoPool()->Capacity());
    fprintf(fp, "<IncrementalMSRFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalMSRFONDInfoPool()->Count(), manager->GetIncrementalMSRFONDInfoPool()->Capacity());
    fprintf(fp, "<GenericItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetGenericItemInfoPool()->Count(), manager->GetGenericItemInfoPool()->Capacity());

    fprintf(fp, "<OLSFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetOLSFONDInfoPool()->Count(), manager->GetOLSFONDInfoPool()->Capacity());
    fprintf(fp, "<IncrementalOLRFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalOLRFONDInfoPool()->Count(), manager->GetIncrementalOLRFONDInfoPool()->Capacity());
    fprintf(fp, "<OLSFONDItemInfo Used %d of %d", manager->GetOLSFONDItemInfoPool()->Count(), manager->GetOLSFONDItemInfoPool()->Capacity());

    fprintf(fp, "<OLSCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetOLSCURRInfoPool()->Count(), manager->GetOLSCURRInfoPool()->Capacity());
    fprintf(fp, "<IncrementalOLRCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalOLRCURRInfoPool()->Count(), manager->GetIncrementalOLRCURRInfoPool()->Capacity());
    fprintf(fp, "<OLSCURRItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetOLSCURRItemInfoPool()->Count(), manager->GetOLSCURRItemInfoPool()->Capacity());

    fprintf(fp, "<TLSFONDInfo Used=\"%d\" Capacity\"%d\"/>", manager->GetTLSFONDInfoPool()->Count(), manager->GetTLSFONDInfoPool()->Capacity());
    fprintf(fp, "<IncrementalTLRFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalTLRFONDInfoPool()->Count(), manager->GetIncrementalTLRFONDInfoPool()->Capacity());
    fprintf(fp, "<TLSFONDItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetTLSFONDItemInfoPool()->Count(), manager->GetTLSFONDItemInfoPool()->Capacity());

    fprintf(fp, "<TLSCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetTLSCURRInfoPool()->Count(), manager->GetTLSCURRInfoPool()->Capacity());
    fprintf(fp, "<IncrementalTLRCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetIncrementalTLRCURRInfoPool()->Count(), manager->GetIncrementalTLRCURRInfoPool()->Capacity());
    fprintf(fp, "<TLSCURRItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetTLSCURRItemInfoPool()->Count(), manager->GetTLSCURRItemInfoPool()->Capacity());

    fprintf(fp, "<SecurityDefinitionInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetSecurityDefinitionInfoPool()->Count(), manager->GetSecurityDefinitionInfoPool()->Capacity());
    fprintf(fp, "<SecurityDefinitionGroupInstrAttribItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetSecurityDefinitionGroupInstrAttribItemInfoPool()->Count(), manager->GetSecurityDefinitionGroupInstrAttribItemInfoPool()->Capacity());
    fprintf(fp, "<SecurityDefinitionMarketSegmentGrpItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetSecurityDefinitionMarketSegmentGrpItemInfoPool()->Count(), manager->GetSecurityDefinitionMarketSegmentGrpItemInfoPool()->Capacity());
    fprintf(fp, "<SecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Count(), manager->GetSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Capacity());

    fprintf(fp, "<SecurityStatusInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetSecurityStatusInfoPool()->Count(), manager->GetSecurityStatusInfoPool()->Capacity());
    fprintf(fp, "<TradingSessionStatusInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetTradingSessionStatusInfoPool()->Count(), manager->GetTradingSessionStatusInfoPool()->Capacity());

    this->RemoveTabs();
    fprintf(fp, "</FastProtocolManager>\n");
}



