//
// Created by root on 18.07.16.
//

#ifndef HFT_ROBOT_LOGERRORMESSAGECODES_H
#define HFT_ROBOT_LOGERRORMESSAGECODES_H

typedef enum _LogMessageCode {
#pragma region LogMessageCodes_GeneratedCode
	lmcNone = 0,
	lmcSuccess = 1,
	lmcFailed = 2,
	lmcRobot_AddDefaultTestMarkets = 3,
	lmcFeedChannel_Connect = 4,
	lmcFeedChannel_Disconnect = 5,
	lmcFeedConnection_Connect = 6,
	lmcFeedConnection_Disconnect = 7,
	lmcMarketInfo_Connect = 8,
	lmcMarketInfo_Disconnect = 9,
	lmcMarketServerInfo_Connect = 10,
	lmcMarketServerInfo_Disconnect = 11,
	lmcRobot_Robot = 12,
	lmcRobot_ConnectChannels = 13,
	lmcRobot_ConnectMarkets = 14,
	lmcRobot_AddDefaultTestChannels = 15,
	lmcRobot_Run = 16,
	lmcWinSockManager_Initialize = 17,
	lmcWinSockManager_Close = 18,
	lmcWinSockManager_Reconnect = 19,
	lmcWinSockManager_Connect = 20,
	lmcMarketInfo_Logon = 21,
	lmcRobot_LogonMarkets = 22,
	lmcMarketServerInfo_Logon = 23,
	lmcFeedConnection_InitializeSockets = 24,
	lmcRobot_SetFeedChannelsForMarkets = 25,
	lmcFOND_market_not_found = 26,
	lmcFOND_feed_channel_not_found = 27,
	lmcCURR_market_not_found = 28,
	lmcCURR_feed_channel_not_found = 29,
	lmcWinSockManager_DoWork = 30,
	lmcWinSockManager_StopWork = 31,
	lmcMarketInfo_DoWork = 32,
	lmcRobot_MarketsDoWork = 33,
	lmcRobot_DoWork = 34,
	lmcRobot_DoWorkCore = 35,
	lmcMarketServerInfo_DoWork = 36,
	lmcMarketServerInfo_Logout = 37,
	lmcRobot_InitializeThreads = 38,
	lmcWinSockManager_SendFix = 39,
	lmcWinSockManager_RecvFix = 40,
	lmcMarketServerInfo_SendLogon_Atom = 41,
	lmcMarketServerInfo_RepeatSendLogon_Atom = 42,
	lmcMarketServerInfo_RecvLogon_Atom = 43,
	lmcMarketServerInfo_WaitRecvLogon_Atom = 44,
	lmcMarketServerInfo_SendLogout_Atom = 45,
	lmcMarketServerInfo_RepeatSendLogout_Atom = 46,
	lmcMarketServerInfo_RecvLogout_Atom = 47,
	lmcMarketServerInfo_WaitRecvLogout_Atom = 48,
	lmcMarketServerInfo_Reconnect_Atom = 49,
	lmcMarketServerInfo_SendTestRequest_Atom = 50,
	lmcMarketServerInfo_RepeatSendTestRequest_Atom = 51,
	lmcMarketServerInfo_RecvHearthBeat_Atom = 52
#pragma  endregion
}LogMessageCode;


class LogMessageProvider {
    const int  m_dynamicLogMessageStartIndex = 5000;
	const int  m_logMessageTextCapacity = 10000;

	const char **m_logMessageText;
	int 		m_dynamicLogMessageCount;

    void InitializeLogMessageText();
public:
    LogMessageProvider();
    ~LogMessageProvider();

	inline const char* Message(int message) { return this->m_logMessageText[message]; }
	int RegisterText(const char *text);
};

class DefaultLogMessageProvider {
public:
	static LogMessageProvider *Default;
};

#endif //HFT_ROBOT_LOGERRORMESSAGECODES_H
