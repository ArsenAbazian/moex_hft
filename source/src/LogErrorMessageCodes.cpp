//
// Created by root on 18.07.16.
//
#include <memory.h>
#include "LogErrorMessageCodes.h"

void LogMessageProvider::InitializeLogMessageText() {
	this->m_logMessageText = new const char*[this->m_logMessageTextCapacity];
    bzero(this->m_logMessageText, sizeof(const char*) * this->m_logMessageTextCapacity);

#pragma region LogMessagesProvider_InitializeLogMessageText_GeneratedCode
	this->m_logMessageText[LogMessageCode::lmcNone] = "none";
	this->m_logMessageText[LogMessageCode::lmcSuccess] = "ok";
	this->m_logMessageText[LogMessageCode::lmcFailed] = "failed";
	this->m_logMessageText[LogMessageCode::lmcRobot_AddDefaultTestMarkets] = "Robot::AddDefaultTestMarkets";
	this->m_logMessageText[LogMessageCode::lmcFeedChannel_Connect] = "FeedChannel::Connect";
	this->m_logMessageText[LogMessageCode::lmcFeedChannel_Disconnect] = "FeedChannel::Disconnect";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Connect] = "FeedConnection::Connect";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Disconnect] = "FeedConnection::Disconnect";
	this->m_logMessageText[LogMessageCode::lmcMarketInfo_Connect] = "MarketInfo::Connect";
	this->m_logMessageText[LogMessageCode::lmcMarketInfo_Disconnect] = "MarketInfo::Disconnect";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_Connect] = "MarketServerInfo::Connect";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_Disconnect] = "MarketServerInfo::Disconnect";
	this->m_logMessageText[LogMessageCode::lmcRobot_Robot] = "Robot::~Robot";
	this->m_logMessageText[LogMessageCode::lmcRobot_ConnectChannels] = "Robot::ConnectChannels";
	this->m_logMessageText[LogMessageCode::lmcRobot_ConnectMarkets] = "Robot::ConnectMarkets";
	this->m_logMessageText[LogMessageCode::lmcRobot_AddDefaultTestChannels] = "Robot::AddDefaultTestChannels";
	this->m_logMessageText[LogMessageCode::lmcRobot_Run] = "Robot::Run";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_Initialize] = "WinSockManager::Initialize";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_Close] = "WinSockManager::Close";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_Reconnect] = "WinSockManager::Reconnect";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_Connect] = "WinSockManager::Connect";
	this->m_logMessageText[LogMessageCode::lmcMarketInfo_Logon] = "MarketInfo::Logon";
	this->m_logMessageText[LogMessageCode::lmcRobot_LogonMarkets] = "Robot::LogonMarkets";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_Logon] = "MarketServerInfo::Logon";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_InitializeSockets] = "FeedConnection::InitializeSockets";
	this->m_logMessageText[LogMessageCode::lmcRobot_SetFeedChannelsForMarkets] = "Robot::SetFeedChannelsForMarkets";
	this->m_logMessageText[LogMessageCode::lmcFOND_market_not_found] = "FOND market not found.";
	this->m_logMessageText[LogMessageCode::lmcFOND_feed_channel_not_found] = "FOND feed channel not found.";
	this->m_logMessageText[LogMessageCode::lmcCURR_market_not_found] = "CURR market not found.";
	this->m_logMessageText[LogMessageCode::lmcCURR_feed_channel_not_found] = "CURR feed channel not found.";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_DoWork] = "WinSockManager::DoWork";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_StopWork] = "WinSockManager::StopWork";
	this->m_logMessageText[LogMessageCode::lmcMarketInfo_DoWork] = "MarketInfo::DoWork";
	this->m_logMessageText[LogMessageCode::lmcRobot_MarketsDoWork] = "Robot::MarketsDoWork";
	this->m_logMessageText[LogMessageCode::lmcRobot_DoWork] = "Robot::DoWork";
	this->m_logMessageText[LogMessageCode::lmcRobot_DoWorkCore] = "Robot::DoWorkCore";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_DoWork] = "MarketServerInfo::DoWork";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_Logout] = "MarketServerInfo::Logout";
	this->m_logMessageText[LogMessageCode::lmcRobot_InitializeThreads] = "Robot::InitializeThreads";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_SendFix] = "WinSockManager::SendFix";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_RecvFix] = "WinSockManager::RecvFix";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_SendLogon_Atom] = "MarketServerInfo::SendLogon_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RepeatSendLogon_Atom] = "MarketServerInfo::RepeatSendLogon_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RecvLogon_Atom] = "MarketServerInfo::RecvLogon_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_WaitRecvLogon_Atom] = "MarketServerInfo::WaitRecvLogon_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_SendLogout_Atom] = "MarketServerInfo::SendLogout_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RepeatSendLogout_Atom] = "MarketServerInfo::RepeatSendLogout_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RecvLogout_Atom] = "MarketServerInfo::RecvLogout_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_WaitRecvLogout_Atom] = "MarketServerInfo::WaitRecvLogout_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_Reconnect_Atom] = "MarketServerInfo::Reconnect_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_SendTestRequest_Atom] = "MarketServerInfo::SendTestRequest_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RepeatSendTestRequest_Atom] = "MarketServerInfo::RepeatSendTestRequest_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RecvHearthBeat_Atom] = "MarketServerInfo::RecvHearthBeat_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_SendResendRequest_Atom] = "MarketServerInfo::SendResendRequest_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RepeatSendResendRequest_Atom] = "MarketServerInfo::RepeatSendResendRequest_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_ProcessMessages] = "MarketServerInfo::ProcessMessages";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_ProcessMessage] = "MarketServerInfo::ProcessMessage";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_OnReceiveHearthBeatMessage] = "MarketServerInfo::OnReceiveHearthBeatMessage";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_OnReceiveResendRequestMessage] = "MarketServerInfo::OnReceiveResendRequestMessage";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_OnReceiveLogonMessage] = "MarketServerInfo::OnReceiveLogonMessage";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_OnReceiveLogoutMessage] = "MarketServerInfo::OnReceiveLogoutMessage";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_OnReceiveTestRequestMessage] = "MarketServerInfo::OnReceiveTestRequestMessage";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_ResendLastMessage_Atom] = "MarketServerInfo::ResendLastMessage_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RecvMessage_Atom] = "MarketServerInfo::RecvMessage_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_RecvResendRequest_Atom] = "MarketServerInfo::RecvResendRequest_Atom";
	this->m_logMessageText[LogMessageCode::lmcFixMessage] = "FixMessage";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_Send] = "WinSockManager::Send";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_Recv] = "WinSockManager::Recv";
	this->m_logMessageText[LogMessageCode::lmcFixProtocolManager_SendFix] = "FixProtocolManager::SendFix";
	this->m_logMessageText[LogMessageCode::lmcFixProtocolManager_RecvFix] = "FixProtocolManager::RecvFix";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_ResendMessageSeq_Atom] = "MarketServerInfo::ResendMessageSeq_Atom";
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_OnReceiveReject] = "MarketServerInfo::OnReceiveReject";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_ProcessMessage] = "FeedConnection::ProcessMessage";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Decode] = "FeedConnection::Decode";
	this->m_logMessageText[LogMessageCode::lmcsocketA] = "socketA";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Listen_Atom] = "FeedConnection::Listen_Atom";
	this->m_logMessageText[LogMessageCode::lmcsocketB] = "socketB";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_UpdateManagersPollStatus] = "WinSockManager::UpdateManagersPollStatus";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_SendLogon_Atom] = "FeedConnection::SendLogon_Atom";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_ResendLastMessage_Atom] = "FeedConnection::ResendLastMessage_Atom";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Reconnect_Atom] = "FeedConnection::Reconnect_Atom";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_SendCore] = "FeedConnection::SendCore";
	this->m_logMessageText[LogMessageCode::lmcWinSockManager_ConnectFast] = "WinSockManager::ConnectFast";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Listen_Atom_Incremental] = "FeedConnection::Listen_Atom_Incremental";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_StartListenSnapshot] = "FeedConnection::StartListenSnapshot";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_GetRouteFirst] = "FeedConnection::GetRouteFirst";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_GetLastFragment] = "FeedConnection::GetLastFragment";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_StartNewSnapshot] = "FeedConnection::StartNewSnapshot";
	this->m_logMessageText[LogMessageCode::lmcFeedConnection_Listen_Atom_Snapshot] = "FeedConnection::Listen_Atom_Snapshot";
#pragma endregion
}

LogMessageProvider::LogMessageProvider() {
    this->m_dynamicLogMessageCount = 0;
    this->InitializeLogMessageText();
}

LogMessageProvider::~LogMessageProvider() {
    delete[] this->m_logMessageText;
}

int LogMessageProvider::RegisterText(const char *text) {
    for(int i = this->m_dynamicLogMessageStartIndex; i < this->m_dynamicLogMessageCount; i++) {
        if(strcmp(this->m_logMessageText[i], text) == 0)
            return i;
    }
    int length = strlen(text);
    char *newText = new char[length + 1];
    strcpy(newText, text);

    this->m_logMessageText[this->m_dynamicLogMessageStartIndex + this->m_dynamicLogMessageCount] = newText;
    this->m_dynamicLogMessageCount++;

    return this->m_dynamicLogMessageStartIndex + this->m_dynamicLogMessageCount - 1;
}

LogMessageProvider* DefaultLogMessageProvider::Default = new LogMessageProvider();

