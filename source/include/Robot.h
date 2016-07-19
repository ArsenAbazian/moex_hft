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
		AddMarket(new MarketInfo("FOND", FundMarketSenderComputerId, FundMarketPassword, FundMarketTradeServerAddress, FundMarketTradeASTSServerName,
			FundMarketTradeName, FundMarketTradeServerPort, FundMarketTradeTargetComputerId,
			FundMarketTradeCaptureName, FundMarketTradeCaptureServerPort, FundMarketTradeCaptureTargetComputerId,
			FundMarketTradeDropCopyName, FundMarketTradeDropCopyServerPort, FundMarketTradeDropCopyTargetComputerId));

		AddMarket(new MarketInfo("CURR", CurrencyMarketSenderComputerId, CurrencyMarketPassword, CurrencyMarketTradeServerAddress, CurrencyMarketTradeASTSServerName,
			CurrencyMarketTradeName, CurrencyMarketTradeServerPort, CurrencyMarketTradeTargetComputerId,
			CurrencyMarketTradeCaptureName, CurrencyMarketTradeCaptureServerPort, CurrencyMarketTradeCaptureTargetComputerId,
			CurrencyMarketTradeDropCopyName, CurrencyMarketTradeDropCopyeServerPort, CurrencyMarketTradeDropCopyTargetComputerId));
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
