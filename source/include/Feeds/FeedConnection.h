#pragma once
#include "../Managers/WinSockManager.h"
#include "../Fast/FastProtocolManager.h"
#include "../Fix/FixProtocolManager.h"
#include "../Settings.h"
#include <sys/time.h>
#include "../Stopwatch.h"
#include "../Lib/AutoAllocatePointerList.h"
#include "../Lib/StringIdComparer.h"
#include "../MarketData/MarketDataTable.h"
#include "../MarketData/OrderInfo.h"
#include "../MarketData/OrderBookInfo.h"
#include "../MarketData/TradeInfo.h"
#include "../MarketData/StatisticInfo.h"
#include "../MarketData/SymbolManager.h"
#include "../ConnectionParameters.h"
#include "FeedTypes.h"
#include "../Managers/DebugInfoManager.h"
#include "../ProgramStatistics.h"
class OrderBookTesterForts;
class OrderTesterFond;
class OrderTesterCurr;
class TradeTesterFond;
class TradeTesterCurr;
class TestMessagesHelper;
class StatisticsTesterFond;
class StatisticsTesterCurr;
class SecurityDefinitionTester;
class SecurityStatusTester;
class DebugInfoManager;
class HistoricalReplayTester;

#define max_fast(x, y) (x ^ ((x ^ y) & -(x < y)))
class FeedConnection {
    friend class OrderTesterFond;
    friend class OrderTesterCurr;
    friend class TradeTesterFond;
    friend class TradeTesterCurr;
    friend class FeedConnectionTester;
    friend class TestMessagesHelper;
    friend class StatisticsTesterFond;
    friend class StatisticsTesterCurr;
    friend class SecurityDefinitionTester;
    friend class SecurityStatusTester;
    friend class DebugInfoManager;
    friend class HistoricalReplayTester;
    friend class OrderBookTesterForts;

public:
    static const int MaxReceiveBufferSize                      = 1500;
    static const int WaitAnyPacketMaxTimeMcs                   = 4000000;
    static const int WaitAnyPacketFortsMaxTimeMcs              = 40000000;
    static const int WaitSecurityStatusFortsMaxTimeMcs         = 120000000;
    static const int MaxHrUnsuccessfulConnectCount             = 20;
    static const int WaitSecurityDefinitionPacketMaxTimeMcs    = 20000000;
protected:
    WinSockManager                              *socketAManager;
    WinSockManager                              *socketBManager;
    unsigned char                               *m_recvBuffer;
    unsigned char                               *m_recvBufferCurrentPos;
    FeedConnectionMessageInfo                   **m_packets;

    int                                         m_windowMsgSeqNum;
    int                                         m_startMsgSeqNum;
    int                                         m_endMsgSeqNum;
    int                                         m_packetsCount;

    FeedConnection                              *m_snapshot;
    Stopwatch                                   *m_waitTimer;

    SymbolManager                               *m_symbolManager;
    FastProtocolManager                         *m_fastProtocolManager;

    FeedConnectionState                         m_state;
    int                                         m_symbolsToRecvSnapshot;

    MarketDataTable<OrderInfo, AstsOLSFONDInfo, AstsOLSFONDItemInfo>            *m_orderTableFond;
    MarketDataTable<OrderInfo, AstsOLSCURRInfo, AstsOLSCURRItemInfo>            *m_orderTableCurr;
    MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo>           *m_fortsOrderBookTable;

    LinkedPointer<FortsSecurityDefinitionInfo>  **m_symbolsForts;

    int                                         m_queueItemsCount;
    int                                         m_fortsIncrementalRouteFirst;
    int                                         m_fortsRouteFirtsSecurityId;
    int                                         m_lostPacketCount;
    int                                         m_snapshotRouteFirst;
    int                                         m_snapshotLastFragment;
    int                                         m_nextFortsSnapshotRouteFirst;
    int                                         m_lastMsgSeqNumProcessed;
    int                                         m_rptSeq;
    FeedConnectionProtocol                      protocol;

    AstsSnapshotInfo                            *m_astsSnapshotInfo;
    FortsSnapshotInfo                           *m_fortsSnapshotInfo;
    MarketDataTable<TradeInfo, AstsTLSFONDInfo, AstsTLSFONDItemInfo>            *m_tradeTableFond;
    MarketDataTable<TradeInfo, AstsTLSCURRInfo, AstsTLSCURRItemInfo>            *m_tradeTableCurr;
    MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo>       *m_statTableFond;
    MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo>       *m_statTableCurr;
    MarketDataTable<TradeInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo>               *m_fortsTradeBookTable;

    LinkedPointer<AstsSecurityDefinitionInfo>   **m_symbols;
    int                                         m_symbolsCount;
    FeedConnectionType                          m_type;
    FeedConnectionId                            m_id;
    FeedMarketType                              m_marketType;

    char                                        m_idName[128];
    char                                        m_channelName[128];
    char                                        feedTypeName[128];

    FeedConnection                              *m_incremental;
    FeedConnection                              *m_historicalReplay;
    FeedConnection                              *m_securityDefinition;
    FeedConnection                              *m_connectionsToRecvSymbols[32];
    FeedConnection                              *m_connToRecvHistoricalReplay[32];

    int                                         m_connectionsToRecvSymbolsCount;
    int                                         m_connToRecvHistoricalReplayCount;

    FortsTradingSessionStatusInfo               *m_fortsTradingSessionStatus;

    FeedConnectionSecurityDefinitionMode        m_idfMode;
    FeedConnectionSecurityDefinitionState       m_idfState;
    int                                         m_idfMaxMsgSeqNo;
    int                                         m_idfStartMsgSeqNo;
    int                                         m_isfStartSnapshotCount;
    int                                         m_hrMessageSize;

    FeedConnection                                 *m_idfSnapshotClient;
    PointerList<FeedConnectionRequestMessageInfo>  *m_hsRequestList;

    FeedConnectionHistoricalReplayState             m_hsState;
    int                                             m_hrSizeRemain;
    int                                             m_hrUnsuccessfulConnectCount;
    int                                             m_requestMessageStartIndex;


    int                                             m_idLogIndex;
    int                                             m_feedTypeNameLogIndex;

    char                                        feedASourceIp[64];
    char                                        feedAIp[64];
    char                                        feedBSourceIp[64];
    char                                        feedBIp[64];

    int                                         feedBPort;
    int                                         feedAPort;

    const char                                  *m_senderCompId;
    const char                                  *m_password;
    int                                         m_senderCompIdLength;
    int                                         m_passwordLength;

    AstsLogonInfo                               *m_fastLogonInfo;
    FixProtocolManager                          *m_fixProtocolManager;
    FixLogonInfo                                *m_hsLogonInfo;
    FixRejectInfo                               *m_hsRejectInfo;

    FeedConnectionState                         m_nextState;
    int                                          m_hsMsgSeqNo;
    int                                         m_reconnectCount;
    int                                         m_maxReconnectCount;

    unsigned int                                m_recvBufferSize;
    unsigned int                                m_sendBufferSize;
    unsigned char                               *m_sendBuffer;
    unsigned char                               *m_sendBufferCurrentPos;
    ISocketBufferProvider                       *m_socketABufferProvider;

#ifdef TEST
    int                                         m_waitLostIncrementalMessageMaxTimeMcs;
    int                                         m_waitIncrementalMessageMaxTimeMcs;
    int                                         m_waitIncrementalMessageMaxTimeMcsForts;
    int                                         m_snapshotMaxTimeMcs;
#else
    const int                                   m_waitLostIncrementalMessageMaxTimeMcs = 100000;
    const int                                   m_waitIncrementalMessageMaxTimeMcs = 4000000;
    const int                                   m_waitIncrementalMessageMaxTimeMcsForts = 40000000;
    const int                                   m_snapshotMaxTimeMcs = 30000;
#endif
#ifdef TEST
    TestMessagesHelper                          *m_testHelper;
#endif

    int                                         m_maxLostPacketCountForStartSnapshot;
    char                                        feedTypeValue;
    bool                                        m_tableInSnapshotMode;
    bool                                        m_enableHistoricalReplay;
    bool                                        m_allowSaveSecurityDefinitions;
    bool                                        m_idfDataCollected;
    bool                                        m_idfAllowUpdateData;
    bool                                        m_idfStopAfterUpdateAllMessages;
    bool                                        m_allowGenerateSecurityDefinitions;
    bool                                        m_securityStatusSnapshotActive;
    bool                                        m_shouldReceiveAnswer;
    bool                                        m_shouldUseNextState;
    bool                                        m_paddingByte;

    void InitializeHistoricalReplay() {
        this->m_hsRequestList = new PointerList<FeedConnectionRequestMessageInfo>(RobotSettings::Default->HistoricalReplayMaxMessageRequestCount);
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
    int GetPacketsCount() { throw; }
    void InitializePackets(int count) {
        this->m_packetsCount = count;
        this->m_packets = new FeedConnectionMessageInfo*[ this->m_packetsCount ];
        for(int i = 0; i < this->m_packetsCount; i++)
            this->m_packets[i] = new FeedConnectionMessageInfo();
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnectionInfo::InitializePackets");
    }
    void InitializeSecurityDefinitionForts() {
        this->m_symbolsForts = new LinkedPointer<FortsSecurityDefinitionInfo>*[RobotSettings::Default->MaxSecurityDefinitionCount];
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++)
            this->m_symbolsForts[i] = new LinkedPointer<FortsSecurityDefinitionInfo>();
        this->m_symbolsCount = 0;
        this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->m_symbolManager = new SymbolManager(RobotSettings::Default->MarketDataMaxSymbolsCountForts, true, SymbolHashType::Last4Chars);
    }
    void InitializeSecurityDefinition() {
        InitializeSecurityDefinition(SymbolHashType::Last4Chars);
    }
    void InitializeSecurityDefinition(SymbolHashType hashType) {
        this->m_symbols = new LinkedPointer<AstsSecurityDefinitionInfo>*[RobotSettings::Default->MaxSecurityDefinitionCount];
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++)
            this->m_symbols[i] = new LinkedPointer<AstsSecurityDefinitionInfo>();
        this->m_symbolsCount = 0;
        this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->m_symbolManager = new SymbolManager(RobotSettings::Default->MarketDataMaxSymbolsCount, hashType);
    }
    void DisposeSecurityDefinitionForts() {
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++)
            delete this->m_symbolsForts[i];
        delete this->m_symbolsForts;
    }
    void DisposeSecurityDefinition() {
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++)
            delete this->m_symbols[i];
        delete this->m_symbols;
    }

    inline int TryGetSecurityDefinitionTotNumReportsAsts(unsigned char *buffer) {
        this->m_fastProtocolManager->SetNewBuffer(buffer + 4);
        this->m_fastProtocolManager->DecodeAstsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fmcSecurityDefinition)
            return 0;
        return this->m_fastProtocolManager->GetAstsTotalNumReports();
    }

    inline int TryGetSecurityDefinitionTotNumReportsForts(unsigned char *buffer) {
        this->m_fastProtocolManager->SetNewBuffer(buffer + 4);
        this->m_fastProtocolManager->DecodeFortsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fortsSecurityDefinition)
            return 0;
        return this->m_fastProtocolManager->GetFortsTotalNumReports();
    }

    inline int TryGetSecurityDefinitionTotNumReports(unsigned char *buffer) {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return this->TryGetSecurityDefinitionTotNumReportsAsts(buffer);
        return this->TryGetSecurityDefinitionTotNumReportsForts(buffer);
    }

    void ThreatFirstMessageIndexAsStart() {
        this->m_startMsgSeqNum = -1;
        this->m_endMsgSeqNum = 0;
    }

    inline FeedConnectionMessageInfo* Packet(int index) { return this->m_packets[index - this->m_windowMsgSeqNum]; }
    inline bool SupportWindow() {
        return this->m_type == FeedConnectionType::fctIncremental ||
                this->m_type == FeedConnectionType::fctIncrementalForts ||
                this->m_type == FeedConnectionType::fctInstrumentStatus ||
                this->m_type == FeedConnectionType::fctInstrumentStatusForts;
    }

    inline bool ProcessServerCoreIncremental_HistoricalReplay(unsigned char *buffer, int size, int msgSeqNum) {
        if(msgSeqNum < this->m_windowMsgSeqNum) // out of window
            return true;
        if(msgSeqNum - this->m_windowMsgSeqNum >= this->m_packetsCount) {
            // we should start snapshot
            OnMsgSeqNumOutOfBounds(msgSeqNum, size);
            return false;
        }
        FeedConnectionMessageInfo *info = this->Packet(msgSeqNum);
        if(info->m_address != 0) // already recv
            return true;

        if(this->m_endMsgSeqNum < msgSeqNum)
            this->m_endMsgSeqNum = msgSeqNum;

        info->m_address = buffer;
        info->m_size = size;
        info->m_requested = true;
        return true;
    }
    inline bool ProcessServerCoreSecurityStatus_HistoricalReplay(unsigned char *buffer, int size, int msgSeqNum) {
        int localMsgSeqNum = msgSeqNum - this->m_windowMsgSeqNum;
        if(localMsgSeqNum < 0) // out of window
            return true;
        if(localMsgSeqNum >= this->m_packetsCount) {
            // we should start snapshot
            this->StartSecurityStatusSnapshot();
            return false;
        }
        FeedConnectionMessageInfo *info = this->m_packets[localMsgSeqNum];
        if(info->m_address != 0) // already recv
            return true;

        if(this->m_endMsgSeqNum < msgSeqNum)
            this->m_endMsgSeqNum = msgSeqNum;
        if(this->m_startMsgSeqNum == -1) // should we do this? well security status starts immediately after security definition so...
            this->m_startMsgSeqNum = msgSeqNum;

        info->m_address = buffer;
        info->m_size = size;
        info->m_requested = true;
        return true;
    }
    inline bool ProcessServerCore_FromHistoricalReplay(unsigned char *buffer, int size, int msgSeqNum) {
        // we should only process incremental messages
        if(this->m_type == FeedConnectionType::fctIncremental || this->m_type == FeedConnectionType::fctIncrementalForts)
            return ProcessServerCoreIncremental_HistoricalReplay(buffer, size, msgSeqNum);
        if(this->m_type == FeedConnectionType::fctInstrumentStatus)
            return ProcessServerCoreSecurityStatus_HistoricalReplay(buffer, size, msgSeqNum);
        return true;
    }

    inline bool ProcessServerCoreSecurityDefinition(int size, int msgSeqNum) {
        this->m_endMsgSeqNum = msgSeqNum;

        FeedConnectionMessageInfo *info = this->m_packets[msgSeqNum];
        if(info->m_address != null)
            return true;

        if(this->m_idfStartMsgSeqNo == 0)
            this->m_idfStartMsgSeqNo = msgSeqNum;
        if(this->m_idfMaxMsgSeqNo == 0)
            this->m_idfMaxMsgSeqNo = TryGetSecurityDefinitionTotNumReports(this->m_recvBufferCurrentPos);

        info->m_address = this->m_recvBufferCurrentPos + 4;
        info->m_size = size - 4;
        this->NextRecv(size);
        return true;
    }
    inline bool ProcessServerCoreSnapshot(int size, int msgSeqNum) {
        FeedConnectionMessageInfo *info = this->m_packets[msgSeqNum];

        if(info->m_address != 0)
            return true;

        if(this->m_startMsgSeqNum == -1) { // initialization
            this->m_startMsgSeqNum = msgSeqNum;
            this->m_endMsgSeqNum = msgSeqNum;
        }
        else { // normal cycle
            if(this->m_endMsgSeqNum < msgSeqNum) // recv next message
                this->m_endMsgSeqNum = msgSeqNum;
            else { // some kind of previous message
                if(this->m_endMsgSeqNum > msgSeqNum && msgSeqNum == 1) { // new cycle detected
                    if (this->m_snapshotRouteFirst != -1)
                        this->ClearPackets(this->m_snapshotRouteFirst, this->m_startMsgSeqNum);
                    this->ClearPackets(this->m_startMsgSeqNum, this->m_endMsgSeqNum);
                    this->m_startMsgSeqNum = msgSeqNum;
                    this->m_endMsgSeqNum = msgSeqNum;
                }
            }
            if(msgSeqNum < this->m_startMsgSeqNum) // recv already processed message
                return false;
        }

        //printf("%s \"%s\"\n", this->m_idName, DebugInfoManager::Default->BinaryToString(this->m_recvBufferCurrentPos, size));
        info->m_address = this->m_recvBufferCurrentPos + 4;
        info->m_size = size;
        this->NextRecv(size);
        return true;
    }
    __attribute__((noinline))
    void OnMsgSeqNumOutOfBounds(int msgSeqNum, int size) {
        this->ClearLocalPackets(0, this->GetLocalIndex(this->m_endMsgSeqNum));
        this->m_startMsgSeqNum = msgSeqNum;
        this->m_windowMsgSeqNum = msgSeqNum;
        this->m_endMsgSeqNum = msgSeqNum;

        FeedConnectionMessageInfo *info = this->Packet(msgSeqNum);
        info->m_address = this->m_recvBufferCurrentPos + 4;
        info->m_size = size;
        this->NextRecv(size);

        this->StartListenSnapshot();
    }
    __attribute__((noinline))
    bool OnProcessServerCoreIncrementalNonNextItem(int size, int msgSeqNum) {
        //printf("non next    item inc %d s = %d e = %d w = %d\n", msgSeqNum, this->m_startMsgSeqNum, this->m_endMsgSeqNum, this->m_windowMsgSeqNum);
        int localMsgSeqNum = msgSeqNum - this->m_windowMsgSeqNum;
        if(localMsgSeqNum < 0) // out of window
            return true;
        if(localMsgSeqNum >= this->m_packetsCount) {
            // we should start snapshot
            OnMsgSeqNumOutOfBounds(msgSeqNum, size);
            return false;
        }
        FeedConnectionMessageInfo *info = this->m_packets[localMsgSeqNum];
        if(info->m_address != 0) // already recv
            return true;

        if(this->m_endMsgSeqNum < msgSeqNum)
            this->m_endMsgSeqNum = msgSeqNum;
        info->m_address = this->m_recvBufferCurrentPos + 4;
        info->m_size = size;
        //printf("%s \"%s\"\n", this->m_idName, DebugInfoManager::Default->BinaryToString(this->m_recvBufferCurrentPos, size));
        this->NextRecv(size);
        return true;
    }
    inline bool ProcessServerCoreIncremental(int size, int msgSeqNum) {
        if(this->m_windowMsgSeqNum == msgSeqNum && msgSeqNum == this->m_endMsgSeqNum + 1) { // next packet received...
            this->m_endMsgSeqNum = msgSeqNum;
            int localMsgSeqNum = msgSeqNum - this->m_windowMsgSeqNum;
            FeedConnectionMessageInfo *info = this->m_packets[localMsgSeqNum];
            info->m_address = this->m_recvBufferCurrentPos + 4;
            info->m_size = size;
            //printf("%s \"%s\"\n", this->m_idName, DebugInfoManager::Default->BinaryToString(this->m_recvBufferCurrentPos, size));
            this->NextRecv(size);
            return true;
        }
        if(msgSeqNum == this->m_endMsgSeqNum)
            return true;
        return OnProcessServerCoreIncrementalNonNextItem(size, msgSeqNum);
    }
    __attribute__((noinline))
    void OnMsgSeqNumOutOfBoundsSecurityStatus(int msgSeqNum) {
        this->ClearLocalPackets(0, this->GetLocalIndex(this->m_endMsgSeqNum));
        this->m_startMsgSeqNum = msgSeqNum;
        this->m_windowMsgSeqNum = msgSeqNum;
        this->m_endMsgSeqNum = msgSeqNum;
        // we should start snapshot
        this->StartSecurityStatusSnapshot();
    }
    inline bool OnProcessServerCoreSecurityStatusNonNextItem(int size, int msgSeqNum) {
        int local = msgSeqNum - this->m_windowMsgSeqNum;
        if(local < 0) // out of window
            return true;
        if(local >= this->m_packetsCount) {
            OnMsgSeqNumOutOfBoundsSecurityStatus(msgSeqNum);
            return false;
        }
        FeedConnectionMessageInfo *info = this->m_packets[local];
        if(info->m_address != 0) // already recv
            return true;

        this->m_endMsgSeqNum = max_fast(this->m_endMsgSeqNum, msgSeqNum);
        //if(this->m_startMsgSeqNum == -1) // should we do this? well security status starts immediately after security definition so...
        //    this->m_startMsgSeqNum = msgSeqNum;

        info->m_address = this->m_recvBufferCurrentPos + 4;
        info->m_size = size;
        this->NextRecv(size);
        return true;
    }
    inline bool ProcessServerCoreSecurityStatusAsts(int size, UINT64 data) {
        int msgSeqNum = ((int)data);
        if(this->m_windowMsgSeqNum == msgSeqNum && msgSeqNum == this->m_endMsgSeqNum + 1) { // next item
            this->m_endMsgSeqNum = msgSeqNum;
            if(ShouldSkipMessageAsts(data)) {
                msgSeqNum++;
                this->m_startMsgSeqNum = msgSeqNum;
                this->m_windowMsgSeqNum = msgSeqNum;
                return true;
            }
            FeedConnectionMessageInfo *info = this->m_packets[msgSeqNum - this->m_windowMsgSeqNum];
            info->m_address = this->m_recvBufferCurrentPos + 4;
            info->m_size = size;
            this->NextRecv(size);
            return true;
        }
        return OnProcessServerCoreSecurityStatusNonNextItem(size, msgSeqNum);
    }
    inline bool ProcessServerCoreSecurityStatusForts(int size, UINT64 data) {
        int msgSeqNum = ((int)data);
        if(this->m_windowMsgSeqNum == msgSeqNum && msgSeqNum == this->m_endMsgSeqNum + 1) { // next item
            this->m_endMsgSeqNum = msgSeqNum;
            if(ShouldSkipMessageForts(data)) {
                msgSeqNum++;
                this->m_startMsgSeqNum = msgSeqNum;
                this->m_windowMsgSeqNum = msgSeqNum;
                return true;
            }
            int localMsgSeqNum = msgSeqNum - this->m_windowMsgSeqNum;
            FeedConnectionMessageInfo *info = this->m_packets[localMsgSeqNum];
            info->m_address = this->m_recvBufferCurrentPos + 4;
            info->m_size = size;
            this->NextRecv(size);
            return true;
        }
        return OnProcessServerCoreSecurityStatusNonNextItem(size, msgSeqNum);
    }
