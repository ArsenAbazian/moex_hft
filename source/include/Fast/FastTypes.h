//
//
// Created by root on 21.08.16.
//

#ifndef HFT_ROBOT_FASTTYPES_H
#define HFT_ROBOT_FASTTYPES_H

#define FAST_STOPBIT_FIRST_BYTE         0x0000000000000080L
#define FAST_STOPBIT_SECOND_BYTE        0x0000000000008000L
#define FAST_STOPBIT_THIRD_BYTE         0x0000000000800000L
#define FAST_STOPBIT_FORTH_BYTE         0x0000000080000000L

#define FAST_STOPBIT_FIFTH_BYTE         0x0000008000000000L
#define FAST_STOPBIT_SIXSTH_BYTE        0x0000800000000000L
#define FAST_STOPBIT_SEVENTH_BYTE       0x0080000000000000L

#include "../Settings.h"
#include "../Lib/AutoAllocatePointerList.h"
#include "../Fix/FixTypes.h"

typedef enum _MDUpdateAction {
    mduaAdd = 0,
    mduaChange = 1,
    mduaDelete = 2
}MDUpdateAction;

typedef enum _MDEntryType {
    mdetBuyQuote = '0',
    mdetSellQuote = '1',
    mdetLastDealInfo = '2',
    mdetIndicesList = '3',
    mdetPriceOpenFirst = '4',
    mdetPriceCloseLast = '5',
    mdetPriceMax = '7',
    mdetPriceMin = '8',
    mdetPriceAve = '9',
    mdetDisbalance = 'A', // A
    mdetTransactionsMagnitude = 'B', //B
    mdetEmptyBook = 'J', // J
    mdetOfferPriceMin = 'N',
    mdetBidPriceMax = 'O',
    mdetAuctionPriceCalculated = 'Q',
    mdetAuctionPriceClose = 'W',
    mdetAuctionMagnitudeClose = 'c',
    mdetMSSTradingDenyNotEnoughMoney = 'e',
    mdetMSSTradeOfferAuctionMagnitudeOpenClose = 'f',
    mdetOLSTradeOfferAuctionOpenClose = 'f',
    mdetMSSTradeBidAuctionMagnitudeOpenClose = 'g',
    mdetOLSTradeBidAuctionOpenClose = 'g',
    mdetSessionOffer = 'i',
    mdetSessionBid = 'j',
    mdetPreTradePeriodPrice = 'h',
    mdetPostTradePeriodPrice = 'k',
    mdetTradePrice2 = 'l',
    mdetTradePrice = 'm',
    mdetPriceOpenOfficial = 'o',
    mdetPriceCurrentOfficial = 'p',
    mdetLegitimQuote = 'q',
    mdetPriceCloseOfficial = 'r',
    mdetOfferTotal = 'v',
    mdetBidTotal = 'w',
    mdetAuctionPriceBigPackets = 's',
    mdetAuctionMagnitudeBigPackets = 'x',
    mdetCumulativeCouponDebit = 'y',
    mdetDuration = 'u',
    mdetAllDeals = 'z'
}MDEntryType;

typedef enum _SecurityStatus {
    ssUndefined = 0,
    ssNoTrading = 18,
    ssOpening = 118,
    ssTradingClosed = 18,
    ssClosing = 130,
    ssTradingPaused = 2,
    ssNormalTrading = 17,
    ssClosingAuction = 102,
    ssBigPacketAuction = 106,
    ssDiscreteAuction = 107,
    ssOpeningAuction = 119,
    ssTradingByClosingAuctionPrice = 120
}SecurityStatus;

#pragma region Defines_GeneratedCode
#define PRESENCE_MAP_INDEX0  0x0000000000000040L
#define PRESENCE_MAP_INDEX1  0x0000000000000020L
#define PRESENCE_MAP_INDEX2  0x0000000000000010L
#define PRESENCE_MAP_INDEX3  0x0000000000000008L
#define PRESENCE_MAP_INDEX4  0x0000000000000004L
#define PRESENCE_MAP_INDEX5  0x0000000000000002L
#define PRESENCE_MAP_INDEX6  0x0000000000000001L
#define PRESENCE_MAP_INDEX7  0x0000000000004000L
#define PRESENCE_MAP_INDEX8  0x0000000000002000L
#define PRESENCE_MAP_INDEX9  0x0000000000001000L
#define PRESENCE_MAP_INDEX10 0x0000000000000800L
#define PRESENCE_MAP_INDEX11 0x0000000000000400L
#define PRESENCE_MAP_INDEX12 0x0000000000000200L
#define PRESENCE_MAP_INDEX13 0x0000000000000100L
#define PRESENCE_MAP_INDEX14 0x0000000000400000L
#define PRESENCE_MAP_INDEX15 0x0000000000200000L
#define PRESENCE_MAP_INDEX16 0x0000000000100000L
#define PRESENCE_MAP_INDEX17 0x0000000000080000L
#define PRESENCE_MAP_INDEX18 0x0000000000040000L
#define PRESENCE_MAP_INDEX19 0x0000000000020000L
#define PRESENCE_MAP_INDEX20 0x0000000000010000L
#define PRESENCE_MAP_INDEX21 0x0000000040000000L
#define PRESENCE_MAP_INDEX22 0x0000000020000000L
#define PRESENCE_MAP_INDEX23 0x0000000010000000L
#define PRESENCE_MAP_INDEX24 0x0000000008000000L
#define PRESENCE_MAP_INDEX25 0x0000000004000000L
#define PRESENCE_MAP_INDEX26 0x0000000002000000L
#define PRESENCE_MAP_INDEX27 0x0000000001000000L
#define PRESENCE_MAP_INDEX28 0x0000004000000000L
#define PRESENCE_MAP_INDEX29 0x0000002000000000L
#define PRESENCE_MAP_INDEX30 0x0000001000000000L
#define PRESENCE_MAP_INDEX31 0x0000000800000000L
#define PRESENCE_MAP_INDEX32 0x0000000400000000L
#define PRESENCE_MAP_INDEX33 0x0000000200000000L
#define PRESENCE_MAP_INDEX34 0x0000000100000000L
#define PRESENCE_MAP_INDEX35 0x0000400000000000L
#define PRESENCE_MAP_INDEX36 0x0000200000000000L
#define PRESENCE_MAP_INDEX37 0x0000100000000000L
#define PRESENCE_MAP_INDEX38 0x0000080000000000L
#define PRESENCE_MAP_INDEX39 0x0000040000000000L
#define PRESENCE_MAP_INDEX40 0x0000020000000000L
#define PRESENCE_MAP_INDEX41 0x0000010000000000L
#define PRESENCE_MAP_INDEX42 0x0040000000000000L
#define PRESENCE_MAP_INDEX43 0x0020000000000000L
#define PRESENCE_MAP_INDEX44 0x0010000000000000L
#define PRESENCE_MAP_INDEX45 0x0008000000000000L
#define PRESENCE_MAP_INDEX46 0x0004000000000000L
#define PRESENCE_MAP_INDEX47 0x0002000000000000L
#define PRESENCE_MAP_INDEX48 0x0001000000000000L
#define PRESENCE_MAP_INDEX49 0x4000000000000000L
#define PRESENCE_MAP_INDEX50 0x2000000000000000L
#define PRESENCE_MAP_INDEX51 0x1000000000000000L
#define PRESENCE_MAP_INDEX52 0x0800000000000000L
#define PRESENCE_MAP_INDEX53 0x0400000000000000L
#define PRESENCE_MAP_INDEX54 0x0200000000000000L
#define PRESENCE_MAP_INDEX55 0x0100000000000000L
#define NULL_MAP_INDEX0      0x0000000000000001L
#define NULL_MAP_INDEX1      0x0000000000000002L
#define NULL_MAP_INDEX2      0x0000000000000004L
#define NULL_MAP_INDEX3      0x0000000000000008L
#define NULL_MAP_INDEX4      0x0000000000000010L
#define NULL_MAP_INDEX5      0x0000000000000020L
#define NULL_MAP_INDEX6      0x0000000000000040L
#define NULL_MAP_INDEX7      0x0000000000000080L
#define NULL_MAP_INDEX8      0x0000000000000100L
#define NULL_MAP_INDEX9      0x0000000000000200L
#define NULL_MAP_INDEX10     0x0000000000000400L
#define NULL_MAP_INDEX11     0x0000000000000800L
#define NULL_MAP_INDEX12     0x0000000000001000L
#define NULL_MAP_INDEX13     0x0000000000002000L
#define NULL_MAP_INDEX14     0x0000000000004000L
#define NULL_MAP_INDEX15     0x0000000000008000L
#define NULL_MAP_INDEX16     0x0000000000010000L
#define NULL_MAP_INDEX17     0x0000000000020000L
#define NULL_MAP_INDEX18     0x0000000000040000L
#define NULL_MAP_INDEX19     0x0000000000080000L
#define NULL_MAP_INDEX20     0x0000000000100000L
#define NULL_MAP_INDEX21     0x0000000000200000L
#define NULL_MAP_INDEX22     0x0000000000400000L
#define NULL_MAP_INDEX23     0x0000000000800000L
#define NULL_MAP_INDEX24     0x0000000001000000L
#define NULL_MAP_INDEX25     0x0000000002000000L
#define NULL_MAP_INDEX26     0x0000000004000000L
#define NULL_MAP_INDEX27     0x0000000008000000L
#define NULL_MAP_INDEX28     0x0000000010000000L
#define NULL_MAP_INDEX29     0x0000000020000000L
#define NULL_MAP_INDEX30     0x0000000040000000L
#define NULL_MAP_INDEX31     0x0000000080000000L
#define NULL_MAP_INDEX32     0x0000000100000000L
#define NULL_MAP_INDEX33     0x0000000200000000L
#define NULL_MAP_INDEX34     0x0000000400000000L
#define NULL_MAP_INDEX35     0x0000000800000000L
#define NULL_MAP_INDEX36     0x0000001000000000L
#define NULL_MAP_INDEX37     0x0000002000000000L
#define NULL_MAP_INDEX38     0x0000004000000000L
#define NULL_MAP_INDEX39     0x0000008000000000L
#define NULL_MAP_INDEX40     0x0000010000000000L
#define NULL_MAP_INDEX41     0x0000020000000000L
#define NULL_MAP_INDEX42     0x0000040000000000L
#define NULL_MAP_INDEX43     0x0000080000000000L
#define NULL_MAP_INDEX44     0x0000100000000000L
#define NULL_MAP_INDEX45     0x0000200000000000L
#define NULL_MAP_INDEX46     0x0000400000000000L
#define NULL_MAP_INDEX47     0x0000800000000000L
#define NULL_MAP_INDEX48     0x0001000000000000L
#define NULL_MAP_INDEX49     0x0002000000000000L
#define NULL_MAP_INDEX50     0x0004000000000000L
#define NULL_MAP_INDEX51     0x0008000000000000L
#define NULL_MAP_INDEX52     0x0010000000000000L
#define NULL_MAP_INDEX53     0x0020000000000000L
#define NULL_MAP_INDEX54     0x0040000000000000L
#define NULL_MAP_INDEX55     0x0080000000000000L
#define NULL_MAP_INDEX56     0x0100000000000000L
#define NULL_MAP_INDEX57     0x0200000000000000L
#define NULL_MAP_INDEX58     0x0400000000000000L
#define NULL_MAP_INDEX59     0x0800000000000000L
#define NULL_MAP_INDEX60     0x1000000000000000L
#define NULL_MAP_INDEX61     0x2000000000000000L
#define NULL_MAP_INDEX62     0x4000000000000000L
#define NULL_MAP_INDEX63     0x8000000000000000L
#pragma endregion

#pragma region Asts_Message_Info_Structures_Definition_GeneratedCode
class AstsSnapshotInfo {
public:
	UINT64				PresenceMap;
	UINT64				NullMap;
	int				TemplateId;
	INT32				RptSeq;
	UINT32				LastFragment;
	UINT32				RouteFirst;
	UINT32				LastMsgSeqNumProcessed;
	UINT64				SendingTime;
	char				Symbol[32];
	int					SymbolLength;
	char				TradingSessionID[32];
	int					TradingSessionIDLength;
	AstsSnapshotInfo() {
		memset(this, 0, sizeof(AstsSnapshotInfo));
	}
};

class AstsLogonInfo;
class AstsLogoutInfo;
class AstsGenericItemInfo;
class AstsGenericInfo;
class AstsOLSFONDItemInfo;
class AstsOLSFONDInfo;
class AstsOLSCURRItemInfo;
class AstsOLSCURRInfo;
class AstsTLSFONDItemInfo;
class AstsTLSFONDInfo;
class AstsTLSCURRItemInfo;
class AstsTLSCURRInfo;
class AstsSecurityDefinitionGroupInstrAttribItemInfo;
class AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;
class AstsSecurityDefinitionMarketSegmentGrpItemInfo;
class AstsSecurityDefinitionInfo;
class AstsSecurityStatusInfo;
class AstsTradingSessionStatusInfo;
class AstsHeartbeatInfo;
class AstsIncrementalGenericInfo;
class AstsIncrementalMSRFONDInfo;
class AstsIncrementalMSRCURRInfo;
class AstsIncrementalOLRFONDInfo;
class AstsIncrementalOLRCURRInfo;
class AstsIncrementalTLRFONDInfo;
class AstsIncrementalTLRCURRInfo;

class AstsLogonInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsLogonInfo>							*Pointer;
	AutoAllocatePointerList<AstsLogonInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = A
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	char							TargetCompID[32];			// id=56  
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							HeartBtInt;			// id=108  
	char							Username[16];			// id=553  presence=optional  
	char							Password[16];			// id=554  presence=optional  
	char							DefaultApplVerID[16];			// id=1137  
	int								MessageTypeLength;			// id=35    constant has constant value = A
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TargetCompIDLength;			// id=56  
	int								UsernameLength;			// id=553  presence=optional  
	int								PasswordLength;			// id=554  presence=optional  
	int								DefaultApplVerIDLength;			// id=1137  

	AstsLogonInfo() {
		memset(this, 0, sizeof(AstsLogonInfo));
	}
	~AstsLogonInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsLogoutInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsLogoutInfo>							*Pointer;
	AutoAllocatePointerList<AstsLogoutInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = 5
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	char							TargetCompID[32];			// id=56  
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							Text[512];			// id=58  presence=optional  
	int								MessageTypeLength;			// id=35    constant has constant value = 5
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TargetCompIDLength;			// id=56  
	int								TextLength;			// id=58  presence=optional  

	AstsLogoutInfo() {
		memset(this, 0, sizeof(AstsLogoutInfo));
	}
	~AstsLogoutInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsGenericItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsGenericItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsGenericItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  presence=optional  fixed_size=1  
	char							MDEntryID[16];			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT32							MDEntryTime;			// id=273  presence=optional  
	UINT32							OrigTime;			// id=9412  presence=optional  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	Decimal							MDEntrySize;			// id=271  presence=optional  
	char							QuoteCondition[16];			// id=276  presence=optional  
	char							TradeCondition[16];			// id=277  presence=optional  
	char							OpenCloseSettlFlag[4];			// id=286  presence=optional  
	char							OrdType[4];			// id=40  presence=optional  
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	UINT32							StartTime;			// id=9820  presence=optional  
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	Decimal							BidMarketSize;			// id=5292  presence=optional  
	Decimal							AskMarketSize;			// id=5293  presence=optional  
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	Decimal							TradeValue;			// id=6143  presence=optional  
	Decimal							Yield;			// id=236  presence=optional  
	Decimal							TotalVolume;			// id=5791  presence=optional  
	INT32							OfferNbOr;			// id=9168  presence=optional  
	INT32							BidNbOr;			// id=9169  presence=optional  
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	UINT32							SettlDate;			// id=64  presence=optional  
	char							SettleType[16];			// id=5459  presence=optional  
	INT32							SumQtyOfBest;			// id=10503  presence=optional  
	char							OrderSide[4];			// id=10504  presence=optional  
	char							OrderStatus[4];			// id=10505  presence=optional  fixed_size=1  
	Decimal							MinCurrPx;			// id=10509  presence=optional  
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional  
	UINT32							VolumeIndicator;			// id=7017  presence=optional  
	Decimal							Price;			// id=44  presence=optional  
	INT32							PriceType;			// id=423  presence=optional  
	Decimal							NominalValue;			// id=9280  presence=optional  
	Decimal							RepoToPx;			// id=5677  presence=optional  
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	char							CXFlag[4];			// id=5154  presence=optional  
	char							TradingSessionSubID[4];			// id=625  presence=optional  
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1  
	INT32							RptSeq;			// id=83  presence=optional  
	char							Symbol[16];			// id=55  presence=optional  
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int								MDEntryTypeLength;			// id=269  presence=optional  fixed_size=1  
	int								MDEntryIDLength;			// id=278  presence=optional  
	int								QuoteConditionLength;			// id=276  presence=optional  
	int								TradeConditionLength;			// id=277  presence=optional  
	int								OpenCloseSettlFlagLength;			// id=286  presence=optional  
	int								OrdTypeLength;			// id=40  presence=optional  
	int								SettleTypeLength;			// id=5459  presence=optional  
	int								OrderSideLength;			// id=10504  presence=optional  
	int								OrderStatusLength;			// id=10505  presence=optional  fixed_size=1  
	int								CXFlagLength;			// id=5154  presence=optional  
	int								TradingSessionSubIDLength;			// id=625  presence=optional  
	int								SymbolLength;			// id=55  presence=optional  
	int								TradingSessionIDLength;			// id=336  presence=optional  

	AstsGenericItemInfo() {
		memset(this, 0, sizeof(AstsGenericItemInfo));
	}
	~AstsGenericItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsGenericInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsGenericInfo>							*Pointer;
	AutoAllocatePointerList<AstsGenericInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							TradingSessionID[16];			// id=336  presence=optional  
	char							Symbol[16];			// id=55  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	AstsGenericItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TradingSessionIDLength;			// id=336  presence=optional  
	int								SymbolLength;			// id=55  
	int								GroupMDEntriesCount;

	AstsGenericInfo() {
		memset(this, 0, sizeof(AstsGenericInfo));
	}
	~AstsGenericInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsOLSFONDItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSFONDItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  presence=optional  fixed_size=1    copy
	char							MDEntryID[16];			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	Decimal							Yield;			// id=236  presence=optional    copy
	char							OrderStatus[4];			// id=10505  presence=optional  fixed_size=1    copy
	char							OrdType[4];			// id=40  presence=optional    copy
	Decimal							TotalVolume;			// id=5791  presence=optional    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1  
	char							Symbol[16];			// id=55  presence=optional    copy
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional    copy
	int								MDEntryTypeLength;			// id=269  presence=optional  fixed_size=1    copy
	int								MDEntryIDLength;			// id=278  presence=optional  
	int								OrderStatusLength;			// id=10505  presence=optional  fixed_size=1    copy
	int								OrdTypeLength;			// id=40  presence=optional    copy
	int								TradingSessionSubIDLength;			// id=625  presence=optional    copy
	int								SymbolLength;			// id=55  presence=optional    copy
	int								TradingSessionIDLength;			// id=336  presence=optional    copy

	AstsOLSFONDItemInfo() {
		memset(this, 0, sizeof(AstsOLSFONDItemInfo));
	}
	~AstsOLSFONDItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsOLSFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	char							Symbol[16];			// id=55  
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	AstsOLSFONDItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TradingSessionIDLength;			// id=336  presence=optional  
	int								SymbolLength;			// id=55  
	int								GroupMDEntriesCount;

	AstsOLSFONDInfo() {
		memset(this, 0, sizeof(AstsOLSFONDInfo));
	}
	~AstsOLSFONDInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsOLSCURRItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSCURRItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  presence=optional  fixed_size=1    copy
	char							MDEntryID[16];			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	char							OrderStatus[4];			// id=10505  presence=optional  fixed_size=1    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1    copy
	char							Symbol[16];			// id=55  presence=optional    copy
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional    copy
	int								MDEntryTypeLength;			// id=269  presence=optional  fixed_size=1    copy
	int								MDEntryIDLength;			// id=278  presence=optional  
	int								OrderStatusLength;			// id=10505  presence=optional  fixed_size=1    copy
	int								TradingSessionSubIDLength;			// id=625  presence=optional    copy
	int								SymbolLength;			// id=55  presence=optional    copy
	int								TradingSessionIDLength;			// id=336  presence=optional    copy

	AstsOLSCURRItemInfo() {
		memset(this, 0, sizeof(AstsOLSCURRItemInfo));
	}
	~AstsOLSCURRItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsOLSCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	char							Symbol[16];			// id=55  
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	AstsOLSCURRItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TradingSessionIDLength;			// id=336  presence=optional  
	int								SymbolLength;			// id=55  
	int								GroupMDEntriesCount;

	AstsOLSCURRInfo() {
		memset(this, 0, sizeof(AstsOLSCURRInfo));
	}
	~AstsOLSCURRInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsTLSFONDItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSFONDItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  fixed_size=1  
	char							MDEntryID[16];			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	char							OrderSide[4];			// id=10504  presence=optional    copy
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional    copy
	Decimal							TradeValue;			// id=6143  presence=optional    copy
	Decimal							Yield;			// id=236  presence=optional    copy
	UINT32							SettlDate;			// id=64  presence=optional    copy
	char							SettleType[16];			// id=5459  presence=optional    copy
	Decimal							Price;			// id=44  presence=optional    copy
	INT32							PriceType;			// id=423  presence=optional    copy
	Decimal							RepoToPx;			// id=5677  presence=optional    copy
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	char							RefOrderID[16];			// id=1080  presence=optional    copy
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1  
	char							Symbol[16];			// id=55  presence=optional  
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int								MDEntryTypeLength;			// id=269  fixed_size=1  
	int								MDEntryIDLength;			// id=278  presence=optional  
	int								OrderSideLength;			// id=10504  presence=optional    copy
	int								SettleTypeLength;			// id=5459  presence=optional    copy
	int								TradingSessionSubIDLength;			// id=625  presence=optional    copy
	int								RefOrderIDLength;			// id=1080  presence=optional    copy
	int								SymbolLength;			// id=55  presence=optional  
	int								TradingSessionIDLength;			// id=336  presence=optional  

	AstsTLSFONDItemInfo() {
		memset(this, 0, sizeof(AstsTLSFONDItemInfo));
	}
	~AstsTLSFONDItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsTLSFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	char							Symbol[16];			// id=55  
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	AstsTLSFONDItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TradingSessionIDLength;			// id=336  presence=optional  
	int								SymbolLength;			// id=55  
	int								GroupMDEntriesCount;

	AstsTLSFONDInfo() {
		memset(this, 0, sizeof(AstsTLSFONDInfo));
	}
	~AstsTLSFONDInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsTLSCURRItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSCURRItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  fixed_size=1  
	char							MDEntryID[16];			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	char							OrderSide[4];			// id=10504  presence=optional    copy
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	Decimal							TradeValue;			// id=6143  presence=optional    copy
	UINT32							SettlDate;			// id=64  presence=optional    copy
	char							SettleType[16];			// id=5459  presence=optional    copy
	Decimal							Price;			// id=44  presence=optional    copy
	INT32							PriceType;			// id=423  presence=optional    copy
	Decimal							RepoToPx;			// id=5677  presence=optional    copy
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	char							RefOrderID[16];			// id=1080  presence=optional    copy
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1  
	char							Symbol[16];			// id=55  presence=optional  
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int								MDEntryTypeLength;			// id=269  fixed_size=1  
	int								MDEntryIDLength;			// id=278  presence=optional  
	int								OrderSideLength;			// id=10504  presence=optional    copy
	int								SettleTypeLength;			// id=5459  presence=optional    copy
	int								TradingSessionSubIDLength;			// id=625  presence=optional    copy
	int								RefOrderIDLength;			// id=1080  presence=optional    copy
	int								SymbolLength;			// id=55  presence=optional  
	int								TradingSessionIDLength;			// id=336  presence=optional  

	AstsTLSCURRItemInfo() {
		memset(this, 0, sizeof(AstsTLSCURRItemInfo));
	}
	~AstsTLSCURRItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsTLSCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	char							Symbol[16];			// id=55  
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	AstsTLSCURRItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TradingSessionIDLength;			// id=336  presence=optional  
	int								SymbolLength;			// id=55  
	int								GroupMDEntriesCount;

	AstsTLSCURRInfo() {
		memset(this, 0, sizeof(AstsTLSCURRInfo));
	}
	~AstsTLSCURRInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsSecurityDefinitionGroupInstrAttribItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionGroupInstrAttribItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>							*Allocator;
	bool							Used;
	INT32							InstrAttribType;			// id=871  
	unsigned char							InstrAttribValue[128];			// id=872  presence=optional  
	int								InstrAttribValueLength;			// id=872  presence=optional  

	AstsSecurityDefinitionGroupInstrAttribItemInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionGroupInstrAttribItemInfo));
	}
	~AstsSecurityDefinitionGroupInstrAttribItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Allocator;
	bool							Used;
	char							TradingSessionID[16];			// id=336  
	char							TradingSessionSubID[4];			// id=625  presence=optional  
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	INT32							OrderNote;			// id=9680  presence=optional  
	int								TradingSessionIDLength;			// id=336  
	int								TradingSessionSubIDLength;			// id=625  presence=optional  

	AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo));
	}
	~AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsSecurityDefinitionMarketSegmentGrpItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionMarketSegmentGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>							*Allocator;
	bool							Used;
	Decimal							RoundLot;			// id=561  presence=optional  
	AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* TradingSessionRulesGrp[256];			// presence=optional  
	int								TradingSessionRulesGrpCount;			// presence=optional  

	AstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionMarketSegmentGrpItemInfo));
	}
	~AstsSecurityDefinitionMarketSegmentGrpItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->ReleaseUnused();
	}
};

class AstsSecurityDefinitionInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = d
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34    increment
	UINT64							SendingTime;			// id=52  
	char							MessageEncoding[16];			// id=347    default
	INT32							TotNumReports;			// id=911  presence=optional  
	char							Symbol[16];			// id=55  presence=optional  
	unsigned char							SecurityID[128];			// id=48  presence=optional  
	unsigned char							SecurityIDSource[128];			// id=22  presence=optional  
	INT32							Product;			// id=460  presence=optional  
	unsigned char							CFICode[128];			// id=461  presence=optional  
	unsigned char							SecurityType[128];			// id=167  presence=optional  
	UINT32							MaturityDate;			// id=541  presence=optional  
	UINT32							SettlDate;			// id=64  presence=optional  
	char							SettleType[16];			// id=5459  presence=optional  
	Decimal							OrigIssueAmt;			// id=5850  presence=optional  
	UINT32							CouponPaymentDate;			// id=224  presence=optional  
	Decimal							CouponRate;			// id=223  presence=optional  
	UINT32							SettlFixingDate;			// id=9119  presence=optional  
	Decimal							DividendNetPx;			// id=9982  presence=optional  
	unsigned char							SecurityDesc[128];			// id=107  presence=optional  
	unsigned char							EncodedSecurityDesc[128];			// id=351  presence=optional  
	unsigned char							QuoteText[128];			// id=9696  presence=optional  
	AstsSecurityDefinitionGroupInstrAttribItemInfo* GroupInstrAttrib[256];			// presence=optional  
	char							Currency[4];			// id=15  presence=optional  
	AstsSecurityDefinitionMarketSegmentGrpItemInfo* MarketSegmentGrp[256];			// presence=optional  
	char							SettlCurrency[16];			// id=120  presence=optional  
	INT32							PriceType;			// id=423  presence=optional  
	char							StateSecurityID[16];			// id=5217  presence=optional  
	unsigned char							EncodedShortSecurityDesc[128];			// id=5383  presence=optional  
	unsigned char							MarketCode[128];			// id=5385  presence=optional  
	Decimal							MinPriceIncrement;			// id=969  presence=optional  
	Decimal							MktShareLimit;			// id=5387  presence=optional  
	Decimal							MktShareThreshold;			// id=5388  presence=optional  
	Decimal							MaxOrdersVolume;			// id=5389  presence=optional  
	Decimal							PriceMvmLimit;			// id=5470  presence=optional  
	Decimal							FaceValue;			// id=5508  presence=optional  
	Decimal							BaseSwapPx;			// id=5556  presence=optional  
	Decimal							RepoToPx;			// id=5677  presence=optional  
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	Decimal							NoSharesIssued;			// id=7595  presence=optional  
	Decimal							HighLimit;			// id=9199  presence=optional  
	Decimal							LowLimit;			// id=9200  presence=optional  
	INT32							NumOfDaysToMaturity;			// id=10508  presence=optional  
	int								MessageTypeLength;			// id=35    constant has constant value = d
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								MessageEncodingLength;			// id=347    default
	int								SymbolLength;			// id=55  presence=optional  
	int								SecurityIDLength;			// id=48  presence=optional  
	int								SecurityIDSourceLength;			// id=22  presence=optional  
	int								CFICodeLength;			// id=461  presence=optional  
	int								SecurityTypeLength;			// id=167  presence=optional  
	int								SettleTypeLength;			// id=5459  presence=optional  
	int								SecurityDescLength;			// id=107  presence=optional  
	int								EncodedSecurityDescLength;			// id=351  presence=optional  
	int								QuoteTextLength;			// id=9696  presence=optional  
	int								GroupInstrAttribCount;			// presence=optional  
	int								CurrencyLength;			// id=15  presence=optional  
	int								MarketSegmentGrpCount;			// presence=optional  
	int								SettlCurrencyLength;			// id=120  presence=optional  
	int								StateSecurityIDLength;			// id=5217  presence=optional  
	int								EncodedShortSecurityDescLength;			// id=5383  presence=optional  
	int								MarketCodeLength;			// id=5385  presence=optional  

	AstsSecurityDefinitionInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionInfo));
	}
	~AstsSecurityDefinitionInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->Clear();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->ReleaseUnused();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->ReleaseUnused();
	}
};

class AstsSecurityStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityStatusInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = f
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							Symbol[16];			// id=55  
	char							TradingSessionID[16];			// id=336  presence=optional  
	char							TradingSessionSubID[4];			// id=625  presence=optional  
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	int								MessageTypeLength;			// id=35    constant has constant value = f
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								SymbolLength;			// id=55  
	int								TradingSessionIDLength;			// id=336  presence=optional  
	int								TradingSessionSubIDLength;			// id=625  presence=optional  

	AstsSecurityStatusInfo() {
		memset(this, 0, sizeof(AstsSecurityStatusInfo));
	}
	~AstsSecurityStatusInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsTradingSessionStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<AstsTradingSessionStatusInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = h
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							TradSesStatus;			// id=340  
	char							Text[512];			// id=58  presence=optional  
	char							TradingSessionID[16];			// id=336  
	int								MessageTypeLength;			// id=35    constant has constant value = h
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TextLength;			// id=58  presence=optional  
	int								TradingSessionIDLength;			// id=336  

	AstsTradingSessionStatusInfo() {
		memset(this, 0, sizeof(AstsTradingSessionStatusInfo));
	}
	~AstsTradingSessionStatusInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsHeartbeatInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<AstsHeartbeatInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = 0
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int								MessageTypeLength;			// id=35    constant has constant value = 0
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX

	AstsHeartbeatInfo() {
		memset(this, 0, sizeof(AstsHeartbeatInfo));
	}
	~AstsHeartbeatInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class AstsIncrementalGenericInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalGenericInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalGenericInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	AstsGenericItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalGenericInfo() {
		memset(this, 0, sizeof(AstsIncrementalGenericInfo));
	}
	~AstsIncrementalGenericInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalMSRFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalMSRFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							LastUpdateTime;			// id=779  presence=optional  
	AstsGenericItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalMSRFONDInfo() {
		memset(this, 0, sizeof(AstsIncrementalMSRFONDInfo));
	}
	~AstsIncrementalMSRFONDInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalMSRCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalMSRCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							LastUpdateTime;			// id=779  presence=optional  
	AstsGenericItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalMSRCURRInfo() {
		memset(this, 0, sizeof(AstsIncrementalMSRCURRInfo));
	}
	~AstsIncrementalMSRCURRInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalOLRFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalOLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	AstsOLSFONDItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalOLRFONDInfo() {
		memset(this, 0, sizeof(AstsIncrementalOLRFONDInfo));
	}
	~AstsIncrementalOLRFONDInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalOLRCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalOLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	AstsOLSCURRItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalOLRCURRInfo() {
		memset(this, 0, sizeof(AstsIncrementalOLRCURRInfo));
	}
	~AstsIncrementalOLRCURRInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalTLRFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalTLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	AstsTLSFONDItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalTLRFONDInfo() {
		memset(this, 0, sizeof(AstsIncrementalTLRFONDInfo));
	}
	~AstsIncrementalTLRFONDInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalTLRCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalTLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	AstsTLSCURRItemInfo* GroupMDEntries[256];
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								GroupMDEntriesCount;

	AstsIncrementalTLRCURRInfo() {
		memset(this, 0, sizeof(AstsIncrementalTLRCURRInfo));
	}
	~AstsIncrementalTLRCURRInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsObjectsAllocationInfo {
	AutoAllocatePointerList<AstsLogonInfo>				*m_astsLogon;
	AutoAllocatePointerList<AstsLogoutInfo>				*m_astsLogout;
	AutoAllocatePointerList<AstsGenericItemInfo>				*m_astsGenericItems;
	AutoAllocatePointerList<AstsGenericInfo>				*m_astsGeneric;
	AutoAllocatePointerList<AstsOLSFONDItemInfo>				*m_astsOLSFONDItems;
	AutoAllocatePointerList<AstsOLSFONDInfo>				*m_astsOLSFOND;
	AutoAllocatePointerList<AstsOLSCURRItemInfo>				*m_astsOLSCURRItems;
	AutoAllocatePointerList<AstsOLSCURRInfo>				*m_astsOLSCURR;
	AutoAllocatePointerList<AstsTLSFONDItemInfo>				*m_astsTLSFONDItems;
	AutoAllocatePointerList<AstsTLSFONDInfo>				*m_astsTLSFOND;
	AutoAllocatePointerList<AstsTLSCURRItemInfo>				*m_astsTLSCURRItems;
	AutoAllocatePointerList<AstsTLSCURRInfo>				*m_astsTLSCURR;
	AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>				*m_astsSecurityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>				*m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>				*m_astsSecurityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<AstsSecurityDefinitionInfo>				*m_astsSecurityDefinition;
	AutoAllocatePointerList<AstsSecurityStatusInfo>				*m_astsSecurityStatus;
	AutoAllocatePointerList<AstsTradingSessionStatusInfo>				*m_astsTradingSessionStatus;
	AutoAllocatePointerList<AstsHeartbeatInfo>				*m_astsHeartbeat;
	AutoAllocatePointerList<AstsIncrementalGenericInfo>				*m_astsIncrementalGeneric;
	AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>				*m_astsIncrementalMSRFOND;
	AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>				*m_astsIncrementalMSRCURR;
	AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>				*m_astsIncrementalOLRFOND;
	AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>				*m_astsIncrementalOLRCURR;
	AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>				*m_astsIncrementalTLRFOND;
	AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>				*m_astsIncrementalTLRCURR;
public:
	 static AstsObjectsAllocationInfo *Default;
	AstsObjectsAllocationInfo(int count) {
		this->m_astsLogon = new AutoAllocatePointerList<AstsLogonInfo>(count, count, "AstsLogonInfo");
		this->m_astsLogout = new AutoAllocatePointerList<AstsLogoutInfo>(count, count, "AstsLogoutInfo");
		this->m_astsGenericItems = new AutoAllocatePointerList<AstsGenericItemInfo>(count, count, "AstsGenericItemInfo");
		this->m_astsGeneric = new AutoAllocatePointerList<AstsGenericInfo>(count, count, "AstsGenericInfo");
		this->m_astsOLSFONDItems = new AutoAllocatePointerList<AstsOLSFONDItemInfo>(count, count, "AstsOLSFONDItemInfo");
		this->m_astsOLSFOND = new AutoAllocatePointerList<AstsOLSFONDInfo>(count, count, "AstsOLSFONDInfo");
		this->m_astsOLSCURRItems = new AutoAllocatePointerList<AstsOLSCURRItemInfo>(count, count, "AstsOLSCURRItemInfo");
		this->m_astsOLSCURR = new AutoAllocatePointerList<AstsOLSCURRInfo>(count, count, "AstsOLSCURRInfo");
		this->m_astsTLSFONDItems = new AutoAllocatePointerList<AstsTLSFONDItemInfo>(count, count, "AstsTLSFONDItemInfo");
		this->m_astsTLSFOND = new AutoAllocatePointerList<AstsTLSFONDInfo>(count, count, "AstsTLSFONDInfo");
		this->m_astsTLSCURRItems = new AutoAllocatePointerList<AstsTLSCURRItemInfo>(count, count, "AstsTLSCURRItemInfo");
		this->m_astsTLSCURR = new AutoAllocatePointerList<AstsTLSCURRInfo>(count, count, "AstsTLSCURRInfo");
		this->m_astsSecurityDefinitionGroupInstrAttribItems = new AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>(count, count, "AstsSecurityDefinitionGroupInstrAttribItemInfo");
		this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(count, count, "AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo");
		this->m_astsSecurityDefinitionMarketSegmentGrpItems = new AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>(count, count, "AstsSecurityDefinitionMarketSegmentGrpItemInfo");
		this->m_astsSecurityDefinition = new AutoAllocatePointerList<AstsSecurityDefinitionInfo>(count, count, "AstsSecurityDefinitionInfo");
		this->m_astsSecurityStatus = new AutoAllocatePointerList<AstsSecurityStatusInfo>(count, count, "AstsSecurityStatusInfo");
		this->m_astsTradingSessionStatus = new AutoAllocatePointerList<AstsTradingSessionStatusInfo>(count, count, "AstsTradingSessionStatusInfo");
		this->m_astsHeartbeat = new AutoAllocatePointerList<AstsHeartbeatInfo>(count, count, "AstsHeartbeatInfo");
		this->m_astsIncrementalGeneric = new AutoAllocatePointerList<AstsIncrementalGenericInfo>(count, count, "AstsIncrementalGenericInfo");
		this->m_astsIncrementalMSRFOND = new AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>(count, count, "AstsIncrementalMSRFONDInfo");
		this->m_astsIncrementalMSRCURR = new AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>(count, count, "AstsIncrementalMSRCURRInfo");
		this->m_astsIncrementalOLRFOND = new AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>(count, count, "AstsIncrementalOLRFONDInfo");
		this->m_astsIncrementalOLRCURR = new AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>(count, count, "AstsIncrementalOLRCURRInfo");
		this->m_astsIncrementalTLRFOND = new AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>(count, count, "AstsIncrementalTLRFONDInfo");
		this->m_astsIncrementalTLRCURR = new AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>(count, count, "AstsIncrementalTLRCURRInfo");
	}
	inline void AllocateLogonInfoPool(int count, int addCount) {
		this->m_astsLogon->Append(count);
		this->m_astsLogon->AddCount(addCount);
	}
	inline void AllocateLogoutInfoPool(int count, int addCount) {
		this->m_astsLogout->Append(count);
		this->m_astsLogout->AddCount(addCount);
	}
	inline void AllocateGenericItemInfoPool(int count, int addCount) {
		this->m_astsGenericItems->Append(count);
		this->m_astsGenericItems->AddCount(addCount);
	}
	inline void AllocateGenericInfoPool(int count, int addCount) {
		this->m_astsGeneric->Append(count);
		this->m_astsGeneric->AddCount(addCount);
	}
	inline void AllocateOLSFONDItemInfoPool(int count, int addCount) {
		this->m_astsOLSFONDItems->Append(count);
		this->m_astsOLSFONDItems->AddCount(addCount);
	}
	inline void AllocateOLSFONDInfoPool(int count, int addCount) {
		this->m_astsOLSFOND->Append(count);
		this->m_astsOLSFOND->AddCount(addCount);
	}
	inline void AllocateOLSCURRItemInfoPool(int count, int addCount) {
		this->m_astsOLSCURRItems->Append(count);
		this->m_astsOLSCURRItems->AddCount(addCount);
	}
	inline void AllocateOLSCURRInfoPool(int count, int addCount) {
		this->m_astsOLSCURR->Append(count);
		this->m_astsOLSCURR->AddCount(addCount);
	}
	inline void AllocateTLSFONDItemInfoPool(int count, int addCount) {
		this->m_astsTLSFONDItems->Append(count);
		this->m_astsTLSFONDItems->AddCount(addCount);
	}
	inline void AllocateTLSFONDInfoPool(int count, int addCount) {
		this->m_astsTLSFOND->Append(count);
		this->m_astsTLSFOND->AddCount(addCount);
	}
	inline void AllocateTLSCURRItemInfoPool(int count, int addCount) {
		this->m_astsTLSCURRItems->Append(count);
		this->m_astsTLSCURRItems->AddCount(addCount);
	}
	inline void AllocateTLSCURRInfoPool(int count, int addCount) {
		this->m_astsTLSCURR->Append(count);
		this->m_astsTLSCURR->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(int count, int addCount) {
		this->m_astsSecurityDefinitionGroupInstrAttribItems->Append(count);
		this->m_astsSecurityDefinitionGroupInstrAttribItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(int count, int addCount) {
		this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Append(count);
		this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(int count, int addCount) {
		this->m_astsSecurityDefinitionMarketSegmentGrpItems->Append(count);
		this->m_astsSecurityDefinitionMarketSegmentGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInfoPool(int count, int addCount) {
		this->m_astsSecurityDefinition->Append(count);
		this->m_astsSecurityDefinition->AddCount(addCount);
	}
	inline void AllocateSecurityStatusInfoPool(int count, int addCount) {
		this->m_astsSecurityStatus->Append(count);
		this->m_astsSecurityStatus->AddCount(addCount);
	}
	inline void AllocateTradingSessionStatusInfoPool(int count, int addCount) {
		this->m_astsTradingSessionStatus->Append(count);
		this->m_astsTradingSessionStatus->AddCount(addCount);
	}
	inline void AllocateHeartbeatInfoPool(int count, int addCount) {
		this->m_astsHeartbeat->Append(count);
		this->m_astsHeartbeat->AddCount(addCount);
	}
	inline void AllocateIncrementalGenericInfoPool(int count, int addCount) {
		this->m_astsIncrementalGeneric->Append(count);
		this->m_astsIncrementalGeneric->AddCount(addCount);
	}
	inline void AllocateIncrementalMSRFONDInfoPool(int count, int addCount) {
		this->m_astsIncrementalMSRFOND->Append(count);
		this->m_astsIncrementalMSRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalMSRCURRInfoPool(int count, int addCount) {
		this->m_astsIncrementalMSRCURR->Append(count);
		this->m_astsIncrementalMSRCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalOLRFONDInfoPool(int count, int addCount) {
		this->m_astsIncrementalOLRFOND->Append(count);
		this->m_astsIncrementalOLRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalOLRCURRInfoPool(int count, int addCount) {
		this->m_astsIncrementalOLRCURR->Append(count);
		this->m_astsIncrementalOLRCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalTLRFONDInfoPool(int count, int addCount) {
		this->m_astsIncrementalTLRFOND->Append(count);
		this->m_astsIncrementalTLRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalTLRCURRInfoPool(int count, int addCount) {
		this->m_astsIncrementalTLRCURR->Append(count);
		this->m_astsIncrementalTLRCURR->AddCount(addCount);
	}
	inline void AllocateLogonInfoPoolTo(int count) {
		count -= this->m_astsLogon->Capacity();
		if(count > 0)
			this->m_astsLogon->Append(count);
	}
	inline void AllocateLogoutInfoPoolTo(int count) {
		count -= this->m_astsLogout->Capacity();
		if(count > 0)
			this->m_astsLogout->Append(count);
	}
	inline void AllocateGenericItemInfoPoolTo(int count) {
		count -= this->m_astsGenericItems->Capacity();
		if(count > 0)
			this->m_astsGenericItems->Append(count);
	}
	inline void AllocateGenericInfoPoolTo(int count) {
		count -= this->m_astsGeneric->Capacity();
		if(count > 0)
			this->m_astsGeneric->Append(count);
	}
	inline void AllocateOLSFONDItemInfoPoolTo(int count) {
		count -= this->m_astsOLSFONDItems->Capacity();
		if(count > 0)
			this->m_astsOLSFONDItems->Append(count);
	}
	inline void AllocateOLSFONDInfoPoolTo(int count) {
		count -= this->m_astsOLSFOND->Capacity();
		if(count > 0)
			this->m_astsOLSFOND->Append(count);
	}
	inline void AllocateOLSCURRItemInfoPoolTo(int count) {
		count -= this->m_astsOLSCURRItems->Capacity();
		if(count > 0)
			this->m_astsOLSCURRItems->Append(count);
	}
	inline void AllocateOLSCURRInfoPoolTo(int count) {
		count -= this->m_astsOLSCURR->Capacity();
		if(count > 0)
			this->m_astsOLSCURR->Append(count);
	}
	inline void AllocateTLSFONDItemInfoPoolTo(int count) {
		count -= this->m_astsTLSFONDItems->Capacity();
		if(count > 0)
			this->m_astsTLSFONDItems->Append(count);
	}
	inline void AllocateTLSFONDInfoPoolTo(int count) {
		count -= this->m_astsTLSFOND->Capacity();
		if(count > 0)
			this->m_astsTLSFOND->Append(count);
	}
	inline void AllocateTLSCURRItemInfoPoolTo(int count) {
		count -= this->m_astsTLSCURRItems->Capacity();
		if(count > 0)
			this->m_astsTLSCURRItems->Append(count);
	}
	inline void AllocateTLSCURRInfoPoolTo(int count) {
		count -= this->m_astsTLSCURR->Capacity();
		if(count > 0)
			this->m_astsTLSCURR->Append(count);
	}
	inline void AllocateSecurityDefinitionGroupInstrAttribItemInfoPoolTo(int count) {
		count -= this->m_astsSecurityDefinitionGroupInstrAttribItems->Capacity();
		if(count > 0)
			this->m_astsSecurityDefinitionGroupInstrAttribItems->Append(count);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPoolTo(int count) {
		count -= this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Capacity();
		if(count > 0)
			this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpItemInfoPoolTo(int count) {
		count -= this->m_astsSecurityDefinitionMarketSegmentGrpItems->Capacity();
		if(count > 0)
			this->m_astsSecurityDefinitionMarketSegmentGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInfoPoolTo(int count) {
		count -= this->m_astsSecurityDefinition->Capacity();
		if(count > 0)
			this->m_astsSecurityDefinition->Append(count);
	}
	inline void AllocateSecurityStatusInfoPoolTo(int count) {
		count -= this->m_astsSecurityStatus->Capacity();
		if(count > 0)
			this->m_astsSecurityStatus->Append(count);
	}
	inline void AllocateTradingSessionStatusInfoPoolTo(int count) {
		count -= this->m_astsTradingSessionStatus->Capacity();
		if(count > 0)
			this->m_astsTradingSessionStatus->Append(count);
	}
	inline void AllocateHeartbeatInfoPoolTo(int count) {
		count -= this->m_astsHeartbeat->Capacity();
		if(count > 0)
			this->m_astsHeartbeat->Append(count);
	}
	inline void AllocateIncrementalGenericInfoPoolTo(int count) {
		count -= this->m_astsIncrementalGeneric->Capacity();
		if(count > 0)
			this->m_astsIncrementalGeneric->Append(count);
	}
	inline void AllocateIncrementalMSRFONDInfoPoolTo(int count) {
		count -= this->m_astsIncrementalMSRFOND->Capacity();
		if(count > 0)
			this->m_astsIncrementalMSRFOND->Append(count);
	}
	inline void AllocateIncrementalMSRCURRInfoPoolTo(int count) {
		count -= this->m_astsIncrementalMSRCURR->Capacity();
		if(count > 0)
			this->m_astsIncrementalMSRCURR->Append(count);
	}
	inline void AllocateIncrementalOLRFONDInfoPoolTo(int count) {
		count -= this->m_astsIncrementalOLRFOND->Capacity();
		if(count > 0)
			this->m_astsIncrementalOLRFOND->Append(count);
	}
	inline void AllocateIncrementalOLRCURRInfoPoolTo(int count) {
		count -= this->m_astsIncrementalOLRCURR->Capacity();
		if(count > 0)
			this->m_astsIncrementalOLRCURR->Append(count);
	}
	inline void AllocateIncrementalTLRFONDInfoPoolTo(int count) {
		count -= this->m_astsIncrementalTLRFOND->Capacity();
		if(count > 0)
			this->m_astsIncrementalTLRFOND->Append(count);
	}
	inline void AllocateIncrementalTLRCURRInfoPoolTo(int count) {
		count -= this->m_astsIncrementalTLRCURR->Capacity();
		if(count > 0)
			this->m_astsIncrementalTLRCURR->Append(count);
	}
	inline AutoAllocatePointerList<AstsLogonInfo>* GetAstsLogonInfoPool() {
		return this->m_astsLogon;
	}
	inline AutoAllocatePointerList<AstsLogoutInfo>* GetAstsLogoutInfoPool() {
		return this->m_astsLogout;
	}
	inline AutoAllocatePointerList<AstsGenericItemInfo>* GetAstsGenericItemInfoPool() {
		return this->m_astsGenericItems;
	}
	inline AutoAllocatePointerList<AstsGenericInfo>* GetAstsGenericInfoPool() {
		return this->m_astsGeneric;
	}
	inline AutoAllocatePointerList<AstsOLSFONDItemInfo>* GetAstsOLSFONDItemInfoPool() {
		return this->m_astsOLSFONDItems;
	}
	inline AutoAllocatePointerList<AstsOLSFONDInfo>* GetAstsOLSFONDInfoPool() {
		return this->m_astsOLSFOND;
	}
	inline AutoAllocatePointerList<AstsOLSCURRItemInfo>* GetAstsOLSCURRItemInfoPool() {
		return this->m_astsOLSCURRItems;
	}
	inline AutoAllocatePointerList<AstsOLSCURRInfo>* GetAstsOLSCURRInfoPool() {
		return this->m_astsOLSCURR;
	}
	inline AutoAllocatePointerList<AstsTLSFONDItemInfo>* GetAstsTLSFONDItemInfoPool() {
		return this->m_astsTLSFONDItems;
	}
	inline AutoAllocatePointerList<AstsTLSFONDInfo>* GetAstsTLSFONDInfoPool() {
		return this->m_astsTLSFOND;
	}
	inline AutoAllocatePointerList<AstsTLSCURRItemInfo>* GetAstsTLSCURRItemInfoPool() {
		return this->m_astsTLSCURRItems;
	}
	inline AutoAllocatePointerList<AstsTLSCURRInfo>* GetAstsTLSCURRInfoPool() {
		return this->m_astsTLSCURR;
	}
	inline AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>* GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems;
	}
	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}
	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems;
	}
	inline AutoAllocatePointerList<AstsSecurityDefinitionInfo>* GetAstsSecurityDefinitionInfoPool() {
		return this->m_astsSecurityDefinition;
	}
	inline AutoAllocatePointerList<AstsSecurityStatusInfo>* GetAstsSecurityStatusInfoPool() {
		return this->m_astsSecurityStatus;
	}
	inline AutoAllocatePointerList<AstsTradingSessionStatusInfo>* GetAstsTradingSessionStatusInfoPool() {
		return this->m_astsTradingSessionStatus;
	}
	inline AutoAllocatePointerList<AstsHeartbeatInfo>* GetAstsHeartbeatInfoPool() {
		return this->m_astsHeartbeat;
	}
	inline AutoAllocatePointerList<AstsIncrementalGenericInfo>* GetAstsIncrementalGenericInfoPool() {
		return this->m_astsIncrementalGeneric;
	}
	inline AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>* GetAstsIncrementalMSRFONDInfoPool() {
		return this->m_astsIncrementalMSRFOND;
	}
	inline AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>* GetAstsIncrementalMSRCURRInfoPool() {
		return this->m_astsIncrementalMSRCURR;
	}
	inline AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>* GetAstsIncrementalOLRFONDInfoPool() {
		return this->m_astsIncrementalOLRFOND;
	}
	inline AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>* GetAstsIncrementalOLRCURRInfoPool() {
		return this->m_astsIncrementalOLRCURR;
	}
	inline AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>* GetAstsIncrementalTLRFONDInfoPool() {
		return this->m_astsIncrementalTLRFOND;
	}
	inline AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>* GetAstsIncrementalTLRCURRInfoPool() {
		return this->m_astsIncrementalTLRCURR;
	}
};
class AstsOLSFONDItemInfoPresenceIndices{
public:
	static const UINT64 MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX0;
	static const UINT64 MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX1;
	static const UINT64 MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const UINT64 OrigTimePresenceIndex = PRESENCE_MAP_INDEX3;
	static const UINT64 MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const UINT64 MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const UINT64 YieldPresenceIndex = PRESENCE_MAP_INDEX6;
	static const UINT64 OrderStatusPresenceIndex = PRESENCE_MAP_INDEX7;
	static const UINT64 OrdTypePresenceIndex = PRESENCE_MAP_INDEX8;
	static const UINT64 TotalVolumePresenceIndex = PRESENCE_MAP_INDEX9;
	static const UINT64 TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX10;
};
class AstsOLSCURRItemInfoPresenceIndices{
public:
	static const UINT64 MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX0;
	static const UINT64 MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX1;
	static const UINT64 MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const UINT64 OrigTimePresenceIndex = PRESENCE_MAP_INDEX3;
	static const UINT64 MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const UINT64 MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const UINT64 OrderStatusPresenceIndex = PRESENCE_MAP_INDEX6;
	static const UINT64 TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX7;
};
class AstsTLSFONDItemInfoPresenceIndices{
public:
	static const UINT64 MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX0;
	static const UINT64 MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX1;
	static const UINT64 OrigTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const UINT64 OrderSidePresenceIndex = PRESENCE_MAP_INDEX3;
	static const UINT64 MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const UINT64 MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const UINT64 AccruedInterestAmtPresenceIndex = PRESENCE_MAP_INDEX6;
	static const UINT64 TradeValuePresenceIndex = PRESENCE_MAP_INDEX7;
	static const UINT64 YieldPresenceIndex = PRESENCE_MAP_INDEX8;
	static const UINT64 SettlDatePresenceIndex = PRESENCE_MAP_INDEX9;
	static const UINT64 SettleTypePresenceIndex = PRESENCE_MAP_INDEX10;
	static const UINT64 PricePresenceIndex = PRESENCE_MAP_INDEX11;
	static const UINT64 PriceTypePresenceIndex = PRESENCE_MAP_INDEX12;
	static const UINT64 RepoToPxPresenceIndex = PRESENCE_MAP_INDEX13;
	static const UINT64 BuyBackPxPresenceIndex = PRESENCE_MAP_INDEX14;
	static const UINT64 BuyBackDatePresenceIndex = PRESENCE_MAP_INDEX15;
	static const UINT64 TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX16;
	static const UINT64 RefOrderIDPresenceIndex = PRESENCE_MAP_INDEX17;
};
class AstsTLSCURRItemInfoPresenceIndices{
public:
	static const UINT64 MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX0;
	static const UINT64 MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX1;
	static const UINT64 OrigTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const UINT64 OrderSidePresenceIndex = PRESENCE_MAP_INDEX3;
	static const UINT64 MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const UINT64 MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const UINT64 TradeValuePresenceIndex = PRESENCE_MAP_INDEX6;
	static const UINT64 SettlDatePresenceIndex = PRESENCE_MAP_INDEX7;
	static const UINT64 SettleTypePresenceIndex = PRESENCE_MAP_INDEX8;
	static const UINT64 PricePresenceIndex = PRESENCE_MAP_INDEX9;
	static const UINT64 PriceTypePresenceIndex = PRESENCE_MAP_INDEX10;
	static const UINT64 RepoToPxPresenceIndex = PRESENCE_MAP_INDEX11;
	static const UINT64 BuyBackPxPresenceIndex = PRESENCE_MAP_INDEX12;
	static const UINT64 BuyBackDatePresenceIndex = PRESENCE_MAP_INDEX13;
	static const UINT64 TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX14;
	static const UINT64 RefOrderIDPresenceIndex = PRESENCE_MAP_INDEX15;
};
class AstsIncrementalOLRFONDItemInfoPresenceIndices{
public:
	static const UINT64 MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX0;
	static const UINT64 SymbolPresenceIndex = PRESENCE_MAP_INDEX1;
	static const UINT64 MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX2;
	static const UINT64 MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX3;
	static const UINT64 OrigTimePresenceIndex = PRESENCE_MAP_INDEX4;
	static const UINT64 MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX5;
	static const UINT64 MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX6;
	static const UINT64 YieldPresenceIndex = PRESENCE_MAP_INDEX7;
	static const UINT64 OrderStatusPresenceIndex = PRESENCE_MAP_INDEX8;
	static const UINT64 OrdTypePresenceIndex = PRESENCE_MAP_INDEX9;
	static const UINT64 TotalVolumePresenceIndex = PRESENCE_MAP_INDEX10;
	static const UINT64 TradingSessionIDPresenceIndex = PRESENCE_MAP_INDEX11;
	static const UINT64 TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX12;
};
class AstsIncrementalOLRCURRItemInfoPresenceIndices{
public:
	static const UINT64 MDUpdateActionPresenceIndex = PRESENCE_MAP_INDEX0;
	static const UINT64 MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX1;
	static const UINT64 SymbolPresenceIndex = PRESENCE_MAP_INDEX2;
	static const UINT64 MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX3;
	static const UINT64 MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX4;
	static const UINT64 OrigTimePresenceIndex = PRESENCE_MAP_INDEX5;
	static const UINT64 MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX6;
	static const UINT64 MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX7;
	static const UINT64 OrderStatusPresenceIndex = PRESENCE_MAP_INDEX8;
	static const UINT64 TradingSessionIDPresenceIndex = PRESENCE_MAP_INDEX9;
	static const UINT64 TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX10;
};
class AstsLogonInfoNullIndices{
public:
	static const UINT64 UsernameNullIndex = NULL_MAP_INDEX0;
	static const UINT64 PasswordNullIndex = NULL_MAP_INDEX1;
};
class AstsLogoutInfoNullIndices{
public:
	static const UINT64 TextNullIndex = NULL_MAP_INDEX0;
};
class AstsGenericItemInfoNullIndices{
public:
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 QuoteConditionNullIndex = NULL_MAP_INDEX7;
	static const UINT64 TradeConditionNullIndex = NULL_MAP_INDEX8;
	static const UINT64 OpenCloseSettlFlagNullIndex = NULL_MAP_INDEX9;
	static const UINT64 OrdTypeNullIndex = NULL_MAP_INDEX10;
	static const UINT64 EffectiveTimeNullIndex = NULL_MAP_INDEX11;
	static const UINT64 StartTimeNullIndex = NULL_MAP_INDEX12;
	static const UINT64 AccruedInterestAmtNullIndex = NULL_MAP_INDEX13;
	static const UINT64 ChgFromWAPriceNullIndex = NULL_MAP_INDEX14;
	static const UINT64 ChgOpenInterestNullIndex = NULL_MAP_INDEX15;
	static const UINT64 BidMarketSizeNullIndex = NULL_MAP_INDEX16;
	static const UINT64 AskMarketSizeNullIndex = NULL_MAP_INDEX17;
	static const UINT64 TotalNumOfTradesNullIndex = NULL_MAP_INDEX18;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX19;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX20;
	static const UINT64 TotalVolumeNullIndex = NULL_MAP_INDEX21;
	static const UINT64 OfferNbOrNullIndex = NULL_MAP_INDEX22;
	static const UINT64 BidNbOrNullIndex = NULL_MAP_INDEX23;
	static const UINT64 ChgFromSettlmntNullIndex = NULL_MAP_INDEX24;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX25;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX26;
	static const UINT64 SumQtyOfBestNullIndex = NULL_MAP_INDEX27;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX28;
	static const UINT64 OrderStatusNullIndex = NULL_MAP_INDEX29;
	static const UINT64 MinCurrPxNullIndex = NULL_MAP_INDEX30;
	static const UINT64 MinCurrPxChgTimeNullIndex = NULL_MAP_INDEX31;
	static const UINT64 VolumeIndicatorNullIndex = NULL_MAP_INDEX32;
	static const UINT64 PriceNullIndex = NULL_MAP_INDEX33;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX34;
	static const UINT64 NominalValueNullIndex = NULL_MAP_INDEX35;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX36;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX37;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX38;
	static const UINT64 CXFlagNullIndex = NULL_MAP_INDEX39;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX40;
};
class AstsGenericInfoNullIndices{
public:
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX1;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX2;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX6;
	static const UINT64 NetChgPrevDayNullIndex = NULL_MAP_INDEX7;
};
class AstsOLSFONDItemInfoNullIndices{
public:
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX7;
	static const UINT64 OrderStatusNullIndex = NULL_MAP_INDEX8;
	static const UINT64 OrdTypeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 TotalVolumeNullIndex = NULL_MAP_INDEX10;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX11;
};
class AstsOLSFONDInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX6;
};
class AstsOLSCURRItemInfoNullIndices{
public:
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 OrderStatusNullIndex = NULL_MAP_INDEX7;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX8;
};
class AstsOLSCURRInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
};
class AstsTLSFONDItemInfoNullIndices{
public:
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX2;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 AccruedInterestAmtNullIndex = NULL_MAP_INDEX7;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX8;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX9;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX10;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX11;
	static const UINT64 PriceNullIndex = NULL_MAP_INDEX12;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX13;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX14;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX15;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX16;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX17;
	static const UINT64 RefOrderIDNullIndex = NULL_MAP_INDEX18;
};
class AstsTLSFONDInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX6;
};
class AstsTLSCURRItemInfoNullIndices{
public:
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX2;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX7;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX8;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 PriceNullIndex = NULL_MAP_INDEX10;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX11;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX12;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX13;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX14;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX15;
	static const UINT64 RefOrderIDNullIndex = NULL_MAP_INDEX16;
};
class AstsTLSCURRInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
};
class AstsSecurityDefinitionGroupInstrAttribItemInfoNullIndices{
public:
	static const UINT64 InstrAttribValueNullIndex = NULL_MAP_INDEX0;
};
class AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoNullIndices{
public:
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX1;
	static const UINT64 OrderNoteNullIndex = NULL_MAP_INDEX2;
};
class AstsSecurityDefinitionMarketSegmentGrpItemInfoNullIndices{
public:
	static const UINT64 RoundLotNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TradingSessionRulesGrpNullIndex = NULL_MAP_INDEX1;
};
class AstsSecurityDefinitionInfoNullIndices{
public:
	static const UINT64 TotNumReportsNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SecurityIDSourceNullIndex = NULL_MAP_INDEX3;
	static const UINT64 ProductNullIndex = NULL_MAP_INDEX4;
	static const UINT64 CFICodeNullIndex = NULL_MAP_INDEX5;
	static const UINT64 SecurityTypeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 MaturityDateNullIndex = NULL_MAP_INDEX7;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX8;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 OrigIssueAmtNullIndex = NULL_MAP_INDEX10;
	static const UINT64 CouponPaymentDateNullIndex = NULL_MAP_INDEX11;
	static const UINT64 CouponRateNullIndex = NULL_MAP_INDEX12;
	static const UINT64 SettlFixingDateNullIndex = NULL_MAP_INDEX13;
	static const UINT64 DividendNetPxNullIndex = NULL_MAP_INDEX14;
	static const UINT64 SecurityDescNullIndex = NULL_MAP_INDEX15;
	static const UINT64 EncodedSecurityDescNullIndex = NULL_MAP_INDEX16;
	static const UINT64 QuoteTextNullIndex = NULL_MAP_INDEX17;
	static const UINT64 GroupInstrAttribNullIndex = NULL_MAP_INDEX18;
	static const UINT64 CurrencyNullIndex = NULL_MAP_INDEX19;
	static const UINT64 MarketSegmentGrpNullIndex = NULL_MAP_INDEX20;
	static const UINT64 SettlCurrencyNullIndex = NULL_MAP_INDEX21;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX22;
	static const UINT64 StateSecurityIDNullIndex = NULL_MAP_INDEX23;
	static const UINT64 EncodedShortSecurityDescNullIndex = NULL_MAP_INDEX24;
	static const UINT64 MarketCodeNullIndex = NULL_MAP_INDEX25;
	static const UINT64 MinPriceIncrementNullIndex = NULL_MAP_INDEX26;
	static const UINT64 MktShareLimitNullIndex = NULL_MAP_INDEX27;
	static const UINT64 MktShareThresholdNullIndex = NULL_MAP_INDEX28;
	static const UINT64 MaxOrdersVolumeNullIndex = NULL_MAP_INDEX29;
	static const UINT64 PriceMvmLimitNullIndex = NULL_MAP_INDEX30;
	static const UINT64 FaceValueNullIndex = NULL_MAP_INDEX31;
	static const UINT64 BaseSwapPxNullIndex = NULL_MAP_INDEX32;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX33;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX34;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX35;
	static const UINT64 NoSharesIssuedNullIndex = NULL_MAP_INDEX36;
	static const UINT64 HighLimitNullIndex = NULL_MAP_INDEX37;
	static const UINT64 LowLimitNullIndex = NULL_MAP_INDEX38;
	static const UINT64 NumOfDaysToMaturityNullIndex = NULL_MAP_INDEX39;
};
class AstsSecurityStatusInfoNullIndices{
public:
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX2;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX3;
};
class AstsTradingSessionStatusInfoNullIndices{
public:
	static const UINT64 TextNullIndex = NULL_MAP_INDEX0;
};
class AstsIncrementalGenericItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX3;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX4;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX5;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX6;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX8;
	static const UINT64 EffectiveTimeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 StartTimeNullIndex = NULL_MAP_INDEX10;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX11;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX12;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX13;
	static const UINT64 QuoteConditionNullIndex = NULL_MAP_INDEX14;
	static const UINT64 TradeConditionNullIndex = NULL_MAP_INDEX15;
	static const UINT64 OpenCloseSettlFlagNullIndex = NULL_MAP_INDEX16;
	static const UINT64 OrdTypeNullIndex = NULL_MAP_INDEX17;
	static const UINT64 NetChgPrevDayNullIndex = NULL_MAP_INDEX18;
	static const UINT64 AccruedInterestAmtNullIndex = NULL_MAP_INDEX19;
	static const UINT64 ChgFromWAPriceNullIndex = NULL_MAP_INDEX20;
	static const UINT64 ChgOpenInterestNullIndex = NULL_MAP_INDEX21;
	static const UINT64 BidMarketSizeNullIndex = NULL_MAP_INDEX22;
	static const UINT64 AskMarketSizeNullIndex = NULL_MAP_INDEX23;
	static const UINT64 TotalNumOfTradesNullIndex = NULL_MAP_INDEX24;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX25;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX26;
	static const UINT64 TotalVolumeNullIndex = NULL_MAP_INDEX27;
	static const UINT64 OfferNbOrNullIndex = NULL_MAP_INDEX28;
	static const UINT64 BidNbOrNullIndex = NULL_MAP_INDEX29;
	static const UINT64 ChgFromSettlmntNullIndex = NULL_MAP_INDEX30;
	static const UINT64 SumQtyOfBestNullIndex = NULL_MAP_INDEX31;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX32;
	static const UINT64 OrderStatusNullIndex = NULL_MAP_INDEX33;
	static const UINT64 MinCurrPxNullIndex = NULL_MAP_INDEX34;
	static const UINT64 MinCurrPxChgTimeNullIndex = NULL_MAP_INDEX35;
	static const UINT64 VolumeIndicatorNullIndex = NULL_MAP_INDEX36;
	static const UINT64 PriceNullIndex = NULL_MAP_INDEX37;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX38;
	static const UINT64 NominalValueNullIndex = NULL_MAP_INDEX39;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX40;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX41;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX42;
	static const UINT64 CXFlagNullIndex = NULL_MAP_INDEX43;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX44;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX45;
};
class AstsIncrementalMSRFONDItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX3;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX8;
	static const UINT64 StartTimeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 QuoteConditionNullIndex = NULL_MAP_INDEX10;
	static const UINT64 TradeConditionNullIndex = NULL_MAP_INDEX11;
	static const UINT64 OpenCloseSettlFlagNullIndex = NULL_MAP_INDEX12;
	static const UINT64 NetChgPrevDayNullIndex = NULL_MAP_INDEX13;
	static const UINT64 AccruedInterestAmtNullIndex = NULL_MAP_INDEX14;
	static const UINT64 ChgFromWAPriceNullIndex = NULL_MAP_INDEX15;
	static const UINT64 ChgOpenInterestNullIndex = NULL_MAP_INDEX16;
	static const UINT64 BidMarketSizeNullIndex = NULL_MAP_INDEX17;
	static const UINT64 AskMarketSizeNullIndex = NULL_MAP_INDEX18;
	static const UINT64 TotalNumOfTradesNullIndex = NULL_MAP_INDEX19;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX20;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX21;
	static const UINT64 OfferNbOrNullIndex = NULL_MAP_INDEX22;
	static const UINT64 BidNbOrNullIndex = NULL_MAP_INDEX23;
	static const UINT64 ChgFromSettlmntNullIndex = NULL_MAP_INDEX24;
	static const UINT64 MinCurrPxNullIndex = NULL_MAP_INDEX25;
	static const UINT64 MinCurrPxChgTimeNullIndex = NULL_MAP_INDEX26;
	static const UINT64 VolumeIndicatorNullIndex = NULL_MAP_INDEX27;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX28;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX29;
	static const UINT64 CXFlagNullIndex = NULL_MAP_INDEX30;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX31;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX32;
};
class AstsIncrementalMSRFONDInfoNullIndices{
public:
	static const UINT64 LastUpdateTimeNullIndex = NULL_MAP_INDEX0;
};
class AstsIncrementalMSRCURRItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX3;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX8;
	static const UINT64 StartTimeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 QuoteConditionNullIndex = NULL_MAP_INDEX10;
	static const UINT64 TradeConditionNullIndex = NULL_MAP_INDEX11;
	static const UINT64 OpenCloseSettlFlagNullIndex = NULL_MAP_INDEX12;
	static const UINT64 NetChgPrevDayNullIndex = NULL_MAP_INDEX13;
	static const UINT64 ChgFromWAPriceNullIndex = NULL_MAP_INDEX14;
	static const UINT64 ChgOpenInterestNullIndex = NULL_MAP_INDEX15;
	static const UINT64 BidMarketSizeNullIndex = NULL_MAP_INDEX16;
	static const UINT64 AskMarketSizeNullIndex = NULL_MAP_INDEX17;
	static const UINT64 TotalNumOfTradesNullIndex = NULL_MAP_INDEX18;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX19;
	static const UINT64 OfferNbOrNullIndex = NULL_MAP_INDEX20;
	static const UINT64 BidNbOrNullIndex = NULL_MAP_INDEX21;
	static const UINT64 ChgFromSettlmntNullIndex = NULL_MAP_INDEX22;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX23;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX24;
	static const UINT64 CXFlagNullIndex = NULL_MAP_INDEX25;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX26;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX27;
};
class AstsIncrementalMSRCURRInfoNullIndices{
public:
	static const UINT64 LastUpdateTimeNullIndex = NULL_MAP_INDEX0;
};
class AstsIncrementalOLRFONDItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX3;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX8;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX10;
	static const UINT64 OrderStatusNullIndex = NULL_MAP_INDEX11;
	static const UINT64 OrdTypeNullIndex = NULL_MAP_INDEX12;
	static const UINT64 TotalVolumeNullIndex = NULL_MAP_INDEX13;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX14;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX15;
};
class AstsIncrementalOLRCURRItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryTypeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX3;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX8;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 OrderStatusNullIndex = NULL_MAP_INDEX10;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX11;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX12;
};
class AstsIncrementalTLRFONDItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX2;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX3;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX5;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX8;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 AccruedInterestAmtNullIndex = NULL_MAP_INDEX10;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX11;
	static const UINT64 YieldNullIndex = NULL_MAP_INDEX12;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX13;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX14;
	static const UINT64 PriceNullIndex = NULL_MAP_INDEX15;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX16;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX17;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX18;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX19;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX20;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX21;
	static const UINT64 RefOrderIDNullIndex = NULL_MAP_INDEX22;
};
class AstsIncrementalTLRCURRItemInfoNullIndices{
public:
	static const UINT64 MDUpdateActionNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX2;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX3;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntryTimeNullIndex = NULL_MAP_INDEX5;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX6;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX8;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 TradeValueNullIndex = NULL_MAP_INDEX10;
	static const UINT64 SettlDateNullIndex = NULL_MAP_INDEX11;
	static const UINT64 SettleTypeNullIndex = NULL_MAP_INDEX12;
	static const UINT64 PriceNullIndex = NULL_MAP_INDEX13;
	static const UINT64 PriceTypeNullIndex = NULL_MAP_INDEX14;
	static const UINT64 RepoToPxNullIndex = NULL_MAP_INDEX15;
	static const UINT64 BuyBackPxNullIndex = NULL_MAP_INDEX16;
	static const UINT64 BuyBackDateNullIndex = NULL_MAP_INDEX17;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX18;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX19;
	static const UINT64 RefOrderIDNullIndex = NULL_MAP_INDEX20;
};
#pragma endregion

