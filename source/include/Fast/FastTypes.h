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

#include "Types.h"
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

#pragma region Message_Info_Structures_Definition_GeneratedCode
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

typedef struct _FastSnapshotInfo {
	UINT64				PresenceMap;
	int				TemplateId;
	INT32				RptSeq;
	bool				IsNullRptSeq;
	UINT32				LastFragment;
	bool				IsNullLastFragment;
	UINT32				RouteFirst;
	bool				IsNullRouteFirst;
	UINT32				LastMsgSeqNumProcessed;
	bool				IsNullLastMsgSeqNumProcessed;
	UINT64				SendingTime;
	bool				IsNullSendingTime;
}FastSnapshotInfo;

class FastLogonInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastLogonInfo>							*Pointer;
	AutoAllocatePointerList<FastLogonInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = A
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	char*							TargetCompID;			// id=56  
	int							TargetCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							HeartBtInt;			// id=108  
	char*							Username;			// id=553  presence=optional  
	int							UsernameLength;
	bool							IsNullUsername;
	char*							Password;			// id=554  presence=optional  
	int							PasswordLength;
	bool							IsNullPassword;
	char*							DefaultApplVerID;			// id=1137  
	int							DefaultApplVerIDLength;

	FastLogonInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->TargetCompID = 0;
		this->TargetCompIDLength = 0;
		this->IsNullUsername = true;
		this->Username = 0;
		this->UsernameLength = 0;
		this->IsNullPassword = true;
		this->Password = 0;
		this->PasswordLength = 0;
		this->DefaultApplVerID = 0;
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
	LinkedPointer<FastLogoutInfo>							*Pointer;
	AutoAllocatePointerList<FastLogoutInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = 5
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	char*							TargetCompID;			// id=56  
	int							TargetCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char*							Text;			// id=58  presence=optional  
	int							TextLength;
	bool							IsNullText;

	FastLogoutInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->TargetCompID = 0;
		this->TargetCompIDLength = 0;
		this->IsNullText = true;
		this->Text = 0;
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
	LinkedPointer<FastGenericItemInfo>							*Pointer;
	AutoAllocatePointerList<FastGenericItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							IsNullMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							IsNullMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							IsNullMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							IsNullMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							IsNullOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							IsNullMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							IsNullMDEntrySize;
	char*							QuoteCondition;			// id=276  presence=optional  
	int							QuoteConditionLength;
	bool							IsNullQuoteCondition;
	char*							TradeCondition;			// id=277  presence=optional  
	int							TradeConditionLength;
	bool							IsNullTradeCondition;
	char*							OpenCloseSettlFlag;			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength;
	bool							IsNullOpenCloseSettlFlag;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							IsNullOrdType;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							IsNullEffectiveTime;
	UINT32							StartTime;			// id=9820  presence=optional  
	bool							IsNullStartTime;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							IsNullAccruedInterestAmt;
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	bool							IsNullChgFromWAPrice;
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	bool							IsNullChgOpenInterest;
	Decimal							BidMarketSize;			// id=5292  presence=optional  
	bool							IsNullBidMarketSize;
	Decimal							AskMarketSize;			// id=5293  presence=optional  
	bool							IsNullAskMarketSize;
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	bool							IsNullTotalNumOfTrades;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							IsNullTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							IsNullYield;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							IsNullTotalVolume;
	INT32							OfferNbOr;			// id=9168  presence=optional  
	bool							IsNullOfferNbOr;
	INT32							BidNbOr;			// id=9169  presence=optional  
	bool							IsNullBidNbOr;
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	bool							IsNullChgFromSettlmnt;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							IsNullSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							IsNullSettleType;
	INT32							SumQtyOfBest;			// id=10503  presence=optional  
	bool							IsNullSumQtyOfBest;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							IsNullOrderSide;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							IsNullOrderStatus;
	Decimal							MinCurrPx;			// id=10509  presence=optional  
	bool							IsNullMinCurrPx;
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional  
	bool							IsNullMinCurrPxChgTime;
	UINT32							VolumeIndicator;			// id=7017  presence=optional  
	bool							IsNullVolumeIndicator;
	Decimal							Price;			// id=44  presence=optional  
	bool							IsNullPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							IsNullPriceType;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							IsNullNominalValue;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							IsNullRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							IsNullBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							IsNullBuyBackDate;
	char*							CXFlag;			// id=5154  presence=optional  
	int							CXFlagLength;
	bool							IsNullCXFlag;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							IsNullMDUpdateAction;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							IsNullRptSeq;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							IsNullSymbol;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							IsNullNetChgPrevDay;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;

	FastGenericItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->IsNullMDEntryType = true;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->IsNullMDEntryID = true;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->IsNullMDEntryDate = true;
		this->IsNullMDEntryTime = true;
		this->IsNullOrigTime = true;
		this->IsNullMDEntryPx = true;
		this->IsNullMDEntrySize = true;
		this->IsNullQuoteCondition = true;
		this->QuoteCondition = 0;
		this->QuoteConditionLength = 0;
		this->IsNullTradeCondition = true;
		this->TradeCondition = 0;
		this->TradeConditionLength = 0;
		this->IsNullOpenCloseSettlFlag = true;
		this->OpenCloseSettlFlag = 0;
		this->OpenCloseSettlFlagLength = 0;
		this->IsNullOrdType = true;
		this->OrdType = 0;
		this->OrdTypeLength = 0;
		this->IsNullEffectiveTime = true;
		this->IsNullStartTime = true;
		this->IsNullAccruedInterestAmt = true;
		this->IsNullChgFromWAPrice = true;
		this->IsNullChgOpenInterest = true;
		this->IsNullBidMarketSize = true;
		this->IsNullAskMarketSize = true;
		this->IsNullTotalNumOfTrades = true;
		this->IsNullTradeValue = true;
		this->IsNullYield = true;
		this->IsNullTotalVolume = true;
		this->IsNullOfferNbOr = true;
		this->IsNullBidNbOr = true;
		this->IsNullChgFromSettlmnt = true;
		this->IsNullSettlDate = true;
		this->IsNullSettleType = true;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->IsNullSumQtyOfBest = true;
		this->IsNullOrderSide = true;
		this->OrderSide = 0;
		this->OrderSideLength = 0;
		this->IsNullOrderStatus = true;
		this->OrderStatus = 0;
		this->OrderStatusLength = 0;
		this->IsNullMinCurrPx = true;
		this->IsNullMinCurrPxChgTime = true;
		this->IsNullVolumeIndicator = true;
		this->IsNullPrice = true;
		this->IsNullPriceType = true;
		this->IsNullNominalValue = true;
		this->IsNullRepoToPx = true;
		this->IsNullBuyBackPx = true;
		this->IsNullBuyBackDate = true;
		this->IsNullCXFlag = true;
		this->CXFlag = 0;
		this->CXFlagLength = 0;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullMDUpdateAction = true;
		this->IsNullRptSeq = true;
		this->IsNullSymbol = true;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullNetChgPrevDay = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
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
	LinkedPointer<FastGenericInfo>							*Pointer;
	AutoAllocatePointerList<FastGenericInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = W
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							IsNullLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							IsNullLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							IsNullRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							IsNullTradSesStatus;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							IsNullMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							IsNullAuctionIndicator;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							IsNullNetChgPrevDay;
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastGenericInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullLastMsgSeqNumProcessed = true;
		this->IsNullLastFragment = true;
		this->IsNullRouteFirst = true;
		this->IsNullTradSesStatus = true;
		this->IsNullMDSecurityTradingStatus = true;
		this->IsNullAuctionIndicator = true;
		this->IsNullNetChgPrevDay = true;
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
	LinkedPointer<FastIncrementalGenericInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalGenericInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastIncrementalGenericInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
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
	LinkedPointer<FastOLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSFONDItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  presence=optional    copy
	int							MDEntryTypeLength;
	bool							IsNullMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							IsNullMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	bool							IsNullMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	bool							IsNullMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	bool							IsNullOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	bool							IsNullMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	bool							IsNullMDEntrySize;
	Decimal							Yield;			// id=236  presence=optional    copy
	bool							IsNullYield;
	char*							OrderStatus;			// id=10505  presence=optional    copy
	int							OrderStatusLength;
	bool							IsNullOrderStatus;
	char*							OrdType;			// id=40  presence=optional    copy
	int							OrdTypeLength;
	bool							IsNullOrdType;
	Decimal							TotalVolume;			// id=5791  presence=optional    copy
	bool							IsNullTotalVolume;
	char*							TradingSessionSubID;			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							IsNullMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional    copy
	int							SymbolLength;
	bool							IsNullSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							IsNullRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional    copy
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;

	FastOLSFONDItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->IsNullMDEntryType = true;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->IsNullMDEntryID = true;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->IsNullMDEntryDate = true;
		this->IsNullMDEntryTime = true;
		this->IsNullOrigTime = true;
		this->IsNullMDEntryPx = true;
		this->IsNullMDEntrySize = true;
		this->IsNullYield = true;
		this->IsNullOrderStatus = true;
		this->OrderStatus = 0;
		this->OrderStatusLength = 0;
		this->IsNullOrdType = true;
		this->OrdType = 0;
		this->OrdTypeLength = 0;
		this->IsNullTotalVolume = true;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullMDUpdateAction = true;
		this->IsNullSymbol = true;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullRptSeq = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
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
	LinkedPointer<FastOLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSFONDInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = W
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							IsNullLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							IsNullLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							IsNullRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							IsNullTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							IsNullMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							IsNullAuctionIndicator;
	int							GroupMDEntriesCount;
	FastOLSFONDItemInfo* GroupMDEntries[256];

	FastOLSFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullLastMsgSeqNumProcessed = true;
		this->IsNullLastFragment = true;
		this->IsNullRouteFirst = true;
		this->IsNullTradSesStatus = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullMDSecurityTradingStatus = true;
		this->IsNullAuctionIndicator = true;
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
	LinkedPointer<FastOLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSCURRItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  presence=optional    copy
	int							MDEntryTypeLength;
	bool							IsNullMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							IsNullMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	bool							IsNullMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	bool							IsNullMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	bool							IsNullOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	bool							IsNullMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	bool							IsNullMDEntrySize;
	char*							OrderStatus;			// id=10505  presence=optional    copy
	int							OrderStatusLength;
	bool							IsNullOrderStatus;
	char*							TradingSessionSubID;			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional    copy
	bool							IsNullMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional    copy
	int							SymbolLength;
	bool							IsNullSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							IsNullRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional    copy
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;

	FastOLSCURRItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->IsNullMDEntryType = true;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->IsNullMDEntryID = true;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->IsNullMDEntryDate = true;
		this->IsNullMDEntryTime = true;
		this->IsNullOrigTime = true;
		this->IsNullMDEntryPx = true;
		this->IsNullMDEntrySize = true;
		this->IsNullOrderStatus = true;
		this->OrderStatus = 0;
		this->OrderStatusLength = 0;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullMDUpdateAction = true;
		this->IsNullSymbol = true;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullRptSeq = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
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
	LinkedPointer<FastOLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastOLSCURRInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = W
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							IsNullLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							IsNullLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							IsNullRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							IsNullTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							IsNullMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastOLSCURRItemInfo* GroupMDEntries[256];

	FastOLSCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullLastMsgSeqNumProcessed = true;
		this->IsNullLastFragment = true;
		this->IsNullRouteFirst = true;
		this->IsNullTradSesStatus = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullMDSecurityTradingStatus = true;
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
	LinkedPointer<FastTLSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSFONDItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  
	int							MDEntryTypeLength;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							IsNullMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	bool							IsNullMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	bool							IsNullMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	bool							IsNullOrigTime;
	char*							OrderSide;			// id=10504  presence=optional    copy
	int							OrderSideLength;
	bool							IsNullOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	bool							IsNullMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	bool							IsNullMDEntrySize;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional    copy
	bool							IsNullAccruedInterestAmt;
	Decimal							TradeValue;			// id=6143  presence=optional    copy
	bool							IsNullTradeValue;
	Decimal							Yield;			// id=236  presence=optional    copy
	bool							IsNullYield;
	UINT32							SettlDate;			// id=64  presence=optional    copy
	bool							IsNullSettlDate;
	char*							SettleType;			// id=5459  presence=optional    copy
	int							SettleTypeLength;
	bool							IsNullSettleType;
	Decimal							Price;			// id=44  presence=optional    copy
	bool							IsNullPrice;
	INT32							PriceType;			// id=423  presence=optional    copy
	bool							IsNullPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional    copy
	bool							IsNullRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy
	bool							IsNullBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy
	bool							IsNullBuyBackDate;
	char*							TradingSessionSubID;			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	char*							RefOrderID;			// id=1080  presence=optional    copy
	int							RefOrderIDLength;
	bool							IsNullRefOrderID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							IsNullMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							IsNullSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							IsNullRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;

	FastTLSFONDItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->IsNullMDEntryID = true;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->IsNullMDEntryDate = true;
		this->IsNullMDEntryTime = true;
		this->IsNullOrigTime = true;
		this->IsNullOrderSide = true;
		this->OrderSide = 0;
		this->OrderSideLength = 0;
		this->IsNullMDEntryPx = true;
		this->IsNullMDEntrySize = true;
		this->IsNullAccruedInterestAmt = true;
		this->IsNullTradeValue = true;
		this->IsNullYield = true;
		this->IsNullSettlDate = true;
		this->IsNullSettleType = true;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->IsNullPrice = true;
		this->IsNullPriceType = true;
		this->IsNullRepoToPx = true;
		this->IsNullBuyBackPx = true;
		this->IsNullBuyBackDate = true;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullRefOrderID = true;
		this->RefOrderID = 0;
		this->RefOrderIDLength = 0;
		this->IsNullMDUpdateAction = true;
		this->IsNullSymbol = true;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullRptSeq = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
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
	LinkedPointer<FastTLSFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSFONDInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = W
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							IsNullLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							IsNullLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							IsNullRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							IsNullTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							IsNullMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							IsNullAuctionIndicator;
	int							GroupMDEntriesCount;
	FastTLSFONDItemInfo* GroupMDEntries[256];

	FastTLSFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullLastMsgSeqNumProcessed = true;
		this->IsNullLastFragment = true;
		this->IsNullRouteFirst = true;
		this->IsNullTradSesStatus = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullMDSecurityTradingStatus = true;
		this->IsNullAuctionIndicator = true;
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
	LinkedPointer<FastTLSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSCURRItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  
	int							MDEntryTypeLength;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							IsNullMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional    copy
	bool							IsNullMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional    copy
	bool							IsNullMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional    copy
	bool							IsNullOrigTime;
	char*							OrderSide;			// id=10504  presence=optional    copy
	int							OrderSideLength;
	bool							IsNullOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional    copy
	bool							IsNullMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional    copy
	bool							IsNullMDEntrySize;
	Decimal							TradeValue;			// id=6143  presence=optional    copy
	bool							IsNullTradeValue;
	UINT32							SettlDate;			// id=64  presence=optional    copy
	bool							IsNullSettlDate;
	char*							SettleType;			// id=5459  presence=optional    copy
	int							SettleTypeLength;
	bool							IsNullSettleType;
	Decimal							Price;			// id=44  presence=optional    copy
	bool							IsNullPrice;
	INT32							PriceType;			// id=423  presence=optional    copy
	bool							IsNullPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional    copy
	bool							IsNullRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional    copy
	bool							IsNullBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional    copy
	bool							IsNullBuyBackDate;
	char*							TradingSessionSubID;			// id=625  presence=optional    copy
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	char*							RefOrderID;			// id=1080  presence=optional    copy
	int							RefOrderIDLength;
	bool							IsNullRefOrderID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							IsNullMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							IsNullSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							IsNullRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;

	FastTLSCURRItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->IsNullMDEntryID = true;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->IsNullMDEntryDate = true;
		this->IsNullMDEntryTime = true;
		this->IsNullOrigTime = true;
		this->IsNullOrderSide = true;
		this->OrderSide = 0;
		this->OrderSideLength = 0;
		this->IsNullMDEntryPx = true;
		this->IsNullMDEntrySize = true;
		this->IsNullTradeValue = true;
		this->IsNullSettlDate = true;
		this->IsNullSettleType = true;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->IsNullPrice = true;
		this->IsNullPriceType = true;
		this->IsNullRepoToPx = true;
		this->IsNullBuyBackPx = true;
		this->IsNullBuyBackDate = true;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullRefOrderID = true;
		this->RefOrderID = 0;
		this->RefOrderIDLength = 0;
		this->IsNullMDUpdateAction = true;
		this->IsNullSymbol = true;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullRptSeq = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
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
	LinkedPointer<FastTLSCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastTLSCURRInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = W
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							IsNullLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							IsNullLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							IsNullRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							IsNullTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							IsNullMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastTLSCURRItemInfo* GroupMDEntries[256];

	FastTLSCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullLastMsgSeqNumProcessed = true;
		this->IsNullLastFragment = true;
		this->IsNullRouteFirst = true;
		this->IsNullTradSesStatus = true;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullMDSecurityTradingStatus = true;
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
	LinkedPointer<FastIncrementalMSRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalMSRFONDInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							LastUpdateTime;			// id=779  presence=optional  
	bool							IsNullLastUpdateTime;
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastIncrementalMSRFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullLastUpdateTime = true;
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
	LinkedPointer<FastIncrementalMSRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalMSRCURRInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT64							LastUpdateTime;			// id=779  presence=optional  
	bool							IsNullLastUpdateTime;
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[256];

	FastIncrementalMSRCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullLastUpdateTime = true;
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
	LinkedPointer<FastIncrementalOLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalOLRFONDInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastOLSFONDItemInfo* GroupMDEntries[256];

	FastIncrementalOLRFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
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
	LinkedPointer<FastIncrementalOLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalOLRCURRInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastOLSCURRItemInfo* GroupMDEntries[256];

	FastIncrementalOLRCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
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
	LinkedPointer<FastIncrementalTLRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalTLRFONDInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastTLSFONDItemInfo* GroupMDEntries[256];

	FastIncrementalTLRFONDInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
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
	LinkedPointer<FastIncrementalTLRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalTLRCURRInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = X
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastTLSCURRItemInfo* GroupMDEntries[256];

	FastIncrementalTLRCURRInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
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
	LinkedPointer<FastSecurityDefinitionGroupInstrAttribItemInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>							*Allocator;
	bool							Used;
	INT32							InstrAttribType;			// id=871  
	BYTE*							InstrAttribValue;			// id=872  presence=optional  
	int							InstrAttribValueLength;
	bool							IsNullInstrAttribValue;

	FastSecurityDefinitionGroupInstrAttribItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->IsNullInstrAttribValue = true;
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
	LinkedPointer<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>							*Allocator;
	bool							Used;
	char*							TradingSessionID;			// id=336  
	int							TradingSessionIDLength;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	bool							IsNullSecurityTradingStatus;
	INT32							OrderNote;			// id=9680  presence=optional  
	bool							IsNullOrderNote;

	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullSecurityTradingStatus = true;
		this->IsNullOrderNote = true;
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
	LinkedPointer<FastSecurityDefinitionMarketSegmentGrpItemInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>							*Allocator;
	bool							Used;
	Decimal							RoundLot;			// id=561  presence=optional  
	bool							IsNullRoundLot;
	int							TradingSessionRulesGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* TradingSessionRulesGrp[256];			// presence=optional  
	bool							IsNullTradingSessionRulesGrp;

	FastSecurityDefinitionMarketSegmentGrpItemInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->IsNullRoundLot = true;
		this->IsNullTradingSessionRulesGrp = true;
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
	LinkedPointer<FastSecurityDefinitionInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityDefinitionInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = d
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34    increment
	UINT64							SendingTime;			// id=52  
	char*							MessageEncoding;			// id=347    default
	int							MessageEncodingLength;
	INT32							TotNumReports;			// id=911  presence=optional  
	bool							IsNullTotNumReports;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							IsNullSymbol;
	BYTE*							SecurityID;			// id=48  presence=optional  
	int							SecurityIDLength;
	bool							IsNullSecurityID;
	BYTE*							SecurityIDSource;			// id=22  presence=optional  
	int							SecurityIDSourceLength;
	bool							IsNullSecurityIDSource;
	INT32							Product;			// id=460  presence=optional  
	bool							IsNullProduct;
	BYTE*							CFICode;			// id=461  presence=optional  
	int							CFICodeLength;
	bool							IsNullCFICode;
	BYTE*							SecurityType;			// id=167  presence=optional  
	int							SecurityTypeLength;
	bool							IsNullSecurityType;
	UINT32							MaturityDate;			// id=541  presence=optional  
	bool							IsNullMaturityDate;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							IsNullSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							IsNullSettleType;
	Decimal							OrigIssueAmt;			// id=5850  presence=optional  
	bool							IsNullOrigIssueAmt;
	UINT32							CouponPaymentDate;			// id=224  presence=optional  
	bool							IsNullCouponPaymentDate;
	Decimal							CouponRate;			// id=223  presence=optional  
	bool							IsNullCouponRate;
	UINT32							SettlFixingDate;			// id=9119  presence=optional  
	bool							IsNullSettlFixingDate;
	Decimal							DividendNetPx;			// id=9982  presence=optional  
	bool							IsNullDividendNetPx;
	BYTE*							SecurityDesc;			// id=107  presence=optional  
	int							SecurityDescLength;
	bool							IsNullSecurityDesc;
	BYTE*							EncodedSecurityDesc;			// id=351  presence=optional  
	int							EncodedSecurityDescLength;
	bool							IsNullEncodedSecurityDesc;
	BYTE*							QuoteText;			// id=9696  presence=optional  
	int							QuoteTextLength;
	bool							IsNullQuoteText;
	int							GroupInstrAttribCount;			// presence=optional  
	FastSecurityDefinitionGroupInstrAttribItemInfo* GroupInstrAttrib[256];			// presence=optional  
	bool							IsNullGroupInstrAttrib;
	char*							Currency;			// id=15  presence=optional  
	int							CurrencyLength;
	bool							IsNullCurrency;
	int							MarketSegmentGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpItemInfo* MarketSegmentGrp[256];			// presence=optional  
	bool							IsNullMarketSegmentGrp;
	char*							SettlCurrency;			// id=120  presence=optional  
	int							SettlCurrencyLength;
	bool							IsNullSettlCurrency;
	INT32							PriceType;			// id=423  presence=optional  
	bool							IsNullPriceType;
	char*							StateSecurityID;			// id=5217  presence=optional  
	int							StateSecurityIDLength;
	bool							IsNullStateSecurityID;
	BYTE*							EncodedShortSecurityDesc;			// id=5383  presence=optional  
	int							EncodedShortSecurityDescLength;
	bool							IsNullEncodedShortSecurityDesc;
	BYTE*							MarketCode;			// id=5385  presence=optional  
	int							MarketCodeLength;
	bool							IsNullMarketCode;
	Decimal							MinPriceIncrement;			// id=969  presence=optional  
	bool							IsNullMinPriceIncrement;
	Decimal							MktShareLimit;			// id=5387  presence=optional  
	bool							IsNullMktShareLimit;
	Decimal							MktShareThreshold;			// id=5388  presence=optional  
	bool							IsNullMktShareThreshold;
	Decimal							MaxOrdersVolume;			// id=5389  presence=optional  
	bool							IsNullMaxOrdersVolume;
	Decimal							PriceMvmLimit;			// id=5470  presence=optional  
	bool							IsNullPriceMvmLimit;
	Decimal							FaceValue;			// id=5508  presence=optional  
	bool							IsNullFaceValue;
	Decimal							BaseSwapPx;			// id=5556  presence=optional  
	bool							IsNullBaseSwapPx;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							IsNullRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							IsNullBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							IsNullBuyBackDate;
	Decimal							NoSharesIssued;			// id=7595  presence=optional  
	bool							IsNullNoSharesIssued;
	Decimal							HighLimit;			// id=9199  presence=optional  
	bool							IsNullHighLimit;
	Decimal							LowLimit;			// id=9200  presence=optional  
	bool							IsNullLowLimit;
	INT32							NumOfDaysToMaturity;			// id=10508  presence=optional  
	bool							IsNullNumOfDaysToMaturity;

	FastSecurityDefinitionInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->MessageEncoding = 0;
		this->MessageEncodingLength = 0;
		this->IsNullTotNumReports = true;
		this->IsNullSymbol = true;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullSecurityID = true;
		this->IsNullSecurityIDSource = true;
		this->IsNullProduct = true;
		this->IsNullCFICode = true;
		this->IsNullSecurityType = true;
		this->IsNullMaturityDate = true;
		this->IsNullSettlDate = true;
		this->IsNullSettleType = true;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->IsNullOrigIssueAmt = true;
		this->IsNullCouponPaymentDate = true;
		this->IsNullCouponRate = true;
		this->IsNullSettlFixingDate = true;
		this->IsNullDividendNetPx = true;
		this->IsNullSecurityDesc = true;
		this->IsNullEncodedSecurityDesc = true;
		this->IsNullQuoteText = true;
		this->IsNullGroupInstrAttrib = true;
		this->GroupInstrAttribCount = 0;
		this->IsNullCurrency = true;
		this->Currency = 0;
		this->CurrencyLength = 0;
		this->IsNullMarketSegmentGrp = true;
		this->MarketSegmentGrpCount = 0;
		this->IsNullSettlCurrency = true;
		this->SettlCurrency = 0;
		this->SettlCurrencyLength = 0;
		this->IsNullPriceType = true;
		this->IsNullStateSecurityID = true;
		this->StateSecurityID = 0;
		this->StateSecurityIDLength = 0;
		this->IsNullEncodedShortSecurityDesc = true;
		this->IsNullMarketCode = true;
		this->IsNullMinPriceIncrement = true;
		this->IsNullMktShareLimit = true;
		this->IsNullMktShareThreshold = true;
		this->IsNullMaxOrdersVolume = true;
		this->IsNullPriceMvmLimit = true;
		this->IsNullFaceValue = true;
		this->IsNullBaseSwapPx = true;
		this->IsNullRepoToPx = true;
		this->IsNullBuyBackPx = true;
		this->IsNullBuyBackDate = true;
		this->IsNullNoSharesIssued = true;
		this->IsNullHighLimit = true;
		this->IsNullLowLimit = true;
		this->IsNullNumOfDaysToMaturity = true;
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
	LinkedPointer<FastSecurityStatusInfo>							*Pointer;
	AutoAllocatePointerList<FastSecurityStatusInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = f
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char*							Symbol;			// id=55  
	int							SymbolLength;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							IsNullTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							IsNullTradingSessionSubID;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	bool							IsNullSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							IsNullAuctionIndicator;

	FastSecurityStatusInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->IsNullTradingSessionID = true;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->IsNullTradingSessionSubID = true;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->IsNullSecurityTradingStatus = true;
		this->IsNullAuctionIndicator = true;
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
	LinkedPointer<FastTradingSessionStatusInfo>							*Pointer;
	AutoAllocatePointerList<FastTradingSessionStatusInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = h
	int							MessageTypeLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							TradSesStatus;			// id=340  
	char*							Text;			// id=58  presence=optional  
	int							TextLength;
	bool							IsNullText;
	char*							TradingSessionID;			// id=336  
	int							TradingSessionIDLength;

	FastTradingSessionStatusInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->IsNullText = true;
		this->Text = 0;
		this->TextLength = 0;
		this->TradingSessionID = 0;
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
	LinkedPointer<FastHeartbeatInfo>							*Pointer;
	AutoAllocatePointerList<FastHeartbeatInfo>							*Allocator;
	bool							Used;
	char*							MessageType;			// id=35    constant has constant value = 0
	int							MessageTypeLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  

	FastHeartbeatInfo(){
		this->Used = false;
		this->Pointer = 0;
		this->Allocator = 0;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
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
public:
	int				m_logonCount;
	int				m_logonAddCount;
	int				m_logoutCount;
	int				m_logoutAddCount;
	int				m_genericItemsCount;
	int				m_genericItemsAddCount;
	int				m_genericCount;
	int				m_genericAddCount;
	int				m_incrementalGenericCount;
	int				m_incrementalGenericAddCount;
	int				m_oLSFONDItemsCount;
	int				m_oLSFONDItemsAddCount;
	int				m_oLSFONDCount;
	int				m_oLSFONDAddCount;
	int				m_oLSCURRItemsCount;
	int				m_oLSCURRItemsAddCount;
	int				m_oLSCURRCount;
	int				m_oLSCURRAddCount;
	int				m_tLSFONDItemsCount;
	int				m_tLSFONDItemsAddCount;
	int				m_tLSFONDCount;
	int				m_tLSFONDAddCount;
	int				m_tLSCURRItemsCount;
	int				m_tLSCURRItemsAddCount;
	int				m_tLSCURRCount;
	int				m_tLSCURRAddCount;
	int				m_incrementalMSRFONDCount;
	int				m_incrementalMSRFONDAddCount;
	int				m_incrementalMSRCURRCount;
	int				m_incrementalMSRCURRAddCount;
	int				m_incrementalOLRFONDCount;
	int				m_incrementalOLRFONDAddCount;
	int				m_incrementalOLRCURRCount;
	int				m_incrementalOLRCURRAddCount;
	int				m_incrementalTLRFONDCount;
	int				m_incrementalTLRFONDAddCount;
	int				m_incrementalTLRCURRCount;
	int				m_incrementalTLRCURRAddCount;
	int				m_securityDefinitionGroupInstrAttribItemsCount;
	int				m_securityDefinitionGroupInstrAttribItemsAddCount;
	int				m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount;
	int				m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount;
	int				m_securityDefinitionMarketSegmentGrpItemsCount;
	int				m_securityDefinitionMarketSegmentGrpItemsAddCount;
	int				m_securityDefinitionCount;
	int				m_securityDefinitionAddCount;
	int				m_securityStatusCount;
	int				m_securityStatusAddCount;
	int				m_tradingSessionStatusCount;
	int				m_tradingSessionStatusAddCount;
	int				m_heartbeatCount;
	int				m_heartbeatAddCount;
	FastObjectsAllocationInfo() {

	this->m_logonCount = 3;
	this->m_logonAddCount = 3;
	this->m_logoutCount = 3;
	this->m_logoutAddCount = 3;
	this->m_genericItemsCount = 3;
	this->m_genericItemsAddCount = 3;
	this->m_genericCount = 3;
	this->m_genericAddCount = 3;
	this->m_incrementalGenericCount = 3;
	this->m_incrementalGenericAddCount = 3;
	this->m_oLSFONDItemsCount = 3;
	this->m_oLSFONDItemsAddCount = 3;
	this->m_oLSFONDCount = 3;
	this->m_oLSFONDAddCount = 3;
	this->m_oLSCURRItemsCount = 3;
	this->m_oLSCURRItemsAddCount = 3;
	this->m_oLSCURRCount = 3;
	this->m_oLSCURRAddCount = 3;
	this->m_tLSFONDItemsCount = 3;
	this->m_tLSFONDItemsAddCount = 3;
	this->m_tLSFONDCount = 3;
	this->m_tLSFONDAddCount = 3;
	this->m_tLSCURRItemsCount = 3;
	this->m_tLSCURRItemsAddCount = 3;
	this->m_tLSCURRCount = 3;
	this->m_tLSCURRAddCount = 3;
	this->m_incrementalMSRFONDCount = 3;
	this->m_incrementalMSRFONDAddCount = 3;
	this->m_incrementalMSRCURRCount = 3;
	this->m_incrementalMSRCURRAddCount = 3;
	this->m_incrementalOLRFONDCount = 3;
	this->m_incrementalOLRFONDAddCount = 3;
	this->m_incrementalOLRCURRCount = 3;
	this->m_incrementalOLRCURRAddCount = 3;
	this->m_incrementalTLRFONDCount = 3;
	this->m_incrementalTLRFONDAddCount = 3;
	this->m_incrementalTLRCURRCount = 3;
	this->m_incrementalTLRCURRAddCount = 3;
	this->m_securityDefinitionGroupInstrAttribItemsCount = 3;
	this->m_securityDefinitionGroupInstrAttribItemsAddCount = 3;
	this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = 3;
	this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = 3;
	this->m_securityDefinitionMarketSegmentGrpItemsCount = 3;
	this->m_securityDefinitionMarketSegmentGrpItemsAddCount = 3;
	this->m_securityDefinitionCount = 3;
	this->m_securityDefinitionAddCount = 3;
	this->m_securityStatusCount = 3;
	this->m_securityStatusAddCount = 3;
	this->m_tradingSessionStatusCount = 3;
	this->m_tradingSessionStatusAddCount = 3;
	this->m_heartbeatCount = 3;
	this->m_heartbeatAddCount = 3;
	}
	FastObjectsAllocationInfo(int count, int addCount) {

	this->m_logonCount = count;
	this->m_logonAddCount = addCount;
	this->m_logoutCount = count;
	this->m_logoutAddCount = addCount;
	this->m_genericItemsCount = count;
	this->m_genericItemsAddCount = addCount;
	this->m_genericCount = count;
	this->m_genericAddCount = addCount;
	this->m_incrementalGenericCount = count;
	this->m_incrementalGenericAddCount = addCount;
	this->m_oLSFONDItemsCount = count;
	this->m_oLSFONDItemsAddCount = addCount;
	this->m_oLSFONDCount = count;
	this->m_oLSFONDAddCount = addCount;
	this->m_oLSCURRItemsCount = count;
	this->m_oLSCURRItemsAddCount = addCount;
	this->m_oLSCURRCount = count;
	this->m_oLSCURRAddCount = addCount;
	this->m_tLSFONDItemsCount = count;
	this->m_tLSFONDItemsAddCount = addCount;
	this->m_tLSFONDCount = count;
	this->m_tLSFONDAddCount = addCount;
	this->m_tLSCURRItemsCount = count;
	this->m_tLSCURRItemsAddCount = addCount;
	this->m_tLSCURRCount = count;
	this->m_tLSCURRAddCount = addCount;
	this->m_incrementalMSRFONDCount = count;
	this->m_incrementalMSRFONDAddCount = addCount;
	this->m_incrementalMSRCURRCount = count;
	this->m_incrementalMSRCURRAddCount = addCount;
	this->m_incrementalOLRFONDCount = count;
	this->m_incrementalOLRFONDAddCount = addCount;
	this->m_incrementalOLRCURRCount = count;
	this->m_incrementalOLRCURRAddCount = addCount;
	this->m_incrementalTLRFONDCount = count;
	this->m_incrementalTLRFONDAddCount = addCount;
	this->m_incrementalTLRCURRCount = count;
	this->m_incrementalTLRCURRAddCount = addCount;
	this->m_securityDefinitionGroupInstrAttribItemsCount = count;
	this->m_securityDefinitionGroupInstrAttribItemsAddCount = addCount;
	this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount = count;
	this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount = addCount;
	this->m_securityDefinitionMarketSegmentGrpItemsCount = count;
	this->m_securityDefinitionMarketSegmentGrpItemsAddCount = addCount;
	this->m_securityDefinitionCount = count;
	this->m_securityDefinitionAddCount = addCount;
	this->m_securityStatusCount = count;
	this->m_securityStatusAddCount = addCount;
	this->m_tradingSessionStatusCount = count;
	this->m_tradingSessionStatusAddCount = addCount;
	this->m_heartbeatCount = count;
	this->m_heartbeatAddCount = addCount;
	}
};
class FastOLSFONDItemInfoPresenceIndices{
public:
	static const int MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX0;
	static const int MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX1;
	static const int MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const int OrigTimePresenceIndex = PRESENCE_MAP_INDEX3;
	static const int MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const int MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const int YieldPresenceIndex = PRESENCE_MAP_INDEX6;
	static const int OrderStatusPresenceIndex = PRESENCE_MAP_INDEX7;
	static const int OrdTypePresenceIndex = PRESENCE_MAP_INDEX8;
	static const int TotalVolumePresenceIndex = PRESENCE_MAP_INDEX9;
	static const int TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX10;
};
class FastOLSCURRItemInfoPresenceIndices{
public:
	static const int MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX0;
	static const int MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX1;
	static const int MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const int OrigTimePresenceIndex = PRESENCE_MAP_INDEX3;
	static const int MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const int MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const int OrderStatusPresenceIndex = PRESENCE_MAP_INDEX6;
	static const int TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX7;
};
class FastTLSFONDItemInfoPresenceIndices{
public:
	static const int MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX0;
	static const int MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX1;
	static const int OrigTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const int OrderSidePresenceIndex = PRESENCE_MAP_INDEX3;
	static const int MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const int MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const int AccruedInterestAmtPresenceIndex = PRESENCE_MAP_INDEX6;
	static const int TradeValuePresenceIndex = PRESENCE_MAP_INDEX7;
	static const int YieldPresenceIndex = PRESENCE_MAP_INDEX8;
	static const int SettlDatePresenceIndex = PRESENCE_MAP_INDEX9;
	static const int SettleTypePresenceIndex = PRESENCE_MAP_INDEX10;
	static const int PricePresenceIndex = PRESENCE_MAP_INDEX11;
	static const int PriceTypePresenceIndex = PRESENCE_MAP_INDEX12;
	static const int RepoToPxPresenceIndex = PRESENCE_MAP_INDEX13;
	static const int BuyBackPxPresenceIndex = PRESENCE_MAP_INDEX14;
	static const int BuyBackDatePresenceIndex = PRESENCE_MAP_INDEX15;
	static const int TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX16;
	static const int RefOrderIDPresenceIndex = PRESENCE_MAP_INDEX17;
};
class FastTLSCURRItemInfoPresenceIndices{
public:
	static const int MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX0;
	static const int MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX1;
	static const int OrigTimePresenceIndex = PRESENCE_MAP_INDEX2;
	static const int OrderSidePresenceIndex = PRESENCE_MAP_INDEX3;
	static const int MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX4;
	static const int MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX5;
	static const int TradeValuePresenceIndex = PRESENCE_MAP_INDEX6;
	static const int SettlDatePresenceIndex = PRESENCE_MAP_INDEX7;
	static const int SettleTypePresenceIndex = PRESENCE_MAP_INDEX8;
	static const int PricePresenceIndex = PRESENCE_MAP_INDEX9;
	static const int PriceTypePresenceIndex = PRESENCE_MAP_INDEX10;
	static const int RepoToPxPresenceIndex = PRESENCE_MAP_INDEX11;
	static const int BuyBackPxPresenceIndex = PRESENCE_MAP_INDEX12;
	static const int BuyBackDatePresenceIndex = PRESENCE_MAP_INDEX13;
	static const int TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX14;
	static const int RefOrderIDPresenceIndex = PRESENCE_MAP_INDEX15;
};
class FastIncrementalOLRFONDItemInfoPresenceIndices{
public:
	static const int MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX0;
	static const int SymbolPresenceIndex = PRESENCE_MAP_INDEX1;
	static const int MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX2;
	static const int MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX3;
	static const int OrigTimePresenceIndex = PRESENCE_MAP_INDEX4;
	static const int MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX5;
	static const int MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX6;
	static const int YieldPresenceIndex = PRESENCE_MAP_INDEX7;
	static const int OrderStatusPresenceIndex = PRESENCE_MAP_INDEX8;
	static const int OrdTypePresenceIndex = PRESENCE_MAP_INDEX9;
	static const int TotalVolumePresenceIndex = PRESENCE_MAP_INDEX10;
	static const int TradingSessionIDPresenceIndex = PRESENCE_MAP_INDEX11;
	static const int TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX12;
};
class FastIncrementalOLRCURRItemInfoPresenceIndices{
public:
	static const int MDUpdateActionPresenceIndex = PRESENCE_MAP_INDEX0;
	static const int MDEntryTypePresenceIndex = PRESENCE_MAP_INDEX1;
	static const int SymbolPresenceIndex = PRESENCE_MAP_INDEX2;
	static const int MDEntryDatePresenceIndex = PRESENCE_MAP_INDEX3;
	static const int MDEntryTimePresenceIndex = PRESENCE_MAP_INDEX4;
	static const int OrigTimePresenceIndex = PRESENCE_MAP_INDEX5;
	static const int MDEntryPxPresenceIndex = PRESENCE_MAP_INDEX6;
	static const int MDEntrySizePresenceIndex = PRESENCE_MAP_INDEX7;
	static const int OrderStatusPresenceIndex = PRESENCE_MAP_INDEX8;
	static const int TradingSessionIDPresenceIndex = PRESENCE_MAP_INDEX9;
	static const int TradingSessionSubIDPresenceIndex = PRESENCE_MAP_INDEX10;
};
#pragma endregion

#endif //HFT_ROBOT_FASTTYPES_H