#pragma region ProcessSever
#ifdef TEST
    inline bool DebugProcessServerCore(int size) {
        int msgSeqNum = *((UINT*)this->m_recvBufferCurrentPos);

        if(this->m_type == FeedConnectionType::fctIncremental || this->m_type == FeedConnectionType::fctIncrementalForts)
            return ProcessServerCoreIncremental(size, msgSeqNum);
        if(this->m_type == FeedConnectionType::fctInstrumentStatus)
            return ProcessServerCoreSecurityStatusAsts(size, *((UINT64*)this->m_recvBufferCurrentPos));
        if(this->m_type == FeedConnectionType::fctInstrumentStatusForts)
            return ProcessServerCoreSecurityStatusForts(size, *((UINT64*)this->m_recvBufferCurrentPos));
        if(this->m_type == FeedConnectionType::fctSnapshot)
            return ProcessServerCoreSnapshot(size, msgSeqNum);
        if(this->m_type == FeedConnectionType::fctInstrumentDefinition)
            return ProcessServerCoreSecurityDefinition(size, msgSeqNum);
        return false;
    }
#endif
    // in a case we have received NEXT msg in socket A
    inline void FlushSocketBManager() {
        this->socketBManager->FlushUDP();
    }

    __attribute__((noinline))
    void OnFailProcessSocketManager(WinSockManager *socketManager) {
        DefaultLogManager::Default->WriteSuccess(socketManager->SocketLogName(),
                                                 LogMessageCode::lmcFeedConnection_Listen_Atom,
                                                 false)->m_errno = errno;
        socketManager->Reconnect();
    }

    inline int ProcessSocketManager(WinSockManager *socketManager) {
        if(!socketManager->RecvUDP(this->m_recvBufferCurrentPos)) {
            OnFailProcessSocketManager(socketManager);
            return 0;
        }
        return socketManager->RecvSize();
    }

    inline bool ProcessServerIncremental(WinSockManager *socketManager) {
        if(!socketManager->ShouldRecv())
            return false;
        unsigned char *current = this->m_recvBufferCurrentPos;
        if(!socketManager->RecvUDP(current)) {
            OnFailProcessSocketManager(socketManager);
            return false;
        }
        return ProcessServerCoreIncremental(socketManager->RecvSize(), *((UINT*)current));
    }
    inline bool ProcessServerAIncremental() { return this->ProcessServerIncremental(this->socketAManager); }
    inline bool ProcessServerBIncremental() { return this->ProcessServerIncremental(this->socketBManager); }

    inline bool ProcessServerSecurityStatusAsts(WinSockManager *socketManager) {
        if(!socketManager->ShouldRecv())
            return false;
        unsigned char *current = this->m_recvBufferCurrentPos;
        if(!socketManager->RecvUDP(current)) {
            OnFailProcessSocketManager(socketManager);
            return false;
        }
        return ProcessServerCoreSecurityStatusAsts(socketManager->RecvSize(), *((UINT64*)current));
    }

    inline bool ProcessServerSecurityStatusForts(WinSockManager *socketManager) {
        if(!socketManager->ShouldRecv())
            return false;
        unsigned char *current = this->m_recvBufferCurrentPos;
        if(!socketManager->RecvUDP(current)) {
            OnFailProcessSocketManager(socketManager);
            return false;
        }
        return ProcessServerCoreSecurityStatusForts(socketManager->RecvSize(), *((UINT64*)current));
    }

    inline bool ProcessServerASecurityStatusAsts() { return this->ProcessServerSecurityStatusAsts(this->socketAManager); }
    inline bool ProcessServerBSecurityStatusAsts() { return this->ProcessServerSecurityStatusAsts(this->socketBManager); }

    inline bool ProcessServerASecurityStatusForts() { return this->ProcessServerSecurityStatusForts(this->socketAManager); }
    inline bool ProcessServerBSecurityStatusForts() { return this->ProcessServerSecurityStatusForts(this->socketBManager); }

    inline bool ProcessServerSnapshot(WinSockManager *socketManager) {
        int size = this->ProcessSocketManager(socketManager);
        if(size == 0)
            return false;
        return ProcessServerCoreSnapshot(socketManager->RecvSize(), *((UINT32*)this->m_recvBufferCurrentPos));
    }
    inline bool ProcessServerASnapshot() { return this->ProcessServerSnapshot(this->socketAManager); }
    inline bool ProcessServerBSnapshot() { return this->ProcessServerSnapshot(this->socketBManager); }

    inline bool ProcessServerSecurityDefinition(WinSockManager *socketManager) {
        int size = this->ProcessSocketManager(socketManager);
        if(size == 0)
            return false;
        return ProcessServerCoreSecurityDefinition(size, *((UINT32*)this->m_recvBufferCurrentPos));
    }
    inline bool ProcessServerASecurityDefinition() { return this->ProcessServerSecurityDefinition(this->socketAManager); }
    inline bool ProcessServerBSecurityDefinition() { return this->ProcessServerSecurityDefinition(this->socketBManager); }

#pragma endregion
    inline bool HasQueueEntries() { return this->m_queueItemsCount > 0; }

    inline bool ShouldRestoreIncrementalMessages() {
        return this->HasPotentiallyLostPackets() || this->HasQueueEntries();
    }

    inline bool CanStopListeningSnapshot() {
        return this->SymbolsToRecvSnapshotCount() == 0 && !this->HasQueueEntries();
    }

