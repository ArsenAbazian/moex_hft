#pragma once
#include "WinSockManager.h"
#include "FastProtocolManager.h"
#include "Types.h"
#include <sys/time.h>
#include "Stopwatch.h"
#include "Lib/AutoAllocatePointerList.h"
#include "Lib/HashTable.h"
#include "MarketData/MarketDataTable.h"

typedef enum _FeedConnectionMessage {
	fcmHeartBeat = 2108,
	fmcFullRefresh_OBS_FOND = 2412,
	fmcIncrementalRefresh_OBR_FOND = 2422,
	fmcFullRefresh_OBS_CURR = 3502,
	fmcIncrementalRefresh_OBR_CURR = 3512,
	fmcFullRefresh_OLS_FOND = 2410,
	fmcIncrementalRefresh_OLR_FOND = 2420,
	fmcFullRefresh_OLS_CURR = 3500,
	fmcIncrementalRefresh_OLR_CURR = 3510,
	fmcFullRefresh_TLS_FOND = 2411,
	fmcIncrementalRefresh_TLR_FOND = 2421,
	fmcFullRefresh_TLS_CURR = 3501,
	fmcIncrementalRefresh_TLR_CURR = 3511
}FeedConnectionMessage;

typedef enum _FeedConnectionProtocol {
	TCP_IP,
	UDP_IP
}FeedConnectionProtocol;

typedef enum _FeedConnectionState {
	fcsSuspend,
	fcsListenIncremental,
    fcsListenSnapshot,
    fcsConnect
} FeedConnectionState;

typedef enum _FeedConnectionProcessMessageResultValue {
	fcMsgResProcessed,
	fcMsgResFailed,
	fcMsgResProcessedExit
}FeedConnectionProcessMessageResultValue;

class FeedConnection;
typedef bool (FeedConnection::*FeedConnectionWorkAtomPtr)();

