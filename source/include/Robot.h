#pragma once
#include "FeedChannel.h"
#include "MarketInfo.h"
#include "Fix/FixProtocolManager.h"
#include "Managers/LogManager.h"
#include "ConnectionParameters.h"

#define MARKET_INFO_CAPACITY 10
typedef enum _RobotState {

} RobotState;

class Robot {
	FeedChannel *channels[MARKET_INFO_CAPACITY];
	int		channelsCount;

	MarketInfo *markets[MARKET_INFO_CAPACITY];
	int		marketCount;

    MarketInfo *m_currMarket;
    MarketInfo *m_fondMarket;

    bool        m_allowFondMarket;
    bool        m_allowCurrMarket;

	RobotState state;

	FixProtocolManager *protocolManager;

    MarketInfo* FindMarket(const char* name) {
        for(int i = 0; i < this->marketCount; i++) {
            if(strcmp(this->markets[i]->Name(), name) == 0)
                return this->markets[i];
        }
        return NULL;
    }
    FeedChannel *FindFeedChannel(const char* id) {
        for(int i = 0; i < this->channelsCount; i++) {
            if(strcmp(this->channels[i]->Id(), id) == 0)
                return this->channels[i];
        }
        return NULL;
    }

    bool ConnectMarkets();
    bool DisconnectMarkets();
    bool DoWork();

    bool CollectSecurityDefinitions();
    bool CollectSecurityDefinitions_FondOnly();
    bool CollectSecurityDefinitions_CurrOnly();
    bool MainLoop();
    bool MainLoop_FondOnly();
    bool MainLoop_CurrOnly();

    inline bool DoWorkAtom() {
        return true;
    }
    inline bool Working() {
        return this->m_currMarket->Working() || this->m_fondMarket->Working();
    }

public:
	Robot();
	~Robot();

    inline bool AllowFondMarket() { return this->m_allowFondMarket; }
    inline void AllowFondMarket(bool value) { this->m_allowFondMarket = value; }
    inline bool AllowCurrMarket() { return this->m_allowCurrMarket; }
    inline void AllowCurrMarket(bool value) { this->m_allowCurrMarket = value; }

    inline bool AllowFeed(const char *feedId) {
#ifdef ALLOW_STATISTICS
        if(StringIdComparer::Equal(feedId, "MSR") || StringIdComparer::Equal(feedId, "MSS"))
            return true;
#endif
#ifdef ALLOW_ORDERS
        if(StringIdComparer::Equal(feedId, "OLR") || StringIdComparer::Equal(feedId, "OLS"))
            return true;
#endif
#ifdef ALLOW_TRADES
        if(StringIdComparer::Equal(feedId, "TLR") || StringIdComparer::Equal(feedId, "TLS"))
            return true;
#endif
#ifdef ALLOW_STATUS
        if(StringIdComparer::Equal(feedId, "ISF"))
            return true;
#endif
        if(StringIdComparer::Equal(feedId, "IDF"))
            return true;
        if(StringIdComparer::Equal(feedId, "H"))
            return true;
        return false;
    }

	void AddChannel(FeedChannel *info) {
		this->channels[this->channelsCount] = info;
		this->channelsCount++;
	}

	void AddMarket(MarketInfo *info) { 
		this->markets[this->marketCount] = info;
		this->marketCount++;
	}

	bool AddDefaultTestChannels();

