#pragma once
#include "WinSockManager.h"
#include "FastProtocolManager.h"
#include "Types.h"
#include <sys/time.h>
#include "Stopwatch.h"
#include "Lib/AutoAllocatePointerList.h"
#include "Lib/StringIdComparer.h"
#include "MarketData/MarketDataTable.h"
#include "MarketData/OrderInfo.h"
#include "MarketData/TradeInfo.h"
#include "MarketData/StatisticInfo.h"

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
    fcidIdfCurr
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

class FeedConnection;
typedef bool (FeedConnection::*FeedConnectionWorkAtomPtr)();

typedef enum _FeedConnectionType {
    Incremental,
    Snapshot,
    InstrumentDefinition
}FeedConnectionType;

class FeedConnectionMessageInfo {
public:
    FeedConnectionMessageInfo() {
        this->m_item = 0;
        this->m_processed = false;
    }
    BinaryLogItem       *m_item;
    bool                 m_processed;
    inline void Clear() {
        this->m_item = 0;
        this->m_processed = false;
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
    bool                                        m_idfDataCollected;
    bool                                        m_allowUpdateIdfData;

    FeedConnectionMessageInfo                   **m_packets;

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
    bool                                        m_fakeConnect;


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

protected:
	MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>			*m_orderTableFond;
	MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>			*m_orderTableCurr;
	MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>			*m_tradeTableFond;
	MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>			*m_tradeTableCurr;
    MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>       *m_statTableFond;
    MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>       *m_statTableCurr;
    LinkedPointer<FastSecurityDefinitionInfo>                                   **m_securityDefinitions;
    int                                          m_securityDefinitionsCount;
    int                                          m_lastUpdatedSecurityDefinitionIndex;

private:

    inline void GetCurrentTime(UINT64 *time) {
        gettimeofday(this->m_tval, NULL);
        *time = this->m_tval->tv_usec / 1000;
    }

	inline bool CanListen() { return this->socketAManager->ShouldRecv() || this->socketBManager->ShouldRecv(); }

    inline bool ProcessServerA() { return this->ProcessServer(this->socketAManager, LogMessageCode::lmcsocketA); }
    inline bool ProcessServerB() { return this->ProcessServer(this->socketBManager, LogMessageCode::lmcsocketB); }
    inline bool ProcessServerCore(int size) {
        int msgSeqNum = *((UINT*)this->m_recvABuffer->CurrentPos());
        if(this->m_packets[msgSeqNum]->m_item != 0)
            return false;

        this->m_recvABuffer->SetCurrentItemSize(size);
        BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
                                                                    this->m_recvABuffer->BufferIndex(),
                                                                    this->m_recvABuffer->CurrentItemIndex());
        if(this->m_type == FeedConnectionType::Incremental) {
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
        }
        else {
            this->m_waitTimer->Start();
            if(this->m_startMsgSeqNum == -1)
                this->m_startMsgSeqNum = msgSeqNum;
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
        }
        this->m_packets[msgSeqNum]->m_item = item;
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
        int index = info->m_item->m_itemIndex;
        unsigned char *buffer = this->m_recvABuffer->Item(index);
        if(this->ShouldSkipMessage(buffer))
            return false;
        int size = this->m_recvABuffer->ItemLength(index);
        this->m_fastProtocolManager->SetNewBuffer(buffer, size);
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
            if(this->m_packets[i]->m_item == 0) {
                newStartMsgSeqNum = i;
                break;
            }
            if(!this->ProcessIncremental(this->m_packets[i]))
                return false;
            i++;
        }