typedef enum _FeedConnectionType {
    Incremental,
    Snapshot
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

class OrderBookTester;
class OrderTester;
class TradeTester;

class FeedConnection {
	friend class OrderBookTester;
    friend class OrderTester;
	friend class TradeTester;
	friend class FeedConnectionTester;

public:
	const int MaxReceiveBufferSize 				= 1500;
    const int WaitAnyPacketMaxTimeSec           = 10;
protected:
	char										id[16];
	char										feedTypeName[64];

    FeedConnectionType                          m_type;
    FeedConnection                              *m_incremental;
    FeedConnection                              *m_snapshot;
    int                                         m_snapshotRouteFirst;
    int                                         m_snapshotLastFragment;
    int                                         m_lastMsgSeqNumProcessed;
	int											m_rptSeq;

    int                                         m_waitIncrementalMaxTimeMs;
    int                                         m_snapshotMaxTimeMs;
    bool                                        m_isLastIncrementalRecv;

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
	MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>		*m_orderBookTableFond;
	MarketDataTable<OrderBookInfo,FastOBSCURRInfo, FastOBSCURRItemInfo>        *m_orderBookTableCurr;
	MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>			*m_orderTableFond;
	MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>			*m_orderTableCurr;
	MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>			*m_tradeTableFond;
	MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>			*m_tradeTableCurr;
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
        if(this->m_orderBookTableFond != 0)
            return this->m_orderBookTableFond->HasQueueEntries();
        else if(this->m_orderBookTableCurr != 0)
            return this->m_orderBookTableCurr->HasQueueEntries();
        else if(this->m_orderTableFond != 0)
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

    inline bool ApplySnapshot_OBS_FOND() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastOBSFONDInfo *info = (FastOBSFONDInfo *) this->m_fastProtocolManager->DecodeOBSFOND();
        this->m_incremental->OnFullRefresh_OBS_FOND_Start(info);
        this->m_incremental->OnFullRefresh_OBS_FOND(info);
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            this->m_incremental->OnFullRefresh_OBS_FOND(
                    (FastOBSFONDInfo *) this->m_fastProtocolManager->DecodeOBSFOND());
        }
        this->m_incremental->OnFullRefresh_OBS_FOND_End();
        return true;
    }
    inline bool ApplySnapshot_OBS_CURR() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastOBSCURRInfo *info = (FastOBSCURRInfo *) this->m_fastProtocolManager->DecodeOBSCURR();
        this->m_incremental->OnFullRefresh_OBS_CURR_Start(info);
        this->m_incremental->OnFullRefresh_OBS_CURR(info);
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            this->m_incremental->OnFullRefresh_OBS_CURR(
                    (FastOBSCURRInfo *) this->m_fastProtocolManager->DecodeOBSCURR());
        }
        this->m_incremental->OnFullRefresh_OBS_CURR_End();
        return true;
    }
    inline bool ApplySnapshot_OLS_FOND() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastOLSFONDInfo *info = (FastOLSFONDInfo *) this->m_fastProtocolManager->DecodeOLSFOND();
        this->m_incremental->OnFullRefresh_OLS_FOND_Start(info);
        this->m_incremental->OnFullRefresh_OLS_FOND(info);
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            this->m_incremental->OnFullRefresh_OLS_FOND(
                    (FastOLSFONDInfo *) this->m_fastProtocolManager->DecodeOLSFOND());
        }
        this->m_incremental->OnFullRefresh_OLS_FOND_End();
        return true;
    }
    inline bool ApplySnapshot_OLS_CURR() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastOLSCURRInfo *info = (FastOLSCURRInfo *) this->m_fastProtocolManager->DecodeOLSCURR();
        this->m_incremental->OnFullRefresh_OLS_CURR_Start(info);
        this->m_incremental->OnFullRefresh_OLS_CURR(info);
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            this->m_incremental->OnFullRefresh_OLS_CURR(
                    (FastOLSCURRInfo *) this->m_fastProtocolManager->DecodeOLSCURR());
        }
        this->m_incremental->OnFullRefresh_OLS_CURR_End();
        return true;
    }
    inline bool ApplySnapshot_TLS_FOND() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastTLSFONDInfo *info = (FastTLSFONDInfo *) this->m_fastProtocolManager->DecodeTLSFOND();
        this->m_incremental->OnFullRefresh_TLS_FOND_Start(info);
        this->m_incremental->OnFullRefresh_TLS_FOND(info);
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            this->m_incremental->OnFullRefresh_TLS_FOND(
                    (FastTLSFONDInfo *) this->m_fastProtocolManager->DecodeTLSFOND());
        }
        this->m_incremental->OnFullRefresh_TLS_FOND_End();
        return true;
    }
    inline bool ApplySnapshot_TLS_CURR() {
        this->PrepareDecodeSnapshotMessage(this->m_snapshotRouteFirst);
        FastTLSCURRInfo *info = (FastTLSCURRInfo *) this->m_fastProtocolManager->DecodeTLSCURR();
        this->m_incremental->OnFullRefresh_TLS_CURR_Start(info);
        this->m_incremental->OnFullRefresh_TLS_CURR(info);
        for(int i = this->m_snapshotRouteFirst + 1; i <= this->m_snapshotLastFragment; i++) {
            if(!this->PrepareDecodeSnapshotMessage(i))
                continue;
            this->m_incremental->OnFullRefresh_TLS_CURR(
                    (FastTLSCURRInfo *) this->m_fastProtocolManager->DecodeTLSCURR());
        }
        this->m_incremental->OnFullRefresh_TLS_CURR_End();
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
        return true;
    }
    inline void MarketTableEnterSnapshotMode() {
        if(this->m_orderBookTableFond != 0) {
            this->m_orderBookTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_orderBookTableCurr != 0) {
            this->m_orderBookTableCurr->EnterSnapshotMode();
            return;
        }
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
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->EnterSnapshotMode();
            return;
        }
    }
    inline int SymbolsToRecvSnapshotCount() {
        if(this->m_orderBookTableFond != 0)
            return this->m_orderBookTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_orderBookTableCurr != 0)
            return this->m_orderBookTableCurr->SymbolsToRecvSnapshotCount();
        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->SymbolsToRecvSnapshotCount();
        if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_orderTableCurr != 0)
            return this->m_tradeTableCurr->SymbolsToRecvSnapshotCount();
        return 0;
    }
    inline void MarketTableExitSnapshotMode() {
        if(this->m_orderBookTableFond != 0) {
            this->m_orderBookTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_orderBookTableCurr != 0) {
            this->m_orderBookTableCurr->ExitSnapshotMode();
            return;
        }
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->ExitSnapshotMode();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_orderTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->ExitSnapshotMode();
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
	inline bool StopListenSnapshot() {
		if(!this->m_snapshot->Stop()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, false);
			return false;
		}
        this->MarketTableExitSnapshotMode();
		DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, true);
		return true;
	}
	inline FastSnapshotInfo* GetSnapshotInfo(int index) {
		BinaryLogItem *item = this->m_packets[index]->m_item;
		unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
		this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
		this->m_fastProtocolManager->ReadMsgSeqNumber();
		return this->m_fastProtocolManager->GetSnapshotInfo();
	}

    inline void ResetWaitTime() { this->m_waitTimer->Start(); }
    inline bool ActualMsgSeqNum() { return this->m_startMsgSeqNum == this->m_endMsgSeqNum; }

	inline void IncrementMsgSeqNo() { this->m_startMsgSeqNum++; }
	bool InitializeSockets();
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
            case FeedConnectionMessage::fmcFullRefresh_OBS_FOND:
                return this->ApplySnapshot_OBS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_OBS_CURR:
                return this->ApplySnapshot_OBS_CURR();
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
                break;
            }
        }
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
            this->SkipLostPackets();
            this->m_waitTimer->Stop(1);
            this->m_snapshotRouteFirst = -1;
            this->m_snapshotLastFragment = -1;
        }

        int snapshotCount = 0;
        while(TryFindAndApplySnapshot())
            snapshotCount++;


        /*
        while(this->m_startMsgSeqNum <= this->m_endMsgSeqNum) {
            if(this->m_packets[this->m_startMsgSeqNum] == 0) {
                if (!this->m_waitTimer->Active()) {
                    this->m_waitTimer->Start();
                }
                if (this->m_waitTimer->ElapsedSeconds() > 3) {
                    printf("  snapshot has empty packets.\n");
                    this->m_waitTimer->Stop();
                    this->StartNewSnapshot();
                }
                return true;
            }
            FastSnapshotInfo *info = this->GetSnapshotInfo(this->m_startMsgSeqNum);
            if(info == 0) {
                this->m_startMsgSeqNum++;
                continue;
            }
            printf("\t\t  message -> MsgSeqNum = %d, TemplateId = %d, SendingTime = %lu IsRouteFirst = %d, IsLastFragment = %d, LastMsgSeqProcessed = %d, RptSeq = %d\n",
                   this->m_startMsgSeqNum,
                   info->TemplateId,
                   info->SendingTime,
                   info->RouteFirst,
                   info->LastFragment, info->LastMsgSeqNumProcessed, info->RptSeq);
            if(this->m_snapshotRouteFirst == -1) {
                if (info->RouteFirst == 1) {
                    this->m_snapshotRouteFirst = this->m_startMsgSeqNum;
                }
                else {
                    this->m_startMsgSeqNum++;
                    continue;
                }
            }
            if (info->LastFragment == 0) {
                this->m_startMsgSeqNum++;
                continue;
            }
            this->m_snapshotLastFragment = this->m_startMsgSeqNum;
            this->m_startMsgSeqNum++;
            printf("\t\tFound Snapshot -> MsgSeqNum = %d, TemplateId = %d, SendingTime = %lu RouteFirst = %d, LastFragment = %d, LastMsgSeqProcessed = %d, RptSeq = %d\n",
                   this->m_startMsgSeqNum - 1,
                   info->TemplateId,
                   info->SendingTime,
                   this->m_snapshotRouteFirst,
                   this->m_snapshotLastFragment, info->LastMsgSeqNumProcessed, info->RptSeq);
            if (info->LastMsgSeqNumProcessed == 0 && info->RptSeq == 0) {
                printf("\t\tEmpty Snapshot -> Apply\n");
                this->m_waitTimer->Stop();
                return true;
            }
            if (info->LastMsgSeqNumProcessed < this->m_incremental->m_startMsgSeqNum) {
                printf("\t\tOutdated Snapshot. Need %d vs %d -> Continue\n",
                       this->m_incremental->m_startMsgSeqNum,
                       info->LastMsgSeqNumProcessed);
                this->m_snapshotRouteFirst = -1;
                this->m_snapshotLastFragment = -1;
                continue;
            }
            printf("\t\tCorrect Snapshot. Need %d vs %d - > Apply\n",
                   this->m_incremental->m_startMsgSeqNum,
                   info->LastMsgSeqNumProcessed);

            this->m_lastMsgSeqNumProcessed = info->LastMsgSeqNumProcessed;
            this->m_rptSeq = info->RptSeq;

            this->m_waitTimer->Stop();
            return true;
        }
        */

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

	bool Suspend_Atom();
	bool Listen_Atom();
    bool Listen_Atom_Incremental();
    bool Listen_Atom_Snapshot();
    bool SendLogon_Atom();
    bool ResendLastMessage_Atom();
    bool Reconnect_Atom();

    inline void ReconnectSetNextState(FeedConnectionState state) {
        this->m_waitTimer->Stop();
        this->SetNextState(state);
        this->SetState(FeedConnectionState::fcsConnect);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState);
    }

	FILE *obrLogFile;
	inline bool OnIncrementalRefresh_OBR_FOND(FastOBSFONDItemInfo *info) {
        return this->m_orderBookTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_OBR_CURR(FastOBSCURRItemInfo *info) {
		return true; // TODO!!!!!
        //return this->m_orderBookTableCurr->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_OLR_FOND(FastOLSFONDItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
        return true; // TODO!!!!!
		//return this->m_orderTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_OLR_CURR(FastOLSCURRItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
        return true; // TODO!!!!!
		//return this->m_orderTableCurr->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_TLR_FOND(FastTLSFONDItemInfo *info) {
        return true; // TODO!!!!!
		//return this->m_tradeTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_TLR_CURR(FastTLSCURRItemInfo *info) {
        return true; // TODO!!!!!
		//return this->m_tradeTableCurr->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_OBR_FOND(FastIncrementalOBRFONDInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_OBR_FOND(info->GroupMDEntries[i]);
		}
		return res;
	}

    inline bool OnIncrementalRefresh_OBR_CURR(FastIncrementalOBRCURRInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OBR_CURR(info->GroupMDEntries[i]);
        }
        return res;
    }

    inline bool OnIncrementalRefresh_OLR_FOND(FastIncrementalOLRFONDInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OLR_FOND(info->GroupMDEntries[i]);
        }
        return res;
    }

    inline bool OnIncrementalRefresh_OLR_CURR(FastIncrementalOLRCURRInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OLR_CURR(info->GroupMDEntries[i]);
        }
        return res;
    }

    inline bool OnIncrementalRefresh_TLR_FOND(FastIncrementalTLRFONDInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_TLR_FOND(info->GroupMDEntries[i]);
        }
        return res;
    }

    inline bool OnIncrementalRefresh_TLR_CURR(FastIncrementalTLRCURRInfo *info) {
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_TLR_CURR(info->GroupMDEntries[i]);
        }
        return res;
    }

    inline void OnFullRefresh_OBS_FOND_Start(FastOBSFONDInfo *info) {
        this->m_orderBookTableFond->StartProcessSnapshot(info);
    }

    inline void OnFullRefresh_OBS_FOND_End() {
        this->m_orderBookTableFond->EndProcessSnapshot();
    }

    inline void OnFullRefresh_OBS_FOND(FastOBSFONDInfo *info) {
        this->m_orderBookTableFond->ProcessSnapshot(info);
    }

    inline void OnFullRefresh_OBS_CURR_Start(FastOBSCURRInfo *info) {
        // TODO!!!!!
        //this->m_orderBookTableCurr->StartProcessSnapshot(info);
    }

    inline void OnFullRefresh_OBS_CURR_End() {
        // TODO!!!!!
        this->m_orderBookTableCurr->EndProcessSnapshot();
    }
    
    inline void OnFullRefresh_OBS_CURR(FastOBSCURRInfo *info) {
        // TODO!!!!!
        //return this->m_orderBookTableCurr->ProcessSnapshot(info);
	}

    inline void OnFullRefresh_OLS_FOND_Start(FastOLSFONDInfo *info) {
        // TODO!!!!!
        //this->m_orderTableFond->StartProcessSnapshot(info);
    }

    inline void OnFullRefresh_OLS_FOND_End() {
        // TODO!!!!!
        //this->m_orderTableFond->EndProcessSnapshot();
    }
    
	inline void OnFullRefresh_OLS_FOND(FastOLSFONDInfo *info) {
        // TODO!!!!!
		//return this->m_orderTableFond->ProcessSnapshot(info);
	}

    inline void OnFullRefresh_OLS_CURR_Start(FastOLSCURRInfo *info) {
        // TODO!!!!!
        //this->m_orderTableCurr->StartProcessSnapshot(info);
    }

    inline void OnFullRefresh_OLS_CURR_End() {
        // TODO!!!!!
        //this->m_orderTableCurr->EndProcessSnapshot();
    }
    
	inline void OnFullRefresh_OLS_CURR(FastOLSCURRInfo *info) {
        // TODO!!!!!
		//return this->m_orderTableCurr->ProcessSnapshot(info);
	}

    inline void OnFullRefresh_TLS_FOND_Start(FastTLSFONDInfo *info) {
        // TODO!!!!!
        //this->m_tradeTableFond->StartProcessSnapshot(info);
    }
    
    inline void OnFullRefresh_TLS_FOND_End() {
        // TODO!!!!!
        //this->m_tradeTableFond->EndProcessSnapshot();
    }

	inline void OnFullRefresh_TLS_FOND(FastTLSFONDInfo *info) {
        // TODO!!!!!
		//return this->m_tradeTableFond->ProcessSnapshot(info);
	}

    inline void OnFullRefresh_TLS_CURR_Start(FastTLSCURRInfo *info) {
        // TODO!!!!!
        //this->m_tradeTableCurr->StartProcessSnapshot(info);
    }

    inline void OnFullRefresh_TLS_CURR_End() {
        // TODO!!!!!
        //this->m_tradeTableCurr->EndProcessSnapshot();
    }
    
	inline void OnFullRefresh_TLS_CURR(FastTLSCURRInfo *info) {
        // TODO!!!!!
        //return this->m_tradeTableCurr->ProcessSnapshot(info);
	}

	inline bool ApplyIncrementalCore() {
		switch(this->m_fastProtocolManager->TemplateId()) {
			case FeedConnectionMessage::fcmHeartBeat:
				break;
			case FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND:
				return this->OnIncrementalRefresh_OBR_FOND((FastIncrementalOBRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OBR_CURR:
				return this->OnIncrementalRefresh_OBR_CURR((FastIncrementalOBRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
				return this->OnIncrementalRefresh_OLR_FOND((FastIncrementalOLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
				return this->OnIncrementalRefresh_OLR_CURR((FastIncrementalOLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
				return this->OnIncrementalRefresh_TLR_FOND((FastIncrementalTLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
				return this->OnIncrementalRefresh_TLR_CURR((FastIncrementalTLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
		}
		return true;
	}

	inline bool ProcessIncrementalCore(unsigned char *buffer, int length) {
		this->m_fastProtocolManager->SetNewBuffer(buffer, length);
		this->m_fastProtocolManager->ReadMsgSeqNumber();

		if(this->m_fastProtocolManager->Decode() == 0)
			return true;
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
		if(this->ShouldSkipMessage(buffer))
			return true;  // TODO - take this message into account, becasue it determines feed alive

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
        info->m_processed = true;
		return this->ProcessIncremental(buffer, this->m_recvABuffer->ItemLength(info->m_item->m_itemIndex));
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	FeedConnection();
	~FeedConnection();

    inline void FakeConnect(bool value) { this->m_fakeConnect = value; }
    inline int LastMsgSeqNumProcessed() { return this->m_lastMsgSeqNumProcessed; }
	inline MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *OrderBookFond() { return this->m_orderBookTableFond; }
	inline MarketDataTable<OrderBookInfo, FastOBSCURRInfo, FastOBSCURRItemInfo> *OrderBookCurr() { return this->m_orderBookTableCurr; }
	inline MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo> *OrderFond() { return this->m_orderTableFond; }
	inline MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo> *OrderCurr() { return this->m_orderTableCurr; }
	inline MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo> *TradeFond() { return this->m_tradeTableFond; }
	inline MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo> *TradeCurr() { return this->m_tradeTableCurr; }
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

    inline char* Id() { return this->id; }

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
        if(st == FeedConnectionState::fcsListenSnapshot)
            return this->Listen_Atom_Snapshot();
        if(st == FeedConnectionState::fcsSuspend)
            return true;
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;

	}
	inline void Listen() {
        FeedConnectionState st = this->m_type == FeedConnectionType::Incremental?
                                FeedConnectionState::fcsListenIncremental:
                                FeedConnectionState::fcsListenSnapshot;
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
};

class FeedConnection_CURR_OBR : public FeedConnection {
public:
	FeedConnection_CURR_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {

		this->SetType(FeedConnectionType::Incremental);
		this->m_orderBookTableCurr = new MarketDataTable<OrderBookInfo, FastOBSCURRInfo, FastOBSCURRItemInfo>();
    }
	FeedConnection_CURR_OBR() : FeedConnection() {
		this->m_orderBookTableCurr = new MarketDataTable<OrderBookInfo, FastOBSCURRInfo, FastOBSCURRItemInfo>();
	}
	~FeedConnection_CURR_OBR() {
		delete this->m_orderBookTableCurr;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OBS : public FeedConnection {
public:
	FeedConnection_CURR_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	FeedConnection_CURR_OBS() : FeedConnection() { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSR : public FeedConnection {
public:
	FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
    }
	FeedConnection_CURR_MSR() : FeedConnection() { }
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
    }
	FeedConnection_CURR_MSS() : FeedConnection() { }
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
    }
	FeedConnection_CURR_OLR() : FeedConnection() {
		this->m_orderTableCurr = new MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>();
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
    }
	FeedConnection_CURR_OLS() : FeedConnection() { }
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
    }
	FeedConnection_CURR_TLR() : FeedConnection() {
		this->m_tradeTableCurr = new MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>();
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

    }
	FeedConnection_CURR_TLS() : FeedConnection() { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBR : public FeedConnection {
public:
	FeedConnection_FOND_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_orderBookTableFond = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();
    }
	FeedConnection_FOND_OBR() : FeedConnection() {
		this->m_orderBookTableFond = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();
	}
	~FeedConnection_FOND_OBR() {
		delete this->m_orderBookTableFond;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBS : public FeedConnection {
public:
	FeedConnection_FOND_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	FeedConnection_FOND_OBS() : FeedConnection() { }
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
    }
	FeedConnection_FOND_MSR() : FeedConnection() { }
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
    }
	FeedConnection_FOND_MSS() : FeedConnection() { }
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
    }
	FeedConnection_FOND_OLR() : FeedConnection() {
		this->m_orderTableFond = new MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>();
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
    }
	FeedConnection_FOND_OLS() : FeedConnection() { }
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
    }
	FeedConnection_FOND_TLR() : FeedConnection() {
		this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
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
    }
	FeedConnection_FOND_TLS() : FeedConnection() { }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