#pragma region snapshot
    inline bool PrepareDecodeSnapshotMessageCore(int packetIndex) {
        FeedConnectionMessageInfo *info = this->m_packets[packetIndex];
        unsigned char *buffer = info->m_address;
        if(this->ShouldSkipMessageAsts(buffer))
            return false;
        this->m_fastProtocolManager->SetNewBuffer(buffer);
        return true;
    }
    inline bool PrepareDecodeSnapshotMessage(int packetIndex) {
        if(!this->PrepareDecodeSnapshotMessageCore(packetIndex))
            return false;
        this->m_fastProtocolManager->DecodeAstsHeader();
        return true;
    }

    inline int GetAstsSnapshotSymbolIndex() {
        return this->m_symbolManager->GetSymbol(this->m_astsSnapshotInfo->Symbol, this->m_astsSnapshotInfo->SymbolLength)->m_index;
    }

    inline bool StartApplySnapshot_OLS_FOND() {
        this->m_incremental->OrderFond()->ObtainSnapshotItem(this->GetAstsSnapshotSymbolIndex(), this->m_astsSnapshotInfo);
        if(this->m_incremental->OrderFond()->ApplyQuickSnapshot(this->m_astsSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->Inc(Counters::cFondOls);
            ProgramStatistics::Total->Inc(Counters::cFondOls);
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->OrderFond()->StartProcessSnapshot();
        this->ApplySnapshotPart_OLS_FOND(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_OLS_FOND(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cFondOls);
        ProgramStatistics::Total->Inc(Counters::cFondOls);
#endif
        AstsOLSFONDInfo *info = this->m_fastProtocolManager->DecodeAstsOLSFOND();
        this->m_incremental->OrderFond()->ProcessSnapshot(info);
        return true;
    }

    inline bool EndApplySnapshot_OLS_FOND() {
        this->m_incremental->OrderFond()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_OLS_FOND() {
        this->m_incremental->OrderFond()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_OLS_CURR() {
        this->m_incremental->OrderCurr()->ObtainSnapshotItem(this->GetAstsSnapshotSymbolIndex(), this->m_astsSnapshotInfo);
        if(this->m_incremental->OrderCurr()->ApplyQuickSnapshot(this->m_astsSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->Inc(Counters::cCurrOls);
            ProgramStatistics::Total->Inc(Counters::cCurrOls);
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->OrderCurr()->StartProcessSnapshot();
        this->ApplySnapshotPart_OLS_CURR(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_OLS_CURR(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cCurrOls);
        ProgramStatistics::Total->Inc(Counters::cCurrOls);
#endif
        AstsOLSCURRInfo *info = this->m_fastProtocolManager->DecodeAstsOLSCURR();
        this->m_incremental->OrderCurr()->ProcessSnapshot(info);
        return true;
    }

    inline bool EndApplySnapshot_OLS_CURR() {
        this->m_incremental->OrderCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_OLS_CURR() {
        this->m_incremental->OrderCurr()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_TLS_FOND() {
        this->m_incremental->TradeFond()->ObtainSnapshotItem(this->GetAstsSnapshotSymbolIndex(), this->m_astsSnapshotInfo);
        if(this->m_incremental->TradeFond()->ApplyQuickSnapshot(this->m_astsSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->Inc(Counters::cFondTls);
            ProgramStatistics::Total->Inc(Counters::cFondTls);
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->TradeFond()->StartProcessSnapshot();
        this->ApplySnapshotPart_TLS_FOND(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_TLS_FOND(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cFondTls);
        ProgramStatistics::Total->Inc(Counters::cFondTls);
#endif
        AstsTLSFONDInfo *info = this->m_fastProtocolManager->DecodeAstsTLSFOND();
        this->m_incremental->TradeFond()->ProcessSnapshot(info);
        return true;
    }

    inline bool EndApplySnapshot_TLS_FOND() {
        this->m_incremental->TradeFond()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_TLS_FOND() {
        this->m_incremental->TradeFond()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_TLS_CURR() {
        this->m_incremental->TradeCurr()->ObtainSnapshotItem(this->GetAstsSnapshotSymbolIndex(), this->m_astsSnapshotInfo);
        if(this->m_incremental->TradeCurr()->ApplyQuickSnapshot(this->m_astsSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->Inc(Counters::cCurrTls);
            ProgramStatistics::Total->Inc(Counters::cCurrTls);
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->TradeCurr()->StartProcessSnapshot();
        this->ApplySnapshotPart_TLS_CURR(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_TLS_CURR(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cCurrTls);
        ProgramStatistics::Total->Inc(Counters::cCurrTls);
#endif
        AstsTLSCURRInfo *info = this->m_fastProtocolManager->DecodeAstsTLSCURR();
        this->m_incremental->TradeCurr()->ProcessSnapshot(info);
        return true;
    }

    inline bool EndApplySnapshot_TLS_CURR() {
        this->m_incremental->TradeCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_TLS_CURR() {
        this->m_incremental->TradeCurr()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_MSS_FOND() {
        this->m_incremental->StatisticFond()->ObtainSnapshotItem(this->GetAstsSnapshotSymbolIndex(), this->m_astsSnapshotInfo);
        if(this->m_incremental->StatisticFond()->ApplyQuickSnapshot(this->m_astsSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->Inc(Counters::cFondMss);
            ProgramStatistics::Total->Inc(Counters::cFondMss);
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->StatisticFond()->StartProcessSnapshot();
        this->ApplySnapshotPart_MSS_FOND(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_MSS_FOND(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cFondMss);
        ProgramStatistics::Total->Inc(Counters::cFondMss);
#endif
        AstsGenericInfo *info = this->m_fastProtocolManager->DecodeAstsGeneric();
        this->m_incremental->StatisticFond()->ProcessSnapshot(info);
        return true;
    }

    inline bool EndApplySnapshot_MSS_FOND() {
        this->m_incremental->StatisticFond()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_MSS_FOND() {
        this->m_incremental->StatisticFond()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_MSS_CURR() {
        this->m_incremental->StatisticCurr()->ObtainSnapshotItem(this->GetAstsSnapshotSymbolIndex(), this->m_astsSnapshotInfo);
        if(this->m_incremental->StatisticCurr()->ApplyQuickSnapshot(this->m_astsSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->Inc(Counters::cCurrMss);
            ProgramStatistics::Total->Inc(Counters::cCurrMss);
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->StatisticCurr()->StartProcessSnapshot();
        this->ApplySnapshotPart_MSS_CURR(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_MSS_CURR(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cCurrMss);
        ProgramStatistics::Total->Inc(Counters::cCurrMss);
#endif
        AstsGenericInfo *info = this->m_fastProtocolManager->DecodeAstsGeneric();
        this->m_incremental->StatisticCurr()->ProcessSnapshot(info);
        return true;
    }

    inline bool EndApplySnapshot_MSS_CURR() {
        this->m_incremental->StatisticCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_MSS_CURR() {
        this->m_incremental->StatisticCurr()->CancelSnapshot();
        return true;
    }
    
#pragma endregion

#pragma FORT snapshot
    inline bool PrepareDecodeSnapshotMessageForts(int packetIndex) {
        if(!this->PrepareDecodeSnapshotMessageCore(packetIndex))
            return false;
        this->m_fastProtocolManager->DecodeFortsHeader();
        return true;
    }

    inline int GetFortsSnapshotSymbolIndex() {
        return this->m_symbolManager->GetSymbol(this->m_fortsSnapshotInfo->SecurityID)->m_index;
    }
    inline SymbolInfo* GetFortsSnapshotSymbolInfo() {
        return this->m_symbolManager->GetExistingSymbol(this->m_fortsSnapshotInfo->SecurityID);
    }

    inline bool StartApplySnapshot_FORTS_OBS() {
        SymbolInfo *info = GetFortsSnapshotSymbolInfo();
        if(info == 0) {
            //printf("%s  invalid security id = %" PRIu64 "\n", this->m_idName, this->m_fortsSnapshotInfo->SecurityID);
            return false; // do not apply snapshot - symbol does not exist
        }
        this->m_incremental->OrderBookForts()->ObtainSnapshotItem(info->m_index, this->m_fortsSnapshotInfo);
        //printf("%s  start snap for security id = %" PRIu64 "\n", this->m_idName, this->m_fortsSnapshotInfo->SecurityID);
        if(this->m_incremental->OrderBookForts()->ApplyQuickSnapshot(this->m_fortsSnapshotInfo)) {
            return false; // skip all the snapshot
        }
        this->m_incremental->OrderBookForts()->StartProcessSnapshot();
        this->ApplySnapshotPart_FORTS_OBS(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_FORTS_OBS(int index) {
        this->PrepareDecodeSnapshotMessageForts(index);
        FortsDefaultSnapshotMessageInfo *info = this->m_fastProtocolManager->DecodeFortsDefaultSnapshotMessage();
        this->m_incremental->OrderBookForts()->ProcessSnapshotForts(info);
        return true;
    }

    inline bool EndApplySnapshot_FORTS_OBS() {
        this->m_incremental->OrderBookForts()->EndProcessSnapshot();
//        printf("%s  end snap for security id = %" PRIu64 "  que = %d  ss = %d\n",
//               this->m_idName,
//               this->m_fortsSnapshotInfo->SecurityID,
//               this->m_incremental->QueueEntriesCount(),
        //this->m_incremental->SymbolsToRecvSnapshotCount());
        return true;
    }

    inline bool CancelApplySnapshot_FORTS_OBS() {
        //printf("%s  cancel snap for security id = %" PRIu64 "\n", this->m_idName, this->m_fortsSnapshotInfo->SecurityID);
        this->m_incremental->OrderBookForts()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_FORTS_TLS() {
        SymbolInfo *info = GetFortsSnapshotSymbolInfo();
        if(info == 0) {
            //printf("%s  invalid security id = %" PRIu64 "\n", this->m_idName, this->m_fortsSnapshotInfo->SecurityID);
            return false; // do not apply snapshot - symbol does not exist
        }
        this->m_incremental->TradeForts()->ObtainSnapshotItem(info->m_index, this->m_fortsSnapshotInfo);
        //printf("%s  start snap for security id = %" PRIu64 "\n", this->m_idName, this->m_fortsSnapshotInfo->SecurityID);
        if(this->m_incremental->TradeForts()->ApplyQuickSnapshot(this->m_fortsSnapshotInfo)) {
            return false; // skip all the snapshot
        }
        this->m_incremental->TradeForts()->StartProcessSnapshot();
        this->ApplySnapshotPart_FORTS_TLS(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_FORTS_TLS(int index) {
        this->PrepareDecodeSnapshotMessageForts(index);
        FortsDefaultSnapshotMessageInfo *info = this->m_fastProtocolManager->DecodeFortsDefaultSnapshotMessage();
        //printf("%s  apply part for security id = %" PRIu64 "  index = %d\n", this->m_idName, info->SecurityID, index);
        this->m_incremental->TradeForts()->ProcessSnapshotForts(info);
        return true;
    }

    inline bool EndApplySnapshot_FORTS_TLS() {
//        printf("%s  end snap for security id = %" PRIu64 "  que = %d  ss = %d\n",
//               this->m_idName,
//               this->m_fortsSnapshotInfo->SecurityID,
//               this->m_incremental->QueueEntriesCount(),
//               this->m_incremental->SymbolsToRecvSnapshotCount());
        this->m_incremental->TradeForts()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_FORTS_TLS() {
        //printf("%s  cancel snap for security id = %" PRIu64 "\n", this->m_idName, this->m_fortsSnapshotInfo->SecurityID);
        this->m_incremental->TradeForts()->CancelSnapshot();
        return true;
    }
#pragma endregion

    inline int GetRequestMessageEndIndex(int start) {
        int end = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        for(int i = start - this->m_windowMsgSeqNum; i <= end; i++) {
            if(this->m_packets[i]->m_address != 0)
                return i + this->m_windowMsgSeqNum - 1;
        }
        return start;
    }

    inline int GetRequestMessageStartIndex(int start) {
        int localEnd = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        int localStart = start - this->m_windowMsgSeqNum;
        if(localStart < 0) localStart = 0;
        for(int i = localStart; i <= localEnd; i++) {
            if(this->m_packets[i]->m_address == 0 && !this->m_packets[i]->m_requested)
                return i + this->m_windowMsgSeqNum;
        }
        return this->m_endMsgSeqNum + 1;
    }

    inline void RequestMessages(int start, int end) {
        FeedConnectionMessageInfo **info = this->m_packets + start - this->m_windowMsgSeqNum;
        for(int i = start; i <= end; i++, info++)
            (*info)->m_requested = true;
        printf("request messages from %d to %d\n", start, end);
        this->m_historicalReplay->HrRequestMessage(this, start, end);
    }

    inline bool StartSecurityStatusSnapshot() {
        if(this->m_securityDefinition->State() != FeedConnectionState::fcsSuspend)
            return true; // already connected
        DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_StartSecurityStatusSnapshot);
        this->m_securityDefinition->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmUpdateData;
        this->m_securityDefinition->IdfStopAfterUpdateMessages(true);
        this->m_securityDefinition->m_idfSnapshotClient = this;
        if(!this->m_securityDefinition->Start()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        this->m_securityStatusSnapshotActive = true;
        this->m_isfStartSnapshotCount++;
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline void AfterMoveWindow() {
        this->ResetRecvBuffer();
    }

    __attribute__((noinline))
    void FinishSecurityStatusSnapshot() {
        DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_FinishSecurityStatusSnapshot);
        this->m_securityDefinition->Stop();
        this->m_securityStatusSnapshotActive = false;
        this->m_securityDefinition->m_idfSnapshotClient = 0;
        this->ClearLocalPackets(0, this->m_endMsgSeqNum - this->m_windowMsgSeqNum);
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
        DefaultLogManager::Default->EndLog(true);
    }

    inline bool IsSecurityStatusSnapshotActive() { return this->m_securityStatusSnapshotActive; }

    inline bool ShouldStartSecurityStatusSnapshot(int endIndex) {
        if(this->m_securityStatusSnapshotActive)
            return false;
        if(this->m_securityDefinition->m_state != FeedConnectionState::fcsSuspend)
            return false;
        if(this->m_historicalReplay == 0)
            return true;
        if(endIndex - this->m_requestMessageStartIndex < this->m_maxLostPacketCountForStartSnapshot)
            return false;
        return true;
    }

    inline bool ShouldStartIncrementalSnapshot(int endIndex) {
        if(this->m_historicalReplay == 0)
            return true;
        if(!this->m_enableHistoricalReplay)
            return true;
        return (endIndex - this->m_requestMessageStartIndex + 1) >= this->m_maxLostPacketCountForStartSnapshot;
    }

    inline bool CheckRequestLostIncrementalMessages() {
        if(this->m_requestMessageStartIndex == -1) {
            if(this->HasQueueEntries() || this->SymbolsToRecvSnapshotCount() > 0) {
                if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend)
                    return this->StartListenSnapshot();
            }
            return true;
        }
        if(this->m_snapshot->State() != FeedConnectionState::fcsSuspend)
            return true;
        while(this->m_requestMessageStartIndex <= this->m_endMsgSeqNum) {
            this->m_requestMessageStartIndex = GetRequestMessageStartIndex(this->m_requestMessageStartIndex);
            if(this->m_requestMessageStartIndex > this->m_endMsgSeqNum) {
                if(this->HasQueueEntries() || this->SymbolsToRecvSnapshotCount() > 0) {
                    if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend)
                        return this->StartListenSnapshot();
                }
                return true;
            }
            int endIndex = GetRequestMessageEndIndex(this->m_requestMessageStartIndex);
            if(ShouldStartIncrementalSnapshot(endIndex)) {
                this->m_requestMessageStartIndex = -1;
                return this->StartListenSnapshot();
            }
            this->RequestMessages(this->m_requestMessageStartIndex, endIndex);
            this->m_requestMessageStartIndex = endIndex + 1;
        }
        return true;
    }

    inline void CheckRequestLostSecurityStatusMessages() {
        if(this->m_securityStatusSnapshotActive)
            return;
        if(this->m_requestMessageStartIndex == -1)
            return;
        while(this->m_requestMessageStartIndex <= this->m_endMsgSeqNum) {
            this->m_requestMessageStartIndex = GetRequestMessageStartIndex(this->m_requestMessageStartIndex);
            if(this->m_requestMessageStartIndex > this->m_endMsgSeqNum)
                break;
            int endIndex = GetRequestMessageEndIndex(this->m_requestMessageStartIndex);
            if(ShouldStartSecurityStatusSnapshot(endIndex))
                this->StartSecurityStatusSnapshot();
            else if(!IsSecurityStatusSnapshotActive())
                this->RequestMessages(this->m_requestMessageStartIndex, endIndex);
            this->m_requestMessageStartIndex = endIndex + 1;
        }
    }

    __attribute__((noinline))
    void ProcessSecurityStatusMessages_MultipleMessages(){
        int i = this->m_startMsgSeqNum - this->m_windowMsgSeqNum;
        int end = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        if(i < 0) i = 0;
        while(i <= end) {
            if(this->m_packets[i]->m_processed) {
                i++; continue;
            }
            if(this->m_packets[i]->m_address == 0) {
                if(this->m_securityStatusSnapshotActive) {
                    i++; continue;
                }
                if(this->m_requestMessageStartIndex < i + this->m_windowMsgSeqNum)
                    this->m_requestMessageStartIndex = i + this->m_windowMsgSeqNum;
                break;
            }
            if(this->m_id != FeedConnectionId::fcidIdfIncForts) {
                if(!this->ProcessSecurityStatus(this->m_packets[i]))
                    return;
            }
            else {
                if(!this->ProcessSecurityStatusForts(this->m_packets[i]))
                    return;
            }
            i++;
        }
        if(i > end) {
            this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
            this->ClearLocalPackets(0, end);
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            this->AfterMoveWindow();
        }
        else {
            this->m_startMsgSeqNum = i + this->m_windowMsgSeqNum;
            this->CheckRequestLostSecurityStatusMessages();
        }
    }

    inline void ProcessSecurityStatusMessages() {
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return;
        if(this->m_startMsgSeqNum == this->m_endMsgSeqNum) { // special case - one packet
            FeedConnectionMessageInfo *info = this->Packet(this->m_startMsgSeqNum);
            this->m_startMsgSeqNum ++;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            this->ProcessSecurityStatus(info);
            info->Clear();
            this->AfterMoveWindow();
        }
        ProcessSecurityStatusMessages_MultipleMessages();
    }

    inline void ProcessSecurityStatusMessagesForts() {
        if(this->m_securityStatusSnapshotActive && this->m_securityDefinition->IsIdfDataCollected())
            this->FinishSecurityStatusSnapshot();
        if(this->m_startMsgSeqNum - this->m_endMsgSeqNum == 1)
            return;
        if(this->m_startMsgSeqNum == this->m_endMsgSeqNum) { // special case - one packet
            FeedConnectionMessageInfo *info = this->Packet(this->m_startMsgSeqNum);
            this->m_startMsgSeqNum ++;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            this->ProcessSecurityStatusForts(info);
            info->Clear();
            this->AfterMoveWindow();
        }
        ProcessSecurityStatusMessages_MultipleMessages();
    }

    //This code is for debug only and should not be used in release
    bool DebugCheckActuality() {
        if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->DebugCheckActuality();
        if(this->m_tradeTableCurr != 0)
            return this->m_tradeTableCurr->DebugCheckActuality();
        if(this->m_statTableCurr != 0)
            return this->m_statTableCurr->DebugCheckActuality();

        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->DebugCheckActuality();
        if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->DebugCheckActuality();
        if(this->m_statTableFond != 0)
            return this->m_statTableFond->DebugCheckActuality();

        return true;
    }

    __attribute__((noinline))
    void ProcessIncrementalMessages_MultipleMessages() {
        //printf("multiple messages inc s = %d e = %d w = %d\n", this->m_startMsgSeqNum, this->m_endMsgSeqNum, this->m_windowMsgSeqNum);
        int localStart = this->m_startMsgSeqNum - this->m_windowMsgSeqNum;
        int localEnd = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;

        int newStartMsgSeqNum = -1;
        int i = localStart;

        FeedConnectionMessageInfo **pinfo = this->m_packets + i;
        FeedConnectionMessageInfo *info;
        while(i <= localEnd) {
            info = *pinfo;
            if(info->m_processed) {
                i++;
                pinfo++;
                continue;
            }
            if(info->m_address == 0) {
                if(this->m_requestMessageStartIndex < i + this->m_windowMsgSeqNum)
                    this->m_requestMessageStartIndex = i + this->m_windowMsgSeqNum;
                newStartMsgSeqNum = i + this->m_windowMsgSeqNum;
                break;
            }
            this->ProcessIncrementalAsts(info);
            i++;
            pinfo++;
        }

        while(i <= localEnd) {
            info = *pinfo;
            if(info->m_processed || info->m_address == 0) {
                i++;
                pinfo++;
                continue;
            }
            this->ProcessIncrementalAsts(info);
            i++;
            pinfo++;
        }
        if(newStartMsgSeqNum != -1) {
            this->m_startMsgSeqNum = newStartMsgSeqNum;
        } else {
            this->ClearLocalPackets(0, localEnd);
            this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            this->AfterMoveWindow();
        }
    }

    inline void ProcessIncrementalMessages() {
        if(this->m_windowMsgSeqNum > this->m_endMsgSeqNum) // nothing to check
            return;
        if(this->m_windowMsgSeqNum == this->m_endMsgSeqNum) { // special case - one packet
            FeedConnectionMessageInfo *info = this->Packet(this->m_startMsgSeqNum);
            this->m_startMsgSeqNum++;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            this->ProcessIncrementalAsts(info);
            info->Clear();
            this->AfterMoveWindow();
        } else { // more than one packet
            ProcessIncrementalMessages_MultipleMessages();
        }
    }

    inline void ProcessIncrementalMessages_MultipleMessagesForts() {
        int localStart = this->m_startMsgSeqNum - this->m_windowMsgSeqNum;
        int localEnd = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;

        int newStartMsgSeqNum = -1;
        int lastNullMsgSeq = 0;
        int i = localStart;

        FeedConnectionMessageInfo **pinfo = this->m_packets + i;
        FeedConnectionMessageInfo *info;
        int msgSeqNum = this->m_startMsgSeqNum;
        while (i <= localEnd) {
            info = *pinfo;
            if (info->m_processed) {
                i++; msgSeqNum++; pinfo++;
                continue;
            }
            if (info->m_address == 0) {
                if (this->m_requestMessageStartIndex < msgSeqNum)
                    this->m_requestMessageStartIndex = msgSeqNum;
                newStartMsgSeqNum = msgSeqNum;
                break;
            }
            this->ProcessIncrementalForts(info, msgSeqNum);
            i++; msgSeqNum++; pinfo++;
        }

        // we cannot process messages after lost message
        // because messages are fragmented
        // but we can do this only when snapshot is started
        if(i <= localEnd && this->m_snapshot->State() != FeedConnectionState::fcsSuspend) {
            lastNullMsgSeq = newStartMsgSeqNum;
            while (i <= localEnd) {
                info = *pinfo;
                if (info->m_processed) {
                    i++; msgSeqNum++; pinfo++;
                    continue;
                }
                if(info->m_address == 0) {
                    lastNullMsgSeq = msgSeqNum;
                    i++; msgSeqNum++; pinfo++;
                    continue;
                }
                this->ProcessIncrementalForts(info, msgSeqNum, lastNullMsgSeq);
                i++; msgSeqNum++; pinfo++;
            }
        }
        if (newStartMsgSeqNum != -1) {
            this->m_startMsgSeqNum = newStartMsgSeqNum;
        }
        else {
            this->ClearLocalPackets(0, localEnd);
            this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            this->AfterMoveWindow();
        }
    }

    inline void ProcessIncrementalMessagesForts() {
        if(this->m_windowMsgSeqNum == this->m_endMsgSeqNum) { // special case - one packet
            FeedConnectionMessageInfo *info = this->Packet(this->m_startMsgSeqNum);
            this->ProcessIncrementalForts(info, this->m_startMsgSeqNum);
            this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
            info->Clear();
            this->AfterMoveWindow();
        }
        else { // more than one packet
            ProcessIncrementalMessages_MultipleMessagesForts();
        }
        return;
    }

    void MarketTableEnterSnapshotMode() {
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
        if(this->m_fortsOrderBookTable != 0) {
            this->m_fortsOrderBookTable->EnterSnapshotMode();
            return;
        }
        if(this->m_fortsTradeBookTable != 0) {
            this->m_fortsTradeBookTable->EnterSnapshotMode();
            return;
        }
    }
public:
    inline int SymbolsToRecvSnapshotCount() const { return this->m_symbolsToRecvSnapshot; }
    inline bool IsMarketTableInSnapshotMode() const { return this->m_tableInSnapshotMode; }
    inline int QueueEntriesCount() const { return this->m_queueItemsCount; }
protected:
    void MarketTableExitSnapshotMode() {
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
        if(this->m_fortsOrderBookTable != 0) {
            this->m_fortsOrderBookTable->ExitSnapshotMode();
            return;
        }
        if(this->m_fortsTradeBookTable != 0) {
            this->m_fortsTradeBookTable->ExitSnapshotMode();
            return;
        }
    }
    inline bool StartIncrementalSnapshot() {
        if(this->m_snapshot->State() == FeedConnectionState::fcsListenSnapshot && this->IsMarketTableInSnapshotMode())
            return true;
        if(!this->m_snapshot->Start()) {
            DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, false);
            return false;
        }
        this->MarketTableEnterSnapshotMode();
        this->m_snapshot->StartNewSnapshot();
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, true);
        return true;
    }
    __attribute__((noinline))
    bool StartListenSnapshot() {
        if(this->m_type == FeedConnectionType::fctInstrumentStatus || this->m_type == FeedConnectionType::fctInstrumentStatusForts)
            return this->StartSecurityStatusSnapshot();
        return this->StartIncrementalSnapshot();
    }
    inline void UpdateMessageSeqNoAfterSnapshot() {
        this->ClearLocalPackets(0, GetLocalIndex(this->m_endMsgSeqNum));
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
    }
    inline bool StopListenSnapshot() {
        if(!this->m_snapshot->Stop()) {
            DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, false);
            return false;
        }
        this->MarketTableExitSnapshotMode();
        this->UpdateMessageSeqNoAfterSnapshot();
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, true);
        return true;
    }

    inline AstsSnapshotInfo* GetAstsSnapshotInfo(int msgSeqNo) {
        FeedConnectionMessageInfo *item = this->m_packets[msgSeqNo];
        unsigned char *buffer = item->m_address;
        if(this->ShouldSkipMessageAsts(buffer))
            return 0;
        this->m_fastProtocolManager->SetNewBuffer(buffer);
        return this->m_fastProtocolManager->GetAstsSnapshotInfo();
    }

    inline FortsSnapshotInfo* GetFortsSnapshotInfo(int msgSeqNo) {
        FeedConnectionMessageInfo *item = this->m_packets[msgSeqNo];
        unsigned char *buffer = item->m_address;
        if(this->ShouldSkipMessageForts(buffer))
            return 0;
        this->m_fastProtocolManager->SetNewBuffer(buffer);

        FortsSnapshotInfo* info = this->m_fastProtocolManager->GetFortsSnapshotInfo();
        if(info == 0) // TODO Trading Session Status sometimes appears in snap
            return 0;
        // for FORTS if LastFragment field is not presented i.e. == null then it is can be threathed as LastFragment = 1
        if((info->NullMap & FortsDefaultSnapshotMessageInfoNullIndices::LastFragmentNullIndex) != 0)
            info->LastFragment = 1;
        return info;
    }

    inline void ResetWaitTime() {
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->m_waitTimer->StartFast();
    }
    inline bool ActualMsgSeqNum() { return this->m_startMsgSeqNum == this->m_endMsgSeqNum; }

    inline void IncrementMsgSeqNo() { this->m_startMsgSeqNum++; }
    virtual ISocketBufferProvider* CreateSocketBufferProvider() {
            return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                            RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
                                            RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
                                            RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
                                            RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
    }
    virtual void ClearSocketBufferProvider() {

    }
    void SetMaxReconnectCount(int value) { this->m_maxReconnectCount = value; }
    void SetMaxLostPacketCountForStartSnapshot(int count) { this->m_maxLostPacketCountForStartSnapshot = count; }
    int MaxLostPacketCountForStartSnapshot() { return this->m_maxLostPacketCountForStartSnapshot; }
    inline void SetState(FeedConnectionState state) { this->m_state = state; }
    inline void SetId(FeedConnectionId id) { this->m_id = id; }
    inline void SetHsState(FeedConnectionHistoricalReplayState state) { this->m_hsState = state; }
    inline void SetNextState(FeedConnectionState state) {
        this->m_nextState = state;
        this->m_shouldUseNextState = true;
    }

    inline int GetLocalIndex(int msgSeqNo) { return msgSeqNo - this->m_windowMsgSeqNum; }
    inline int LocalIndexToMsgSeqNo(int index) { return index + this->m_windowMsgSeqNum; }
    inline bool FindRouteFirstAsts() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if (this->m_packets[i]->m_address == 0) {
                this->m_startMsgSeqNum = i;
                return false;
            }
            this->m_astsSnapshotInfo = this->GetAstsSnapshotInfo(i);
            if (this->m_astsSnapshotInfo != 0 && this->m_astsSnapshotInfo->RouteFirst == 1) {
                this->m_startMsgSeqNum = i;
                this->m_snapshotRouteFirst = i;
                return true;
            }
            this->m_packets[i]->Clear();
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        return false;
    }
    inline bool FindRouteFirstForts() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if (this->m_packets[i]->m_address == 0) {
                this->m_startMsgSeqNum = i;
                return false;
            }
            this->m_fortsSnapshotInfo = this->GetFortsSnapshotInfo(i);
            if(i == this->m_nextFortsSnapshotRouteFirst || i == 1) {
                if(this->m_fortsSnapshotInfo == 0) {
                    this->m_nextFortsSnapshotRouteFirst = i + 1;
                    this->m_snapshotRouteFirst = -1;
                    this->m_packets[i]->Clear();
                    continue;
                }
                else {
                    this->m_startMsgSeqNum = i;
                    this->m_snapshotRouteFirst = i;
                    return true;
                }
            }
            if(this->m_fortsSnapshotInfo != 0 && this->m_fortsSnapshotInfo->LastFragment == 1) {
                this->m_nextFortsSnapshotRouteFirst = i + 1;
            }
            this->m_packets[i]->Clear();
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        return false;
    }

    inline bool StartApplySnapshotAsts() {
        switch(this->m_astsSnapshotInfo->TemplateId) {
            case FeedTemplateId::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->StartApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->StartApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                return this->StartApplySnapshot_OLS_FOND();
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                return this->StartApplySnapshot_OLS_CURR();
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                return this->StartApplySnapshot_TLS_FOND();
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                return this->StartApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool EndApplySnapshotAsts() {
        switch(this->m_astsSnapshotInfo->TemplateId) {
            case FeedTemplateId::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->EndApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->EndApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                return this->EndApplySnapshot_OLS_FOND();
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                return this->EndApplySnapshot_OLS_CURR();
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                return this->EndApplySnapshot_TLS_FOND();
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                return this->EndApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool CancelSnapshotAsts() {
        switch(this->m_astsSnapshotInfo->TemplateId) {
            case FeedTemplateId::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->CancelApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->CancelApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                return this->CancelApplySnapshot_OLS_FOND();
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                return this->CancelApplySnapshot_OLS_CURR();
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                return this->CancelApplySnapshot_TLS_FOND();
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                return this->CancelApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool ApplySnapshotPartAsts(int index) {
        switch(this->m_astsSnapshotInfo->TemplateId) {
            case FeedTemplateId::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->ApplySnapshotPart_MSS_FOND(index);
                    case FeedConnectionId::fcidMssCurr:
                        return this->ApplySnapshotPart_MSS_CURR(index);
                    default:
                        return false;
                }
                break;
            case FeedTemplateId::fmcFullRefresh_OLS_FOND:
                return this->ApplySnapshotPart_OLS_FOND(index);
            case FeedTemplateId::fmcFullRefresh_OLS_CURR:
                return this->ApplySnapshotPart_OLS_CURR(index);
            case FeedTemplateId::fmcFullRefresh_TLS_FOND:
                return this->ApplySnapshotPart_TLS_FOND(index);
            case FeedTemplateId::fmcFullRefresh_TLS_CURR:
                return this->ApplySnapshotPart_TLS_CURR(index);
            default:
                return false;
        }
    }

    inline bool StartApplySnapshotForts() {
        if(this->m_fortsSnapshotInfo->TemplateId == FeedTemplateId::fortsTradingSessionStatus) {
            //TODO remove debug
            //printf("process trading sessions status\n");
            this->ProcessTradingSessionStatusForts();
            return false; // prevent from calling end process snapshot
        }
        if(this->m_fortsSnapshotInfo->TemplateId == FeedTemplateId::fortsSequenceReset) {
            return false;
        }
        if(this->m_fortsSnapshotInfo->TemplateId == FeedTemplateId::fortsSnapshot) {
            FeedConnectionId incId = this->m_incremental->Id();
            if (incId == FeedConnectionId::fcidObrForts)
                return this->StartApplySnapshot_FORTS_OBS();
            else if (incId == FeedConnectionId::fcidTlrForts)
                return this->StartApplySnapshot_FORTS_TLS();
        }
        return false;
    }
    inline bool EndApplySnapshotForts() {
        FeedConnectionId incId = this->m_incremental->Id();
        if (incId == FeedConnectionId::fcidObrForts)
            return this->EndApplySnapshot_FORTS_OBS();
        else if (incId == FeedConnectionId::fcidTlrForts)
            return this->EndApplySnapshot_FORTS_TLS();
        return true;
    }
    inline bool CancelSnapshotForts() {
        FeedConnectionId incId = this->m_incremental->Id();
        if (incId == FeedConnectionId::fcidObrForts)
            return this->CancelApplySnapshot_FORTS_OBS();
        else if (incId == FeedConnectionId::fcidTlrForts)
            return this->CancelApplySnapshot_FORTS_TLS();
        return true;
    }
    inline bool ApplySnapshotPartForts(int index) {
        if(this->m_fortsSnapshotInfo->TemplateId == FeedTemplateId::fortsTradingSessionStatus) {
            this->ProcessTradingSessionStatusForts();
            return true;
        }

        FeedConnectionId incId = this->m_incremental->Id();
        if(incId == FeedConnectionId::fcidObrForts)
            return this->ApplySnapshotPart_FORTS_OBS(index);
        else if(incId == FeedConnectionId::fcidTlrForts)
            return this->ApplySnapshotPart_FORTS_TLS(index);
        return true;
    }

    inline void ProcessTradingSessionStatusForts() {
        FeedConnectionMessageInfo *info = this->m_packets[this->m_startMsgSeqNum];
        this->m_fastProtocolManager->SetNewBuffer(info->m_address, info->m_size);
        FortsTradingSessionStatusInfo *sinfo = this->m_fastProtocolManager->DecodeFortsTradingSessionStatus();
        this->m_incremental->OnTradingSessionStatusForts(sinfo);
    }

    inline bool StartApplySnapshot() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return this->StartApplySnapshotAsts();
        return this->StartApplySnapshotForts();
    }
    inline bool EndApplySnapshot() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return this->EndApplySnapshotAsts();
        return this->EndApplySnapshotForts();
    }
    inline bool CancelSnapshot() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return this->CancelSnapshotAsts();
        return this->CancelSnapshotForts();
    }
    inline bool ApplySnapshotPart(int index) {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return this->ApplySnapshotPartAsts(index);
        return this->ApplySnapshotPartForts(index);
    }

    inline bool TryFindAndApplySnapshotContinuouslyForts() {
        if(this->m_snapshotRouteFirst == -1) {
            if(!FindRouteFirstForts())
                return false;
             // TODO remove debug
            printf("%s   find snapshot %d   sid = %" PRIu64 "  lf = %d rptSeq = %d\n",
                   this->m_idName,
                   this->m_snapshotRouteFirst,
                   this->m_fortsSnapshotInfo->SecurityID,
                   this->m_fortsSnapshotInfo->LastFragment,
                   this->m_fortsSnapshotInfo->RptSeq);
            if(!StartApplySnapshotForts()) {
                if(this->m_fortsSnapshotInfo->LastFragment == 1)
                    this->m_nextFortsSnapshotRouteFirst = this->m_snapshotRouteFirst + 1;
                this->m_packets[this->m_snapshotRouteFirst]->Clear();
                this->m_snapshotRouteFirst = -1;
                this->m_startMsgSeqNum++;
                return true;
            }
            this->m_packets[this->m_snapshotRouteFirst]->Clear();
            if(this->m_fortsSnapshotInfo->LastFragment) {
                EndApplySnapshotForts();
                this->m_nextFortsSnapshotRouteFirst = this->m_snapshotRouteFirst + 1;
                this->m_snapshotRouteFirst = -1;
                //do not. please do not reset buffer. because there can be another items after this snapshot
            }
            this->m_startMsgSeqNum++;
            if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
                this->ResetRecvBuffer();
            return true;
        }
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return false;
        while(this->m_startMsgSeqNum <= this->m_endMsgSeqNum) {
            if (this->m_packets[this->m_startMsgSeqNum]->m_address == 0)
                return false;
            this->m_fortsSnapshotInfo = this->GetFortsSnapshotInfo(this->m_startMsgSeqNum);
            if(this->m_fortsSnapshotInfo == 0)
                return false;
            this->ApplySnapshotPartForts(this->m_startMsgSeqNum);
            this->m_packets[this->m_startMsgSeqNum]->Clear();
            if(this->m_fortsSnapshotInfo->LastFragment) {
                EndApplySnapshotForts();
                this->m_snapshotRouteFirst = -1;
                this->m_nextFortsSnapshotRouteFirst = this->m_startMsgSeqNum + 1;
                //do not. please do not reset buffer. because there can be another items after this snapshot
                this->m_startMsgSeqNum++;
                if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
                    this->ResetRecvBuffer();
                return true;
            }
            this->m_startMsgSeqNum++;
            if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
                this->ResetRecvBuffer();
        }
        return true;
    }

    inline bool TryFindAndApplySnapshotContinuouslyAsts() {
        if(this->m_snapshotRouteFirst == -1) {
            if(!FindRouteFirstAsts())
                return false;
            if(!StartApplySnapshot()) {
                this->m_packets[this->m_snapshotRouteFirst]->Clear();
                this->m_snapshotRouteFirst = -1;
                this->m_startMsgSeqNum++;
                return true;
            }
            this->m_packets[this->m_snapshotRouteFirst]->Clear();
            if(this->m_astsSnapshotInfo->LastFragment) {
                EndApplySnapshot();
                this->m_snapshotRouteFirst = -1;
                //do not. please do not reset buffer. because there can be another items after this snapshot
            }
            this->m_startMsgSeqNum++;
            if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
                this->ResetRecvBuffer();
            return true;
        }
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return false;
        while(this->m_startMsgSeqNum <= this->m_endMsgSeqNum) {
            if (this->m_packets[this->m_startMsgSeqNum]->m_address == 0)
                return false;
            this->m_astsSnapshotInfo = this->GetAstsSnapshotInfo(this->m_startMsgSeqNum);
            if(this->m_astsSnapshotInfo == 0)
                return false;
            this->ApplySnapshotPart(this->m_startMsgSeqNum);
            this->m_packets[this->m_startMsgSeqNum]->Clear();
            if(this->m_astsSnapshotInfo->LastFragment) {
                EndApplySnapshot();
                this->m_snapshotRouteFirst = -1;
                //do not. please do not reset buffer. because there can be another items after this snapshot
                this->m_startMsgSeqNum++;
                if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
                    this->ResetRecvBuffer();
                return true;
            }
            this->m_startMsgSeqNum++;
            if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
                this->ResetRecvBuffer();
        }
        return true;
    }

    inline bool TryFindAndApplySnapshotContinuously() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return TryFindAndApplySnapshotContinuouslyAsts();
        return TryFindAndApplySnapshotContinuouslyForts();
    }

    inline bool HasPotentiallyLostPackets() {
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return false;
        return this->m_packets[GetLocalIndex(this->m_startMsgSeqNum)]->m_address == 0;
    }

    inline void UpdateLostPacketsStatistic(int count) {
        if(this->m_id == FeedConnectionId::fcidIdfCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrIdfLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrIdfLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidIdfFond) {
            ProgramStatistics::Current->Set(Counters::cFondIdfLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondIdfLost, count);
            return;
        }
        
        if(this->m_id == FeedConnectionId::fcidOlrCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrOlrLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrOlrLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidOlrFond) {
            ProgramStatistics::Current->Set(Counters::cFondOlrLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondOlrLost, count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidOlsCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrOlsLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrOlsLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidOlsFond) {
            ProgramStatistics::Current->Set(Counters::cFondOlsLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondOlsLost, count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidTlrCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrTlrLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrTlrLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidTlrFond) {
            ProgramStatistics::Current->Set(Counters::cFondTlrLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondTlrLost, count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidTlsCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrTlsLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrTlsLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidTlsFond) {
            ProgramStatistics::Current->Set(Counters::cFondTlsLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondTlsLost, count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidMsrCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrMsrLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrMsrLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidMsrFond) {
            ProgramStatistics::Current->Set(Counters::cFondMsrLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondMsrLost, count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidMssCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrMssLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrMssLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidMssFond) {
            ProgramStatistics::Current->Set(Counters::cFondMssLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondMssLost, count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidIsfCurr) {
            ProgramStatistics::Current->Set(Counters::cCurrIdfLost, count);
            ProgramStatistics::Total->Inc(Counters::cCurrIdfLost, count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidIsfFond) {
            ProgramStatistics::Current->Set(Counters::cFondIdfLost, count);
            ProgramStatistics::Total->Inc(Counters::cFondIdfLost, count);
            return;
        }
    }

    inline void SkipLostSnapshotPackets() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if(this->m_packets[i]->m_address != 0) {
#ifdef COLLECT_STATISTICS
                this->m_lostPacketCount += i - this->m_startMsgSeqNum;
                this->UpdateLostPacketsStatistic(i - this->m_startMsgSeqNum);
#endif
                this->m_startMsgSeqNum = i;
                return;
            }
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
    }

    inline void ClearPackets(int start, int end) {
        FeedConnectionMessageInfo **info = (this->m_packets + start - this->m_windowMsgSeqNum);
        for(int i = start; i <= end; i++, info++) {
            (*info)->Clear();
        }
    }

    inline void ClearLocalPackets(int start, int end) {
        FeedConnectionMessageInfo **info = (this->m_packets + start);
        for(int i = start; i <= end; i++, info++) {
            (*info)->Clear();
        }
    }

    inline bool ProcessSecurityDefinitionForts(unsigned char *buffer) {
        this->m_fastProtocolManager->SetNewBuffer(buffer);
        this->m_fastProtocolManager->DecodeFortsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fortsSecurityDefinition) {
            printf("not an security definition template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }
        return this->ProcessSecurityDefinition(this->m_fastProtocolManager->DecodeFortsSecurityDefinition());
    }

    inline bool ProcessSecurityDefinitionAsts(unsigned char *buffer) {
        this->m_fastProtocolManager->SetNewBuffer(buffer);
        this->m_fastProtocolManager->DecodeAstsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fmcSecurityDefinition) {
            printf("not an security definition template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }
        return this->ProcessSecurityDefinition(this->m_fastProtocolManager->DecodeAstsSecurityDefinition());
    }

    inline bool ProcessSecurityDefinitionForts(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
        info->m_processed = true;
        if(this->ShouldSkipMessageForts(buffer)) {
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }
        return this->ProcessSecurityDefinitionForts(buffer);
    }

    inline bool ProcessSecurityDefinitionAsts(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
        info->m_processed = true;
        if(this->ShouldSkipMessageAsts(buffer)) {
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }
        return this->ProcessSecurityDefinitionAsts(buffer);
    }

    inline bool IdfAllowGenerateSecurityDefinitions() { return this->m_allowGenerateSecurityDefinitions; }
    inline void IdfAllowGenerateSecurityDefinitions(bool value) { this->m_allowGenerateSecurityDefinitions = value; }

    inline void OnCollectAllSecurityDefinitions() {
        this->m_idfDataCollected = true;
    };

    inline bool ProcessSecurityDefinitionMessagesFromStart() {
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmUpdateData) {
            FeedConnectionMessageInfo *info = this->Packet(this->m_endMsgSeqNum);
            this->UpdateSecurityDefinition(info);
            info->Clear();
            if(this->m_endMsgSeqNum == this->m_idfStartMsgSeqNo) {
                this->OnSecurityDefinitionUpdateAllMessages();
            }
        }
        else {
            if (this->m_endMsgSeqNum == this->m_idfStartMsgSeqNo) {
                if (this->HasLostPackets(1, this->m_idfMaxMsgSeqNo)) {
                    int lostPacketCount = CalcLostPacketCount(1, this->m_idfMaxMsgSeqNo);
#ifdef COLLECT_STATISTICS
                    if(this->m_id == FeedConnectionId::fcidIdfFond) {
                        ProgramStatistics::Total->Set(Counters::cFondIdfLost, this->m_idfMaxMsgSeqNo - lostPacketCount);
                        ProgramStatistics::Total->Set(Counters::cFondIdfLost, lostPacketCount);
                    }
                    else if(this->m_id == FeedConnectionId::fcidIdfCurr){
                        ProgramStatistics::Total->Set(Counters::cCurrIdfLost, this->m_idfMaxMsgSeqNo - lostPacketCount);
                        ProgramStatistics::Total->Set(Counters::cCurrIdfLost, lostPacketCount);
                    }
#endif
                    this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessToEnd;
                    return true;
                }
#ifdef COLLECT_STATISTICS
                if(this->m_id == FeedConnectionId::fcidIdfFond)
                    ProgramStatistics::Total->Set(Counters::cFondIdf, this->m_idfMaxMsgSeqNo);
                else if(this->m_id == FeedConnectionId::fcidIdfCurr)
                    ProgramStatistics::Total->Set(Counters::cFondIdf, this->m_idfMaxMsgSeqNo);
#endif
                if(this->IdfAllowGenerateSecurityDefinitions())
                    this->GenerateSecurityDefinitions();
                else
                    this->OnCollectAllSecurityDefinitions();
            }
        }
        return true;
    }

    inline bool ProcessSecurityDefinitionMessagesToEnd() {
        if(this->m_endMsgSeqNum == this->m_idfMaxMsgSeqNo)
            this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessFromStart;
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmUpdateData) {
            FeedConnectionMessageInfo *info = this->Packet(this->m_endMsgSeqNum);
            this->UpdateSecurityDefinition(info);
            info->Clear();
        }
        return true;
    }

    inline bool ListenSecurityDefinition_Core() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
#ifdef COLLECT_STATISTICS
        if(this->m_id == FeedConnectionId::fcidIdfFond)
            ProgramStatistics::Current->Set(Counters::cFondIdf, this->m_endMsgSeqNum);
        else
            ProgramStatistics::Current->Set(Counters::cCurrIdf, this->m_endMsgSeqNum);
#endif
        if(this->m_idfState == FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            return this->ProcessSecurityDefinitionMessagesToEnd();
        return this->ProcessSecurityDefinitionMessagesFromStart();
    }

    inline bool ListenSnapshot_Core() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        if(this->m_startMsgSeqNum < 1)
            return true;
        if(this->HasPotentiallyLostPackets()) {
            this->m_waitTimer->ActivateFast(1);
        }
        else
            this->m_waitTimer->Stop(1);
        if(this->m_waitTimer->IsTimeOutFast(1, this->m_snapshotMaxTimeMcs) ||
                this->m_endMsgSeqNum - this->m_startMsgSeqNum > 5) {
            if(this->m_snapshotRouteFirst != -1) {
                this->CancelSnapshot();
                //this->ClearPackets(this->m_snapshotRouteFirst, this->m_startMsgSeqNum);
            }
            //printf("%s skip lost packet %d %d\n", this->m_idName, this->m_startMsgSeqNum, this->m_endMsgSeqNum);
            this->SkipLostSnapshotPackets();
            this->m_waitTimer->Stop(1);
            this->m_snapshotRouteFirst = -1;
            this->m_snapshotLastFragment = -1;
        }

        int snapshotCount = 0;
        if(this->m_marketType == FeedMarketType::fmtAsts) {
            while (TryFindAndApplySnapshotContinuouslyAsts())
                snapshotCount++;
        }
        else {
            while (TryFindAndApplySnapshotContinuouslyForts())
                snapshotCount++;
        }

        return true;
    }
    inline bool ListenIncremental_Core() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
#ifndef TEST
        // TODO remove hack. just skip 30 messages and then try to restore
        // Skip this hack when testing :)
//        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend && (this->m_endMsgSeqNum % 100) < 10) {
//            if(this->m_endMsgSeqNum >= this->m_startMsgSeqNum && this->Packet(this->m_endMsgSeqNum)->m_address != 0) {
//                this->Packet(this->m_endMsgSeqNum)->m_address = 0;
//                //printf("packet %d is lost, requestIndexd = %d\n", this->m_endMsgSeqNum, this->m_requestMessageStartIndex);
//            }
//            return true;
//        }
#endif
        this->ProcessIncrementalMessages();
        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend) {
            if(!this->ShouldRestoreIncrementalMessages()) {
                this->m_waitTimer->Stop();
                return true;
            }
            this->m_waitTimer->ActivateFast();
            if(this->m_waitTimer->IsTimeOutFast(this->m_waitLostIncrementalMessageMaxTimeMcs)) {
                if(!this->CheckRequestLostIncrementalMessages())
                    return false;
                this->m_waitTimer->Stop();
            }
        }
        else {
            if(this->CanStopListeningSnapshot()) {
                this->StopListenSnapshot();
                this->m_waitTimer->ActivateFast();
                this->m_waitTimer->Stop(1);
            }
        }
        return true;
    }

    inline bool ListenIncremental_Forts_Core() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
#ifndef TEST
        // TODO remove hack. just skip 30 messages and then try to restore
        // Skip this hack when testing :)
//        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend && (this->m_endMsgSeqNum % 100) < 10) {
//            if(this->m_endMsgSeqNum >= this->m_startMsgSeqNum && this->Packet(this->m_endMsgSeqNum)->m_address != 0) {
//                this->Packet(this->m_endMsgSeqNum)->m_address = 0;
//                //printf("packet %d is lost, requestIndexd = %d\n", this->m_endMsgSeqNum, this->m_requestMessageStartIndex);
//            }
//            return true;
//        }
#endif
        this->ProcessIncrementalMessagesForts();
        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend) {
            if(!this->ShouldRestoreIncrementalMessages()) {
                this->m_waitTimer->Stop();
                return true;
            }
            this->m_waitTimer->ActivateFast();
            if(this->m_waitTimer->IsTimeOutFast(this->m_waitLostIncrementalMessageMaxTimeMcs)) {
                if(!this->CheckRequestLostIncrementalMessages())
                    return false;
                this->m_waitTimer->Stop();
            }
        }
        else {
            //printf("%d que entries and %d symbols to go\n", this->OrderCurr()->QueueEntriesCount(), this->OrderCurr()->SymbolsToRecvSnapshotCount());
            if(this->CanStopListeningSnapshot()) {
                this->StopListenSnapshot();
                this->m_waitTimer->ActivateFast();
                this->m_waitTimer->Stop(1);
            }
        }
        return true;
    }

    inline bool ListenSecurityStatusCore() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        this->ProcessSecurityStatusMessages();
        return true;
    }
    inline bool ListenSecurityStatusFortsCore() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        this->ProcessSecurityStatusMessagesForts();
        return true;
    }

    inline bool InitializeSockets() {
        if(this->socketAManager != NULL)
            return true;
        //DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_InitializeSockets);

        this->socketAManager = new WinSockManager();
        this->socketAManager->SocketLogName(LogMessageCode::lmcsocketA);
        if(this->m_id != FeedConnectionId::fcidHFond && this->m_id != FeedConnectionId::fcidHCurr) {
            this->socketBManager = new WinSockManager();
            this->socketAManager->SocketLogName(LogMessageCode::lmcsocketB);
        }

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
            this->m_reconnectCount++;
            if(this->m_reconnectCount > this->m_maxReconnectCount)
                return false;
            return true;
        }
        if(this->protocol == FeedConnectionProtocol::UDP_IP) {
            if (!this->socketBManager->Reconnect()) {
                DefaultLogManager::Default->EndLog(false);
                this->m_reconnectCount++;
                if (this->m_reconnectCount > this->m_maxReconnectCount)
                    return false;
                return true;
            }
        }
#endif
        this->m_reconnectCount = 0;
        this->SetState(this->m_nextState);
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->m_waitTimer->StartFast();
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
#ifdef TEST
        WinSockManager::m_testHelper = this->m_testHelper;
#endif
        if(!this->m_fixProtocolManager->SendFix(this->socketAManager)) {
            this->Disconnect();
            return true;
        }
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsWaitLogon;
        this->m_hrMessageSize = 0;
        this->m_waitTimer->Stop(2);
        return true;
    }

    inline bool CanRecv() { return this->socketAManager->ShouldRecv(); }

    inline void OnProcessHistoricalReplayExpectedLogoutMessage(AstsLogoutInfo *info) {
        info->Text[info->TextLength] = 0;
        printf("\t\tHistorical Replay - Logout: %s\n", info->Text);
        info->Clear();
    }

    inline void OnProcessHistoricalReplayUnexpectedLogoutMessage(const char *methodName, AstsLogoutInfo *info) {
        info->Text[info->TextLength] = 0;
        // Limit of connections for this IP exceeded
        // TODO remove debug
        printf("\t\tHistorical Replay - %s - UNEXPECTED Logout: %s\n", methodName, info->Text);
        static const char *limit = "Limit of connections for this IP exceeded";
        if(StringIdComparer::Equal(info->Text, info->TextLength, limit, strlen(limit))) {
            this->OnHistricalReplayExceedUnsuccessfullConnectCount();
        }
        info->Clear();
    }

    inline bool IsHrReceiveFailedProcessed() {
        bool res;
        if(this->m_hrMessageSize != 0)
            res = this->socketAManager->Recv(this->m_recvBufferCurrentPos + 4);
        else
            res = this->socketAManager->Recv(this->m_recvBufferCurrentPos);
        if(!res) {
            this->Disconnect();
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }
        return false;
    }

    inline void OnHistricalReplayExceedUnsuccessfullConnectCount() {
        printf("ERROR: HistoricalReplay not working.... Switching to snapshots\n");
        for(int i = 0; i < this->m_connToRecvHistoricalReplayCount; i++)
            this->m_connToRecvHistoricalReplay[i]->EnableHistoricalReplay(false);

        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Start();
        while(ptr != 0) {
            ptr->Data()->m_conn->StartListenSnapshot();
            ptr = ptr->Next();
        }
        this->m_hsRequestList->Clear();
    }

    inline void CheckReconnectHistoricalReplay() {
        this->m_waitTimer->ActivateFast(2);
        if(this->m_waitTimer->ElapsedMicrosecondsFast(2) > 9000000) {
            //this->Disconnect();
            //this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            this->HistoricalReplay_SendLogout();
            this->m_waitTimer->Stop();
            printf("historical replay timeout - reconnnect.\n");
            this->m_hrUnsuccessfulConnectCount++;
            if(this->m_hrUnsuccessfulConnectCount > FeedConnection::MaxHrUnsuccessfulConnectCount) {
                this->OnHistricalReplayExceedUnsuccessfullConnectCount();
            }
        }
    }

    inline bool HistoricalReplay_WaitLogon() {
        if(!this->CanRecv()) {
            this->CheckReconnectHistoricalReplay();
            return true;
        }
        this->m_hrUnsuccessfulConnectCount = 0;
        this->m_waitTimer->Stop(2);
        if(this->IsHrReceiveFailedProcessed())
            return true;
        int size = this->socketAManager->RecvSize();
        if(size == 4) {
            this->m_hrMessageSize = *(int*)this->socketAManager->RecvBytes();
            return true;
        }
        unsigned char *buffer = this->socketAManager->RecvBytes();
        this->NextRecv(size);
        if(this->m_hrMessageSize == 0) {
            buffer += 4; size -= 4;
        }
        this->m_fastProtocolManager->SetNewBuffer(buffer);
        this->m_fastProtocolManager->DecodeAstsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fmcLogon) {
            this->Disconnect();
            if(this->m_fastProtocolManager->TemplateId() == FeedTemplateId::fmcLogout) {
                this->OnProcessHistoricalReplayUnexpectedLogoutMessage("OnWaitLogon", this->m_fastProtocolManager->DecodeAstsLogout());
            }
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }
        return this->HistoricalReplay_SendMarketDataRequest();
    }

    inline bool HistoricalReplay_SendMarketDataRequest() {
        FeedConnectionRequestMessageInfo *info = this->m_hsRequestList->Start()->Data();
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_fixProtocolManager->CreateMarketDataRequest(info->m_conn->m_idName, 3, info->StartMsgSeqNo(), info->EndMsgSeqNo());

        if(!this->m_fixProtocolManager->SendFix(this->socketAManager)) {
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            this->Disconnect();
            return true;
        }
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsRecvMessage;
        this->m_hrSizeRemain = 0;
        this->m_hrMessageSize = 0;
        this->m_waitTimer->Stop(2);
        return true;
    }

    inline bool HistoricalReplay_RecvMessage() {
        if(!this->CanRecv()) {
            this->CheckReconnectHistoricalReplay();
            return true;
        }
        this->m_hrUnsuccessfulConnectCount = 0;
        this->m_waitTimer->Stop(2);

        unsigned char *buffer = this->m_recvBufferCurrentPos;
        this->socketAManager->Recv(buffer + this->m_hrSizeRemain);
        this->m_hrSizeRemain += this->socketAManager->RecvSize();

        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Start();
        FeedConnectionRequestMessageInfo *msg = ptr->Data();

        while(true) {
            if(this->m_hrMessageSize == 0) {
                if(this->m_hrSizeRemain < 4)
                    break;
                this->m_hrMessageSize = *(int*)buffer;
                buffer += 4; this->m_hrSizeRemain -= 4;
                this->NextExactRecv(4);
            }
            if(this->m_hrSizeRemain < this->m_hrMessageSize) {
                break;
            }
            this->m_fastProtocolManager->SetNewBuffer(buffer);
            this->m_fastProtocolManager->DecodeAstsHeader();

            if(this->m_fastProtocolManager->TemplateId() == FeedTemplateId::fmcLogout) {
                if(msg->IsAllMessagesReceived()) {
                    this->OnProcessHistoricalReplayExpectedLogoutMessage(this->m_fastProtocolManager->DecodeAstsLogout());
                    this->m_hsRequestList->Remove(ptr);
                    this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
                    return this->HistoricalReplay_SendLogout();
                }
                this->OnProcessHistoricalReplayUnexpectedLogoutMessage("OnRecvMessage", this->m_fastProtocolManager->DecodeAstsLogout());
                this->Disconnect();
                this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
                return true;
            }

            msg->IncMsgSeqNo();
            msg->m_conn->ProcessServerCore_FromHistoricalReplay(this->m_recvBufferCurrentPos, this->m_hrMessageSize, msg->LastRecvMsgSeqNo());

            this->NextExactRecv(this->m_hrMessageSize);
            this->m_hrSizeRemain -= this->m_hrMessageSize;
            buffer += this->m_hrMessageSize;
            this->m_hrMessageSize = 0;
        }

        return true;
    }

    inline bool HistoricalReplay_SendLogout() {
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_fixProtocolManager->CreateFastLogoutMessage("Hasta la vista baby!", 20);

        this->m_fixProtocolManager->SendFix(this->socketAManager);
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
        this->Disconnect();
        return true;
    }

    inline bool HistoricalReplay_Suspend() {
        if(this->m_hsRequestList->Count() == 0)
            return true;
        FeedConnectionRequestMessageInfo *info = this->m_hsRequestList->Start()->Data();
        printf("Request message [%d, %d]. Try %d. Count = %d\n", info->StartMsgSeqNo(), info->EndMsgSeqNo(), info->m_requestCount, this->m_hsRequestList->Count());
//        if(info->m_requestCount >= 5) {
//            this->m_hsRequestList->Remove(this->m_hsRequestList->Start());
//            return true;
//        }
        info->m_requestCount++;

        return this->HistoricalReplay_SendLogon();
    }

    inline bool HistoricalReplay_Atom() {
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsSuspend)
            return this->HistoricalReplay_Suspend();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsWaitLogon)
            return this->HistoricalReplay_WaitLogon();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsRecvMessage)
            return this->HistoricalReplay_RecvMessage();
        return true;
    }
public:
    inline unsigned char* SendBuffer() { return this->m_sendBuffer; }
    inline unsigned char* RecvBuffer() { return this->m_recvBuffer; }
    inline void ResetSendBuffer() { this->m_sendBufferCurrentPos = this->m_sendBuffer; }
    inline void ResetRecvBuffer() { this->m_recvBufferCurrentPos = this->m_recvBuffer; }
    inline void NextRecv(int size) {  this->m_recvBufferCurrentPos += (size & 0xfffffffc) + 8; }
    inline void NextSend(int size) { this->m_sendBufferCurrentPos += (size & 0xfffffffc) + 8; }
    inline void NextExactRecv(int size) { this->m_recvBufferCurrentPos += size; }
    inline void NextExactSend(int size) { this->m_sendBufferCurrentPos += size; }
    inline double CalcRecvMemoryUsagePercentage() {
        return ((double)(this->m_recvBufferCurrentPos - this->m_recvBuffer)) / this->m_recvBufferSize;
    }

    inline void HrRequestMessage(FeedConnection *conn, int start, int end) {
        if(this->m_hsRequestList->IsFull()) {
            printf("error request msg: list is full.\n");
            return;
        }
        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Pop();
        FeedConnectionRequestMessageInfo *info = ptr->Data();
        info->m_conn = conn;
        info->SetMsgSeq(start, end);
        info->m_requestCount = 0;

        this->UpdateLostPacketsStatistic(end - start + 1);
        this->m_hsRequestList->Add(ptr);
    }
    inline void HrRequestMessage(FeedConnection *conn, int msgSeqNo) {
        HrRequestMessage(conn, msgSeqNo, msgSeqNo);
    }
    inline bool AllowSaveSecurityDefinitions() { return this->m_allowSaveSecurityDefinitions; }
    inline void AllowSaveSecurityDefinitions(bool value) { this->m_allowSaveSecurityDefinitions = value; }
    void SaveSecurityDefinitions() {
        DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_SaveSecurityDefinition);
        FILE *fp = fopen(this->m_channelName, "wb");
        fwrite(&(this->m_idfMaxMsgSeqNo), sizeof(int), 1, fp);
        for(int i = 1; i <= this->m_idfMaxMsgSeqNo; i++) {
            unsigned short size = this->m_packets[i]->m_size;
            fwrite(&(size), sizeof(int), 1, fp);
            fwrite(this->m_packets[i]->m_address, 1, this->m_packets[i]->m_size, fp);
        }
        fclose(fp);
        DefaultLogManager::Default->EndLog(true);
    }
    bool LoadSecurityDefinitions() {
        if(!this->AllowSaveSecurityDefinitions())
            return false;
        DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_LoadSecurityDefinition);
        FILE *fp = fopen(this->m_channelName, "rb");
        if(fp == 0) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        fread(&(this->m_idfMaxMsgSeqNo), sizeof(int), 1, fp);
        for(int i = 1; i <= this->m_idfMaxMsgSeqNo; i++) {
            unsigned int size = 0;
            fread(&size, sizeof(int), 1, fp);
            this->m_packets[i]->m_size = size;
            fread(this->m_recvBufferCurrentPos, 1, this->m_packets[i]->m_size, fp);
            this->m_packets[i]->m_address = this->m_recvBufferCurrentPos;
            this->NextRecv(this->m_packets[i]->m_size);
        }
        this->AllowSaveSecurityDefinitions(false); // suppress to save again the same data

        fclose(fp);
        DefaultLogManager::Default->EndLog(true);
        return true;
    }
    inline bool GenerateSecurityDefinitionsCoreAsts() {
        FeedConnectionMessageInfo **info = (this->m_packets + 1); // skip zero messsage
        for (int i = 1; i <= this->m_idfMaxMsgSeqNo; i++, info++) {
            if (!this->ProcessSecurityDefinitionAsts(*info))
                return false;
        }
        return true;
    }
    inline bool GenerateSecurityDefinitionsCoreForts() {
        FeedConnectionMessageInfo **info = (this->m_packets + 1); // skip zero messsage
        for (int i = 1; i <= this->m_idfMaxMsgSeqNo; i++, info++) {
            if (!this->ProcessSecurityDefinitionForts(*info))
                return false;
        }
        return true;
    }
    inline bool GenerateSecurityDefinitionsCore() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return GenerateSecurityDefinitionsCoreAsts();
        return GenerateSecurityDefinitionsCoreForts();
    }
    inline bool GenerateSecurityDefinitions() {
        printf("\t\t%s %s generating security definitions count = %d\n", this->m_channelName, this->m_idName, this->m_idfMaxMsgSeqNo); // TODOO remove debug
        this->m_waitTimer->Start(3); // TODOO remove debug
        if(this->AllowSaveSecurityDefinitions())
            this->SaveSecurityDefinitions();
        this->BeforeProcessSecurityDefinitions();
        this->GenerateSecurityDefinitionsCore();
        this->AfterProcessSecurityDefinitions();
        this->OnSecurityDefinitionRecvAllMessages();
        printf("\t\t%s %s done in %ld ms.\n", this->m_channelName, this->m_idName, this->m_waitTimer->ElapsedMillisecondsFast(3)); // TODOO remove debug
        this->m_waitTimer->Stop(3);
        return true;
    }
protected:
    inline bool ListenIncremental() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        bool recv = this->ProcessServerAIncremental();
        recv |= this->ProcessServerBIncremental();

        if(!recv) {
            this->m_waitTimer->ActivateFast(1);
            if(this->m_waitTimer->IsTimeOutFast(1, this->m_waitIncrementalMessageMaxTimeMcs)) {
                if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend)
                    this->StartListenSnapshot();
                return true;
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->ListenIncremental_Core();
    }
    inline bool ListenIncremental_Forts() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        bool recv = this->ProcessServerAIncremental();
        recv |= this->ProcessServerBIncremental();

        if(!recv) {
            this->m_waitTimer->ActivateFast(1);
            if(this->m_waitTimer->IsTimeOutFast(1, this->m_waitIncrementalMessageMaxTimeMcsForts)) {
                //TODO remove debug
                if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend) {
                    printf("%s listen atom incremental timeout %lu ms... start snapshot\n", this->m_idName, this->m_waitTimer->ElapsedMillisecondsFast(1));
                    this->StartListenSnapshot();
                }
                return true;
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }

        return this->ListenIncremental_Forts_Core();
    }

    __attribute__((noinline))
    void OnListenSecurityStatusTimeout() {
        printf("%s %s Timeout 10 sec... Reconnect...\n", this->m_channelName, this->m_idName);
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_ListenSecurityStatus, false);
        this->ReconnectSetNextState(FeedConnectionState::fcsListenSecurityStatus);
    }

    inline bool ListenSecurityStatus() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        bool recv = this->ProcessServerASecurityStatusAsts();
        if(!recv)
            recv = this->ProcessServerBSecurityStatusAsts();
        else
            this->ProcessServerBSecurityStatusAsts();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->StartFast(1);
            }
            else {
                if(this->m_waitTimer->IsTimeOutFast(1, this->WaitAnyPacketMaxTimeMcs))
                    OnListenSecurityStatusTimeout();
            }
            return true;
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->ListenSecurityStatusCore();
    }
    inline bool ListenSecurityStatusForts() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        bool recv = this->ProcessServerASecurityStatusForts();
        if(!recv)
            recv = this->ProcessServerBSecurityStatusForts();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->StartFast(1);
            }
            else {
                if(this->m_waitTimer->ElapsedMicrosecondsFast(1) > this->WaitSecurityStatusFortsMaxTimeMcs) {
                    OnListenSecurityStatusTimeout();
                }
            }
            return true;
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->ListenSecurityStatusFortsCore();
    }

    inline bool ListenSecurityDefinition() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        bool recv = this->ProcessServerASecurityDefinition();
        recv |= this->ProcessServerBSecurityDefinition();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->StartFast(1);
            }
            else {
                if(this->m_waitTimer->IsTimeOutFast(1, this->WaitAnyPacketMaxTimeMcs)) {
                    printf("%s %s Timeout 10 sec... Reconnect...\n", this->m_channelName, this->m_idName);
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_ListenSecurityDefinition, false);
                    this->ReconnectSetNextState(FeedConnectionState::fcsListenSecurityDefinition);
                }
            }
            return true;
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->ListenSecurityDefinition_Core();
    }

    inline bool ListenSnapshot() {
#ifdef TEST
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
#endif
        bool recv = this->ProcessServerASnapshot();
        recv |= this->ProcessServerBSnapshot();

        if(!recv) {
            if(!this->m_waitTimer->Active(2)) {
                this->m_waitTimer->StartFast(2);
            }
            else {
                if(this->m_waitTimer->IsTimeOutFast(2, this->WaitAnyPacketMaxTimeMcs)) {
                    this->m_waitTimer->Stop(2);
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_ListenSnapshot, false);
                    this->socketAManager->UpdatePollStatus();
                    this->socketBManager->UpdatePollStatus();
                    printf("a = %d  b = %d\n", this->socketAManager->PollFd()->revents, this->socketBManager->PollFd()->revents);
                    //TODO uncomment this code....
                    ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
                    return true;
                }
            }
        }
        else {
            this->m_waitTimer->Stop(2);
            return this->ListenSnapshot_Core();
        }
        return true;
    }

    inline void ReconnectSetNextState(FeedConnectionState state) {
        this->m_waitTimer->Stop();
        this->SetNextState(state);
        this->SetState(FeedConnectionState::fcsConnect);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState);
    }

    inline void OnIncrementalRefresh_OLR_FOND(AstsOLSFONDItemInfo *info) {
        int index = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength)->m_index;
        this->m_orderTableFond->ProcessIncremental(info, index, info->TradingSessionIDUint);
    }

    inline void OnIncrementalRefresh_OLR_FOND_Cached(AstsOLSFONDItemInfo *info) {
        if(info->PresenceMap == 0)
            this->m_orderTableFond->ProcessIncremental(info);
        return this->OnIncrementalRefresh_OLR_FOND(info);
    }

    inline void OnIncrementalRefresh_OLR_CURR(AstsOLSCURRItemInfo *info) {
        int index = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength)->m_index;
        this->m_orderTableCurr->ProcessIncremental(info, index, info->TradingSessionIDUint);
    }

    inline void OnIncrementalRefresh_OLR_CURR_Cached(AstsOLSCURRItemInfo *info) {
        if(info->PresenceMap == 0)
            this->m_orderTableCurr->ProcessIncremental(info);
        return this->OnIncrementalRefresh_OLR_CURR(info);
    }

    inline void OnIncrementalRefresh_TLR_FOND(AstsTLSFONDItemInfo *info) {
        int index = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength)->m_index;
        this->m_tradeTableFond->ProcessIncremental(info, index, info->TradingSessionIDUint);
    }

    inline void OnIncrementalRefresh_TLR_CURR(AstsTLSCURRItemInfo *info) {
        int index = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength)->m_index;
        this->m_tradeTableCurr->ProcessIncremental(info, index, info->TradingSessionIDUint);
    }

    inline void OnIncrementalRefresh_MSR_FOND(AstsGenericItemInfo *info) {
        int index = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength)->m_index;
        this->m_statTableFond->ProcessIncremental(info, index, info->TradingSessionIDUint);
    }

    inline void OnIncrementalRefresh_MSR_CURR(AstsGenericItemInfo *info) {
        int index = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength)->m_index;
        this->m_statTableCurr->ProcessIncremental(info, index, info->TradingSessionIDUint);
    }

    inline UINT64 GetFortsSecurityId(FortsDefaultSnapshotMessageMDEntriesItemInfo *info) {
        // if SecurityID not present this means fragmented message. so use m_fortsRouteFirtsSecurityId
        if((info->NullMap & FortsDefaultIncrementalRefreshMessageMDEntriesItemInfoNullIndices::SecurityIDNullIndex) != 0)
            return this->m_fortsRouteFirtsSecurityId;
        return info->SecurityID;
    }

    inline void OnIncrementalRefresh_FORTS_OBR(FortsDefaultSnapshotMessageMDEntriesItemInfo *info) {
        // since there is fragmented messages
        SymbolInfo *smb = this->m_symbolManager->GetExistingSymbol(GetFortsSecurityId(info));
        if(smb == 0) {
            //TODO remove debug
            printf("skip securityId = %" PRIu64 "\n", GetFortsSecurityId(info));
            return;
        }
        this->m_fortsOrderBookTable->ProcessIncremental(info, smb->m_index);
    }

    inline void OnIncrementalRefresh_FORTS_TLR(FortsDefaultSnapshotMessageMDEntriesItemInfo *info) {
        SymbolInfo *smb = this->m_symbolManager->GetExistingSymbol(GetFortsSecurityId(info));
        if(smb == 0) {
            //TODO remove debug
            printf("skip securityId = %" PRIu64 "\n", GetFortsSecurityId(info));
            return;
        }
        this->m_fortsTradeBookTable->ProcessIncremental(info, smb->m_index);
    }

    inline void OnIncrementalRefresh_OLR_FOND(AstsIncrementalOLRFONDInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cFondOlr);
        ProgramStatistics::Total->Inc(Counters::cFondOlr);
#endif
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            this->OnIncrementalRefresh_OLR_FOND(info->GroupMDEntries[i]);
        }
    }

    inline void OnIncrementalRefresh_OLR_CURR(AstsIncrementalOLRCURRInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cCurrOlr);
        ProgramStatistics::Total->Inc(Counters::cCurrOlr);
