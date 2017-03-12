//
// Created by root on 09.02.17.
//
#include "DebugInfoManager.h"
#include "../MarketData/StatisticInfo.h"
#include "Feeds/AstsFeedChannel.h"
//#define ENABLE_LOG


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
#ifdef ENABLE_LOG
    StatisticItemDecimal *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Value = %g. %d Items \n", value->Time(), value->Value()->Calculate(), list->Count());
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemDecimal2> *list) {
#ifdef ENABLE_LOG
    StatisticItemDecimal2 *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Px = %g Size = %g. %d Items \n", value->Time(), value->Value()->Calculate(), value->Value2()->Calculate(), list->Count());
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemLastDealInfo> *list) {
#ifdef ENABLE_LOG
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
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemIndexList> *list) {
#ifdef ENABLE_LOG
    StatisticItemIndexList *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Px = %g Size = %g TradeValue = %g. %d Items \n",
           value->Time(),
           value->Price()->Calculate(),
           value->Size()->Calculate(),
           value->TradeValue()->Calculate(),
           list->Count());
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTotalBid> *list) {
#ifdef ENABLE_LOG
    StatisticItemTotalBid *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Value = %g BidNbOr = %d. %d Items \n", value->Time(), value->Size()->Calculate(), value->BidNbOr(), list->Count());
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTotalOffer> *list) {
#ifdef ENABLE_LOG
    StatisticItemTotalOffer *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Value = %g OfferNbOr = %d. %d Items \n", value->Time(), value->Size()->Calculate(), value->OfferNbOr(), list->Count());
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, PointerListLite<StatisticItemTransactionsMagnitude> *list) {
#ifdef ENABLE_LOG
    StatisticItemTransactionsMagnitude *value = list->End()->Data();
    printf(" %s %s %s ", GetString(symbol, 0), GetString(trading, 1), string);
    printf("Time = %ld Size = %g TotalNumOfTrades = %u TradeValue = %g. %d Items \n",
           value->Time(),
           value->Size()->Calculate(),
           value->TotalNumOfTrades(),
           value->TradeValue()->Calculate(),
           list->Count());
#endif
}

void DebugInfoManager::Log(SizedArray *symbol, SizedArray *trading, const char *string, char *entryId, int entryIdLength, Decimal *price, Decimal *size) {
#ifdef ENABLE_LOG
    printf("%s %s %s %s Price = %g Size = %g\n", GetString(symbol, 0), GetString(trading, 1), string, GetString(entryId, entryIdLength, 2), price->Calculate(), size->Calculate());
#endif
}

