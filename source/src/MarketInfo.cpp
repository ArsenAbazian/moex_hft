#include "../include/MarketInfo.h"
#include "../include/Managers/LogManager.h"

void MarketInfo::Initialize(const char* name, const char *senderComputerId, const char *password,
    const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
    const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
    const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName) {
    
    strcpy(this->m_name, name);
    this->m_nameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->m_name);

    this->m_trade = this->CreateTradeServerInfo(tradeName, tradeAddress, tradePort, senderComputerId, password, tradeTargetComputerId, tradeASTSServerName);
    this->m_tradeCapture = this->CreateTradeCaptureServerInfo(tradeCaptureName, tradeCaptureAddress, tradeCapturePort, senderComputerId, password, tradeCaptureTargetComputerId, tradeCaptureASTSServerName);
    this->m_dropCopy = this->CreateDropCopyServerInfo(tradeDropCopyName, tradeDropCopyAddress, tradeDropCopyPort, senderComputerId, password, tradeDropCopyTargetComputerId, tradeDropCopyASTSServerName);

    this->m_enable = true;
}

MarketServerInfo* MarketInfo::CreateTradeServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) {
    return new TradeMarketServerInfo(name, internetAddress, internetPort, senderComputerId, password, targetComputerId, astsServerName);
}
MarketServerInfo* MarketInfo::CreateTradeCaptureServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) {
    return new TradeCaptureMarketServerInfo(name, internetAddress, internetPort, senderComputerId, password, targetComputerId, astsServerName);
}
MarketServerInfo* MarketInfo::CreateDropCopyServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName) {
    return new TradeDropCopyMarketServerInfo(name, internetAddress, internetPort, senderComputerId, password, targetComputerId, astsServerName);
}

MarketInfo::MarketInfo(const char* name, const char *senderComputerId, const char *password,
    const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
    const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
    const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName) {
    
    this->Initialize(name, senderComputerId, password,
        tradeName, tradeAddress, tradePort, tradeTargetComputerId, tradeASTSServerName,
        tradeCaptureName, tradeCaptureAddress, tradeCapturePort, tradeCaptureTargetComputerId, tradeCaptureASTSServerName,
        tradeDropCopyName, tradeDropCopyAddress, tradeDropCopyPort, tradeDropCopyTargetComputerId, tradeDropCopyASTSServerName);
}

MarketInfo::MarketInfo(const char* name, const char *senderComputedId, const char *password, const char *inetAddress, const char *astsServerName,
    const char *tradeName, int tradePort, const char *tradeTargetCompId,
    const char *tradeCaptureName, int tradeCapturePort, const char *tradeCaptureTargetCompId,
    const char *tradeDropCopyName, int tradeDropCopyPort, const char *tradeDropCopyTargetCompId) {
    
    this->Initialize(name, senderComputedId, password, tradeName, inetAddress, tradePort, tradeTargetCompId, astsServerName, tradeCaptureName, inetAddress, tradeCapturePort, tradeCaptureTargetCompId, astsServerName, tradeDropCopyName, inetAddress, tradeDropCopyPort, tradeDropCopyTargetCompId, astsServerName);
}

MarketInfo::~MarketInfo() { 
// TODO: i don't like this code. calling non-virtual destructor from non-final class with virtual functions, but without virtual destructor.
    if (this->m_trade != NULL)
        delete this->m_trade;
    if (this->m_tradeCapture != NULL)
        delete this->m_tradeCapture;
    if (this->m_dropCopy != NULL)
        delete this->m_dropCopy;
}

bool MarketInfo::Connect() { 
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketInfo_Connect);
    if (this->m_trade == NULL) {
        DefaultLogManager::Default->EndLog(true);
        return true;
    }
/*
    if(!this->m_trade->Connect()) {
#ifndef ROBOT_WORK_ANYWAY
        DefaultLogManager::Default->EndLog(false);
        return false;
#endif
    }
    if(!this->m_tradeCapture->Connect()) {
#ifndef ROBOT_WORK_ANYWAY
        DefaultLogManager::Default->EndLog(false);
        return false;
#endif
    }
    if(!this->m_dropCopy->Connect()) {
#ifndef ROBOT_WORK_ANYWAY
        DefaultLogManager::Default->EndLog(false);
        return false;
#endif
    }
*/
    if(this->m_feedChannel != NULL && !this->m_feedChannel->Connect()) {
#ifndef ROBOT_WORK_ANYWAY
        DefaultLogManager::Default->EndLog(false);
        return false;
#endif
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool MarketInfo::Disconnect() {
    DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcMarketInfo_Disconnect);
    if (this->m_trade == NULL)
        return true;
    if (!this->m_trade->Disconnect()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if (!this->m_tradeCapture->Disconnect()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if (!this->m_dropCopy->Disconnect()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(this->m_feedChannel != NULL && !this->m_feedChannel->Disconnect()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}