#endif
        OrderInfo<AstsOLSCURRItemInfo> *oitem;
        /*
        if(info->GroupMDEntriesCount > 3) {
            for(int i = 0; i < info->GroupMDEntriesCount; i++) {
                AstsOLSCURRItemInfo *item = info->GroupMDEntries[i];
                if(item->PresenceMap > 1) {
                    int index = this->m_symbolManager->GetSymbol(item->Symbol, item->SymbolLength)->m_index;
                    oitem = this->m_orderTableCurr->GetItem(index, item->TradingSessionIDUint);
                }
                if(item->MDUpdateAction != MDUpdateAction::mduaAdd) {
                    UINT64 hash = HashTable::Default->CalcHash(item->MDEntryID, item->MDEntryIDLength);
                    LinkedPointer<HashTableItemInfo> *ptr = HashTable::Default->Bucket()[hash];
                    if(ptr != 0)
                        __builtin_prefetch(ptr->Data()->m_object, 0, _MM_HINT_T0);
                }
            }
        }*/
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            AstsOLSCURRItemInfo *item = info->GroupMDEntries[i];
            //if(item->PresenceMap > 1) {
                int index = this->m_symbolManager->GetSymbol(item->Symbol, item->SymbolLength)->m_index;
                oitem = this->m_orderTableCurr->GetItem(index, item->TradingSessionIDUint);
            //}
            this->m_orderTableCurr->ProcessIncremental(item, oitem);
        }
    }

    inline void OnIncrementalRefresh_TLR_FOND(AstsIncrementalTLRFONDInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cFondTlr);
        ProgramStatistics::Total->Inc(Counters::cFondTlr);
