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

    inline void PrintSnapFeedStatistics(const char *name, FeedConnection *fc) {
        printf("%s   buffer usage %g  buffer items usage %g  msgSeqNo = %d\n",
               name,
               fc->RecvBuffer()->CalcMemoryUsagePercentage(),
               fc->RecvBuffer()->CalcItemsUsagePercentage(),
               fc->MsgSeqNo()
        );
    }

    inline void PrintIncFeedStatistics(const char *name, FeedConnection *fc, int usedItemsCount, int totalItemsCount) {
        bool inSnapshot = fc->Snapshot()->State() == FeedConnectionState::fcsListenSnapshot;
        printf("%s   state = %s  items used = %d of %d %g%%  que_entries_count = %d  snapshot symbols %d  buffer usage %g  buffer items usage %g  msgSeqNo = %d\n",
               name,
               inSnapshot? "snap" : "inc",
               usedItemsCount, totalItemsCount, 100.0 * usedItemsCount / totalItemsCount,
               fc->QueueEntriesCount(),
               fc->SymbolsToRecvSnapshotCount(),
               fc->RecvBuffer()->CalcMemoryUsagePercentage(),
               fc->RecvBuffer()->CalcItemsUsagePercentage(),
               fc->MsgSeqNo()
        );
    }

    inline void PrintStatisticsFond() {
        printf("------\n");
#ifdef ALLOW_ORDERS
        this->PrintIncFeedStatistics("fond olr", this->m_fondMarket->FeedChannel()->Olr(),
                                     this->m_fondMarket->FeedChannel()->Olr()->FastManager()->GetAstsOLSFONDItemInfoPool()->Count(),
                                     this->m_fondMarket->FeedChannel()->Olr()->FastManager()->GetAstsOLSFONDItemInfoPool()->Capacity());
#endif

#ifdef ALLOW_STATISTICS
        this->PrintIncFeedStatistics("fond msr", this->m_fondMarket->FeedChannel()->Msr(),
                                     this->m_fondMarket->FeedChannel()->Msr()->FastManager()->GetAstsGenericItemInfoPool()->Count(),
                                     this->m_fondMarket->FeedChannel()->Msr()->FastManager()->GetAstsGenericItemInfoPool()->Capacity());
#endif


#ifdef ALLOW_TRADES
        this->PrintIncFeedStatistics("fond tlr", this->m_fondMarket->FeedChannel()->Tlr(),
                                     this->m_fondMarket->FeedChannel()->Tlr()->FastManager()->GetAstsTLSFONDItemInfoPool()->Count(),
                                     this->m_fondMarket->FeedChannel()->Tlr()->FastManager()->GetAstsTLSFONDItemInfoPool()->Capacity());
#endif

#ifdef ALLOW_ORDERS
        this->PrintSnapFeedStatistics("fond ols", this->m_fondMarket->FeedChannel()->Ols());
#endif

#ifdef ALLOW_STATISTICS
        this->PrintSnapFeedStatistics("fond mss", this->m_fondMarket->FeedChannel()->Mss());
#endif


#ifdef ALLOW_TRADES
        this->PrintSnapFeedStatistics("fond tls", this->m_fondMarket->FeedChannel()->Tls());
#endif

#ifdef ALLOW_STATUS
        printf("fond isf socket buffer usage = %g item usage = %g\n",
                   this->m_fondMarket->FeedChannel()->Isf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_fondMarket->FeedChannel()->Isf()->RecvBuffer()->CalcItemsUsagePercentage());
#endif
    }

    inline void PrintStatisticsCurr() {
        printf("------\n");
#ifdef ALLOW_ORDERS
        this->PrintIncFeedStatistics("curr olr", this->m_currMarket->FeedChannel()->Olr(),
            this->m_currMarket->FeedChannel()->Olr()->FastManager()->GetAstsOLSCURRItemInfoPool()->Count(),
            this->m_currMarket->FeedChannel()->Olr()->FastManager()->GetAstsOLSCURRItemInfoPool()->Capacity());
#endif

#ifdef ALLOW_STATISTICS
        this->PrintIncFeedStatistics("curr msr", this->m_currMarket->FeedChannel()->Msr(),
            this->m_currMarket->FeedChannel()->Msr()->FastManager()->GetAstsGenericItemInfoPool()->Count(),
            this->m_currMarket->FeedChannel()->Msr()->FastManager()->GetAstsGenericItemInfoPool()->Capacity());
#endif


#ifdef ALLOW_TRADES
        this->PrintIncFeedStatistics("curr tlr", this->m_currMarket->FeedChannel()->Tlr(),
            this->m_currMarket->FeedChannel()->Tlr()->FastManager()->GetAstsTLSCURRItemInfoPool()->Count(),
            this->m_currMarket->FeedChannel()->Tlr()->FastManager()->GetAstsTLSCURRItemInfoPool()->Capacity());
#endif

#ifdef ALLOW_ORDERS
        this->PrintSnapFeedStatistics("curr ols", this->m_currMarket->FeedChannel()->Ols());
#endif

#ifdef ALLOW_STATISTICS
        this->PrintSnapFeedStatistics("curr mss", this->m_currMarket->FeedChannel()->Mss());
#endif


#ifdef ALLOW_TRADES
        this->PrintSnapFeedStatistics("curr tls", this->m_currMarket->FeedChannel()->Tls());
#endif

#ifdef ALLOW_STATUS
        printf("curr isf socket buffer usage = %g item usage = %g\n",
                   this->m_currMarket->FeedChannel()->Isf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                   this->m_currMarket->FeedChannel()->Isf()->RecvBuffer()->CalcItemsUsagePercentage());
#endif
    }

    inline void PrintStatistics() {
        if(this->AllowFondMarket())
            this->PrintStatisticsFond();
        if(this->AllowCurrMarket())
            this->PrintStatisticsCurr();
    }
};