void DebugInfoManager::PrintStatistics(AstsFeedChannel *channel) {
    printf("Start AstsFeedChannel %s\n", channel->Name());
    this->AddTabs();
    this->PrintStatistics(channel->Olr());
    this->PrintStatistics(channel->Ols());
    this->PrintStatistics(channel->Tlr());
    this->PrintStatistics(channel->Tls());
    this->PrintStatistics(channel->Msr());
    this->PrintStatistics(channel->Mss());
    this->PrintStatistics(channel->Idf());
    this->PrintStatistics(channel->Isf());
    this->RemoveTabs();
    printf("End AstsFeedChannel %s\n", channel->Name());
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
    printf("Type Hr\n");
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
    printf("HeartbeatInfo Used %d of %d", manager->GetAstsHeartbeatInfoPool()->Count(), manager->GetAstsHeartbeatInfoPool()->Capacity());
    printf("LogonInfo Used %d of %d", manager->GetAstsLogonInfoPool()->Count(), manager->GetAstsLogonInfoPool()->Capacity());
    printf("LogoutInfo Used %d of %d", manager->GetAstsLogoutInfoPool()->Count(), manager->GetAstsLogoutInfoPool()->Capacity());

    printf("GenericInfo Used %d of %d", manager->GetAstsGenericInfoPool()->Count(), manager->GetAstsGenericInfoPool()->Capacity());
    printf("IncrementalGenericInfo Used %d of %d", manager->GetAstsIncrementalGenericInfoPool()->Count(), manager->GetAstsIncrementalGenericInfoPool()->Capacity());
    printf("IncrementalMSRCURRInfo Used %d of %d", manager->GetAstsIncrementalMSRCURRInfoPool()->Count(), manager->GetAstsIncrementalMSRCURRInfoPool()->Capacity());
    printf("IncrementalMSRFONDInfo Used %d of %d", manager->GetAstsIncrementalMSRFONDInfoPool()->Count(), manager->GetAstsIncrementalMSRFONDInfoPool()->Capacity());
    printf("GenericItemInfo Used %d of %d", manager->GetAstsGenericItemInfoPool()->Count(), manager->GetAstsGenericItemInfoPool()->Capacity());

    printf("OLSFONDInfo Used %d of %d", manager->GetAstsOLSFONDInfoPool()->Count(), manager->GetAstsOLSFONDInfoPool()->Capacity());
    printf("IncrementalOLRFONDInfo Used %d of %d", manager->GetAstsIncrementalOLRFONDInfoPool()->Count(), manager->GetAstsIncrementalOLRFONDInfoPool()->Capacity());
    printf("OLSFONDItemInfo Used %d of %d", manager->GetAstsOLSFONDItemInfoPool()->Count(), manager->GetAstsOLSFONDItemInfoPool()->Capacity());

    printf("OLSCURRInfo Used %d of %d", manager->GetAstsOLSCURRInfoPool()->Count(), manager->GetAstsOLSCURRInfoPool()->Capacity());
    printf("IncrementalOLRCURRInfo Used %d of %d", manager->GetAstsIncrementalOLRCURRInfoPool()->Count(), manager->GetAstsIncrementalOLRCURRInfoPool()->Capacity());
    printf("OLSCURRItemInfo Used %d of %d", manager->GetAstsOLSCURRItemInfoPool()->Count(), manager->GetAstsOLSCURRItemInfoPool()->Capacity());

    printf("TLSFONDInfo Used %d of %d", manager->GetAstsTLSFONDInfoPool()->Count(), manager->GetAstsTLSFONDInfoPool()->Capacity());
    printf("IncrementalTLRFONDInfo Used %d of %d", manager->GetAstsIncrementalTLRFONDInfoPool()->Count(), manager->GetAstsIncrementalTLRFONDInfoPool()->Capacity());
    printf("TLSFONDItemInfo Used %d of %d", manager->GetAstsTLSFONDItemInfoPool()->Count(), manager->GetAstsTLSFONDItemInfoPool()->Capacity());

    printf("TLSCURRInfo Used %d of %d", manager->GetAstsTLSCURRInfoPool()->Count(), manager->GetAstsTLSCURRInfoPool()->Capacity());
    printf("IncrementalTLRCURRInfo Used %d of %d", manager->GetAstsIncrementalTLRCURRInfoPool()->Count(), manager->GetAstsIncrementalTLRCURRInfoPool()->Capacity());
    printf("TLSCURRItemInfo Used %d of %d", manager->GetAstsTLSCURRItemInfoPool()->Count(), manager->GetAstsTLSCURRItemInfoPool()->Capacity());

    printf("SecurityDefinitionInfo Used %d of %d", manager->GetAstsSecurityDefinitionInfoPool()->Count(), manager->GetAstsSecurityDefinitionInfoPool()->Capacity());
    printf("SecurityDefinitionGroupInstrAttribItemInfo Used %d of %d", manager->GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool()->Count(), manager->GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool()->Capacity());
    printf("SecurityDefinitionMarketSegmentGrpItemInfo Used %d of %d", manager->GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool()->Count(), manager->GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool()->Capacity());
    printf("SecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo Used %d of %d", manager->GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Count(), manager->GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Capacity());

    printf("SecurityStatusInfo Used %d of %d", manager->GetAstsSecurityStatusInfoPool()->Count(), manager->GetAstsSecurityStatusInfoPool()->Capacity());
    printf("TradingSessionStatusInfo Used %d of %d", manager->GetAstsTradingSessionStatusInfoPool()->Count(), manager->GetAstsTradingSessionStatusInfoPool()->Capacity());

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

void DebugInfoManager::PrintStatisticsXml(const char *fileName, AstsFeedChannel *channel) {
    this->fp = fopen(fileName, "wt");

    fprintf(fp, "<AstsFeedChannel Name=\"%s\">\n", channel->Name());
    this->AddTabs();
    this->PrintStatisticsXml(channel->Olr());
    this->PrintStatisticsXml(channel->Ols());
    this->PrintStatisticsXml(channel->Tlr());
    this->PrintStatisticsXml(channel->Tls());
    this->PrintStatisticsXml(channel->Msr());
    this->PrintStatisticsXml(channel->Mss());
    this->PrintStatisticsXml(channel->Idf());
    this->PrintStatisticsXml(channel->Isf());
    this->RemoveTabs();
    fprintf(fp, "</AstsFeedChannel>\n");
    fclose(fp);
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
    fprintf(fp,"<Type>Hr</Type>\n");
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
    fprintf(fp, "<HeartbeatInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsHeartbeatInfoPool()->Count(), manager->GetAstsHeartbeatInfoPool()->Capacity());
    fprintf(fp, "<LogonInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsLogonInfoPool()->Count(), manager->GetAstsLogonInfoPool()->Capacity());
    fprintf(fp, "<LogoutInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsLogoutInfoPool()->Count(), manager->GetAstsLogoutInfoPool()->Capacity());

    fprintf(fp, "<GenericInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsGenericInfoPool()->Count(), manager->GetAstsGenericInfoPool()->Capacity());
    fprintf(fp, "<IncrementalGenericInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalGenericInfoPool()->Count(), manager->GetAstsIncrementalGenericInfoPool()->Capacity());
    fprintf(fp, "<IncrementalMSRCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalMSRCURRInfoPool()->Count(), manager->GetAstsIncrementalMSRCURRInfoPool()->Capacity());
    fprintf(fp, "<IncrementalMSRFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalMSRFONDInfoPool()->Count(), manager->GetAstsIncrementalMSRFONDInfoPool()->Capacity());
    fprintf(fp, "<GenericItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsGenericItemInfoPool()->Count(), manager->GetAstsGenericItemInfoPool()->Capacity());

    fprintf(fp, "<OLSFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsOLSFONDInfoPool()->Count(), manager->GetAstsOLSFONDInfoPool()->Capacity());
    fprintf(fp, "<IncrementalOLRFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalOLRFONDInfoPool()->Count(), manager->GetAstsIncrementalOLRFONDInfoPool()->Capacity());
    fprintf(fp, "<OLSFONDItemInfo Used %d of %d", manager->GetAstsOLSFONDItemInfoPool()->Count(), manager->GetAstsOLSFONDItemInfoPool()->Capacity());

    fprintf(fp, "<OLSCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsOLSCURRInfoPool()->Count(), manager->GetAstsOLSCURRInfoPool()->Capacity());
    fprintf(fp, "<IncrementalOLRCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalOLRCURRInfoPool()->Count(), manager->GetAstsIncrementalOLRCURRInfoPool()->Capacity());
    fprintf(fp, "<OLSCURRItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsOLSCURRItemInfoPool()->Count(), manager->GetAstsOLSCURRItemInfoPool()->Capacity());

    fprintf(fp, "<TLSFONDInfo Used=\"%d\" Capacity\"%d\"/>", manager->GetAstsTLSFONDInfoPool()->Count(), manager->GetAstsTLSFONDInfoPool()->Capacity());
    fprintf(fp, "<IncrementalTLRFONDInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalTLRFONDInfoPool()->Count(), manager->GetAstsIncrementalTLRFONDInfoPool()->Capacity());
    fprintf(fp, "<TLSFONDItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsTLSFONDItemInfoPool()->Count(), manager->GetAstsTLSFONDItemInfoPool()->Capacity());

    fprintf(fp, "<TLSCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsTLSCURRInfoPool()->Count(), manager->GetAstsTLSCURRInfoPool()->Capacity());
    fprintf(fp, "<IncrementalTLRCURRInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsIncrementalTLRCURRInfoPool()->Count(), manager->GetAstsIncrementalTLRCURRInfoPool()->Capacity());
    fprintf(fp, "<TLSCURRItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsTLSCURRItemInfoPool()->Count(), manager->GetAstsTLSCURRItemInfoPool()->Capacity());

    fprintf(fp, "<SecurityDefinitionInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsSecurityDefinitionInfoPool()->Count(), manager->GetAstsSecurityDefinitionInfoPool()->Capacity());
    fprintf(fp, "<SecurityDefinitionGroupInstrAttribItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool()->Count(), manager->GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool()->Capacity());
    fprintf(fp, "<SecurityDefinitionMarketSegmentGrpItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool()->Count(), manager->GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool()->Capacity());
    fprintf(fp, "<SecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Count(), manager->GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool()->Capacity());

    fprintf(fp, "<SecurityStatusInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsSecurityStatusInfoPool()->Count(), manager->GetAstsSecurityStatusInfoPool()->Capacity());
    fprintf(fp, "<TradingSessionStatusInfo Used=\"%d\" Capacity=\"%d\"/>", manager->GetAstsTradingSessionStatusInfoPool()->Count(), manager->GetAstsTradingSessionStatusInfoPool()->Capacity());

    this->RemoveTabs();
    fprintf(fp, "</FastProtocolManager>\n");
}

int DebugInfoManager::CalcOrderFondTotalEntriesCount(FeedConnection *conn) {
    int count = 0;

    for(int i = 0; i < conn->OrderFond()->SymbolsCount(); i++) {
        for(int j = 0; j < conn->OrderFond()->Symbol(i)->SessionCount(); j++) {
            count += conn->OrderFond()->Symbol(i)->Session(j)->BuyQuotes()->Count();
            count += conn->OrderFond()->Symbol(i)->Session(j)->SellQuotes()->Count();
        }
    }

    return count;
}
int DebugInfoManager::CalcOrderCurrTotalEntriesCount(FeedConnection *conn) {
    int count = 0;

    for(int i = 0; i < conn->OrderCurr()->SymbolsCount(); i++) {
        for(int j = 0; j < conn->OrderCurr()->Symbol(i)->SessionCount(); j++) {
            count += conn->OrderCurr()->Symbol(i)->Session(j)->BuyQuotes()->Count();
            count += conn->OrderCurr()->Symbol(i)->Session(j)->SellQuotes()->Count();
        }
    }

    return count;
}
int DebugInfoManager::CalcTradeFondTotalEntriesCount(FeedConnection *conn) {
    int count = 0;

    for(int i = 0; i < conn->TradeFond()->SymbolsCount(); i++) {
        for(int j = 0; j < conn->TradeFond()->Symbol(i)->SessionCount(); j++) {
            count += conn->TradeFond()->Symbol(i)->Session(j)->Trades()->Count();
        }
    }

    return count;
}
int DebugInfoManager::CalcTradeCurrTotalEntriesCount(FeedConnection *conn) {
    int count = 0;

    for(int i = 0; i < conn->TradeCurr()->SymbolsCount(); i++) {
        for(int j = 0; j < conn->TradeCurr()->Symbol(i)->SessionCount(); j++) {
            count += conn->TradeCurr()->Symbol(i)->Session(j)->Trades()->Count();
        }
    }

    return count;
}

int DebugInfoManager::CheckIsFriedMDEntryQueryCleared() {
    int index = 0;
    LinkedPointer<MDEntryQueue> *start = MDEntryQueue::Pool->Start();
    while(start != 0) {
        MDEntryQueue *data = start->Data();
        if(!data->IsCleared())
            return index;
        if(start == MDEntryQueue::Pool->End())
            break;
        start = start->Next();
        index++;
    }
    return -1;
}

MDEntryQueue* DebugInfoManager::GetFirstMDEntryQueue() {
    int index = 0;
    LinkedPointer<MDEntryQueue> *start = MDEntryQueue::Pool->Start();
    while(start != 0) {
        MDEntryQueue *data = start->Data();
        if(!data->IsCleared())
            return data;
        if(start == MDEntryQueue::Pool->End())
            break;
        start = start->Next();
    }
    return 0;
}
int DebugInfoManager::GetFirstNonEmptyEntry() {
    int index = 0;
    LinkedPointer<MDEntryQueue> *start = MDEntryQueue::Pool->Start();
    while(start != 0) {
        MDEntryQueue *data = start->Data();
        if(!data->IsCleared())
            return data->GetFirstNonEmptyEntry();
        if(start == MDEntryQueue::Pool->End())
            break;
        start = start->Next();
    }
    return -1;
}

int DebugInfoManager::CalcMDEntryQueCount(AstsFeedChannel *channel, MDEntryQueue *que) {
    int count = 0;
    if(channel->Olr() != 0) {
        if(channel->Olr()->OrderCurr() != 0)
            count += channel->Olr()->OrderCurr()->DebugCalcEntryQueCount(que);
        if(channel->Olr()->OrderFond() != 0)
            count += channel->Olr()->OrderFond()->DebugCalcEntryQueCount(que);
    }
    if(channel->Tlr() != 0) {
        if(channel->Tlr()->TradeCurr() != 0)
            count += channel->Tlr()->TradeCurr()->DebugCalcEntryQueCount(que);
        if(channel->Tlr()->TradeFond() != 0)
            count += channel->Tlr()->TradeFond()->DebugCalcEntryQueCount(que);
    }
    if(channel->Msr() != 0) {
        if(channel->Msr()->StatisticCurr() != 0)
            count += channel->Msr()->StatisticCurr()->DebugCalcEntryQueCount(que);
        if(channel->Msr()->StatisticFond() != 0)
            count += channel->Msr()->StatisticFond()->DebugCalcEntryQueCount(que);
    }
    return count;
}

void DebugInfoManager::DebugCheckForDublicateItems(AstsFeedChannel *channel) {
    LinkedPointer<MDEntryQueue> *node = MDEntryQueue::Pool->Start();
    while(node != 0) {
        if(node == MDEntryQueue::Pool->End())
            break;
        if(node->Data() == 0)
            throw;
        int count = this->CalcMDEntryQueCount(channel, node->Data());
        if(count != 0) {
            this->CalcMDEntryQueCount(channel, node->Data());
            this->CalcMDEntryQueCount(channel, node->Data());
            throw;
        }
        node = node->Next();
    }

    node = MDEntryQueue::Pool->UsedStart();
    while(node != 0) {
        if(node == MDEntryQueue::Pool->UsedEnd())
            break;
        if(node->Data() == 0)
            throw;
        int count = this->CalcMDEntryQueCount(channel, node->Data());
        if(count != 1) {
            this->CalcMDEntryQueCount(channel, node->Data());
            this->CalcMDEntryQueCount(channel, node->Data());
            throw;
        }
        node = node->Next();
    }
}