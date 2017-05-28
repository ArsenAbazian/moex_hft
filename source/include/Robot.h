#pragma once
#include "Feeds/AstsFeedChannel.h"
#include "Feeds/Forts/FortsFeedChannel.h"
#include "MarketInfo.h"
#include "Fix/FixProtocolManager.h"
#include "Managers/LogManager.h"
#include "ConnectionParameters.h"
#include "Managers/CommandManager.h"

#define MARKET_INFO_CAPACITY 16

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
class Robot {
    AstsFeedChannel *channels[MARKET_INFO_CAPACITY];
    int     channelsCount;

    MarketInfo *markets[MARKET_INFO_CAPACITY];
    int     marketCount;

    FortsFeedChannel        *m_fortsChannel;
    bool                    m_allowFortsFeeds[MarketDataGroupId::mdgidCount];

    MarketInfo              *m_currMarket;
    MarketInfo              *m_fondMarket;

    bool                    m_allowFondMarket;
    bool                    m_allowCurrMarket;
    bool                    m_allowFortsMarket;

    FixProtocolManager      *protocolManager;
    CommandManager          *m_commandManager;

    MarketInfo* FindMarket(const char* name) {
        for(int i = 0; i < this->marketCount; i++) {
            if(strcmp(this->markets[i]->Name(), name) == 0)
                return this->markets[i];
        }
        return NULL;
    }
    AstsFeedChannel *FindAstsFeedChannel(const char *id) {
        for(int i = 0; i < this->channelsCount; i++) {
            if(strcmp(this->channels[i]->Id(), id) == 0)
                return this->channels[i];
        }
        return NULL;
    }

    bool ConnectMarkets();
    bool DisconnectMarkets();
    bool DoWork();

    bool CollectSecurityDefinitionsAsts();
    bool CollectSecurityDefinitions_FondOnly();
    bool CollectSecurityDefinitions_CurrOnly();
    bool CollectSecurityDefinitionsForts();
    bool MainLoopAsts();
    bool MainLoop_FondOnly();
    bool MainLoop_CurrOnly();
    bool MainLoopForts();

    inline bool DoWorkAtom() {
#ifdef ALLOW_COMMAND_MANAGER
        if(!this->m_commandManager->DoWorkAtom())
            return false;
#endif
        return true;
    }
    inline bool Working() {
        return (this->m_allowCurrMarket && this->m_currMarket->Working()) ||
                (this->m_allowFondMarket && this->m_fondMarket->Working()) ||
                this->m_allowFortsMarket;
    }

public:
    Robot();
    ~Robot();

    inline bool AllowFondMarket() { return this->m_allowFondMarket; }
    inline void AllowFondMarket(bool value) { this->m_allowFondMarket = value; }
    inline bool AllowCurrMarket() { return this->m_allowCurrMarket; }
    inline void AllowCurrMarket(bool value) { this->m_allowCurrMarket = value; }
    inline bool AllowFortsMarket() { return this->m_allowFortsMarket; }
    inline void AllowFortsMarket(bool value) { this->m_allowFortsMarket = value; }

