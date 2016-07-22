#pragma once
#include "FeedChannel.h"
#include "MarketInfo.h"
#include "FixProtocolManager.h"
#include "LogManager.h"
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

	RobotState state;

	FixProtocolManager *protocolManager;
    FeedConnection* CreateConnectionCore(const char *feedChannelId, const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);

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

        MarketInfo *fondMarket = FindMarket("FOND");
        FeedChannel *fondChannel = FindFeedChannel("FOND");
        if(fondMarket == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcFOND_market_not_found);
            return false;
        }
        if(fondChannel == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcFOND_feed_channel_not_found);
            return false;
        }

        MarketInfo *currMarket = FindMarket("CURR");
        FeedChannel *currChannel = FindFeedChannel("CURR");
        if(currMarket == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcCURR_market_not_found);
            return false;
        }
        if(currChannel == NULL) {
            DefaultLogManager::Default->EndLog(false, LogMessageCode::lmcCURR_feed_channel_not_found);
            return false;
        }

        fondMarket->SetFeedChannel(fondChannel);
        currMarket->SetFeedChannel(currChannel);

        DefaultLogManager::Default->EndLog(true);
        return true;
    }

	inline FeedChannel **Channels() { return (FeedChannel**)this->channels; }
	inline int ChannelCount() { return this->channelsCount; }

	inline MarketInfo **Markets() { return (MarketInfo**)this->markets; }
	inline int MarketCount() { return this->marketCount; }

	bool ConnectChannels();
	bool DisconnectChannels();
	bool LogonChannels();
	bool LogoutChannels();

	bool ConnectMarkets();
	bool DisconnectMarkets();
	bool LogonMarkets();
	bool LogoutMarkets();

	bool Run();
};
