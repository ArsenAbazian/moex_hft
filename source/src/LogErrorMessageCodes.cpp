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
	this->m_logMessageText[LogMessageCode::lmcSuccess] = "success";
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
	this->m_logMessageText[LogMessageCode::lmcMarketServerInfo_Logon] = "MarketServerInfo_Logon";
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

