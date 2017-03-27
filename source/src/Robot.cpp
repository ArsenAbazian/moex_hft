#include "Robot.h"
#include "AstsFeedChannel.h"
#include <cstdio>
#include "ProgramStatistics.h"
#include "Feeds/Forts/FortsFeeds.h"

Robot::Robot() {
	this->channelsCount = 0;
	memset(this->channels, 0, sizeof(AstsFeedChannel*) * MARKET_INFO_CAPACITY);
    this->m_allowCurrMarket = true;
    this->m_allowFondMarket = true;
    for(int i = 0; i < MarketDataGroupId::mdgidCount; i++)
        this->m_allowFortsFeeds[i] = false;
}

Robot::~Robot() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_Robot);

    bool result = DisconnectMarkets();
	delete this->protocolManager;

    DefaultLogManager::Default->EndLog(result);
}

bool Robot::ConnectMarkets() {
	
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_ConnectMarkets);
	for (int i = 0; i < this->marketCount; i++) {
		if (!this->markets[i]->Connect()) {
			DefaultLogManager::Default->EndLog(false);
#ifdef ROBOT_WORK_ANYWAY
            continue;
#else
			return false;
#endif
		}
	}

    if(this->AllowFortsMarket())
        this->FortsChannel()->Prepare();

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool Robot::DisconnectMarkets() {
	bool success = true;
	for (int i = 0; i < this->marketCount; i++) {
		success &= this->markets[i]->Disconnect();
	}
	return success;
}

