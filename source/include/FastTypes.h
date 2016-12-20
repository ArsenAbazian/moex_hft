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
#include "FixTypes.h"

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
    mdetAskPriceMax = 'N',
    mdetBidPriceMin = 'O',
    mdetAuctionPriceCalculated = 'Q',
    mdetAuctionPriceClose = 'W',
    mdetAuctionMagnitudeClose = 'c',
    mdetMSSTradingDenyNotEnoughMoney = 'e',
    mdetMSSTradeAskAuctionMagnitudeOpenClose = 'f',
    mdetOLSTradeAskAuctionOpenClose = 'f',
    mdetMSSTradeBidAuctionMagnitudeOpenClose = 'g',
    mdetOLSTradeBidAuctionOpenClose = 'g',
    mdetSessionAsk = 'i',
    mdetSessionBid = 'j',
    mdetPreTradePeriodPrice = 'h',
    mdetPostTradePeriodPrice = 'k',
    mdetTradePrice2 = 'l',
    mdetTradePrice = 'm',
    mdetPriceOpenOfficial = 'o',
    mdetPriceCurrentOfficial = 'p',
    mdetLegitimQuote = 'q',
    mdetPriceCloseOfficial = 'r',
    mdetAskTotal = 'v',
    mdetBidTotal = 'w',
    mdetAuctionPriceBigPackets = 's',
    mdetAuctionMagnitudeBigPackets = 'x',
    mdetCumulativeCouponDebit = 'y',
    mdetDuration = 'u',
    mdetAllDeals = 'z'
}MDEntryType;

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
	bool				AllowRptSeq;
	UINT32				LastFragment;
	bool				AllowLastFragment;
	UINT32				RouteFirst;
	bool				AllowRouteFirst;
	UINT32				LastMsgSeqNumProcessed;
	bool				AllowLastMsgSeqNumProcessed;
	UINT64				SendingTime;
	bool				AllowSendingTime;
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
	bool							AllowUsername;
	char*							Password;			// id=554  presence=optional  
	int							PasswordLength;
	bool							AllowPassword;
	char*							DefaultApplVerID;			// id=1137  
	int							DefaultApplVerIDLength;

	FastLogonInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->TargetCompID = 0;
		this->TargetCompIDLength = 0;
		this->AllowUsername = false;
		this->Username = 0;
		this->UsernameLength = 0;
		this->AllowPassword = false;
		this->Password = 0;
		this->PasswordLength = 0;
		this->DefaultApplVerID = 0;
		this->DefaultApplVerIDLength = 0;
	}
	~FastLogonInfo(){ }
	inline void Clear() {
		this->Used = false;
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowText;

	FastLogoutInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->TargetCompID = 0;
		this->TargetCompIDLength = 0;
		this->AllowText = false;
		this->Text = 0;
		this->TextLength = 0;
	}
	~FastLogoutInfo(){ }
	inline void Clear() {
		this->Used = false;
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							QuoteCondition;			// id=276  presence=optional  
	int							QuoteConditionLength;
	bool							AllowQuoteCondition;
	char*							TradeCondition;			// id=277  presence=optional  
	int							TradeConditionLength;
	bool							AllowTradeCondition;
	char*							OpenCloseSettlFlag;			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength;
	bool							AllowOpenCloseSettlFlag;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							AllowOrdType;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							AllowEffectiveTime;
	UINT32							StartTime;			// id=9820  presence=optional  
	bool							AllowStartTime;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	bool							AllowChgFromWAPrice;
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	bool							AllowChgOpenInterest;
	Decimal							BidMarketSize;			// id=5292  presence=optional  
	bool							AllowBidMarketSize;
	Decimal							AskMarketSize;			// id=5293  presence=optional  
	bool							AllowAskMarketSize;
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	bool							AllowTotalNumOfTrades;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							AllowTotalVolume;
	INT32							OfferNbOr;			// id=9168  presence=optional  
	bool							AllowOfferNbOr;
	INT32							BidNbOr;			// id=9169  presence=optional  
	bool							AllowBidNbOr;
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	bool							AllowChgFromSettlmnt;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	INT32							SumQtyOfBest;			// id=10503  presence=optional  
	bool							AllowSumQtyOfBest;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	Decimal							MinCurrPx;			// id=10509  presence=optional  
	bool							AllowMinCurrPx;
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional  
	bool							AllowMinCurrPxChgTime;
	UINT32							VolumeIndicator;			// id=7017  presence=optional  
	bool							AllowVolumeIndicator;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							AllowNominalValue;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							CXFlag;			// id=5154  presence=optional    copy
	int							CXFlagLength;
	char*							PrevCXFlag; // copy
	int							PrevCXFlagLength; // copy
	bool							AllowCXFlag;
	const UINT							CXFlagPresenceIndex = PRESENCE_MAP_INDEX1;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							AllowNetChgPrevDay;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastGenericItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowMDEntryType = false;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryDate = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowQuoteCondition = false;
		this->QuoteCondition = 0;
		this->QuoteConditionLength = 0;
		this->AllowTradeCondition = false;
		this->TradeCondition = 0;
		this->TradeConditionLength = 0;
		this->AllowOpenCloseSettlFlag = false;
		this->OpenCloseSettlFlag = 0;
		this->OpenCloseSettlFlagLength = 0;
		this->AllowOrdType = false;
		this->OrdType = 0;
		this->OrdTypeLength = 0;
		this->AllowEffectiveTime = false;
		this->AllowStartTime = false;
		this->AllowAccruedInterestAmt = false;
		this->AllowChgFromWAPrice = false;
		this->AllowChgOpenInterest = false;
		this->AllowBidMarketSize = false;
		this->AllowAskMarketSize = false;
		this->AllowTotalNumOfTrades = false;
		this->AllowTradeValue = false;
		this->AllowYield = false;
		this->AllowTotalVolume = false;
		this->AllowOfferNbOr = false;
		this->AllowBidNbOr = false;
		this->AllowChgFromSettlmnt = false;
		this->AllowSettlDate = false;
		this->AllowSettleType = false;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->AllowSumQtyOfBest = false;
		this->AllowOrderSide = false;
		this->OrderSide = 0;
		this->OrderSideLength = 0;
		this->AllowOrderStatus = false;
		this->OrderStatus = 0;
		this->OrderStatusLength = 0;
		this->AllowMinCurrPx = false;
		this->AllowMinCurrPxChgTime = false;
		this->AllowVolumeIndicator = false;
		this->AllowPrice = false;
		this->AllowPriceType = false;
		this->AllowNominalValue = false;
		this->AllowRepoToPx = false;
		this->AllowBuyBackPx = false;
		this->AllowBuyBackDate = false;
		this->AllowDealNumber = false;
		this->DealNumber = 0;
		this->DealNumberLength = 0;
		this->AllowCXFlag = false;
		this->CXFlag = 0;
		this->CXFlagLength = 0;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowRptSeq = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowNetChgPrevDay = false;
		this->AllowTradingSessionID = false;
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
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							AllowNetChgPrevDay;
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[64];

	FastGenericInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowTradSesStatus = false;
		this->AllowMDSecurityTradingStatus = false;
		this->AllowAuctionIndicator = false;
		this->AllowNetChgPrevDay = false;
	}
	~FastGenericInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	FastGenericItemInfo* GroupMDEntries[64];

	FastIncrementalGenericInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalGenericInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							AllowOrdType;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							AllowTotalVolume;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastOLSFONDItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowMDEntryType = false;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryDate = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowDealNumber = false;
		this->DealNumber = 0;
		this->DealNumberLength = 0;
		this->AllowYield = false;
		this->AllowOrderStatus = false;
		this->OrderStatus = 0;
		this->OrderStatusLength = 0;
		this->AllowOrdType = false;
		this->OrdType = 0;
		this->OrdTypeLength = 0;
		this->AllowTotalVolume = false;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowRptSeq = false;
		this->AllowTradingSessionID = false;
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
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	int							GroupMDEntriesCount;
	FastOLSFONDItemInfo* GroupMDEntries[64];

	FastOLSFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowTradSesStatus = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowMDSecurityTradingStatus = false;
		this->AllowAuctionIndicator = false;
	}
	~FastOLSFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastOLSCURRItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowMDEntryType = false;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryDate = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowDealNumber = false;
		this->DealNumber = 0;
		this->DealNumberLength = 0;
		this->AllowOrderStatus = false;
		this->OrderStatus = 0;
		this->OrderStatusLength = 0;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowRptSeq = false;
		this->AllowTradingSessionID = false;
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
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastOLSCURRItemInfo* GroupMDEntries[64];

	FastOLSCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowTradSesStatus = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowMDSecurityTradingStatus = false;
	}
	~FastOLSCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastTLSFONDItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryDate = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowOrderSide = false;
		this->OrderSide = 0;
		this->OrderSideLength = 0;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowAccruedInterestAmt = false;
		this->AllowTradeValue = false;
		this->AllowYield = false;
		this->AllowSettlDate = false;
		this->AllowSettleType = false;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->AllowPrice = false;
		this->AllowPriceType = false;
		this->AllowRepoToPx = false;
		this->AllowBuyBackPx = false;
		this->AllowBuyBackDate = false;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowRptSeq = false;
		this->AllowTradingSessionID = false;
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
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	int							GroupMDEntriesCount;
	FastTLSFONDItemInfo* GroupMDEntries[64];

	FastTLSFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowTradSesStatus = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowMDSecurityTradingStatus = false;
		this->AllowAuctionIndicator = false;
	}
	~FastTLSFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastTLSCURRItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryDate = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowOrderSide = false;
		this->OrderSide = 0;
		this->OrderSideLength = 0;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowTradeValue = false;
		this->AllowSettlDate = false;
		this->AllowSettleType = false;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->AllowPrice = false;
		this->AllowPriceType = false;
		this->AllowRepoToPx = false;
		this->AllowBuyBackPx = false;
		this->AllowBuyBackDate = false;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowRptSeq = false;
		this->AllowTradingSessionID = false;
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
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastTLSCURRItemInfo* GroupMDEntries[64];

	FastTLSCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowTradSesStatus = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowMDSecurityTradingStatus = false;
	}
	~FastTLSCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastOBSFONDItemInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastOBSFONDItemInfo>							*Pointer;
	AutoAllocatePointerList<FastOBSFONDItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							AllowEffectiveTime;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							AllowNominalValue;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastOBSFONDItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowMDEntryType = false;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowYield = false;
		this->AllowEffectiveTime = false;
		this->AllowNominalValue = false;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowRptSeq = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
	}
	~FastOBSFONDItemInfo(){ }
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

class FastOBSFONDInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastOBSFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastOBSFONDInfo>							*Allocator;
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
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	int							GroupMDEntriesCount;
	FastOBSFONDItemInfo* GroupMDEntries[64];

	FastOBSFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowTradSesStatus = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowMDSecurityTradingStatus = false;
		this->AllowAuctionIndicator = false;
	}
	~FastOBSFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastOBSCURRItemInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastOBSCURRItemInfo>							*Pointer;
	AutoAllocatePointerList<FastOBSCURRItemInfo>							*Allocator;
	bool							Used;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;

	FastOBSCURRItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowMDEntryType = false;
		this->MDEntryType = 0;
		this->MDEntryTypeLength = 0;
		this->AllowMDEntryID = false;
		this->MDEntryID = 0;
		this->MDEntryIDLength = 0;
		this->AllowMDEntryPx = false;
		this->AllowMDEntrySize = false;
		this->AllowMDEntryTime = false;
		this->AllowOrigTime = false;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowMDUpdateAction = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowRptSeq = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
	}
	~FastOBSCURRItemInfo(){ }
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

class FastOBSCURRInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastOBSCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastOBSCURRInfo>							*Allocator;
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
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastOBSCURRItemInfo* GroupMDEntries[64];

	FastOBSCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowLastMsgSeqNumProcessed = false;
		this->AllowTradSesStatus = false;
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowLastFragment = false;
		this->AllowRouteFirst = false;
		this->AllowMDSecurityTradingStatus = false;
	}
	~FastOBSCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[64];

	FastIncrementalMSRFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalMSRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	int							GroupMDEntriesCount;
	FastGenericItemInfo* GroupMDEntries[64];

	FastIncrementalMSRCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalMSRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	FastOLSFONDItemInfo* GroupMDEntries[64];

	FastIncrementalOLRFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalOLRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	FastOLSCURRItemInfo* GroupMDEntries[64];

	FastIncrementalOLRCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalOLRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalOBRFONDInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastIncrementalOBRFONDInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalOBRFONDInfo>							*Allocator;
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
	FastOBSFONDItemInfo* GroupMDEntries[64];

	FastIncrementalOBRFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalOBRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->ReleaseUnused();
	}
};