#pragma region Forts_Message_Info_Structures_Definition_GeneratedCode
class FortsSnapshotInfo {
public:
	UINT64				PresenceMap;
	UINT64				NullMap;
	int				TemplateId;
	UINT32				RptSeq;
	UINT32				LastFragment;
	UINT32				LastMsgSeqNumProcessed;
	UINT64				SendingTime;
	UINT64				SecurityID;
	FortsSnapshotInfo() {
		memset(this, 0, sizeof(FortsSnapshotInfo));
	}
};

class FortsDefaultSnapshotMessageMDEntriesItemInfo;
class FortsDefaultSnapshotMessageInfo;
class FortsSecurityDefinitionMDFeedTypesItemInfo;
class FortsSecurityDefinitionUnderlyingsItemInfo;
class FortsSecurityDefinitionInstrumentLegsItemInfo;
class FortsSecurityDefinitionInstrumentAttributesItemInfo;
class FortsSecurityDefinitionEvntGrpItemInfo;
class FortsSecurityDefinitionInfo;
class FortsSecurityDefinitionUpdateReportInfo;
class FortsSecurityStatusInfo;
class FortsHeartbeatInfo;
class FortsSequenceResetInfo;
class FortsTradingSessionStatusInfo;
class FortsNewsNewsTextItemInfo;
class FortsNewsInfo;
class FortsOrdersLogMDEntriesItemInfo;
class FortsOrdersLogInfo;
class FortsOrdersBookMDEntriesItemInfo;
class FortsOrdersBookInfo;
class FortsLogonInfo;
class FortsLogoutInfo;
class FortsDefaultIncrementalRefreshMessageInfo;

class FortsDefaultSnapshotMessageMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional  
	UINT64							MDEntryID;			// id=278  presence=optional  
	UINT32							MarketDepth;			// id=264  presence=optional  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT64							MDEntryTime;			// id=273  
	UINT64							MDEntrySize;			// id=271  presence=optional  
	UINT32							MDPriceLevel;			// id=1023  presence=optional  
	INT32							NumberOfOrders;			// id=346  presence=optional  
	char							MDEntryTradeType[4];			// id=20003  presence=optional  
	INT32							TrdType;			// id=828  presence=optional  
	INT32							MDFlags;			// id=20017  presence=optional  
	char							Currency[4];			// id=15  presence=optional  
	char							OrderSide[4];			// id=10504  presence=optional  
	UINT32							MDUpdateAction;			// id=279  
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							Symbol[16];			// id=55  presence=optional  
	char							SecurityGroup[16];			// id=1151  presence=optional  
	UINT32							RptSeq;			// id=83  
	Decimal							LastPx;			// id=31  presence=optional  
	UINT64							Revision;			// id=20018  presence=optional  
	int								MDEntryTypeLength;			// id=269  
	int								MDEntryTradeTypeLength;			// id=20003  presence=optional  
	int								CurrencyLength;			// id=15  presence=optional  
	int								OrderSideLength;			// id=10504  presence=optional  
	int								SymbolLength;			// id=55  presence=optional  
	int								SecurityGroupLength;			// id=1151  presence=optional  

	FortsDefaultSnapshotMessageMDEntriesItemInfo() {
		memset(this, 0, sizeof(FortsDefaultSnapshotMessageMDEntriesItemInfo));
	}
	~FortsDefaultSnapshotMessageMDEntriesItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsDefaultSnapshotMessageInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsDefaultSnapshotMessageInfo>							*Pointer;
	AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = W
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RptSeq;			// id=83  
	UINT32							TotNumReports;			// id=911  
	UINT32							LastMsgSeqNumProcessed;			// id=369  
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							Symbol[16];			// id=55  presence=optional  
	char							SecurityGroup[16];			// id=1151  presence=optional  
	FortsDefaultSnapshotMessageMDEntriesItemInfo* MDEntries[256];
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								SymbolLength;			// id=55  presence=optional  
	int								SecurityGroupLength;			// id=1151  presence=optional  
	int								MDEntriesCount;

	FortsDefaultSnapshotMessageInfo() {
		memset(this, 0, sizeof(FortsDefaultSnapshotMessageInfo));
	}
	~FortsDefaultSnapshotMessageInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsSecurityDefinitionMDFeedTypesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionMDFeedTypesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>							*Allocator;
	bool							Used;
	char							MDFeedType[16];			// id=1022  
	UINT32							MarketDepth;			// id=264  presence=optional  
	UINT32							MDBookType;			// id=1021  presence=optional  
	int								MDFeedTypeLength;			// id=1022  

	FortsSecurityDefinitionMDFeedTypesItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionMDFeedTypesItemInfo));
	}
	~FortsSecurityDefinitionMDFeedTypesItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSecurityDefinitionUnderlyingsItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionUnderlyingsItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>							*Allocator;
	bool							Used;
	char							UnderlyingSymbol[16];			// id=311  
	UINT64							UnderlyingSecurityID;			// id=309  presence=optional  
	int								UnderlyingSymbolLength;			// id=311  

	FortsSecurityDefinitionUnderlyingsItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionUnderlyingsItemInfo));
	}
	~FortsSecurityDefinitionUnderlyingsItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSecurityDefinitionInstrumentLegsItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionInstrumentLegsItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>							*Allocator;
	bool							Used;
	char							LegSymbol[16];			// id=600  
	UINT64							LegSecurityID;			// id=602  
	Decimal							LegRatioQty;			// id=623  
	int								LegSymbolLength;			// id=600  

	FortsSecurityDefinitionInstrumentLegsItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionInstrumentLegsItemInfo));
	}
	~FortsSecurityDefinitionInstrumentLegsItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSecurityDefinitionInstrumentAttributesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionInstrumentAttributesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>							*Allocator;
	bool							Used;
	INT32							InstrAttribType;			// id=871  
	char							InstrAttribValue[16];			// id=872  
	int								InstrAttribValueLength;			// id=872  

	FortsSecurityDefinitionInstrumentAttributesItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionInstrumentAttributesItemInfo));
	}
	~FortsSecurityDefinitionInstrumentAttributesItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSecurityDefinitionEvntGrpItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionEvntGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>							*Allocator;
	bool							Used;
	INT32							EventType;			// id=865  
	UINT32							EventDate;			// id=866  
	UINT64							EventTime;			// id=1145  

	FortsSecurityDefinitionEvntGrpItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionEvntGrpItemInfo));
	}
	~FortsSecurityDefinitionEvntGrpItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSecurityDefinitionInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = d
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							TotNumReports;			// id=911  
	char							Symbol[16];			// id=55  
	unsigned char							SecurityDesc[128];			// id=107  presence=optional  charset=unicode  
	UINT64							SecurityID;			// id=48  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							SecurityAltID[16];			// id=455  presence=optional  
	char							SecurityAltIDSource[16];			// id=456  presence=optional  
	char							SecurityType[16];			// id=167  presence=optional  
	char							CFICode[16];			// id=461  presence=optional  
	Decimal							StrikePrice;			// id=202  presence=optional  
	Decimal							ContractMultiplier;			// id=231  presence=optional  
	UINT32							SecurityTradingStatus;			// id=326  presence=optional  
	char							Currency[4];			// id=15  presence=optional  
	char							MarketID[16];			// id=1301    constant has constant value = MOEX
	char							MarketSegmentID[16];			// id=1300  
	UINT32							TradingSessionID;			// id=336  presence=optional  
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional  
	Decimal							Volatility;			// id=5678  presence=optional  
	FortsSecurityDefinitionMDFeedTypesItemInfo* MDFeedTypes[256];
	FortsSecurityDefinitionUnderlyingsItemInfo* Underlyings[256];			// presence=optional  
	Decimal							HighLimitPx;			// id=1149  presence=optional  
	Decimal							LowLimitPx;			// id=1148  presence=optional  
	Decimal							MinPriceIncrement;			// id=969  presence=optional  
	Decimal							MinPriceIncrementAmount;			// id=1146  presence=optional  
	Decimal							InitialMarginOnBuy;			// id=20002  presence=optional  
	Decimal							InitialMarginOnSell;			// id=20000  presence=optional  
	Decimal							InitialMarginSyntetic;			// id=20001  presence=optional  
	char							QuotationList[16];			// id=20005  presence=optional  
	Decimal							TheorPrice;			// id=20006  presence=optional  
	Decimal							TheorPriceLimit;			// id=20007  presence=optional  
	FortsSecurityDefinitionInstrumentLegsItemInfo* InstrumentLegs[256];			// presence=optional  
	FortsSecurityDefinitionInstrumentAttributesItemInfo* InstrumentAttributes[256];			// presence=optional  
	Decimal							UnderlyingQty;			// id=879  presence=optional  
	char							UnderlyingCurrency[16];			// id=318  presence=optional  
	FortsSecurityDefinitionEvntGrpItemInfo* EvntGrp[256];			// presence=optional  
	UINT32							MaturityDate;			// id=541  presence=optional  
	UINT32							MaturityTime;			// id=1079  presence=optional  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = d
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								SymbolLength;			// id=55  
	int								SecurityDescLength;			// id=107  presence=optional  charset=unicode  
	int								SecurityAltIDLength;			// id=455  presence=optional  
	int								SecurityAltIDSourceLength;			// id=456  presence=optional  
	int								SecurityTypeLength;			// id=167  presence=optional  
	int								CFICodeLength;			// id=461  presence=optional  
	int								CurrencyLength;			// id=15  presence=optional  
	int								MarketIDLength;			// id=1301    constant has constant value = MOEX
	int								MarketSegmentIDLength;			// id=1300  
	int								MDFeedTypesCount;
	int								UnderlyingsCount;			// presence=optional  
	int								QuotationListLength;			// id=20005  presence=optional  
	int								InstrumentLegsCount;			// presence=optional  
	int								InstrumentAttributesCount;			// presence=optional  
	int								UnderlyingCurrencyLength;			// id=318  presence=optional  
	int								EvntGrpCount;			// presence=optional  

	FortsSecurityDefinitionInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionInfo));
	}
	~FortsSecurityDefinitionInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDFeedTypesCount; i++)
			this->MDFeedTypes[i]->Clear();
		for(int i = 0; i < this->UnderlyingsCount; i++)
			this->Underlyings[i]->Clear();
		for(int i = 0; i < this->InstrumentLegsCount; i++)
			this->InstrumentLegs[i]->Clear();
		for(int i = 0; i < this->InstrumentAttributesCount; i++)
			this->InstrumentAttributes[i]->Clear();
		for(int i = 0; i < this->EvntGrpCount; i++)
			this->EvntGrp[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDFeedTypesCount; i++)
			this->MDFeedTypes[i]->ReleaseUnused();
		for(int i = 0; i < this->UnderlyingsCount; i++)
			this->Underlyings[i]->ReleaseUnused();
		for(int i = 0; i < this->InstrumentLegsCount; i++)
			this->InstrumentLegs[i]->ReleaseUnused();
		for(int i = 0; i < this->InstrumentAttributesCount; i++)
			this->InstrumentAttributes[i]->ReleaseUnused();
		for(int i = 0; i < this->EvntGrpCount; i++)
			this->EvntGrp[i]->ReleaseUnused();
	}
};

class FortsSecurityDefinitionUpdateReportInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionUpdateReportInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = BP
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							SecurityID;			// id=48  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	Decimal							Volatility;			// id=5678  presence=optional  
	Decimal							TheorPrice;			// id=20006  presence=optional  
	Decimal							TheorPriceLimit;			// id=20007  presence=optional  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = BP
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX

	FortsSecurityDefinitionUpdateReportInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionUpdateReportInfo));
	}
	~FortsSecurityDefinitionUpdateReportInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSecurityStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityStatusInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = f
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							SecurityID;			// id=48  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							Symbol[16];			// id=55  
	UINT32							SecurityTradingStatus;			// id=326  presence=optional  
	Decimal							HighLimitPx;			// id=1149  presence=optional  
	Decimal							LowLimitPx;			// id=1148  presence=optional  
	Decimal							InitialMarginOnBuy;			// id=20002  presence=optional  
	Decimal							InitialMarginOnSell;			// id=20000  presence=optional  
	Decimal							InitialMarginSyntetic;			// id=20001  presence=optional  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = f
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								SymbolLength;			// id=55  

	FortsSecurityStatusInfo() {
		memset(this, 0, sizeof(FortsSecurityStatusInfo));
	}
	~FortsSecurityStatusInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsHeartbeatInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<FortsHeartbeatInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = 0
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = 0
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX

	FortsHeartbeatInfo() {
		memset(this, 0, sizeof(FortsHeartbeatInfo));
	}
	~FortsHeartbeatInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsSequenceResetInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSequenceResetInfo>							*Pointer;
	AutoAllocatePointerList<FortsSequenceResetInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = 4
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							NewSeqNo;			// id=36  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = 4
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX

	FortsSequenceResetInfo() {
		memset(this, 0, sizeof(FortsSequenceResetInfo));
	}
	~FortsSequenceResetInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsTradingSessionStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<FortsTradingSessionStatusInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = h
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							TradSesOpenTime;			// id=342  
	UINT64							TradSesCloseTime;			// id=344  
	UINT64							TradSesIntermClearingStartTime;			// id=5840  presence=optional  
	UINT64							TradSesIntermClearingEndTime;			// id=5841  presence=optional  
	UINT32							TradingSessionID;			// id=336  
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional  
	UINT32							TradSesStatus;			// id=340  
	char							MarketID[16];			// id=1301    constant has constant value = MOEX
	char							MarketSegmentID[16];			// id=1300  
	INT32							TradSesEvent;			// id=1368  presence=optional  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = h
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								MarketIDLength;			// id=1301    constant has constant value = MOEX
	int								MarketSegmentIDLength;			// id=1300  

	FortsTradingSessionStatusInfo() {
		memset(this, 0, sizeof(FortsTradingSessionStatusInfo));
	}
	~FortsTradingSessionStatusInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsNewsNewsTextItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsNewsNewsTextItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsNewsNewsTextItemInfo>							*Allocator;
	bool							Used;
	unsigned char							Text[128];			// id=58  charset=unicode  
	int								TextLength;			// id=58  charset=unicode  

	FortsNewsNewsTextItemInfo() {
		memset(this, 0, sizeof(FortsNewsNewsTextItemInfo));
	}
	~FortsNewsNewsTextItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsNewsInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsNewsInfo>							*Pointer;
	AutoAllocatePointerList<FortsNewsInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = B
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  presence=optional  
	char							NewsId[16];			// id=1472  presence=optional  
	UINT64							OrigTime;			// id=42  presence=optional  
	char							LanguageCode[16];			// id=1474  presence=optional  
	UINT32							Urgency;			// id=61  presence=optional  
	unsigned char							Headline[128];			// id=148  charset=unicode  
	char							MarketID[16];			// id=1301    constant has constant value = MOEX
	char							MarketSegmentID[16];			// id=1300  presence=optional  
	FortsNewsNewsTextItemInfo* NewsText[256];
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = B
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								NewsIdLength;			// id=1472  presence=optional  
	int								LanguageCodeLength;			// id=1474  presence=optional  
	int								HeadlineLength;			// id=148  charset=unicode  
	int								MarketIDLength;			// id=1301    constant has constant value = MOEX
	int								MarketSegmentIDLength;			// id=1300  presence=optional  
	int								NewsTextCount;

	FortsNewsInfo() {
		memset(this, 0, sizeof(FortsNewsInfo));
	}
	~FortsNewsInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->ReleaseUnused();
	}
};

class FortsOrdersLogMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersLogMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>							*Allocator;
	bool							Used;
	UINT32							MDUpdateAction;			// id=279  
	char							MDEntryType[4];			// id=269  
	UINT64							MDEntryID;			// id=278  presence=optional  
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	UINT32							RptSeq;			// id=83  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT64							MDEntryTime;			// id=273  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	UINT64							MDEntrySize;			// id=271  presence=optional  
	Decimal							LastPx;			// id=31  presence=optional  
	UINT64							LastQty;			// id=32  presence=optional  
	UINT64							TradeID;			// id=1003  presence=optional  
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional  
	UINT64							MDFlags;			// id=20017  presence=optional  
	UINT64							Revision;			// id=20018  presence=optional  
	int								MDEntryTypeLength;			// id=269  

	FortsOrdersLogMDEntriesItemInfo() {
		memset(this, 0, sizeof(FortsOrdersLogMDEntriesItemInfo));
	}
	~FortsOrdersLogMDEntriesItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsOrdersLogInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersLogInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersLogInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = X
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  
	FortsOrdersLogMDEntriesItemInfo* MDEntries[256];
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								MDEntriesCount;

	FortsOrdersLogInfo() {
		memset(this, 0, sizeof(FortsOrdersLogInfo));
	}
	~FortsOrdersLogInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsOrdersBookMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersBookMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  
	UINT64							MDEntryID;			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT64							MDEntryTime;			// id=273  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	UINT64							MDEntrySize;			// id=271  presence=optional  
	UINT64							TradeID;			// id=1003  presence=optional  
	UINT64							MDFlags;			// id=20017  presence=optional  
	int								MDEntryTypeLength;			// id=269  

	FortsOrdersBookMDEntriesItemInfo() {
		memset(this, 0, sizeof(FortsOrdersBookMDEntriesItemInfo));
	}
	~FortsOrdersBookMDEntriesItemInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsOrdersBookInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersBookInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersBookInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = W
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  
	UINT32							RptSeq;			// id=83  presence=optional  
	UINT32							LastFragment;			// id=893  
	UINT32							RouteFirst;			// id=7944  
	UINT32							ExchangeTradingSessionID;			// id=5842  
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	FortsOrdersBookMDEntriesItemInfo* MDEntries[256];
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = W
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								MDEntriesCount;

	FortsOrdersBookInfo() {
		memset(this, 0, sizeof(FortsOrdersBookInfo));
	}
	~FortsOrdersBookInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsLogonInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsLogonInfo>							*Pointer;
	AutoAllocatePointerList<FortsLogonInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = A
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = A
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX

	FortsLogonInfo() {
		memset(this, 0, sizeof(FortsLogonInfo));
	}
	~FortsLogonInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsLogoutInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsLogoutInfo>							*Pointer;
	AutoAllocatePointerList<FortsLogoutInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = 5
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							Text[512];			// id=58  presence=optional  
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = 5
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								TextLength;			// id=58  presence=optional  

	FortsLogoutInfo() {
		memset(this, 0, sizeof(FortsLogoutInfo));
	}
	~FortsLogoutInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
	}
};

class FortsDefaultIncrementalRefreshMessageInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsDefaultIncrementalRefreshMessageInfo>							*Pointer;
	AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	char							MessageType[16];			// id=35    constant has constant value = X
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  presence=optional  
	FortsDefaultSnapshotMessageMDEntriesItemInfo* MDEntries[256];
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9
	int								MessageTypeLength;			// id=35    constant has constant value = X
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX
	int								MDEntriesCount;

	FortsDefaultIncrementalRefreshMessageInfo() {
		memset(this, 0, sizeof(FortsDefaultIncrementalRefreshMessageInfo));
	}
	~FortsDefaultIncrementalRefreshMessageInfo() { }
	inline void Clear() {
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsObjectsAllocationInfo {
	AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>				*m_fortsDefaultSnapshotMessageMDEntriesItems;
	AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>				*m_fortsDefaultSnapshotMessage;
	AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>				*m_fortsSecurityDefinitionMDFeedTypesItems;
	AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>				*m_fortsSecurityDefinitionUnderlyingsItems;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>				*m_fortsSecurityDefinitionInstrumentLegsItems;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>				*m_fortsSecurityDefinitionInstrumentAttributesItems;
	AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>				*m_fortsSecurityDefinitionEvntGrpItems;
	AutoAllocatePointerList<FortsSecurityDefinitionInfo>				*m_fortsSecurityDefinition;
	AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>				*m_fortsSecurityDefinitionUpdateReport;
	AutoAllocatePointerList<FortsSecurityStatusInfo>				*m_fortsSecurityStatus;
	AutoAllocatePointerList<FortsHeartbeatInfo>				*m_fortsHeartbeat;
	AutoAllocatePointerList<FortsSequenceResetInfo>				*m_fortsSequenceReset;
	AutoAllocatePointerList<FortsTradingSessionStatusInfo>				*m_fortsTradingSessionStatus;
	AutoAllocatePointerList<FortsNewsNewsTextItemInfo>				*m_fortsNewsNewsTextItems;
	AutoAllocatePointerList<FortsNewsInfo>				*m_fortsNews;
	AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>				*m_fortsOrdersLogMDEntriesItems;
	AutoAllocatePointerList<FortsOrdersLogInfo>				*m_fortsOrdersLog;
	AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>				*m_fortsOrdersBookMDEntriesItems;
	AutoAllocatePointerList<FortsOrdersBookInfo>				*m_fortsOrdersBook;
	AutoAllocatePointerList<FortsLogonInfo>				*m_fortsLogon;
	AutoAllocatePointerList<FortsLogoutInfo>				*m_fortsLogout;
	AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>				*m_fortsDefaultIncrementalRefreshMessage;
public:
	 static FortsObjectsAllocationInfo *Default;
	FortsObjectsAllocationInfo(int count) {
		this->m_fortsDefaultSnapshotMessageMDEntriesItems = new AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>(count, count, "FortsDefaultSnapshotMessageMDEntriesItemInfo");
		this->m_fortsDefaultSnapshotMessage = new AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>(count, count, "FortsDefaultSnapshotMessageInfo");
		this->m_fortsSecurityDefinitionMDFeedTypesItems = new AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>(count, count, "FortsSecurityDefinitionMDFeedTypesItemInfo");
		this->m_fortsSecurityDefinitionUnderlyingsItems = new AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>(count, count, "FortsSecurityDefinitionUnderlyingsItemInfo");
		this->m_fortsSecurityDefinitionInstrumentLegsItems = new AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>(count, count, "FortsSecurityDefinitionInstrumentLegsItemInfo");
		this->m_fortsSecurityDefinitionInstrumentAttributesItems = new AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>(count, count, "FortsSecurityDefinitionInstrumentAttributesItemInfo");
		this->m_fortsSecurityDefinitionEvntGrpItems = new AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>(count, count, "FortsSecurityDefinitionEvntGrpItemInfo");
		this->m_fortsSecurityDefinition = new AutoAllocatePointerList<FortsSecurityDefinitionInfo>(count, count, "FortsSecurityDefinitionInfo");
		this->m_fortsSecurityDefinitionUpdateReport = new AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>(count, count, "FortsSecurityDefinitionUpdateReportInfo");
		this->m_fortsSecurityStatus = new AutoAllocatePointerList<FortsSecurityStatusInfo>(count, count, "FortsSecurityStatusInfo");
		this->m_fortsHeartbeat = new AutoAllocatePointerList<FortsHeartbeatInfo>(count, count, "FortsHeartbeatInfo");
		this->m_fortsSequenceReset = new AutoAllocatePointerList<FortsSequenceResetInfo>(count, count, "FortsSequenceResetInfo");
		this->m_fortsTradingSessionStatus = new AutoAllocatePointerList<FortsTradingSessionStatusInfo>(count, count, "FortsTradingSessionStatusInfo");
		this->m_fortsNewsNewsTextItems = new AutoAllocatePointerList<FortsNewsNewsTextItemInfo>(count, count, "FortsNewsNewsTextItemInfo");
		this->m_fortsNews = new AutoAllocatePointerList<FortsNewsInfo>(count, count, "FortsNewsInfo");
		this->m_fortsOrdersLogMDEntriesItems = new AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>(count, count, "FortsOrdersLogMDEntriesItemInfo");
		this->m_fortsOrdersLog = new AutoAllocatePointerList<FortsOrdersLogInfo>(count, count, "FortsOrdersLogInfo");
		this->m_fortsOrdersBookMDEntriesItems = new AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>(count, count, "FortsOrdersBookMDEntriesItemInfo");
		this->m_fortsOrdersBook = new AutoAllocatePointerList<FortsOrdersBookInfo>(count, count, "FortsOrdersBookInfo");
		this->m_fortsLogon = new AutoAllocatePointerList<FortsLogonInfo>(count, count, "FortsLogonInfo");
		this->m_fortsLogout = new AutoAllocatePointerList<FortsLogoutInfo>(count, count, "FortsLogoutInfo");
		this->m_fortsDefaultIncrementalRefreshMessage = new AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>(count, count, "FortsDefaultIncrementalRefreshMessageInfo");
	}
	inline void AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(int count, int addCount) {
		this->m_fortsDefaultSnapshotMessageMDEntriesItems->Append(count);
		this->m_fortsDefaultSnapshotMessageMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateDefaultSnapshotMessageInfoPool(int count, int addCount) {
		this->m_fortsDefaultSnapshotMessage->Append(count);
		this->m_fortsDefaultSnapshotMessage->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMDFeedTypesItemInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinitionMDFeedTypesItems->Append(count);
		this->m_fortsSecurityDefinitionMDFeedTypesItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionUnderlyingsItemInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinitionUnderlyingsItems->Append(count);
		this->m_fortsSecurityDefinitionUnderlyingsItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInstrumentLegsItemInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinitionInstrumentLegsItems->Append(count);
		this->m_fortsSecurityDefinitionInstrumentLegsItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInstrumentAttributesItemInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinitionInstrumentAttributesItems->Append(count);
		this->m_fortsSecurityDefinitionInstrumentAttributesItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionEvntGrpItemInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinitionEvntGrpItems->Append(count);
		this->m_fortsSecurityDefinitionEvntGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinition->Append(count);
		this->m_fortsSecurityDefinition->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionUpdateReportInfoPool(int count, int addCount) {
		this->m_fortsSecurityDefinitionUpdateReport->Append(count);
		this->m_fortsSecurityDefinitionUpdateReport->AddCount(addCount);
	}
	inline void AllocateSecurityStatusInfoPool(int count, int addCount) {
		this->m_fortsSecurityStatus->Append(count);
		this->m_fortsSecurityStatus->AddCount(addCount);
	}
	inline void AllocateHeartbeatInfoPool(int count, int addCount) {
		this->m_fortsHeartbeat->Append(count);
		this->m_fortsHeartbeat->AddCount(addCount);
	}
	inline void AllocateSequenceResetInfoPool(int count, int addCount) {
		this->m_fortsSequenceReset->Append(count);
		this->m_fortsSequenceReset->AddCount(addCount);
	}
	inline void AllocateTradingSessionStatusInfoPool(int count, int addCount) {
		this->m_fortsTradingSessionStatus->Append(count);
		this->m_fortsTradingSessionStatus->AddCount(addCount);
	}
	inline void AllocateNewsNewsTextItemInfoPool(int count, int addCount) {
		this->m_fortsNewsNewsTextItems->Append(count);
		this->m_fortsNewsNewsTextItems->AddCount(addCount);
	}
	inline void AllocateNewsInfoPool(int count, int addCount) {
		this->m_fortsNews->Append(count);
		this->m_fortsNews->AddCount(addCount);
	}
	inline void AllocateOrdersLogMDEntriesItemInfoPool(int count, int addCount) {
		this->m_fortsOrdersLogMDEntriesItems->Append(count);
		this->m_fortsOrdersLogMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateOrdersLogInfoPool(int count, int addCount) {
		this->m_fortsOrdersLog->Append(count);
		this->m_fortsOrdersLog->AddCount(addCount);
	}
	inline void AllocateOrdersBookMDEntriesItemInfoPool(int count, int addCount) {
		this->m_fortsOrdersBookMDEntriesItems->Append(count);
		this->m_fortsOrdersBookMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateOrdersBookInfoPool(int count, int addCount) {
		this->m_fortsOrdersBook->Append(count);
		this->m_fortsOrdersBook->AddCount(addCount);
	}
	inline void AllocateLogonInfoPool(int count, int addCount) {
		this->m_fortsLogon->Append(count);
		this->m_fortsLogon->AddCount(addCount);
	}
	inline void AllocateLogoutInfoPool(int count, int addCount) {
		this->m_fortsLogout->Append(count);
		this->m_fortsLogout->AddCount(addCount);
	}
	inline void AllocateDefaultIncrementalRefreshMessageInfoPool(int count, int addCount) {
		this->m_fortsDefaultIncrementalRefreshMessage->Append(count);
		this->m_fortsDefaultIncrementalRefreshMessage->AddCount(addCount);
	}
	inline void AllocateDefaultSnapshotMessageMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_fortsDefaultSnapshotMessageMDEntriesItems->Capacity();
		if(count > 0)
			this->m_fortsDefaultSnapshotMessageMDEntriesItems->Append(count);
	}
	inline void AllocateDefaultSnapshotMessageInfoPoolTo(int count) {
		count -= this->m_fortsDefaultSnapshotMessage->Capacity();
		if(count > 0)
			this->m_fortsDefaultSnapshotMessage->Append(count);
	}
	inline void AllocateSecurityDefinitionMDFeedTypesItemInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinitionMDFeedTypesItems->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinitionMDFeedTypesItems->Append(count);
	}
	inline void AllocateSecurityDefinitionUnderlyingsItemInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinitionUnderlyingsItems->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinitionUnderlyingsItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInstrumentLegsItemInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinitionInstrumentLegsItems->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinitionInstrumentLegsItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInstrumentAttributesItemInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinitionInstrumentAttributesItems->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinitionInstrumentAttributesItems->Append(count);
	}
	inline void AllocateSecurityDefinitionEvntGrpItemInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinitionEvntGrpItems->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinitionEvntGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinition->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinition->Append(count);
	}
	inline void AllocateSecurityDefinitionUpdateReportInfoPoolTo(int count) {
		count -= this->m_fortsSecurityDefinitionUpdateReport->Capacity();
		if(count > 0)
			this->m_fortsSecurityDefinitionUpdateReport->Append(count);
	}
	inline void AllocateSecurityStatusInfoPoolTo(int count) {
		count -= this->m_fortsSecurityStatus->Capacity();
		if(count > 0)
			this->m_fortsSecurityStatus->Append(count);
	}
	inline void AllocateHeartbeatInfoPoolTo(int count) {
		count -= this->m_fortsHeartbeat->Capacity();
		if(count > 0)
			this->m_fortsHeartbeat->Append(count);
	}
	inline void AllocateSequenceResetInfoPoolTo(int count) {
		count -= this->m_fortsSequenceReset->Capacity();
		if(count > 0)
			this->m_fortsSequenceReset->Append(count);
	}
	inline void AllocateTradingSessionStatusInfoPoolTo(int count) {
		count -= this->m_fortsTradingSessionStatus->Capacity();
		if(count > 0)
			this->m_fortsTradingSessionStatus->Append(count);
	}
	inline void AllocateNewsNewsTextItemInfoPoolTo(int count) {
		count -= this->m_fortsNewsNewsTextItems->Capacity();
		if(count > 0)
			this->m_fortsNewsNewsTextItems->Append(count);
	}
	inline void AllocateNewsInfoPoolTo(int count) {
		count -= this->m_fortsNews->Capacity();
		if(count > 0)
			this->m_fortsNews->Append(count);
	}
	inline void AllocateOrdersLogMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_fortsOrdersLogMDEntriesItems->Capacity();
		if(count > 0)
			this->m_fortsOrdersLogMDEntriesItems->Append(count);
	}
	inline void AllocateOrdersLogInfoPoolTo(int count) {
		count -= this->m_fortsOrdersLog->Capacity();
		if(count > 0)
			this->m_fortsOrdersLog->Append(count);
	}
	inline void AllocateOrdersBookMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_fortsOrdersBookMDEntriesItems->Capacity();
		if(count > 0)
			this->m_fortsOrdersBookMDEntriesItems->Append(count);
	}
	inline void AllocateOrdersBookInfoPoolTo(int count) {
		count -= this->m_fortsOrdersBook->Capacity();
		if(count > 0)
			this->m_fortsOrdersBook->Append(count);
	}
	inline void AllocateLogonInfoPoolTo(int count) {
		count -= this->m_fortsLogon->Capacity();
		if(count > 0)
			this->m_fortsLogon->Append(count);
	}
	inline void AllocateLogoutInfoPoolTo(int count) {
		count -= this->m_fortsLogout->Capacity();
		if(count > 0)
			this->m_fortsLogout->Append(count);
	}
	inline void AllocateDefaultIncrementalRefreshMessageInfoPoolTo(int count) {
		count -= this->m_fortsDefaultIncrementalRefreshMessage->Capacity();
		if(count > 0)
			this->m_fortsDefaultIncrementalRefreshMessage->Append(count);
	}
	inline AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>* GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool() {
		return this->m_fortsDefaultSnapshotMessageMDEntriesItems;
	}
	inline AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>* GetFortsDefaultSnapshotMessageInfoPool() {
		return this->m_fortsDefaultSnapshotMessage;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>* GetFortsSecurityDefinitionMDFeedTypesItemInfoPool() {
		return this->m_fortsSecurityDefinitionMDFeedTypesItems;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>* GetFortsSecurityDefinitionUnderlyingsItemInfoPool() {
		return this->m_fortsSecurityDefinitionUnderlyingsItems;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>* GetFortsSecurityDefinitionInstrumentLegsItemInfoPool() {
		return this->m_fortsSecurityDefinitionInstrumentLegsItems;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>* GetFortsSecurityDefinitionInstrumentAttributesItemInfoPool() {
		return this->m_fortsSecurityDefinitionInstrumentAttributesItems;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>* GetFortsSecurityDefinitionEvntGrpItemInfoPool() {
		return this->m_fortsSecurityDefinitionEvntGrpItems;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionInfo>* GetFortsSecurityDefinitionInfoPool() {
		return this->m_fortsSecurityDefinition;
	}
	inline AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>* GetFortsSecurityDefinitionUpdateReportInfoPool() {
		return this->m_fortsSecurityDefinitionUpdateReport;
	}
	inline AutoAllocatePointerList<FortsSecurityStatusInfo>* GetFortsSecurityStatusInfoPool() {
		return this->m_fortsSecurityStatus;
	}
	inline AutoAllocatePointerList<FortsHeartbeatInfo>* GetFortsHeartbeatInfoPool() {
		return this->m_fortsHeartbeat;
	}
	inline AutoAllocatePointerList<FortsSequenceResetInfo>* GetFortsSequenceResetInfoPool() {
		return this->m_fortsSequenceReset;
	}
	inline AutoAllocatePointerList<FortsTradingSessionStatusInfo>* GetFortsTradingSessionStatusInfoPool() {
		return this->m_fortsTradingSessionStatus;
	}
	inline AutoAllocatePointerList<FortsNewsNewsTextItemInfo>* GetFortsNewsNewsTextItemInfoPool() {
		return this->m_fortsNewsNewsTextItems;
	}
	inline AutoAllocatePointerList<FortsNewsInfo>* GetFortsNewsInfoPool() {
		return this->m_fortsNews;
	}
	inline AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>* GetFortsOrdersLogMDEntriesItemInfoPool() {
		return this->m_fortsOrdersLogMDEntriesItems;
	}
	inline AutoAllocatePointerList<FortsOrdersLogInfo>* GetFortsOrdersLogInfoPool() {
		return this->m_fortsOrdersLog;
	}
	inline AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>* GetFortsOrdersBookMDEntriesItemInfoPool() {
		return this->m_fortsOrdersBookMDEntriesItems;
	}
	inline AutoAllocatePointerList<FortsOrdersBookInfo>* GetFortsOrdersBookInfoPool() {
		return this->m_fortsOrdersBook;
	}
	inline AutoAllocatePointerList<FortsLogonInfo>* GetFortsLogonInfoPool() {
		return this->m_fortsLogon;
	}
	inline AutoAllocatePointerList<FortsLogoutInfo>* GetFortsLogoutInfoPool() {
		return this->m_fortsLogout;
	}
	inline AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>* GetFortsDefaultIncrementalRefreshMessageInfoPool() {
		return this->m_fortsDefaultIncrementalRefreshMessage;
	}
};
class FortsDefaultSnapshotMessageMDEntriesItemInfoNullIndices{
public:
	static const UINT64 ExchangeTradingSessionIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MarketDepthNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX3;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDPriceLevelNullIndex = NULL_MAP_INDEX6;
	static const UINT64 NumberOfOrdersNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntryTradeTypeNullIndex = NULL_MAP_INDEX8;
	static const UINT64 TrdTypeNullIndex = NULL_MAP_INDEX9;
	static const UINT64 MDFlagsNullIndex = NULL_MAP_INDEX10;
	static const UINT64 CurrencyNullIndex = NULL_MAP_INDEX11;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX12;
};
class FortsDefaultSnapshotMessageInfoNullIndices{
public:
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SecurityGroupNullIndex = NULL_MAP_INDEX3;
};
class FortsSecurityDefinitionMDFeedTypesItemInfoNullIndices{
public:
	static const UINT64 MarketDepthNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDBookTypeNullIndex = NULL_MAP_INDEX1;
};
class FortsSecurityDefinitionUnderlyingsItemInfoNullIndices{
public:
	static const UINT64 UnderlyingSecurityIDNullIndex = NULL_MAP_INDEX0;
};
class FortsSecurityDefinitionInfoNullIndices{
public:
	static const UINT64 SecurityDescNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityAltIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SecurityAltIDSourceNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SecurityTypeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 CFICodeNullIndex = NULL_MAP_INDEX4;
	static const UINT64 StrikePriceNullIndex = NULL_MAP_INDEX5;
	static const UINT64 ContractMultiplierNullIndex = NULL_MAP_INDEX6;
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX7;
	static const UINT64 CurrencyNullIndex = NULL_MAP_INDEX8;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX9;
	static const UINT64 ExchangeTradingSessionIDNullIndex = NULL_MAP_INDEX10;
	static const UINT64 VolatilityNullIndex = NULL_MAP_INDEX11;
	static const UINT64 UnderlyingsNullIndex = NULL_MAP_INDEX12;
	static const UINT64 HighLimitPxNullIndex = NULL_MAP_INDEX13;
	static const UINT64 LowLimitPxNullIndex = NULL_MAP_INDEX14;
	static const UINT64 MinPriceIncrementNullIndex = NULL_MAP_INDEX15;
	static const UINT64 MinPriceIncrementAmountNullIndex = NULL_MAP_INDEX16;
	static const UINT64 InitialMarginOnBuyNullIndex = NULL_MAP_INDEX17;
	static const UINT64 InitialMarginOnSellNullIndex = NULL_MAP_INDEX18;
	static const UINT64 InitialMarginSynteticNullIndex = NULL_MAP_INDEX19;
	static const UINT64 QuotationListNullIndex = NULL_MAP_INDEX20;
	static const UINT64 TheorPriceNullIndex = NULL_MAP_INDEX21;
	static const UINT64 TheorPriceLimitNullIndex = NULL_MAP_INDEX22;
	static const UINT64 InstrumentLegsNullIndex = NULL_MAP_INDEX23;
	static const UINT64 InstrumentAttributesNullIndex = NULL_MAP_INDEX24;
	static const UINT64 UnderlyingQtyNullIndex = NULL_MAP_INDEX25;
	static const UINT64 UnderlyingCurrencyNullIndex = NULL_MAP_INDEX26;
	static const UINT64 EvntGrpNullIndex = NULL_MAP_INDEX27;
	static const UINT64 MaturityDateNullIndex = NULL_MAP_INDEX28;
	static const UINT64 MaturityTimeNullIndex = NULL_MAP_INDEX29;
};
class FortsSecurityDefinitionUpdateReportInfoNullIndices{
public:
	static const UINT64 VolatilityNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TheorPriceNullIndex = NULL_MAP_INDEX1;
	static const UINT64 TheorPriceLimitNullIndex = NULL_MAP_INDEX2;
};
class FortsSecurityStatusInfoNullIndices{
public:
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX0;
	static const UINT64 HighLimitPxNullIndex = NULL_MAP_INDEX1;
	static const UINT64 LowLimitPxNullIndex = NULL_MAP_INDEX2;
	static const UINT64 InitialMarginOnBuyNullIndex = NULL_MAP_INDEX3;
	static const UINT64 InitialMarginOnSellNullIndex = NULL_MAP_INDEX4;
	static const UINT64 InitialMarginSynteticNullIndex = NULL_MAP_INDEX5;
};
class FortsTradingSessionStatusInfoNullIndices{
public:
	static const UINT64 TradSesIntermClearingStartTimeNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TradSesIntermClearingEndTimeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 ExchangeTradingSessionIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesEventNullIndex = NULL_MAP_INDEX3;
};
class FortsNewsInfoNullIndices{
public:
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX0;
	static const UINT64 NewsIdNullIndex = NULL_MAP_INDEX1;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX2;
	static const UINT64 LanguageCodeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 UrgencyNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MarketSegmentIDNullIndex = NULL_MAP_INDEX5;
};
class FortsOrdersLogMDEntriesItemInfoNullIndices{
public:
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX3;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX5;
	static const UINT64 LastPxNullIndex = NULL_MAP_INDEX6;
	static const UINT64 LastQtyNullIndex = NULL_MAP_INDEX7;
	static const UINT64 TradeIDNullIndex = NULL_MAP_INDEX8;
	static const UINT64 ExchangeTradingSessionIDNullIndex = NULL_MAP_INDEX9;
	static const UINT64 MDFlagsNullIndex = NULL_MAP_INDEX10;
	static const UINT64 RevisionNullIndex = NULL_MAP_INDEX11;
};
class FortsOrdersBookMDEntriesItemInfoNullIndices{
public:
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradeIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDFlagsNullIndex = NULL_MAP_INDEX5;
};
class FortsOrdersBookInfoNullIndices{
public:
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX1;
};
class FortsLogoutInfoNullIndices{
public:
	static const UINT64 TextNullIndex = NULL_MAP_INDEX0;
};
class FortsDefaultIncrementalRefreshMessageMDEntriesItemInfoNullIndices{
public:
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SecurityGroupNullIndex = NULL_MAP_INDEX2;
	static const UINT64 ExchangeTradingSessionIDNullIndex = NULL_MAP_INDEX3;
	static const UINT64 MarketDepthNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDPriceLevelNullIndex = NULL_MAP_INDEX5;
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX6;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX7;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX8;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX9;
	static const UINT64 NumberOfOrdersNullIndex = NULL_MAP_INDEX10;
	static const UINT64 MDEntryTradeTypeNullIndex = NULL_MAP_INDEX11;
	static const UINT64 TrdTypeNullIndex = NULL_MAP_INDEX12;
	static const UINT64 LastPxNullIndex = NULL_MAP_INDEX13;
	static const UINT64 MDFlagsNullIndex = NULL_MAP_INDEX14;
	static const UINT64 CurrencyNullIndex = NULL_MAP_INDEX15;
	static const UINT64 RevisionNullIndex = NULL_MAP_INDEX16;
	static const UINT64 OrderSideNullIndex = NULL_MAP_INDEX17;
};
class FortsDefaultIncrementalRefreshMessageInfoNullIndices{
public:
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX0;
};
#pragma endregion

#endif //HFT_ROBOT_FASTTYPES_H
