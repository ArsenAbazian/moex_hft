#pragma once
#include "MarketServerInfo.h"
#include "Feeds/AstsFeedChannel.h"

class MarketInfo {

    char                m_name[16];
    int                 m_nameLogIndex;

    MarketServerInfo    *m_trade;
    MarketServerInfo    *m_tradeCapture;
    MarketServerInfo    *m_dropCopy;

    AstsFeedChannel     *m_feedChannel;

    virtual MarketServerInfo* CreateTradeServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName);
    virtual MarketServerInfo* CreateTradeCaptureServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName);
    virtual MarketServerInfo* CreateDropCopyServerInfo(const char *name, const char *internetAddress, int internetPort, const char *senderComputerId, const char *password, const char *targetComputerId, const char *astsServerName);

    void Initialize(const char* name, const char *senderComputerId, const char *password,
        const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
        const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
        const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName);
public:

    MarketInfo(const char* name, const char *senderComputerId, const char *password,
        const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
        const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
        const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName);
    
    MarketInfo(const char* name, const char *senderComputedId, const char *password, const char *inetAddress, const char *astsServerName, 
        const char *tradeName, int tradePort, const char *tradeTargetCompId, 
        const char *tradeCaptureName, int tradeCapturePort, const char *tradeCaptureTargetCompId, 
        const char *tradeDropCopyName, int tradeDropCopyPort, const char *tradeDropCopyTargetCompId);
    
    ~MarketInfo();

    void SetFeedChannel(AstsFeedChannel *feedChannel) {
        this->m_feedChannel = feedChannel;
        this->m_feedChannel->SetSenderCompId(this->m_trade->SenderComputerId());
        this->m_feedChannel->SetPassword(this->m_trade->Password());
    }

    inline AstsFeedChannel* FeedChannel() { return this->m_feedChannel; }
    inline const char* Name() { return this->m_name; }

    bool Connect();
    bool Disconnect();

    inline MarketServerInfo* Trade() { return this->m_trade; }
    inline MarketServerInfo* TradeCapture() { return this->m_tradeCapture; }
    inline MarketServerInfo* TradeDropCopy() { return this->m_dropCopy; }

    inline bool Working() {
        return this->m_trade->Working() || this->m_tradeCapture->Working() || this->m_dropCopy->Working();
    }

    inline bool DoWorkAtom() {
        bool res = this->m_feedChannel->DoWorkAtom();
        this->m_tradeCapture->SetState(MarketServerState::mssEnd);
        this->m_dropCopy->SetState(MarketServerState::mssEnd);
        //res &= this->m_trade->DoWorkAtom();
        //res &= this->m_tradeCapture->DoWorkAtom();
        //res &= this->m_dropCopy->DoWorkAtom();

        return res;
    }
};

class FondMarketInfo : public MarketInfo {
public:
    FondMarketInfo(const char* name, const char *senderComputerId, const char *password,
               const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
               const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
               const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName) :
    MarketInfo(name, senderComputerId, password, tradeName, tradeAddress, tradePort, tradeTargetComputerId, tradeASTSServerName,
    tradeCaptureName, tradeCaptureAddress, tradeCapturePort, tradeCaptureTargetComputerId, tradeCaptureASTSServerName,
    tradeDropCopyName, tradeDropCopyAddress, tradeDropCopyPort, tradeDropCopyTargetComputerId, tradeDropCopyASTSServerName) {}

    FondMarketInfo(const char* name, const char *senderComputedId, const char *password, const char *inetAddress, const char *astsServerName,
               const char *tradeName, int tradePort, const char *tradeTargetCompId,
               const char *tradeCaptureName, int tradeCapturePort, const char *tradeCaptureTargetCompId,
               const char *tradeDropCopyName, int tradeDropCopyPort, const char *tradeDropCopyTargetCompId) :
            MarketInfo(name, senderComputedId, password, inetAddress, astsServerName,
            tradeName, tradePort, tradeTargetCompId,
            tradeCaptureName, tradeCapturePort, tradeCaptureTargetCompId,
            tradeDropCopyName, tradeDropCopyPort, tradeDropCopyTargetCompId) { }
};

class CurrencyMarketInfo : public MarketInfo {
public:
    CurrencyMarketInfo(const char* name, const char *senderComputerId, const char *password,
                   const char *tradeName, const char *tradeAddress, int tradePort, const char *tradeTargetComputerId, const char *tradeASTSServerName,
                   const char *tradeCaptureName, const char *tradeCaptureAddress, int tradeCapturePort, const char *tradeCaptureTargetComputerId, const char *tradeCaptureASTSServerName,
                   const char *tradeDropCopyName, const char *tradeDropCopyAddress, int tradeDropCopyPort, const char *tradeDropCopyTargetComputerId, const char *tradeDropCopyASTSServerName) :
            MarketInfo(name, senderComputerId, password, tradeName, tradeAddress, tradePort, tradeTargetComputerId, tradeASTSServerName,
                       tradeCaptureName, tradeCaptureAddress, tradeCapturePort, tradeCaptureTargetComputerId, tradeCaptureASTSServerName,
                       tradeDropCopyName, tradeDropCopyAddress, tradeDropCopyPort, tradeDropCopyTargetComputerId, tradeDropCopyASTSServerName) {}

    CurrencyMarketInfo(const char* name, const char *senderComputedId, const char *password, const char *inetAddress, const char *astsServerName,
                   const char *tradeName, int tradePort, const char *tradeTargetCompId,
                   const char *tradeCaptureName, int tradeCapturePort, const char *tradeCaptureTargetCompId,
                   const char *tradeDropCopyName, int tradeDropCopyPort, const char *tradeDropCopyTargetCompId) :
            MarketInfo(name, senderComputedId, password, inetAddress, astsServerName,
                       tradeName, tradePort, tradeTargetCompId,
                       tradeCaptureName, tradeCapturePort, tradeCaptureTargetCompId,
                       tradeDropCopyName, tradeDropCopyPort, tradeDropCopyTargetCompId) { }
};