        while(i <= this->m_endMsgSeqNum) {
            if(this->m_packets[i]->m_processed || this->m_packets[i]->m_item == 0) {
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
		DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, true);
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
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, true);
		return true;
	}
	inline FastSnapshotInfo* GetSnapshotInfo(int index) {
		BinaryLogItem *item = this->m_packets[index]->m_item;
		unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
		if(this->ShouldSkipMessage(buffer))
            return 0;
        this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
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
            if (this->m_packets[i]->m_item == 0) {
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
            if (this->m_packets[i]->m_item == 0) {
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
        return this->m_packets[this->m_startMsgSeqNum]->m_item == 0;
    }

    inline void SkipLostPackets() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if(this->m_packets[i]->m_item != 0) {
                this->m_startMsgSeqNum = i;
                return;
            }
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
    }

    inline void ClearPackets(int start, int end) {
        for(int i = start; i <= end; i++) {
            this->m_packets[i]->Clear();
        }
    }

    inline bool Listen_Atom_SecurityDefinition_Core() {
        return false;
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
        DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_InitializeSockets);

        this->socketAManager = new WinSockManager();
        this->socketBManager = new WinSockManager();

        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool Suspend_Atom() {
        return true;
    }

    inline bool Reconnect_Atom() {
        DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Reconnect_Atom);

        if(!this->m_fakeConnect) {
            if(!this->socketAManager->Reconnect()) {
                DefaultLogManager::Default->EndLog(false);
                return true;
            }
        }

        this->SetState(this->m_nextState);
        this->m_waitTimer->Start();
        this->m_waitTimer->Stop(1);
        this->m_startMsgSeqNum = -1;
        this->m_endMsgSeqNum = -1;
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

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

    inline bool Listen_Atom_SecurityDefinition(){
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->Start(1);
            }
            else {
                if(this->m_waitTimer->ElapsedSeconds(1) > this->WaitAnyPacketMaxTimeSec) {
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_SecurityDefinition, false);
                    return false;
                }
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->Listen_Atom_SecurityDefinition_Core();
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
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		bool res = this->ProcessIncrementalCore(buffer, length);
		DefaultLogManager::Default->EndLog(res);
		return res;
	}

	inline bool ProcessIncremental(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = this->m_recvABuffer->Item(info->m_item->m_itemIndex);
		if(this->ShouldSkipMessage(buffer)) {
            info->m_processed = true;
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }

		//TODO remove unused logging
		/*
		int length = this->m_recvABuffer->ItemLength(item->m_itemIndex);
		fprintf(this->obrLogFile, "unsigned char *msg%d = new unsigned char [%d] { ", item->m_itemIndex, length);
		for(int i = 0; i < length; i++) {
			fprintf(this->obrLogFile, "0x%2.2x", buffer[i]);
			if(i < length - 1)
				fprintf(this->obrLogFile, ", ");
		}
		fprintf(this->obrLogFile, "};\n");
		fflush(this->obrLogFile);
		//till this
		*/
        DefaultLogManager::Default->WriteFast(this->m_idLogIndex, this->m_recvABuffer->BufferIndex(), info->m_item->m_itemIndex);
        info->m_processed = true;
		return this->ProcessIncremental(buffer, this->m_recvABuffer->ItemLength(info->m_item->m_itemIndex));
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	FeedConnection();
	~FeedConnection();

    inline void FakeConnect(bool value) { this->m_fakeConnect = value; }
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
    inline FeedConnection *Snapshot() { return this->m_snapshot; }

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

    inline void AddSecurityDefinitionToList(FastSecurityDefinitionInfo *info) {
        this->m_securityDefinitions[this->m_securityDefinitionsCount]->Data(info);
        this->m_securityDefinitionsCount++;
    }

    inline bool ProcessSecurityDefinition(FastSecurityDefinitionInfo *info) {
        info->Used = true;
        this->AddSecurityDefinitionToList(info);

        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
            FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
            m->Used = true;
            FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
            for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                (*trading)->Used = true;
            }
        }
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

	inline bool Connect() {
		if(this->m_fakeConnect)
            return true;
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
    }
    void SetPassword(const char *password) {
        this->m_password = password;
        this->m_passwordLength = strlen(this->m_password);
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
        return FeedConnectionState::fcsListenIncremental;
    }
	inline void Listen() {
        FeedConnectionState st = CalcListenStateByType();
		if(this->m_state == FeedConnectionState::fcsSuspend)
			this->SetState(st);
		else
			this->SetNextState(st);
	}
    inline bool Start() {
        if(!this->Connect())
			return false;
		if(this->m_state != FeedConnectionState::fcsSuspend)
            return true;
        this->m_waitTimer->Start();
        this->m_waitTimer->Stop(1);
        this->Listen();
		return true;
    }
	inline bool Stop() {
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

class FeedConnection_CURR_MSR : public FeedConnection {
public:
	FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
        this->m_statTableCurr = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->m_id = FeedConnectionId::fcidMsrCurr;
    }
	FeedConnection_CURR_MSR() : FeedConnection() {
        this->m_statTableCurr = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->m_id = FeedConnectionId::fcidMsrCurr;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSS : public FeedConnection {
public:
	FeedConnection_CURR_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidMssCurr;
    }
	FeedConnection_CURR_MSS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidMssCurr;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
	FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->m_id = FeedConnectionId::fcidOlrCurr;
    }
	FeedConnection_CURR_OLR() : FeedConnection() {
		this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->m_id = FeedConnectionId::fcidOlrCurr;
	}
	~FeedConnection_CURR_OLR() {
		delete this->m_orderTableCurr;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLS : public FeedConnection {
public:
	FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidOlsCurr;
    }
	FeedConnection_CURR_OLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidOlsCurr;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
	FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
        this->m_id = FeedConnectionId::fcidTlrCurr;
    }
	FeedConnection_CURR_TLR() : FeedConnection() {
		this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->m_id = FeedConnectionId::fcidTlrCurr;
	}
	~FeedConnection_CURR_TLR() {
		delete this->m_tradeTableCurr;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLS : public FeedConnection {
public:
	FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidTlsCurr;

    }
	FeedConnection_CURR_TLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidTlsCurr;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
	FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->m_id = FeedConnectionId::fcidMsrFond;
    }
	FeedConnection_FOND_MSR() : FeedConnection() {
        this->SetType(FeedConnectionType::Incremental);
        this->m_statTableFond = new MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>();
        this->m_id = FeedConnectionId::fcidMsrFond;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSS : public FeedConnection {
public:
	FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidMssFond;
    }
	FeedConnection_FOND_MSS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidMssFond;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
	FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->m_id = FeedConnectionId::fcidOlrFond;
    }
	FeedConnection_FOND_OLR() : FeedConnection() {
        this->SetType(FeedConnectionType::Incremental);
		this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
        this->m_id = FeedConnectionId::fcidOlrFond;
	}
	~FeedConnection_FOND_OLR() {
		delete this->m_orderTableFond;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLS : public FeedConnection {
public:
	FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidOlsFond;
    }
	FeedConnection_FOND_OLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidOlsFond;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
	FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->m_id = FeedConnectionId::fcidTlrFond;
    }
	FeedConnection_FOND_TLR() : FeedConnection() {
		this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetType(FeedConnectionType::Incremental);
        this->m_id = FeedConnectionId::fcidTlrFond;
	}
	~FeedConnection_FOND_TLR() {
		delete this->m_tradeTableFond;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLS : public FeedConnection {
public:
	FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidTlsFond;
    }
	FeedConnection_FOND_TLS() : FeedConnection() {
        this->SetType(FeedConnectionType::Snapshot);
        this->m_id = FeedConnectionId::fcidTlsFond;
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_IDF : public FeedConnection{
public:
    FeedConnection_FOND_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->m_id = FeedConnectionId::fcidIdfFond;
        this->m_securityDefinitions = new LinkedPointer<FastSecurityDefinitionInfo>*[RobotSettings::MaxSecurityDefinitionCount];
        for(int i = 0; i < RobotSettings::MaxSecurityDefinitionCount; i++)
            this->m_securityDefinitions[i] = new LinkedPointer<FastSecurityDefinitionInfo>();
        this->m_securityDefinitionsCount = 0;
        this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
    }
    ~FeedConnection_FOND_IDF() {
        for(int i = 0; i < RobotSettings::MaxSecurityDefinitionCount; i++)
            delete this->m_securityDefinitions[i];
        delete this->m_securityDefinitions;
    }
};

class FeedConnection_CURR_IDF : public FeedConnection{
public:
    FeedConnection_CURR_IDF(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::InstrumentDefinition);
        this->m_id = FeedConnectionId::fcidIdfCurr;
        this->m_securityDefinitions = new LinkedPointer<FastSecurityDefinitionInfo>*[RobotSettings::MaxSecurityDefinitionCount];
        for(int i = 0; i < RobotSettings::MaxSecurityDefinitionCount; i++)
            this->m_securityDefinitions[i] = new LinkedPointer<FastSecurityDefinitionInfo>();
        this->m_securityDefinitionsCount = 0;
        this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
    }
    ~FeedConnection_CURR_IDF() {
        for(int i = 0; i < RobotSettings::MaxSecurityDefinitionCount; i++)
            delete this->m_securityDefinitions[i];
        delete this->m_securityDefinitions;
    }
};

