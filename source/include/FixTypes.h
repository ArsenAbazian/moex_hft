//
// Created by arsen on 11.07.16.
//

#ifndef HFT_ROBOT_FIXTYPES_H
#define HFT_ROBOT_FIXTYPES_H

#include "Types.h"
#include "UTCTimeConverter.h"

#pragma pack(push)
#pragma pack(4)
typedef struct _PartyInfo {
    char	ID[16];
    int		IDLength;
    char	IDSource;
    int		Role;
} FixPartyInfo;

typedef struct _UnderlyingSymbolInfo {
    char	Symbol[16];
    int		SymbolLength;
    char	SymbolSfx[16];
    int		SymbolSfxLength;
    char	SecurityId[16];
    int		SecurityIdLength;
    char	SecurityIdSource[32];
    int		SecurityIdSourceLength;
    int		NoSecurityAltId;
    char	SecurityAltId[16][16];	// max 16
    int		SecurityAltIdLength[16];
    char	SecurityAltIdSource[16][32];
    int		SecurityAltIdSourceLength[16];
    bool	AllowProduct;
    int		Product;
    char	CfiCode[32];
    int		CfiCodeLength;
    char	SecurityType[16];
    int		SecurityTypeLength;
    char	SecuritySubType[32];
    int		SecuritySubTypeLength;
    bool	AllowMonthYear;
    int		Month;
    int		Year;
    char	MonthYearString[8];
    int		MaturityDateMonth;
    int		MaturityDateYear;
    bool	AllowMaturityDate;
    char	MaturityDateString[8];
    int		CouponPaymentDateMonth;
    int		CouponPaymentDateYear;
    bool	AllowCouponPaymentDate;
    char	CouponPaymentDateString[8];
    int		IssueDateMonth;
    int		IssueDateYear;
    bool	AllowIssueDate;
    char	IssueDateString[8];
    bool	AllowRepoCollateralSecurityType;
    int		RepoCollateralSecurityType;
    bool	AllowRepurchaseTerm;
    int		RepurchaseTerm;
    bool	AllowRepurchaseRate;
    float	RepurchaseRate;
    bool	AllowFactor;
    float	Factor;
    char	CreditRating[16];
    int		CreditRatingLength;
    char	InstrRegistry[32];
    int		InstrRegistryLength;
    bool	AllowCountry;
    char	Country[2];
    char	StateOrProvinceOfIssue[128];
    int		StateOrProvinceOfIssueLength;
    char	LocaleOfIssue[32];
    int		LocaleOfIssueLength;
    int		RedemtionDateMonth;
    int		RedemtionDateYear;
    bool	AllowRedemptionDate;
    char	RedemptionDate[8];
    bool	AllowStrikePrice;
    float	StrikePrice;
    bool	AllowStrikeCurrency;
    char	StrikeCurrency[3];
    bool	AllowOptAttribute;
    char	OptAttribute;
    bool	AllowContractMultiplier;
    float	ContractMultiplier;
    bool	AllowCouponRate;
    float	CouponRate;
    char	SecurityExchange[128];
    int		SecurityExchangeLength;
    char	Issuer[64];
    int		IssuerLength;
    int		EncodedIssuerLength;
    char	EncodedIssuer[128];
    int		SecurityDescriptionLength;
    char	SecurityDescription[128];
    int		EncodedSecurityDescriptionLength;
    char	EncodedSecurityDescription[128];
    char	CPProgramm[128];
    int		CPProgrammLength;
    char	CPRegType[64];
    int		CPRegTypeLength;
    bool	AllowCurrency;
    char	Currency[3];
    bool	AllowQty;
    float	Qty;
    bool	AllowPx;
    float	Px;
    bool	AllowDirtyPrice;
    float	DirtyPrice;
    bool	AllowEndPrice;
    float	EndPrice;
    bool	AllowStartValue;
    float	StartValue;
    bool	AllowCurrentValue;
    float	CurrentValue;
    bool	AllowEndValue;
    float	EndValue;
} UnderlyingSymbolInfo;

typedef struct _UnderlyingStipulation {
    char	StipType[32];
    int		StipTypeLength;
    char	StipValue[16];
    int		StipValueLength;
}UnderlyingStipulation;

typedef enum _FixSessionStatus  {
    Active = 0,
    PasswordDoesNotMeetRequirements = 3
}FixSessionStatus;


typedef struct _LogonInfo {
    int MsgStartSeqNo;
    int EncryptionType;
    int HearthBtInt;
    bool ShouldResetSeqNum;
    char SenderCompID[32];
    int SenderCompIDLength;
    char Password[12];
    int PassLength;
    char NewPassword[12];
    int NewPassLength;
    bool AllowSessionStatus;
    FixSessionStatus SessionStatus;
    bool CancelOnDisconnect;
    char LanguageId;
}FixLogonInfo;

typedef enum _FixSessionRejectReason {
    IncorrectTag = 0,
    FieldMissing = 1,
    TagIsNotDefinedForMessage = 2,
    UndefinedTag = 3,
    TagMissingValue = 4,
    IncorrectTagValue = 5,
    DataFormatNotCorrectForTagValue = 6,
    DecryptionProblem = 7,
    SigningProblem = 8,
    CompIDProblem = 9,
    SendingTimeNotCorrect = 10,
    IncorrectMsgType = 11,
    XMLValidationProblem = 12,
    TagIsUsedMoreThanOnce = 13,
    InvalidTagOrder = 14,
    InvalidFieldOrder = 15,
    IncorrectNumInGroup = 16,
    FieldNoDataValueContainsSeparator = 17,
    Other = 99,
    NoReason = -1
}FixSessionRejectReason;


typedef struct _FixOrderStatusRequestInfo {
    char        OrderId[64];
    int         OrderIdLength;
    char        CiOrdId[64];
    int         CiOrdIdLength;
}FixOrderStatusRequestInfo;

static const char	**FixSecurityType = new const char*[5] {
        "FXSPOT",
        "FXSWAP",
        "FXFWD",
        "FXBKT",
        "REPO"
};

static int		*FixSecurityTypeLength = new int[5] {
        6,
        6,
        5,
        5,
        4
};

#define FixCFICodeLength 6

typedef struct _FixInstrumentInfo {
    char	Symbol[12];
    int		SymbolLength;
    bool	AllowProduct;
    int		Product;
    bool	AllowCFICode;
    char	CFICode[6];
    bool	AllowSecurityType;
    char	*SecurityType;
    int		SecurityTypeLength;
}FixInstrumentInfo;

