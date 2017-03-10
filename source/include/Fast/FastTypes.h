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
	char							Currency[4];			// id=15  presence=optional  
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
	AutoAllocatePointerList<FastLogonInfo>				*m_fastLogon;
	AutoAllocatePointerList<FastLogoutInfo>				*m_fastLogout;
	AutoAllocatePointerList<FastGenericItemInfo>				*m_fastGenericItems;
	AutoAllocatePointerList<FastGenericInfo>				*m_fastGeneric;
	AutoAllocatePointerList<FastIncrementalGenericInfo>				*m_fastIncrementalGeneric;
	AutoAllocatePointerList<FastOLSFONDItemInfo>				*m_fastOLSFONDItems;
	AutoAllocatePointerList<FastOLSFONDInfo>				*m_fastOLSFOND;
	AutoAllocatePointerList<FastOLSCURRItemInfo>				*m_fastOLSCURRItems;
	AutoAllocatePointerList<FastOLSCURRInfo>				*m_fastOLSCURR;
	AutoAllocatePointerList<FastTLSFONDItemInfo>				*m_fastTLSFONDItems;
	AutoAllocatePointerList<FastTLSFONDInfo>				*m_fastTLSFOND;
	AutoAllocatePointerList<FastTLSCURRItemInfo>				*m_fastTLSCURRItems;
	AutoAllocatePointerList<FastTLSCURRInfo>				*m_fastTLSCURR;
	AutoAllocatePointerList<FastIncrementalMSRFONDInfo>				*m_fastIncrementalMSRFOND;
	AutoAllocatePointerList<FastIncrementalMSRCURRInfo>				*m_fastIncrementalMSRCURR;
	AutoAllocatePointerList<FastIncrementalOLRFONDInfo>				*m_fastIncrementalOLRFOND;
	AutoAllocatePointerList<FastIncrementalOLRCURRInfo>				*m_fastIncrementalOLRCURR;
	AutoAllocatePointerList<FastIncrementalTLRFONDInfo>				*m_fastIncrementalTLRFOND;
	AutoAllocatePointerList<FastIncrementalTLRCURRInfo>				*m_fastIncrementalTLRCURR;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>				*m_fastSecurityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>				*m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>				*m_fastSecurityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionInfo>				*m_fastSecurityDefinition;
	AutoAllocatePointerList<FastSecurityStatusInfo>				*m_fastSecurityStatus;
	AutoAllocatePointerList<FastTradingSessionStatusInfo>				*m_fastTradingSessionStatus;
	AutoAllocatePointerList<FastHeartbeatInfo>				*m_fastHeartbeat;
