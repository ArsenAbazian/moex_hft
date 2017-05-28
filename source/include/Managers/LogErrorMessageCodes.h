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
	lmcMarketServerInfo_RecvHearthBeat_Atom = 52,
	lmcMarketServerInfo_SendResendRequest_Atom = 53,
	lmcMarketServerInfo_RepeatSendResendRequest_Atom = 54,
	lmcMarketServerInfo_ProcessMessages = 55,
	lmcMarketServerInfo_ProcessMessage = 56,
	lmcMarketServerInfo_OnReceiveHearthBeatMessage = 57,
	lmcMarketServerInfo_OnReceiveResendRequestMessage = 58,
	lmcMarketServerInfo_OnReceiveLogonMessage = 59,
	lmcMarketServerInfo_OnReceiveLogoutMessage = 60,
	lmcMarketServerInfo_OnReceiveTestRequestMessage = 61,
	lmcMarketServerInfo_ResendLastMessage_Atom = 62,
	lmcMarketServerInfo_RecvMessage_Atom = 63,
	lmcMarketServerInfo_RecvResendRequest_Atom = 64,
	lmcFixMessage = 65,
	lmcWinSockManager_Send = 66,
	lmcWinSockManager_Recv = 67,
	lmcFixProtocolManager_SendFix = 68,
	lmcFixProtocolManager_RecvFix = 69,
	lmcMarketServerInfo_ResendMessageSeq_Atom = 70,
	lmcMarketServerInfo_OnReceiveReject = 71,
	lmcFeedConnection_ProcessMessage = 72,
	lmcFeedConnection_Decode = 73,
	lmcsocketA = 74,
	lmcFeedConnection_Listen_Atom = 75,
	lmcsocketB = 76,
	lmcWinSockManager_UpdateManagersPollStatus = 77,
	lmcFeedConnection_SendLogon_Atom = 78,
	lmcFeedConnection_ResendLastMessage_Atom = 79,
	lmcFeedConnection_Reconnect_Atom = 80,
	lmcFeedConnection_SendCore = 81,
	lmcWinSockManager_ConnectFast = 82,
	lmcFeedConnection_ListenIncremental = 83,
	lmcFeedConnection_StartListenSnapshot = 84,
	lmcFeedConnection_GetRouteFirst = 85,
	lmcFeedConnection_GetLastFragment = 86,
	lmcFeedConnection_StartNewSnapshot = 87,
	lmcFeedConnection_ListenSnapshot = 88,
	lmcFeedConnection_StopListenSnapshot = 89,
	lmcFeedConnection_ListenSecurityDefinition = 90,
	lmcFeedConnection_ListenSecurityStatus = 91,
	lmcsocket_close = 92,
	lmcsocket_socket = 93,
	lmcsocket_bind = 94,
	lmcsocket_setsockopt = 95,
	lmcRobot_CollectSecurityDefinitions = 96,
	lmcRobot_GenerateSecurityDefinitions = 97,
	lmcFeedConnection_SaveSecurityDefinition = 98,
	lmcFeedConnection_LoadSecurityDefinition = 99,
	lmcRobot_CollectSecurityDefinitionsForts = 100,
	lmcRobot_GenerateSecurityDefinitionsForts = 101,
	lmcFeedConnection_StartSecurityStatusSnapshot = 102,
	lmcFeedConnection_FinishSecurityStatusSnapshot = 103,
	lmcFeedConnection_ListenSecurityStatusForts = 104,
	lmcCommandManager_SetUp_46_147_193_130 = 105,
	lmcCommandManager_TearDown = 106,
#pragma  endregion
}LogMessageCode;


class LogMessageProvider {
    static const int  m_dynamicLogMessageStartIndex = 5000;
    static const int  m_logMessageTextCapacity = 10000;

	const char **m_logMessageText;
	int         m_dynamicLogMessageCount;
	int			m_paddingBytes;
    void InitializeLogMessageText();
public:
    LogMessageProvider();
    ~LogMessageProvider();

    inline const char* Message(int message) const { return this->m_logMessageText[message]; }
    int RegisterText(const char *text);
};

class DefaultLogMessageProvider {
public:
    static LogMessageProvider *Default;
};

#endif //HFT_ROBOT_LOGERRORMESSAGECODES_H