typedef struct _FixPartyListInfo {
    int				Count;
    FixPartyInfo	Parties[16];
}FixPartyListInfo;

typedef struct _FixCommisionData {
    float			Commision;
    char			Type[16];
    int				TypeLength;
}FixCommisionData;

typedef struct _FixOrderQtyData {
    float			Qty;
    float			CashQty;
}FixOrderQtyData;

const char FixSideBuy	= '1';
const char FixSideSell	= '2';

const char FixOrdTypeMarket = '1';
const char FixOrdTypeLimit = '2';
const char FixOrdTypeAveragePrice = 'W';

const int	PercentageNominal = 1;
const int	PerItem = 2;
const int	Debit = 9;

const char FixTradeThruTimeFullDay = '0';
const char FixTradeThruTimeGetAvailable = '3';
const char FixTradeThruTimeFullOrDecline = '4';

typedef struct _FixNewOrderInfo {
    char				ClOrdID[12];
    int					ClOrdIDLength;
    FixPartyListInfo	Parties;
    char				Account[12];
    int					AccountLength;
    bool				AllowMaxFloor;
    float				MaxFloor;
    char				SecClOrdID[12];
    int					SecClOrdIDLength;
    char*				TradingSessionID;
    int					TradingSessionIDLength;
    FixInstrumentInfo	Instrument;
    char				Side;
    SYSTEMTIME			TransactTime;
    char				TransactTimeString[UTCTimeStampLength];
    FixOrderQtyData		OrderQtyData;
    char				OrderType;
    bool				AllowPriceType;
    int					PriceType;
    bool				AllowPrice;
    float				Price;
    bool				AllowTradeThruTime;
    char				TradeThruTime;
    bool				AllowTimeInForce;
    char				TimeInForce;
    bool				AllowEffectiveTime;
    SYSTEMTIME			EffectiveTime;
    char				EffectiveTimeString[UTCTimeStampLength];
    bool				AllowOrderCapacity;
    char				OrderCapacity;
    bool				AllowOrderRestrictions;
    char				OrderRestrictions[128];
    int					OrderRestrictionsLength;
    bool				AllowMaxPiceLevels;
    int					MaxPriceLevels;
    bool				AllowCancelOrigOnReject;
    bool				CancelOrigOnReject;
}FixNewOrderInfo;

typedef struct _FixOrderCancelRequestInfo {
    char				OrigClOrdID[12];
    int					OrigClOrdIDLength;
    char				OrdID[12];
    int					OrdIDLength;
    char				ClOrdID[12];
    int					ClOrdIDLength;
    char				Side;
    SYSTEMTIME			TransactTime;
    char				TransactTimeString[UTCTimeStampLength];
}FixOrderCancelRequestInfo;

const char MassCancelRequestTypeByInstrument = '1';
const char MassCancelRequestTypeByQuery = '7';

typedef struct _FixOrderMassCancelRequest {
    char				ClOrdID[12];
    int					ClOrdIDLength;
    char				SecClOrdID[12];
    int					SecClOrdIDLength;
    char				MassCancelRequestType;
    char*				TradingSessionID;
    int					TradingSessionIDLength;
    FixInstrumentInfo	Instrument;
    bool				AllowSide;
    char				Side;
    SYSTEMTIME			TransactTime;
    char				TransactTimeString[UTCTimeStampLength];
    char				Account[12];
    int					AccountLength;
    bool				AllowParties;
    FixPartyListInfo	Parties;
}FixOrderMassCancelRequestInfo;


// Processing Diagnostic Codes
typedef enum _FixDiagnosticCodes {
    FixDcSuccess,
    FixDcFailed,
    FixDcCheckFixVersion,
    FixDcProcessCheckHeader,
    FixDcProcessMessageBodyLen,
}FixDiagnosticCodes;

typedef enum _FixSecurityRequestType {
    FixSecurityRequestType_RequestSecurityIdentityAndSpecifications = 0,
    FixSecurityRequestType_RequestSecurityIdentityAndSpecificationsProvided = 1,
    FixSecurityRequestType_RequestListSequrityTypes = 2,
    FixSecurityRequestType_RequestListSecurities = 3
}FixSecurityRequestType;

typedef enum _FixSecurityListRequestType {
    FixSecurityListRequestType_Symbol = 0,
    FixSecurityListRequestType_SecurityType_CFICode = 1,
    FixSecurityListRequestType_Product = 2,
    FixSecurityListRequestType_TradingSessionID = 3,
    FixSecurityListRequestType_All = 4
}FixSecurityListRequestType;

typedef struct _FixHeaderInfo {
    char*       name;
    int         nameLength;
    int         bodyLength;
    char        msgType;
    char*       senderCompID;
    int         senderCompIDLength;
    char*       targetCompID;
    int         targetCompIDLength;
    int         msgSeqNum;
    bool        possDupFlag;
    bool        possResend;
    char*       sendingTime;
    char*       origSendingTime;
}FixHeaderInfo;

typedef struct _FixTagValueInfo {
    char		*StartingAddress;
    int			Tag;
    char		*ValueString;
    int			ValueStringLength;
    float		FloatValue;
    int			IntValue;
    char		CharValue;
    int			Length;
}FixTagValueInfo;

typedef struct _FixRejectInfo {
    int         RefMsgSeqNum;
    int         RefTagId;
    char        RefMsgType[512];
    int         RefMsgTypeLength;
    FixSessionRejectReason SessionRejectReason;
    char        Text[512];
    int         TextLength;
    char        EncodedText[512];
    int         EncodedTextLength;
}FixRejectInfo;

typedef struct _Decimal {
    INT32		Mantissa;
    INT32		Exponent;
}Decimal;
#pragma pack(pop)

#define FIX_SEPARATOR 					0x01
#define FIX_SEPARATOR_SECOND_BYTE		0x00000100L
#define FIX_SEPARATOR_THIRD_BYTE		0x00010000L
#define FIX_SEPARATOR_FORTH_BYTE		0x01000000L