public:
	 static FastObjectsAllocationInfo *Default;
	FastObjectsAllocationInfo(int count) {
		this->m_fastLogon = new AutoAllocatePointerList<FastLogonInfo>(count, count, "FastLogonInfo");
		this->m_fastLogout = new AutoAllocatePointerList<FastLogoutInfo>(count, count, "FastLogoutInfo");
		this->m_fastGenericItems = new AutoAllocatePointerList<FastGenericItemInfo>(count, count, "FastGenericItemInfo");
		this->m_fastGeneric = new AutoAllocatePointerList<FastGenericInfo>(count, count, "FastGenericInfo");
		this->m_fastIncrementalGeneric = new AutoAllocatePointerList<FastIncrementalGenericInfo>(count, count, "FastIncrementalGenericInfo");
		this->m_fastOLSFONDItems = new AutoAllocatePointerList<FastOLSFONDItemInfo>(count, count, "FastOLSFONDItemInfo");
		this->m_fastOLSFOND = new AutoAllocatePointerList<FastOLSFONDInfo>(count, count, "FastOLSFONDInfo");
		this->m_fastOLSCURRItems = new AutoAllocatePointerList<FastOLSCURRItemInfo>(count, count, "FastOLSCURRItemInfo");
		this->m_fastOLSCURR = new AutoAllocatePointerList<FastOLSCURRInfo>(count, count, "FastOLSCURRInfo");
		this->m_fastTLSFONDItems = new AutoAllocatePointerList<FastTLSFONDItemInfo>(count, count, "FastTLSFONDItemInfo");
		this->m_fastTLSFOND = new AutoAllocatePointerList<FastTLSFONDInfo>(count, count, "FastTLSFONDInfo");
		this->m_fastTLSCURRItems = new AutoAllocatePointerList<FastTLSCURRItemInfo>(count, count, "FastTLSCURRItemInfo");
		this->m_fastTLSCURR = new AutoAllocatePointerList<FastTLSCURRInfo>(count, count, "FastTLSCURRInfo");
		this->m_fastIncrementalMSRFOND = new AutoAllocatePointerList<FastIncrementalMSRFONDInfo>(count, count, "FastIncrementalMSRFONDInfo");
		this->m_fastIncrementalMSRCURR = new AutoAllocatePointerList<FastIncrementalMSRCURRInfo>(count, count, "FastIncrementalMSRCURRInfo");
		this->m_fastIncrementalOLRFOND = new AutoAllocatePointerList<FastIncrementalOLRFONDInfo>(count, count, "FastIncrementalOLRFONDInfo");
		this->m_fastIncrementalOLRCURR = new AutoAllocatePointerList<FastIncrementalOLRCURRInfo>(count, count, "FastIncrementalOLRCURRInfo");
		this->m_fastIncrementalTLRFOND = new AutoAllocatePointerList<FastIncrementalTLRFONDInfo>(count, count, "FastIncrementalTLRFONDInfo");
		this->m_fastIncrementalTLRCURR = new AutoAllocatePointerList<FastIncrementalTLRCURRInfo>(count, count, "FastIncrementalTLRCURRInfo");
		this->m_fastSecurityDefinitionGroupInstrAttribItems = new AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>(count, count, "FastSecurityDefinitionGroupInstrAttribItemInfo");
		this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(count, count, "FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo");
		this->m_fastSecurityDefinitionMarketSegmentGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>(count, count, "FastSecurityDefinitionMarketSegmentGrpItemInfo");
		this->m_fastSecurityDefinition = new AutoAllocatePointerList<FastSecurityDefinitionInfo>(count, count, "FastSecurityDefinitionInfo");
		this->m_fastSecurityStatus = new AutoAllocatePointerList<FastSecurityStatusInfo>(count, count, "FastSecurityStatusInfo");
		this->m_fastTradingSessionStatus = new AutoAllocatePointerList<FastTradingSessionStatusInfo>(count, count, "FastTradingSessionStatusInfo");
		this->m_fastHeartbeat = new AutoAllocatePointerList<FastHeartbeatInfo>(count, count, "FastHeartbeatInfo");
	}
	inline void AllocateLogonInfoPool(int count, int addCount) {
		this->m_fastLogon->Append(count);
		this->m_fastLogon->AddCount(addCount);
	}
	inline void AllocateLogoutInfoPool(int count, int addCount) {
		this->m_fastLogout->Append(count);
		this->m_fastLogout->AddCount(addCount);
	}
	inline void AllocateGenericItemInfoPool(int count, int addCount) {
		this->m_fastGenericItems->Append(count);
		this->m_fastGenericItems->AddCount(addCount);
	}
	inline void AllocateGenericInfoPool(int count, int addCount) {
		this->m_fastGeneric->Append(count);
		this->m_fastGeneric->AddCount(addCount);
	}
	inline void AllocateIncrementalGenericInfoPool(int count, int addCount) {
		this->m_fastIncrementalGeneric->Append(count);
		this->m_fastIncrementalGeneric->AddCount(addCount);
	}
	inline void AllocateOLSFONDItemInfoPool(int count, int addCount) {
		this->m_fastOLSFONDItems->Append(count);
		this->m_fastOLSFONDItems->AddCount(addCount);
	}
	inline void AllocateOLSFONDInfoPool(int count, int addCount) {
		this->m_fastOLSFOND->Append(count);
		this->m_fastOLSFOND->AddCount(addCount);
	}
	inline void AllocateOLSCURRItemInfoPool(int count, int addCount) {
		this->m_fastOLSCURRItems->Append(count);
		this->m_fastOLSCURRItems->AddCount(addCount);
	}
	inline void AllocateOLSCURRInfoPool(int count, int addCount) {
		this->m_fastOLSCURR->Append(count);
		this->m_fastOLSCURR->AddCount(addCount);
	}
	inline void AllocateTLSFONDItemInfoPool(int count, int addCount) {
		this->m_fastTLSFONDItems->Append(count);
		this->m_fastTLSFONDItems->AddCount(addCount);
	}
	inline void AllocateTLSFONDInfoPool(int count, int addCount) {
		this->m_fastTLSFOND->Append(count);
		this->m_fastTLSFOND->AddCount(addCount);
	}
	inline void AllocateTLSCURRItemInfoPool(int count, int addCount) {
		this->m_fastTLSCURRItems->Append(count);
		this->m_fastTLSCURRItems->AddCount(addCount);
	}
	inline void AllocateTLSCURRInfoPool(int count, int addCount) {
		this->m_fastTLSCURR->Append(count);
		this->m_fastTLSCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalMSRFONDInfoPool(int count, int addCount) {
		this->m_fastIncrementalMSRFOND->Append(count);
		this->m_fastIncrementalMSRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalMSRCURRInfoPool(int count, int addCount) {
		this->m_fastIncrementalMSRCURR->Append(count);
		this->m_fastIncrementalMSRCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalOLRFONDInfoPool(int count, int addCount) {
		this->m_fastIncrementalOLRFOND->Append(count);
		this->m_fastIncrementalOLRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalOLRCURRInfoPool(int count, int addCount) {
		this->m_fastIncrementalOLRCURR->Append(count);
		this->m_fastIncrementalOLRCURR->AddCount(addCount);
	}
	inline void AllocateIncrementalTLRFONDInfoPool(int count, int addCount) {
		this->m_fastIncrementalTLRFOND->Append(count);
		this->m_fastIncrementalTLRFOND->AddCount(addCount);
	}
	inline void AllocateIncrementalTLRCURRInfoPool(int count, int addCount) {
		this->m_fastIncrementalTLRCURR->Append(count);
		this->m_fastIncrementalTLRCURR->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionGroupInstrAttribItemInfoPool(int count, int addCount) {
		this->m_fastSecurityDefinitionGroupInstrAttribItems->Append(count);
		this->m_fastSecurityDefinitionGroupInstrAttribItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool(int count, int addCount) {
		this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Append(count);
		this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpItemInfoPool(int count, int addCount) {
		this->m_fastSecurityDefinitionMarketSegmentGrpItems->Append(count);
		this->m_fastSecurityDefinitionMarketSegmentGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInfoPool(int count, int addCount) {
		this->m_fastSecurityDefinition->Append(count);
		this->m_fastSecurityDefinition->AddCount(addCount);
	}
	inline void AllocateSecurityStatusInfoPool(int count, int addCount) {
		this->m_fastSecurityStatus->Append(count);
		this->m_fastSecurityStatus->AddCount(addCount);
	}
	inline void AllocateTradingSessionStatusInfoPool(int count, int addCount) {
		this->m_fastTradingSessionStatus->Append(count);
		this->m_fastTradingSessionStatus->AddCount(addCount);
	}
	inline void AllocateHeartbeatInfoPool(int count, int addCount) {
		this->m_fastHeartbeat->Append(count);
		this->m_fastHeartbeat->AddCount(addCount);
	}
	inline void AllocateLogonInfoPoolTo(int count) {
		count -= this->m_fastLogon->Capacity();
		if(count > 0)
			this->m_fastLogon->Append(count);
	}
	inline void AllocateLogoutInfoPoolTo(int count) {
		count -= this->m_fastLogout->Capacity();
		if(count > 0)
			this->m_fastLogout->Append(count);
	}
	inline void AllocateGenericItemInfoPoolTo(int count) {
		count -= this->m_fastGenericItems->Capacity();
		if(count > 0)
			this->m_fastGenericItems->Append(count);
	}
	inline void AllocateGenericInfoPoolTo(int count) {
		count -= this->m_fastGeneric->Capacity();
		if(count > 0)
			this->m_fastGeneric->Append(count);
	}
	inline void AllocateIncrementalGenericInfoPoolTo(int count) {
		count -= this->m_fastIncrementalGeneric->Capacity();
		if(count > 0)
			this->m_fastIncrementalGeneric->Append(count);
	}
	inline void AllocateOLSFONDItemInfoPoolTo(int count) {
		count -= this->m_fastOLSFONDItems->Capacity();
		if(count > 0)
			this->m_fastOLSFONDItems->Append(count);
	}
	inline void AllocateOLSFONDInfoPoolTo(int count) {
		count -= this->m_fastOLSFOND->Capacity();
		if(count > 0)
			this->m_fastOLSFOND->Append(count);
	}
	inline void AllocateOLSCURRItemInfoPoolTo(int count) {
		count -= this->m_fastOLSCURRItems->Capacity();
		if(count > 0)
			this->m_fastOLSCURRItems->Append(count);
	}
	inline void AllocateOLSCURRInfoPoolTo(int count) {
		count -= this->m_fastOLSCURR->Capacity();
		if(count > 0)
			this->m_fastOLSCURR->Append(count);
	}
	inline void AllocateTLSFONDItemInfoPoolTo(int count) {
		count -= this->m_fastTLSFONDItems->Capacity();
		if(count > 0)
			this->m_fastTLSFONDItems->Append(count);
	}
	inline void AllocateTLSFONDInfoPoolTo(int count) {
		count -= this->m_fastTLSFOND->Capacity();
		if(count > 0)
			this->m_fastTLSFOND->Append(count);
	}
	inline void AllocateTLSCURRItemInfoPoolTo(int count) {
		count -= this->m_fastTLSCURRItems->Capacity();
		if(count > 0)
			this->m_fastTLSCURRItems->Append(count);
	}
	inline void AllocateTLSCURRInfoPoolTo(int count) {
		count -= this->m_fastTLSCURR->Capacity();
		if(count > 0)
			this->m_fastTLSCURR->Append(count);
	}
	inline void AllocateIncrementalMSRFONDInfoPoolTo(int count) {
		count -= this->m_fastIncrementalMSRFOND->Capacity();
		if(count > 0)
			this->m_fastIncrementalMSRFOND->Append(count);
	}
	inline void AllocateIncrementalMSRCURRInfoPoolTo(int count) {
		count -= this->m_fastIncrementalMSRCURR->Capacity();
		if(count > 0)
			this->m_fastIncrementalMSRCURR->Append(count);
	}
	inline void AllocateIncrementalOLRFONDInfoPoolTo(int count) {
		count -= this->m_fastIncrementalOLRFOND->Capacity();
		if(count > 0)
			this->m_fastIncrementalOLRFOND->Append(count);
	}
	inline void AllocateIncrementalOLRCURRInfoPoolTo(int count) {
		count -= this->m_fastIncrementalOLRCURR->Capacity();
		if(count > 0)
			this->m_fastIncrementalOLRCURR->Append(count);
	}
	inline void AllocateIncrementalTLRFONDInfoPoolTo(int count) {
		count -= this->m_fastIncrementalTLRFOND->Capacity();
		if(count > 0)
			this->m_fastIncrementalTLRFOND->Append(count);
	}
	inline void AllocateIncrementalTLRCURRInfoPoolTo(int count) {
		count -= this->m_fastIncrementalTLRCURR->Capacity();
		if(count > 0)
			this->m_fastIncrementalTLRCURR->Append(count);
	}
	inline void AllocateSecurityDefinitionGroupInstrAttribItemInfoPoolTo(int count) {
		count -= this->m_fastSecurityDefinitionGroupInstrAttribItems->Capacity();
		if(count > 0)
			this->m_fastSecurityDefinitionGroupInstrAttribItems->Append(count);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPoolTo(int count) {
		count -= this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Capacity();
		if(count > 0)
			this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionMarketSegmentGrpItemInfoPoolTo(int count) {
		count -= this->m_fastSecurityDefinitionMarketSegmentGrpItems->Capacity();
		if(count > 0)
			this->m_fastSecurityDefinitionMarketSegmentGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInfoPoolTo(int count) {
		count -= this->m_fastSecurityDefinition->Capacity();
		if(count > 0)
			this->m_fastSecurityDefinition->Append(count);
	}
	inline void AllocateSecurityStatusInfoPoolTo(int count) {
		count -= this->m_fastSecurityStatus->Capacity();
		if(count > 0)
			this->m_fastSecurityStatus->Append(count);
	}
	inline void AllocateTradingSessionStatusInfoPoolTo(int count) {
		count -= this->m_fastTradingSessionStatus->Capacity();
		if(count > 0)
			this->m_fastTradingSessionStatus->Append(count);
	}
	inline void AllocateHeartbeatInfoPoolTo(int count) {
		count -= this->m_fastHeartbeat->Capacity();
		if(count > 0)
			this->m_fastHeartbeat->Append(count);
	}
	inline AutoAllocatePointerList<FastLogonInfo>* GetFastLogonInfoPool() {
		return this->m_fastLogon;
	}
	inline AutoAllocatePointerList<FastLogoutInfo>* GetFastLogoutInfoPool() {
		return this->m_fastLogout;
	}
	inline AutoAllocatePointerList<FastGenericItemInfo>* GetFastGenericItemInfoPool() {
		return this->m_fastGenericItems;
	}
	inline AutoAllocatePointerList<FastGenericInfo>* GetFastGenericInfoPool() {
		return this->m_fastGeneric;
	}
	inline AutoAllocatePointerList<FastIncrementalGenericInfo>* GetFastIncrementalGenericInfoPool() {
		return this->m_fastIncrementalGeneric;
	}
	inline AutoAllocatePointerList<FastOLSFONDItemInfo>* GetFastOLSFONDItemInfoPool() {
		return this->m_fastOLSFONDItems;
	}
	inline AutoAllocatePointerList<FastOLSFONDInfo>* GetFastOLSFONDInfoPool() {
		return this->m_fastOLSFOND;
	}
	inline AutoAllocatePointerList<FastOLSCURRItemInfo>* GetFastOLSCURRItemInfoPool() {
		return this->m_fastOLSCURRItems;
	}
	inline AutoAllocatePointerList<FastOLSCURRInfo>* GetFastOLSCURRInfoPool() {
		return this->m_fastOLSCURR;
	}
	inline AutoAllocatePointerList<FastTLSFONDItemInfo>* GetFastTLSFONDItemInfoPool() {
		return this->m_fastTLSFONDItems;
	}
	inline AutoAllocatePointerList<FastTLSFONDInfo>* GetFastTLSFONDInfoPool() {
		return this->m_fastTLSFOND;
	}
	inline AutoAllocatePointerList<FastTLSCURRItemInfo>* GetFastTLSCURRItemInfoPool() {
		return this->m_fastTLSCURRItems;
	}
	inline AutoAllocatePointerList<FastTLSCURRInfo>* GetFastTLSCURRInfoPool() {
		return this->m_fastTLSCURR;
	}
	inline AutoAllocatePointerList<FastIncrementalMSRFONDInfo>* GetFastIncrementalMSRFONDInfoPool() {
		return this->m_fastIncrementalMSRFOND;
	}
	inline AutoAllocatePointerList<FastIncrementalMSRCURRInfo>* GetFastIncrementalMSRCURRInfoPool() {
		return this->m_fastIncrementalMSRCURR;
	}
	inline AutoAllocatePointerList<FastIncrementalOLRFONDInfo>* GetFastIncrementalOLRFONDInfoPool() {
		return this->m_fastIncrementalOLRFOND;
	}
	inline AutoAllocatePointerList<FastIncrementalOLRCURRInfo>* GetFastIncrementalOLRCURRInfoPool() {
		return this->m_fastIncrementalOLRCURR;
	}
	inline AutoAllocatePointerList<FastIncrementalTLRFONDInfo>* GetFastIncrementalTLRFONDInfoPool() {
		return this->m_fastIncrementalTLRFOND;
	}
	inline AutoAllocatePointerList<FastIncrementalTLRCURRInfo>* GetFastIncrementalTLRCURRInfoPool() {
		return this->m_fastIncrementalTLRCURR;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>* GetFastSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_fastSecurityDefinitionGroupInstrAttribItems;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>* GetFastSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_fastSecurityDefinitionMarketSegmentGrpItems;
	}
	inline AutoAllocatePointerList<FastSecurityDefinitionInfo>* GetFastSecurityDefinitionInfoPool() {
		return this->m_fastSecurityDefinition;
	}
	inline AutoAllocatePointerList<FastSecurityStatusInfo>* GetFastSecurityStatusInfoPool() {
		return this->m_fastSecurityStatus;
	}
	inline AutoAllocatePointerList<FastTradingSessionStatusInfo>* GetFastTradingSessionStatusInfoPool() {
		return this->m_fastTradingSessionStatus;
	}
	inline AutoAllocatePointerList<FastHeartbeatInfo>* GetFastHeartbeatInfoPool() {
		return this->m_fastHeartbeat;
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
class SpectraSnapshotInfo {
public:
	UINT64				PresenceMap;
	UINT64				NullMap;
	int				TemplateId;
	UINT32				RptSeq;
	UINT32				LastFragment;
	UINT32				RouteFirst;
	UINT32				LastMsgSeqNumProcessed;
	UINT64				SendingTime;
	char				Symbol[32];
	int					SymbolLength;
	UINT32				TradingSessionID;
	SpectraSnapshotInfo() {
		this->PresenceMap = 0;
		this->NullMap = 0;
	}
};

class SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>							*Allocator;
	bool							Used;
	UINT32							MDUpdateAction;			// id=279  
	char							MDEntryType[4];			// id=269  
	int							MDEntryTypeLength = 0;
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							Symbol[16];			// id=55  presence=optional  
	int							SymbolLength = 0;
	char							SecurityGroup[16];			// id=1151  presence=optional  
	int							SecurityGroupLength = 0;
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional  
	UINT32							RptSeq;			// id=83  
	UINT32							MarketDepth;			// id=264  presence=optional  
	UINT32							MDPriceLevel;			// id=1023  presence=optional  
	UINT64							MDEntryID;			// id=278  presence=optional  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	UINT64							MDEntrySize;			// id=271  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT64							MDEntryTime;			// id=273  
	INT32							NumberOfOrders;			// id=346  presence=optional  
	char							MDEntryTradeType[4];			// id=20003  presence=optional  
	int							MDEntryTradeTypeLength = 0;
	INT32							TrdType;			// id=828  presence=optional  
	Decimal							LastPx;			// id=31  presence=optional  
	INT32							MDFlags;			// id=20017  presence=optional  
	char							Currency[4];			// id=15  presence=optional  
	int							CurrencyLength = 0;
	UINT64							Revision;			// id=20018  presence=optional  
	char							OrderSide[4];			// id=10504  presence=optional  
	int							OrderSideLength = 0;

	SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->SecurityGroup[0] = '\0';
		this->SecurityGroupLength = 0;
		this->MDEntryTradeType[0] = '\0';
		this->MDEntryTradeTypeLength = 0;
		this->Currency[0] = '\0';
		this->CurrencyLength = 0;
		this->OrderSide[0] = '\0';
		this->OrderSideLength = 0;
	}
	~SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo(){ }
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

class SpectraDefaultIncrementalRefreshMessageInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraDefaultIncrementalRefreshMessageInfo>							*Pointer;
	AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  presence=optional  
	int							MDEntriesCount;
	SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo* MDEntries[256];

	SpectraDefaultIncrementalRefreshMessageInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->MDEntriesCount = 0;
	}
	~SpectraDefaultIncrementalRefreshMessageInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class SpectraDefaultSnapshotMessageMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraDefaultSnapshotMessageMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraDefaultSnapshotMessageMDEntriesItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  
	int							MDEntryTypeLength = 0;
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
	int							MDEntryTradeTypeLength = 0;
	INT32							TrdType;			// id=828  presence=optional  
	INT32							MDFlags;			// id=20017  presence=optional  
	char							Currency[4];			// id=15  presence=optional  
	int							CurrencyLength = 0;
	char							OrderSide[4];			// id=10504  presence=optional  
	int							OrderSideLength = 0;

	SpectraDefaultSnapshotMessageMDEntriesItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
		this->MDEntryTradeType[0] = '\0';
		this->MDEntryTradeTypeLength = 0;
		this->Currency[0] = '\0';
		this->CurrencyLength = 0;
		this->OrderSide[0] = '\0';
		this->OrderSideLength = 0;
	}
	~SpectraDefaultSnapshotMessageMDEntriesItemInfo(){ }
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

class SpectraDefaultSnapshotMessageInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraDefaultSnapshotMessageInfo>							*Pointer;
	AutoAllocatePointerList<SpectraDefaultSnapshotMessageInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  presence=optional  
	UINT32							RptSeq;			// id=83  
	UINT32							TotNumReports;			// id=911  
	UINT32							LastMsgSeqNumProcessed;			// id=369  
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							Symbol[16];			// id=55  presence=optional  
	int							SymbolLength = 0;
	char							SecurityGroup[16];			// id=1151  presence=optional  
	int							SecurityGroupLength = 0;
	int							MDEntriesCount;
	SpectraDefaultSnapshotMessageMDEntriesItemInfo* MDEntries[256];

	SpectraDefaultSnapshotMessageInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->SecurityGroup[0] = '\0';
		this->SecurityGroupLength = 0;
		this->MDEntriesCount = 0;
	}
	~SpectraDefaultSnapshotMessageInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class SpectraSecurityDefinitionMDFeedTypesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionMDFeedTypesItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionMDFeedTypesItemInfo>							*Allocator;
	bool							Used;
	char							MDFeedType[16];			// id=1022  
	int							MDFeedTypeLength = 0;
	UINT32							MarketDepth;			// id=264  presence=optional  
	UINT32							MDBookType;			// id=1021  presence=optional  

	SpectraSecurityDefinitionMDFeedTypesItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDFeedType[0] = '\0';
		this->MDFeedTypeLength = 0;
	}
	~SpectraSecurityDefinitionMDFeedTypesItemInfo(){ }
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

class SpectraSecurityDefinitionUnderlyingsItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionUnderlyingsItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionUnderlyingsItemInfo>							*Allocator;
	bool							Used;
	char							UnderlyingSymbol[16];			// id=311  
	int							UnderlyingSymbolLength = 0;
	UINT64							UnderlyingSecurityID;			// id=309  presence=optional  

	SpectraSecurityDefinitionUnderlyingsItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->UnderlyingSymbol[0] = '\0';
		this->UnderlyingSymbolLength = 0;
	}
	~SpectraSecurityDefinitionUnderlyingsItemInfo(){ }
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

class SpectraSecurityDefinitionInstrumentLegsItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionInstrumentLegsItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentLegsItemInfo>							*Allocator;
	bool							Used;
	char							LegSymbol[16];			// id=600  
	int							LegSymbolLength = 0;
	UINT64							LegSecurityID;			// id=602  
	Decimal							LegRatioQty;			// id=623  

	SpectraSecurityDefinitionInstrumentLegsItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->LegSymbol[0] = '\0';
		this->LegSymbolLength = 0;
	}
	~SpectraSecurityDefinitionInstrumentLegsItemInfo(){ }
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

class SpectraSecurityDefinitionInstrumentAttributesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionInstrumentAttributesItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentAttributesItemInfo>							*Allocator;
	bool							Used;
	INT32							InstrAttribType;			// id=871  
	char							InstrAttribValue[16];			// id=872  
	int							InstrAttribValueLength = 0;

	SpectraSecurityDefinitionInstrumentAttributesItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->InstrAttribValue[0] = '\0';
		this->InstrAttribValueLength = 0;
	}
	~SpectraSecurityDefinitionInstrumentAttributesItemInfo(){ }
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

class SpectraSecurityDefinitionEvntGrpItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionEvntGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionEvntGrpItemInfo>							*Allocator;
	bool							Used;
	INT32							EventType;			// id=865  
	UINT32							EventDate;			// id=866  
	UINT64							EventTime;			// id=1145  

	SpectraSecurityDefinitionEvntGrpItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
	}
	~SpectraSecurityDefinitionEvntGrpItemInfo(){ }
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

class SpectraSecurityDefinitionInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = d
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							TotNumReports;			// id=911  
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	char							SecurityDesc[16];			// id=107  presence=optional  charset=unicode  
	int							SecurityDescLength = 0;
	UINT64							SecurityID;			// id=48  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							SecurityAltID[16];			// id=455  presence=optional  
	int							SecurityAltIDLength = 0;
	char							SecurityAltIDSource[16];			// id=456  presence=optional  
	int							SecurityAltIDSourceLength = 0;
	char							SecurityType[16];			// id=167  presence=optional  
	int							SecurityTypeLength = 0;
	char							CFICode[16];			// id=461  presence=optional  
	int							CFICodeLength = 0;
	Decimal							StrikePrice;			// id=202  presence=optional  
	Decimal							ContractMultiplier;			// id=231  presence=optional  
	UINT32							SecurityTradingStatus;			// id=326  presence=optional  
	char							Currency[4];			// id=15  presence=optional  
	int							CurrencyLength = 0;
	char							MarketID[16];			// id=1301    constant has constant value = MOEX
	int							MarketIDLength = 0;
	char							MarketSegmentID[16];			// id=1300  
	int							MarketSegmentIDLength = 0;
	UINT32							TradingSessionID;			// id=336  presence=optional  
	UINT32							ExchangeTradingSessionID;			// id=5842  presence=optional  
	Decimal							Volatility;			// id=5678  presence=optional  
	int							MDFeedTypesCount;
	SpectraSecurityDefinitionMDFeedTypesItemInfo* MDFeedTypes[256];
	int							UnderlyingsCount;			// presence=optional  
	SpectraSecurityDefinitionUnderlyingsItemInfo* Underlyings[256];			// presence=optional  
	Decimal							HighLimitPx;			// id=1149  presence=optional  
	Decimal							LowLimitPx;			// id=1148  presence=optional  
	Decimal							MinPriceIncrement;			// id=969  presence=optional  
	Decimal							MinPriceIncrementAmount;			// id=1146  presence=optional  
	Decimal							InitialMarginOnBuy;			// id=20002  presence=optional  
	Decimal							InitialMarginOnSell;			// id=20000  presence=optional  
	Decimal							InitialMarginSyntetic;			// id=20001  presence=optional  
	char							QuotationList[16];			// id=20005  presence=optional  
	int							QuotationListLength = 0;
	Decimal							TheorPrice;			// id=20006  presence=optional  
	Decimal							TheorPriceLimit;			// id=20007  presence=optional  
	int							InstrumentLegsCount;			// presence=optional  
	SpectraSecurityDefinitionInstrumentLegsItemInfo* InstrumentLegs[256];			// presence=optional  
	int							InstrumentAttributesCount;			// presence=optional  
	SpectraSecurityDefinitionInstrumentAttributesItemInfo* InstrumentAttributes[256];			// presence=optional  
	Decimal							UnderlyingQty;			// id=879  presence=optional  
	char							UnderlyingCurrency[16];			// id=318  presence=optional  
	int							UnderlyingCurrencyLength = 0;
	int							EvntGrpCount;			// presence=optional  
	SpectraSecurityDefinitionEvntGrpItemInfo* EvntGrp[256];			// presence=optional  
	UINT32							MaturityDate;			// id=541  presence=optional  
	UINT32							MaturityTime;			// id=1079  presence=optional  

	SpectraSecurityDefinitionInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
		this->SecurityDesc[0] = '\0';
		this->SecurityDescLength = 0;
		this->SecurityAltID[0] = '\0';
		this->SecurityAltIDLength = 0;
		this->SecurityAltIDSource[0] = '\0';
		this->SecurityAltIDSourceLength = 0;
		this->SecurityType[0] = '\0';
		this->SecurityTypeLength = 0;
		this->CFICode[0] = '\0';
		this->CFICodeLength = 0;
		this->Currency[0] = '\0';
		this->CurrencyLength = 0;
		this->MarketID[0] = '\0';
		this->MarketIDLength = 0;
		this->MarketSegmentID[0] = '\0';
		this->MarketSegmentIDLength = 0;
		this->MDFeedTypesCount = 0;
		this->UnderlyingsCount = 0;
		this->QuotationList[0] = '\0';
		this->QuotationListLength = 0;
		this->InstrumentLegsCount = 0;
		this->InstrumentAttributesCount = 0;
		this->UnderlyingCurrency[0] = '\0';
		this->UnderlyingCurrencyLength = 0;
		this->EvntGrpCount = 0;
	}
	~SpectraSecurityDefinitionInfo(){ }
	inline void Clear() {
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

class SpectraSecurityDefinitionUpdateReportInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityDefinitionUpdateReportInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityDefinitionUpdateReportInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = BP
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							SecurityID;			// id=48  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	Decimal							Volatility;			// id=5678  presence=optional  
	Decimal							TheorPrice;			// id=20006  presence=optional  
	Decimal							TheorPriceLimit;			// id=20007  presence=optional  

	SpectraSecurityDefinitionUpdateReportInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
	}
	~SpectraSecurityDefinitionUpdateReportInfo(){ }
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

class SpectraSecurityStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSecurityStatusInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = f
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							SecurityID;			// id=48  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	char							Symbol[16];			// id=55  
	int							SymbolLength = 0;
	UINT32							SecurityTradingStatus;			// id=326  presence=optional  
	Decimal							HighLimitPx;			// id=1149  presence=optional  
	Decimal							LowLimitPx;			// id=1148  presence=optional  
	Decimal							InitialMarginOnBuy;			// id=20002  presence=optional  
	Decimal							InitialMarginOnSell;			// id=20000  presence=optional  
	Decimal							InitialMarginSyntetic;			// id=20001  presence=optional  

	SpectraSecurityStatusInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->Symbol[0] = '\0';
		this->SymbolLength = 0;
	}
	~SpectraSecurityStatusInfo(){ }
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

class SpectraHeartbeatInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<SpectraHeartbeatInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = 0
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  

	SpectraHeartbeatInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
	}
	~SpectraHeartbeatInfo(){ }
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

class SpectraSequenceResetInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraSequenceResetInfo>							*Pointer;
	AutoAllocatePointerList<SpectraSequenceResetInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = 4
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							NewSeqNo;			// id=36  

	SpectraSequenceResetInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
	}
	~SpectraSequenceResetInfo(){ }
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

class SpectraTradingSessionStatusInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<SpectraTradingSessionStatusInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = h
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
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
	int							MarketIDLength = 0;
	char							MarketSegmentID[16];			// id=1300  
	int							MarketSegmentIDLength = 0;
	INT32							TradSesEvent;			// id=1368  presence=optional  

	SpectraTradingSessionStatusInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->MarketID[0] = '\0';
		this->MarketIDLength = 0;
		this->MarketSegmentID[0] = '\0';
		this->MarketSegmentIDLength = 0;
	}
	~SpectraTradingSessionStatusInfo(){ }
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

class SpectraNewsNewsTextItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraNewsNewsTextItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraNewsNewsTextItemInfo>							*Allocator;
	bool							Used;
	char							Text[512];			// id=58  charset=unicode  
	int							TextLength = 0;

	SpectraNewsNewsTextItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->Text[0] = '\0';
		this->TextLength = 0;
	}
	~SpectraNewsNewsTextItemInfo(){ }
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

class SpectraNewsInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraNewsInfo>							*Pointer;
	AutoAllocatePointerList<SpectraNewsInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = B
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  presence=optional  
	char							NewsId[16];			// id=1472  presence=optional  
	int							NewsIdLength = 0;
	UINT64							OrigTime;			// id=42  presence=optional  
	char							LanguageCode[16];			// id=1474  presence=optional  
	int							LanguageCodeLength = 0;
	UINT32							Urgency;			// id=61  presence=optional  
	char							Headline[16];			// id=148  charset=unicode  
	int							HeadlineLength = 0;
	char							MarketID[16];			// id=1301    constant has constant value = MOEX
	int							MarketIDLength = 0;
	char							MarketSegmentID[16];			// id=1300  presence=optional  
	int							MarketSegmentIDLength = 0;
	int							NewsTextCount;
	SpectraNewsNewsTextItemInfo* NewsText[256];

	SpectraNewsInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->NewsId[0] = '\0';
		this->NewsIdLength = 0;
		this->LanguageCode[0] = '\0';
		this->LanguageCodeLength = 0;
		this->Headline[0] = '\0';
		this->HeadlineLength = 0;
		this->MarketID[0] = '\0';
		this->MarketIDLength = 0;
		this->MarketSegmentID[0] = '\0';
		this->MarketSegmentIDLength = 0;
		this->NewsTextCount = 0;
	}
	~SpectraNewsInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->NewsTextCount; i++)
			this->NewsText[i]->ReleaseUnused();
	}
};

class SpectraOrdersLogMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraOrdersLogMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraOrdersLogMDEntriesItemInfo>							*Allocator;
	bool							Used;
	UINT32							MDUpdateAction;			// id=279  
	char							MDEntryType[4];			// id=269  
	int							MDEntryTypeLength = 0;
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

	SpectraOrdersLogMDEntriesItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
	}
	~SpectraOrdersLogMDEntriesItemInfo(){ }
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

class SpectraOrdersLogInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraOrdersLogInfo>							*Pointer;
	AutoAllocatePointerList<SpectraOrdersLogInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = X
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastFragment;			// id=893  
	int							MDEntriesCount;
	SpectraOrdersLogMDEntriesItemInfo* MDEntries[256];

	SpectraOrdersLogInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->MDEntriesCount = 0;
	}
	~SpectraOrdersLogInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class SpectraOrdersBookMDEntriesItemInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraOrdersBookMDEntriesItemInfo>							*Pointer;
	AutoAllocatePointerList<SpectraOrdersBookMDEntriesItemInfo>							*Allocator;
	bool							Used;
	char							MDEntryType[4];			// id=269  
	int							MDEntryTypeLength = 0;
	UINT64							MDEntryID;			// id=278  presence=optional  
	UINT32							MDEntryDate;			// id=272  presence=optional  
	UINT64							MDEntryTime;			// id=273  
	Decimal							MDEntryPx;			// id=270  presence=optional  
	UINT64							MDEntrySize;			// id=271  presence=optional  
	UINT64							TradeID;			// id=1003  presence=optional  
	UINT64							MDFlags;			// id=20017  presence=optional  

	SpectraOrdersBookMDEntriesItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->MDEntryType[0] = '\0';
		this->MDEntryTypeLength = 0;
	}
	~SpectraOrdersBookMDEntriesItemInfo(){ }
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

class SpectraOrdersBookInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraOrdersBookInfo>							*Pointer;
	AutoAllocatePointerList<SpectraOrdersBookInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = W
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  
	UINT32							RptSeq;			// id=83  presence=optional  
	UINT32							LastFragment;			// id=893  
	UINT32							RouteFirst;			// id=7944  
	UINT32							ExchangeTradingSessionID;			// id=5842  
	UINT64							SecurityID;			// id=48  presence=optional  
	UINT32							SecurityIDSource;			// id=22    constant has constant value = 8
	int							MDEntriesCount;
	SpectraOrdersBookMDEntriesItemInfo* MDEntries[256];

	SpectraOrdersBookInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->MDEntriesCount = 0;
	}
	~SpectraOrdersBookInfo(){ }
	inline void Clear() {
		this->Used = false;
		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		this->Allocator->FreeItem(this->Pointer);
		for(int i = 0; i < this->MDEntriesCount; i++)
			this->MDEntries[i]->ReleaseUnused();
	}
};

class SpectraLogonInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraLogonInfo>							*Pointer;
	AutoAllocatePointerList<SpectraLogonInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = A
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  

	SpectraLogonInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
	}
	~SpectraLogonInfo(){ }
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

class SpectraLogoutInfo{
public:
	UINT64							PresenceMap;
	UINT64							NullMap;
	LinkedPointer<SpectraLogoutInfo>							*Pointer;
	AutoAllocatePointerList<SpectraLogoutInfo>							*Allocator;
	bool							Used;
	char							ApplVerID[16];			// id=1128    constant has constant value = 9
	int							ApplVerIDLength = 0;
	char							MessageType[16];			// id=35    constant has constant value = 5
	int							MessageTypeLength = 0;
	char							SenderCompID[32];			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength = 0;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char							Text[512];			// id=58  presence=optional  
	int							TextLength = 0;

	SpectraLogoutInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->NullMap = 0;
		this->ApplVerID[0] = '\0';
		this->ApplVerIDLength = 0;
		this->MessageType[0] = '\0';
		this->MessageTypeLength = 0;
		this->SenderCompID[0] = '\0';
		this->SenderCompIDLength = 0;
		this->Text[0] = '\0';
		this->TextLength = 0;
	}
	~SpectraLogoutInfo(){ }
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

class SpectraObjectsAllocationInfo {
	AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>				*m_spectraDefaultIncrementalRefreshMessageMDEntriesItems;
	AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageInfo>				*m_spectraDefaultIncrementalRefreshMessage;
	AutoAllocatePointerList<SpectraDefaultSnapshotMessageMDEntriesItemInfo>				*m_spectraDefaultSnapshotMessageMDEntriesItems;
	AutoAllocatePointerList<SpectraDefaultSnapshotMessageInfo>				*m_spectraDefaultSnapshotMessage;
	AutoAllocatePointerList<SpectraSecurityDefinitionMDFeedTypesItemInfo>				*m_spectraSecurityDefinitionMDFeedTypesItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionUnderlyingsItemInfo>				*m_spectraSecurityDefinitionUnderlyingsItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentLegsItemInfo>				*m_spectraSecurityDefinitionInstrumentLegsItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentAttributesItemInfo>				*m_spectraSecurityDefinitionInstrumentAttributesItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionEvntGrpItemInfo>				*m_spectraSecurityDefinitionEvntGrpItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionInfo>				*m_spectraSecurityDefinition;
	AutoAllocatePointerList<SpectraSecurityDefinitionUpdateReportInfo>				*m_spectraSecurityDefinitionUpdateReport;
	AutoAllocatePointerList<SpectraSecurityStatusInfo>				*m_spectraSecurityStatus;
	AutoAllocatePointerList<SpectraHeartbeatInfo>				*m_spectraHeartbeat;
	AutoAllocatePointerList<SpectraSequenceResetInfo>				*m_spectraSequenceReset;
	AutoAllocatePointerList<SpectraTradingSessionStatusInfo>				*m_spectraTradingSessionStatus;
	AutoAllocatePointerList<SpectraNewsNewsTextItemInfo>				*m_spectraNewsNewsTextItems;
	AutoAllocatePointerList<SpectraNewsInfo>				*m_spectraNews;
	AutoAllocatePointerList<SpectraOrdersLogMDEntriesItemInfo>				*m_spectraOrdersLogMDEntriesItems;
	AutoAllocatePointerList<SpectraOrdersLogInfo>				*m_spectraOrdersLog;
	AutoAllocatePointerList<SpectraOrdersBookMDEntriesItemInfo>				*m_spectraOrdersBookMDEntriesItems;
	AutoAllocatePointerList<SpectraOrdersBookInfo>				*m_spectraOrdersBook;
	AutoAllocatePointerList<SpectraLogonInfo>				*m_spectraLogon;
	AutoAllocatePointerList<SpectraLogoutInfo>				*m_spectraLogout;
public:
	 static SpectraObjectsAllocationInfo *Default;
	SpectraObjectsAllocationInfo(int count) {
		this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems = new AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>(count, count, "SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo");
		this->m_spectraDefaultIncrementalRefreshMessage = new AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageInfo>(count, count, "SpectraDefaultIncrementalRefreshMessageInfo");
		this->m_spectraDefaultSnapshotMessageMDEntriesItems = new AutoAllocatePointerList<SpectraDefaultSnapshotMessageMDEntriesItemInfo>(count, count, "SpectraDefaultSnapshotMessageMDEntriesItemInfo");
		this->m_spectraDefaultSnapshotMessage = new AutoAllocatePointerList<SpectraDefaultSnapshotMessageInfo>(count, count, "SpectraDefaultSnapshotMessageInfo");
		this->m_spectraSecurityDefinitionMDFeedTypesItems = new AutoAllocatePointerList<SpectraSecurityDefinitionMDFeedTypesItemInfo>(count, count, "SpectraSecurityDefinitionMDFeedTypesItemInfo");
		this->m_spectraSecurityDefinitionUnderlyingsItems = new AutoAllocatePointerList<SpectraSecurityDefinitionUnderlyingsItemInfo>(count, count, "SpectraSecurityDefinitionUnderlyingsItemInfo");
		this->m_spectraSecurityDefinitionInstrumentLegsItems = new AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentLegsItemInfo>(count, count, "SpectraSecurityDefinitionInstrumentLegsItemInfo");
		this->m_spectraSecurityDefinitionInstrumentAttributesItems = new AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentAttributesItemInfo>(count, count, "SpectraSecurityDefinitionInstrumentAttributesItemInfo");
		this->m_spectraSecurityDefinitionEvntGrpItems = new AutoAllocatePointerList<SpectraSecurityDefinitionEvntGrpItemInfo>(count, count, "SpectraSecurityDefinitionEvntGrpItemInfo");
		this->m_spectraSecurityDefinition = new AutoAllocatePointerList<SpectraSecurityDefinitionInfo>(count, count, "SpectraSecurityDefinitionInfo");
		this->m_spectraSecurityDefinitionUpdateReport = new AutoAllocatePointerList<SpectraSecurityDefinitionUpdateReportInfo>(count, count, "SpectraSecurityDefinitionUpdateReportInfo");
		this->m_spectraSecurityStatus = new AutoAllocatePointerList<SpectraSecurityStatusInfo>(count, count, "SpectraSecurityStatusInfo");
		this->m_spectraHeartbeat = new AutoAllocatePointerList<SpectraHeartbeatInfo>(count, count, "SpectraHeartbeatInfo");
		this->m_spectraSequenceReset = new AutoAllocatePointerList<SpectraSequenceResetInfo>(count, count, "SpectraSequenceResetInfo");
		this->m_spectraTradingSessionStatus = new AutoAllocatePointerList<SpectraTradingSessionStatusInfo>(count, count, "SpectraTradingSessionStatusInfo");
		this->m_spectraNewsNewsTextItems = new AutoAllocatePointerList<SpectraNewsNewsTextItemInfo>(count, count, "SpectraNewsNewsTextItemInfo");
		this->m_spectraNews = new AutoAllocatePointerList<SpectraNewsInfo>(count, count, "SpectraNewsInfo");
		this->m_spectraOrdersLogMDEntriesItems = new AutoAllocatePointerList<SpectraOrdersLogMDEntriesItemInfo>(count, count, "SpectraOrdersLogMDEntriesItemInfo");
		this->m_spectraOrdersLog = new AutoAllocatePointerList<SpectraOrdersLogInfo>(count, count, "SpectraOrdersLogInfo");
		this->m_spectraOrdersBookMDEntriesItems = new AutoAllocatePointerList<SpectraOrdersBookMDEntriesItemInfo>(count, count, "SpectraOrdersBookMDEntriesItemInfo");
		this->m_spectraOrdersBook = new AutoAllocatePointerList<SpectraOrdersBookInfo>(count, count, "SpectraOrdersBookInfo");
		this->m_spectraLogon = new AutoAllocatePointerList<SpectraLogonInfo>(count, count, "SpectraLogonInfo");
		this->m_spectraLogout = new AutoAllocatePointerList<SpectraLogoutInfo>(count, count, "SpectraLogoutInfo");
	}
	inline void AllocateDefaultIncrementalRefreshMessageMDEntriesItemInfoPool(int count, int addCount) {
		this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems->Append(count);
		this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateDefaultIncrementalRefreshMessageInfoPool(int count, int addCount) {
		this->m_spectraDefaultIncrementalRefreshMessage->Append(count);
		this->m_spectraDefaultIncrementalRefreshMessage->AddCount(addCount);
	}
	inline void AllocateDefaultSnapshotMessageMDEntriesItemInfoPool(int count, int addCount) {
		this->m_spectraDefaultSnapshotMessageMDEntriesItems->Append(count);
		this->m_spectraDefaultSnapshotMessageMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateDefaultSnapshotMessageInfoPool(int count, int addCount) {
		this->m_spectraDefaultSnapshotMessage->Append(count);
		this->m_spectraDefaultSnapshotMessage->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionMDFeedTypesItemInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinitionMDFeedTypesItems->Append(count);
		this->m_spectraSecurityDefinitionMDFeedTypesItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionUnderlyingsItemInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinitionUnderlyingsItems->Append(count);
		this->m_spectraSecurityDefinitionUnderlyingsItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInstrumentLegsItemInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinitionInstrumentLegsItems->Append(count);
		this->m_spectraSecurityDefinitionInstrumentLegsItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInstrumentAttributesItemInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinitionInstrumentAttributesItems->Append(count);
		this->m_spectraSecurityDefinitionInstrumentAttributesItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionEvntGrpItemInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinitionEvntGrpItems->Append(count);
		this->m_spectraSecurityDefinitionEvntGrpItems->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinition->Append(count);
		this->m_spectraSecurityDefinition->AddCount(addCount);
	}
	inline void AllocateSecurityDefinitionUpdateReportInfoPool(int count, int addCount) {
		this->m_spectraSecurityDefinitionUpdateReport->Append(count);
		this->m_spectraSecurityDefinitionUpdateReport->AddCount(addCount);
	}
	inline void AllocateSecurityStatusInfoPool(int count, int addCount) {
		this->m_spectraSecurityStatus->Append(count);
		this->m_spectraSecurityStatus->AddCount(addCount);
	}
	inline void AllocateHeartbeatInfoPool(int count, int addCount) {
		this->m_spectraHeartbeat->Append(count);
		this->m_spectraHeartbeat->AddCount(addCount);
	}
	inline void AllocateSequenceResetInfoPool(int count, int addCount) {
		this->m_spectraSequenceReset->Append(count);
		this->m_spectraSequenceReset->AddCount(addCount);
	}
	inline void AllocateTradingSessionStatusInfoPool(int count, int addCount) {
		this->m_spectraTradingSessionStatus->Append(count);
		this->m_spectraTradingSessionStatus->AddCount(addCount);
	}
	inline void AllocateNewsNewsTextItemInfoPool(int count, int addCount) {
		this->m_spectraNewsNewsTextItems->Append(count);
		this->m_spectraNewsNewsTextItems->AddCount(addCount);
	}
	inline void AllocateNewsInfoPool(int count, int addCount) {
		this->m_spectraNews->Append(count);
		this->m_spectraNews->AddCount(addCount);
	}
	inline void AllocateOrdersLogMDEntriesItemInfoPool(int count, int addCount) {
		this->m_spectraOrdersLogMDEntriesItems->Append(count);
		this->m_spectraOrdersLogMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateOrdersLogInfoPool(int count, int addCount) {
		this->m_spectraOrdersLog->Append(count);
		this->m_spectraOrdersLog->AddCount(addCount);
	}
	inline void AllocateOrdersBookMDEntriesItemInfoPool(int count, int addCount) {
		this->m_spectraOrdersBookMDEntriesItems->Append(count);
		this->m_spectraOrdersBookMDEntriesItems->AddCount(addCount);
	}
	inline void AllocateOrdersBookInfoPool(int count, int addCount) {
		this->m_spectraOrdersBook->Append(count);
		this->m_spectraOrdersBook->AddCount(addCount);
	}
	inline void AllocateLogonInfoPool(int count, int addCount) {
		this->m_spectraLogon->Append(count);
		this->m_spectraLogon->AddCount(addCount);
	}
	inline void AllocateLogoutInfoPool(int count, int addCount) {
		this->m_spectraLogout->Append(count);
		this->m_spectraLogout->AddCount(addCount);
	}
	inline void AllocateDefaultIncrementalRefreshMessageMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems->Capacity();
		if(count > 0)
			this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems->Append(count);
	}
	inline void AllocateDefaultIncrementalRefreshMessageInfoPoolTo(int count) {
		count -= this->m_spectraDefaultIncrementalRefreshMessage->Capacity();
		if(count > 0)
			this->m_spectraDefaultIncrementalRefreshMessage->Append(count);
	}
	inline void AllocateDefaultSnapshotMessageMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_spectraDefaultSnapshotMessageMDEntriesItems->Capacity();
		if(count > 0)
			this->m_spectraDefaultSnapshotMessageMDEntriesItems->Append(count);
	}
	inline void AllocateDefaultSnapshotMessageInfoPoolTo(int count) {
		count -= this->m_spectraDefaultSnapshotMessage->Capacity();
		if(count > 0)
			this->m_spectraDefaultSnapshotMessage->Append(count);
	}
	inline void AllocateSecurityDefinitionMDFeedTypesItemInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinitionMDFeedTypesItems->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinitionMDFeedTypesItems->Append(count);
	}
	inline void AllocateSecurityDefinitionUnderlyingsItemInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinitionUnderlyingsItems->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinitionUnderlyingsItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInstrumentLegsItemInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinitionInstrumentLegsItems->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinitionInstrumentLegsItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInstrumentAttributesItemInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinitionInstrumentAttributesItems->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinitionInstrumentAttributesItems->Append(count);
	}
	inline void AllocateSecurityDefinitionEvntGrpItemInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinitionEvntGrpItems->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinitionEvntGrpItems->Append(count);
	}
	inline void AllocateSecurityDefinitionInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinition->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinition->Append(count);
	}
	inline void AllocateSecurityDefinitionUpdateReportInfoPoolTo(int count) {
		count -= this->m_spectraSecurityDefinitionUpdateReport->Capacity();
		if(count > 0)
			this->m_spectraSecurityDefinitionUpdateReport->Append(count);
	}
	inline void AllocateSecurityStatusInfoPoolTo(int count) {
		count -= this->m_spectraSecurityStatus->Capacity();
		if(count > 0)
			this->m_spectraSecurityStatus->Append(count);
	}
	inline void AllocateHeartbeatInfoPoolTo(int count) {
		count -= this->m_spectraHeartbeat->Capacity();
		if(count > 0)
			this->m_spectraHeartbeat->Append(count);
	}
	inline void AllocateSequenceResetInfoPoolTo(int count) {
		count -= this->m_spectraSequenceReset->Capacity();
		if(count > 0)
			this->m_spectraSequenceReset->Append(count);
	}
	inline void AllocateTradingSessionStatusInfoPoolTo(int count) {
		count -= this->m_spectraTradingSessionStatus->Capacity();
		if(count > 0)
			this->m_spectraTradingSessionStatus->Append(count);
	}
	inline void AllocateNewsNewsTextItemInfoPoolTo(int count) {
		count -= this->m_spectraNewsNewsTextItems->Capacity();
		if(count > 0)
			this->m_spectraNewsNewsTextItems->Append(count);
	}
	inline void AllocateNewsInfoPoolTo(int count) {
		count -= this->m_spectraNews->Capacity();
		if(count > 0)
			this->m_spectraNews->Append(count);
	}
	inline void AllocateOrdersLogMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_spectraOrdersLogMDEntriesItems->Capacity();
		if(count > 0)
			this->m_spectraOrdersLogMDEntriesItems->Append(count);
	}
	inline void AllocateOrdersLogInfoPoolTo(int count) {
		count -= this->m_spectraOrdersLog->Capacity();
		if(count > 0)
			this->m_spectraOrdersLog->Append(count);
	}
	inline void AllocateOrdersBookMDEntriesItemInfoPoolTo(int count) {
		count -= this->m_spectraOrdersBookMDEntriesItems->Capacity();
		if(count > 0)
			this->m_spectraOrdersBookMDEntriesItems->Append(count);
	}
	inline void AllocateOrdersBookInfoPoolTo(int count) {
		count -= this->m_spectraOrdersBook->Capacity();
		if(count > 0)
			this->m_spectraOrdersBook->Append(count);
	}
	inline void AllocateLogonInfoPoolTo(int count) {
		count -= this->m_spectraLogon->Capacity();
		if(count > 0)
			this->m_spectraLogon->Append(count);
	}
	inline void AllocateLogoutInfoPoolTo(int count) {
		count -= this->m_spectraLogout->Capacity();
		if(count > 0)
			this->m_spectraLogout->Append(count);
	}
	inline AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>* GetSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfoPool() {
		return this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems;
	}
	inline AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageInfo>* GetSpectraDefaultIncrementalRefreshMessageInfoPool() {
		return this->m_spectraDefaultIncrementalRefreshMessage;
	}
	inline AutoAllocatePointerList<SpectraDefaultSnapshotMessageMDEntriesItemInfo>* GetSpectraDefaultSnapshotMessageMDEntriesItemInfoPool() {
		return this->m_spectraDefaultSnapshotMessageMDEntriesItems;
	}
	inline AutoAllocatePointerList<SpectraDefaultSnapshotMessageInfo>* GetSpectraDefaultSnapshotMessageInfoPool() {
		return this->m_spectraDefaultSnapshotMessage;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionMDFeedTypesItemInfo>* GetSpectraSecurityDefinitionMDFeedTypesItemInfoPool() {
		return this->m_spectraSecurityDefinitionMDFeedTypesItems;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionUnderlyingsItemInfo>* GetSpectraSecurityDefinitionUnderlyingsItemInfoPool() {
		return this->m_spectraSecurityDefinitionUnderlyingsItems;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentLegsItemInfo>* GetSpectraSecurityDefinitionInstrumentLegsItemInfoPool() {
		return this->m_spectraSecurityDefinitionInstrumentLegsItems;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentAttributesItemInfo>* GetSpectraSecurityDefinitionInstrumentAttributesItemInfoPool() {
		return this->m_spectraSecurityDefinitionInstrumentAttributesItems;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionEvntGrpItemInfo>* GetSpectraSecurityDefinitionEvntGrpItemInfoPool() {
		return this->m_spectraSecurityDefinitionEvntGrpItems;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionInfo>* GetSpectraSecurityDefinitionInfoPool() {
		return this->m_spectraSecurityDefinition;
	}
	inline AutoAllocatePointerList<SpectraSecurityDefinitionUpdateReportInfo>* GetSpectraSecurityDefinitionUpdateReportInfoPool() {
		return this->m_spectraSecurityDefinitionUpdateReport;
	}
	inline AutoAllocatePointerList<SpectraSecurityStatusInfo>* GetSpectraSecurityStatusInfoPool() {
		return this->m_spectraSecurityStatus;
	}
	inline AutoAllocatePointerList<SpectraHeartbeatInfo>* GetSpectraHeartbeatInfoPool() {
		return this->m_spectraHeartbeat;
	}
	inline AutoAllocatePointerList<SpectraSequenceResetInfo>* GetSpectraSequenceResetInfoPool() {
		return this->m_spectraSequenceReset;
	}
	inline AutoAllocatePointerList<SpectraTradingSessionStatusInfo>* GetSpectraTradingSessionStatusInfoPool() {
		return this->m_spectraTradingSessionStatus;
	}
	inline AutoAllocatePointerList<SpectraNewsNewsTextItemInfo>* GetSpectraNewsNewsTextItemInfoPool() {
		return this->m_spectraNewsNewsTextItems;
	}
	inline AutoAllocatePointerList<SpectraNewsInfo>* GetSpectraNewsInfoPool() {
		return this->m_spectraNews;
	}
	inline AutoAllocatePointerList<SpectraOrdersLogMDEntriesItemInfo>* GetSpectraOrdersLogMDEntriesItemInfoPool() {
		return this->m_spectraOrdersLogMDEntriesItems;
	}
	inline AutoAllocatePointerList<SpectraOrdersLogInfo>* GetSpectraOrdersLogInfoPool() {
		return this->m_spectraOrdersLog;
	}
	inline AutoAllocatePointerList<SpectraOrdersBookMDEntriesItemInfo>* GetSpectraOrdersBookMDEntriesItemInfoPool() {
		return this->m_spectraOrdersBookMDEntriesItems;
	}
	inline AutoAllocatePointerList<SpectraOrdersBookInfo>* GetSpectraOrdersBookInfoPool() {
		return this->m_spectraOrdersBook;
	}
	inline AutoAllocatePointerList<SpectraLogonInfo>* GetSpectraLogonInfoPool() {
		return this->m_spectraLogon;
	}
	inline AutoAllocatePointerList<SpectraLogoutInfo>* GetSpectraLogoutInfoPool() {
		return this->m_spectraLogout;
	}
};
class SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfoNullIndices{
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
class SpectraDefaultIncrementalRefreshMessageInfoNullIndices{
public:
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX0;
};
class SpectraDefaultSnapshotMessageMDEntriesItemInfoNullIndices{
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
class SpectraDefaultSnapshotMessageInfoNullIndices{
public:
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX1;
	static const UINT64 SymbolNullIndex = NULL_MAP_INDEX2;
	static const UINT64 SecurityGroupNullIndex = NULL_MAP_INDEX3;
};
class SpectraSecurityDefinitionMDFeedTypesItemInfoNullIndices{
public:
	static const UINT64 MarketDepthNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDBookTypeNullIndex = NULL_MAP_INDEX1;
};
class SpectraSecurityDefinitionUnderlyingsItemInfoNullIndices{
public:
	static const UINT64 UnderlyingSecurityIDNullIndex = NULL_MAP_INDEX0;
};
class SpectraSecurityDefinitionInfoNullIndices{
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
class SpectraSecurityDefinitionUpdateReportInfoNullIndices{
public:
	static const UINT64 VolatilityNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TheorPriceNullIndex = NULL_MAP_INDEX1;
	static const UINT64 TheorPriceLimitNullIndex = NULL_MAP_INDEX2;
};
class SpectraSecurityStatusInfoNullIndices{
public:
	static const UINT64 SecurityTradingStatusNullIndex = NULL_MAP_INDEX0;
	static const UINT64 HighLimitPxNullIndex = NULL_MAP_INDEX1;
	static const UINT64 LowLimitPxNullIndex = NULL_MAP_INDEX2;
	static const UINT64 InitialMarginOnBuyNullIndex = NULL_MAP_INDEX3;
	static const UINT64 InitialMarginOnSellNullIndex = NULL_MAP_INDEX4;
	static const UINT64 InitialMarginSynteticNullIndex = NULL_MAP_INDEX5;
};
class SpectraTradingSessionStatusInfoNullIndices{
public:
	static const UINT64 TradSesIntermClearingStartTimeNullIndex = NULL_MAP_INDEX0;
	static const UINT64 TradSesIntermClearingEndTimeNullIndex = NULL_MAP_INDEX1;
	static const UINT64 ExchangeTradingSessionIDNullIndex = NULL_MAP_INDEX2;
	static const UINT64 TradSesEventNullIndex = NULL_MAP_INDEX3;
};
class SpectraNewsInfoNullIndices{
public:
	static const UINT64 LastFragmentNullIndex = NULL_MAP_INDEX0;
	static const UINT64 NewsIdNullIndex = NULL_MAP_INDEX1;
	static const UINT64 OrigTimeNullIndex = NULL_MAP_INDEX2;
	static const UINT64 LanguageCodeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 UrgencyNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MarketSegmentIDNullIndex = NULL_MAP_INDEX5;
};
class SpectraOrdersLogMDEntriesItemInfoNullIndices{
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
class SpectraOrdersBookMDEntriesItemInfoNullIndices{
public:
	static const UINT64 MDEntryIDNullIndex = NULL_MAP_INDEX0;
	static const UINT64 MDEntryDateNullIndex = NULL_MAP_INDEX1;
	static const UINT64 MDEntryPxNullIndex = NULL_MAP_INDEX2;
	static const UINT64 MDEntrySizeNullIndex = NULL_MAP_INDEX3;
	static const UINT64 TradeIDNullIndex = NULL_MAP_INDEX4;
	static const UINT64 MDFlagsNullIndex = NULL_MAP_INDEX5;
};
class SpectraOrdersBookInfoNullIndices{
public:
	static const UINT64 RptSeqNullIndex = NULL_MAP_INDEX0;
	static const UINT64 SecurityIDNullIndex = NULL_MAP_INDEX1;
};
class SpectraLogoutInfoNullIndices{
public:
	static const UINT64 TextNullIndex = NULL_MAP_INDEX0;
};
#pragma endregion

#endif //HFT_ROBOT_FASTTYPES_H
