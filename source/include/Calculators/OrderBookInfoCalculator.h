//
// Created by root on 11.04.17.
//

#ifndef HFT_ROBOT_ORDERBOOKCALCULATOR_H
#define HFT_ROBOT_ORDERBOOKCALCULATOR_H

#include "../Lib/PointerList.h"
#include "../Robot.h"

class OrderBookCalcInfo {
    const char *m_symbol;
    const char *m_tradingSession;
    int         m_askCount;
    int         m_bidCount;
public:
    OrderBookCalcInfo() :
            m_symbol(0),
            m_tradingSession(0),
            m_askCount(0),
            m_bidCount(0) {
    }
    inline const char* Symbol() { return this->m_symbol; }
    inline const char* Session() { return this->m_tradingSession; }
    inline int BidCount() { return this->m_bidCount; }
    inline int AskCount() { return this->m_askCount; }

    inline const char* Symbol(const char *symbol) { this->m_symbol = symbol; }
    inline const char* Session(const char *session) { this->m_tradingSession = session; }
    inline int BidCount(int bidCount) { this->m_bidCount = bidCount; }
    inline int AskCount(int askCount) { this->m_askCount = askCount; }

    inline int Deepness() { return this->m_askCount > this->m_bidCount? this->m_askCount: this->m_bidCount; }
    inline void Clear() {
        this->m_symbol = 0;
        this->m_tradingSession = 0;
        this->m_askCount = 0;
        this->m_bidCount = 0;
    }
};

class OrderBookInfoCalculator {
    Robot                       *m_robot;
    PointerList<OrderBookCalcInfo>  *m_fondList;
    PointerList<OrderBookCalcInfo>  *m_currList;
    PointerList<OrderBookCalcInfo>  *m_futList;
    PointerList<OrderBookCalcInfo>  *m_optList;

    inline void SafeClear(PointerList<OrderBookCalcInfo>  *list) {
        if(list != 0) list->Clear();
    }
    inline void SafeDestroy(PointerList<OrderBookCalcInfo>  *list) {
        if(list != 0) delete list;
    }
public:
    OrderBookInfoCalculator(Robot *robot) :
            m_robot(robot),
            m_fondList(0),
            m_currList(0),
            m_futList(0),
            m_optList(0) {
        if(this->m_robot->AllowFondMarket())
            this->m_fondList = new PointerList<OrderBookCalcInfo>(25000, true, "LiquidityCalculator::FondList");
        if(this->m_robot->AllowCurrMarket())
            this->m_fondList = new PointerList<OrderBookCalcInfo>(2000, true, "LiquidityCalculator::CurrList");
        if(this->m_robot->AllowFortsMarket()) {
            if(this->m_robot->AllowFutures())
                this->m_futList = new PointerList<OrderBookCalcInfo>(2000, true, "LiquidityCalculator::FutList");
            if(this->m_robot->AllowOptions())
                this->m_optList = new PointerList<OrderBookCalcInfo>(2000, true, "LiquidityCalculator::OptList");
        }
    }
    ~OrderBookInfoCalculator() {
        this->SafeDestroy(this->m_fondList);
        this->SafeDestroy(this->m_currList);
        this->SafeDestroy(this->m_futList);
        this->SafeDestroy(this->m_optList);
    }

    inline void Clear() {
        this->SafeClear(this->m_fondList);
        this->SafeClear(this->m_currList);
        this->SafeClear(this->m_futList);
        this->SafeClear(this->m_optList);
    }
    inline void Init(OrderBookCalcInfo *info, OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item) {
        info->BidCount(item->BuyQuotes()->Count);
        info->AskCount(item->SellQuotes()->Count);
        info->Symbol(item->Symbol()->m_text);
        info->Session(item->TradingSession()->m_text);
    }
    inline void Insert(PointerList<OrderBookCalcInfo> *list, OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo> *item) {
        int dp = item->BuyQuotes()->Count() + item->SellQuotes()->Count();
        LinkedPointer<OrderBookCalcInfo>  *node = list->Start();
        while(node != 0) {
            if(node->Data()->Deepness() < dp) {
                LinkedPointer<OrderBookCalcInfo> newNode = list->Pop();
                this->Init(newNode->Data(), item);
                list->Insert(node, newNode);
                return;
            }
            node = node->Next();
        }
        LinkedPointer<OrderBookCalcInfo> newNode = list->Pop();
        this->Init(newNode->Data(), item);
        list->Add(newNode);
    }
    inline void CalculateFortsCore(FeedConnection_FORTS_INC *fc) {
        MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo> *table = fc->OrderBookForts();
        for(int i = 0; i < table->SymbolsCount(); i++) {
            MarketSymbolInfo<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>> *s = table->Symbol(i);
            this->Insert(this->m_futList, s->Session(0));
        }
    }
    inline CalculateFut() {
        this->CalculateFortsCore(this->m_robot->FortsChannel()->FutBook50()->Inc());
    }
    inline CalculateOpt() {
        this->CalculateFortsCore(this->m_robot->FortsChannel()->OptBook50()->Inc());
    }
    void CalculateFond() {

    }
    void CalculateCurr() {

    }

    void Calculate() {
        if(this->m_futList != 0)
            this->CalculateFut();
        if(this->m_optList != 0)
            this->CalculateOpt();
        if(this->m_fondList != 0)
            this->CalculateFond();
        if(this->m_currList != 0)
            this->CalculateCurr();
    }
};

#endif //HFT_ROBOT_ORDERBOOKCALCULATOR_H