#pragma region SessionRejectReason
#define SrrInvalidTagNumber "0" // Invalid tag number
#define SrrRequiredTagMissing "1" // Required tag missing
#define SrrTagNotDefinedForThisMessageType "2" // Tag not defined for this MessageCore type
#define SrrUndefinedTag "3" // Undefined Tag
#define SrrTagSpecifiedWithoutAValue "4" // Tag specified without a value
#define SrrValueIsIncorrectForThisTag "5" // Value is incorrect(out of range) for this tag
#define SrrIncorrectDataFormatForValue "6" // Incorrect data format for value
#define SrrDecryptionProblem "7" // Decryption problem
#define SrrSignatureProblem "8" //Signature <89> problem
#define SrrCompIDProblem "9" //CompID problem
#define SrrSendingTimeProblem "10" //SendingTime <52> accuracy problem
#define SrrInvalidMsgType "11" //Invalid MsgType <35>
#pragma endregion

#pragma region MessageTypes
#define MsgTypeHearthBeat  '0'
#define MsgTypeTestRequest  '1'
#define MsgTypeResendRequest  '2'
#define MsgTypeReject  '3'
#define MsgTypeSequenceReset  '4'
#define MsgTypeLogout  '5'
#define MsgTypeIndicationOfInterest  '6'
#define MsgTypeAdvertisement  '7'
#define MsgTypeExecutionReport  '8'
#define MsgTypeOrderCancelReject  '9'
#define MsgTypeLogon  'A'
#define MsgTypeNews  'B'
#define MsgTypeEmail  'C'
#define MsgTypeOrderSingle  'D'
#define MsgTypeOrderList  'E'
#define MsgTypeOrderCancelRequest  'F'
#define MsgTypeOrderCancelReplaceRequest  'G'
#define MsgTypeOrderStatusRequest  'H'
#define MsgTypeAllocation  'J'
#define MsgTypeListCancelRequest  'K'
#define MsgTypeListExecute  'L'
#define MsgTypeListStatusRequest  'M'
#define MsgTypeListStatus  'N'
#define MsgTypeAllocationACK  'P'
#define MsgTypeDontKnowTrade  'Q'
#define MsgTypeQuoteRequest  'R'
#define MsgTypeQuote  'S'
#define MsgTypeSettlementInstructions  'T'
#define MsgTypeMarketDataRequest  'V'
#define MsgTypeMarketDataSnapshotFullRefresh 'W'
#define MsgTypeMarketDataIncrementalRefresh 'X'
#define MsgTypeMarketDataRequestReject  'Y'
#define MsgTypeQuoteCancel  'Z'
#define MsgTypeQuoteStatusRequest  'a'
#define MsgTypeQuoteAcknowledgement  'b'
#define MsgTypeSecurityDefinitionRequest  'c'
#define MsgTypeSecurityDefinition  'd'
#define MsgTypeSecurityStatusRequest  'e'
#define MsgTypeSecurityStatus  'f'
#define MsgTypeTradingSessionStatusRequest  'g'
#define MsgTypeTradingSessionStatus  'h'
#define MsgTypeMassQuote  'i'
#define MsgTypeBusinessMessageReject  'j'
#define MsgTypeBidRequest  'k'
#define MsgTypeBidResponse  'l'
#define MsgTypeListStrikePrice  'm'
#define MsgTypeOrderMassCancelRequest 'q'
#define MsgTypeSecurityListRequest 'x'
#pragma endregion

