//
// Created by arsen on 11.07.16.
//

#ifndef HFT_ROBOT_FIXTYPES_H
#define HFT_ROBOT_FIXTYPES_H

#include "../Settings.h"
#include "../Converters/UTCTimeConverter.h"
#include "FixProtocolMacros.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
typedef struct _PartyInfo {
    int     IDLength;
    int     Role;
    char    ID[19];
    char    IDSource;
} FixPartyInfo;

typedef struct _UnderlyingSymbolInfo {
    char    Symbol[16];
    int     SymbolLength;
    char    SymbolSfx[16];
    int     SymbolSfxLength;
    char    SecurityId[16];
    int     SecurityIdLength;
    char    SecurityIdSource[32];
    int     SecurityIdSourceLength;
    int     NoSecurityAltId;
    char    SecurityAltId[16][16];  // max 16
    int     SecurityAltIdLength[16];
    char    SecurityAltIdSource[16][32];
    int     SecurityAltIdSourceLength[16];
    bool    AllowProduct;
    int     Product;
    char    CfiCode[32];
    int     CfiCodeLength;
    char    SecurityType[16];
    int     SecurityTypeLength;
    char    SecuritySubType[32];
    int     SecuritySubTypeLength;
    bool    AllowMonthYear;
    int     Month;
    int     Year;
    char    MonthYearString[8];
    int     MaturityDateMonth;
    int     MaturityDateYear;
    bool    AllowMaturityDate;
    char    MaturityDateString[8];
    int     CouponPaymentDateMonth;
    int     CouponPaymentDateYear;
    bool    AllowCouponPaymentDate;
    char    CouponPaymentDateString[8];
    int     IssueDateMonth;
    int     IssueDateYear;
    bool    AllowIssueDate;
    char    IssueDateString[8];
    bool    AllowRepoCollateralSecurityType;
    int     RepoCollateralSecurityType;
    bool    AllowRepurchaseTerm;
    int     RepurchaseTerm;
    bool    AllowRepurchaseRate;
    float   RepurchaseRate;
    bool    AllowFactor;
    float   Factor;
    char    CreditRating[16];
    int     CreditRatingLength;
    char    InstrRegistry[32];
    int     InstrRegistryLength;
    bool    AllowCountry;
    char    Country[2];
    char    StateOrProvinceOfIssue[128];
    int     StateOrProvinceOfIssueLength;
    char    LocaleOfIssue[32];
    int     LocaleOfIssueLength;
    int     RedemtionDateMonth;
    int     RedemtionDateYear;
    bool    AllowRedemptionDate;
    char    RedemptionDate[8];
    bool    AllowStrikePrice;
    float   StrikePrice;
    bool    AllowStrikeCurrency;
    char    StrikeCurrency[3];
    bool    AllowOptAttribute;
    char    OptAttribute;
    bool    AllowContractMultiplier;
    float   ContractMultiplier;
    bool    AllowCouponRate;
    float   CouponRate;
    char    SecurityExchange[128];
    int     SecurityExchangeLength;
    char    Issuer[64];
    int     IssuerLength;
    int     EncodedIssuerLength;
    char    EncodedIssuer[128];
    int     SecurityDescriptionLength;
    char    SecurityDescription[128];
    int     EncodedSecurityDescriptionLength;
    char    EncodedSecurityDescription[128];
    char    CPProgramm[128];
    int     CPProgrammLength;
    char    CPRegType[64];
    int     CPRegTypeLength;
    bool    AllowCurrency;
    char    Currency[3];
    bool    AllowQty;
    float   Qty;
    bool    AllowPx;
    float   Px;
    bool    AllowDirtyPrice;
    float   DirtyPrice;
    bool    AllowEndPrice;
    float   EndPrice;
    bool    AllowStartValue;
    float   StartValue;
    bool    AllowCurrentValue;
    float   CurrentValue;
    bool    AllowEndValue;
    float   EndValue;
} UnderlyingSymbolInfo;

