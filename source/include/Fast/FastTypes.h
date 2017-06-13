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
#include <immintrin.h>
#include <x86intrin.h>

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
	UINT64							PresenceMap;
	UINT64							NullMap;
	UINT32							TemplateId;
	INT32							RptSeq; // offset = 20
	UINT32							LastFragment; // offset = 24
	UINT32							RouteFirst; // offset = 28
	UINT32							LastMsgSeqNumProcessed; // offset = 32
	char							PaddingBytes0[12];
	char							Symbol[16] __attribute__((aligned(16))); // offset = 48
	int								SymbolLength; // offset = 64
	char							TradingSessionID[4]; // offset = 68
	char							PaddingBytes1[8];
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
	int								TargetCompIDLength;			// id=56   offset = 0 order =  0
	char							TargetCompID[32];			// id=56   offset = 4 order =  0
	INT32							HeartBtInt;			// id=108   offset = 36 order =  0
	int								UsernameLength;			// id=553  presence=optional   offset = 40 order =  0
	char							Username[16];			// id=553  presence=optional   offset = 44 order =  0
	int								PasswordLength;			// id=554  presence=optional   offset = 60 order =  0
	char							Password[16];			// id=554  presence=optional   offset = 64 order =  0
	int								DefaultApplVerIDLength;			// id=1137   offset = 80 order =  0
	char							DefaultApplVerID[16];			// id=1137   offset = 84 order =  0
	int								MessageTypeLength;			// id=35    constant has constant value = A offset = 100 order =  999
	char							MessageType[16];			// id=35    constant has constant value = A offset = 104 order =  999
	int								BeginStringLength;			// id=8    constant has constant value = FIXT.1.1 offset = 120 order =  999
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1 offset = 124 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 140 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 144 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 176 order =  999
	char							PaddingBytes0[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 184 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsLogonInfo>							*Pointer;
	AutoAllocatePointerList<AstsLogonInfo>							*Allocator;

	AstsLogonInfo() {
		memset(this, 0, sizeof(AstsLogonInfo));
	}
	~AstsLogonInfo() { }
	inline void Assign(AstsLogonInfo *item) {
		// size = 192
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 12; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsLogoutInfo{
public:
	int								TargetCompIDLength;			// id=56   offset = 0 order =  0
	char							TargetCompID[32];			// id=56   offset = 4 order =  0
	int								TextLength;			// id=58  presence=optional   offset = 36 order =  0
	char							Text[512];			// id=58  presence=optional   offset = 40 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 552 order =  999
	char							PaddingBytes0[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 560 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsLogoutInfo>							*Pointer;
	AutoAllocatePointerList<AstsLogoutInfo>							*Allocator;
	char							PaddingBytes1[8];

	AstsLogoutInfo() {
		memset(this, 0, sizeof(AstsLogoutInfo));
	}
	~AstsLogoutInfo() { }
	inline void Assign(AstsLogoutInfo *item) {
		// size = 568
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 36; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsGenericItemInfo{
public:
	char							MDEntryType[4];			// id=269  presence=optional  fixed_size=1   offset = 0 order =  0
	int								MDEntryIDLength;			// id=278  presence=optional  predict=Max8   offset = 4 order =  0
	char							MDEntryID[16];			// id=278  presence=optional  predict=Max8   offset = 8 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional   offset = 24 order =  0
	UINT32							MDEntryTime;			// id=273  presence=optional   offset = 28 order =  0
	UINT32							OrigTime;			// id=9412  presence=optional   offset = 32 order =  0
	char							PaddingBytes0[4];
	Decimal							MDEntryPx;			// id=270  presence=optional   offset = 40 order =  0
	Decimal							MDEntrySize;			// id=271  presence=optional   offset = 56 order =  0
	int								QuoteConditionLength;			// id=276  presence=optional   offset = 72 order =  0
	char							QuoteCondition[16];			// id=276  presence=optional   offset = 76 order =  0
	int								TradeConditionLength;			// id=277  presence=optional   offset = 92 order =  0
	char							TradeCondition[16];			// id=277  presence=optional   offset = 96 order =  0
	int								OpenCloseSettlFlagLength;			// id=286  presence=optional   offset = 112 order =  0
	char							OpenCloseSettlFlag[4];			// id=286  presence=optional   offset = 116 order =  0
	char							OrdType[4];			// id=40  fixed_size=1  presence=optional   offset = 120 order =  0
	UINT32							EffectiveTime;			// id=5902  presence=optional   offset = 124 order =  0
	UINT32							StartTime;			// id=9820  presence=optional   offset = 128 order =  0
	char							PaddingBytes1[4];
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional   offset = 136 order =  0
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional   offset = 152 order =  0
	Decimal							ChgOpenInterest;			// id=5511  presence=optional   offset = 168 order =  0
	Decimal							BidMarketSize;			// id=5292  presence=optional   offset = 184 order =  0
	Decimal							AskMarketSize;			// id=5293  presence=optional   offset = 200 order =  0
	INT32							TotalNumOfTrades;			// id=6139  presence=optional   offset = 216 order =  0
	char							PaddingBytes2[4];
	Decimal							TradeValue;			// id=6143  presence=optional   offset = 224 order =  0
	Decimal							Yield;			// id=236  presence=optional   offset = 240 order =  0
	Decimal							TotalVolume;			// id=5791  presence=optional   offset = 256 order =  0
	INT32							OfferNbOr;			// id=9168  presence=optional   offset = 272 order =  0
	INT32							BidNbOr;			// id=9169  presence=optional   offset = 276 order =  0
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional   offset = 280 order =  0
	UINT32							SettlDate;			// id=64  presence=optional   offset = 296 order =  0
	int								SettleTypeLength;			// id=5459  presence=optional   offset = 300 order =  0
	char							SettleType[16];			// id=5459  presence=optional   offset = 304 order =  0
	INT32							SumQtyOfBest;			// id=10503  presence=optional   offset = 320 order =  0
	int								OrderSideLength;			// id=10504  presence=optional   offset = 324 order =  0
	char							OrderSide[4];			// id=10504  presence=optional   offset = 328 order =  0
	char							OrderStatus[4];			// id=10505  presence=optional  fixed_size=1   offset = 332 order =  0
	Decimal							MinCurrPx;			// id=10509  presence=optional   offset = 336 order =  0
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional   offset = 352 order =  0
	UINT32							VolumeIndicator;			// id=7017  presence=optional   offset = 356 order =  0
	Decimal							Price;			// id=44  presence=optional   offset = 360 order =  0
	INT32							PriceType;			// id=423  presence=optional   offset = 376 order =  0
	char							PaddingBytes3[4];
	Decimal							NominalValue;			// id=9280  presence=optional   offset = 384 order =  0
	Decimal							RepoToPx;			// id=5677  presence=optional   offset = 400 order =  0
	Decimal							BuyBackPx;			// id=5558  presence=optional   offset = 416 order =  0
	UINT32							BuyBackDate;			// id=5559  presence=optional   offset = 432 order =  0
	int								CXFlagLength;			// id=5154  presence=optional   offset = 436 order =  0
	char							CXFlag[4];			// id=5154  presence=optional   offset = 440 order =  0
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12   offset = 444 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12   offset = 448 order =  0
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1   offset = 452 order =  0
	INT32							RptSeq;			// id=83  presence=optional   offset = 456 order =  0
	int								SymbolLength;			// id=55  aligned=16  predict=Max16  presence=optional   offset = 460 order =  0
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16  presence=optional   offset = 464 order =  0
	Decimal							NetChgPrevDay;			// id=451  presence=optional   offset = 480 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 496 order =  0
		UINT32		TradingSessionIDUint;
	};
	char							PaddingBytes4[4];
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsGenericItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsGenericItemInfo>							*Allocator;
	char							PaddingBytes5[8];

	AstsGenericItemInfo() {
		memset(this, 0, sizeof(AstsGenericItemInfo));
	}
	~AstsGenericItemInfo() { }
	inline void Assign(AstsGenericItemInfo *item) {
		// size = 504
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 32; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsGenericInfo{
public:
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 0 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								SymbolLength;			// id=55  aligned=16  predict=Max16   offset = 4 order =  0
	char							PaddingBytes0[8];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16   offset = 16 order =  0
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional   offset = 32 order =  0
	INT32							RptSeq;			// id=83   offset = 36 order =  0
	UINT32							LastFragment;			// id=893  presence=optional   offset = 40 order =  0
	UINT32							RouteFirst;			// id=7944  presence=optional   offset = 44 order =  0
	INT32							TradSesStatus;			// id=340  presence=optional   offset = 48 order =  0
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional   offset = 52 order =  0
	UINT32							AuctionIndicator;			// id=5509  presence=optional   offset = 56 order =  0
	char							PaddingBytes1[4];
	Decimal							NetChgPrevDay;			// id=451  presence=optional   offset = 64 order =  0
	int								GroupMDEntriesCount;//		 offset = 80 order =  0
	char							PaddingBytes2[4];
	AstsGenericItemInfo* GroupMDEntries[256];//		 offset = 88 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2136 order =  999
	char							PaddingBytes3[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2144 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsGenericInfo>							*Pointer;
	AutoAllocatePointerList<AstsGenericInfo>							*Allocator;
	char							PaddingBytes4[8];

	AstsGenericInfo() {
		memset(this, 0, sizeof(AstsGenericInfo));
	}
	~AstsGenericInfo() { }
	inline void Assign(AstsGenericInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 80 order =  0
		// size = 2152
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 135; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsOLSFONDItemInfo{
public:
	char							MDEntryType[4];			// id=269  presence=optional  fixed_size=1    copy offset = 0 order =  0
	int								MDEntryIDLength;			// id=278  presence=optional  predict=Max8   offset = 4 order =  0
	char							MDEntryID[16];			// id=278  presence=optional  predict=Max8   offset = 8 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional    copy offset = 24 order =  0
	UINT32							MDEntryTime;			// id=273  presence=optional    copy offset = 28 order =  0
	UINT32							OrigTime;			// id=9412  presence=optional    copy offset = 32 order =  0
	char							PaddingBytes0[4];
	Decimal							MDEntryPx;			// id=270  presence=optional    copy offset = 40 order =  0
	Decimal							MDEntrySize;			// id=271  presence=optional    copy offset = 56 order =  0
	Decimal							Yield;			// id=236  presence=optional    copy offset = 72 order =  0
	char							OrderStatus[4];			// id=10505  presence=optional  fixed_size=1    copy offset = 88 order =  0
	char							OrdType[4];			// id=40  fixed_size=1  presence=optional    copy offset = 92 order =  0
	Decimal							TotalVolume;			// id=5791  presence=optional    copy offset = 96 order =  0
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12    copy offset = 112 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12    copy offset = 116 order =  0
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1   offset = 120 order =  0
	int								SymbolLength;			// id=55  aligned=16  predict=Max16  presence=optional    copy offset = 124 order =  0
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16  presence=optional    copy offset = 128 order =  0
	INT32							RptSeq;			// id=83  presence=optional   offset = 144 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional    copy offset = 148 order =  0
		UINT32		TradingSessionIDUint;
	};
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSFONDItemInfo>							*Allocator;
	char							PaddingBytes1[8];

	AstsOLSFONDItemInfo() {
		memset(this, 0, sizeof(AstsOLSFONDItemInfo));
	}
	~AstsOLSFONDItemInfo() { }
	inline void Assign(AstsOLSFONDItemInfo *item) {
		// size = 152
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 10; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsOLSFONDInfo{
public:
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional   offset = 0 order =  0
	INT32							RptSeq;			// id=83   offset = 4 order =  0
	UINT32							LastFragment;			// id=893  presence=optional   offset = 8 order =  0
	UINT32							RouteFirst;			// id=7944  presence=optional   offset = 12 order =  0
	INT32							TradSesStatus;			// id=340  presence=optional   offset = 16 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 20 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								SymbolLength;			// id=55  aligned=16  predict=Max16   offset = 24 order =  0
	char							PaddingBytes0[4];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16   offset = 32 order =  0
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional   offset = 48 order =  0
	UINT32							AuctionIndicator;			// id=5509  presence=optional   offset = 52 order =  0
	int								GroupMDEntriesCount;//		 offset = 56 order =  0
	char							PaddingBytes1[4];
	AstsOLSFONDItemInfo* GroupMDEntries[256];//		 offset = 64 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2112 order =  999
	char							PaddingBytes2[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2120 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSFONDInfo>							*Allocator;

	AstsOLSFONDInfo() {
		memset(this, 0, sizeof(AstsOLSFONDInfo));
	}
	~AstsOLSFONDInfo() { }
	inline void Assign(AstsOLSFONDInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 56 order =  0
		// size = 2128
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 133; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsOLSCURRItemInfo{
public:
	char							MDEntryType[4];			// id=269  presence=optional  fixed_size=1    copy offset = 0 order =  0
	int								MDEntryIDLength;			// id=278  presence=optional  predict=Max8   offset = 4 order =  0
	char							MDEntryID[16];			// id=278  presence=optional  predict=Max8   offset = 8 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional    copy offset = 24 order =  0
	UINT32							MDEntryTime;			// id=273  presence=optional    copy offset = 28 order =  0
	UINT32							OrigTime;			// id=9412  presence=optional    copy offset = 32 order =  0
	char							PaddingBytes0[4];
	Decimal							MDEntryPx;			// id=270  presence=optional    copy offset = 40 order =  0
	Decimal							MDEntrySize;			// id=271  presence=optional    copy offset = 56 order =  0
	char							OrderStatus[4];			// id=10505  presence=optional  fixed_size=1    copy offset = 72 order =  0
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12    copy offset = 76 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12    copy offset = 80 order =  0
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1    copy offset = 84 order =  0
	int								SymbolLength;			// id=55  aligned=16  predict=Max16  presence=optional    copy offset = 88 order =  0
	char							PaddingBytes1[4];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16  presence=optional    copy offset = 96 order =  0
	INT32							RptSeq;			// id=83  presence=optional   offset = 112 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional    copy offset = 116 order =  0
		UINT32		TradingSessionIDUint;
	};
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSCURRItemInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsOLSCURRItemInfo() {
		memset(this, 0, sizeof(AstsOLSCURRItemInfo));
	}
	~AstsOLSCURRItemInfo() { }
	inline void Assign(AstsOLSCURRItemInfo *item) {
		// size = 120
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 8; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsOLSCURRInfo{
public:
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional   offset = 0 order =  0
	INT32							RptSeq;			// id=83   offset = 4 order =  0
	UINT32							LastFragment;			// id=893  presence=optional   offset = 8 order =  0
	UINT32							RouteFirst;			// id=7944  presence=optional   offset = 12 order =  0
	INT32							TradSesStatus;			// id=340  presence=optional   offset = 16 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 20 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								SymbolLength;			// id=55  aligned=16  predict=Max16   offset = 24 order =  0
	char							PaddingBytes0[4];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16   offset = 32 order =  0
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional   offset = 48 order =  0
	int								GroupMDEntriesCount;//		 offset = 52 order =  0
	AstsOLSCURRItemInfo* GroupMDEntries[256];//		 offset = 56 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2104 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2112 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsOLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsOLSCURRInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsOLSCURRInfo() {
		memset(this, 0, sizeof(AstsOLSCURRInfo));
	}
	~AstsOLSCURRInfo() { }
	inline void Assign(AstsOLSCURRInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 52 order =  0
		// size = 2120
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 133; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsTLSFONDItemInfo{
public:
	char							MDEntryType[4];			// id=269  fixed_size=1   offset = 0 order =  0
	int								MDEntryIDLength;			// id=278  presence=optional  predict=Max8   offset = 4 order =  0
	char							MDEntryID[16];			// id=278  presence=optional  predict=Max8   offset = 8 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional    copy offset = 24 order =  0
	UINT32							MDEntryTime;			// id=273  presence=optional    copy offset = 28 order =  0
	UINT32							OrigTime;			// id=9412  presence=optional    copy offset = 32 order =  0
	int								OrderSideLength;			// id=10504  presence=optional    copy offset = 36 order =  0
	char							OrderSide[4];			// id=10504  presence=optional    copy offset = 40 order =  0
	char							PaddingBytes0[4];
	Decimal							MDEntryPx;			// id=270  presence=optional    copy offset = 48 order =  0
	Decimal							MDEntrySize;			// id=271  presence=optional    copy offset = 64 order =  0
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional    copy offset = 80 order =  0
	Decimal							TradeValue;			// id=6143  presence=optional    copy offset = 96 order =  0
	Decimal							Yield;			// id=236  presence=optional    copy offset = 112 order =  0
	UINT32							SettlDate;			// id=64  presence=optional    copy offset = 128 order =  0
	int								SettleTypeLength;			// id=5459  presence=optional    copy offset = 132 order =  0
	char							SettleType[16];			// id=5459  presence=optional    copy offset = 136 order =  0
	Decimal							Price;			// id=44  presence=optional    copy offset = 152 order =  0
	INT32							PriceType;			// id=423  presence=optional    copy offset = 168 order =  0
	char							PaddingBytes1[4];
	Decimal							RepoToPx;			// id=5677  presence=optional    copy offset = 176 order =  0
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy offset = 192 order =  0
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy offset = 208 order =  0
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12    copy offset = 212 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12    copy offset = 216 order =  0
	int								RefOrderIDLength;			// id=1080  presence=optional    copy offset = 220 order =  0
	char							RefOrderID[16];			// id=1080  presence=optional    copy offset = 224 order =  0
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1   offset = 240 order =  0
	int								SymbolLength;			// id=55  aligned=16  predict=Max16  presence=optional   offset = 244 order =  0
	char							PaddingBytes2[8];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16  presence=optional   offset = 256 order =  0
	INT32							RptSeq;			// id=83  presence=optional   offset = 272 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 276 order =  0
		UINT32		TradingSessionIDUint;
	};
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSFONDItemInfo>							*Allocator;
	char							PaddingBytes3[8];

	AstsTLSFONDItemInfo() {
		memset(this, 0, sizeof(AstsTLSFONDItemInfo));
	}
	~AstsTLSFONDItemInfo() { }
	inline void Assign(AstsTLSFONDItemInfo *item) {
		// size = 280
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 18; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsTLSFONDInfo{
public:
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional   offset = 0 order =  0
	INT32							RptSeq;			// id=83   offset = 4 order =  0
	UINT32							LastFragment;			// id=893  presence=optional   offset = 8 order =  0
	UINT32							RouteFirst;			// id=7944  presence=optional   offset = 12 order =  0
	INT32							TradSesStatus;			// id=340  presence=optional   offset = 16 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 20 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								SymbolLength;			// id=55  aligned=16  predict=Max16   offset = 24 order =  0
	char							PaddingBytes0[4];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16   offset = 32 order =  0
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional   offset = 48 order =  0
	UINT32							AuctionIndicator;			// id=5509  presence=optional   offset = 52 order =  0
	int								GroupMDEntriesCount;//		 offset = 56 order =  0
	char							PaddingBytes1[4];
	AstsTLSFONDItemInfo* GroupMDEntries[256];//		 offset = 64 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2112 order =  999
	char							PaddingBytes2[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2120 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSFONDInfo>							*Allocator;

	AstsTLSFONDInfo() {
		memset(this, 0, sizeof(AstsTLSFONDInfo));
	}
	~AstsTLSFONDInfo() { }
	inline void Assign(AstsTLSFONDInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 56 order =  0
		// size = 2128
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 133; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsTLSCURRItemInfo{
public:
	char							MDEntryType[4];			// id=269  fixed_size=1   offset = 0 order =  0
	int								MDEntryIDLength;			// id=278  presence=optional  predict=Max8   offset = 4 order =  0
	char							MDEntryID[16];			// id=278  presence=optional  predict=Max8   offset = 8 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional    copy offset = 24 order =  0
	UINT32							MDEntryTime;			// id=273  presence=optional    copy offset = 28 order =  0
	UINT32							OrigTime;			// id=9412  presence=optional    copy offset = 32 order =  0
	int								OrderSideLength;			// id=10504  presence=optional    copy offset = 36 order =  0
	char							OrderSide[4];			// id=10504  presence=optional    copy offset = 40 order =  0
	char							PaddingBytes0[4];
	Decimal							MDEntryPx;			// id=270  presence=optional    copy offset = 48 order =  0
	Decimal							MDEntrySize;			// id=271  presence=optional    copy offset = 64 order =  0
	Decimal							TradeValue;			// id=6143  presence=optional    copy offset = 80 order =  0
	UINT32							SettlDate;			// id=64  presence=optional    copy offset = 96 order =  0
	int								SettleTypeLength;			// id=5459  presence=optional    copy offset = 100 order =  0
	char							SettleType[16];			// id=5459  presence=optional    copy offset = 104 order =  0
	Decimal							Price;			// id=44  presence=optional    copy offset = 120 order =  0
	INT32							PriceType;			// id=423  presence=optional    copy offset = 136 order =  0
	char							PaddingBytes1[4];
	Decimal							RepoToPx;			// id=5677  presence=optional    copy offset = 144 order =  0
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy offset = 160 order =  0
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy offset = 176 order =  0
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12    copy offset = 180 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12    copy offset = 184 order =  0
	int								RefOrderIDLength;			// id=1080  presence=optional    copy offset = 188 order =  0
	char							RefOrderID[16];			// id=1080  presence=optional    copy offset = 192 order =  0
	UINT32							MDUpdateAction;			// id=279  presence=optional  fixed_size=1   offset = 208 order =  0
	int								SymbolLength;			// id=55  aligned=16  predict=Max16  presence=optional   offset = 212 order =  0
	char							PaddingBytes2[8];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16  presence=optional   offset = 224 order =  0
	INT32							RptSeq;			// id=83  presence=optional   offset = 240 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 244 order =  0
		UINT32		TradingSessionIDUint;
	};
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSCURRItemInfo>							*Allocator;
	char							PaddingBytes3[8];

	AstsTLSCURRItemInfo() {
		memset(this, 0, sizeof(AstsTLSCURRItemInfo));
	}
	~AstsTLSCURRItemInfo() { }
	inline void Assign(AstsTLSCURRItemInfo *item) {
		// size = 248
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 16; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsTLSCURRInfo{
public:
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional   offset = 0 order =  0
	INT32							RptSeq;			// id=83   offset = 4 order =  0
	UINT32							LastFragment;			// id=893  presence=optional   offset = 8 order =  0
	UINT32							RouteFirst;			// id=7944  presence=optional   offset = 12 order =  0
	INT32							TradSesStatus;			// id=340  presence=optional   offset = 16 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 20 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								SymbolLength;			// id=55  aligned=16  predict=Max16   offset = 24 order =  0
	char							PaddingBytes0[4];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16   offset = 32 order =  0
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional   offset = 48 order =  0
	int								GroupMDEntriesCount;//		 offset = 52 order =  0
	AstsTLSCURRItemInfo* GroupMDEntries[256];//		 offset = 56 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2104 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2112 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsTLSCURRInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsTLSCURRInfo() {
		memset(this, 0, sizeof(AstsTLSCURRInfo));
	}
	~AstsTLSCURRInfo() { }
	inline void Assign(AstsTLSCURRInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 52 order =  0
		// size = 2120
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 133; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsSecurityDefinitionGroupInstrAttribItemInfo{
public:
	INT32							InstrAttribType;			// id=871   offset = 0 order =  0
	int								InstrAttribValueLength;			// id=872  presence=optional   offset = 4 order =  0
	unsigned char							InstrAttribValue[128];			// id=872  presence=optional   offset = 8
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionGroupInstrAttribItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>							*Allocator;
	char							PaddingBytes0[8];

	AstsSecurityDefinitionGroupInstrAttribItemInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionGroupInstrAttribItemInfo));
	}
	~AstsSecurityDefinitionGroupInstrAttribItemInfo() { }
	inline void Assign(AstsSecurityDefinitionGroupInstrAttribItemInfo *item) {
		// size = 24
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 2; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo{
public:
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4   offset = 0 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12   offset = 4 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12   offset = 8 order =  0
	INT32							SecurityTradingStatus;			// id=326  presence=optional   offset = 12 order =  0
	INT32							OrderNote;			// id=9680  presence=optional   offset = 16 order =  0
	char							PaddingBytes0[4];
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Allocator;
	char							PaddingBytes1[8];

	AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo));
	}
	~AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() { }
	inline void Assign(AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *item) {
		// size = 24
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 2; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsSecurityDefinitionMarketSegmentGrpItemInfo{
public:
	Decimal							RoundLot;			// id=561  presence=optional   offset = 0 order =  0
	int								TradingSessionRulesGrpCount;//		 offset = 16 order =  0
	char							PaddingBytes0[4];
	AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* TradingSessionRulesGrp[16];			// presence=optional  max_count=16  //		 offset = 24 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionMarketSegmentGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>							*Allocator;
	char							PaddingBytes1[8];

	AstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionMarketSegmentGrpItemInfo));
	}
	~AstsSecurityDefinitionMarketSegmentGrpItemInfo() { }
	inline void Assign(AstsSecurityDefinitionMarketSegmentGrpItemInfo *item) {
	int								TradingSessionRulesGrpCount;//		 offset = 16 order =  0
		// size = 152
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 10; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->ReleaseUnused();
	}
};

class AstsSecurityDefinitionInfo{
public:
	int								MessageEncodingLength;			// id=347    default offset = 0 order =  0
	char							MessageEncoding[16];			// id=347    default offset = 4 order =  0
	INT32							TotNumReports;			// id=911  presence=optional   offset = 20 order =  0
	int								SymbolLength;			// id=55  aligned=16  predict=Max16  presence=optional   offset = 24 order =  0
	char							PaddingBytes0[4];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16  presence=optional   offset = 32 order =  0
	int								SecurityIDLength;			// id=48  presence=optional   offset = 48 order =  0
	unsigned char							SecurityID[128];			// id=48  presence=optional   offset = 52
	int								SecurityIDSourceLength;			// id=22  presence=optional   offset = 68 order =  0
	unsigned char							SecurityIDSource[128];			// id=22  presence=optional   offset = 72
	INT32							Product;			// id=460  presence=optional   offset = 88 order =  0
	int								CFICodeLength;			// id=461  presence=optional   offset = 92 order =  0
	unsigned char							CFICode[128];			// id=461  presence=optional   offset = 96
	int								SecurityTypeLength;			// id=167  presence=optional   offset = 112 order =  0
	unsigned char							SecurityType[128];			// id=167  presence=optional   offset = 116
	UINT32							MaturityDate;			// id=541  presence=optional   offset = 132 order =  0
	UINT32							SettlDate;			// id=64  presence=optional   offset = 136 order =  0
	int								SettleTypeLength;			// id=5459  presence=optional   offset = 140 order =  0
	char							SettleType[16];			// id=5459  presence=optional   offset = 144 order =  0
	Decimal							OrigIssueAmt;			// id=5850  presence=optional   offset = 160 order =  0
	UINT32							CouponPaymentDate;			// id=224  presence=optional   offset = 176 order =  0
	char							PaddingBytes1[4];
	Decimal							CouponRate;			// id=223  presence=optional   offset = 184 order =  0
	UINT32							SettlFixingDate;			// id=9119  presence=optional   offset = 200 order =  0
	char							PaddingBytes2[4];
	Decimal							DividendNetPx;			// id=9982  presence=optional   offset = 208 order =  0
	int								SecurityDescLength;			// id=107  presence=optional   offset = 224 order =  0
	unsigned char							SecurityDesc[128];			// id=107  presence=optional   offset = 228
	int								EncodedSecurityDescLength;			// id=351  presence=optional   offset = 244 order =  0
	unsigned char							EncodedSecurityDesc[128];			// id=351  presence=optional   offset = 248
	int								QuoteTextLength;			// id=9696  presence=optional   offset = 264 order =  0
	unsigned char							QuoteText[128];			// id=9696  presence=optional   offset = 268
	int								GroupInstrAttribCount;//		 offset = 284 order =  0
	AstsSecurityDefinitionGroupInstrAttribItemInfo* GroupInstrAttrib[16];			// presence=optional  max_count=16  //		 offset = 288 order =  0
	int								CurrencyLength;			// id=15  presence=optional   offset = 416 order =  0
	char							Currency[4];			// id=15  presence=optional   offset = 420 order =  0
	int								MarketSegmentGrpCount;//		 offset = 424 order =  0
	char							PaddingBytes3[4];
	AstsSecurityDefinitionMarketSegmentGrpItemInfo* MarketSegmentGrp[16];			// presence=optional  max_count=16  //		 offset = 432 order =  0
	int								SettlCurrencyLength;			// id=120  presence=optional   offset = 560 order =  0
	char							SettlCurrency[16];			// id=120  presence=optional   offset = 564 order =  0
	INT32							PriceType;			// id=423  presence=optional   offset = 580 order =  0
	int								StateSecurityIDLength;			// id=5217  presence=optional   offset = 584 order =  0
	char							StateSecurityID[16];			// id=5217  presence=optional   offset = 588 order =  0
	int								EncodedShortSecurityDescLength;			// id=5383  presence=optional   offset = 604 order =  0
	unsigned char							EncodedShortSecurityDesc[128];			// id=5383  presence=optional   offset = 608
	int								MarketCodeLength;			// id=5385  presence=optional   offset = 624 order =  0
	unsigned char							MarketCode[128];			// id=5385  presence=optional   offset = 628
	char							PaddingBytes4[4];
	Decimal							MinPriceIncrement;			// id=969  presence=optional   offset = 648 order =  0
	Decimal							MktShareLimit;			// id=5387  presence=optional   offset = 664 order =  0
	Decimal							MktShareThreshold;			// id=5388  presence=optional   offset = 680 order =  0
	Decimal							MaxOrdersVolume;			// id=5389  presence=optional   offset = 696 order =  0
	Decimal							PriceMvmLimit;			// id=5470  presence=optional   offset = 712 order =  0
	Decimal							FaceValue;			// id=5508  presence=optional   offset = 728 order =  0
	Decimal							BaseSwapPx;			// id=5556  presence=optional   offset = 744 order =  0
	Decimal							RepoToPx;			// id=5677  presence=optional   offset = 760 order =  0
	Decimal							BuyBackPx;			// id=5558  presence=optional   offset = 776 order =  0
	UINT32							BuyBackDate;			// id=5559  presence=optional   offset = 792 order =  0
	char							PaddingBytes5[4];
	Decimal							NoSharesIssued;			// id=7595  presence=optional   offset = 800 order =  0
	Decimal							HighLimit;			// id=9199  presence=optional   offset = 816 order =  0
	Decimal							LowLimit;			// id=9200  presence=optional   offset = 832 order =  0
	INT32							NumOfDaysToMaturity;			// id=10508  presence=optional   offset = 848 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true    increment offset = 852 order =  999
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 856 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityDefinitionInfo>							*Allocator;

	AstsSecurityDefinitionInfo() {
		memset(this, 0, sizeof(AstsSecurityDefinitionInfo));
	}
	~AstsSecurityDefinitionInfo() { }
	inline void Assign(AstsSecurityDefinitionInfo *item) {
	int								GroupInstrAttribCount;//		 offset = 284 order =  0
	int								MarketSegmentGrpCount;//		 offset = 424 order =  0
		// size = 864
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 54; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->Clear();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->ReleaseUnused();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->ReleaseUnused();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->ReleaseUnused();
	}
};

class AstsSecurityStatusInfo{
public:
	int								SymbolLength;			// id=55  aligned=16  predict=Max16   offset = 0 order =  0
	char							PaddingBytes0[12];
	char							Symbol[16] __attribute__((aligned(16)));			// id=55  aligned=16  predict=Max16   offset = 16 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4  presence=optional   offset = 32 order =  0
		UINT32		TradingSessionIDUint;
	};
	int								TradingSessionSubIDLength;			// id=625  presence=optional  predict=12   offset = 36 order =  0
	char							TradingSessionSubID[4];			// id=625  presence=optional  predict=12   offset = 40 order =  0
	INT32							SecurityTradingStatus;			// id=326  presence=optional   offset = 44 order =  0
	UINT32							AuctionIndicator;			// id=5509  presence=optional   offset = 48 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 52 order =  999
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 56 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<AstsSecurityStatusInfo>							*Allocator;

	AstsSecurityStatusInfo() {
		memset(this, 0, sizeof(AstsSecurityStatusInfo));
	}
	~AstsSecurityStatusInfo() { }
	inline void Assign(AstsSecurityStatusInfo *item) {
		// size = 64
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 4; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
	}
	inline void ReleaseUnused() {

	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsTradingSessionStatusInfo{
public:
	INT32							TradSesStatus;			// id=340   offset = 0 order =  0
	int								TextLength;			// id=58  presence=optional   offset = 4 order =  0
	char							Text[512];			// id=58  presence=optional   offset = 8 order =  0
	union {
		char		TradingSessionID[4];			// id=336  fixed_size=4  union=uint32  size=4   offset = 520 order =  0
		UINT32		TradingSessionIDUint;
	};
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 524 order =  999
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 528 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<AstsTradingSessionStatusInfo>							*Allocator;
	char							PaddingBytes0[8];

	AstsTradingSessionStatusInfo() {
		memset(this, 0, sizeof(AstsTradingSessionStatusInfo));
	}
	~AstsTradingSessionStatusInfo() { }
	inline void Assign(AstsTradingSessionStatusInfo *item) {
		// size = 536
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 34; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
	}
	inline void ReleaseUnused() {

	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsHeartbeatInfo{
public:
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 0 order =  999
	char							PaddingBytes0[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 8 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<AstsHeartbeatInfo>							*Allocator;

	AstsHeartbeatInfo() {
		memset(this, 0, sizeof(AstsHeartbeatInfo));
	}
	~AstsHeartbeatInfo() { }
	inline void Assign(AstsHeartbeatInfo *item) {
		// size = 16
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 1; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
	}
	inline void ReleaseUnused() {

	}
	inline void ReleaseUnusedChildren() {
	}
};

class AstsIncrementalGenericInfo{
public:
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
	char							PaddingBytes0[4];
	AstsGenericItemInfo* GroupMDEntries[256];//		 offset = 8 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2056 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2064 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalGenericInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalGenericInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsIncrementalGenericInfo() {
		memset(this, 0, sizeof(AstsIncrementalGenericInfo));
	}
	~AstsIncrementalGenericInfo() { }
	inline void Assign(AstsIncrementalGenericInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
		// size = 2072
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalMSRFONDInfo{
public:
	UINT64							LastUpdateTime;			// id=779  presence=optional   offset = 0 order =  0
	int								GroupMDEntriesCount;//		 offset = 8 order =  0
	char							PaddingBytes0[4];
	AstsGenericItemInfo* GroupMDEntries[256];//		 offset = 16 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2064 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2072 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalMSRFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>							*Allocator;

	AstsIncrementalMSRFONDInfo() {
		memset(this, 0, sizeof(AstsIncrementalMSRFONDInfo));
	}
	~AstsIncrementalMSRFONDInfo() { }
	inline void Assign(AstsIncrementalMSRFONDInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 8 order =  0
		// size = 2080
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalMSRCURRInfo{
public:
	UINT64							LastUpdateTime;			// id=779  presence=optional   offset = 0 order =  0
	int								GroupMDEntriesCount;//		 offset = 8 order =  0
	char							PaddingBytes0[4];
	AstsGenericItemInfo* GroupMDEntries[256];//		 offset = 16 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2064 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2072 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalMSRCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>							*Allocator;

	AstsIncrementalMSRCURRInfo() {
		memset(this, 0, sizeof(AstsIncrementalMSRCURRInfo));
	}
	~AstsIncrementalMSRCURRInfo() { }
	inline void Assign(AstsIncrementalMSRCURRInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 8 order =  0
		// size = 2080
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalOLRFONDInfo{
public:
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
	char							PaddingBytes0[4];
	AstsOLSFONDItemInfo* GroupMDEntries[256];			// process_empty_pmap=true  //		 offset = 8 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2056 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2064 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalOLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsIncrementalOLRFONDInfo() {
		memset(this, 0, sizeof(AstsIncrementalOLRFONDInfo));
	}
	~AstsIncrementalOLRFONDInfo() { }
	inline void Assign(AstsIncrementalOLRFONDInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
		// size = 2072
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalOLRCURRInfo{
public:
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
	char							PaddingBytes0[4];
	AstsOLSCURRItemInfo* GroupMDEntries[256];			// process_empty_pmap=true  pmap1=6263  pmap2=30839  //		 offset = 8 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2056 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2064 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalOLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsIncrementalOLRCURRInfo() {
		memset(this, 0, sizeof(AstsIncrementalOLRCURRInfo));
	}
	~AstsIncrementalOLRCURRInfo() { }
	inline void Assign(AstsIncrementalOLRCURRInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
		// size = 2072
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalTLRFONDInfo{
public:
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
	char							PaddingBytes0[4];
	AstsTLSFONDItemInfo* GroupMDEntries[256];//		 offset = 8 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2056 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2064 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalTLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsIncrementalTLRFONDInfo() {
		memset(this, 0, sizeof(AstsIncrementalTLRFONDInfo));
	}
	~AstsIncrementalTLRFONDInfo() { }
	inline void Assign(AstsIncrementalTLRFONDInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
		// size = 2072
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class AstsIncrementalTLRCURRInfo{
public:
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
	char							PaddingBytes0[4];
	AstsTLSCURRItemInfo* GroupMDEntries[256];//		 offset = 8 order =  0
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2056 order =  999
	char							PaddingBytes1[4];
	UINT64							SendingTime;			// id=52  predict=9  skip=true   offset = 2064 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<AstsIncrementalTLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>							*Allocator;
	char							PaddingBytes2[8];

	AstsIncrementalTLRCURRInfo() {
		memset(this, 0, sizeof(AstsIncrementalTLRCURRInfo));
	}
	~AstsIncrementalTLRCURRInfo() { }
	inline void Assign(AstsIncrementalTLRCURRInfo *item) {
	int								GroupMDEntriesCount;//		 offset = 0 order =  0
		// size = 2072
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 130; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
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
class AstsPackedTemplateId {
public:
	static const UINT32 AstsLogonInfo = 0xb510;
	static const UINT32 AstsLogoutInfo = 0xb610;
	static const UINT32 AstsGenericInfo = 0xb710;
	static const UINT32 AstsOLSFONDInfo = 0xce13;
	static const UINT32 AstsOLSCURRInfo = 0x901c;
	static const UINT32 AstsTLSFONDInfo = 0xcf13;
	static const UINT32 AstsTLSCURRInfo = 0x911c;
	static const UINT32 AstsSecurityDefinitionInfo = 0xc310;
	static const UINT32 AstsSecurityStatusInfo = 0xba10;
	static const UINT32 AstsTradingSessionStatusInfo = 0xbb10;
	static const UINT32 AstsHeartbeatInfo = 0xbc10;
	static const UINT32 AstsIncrementalGenericInfo = 0xb810;
	static const UINT32 AstsIncrementalMSRFONDInfo = 0xdb13;
	static const UINT32 AstsIncrementalMSRCURRInfo = 0x9d1c;
	static const UINT32 AstsIncrementalOLRFONDInfo = 0xd813;
	static const UINT32 AstsIncrementalOLRCURRInfo = 0x9a1c;
	static const UINT32 AstsIncrementalTLRFONDInfo = 0xd913;
	static const UINT32 AstsIncrementalTLRCURRInfo = 0x9b1c;
};
#pragma endregion

#pragma region Forts_Message_Info_Structures_Definition_GeneratedCode
class FortsSnapshotInfo {
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	UINT32							TemplateId;
	UINT32							RptSeq; // offset = 20
	UINT32							LastFragment; // offset = 24
	UINT32							LastMsgSeqNumProcessed; // offset = 28
	UINT64							SecurityID; // offset = 32
	char							PaddingBytes0[8];
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
	int								MDEntryTypeLength;			// id=269   offset = 0 order =  0
	char							MDEntryType[4];			// id=269   offset = 4 order =  0
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional   offset = 8 order =  0
	char							PaddingBytes0[4];
	UINT64							MDEntryID;			// id=278  presence=optional   offset = 16 order =  0
	UINT32							MarketDepth;			// id=264  presence=optional   offset = 24 order =  0
	char							PaddingBytes1[4];
	Decimal							MDEntryPx;			// id=270  presence=optional   offset = 32 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional   offset = 48 order =  0
	char							PaddingBytes2[4];
	UINT64							MDEntryTime;			// id=273   offset = 56 order =  0
	UINT64							MDEntrySize;			// id=271  presence=optional   offset = 64 order =  0
	UINT32							MDPriceLevel;			// id=1023  presence=optional   offset = 72 order =  0
	INT32							NumberOfOrders;			// id=346  presence=optional   offset = 76 order =  0
	int								MDEntryTradeTypeLength;			// id=20003  presence=optional   offset = 80 order =  0
	char							MDEntryTradeType[4];			// id=20003  presence=optional   offset = 84 order =  0
	INT32							TrdType;			// id=828  presence=optional   offset = 88 order =  0
	INT32							MDFlags;			// id=20017  presence=optional   offset = 92 order =  0
	int								CurrencyLength;			// id=15  presence=optional   offset = 96 order =  0
	char							Currency[4];			// id=15  presence=optional   offset = 100 order =  0
	int								OrderSideLength;			// id=10504  presence=optional   offset = 104 order =  0
	char							OrderSide[4];			// id=10504  presence=optional   offset = 108 order =  0
	UINT32							MDUpdateAction;			// id=279   offset = 112 order =  0
	char							PaddingBytes3[4];
	UINT64							SecurityID;			// id=48  presence=optional   offset = 120 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 128 order =  0
	int								SymbolLength;			// id=55  presence=optional   offset = 132 order =  0
	char							Symbol[16];			// id=55  presence=optional   offset = 136 order =  0
	int								SecurityGroupLength;			// id=1151  presence=optional   offset = 152 order =  0
	char							SecurityGroup[16];			// id=1151  presence=optional   offset = 156 order =  0
	UINT32							RptSeq;			// id=83   offset = 172 order =  0
	Decimal							LastPx;			// id=31  presence=optional   offset = 176 order =  0
	UINT64							Revision;			// id=20018  presence=optional   offset = 192 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsDefaultSnapshotMessageMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>							*Allocator;
	char							PaddingBytes4[8];

	FortsDefaultSnapshotMessageMDEntriesItemInfo() {
		memset(this, 0, sizeof(FortsDefaultSnapshotMessageMDEntriesItemInfo));
	}
	~FortsDefaultSnapshotMessageMDEntriesItemInfo() { }
	inline void Assign(FortsDefaultSnapshotMessageMDEntriesItemInfo *item) {
		// size = 200
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 13; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsDefaultSnapshotMessageInfo{
public:
	UINT32							LastFragment;			// id=893  presence=optional   offset = 0 order =  0
	UINT32							RptSeq;			// id=83   offset = 4 order =  0
	UINT32							TotNumReports;			// id=911   offset = 8 order =  0
	UINT32							LastMsgSeqNumProcessed;			// id=369   offset = 12 order =  0
	UINT64							SecurityID;			// id=48  presence=optional   offset = 16 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 24 order =  0
	int								SymbolLength;			// id=55  presence=optional   offset = 28 order =  0
	char							Symbol[16];			// id=55  presence=optional   offset = 32 order =  0
	int								SecurityGroupLength;			// id=1151  presence=optional   offset = 48 order =  0
	char							SecurityGroup[16];			// id=1151  presence=optional   offset = 52 order =  0
	int								MDEntriesCount;//		 offset = 68 order =  0
	FortsDefaultSnapshotMessageMDEntriesItemInfo* MDEntries[256];//		 offset = 72 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 2120 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 2124 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = W offset = 2140 order =  999
	char							MessageType[16];			// id=35    constant has constant value = W offset = 2144 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 2160 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 2164 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2196 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 2200 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsDefaultSnapshotMessageInfo>							*Pointer;
	AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>							*Allocator;

	FortsDefaultSnapshotMessageInfo() {
		memset(this, 0, sizeof(FortsDefaultSnapshotMessageInfo));
	}
	~FortsDefaultSnapshotMessageInfo() { }
	inline void Assign(FortsDefaultSnapshotMessageInfo *item) {
	int								MDEntriesCount;//		 offset = 68 order =  0
		// size = 2208
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 138; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsSecurityDefinitionMDFeedTypesItemInfo{
public:
	int								MDFeedTypeLength;			// id=1022   offset = 0 order =  0
	char							MDFeedType[16];			// id=1022   offset = 4 order =  0
	UINT32							MarketDepth;			// id=264  presence=optional   offset = 20 order =  0
	UINT32							MDBookType;			// id=1021  presence=optional   offset = 24 order =  0
	char							PaddingBytes0[4];
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionMDFeedTypesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>							*Allocator;

	FortsSecurityDefinitionMDFeedTypesItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionMDFeedTypesItemInfo));
	}
	~FortsSecurityDefinitionMDFeedTypesItemInfo() { }
	inline void Assign(FortsSecurityDefinitionMDFeedTypesItemInfo *item) {
		// size = 32
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 2; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSecurityDefinitionUnderlyingsItemInfo{
public:
	int								UnderlyingSymbolLength;			// id=311   offset = 0 order =  0
	char							UnderlyingSymbol[16];			// id=311   offset = 4 order =  0
	char							PaddingBytes0[4];
	UINT64							UnderlyingSecurityID;			// id=309  presence=optional   offset = 24 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionUnderlyingsItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>							*Allocator;

	FortsSecurityDefinitionUnderlyingsItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionUnderlyingsItemInfo));
	}
	~FortsSecurityDefinitionUnderlyingsItemInfo() { }
	inline void Assign(FortsSecurityDefinitionUnderlyingsItemInfo *item) {
		// size = 32
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 2; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSecurityDefinitionInstrumentLegsItemInfo{
public:
	int								LegSymbolLength;			// id=600   offset = 0 order =  0
	char							LegSymbol[16];			// id=600   offset = 4 order =  0
	char							PaddingBytes0[4];
	UINT64							LegSecurityID;			// id=602   offset = 24 order =  0
	Decimal							LegRatioQty;			// id=623   offset = 32 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionInstrumentLegsItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>							*Allocator;

	FortsSecurityDefinitionInstrumentLegsItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionInstrumentLegsItemInfo));
	}
	~FortsSecurityDefinitionInstrumentLegsItemInfo() { }
	inline void Assign(FortsSecurityDefinitionInstrumentLegsItemInfo *item) {
		// size = 48
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 3; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSecurityDefinitionInstrumentAttributesItemInfo{
public:
	INT32							InstrAttribType;			// id=871   offset = 0 order =  0
	int								InstrAttribValueLength;			// id=872   offset = 4 order =  0
	char							InstrAttribValue[16];			// id=872   offset = 8 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionInstrumentAttributesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>							*Allocator;
	char							PaddingBytes0[8];

	FortsSecurityDefinitionInstrumentAttributesItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionInstrumentAttributesItemInfo));
	}
	~FortsSecurityDefinitionInstrumentAttributesItemInfo() { }
	inline void Assign(FortsSecurityDefinitionInstrumentAttributesItemInfo *item) {
		// size = 24
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 2; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSecurityDefinitionEvntGrpItemInfo{
public:
	INT32							EventType;			// id=865   offset = 0 order =  0
	UINT32							EventDate;			// id=866   offset = 4 order =  0
	UINT64							EventTime;			// id=1145   offset = 8 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionEvntGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>							*Allocator;

	FortsSecurityDefinitionEvntGrpItemInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionEvntGrpItemInfo));
	}
	~FortsSecurityDefinitionEvntGrpItemInfo() { }
	inline void Assign(FortsSecurityDefinitionEvntGrpItemInfo *item) {
		// size = 16
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 1; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSecurityDefinitionInfo{
public:
	UINT32							TotNumReports;			// id=911   offset = 0 order =  0
	int								SymbolLength;			// id=55   offset = 4 order =  0
	char							Symbol[16];			// id=55   offset = 8 order =  0
	int								SecurityDescLength;			// id=107  presence=optional  charset=unicode   offset = 24 order =  0
	unsigned char							SecurityDesc[128];			// id=107  presence=optional  charset=unicode   offset = 28
	char							PaddingBytes0[4];
	UINT64							SecurityID;			// id=48   offset = 48 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 56 order =  0
	int								SecurityAltIDLength;			// id=455  presence=optional   offset = 60 order =  0
	char							SecurityAltID[16];			// id=455  presence=optional   offset = 64 order =  0
	int								SecurityAltIDSourceLength;			// id=456  presence=optional   offset = 80 order =  0
	char							SecurityAltIDSource[16];			// id=456  presence=optional   offset = 84 order =  0
	int								SecurityTypeLength;			// id=167  presence=optional   offset = 100 order =  0
	char							SecurityType[16];			// id=167  presence=optional   offset = 104 order =  0
	int								CFICodeLength;			// id=461  presence=optional   offset = 120 order =  0
	char							CFICode[16];			// id=461  presence=optional   offset = 124 order =  0
	char							PaddingBytes1[4];
	Decimal							StrikePrice;			// id=202  presence=optional   offset = 144 order =  0
	Decimal							ContractMultiplier;			// id=231  presence=optional   offset = 160 order =  0
	UINT32							SecurityTradingStatus;			// id=326  presence=optional   offset = 176 order =  0
	int								CurrencyLength;			// id=15  presence=optional   offset = 180 order =  0
	char							Currency[4];			// id=15  presence=optional   offset = 184 order =  0
	int								MarketIDLength;			// id=1301    constant has constant value = MOEX offset = 188 order =  0
	char							MarketID[16];			// id=1301    constant has constant value = MOEX offset = 192 order =  0
	int								MarketSegmentIDLength;			// id=1300   offset = 208 order =  0
	char							MarketSegmentID[16];			// id=1300   offset = 212 order =  0
	UINT32							TradingSessionID;			// id=336  presence=optional   offset = 228 order =  0
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional   offset = 232 order =  0
	char							PaddingBytes2[4];
	Decimal							Volatility;			// id=5678  presence=optional   offset = 240 order =  0
	int								MDFeedTypesCount;//		 offset = 256 order =  0
	char							PaddingBytes3[4];
	FortsSecurityDefinitionMDFeedTypesItemInfo* MDFeedTypes[256];//		 offset = 264 order =  0
	int								UnderlyingsCount;//		 offset = 2312 order =  0
	char							PaddingBytes4[4];
	FortsSecurityDefinitionUnderlyingsItemInfo* Underlyings[256];			// presence=optional  //		 offset = 2320 order =  0
	Decimal							HighLimitPx;			// id=1149  presence=optional   offset = 4368 order =  0
	Decimal							LowLimitPx;			// id=1148  presence=optional   offset = 4384 order =  0
	Decimal							MinPriceIncrement;			// id=969  presence=optional   offset = 4400 order =  0
	Decimal							MinPriceIncrementAmount;			// id=1146  presence=optional   offset = 4416 order =  0
	Decimal							InitialMarginOnBuy;			// id=20002  presence=optional   offset = 4432 order =  0
	Decimal							InitialMarginOnSell;			// id=20000  presence=optional   offset = 4448 order =  0
	Decimal							InitialMarginSyntetic;			// id=20001  presence=optional   offset = 4464 order =  0
	int								QuotationListLength;			// id=20005  presence=optional   offset = 4480 order =  0
	char							QuotationList[16];			// id=20005  presence=optional   offset = 4484 order =  0
	char							PaddingBytes5[4];
	Decimal							TheorPrice;			// id=20006  presence=optional   offset = 4504 order =  0
	Decimal							TheorPriceLimit;			// id=20007  presence=optional   offset = 4520 order =  0
	int								InstrumentLegsCount;//		 offset = 4536 order =  0
	char							PaddingBytes6[4];
	FortsSecurityDefinitionInstrumentLegsItemInfo* InstrumentLegs[256];			// presence=optional  //		 offset = 4544 order =  0
	int								InstrumentAttributesCount;//		 offset = 6592 order =  0
	char							PaddingBytes7[4];
	FortsSecurityDefinitionInstrumentAttributesItemInfo* InstrumentAttributes[256];			// presence=optional  //		 offset = 6600 order =  0
	Decimal							UnderlyingQty;			// id=879  presence=optional   offset = 8648 order =  0
	int								UnderlyingCurrencyLength;			// id=318  presence=optional   offset = 8664 order =  0
	char							UnderlyingCurrency[16];			// id=318  presence=optional   offset = 8668 order =  0
	int								EvntGrpCount;//		 offset = 8684 order =  0
	FortsSecurityDefinitionEvntGrpItemInfo* EvntGrp[256];			// presence=optional  //		 offset = 8688 order =  0
	UINT32							MaturityDate;			// id=541  presence=optional   offset = 10736 order =  0
	UINT32							MaturityTime;			// id=1079  presence=optional   offset = 10740 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 10744 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 10748 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = d offset = 10764 order =  999
	char							MessageType[16];			// id=35    constant has constant value = d offset = 10768 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 10784 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 10788 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 10820 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 10824 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionInfo>							*Allocator;

	FortsSecurityDefinitionInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionInfo));
	}
	~FortsSecurityDefinitionInfo() { }
	inline void Assign(FortsSecurityDefinitionInfo *item) {
	int								MDFeedTypesCount;//		 offset = 256 order =  0
	int								UnderlyingsCount;//		 offset = 2312 order =  0
	int								InstrumentLegsCount;//		 offset = 4536 order =  0
	int								InstrumentAttributesCount;//		 offset = 6592 order =  0
	int								EvntGrpCount;//		 offset = 8684 order =  0
		// size = 10832
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 677; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
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

		this->Allocator->FreeItemUnsafe(this->Pointer);
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
	inline void ReleaseUnusedChildren() {
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
	UINT64							SecurityID;			// id=48   offset = 0 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 8 order =  0
	char							PaddingBytes0[4];
	Decimal							Volatility;			// id=5678  presence=optional   offset = 16 order =  0
	Decimal							TheorPrice;			// id=20006  presence=optional   offset = 32 order =  0
	Decimal							TheorPriceLimit;			// id=20007  presence=optional   offset = 48 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 64 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 68 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = BP offset = 84 order =  999
	char							MessageType[16];			// id=35    constant has constant value = BP offset = 88 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 104 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 108 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 140 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 144 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityDefinitionUpdateReportInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>							*Allocator;
	char							PaddingBytes1[8];

	FortsSecurityDefinitionUpdateReportInfo() {
		memset(this, 0, sizeof(FortsSecurityDefinitionUpdateReportInfo));
	}
	~FortsSecurityDefinitionUpdateReportInfo() { }
	inline void Assign(FortsSecurityDefinitionUpdateReportInfo *item) {
		// size = 152
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 10; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSecurityStatusInfo{
public:
	UINT64							SecurityID;			// id=48   offset = 0 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 8 order =  0
	int								SymbolLength;			// id=55   offset = 12 order =  0
	char							Symbol[16];			// id=55   offset = 16 order =  0
	UINT32							SecurityTradingStatus;			// id=326  presence=optional   offset = 32 order =  0
	char							PaddingBytes0[4];
	Decimal							HighLimitPx;			// id=1149  presence=optional   offset = 40 order =  0
	Decimal							LowLimitPx;			// id=1148  presence=optional   offset = 56 order =  0
	Decimal							InitialMarginOnBuy;			// id=20002  presence=optional   offset = 72 order =  0
	Decimal							InitialMarginOnSell;			// id=20000  presence=optional   offset = 88 order =  0
	Decimal							InitialMarginSyntetic;			// id=20001  presence=optional   offset = 104 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 120 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 124 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = f offset = 140 order =  999
	char							MessageType[16];			// id=35    constant has constant value = f offset = 144 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 160 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 164 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 196 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 200 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<FortsSecurityStatusInfo>							*Allocator;

	FortsSecurityStatusInfo() {
		memset(this, 0, sizeof(FortsSecurityStatusInfo));
	}
	~FortsSecurityStatusInfo() { }
	inline void Assign(FortsSecurityStatusInfo *item) {
		// size = 208
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 13; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsHeartbeatInfo{
public:
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 0 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 4 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = 0 offset = 20 order =  999
	char							MessageType[16];			// id=35    constant has constant value = 0 offset = 24 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 40 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 44 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 76 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 80 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<FortsHeartbeatInfo>							*Allocator;
	char							PaddingBytes0[8];

	FortsHeartbeatInfo() {
		memset(this, 0, sizeof(FortsHeartbeatInfo));
	}
	~FortsHeartbeatInfo() { }
	inline void Assign(FortsHeartbeatInfo *item) {
		// size = 88
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 6; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsSequenceResetInfo{
public:
	UINT32							NewSeqNo;			// id=36   offset = 0 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 4 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 8 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = 4 offset = 24 order =  999
	char							MessageType[16];			// id=35    constant has constant value = 4 offset = 28 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 44 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 48 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 80 order =  999
	char							PaddingBytes0[4];
	UINT64							SendingTime;			// id=52  skip=true   offset = 88 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsSequenceResetInfo>							*Pointer;
	AutoAllocatePointerList<FortsSequenceResetInfo>							*Allocator;

	FortsSequenceResetInfo() {
		memset(this, 0, sizeof(FortsSequenceResetInfo));
	}
	~FortsSequenceResetInfo() { }
	inline void Assign(FortsSequenceResetInfo *item) {
		// size = 96
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 6; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsTradingSessionStatusInfo{
public:
	UINT64							TradSesOpenTime;			// id=342   offset = 0 order =  0
	UINT64							TradSesCloseTime;			// id=344   offset = 8 order =  0
	UINT64							TradSesIntermClearingStartTime;			// id=5840  presence=optional   offset = 16 order =  0
	UINT64							TradSesIntermClearingEndTime;			// id=5841  presence=optional   offset = 24 order =  0
	UINT32							TradingSessionID;			// id=336   offset = 32 order =  0
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional   offset = 36 order =  0
	UINT32							TradSesStatus;			// id=340   offset = 40 order =  0
	int								MarketIDLength;			// id=1301    constant has constant value = MOEX offset = 44 order =  0
	char							MarketID[16];			// id=1301    constant has constant value = MOEX offset = 48 order =  0
	int								MarketSegmentIDLength;			// id=1300   offset = 64 order =  0
	char							MarketSegmentID[16];			// id=1300   offset = 68 order =  0
	INT32							TradSesEvent;			// id=1368  presence=optional   offset = 84 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 88 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 92 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = h offset = 108 order =  999
	char							MessageType[16];			// id=35    constant has constant value = h offset = 112 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 128 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 132 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 164 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 168 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<FortsTradingSessionStatusInfo>							*Allocator;

	FortsTradingSessionStatusInfo() {
		memset(this, 0, sizeof(FortsTradingSessionStatusInfo));
	}
	~FortsTradingSessionStatusInfo() { }
	inline void Assign(FortsTradingSessionStatusInfo *item) {
		// size = 176
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 11; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsNewsNewsTextItemInfo{
public:
	int								TextLength;			// id=58  charset=unicode   offset = 0 order =  0
	unsigned char							Text[128];			// id=58  charset=unicode   offset = 4
	char							PaddingBytes0[4];
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsNewsNewsTextItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsNewsNewsTextItemInfo>							*Allocator;
	char							PaddingBytes1[8];

	FortsNewsNewsTextItemInfo() {
		memset(this, 0, sizeof(FortsNewsNewsTextItemInfo));
	}
	~FortsNewsNewsTextItemInfo() { }
	inline void Assign(FortsNewsNewsTextItemInfo *item) {
		// size = 520
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 33; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsNewsInfo{
public:
	UINT32							LastFragment;			// id=893  presence=optional   offset = 0 order =  0
	int								NewsIdLength;			// id=1472  presence=optional   offset = 4 order =  0
	char							NewsId[16];			// id=1472  presence=optional   offset = 8 order =  0
	UINT64							OrigTime;			// id=42  presence=optional   offset = 24 order =  0
	int								LanguageCodeLength;			// id=1474  presence=optional   offset = 32 order =  0
	char							LanguageCode[16];			// id=1474  presence=optional   offset = 36 order =  0
	UINT32							Urgency;			// id=61  presence=optional   offset = 52 order =  0
	int								HeadlineLength;			// id=148  charset=unicode   offset = 56 order =  0
	unsigned char							Headline[128];			// id=148  charset=unicode   offset = 60
	int								MarketIDLength;			// id=1301    constant has constant value = MOEX offset = 76 order =  0
	char							MarketID[16];			// id=1301    constant has constant value = MOEX offset = 80 order =  0
	int								MarketSegmentIDLength;			// id=1300  presence=optional   offset = 96 order =  0
	char							MarketSegmentID[16];			// id=1300  presence=optional   offset = 100 order =  0
	int								NewsTextCount;//		 offset = 116 order =  0
	FortsNewsNewsTextItemInfo* NewsText[256];//		 offset = 120 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 2168 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 2172 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = B offset = 2188 order =  999
	char							MessageType[16];			// id=35    constant has constant value = B offset = 2192 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 2208 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 2212 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2244 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 2248 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsNewsInfo>							*Pointer;
	AutoAllocatePointerList<FortsNewsInfo>							*Allocator;

	FortsNewsInfo() {
		memset(this, 0, sizeof(FortsNewsInfo));
	}
	~FortsNewsInfo() { }
	inline void Assign(FortsNewsInfo *item) {
	int								NewsTextCount;//		 offset = 116 order =  0
		// size = 2256
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 141; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->ReleaseUnused();
	}
};

class FortsOrdersLogMDEntriesItemInfo{
public:
	UINT32							MDUpdateAction;			// id=279   offset = 0 order =  0
	int								MDEntryTypeLength;			// id=269   offset = 4 order =  0
	char							MDEntryType[4];			// id=269   offset = 8 order =  0
	char							PaddingBytes0[4];
	UINT64							MDEntryID;			// id=278  presence=optional   offset = 16 order =  0
	UINT64							SecurityID;			// id=48  presence=optional   offset = 24 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 32 order =  0
	UINT32							RptSeq;			// id=83  presence=optional   offset = 36 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional   offset = 40 order =  0
	char							PaddingBytes1[4];
	UINT64							MDEntryTime;			// id=273   offset = 48 order =  0
	Decimal							MDEntryPx;			// id=270  presence=optional   offset = 56 order =  0
	UINT64							MDEntrySize;			// id=271  presence=optional   offset = 72 order =  0
	Decimal							LastPx;			// id=31  presence=optional   offset = 80 order =  0
	UINT64							LastQty;			// id=32  presence=optional   offset = 96 order =  0
	UINT64							TradeID;			// id=1003  presence=optional   offset = 104 order =  0
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional   offset = 112 order =  0
	char							PaddingBytes2[4];
	UINT64							MDFlags;			// id=20017  presence=optional   offset = 120 order =  0
	UINT64							Revision;			// id=20018  presence=optional   offset = 128 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersLogMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>							*Allocator;
	char							PaddingBytes3[8];

	FortsOrdersLogMDEntriesItemInfo() {
		memset(this, 0, sizeof(FortsOrdersLogMDEntriesItemInfo));
	}
	~FortsOrdersLogMDEntriesItemInfo() { }
	inline void Assign(FortsOrdersLogMDEntriesItemInfo *item) {
		// size = 136
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 9; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsOrdersLogInfo{
public:
	UINT32							LastFragment;			// id=893   offset = 0 order =  0
	int								MDEntriesCount;//		 offset = 4 order =  0
	FortsOrdersLogMDEntriesItemInfo* MDEntries[256];//		 offset = 8 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 2056 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 2060 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = X offset = 2076 order =  999
	char							MessageType[16];			// id=35    constant has constant value = X offset = 2080 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 2096 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 2100 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2132 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 2136 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersLogInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersLogInfo>							*Allocator;

	FortsOrdersLogInfo() {
		memset(this, 0, sizeof(FortsOrdersLogInfo));
	}
	~FortsOrdersLogInfo() { }
	inline void Assign(FortsOrdersLogInfo *item) {
	int								MDEntriesCount;//		 offset = 4 order =  0
		// size = 2144
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 134; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsOrdersBookMDEntriesItemInfo{
public:
	int								MDEntryTypeLength;			// id=269   offset = 0 order =  0
	char							MDEntryType[4];			// id=269   offset = 4 order =  0
	UINT64							MDEntryID;			// id=278  presence=optional   offset = 8 order =  0
	UINT32							MDEntryDate;			// id=272  presence=optional   offset = 16 order =  0
	char							PaddingBytes0[4];
	UINT64							MDEntryTime;			// id=273   offset = 24 order =  0
	Decimal							MDEntryPx;			// id=270  presence=optional   offset = 32 order =  0
	UINT64							MDEntrySize;			// id=271  presence=optional   offset = 48 order =  0
	UINT64							TradeID;			// id=1003  presence=optional   offset = 56 order =  0
	UINT64							MDFlags;			// id=20017  presence=optional   offset = 64 order =  0
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersBookMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>							*Allocator;
	char							PaddingBytes1[8];

	FortsOrdersBookMDEntriesItemInfo() {
		memset(this, 0, sizeof(FortsOrdersBookMDEntriesItemInfo));
	}
	~FortsOrdersBookMDEntriesItemInfo() { }
	inline void Assign(FortsOrdersBookMDEntriesItemInfo *item) {
		// size = 72
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 5; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsOrdersBookInfo{
public:
	UINT32							LastMsgSeqNumProcessed;			// id=369   offset = 0 order =  0
	UINT32							RptSeq;			// id=83  presence=optional   offset = 4 order =  0
	UINT32							LastFragment;			// id=893   offset = 8 order =  0
	UINT32							RouteFirst;			// id=7944   offset = 12 order =  0
	UINT32							ExchangeTradingSessionID;			// id=5842   offset = 16 order =  0
	char							PaddingBytes0[4];
	UINT64							SecurityID;			// id=48  presence=optional   offset = 24 order =  0
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8 offset = 32 order =  0
	int								MDEntriesCount;//		 offset = 36 order =  0
	FortsOrdersBookMDEntriesItemInfo* MDEntries[256];//		 offset = 40 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 2088 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 2092 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = W offset = 2108 order =  999
	char							MessageType[16];			// id=35    constant has constant value = W offset = 2112 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 2128 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 2132 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2164 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 2168 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsOrdersBookInfo>							*Pointer;
	AutoAllocatePointerList<FortsOrdersBookInfo>							*Allocator;

	FortsOrdersBookInfo() {
		memset(this, 0, sizeof(FortsOrdersBookInfo));
	}
	~FortsOrdersBookInfo() { }
	inline void Assign(FortsOrdersBookInfo *item) {
	int								MDEntriesCount;//		 offset = 36 order =  0
		// size = 2176
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 136; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class FortsLogonInfo{
public:
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 0 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 4 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = A offset = 20 order =  999
	char							MessageType[16];			// id=35    constant has constant value = A offset = 24 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 40 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 44 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 76 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 80 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsLogonInfo>							*Pointer;
	AutoAllocatePointerList<FortsLogonInfo>							*Allocator;
	char							PaddingBytes0[8];

	FortsLogonInfo() {
		memset(this, 0, sizeof(FortsLogonInfo));
	}
	~FortsLogonInfo() { }
	inline void Assign(FortsLogonInfo *item) {
		// size = 88
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 6; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsLogoutInfo{
public:
	int								TextLength;			// id=58  presence=optional   offset = 0 order =  0
	char							Text[512];			// id=58  presence=optional   offset = 4 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 516 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 520 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = 5 offset = 536 order =  999
	char							MessageType[16];			// id=35    constant has constant value = 5 offset = 540 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 556 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 560 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 592 order =  999
	char							PaddingBytes0[4];
	UINT64							SendingTime;			// id=52  skip=true   offset = 600 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsLogoutInfo>							*Pointer;
	AutoAllocatePointerList<FortsLogoutInfo>							*Allocator;

	FortsLogoutInfo() {
		memset(this, 0, sizeof(FortsLogoutInfo));
	}
	~FortsLogoutInfo() { }
	inline void Assign(FortsLogoutInfo *item) {
		// size = 608
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 38; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
	}
	inline void ReleaseUnusedChildren() {
	}
};

class FortsDefaultIncrementalRefreshMessageInfo{
public:
	UINT32							LastFragment;			// id=893  presence=optional   offset = 0 order =  0
	int								MDEntriesCount;//		 offset = 4 order =  0
	FortsDefaultSnapshotMessageMDEntriesItemInfo* MDEntries[256];//		 offset = 8 order =  0
	int								ApplVerIDLength;			// id=1128    constant has constant value = 9 offset = 2056 order =  999
	char							ApplVerID[16];			// id=1128    constant has constant value = 9 offset = 2060 order =  999
	int								MessageTypeLength;			// id=35    constant has constant value = X offset = 2076 order =  999
	char							MessageType[16];			// id=35    constant has constant value = X offset = 2080 order =  999
	int								SenderCompIDLength;			// id=49    constant has constant value = MOEX offset = 2096 order =  999
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX offset = 2100 order =  999
	UINT32							MsgSeqNum;			// id=34  skip=true   offset = 2132 order =  999
	UINT64							SendingTime;			// id=52  skip=true   offset = 2136 order =  999
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FortsDefaultIncrementalRefreshMessageInfo>							*Pointer;
	AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>							*Allocator;

	FortsDefaultIncrementalRefreshMessageInfo() {
		memset(this, 0, sizeof(FortsDefaultIncrementalRefreshMessageInfo));
	}
	~FortsDefaultIncrementalRefreshMessageInfo() { }
	inline void Assign(FortsDefaultIncrementalRefreshMessageInfo *item) {
	int								MDEntriesCount;//		 offset = 4 order =  0
		// size = 2144
		__m128 *dst = (__m128*)this;
		__m128 *src = (__m128*)item;
		for(int i = 0; i < 134; i++, src ++, dst ++) {
			__m128 t = *src;
			*(dst) = t;
		}
	}
	inline void Clear() {
		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {

		this->Allocator->FreeItemUnsafe(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
	inline void ReleaseUnusedChildren() {
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
class FortsPackedTemplateId {
public:
	static const UINT32 FortsDefaultSnapshotMessageInfo = 0x008d;
	static const UINT32 FortsSecurityDefinitionInfo = 0x0083;
	static const UINT32 FortsSecurityDefinitionUpdateReportInfo = 0x0084;
	static const UINT32 FortsSecurityStatusInfo = 0x0085;
	static const UINT32 FortsHeartbeatInfo = 0x0086;
	static const UINT32 FortsSequenceResetInfo = 0x0087;
	static const UINT32 FortsTradingSessionStatusInfo = 0x0088;
	static const UINT32 FortsNewsInfo = 0x0089;
	static const UINT32 FortsOrdersLogInfo = 0x008e;
	static const UINT32 FortsOrdersBookInfo = 0x008f;
	static const UINT32 FortsLogonInfo = 0xe807;
	static const UINT32 FortsLogoutInfo = 0xe907;
	static const UINT32 FortsDefaultIncrementalRefreshMessageInfo = 0x008c;
};
#pragma endregion

#endif //HFT_ROBOT_FASTTYPES_H
