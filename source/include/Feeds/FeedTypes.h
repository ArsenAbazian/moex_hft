//
// Created by root on 24.01.17.
//

#ifndef HFT_ROBOT_FEEDTYPES_H
#define HFT_ROBOT_FEEDTYPES_H

typedef enum _FeedMarketType {
    fmtAsts,
    fmtForts
}FeedMarketType;

typedef enum _FeedConnectionMessage {
    fmcLogon = 2101,
    fmcLogout = 2102,
    fcmHeartBeat = 2108,
    fmcSecurityStatus = 2106,
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

typedef enum _FortsMessage {
    fortsSecurityDefinition = 3,
    fortsSecurityDefinitionUpdateReport = 4,
    fortsSecurityStatus = 5
}FortsMessage;

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
    fcidHCurr,
    fcidIdfForts,
    fcidIdfIncForts,
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
    fcsListenSecurityStatus,
    fcsListenSecurityStatusForts,
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
    sdsProcessToEnd,
    sdsProcessFromStart,
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
    IncrementalForts,
    Snapshot,
    InstrumentDefinition,
    InstrumentStatus,
    InstrumentStatusForts,
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
    inline bool IsCleared() {
        return this->m_address == 0 && !this->m_processed && !this->m_requested;
    }
};

class FeedConnectionRequestMessageInfo {
    int                         m_startMsgSeqNo;
    int                         m_endMsgSeqNo;
    int                         m_lastRecvMsgSeqNo;
public:
    FeedConnection             *m_conn;
    int                         m_requestCount;

    FeedConnectionRequestMessageInfo() {
        this->m_requestCount = 0;
        this->m_startMsgSeqNo = 0;
        this->m_endMsgSeqNo = 0;
        this->m_conn = 0;
    }
    inline void Clear() {
        this->m_requestCount = 0;
        this->m_startMsgSeqNo = 0;
        this->m_endMsgSeqNo = 0;
        this->m_conn = 0;
    }

    inline void SetMsgSeq(int start, int end) {
        this->m_startMsgSeqNo = start;
        this->m_endMsgSeqNo = end;
        this->m_lastRecvMsgSeqNo = start - 1;
    }

    inline int StartMsgSeqNo() { return this->m_startMsgSeqNo; }
    inline int EndMsgSeqNo() { return this->m_endMsgSeqNo; }
    inline bool IsAllMessagesReceived() { return this->m_lastRecvMsgSeqNo == this->m_endMsgSeqNo; }
    inline void IncMsgSeqNo() { this->m_lastRecvMsgSeqNo++; }
    inline int LastRecvMsgSeqNo() { return this->m_lastRecvMsgSeqNo; }
};

#endif //HFT_ROBOT_FEEDTYPES_H
