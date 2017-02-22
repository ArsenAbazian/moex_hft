#pragma once
#include "FeedChannel.h"
#include "MarketInfo.h"
#include "Fix/FixProtocolManager.h"
#include "Managers/LogManager.h"
#include "ConnectionParameters.h"

#define MARKET_INFO_CAPACITY 10
typedef enum _RobotState {

} RobotState;
class Robot
{
	FeedChannel *channels[MARKET_INFO_CAPACITY];
	int		channelsCount;

	MarketInfo *markets[MARKET_INFO_CAPACITY];
	int		marketCount;

    MarketInfo *m_currMarket;
    MarketInfo *m_fondMarket;

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
    bool MainLoop();
    inline bool DoWorkAtom() {
        return true;
    }
    inline bool Working() {
        return this->m_currMarket->Working() || this->m_fondMarket->Working();
    }

public:
	Robot();
	~Robot();

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
		AddMarket(new FondMarketInfo("FOND", FundMarketSenderComputerId, FundMarketPassword, FundMarketTradeServerAddress, FundMarketTradeASTSServerName,
			FundMarketTradeName, FundMarketTradeServerPort, FundMarketTradeTargetComputerId,
			FundMarketTradeCaptureName, FundMarketTradeCaptureServerPort, FundMarketTradeCaptureTargetComputerId,
			FundMarketTradeDropCopyName, FundMarketTradeDropCopyServerPort, FundMarketTradeDropCopyTargetComputerId));
		AddMarket(new CurrencyMarketInfo("CURR", CurrencyMarketSenderComputerId, CurrencyMarketPassword, CurrencyMarketTradeServerAddress, CurrencyMarketTradeASTSServerName,
			CurrencyMarketTradeName, CurrencyMarketTradeServerPort, CurrencyMarketTradeTargetComputerId,
			CurrencyMarketTradeCaptureName, CurrencyMarketTradeCaptureServerPort, CurrencyMarketTradeCaptureTargetComputerId,
			CurrencyMarketTradeDropCopyName, CurrencyMarketTradeDropCopyeServerPort, CurrencyMarketTradeDropCopyTargetComputerId));
		DefaultLogManager::Default->EndLog(true);
		return true;
	}

    bool SetFeedChannelsForMarkets() {
        DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_SetFeedChannelsForMarkets);

        this->m_fondMarket = FindMarket("FOND");
        FeedChannel *fondChannel = FindFeedChannel("FOND");
        if(this->m_fondMarket == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcFOND_market_not_found);
            return false;
        }
        if(fondChannel == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcFOND_feed_channel_not_found);
            return false;
        }

        this->m_currMarket = FindMarket("CURR");
        FeedChannel *currChannel = FindFeedChannel("CURR");
        if(this->m_currMarket == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcCURR_market_not_found);
            return false;
        }
        if(currChannel == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcCURR_feed_channel_not_found);
            return false;
        }
        this->m_fondMarket->SetFeedChannel(fondChannel);
        this->m_currMarket->SetFeedChannel(currChannel);

        DefaultLogManager::Default->EndLog(true);
        return true;
    }

	inline FeedChannel **Channels() { return (FeedChannel**)this->channels; }
	inline int ChannelCount() { return this->channelsCount; }

	inline MarketInfo **Markets() { return (MarketInfo**)this->markets; }
	inline int MarketCount() { return this->marketCount; }

	bool Run();
};
