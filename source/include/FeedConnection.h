#pragma once
#include "WinSockManager.h"
#include "FastProtocolManager.h"
#include "FixProtocolManager.h"
#include "Types.h"
#include <sys/time.h>
#include "Stopwatch.h"
#include "Lib/AutoAllocatePointerList.h"
#include "Lib/StringIdComparer.h"
#include "MarketData/MarketDataTable.h"
#include "MarketData/OrderInfo.h"
#include "MarketData/TradeInfo.h"
#include "MarketData/StatisticInfo.h"
#include "MarketData/SymbolManager.h"
#include "ConnectionParameters.h"

typedef enum _FeedConnectionMessage {
	fmcLogon = 2101,
    fmcLogout = 2102,
    fcmHeartBeat = 2108,
    fmcSecuritySratus = 2106,
    fmcTradingSessionStatus = 2107,
    fmcSecurityDefinition = 2115,
	fmcFullRefresh_Generic = 2103,
	fmcIncrementalRefresh_Generic = 2104,
	fmcFullRefresh_OLS_FOND = 2510,
	fmcIncrementalRefresh_OLR_FOND = 2520,
	fmcFullRefresh_OLS_CURR = 3600,
	fmcIncrementalRefresh_OLR_CURR = 3610,
	fmcFullRefresh_TLS_FOND = 2511,
	fmcIncrementalRefresh_TLR_FOND = 2521,
	fmcFullRefresh_TLS_CURR = 3601,
	fmcIncrementalRefresh_TLR_CURR = 3611,
    fmcIncrementalRefresh_MSR_FOND = 2523,
    fmcIncrementalRefresh_MSR_CURR = 3613
} FeedConnectionMessage;

typedef enum _FeedConnectionId {
    fcidObrFond,
    fcidObrCurr,
    fcidOlrFond,
    fcidOlrCurr,
    fcidTlrFond,
    fcidTlrCurr,
    fcidMsrFond,
    fcidMsrCurr,
    fcidObsFond,
    fcidObsCurr,
    fcidOlsFond,
    fcidOlsCurr,
    fcidTlsFond,
    fcidTlsCurr,
    fcidMssFond,
    fcidMssCurr,
    fcidUnknown,
    fcidIdfFond,
    fcidIdfCurr,
    fcidIsfFond,
    fcidIsfCurr,
    fcidHFond,
    fcidHCurr
}FeedConnectionId;

typedef enum _FeedConnectionProtocol {
	TCP_IP,
	UDP_IP
}FeedConnectionProtocol;

typedef enum _FeedConnectionState {
	fcsSuspend,
	fcsListenIncremental,
    fcsListenSnapshot,
    fcsListenSecurityDefinition,
    fcsHistoricalReplay,
    fcsConnect
} FeedConnectionState;

typedef enum _FeedConnectionProcessMessageResultValue {
	fcMsgResProcessed,
	fcMsgResFailed,
	fcMsgResProcessedExit
}FeedConnectionProcessMessageResultValue;

typedef enum _FeedConnectionSecurityDefinitionMode {
    sdmCollectData,
    sdmUpdateData
}FeedConnectionSecurityDefinitionMode;

typedef enum _FeedConnectionSecurityDefinitionState {
    sdsWaitForFirstMessage,
    sdsProcessing
}FeedConnectionSecurityDefinitionState;

typedef enum _FeedConnectionHistoricalReplayState {
    hsWaitLogon,
    hsRecvMessage,
    hsWaitLogout,
    hsSuspend
}FeedConnectionHistoricalReplayState;

class FeedConnection;
typedef bool (FeedConnection::*FeedConnectionWorkAtomPtr)();

typedef enum _FeedConnectionType {
    Incremental,
    Snapshot,
    InstrumentDefinition,
    InstrumentStatus,
    HistoricalReplay
}FeedConnectionType;

class FeedConnectionMessageInfo {
public:
    FeedConnectionMessageInfo() {
        this->m_address = 0;
        this->m_processed = false;
    }
    bool                 m_processed;
    bool                 m_requested;
    unsigned char       *m_address;
    int                  m_size;
    inline void Clear() {
        this->m_address = 0;
        this->m_processed = false;
        this->m_requested = false;
    }
};

class FeedConnectionRequestMessageInfo {
public:
    int                         m_msgSeqNo;
    FeedConnection             *m_conn;
    int                         m_requestCount;

    FeedConnectionRequestMessageInfo() {
        this->m_requestCount = 0;
        this->m_msgSeqNo = 0;
        this->m_conn = 0;
    }
    inline void Clear() {
        this->m_requestCount = 0;
        this->m_msgSeqNo = 0;
        this->m_conn = 0;
    }
};

class OrderTesterFond;
class OrderTesterCurr;
class TradeTesterFond;
class TradeTesterCurr;
class TestMessagesHelper;
class StatisticsTesterFond;
class StatisticsTesterCurr;
class InstrumentDefinitionTester;
class HistoricalReplayTester;

class FeedConnection {
    friend class OrderTesterFond;
    friend class OrderTesterCurr;
	friend class TradeTesterFond;
    friend class TradeTesterCurr;
	friend class FeedConnectionTester;
    friend class TestMessagesHelper;
    friend class StatisticsTesterFond;
    friend class StatisticsTesterCurr;
    friend class InstrumentDefinitionTester;
    friend class HistoricalReplayTester;

public:
	const int MaxReceiveBufferSize 				= 1500;
    const int WaitAnyPacketMaxTimeSec           = 10;
protected:
	char										m_idName[16];
	char										feedTypeName[64];

    FeedConnectionType                          m_type;
    FeedConnectionId                            m_id;

    FeedConnection                              *m_incremental;
    FeedConnection                              *m_snapshot;
    FeedConnection                              *m_historicalReplay;

    FeedConnection                              *m_connectionsToRecvSymbols[32];
    int                                         m_connectionsToRecvSymbolsCount;

    int                                         m_snapshotRouteFirst;
    int                                         m_snapshotLastFragment;
    int                                         m_lastMsgSeqNumProcessed;
	int											m_rptSeq;

    int                                         m_waitIncrementalMaxTimeMs;
    int                                         m_snapshotMaxTimeMs;
    bool                                        m_isLastIncrementalRecv;

    bool                                        m_doNotCheckIncrementalActuality;

    FeedConnectionSecurityDefinitionMode        m_idfMode;
    FeedConnectionSecurityDefinitionState       m_idfState;

    bool                                        m_idfDataCollected;
    bool                                        m_allowUpdateIdfData;
    SymbolManager                               *m_symbolManager;

    FeedConnectionHistoricalReplayState             m_hsState;
    PointerList<FeedConnectionRequestMessageInfo>  *m_hsRequestList;
    int                                             m_hrMessageSeqNo;

    FeedConnectionMessageInfo                       **m_packets;

	int     									m_idLogIndex;
	int 										m_feedTypeNameLogIndex;

	char										feedTypeValue;

	FeedConnectionProtocol 						protocol;

	char										feedASourceIp[64];
	char										feedAIp[64];
	int											feedAPort;

	char										feedBSourceIp[64];
	char										feedBIp[64];
	int											feedBPort;

	int											m_startMsgSeqNum;
    int                                         m_endMsgSeqNum;

    const char                                  *m_senderCompId;
    int                                         m_senderCompIdLength;
    const char                                  *m_password;
    int                                         m_passwordLength;

	WinSockManager								*socketAManager;
	WinSockManager								*socketBManager;
	FastProtocolManager 						*m_fastProtocolManager;
    FastLogonInfo                               *m_fastLogonInfo;

    FixProtocolManager                          *m_fixProtocolManager;
    FixLogonInfo                                *m_hsLogonInfo;
    FixRejectInfo                               *m_hsRejectInfo;
    int                                          m_hsMsgSeqNo;
    SocketBuffer								*m_hsSendABuffer;
    SocketBuffer								*m_hsRecvABuffer;