#define TagAccount  1
#define TagAdvId  2
#define TagAdvRefID  3
#define TagAdvSide  4
#define TagAdvTransType  5
#define TagAvgPx  6
#define TagBeginSeqNo  7
#define TagBeginString  8
#define TagBodyLength  9
#define TagCheckSum  10
#define TagClOrdID  11
#define TagCommission  12
#define TagCommType  13
#define TagCumQty  14
#define TagCurrency  15
#define TagEndSeqNo  16
#define TagExecID  17
#define TagExecInst  18
#define TagExecRefID  19
#define TagExecTransType  20
#define TagHandlInst  21
#define TagSecurityIDSource  22
#define TagIOIID  23
#define TagIOIOthSvc  24
#define TagIOIQltyInd  25
#define TagIOIRefID  26
#define TagIOIQty  27
#define TagIOITransType  28
#define TagLastCapacity  29
#define TagLastMkt  30
#define TagLastPx  31
#define TagLastQty  32
#define TagNoLinesOfText  33
#define TagMsgSeqNum  34
#define TagMsgType  35
#define TagNewSeqNo  36
#define TagOrderID  37
#define TagOrderQty  38
#define TagOrdStatus  39
#define TagOrdType  40
#define TagOrigClOrdID  41
#define TagOrigTime  42
#define TagPossDupFlag  43
#define TagPrice  44
#define TagRefSeqNum  45
#define TagRelatdSym  46
#define TagRule80A  47
#define TagSecurityID  48
#define TagSenderCompID  49
#define TagSenderSubID  50
#define TagSendingDate  51
#define TagSendingTime  52
#define TagQuantity  53
#define TagSide  54
#define TagSymbol  55
#define TagTargetCompID  56
#define TagTargetSubID  57
#define TagText  58
#define TagTimeInForce  59
#define TagTransactTime  60
#define TagUrgency  61
#define TagValidUntilTime  62
#define TagSettlType  63
#define TagSettlDate  64
#define TagSymbolSfx  65
#define TagListID  66
#define TagListSeqNo  67
#define TagTotNoOrders  68
#define TagListExecInst  69
#define TagAllocID  70
#define TagAllocTransType  71
#define TagRefAllocID  72
#define TagNoOrders  73
#define TagAvgPxPrecision  74
#define TagTradeDate  75
#define TagExecBroker  76
#define TagPositionEffect  77
#define TagNoAllocs  78
#define TagAllocAccount  79
#define TagAllocQty  80
#define TagProcessCode  81
#define TagNoRpts  82
#define TagRptSeq  83
#define TagCxlQty  84
#define TagNoDlvyInst  85
#define TagDlvyInst  86
#define TagAllocStatus  87
#define TagAllocRejCode  88
#define TagSignature  89
#define TagSecureDataLen  90
#define TagSecureData  91
#define TagBrokerOfCredit  92
#define TagSignatureLength  93
#define TagEmailType  94
#define TagRawDataLength  95
#define TagRawData  96
#define TagPossResend  97
#define TagEncryptMethod  98
#define TagStopPx  99
#define TagExDestination  100
#define TagCxlRejReason  102
#define TagOrdRejReason  103
#define TagIOIQualifier  104
#define TagWaveNo  105
#define TagIssuer  106
#define TagSecurityDesc  107
#define TagHeartBtInt  108
#define TagClientID  109
#define TagMinQty  110
#define TagMaxFloor  111
#define TagTestReqID  112
#define TagReportToExch  113
#define TagLocateReqd  114
#define TagOnBehalfOfCompID  115
#define TagOnBehalfOfSubID  116
#define TagQuoteID  117
#define TagNetMoney  118
#define TagSettlCurrAmt  119
#define TagSettlCurrency  120
#define TagForexReq  121
#define TagOrigSendingTime  122
#define TagGapFillFlag  123
#define TagNoExecs  124
#define TagCxlType  125
#define TagExpireTime  126
#define TagDKReason  127
#define TagDeliverToCompID  128
#define TagDeliverToSubID  129
#define TagIOINaturalFlag  130
#define TagQuoteReqID  131
#define TagBidPx  132
#define TagOfferPx  133
#define TagBidSize  134
#define TagOfferSize  135
#define TagNoMiscFees  136
#define TagMiscFeeAmt  137
#define TagMiscFeeCurr  138
#define TagMiscFeeType  139
#define TagPrevClosePx  140
#define TagResetSeqNumFlag  141
#define TagSenderLocationID  142
#define TagTargetLocationID  143
#define TagOnBehalfOfLocationID  144
#define TagDeliverToLocationID  145
#define TagNoRelatedSym  146
#define TagSubject  147
#define TagHeadline  148
#define TagURLLink  149
#define TagExecType  150
#define TagLeavesQty  151
#define TagCashOrderQty  152
#define TagAllocAvgPx  153
#define TagAllocNetMoney  154
#define TagSettlCurrFxRate  155
#define TagSettlCurrFxRateCalc  156
#define TagNumDaysInterest  157
#define TagAccruedInterestRate  158
#define TagAccruedInterestAmt  159
#define TagSettlInstMode  160
#define TagAllocText  161
#define TagSettlInstID  162
#define TagSettlInstTransType  163
#define TagEmailThreadID  164
#define TagSettlInstSource  165
#define TagSettlLocation  166
#define TagSecurityType  167
#define TagEffectiveTime  168
#define TagStandInstDbType  169
#define TagStandInstDbName  170
#define TagStandInstDbID  171
#define TagSettlDeliveryType  172
#define TagSettlDepositoryCode  173
#define TagSettlBrkrCode  174
#define TagSettlInstCode  175
#define TagSecuritySettlAgentName  176
#define TagSecuritySettlAgentCode  177
#define TagSecuritySettlAgentAcctNum  178
#define TagSecuritySettlAgentAcctName  179
#define TagSecuritySettlAgentContactName  180
#define TagSecuritySettlAgentContactPhone  181
#define TagCashSettlAgentName  182
#define TagCashSettlAgentCode  183
#define TagCashSettlAgentAcctNum  184
#define TagCashSettlAgentAcctName  185
#define TagCashSettlAgentContactName  186
#define TagCashSettlAgentContactPhone  187
#define TagBidSpotRate  188
#define TagBidForwardPoints  189
#define TagOfferSpotRate  190
#define TagOfferForwardPoints  191
#define TagOrderQty2  192
#define TagSettlDate2  193
#define TagLastSpotRate  194
#define TagLastForwardPoints  195
#define TagAllocLinkID  196
#define TagAllocLinkType  197
#define TagSecondaryOrderID  198
#define TagNoIOIQualifiers  199
#define TagMaturityMonthYear  200
#define TagPutOrCall  201
#define TagStrikePrice  202
#define TagCoveredOrUncovered  203
#define TagCustomerOrFirm  204
#define TagMaturityDay  205
#define TagOptAttribute  206
#define TagSecurityExchange  207
#define TagNotifyBrokerOfCredit  208
#define TagAllocHandlInst  209
#define TagMaxShow  210
#define TagPegOffsetValue  211
#define TagXmlDataLen  212
#define TagXmlData  213
#define TagSettlInstRefID  214
#define TagNoRoutingIDs  215
#define TagRoutingType  216
#define TagRoutingID  217
#define TagSpread  218
#define TagBenchmark  219
#define TagBenchmarkCurveCurrency  220
#define TagBenchmarkCurveName  221
#define TagBenchmarkCurvePoint  222
#define TagCouponRate  223
#define TagCouponPaymentDate  224
#define TagIssueDate  225
#define TagRepurchaseTerm  226
#define TagRepurchaseRate  227
#define TagFactor  228
#define TagTradeOriginationDate  229
#define TagExDate  230
#define TagContractMultiplier  231
#define TagNoStipulations  232
#define TagStipulationType  233
#define TagStipulationValue  234
#define TagYieldType  235
#define TagYield  236
#define TagTotalTakedown  237
#define TagConcession  238
#define TagRepoCollateralSecurityType  239
#define TagRedemptionDate  240
#define TagUnderlyingCouponPaymentDate  241
#define TagUnderlyingIssueDate  242
#define TagUnderlyingRepoCollateralSecurityType  243
#define TagUnderlyingRepurchaseTerm  244
#define TagUnderlyingRepurchaseRate  245
#define TagUnderlyingFactor  246
#define TagUnderlyingRedemptionDate  247
#define TagLegCouponPaymentDate  248
#define TagLegIssueDate  249
#define TagLegRepoCollateralSecurityType  250
#define TagLegRepurchaseTerm  251
#define TagLegRepurchaseRate  252
#define TagLegFactor  253
#define TagLegRedemptionDate  254
#define TagCreditRating  255
#define TagUnderlyingCreditRating  256
#define TagLegCreditRating  257
#define TagTradedFlatSwitch  258
#define TagBasisFeatureDate  259
#define TagBasisFeaturePrice  260
#define TagMDReqID  262
#define TagSubscriptionRequestType  263
#define TagMarketDepth  264
#define TagMDUpdateType  265
#define TagAggregatedBook  266
#define TagNoMDEntryTypes  267
#define TagNoMDEntries  268
#define TagMDEntryType  269
#define TagMDEntryPx  270
#define TagMDEntrySize  271
#define TagMDEntryDate  272
#define TagMDEntryTime  273
#define TagTickDirection  274
#define TagMDMkt  275
#define TagQuoteCondition  276
#define TagTradeCondition  277
#define TagMDEntryID  278
#define TagMDUpdateAction  279
#define TagMDEntryRefID  280
#define TagMDReqRejReason  281
#define TagMDEntryOriginator  282
#define TagLocationID  283
#define TagDeskID  284
#define TagDeleteReason  285
#define TagOpenCloseSettlFlag  286
#define TagSellerDays  287
#define TagMDEntryBuyer  288
#define TagMDEntrySeller  289
#define TagMDEntryPositionNo  290
#define TagFinancialStatus  291
#define TagCorporateAction  292
#define TagDefBidSize  293
#define TagDefOfferSize  294
#define TagNoQuoteEntries  295
#define TagNoQuoteSets  296
#define TagQuoteStatus  297
#define TagQuoteCancelType  298
#define TagQuoteEntryID  299
#define TagQuoteRejectReason  300
#define TagQuoteResponseLevel  301
#define TagQuoteSetID  302
#define TagQuoteRequestType  303
#define TagTotNoQuoteEntries  304
#define TagUnderlyingSecurityIDSource  305
#define TagUnderlyingIssuer  306
#define TagUnderlyingSecurityDesc  307
#define TagUnderlyingSecurityExchange  308
#define TagUnderlyingSecurityID  309
#define TagUnderlyingSecurityType  310
#define TagUnderlyingSymbol  311
#define TagUnderlyingSymbolSfx  312
#define TagUnderlyingMaturityMonthYear  313
#define TagUnderlyingMaturityDay  314
#define TagUnderlyingPutOrCall  315
#define TagUnderlyingStrikePrice  316
#define TagUnderlyingOptAttribute  317
#define TagUnderlyingCurrency  318
#define TagRatioQty  319
#define TagSecurityReqID  320
#define TagSecurityRequestType  321
#define TagSecurityResponseID  322
#define TagSecurityResponseType  323
#define TagSecurityStatusReqID  324
#define TagUnsolicitedIndicator  325
#define TagSecurityTradingStatus  326
#define TagHaltReason  327
#define TagInViewOfCommon  328
#define TagDueToRelated  329
#define TagBuyVolume  330
#define TagSellVolume  331
#define TagHighPx  332
#define TagLowPx  333
#define TagAdjustment  334
#define TagTradSesReqID  335
#define TagTradingSessionID  336
#define TagContraTrader  337
#define TagTradSesMethod  338
#define TagTradSesMode  339
#define TagTradSesStatus  340
#define TagTradSesStartTime  341
#define TagTradSesOpenTime  342
#define TagTradSesPreCloseTime  343
#define TagTradSesCloseTime  344
#define TagTradSesEndTime  345
#define TagNumberOfOrders  346
#define TagMessageEncoding  347
#define TagEncodedIssuerLen  348
#define TagEncodedIssuer  349
#define TagEncodedSecurityDescLen  350
#define TagEncodedSecurityDesc  351
#define TagEncodedListExecInstLen  352
#define TagEncodedListExecInst  353
#define TagEncodedTextLen  354
#define TagEncodedText  355
#define TagEncodedSubjectLen  356
#define TagEncodedSubject  357
#define TagEncodedHeadlineLen  358
#define TagEncodedHeadline  359
#define TagEncodedAllocTextLen  360
#define TagEncodedAllocText  361
#define TagEncodedUnderlyingIssuerLen  362
#define TagEncodedUnderlyingIssuer  363
#define TagEncodedUnderlyingSecurityDescLen  364
#define TagEncodedUnderlyingSecurityDesc  365
#define TagAllocPrice  366
#define TagQuoteSetValidUntilTime  367
#define TagQuoteEntryRejectReason  368
#define TagLastMsgSeqNumProcessed  369
#define TagOnBehalfOfSendingTime  370
#define TagRefTagID  371
#define TagRefMsgType  372
#define TagSessionRejectReason  373
#define TagBidRequestTransType  374
#define TagContraBroker  375
#define TagComplianceID  376
#define TagSolicitedFlag  377
#define TagExecRestatementReason  378
#define TagBusinessRejectRefID  379
#define TagBusinessRejectReason  380
#define TagGrossTradeAmt  381
#define TagNoContraBrokers  382
#define TagMaxMessageSize  383
#define TagNoMsgTypes  384
#define TagMsgDirection  385
#define TagNoTradingSessions  386
#define TagTotalVolumeTraded  387
#define TagDiscretionInst  388
#define TagDiscretionOffsetValue  389
#define TagBidID  390
#define TagClientBidID  391
#define TagListName  392
#define TagTotNoRelatedSym  393
#define TagBidType  394
#define TagNumTickets  395
#define TagSideValue1  396
#define TagSideValue2  397
#define TagNoBidDescriptors  398
#define TagBidDescriptorType  399
#define TagBidDescriptor  400
#define TagSideValueInd  401
#define TagLiquidityPctLow  402
#define TagLiquidityPctHigh  403
#define TagLiquidityValue  404
#define TagEFPTrackingError  405
#define TagFairValue  406
#define TagOutsideIndexPct  407
#define TagValueOfFutures  408
#define TagLiquidityIndType  409
#define TagWtAverageLiquidity  410
#define TagExchangeForPhysical  411
#define TagOutMainCntryUIndex  412
#define TagCrossPercent  413
#define TagProgRptReqs  414
#define TagProgPeriodInterval  415
#define TagIncTaxInd  416
#define TagNumBidders  417
#define TagBidTradeType  418
#define TagBasisPxType  419
#define TagNoBidComponents  420
#define TagCountry  421
#define TagTotNoStrikes  422
#define TagPriceType  423
#define TagDayOrderQty  424
#define TagDayCumQty  425
#define TagDayAvgPx  426
#define TagGTBookingInst  427
#define TagNoStrikes  428
#define TagListStatusType  429
#define TagNetGrossInd  430
#define TagListOrderStatus  431
#define TagExpireDate  432
#define TagListExecInstType  433
#define TagCxlRejResponseTo  434
#define TagUnderlyingCouponRate  435
#define TagUnderlyingContractMultiplier  436
#define TagContraTradeQty  437
#define TagContraTradeTime  438
#define TagClearingFirm  439
#define TagClearingAccount  440
#define TagLiquidityNumSecurities  441
#define TagMultiLegReportingType  442
#define TagStrikeTime  443
#define TagListStatusText  444
#define TagEncodedListStatusTextLen  445
#define TagEncodedListStatusText  446
#define TagPartyIDSource  447
#define TagPartyID  448
#define TagTotalVolumeTradedDate  449
#define TagTotalVolumeTradedTime  450
#define TagNetChgPrevDay  451
#define TagPartyRole  452
#define TagNoPartyIDs  453
#define TagNoSecurityAltID  454
#define TagSecurityAltID  455
#define TagSecurityAltIDSource  456
#define TagNoUnderlyingSecurityAltID  457
#define TagUnderlyingSecurityAltID  458
#define TagUnderlyingSecurityAltIDSource  459
#define TagProduct  460
#define TagCFICode  461
#define TagUnderlyingProduct  462
#define TagUnderlyingCFICode  463
#define TagTestMessageIndicator  464
#define TagQuantityType  465
#define TagBookingRefID  466
#define TagIndividualAllocID  467
#define TagRoundingDirection  468
#define TagRoundingModulus  469
#define TagCountryOfIssue  470
#define TagStateOrProvinceOfIssue  471
#define TagLocaleOfIssue  472
#define TagNoRegistDtls  473
#define TagMailingDtls  474
#define TagInvestorCountryOfResidence  475
#define TagPaymentRef  476
#define TagDistribPaymentMethod  477
#define TagCashDistribCurr  478
#define TagCommCurrency  479
#define TagCancellationRights  480
#define TagMoneyLaunderingStatus  481
#define TagMailingInst  482
#define TagTransBkdTime  483
#define TagExecPriceType  484
#define TagExecPriceAdjustment  485
#define TagDateOfBirth  486
#define TagTradeReportTransType  487
#define TagCardHolderName  488
#define TagCardNumber  489
#define TagCardExpDate  490
#define TagCardIssNum  491
#define TagPaymentMethod  492
#define TagRegistAcctType  493
#define TagDesignation  494
#define TagTaxAdvantageType  495
#define TagRegistRejReasonText  496
#define TagFundRenewWaiv  497
#define TagCashDistribAgentName  498
#define TagCashDistribAgentCode  499
#define TagCashDistribAgentAcctNumber  500
#define TagCashDistribPayRef  501
#define TagCashDistribAgentAcctName  502
#define TagCardStartDate  503
#define TagPaymentDate  504
#define TagPaymentRemitterID  505
#define TagRegistStatus  506
#define TagRegistRejReasonCode  507
#define TagRegistRefID  508
#define TagRegistDtls  509
#define TagNoDistribInsts  510
#define TagRegistEmail  511
#define TagDistribPercentage  512
#define TagRegistID  513
#define TagRegistTransType  514
#define TagExecValuationPoint  515
#define TagOrderPercent  516
#define TagOwnershipType  517
#define TagNoContAmts  518
#define TagContAmtType  519
#define TagContAmtValue  520
#define TagContAmtCurr  521
#define TagOwnerType  522
#define TagPartySubID  523
#define TagNestedPartyID  524
#define TagNestedPartyIDSource  525
#define TagSecondaryClOrdID  526
#define TagSecondaryExecID  527
#define TagOrderCapacity  528
#define TagOrderRestrictions  529
#define TagMassCancelRequestType  530
#define TagMassCancelResponse  531
#define TagMassCancelRejectReason  532
#define TagTotalAffectedOrders  533
#define TagNoAffectedOrders  534
#define TagAffectedOrderID  535
#define TagAffectedSecondaryOrderID  536
#define TagQuoteType  537
#define TagNestedPartyRole  538
#define TagNoNestedPartyIDs  539
#define TagTotalAccruedInterestAmt  540
#define TagMaturityDate  541
#define TagUnderlyingMaturityDate  542
#define TagInstrRegistry  543
#define TagCashMargin  544
#define TagNestedPartySubID  545
#define TagScope  546
#define TagMDImplicitDelete  547
#define TagCrossID  548
#define TagCrossType  549
#define TagCrossPrioritization  550
#define TagOrigCrossID  551
#define TagNoSides  552
#define TagUsername  553
#define TagPassword  554
#define TagNoLegs  555
#define TagLegCurrency  556
#define TagTotNoSecurityTypes  557
#define TagNoSecurityTypes  558
#define TagSecurityListRequestType  559
#define TagSecurityRequestResult  560
#define TagRoundLot  561
#define TagMinTradeVol  562
#define TagMultiLegRptTypeReq  563
#define TagLegPositionEffect  564
#define TagLegCoveredOrUncovered  565
#define TagLegPrice  566
#define TagTradSesStatusRejReason  567
#define TagTradeRequestID  568
#define TagTradeRequestType  569
#define TagPreviouslyReported  570
#define TagTradeReportID  571
#define TagTradeReportRefID  572
#define TagMatchStatus  573
#define TagMatchType  574
#define TagOddLot  575
#define TagNoClearingInstructions  576
#define TagClearingInstruction  577
#define TagTradeInputSource  578
#define TagTradeInputDevice  579
#define TagNoDates  580
#define TagAccountType  581
#define TagCustOrderCapacity  582
#define TagClOrdLinkID  583
#define TagMassStatusReqID  584
#define TagMassStatusReqType  585
#define TagOrigOrdModTime  586
#define TagLegSettlType  587
#define TagLegSettlDate  588
#define TagDayBookingInst  589
#define TagBookingUnit  590
#define TagPreallocMethod  591
#define TagUnderlyingCountryOfIssue  592
#define TagUnderlyingStateOrProvinceOfIssue  593
#define TagUnderlyingLocaleOfIssue  594
#define TagUnderlyingInstrRegistry  595
#define TagLegCountryOfIssue  596
#define TagLegStateOrProvinceOfIssue  597
#define TagLegLocaleOfIssue  598
#define TagLegInstrRegistry  599
#define TagLegSymbol  600
#define TagLegSymbolSfx  601
#define TagLegSecurityID  602
#define TagLegSecurityIDSource  603
#define TagNoLegSecurityAltID  604
#define TagLegSecurityAltID  605
#define TagLegSecurityAltIDSource  606
#define TagLegProduct  607
#define TagLegCFICode  608
#define TagLegSecurityType  609
#define TagLegMaturityMonthYear  610
#define TagLegMaturityDate  611
#define TagLegStrikePrice  612
#define TagLegOptAttribute  613
#define TagLegContractMultiplier  614
#define TagLegCouponRate  615
#define TagLegSecurityExchange  616
#define TagLegIssuer  617
#define TagEncodedLegIssuerLen  618
#define TagEncodedLegIssuer  619
#define TagLegSecurityDesc  620
#define TagEncodedLegSecurityDescLen  621
#define TagEncodedLegSecurityDesc  622
#define TagLegRatioQty  623
#define TagLegSide  624
#define TagTradingSessionSubID  625
#define TagAllocType  626
#define TagNoHops  627
#define TagHopCompID  628
#define TagHopSendingTime  629
#define TagHopRefID  630
#define TagMidPx  631
#define TagBidYield  632
#define TagMidYield  633
#define TagOfferYield  634
#define TagClearingFeeIndicator  635
#define TagWorkingIndicator  636
#define TagLegLastPx  637
#define TagPriorityIndicator  638
#define TagPriceImprovement  639
#define TagPrice2  640
#define TagLastForwardPoints2  641
#define TagBidForwardPoints2  642
#define TagOfferForwardPoints2  643
#define TagRFQReqID  644
#define TagMktBidPx  645
#define TagMktOfferPx  646
#define TagMinBidSize  647
#define TagMinOfferSize  648
#define TagQuoteStatusReqID  649
#define TagLegalConfirm  650
#define TagUnderlyingLastPx  651
#define TagUnderlyingLastQty  652
#define TagSecDefStatus  653
#define TagLegRefID  654
#define TagContraLegRefID  655
#define TagSettlCurrBidFxRate  656
#define TagSettlCurrOfferFxRate  657
#define TagQuoteRequestRejectReason  658
#define TagSideComplianceID  659
#define TagAcctIDSource  660
#define TagAllocAcctIDSource  661
#define TagBenchmarkPrice  662
#define TagBenchmarkPriceType  663
#define TagConfirmID  664
#define TagConfirmStatus  665
#define TagConfirmTransType  666
#define TagContractSettlMonth  667
#define TagDeliveryForm  668
#define TagLastParPx  669
#define TagNoLegAllocs  670
#define TagLegAllocAccount  671
#define TagLegIndividualAllocID  672
#define TagLegAllocQty  673
#define TagLegAllocAcctIDSource  674
#define TagLegSettlCurrency  675
#define TagLegBenchmarkCurveCurrency  676
#define TagLegBenchmarkCurveName  677
#define TagLegBenchmarkCurvePoint  678
#define TagLegBenchmarkPrice  679
#define TagLegBenchmarkPriceType  680
#define TagLegBidPx  681
#define TagLegIOIQty  682
#define TagNoLegStipulations  683
#define TagLegOfferPx  684
#define TagLegOrderQty  685
#define TagLegPriceType  686
#define TagLegQty  687
#define TagLegStipulationType  688
#define TagLegStipulationValue  689
#define TagLegSwapType  690
#define TagPool  691
#define TagQuotePriceType  692
#define TagQuoteRespID  693
#define TagQuoteRespType  694
#define TagQuoteQualifier  695
#define TagYieldRedemptionDate  696
#define TagYieldRedemptionPrice  697
#define TagYieldRedemptionPriceType  698
#define TagBenchmarkSecurityID  699
#define TagReversalIndicator  700
#define TagYieldCalcDate  701
#define TagNoPositions  702
#define TagPosType  703
#define TagLongQty  704
#define TagShortQty  705
#define TagPosQtyStatus  706
#define TagPosAmtType  707
#define TagPosAmt  708
#define TagPosTransType  709
#define TagPosReqID  710
#define TagNoUnderlyings  711
#define TagPosMaintAction  712
#define TagOrigPosReqRefID  713
#define TagPosMaintRptRefID  714
#define TagClearingBusinessDate  715
#define TagSettlSessID  716
#define TagSettlSessSubID  717
#define TagAdjustmentType  718
#define TagContraryInstructionIndicator  719
#define TagPriorSpreadIndicator  720
#define TagPosMaintRptID  721
#define TagPosMaintStatus  722
#define TagPosMaintResult  723
#define TagPosReqType  724
#define TagResponseTransportType  725
#define TagResponseDestination  726
#define TagTotalNumPosReports  727
#define TagPosReqResult  728
#define TagPosReqStatus  729
#define TagSettlPrice  730
#define TagSettlPriceType  731
#define TagUnderlyingSettlPrice  732
#define TagUnderlyingSettlPriceType  733
#define TagPriorSettlPrice  734
#define TagNoQuoteQualifiers  735
#define TagAllocSettlCurrency  736
#define TagAllocSettlCurrAmt  737
#define TagInterestAtMaturity  738
#define TagLegDatedDate  739
#define TagLegPool  740
#define TagAllocInterestAtMaturity  741
#define TagAllocAccruedInterestAmt  742
#define TagDeliveryDate  743
#define TagAssignmentMethod  744
#define TagAssignmentUnit  745
#define TagOpenInterest  746
#define TagExerciseMethod  747
#define TagTotNumTradeReports  748
#define TagTradeRequestResult  749
#define TagTradeRequestStatus  750
#define TagTradeReportRejectReason  751
#define TagSideMultiLegReportingType  752
#define TagNoPosAmt  753
#define TagAutoAcceptIndicator  754
#define TagAllocReportID  755
#define TagNoNested2PartyIDs  756
#define TagNested2PartyID  757
#define TagNested2PartyIDSource  758
#define TagNested2PartyRole  759
#define TagNested2PartySubID  760
#define TagBenchmarkSecurityIDSource  761
#define TagSecuritySubType  762
#define TagUnderlyingSecuritySubType  763
#define TagLegSecuritySubType  764
#define TagAllowableOneSidednessPct  765
#define TagAllowableOneSidednessValue  766
#define TagAllowableOneSidednessCurr  767
#define TagNoTrdRegTimestamps  768
#define TagTrdRegTimestamp  769
#define TagTrdRegTimestampType  770
#define TagTrdRegTimestampOrigin  771
#define TagConfirmRefID  772
#define TagConfirmType  773
#define TagConfirmRejReason  774
#define TagBookingType  775
#define TagIndividualAllocRejCode  776
#define TagSettlInstMsgID  777
#define TagNoSettlInst  778
#define TagLastUpdateTime  779
#define TagAllocSettlInstType  780
#define TagNoSettlPartyIDs  781
#define TagSettlPartyID  782
#define TagSettlPartyIDSource  783
#define TagSettlPartyRole  784
#define TagSettlPartySubID  785
#define TagSettlPartySubIDType  786
#define TagDlvyInstType  787
#define TagTerminationType  788
#define TagNextExpectedMsgSeqNum  789
#define TagOrdStatusReqID  790
#define TagSettlInstReqID  791
#define TagSettlInstReqRejCode  792
#define TagSecondaryAllocID  793
#define TagAllocReportType  794
#define TagAllocReportRefID  795
#define TagAllocCancReplaceReason  796
#define TagCopyMsgIndicator  797
#define TagAllocAccountType  798
#define TagOrderAvgPx  799
#define TagOrderBookingQty  800
#define TagNoSettlPartySubIDs  801
#define TagNoPartySubIDs  802
#define TagPartySubIDType  803
#define TagNoNestedPartySubIDs  804
#define TagNestedPartySubIDType  805
#define TagNoNested2PartySubIDs  806
#define TagNested2PartySubIDType  807
#define TagAllocIntermedReqType  808
#define TagUnderlyingPx  810
#define TagPriceDelta  811
#define TagApplQueueMax  812
#define TagApplQueueDepth  813
#define TagApplQueueResolution  814
#define TagApplQueueAction  815
#define TagNoAltMDSource  816
#define TagAltMDSourceID  817
#define TagSecondaryTradeReportID  818
#define TagAvgPxIndicator  819
#define TagTradeLinkID  820
#define TagOrderInputDevice  821
#define TagUnderlyingTradingSessionID  822
#define TagUnderlyingTradingSessionSubID  823
#define TagTradeLegRefID  824
#define TagExchangeRule  825
#define TagTradeAllocIndicator  826
#define TagExpirationCycle  827
#define TagTrdType  828
#define TagTrdSubType  829
#define TagTransferReason  830
#define TagAsgnReqID  831
#define TagTotNumAssignmentReports  832
#define TagAsgnRptID  833
#define TagThresholdAmount  834
#define TagPegMoveType  835
#define TagPegOffsetType  836
#define TagPegLimitType  837
#define TagPegRoundDirection  838
#define TagPeggedPrice  839
#define TagPegScope  840
#define TagDiscretionMoveType  841
#define TagDiscretionOffsetType  842
#define TagDiscretionLimitType  843
#define TagDiscretionRoundDirection  844
#define TagDiscretionPrice  845
#define TagDiscretionScope  846
#define TagTargetStrategy  847
#define TagTargetStrategyParameters  848
#define TagParticipationRate  849
#define TagTargetStrategyPerformance  850
#define TagLastLiquidityInd  851
#define TagPublishTrdIndicator  852
#define TagShortSaleReason  853
#define TagQtyType  854
#define TagSecondaryTrdType  855
#define TagTradeReportType  856
#define TagAllocNoOrdersType  857
#define TagSharedCommission  858
#define TagConfirmReqID  859
#define TagAvgParPx  860
#define TagReportedPx  861
#define TagNoCapacities  862
#define TagOrderCapacityQty  863
#define TagNoEvents  864
#define TagEventType  865
#define TagEventDate  866
#define TagEventPx  867
#define TagEventText  868
#define TagPctAtRisk  869
#define TagNoInstrAttrib  870
#define TagInstrAttribType  871
#define TagInstrAttribValue  872
#define TagDatedDate  873
#define TagInterestAccrualDate  874
#define TagCPProgram  875
#define TagCPRegType  876
#define TagUnderlyingCPProgram  877
#define TagUnderlyingCPRegType  878
#define TagUnderlyingQty  879
#define TagTrdMatchID  880
#define TagSecondaryTradeReportRefID  881
#define TagUnderlyingDirtyPrice  882
#define TagUnderlyingEndPrice  883
#define TagUnderlyingStartValue  884
#define TagUnderlyingCurrentValue  885
#define TagUnderlyingEndValue  886
#define TagNoUnderlyingStips  887
#define TagUnderlyingStipType  888
#define TagUnderlyingStipValue  889
#define TagMaturityNetMoney  890
#define TagMiscFeeBasis  891
#define TagTotNoAllocs  892
#define TagLastFragment  893
#define TagCollReqID  894
#define TagCollAsgnReason  895
#define TagCollInquiryQualifier  896
#define TagNoTrades  897
#define TagMarginRatio  898
#define TagMarginExcess  899
#define TagTotalNetValue  900
#define TagCashOutstanding  901
#define TagCollAsgnID  902
#define TagCollAsgnTransType  903
#define TagCollRespID  904
#define TagCollAsgnRespType  905
#define TagCollAsgnRejectReason  906
#define TagCollAsgnRefID  907
#define TagCollRptID  908
#define TagCollInquiryID  909
#define TagCollStatus  910
#define TagTotNumReports  911
#define TagLastRptRequested  912
#define TagAgreementDesc  913
#define TagAgreementID  914
#define TagAgreementDate  915
#define TagStartDate  916
#define TagEndDate  917
#define TagAgreementCurrency  918
#define TagDeliveryType  919
#define TagEndAccruedInterestAmt  920
#define TagStartCash  921
#define TagEndCash  922
#define TagUserRequestID  923
#define TagUserRequestType  924
#define TagNewPassword  925
#define TagUserStatus  926
#define TagUserStatusText  927
#define TagStatusValue  928
#define TagStatusText  929
#define TagRefCompID  930
#define TagRefSubID  931
#define TagNetworkResponseID  932
#define TagNetworkRequestID  933
#define TagLastNetworkResponseID  934
#define TagNetworkRequestType  935
#define TagNoCompIDs  936
#define TagNetworkStatusResponseType  937
#define TagNoCollInquiryQualifier  938
#define TagTrdRptStatus  939
#define TagAffirmStatus  940
#define TagUnderlyingStrikeCurrency  941
#define TagLegStrikeCurrency  942
#define TagTimeBracket  943
#define TagCollAction  944
#define TagCollInquiryStatus  945
#define TagCollInquiryResult  946
#define TagStrikeCurrency  947
#define TagNoNested3PartyIDs  948
#define TagNested3PartyID  949
#define TagNested3PartyIDSource  950
#define TagNested3PartyRole  951
#define TagNoNested3PartySubIDs  952
#define TagNested3PartySubID  953
#define TagNested3PartySubIDType  954
#define TagLegContractSettlMonth  955
#define TagLegInterestAccrualDate  956

#endif //HFT_ROBOT_FIXTYPES_H