typedef struct _UnderlyingStipulation {
    char    StipType[32];
    int     StipTypeLength;
    char    StipValue[16];
    int     StipValueLength;
}UnderlyingStipulation;

typedef enum _FixSessionStatus  {
    fssActive = 0,
    fssPasswordDoesNotMeetRequirements = 3
}FixSessionStatus;


typedef struct _LogonInfo {
    int                 MsgStartSeqNo;
    int                 EncryptionType;
    int                 HearthBtInt;
    int                 SenderCompIDLength;
    int                 UserNameLength;
    int                 PassLength;
    int                 NewPassLength;
    char                SenderCompID[32];
    char                UserName[32];
    char                Password[16];
    char                NewPassword[16];
    FixSessionStatus    SessionStatus;
    bool                AllowSessionStatus;
    bool                CancelOnDisconnect;
    char                LanguageId;
    bool                ShouldResetSeqNum;
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

static const char   **FixSecurityType = new const char*[5] {
        "FXSPOT",
        "FXSWAP",
        "FXFWD",
        "FXBKT",
        "REPO"
};

static int      *FixSecurityTypeLength = new int[5] {
        6,
        6,
        5,
        5,
        4
};

#define FixCFICodeLength 6

typedef struct _FixInstrumentInfo {
    char    Symbol[12];
    int     SymbolLength;
    bool    AllowProduct;
    int     Product;
    bool    AllowCFICode;
    char    CFICode[6];
    bool    AllowSecurityType;
    char    *SecurityType;
    int     SecurityTypeLength;
}FixInstrumentInfo;

typedef struct _FixPartyListInfo {
    int             Count;
    FixPartyInfo    Parties[16];
}FixPartyListInfo;

typedef struct _FixCommisionData {
    float           Commision;
    char            Type[16];
    int             TypeLength;
}FixCommisionData;

typedef struct _FixOrderQtyData {
    float           Qty;
    float           CashQty;
}FixOrderQtyData;

const char FixSideBuy   = '1';
const char FixSideSell  = '2';

const char FixOrdTypeMarket = '1';
const char FixOrdTypeLimit = '2';
const char FixOrdTypeAveragePrice = 'W';

const int   PercentageNominal = 1;
const int   PerItem = 2;
const int   Debit = 9;

const char FixTradeThruTimeFullDay = '0';
const char FixTradeThruTimeGetAvailable = '3';
const char FixTradeThruTimeFullOrDecline = '4';

#pragma region Tags
static const char* FixProtocolVersion = "FIX.4.4";
static const int FixProtocolVersionLength = 7;
static const char* FastProtocolVersion = "FIXT.1.1";
static const int FastProtocolVersionLength = 8;
#pragma endregion

typedef struct _FixNewOrderInfo {
    char                ClOrdID[12];
    int                 ClOrdIDLength;
    FixPartyListInfo    Parties;
    char                Account[12];
    int                 AccountLength;
    bool                AllowMaxFloor;
    float               MaxFloor;
    char                SecClOrdID[12];
    int                 SecClOrdIDLength;
    char*               TradingSessionID;
    int                 TradingSessionIDLength;
    FixInstrumentInfo   Instrument;
    char                Side;
    SYSTEMTIME          TransactTime;
    char                TransactTimeString[UTCTimeStampLength];
    FixOrderQtyData     OrderQtyData;
    char                OrderType;
    bool                AllowPriceType;
    int                 PriceType;
    bool                AllowPrice;
    float               Price;
    bool                AllowTradeThruTime;
    char                TradeThruTime;
    bool                AllowTimeInForce;
    char                TimeInForce;
    bool                AllowEffectiveTime;
    SYSTEMTIME          EffectiveTime;
    char                EffectiveTimeString[UTCTimeStampLength];
    bool                AllowOrderCapacity;
    char                OrderCapacity;
    bool                AllowOrderRestrictions;
    char                OrderRestrictions[128];
    int                 OrderRestrictionsLength;
    bool                AllowMaxPiceLevels;
    int                 MaxPriceLevels;
    bool                AllowCancelOrigOnReject;
    bool                CancelOrigOnReject;
}FixNewOrderInfo;

typedef struct _FixOrderCancelRequestInfo {
    char                OrigClOrdID[12];
    int                 OrigClOrdIDLength;
    char                OrdID[12];
    int                 OrdIDLength;
    char                ClOrdID[12];
    int                 ClOrdIDLength;
    char                Side;
    SYSTEMTIME          TransactTime;
    char                TransactTimeString[UTCTimeStampLength];
}FixOrderCancelRequestInfo;

const char MassCancelRequestTypeByInstrument = '1';
const char MassCancelRequestTypeByQuery = '7';

typedef struct _FixOrderMassCancelRequest {
    char                ClOrdID[12];
    int                 ClOrdIDLength;
    char                SecClOrdID[12];
    int                 SecClOrdIDLength;
    char                MassCancelRequestType;
    char*               TradingSessionID;
    int                 TradingSessionIDLength;
    FixInstrumentInfo   Instrument;
    bool                AllowSide;
    char                Side;
    SYSTEMTIME          TransactTime;
    char                TransactTimeString[UTCTimeStampLength];
    char                Account[12];
    int                 AccountLength;
    bool                AllowParties;
    FixPartyListInfo    Parties;
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
    char*       sendingTime;
    char*       origSendingTime;
    char*       senderCompID;
    char*       targetCompID;
    int         nameLength;
    int         bodyLength;
    int         senderCompIDLength;
    int         targetCompIDLength;
    int         msgSeqNum;
    bool        possDupFlag;
    bool        possResend;
    char        msgType;
    char        paddingByte;
}FixHeaderInfo;

typedef struct _FixTagValueInfo {
    char        *StartingAddress;
    int         Tag;
    char        *ValueString;
    int         ValueStringLength;
    float       FloatValue;
    int         IntValue;
    char        CharValue;
    int         Length;
}FixTagValueInfo;

typedef struct _FixRejectInfo {
    char        *Text;
    int         RefMsgSeqNum;
    int         RefTagId;
    FixSessionRejectReason SessionRejectReason;
    short       TextLength;
    bool        AllowRefMsgType;
    char        RefMsgType;
}FixRejectInfo;

typedef struct _FixHearthBeatInfo {
    int         TestReqID;
}FixHearthBeatInfo;

typedef struct _FixResendRequestInfo {
    int         BeginSeqNo;
    int         EndSeqNo;
}FixResendRequestInfo;

typedef struct _FixMarketDataRequestInfo {
    char*       FeedId;
    int         FeedIdLength;
    int         BeginSeqNo;
    int         EndSeqNo;
    int         PaddingByte;
}FixMarketDataRequestInfo;

#pragma clang diagnostic pop

class Decimal {
    static INT64 PowOf10[10];
    static float MulOf10[10];
    static float DivOf10[10];

public:
    INT64       Mantissa;
    float       Value;
    INT32       Exponent;

    Decimal(int value) :
            Mantissa(value),
            Exponent(0),
            Value(0) {
    }
    Decimal() : Mantissa(0),
                Exponent(0),
                Value(0) {
    }
    Decimal(INT64 mantissa, INT32 exponent) :
            Mantissa(mantissa),
            Exponent(exponent),
            Value(0) {
    }
    inline void Set(INT64 mantissa, INT32 exponent) {
        this->Mantissa = mantissa;
        this->Exponent = exponent;
    }
    inline void Set(Decimal *value) {
        this->Mantissa = value->Mantissa;
        this->Exponent = value->Exponent;
    }
    inline float DivOf10Func(int value) {
        if(value > 4) {
            if(value > 7) {
                if(value > 8)
                    return 0.000000001;  // 9
                else
                    return 0.00000001;   // 8
            }
            else {
                if(value > 5) {
                    if(value > 6)
                        return 0.0000001;  // 7
                    else
                        return 0.000001;   // 6
                }
                else
                    return 0.00001;  // 5
            }
        }
        else {
            if(value > 2) {
                if(value > 3)
                    return 0.0001;  // 4
                else
                    return 0.001;   // 3
            }
            else {
                if(value > 1)
                    return 0.01;  // 2
                else {
                    if(value == 1)
                        return 0.1;  // 1
                    return 1.0;  // 0
                }
            }
        }
    }
    inline INT64 PowOf10Func(int value) {
        if(value > 4) {
            if(value > 7) {
                if(value > 8)
                    return 1000000000;  // 9
                else
                    return 100000000;   // 8
            }
            else {
                if(value > 5) {
                    if(value > 6)
                        return 10000000;  // 7
                    else
                        return 1000000;   // 6
                }
                else
                    return 100000;  // 5
            }
        }
        else {
            if(value > 2) {
                if(value > 3)
                    return 10000;  // 4
                else
                    return 1000;   // 3
            }
            else {
                if(value > 1)
                    return 100;  // 2
                else {
                    if(value == 1)
                        return 10;  // 1
                    return 1;  // 0
                }
            }
        }
    }
    inline float MulOf10Func(int value) {
        if(value > 4) {
            if(value > 7) {
                if(value > 8)
                    return 1000000000.0;  // 9
                else
                    return 100000000.0;   // 8
            }
            else {
                if(value > 5) {
                    if(value > 6)
                        return 10000000.0;  // 7
                    else
                        return 1000000.0;   // 6
                }
                else
                    return 100000.0;  // 5
            }
        }
        else {
            if(value > 2) {
                if(value > 3)
                    return 10000.0;  // 4
                else
                    return 1000.0;   // 3
            }
            else {
                if(value > 1)
                    return 100.0;  // 2
                else {
                    if(value == 1)
                        return 10.0;  // 1
                    return 1.0;  // 0
                }
            }
        }
    }
    inline float Calculate() {
        if(Exponent < 0)
            Value = ((float)Mantissa) * DivOf10[-Exponent];
        else
            Value = ((float)Mantissa) * MulOf10[Exponent];
        return Value;
    }
    inline float CalculateFunc() {
        if(Exponent < 0)
            Value = ((float)Mantissa) * DivOf10Func(-Exponent);
        else
            Value = ((float)Mantissa) * MulOf10Func(Exponent);
        return Value;
    }
    inline float Calculate(INT64 mantissa, INT32 exponent) {
        if(Exponent < 0)
            return ((float)mantissa) * DivOf10[-exponent];
        return ((float)mantissa) * MulOf10[exponent];
    }
    inline INT64 CalculatePositiveInteger() {
        int mul = PowOf10[this->Exponent];
        return this->Mantissa * mul;
    }
    inline bool Less(Decimal *value) {
        return this->Calculate() < value->Calculate();
    }
    inline bool LessOrEqual(Decimal *value) {
        return this->Calculate() <= value->Calculate();
    }
    inline bool Equal(Decimal *value) {
        return this->Calculate() == value->Calculate();
    }
    inline bool Equal(UINT64 mantissa, UINT32 exponent) {
        return this->Calculate() == Calculate(mantissa, exponent);
    }
    inline bool Greater(Decimal *value) {
        return !this->LessOrEqual(value);
    }
    inline bool GreaterOrEqual(Decimal *value) {
        return !this->Less(value);
    }
    inline void Assign(Decimal *value) {
        this->Mantissa = value->Mantissa;
        this->Exponent = value->Exponent;
        this->Value = value->Value;
    }
};

#define FIX_SEPARATOR                   0x01
#define FIX_SEPARATOR_SECOND_BYTE       0x00000100L
#define FIX_SEPARATOR_THIRD_BYTE        0x00010000L
#define FIX_SEPARATOR_FORTH_BYTE        0x01000000L

#define FIX_EQUAL                   0x3d
#define FIX_EQUAL_SECOND_BYTE       0x00003d00L
#define FIX_EQUAL_THIRD_BYTE        0x003d0000L
#define FIX_EQUAL_FORTH_BYTE        0x3d000000L

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

#endif //HFT_ROBOT_FIXTYPES_H