	ISocketBufferProvider						*m_socketABufferProvider;
	SocketBuffer								*m_sendABuffer;
	SocketBuffer								*m_recvABuffer;

	FeedConnectionState							m_state;
	FeedConnectionState							m_nextState;

    bool										m_shouldUseNextState;

    struct timeval                              *m_tval;
    Stopwatch                                   *m_stopwatch;
    Stopwatch                                   *m_waitTimer;
    bool                                        m_shouldReceiveAnswer;

	MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>			*m_orderTableFond;
	MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>			*m_orderTableCurr;
	MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>			*m_tradeTableFond;
	MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>			*m_tradeTableCurr;
    MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>       *m_statTableFond;
    MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>       *m_statTableCurr;
    LinkedPointer<FastSecurityDefinitionInfo>                                   **m_securityDefinitions;
    int                                          m_securityDefinitionsCount;
    int                                          m_lastUpdatedSecurityDefinitionIndex;

    void InitializeHistoricalReplay() {
        this->m_hsRequestList = new PointerList<FeedConnectionRequestMessageInfo>(RobotSettings::HistoricalReplayMaxMessageRequestCount);
        this->m_hsRequestList->AllocData();
        this->m_fixProtocolManager = new FixProtocolManager(this->m_socketABufferProvider, FastProtocolVersion);
        this->m_fixProtocolManager->SetTargetComputerId(HistoricalReplayTargetComputerId);
        this->m_hsLogonInfo = new FixLogonInfo();
        this->m_hsRejectInfo = new FixRejectInfo();
        this->m_hsMsgSeqNo = 1;
    }
    void DisposeHistoricalReplay() {
        this->m_hsRequestList->FreeData();
        delete this->m_hsRequestList;
        delete this->m_hsLogonInfo;
        delete this->m_hsRejectInfo;
    }
    void InitializePackets() {
        this->m_packets = new FeedConnectionMessageInfo*[RobotSettings::DefaultFeedConnectionPacketCount];
        for(int i = 0; i < RobotSettings::DefaultFeedConnectionPacketCount; i++)
            this->m_packets[i] = new FeedConnectionMessageInfo();
    }
    void InitializeSecurityDefinition() {
        this->m_securityDefinitions = new LinkedPointer<FastSecurityDefinitionInfo>*[RobotSettings::MaxSecurityDefinitionCount];
        for(int i = 0; i < RobotSettings::MaxSecurityDefinitionCount; i++)
            this->m_securityDefinitions[i] = new LinkedPointer<FastSecurityDefinitionInfo>();
        this->m_securityDefinitionsCount = 0;
        this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->m_symbolManager = new SymbolManager(RobotSettings::MarketDataMaxSymbolsCount);
    }
    void DisposeSecurityDefinition() {
        for(int i = 0; i < RobotSettings::MaxSecurityDefinitionCount; i++)
            delete this->m_securityDefinitions[i];
        delete this->m_securityDefinitions;
    }

    inline void GetCurrentTime(UINT64 *time) {
        gettimeofday(this->m_tval, NULL);
        *time = this->m_tval->tv_usec / 1000;
    }

	inline bool CanListen() { return this->socketAManager->ShouldRecv() || this->socketBManager->ShouldRecv(); }

    inline bool ProcessServerA() { return this->ProcessServer(this->socketAManager, LogMessageCode::lmcsocketA); }
    inline bool ProcessServerB() { return this->ProcessServer(this->socketBManager, LogMessageCode::lmcsocketB); }
    inline bool ProcessServerCore(int size) {
        int msgSeqNum = *((UINT*)this->m_recvABuffer->CurrentPos());
        if(this->m_packets[msgSeqNum]->m_address != 0)
            return true;

        this->m_recvABuffer->SetCurrentItemSize(size);
        /*
        BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
                                                                    this->m_recvABuffer->BufferIndex(),
                                                                    this->m_recvABuffer->CurrentItemIndex());
                                                                    */
        if(this->m_type == FeedConnectionType::Incremental) {
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
        }
        else if(this->m_type == FeedConnectionType::InstrumentDefinition) {
            if(this->m_idfState == FeedConnectionSecurityDefinitionState::sdsWaitForFirstMessage) {
                if(msgSeqNum != 1)
                    return true;
                this->m_startMsgSeqNum = 1;
                this->m_endMsgSeqNum = 1;
                this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessing;
            }
            else {
                if(this->m_endMsgSeqNum < msgSeqNum)
                    this->m_endMsgSeqNum = msgSeqNum;
            }
        }
        else {
            this->m_waitTimer->Start();
            if(this->m_startMsgSeqNum == -1)
                this->m_startMsgSeqNum = msgSeqNum;
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
        }
        this->m_packets[msgSeqNum]->m_address = this->m_recvABuffer->CurrentPos();
        this->m_packets[msgSeqNum]->m_size = size;
        this->m_recvABuffer->Next(size);
        return true;
    }
    inline bool ProcessServer(WinSockManager *socketManager, LogMessageCode socketName) {
        if(!socketManager->ShouldRecv())
            return false;
        if(!socketManager->Recv(this->m_recvABuffer->CurrentPos())) {
            DefaultLogManager::Default->WriteSuccess(socketName,
                                                     LogMessageCode::lmcFeedConnection_Listen_Atom,
                                                     false)->m_errno = errno;
            socketManager->Reconnect();
            return false;
        }
        int size = socketManager->RecvSize();
        if(size == 0)
            return false;
        return this->ProcessServerCore(size);
    }

    inline bool HasQueueEntries() {
        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->HasQueueEntries();
        else if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->HasQueueEntries();
        else if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->HasQueueEntries();
        else if(this->m_tradeTableCurr != 0)
            return this->m_tradeTableCurr->HasQueueEntries();
        return false;
    }

    inline bool ShouldStartSnapshot() {
        if(this->m_doNotCheckIncrementalActuality)
            return false;
        return this->HasPotentiallyLostPackets() || this->HasQueueEntries();
    }

    inline bool CanStopListeningSnapshot() {
        return this->SymbolsToRecvSnapshotCount() == 0 && !this->HasQueueEntries();
    }

    inline bool PrepareDecodeSnapshotMessage(int packetIndex) {
        FeedConnectionMessageInfo *info = this->m_packets[packetIndex];
        unsigned char *buffer = info->m_address;
        if(this->ShouldSkipMessage(buffer))
            return false;
        this->m_fastProtocolManager->SetNewBuffer(buffer, info->m_size);
        this->m_fastProtocolManager->ReadMsgSeqNumber();
        this->m_fastProtocolManager->DecodeHeader();
        return true;
    }