#endif
        this->OnIncrementalRefresh_TLR_FOND(info->GroupMDEntries[0]);
        for(int i = 1; i < info->GroupMDEntriesCount; i++) {
            this->OnIncrementalRefresh_TLR_FOND(info->GroupMDEntries[i]);
        }
    }

    inline void OnIncrementalRefresh_TLR_CURR(AstsIncrementalTLRCURRInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cCurrTlr);
        ProgramStatistics::Total->Inc(Counters::cCurrTlr);
#endif
        this->OnIncrementalRefresh_TLR_CURR(info->GroupMDEntries[0]);
        for(int i = 1; i < info->GroupMDEntriesCount; i++) {
            this->OnIncrementalRefresh_TLR_CURR(info->GroupMDEntries[i]);
        }
    }

    inline void OnIncrementalRefresh_MSR_FOND(AstsIncrementalMSRFONDInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cFondMsr);
        ProgramStatistics::Total->Inc(Counters::cFondMsr);
#endif
        this->OnIncrementalRefresh_MSR_FOND(info->GroupMDEntries[0]);
        for(int i = 1; i < info->GroupMDEntriesCount; i++) {
            this->OnIncrementalRefresh_MSR_FOND(info->GroupMDEntries[i]);
        }
    }

    inline void OnIncrementalRefresh_MSR_CURR(AstsIncrementalMSRCURRInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cCurrMsr);
        ProgramStatistics::Total->Inc(Counters::cCurrMsr);
