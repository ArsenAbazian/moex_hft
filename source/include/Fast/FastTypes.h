//
//
// Created by root on 21.08.16.
//

#ifndef HFT_ROBOT_FASTTYPES_H
#define HFT_ROBOT_FASTTYPES_H

#define FAST_STOPBIT_FIRST_BYTE 		0x0000000000000080L
#define FAST_STOPBIT_SECOND_BYTE		0x0000000000008000L
#define FAST_STOPBIT_THIRD_BYTE			0x0000000000800000L
#define FAST_STOPBIT_FORTH_BYTE			0x0000000080000000L

#define FAST_STOPBIT_FIFTH_BYTE 		0x0000008000000000L
#define FAST_STOPBIT_SIXSTH_BYTE		0x0000800000000000L
#define FAST_STOPBIT_SEVENTH_BYTE		0x0080000000000000L

#include "Settings.h"
#include "Lib/AutoAllocatePointerList.h"
#include "Fix/FixTypes.h"

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
class FastSnapshotInfo {
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
	FastSnapshotInfo() {
		this->PresenceMap = 0;
		this->NullMap = 0;
	}
};

class FastLogonInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastLogonInfo>							*Pointer;
	AutoAllocatePointerList<FastLogonInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = A
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	char							TargetCompID[32];			// id=56  
	int							TargetCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							HeartBtInt;			// id=108  
	char							Username[16];			// id=553  presence=optional  
	int							UsernameLength = 0;
	char							Password[16];			// id=554  presence=optional  
	int							PasswordLength = 0;
	char							DefaultApplVerID[16];			// id=1137  
	int							DefaultApplVerIDLength = 0;

	FastLogonInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TargetCompID[0] = '\0';
		this->TargetCompIDLength = 0;
		this->Username[0] = '\0';
		this->UsernameLength = 0;
		this->Password[0] = '\0';
		this->PasswordLength = 0;
		this->DefaultApplVerID[0] = '\0';
		this->DefaultApplVerIDLength = 0;
	}
	~FastLogonInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastLogoutInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastLogoutInfo>							*Pointer;
	AutoAllocatePointerList<FastLogoutInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = 5
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	char							TargetCompID[32];			// id=56  
	int							TargetCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							Text[512];			// id=58  presence=optional  
	int							TextLength = 0;

	FastLogoutInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TargetCompID[0] = '\0';
		this->TargetCompIDLength = 0;
		this->Text[0] = '\0';
		this->TextLength = 0;
	}
	~FastLogoutInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastGenericItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastGenericItemInfo>							*Pointer;
	AutoAllocatePointerList<FastGenericItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  presence=optional  
	int							MDEntryTypeLength = 0;
	char							MDEntryID[16];			// id=278  presence=optional  
	int							MDEntryIDLength = 0;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT32							MDEntryTime;			// id=273  presence=optional  
	UINT32							OrigTime;			// id=9412  presence=optional  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	Decimal							MDEntrySize;			// id=271  presence=optional  
	char							QuoteCondition[16];			// id=276  presence=optional  
	int							QuoteConditionLength = 0;
	char							TradeCondition[16];			// id=277  presence=optional  
	int							TradeConditionLength = 0;
	char							OpenCloseSettlFlag[4];			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength = 0;
	char							OrdType[4];			// id=40  presence=optional  
	int							OrdTypeLength = 0;
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
	int							SettleTypeLength = 0;
	INT32							SumQtyOfBest;			// id=10503  presence=optional  
	char							OrderSide[4];			// id=10504  presence=optional  
	int							OrderSideLength = 0;
	char							OrderStatus[4];			// id=10505  presence=optional  
	int							OrderStatusLength = 0;
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
	int							CXFlagLength = 0;
	char							TradingSessionSubID[4];			// id=625  presence=optional  
	int							TradingSessionSubIDLength = 0;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	INT32							RptSeq;			// id=83  presence=optional  
	char							Symbol[16];			// id=55  presence=optional  
	int							SymbolLength = 0;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;

	FastGenericItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->MDEntryID[0] = '\0';
		this->MDEntryIDLength = 0;
		this->QuoteCondition[0] = '\0';
		this->QuoteConditionLength = 0;
		this->TradeCondition[0] = '\0';
		this->TradeConditionLength = 0;
		this->OpenCloseSettlFlag[0] = '\0';
		this->OpenCloseSettlFlagLength = 0;
		this->OrdType[0] = '\0';
		this->OrdTypeLength = 0;
		this->SettleType[0] = '\0';
		this->SettleTypeLength = 0;
		this->OrderSide[0] = '\0';
		this->OrderSideLength = 0;
		this->OrderStatus[0] = '\0';
		this->OrderStatusLength = 0;
		this->CXFlag[0] = '\0';
		this->CXFlagLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
	}
	~FastGenericItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastGenericInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastGenericInfo>							*Pointer;
	AutoAllocatePointerList<FastGenericInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastGenericInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastGenericInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalGenericInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalGenericInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalGenericInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastIncrementalGenericInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalGenericInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastOLSFONDItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastOLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSFONDItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  presence=optional    copy
	int							MDEntryTypeLength = 0;
	char							MDEntryID[16];			// id=278  presence=optional  
	int							MDEntryIDLength = 0;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	Decimal							Yield;			// id=236  presence=optional    copy
	char							OrderStatus[4];			// id=10505  presence=optional    copy
	int							OrderStatusLength = 0;
	char							OrdType[4];			// id=40  presence=optional    copy
	int							OrdTypeLength = 0;
	Decimal							TotalVolume;			// id=5791  presence=optional    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength = 0;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	char							Symbol[16];			// id=55  presence=optional    copy
	int							SymbolLength = 0;
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional    copy
	int							TradingSessionIDLength = 0;

	FastOLSFONDItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->MDEntryID[0] = '\0';
		this->MDEntryIDLength = 0;
		this->OrderStatus[0] = '\0';
		this->OrderStatusLength = 0;
		this->OrdType[0] = '\0';
		this->OrdTypeLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
	}
	~FastOLSFONDItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastOLSFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastOLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	int							GroupMDEntriesCount;
	FastOLSFONDItemInfo* GroupMDEntries[256];

	FastOLSFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastOLSFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastOLSCURRItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastOLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSCURRItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  presence=optional    copy
	int							MDEntryTypeLength = 0;
	char							MDEntryID[16];			// id=278  presence=optional  
	int							MDEntryIDLength = 0;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	char							OrderStatus[4];			// id=10505  presence=optional    copy
	int							OrderStatusLength = 0;
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength = 0;
	UINT32							MDUpdateAction;			// id=279  presence=optional    copy
	char							Symbol[16];			// id=55  presence=optional    copy
	int							SymbolLength = 0;
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional    copy
	int							TradingSessionIDLength = 0;

	FastOLSCURRItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->MDEntryID[0] = '\0';
		this->MDEntryIDLength = 0;
		this->OrderStatus[0] = '\0';
		this->OrderStatusLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
	}
	~FastOLSCURRItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastOLSCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastOLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	int							GroupMDEntriesCount;
	FastOLSCURRItemInfo* GroupMDEntries[256];

	FastOLSCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastOLSCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastTLSFONDItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastTLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSFONDItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  
	int							MDEntryTypeLength = 0;
	char							MDEntryID[16];			// id=278  presence=optional  
	int							MDEntryIDLength = 0;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	char							OrderSide[4];			// id=10504  presence=optional    copy
	int							OrderSideLength = 0;
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional    copy
	Decimal							TradeValue;			// id=6143  presence=optional    copy
	Decimal							Yield;			// id=236  presence=optional    copy
	UINT32							SettlDate;			// id=64  presence=optional    copy
	char							SettleType[16];			// id=5459  presence=optional    copy
	int							SettleTypeLength = 0;
	Decimal							Price;			// id=44  presence=optional    copy
	INT32							PriceType;			// id=423  presence=optional    copy
	Decimal							RepoToPx;			// id=5677  presence=optional    copy
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength = 0;
	char							RefOrderID[16];			// id=1080  presence=optional    copy
	int							RefOrderIDLength = 0;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	char							Symbol[16];			// id=55  presence=optional  
	int							SymbolLength = 0;
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;

	FastTLSFONDItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->MDEntryID[0] = '\0';
		this->MDEntryIDLength = 0;
		this->OrderSide[0] = '\0';
		this->OrderSideLength = 0;
		this->SettleType[0] = '\0';
		this->SettleTypeLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
		this->RefOrderID[0] = '\0';
		this->RefOrderIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
	}
	~FastTLSFONDItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastTLSFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastTLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	int							GroupMDEntriesCount;
	FastTLSFONDItemInfo* GroupMDEntries[256];

	FastTLSFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastTLSFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastTLSCURRItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastTLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSCURRItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  
	int							MDEntryTypeLength = 0;
	char							MDEntryID[16];			// id=278  presence=optional  
	int							MDEntryIDLength = 0;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	char							OrderSide[4];			// id=10504  presence=optional    copy
	int							OrderSideLength = 0;
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	Decimal							TradeValue;			// id=6143  presence=optional    copy
	UINT32							SettlDate;			// id=64  presence=optional    copy
	char							SettleType[16];			// id=5459  presence=optional    copy
	int							SettleTypeLength = 0;
	Decimal							Price;			// id=44  presence=optional    copy
	INT32							PriceType;			// id=423  presence=optional    copy
	Decimal							RepoToPx;			// id=5677  presence=optional    copy
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy
	char							TradingSessionSubID[4];			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength = 0;
	char							RefOrderID[16];			// id=1080  presence=optional    copy
	int							RefOrderIDLength = 0;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	char							Symbol[16];			// id=55  presence=optional  
	int							SymbolLength = 0;
	INT32							RptSeq;			// id=83  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;

	FastTLSCURRItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->MDEntryID[0] = '\0';
		this->MDEntryIDLength = 0;
		this->OrderSide[0] = '\0';
		this->OrderSideLength = 0;
		this->SettleType[0] = '\0';
		this->SettleTypeLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
		this->RefOrderID[0] = '\0';
		this->RefOrderIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
	}
	~FastTLSCURRItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastTLSCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastTLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RouteFirst;			// id=7944  presence=optional  
	INT32							TradSesStatus;			// id=340  presence=optional  
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	int							GroupMDEntriesCount;
	FastTLSCURRItemInfo* GroupMDEntries[256];

	FastTLSCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastTLSCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalMSRFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalMSRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalMSRFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							LastUpdateTime;			// id=779  presence=optional  
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastIncrementalMSRFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalMSRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalMSRCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalMSRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalMSRCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							LastUpdateTime;			// id=779  presence=optional  
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastIncrementalMSRCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalMSRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalOLRFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalOLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalOLRFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastOLSFONDItemInfo* GroupMDEntries[256];

	FastIncrementalOLRFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalOLRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalOLRCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalOLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalOLRCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastOLSCURRItemInfo* GroupMDEntries[256];

	FastIncrementalOLRCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalOLRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalTLRFONDInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalTLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalTLRFONDInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastTLSFONDItemInfo* GroupMDEntries[256];

	FastIncrementalTLRFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalTLRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalTLRCURRInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastIncrementalTLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalTLRCURRInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastTLSCURRItemInfo* GroupMDEntries[256];

	FastIncrementalTLRCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->GroupMDEntriesCount = 0;
	}
	~FastIncrementalTLRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastSecurityDefinitionGroupInstrAttribItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastSecurityDefinitionGroupInstrAttribItemInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>							*Allocator;
	bool							Used;
	INT32							InstrAttribType;			// id=871  
	unsigned char							InstrAttribValue[128];			// id=872  presence=optional  
	int							InstrAttribValueLength = 0;

	FastSecurityDefinitionGroupInstrAttribItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
	}
	~FastSecurityDefinitionGroupInstrAttribItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Allocator;
	bool							Used;
	char							TradingSessionID[16];			// id=336  
	int							TradingSessionIDLength = 0;
	char							TradingSessionSubID[4];			// id=625  presence=optional  
	int							TradingSessionSubIDLength = 0;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	INT32							OrderNote;			// id=9680  presence=optional  

	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
	}
	~FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastSecurityDefinitionMarketSegmentGrpItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastSecurityDefinitionMarketSegmentGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>							*Allocator;
	bool							Used;
	Decimal							RoundLot;			// id=561  presence=optional  
	int							TradingSessionRulesGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* TradingSessionRulesGrp[256];			// presence=optional  

	FastSecurityDefinitionMarketSegmentGrpItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->TradingSessionRulesGrpCount = 0;
	}
	~FastSecurityDefinitionMarketSegmentGrpItemInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->TradingSessionRulesGrpCount; i++)
			this->TradingSessionRulesGrp[i]->ReleaseUnused();
	}
};

class FastSecurityDefinitionInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = d
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34    increment
	UINT64							SendingTime;			// id=52  
	char							MessageEncoding[16];			// id=347    default
	int							MessageEncodingLength = 0;
	INT32							TotNumReports;			// id=911  presence=optional  
	char							Symbol[16];			// id=55  presence=optional  
	int							SymbolLength = 0;
	unsigned char							SecurityID[128];			// id=48  presence=optional  
	int							SecurityIDLength = 0;
	unsigned char							SecurityIDSource[128];			// id=22  presence=optional  
	int							SecurityIDSourceLength = 0;
	INT32							Product;			// id=460  presence=optional  
	unsigned char							CFICode[128];			// id=461  presence=optional  
	int							CFICodeLength = 0;
	unsigned char							SecurityType[128];			// id=167  presence=optional  
	int							SecurityTypeLength = 0;
	UINT32							MaturityDate;			// id=541  presence=optional  
	UINT32							SettlDate;			// id=64  presence=optional  
	char							SettleType[16];			// id=5459  presence=optional  
	int							SettleTypeLength = 0;
	Decimal							OrigIssueAmt;			// id=5850  presence=optional  
	UINT32							CouponPaymentDate;			// id=224  presence=optional  
	Decimal							CouponRate;			// id=223  presence=optional  
	UINT32							SettlFixingDate;			// id=9119  presence=optional  
	Decimal							DividendNetPx;			// id=9982  presence=optional  
	unsigned char							SecurityDesc[128];			// id=107  presence=optional  
	int							SecurityDescLength = 0;
	unsigned char							EncodedSecurityDesc[128];			// id=351  presence=optional  
	int							EncodedSecurityDescLength = 0;
	unsigned char							QuoteText[128];			// id=9696  presence=optional  
	int							QuoteTextLength = 0;
	int							GroupInstrAttribCount;			// presence=optional  
	FastSecurityDefinitionGroupInstrAttribItemInfo* GroupInstrAttrib[256];			// presence=optional  
	char							Currency[16];			// id=15  presence=optional  
	int							CurrencyLength = 0;
	int							MarketSegmentGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpItemInfo* MarketSegmentGrp[256];			// presence=optional  
	char							SettlCurrency[16];			// id=120  presence=optional  
	int							SettlCurrencyLength = 0;
	INT32							PriceType;			// id=423  presence=optional  
	char							StateSecurityID[16];			// id=5217  presence=optional  
	int							StateSecurityIDLength = 0;
	unsigned char							EncodedShortSecurityDesc[128];			// id=5383  presence=optional  
	int							EncodedShortSecurityDescLength = 0;
	unsigned char							MarketCode[128];			// id=5385  presence=optional  
	int							MarketCodeLength = 0;
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

	FastSecurityDefinitionInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->MessageEncoding[0] = '\0';
		this->MessageEncodingLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->SettleType[0] = '\0';
		this->SettleTypeLength = 0;
		this->GroupInstrAttribCount = 0;
		this->Currency[0] = '\0';
		this->CurrencyLength = 0;
		this->MarketSegmentGrpCount = 0;
		this->SettlCurrency[0] = '\0';
		this->SettlCurrencyLength = 0;
		this->StateSecurityID[0] = '\0';
		this->StateSecurityIDLength = 0;
	}
	~FastSecurityDefinitionInfo(){ }
	inline void Clear() {
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

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->ReleaseUnused();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->ReleaseUnused();
	}
};

class FastSecurityStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityStatusInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = f
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	char							TradingSessionID[16];			// id=336  presence=optional  
	int							TradingSessionIDLength = 0;
	char							TradingSessionSubID[4];			// id=625  presence=optional  
	int							TradingSessionSubIDLength = 0;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	UINT32							AuctionIndicator;			// id=5509  presence=optional  

	FastSecurityStatusInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
		this->TradingSessionSubID[0] = '\0';
		this->TradingSessionSubIDLength = 0;
	}
	~FastSecurityStatusInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastTradingSessionStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<FastTradingSessionStatusInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = h
	int							MessageTypeLength = 0;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							TradSesStatus;			// id=340  
	char							Text[512];			// id=58  presence=optional  
	int							TextLength = 0;
	char							TradingSessionID[16];			// id=336  
	int							TradingSessionIDLength = 0;

	FastTradingSessionStatusInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->Text[0] = '\0';
		this->TextLength = 0;
		this->TradingSessionID[0] = '\0';
		this->TradingSessionIDLength = 0;
	}
	~FastTradingSessionStatusInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastHeartbeatInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<FastHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<FastHeartbeatInfo>							*Allocator;
	bool							Used;
	char							MessageType[16];			// id=35    constant has constant value = 0
	int							MessageTypeLength = 0;
	char							BeginString[16];			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  

	FastHeartbeatInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->BeginString[0] = '\0';
		this->BeginStringLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
	}
	~FastHeartbeatInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
	}
};