bool Robot::AddDefaultTestChannels() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_AddDefaultTestChannels);
#pragma region Asts_AddDefaultChannels_GeneratedCode
	if(this->AllowCurrMarket()) {
		AstsFeedChannel *curr = new AstsFeedChannel("CURR", "Currency Exchange Market");

		if(this->AllowFeed("MSR")) {
			FeedConnection *msr_curr = new FeedConnection_CURR_MSR("MSR", "Statisctics Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.7", 9027, "10.50.129.200", "239.192.112.135", 9227);
			curr->SetConnection(msr_curr);
		}
		if(this->AllowFeed("MSS")) {
			FeedConnection *mss_curr = new FeedConnection_CURR_MSS("MSS", "Statisctics Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.8", 9028, "10.50.129.200", "239.192.112.136", 9228);
			curr->SetConnection(mss_curr);
		}
		if(this->AllowFeed("OLR")) {
			FeedConnection *olr_curr = new FeedConnection_CURR_OLR("OLR", "Orders Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.1", 9021, "10.50.129.200", "239.192.112.129", 9221);
			curr->SetConnection(olr_curr);
		}
		if(this->AllowFeed("OLS")) {
			FeedConnection *ols_curr = new FeedConnection_CURR_OLS("OLS", "Orders Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.2", 9022, "10.50.129.200", "239.192.112.130", 9222);
			curr->SetConnection(ols_curr);
		}
		if(this->AllowFeed("TLR")) {
			FeedConnection *tlr_curr = new FeedConnection_CURR_TLR("TLR", "Trades Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.5", 9025, "10.50.129.200", "239.192.112.133", 9225);
			curr->SetConnection(tlr_curr);
		}
		if(this->AllowFeed("TLS")) {
			FeedConnection *tls_curr = new FeedConnection_CURR_TLS("TLS", "Trades Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.6", 9026, "10.50.129.200", "239.192.112.134", 9226);
			curr->SetConnection(tls_curr);
		}
		if(this->AllowFeed("IDF")) {
			FeedConnection *idf_curr = new FeedConnection_CURR_IDF("IDF", "Instrument Replay", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.9", 9029, "10.50.129.200", "239.192.112.137", 9229);
			curr->SetConnection(idf_curr);
		}
		if(this->AllowFeed("ISF")) {
			FeedConnection *isf_curr = new FeedConnection_CURR_ISF("ISF", "Instrument Status", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.10", 9030, "10.50.129.200", "239.192.112.138", 9230);
			curr->SetConnection(isf_curr);
		}
		if(this->AllowFeed("H")) {
			FeedConnection *h_curr = new FeedConnection_CURR_H("H", "Historical Replay", 'H', FeedConnectionProtocol::TCP_IP, "1.1.7.200", 20000);
			curr->SetConnection(h_curr);
		}

		this->AddChannel(curr);
	}
	if(this->AllowFondMarket()) {
		AstsFeedChannel *fond = new AstsFeedChannel("FOND", "Stock Exchange Market");

		if(this->AllowFeed("MSR")) {
			FeedConnection *msr_fond = new FeedConnection_FOND_MSR("MSR", "Statisctics Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.7", 9117, "10.50.129.200", "239.192.113.135", 9317);
			fond->SetConnection(msr_fond);
		}
		if(this->AllowFeed("MSS")) {
			FeedConnection *mss_fond = new FeedConnection_FOND_MSS("MSS", "Statisctics Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.8", 9118, "10.50.129.200", "239.192.113.136", 9318);
			fond->SetConnection(mss_fond);
		}
		if(this->AllowFeed("OLR")) {
			FeedConnection *olr_fond = new FeedConnection_FOND_OLR("OLR", "Orders Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.1", 9111, "10.50.129.200", "239.192.113.129", 9311);
			fond->SetConnection(olr_fond);
		}
		if(this->AllowFeed("OLS")) {
			FeedConnection *ols_fond = new FeedConnection_FOND_OLS("OLS", "Orders Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.2", 9112, "10.50.129.200", "239.192.113.130", 9312);
			fond->SetConnection(ols_fond);
		}
		if(this->AllowFeed("TLR")) {
			FeedConnection *tlr_fond = new FeedConnection_FOND_TLR("TLR", "Trades Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.5", 9115, "10.50.129.200", "239.192.113.133", 9315);
			fond->SetConnection(tlr_fond);
		}
		if(this->AllowFeed("TLS")) {
			FeedConnection *tls_fond = new FeedConnection_FOND_TLS("TLS", "Trades Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.6", 9116, "10.50.129.200", "239.192.113.134", 9316);
			fond->SetConnection(tls_fond);
		}
		if(this->AllowFeed("IDF")) {
			FeedConnection *idf_fond = new FeedConnection_FOND_IDF("IDF", "Instrument Replay", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.9", 9119, "10.50.129.200", "239.192.113.137", 9319);
			fond->SetConnection(idf_fond);
		}
		if(this->AllowFeed("ISF")) {
			FeedConnection *isf_fond = new FeedConnection_FOND_ISF("ISF", "Instrument Status", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.10", 9120, "10.50.129.200", "239.192.113.138", 9320);
			fond->SetConnection(isf_fond);
		}
		if(this->AllowFeed("H")) {
			FeedConnection *h_fond = new FeedConnection_FOND_H("H", "Historical Replay", 'H', FeedConnectionProtocol::TCP_IP, "1.1.7.200", 10000);
			fond->SetConnection(h_fond);
		}

		this->AddChannel(fond);
	}
#pragma endregion

#pragma region Forts_AddDefaultChannels_GeneratedCode
	if(this->AllowFortsMarket()) {
		FortsFeedChannel *channel = new FortsFeedChannel();
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook1)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidFutBook1, "F", 1, "Top of book for Futures");
			group->Inc( new FeedConnection_FORTS_OBR("FUT-BOOK-1 Inc", "Top of book for Futures Incremental", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.1", 40001, "10.50.129.90", "239.192.175.1", 41001) );
			group->Snap( new FeedConnection_FORTS_SNAP("FUT-BOOK-1 Snap", "Top of book for Futures Snapshot", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.2", 40002, "10.50.129.90", "239.192.175.2", 41002) );
			channel->FutBook1(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook5)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidFutBook5, "F", 5, "Top 5 Price Levels for Futures");
			group->Inc( new FeedConnection_FORTS_OBR("FUT-BOOK-5 Inc", "Top 5 Price Levels for Futures Incremental", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.3", 40003, "10.50.129.90", "239.192.175.3", 41003) );
			group->Snap( new FeedConnection_FORTS_SNAP("FUT-BOOK-5 Snap", "Top 5 Price Levels for Futures Snapshot", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.4", 40004, "10.50.129.90", "239.192.175.4", 41004) );
			channel->FutBook5(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook20)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidFutBook20, "F", 20, "Top 20 Price Levels for Futures");
			group->Inc( new FeedConnection_FORTS_OBR("FUT-BOOK-20 Inc", "Top 20 Price Levels for Futures Incremental", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.5", 40005, "10.50.129.90", "239.192.175.5", 41005) );
			group->Snap( new FeedConnection_FORTS_SNAP("FUT-BOOK-20 Snap", "Top 20 Price Levels for Futures Snapshot", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.6", 40006, "10.50.129.90", "239.192.175.6", 41006) );
			channel->FutBook20(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidFutBook50)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidFutBook50, "F", 50, "Top 50 Price Levels for Futures");
			group->Inc( new FeedConnection_FORTS_OBR("FUT-BOOK-50 Inc", "Top 50 Price Levels for Futures Incremental", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.7", 40007, "10.50.129.90", "239.192.175.7", 41007) );
			group->Snap( new FeedConnection_FORTS_SNAP("FUT-BOOK-50 Snap", "Top 50 Price Levels for Futures Snapshot", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.8", 40008, "10.50.129.90", "239.192.175.8", 41008) );
			channel->FutBook50(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidFutTrades)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidFutTrades, "F", 0, "Trades for Futures");
			group->Inc( new FeedConnection_FORTS_TLR("FUT-TRADES Inc", "Trades for Futures Incremental", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.9", 40009, "10.50.129.90", "239.192.175.9", 41009) );
			group->Snap( new FeedConnection_FORTS_SNAP("FUT-TRADES Snap", "Trades for Futures Snapshot", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.10", 40010, "10.50.129.90", "239.192.175.10", 41010) );
			channel->FutTrades(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidFutInfo)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidFutInfo, "F", 0, "Futures defintion");
			group->InstrInc( new FeedConnection_FORTS_INSTR_INC("FUT-INFO Instrument Incremetnal", "Futures defintion", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.12", 40012, "10.50.129.90", "239.192.175.12", 41012) );
			group->InstrReplay( new FeedConnection_FORTS_INSTR_SNAP("FUT-INFO Instrument Replay", "Futures defintion", 'F', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.11", 40011, "10.50.129.90", "239.192.175.11", 41011) );
			channel->FutInfo(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidIndex)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidIndex, "I", 0, "Indexes");
			group->Inc( new FeedConnection_FORTS_INDEX("INDEX Inc", "Indexes Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.13", 40013, "10.50.129.90", "239.192.175.13", 41013) );
			group->Snap( new FeedConnection_FORTS_SNAP("INDEX Snap", "Indexes Snapshot", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.14", 40014, "10.50.129.90", "239.192.175.14", 41014) );
			channel->Index(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidNews)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidNews, "N", 0, "News feed");
			group->Inc( new FeedConnection_FORTS_NEWS("NEWS Inc", "News feed Incremental", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.15", 40015, "10.50.129.90", "239.192.175.15", 41015) );
			channel->News(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidNewsSkrin)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidNewsSkrin, "N", 0, "SKRIN News feed");
			group->Inc( new FeedConnection_FORTS_NEWS_SKRIN("NEWS-SKRIN Inc", "SKRIN News feed Incremental", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.16", 40016, "10.50.129.90", "239.192.175.16", 41016) );
			channel->NewsSkrin(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook1)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOptBook1, "O", 1, "Top of book for Options");
			group->Inc( new FeedConnection_FORTS_OBR("OPT-BOOK-1 Inc", "Top of book for Options Incremental", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.17", 40017, "10.50.129.90", "239.192.175.17", 41017) );
			group->Snap( new FeedConnection_FORTS_SNAP("OPT-BOOK-1 Snap", "Top of book for Options Snapshot", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.18", 40018, "10.50.129.90", "239.192.175.18", 41018) );
			channel->OptBook1(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook5)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOptBook5, "O", 5, "Top 5 Price Levels for Options");
			group->Inc( new FeedConnection_FORTS_OBR("OPT-BOOK-5 Inc", "Top 5 Price Levels for Options Incremental", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.19", 40019, "10.50.129.90", "239.192.175.19", 41019) );
			group->Snap( new FeedConnection_FORTS_SNAP("OPT-BOOK-5 Snap", "Top 5 Price Levels for Options Snapshot", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.20", 40020, "10.50.129.90", "239.192.175.20", 41020) );
			channel->OptBook5(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook20)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOptBook20, "O", 20, "Top 20 Price Levels for Options");
			group->Inc( new FeedConnection_FORTS_OBR("OPT-BOOK-20 Inc", "Top 20 Price Levels for Options Incremental", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.21", 40021, "10.50.129.90", "239.192.175.21", 41021) );
			group->Snap( new FeedConnection_FORTS_SNAP("OPT-BOOK-20 Snap", "Top 20 Price Levels for Options Snapshot", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.22", 40022, "10.50.129.90", "239.192.175.22", 41022) );
			channel->OptBook20(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOptBook50)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOptBook50, "O", 50, "Top 50 Price Levels for Options");
			group->Inc( new FeedConnection_FORTS_OBR("OPT-BOOK-50 Inc", "Top 50 Price Levels for Options Incremental", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.23", 40023, "10.50.129.90", "239.192.175.23", 41023) );
			group->Snap( new FeedConnection_FORTS_SNAP("OPT-BOOK-50 Snap", "Top 50 Price Levels for Options Snapshot", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.24", 40024, "10.50.129.90", "239.192.175.24", 41024) );
			channel->OptBook50(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOptTrades)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOptTrades, "O", 0, "Trades for Options");
			group->Inc( new FeedConnection_FORTS_TLR("OPT-TRADES Inc", "Trades for Options Incremental", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.25", 40025, "10.50.129.90", "239.192.175.25", 41025) );
			group->Snap( new FeedConnection_FORTS_SNAP("OPT-TRADES Snap", "Trades for Options Snapshot", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.26", 40026, "10.50.129.90", "239.192.175.26", 41026) );
			channel->OptTrades(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOptInfo)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOptInfo, "O", 0, "Options defintion");
			group->InstrInc( new FeedConnection_FORTS_INSTR_INC("OPT-INFO Instrument Incremetnal", "Options defintion", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.28", 40028, "10.50.129.90", "239.192.175.28", 41028) );
			group->InstrReplay( new FeedConnection_FORTS_INSTR_SNAP("OPT-INFO Instrument Replay", "Options defintion", 'O', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.27", 40027, "10.50.129.90", "239.192.175.27", 41027) );
			channel->OptInfo(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOtcTrades)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOtcTrades, "Q", 0, "Trades for OTC");
			group->Inc( new FeedConnection_FORTS_TLR("OTC-TRADES Inc", "Trades for OTC Incremental", 'Q', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.29", 40029, "10.50.129.90", "239.192.175.29", 41029) );
			group->Snap( new FeedConnection_FORTS_SNAP("OTC-TRADES Snap", "Trades for OTC Snapshot", 'Q', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.30", 40030, "10.50.129.90", "239.192.175.30", 41030) );
			channel->OtcTrades(group);
		}
		if(this->AllowMarketDataGroup(MarketDataGroupId::mdgidOtcIssues)) {
			FortsMarketDataGroup *group = new FortsMarketDataGroup(MarketDataGroupId::mdgidOtcIssues, "Q", 0, "OTC Issues feed");
			group->InstrReplay( new FeedConnection_FORTS_INSTR_SNAP("OTC-ISSUES Instrument Replay", "OTC Issues feed", 'Q', FeedConnectionProtocol::UDP_IP, "10.50.129.90", "239.192.70.31", 40031, "10.50.129.90", "239.192.175.31", 41031) );
			channel->OtcIssues(group);
		}
		this->m_fortsChannel = channel;
	}
#pragma endregion

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::Run() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_Run);
	
	if(!this->AddDefaultTestMarkets()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if(!this->AddDefaultTestChannels()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

    if(!this->SetFeedChannelsForMarkets()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    if(!this->ConnectMarkets()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    if(!this->DoWork()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool Robot::CollectSecurityDefinitions_FondOnly() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitions);

    if(!this->m_fondMarket->FeedChannel()->Idf()->LoadSecurityDefinitions()) {
        if(!this->m_fondMarket->FeedChannel()->Idf()->Start()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        // collect data first
        while (true) {
            if (!WinSockManager::UpdateManagersPollStatus())
                break;

            if (!this->m_fondMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if (this->m_fondMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_fondMarket->FeedChannel()->Idf()->Stop();
                break;
            }

            if (w->ElapsedMilliseconds() > 1000) {
                w->Reset();

                double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
                printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);

                printf("Changes------------------------\n");
                ProgramStatistics::Current->Print();
                printf("Total---------------------------------\n");
                ProgramStatistics::Total->Print();
                printf("--------------------------------------\n");

                cycleCount = 0;
                ProgramStatistics::Current->Clear();
                //ProgramStatistics::Total->ResetFlags();
            }
            cycleCount++;
        }
    }
    DefaultLogManager::Default->EndLog(true);
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitions);
    this->m_fondMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    if(!this->m_fondMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::CollectSecurityDefinitions_CurrOnly() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitions);
    if(!this->m_currMarket->FeedChannel()->Idf()->LoadSecurityDefinitions()) {
        if(!this->m_currMarket->FeedChannel()->Idf()->Start()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        // collect data first
        while (true) {
            if (!WinSockManager::UpdateManagersPollStatus())
                break;
            if (!this->m_currMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if (this->m_currMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_currMarket->FeedChannel()->Idf()->Stop();
                break;
            }

            if (w->ElapsedMilliseconds() > 1000) {
                w->Reset();

                double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
                printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);

                printf("Changes------------------------\n");
                ProgramStatistics::Current->Print();
                printf("Total---------------------------------\n");
                ProgramStatistics::Total->Print();
                printf("--------------------------------------\n");

                cycleCount = 0;
                ProgramStatistics::Current->Clear();
                //ProgramStatistics::Total->ResetFlags();
            }
            cycleCount++;
        }
    }
    DefaultLogManager::Default->EndLog(true);

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitions);
    this->m_currMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    if(!this->m_currMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::CollectSecurityDefinitionsForts() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitionsForts);
    bool collectedFutures = false;
    bool collectedOptions = false;

    if(!this->m_fortsChannel->AllowFutures())
        collectedFutures = true;
    else if (this->m_fortsChannel->LoadSecurityDefinitionFutures())
        collectedFutures = true;

    if(!this->m_fortsChannel->AllowOptions())
        collectedOptions = true;
    else if (this->m_fortsChannel->LoadSecurityDefinitionOptions())
        collectedOptions = true;

    if(!collectedFutures && !this->m_fortsChannel->FutInfo()->InstrReplay()->Start()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!collectedOptions && !this->m_fortsChannel->OptInfo()->InstrReplay()->Start()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!collectedFutures) {
            if(!this->m_fortsChannel->FutInfo()->InstrReplay()->DoWorkAtom()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(this->m_fortsChannel->FutInfo()->InstrReplay()->IsIdfDataCollected()) {
                this->m_fortsChannel->FutInfo()->InstrReplay()->Stop();
                collectedFutures = true;
            }
        }
        if(!collectedOptions) {
            if(!this->m_fortsChannel->OptInfo()->InstrReplay()->DoWorkAtom()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(this->m_fortsChannel->OptInfo()->InstrReplay()->IsIdfDataCollected()) {
                this->m_fortsChannel->OptInfo()->InstrReplay()->Stop();
                collectedOptions = true;
            }
        }
        if(collectedFutures && collectedOptions)
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            w->Reset();

            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);
            printf("process future idf %d of %d\n",
                   this->m_fortsChannel->FutInfo()->InstrReplay()->LastRecvMsgSeqNo(),
                   this->m_fortsChannel->FutInfo()->InstrReplay()->TotalNumReports()
            );
            printf("process options idf %d of %d\n",
                   this->m_fortsChannel->OptInfo()->InstrReplay()->LastRecvMsgSeqNo(),
                   this->m_fortsChannel->OptInfo()->InstrReplay()->TotalNumReports()
            );

            cycleCount = 0;
        }
        cycleCount++;
    }
    DefaultLogManager::Default->EndLog(true);

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitionsForts);

    if(this->m_fortsChannel->AllowFutures())
        this->m_fortsChannel->FutInfo()->InstrReplay()->GenerateSecurityDefinitions();
    if(this->m_fortsChannel->AllowOptions())
        this->m_fortsChannel->OptInfo()->InstrReplay()->GenerateSecurityDefinitions();

    if(this->m_fortsChannel->AllowFutures()) {
        if(!this->m_fortsChannel->OnAfterGenerateSecurityDefinitionsFut()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
    }

    if(this->m_fortsChannel->AllowOptions()) {
        if(!this->m_fortsChannel->OnAfterGenerateSecurityDefinitionsOpt()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
    }

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::CollectSecurityDefinitionsAsts() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitions);

    bool collectedFond = false;
    bool collectedCurr = false;

    if(this->m_fondMarket->FeedChannel()->Idf()->LoadSecurityDefinitions())
        collectedFond = true;
    else if(!this->m_fondMarket->FeedChannel()->Idf()->Start()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(this->m_currMarket->FeedChannel()->Idf()->LoadSecurityDefinitions())
        collectedCurr = true;
    else if(!this->m_currMarket->FeedChannel()->Idf()->Start()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    // collect data first
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!collectedCurr) {
            if (!this->m_currMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(this->m_currMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_currMarket->FeedChannel()->Idf()->Stop();
                collectedCurr = true;
            }
        }
        if(!collectedFond) {
            if (!this->m_fondMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(this->m_fondMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_fondMarket->FeedChannel()->Idf()->Stop();
                collectedFond = true;
            }
        }

        if(collectedFond && collectedCurr)
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            w->Reset();

            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);

            printf("Changes------------------------\n");
            ProgramStatistics::Current->Print();
            printf("Total---------------------------------\n");
            ProgramStatistics::Total->Print();
            printf("--------------------------------------\n");

            cycleCount = 0;
            ProgramStatistics::Current->Clear();
            //ProgramStatistics::Total->ResetFlags();
        }
        cycleCount++;
    }
    DefaultLogManager::Default->EndLog(true);

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitions);

    this->m_fondMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    this->m_currMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    if(!this->m_fondMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!this->m_currMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::MainLoop_FondOnly() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if (!this->m_fondMarket->DoWorkAtom()) {
            return false;
        }
        if(!this->DoWorkAtom()) {
            return false;
        }
        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("--------\n");
            printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);
            this->PrintStatistics();

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }

    return true;
}

bool Robot::MainLoop_CurrOnly() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!this->m_currMarket->DoWorkAtom()) {
            return false;
        }
        if(!this->DoWorkAtom()) {
            return false;
        }
        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("--------\n");
            printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);
            this->PrintStatistics();

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }

    return true;
}

bool Robot::MainLoopForts() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if (!WinSockManager::UpdateManagersPollStatus())
            break;

        if(this->m_fortsChannel->AllowFutures()) {
            if(!this->m_fortsChannel->DoWorkFutures())
                return false;
        }

        if(this->m_fortsChannel->AllowOptions()) {
            if(!this->m_fortsChannel->DoWorkOptions())
                return false;
        }

        if(!this->DoWorkAtom())
            return false;

        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 2000) {
            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("--------\n");
            printf("FORTS cycle count for 2 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);
            this->PrintStatistics();

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }
    return true;
}

bool Robot::MainLoopAsts() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!this->m_currMarket->DoWorkAtom()) {
            return false;
        }
        if(!this->m_fondMarket->DoWorkAtom()) {
            return false;
        }
        if(!this->DoWorkAtom()) {
            return false;
        }
        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 5000) {
            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("--------\n");
            printf("cycle count for 5 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);
            this->PrintStatistics();

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }

    return true;
}

bool Robot::DoWork() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_DoWork);

    if(!this->AllowCurrMarket() && !this->AllowFondMarket() && !this->AllowFortsMarket()) {
        printf("Error: no market enabled!\n");
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    if(this->AllowCurrMarket())
        this->m_currMarket->FeedChannel()->Idf()->AllowSaveSecurityDefinitions(true);
    if(this->AllowFondMarket())
        this->m_fondMarket->FeedChannel()->Idf()->AllowSaveSecurityDefinitions(true);
    if(this->AllowFortsMarket())
        this->m_fortsChannel->AllowSaveSecurityDefinitions(true);

    while(true) {
        if(!this->AllowFortsMarket()) { // no forts market
            if (!this->AllowFondMarket()) {
                if (!this->CollectSecurityDefinitions_CurrOnly()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
                if (!this->MainLoop_CurrOnly()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
            }
            else if (!this->AllowCurrMarket()) {
                if (!this->CollectSecurityDefinitions_FondOnly()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
                if (!this->MainLoop_FondOnly()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
            }
            else {
                if (!this->CollectSecurityDefinitionsAsts()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
                if (!this->MainLoopAsts()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
            }
        }
        else {
            if(!this->AllowFondMarket() && !this->AllowCurrMarket()) {
                if (!this->CollectSecurityDefinitionsForts()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
                if (!this->MainLoopForts()) {
                    DefaultLogManager::Default->EndLog(false);
                    return false;
                }
            }
        }
    }
}