    inline bool ApplySnapshot_OLS_FOND() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastOLSFONDInfo *info = (FastOLSFONDInfo *) this->m_fastProtocolManager->DecodeOLSFOND();
         this->m_incremental->OrderFond()->ObtainSnapshotItem(info);
         if(this->m_incremental->OrderFond()->CheckProcessIfSessionInActualState(info)) {
             info->ReleaseUnused();
             return true;
         }
        if(this->m_incremental->OrderFond()->CheckProcessNullSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(!this->m_incremental->OrderFond()->ShouldProcessSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        this->m_incremental->OrderFond()->StartProcessSnapshot(info);
        this->m_incremental->OrderFond()->ProcessSnapshot(info);
        info->ReleaseUnused();
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            info = (FastOLSFONDInfo *) this->m_fastProtocolManager->DecodeOLSFOND();
            this->m_incremental->OrderFond()->ProcessSnapshot(info);
            info->ReleaseUnused();
        }
        this->m_incremental->OrderFond()->EndProcessSnapshot();
        return true;
    }
    inline bool ApplySnapshot_OLS_CURR() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastOLSCURRInfo *info = (FastOLSCURRInfo *) this->m_fastProtocolManager->DecodeOLSCURR();
        this->m_incremental->OrderCurr()->ObtainSnapshotItem(info);
        if(this->m_incremental->OrderCurr()->CheckProcessIfSessionInActualState(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(this->m_incremental->OrderCurr()->CheckProcessNullSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(!this->m_incremental->OrderCurr()->ShouldProcessSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        this->m_incremental->OrderCurr()->StartProcessSnapshot(info);
        this->m_incremental->OrderCurr()->ProcessSnapshot(info);
        info->ReleaseUnused();
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            info = (FastOLSCURRInfo *) this->m_fastProtocolManager->DecodeOLSCURR();
            this->m_incremental->OrderCurr()->ProcessSnapshot(info);
            info->ReleaseUnused();
        }
        this->m_incremental->OrderCurr()->EndProcessSnapshot();
        return true;
    }
    inline bool ApplySnapshot_TLS_FOND() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastTLSFONDInfo *info = (FastTLSFONDInfo *) this->m_fastProtocolManager->DecodeTLSFOND();
        this->m_incremental->TradeFond()->ObtainSnapshotItem(info);
        if(this->m_incremental->TradeFond()->CheckProcessIfSessionInActualState(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(this->m_incremental->TradeFond()->CheckProcessNullSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(!this->m_incremental->TradeFond()->ShouldProcessSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        this->m_incremental->TradeFond()->StartProcessSnapshot(info);
        this->m_incremental->TradeFond()->ProcessSnapshot(info);
        info->ReleaseUnused();
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            info = (FastTLSFONDInfo *) this->m_fastProtocolManager->DecodeTLSFOND();
            this->m_incremental->TradeFond()->ProcessSnapshot(info);
            info->ReleaseUnused();
        }
        this->m_incremental->TradeFond()->EndProcessSnapshot();
        return true;
    }
    inline bool ApplySnapshot_TLS_CURR() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastTLSCURRInfo *info = (FastTLSCURRInfo *) this->m_fastProtocolManager->DecodeTLSCURR();
        this->m_incremental->TradeCurr()->ObtainSnapshotItem(info);
        if(this->m_incremental->TradeCurr()->CheckProcessIfSessionInActualState(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(this->m_incremental->TradeCurr()->CheckProcessNullSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(!this->m_incremental->TradeCurr()->ShouldProcessSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        this->m_incremental->TradeCurr()->StartProcessSnapshot(info);
        this->m_incremental->TradeCurr()->ProcessSnapshot(info);
        info->ReleaseUnused();
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            info = (FastTLSCURRInfo *) this->m_fastProtocolManager->DecodeTLSCURR();
            this->m_incremental->TradeCurr()->ProcessSnapshot(info);
            info->ReleaseUnused();
        }
        this->m_incremental->TradeCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool ApplySnapshot_MSS_FOND() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastGenericInfo *info = (FastGenericInfo *) this->m_fastProtocolManager->DecodeGeneric();
        this->m_incremental->StatisticFond()->ObtainSnapshotItem(info);
        if(this->m_incremental->StatisticFond()->CheckProcessIfSessionInActualState(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(this->m_incremental->StatisticFond()->CheckProcessNullSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(!this->m_incremental->StatisticFond()->ShouldProcessSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        this->m_incremental->StatisticFond()->StartProcessSnapshot(info);
        this->m_incremental->StatisticFond()->ProcessSnapshot(info);
        info->ReleaseUnused();
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            info = (FastGenericInfo *) this->m_fastProtocolManager->DecodeGeneric();
            this->m_incremental->StatisticFond()->ProcessSnapshot(info);
            info->ReleaseUnused();
        }
        this->m_incremental->StatisticFond()->EndProcessSnapshot();
        return true;
    }
    inline bool ApplySnapshot_MSS_CURR() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastGenericInfo *info = (FastGenericInfo *) this->m_fastProtocolManager->DecodeGeneric();
        this->m_incremental->StatisticCurr()->ObtainSnapshotItem(info);
        if(this->m_incremental->StatisticCurr()->CheckProcessIfSessionInActualState(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(this->m_incremental->StatisticCurr()->CheckProcessNullSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        if(!this->m_incremental->StatisticCurr()->ShouldProcessSnapshot(info)) {
            info->ReleaseUnused();
            return true;
        }
        this->m_incremental->StatisticCurr()->StartProcessSnapshot(info);
        this->m_incremental->StatisticCurr()->ProcessSnapshot(info);
        info->ReleaseUnused();
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            info = (FastGenericInfo *) this->m_fastProtocolManager->DecodeGeneric();
            this->m_incremental->StatisticCurr()->ProcessSnapshot(info);
            info->ReleaseUnused();
        }
        this->m_incremental->StatisticCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool ProcessIncrementalMessages() {
        int i = this->m_startMsgSeqNum;
		int newStartMsgSeqNum = -1;

        while(i <= this->m_endMsgSeqNum) {
            if(this->m_packets[i]->m_processed) {
                i++; continue;
            }
            if(this->m_packets[i]->m_address == 0) {
                newStartMsgSeqNum = i;
                break;
            }
            if(!this->ProcessIncremental(this->m_packets[i]))
                return false;
            i++;
        }

        while(i <= this->m_endMsgSeqNum) {
            if(this->m_packets[i]->m_processed || this->m_packets[i]->m_address == 0) {
                i++; continue;
            }
            if(!this->ProcessIncremental(this->m_packets[i]))
                return false;
            i++;
        }
        if(newStartMsgSeqNum != -1)
            this->m_startMsgSeqNum = newStartMsgSeqNum;
        else
            this->m_startMsgSeqNum = i;
        if(this->m_doNotCheckIncrementalActuality)
            this->m_startMsgSeqNum = i;
        return true;
    }
    inline void MarketTableEnterSnapshotMode() {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->EnterSnapshotMode();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->EnterSnapshotMode();
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_statTableCurr != 0) {
            this->m_statTableCurr->EnterSnapshotMode();
            return;
        }
    }
    inline int SymbolsToRecvSnapshotCount() {
        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->SymbolsToRecvSnapshotCount();
        if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_tradeTableCurr != 0)
            return this->m_tradeTableCurr->SymbolsToRecvSnapshotCount();
        if(this->m_statTableFond != 0)
            return this->m_statTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_statTableCurr != 0)
            return this->m_statTableCurr->SymbolsToRecvSnapshotCount();
        return 0;
    }
    inline void MarketTableExitSnapshotMode() {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->ExitSnapshotMode();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->ExitSnapshotMode();
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_statTableCurr != 0) {
            this->m_statTableCurr->ExitSnapshotMode();
            return;
        }
    }
    inline bool StartListenSnapshot() {
		if(!this->m_snapshot->Start()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, false);
			return false;
		}
        this->MarketTableEnterSnapshotMode();
        this->m_snapshot->StartNewSnapshot();
		//DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, true);
		return true;
	}
    inline void UpdateMessageSeqNoAfterSnapshot() {
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
    }
	inline bool StopListenSnapshot() {
		if(!this->m_snapshot->Stop()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, false);
			return false;
		}
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        this->MarketTableExitSnapshotMode();
		this->UpdateMessageSeqNoAfterSnapshot();
        //DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, true);
		return true;
	}
	inline FastSnapshotInfo* GetSnapshotInfo(int index) {
		FeedConnectionMessageInfo *item = this->m_packets[index];
		unsigned char *buffer = item->m_address;
		if(this->ShouldSkipMessage(buffer))
            return 0;
        this->m_fastProtocolManager->SetNewBuffer(buffer, item->m_size);
		this->m_fastProtocolManager->ReadMsgSeqNumber();
		return this->m_fastProtocolManager->GetSnapshotInfo();
	}

    inline void ResetWaitTime() { this->m_waitTimer->Start(); }
    inline bool ActualMsgSeqNum() { return this->m_startMsgSeqNum == this->m_endMsgSeqNum; }

	inline void IncrementMsgSeqNo() { this->m_startMsgSeqNum++; }
	virtual ISocketBufferProvider* CreateSocketBufferProvider() {
			return new SocketBufferProvider(DefaultSocketBufferManager::Default,
											RobotSettings::DefaultFeedConnectionSendBufferSize,
											RobotSettings::DefaultFeedConnectionSendItemsCount,
											RobotSettings::DefaultFeedConnectionRecvBufferSize,
											RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
	virtual void ClearSocketBufferProvider() {
		//delete (SocketBufferProvider*)this->m_socketABufferProvider;
	}
	inline void SetState(FeedConnectionState state) {
		this->m_state = state;
	}
    inline void SetId(FeedConnectionId id) { this->m_id = id; }
    inline void SetHsState(FeedConnectionHistoricalReplayState state) { this->m_hsState = state; }
	inline void SetNextState(FeedConnectionState state) {
		this->m_nextState = state;
		this->m_shouldUseNextState = true;
	}

    inline bool SnapshotMessageWaitTimeElapsed() {
        if(!this->m_waitTimer->Active()) {
            this->m_waitTimer->Start();
            return false;
        }
        else if(this->m_waitTimer->ElapsedMilliseconds() > this->m_snapshotMaxTimeMs) {
            this->m_waitTimer->Stop();
            return true;
        }
        return false;
    }

    FastSnapshotInfo *m_lastSnapshotInfo;
    inline bool FindRouteFirst() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if (this->m_packets[i]->m_address == 0) {
                this->m_startMsgSeqNum = i;
                return false;
            }
            this->m_lastSnapshotInfo = this->GetSnapshotInfo(i);
            if (this->m_lastSnapshotInfo != 0 && this->m_lastSnapshotInfo->RouteFirst == 1) {
                this->m_startMsgSeqNum = i;
                this->m_snapshotRouteFirst = i;
                return true;
            }
            this->m_packets[i]->Clear();
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        return false;
    }

    inline bool FindLastFragment() {
        if(this->m_lastSnapshotInfo != 0 && this->m_lastSnapshotInfo->LastFragment) {
            this->m_snapshotLastFragment = this->m_startMsgSeqNum;
            this->m_startMsgSeqNum++;
            return true;
        }
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if (this->m_packets[i]->m_address == 0) {
                this->m_startMsgSeqNum = i;
                return false;
            }
            this->m_lastSnapshotInfo = this->GetSnapshotInfo(i);
            if(this->m_lastSnapshotInfo != 0 && this->m_lastSnapshotInfo->LastFragment == 1) {
                this->m_startMsgSeqNum = i + 1;
                this->m_snapshotLastFragment = i;
                return true;
            }
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        return false;
    }

    inline bool ApplySnapshotCore() {
        switch(this->m_lastSnapshotInfo->TemplateId) {
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->ApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->ApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                return this->ApplySnapshot_OLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                return this->ApplySnapshot_OLS_CURR();
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                return this->ApplySnapshot_TLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                return this->ApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool TryFindAndApplySnapshot() {
        if(this->m_snapshotRouteFirst == -1) {
            if(!FindRouteFirst())
                return false;
        }
        if(!FindLastFragment())
            return false;

        ApplySnapshotCore();
        this->ClearPackets(this->m_snapshotRouteFirst, this->m_snapshotLastFragment);

        this->m_snapshotRouteFirst = -1;
        this->m_snapshotLastFragment = -1;
        return true;
    }

    inline bool HasPotentiallyLostPackets() {
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return false;
        return this->m_packets[this->m_startMsgSeqNum]->m_address == 0;
    }

    inline void SkipLostPackets() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if(this->m_packets[i]->m_address != 0) {
                this->m_startMsgSeqNum = i;
                return;
            }
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
    }

    inline void ClearPackets(int start, int end) {
        FeedConnectionMessageInfo **info = (this->m_packets + start);
        for(int i = start; i <= end; i++, info++) {
            (*info)->Clear();
        }
    }

    inline bool ProcessSecurityDefinitionCore(unsigned char *buffer, int length) {
        this->m_fastProtocolManager->SetNewBuffer(buffer, length);
        this->m_fastProtocolManager->ReadMsgSeqNumber();

        this->m_fastProtocolManager->DecodeHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedConnectionMessage::fmcSecurityDefinition) {
            printf("not an security definition template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }
        return this->ProcessSecurityDefinition((FastSecurityDefinitionInfo*)this->m_fastProtocolManager->DecodeSecurityDefinition());
    }

    inline bool ProcessSecurityDefinition(unsigned char *buffer, int length) {
        //DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
        bool res = this->ProcessSecurityDefinitionCore(buffer, length);
        //DefaultLogManager::Default->EndLog(res);
        return res;
    }

    inline bool ProcessSecurityDefinition(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
        if(this->ShouldSkipMessage(buffer)) {
            info->m_processed = true;
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }

        //DefaultLogManager::Default->WriteFast(this->m_idLogIndex, this->m_recvABuffer->BufferIndex(), info->m_item->m_itemIndex);
        info->m_processed = true;
        return this->ProcessSecurityDefinition(buffer, info->m_size);
    }

    inline bool ProcessSecurityDefinitionMessages() {


        int i = this->m_startMsgSeqNum;
        int newStartMsgSeqNo = this->m_endMsgSeqNum + 1;

        while(i <= this->m_endMsgSeqNum) {
            if(this->m_packets[i]->m_processed) {
                i++; continue;
            }
            if(this->m_packets[i]->m_address == 0) {
                newStartMsgSeqNo = i;
                break;
            }
            if(!this->ProcessSecurityDefinition(this->m_packets[i]))
                return false;
            i++;
        }

        while(i <= this->m_endMsgSeqNum) {
            if(this->m_packets[i]->m_processed || this->m_packets[i]->m_address == 0) {
                i++; continue;
            }
            if(!this->ProcessSecurityDefinition(this->m_packets[i]))
                return false;
            i++;
        }

        this->m_startMsgSeqNum = newStartMsgSeqNo;
        if(this->m_doNotCheckIncrementalActuality)
            this->m_startMsgSeqNum = i;
        if(this->m_startMsgSeqNum <= this->m_endMsgSeqNum) {
            if(!this->m_packets[this->m_startMsgSeqNum]->m_requested) {
                this->m_packets[this->m_startMsgSeqNum]->m_requested = true;
                printf("msg %d not received. request via Historical Replay\n", this->m_startMsgSeqNum);
                this->m_historicalReplay->HrRequestMessage(this, this->m_startMsgSeqNum);
            }
        }
        return true;
    }

    inline bool Listen_Atom_SecurityDefinition_Core() {
        if(!this->ProcessSecurityDefinitionMessages())
            return false;
        return true;
    }

    inline bool Listen_Atom_Snapshot_Core() {
        if(this->m_waitTimer->IsElapsedMilliseconds(this->m_snapshotMaxTimeMs)) {
            this->m_waitTimer->Stop();
            this->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
            return true;
        }

        if(this->m_startMsgSeqNum == -1)
            return true;

        if(this->HasPotentiallyLostPackets())
            this->m_waitTimer->Activate(1);
        else
            this->m_waitTimer->Stop(1);
        if(this->m_waitTimer->IsElapsedMilliseconds(1, this->WaitSnapshotMaxTimeMs())) {
            if(this->m_snapshotRouteFirst != -1)
                this->ClearPackets(this->m_snapshotRouteFirst, this->m_startMsgSeqNum);
            this->SkipLostPackets();
            this->m_waitTimer->Stop(1);
            this->m_snapshotRouteFirst = -1;
            this->m_snapshotLastFragment = -1;
        }

        int snapshotCount = 0;
        while(TryFindAndApplySnapshot())
            snapshotCount++;

        return true;
    }

    inline bool Listen_Atom_Incremental_Core() {
        if(!this->ProcessIncrementalMessages())
            return false;
        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend) {
            if(!this->ShouldStartSnapshot()) {
                this->m_waitTimer->Stop();
                return true;
            }
            this->m_waitTimer->Activate();
            if (this->m_waitTimer->ElapsedMilliseconds() >= this->m_waitIncrementalMaxTimeMs) {
                if (!this->StartListenSnapshot())
                    return false;
                this->m_waitTimer->Stop();
            }
        }
        else {
            if(this->CanStopListeningSnapshot()) {
                this->StopListenSnapshot();
                this->m_waitTimer->Activate();
            }
        }
        return true;
    }

    inline bool InitializeSockets() {
        if(this->socketAManager != NULL)
            return true;
        //DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_InitializeSockets);

        this->socketAManager = new WinSockManager();
        if(this->m_id != FeedConnectionId::fcidHFond &&
                this->m_id != FeedConnectionId::fcidHCurr)
            this->socketBManager = new WinSockManager();

        //DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool Suspend_Atom() {
        return true;
    }

    inline bool Reconnect_Atom() {
        DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Reconnect_Atom);

#ifndef  TEST
            if(!this->socketAManager->Reconnect()) {
                DefaultLogManager::Default->EndLog(false);
                return true;
            }
#endif

        this->SetState(this->m_nextState);
        this->m_waitTimer->Start();
        this->m_waitTimer->Stop(1);
        this->m_startMsgSeqNum = -1;
        this->m_endMsgSeqNum = -1;
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline void PrepareLogonInfo() {
        this->m_hsLogonInfo->HearthBtInt = 60;
        this->m_hsLogonInfo->ShouldResetSeqNum = false;

        strcpy(this->m_hsLogonInfo->Password, HistoricalReplayPassword);
        this->m_hsLogonInfo->PassLength = HistoricalReplayPasswordLength;

        strcpy(this->m_hsLogonInfo->SenderCompID, this->m_fixProtocolManager->SenderCompId());
        this->m_hsLogonInfo->SenderCompIDLength = this->m_fixProtocolManager->SenderCompIdLength();

        strcpy(this->m_hsLogonInfo->UserName, HistoricalReplayUserName);
        this->m_hsLogonInfo->UserNameLength = HistoricalReplayUserNameLength;
    }

    //TODO Socket buffer provider
    inline bool HistoricalReplay_SendLogon() {
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_hsLogonInfo->MsgStartSeqNo = this->m_hsMsgSeqNo;
        this->m_fixProtocolManager->CreateFastLogonMessage(this->m_hsLogonInfo);

        if(!this->Connect())
            return false;
        if(!this->m_fixProtocolManager->SendFix(this->socketAManager)) {
            this->Disconnect();
            return true;
        }
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsWaitLogon;
        this->m_hrMessageSeqNo = 0;
        return true;
    }

    inline bool CanRecv() { return this->socketAManager->ShouldRecv(); }

    inline void OnProcessHistoricalReplayUnexpectedLogoutMessage() {
        FastLogoutInfo *info = (FastLogoutInfo*)this->m_fastProtocolManager->LastDecodeInfo();
        info->Text[info->TextLength] = 0;
        printf("Historical Replay - Unexprected Logout: %s\n", info->Text);
    }

    inline bool IsHrReceiveFailedProcessed() {
        bool res;
        if(this->m_hrMessageSeqNo != 0)
            res = this->socketAManager->Recv(this->m_recvABuffer->CurrentPos() + 4);
        else
            res = this->socketAManager->Recv(this->m_recvABuffer->CurrentPos());
        if(!res) {
            this->Disconnect();
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }
        return false;
    }

    inline void RecvProcessHistoricalReplayCore(int size) {
        unsigned char *buffer = this->socketAManager->RecvBytes();
        this->m_fastProtocolManager->SetNewBuffer(buffer, size);
        if(this->m_hrMessageSeqNo == 0) {
            this->m_recvABuffer->Next(size + 4);
            this->m_hrMessageSeqNo = this->m_fastProtocolManager->ReadMsgSeqNumber();
        }
        else {
            this->m_recvABuffer->Next(size);
        }
        this->m_fixProtocolManager->SetRecvMsgSeqNo(this->m_hrMessageSeqNo + 1);
        this->m_hrMessageSeqNo = 0;
        this->m_fastProtocolManager->Decode();
    }

    inline bool HistoricalReplay_WaitLogon() {
        if(!this->CanRecv())
            return true;
        if(this->IsHrReceiveFailedProcessed())
            return true;
        int size = this->socketAManager->RecvSize();
        if(size == 4) {
            this->m_hrMessageSeqNo = *(int*)this->socketAManager->RecvBytes();
            return true;
        }
        this->RecvProcessHistoricalReplayCore(size);
        if(this->m_fastProtocolManager->TemplateId() != FeedConnectionMessage::fmcLogon) {
            this->Disconnect();
            if(this->m_fastProtocolManager->TemplateId() == FeedConnectionMessage::fmcLogout)
                OnProcessHistoricalReplayUnexpectedLogoutMessage();
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }
        return this->HistoricalReplay_SendMarketDataRequest();
    }

    inline bool HistoricalReplay_SendMarketDataRequest() {
        FeedConnectionRequestMessageInfo *info = this->m_hsRequestList->Start()->Data();
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_fixProtocolManager->CreateMarketDataRequest(info->m_conn->m_idName, 3, info->m_msgSeqNo, info->m_msgSeqNo);

        if(!this->m_fixProtocolManager->SendFix(this->socketAManager)) {
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            this->Disconnect();
            return true;
        }
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsRecvMessage;
        return true;
    }

    inline bool HistoricalReplay_RecvMessage() {
        if(!this->CanRecv())
            return true;

        if(this->IsHrReceiveFailedProcessed())
            return true;

        int size = this->socketAManager->RecvSize();
        if(size == 4) {
            this->m_hrMessageSeqNo = *(int*)this->socketAManager->RecvBytes();
            return true;
        }
        this->RecvProcessHistoricalReplayCore(size);
        if(this->m_fastProtocolManager->TemplateId() == FeedConnectionMessage::fmcLogout) {
            this->Disconnect();
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }

        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Start();
        FeedConnectionRequestMessageInfo *msg = ptr->Data();
        msg->m_conn->ProcessServerCore(size);

        this->m_hsRequestList->Remove(ptr);
        this->m_hsState = FeedConnectionHistoricalReplayState::hsWaitLogout;
        return true;
    }

    inline bool HistoricalReplay_WaitLogout() {
        if(!this->CanRecv())
            return true;

        if(this->IsHrReceiveFailedProcessed())
            return true;
        int size = this->socketAManager->RecvSize();
        if(size == 4) {
            this->m_hrMessageSeqNo = *(int*)this->socketAManager->RecvBytes();
            return true;
        }
        if(this->m_hrMessageSeqNo == 0)
            this->m_hrMessageSeqNo = *(int*)this->socketAManager->RecvBytes();
        this->m_recvABuffer->Next(size + 4);
        this->m_fixProtocolManager->SetRecvMsgSeqNo(this->m_hrMessageSeqNo + 1);

        return this->HistoricalReplay_SendLogout();
    }

    inline bool HistoricalReplay_SendLogout() {
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_fixProtocolManager->CreateLogoutMessage("Hasta la vista baby!", 20);

        this->m_fixProtocolManager->SendFix(this->socketAManager);
        this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
        this->Disconnect();
        return true;
    }

    inline bool HistoricalReplay_Suspend() {
        if(this->m_hsRequestList->Count() == 0)
            return true;
        FeedConnectionRequestMessageInfo *info = this->m_hsRequestList->Start()->Data();
        if(info->m_requestCount >= 10) {
            this->m_hsRequestList->Remove(this->m_hsRequestList->Start());
            return true;
        }
        info->m_requestCount++;
        this->m_hsSendABuffer = info->m_conn->m_sendABuffer;
        this->m_hsRecvABuffer = info->m_conn->m_recvABuffer;

        return this->HistoricalReplay_SendLogon();
    }

    inline bool HistoricalReplay_Atom() {
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsSuspend)
            return this->HistoricalReplay_Suspend();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsWaitLogon)
            return this->HistoricalReplay_WaitLogon();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsRecvMessage)
            return this->HistoricalReplay_RecvMessage();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsWaitLogout)
            return this->HistoricalReplay_WaitLogout();
        return true;
    }
public:
    inline void HrRequestMessage(FeedConnection *conn, int msgSeqNo) {
        if(this->m_hsRequestList->IsFull())
            return;
        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Pop();
        FeedConnectionRequestMessageInfo *info = ptr->Data();
        info->m_conn = conn;
        info->m_msgSeqNo = msgSeqNo;
        info->m_requestCount = 0;

        this->m_hsRequestList->Add(ptr);
    }
protected:
    inline bool Listen_Atom_Incremental() {

        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();
        this->m_isLastIncrementalRecv = recv;

        if(!this->m_isLastIncrementalRecv) {
            this->m_waitTimer->Activate(1);
            if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                this->StartListenSnapshot();
                return true;
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }

        return this->Listen_Atom_Incremental_Core();
    }

    inline bool Listen_Atom_SecurityDefinition_WaitForMessage() {
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();
        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->Start(1);
            }
            else {
                if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                    printf("Timeout 10 sec... Reconnect...\n");
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_SecurityDefinition, false);
                    this->ReconnectSetNextState(FeedConnectionState::fcsListenSecurityDefinition);
                    return true;
                }
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        if(this->m_idfState == FeedConnectionSecurityDefinitionState::sdsProcessing) { // TODO debug remove
            printf("Start processing security definition\n");
        }
        return true;
    }

    inline bool Listen_Atom_SecurityDefinition_Processing() {
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->Start(1);
            }
            else {
                if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                    printf("Timeout 10 sec... Reconnect...\n");
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_SecurityDefinition, false);
                    this->ReconnectSetNextState(FeedConnectionState::fcsListenSecurityDefinition);
                    return true;
                }
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->Listen_Atom_SecurityDefinition_Core();
    }

    inline bool Listen_Atom_SecurityDefinition() {
        if(this->m_idfState == FeedConnectionSecurityDefinitionState::sdsWaitForFirstMessage)
            return this->Listen_Atom_SecurityDefinition_WaitForMessage();
        return this->Listen_Atom_SecurityDefinition_Processing();
    }

    inline bool Listen_Atom_Snapshot() {
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->Start(1);
            }
            else {
                if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_Snapshot, false);
                    return false;
                }
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }

        return this->Listen_Atom_Snapshot_Core();
    }

    inline void ReconnectSetNextState(FeedConnectionState state) {
        this->m_waitTimer->Stop();
        this->SetNextState(state);
        this->SetState(FeedConnectionState::fcsConnect);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState);
    }

	FILE *obrLogFile;

	inline bool OnIncrementalRefresh_OLR_FOND(FastOLSFONDItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
		return this->m_orderTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_OLR_CURR(FastOLSCURRItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
		return this->m_orderTableCurr->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_TLR_FOND(FastTLSFONDItemInfo *info) {
		return this->m_tradeTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_TLR_CURR(FastTLSCURRItemInfo *info) {
        return this->m_tradeTableCurr->ProcessIncremental(info);
	}

    inline bool OnIncrementalRefresh_MSR_FOND(FastGenericItemInfo *info) {
        return this->m_statTableFond->ProcessIncremental(info);
    }

    inline bool OnIncrementalRefresh_MSR_CURR(FastGenericItemInfo *info) {
        return this->m_statTableCurr->ProcessIncremental(info);
    }

    inline bool OnIncrementalRefresh_OLR_FOND(FastIncrementalOLRFONDInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OLR_FOND(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_OLR_CURR(FastIncrementalOLRCURRInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OLR_CURR(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_TLR_FOND(FastIncrementalTLRFONDInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_TLR_FOND(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_TLR_CURR(FastIncrementalTLRCURRInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_TLR_CURR(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_MSR_FOND(FastIncrementalMSRFONDInfo *info) {
        this->m_fastProtocolManager->PrintIncrementalMSRFOND(info);
        return true;
        /*bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_MSR_FOND(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;*/
    }

    inline bool OnIncrementalRefresh_MSR_CURR(FastIncrementalMSRCURRInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_MSR_CURR(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnHearthBeatMessage(FastHeartbeatInfo *info) {
        throw; // there is no need to apply message just check
    }

    inline bool ApplyIncrementalCore() {
		switch(this->m_fastProtocolManager->TemplateId()) {
			case FeedConnectionMessage::fcmHeartBeat:
                return this->OnHearthBeatMessage((FastHeartbeatInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
				return this->OnIncrementalRefresh_OLR_FOND((FastIncrementalOLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
				return this->OnIncrementalRefresh_OLR_CURR((FastIncrementalOLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
				return this->OnIncrementalRefresh_TLR_FOND((FastIncrementalTLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
				return this->OnIncrementalRefresh_TLR_CURR((FastIncrementalTLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
            case FeedConnectionMessage::fmcIncrementalRefresh_MSR_FOND:
                return this->OnIncrementalRefresh_MSR_FOND((FastIncrementalMSRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
            case FeedConnectionMessage::fmcIncrementalRefresh_MSR_CURR:
                return this->OnIncrementalRefresh_MSR_CURR((FastIncrementalMSRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
		}
		return true;
	}

	inline bool ProcessIncrementalCore(unsigned char *buffer, int length) {
		this->m_fastProtocolManager->SetNewBuffer(buffer, length);
		this->m_fastProtocolManager->ReadMsgSeqNumber();

		if(this->m_fastProtocolManager->Decode() == 0) {
            printf("unknown template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }
		this->ApplyIncrementalCore();
		return true;
	}

	inline bool ShouldSkipMessage(unsigned char *buffer) {
		unsigned short *templateId = (unsigned short*)(buffer + 5);
		return (*templateId) == 0xbc10;
	}

	inline bool ProcessIncremental(unsigned char *buffer, int length) {
		//DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		bool res = this->ProcessIncrementalCore(buffer, length);
		//DefaultLogManager::Default->EndLog(res);
		return res;
	}

	inline bool ProcessIncremental(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
		if(this->ShouldSkipMessage(buffer)) {
            info->m_processed = true;
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }

        //DefaultLogManager::Default->WriteFast(this->m_idLogIndex, this->m_recvABuffer->BufferIndex(), info->m_item->m_itemIndex);
        info->m_processed = true;
		return this->ProcessIncremental(buffer, info->m_size);
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	FeedConnection();
	~FeedConnection();

    inline int LastMsgSeqNumProcessed() { return this->m_lastMsgSeqNumProcessed; }
    inline MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo> *OrderFond() { return this->m_orderTableFond; }
	inline MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo> *OrderCurr() { return this->m_orderTableCurr; }
	inline MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo> *TradeFond() { return this->m_tradeTableFond; }
	inline MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo> *TradeCurr() { return this->m_tradeTableCurr; }
    inline MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo> *StatisticFond() { return this->m_statTableFond; }
    inline MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo> *StatisticCurr() { return this->m_statTableCurr; }
    inline LinkedPointer<FastSecurityDefinitionInfo>** SecurityDefinitions() { return this->m_securityDefinitions; }
    inline FastSecurityDefinitionInfo* SecurityDefinition(int index) { return this->m_securityDefinitions[index]->Data(); }
    inline int SecurityDefinitionsCount() { return this->m_securityDefinitionsCount; }
    inline FeedConnectionSecurityDefinitionMode SecurityDefinitionMode() { return this->m_idfMode; }
    inline void WaitIncrementalMaxTimeMs(int timeMs) { this->m_waitIncrementalMaxTimeMs = timeMs; }
    inline int WaitIncrementalMaxTimeMs() { return this->m_waitIncrementalMaxTimeMs; }
    inline void WaitSnapshotMaxTimeMs(int timeMs) { this->m_snapshotMaxTimeMs = timeMs; }
    inline int WaitSnapshotMaxTimeMs() { return this->m_snapshotMaxTimeMs; }

    inline void ClearMessages() {
        for(int i = 0;i < RobotSettings::DefaultFeedConnectionPacketCount; i++)
            this->m_packets[i]->Clear();
        this->m_startMsgSeqNum = 1;
        this->m_endMsgSeqNum = 0;
    }

    inline void StartNewSnapshot() {
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartNewSnapshot, true);
        this->m_endMsgSeqNum = -1;
        this->m_startMsgSeqNum = -1;
        this->m_snapshotRouteFirst = -1;
        this->m_snapshotLastFragment = -1;
    }

    inline void SetType(FeedConnectionType type) {
        this->m_type = type;
		if(this->m_state == FeedConnectionState::fcsListenIncremental ||
                this->m_state == FeedConnectionState::fcsListenSnapshot)
			this->SetState(this->m_state);
		else if(this->m_nextState == FeedConnectionState::fcsListenIncremental ||
                this->m_nextState == FeedConnectionState::fcsListenSnapshot)
			this->SetNextState(this->m_state);
    }
    inline FeedConnectionType Type() { return this->m_type; }

    inline void SetIncremental(FeedConnection *conn) {
		if(this->m_incremental == conn)
			return;
		this->m_incremental = conn;
		if(this->m_incremental != 0)
			this->m_incremental->SetSnapshot(this);
	}
    inline FeedConnection *Incremental() { return this->m_incremental; }

    inline void SetSnapshot(FeedConnection *conn) {
		if(this->m_snapshot == conn)
			return;
		this->m_snapshot = conn;
		if(this->m_snapshot != 0)
			this->m_snapshot->SetIncremental(this);
	}
    inline FeedConnection* Snapshot() { return this->m_snapshot; }
    inline void SetHistoricalReplay(FeedConnection *historicalReplay) { this->m_historicalReplay = historicalReplay; }
    inline FeedConnection* HistoricalReplay() { return this->m_historicalReplay; }

    inline FeedConnection** ConnectionsToRecvSymbols() { return this->m_connectionsToRecvSymbols; }
    inline int ConnectionsToRecvSymbolsCount() { return this->m_connectionsToRecvSymbolsCount; }
    inline void AddConnectionToRecvSymbol(FeedConnection *conn) {
        this->m_connectionsToRecvSymbols[this->m_connectionsToRecvSymbolsCount] = conn;
        this->m_connectionsToRecvSymbolsCount++;
    }

    inline int CalcSessionsCount(FastSecurityDefinitionInfo *info) {
        int res = 0;
        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
            res += info->MarketSegmentGrp[i]->TradingSessionRulesGrpCount;
        }
        return res;
    }

    inline void AddSymbol(LinkedPointer<FastSecurityDefinitionInfo> *ptr) {
        FastSecurityDefinitionInfo *info = ptr->Data();
        if(this->m_orderTableFond != 0) {
            MarketSymbolInfo<OrderInfo<FastOLSFONDItemInfo>> *symbol = this->m_orderTableFond->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_orderTableCurr != 0) {
            MarketSymbolInfo<OrderInfo<FastOLSCURRItemInfo>> *symbol = this->m_orderTableCurr->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_tradeTableFond != 0) {
            MarketSymbolInfo<TradeInfo<FastTLSFONDItemInfo>> *symbol = this->m_tradeTableFond->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            MarketSymbolInfo<TradeInfo<FastTLSCURRItemInfo>> *symbol = this->m_tradeTableCurr->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_statTableFond != 0) {
            MarketSymbolInfo<StatisticsInfo<FastGenericItemInfo>> *symbol = this->m_statTableFond->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_statTableCurr != 0) {
            MarketSymbolInfo<StatisticsInfo<FastGenericItemInfo>> *symbol = this->m_statTableCurr->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
    }

    inline void AddSecurityDefinitionToList(FastSecurityDefinitionInfo *info, int index) {
        this->m_securityDefinitions[index]->Data(info);
        this->m_securityDefinitionsCount = index + 1;
    }

    inline void MakeUsed(FastSecurityDefinitionMarketSegmentGrpItemInfo *m, bool used) {
        m->Used = used;
        FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
        for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
            (*trading)->Used = used;
        }
    }

    inline void MakeUsed(FastSecurityDefinitionInfo *info, bool used) {
        info->Used = used;

        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++)
            MakeUsed(*market, used);
    }

    inline void MergeSecurityDefinition(FastSecurityDefinitionInfo *parent, FastSecurityDefinitionInfo *child) {
        int freeIndex = parent->MarketSegmentGrpCount;
        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = child->MarketSegmentGrp;
        for(int i = 0; i < child->MarketSegmentGrpCount; i++, market++) {
            MakeUsed(*market, true);
            parent->MarketSegmentGrp[freeIndex] = *market;
        }
        child->MarketSegmentGrpCount = 0;
    }

    inline bool IsLastSecurityDefinitionMessageRecv(FastSecurityDefinitionInfo *info) {
        return info->TotNumReports == this->m_endMsgSeqNum;
    }

    inline void PrintSymbolManagerDebug() {
        printf("Collected %d symbols\n", this->m_securityDefinitionsCount);
        for(int i = 0; i < this->m_symbolManager->BucketListCount(); i++) {
            int count = this->m_symbolManager->CalcBucketCollisitonCount(i);
            if(count != 0)
                printf("Collision %d = %d\n", i, count);
        }
        printf("Collected %d symbols\n", this->m_securityDefinitionsCount);
    }

    inline void OnSecurityDefinitionRecvAllMessages() {
        this->Stop();

        for(int i = 1; i < this->m_endMsgSeqNum; i++) {
            if(this->m_packets[i]->m_address == 0)
                throw;
        }

        this->ClearPackets(0, this->m_endMsgSeqNum);
        this->PrintSymbolManagerDebug();  // TODO debug messages
        this->AfterProcessSecurityDefinitions();
        this->m_idfDataCollected = true;
    }

    inline bool ProcessSecurityDefinition(FastSecurityDefinitionInfo *info) {
        bool wasNewlyAdded = false;

        printf("process sec_def %d\n", info->MsgSeqNum); // TODO

        SymbolInfo *smb = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength, &wasNewlyAdded);

        MakeUsed(info, true);
        if(wasNewlyAdded) {
            this->AddSecurityDefinitionToList(info, smb->m_index);
        }
        else {
            LinkedPointer<FastSecurityDefinitionInfo> *ptr = this->m_securityDefinitions[smb->m_index];
            MergeSecurityDefinition(ptr->Data(), info);
        }
        info->ReleaseUnused();
        if(IsLastSecurityDefinitionMessageRecv(info))
            this->OnSecurityDefinitionRecvAllMessages();

        return true;
    }

    inline void AddSymbols(int count) {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->InitSymbols(count);
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->InitSymbols(count);
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->InitSymbols(count);
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->InitSymbols(count);
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->InitSymbols(count);
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_statTableCurr->InitSymbols(count);
            return;
        }
    }

    inline void ClearMarketData() {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->Release();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->Release();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->Release();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->Release();
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->Release();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_statTableCurr->Release();
            return;
        }
    }

    inline void ClearSecurityDefinitions() {
        for(int i = 0; i < this->m_securityDefinitionsCount; i++)
            this->m_securityDefinitions[i]->Data()->Clear();
        this->m_securityDefinitionsCount = 0;
    }

    inline void BeforeProcessSecurityDefinitions() {
        this->ClearSecurityDefinitions();
        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++) {
            this->m_connectionsToRecvSymbols[c]->ClearMarketData();
        }
    }

    inline void AddSecurityDefinition(LinkedPointer<FastSecurityDefinitionInfo> *ptr) {
        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++)
            this->m_connectionsToRecvSymbols[c]->AddSymbol(ptr);
    }

    inline int GetSecurityDefinitionIndex(int startIndex, const char *symbol, int length) {
        if(this->m_securityDefinitionsCount == 0)
            return -1;
        for(int i = startIndex + 1; i < this->m_securityDefinitionsCount; i++) {
            FastSecurityDefinitionInfo *prev = this->m_securityDefinitions[i]->Data();
            if(StringIdComparer::Equal(prev->Symbol, prev->SymbolLength, symbol, length))
                return i;
        }
        for(int i = 0; i < startIndex + 1; i++) {
            FastSecurityDefinitionInfo *prev = this->m_securityDefinitions[i]->Data();
            if(StringIdComparer::Equal(prev->Symbol, prev->SymbolLength, symbol, length))
                return i;
        }
        return -1;
    }

    inline void UpdateSecurityDefinition(FastSecurityDefinitionInfo *info) {
        this->m_lastUpdatedSecurityDefinitionIndex = this->GetSecurityDefinitionIndex(this->m_lastUpdatedSecurityDefinitionIndex + 1, info->Symbol, info->SymbolLength);
        if(this->m_lastUpdatedSecurityDefinitionIndex != -1) {
            this->m_securityDefinitions[this->m_lastUpdatedSecurityDefinitionIndex]->Data()->Clear();
            this->m_securityDefinitions[this->m_lastUpdatedSecurityDefinitionIndex]->Data(info);
        }
    }

    inline void AfterProcessSecurityDefinitions() {
        for(int i = 0; i < this->m_connectionsToRecvSymbolsCount; i++)
            this->m_connectionsToRecvSymbols[i]->AddSymbols(this->m_securityDefinitionsCount);

        LinkedPointer<FastSecurityDefinitionInfo> **ptr = this->m_securityDefinitions;
        for(int i = 0; i < this->m_securityDefinitionsCount; i++, ptr++)
            this->AddSecurityDefinition(*ptr);
        this->m_lastUpdatedSecurityDefinitionIndex = -1;
    }

    inline bool HasLostPackets(int msgStart, int msgEnd) {
        FeedConnectionMessageInfo **msg = (this->m_packets + msgStart);
        for(int i = msgStart; i <= msgEnd; i++, msg++) {
            if((*msg)->m_address == 0)
                return true;
        }
        return false;
    }

    inline bool IsIdfDataCollected() { return this->m_idfDataCollected; }
    inline FeedConnectionSecurityDefinitionMode IdfMode() { return this->m_idfMode; }
    inline FeedConnectionSecurityDefinitionState IdfState() { return this->m_idfState; }

	inline bool Connect() {
        if(this->socketAManager != NULL && this->socketAManager->IsConnected())
			return true;
		if(this->socketAManager == NULL && !this->InitializeSockets())
			return false;
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Connect);
		if(this->protocol == FeedConnectionProtocol::UDP_IP) {
			if (!this->socketAManager->ConnectMulticast(this->feedASourceIp, this->feedAIp, this->feedAPort)) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}
			if (!this->socketBManager->ConnectMulticast(this->feedBSourceIp, this->feedBIp, this->feedBPort)) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}
		}
		else {
			if(!this->socketAManager->Connect(this->feedAIp, this->feedAPort)) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}
		}
		DefaultLogManager::Default->EndLog(true);
		return true;
	}

	inline bool Disconnect() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Disconnect);

		bool result = true;
		if(this->socketAManager != NULL)
			result &= this->socketAManager->Disconnect();
		if(this->socketBManager != NULL)
			result &= this->socketBManager->Disconnect();

		DefaultLogManager::Default->EndLog(result);
		return result;
	}

    void SetSenderCompId(const char *senderCompId) {
        this->m_senderCompId = senderCompId;
        if(this->m_senderCompId == NULL)
            this->m_senderCompIdLength = 0;
        else
            this->m_senderCompIdLength = strlen(this->m_senderCompId);
        if(this->m_type == FeedConnectionType::HistoricalReplay && this->m_senderCompId != 0) {
            strcpy(this->m_hsLogonInfo->SenderCompID, this->m_senderCompId);
            this->m_hsLogonInfo->SenderCompIDLength = this->m_senderCompIdLength;
        }
    }
    void SetPassword(const char *password) {
        if(this->m_type == FeedConnectionType::HistoricalReplay) {
            this->m_password = HistoricalReplayPassword;
            this->m_passwordLength = HistoricalReplayPasswordLength;
        }
        else {
            this->m_password = password;
            this->m_passwordLength = strlen(this->m_password);
        }
    }

    inline char* IdName() { return this->m_idName; }
    inline FeedConnectionId Id() { return this->m_id; }

	inline virtual void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);

		DefaultLogManager::Default->EndLog(true);
	}

	inline int MsgSeqNo() { return this->m_startMsgSeqNum; }
	inline int ExpectedMsgSeqNo() { return this->m_startMsgSeqNum + 1; }

	inline bool DoWorkAtom() {
		FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsListenIncremental)
            return this->Listen_Atom_Incremental();
        if(st == FeedConnectionState::fcsHistoricalReplay)
            return this->HistoricalReplay_Atom();
        if(st == FeedConnectionState::fcsListenSecurityDefinition)
            return this->Listen_Atom_SecurityDefinition();
        if(st == FeedConnectionState::fcsListenSnapshot)
            return this->Listen_Atom_Snapshot();
        if(st == FeedConnectionState::fcsSuspend)
            return true;
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;

	}
    inline FeedConnectionState CalcListenStateByType() {
        if(m_type == FeedConnectionType::InstrumentDefinition)
            return FeedConnectionState::fcsListenSecurityDefinition;
        else if(m_type == FeedConnectionType::Snapshot)
            return FeedConnectionState::fcsListenSnapshot;
        else if(m_type == FeedConnectionType::HistoricalReplay)
            return FeedConnectionState::fcsHistoricalReplay;
        return FeedConnectionState::fcsListenIncremental;
    }
	inline void Listen() {
        FeedConnectionState st = CalcListenStateByType();
		if(this->m_state == FeedConnectionState::fcsSuspend)
			this->SetState(st);
		else
			this->SetNextState(st);
	}
    inline void BeforeListen() {
        if(this->m_type == FeedConnectionType::InstrumentDefinition) {
            this->m_idfState = FeedConnectionSecurityDefinitionState::sdsWaitForFirstMessage;
            printf("Wait for First Security Definition\n"); // TODO remove debug
        }
        if(this->m_type == FeedConnectionType::HistoricalReplay) {
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            printf("Start Historical Replay\n");
        }
    }
    inline bool Start() {
        if(this->m_state == FeedConnectionState::fcsHistoricalReplay)
            return true;
        if(!this->Connect())
			return false;
		if(this->m_state != FeedConnectionState::fcsSuspend)
            return true;
        this->m_waitTimer->Start();
        this->m_waitTimer->Stop(1);
        this->BeforeListen();
        this->Listen();
		return true;
    }
	inline bool Stop() {
		if(this->m_state == FeedConnectionState::fcsHistoricalReplay)
            return true;
        this->SetState(FeedConnectionState::fcsSuspend);
		if(!this->Disconnect())
			return false;
		return true;
	}
    inline FeedConnectionState State() { return this->m_state; }
    inline void DoNotCheckIncrementalActuality(bool value) {
        this->m_doNotCheckIncrementalActuality = value;
    }
};