#endif
        this->OnIncrementalRefresh_MSR_CURR(info->GroupMDEntries[0]);
        for(int i = 1; i < info->GroupMDEntriesCount; i++) {
            this->OnIncrementalRefresh_MSR_CURR(info->GroupMDEntries[i]);
        }
    }

    inline void OnTradingSessionStatusForts(FortsTradingSessionStatusInfo *info) {
        if(this->m_fortsTradingSessionStatus != 0)
            this->m_fortsTradingSessionStatus->Clear();
        this->m_fortsTradingSessionStatus = info;
    }

    inline void OnIncrementalRefresh_FORTS_OBR(FortsDefaultIncrementalRefreshMessageInfo *info) {
//#ifdef COLLECT_STATISTICS
//        ProgramStatistics::Current->IncCurrMsrProcessedCount();
//        ProgramStatistics::Total->IncCurrMsrProcessedCount();
//#endif
        for(int i = 0; i < info->MDEntriesCount; i++) {
            this->OnIncrementalRefresh_FORTS_OBR(info->MDEntries[i]);
        }
    }

    inline void OnIncrementalRefresh_FORTS_TLR(FortsDefaultIncrementalRefreshMessageInfo *info) {
//#ifdef COLLECT_STATISTICS
//        ProgramStatistics::Current->IncCurrMsrProcessedCount();
//        ProgramStatistics::Total->IncCurrMsrProcessedCount();
//#endif
        for(int i = 0; i < info->MDEntriesCount; i++) {
            this->OnIncrementalRefresh_FORTS_TLR(info->MDEntries[i]);
        }
    }

    inline void OnHearthBeatMessage(AstsHeartbeatInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->Inc(Counters::cIncHbeatCount);
        ProgramStatistics::Total->Inc(Counters::cIncHbeatCount);
#endif
        info->Clear();
    }

    inline void ApplyIncrementalCoreAsts2(UINT32 templateId) {
        switch(templateId) {
            case AstsPackedTemplateId::AstsIncrementalTLRCURRInfo:
                this->OnIncrementalRefresh_TLR_CURR(this->m_fastProtocolManager->DecodeAstsIncrementalTLRCURR());
                return;
            case AstsPackedTemplateId::AstsIncrementalTLRFONDInfo:
                this->OnIncrementalRefresh_TLR_FOND(this->m_fastProtocolManager->DecodeAstsIncrementalTLRFOND());
                return;
            case AstsPackedTemplateId::AstsIncrementalMSRCURRInfo:
                this->OnIncrementalRefresh_MSR_CURR(this->m_fastProtocolManager->DecodeAstsIncrementalMSRCURR());
                return;
            case AstsPackedTemplateId::AstsIncrementalMSRFONDInfo:
                this->OnIncrementalRefresh_MSR_FOND(this->m_fastProtocolManager->DecodeAstsIncrementalMSRFOND());
                return;
            case AstsPackedTemplateId::AstsHeartbeatInfo:
                return;
            default:
                return;
        }
    }

    inline void ApplyIncrementalCoreAsts() {
        UINT32 templateId = this->m_fastProtocolManager->ParseHeaderFast();
        if(templateId == AstsPackedTemplateId::AstsIncrementalOLRCURRInfo) {
            this->OnIncrementalRefresh_OLR_CURR(this->m_fastProtocolManager->DecodeAstsIncrementalOLRCURR());
            return;
        }
        if(templateId == AstsPackedTemplateId::AstsIncrementalOLRFONDInfo) {
            this->OnIncrementalRefresh_OLR_FOND(this->m_fastProtocolManager->DecodeAstsIncrementalOLRFOND());
            return;
        }
        this->ApplyIncrementalCoreAsts2(templateId);
    }

    inline void ApplyIncrementalCoreForts() {
        int templateId = this->m_fastProtocolManager->TemplateId();
        if (templateId == FeedTemplateId::fortsIncremental) {
            if (this->m_id == FeedConnectionId::fcidObrForts) {
                this->OnIncrementalRefresh_FORTS_OBR(
                        static_cast<FortsDefaultIncrementalRefreshMessageInfo *>(this->m_fastProtocolManager->LastDecodeInfo()));
                return;
            }
            else {
                this->OnIncrementalRefresh_FORTS_TLR(
                        static_cast<FortsDefaultIncrementalRefreshMessageInfo *>(this->m_fastProtocolManager->LastDecodeInfo()));
                return;
            }
        }
        if(templateId == FeedTemplateId::fortsTradingSessionStatus) {
            this->OnTradingSessionStatusForts(
                    static_cast<FortsTradingSessionStatusInfo *>(this->m_fastProtocolManager->LastDecodeInfo()));
            return;
        }
        else if (templateId == FeedTemplateId::fortsHearthBeat) {
            ((FortsHeartbeatInfo*)this->m_fastProtocolManager->LastDecodeInfo())->Clear();
            return;
        }
    }

    inline bool ProcessSecurityStatus(AstsSecurityStatusInfo *info) {
        if(!this->m_securityDefinition->IsIdfDataCollected())
            return true;
        return this->m_securityDefinition->UpdateSecurityDefinition(info);
    }

    inline bool ProcessSecurityDefinitionUpdateReport(FortsSecurityDefinitionUpdateReportInfo *info) {
        if(!this->m_securityDefinition->IsIdfDataCollected())
            return true;
        return this->m_securityDefinition->UpdateSecurityDefinition(info);
    }

    inline bool ProcessSecurityStatus(FortsSecurityStatusInfo *info) {
        if(!this->m_securityDefinition->IsIdfDataCollected())
            return true;
        return this->m_securityDefinition->UpdateSecurityDefinition(info);
    }

    inline bool ProcessSecurityStatusForts(unsigned char *buffer) {
        this->m_fastProtocolManager->SetNewBuffer(buffer);
        this->m_fastProtocolManager->DecodeFortsHeader();
        bool res = true;
        if(this->m_fastProtocolManager->TemplateId() == FeedTemplateId::fortsSecurityStatus) {
            res = this->ProcessSecurityStatus(this->m_fastProtocolManager->DecodeFortsSecurityStatus());
        }
        else if(this->m_fastProtocolManager->TemplateId() == FeedTemplateId::fortsSecurityDefinitionUpdateReport) {
            res = this->ProcessSecurityDefinitionUpdateReport(this->m_fastProtocolManager->DecodeFortsSecurityDefinitionUpdateReport());
        }
        return res;
    }

    inline bool ShouldSkipMessageForts(unsigned char *buffer) {
        return *((unsigned char*)(buffer + 1)) == 0x86;
    }

    inline bool ShouldSkipMessageAsts(unsigned char *buffer) {
        return *((unsigned short*)(buffer + 1)) == 0xbc10;
    }

    inline bool ShouldSkipMessageAsts(UINT64 header) {
        return AstsPackedTemplateId::AstsHeartbeatInfo == ((header >> 40) & 0xffff);
    }
    inline bool ShouldSkipMessageForts(UINT64 header) {
        return FortsPackedTemplateId::FortsHeartbeatInfo == ((header >> 40) & 0xff);
    }
    inline void ProcessIncrementalAsts(FeedConnectionMessageInfo *info) {
        info->m_processed = true;
        this->m_fastProtocolManager->SetNewBuffer(info->m_address, info->m_size);
        this->ApplyIncrementalCoreAsts();
    }
    inline void CheckUpdateFortsIncrementalParams(int messageIndex) {
        if(this->m_fastProtocolManager->TemplateId() == FeedTemplateId::fortsIncremental) {
            FortsDefaultIncrementalRefreshMessageInfo *info = static_cast<FortsDefaultIncrementalRefreshMessageInfo*>(this->m_fastProtocolManager->LastDecodeInfo());
            if(this->m_fortsIncrementalRouteFirst == messageIndex) // at least should be one MDEntry
                this->m_fortsRouteFirtsSecurityId = info->MDEntries[0]->SecurityID;
            // if there is no LastFragment present in message i.e. it == null then it should be threathed as 1
            if((info->NullMap & FortsDefaultSnapshotMessageInfoNullIndices::LastFragmentNullIndex) != 0)
                info->LastFragment = 1;
            if(info->LastFragment == 1)
                this->m_fortsIncrementalRouteFirst = messageIndex + 1;
        }
        else {
            this->m_fortsIncrementalRouteFirst = messageIndex + 1;
        }
    }
    inline void AfterApplyIncrementalForts(int prevFortsRouteFirst) {
        if(this->m_fortsIncrementalRouteFirst != prevFortsRouteFirst)
            this->m_fortsRouteFirtsSecurityId = 0;
    }

    inline bool ProcessIncrementalForts(FeedConnectionMessageInfo *info, int messageIndex) {
        info->m_processed = true;
        this->m_fastProtocolManager->SetNewBuffer(info->m_address, info->m_size);
        this->m_fastProtocolManager->DecodeForts();

        int prevFortsRouteFirst = this->m_fortsIncrementalRouteFirst;
        this->CheckUpdateFortsIncrementalParams(messageIndex);
        this->ApplyIncrementalCoreForts();
        this->AfterApplyIncrementalForts(prevFortsRouteFirst);
        return true;
    }

    inline void ProcessIncrementalForts(FeedConnectionMessageInfo *info, int messageIndex, int lastNullMsgIndex) {
        unsigned char *buffer = info->m_address;
        info->m_processed = true;
        if(this->ShouldSkipMessageForts(buffer)) {
            this->m_fortsIncrementalRouteFirst = messageIndex + 1;
            return;  // TODO - take this message into account, becasue it determines feed alive
        }

        this->m_fastProtocolManager->SetNewBuffer(buffer, info->m_size);

        // there is no need to check
        this->m_fastProtocolManager->DecodeForts();

        int prevFortsRouteFirst = this->m_fortsIncrementalRouteFirst;
        this->CheckUpdateFortsIncrementalParams(messageIndex);
        // it is unfinished fragmented message.
        if(prevFortsRouteFirst <= lastNullMsgIndex) {
            if(this->m_fastProtocolManager->TemplateId() == FeedTemplateId::fortsIncremental) {
                FortsDefaultIncrementalRefreshMessageInfo *ri = static_cast<FortsDefaultIncrementalRefreshMessageInfo*>(this->m_fastProtocolManager->LastDecodeInfo());
                if ((ri->NullMap & FortsDefaultIncrementalRefreshMessageInfoNullIndices::LastFragmentNullIndex) == 0) {
                    ri->Clear();
                    return;
                }
            }
        }
        this->ApplyIncrementalCoreForts();
        this->AfterApplyIncrementalForts(prevFortsRouteFirst);
    }

    inline bool ProcessSecurityStatus(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
        info->m_processed = true;
        if(this->ShouldSkipMessageAsts(buffer))
            return true;
        this->m_fastProtocolManager->SetNewBuffer(buffer, info->m_size);
        UINT32 templateId = this->m_fastProtocolManager->ParseHeaderFast();
        if(templateId == AstsPackedTemplateId::AstsSecurityStatusInfo)
            return this->ProcessSecurityStatus(this->m_fastProtocolManager->DecodeAstsSecurityStatus());
        return true;
    }

    inline bool ProcessSecurityStatusForts(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
        info->m_processed = true;
        if(this->ShouldSkipMessageForts(buffer)) {
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }
        return this->ProcessSecurityStatusForts(buffer);
    }