class FastIncrementalOBRCURRInfo{
public:
	UINT64							PresenceMap;
	LinkedPointer<FastIncrementalOBRCURRInfo>							*Pointer;
	AutoAllocatePointerList<FastIncrementalOBRCURRInfo>							*Allocator;
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
	FastOBSCURRItemInfo* GroupMDEntries[64];

	FastIncrementalOBRCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalOBRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	FastTLSFONDItemInfo* GroupMDEntries[64];

	FastIncrementalTLRFONDInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalTLRFONDInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	FastTLSCURRItemInfo* GroupMDEntries[64];

	FastIncrementalTLRCURRInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
	}
	~FastIncrementalTLRCURRInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupMDEntriesCount; i++)
			this->GroupMDEntries[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowInstrAttribValue;

	FastSecurityDefinitionGroupInstrAttribItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowInstrAttribValue = false;
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
	bool							AllowTradingSessionSubID;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	bool							AllowSecurityTradingStatus;
	INT32							OrderNote;			// id=9680  presence=optional  
	bool							AllowOrderNote;

	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowSecurityTradingStatus = false;
		this->AllowOrderNote = false;
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
	bool							AllowRoundLot;
	int							TradingSessionRulesGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* TradingSessionRulesGrp[64];			// presence=optional  
	bool							AllowTradingSessionRulesGrp;

	FastSecurityDefinitionMarketSegmentGrpItemInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->AllowRoundLot = false;
		this->AllowTradingSessionRulesGrp = false;
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
	bool							AllowTotNumReports;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	BYTE*							SecurityID;			// id=48  presence=optional  
	int							SecurityIDLength;
	bool							AllowSecurityID;
	BYTE*							SecurityIDSource;			// id=22  presence=optional  
	int							SecurityIDSourceLength;
	bool							AllowSecurityIDSource;
	INT32							Product;			// id=460  presence=optional  
	bool							AllowProduct;
	BYTE*							CFICode;			// id=461  presence=optional  
	int							CFICodeLength;
	bool							AllowCFICode;
	BYTE*							SecurityType;			// id=167  presence=optional  
	int							SecurityTypeLength;
	bool							AllowSecurityType;
	UINT32							MaturityDate;			// id=541  presence=optional  
	bool							AllowMaturityDate;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							OrigIssueAmt;			// id=5850  presence=optional  
	bool							AllowOrigIssueAmt;
	UINT32							CouponPaymentDate;			// id=224  presence=optional  
	bool							AllowCouponPaymentDate;
	Decimal							CouponRate;			// id=223  presence=optional  
	bool							AllowCouponRate;
	UINT32							SettlFixingDate;			// id=9119  presence=optional  
	bool							AllowSettlFixingDate;
	Decimal							DividendNetPx;			// id=9982  presence=optional  
	bool							AllowDividendNetPx;
	BYTE*							SecurityDesc;			// id=107  presence=optional  
	int							SecurityDescLength;
	bool							AllowSecurityDesc;
	BYTE*							EncodedSecurityDesc;			// id=351  presence=optional  
	int							EncodedSecurityDescLength;
	bool							AllowEncodedSecurityDesc;
	BYTE*							QuoteText;			// id=9696  presence=optional  
	int							QuoteTextLength;
	bool							AllowQuoteText;
	int							GroupInstrAttribCount;			// presence=optional  
	FastSecurityDefinitionGroupInstrAttribItemInfo* GroupInstrAttrib[64];			// presence=optional  
	bool							AllowGroupInstrAttrib;
	char*							Currency;			// id=15  presence=optional  
	int							CurrencyLength;
	bool							AllowCurrency;
	int							MarketSegmentGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpItemInfo* MarketSegmentGrp[64];			// presence=optional  
	bool							AllowMarketSegmentGrp;
	char*							SettlCurrency;			// id=120  presence=optional  
	int							SettlCurrencyLength;
	bool							AllowSettlCurrency;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	char*							StateSecurityID;			// id=5217  presence=optional  
	int							StateSecurityIDLength;
	bool							AllowStateSecurityID;
	BYTE*							EncodedShortSecurityDesc;			// id=5383  presence=optional  
	int							EncodedShortSecurityDescLength;
	bool							AllowEncodedShortSecurityDesc;
	BYTE*							MarketCode;			// id=5385  presence=optional  
	int							MarketCodeLength;
	bool							AllowMarketCode;
	Decimal							MinPriceIncrement;			// id=969  presence=optional  
	bool							AllowMinPriceIncrement;
	Decimal							MktShareLimit;			// id=5387  presence=optional  
	bool							AllowMktShareLimit;
	Decimal							MktShareThreshold;			// id=5388  presence=optional  
	bool							AllowMktShareThreshold;
	Decimal							MaxOrdersVolume;			// id=5389  presence=optional  
	bool							AllowMaxOrdersVolume;
	Decimal							PriceMvmLimit;			// id=5470  presence=optional  
	bool							AllowPriceMvmLimit;
	Decimal							FaceValue;			// id=5508  presence=optional  
	bool							AllowFaceValue;
	Decimal							BaseSwapPx;			// id=5556  presence=optional  
	bool							AllowBaseSwapPx;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	Decimal							NoSharesIssued;			// id=7595  presence=optional  
	bool							AllowNoSharesIssued;
	Decimal							HighLimit;			// id=9199  presence=optional  
	bool							AllowHighLimit;
	Decimal							LowLimit;			// id=9200  presence=optional  
	bool							AllowLowLimit;
	INT32							NumOfDaysToMaturity;			// id=10508  presence=optional  
	bool							AllowNumOfDaysToMaturity;

	FastSecurityDefinitionInfo(){
		this->Used = false;
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
		this->AllowTotNumReports = false;
		this->AllowSymbol = false;
		this->Symbol = 0;
		this->SymbolLength = 0;
		this->AllowSecurityID = false;
		this->AllowSecurityIDSource = false;
		this->AllowProduct = false;
		this->AllowCFICode = false;
		this->AllowSecurityType = false;
		this->AllowMaturityDate = false;
		this->AllowSettlDate = false;
		this->AllowSettleType = false;
		this->SettleType = 0;
		this->SettleTypeLength = 0;
		this->AllowOrigIssueAmt = false;
		this->AllowCouponPaymentDate = false;
		this->AllowCouponRate = false;
		this->AllowSettlFixingDate = false;
		this->AllowDividendNetPx = false;
		this->AllowSecurityDesc = false;
		this->AllowEncodedSecurityDesc = false;
		this->AllowQuoteText = false;
		this->AllowGroupInstrAttrib = false;
		this->AllowCurrency = false;
		this->Currency = 0;
		this->CurrencyLength = 0;
		this->AllowMarketSegmentGrp = false;
		this->AllowSettlCurrency = false;
		this->SettlCurrency = 0;
		this->SettlCurrencyLength = 0;
		this->AllowPriceType = false;
		this->AllowStateSecurityID = false;
		this->StateSecurityID = 0;
		this->StateSecurityIDLength = 0;
		this->AllowEncodedShortSecurityDesc = false;
		this->AllowMarketCode = false;
		this->AllowMinPriceIncrement = false;
		this->AllowMktShareLimit = false;
		this->AllowMktShareThreshold = false;
		this->AllowMaxOrdersVolume = false;
		this->AllowPriceMvmLimit = false;
		this->AllowFaceValue = false;
		this->AllowBaseSwapPx = false;
		this->AllowRepoToPx = false;
		this->AllowBuyBackPx = false;
		this->AllowBuyBackDate = false;
		this->AllowNoSharesIssued = false;
		this->AllowHighLimit = false;
		this->AllowLowLimit = false;
		this->AllowNumOfDaysToMaturity = false;
	}
	~FastSecurityDefinitionInfo(){ }
	inline void Clear() {
		this->Used = false;
		for(int i = 0; i < this->GroupInstrAttribCount; i++)
			this->GroupInstrAttrib[i]->Clear();
		for(int i = 0; i < this->MarketSegmentGrpCount; i++)
			this->MarketSegmentGrp[i]->Clear();
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	bool							AllowSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;

	FastSecurityStatusInfo(){
		this->Used = false;
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
		this->AllowTradingSessionID = false;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
		this->AllowTradingSessionSubID = false;
		this->TradingSessionSubID = 0;
		this->TradingSessionSubIDLength = 0;
		this->AllowSecurityTradingStatus = false;
		this->AllowAuctionIndicator = false;
	}
	~FastSecurityStatusInfo(){ }
	inline void Clear() {
		this->Used = false;
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	bool							AllowText;
	char*							TradingSessionID;			// id=336  
	int							TradingSessionIDLength;

	FastTradingSessionStatusInfo(){
		this->Used = false;
		this->PresenceMap = 0;
		this->MessageType = 0;
		this->MessageTypeLength = 0;
		this->ApplVerID = 0;
		this->ApplVerIDLength = 0;
		this->BeginString = 0;
		this->BeginStringLength = 0;
		this->SenderCompID = 0;
		this->SenderCompIDLength = 0;
		this->AllowText = false;
		this->Text = 0;
		this->TextLength = 0;
		this->TradingSessionID = 0;
		this->TradingSessionIDLength = 0;
	}
	~FastTradingSessionStatusInfo(){ }
	inline void Clear() {
		this->Used = false;
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

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
	}
	inline void ReleaseUnused() {
		if(this->Used)
			return;

	}
};

#pragma endregion

#endif //HFT_ROBOT_FASTTYPES_H