	bool AddDefaultTestMarkets() { 
		DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_AddDefaultTestMarkets);
		if(this->AllowFondMarket()) {
            AddMarket(new FondMarketInfo("FOND", FundMarketSenderComputerId, FundMarketPassword,
                                         FundMarketTradeServerAddress, FundMarketTradeASTSServerName,
                                         FundMarketTradeName, FundMarketTradeServerPort,
                                         FundMarketTradeTargetComputerId,
                                         FundMarketTradeCaptureName, FundMarketTradeCaptureServerPort,
                                         FundMarketTradeCaptureTargetComputerId,
                                         FundMarketTradeDropCopyName, FundMarketTradeDropCopyServerPort,
                                         FundMarketTradeDropCopyTargetComputerId));
        }
		if(this->AllowCurrMarket()) {
            AddMarket(new CurrencyMarketInfo("CURR", CurrencyMarketSenderComputerId, CurrencyMarketPassword,
                                             CurrencyMarketTradeServerAddress, CurrencyMarketTradeASTSServerName,
                                             CurrencyMarketTradeName, CurrencyMarketTradeServerPort,
                                             CurrencyMarketTradeTargetComputerId,
                                             CurrencyMarketTradeCaptureName, CurrencyMarketTradeCaptureServerPort,
                                             CurrencyMarketTradeCaptureTargetComputerId,
                                             CurrencyMarketTradeDropCopyName, CurrencyMarketTradeDropCopyeServerPort,
                                             CurrencyMarketTradeDropCopyTargetComputerId));
        }
		DefaultLogManager::Default->EndLog(true);
		return true;
	}

    bool SetFeedChannelsForMarkets() {
        DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_SetFeedChannelsForMarkets);

        if(this->AllowFondMarket()) {
            this->m_fondMarket = FindMarket("FOND");
            FeedChannel *fondChannel = FindFeedChannel("FOND");
            if (this->m_fondMarket == NULL) {
                DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcFOND_market_not_found);
                return false;
            }
            if (fondChannel == NULL) {
                DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcFOND_feed_channel_not_found);
                return false;
            }
            this->m_fondMarket->SetFeedChannel(fondChannel);
        }

        if(this->AllowCurrMarket()) {
            this->m_currMarket = FindMarket("CURR");
            FeedChannel *currChannel = FindFeedChannel("CURR");
            if (this->m_currMarket == NULL) {
                DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcCURR_market_not_found);
                return false;
            }
            if (currChannel == NULL) {
                DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcCURR_feed_channel_not_found);
                return false;
            }
            this->m_currMarket->SetFeedChannel(currChannel);
        }

        DefaultLogManager::Default->EndLog(true);
        return true;
    }

	inline FeedChannel **Channels() { return (FeedChannel**)this->channels; }
	inline int ChannelCount() { return this->channelsCount; }

	inline MarketInfo **Markets() { return (MarketInfo**)this->markets; }
	inline int MarketCount() { return this->marketCount; }

	bool Run();

    inline void PrintStatisticsFond() {
#ifdef ALLOW_ORDERS
        if (this->m_fondMarket->FeedChannel()->Ols()->State() == FeedConnectionState::fcsListenSnapshot) {
            int foundSnapshotSymbolsCount = this->m_fondMarket->FeedChannel()->Olr()->OrderFond()->SymbolsToRecvSnapshotCount();
            int foundQueEntries = this->m_fondMarket->FeedChannel()->Olr()->OrderFond()->QueueEntriesCount();
            int msgSeqNumber = this->m_fondMarket->FeedChannel()->Ols()->MsgSeqNo();
            printf("fond olr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
        }
        else {
            printf("fond olr: start = %d end = %d\n",
                   this->m_fondMarket->FeedChannel()->Olr()->MsgSeqNo(),
                   this->m_fondMarket->FeedChannel()->Olr()->LastRecvMsgSeqNo());
        }
#endif
#ifdef ALLOW_TRADES
        if (this->m_fondMarket->FeedChannel()->Tls()->State() == FeedConnectionState::fcsListenSnapshot) {
            int foundSnapshotSymbolsCount = this->m_fondMarket->FeedChannel()->Tlr()->TradeFond()->SymbolsToRecvSnapshotCount();
            int foundQueEntries = this->m_fondMarket->FeedChannel()->Tlr()->TradeFond()->QueueEntriesCount();
            int msgSeqNumber = this->m_fondMarket->FeedChannel()->Tls()->MsgSeqNo();
            printf("fond tlr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
        }
        else {
            printf("fond tlr: start = %d end = %d\n",
                   this->m_fondMarket->FeedChannel()->Tlr()->MsgSeqNo(),
                   this->m_fondMarket->FeedChannel()->Tlr()->LastRecvMsgSeqNo());
        }
#endif
#ifdef ALLOW_STATISTICS
        if (this->m_fondMarket->FeedChannel()->Mss()->State() == FeedConnectionState::fcsListenSnapshot) {
            int foundSnapshotSymbolsCount = this->m_fondMarket->FeedChannel()->Msr()->StatisticFond()->SymbolsToRecvSnapshotCount();
            int foundQueEntries = this->m_fondMarket->FeedChannel()->Msr()->StatisticFond()->QueueEntriesCount();
            int msgSeqNumber = this->m_fondMarket->FeedChannel()->Mss()->MsgSeqNo();
            printf("fond msr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
        }
        else {
            printf("fond msr: start = %d end = %d\n",
                   this->m_fondMarket->FeedChannel()->Msr()->MsgSeqNo(),
                   this->m_fondMarket->FeedChannel()->Msr()->LastRecvMsgSeqNo());
        }
#endif
#ifdef ALLOW_STATUS
        printf("fond iss: start = %d end = %d\n",
               this->m_fondMarket->FeedChannel()->Isf()->MsgSeqNo(),
               this->m_fondMarket->FeedChannel()->Isf()->LastRecvMsgSeqNo());
#endif
        printf("------\n");
#ifdef ALLOW_STATISTICS
        printf("fond msr socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Msr()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Msr()->RecvBuffer()->CalcItemsUsagePercentage());
        printf("fond mss socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Mss()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Mss()->RecvBuffer()->CalcItemsUsagePercentage());
#endif


#ifdef ALLOW_TRADES
        printf("fond tlr socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Tlr()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Tlr()->RecvBuffer()->CalcItemsUsagePercentage());
        printf("fond tls socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Tls()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Tls()->RecvBuffer()->CalcItemsUsagePercentage());
#endif

#ifdef ALLOW_ORDERS
        printf("fond olr socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Olr()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Olr()->RecvBuffer()->CalcItemsUsagePercentage());
        printf("fond ols socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Ols()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Ols()->RecvBuffer()->CalcItemsUsagePercentage());
#endif


#ifdef ALLOW_STATUS
        printf("fond isf socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Isf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Isf()->RecvBuffer()->CalcItemsUsagePercentage());
#endif
    }

    inline void PrintStatisticsCurr() {

#ifdef ALLOW_ORDERS
//        if(this->m_currMarket->FeedChannel()->Ols()->State() == FeedConnectionState::fcsListenSnapshot) {
//            int currSnapshotSymbolsCount = this->m_currMarket->FeedChannel()->Olr()->OrderCurr()->SymbolsToRecvSnapshotCount();
//            int currQueEntries = this->m_currMarket->FeedChannel()->Olr()->OrderCurr()->QueueEntriesCount();
//            int msgSeqNumber = this->m_currMarket->FeedChannel()->Ols()->MsgSeqNo();
//            printf("curr olr: %d que entries and  %d snapshot symbols to go. msg = %d\n", currQueEntries, currSnapshotSymbolsCount, msgSeqNumber);
//        }
//        else {
//            printf("curr olr: start = %d end = %d\n",
//                   this->m_currMarket->FeedChannel()->Olr()->MsgSeqNo(),
//                   this->m_currMarket->FeedChannel()->Olr()->LastRecvMsgSeqNo());
//        }
#endif
#ifdef ALLOW_TRADES
//        if (this->m_currMarket->FeedChannel()->Tls()->State() == FeedConnectionState::fcsListenSnapshot) {
//            int foundSnapshotSymbolsCount = this->m_currMarket->FeedChannel()->Tlr()->TradeCurr()->SymbolsToRecvSnapshotCount();
//            int foundQueEntries = this->m_currMarket->FeedChannel()->Tlr()->TradeCurr()->QueueEntriesCount();
//            int msgSeqNumber = this->m_currMarket->FeedChannel()->Tls()->MsgSeqNo();
//            printf("curr tlr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
//        }
//        else {
//            printf("curr tlr: start = %d end = %d\n",
//                   this->m_currMarket->FeedChannel()->Tlr()->MsgSeqNo(),
//                   this->m_currMarket->FeedChannel()->Tlr()->LastRecvMsgSeqNo());
//        }
#endif
#ifdef ALLOW_STATISTICS
//        if (this->m_currMarket->FeedChannel()->Mss()->State() == FeedConnectionState::fcsListenSnapshot) {
//            int foundSnapshotSymbolsCount = this->m_currMarket->FeedChannel()->Msr()->StatisticCurr()->SymbolsToRecvSnapshotCount();
//            int foundQueEntries = this->m_currMarket->FeedChannel()->Msr()->StatisticCurr()->QueueEntriesCount();
//            int msgSeqNumber = this->m_currMarket->FeedChannel()->Mss()->MsgSeqNo();
//            int actual = this->m_currMarket->FeedChannel()->Msr()->StatisticCurr()->CalcActualQueueEntriesCount();
//            printf("curr msr: %d que entries and  %d snapshot symbols to go. actual que count = %d msg = %d\n",
//                   foundQueEntries,
//                   foundSnapshotSymbolsCount,
//                   actual,
//                   msgSeqNumber);
//            if(actual != foundQueEntries) {
//                printf("error!\n");
//            }
//        }
//        else {
//            printf("curr msr: start = %d end = %d\n",
//                   this->m_currMarket->FeedChannel()->Msr()->MsgSeqNo(),
//                   this->m_currMarket->FeedChannel()->Msr()->LastRecvMsgSeqNo());
//        }
#endif
        printf("------\n");
#ifdef ALLOW_STATUS
        printf("curr iss: start = %d end = %d\n",
               this->m_currMarket->FeedChannel()->Isf()->MsgSeqNo(),
               this->m_currMarket->FeedChannel()->Isf()->LastRecvMsgSeqNo());
#endif

#ifdef ALLOW_STATISTICS
        printf("mode = %s curr msr fast items usage = %g que items = %d snap symbols = %d mdentry_que count = %d socket buffer usage = %g item usage = %g start = %d end = %d window = %d\n",
               (this->m_currMarket->FeedChannel()->Msr()->Snapshot()->State() == FeedConnectionState::fcsListenSnapshot? "snapshot": "normal"),
               ((double)this->m_currMarket->FeedChannel()->Msr()->FastManager()->GetGenericItemInfoPool()->Count()) / (double)this->m_currMarket->FeedChannel()->Msr()->FastManager()->GetOLSCURRItemInfoPool()->Capacity() * 100.0,
               this->m_currMarket->FeedChannel()->Msr()->StatisticCurr()->QueueEntriesCount(),
               this->m_currMarket->FeedChannel()->Msr()->StatisticCurr()->SymbolsToRecvSnapshotCount(),
               MDEntryQueue::Pool->Count(),
               this->m_currMarket->FeedChannel()->Msr()->RecvBuffer()->CalcMemoryUsagePercentage(),
               this->m_currMarket->FeedChannel()->Msr()->RecvBuffer()->CalcItemsUsagePercentage(),
               this->m_currMarket->FeedChannel()->Msr()->MsgSeqNo(),
               this->m_currMarket->FeedChannel()->Msr()->LastRecvMsgSeqNo(),
               this->m_currMarket->FeedChannel()->Msr()->WindowMsgSeqNo()
        );
//        printf("curr mss socket buffer usage = %g item usage = %g\n",
//                   this->m_currMarket->FeedChannel()->Mss()->RecvBuffer()->CalcMemoryUsagePercentage(),
//                   this->m_currMarket->FeedChannel()->Mss()->RecvBuffer()->CalcItemsUsagePercentage());
#endif


#ifdef ALLOW_TRADES
        printf("curr tlr mode = %s tls items count = %d fast items usage = %g que items = %d snap symbols = %d mdentry_que count = %d socket buffer usage = %g item usage = %g start = %d end = %d window = %d \n",
               (this->m_currMarket->FeedChannel()->Tlr()->Snapshot()->State() == FeedConnectionState::fcsListenSnapshot? "snapshot": "normal"),
               DebugInfoManager::Default->CalcTradeCurrTotalEntriesCount(this->m_currMarket->FeedChannel()->Tlr()),
               ((double)this->m_currMarket->FeedChannel()->Tlr()->FastManager()->GetTLSCURRItemInfoPool()->Count()) / (double)this->m_currMarket->FeedChannel()->Tlr()->FastManager()->GetTLSCURRItemInfoPool()->Capacity() * 100.0,
               this->m_currMarket->FeedChannel()->Tlr()->TradeCurr()->QueueEntriesCount(),
               this->m_currMarket->FeedChannel()->Tlr()->TradeCurr()->SymbolsToRecvSnapshotCount(),
               MDEntryQueue::Pool->Count(),
               this->m_currMarket->FeedChannel()->Tlr()->RecvBuffer()->CalcMemoryUsagePercentage(),
               this->m_currMarket->FeedChannel()->Tlr()->RecvBuffer()->CalcItemsUsagePercentage(),
               this->m_currMarket->FeedChannel()->Tlr()->MsgSeqNo(),
               this->m_currMarket->FeedChannel()->Tlr()->LastRecvMsgSeqNo(),
               this->m_currMarket->FeedChannel()->Tlr()->WindowMsgSeqNo()
        );
//        printf("curr tls socket buffer usage = %g item usage = %g\n",
//                   this->m_currMarket->FeedChannel()->Tls()->RecvBuffer()->CalcMemoryUsagePercentage(),
//                   this->m_currMarket->FeedChannel()->Tls()->RecvBuffer()->CalcItemsUsagePercentage());
#endif

#ifdef ALLOW_ORDERS
        printf("curr olr mode = %s ols items count = %d fast items usage = %g que items = %d snap symbols = %d mdentry_que count = %d socket buffer usage = %g item usage = %g start = %d end = %d window = %d \n",
               (this->m_currMarket->FeedChannel()->Olr()->Snapshot()->State() == FeedConnectionState::fcsListenSnapshot? "snapshot": "normal"),
               DebugInfoManager::Default->CalcOrderCurrTotalEntriesCount(this->m_currMarket->FeedChannel()->Olr()),
               ((double)this->m_currMarket->FeedChannel()->Olr()->FastManager()->GetOLSCURRItemInfoPool()->Count()) / (double)this->m_currMarket->FeedChannel()->Olr()->FastManager()->GetOLSCURRItemInfoPool()->Capacity() * 100.0,
               this->m_currMarket->FeedChannel()->Olr()->OrderCurr()->QueueEntriesCount(),
               this->m_currMarket->FeedChannel()->Olr()->OrderCurr()->SymbolsToRecvSnapshotCount(),
               MDEntryQueue::Pool->Count(),
               this->m_currMarket->FeedChannel()->Olr()->RecvBuffer()->CalcMemoryUsagePercentage(),
               this->m_currMarket->FeedChannel()->Olr()->RecvBuffer()->CalcItemsUsagePercentage(),
               this->m_currMarket->FeedChannel()->Olr()->MsgSeqNo(),
               this->m_currMarket->FeedChannel()->Olr()->LastRecvMsgSeqNo(),
               this->m_currMarket->FeedChannel()->Olr()->WindowMsgSeqNo()
        );
//        printf("curr ols socket buffer usage = %g item usage = %g\n",
//                   this->m_currMarket->FeedChannel()->Ols()->RecvBuffer()->CalcMemoryUsagePercentage(),
//                   this->m_currMarket->FeedChannel()->Ols()->RecvBuffer()->CalcItemsUsagePercentage());
#endif


#ifdef ALLOW_STATUS
        printf("curr isf socket buffer usage = %g item usage = %g\n",
                   this->m_currMarket->FeedChannel()->Isf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_currMarket->FeedChannel()->Isf()->RecvBuffer()->CalcItemsUsagePercentage());
#endif
    }

    inline void PrintStatistics(int cycleCount, int elapsedSeconds) {
        double nanosecPerCycle = elapsedSeconds * 1000.0 * 1000.0 * 1000.0 / cycleCount;
        //printf("cycleCount for %d sec = %d. %g nanosec per cycle\n", elapsedSeconds, cycleCount, nanosecPerCycle);

        if(this->AllowFondMarket())
            this->PrintStatisticsFond();
        if(this->AllowCurrMarket())
            this->PrintStatisticsCurr();

        //printf("used queue count = %d\n", MDEntryQueue::Pool->Count());

//        printf("3 sec Changes------------------------\n");
//        ProgramStatistics::Current->Print();
//        printf("Total Changes-------------------------\n");
//        ProgramStatistics::Total->Print();
//        printf("--------------------------------------\n");


        ProgramStatistics::Current->Clear();
        //ProgramStatistics::Total->ResetFlags();
    }
};
