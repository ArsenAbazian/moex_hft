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
	lmcWinSockManager_Connect = 20
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
