//
// Created by root on 05.02.17.
//
#include "../../include/MarketData/StatisticInfo.h"
#include "../../include/Managers/DebugInfoManager.h"

StatisticItemAllocator::StatisticItemAllocator() {
    this->m_decimals = new PointerList<StatisticItemDecimal>(400000, true, "StatisticsInfo::Decimals");
    this->m_decimals2 = new PointerList<StatisticItemDecimal2>(100000, true, "StatisticsInfo::Decimals2");
    this->m_dealInfos = new PointerList<StatisticItemLastDealInfo>(100000, true, "StatisticsInfo::DealInfo");
    this->m_totalOffers = new PointerList<StatisticItemTotalOffer>(800000, true, "StatisticsInfo::TotalOffer");
    this->m_totalBids = new PointerList<StatisticItemTotalBid>(800000, true, "StatisticsInfo::TotalBid");
    this->m_indexLists = new PointerList<StatisticItemIndexList>(100000, true, "StatisticsInfo::IndexList");
    this->m_trMagnitudes = new PointerList<StatisticItemTransactionsMagnitude>(400000, true, "StatisticsInfo::TransactionMagnitudes");
    this->m_booleans = new PointerList<StatisticItem<bool>>(100000, true, "StatisticsInfo::Booleans");
    DebugInfoManager::Default->PrintMemoryInfo("StatisticItemAllocator::StatisticItemAllocator");
}

StatisticItemAllocator* DefaultStatisticItemAllocator::Default = 0;