class FastObjectsAllocationInfo {
	AutoAllocatePointerList<FastLogonInfo>				*m_logon;
	AutoAllocatePointerList<FastLogoutInfo>				*m_logout;
	AutoAllocatePointerList<FastGenericItemInfo>				*m_genericItems;
	AutoAllocatePointerList<FastGenericInfo>				*m_generic;
	AutoAllocatePointerList<FastIncrementalGenericInfo>				*m_incrementalGeneric;
	AutoAllocatePointerList<FastOLSFONDItemInfo>				*m_oLSFONDItems;
	AutoAllocatePointerList<FastOLSFONDInfo>				*m_oLSFOND;
	AutoAllocatePointerList<FastOLSCURRItemInfo>				*m_oLSCURRItems;
	AutoAllocatePointerList<FastOLSCURRInfo>				*m_oLSCURR;
	AutoAllocatePointerList<FastTLSFONDItemInfo>				*m_tLSFONDItems;
	AutoAllocatePointerList<FastTLSFONDInfo>				*m_tLSFOND;
	AutoAllocatePointerList<FastTLSCURRItemInfo>				*m_tLSCURRItems;
	AutoAllocatePointerList<FastTLSCURRInfo>				*m_tLSCURR;
	AutoAllocatePointerList<FastIncrementalMSRFONDInfo>				*m_incrementalMSRFOND;
	AutoAllocatePointerList<FastIncrementalMSRCURRInfo>				*m_incrementalMSRCURR;
	AutoAllocatePointerList<FastIncrementalOLRFONDInfo>				*m_incrementalOLRFOND;
	AutoAllocatePointerList<FastIncrementalOLRCURRInfo>				*m_incrementalOLRCURR;
	AutoAllocatePointerList<FastIncrementalTLRFONDInfo>				*m_incrementalTLRFOND;
	AutoAllocatePointerList<FastIncrementalTLRCURRInfo>				*m_incrementalTLRCURR;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>				*m_securityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>				*m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>				*m_securityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionInfo>				*m_securityDefinition;
	AutoAllocatePointerList<FastSecurityStatusInfo>				*m_securityStatus;
	AutoAllocatePointerList<FastTradingSessionStatusInfo>				*m_tradingSessionStatus;
	AutoAllocatePointerList<FastHeartbeatInfo>				*m_heartbeat;
public:
	 static FastObjectsAllocationInfo *Default;
	FastObjectsAllocationInfo(int count) {
		this->m_logon = new AutoAllocatePointerList<FastLogonInfo>(count, count, "FastLogonInfo");
		this->m_logout = new AutoAllocatePointerList<FastLogoutInfo>(count, count, "FastLogoutInfo");
		this->m_genericItems = new AutoAllocatePointerList<FastGenericItemInfo>(count, count, "FastGenericItemInfo");
		this->m_generic = new AutoAllocatePointerList<FastGenericInfo>(count, count, "FastGenericInfo");
		this->m_incrementalGeneric = new AutoAllocatePointerList<FastIncrementalGenericInfo>(count, count, "FastIncrementalGenericInfo");
		this->m_oLSFONDItems = new AutoAllocatePointerList<FastOLSFONDItemInfo>(count, count, "FastOLSFONDItemInfo");
		this->m_oLSFOND = new AutoAllocatePointerList<FastOLSFONDInfo>(count, count, "FastOLSFONDInfo");
		this->m_oLSCURRItems = new AutoAllocatePointerList<FastOLSCURRItemInfo>(count, count, "FastOLSCURRItemInfo");
		this->m_oLSCURR = new AutoAllocatePointerList<FastOLSCURRInfo>(count, count, "FastOLSCURRInfo");
		this->m_tLSFONDItems = new AutoAllocatePointerList<FastTLSFONDItemInfo>(count, count, "FastTLSFONDItemInfo");
		this->m_tLSFOND = new AutoAllocatePointerList<FastTLSFONDInfo>(count, count, "FastTLSFONDInfo");
		this->m_tLSCURRItems = new AutoAllocatePointerList<FastTLSCURRItemInfo>(count, count, "FastTLSCURRItemInfo");
		this->m_tLSCURR = new AutoAllocatePointerList<FastTLSCURRInfo>(count, count, "FastTLSCURRInfo");
		this->m_incrementalMSRFOND = new AutoAllocatePointerList<FastIncrementalMSRFONDInfo>(count, count, "FastIncrementalMSRFONDInfo");
		this->m_incrementalMSRCURR = new AutoAllocatePointerList<FastIncrementalMSRCURRInfo>(count, count, "FastIncrementalMSRCURRInfo");
		this->m_incrementalOLRFOND = new AutoAllocatePointerList<FastIncrementalOLRFONDInfo>(count, count, "FastIncrementalOLRFONDInfo");
		this->m_incrementalOLRCURR = new AutoAllocatePointerList<FastIncrementalOLRCURRInfo>(count, count, "FastIncrementalOLRCURRInfo");
		this->m_incrementalTLRFOND = new AutoAllocatePointerList<FastIncrementalTLRFONDInfo>(count, count, "FastIncrementalTLRFONDInfo");
		this->m_incrementalTLRCURR = new AutoAllocatePointerList<FastIncrementalTLRCURRInfo>(count, count, "FastIncrementalTLRCURRInfo");
		this->m_securityDefinitionGroupInstrAttribItems = new AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>(count, count, "FastSecurityDefinitionGroupInstrAttribItemInfo");
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(count, count, "FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo");
		this->m_securityDefinitionMarketSegmentGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>(count, count, "FastSecurityDefinitionMarketSegmentGrpItemInfo");
		this->m_securityDefinition = new AutoAllocatePointerList<FastSecurityDefinitionInfo>(count, count, "FastSecurityDefinitionInfo");
		this->m_securityStatus = new AutoAllocatePointerList<FastSecurityStatusInfo>(count, count, "FastSecurityStatusInfo");
		this->m_tradingSessionStatus = new AutoAllocatePointerList<FastTradingSessionStatusInfo>(count, count, "FastTradingSessionStatusInfo");
		this->m_heartbeat = new AutoAllocatePointerList<FastHeartbeatInfo>(count, count, "FastHeartbeatInfo");
	}
	inline void AllocateLogonInfoPool(int count, int addCount) {
		this->m_logon->Append(count);
		this->m_logon->AddCount(addCount);
	}
	inline void AllocateLogoutInfoPool(int count, int addCount) {
		this->m_logout->Append(count);
		this->m_logout->AddCount(addCount);
	}
	inline void AllocateGenericItemInfoPool(int count, int addCount) {
		this->m_genericItems->Append(count);
		this->m_genericItems->AddCount(addCount);
	}
	inline void AllocateGenericInfoPool(int count, int addCount) {
		this->m_generic->Append(count);
		this->m_generic->AddCount(addCount);
	}
	inline void AllocateIncrementalGenericInfoPool(int count, int addCount) {
		this->m_incrementalGeneric->Append(count);
		this->m_incrementalGeneric->AddCount(addCount);
	}
	inline void AllocateOLSFONDItemInfoPool(int count, int addCount) {
		this->m_oLSFONDItems->Append(count);
		this->m_oLSFONDItems->AddCount(addCount);
	}
	inline void AllocateOLSFONDInfoPool(int count, int addCount) {
		this->m_oLSFOND->Append(count);
		this->m_oLSFOND->AddCount(addCount);
	}
	inline void AllocateOLSCURRItemInfoPool(int count, int addCount) {
		this->m_oLSCURRItems->Append(count);
		this->m_oLSCURRItems->AddCount(addCount);
	}
	inline void AllocateOLSCURRInfoPool(int count, int addCount) {
		this->m_oLSCURR->Append(count);
		this->m_oLSCURR->AddCount(addCount);
	}
	inline void AllocateTLSFONDItemInfoPool(int count, int addCount) {
		this->m_tLSFONDItems->Append(count);
		this->m_tLSFONDItems->AddCount(addCount);
	}
	inline void AllocateTLSFONDInfoPool(int count, int addCount) {
		this->m_tLSFOND->Append(count);
		this->m_tLSFOND->AddCount(addCount);
	}
	inline void AllocateTLSCURRItemInfoPool(int count, int addCount) {
		this->m_tLSCURRItems->Append(count);
		this->m_tLSCURRItems->AddCount(addCount);
	}
	inline void AllocateTLSCURRInfoPool(int count, int addCount) {
		this->m_tLSCURR->Append(count);
		this->m_tLSCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalMSRFONDInfoPool(int count, int addCount) {
		this->m_incrementalMSRFOND->Append(count);
		this->m_incrementalMSRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalMSRCURRInfoPool(int count, int addCount) {
		this->m_incrementalMSRCURR->Append(count);
		this->m_incrementalMSRCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalOLRFONDInfoPool(int count, int addCount) {
		this->m_incrementalOLRFOND->Append(count);
		this->m_incrementalOLRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalOLRCURRInfoPool(int count, int addCount) {
		this->m_incrementalOLRCURR->Append(count);
		this->m_incrementalOLRCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalTLRFONDInfoPool(int count, int addCount) {
		this->m_incrementalTLRFOND->Append(count);
		this->m_incrementalTLRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalTLRCURRInfoPool(int count, int addCount) {
		this->m_incrementalTLRCURR->Append(count);
		this->m_incrementalTLRCURR->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(int count, int addCount) {
		this->m_securityDefinitionGroupInstrAttribItems->Append(count);
		this->m_securityDefinitionGroupInstrAttribItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(int count, int addCount) {
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Append(count);
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(int count, int addCount) {
		this->m_securityDefinitionMarketSegmentGrpItems->Append(count);
		this->m_securityDefinitionMarketSegmentGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInfoPool(int count, int addCount) {
		this->m_securityDefinition->Append(count);
		this->m_securityDefinition->AddCount(addCount);
	}
	inline void AllocateSecurityStatusInfoPool(int count, int addCount) {
		this->m_securityStatus->Append(count);
		this->m_securityStatus->AddCount(addCount);
	}
	inline void AllocateTradingSessionStatusInfoPool(int count, int addCount) {
		this->m_tradingSessionStatus->Append(count);
		this->m_tradingSessionStatus->AddCount(addCount);
	}
	inline void AllocateHeartbeatInfoPool(int count, int addCount) {
		this->m_heartbeat->Append(count);
		this->m_heartbeat->AddCount(addCount);
	}
	inline void AllocateLogonInfoPoolTo(int count) {
count -= this->m_logon->Capacity();
if(count > 0)
			this->m_logon->Append(count);
	}
	inline void AllocateLogoutInfoPoolTo(int count) {
count -= this->m_logout->Capacity();
if(count > 0)
			this->m_logout->Append(count);
	}
	inline void AllocateGenericItemInfoPoolTo(int count) {
count -= this->m_genericItems->Capacity();
if(count > 0)
			this->m_genericItems->Append(count);
	}
	inline void AllocateGenericInfoPoolTo(int count) {
count -= this->m_generic->Capacity();
if(count > 0)
			this->m_generic->Append(count);
	}
	inline void AllocateIncrementalGenericInfoPoolTo(int count) {
count -= this->m_incrementalGeneric->Capacity();
if(count > 0)
			this->m_incrementalGeneric->Append(count);
	}
	inline void AllocateOLSFONDItemInfoPoolTo(int count) {
count -= this->m_oLSFONDItems->Capacity();
if(count > 0)
			this->m_oLSFONDItems->Append(count);
	}
	inline void AllocateOLSFONDInfoPoolTo(int count) {
count -= this->m_oLSFOND->Capacity();
if(count > 0)
			this->m_oLSFOND->Append(count);
	}
	inline void AllocateOLSCURRItemInfoPoolTo(int count) {
count -= this->m_oLSCURRItems->Capacity();
if(count > 0)
			this->m_oLSCURRItems->Append(count);
	}
	inline void AllocateOLSCURRInfoPoolTo(int count) {
count -= this->m_oLSCURR->Capacity();
if(count > 0)
			this->m_oLSCURR->Append(count);
	}
	inline void AllocateTLSFONDItemInfoPoolTo(int count) {
count -= this->m_tLSFONDItems->Capacity();
if(count > 0)
			this->m_tLSFONDItems->Append(count);
	}
	inline void AllocateTLSFONDInfoPoolTo(int count) {
count -= this->m_tLSFOND->Capacity();
if(count > 0)
			this->m_tLSFOND->Append(count);
	}
	inline void AllocateTLSCURRItemInfoPoolTo(int count) {
count -= this->m_tLSCURRItems->Capacity();
if(count > 0)
			this->m_tLSCURRItems->Append(count);
	}
	inline void AllocateTLSCURRInfoPoolTo(int count) {
count -= this->m_tLSCURR->Capacity();
if(count > 0)
			this->m_tLSCURR->Append(count);
	}
	inline void AllocateIncrementalMSRFONDInfoPoolTo(int count) {
count -= this->m_incrementalMSRFOND->Capacity();
if(count > 0)
			this->m_incrementalMSRFOND->Append(count);
	}
	inline void AllocateIncrementalMSRCURRInfoPoolTo(int count) {
count -= this->m_incrementalMSRCURR->Capacity();
if(count > 0)
			this->m_incrementalMSRCURR->Append(count);
	}
	inline void AllocateIncrementalOLRFONDInfoPoolTo(int count) {
count -= this->m_incrementalOLRFOND->Capacity();
if(count > 0)
			this->m_incrementalOLRFOND->Append(count);
	}
	inline void AllocateIncrementalOLRCURRInfoPoolTo(int count) {
count -= this->m_incrementalOLRCURR->Capacity();
if(count > 0)
			this->m_incrementalOLRCURR->Append(count);
	}
	inline void AllocateIncrementalTLRFONDInfoPoolTo(int count) {
count -= this->m_incrementalTLRFOND->Capacity();
if(count > 0)
			this->m_incrementalTLRFOND->Append(count);
	}
	inline void AllocateIncrementalTLRCURRInfoPoolTo(int count) {
count -= this->m_incrementalTLRCURR->Capacity();
if(count > 0)
			this->m_incrementalTLRCURR->Append(count);
	}
	inline void AllocateSecurityDefinitionGroupInstrAttribItemInfoPoolTo(int count) {
count -= this->m_securityDefinitionGroupInstrAttribItems->Capacity();
if(count > 0)
			this->m_securityDefinitionGroupInstrAttribItems->Append(count);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPoolTo(int count) {
count -= this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Capacity();
if(count > 0)
			this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpItemInfoPoolTo(int count) {
count -= this->m_securityDefinitionMarketSegmentGrpItems->Capacity();
if(count > 0)
			this->m_securityDefinitionMarketSegmentGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInfoPoolTo(int count) {
count -= this->m_securityDefinition->Capacity();
if(count > 0)
			this->m_securityDefinition->Append(count);
	}
	inline void AllocateSecurityStatusInfoPoolTo(int count) {
count -= this->m_securityStatus->Capacity();
if(count > 0)
			this->m_securityStatus->Append(count);
	}
	inline void AllocateTradingSessionStatusInfoPoolTo(int count) {
count -= this->m_tradingSessionStatus->Capacity();
if(count > 0)
			this->m_tradingSessionStatus->Append(count);
	}
	inline void AllocateHeartbeatInfoPoolTo(int count) {
count -= this->m_heartbeat->Capacity();
if(count > 0)
			this->m_heartbeat->Append(count);
	}
	inline AutoAllocatePointerList<FastLogonInfo>* GetLogonInfoPool() {
		return this->m_logon;
	}
	inline AutoAllocatePointerList<FastLogoutInfo>* GetLogoutInfoPool() {
		return this->m_logout;
	}
	inline AutoAllocatePointerList<FastGenericItemInfo>* GetGenericItemInfoPool() {
		return this->m_genericItems;
	}
	inline AutoAllocatePointerList<FastGenericInfo>* GetGenericInfoPool() {
		return this->m_generic;
	}
	inline AutoAllocatePointerList<FastIncrementalGenericInfo>* GetIncrementalGenericInfoPool() {
		return this->m_incrementalGeneric;
	}
	inline AutoAllocatePointerList<FastOLSFONDItemInfo>* GetOLSFONDItemInfoPool() {
		return this->m_oLSFONDItems;
	}
	inline AutoAllocatePointerList<FastOLSFONDInfo>* GetOLSFONDInfoPool() {
		return this->m_oLSFOND;
	}
	inline AutoAllocatePointerList<FastOLSCURRItemInfo>* GetOLSCURRItemInfoPool() {
		return this->m_oLSCURRItems;
	}
	inline AutoAllocatePointerList<FastOLSCURRInfo>* GetOLSCURRInfoPool() {
		return this->m_oLSCURR;
	}
	inline AutoAllocatePointerList<FastTLSFONDItemInfo>* GetTLSFONDItemInfoPool() {
		return this->m_tLSFONDItems;
	}
	inline AutoAllocatePointerList<FastTLSFONDInfo>* GetTLSFONDInfoPool() {
		return this->m_tLSFOND;
	}
	inline AutoAllocatePointerList<FastTLSCURRItemInfo>* GetTLSCURRItemInfoPool() {
		return this->m_tLSCURRItems;
	}
	inline AutoAllocatePointerList<FastTLSCURRInfo>* GetTLSCURRInfoPool() {
		return this->m_tLSCURR;
	}
	inline AutoAllocatePointerList<FastIncrementalMSRFONDInfo>* GetIncrementalMSRFONDInfoPool() {
		return this->m_incrementalMSRFOND;
	}
	inline AutoAllocatePointerList<FastIncrementalMSRCURRInfo>* GetIncrementalMSRCURRInfoPool() {
		return this->m_incrementalMSRCURR;
	}
	inline AutoAllocatePointerList<FastIncrementalOLRFONDInfo>* GetIncrementalOLRFONDInfoPool() {
		return this->m_incrementalOLRFOND;
	}
	inline AutoAllocatePointerList<FastIncrementalOLRCURRInfo>* GetIncrementalOLRCURRInfoPool() {
		return this->m_incrementalOLRCURR;
	}
	inline AutoAllocatePointerList<FastIncrementalTLRFONDInfo>* GetIncrementalTLRFONDInfoPool() {
		return this->m_incrementalTLRFOND;
	}
	inline AutoAllocatePointerList<FastIncrementalTLRCURRInfo>* GetIncrementalTLRCURRInfoPool() {
		return this->m_incrementalTLRCURR;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>* GetSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_securityDefinitionGroupInstrAttribItems;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>* GetSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_securityDefinitionMarketSegmentGrpItems;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionInfo>* GetSecurityDefinitionInfoPool() {
		return this->m_securityDefinition;
	}
	inline AutoAllocatePointerList<FastSecurityStatusInfo>* GetSecurityStatusInfoPool() {
		return this->m_securityStatus;
	}
	inline AutoAllocatePointerList<FastTradingSessionStatusInfo>* GetTradingSessionStatusInfoPool() {
		return this->m_tradingSessionStatus;
	}
	inline AutoAllocatePointerList<FastHeartbeatInfo>* GetHeartbeatInfoPool() {
		return this->m_heartbeat;
	}
};
class FastOLSFONDItemInfoPresenceIndices{
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
class FastOLSCURRItemInfoPresenceIndices{
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
class FastTLSFONDItemInfoPresenceIndices{
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
class FastTLSCURRItemInfoPresenceIndices{
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
class FastIncrementalOLRFONDItemInfoPresenceIndices{
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
class FastIncrementalOLRCURRItemInfoPresenceIndices{
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
class FastLogonInfoNullIndices{
public:
	static const UINT64 UsernameNullIndex = NULL_MAP_INDEX0;
	static const UINT64 PasswordNullIndex = NULL_MAP_INDEX1;
};
class FastLogoutInfoNullIndices{
public:
	static const UINT64 TextNullIndex = NULL_MAP_INDEX0;
};
class FastGenericItemInfoNullIndices{
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
class FastGenericInfoNullIndices{
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
class FastIncrementalGenericItemInfoNullIndices{
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
class FastOLSFONDItemInfoNullIndices{
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
class FastOLSFONDInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX6;
};
class FastOLSCURRItemInfoNullIndices{
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
class FastOLSCURRInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
};
class FastTLSFONDItemInfoNullIndices{
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
class FastTLSFONDInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX6;
};
class FastTLSCURRItemInfoNullIndices{
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
class FastTLSCURRInfoNullIndices{
public:
	static const UINT64 LastMsgSeqNumProcessedNullIndex = NULL_MAP_INDEX0;
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX1;
	static const UINT64 RouteFirstNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesStatusNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDSecurityTradingStatusNullIndex = NULL_MAP_INDEX5;
};
class FastIncrementalMSRFONDItemInfoNullIndices{
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
class FastIncrementalMSRFONDInfoNullIndices{
public:
	static const UINT64 LastUpdateTimeNullIndex = NULL_MAP_INDEX0;
};
class FastIncrementalMSRCURRItemInfoNullIndices{
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
class FastIncrementalMSRCURRInfoNullIndices{
public:
	static const UINT64 LastUpdateTimeNullIndex = NULL_MAP_INDEX0;
};
class FastIncrementalOLRFONDItemInfoNullIndices{
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
class FastIncrementalOLRCURRItemInfoNullIndices{
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
class FastIncrementalTLRFONDItemInfoNullIndices{
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
class FastIncrementalTLRCURRItemInfoNullIndices{
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
class FastSecurityDefinitionGroupInstrAttribItemInfoNullIndices{
public:
	static const UINT64 InstrAttribValueNullIndex = NULL_MAP_INDEX0;
};
class FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoNullIndices{
public:
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX1;
	static const UINT64 OrderNoteNullIndex = NULL_MAP_INDEX2;
};
class FastSecurityDefinitionMarketSegmentGrpItemInfoNullIndices{
public:
	static const UINT64 RoundLotNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TradingSessionRulesGrpNullIndex = NULL_MAP_INDEX1;
};
class FastSecurityDefinitionInfoNullIndices{
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
class FastSecurityStatusInfoNullIndices{
public:
	static const UINT64 TradingSessionIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TradingSessionSubIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX2;
	static const UINT64 AuctionIndicatorNullIndex = NULL_MAP_INDEX3;
};
class FastTradingSessionStatusInfoNullIndices{
public:
	static const UINT64 TextNullIndex = NULL_MAP_INDEX0;
};
#pragma endregion

#pragma region Spectra_Message_Info_Structures_Definition_GeneratedCode

#pragma endregion

#endif //HFT_ROBOT_FASTTYPES_H