    inline bool AllowMarketDataGroup(MarketDataGroupId id) { return this->m_allowFortsFeeds[id]; }
    inline void AllowMarketDataGroup(MarketDataGroupId id, bool value) { this->m_allowFortsFeeds[id] = value; }
    inline void AllowFutures(bool value) { 
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidFutBook1] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidFutBook5] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidFutBook20] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidFutBook50] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidFutTrades] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidFutInfo] = value;
    }
    inline void AllowOptions(bool value) {
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOptBook1] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOptBook5] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOptBook20] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOptBook50] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOptTrades] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOptInfo] = value;
    }
    inline void AllowNews(bool value) {
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidIndex] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidNews] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidNewsSkrin] = value;
    }
    inline void AllowOtc(bool value) {
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOtcIssues] = value;
        this->m_allowFortsFeeds[MarketDataGroupId::mdgidOtcTrades] = value;
    }

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

    void AddChannel(AstsFeedChannel *info) {
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
            AstsFeedChannel *fondChannel = FindAstsFeedChannel("FOND");
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
            AstsFeedChannel *currChannel = FindAstsFeedChannel("CURR");
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

    inline AstsFeedChannel **Channels() { return (AstsFeedChannel**)this->channels; }
    inline int ChannelCount() { return this->channelsCount; }

    inline FortsFeedChannel *FortsChannel() { return this->m_fortsChannel; }

    inline MarketInfo **Markets() { return (MarketInfo**)this->markets; }
    inline int MarketCount() { return this->marketCount; }

    bool Run();

    inline void PrintSnapFeedStatistics(const char *name, FeedConnection *fc) {
        printf("%-22s   bu = %4.4g%%  lost = %6d  msgSeqNo = %7d\n",
               name,
               fc->CalcRecvMemoryUsagePercentage(),
               fc->LostPacketCount(),
               fc->MsgSeqNo()
        );
    }

    inline void PrintIncFeedStatistics(const char *name, FeedConnection *fc, int usedItemsCount, int totalItemsCount) {
        bool inSnapshot = fc->Snapshot()->State() == FeedConnectionState::fcsListenSnapshot;
        printf("%-22s   state = %-4s  it = %7d of %7d %4.4g%%  que = %3d  ss = %4d  bu = %4.4g%%  msgSeqNo = %7d\n",
               name,
               inSnapshot? "snap" : "inc",
               usedItemsCount, totalItemsCount, 100.0 * usedItemsCount / totalItemsCount,
               fc->QueueEntriesCount(),
               fc->SymbolsToRecvSnapshotCount(),
               fc->CalcRecvMemoryUsagePercentage(),
               fc->MsgSeqNo()
        );
    }

    inline void PrintStatusFeedStatistics(const char *name, FeedConnection *fc, int usedItemsCount, int totalItemsCount) {
        bool inSnapshot = fc->SecurityDefinition()->State() == FeedConnectionState::fcsListenSecurityDefinition;
        printf("%-22s   state = %-4s  it = %7d of %7d %4.4g%%  que = %3d  ss = %4d  bu = %4.4g%%  msgSeqNo = %7d\n",
               name,
               inSnapshot? "snap" : "inc",
               usedItemsCount, totalItemsCount, 100.0 * usedItemsCount / totalItemsCount,
               fc->QueueEntriesCount(),
               fc->SymbolsToRecvSnapshotCount(),
               fc->CalcRecvMemoryUsagePercentage(),
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
        this->PrintStatusFeedStatistics("curr isf", this->m_fondMarket->FeedChannel()->Isf(),
                                        this->m_fondMarket->FeedChannel()->Isf()->FastManager()->GetAstsSecurityStatusInfoPool()->Count(),
                                        this->m_fondMarket->FeedChannel()->Isf()->FastManager()->GetAstsSecurityStatusInfoPool()->Capacity());
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
        this->PrintStatusFeedStatistics("curr isf", this->m_currMarket->FeedChannel()->Isf(),
                                        this->m_currMarket->FeedChannel()->Isf()->FastManager()->GetAstsSecurityStatusInfoPool()->Count(),
                                        this->m_currMarket->FeedChannel()->Isf()->FastManager()->GetAstsSecurityStatusInfoPool()->Capacity());
#endif
    }

    inline void PrintStatisticsForts() {
        printf("------\n");
        if(this->m_fortsChannel->FutBook1() != 0) {
            this->PrintIncFeedStatistics("fut book 1", this->m_fortsChannel->FutBook1()->Inc(),
            this->m_fortsChannel->FutBook1()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
            this->m_fortsChannel->FutBook1()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->FutBook5() != 0) {
            this->PrintIncFeedStatistics("fut book 5", this->m_fortsChannel->FutBook5()->Inc(),
                                         this->m_fortsChannel->FutBook5()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->FutBook5()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->FutBook20() != 0) {
            this->PrintIncFeedStatistics("fut book 20", this->m_fortsChannel->FutBook20()->Inc(),
                                         this->m_fortsChannel->FutBook20()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->FutBook20()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->FutBook50() != 0) {
            this->PrintIncFeedStatistics("fut book 50", this->m_fortsChannel->FutBook50()->Inc(),
                                         this->m_fortsChannel->FutBook50()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->FutBook50()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->FutTrades() != 0) {
            this->PrintIncFeedStatistics("fut book trades", this->m_fortsChannel->FutTrades()->Inc(),
                                         this->m_fortsChannel->FutTrades()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->FutTrades()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }

        if(this->m_fortsChannel->OptBook1() != 0) {
            this->PrintIncFeedStatistics("opt book 1", this->m_fortsChannel->OptBook1()->Inc(),
                                         this->m_fortsChannel->OptBook1()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->OptBook1()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->OptBook5() != 0) {
            this->PrintIncFeedStatistics("opt book 5", this->m_fortsChannel->OptBook5()->Inc(),
                                         this->m_fortsChannel->OptBook5()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->OptBook5()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->OptBook20() != 0) {
            this->PrintIncFeedStatistics("opt book 20", this->m_fortsChannel->OptBook20()->Inc(),
                                         this->m_fortsChannel->OptBook20()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->OptBook20()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->OptBook50() != 0) {
            this->PrintIncFeedStatistics("opt book 50", this->m_fortsChannel->OptBook50()->Inc(),
                                         this->m_fortsChannel->OptBook50()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->OptBook50()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->OptTrades() != 0) {
            this->PrintIncFeedStatistics("opt book trades", this->m_fortsChannel->OptTrades()->Inc(),
                                         this->m_fortsChannel->OptTrades()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Count(),
                                         this->m_fortsChannel->OptTrades()->Inc()->FastManager()->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool()->Capacity());
        }
        printf("\n");
        if(this->m_fortsChannel->FutInfo() !=0 ) {
            this->PrintStatusFeedStatistics("fut status", this->m_fortsChannel->FutInfo()->InstrInc(),
                                            this->m_fortsChannel->FutInfo()->InstrInc()->FastManager()->GetFortsTradingSessionStatusInfoPool()->Count(),
                                            this->m_fortsChannel->FutInfo()->InstrInc()->FastManager()->GetFortsTradingSessionStatusInfoPool()->Capacity());
        }
        if(this->m_fortsChannel->FutInfo() !=0 ) {
            this->PrintStatusFeedStatistics("opt status", this->m_fortsChannel->FutInfo()->InstrInc(),
                                            this->m_fortsChannel->OptInfo()->InstrInc()->FastManager()->GetFortsTradingSessionStatusInfoPool()->Count(),
                                            this->m_fortsChannel->OptInfo()->InstrInc()->FastManager()->GetFortsTradingSessionStatusInfoPool()->Capacity());
        }

        printf("\n");
        if(this->m_fortsChannel->FutInfo() !=0 ) {
            this->PrintSnapFeedStatistics("fut info", this->m_fortsChannel->FutInfo()->InstrReplay());
        }
        if(this->m_fortsChannel->FutInfo() !=0 ) {
            this->PrintSnapFeedStatistics("opt info", this->m_fortsChannel->FutInfo()->InstrReplay());
        }

        printf("\n");

        if(this->m_fortsChannel->OptTrades() != 0) {
            this->PrintSnapFeedStatistics("opt book trades snap", this->m_fortsChannel->OptTrades()->Snap());
        }
        if(this->m_fortsChannel->FutBook1() != 0) {
            this->PrintSnapFeedStatistics("fut book 1 snap", this->m_fortsChannel->FutBook1()->Snap());
        }
        if(this->m_fortsChannel->FutBook5() != 0) {
            this->PrintSnapFeedStatistics("fut book 5 snap", this->m_fortsChannel->FutBook5()->Snap());
        }
        if(this->m_fortsChannel->FutBook20() != 0) {
            this->PrintSnapFeedStatistics("fut book 20 snap", this->m_fortsChannel->FutBook20()->Snap());
        }
        if(this->m_fortsChannel->FutBook50() != 0) {
            this->PrintSnapFeedStatistics("fut book 50 snap", this->m_fortsChannel->FutBook50()->Snap());
        }
        if(this->m_fortsChannel->FutTrades() != 0) {
            this->PrintSnapFeedStatistics("fut book trades snap", this->m_fortsChannel->FutTrades()->Snap());
        }

        if(this->m_fortsChannel->OptBook1() != 0) {
            this->PrintSnapFeedStatistics("opt book 1 snap", this->m_fortsChannel->OptBook1()->Snap());
        }
        if(this->m_fortsChannel->OptBook5() != 0) {
            this->PrintSnapFeedStatistics("opt book 5 snap", this->m_fortsChannel->OptBook5()->Snap());
        }
        if(this->m_fortsChannel->OptBook20() != 0) {
            this->PrintSnapFeedStatistics("opt book 20 snap", this->m_fortsChannel->OptBook20()->Snap());
        }
        if(this->m_fortsChannel->OptBook50() != 0) {
            this->PrintSnapFeedStatistics("opt book 50 snap", this->m_fortsChannel->OptBook50()->Snap());
        }
        if(this->m_fortsChannel->OptTrades() != 0) {
            this->PrintSnapFeedStatistics("opt book trades snap", this->m_fortsChannel->OptTrades()->Snap());
        }
        
    }

    inline void PrintStatistics() {
        if(this->AllowFondMarket())
            this->PrintStatisticsFond();
        if(this->AllowCurrMarket())
            this->PrintStatisticsCurr();
        if(this->AllowFortsMarket())
            this->PrintStatisticsForts();
    }
};
#pragma clang diagnostic pop