public:
    FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
    virtual ~FeedConnection();

    inline int LastMsgSeqNumProcessed() { return this->m_lastMsgSeqNumProcessed; }
    inline MarketDataTable<OrderInfo, AstsOLSFONDInfo, AstsOLSFONDItemInfo> *OrderFond() { return this->m_orderTableFond; }
    inline MarketDataTable<OrderInfo, AstsOLSCURRInfo, AstsOLSCURRItemInfo> *OrderCurr() { return this->m_orderTableCurr; }
    inline MarketDataTable<TradeInfo, AstsTLSFONDInfo, AstsTLSFONDItemInfo> *TradeFond() { return this->m_tradeTableFond; }
    inline MarketDataTable<TradeInfo, AstsTLSCURRInfo, AstsTLSCURRItemInfo> *TradeCurr() { return this->m_tradeTableCurr; }
    inline MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo> *StatisticFond() { return this->m_statTableFond; }
    inline MarketDataTable<StatisticsInfo, AstsGenericInfo, AstsGenericItemInfo> *StatisticCurr() { return this->m_statTableCurr; }

    inline MarketDataTable<OrderBookInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo> *OrderBookForts() { return this->m_fortsOrderBookTable; }
    inline MarketDataTable<TradeInfo, FortsDefaultSnapshotMessageInfo, FortsDefaultSnapshotMessageMDEntriesItemInfo> *TradeForts() { return this->m_fortsTradeBookTable; }

    inline LinkedPointer<AstsSecurityDefinitionInfo>** Symbols() { return this->m_symbols; }
    inline LinkedPointer<FortsSecurityDefinitionInfo>** SymbolsForts() { return this->m_symbolsForts; }
    inline AstsSecurityDefinitionInfo* Symbol(int index) { return this->m_symbols[index]->Data(); }
    inline FortsSecurityDefinitionInfo* SymbolForts(int index) { return this->m_symbolsForts[index]->Data(); }
    inline int SymbolCount() { return this->m_symbolsCount; }
    inline FeedConnectionSecurityDefinitionMode SecurityDefinitionMode() { return this->m_idfMode; }

    inline void SetSymbolManager(SymbolManager *manager) { this->m_symbolManager = manager; }
    inline SymbolManager* GetSymbolManager() { return this->m_symbolManager; }

#ifdef TEST
    inline void WaitLostIncrementalMessageMaxTimeMcs(int timeMs) { this->m_waitLostIncrementalMessageMaxTimeMcs = timeMs; }
    inline int WaitLostIncrementalMessageMaxTimeMcs() { return this->m_waitLostIncrementalMessageMaxTimeMcs; }

    inline void WaitIncrementalMessageMaxTimeMcs(int timeMs) { this->m_waitIncrementalMessageMaxTimeMcs = timeMs; }
    inline int WaitIncrementalMessageMaxTimeMcs() { return this->m_waitIncrementalMessageMaxTimeMcs; }

    inline void WaitSnapshotMaxTimeMcs(int timeMs) { this->m_snapshotMaxTimeMcs = timeMs; }
    inline int WaitSnapshotMaxTimeMcs() { return this->m_snapshotMaxTimeMcs; }
#endif

    inline void ClearMessages() {
        for(int i = 0;i < this->m_packetsCount; i++)
            this->m_packets[i]->Clear();
        this->m_windowMsgSeqNum = 1;
        this->m_startMsgSeqNum = 1;
        this->m_endMsgSeqNum = 0;
    }

    inline void StartNewSnapshot() {
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartNewSnapshot, true);
        this->m_endMsgSeqNum = -1;
        this->m_startMsgSeqNum = -1;
        this->m_windowMsgSeqNum = 0;
        this->m_snapshotRouteFirst = -1;
        this->m_snapshotLastFragment = -1;
        this->m_nextFortsSnapshotRouteFirst = -1;
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
        if(this->m_incremental != 0) {
            this->m_incremental->SetSnapshot(this);
        }
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
    void AddConnectionForHistoricalReplay(FeedConnection *conn) {
        for(int i = 0; i < this->m_connToRecvHistoricalReplayCount; i++) {
            if(this->m_connToRecvHistoricalReplay[i] == conn)
                return;
        }
        this->m_connToRecvHistoricalReplay[this->m_connToRecvHistoricalReplayCount] = conn;
        this->m_connToRecvHistoricalReplayCount++;
    }
    inline void EnableHistoricalReplay(bool enable) { this->m_enableHistoricalReplay = enable; }
    inline void SetHistoricalReplay(FeedConnection *historicalReplay) {
        this->m_historicalReplay = historicalReplay;
        this->m_historicalReplay->AddConnectionForHistoricalReplay(this);
    }
    inline FeedConnection* HistoricalReplay() { return this->m_historicalReplay; }

    inline void SetSecurityDefinition(FeedConnection *securityDefinition) {
        this->m_securityDefinition = securityDefinition;
        this->m_symbolManager = this->m_securityDefinition->m_symbolManager;
    }
    inline FeedConnection* SecurityDefinition() { return this->m_securityDefinition; }

    inline FeedConnection** ConnectionsToRecvSymbols() { return this->m_connectionsToRecvSymbols; }
    inline int ConnectionsToRecvSymbolsCount() { return this->m_connectionsToRecvSymbolsCount; }
    inline void AddConnectionToRecvSymbol(FeedConnection *conn) {
        if(conn == 0)
            return;
        conn->SetSecurityDefinition(this);
        this->m_connectionsToRecvSymbols[this->m_connectionsToRecvSymbolsCount] = conn;
        this->m_connectionsToRecvSymbolsCount++;
    }

    inline int CalcSessionsCount(AstsSecurityDefinitionInfo *info) {
        int res = 0;
        AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
            res += info->MarketSegmentGrp[i]->TradingSessionRulesGrpCount;
        }
        return res;
    }

    inline void AddSymbol(LinkedPointer<FortsSecurityDefinitionInfo> *ptr, int index) {
        FortsSecurityDefinitionInfo *info = ptr->Data();
        if(this->m_fortsOrderBookTable != 0) {
            MarketSymbolInfo<OrderBookInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>> *symbol = this->m_fortsOrderBookTable->AddSymbol(
                    info->Symbol, info->SymbolLength, index);
            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(1);
            symbol->AddSession(info->TradingSessionID);
        }
        else if(this->m_fortsTradeBookTable != 0) {
            MarketSymbolInfo<TradeInfo<FortsDefaultSnapshotMessageMDEntriesItemInfo>> *symbol = this->m_fortsTradeBookTable->AddSymbol(
                    info->Symbol, info->SymbolLength, index);
            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(1);
            symbol->AddSession(info->TradingSessionID);
        }
    }

    __attribute_noinline__
    void AddSymbol(LinkedPointer<AstsSecurityDefinitionInfo> *ptr, int index) {
        AstsSecurityDefinitionInfo *info = ptr->Data();
        if(this->m_orderTableFond != 0) {
            MarketSymbolInfo<OrderInfo<AstsOLSFONDItemInfo>> *symbol = this->m_orderTableFond->AddSymbol(info->Symbol, info->SymbolLength, index);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID);
                }
            }
            return;
        }
        if(this->m_orderTableCurr != 0) {
            MarketSymbolInfo<OrderInfo<AstsOLSCURRItemInfo>> *symbol = this->m_orderTableCurr->AddSymbol(info->Symbol, info->SymbolLength, index);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID);
                }
            }
            return;
        }
        if(this->m_tradeTableFond != 0) {
            MarketSymbolInfo<TradeInfo<AstsTLSFONDItemInfo>> *symbol = this->m_tradeTableFond->AddSymbol(info->Symbol, info->SymbolLength, index);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID);
                }
            }
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            MarketSymbolInfo<TradeInfo<AstsTLSCURRItemInfo>> *symbol = this->m_tradeTableCurr->AddSymbol(info->Symbol, info->SymbolLength, index);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID);
                }
            }
            return;
        }
        if(this->m_statTableFond != 0) {
            MarketSymbolInfo<StatisticsInfo<AstsGenericItemInfo>> *symbol = this->m_statTableFond->AddSymbol(info->Symbol, info->SymbolLength, index);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID);
                }
            }
            return;
        }
        if(this->m_statTableCurr != 0) {
            MarketSymbolInfo<StatisticsInfo<AstsGenericItemInfo>> *symbol = this->m_statTableCurr->AddSymbol(info->Symbol, info->SymbolLength, index);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID);
                }
            }
            return;
        }
    }

    inline void AddSecurityDefinitionToList(FortsSecurityDefinitionInfo *info, int index) {
        this->m_symbolsForts[index]->Data(info);
        this->m_symbolsCount = index + 1;
    }

    inline void AddSecurityDefinitionToList(AstsSecurityDefinitionInfo *info, int index) {
        this->m_symbols[index]->Data(info);
        this->m_symbolsCount = index + 1;
    }

    inline void MakeUsed(AstsSecurityDefinitionMarketSegmentGrpItemInfo *m, bool used) {
        //TODO NO NEED
        //m->Used = used;
        //AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
        //for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
        //    (*trading)->Used = used;
        //}
    }

    inline void MakeUsed(AstsSecurityDefinitionInfo *info, bool used) {
        //TODO NO NEED
        //info->Used = used;

        //AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        //for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++)
        //   MakeUsed(*market, used);
    }

    inline void MergeSecurityDefinition(AstsSecurityDefinitionInfo *parent, AstsSecurityDefinitionInfo *child) {
        int freeIndex = parent->MarketSegmentGrpCount;
        AstsSecurityDefinitionMarketSegmentGrpItemInfo **market = child->MarketSegmentGrp;
        for(int i = 0; i < child->MarketSegmentGrpCount; i++, market++, freeIndex++) {
            MakeUsed(*market, true);
            parent->MarketSegmentGrp[freeIndex] = *market;
        }
        parent->MarketSegmentGrpCount += child->MarketSegmentGrpCount;
        child->MarketSegmentGrpCount = 0;
    }

    inline void PrintSymbolManagerDebug() {
//        printf("Collected %d symbols\n", this->m_symbolsCount);
//        for(int i = 0; i < this->m_symbolManager->BucketListCount(); i++) {
//            int count = this->m_symbolManager->CalcBucketCollisitonCount(i);
//            if(count != 0)
//                printf("Collision %d = %d\n", i, count);
//        }
        printf("Collected %d symbols\n", this->m_symbolsCount);
    }

    inline void CheckAllSymbols() {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            bool isNewlyAdded = false;
            SymbolInfo *info = this->m_symbolManager->GetSymbol(
                    this->m_symbols[i]->Data()->Symbol,
                    this->m_symbols[i]->Data()->SymbolLength, &isNewlyAdded);
            if(!StringIdComparer::Equal(info->m_text, info->m_length,
                                        this->m_symbols[i]->Data()->Symbol,
                                        this->m_symbols[i]->Data()->SymbolLength)) {
                printf("Error: symbol collision\n");
            }
        }
    }

    inline void OnSecurityDefinitionUpdateAllMessages() {
        this->m_idfDataCollected = true;
        if(!this->m_idfStopAfterUpdateAllMessages)
            return;
        this->m_idfStartMsgSeqNo = 0;
        this->Stop();
        if(this->m_idfSnapshotClient != 0)
            this->m_idfSnapshotClient->FinishSecurityStatusSnapshot();
    }

    inline void OnSecurityDefinitionRecvAllMessages() {
        this->m_idfDataCollected = true;
        this->m_idfStartMsgSeqNo = 0;
        this->ClearPackets(1, this->m_idfMaxMsgSeqNo);
        if(!this->m_idfAllowUpdateData) {
            this->Stop();
        }
        else {
            this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmUpdateData;
            this->m_waitTimer->ResetFast(0);
            this->m_waitTimer->ResetFast(1);
        }
    }

    inline bool ProcessSecurityDefinition(FortsSecurityDefinitionInfo *info) {
        bool wasNewlyAdded = false;

        SymbolInfo *smb = this->m_symbolManager->GetSymbol(info->SecurityID, &wasNewlyAdded);

        if(wasNewlyAdded) {
            this->AddSecurityDefinitionToList(info, smb->m_index);
            printf("add forts security definition %" PRIu64 " symbol = %s index = %d  status = %d\n", info->SecurityID, DebugInfoManager::Default->GetString(info->Symbol, info->SymbolLength, 0), smb->m_index, info->SecurityTradingStatus);
        }
        else {
            printf("update forts security definition %" PRIu64 " symbol = %s index = %d\n", info->SecurityID, DebugInfoManager::Default->GetString(info->Symbol, info->SymbolLength, 0), smb->m_index);
            this->UpdateSecurityDefinition(info);
        }
        return true;
    }

    inline bool ProcessSecurityDefinition(AstsSecurityDefinitionInfo *info) {
        bool wasNewlyAdded = false;

        SymbolInfo *smb = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength, &wasNewlyAdded);

        MakeUsed(info, true);
        if(wasNewlyAdded) {
            this->AddSecurityDefinitionToList(info, smb->m_index);
            //printf("add sd to list index = %d\n", smb->m_index);
            //printf("new sec_def %d. sc = %d\n", info->MsgSeqNum, info->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Allocator->Count()); // TODO
        }
        else {
            LinkedPointer<AstsSecurityDefinitionInfo> *ptr = this->m_symbols[smb->m_index];
            if(!StringIdComparer::Equal(ptr->Data()->Symbol, ptr->Data()->SymbolLength, info->Symbol, info->SymbolLength)) {
                printf("merge symbols are not equal\n");
            }
            this->MergeSecurityDefinition(ptr->Data(), info);
            //printf("merge sec_def %d. sc = %d\n", info->MsgSeqNum, info->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Allocator->Count()); // TODO
        }
        return true;
    }

    inline void InitSymbolsForts(int count) {
        if(this->m_fortsOrderBookTable != 0) {
            this->m_fortsOrderBookTable->InitSymbols(count);
            return;
        }
        if(this->m_fortsTradeBookTable != 0) {
            this->m_fortsTradeBookTable->InitSymbols(count);
            return;
        }
    }

    inline void InitSymbols(int count) {
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
        if(this->m_statTableCurr != 0) {
            this->m_statTableCurr->InitSymbols(count);
            return;
        }
        if(this->m_fortsOrderBookTable != 0) {
            this->m_fortsOrderBookTable->InitSymbols(count);
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

    inline void ClearSecurityDefinitionsAsts() {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            this->m_symbols[i]->Data()->Clear();
            this->m_symbols[i]->Data(0);
        }
        this->m_symbolsCount = 0;
    }

    inline void ClearSecurityDefinitionsForts() {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            this->m_symbolsForts[i]->Data()->Clear();
            this->m_symbolsForts[i]->Data(0);
        }
        this->m_symbolsCount = 0;
    }

    inline void ClearSecurityDefinitions() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            ClearSecurityDefinitionsAsts();
        else
            ClearSecurityDefinitionsForts();
    }

    inline void BeforeProcessSecurityDefinitions() {
        this->ClearSecurityDefinitions();
        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++) {
            this->m_connectionsToRecvSymbols[c]->ClearMarketData();
        }
    }

    inline void AddSecurityDefinition(LinkedPointer<AstsSecurityDefinitionInfo> *ptr, int index) {
        SymbolInfo *smb = this->m_symbolManager->GetSymbol(ptr->Data()->Symbol, ptr->Data()->SymbolLength);
        if(smb->m_index != index)
            throw;

        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++)
            this->m_connectionsToRecvSymbols[c]->AddSymbol(ptr, smb->m_index);
    }

    inline void AddSecurityDefinition(LinkedPointer<FortsSecurityDefinitionInfo> *ptr, int index) {
        SymbolInfo *smb = this->m_symbolManager->GetSymbol(ptr->Data()->SecurityID);
        if(smb->m_index != index)
            throw;

        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++)
            this->m_connectionsToRecvSymbols[c]->AddSymbol(ptr, smb->m_index);
    }

    inline AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* FindTradingSession(AstsSecurityDefinitionInfo *info, UINT32 tradingSessionId) {
        for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
            AstsSecurityDefinitionMarketSegmentGrpItemInfo *m = info->MarketSegmentGrp[i];
            for(int j = 0; j < m->TradingSessionRulesGrpCount; j++) {
                AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *t = m->TradingSessionRulesGrp[j];
                if(t->TradingSessionIDUint == tradingSessionId)
                    return t;
            }
        }
        return 0;
    }

    inline void UpdateTradingSession(AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *trading, AstsSecurityStatusInfo *info) {
        trading->NullMap = info->NullMap;
        StringIdComparer::CopyString(trading->TradingSessionSubID, info->TradingSessionSubID, info->TradingSessionSubIDLength);
        trading->TradingSessionSubIDLength = info->TradingSessionSubIDLength;
        trading->SecurityTradingStatus = info->SecurityTradingStatus;
        //Skip AuctionIndicator because there is no data in feed streams for them
    }

    inline bool UpdateSecurityDefinition(AstsSecurityStatusInfo *info) {
        info->Clear(); // just free object before. Data will not be corrupt
        int index = this->IdfFindBySymbol(info->Symbol, info->SymbolLength);
        AstsSecurityDefinitionInfo *sd = this->Symbol(index);
        AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *trading = FindTradingSession(sd, info->TradingSessionIDUint);
        if(trading == 0) // TODO should we do something for unknow session? or just skip?
            return true;
        UpdateTradingSession(trading, info);
        return true;
    }

    inline SymbolInfo* IdfFindBySecurityId(UINT64 securityId) {
        return this->m_symbolManager->GetExistingSymbol(securityId);
    }

    inline bool UpdateSecurityDefinition(FortsSecurityStatusInfo *info) {
        info->Clear(); // just free object before. Data will not be corrupt
        SymbolInfo *s = this->IdfFindBySecurityId(info->SecurityID);
        if(s == 0)
            return true;
        FortsSecurityDefinitionInfo *sd = this->SymbolForts(s->m_index);
        if(sd == 0) return true;
        sd->SecurityTradingStatus = info->SecurityTradingStatus;
        (&(sd->HighLimitPx))->Set(&(info->HighLimitPx));
        (&(sd->LowLimitPx))->Set(&(info->LowLimitPx));
        (&(sd->InitialMarginOnBuy))->Set(&(info->InitialMarginOnBuy));
        (&(sd->InitialMarginOnSell))->Set(&(info->InitialMarginOnSell));
        (&(sd->InitialMarginSyntetic))->Set(&(info->InitialMarginSyntetic));
        printf("%s isf %s %" PRIu64 "\n", this->m_channelName, DebugInfoManager::Default->GetString(sd->Symbol, sd->SymbolLength, 0), info->SecurityID);
        return true;
    }

    inline bool UpdateSecurityDefinition(FortsSecurityDefinitionUpdateReportInfo *info) {
        info->Clear(); // just free object before. Data will not be corrupt
        SymbolInfo *s= this->IdfFindBySecurityId(info->SecurityID);
        if(s == 0)
            return true;
        FortsSecurityDefinitionInfo *sd = this->SymbolForts(s->m_index);
        if(sd == 0) return true;
        (&(sd->Volatility))->Set(&(info->Volatility));
        (&(sd->TheorPrice))->Set(&(info->TheorPrice));
        (&(sd->TheorPriceLimit))->Set(&(info->TheorPriceLimit));
        //printf("%s update report %s %lu msgSeqNum = %d\n", this->m_channelName, DebugInfoManager::Default->GetString(sd->Symbol, sd->SymbolLength, 0), info->SecurityID, info->MsgSeqNum);
        return true;
    }

    inline void UpdateSecurityDefinitionAsts(FeedConnectionMessageInfo *info) {
        this->m_fastProtocolManager->SetNewBuffer(info->m_address); // skip msg seq num
        this->m_fastProtocolManager->DecodeAstsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fmcSecurityDefinition)
            return;
        AstsSecurityDefinitionInfo *fi = this->m_fastProtocolManager->DecodeAstsSecurityDefinition();
        this->UpdateSecurityDefinition(fi);
    }

    inline void UpdateSecurityDefinitionForts(FeedConnectionMessageInfo *info) {
        this->m_fastProtocolManager->SetNewBuffer(info->m_address); // skip msg seq num
        this->m_fastProtocolManager->DecodeFortsHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedTemplateId::fortsSecurityDefinition)
            return;
        FortsSecurityDefinitionInfo *fi = this->m_fastProtocolManager->DecodeFortsSecurityDefinition();
        this->UpdateSecurityDefinition(fi);
    }

    inline void UpdateSecurityDefinition(FeedConnectionMessageInfo *info) {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            UpdateSecurityDefinitionAsts(info);
        else
            UpdateSecurityDefinitionForts(info);
    }

    bool IsEqualsMarketSegmentGroup(AstsSecurityDefinitionMarketSegmentGrpItemInfo *im, AstsSecurityDefinitionMarketSegmentGrpItemInfo *m) {
        if(im->TradingSessionRulesGrpCount != m->TradingSessionRulesGrpCount)
            return false;
        int sCount = m->TradingSessionRulesGrpCount;
        AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **is = im->TradingSessionRulesGrp;
        AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **s = m->TradingSessionRulesGrp;
        bool equals = true;
        for(int i = 0; i < sCount; i++, is++, s++) {
            if((*is)->TradingSessionIDUint != (*s)->TradingSessionIDUint) {
                equals = false;
                break;
            }
        }
        return equals;
    }

    void ReleaseMarketSegmentGroup(AstsSecurityDefinitionMarketSegmentGrpItemInfo *m) {
        m->Clear();
    }

    inline void ReplaceMarketSegmentGroupById(AstsSecurityDefinitionInfo *info, AstsSecurityDefinitionMarketSegmentGrpItemInfo *m) {
        AstsSecurityDefinitionMarketSegmentGrpItemInfo **im = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, im++) {
            if(!IsEqualsMarketSegmentGroup(*im, m))
                continue;

            this->ReleaseMarketSegmentGroup(info->MarketSegmentGrp[i]);
            info->MarketSegmentGrp[i] = m;
            return;
        }
    }

    inline void UpdateSecurityDefinition(LinkedPointer<AstsSecurityDefinitionInfo> *ptr, AstsSecurityDefinitionInfo *curr) {
        AstsSecurityDefinitionInfo *prev = ptr->Data();
        int mcPrev = prev->MarketSegmentGrpCount;
        int mcCurr = curr->MarketSegmentGrpCount;
        for(int i = 0; i < mcCurr; i++) {
            prev->MarketSegmentGrp[mcPrev + i] = curr->MarketSegmentGrp[i];
        }
        for(int i = 0; i < mcPrev; i++) {
            curr->MarketSegmentGrp[i] = prev->MarketSegmentGrp[i];
        }
        int count = mcPrev + mcCurr;
        curr->MarketSegmentGrpCount = mcPrev;
        for(int i = mcPrev; i < count; i++) {
            ReplaceMarketSegmentGroupById(curr, prev->MarketSegmentGrp[i]);
        }
        prev->Allocator->FreeItem(prev->Pointer);
        ptr->Data(curr);
    }

    inline void UpdateSecurityDefinition(LinkedPointer<FortsSecurityDefinitionInfo> *ptr, FortsSecurityDefinitionInfo *curr) {
        FortsSecurityDefinitionInfo *prev = ptr->Data();
        prev->Clear();
        ptr->Data(curr);
    }

    inline int IdfFindBySymbol(const char *symbol, int symbolLength) {
        return this->m_symbolManager->GetSymbol(symbol, symbolLength)->m_index;
    }

    inline void UpdateSecurityDefinition(AstsSecurityDefinitionInfo *info) {
        SymbolInfo *sm = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength);
        LinkedPointer<AstsSecurityDefinitionInfo> *orig = this->m_symbols[sm->m_index];
        this->UpdateSecurityDefinition(orig, info);
    }

    inline void UpdateSecurityDefinition(FortsSecurityDefinitionInfo *info) {
        SymbolInfo *sm = this->m_symbolManager->GetExistingSymbol(info->SecurityID);
        //TODO remove debug
        if(sm == 0)
            return;
        LinkedPointer<FortsSecurityDefinitionInfo> *orig = this->m_symbolsForts[sm->m_index];
        this->UpdateSecurityDefinition(orig, info);
    }

    inline void AfterProcessSecurityDefinitionsForts() {
        //TODO remove debug
        printf("%s %s symbols count = %d\n", this->m_channelName, this->m_idName, this->m_symbolsCount);

        for(int i = 0; i < this->m_connectionsToRecvSymbolsCount; i++)
            this->m_connectionsToRecvSymbols[i]->InitSymbolsForts(this->m_symbolsCount);

        LinkedPointer<FortsSecurityDefinitionInfo> **ptr = this->m_symbolsForts;
        for(int i = 0; i < this->m_symbolsCount; i++, ptr++)
            this->AddSecurityDefinition(*ptr, i);
    }

    inline void AfterProcessSecurityDefinitionsAsts() {
        //TODO remove debug
        printf("%s %s symbols count = %d\n", this->m_channelName, this->m_idName, this->m_symbolsCount);
        int sessionCount = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for (int j = 0; j < this->m_symbols[i]->Data()->MarketSegmentGrpCount; j++) {
                sessionCount += this->m_symbols[i]->Data()->MarketSegmentGrp[j]->TradingSessionRulesGrpCount;
            }
        }
        printf("%s %s total sessions count = %d\n", this->m_channelName, this->m_idName, sessionCount);

        for(int i = 0; i < this->m_connectionsToRecvSymbolsCount; i++)
            this->m_connectionsToRecvSymbols[i]->InitSymbols(this->m_symbolsCount);

        LinkedPointer<AstsSecurityDefinitionInfo> **ptr = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, ptr++)
            this->AddSecurityDefinition(*ptr, i);
    }

    inline void AfterProcessSecurityDefinitions() {
        if(this->m_marketType == FeedMarketType::fmtAsts)
            AfterProcessSecurityDefinitionsAsts();
        else
            AfterProcessSecurityDefinitionsForts();
    }

    inline bool HasLostPackets(int msgStart, int msgEnd) {
        FeedConnectionMessageInfo **msg = (this->m_packets + msgStart - this->m_windowMsgSeqNum);
        for(int i = msgStart; i <= msgEnd; i++, msg++) {
            if((*msg)->m_address == 0)
                return true;
        }
        return false;
    }

    inline int CalcLostPacketCount(int msgStart, int msgEnd) {
        int sum = 0;
        FeedConnectionMessageInfo **msg = (this->m_packets + msgStart - this->m_windowMsgSeqNum);
        for(int i = msgStart; i <= msgEnd; i++, msg++) {
            if((*msg)->m_address == 0)
                sum++;
        }
        return sum;
    }

    inline bool IsIdfDataCollected() { return this->m_idfDataCollected; }
    inline bool IdfAllowUpdateData() { return this->m_idfAllowUpdateData; }
    inline bool IdfStopAfterUpdateMessages() { return this->m_idfStopAfterUpdateAllMessages; }
    inline void IdfStopAfterUpdateMessages(bool value) { this->m_idfStopAfterUpdateAllMessages = value; }
    inline void IdfAllowUpdateData(bool value) { this->m_idfAllowUpdateData = value; }
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
        if((this->socketAManager == NULL || !this->socketAManager->IsConnected()) &&
                (this->socketBManager == NULL || !this->socketBManager->IsConnected()))
            return true;
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
        if(this->m_type == FeedConnectionType::fctHistoricalReplay && this->m_senderCompId != 0) {
            strcpy(this->m_hsLogonInfo->SenderCompID, this->m_senderCompId);
            this->m_hsLogonInfo->SenderCompIDLength = this->m_senderCompIdLength;
        }
    }
    void SetPassword(const char *password) {
        if(this->m_type == FeedConnectionType::fctHistoricalReplay) {
            this->m_password = HistoricalReplayPassword;
            this->m_passwordLength = HistoricalReplayPasswordLength;
        }
        else {
            this->m_password = password;
            this->m_passwordLength = strlen(this->m_password);
        }
    }

    inline char* ChannelName() { return this->m_channelName; }
    inline void ChannelName(const char *channelName) {
        strcpy(this->m_channelName, channelName);
    }
    inline char* IdName() { return this->m_idName; }
    inline FeedConnectionId Id() { return this->m_id; }

    inline virtual void Decode() {
        DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);

        DefaultLogManager::Default->EndLog(true);
    }

    inline int TotalNumReports() { return this->m_idfMaxMsgSeqNo; }
    inline int MsgSeqNo() { return this->m_startMsgSeqNum; }
    inline int LostPacketCount() { return this->m_lostPacketCount; }
    inline int WindowMsgSeqNo () { return this->m_windowMsgSeqNum; }
    inline int WindowSize() { return this->m_endMsgSeqNum - this->m_windowMsgSeqNum; }
    inline int LastRecvMsgSeqNo() { return this->m_endMsgSeqNum; }
    inline int ExpectedMsgSeqNo() { return this->m_startMsgSeqNum + 1; }
    inline FastProtocolManager* FastManager() { return this->m_fastProtocolManager; }

    inline bool DoWorkAtomCommon(FeedConnectionState st) {
        if(st <= FeedConnectionState::fcsListenSecurityDefinition) {
            if(st == FeedConnectionState::fcsSuspend)
                return true;
            if(st == FeedConnectionState::fcsListenSnapshot)
                return this->ListenSnapshot();
            return this->ListenSecurityDefinition();
        }
        else {
            if(st == FeedConnectionState::fcsHistoricalReplay)
                return this->HistoricalReplay_Atom();
            return this->Reconnect_Atom();
        }
        return true;
    }
    // this if organised by frequency of messages
    // incremental and status messages appear mostly often
    // fcsSuspend = 4,
    // fcsListenSnapshot = 5,
    // fcsListenSecurityDefinition = 6,
    // fcsHistoricalReplay = 7,
    // fcsConnect = 8
    inline bool DoWorkAtomIncremental() {
        FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsListenIncremental)
            return this->ListenIncremental();
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;
    }
    inline bool DoWorkAtomSnapshot() {
        FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsSuspend)
            return true;
        if(st == FeedConnectionState::fcsListenSnapshot)
            return this->ListenSnapshot();
        return this->Reconnect_Atom();
    }
    inline bool DoWorkAtomSecurityStatus() {
        FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsListenSecurityStatus)
            return this->ListenSecurityStatus();
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;
    }
    inline bool DoWorkAtomSecurityDefinition() {
        FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsSuspend)
            return true;
        if(st == FeedConnectionState::fcsListenSecurityDefinition)
            return this->ListenSecurityDefinition();
        return this->Reconnect_Atom();
    }
    inline bool DoWorkAtomHistoricalReplay() {
        return this->HistoricalReplay_Atom();
    }

    inline bool DoWorkAtomIncrementalForts() {
        FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsListenIncrementalForts)
            return this->ListenIncremental_Forts();
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;
    }
    inline bool DoWorkAtomSecurityStatusForts() {
        FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsListenSecurityStatusForts)
            return this->ListenSecurityStatusForts();
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;
    }

    inline FeedConnectionState CalcListenStateByType() {
        if(m_type == FeedConnectionType::fctInstrumentDefinition)
            return FeedConnectionState::fcsListenSecurityDefinition;
        else if(m_type == FeedConnectionType::fctSnapshot)
            return FeedConnectionState::fcsListenSnapshot;
        else if(m_type == FeedConnectionType::fctHistoricalReplay)
            return FeedConnectionState::fcsHistoricalReplay;
        else if(m_type == FeedConnectionType::fctInstrumentStatus)
            return FeedConnectionState::fcsListenSecurityStatus;
        else if(m_type == FeedConnectionType::fctInstrumentStatusForts)
            return FeedConnectionState::fcsListenSecurityStatusForts;
        if(this->m_marketType == FeedMarketType::fmtAsts)
            return FeedConnectionState::fcsListenIncremental;
        return FeedConnectionState::fcsListenIncrementalForts;
    }
    inline void Listen() {
        FeedConnectionState st = CalcListenStateByType();
        if(this->m_state == FeedConnectionState::fcsSuspend)
            this->SetState(st);
        else
            this->SetNextState(st);
    }
    inline void BeforeListenSecurityDefinition() {
        this->ClearPackets(1, this->m_idfMaxMsgSeqNo);
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmCollectData)
            this->ClearSecurityDefinitions();

        this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessToEnd;
        this->m_idfStartMsgSeqNo = 0;
        this->m_idfMaxMsgSeqNo = 0;
        this->m_startMsgSeqNum = 0;
        this->m_endMsgSeqNum = 0;
        this->m_windowMsgSeqNum = 0;
        this->m_idfDataCollected = false;
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmCollectData)
            this->m_symbolManager->Clear();
    }
    inline void BeforeListenSecurityStatus() {
        this->m_securityStatusSnapshotActive = false;
    }
    inline void BeforeListen() {
        if(this->m_type == FeedConnectionType::fctInstrumentDefinition) {
            BeforeListenSecurityDefinition();
        }
        if(this->m_type == FeedConnectionType::fctInstrumentStatus ||
                this->m_type == FeedConnectionType::fctInstrumentStatusForts) {
            BeforeListenSecurityStatus();
        }
        if(this->m_type == FeedConnectionType::fctHistoricalReplay) {
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
        }
        if(this->m_type == FeedConnectionType::fctIncremental || this->m_type == FeedConnectionType::fctIncrementalForts) {
            this->m_requestMessageStartIndex = -1;
        }
    }
    inline bool Start() {
        if(this->m_state == FeedConnectionState::fcsHistoricalReplay)
            return true;
        if(!this->Connect())
            return false;
        if(this->m_state != FeedConnectionState::fcsSuspend)
            return true;
        Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        this->m_waitTimer->StartFast();
        this->m_waitTimer->Stop(1);
        this->m_waitTimer->Stop(2); //for snapshot
        this->m_lostPacketCount = 0; // TODO remove debug?
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
        if(this->m_type == FeedConnectionType::fctSnapshot)
            this->ResetRecvBuffer();
        return true;
    }
    inline FeedConnectionState State() { return this->m_state; }


#ifdef TEST
    inline void SetTestMessagesHelper(TestMessagesHelper *helper) { this->m_testHelper = helper; }
#endif
};



