#pragma once
#include "FixTypes.h"

#pragma region Message_Info_Structures_Definition_GeneratedCode
typedef struct _FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo {
	int			PresenceMap[2];
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	char*		QuoteCondition;			// id=276  presence=optional  
	int			QuoteConditionLength;
	char*		TradeCondition;			// id=277  presence=optional  
	int			TradeConditionLength;
	char*		OpenCloseSettlFlag;			// id=286  presence=optional  
	int			OpenCloseSettlFlagLength;
	char*		OrdType;			// id=40  presence=optional  
	int			OrdTypeLength;
	UINT32		EffectiveTime;			// id=5902  presence=optional  
	UINT32		StartTime;			// id=9820  presence=optional  
	Decimal		AccruedInterestAmt;			// id=5384  presence=optional  
	Decimal		ChgFromWAPrice;			// id=5510  presence=optional  
	Decimal		ChgOpenInterest;			// id=5511  presence=optional  
	Decimal		BidMarketSize;			// id=5292  presence=optional  
	Decimal		AskMarketSize;			// id=5293  presence=optional  
	INT32		TotalNumOfTrades;			// id=6139  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	Decimal		TotalVolume;			// id=5791  presence=optional  
	INT32		OfferNbOr;			// id=9168  presence=optional  
	INT32		BidNbOr;			// id=9169  presence=optional  
	Decimal		ChgFromSettlmnt;			// id=9750  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	INT32		SumQtyOfBest;			// id=10503  presence=optional  
	char*		OrderSide;			// id=10504  presence=optional  
	int			OrderSideLength;
	char*		OrderStatus;			// id=10505  presence=optional  
	int			OrderStatusLength;
	Decimal		MinCurrPx;			// id=10509  presence=optional  
	UINT32		MinCurrPxChgTime;			// id=10510  presence=optional  
	UINT32		VolumeIndicator;			// id=7017  presence=optional  
	Decimal		Price;			// id=44  presence=optional  
	INT32		PriceType;			// id=423  presence=optional  
	Decimal		NominalValue;			// id=9280  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	char*		DealNumber;			// id=9885  presence=optional    copy
	int			DealNumberLength;
	char*		PrevDealNumber; // copy
	int			PrevDealNumberLength; // copy
	char*		CXFlag;			// id=5154  presence=optional    copy
	int			CXFlagLength;
	char*		PrevCXFlag; // copy
	int			PrevCXFlagLength; // copy
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo {
	int			PresenceMap[2];
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	INT32		RptSeq;			// id=83  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		EffectiveTime;			// id=5902  presence=optional  
	UINT32		StartTime;			// id=9820  presence=optional  
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	char*		QuoteCondition;			// id=276  presence=optional  
	int			QuoteConditionLength;
	char*		TradeCondition;			// id=277  presence=optional  
	int			TradeConditionLength;
	char*		OpenCloseSettlFlag;			// id=286  presence=optional  
	int			OpenCloseSettlFlagLength;
	char*		OrdType;			// id=40  presence=optional  
	int			OrdTypeLength;
	Decimal		NetChgPrevDay;			// id=451  presence=optional  
	Decimal		AccruedInterestAmt;			// id=5384  presence=optional  
	Decimal		ChgFromWAPrice;			// id=5510  presence=optional  
	Decimal		ChgOpenInterest;			// id=5511  presence=optional  
	Decimal		BidMarketSize;			// id=5292  presence=optional  
	Decimal		AskMarketSize;			// id=5293  presence=optional  
	INT32		TotalNumOfTrades;			// id=6139  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	Decimal		TotalVolume;			// id=5791  presence=optional  
	INT32		OfferNbOr;			// id=9168  presence=optional  
	INT32		BidNbOr;			// id=9169  presence=optional  
	Decimal		ChgFromSettlmnt;			// id=9750  presence=optional  
	INT32		SumQtyOfBest;			// id=10503  presence=optional  
	char*		OrderSide;			// id=10504  presence=optional  
	int			OrderSideLength;
	char*		OrderStatus;			// id=10505  presence=optional  
	int			OrderStatusLength;
	Decimal		MinCurrPx;			// id=10509  presence=optional  
	UINT32		MinCurrPxChgTime;			// id=10510  presence=optional  
	UINT32		VolumeIndicator;			// id=7017  presence=optional  
	Decimal		Price;			// id=44  presence=optional  
	INT32		PriceType;			// id=423  presence=optional  
	Decimal		NominalValue;			// id=9280  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	char*		DealNumber;			// id=9885  presence=optional    copy
	int			DealNumberLength;
	char*		PrevDealNumber; // copy
	int			PrevDealNumberLength; // copy
	char*		CXFlag;			// id=5154  presence=optional    copy
	int			CXFlagLength;
	char*		PrevCXFlag; // copy
	int			PrevCXFlagLength; // copy
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo {
	int			PresenceMap[1];
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	char*		DealNumber;			// id=9885  presence=optional    copy
	int			DealNumberLength;
	char*		PrevDealNumber; // copy
	int			PrevDealNumberLength; // copy
	Decimal		Yield;			// id=236  presence=optional  
	char*		OrderStatus;			// id=10505  presence=optional  
	int			OrderStatusLength;
	char*		OrdType;			// id=40  presence=optional  
	int			OrdTypeLength;
	Decimal		TotalVolume;			// id=5791  presence=optional  
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo {
	int			PresenceMap[1];
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	char*		DealNumber;			// id=9885  presence=optional    copy
	int			DealNumberLength;
	char*		PrevDealNumber; // copy
	int			PrevDealNumberLength; // copy
	char*		OrderStatus;			// id=10505  presence=optional  
	int			OrderStatusLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo {
	char*		MDEntryType;			// id=269  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	char*		OrderSide;			// id=10504  presence=optional  
	int			OrderSideLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	Decimal		AccruedInterestAmt;			// id=5384  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	Decimal		Price;			// id=44  presence=optional  
	INT32		PriceType;			// id=423  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo {
	char*		MDEntryType;			// id=269  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	char*		OrderSide;			// id=10504  presence=optional  
	int			OrderSideLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	Decimal		Price;			// id=44  presence=optional  
	INT32		PriceType;			// id=423  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo {
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	UINT32		EffectiveTime;			// id=5902  presence=optional  
	Decimal		NominalValue;			// id=9280  presence=optional  
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo {
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo {
	int			PresenceMap[1];
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		StartTime;			// id=9820  presence=optional  
	char*		QuoteCondition;			// id=276  presence=optional  
	int			QuoteConditionLength;
	char*		TradeCondition;			// id=277  presence=optional  
	int			TradeConditionLength;
	char*		OpenCloseSettlFlag;			// id=286  presence=optional  
	int			OpenCloseSettlFlagLength;
	Decimal		NetChgPrevDay;			// id=451  presence=optional  
	Decimal		AccruedInterestAmt;			// id=5384  presence=optional  
	Decimal		ChgFromWAPrice;			// id=5510  presence=optional  
	Decimal		ChgOpenInterest;			// id=5511  presence=optional  
	Decimal		BidMarketSize;			// id=5292  presence=optional  
	Decimal		AskMarketSize;			// id=5293  presence=optional  
	INT32		TotalNumOfTrades;			// id=6139  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	INT32		OfferNbOr;			// id=9168  presence=optional  
	INT32		BidNbOr;			// id=9169  presence=optional  
	Decimal		ChgFromSettlmnt;			// id=9750  presence=optional  
	Decimal		MinCurrPx;			// id=10509  presence=optional  
	UINT32		MinCurrPxChgTime;			// id=10510  presence=optional  
	UINT32		VolumeIndicator;			// id=7017  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	char*		CXFlag;			// id=5154  presence=optional    copy
	int			CXFlagLength;
	char*		PrevCXFlag; // copy
	int			PrevCXFlagLength; // copy
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo {
	int			PresenceMap[1];
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	char*		QuoteCondition;			// id=276  presence=optional  
	int			QuoteConditionLength;
	char*		TradeCondition;			// id=277  presence=optional  
	int			TradeConditionLength;
	char*		OpenCloseSettlFlag;			// id=286  presence=optional  
	int			OpenCloseSettlFlagLength;
	Decimal		NetChgPrevDay;			// id=451  presence=optional  
	Decimal		ChgFromWAPrice;			// id=5510  presence=optional  
	Decimal		ChgOpenInterest;			// id=5511  presence=optional  
	INT32		TotalNumOfTrades;			// id=6139  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	INT32		OfferNbOr;			// id=9168  presence=optional  
	INT32		BidNbOr;			// id=9169  presence=optional  
	Decimal		ChgFromSettlmnt;			// id=9750  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	char*		CXFlag;			// id=5154  presence=optional    copy
	int			CXFlagLength;
	char*		PrevCXFlag; // copy
	int			PrevCXFlagLength; // copy
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo {
	int			PresenceMap[1];
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	char*		DealNumber;			// id=9885  presence=optional    copy
	int			DealNumberLength;
	char*		PrevDealNumber; // copy
	int			PrevDealNumberLength; // copy
	Decimal		Yield;			// id=236  presence=optional  
	char*		OrderStatus;			// id=10505  presence=optional  
	int			OrderStatusLength;
	char*		OrdType;			// id=40  presence=optional  
	int			OrdTypeLength;
	Decimal		TotalVolume;			// id=5791  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo {
	int			PresenceMap[1];
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	char*		DealNumber;			// id=9885  presence=optional    copy
	int			DealNumberLength;
	char*		PrevDealNumber; // copy
	int			PrevDealNumberLength; // copy
	char*		OrderStatus;			// id=10505  presence=optional  
	int			OrderStatusLength;
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo {
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	UINT32		EffectiveTime;			// id=5902  presence=optional  
	Decimal		NominalValue;			// id=9280  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo {
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  presence=optional  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo {
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	char*		OrderSide;			// id=10504  presence=optional  
	int			OrderSideLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	Decimal		AccruedInterestAmt;			// id=5384  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	Decimal		Yield;			// id=236  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	Decimal		Price;			// id=44  presence=optional  
	INT32		PriceType;			// id=423  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo {
	UINT32		MDUpdateAction;			// id=279  presence=optional  
	char*		MDEntryType;			// id=269  
	int			MDEntryTypeLength;
	char*		MDEntryID;			// id=278  presence=optional  
	int			MDEntryIDLength;
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	INT32		RptSeq;			// id=83  presence=optional  
	UINT32		MDEntryDate;			// id=272  presence=optional  
	UINT32		MDEntryTime;			// id=273  presence=optional  
	UINT32		OrigTime;			// id=9412  presence=optional  
	char*		OrderSide;			// id=10504  presence=optional  
	int			OrderSideLength;
	Decimal		MDEntryPx;			// id=270  presence=optional  
	Decimal		MDEntrySize;			// id=271  presence=optional  
	Decimal		TradeValue;			// id=6143  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	Decimal		Price;			// id=44  presence=optional  
	INT32		PriceType;			// id=423  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
}FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo;

typedef struct _FastSecurityDefinitionGroupInstrAttribItemInfo {
	INT32		InstrAttribType;			// id=871  
	BYTE*		InstrAttribValue;			// id=872  presence=optional  
	int			InstrAttribValueLength;
}FastSecurityDefinitionGroupInstrAttribItemInfo;

typedef struct _FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo {
	char*		TradingSessionID;			// id=336  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
	INT32		SecurityTradingStatus;			// id=326  presence=optional  
	INT32		OrderNote;			// id=9680  presence=optional  
}FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;

typedef struct _FastSecurityDefinitionMarketSegmentGrpItemInfo {
	Decimal		RoundLot;			// id=561  presence=optional  
	int			TradingSessionRulesGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo** TradingSessionRulesGrp;			// presence=optional  
}FastSecurityDefinitionMarketSegmentGrpItemInfo;

typedef struct _FastLogonInfo {
	char*		MessageType;			// id=35    constant has constant value = A
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	char*		TargetCompID;			// id=56  
	int			TargetCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	INT32		HeartBtInt;			// id=108  
	char*		Username;			// id=553  presence=optional  
	int			UsernameLength;
	char*		Password;			// id=554  presence=optional  
	int			PasswordLength;
	char*		DefaultApplVerID;			// id=1137  
	int			DefaultApplVerIDLength;
}FastLogonInfo;

typedef struct _FastLogoutInfo {
	char*		MessageType;			// id=35    constant has constant value = 5
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	char*		TargetCompID;			// id=56  
	int			TargetCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	char*		Text;			// id=58  presence=optional  
	int			TextLength;
}FastLogoutInfo;

typedef struct _FastMarketDataSnapshotFullRefreshGenericInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		TradSesStatus;			// id=340  presence=optional  
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32		AuctionIndicator;			// id=5509  presence=optional  
	Decimal		NetChgPrevDay;			// id=451  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshGenericInfo;

typedef struct _FastMarketDataIncrementalRefreshGenericInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshGenericInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		TradSesStatus;			// id=340  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32		AuctionIndicator;			// id=5509  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOLSFONDInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		TradSesStatus;			// id=340  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOLSCURRInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		TradSesStatus;			// id=340  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32		AuctionIndicator;			// id=5509  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshTLSFONDInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		TradSesStatus;			// id=340  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshTLSCURRInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	INT32		TradSesStatus;			// id=340  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	UINT32		AuctionIndicator;			// id=5509  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOBSFONDInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = W
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	UINT32		LastMsgSeqNumProcessed;			// id=369  presence=optional  
	INT32		RptSeq;			// id=83  
	INT32		TradSesStatus;			// id=340  presence=optional  
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		Symbol;			// id=55  
	int			SymbolLength;
	UINT32		LastFragment;			// id=893  presence=optional  
	UINT32		RouteFirst;			// id=7944  presence=optional  
	INT32		MDSecurityTradingStatus;			// id=1682  presence=optional  
	int			GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOBSCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshMSRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshMSRCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOLRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOLRCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOBRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOBRCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRFONDInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshTLRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRCURRInfo {
	char*		MessageType;			// id=35    constant has constant value = X
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	int			GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshTLRCURRInfo;

typedef struct _FastSecurityDefinitionInfo {
	int			PresenceMap[2];
	char*		MessageType;			// id=35    constant has constant value = d
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34    increment
	UINT64		SendingTime;			// id=52  
	char*		MessageEncoding;			// id=347    default
	int			MessageEncodingLength;
	INT32		TotNumReports;			// id=911  presence=optional  
	char*		Symbol;			// id=55  presence=optional  
	int			SymbolLength;
	BYTE*		SecurityID;			// id=48  presence=optional  
	int			SecurityIDLength;
	BYTE*		SecurityIDSource;			// id=22  presence=optional  
	int			SecurityIDSourceLength;
	INT32		Product;			// id=460  presence=optional  
	BYTE*		CFICode;			// id=461  presence=optional  
	int			CFICodeLength;
	BYTE*		SecurityType;			// id=167  presence=optional  
	int			SecurityTypeLength;
	UINT32		MaturityDate;			// id=541  presence=optional  
	UINT32		SettlDate;			// id=64  presence=optional  
	char*		SettleType;			// id=5459  presence=optional  
	int			SettleTypeLength;
	Decimal		OrigIssueAmt;			// id=5850  presence=optional  
	UINT32		CouponPaymentDate;			// id=224  presence=optional  
	Decimal		CouponRate;			// id=223  presence=optional  
	UINT32		SettlFixingDate;			// id=9119  presence=optional  
	Decimal		DividendNetPx;			// id=9982  presence=optional  
	BYTE*		SecurityDesc;			// id=107  presence=optional  
	int			SecurityDescLength;
	BYTE*		EncodedSecurityDesc;			// id=351  presence=optional  
	int			EncodedSecurityDescLength;
	BYTE*		QuoteText;			// id=9696  presence=optional  
	int			QuoteTextLength;
	int			GroupInstrAttribCount;			// presence=optional  
	FastSecurityDefinitionGroupInstrAttribItemInfo** GroupInstrAttrib;			// presence=optional  
	char*		Currency;			// id=15  presence=optional  
	int			CurrencyLength;
	int			MarketSegmentGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpItemInfo** MarketSegmentGrp;			// presence=optional  
	char*		SettlCurrency;			// id=120  presence=optional  
	int			SettlCurrencyLength;
	INT32		PriceType;			// id=423  presence=optional  
	char*		StateSecurityID;			// id=5217  presence=optional  
	int			StateSecurityIDLength;
	BYTE*		EncodedShortSecurityDesc;			// id=5383  presence=optional  
	int			EncodedShortSecurityDescLength;
	BYTE*		MarketCode;			// id=5385  presence=optional  
	int			MarketCodeLength;
	Decimal		MinPriceIncrement;			// id=969  presence=optional  
	Decimal		MktShareLimit;			// id=5387  presence=optional  
	Decimal		MktShareThreshold;			// id=5388  presence=optional  
	Decimal		MaxOrdersVolume;			// id=5389  presence=optional  
	Decimal		PriceMvmLimit;			// id=5470  presence=optional  
	Decimal		FaceValue;			// id=5508  presence=optional  
	Decimal		BaseSwapPx;			// id=5556  presence=optional  
	Decimal		RepoToPx;			// id=5677  presence=optional  
	Decimal		BuyBackPx;			// id=5558  presence=optional  
	UINT32		BuyBackDate;			// id=5559  presence=optional  
	Decimal		NoSharesIssued;			// id=7595  presence=optional  
	Decimal		HighLimit;			// id=9199  presence=optional  
	Decimal		LowLimit;			// id=9200  presence=optional  
	INT32		NumOfDaysToMaturity;			// id=10508  presence=optional  
}FastSecurityDefinitionInfo;

typedef struct _FastSecurityStatusInfo {
	char*		MessageType;			// id=35    constant has constant value = f
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	char*		Symbol;			// id=55  
	int			SymbolLength;
	char*		TradingSessionID;			// id=336  presence=optional  
	int			TradingSessionIDLength;
	char*		TradingSessionSubID;			// id=625  presence=optional  
	int			TradingSessionSubIDLength;
	INT32		SecurityTradingStatus;			// id=326  presence=optional  
	UINT32		AuctionIndicator;			// id=5509  presence=optional  
}FastSecurityStatusInfo;

typedef struct _FastTradingSessionStatusInfo {
	char*		MessageType;			// id=35    constant has constant value = h
	int			MessageTypeLength;
	char*		ApplVerID;			// id=1128    constant has constant value = 9
	int			ApplVerIDLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
	INT32		TradSesStatus;			// id=340  
	char*		Text;			// id=58  presence=optional  
	int			TextLength;
	char*		TradingSessionID;			// id=336  
	int			TradingSessionIDLength;
}FastTradingSessionStatusInfo;

typedef struct _FastHeartbeatInfo {
	char*		MessageType;			// id=35    constant has constant value = 0
	int			MessageTypeLength;
	char*		BeginString;			// id=8    constant has constant value = FIXT.1.1
	int			BeginStringLength;
	char*		SenderCompID;			// id=49    constant has constant value = MOEX
	int			SenderCompIDLength;
	UINT32		MsgSeqNum;			// id=34  
	UINT64		SendingTime;			// id=52  
}FastHeartbeatInfo;

#pragma endregion

class FastProtocolManager;

#pragma region Decode_Method_Pointer_Definition_GeneratedCode
typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();
#pragma endregion

#pragma region Checking_Presence_GeneratedCode
#define CheckMandatoryFieldPresence(field) (field != 0)
#define CheckOptionalFieldPresence(field) (field != 0)
#pragma endregion

class FastProtocolManager
{
	const int maxBufferLength = 16000;
	BYTE	*buffer;
	BYTE	*currentPos;
	int		bufferLength;

#pragma region Structure_Objects_Declaration_GeneratedCode
	FastLogonInfo*	logon;
	FastLogoutInfo*	logout;
	FastMarketDataSnapshotFullRefreshGenericInfo*	marketDataSnapshotFullRefreshGeneric;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshGenericInfo*	marketDataIncrementalRefreshGeneric;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo*	marketDataIncrementalRefreshGenericGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOLSFONDInfo*	marketDataSnapshotFullRefreshOLSFOND;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOLSCURRInfo*	marketDataSnapshotFullRefreshOLSCURR;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshTLSFONDInfo*	marketDataSnapshotFullRefreshTLSFOND;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshTLSCURRInfo*	marketDataSnapshotFullRefreshTLSCURR;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOBSFONDInfo*	marketDataSnapshotFullRefreshOBSFOND;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOBSCURRInfo*	marketDataSnapshotFullRefreshOBSCURR;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo*	marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshMSRFONDInfo*	marketDataIncrementalRefreshMSRFOND;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo*	marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshMSRCURRInfo*	marketDataIncrementalRefreshMSRCURR;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo*	marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOLRFONDInfo*	marketDataIncrementalRefreshOLRFOND;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo*	marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOLRCURRInfo*	marketDataIncrementalRefreshOLRCURR;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo*	marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOBRFONDInfo*	marketDataIncrementalRefreshOBRFOND;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo*	marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOBRCURRInfo*	marketDataIncrementalRefreshOBRCURR;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo*	marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshTLRFONDInfo*	marketDataIncrementalRefreshTLRFOND;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo*	marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshTLRCURRInfo*	marketDataIncrementalRefreshTLRCURR;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo*	marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;
	FastSecurityDefinitionInfo*	securityDefinition;
	FastSecurityDefinitionGroupInstrAttribItemInfo*	securityDefinitionGroupInstrAttribItems;
	FastSecurityDefinitionMarketSegmentGrpItemInfo*	securityDefinitionMarketSegmentGrpItems;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*	securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	FastSecurityStatusInfo*	securityStatus;
	FastTradingSessionStatusInfo*	tradingSessionStatus;
	FastHeartbeatInfo*	heartbeat;
	int		marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshGenericGroupMDEntriesItemsMaxCount;
	int		marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsMaxCount;
	int		marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsMaxCount;
	int		marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsMaxCount;
	int		marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsMaxCount;
	int		marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsMaxCount;
	int		marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsMaxCount;
	int		marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsMaxCount;
	int		securityDefinitionGroupInstrAttribItemsMaxCount;
	int		securityDefinitionMarketSegmentGrpItemsMaxCount;
	int		securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsMaxCount;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo*		marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo*		marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo*		marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo*		marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo*		marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo*		marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo*		marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo*		marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo*		marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo*		marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem;
	FastSecurityDefinitionGroupInstrAttribItemInfo*		securityDefinitionGroupInstrAttribItemsCurrentItem;
	FastSecurityDefinitionMarketSegmentGrpItemInfo*		securityDefinitionMarketSegmentGrpItemsCurrentItem;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*		securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem;

	void InitializeMessageInfo() {
		this->logon = new FastLogonInfo();
		memset(this->logon, 0, sizeof(FastLogonInfo));

		this->logout = new FastLogoutInfo();
		memset(this->logout, 0, sizeof(FastLogoutInfo));

		this->marketDataSnapshotFullRefreshGeneric = new FastMarketDataSnapshotFullRefreshGenericInfo();
		memset(this->marketDataSnapshotFullRefreshGeneric, 0, sizeof(FastMarketDataSnapshotFullRefreshGenericInfo));

		this->marketDataSnapshotFullRefreshGenericGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshGenericGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshGeneric = new FastMarketDataIncrementalRefreshGenericInfo();
		memset(this->marketDataIncrementalRefreshGeneric, 0, sizeof(FastMarketDataIncrementalRefreshGenericInfo));

		this->marketDataIncrementalRefreshGenericGroupMDEntriesItems = new FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshGenericGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshGenericGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataSnapshotFullRefreshOLSFOND = new FastMarketDataSnapshotFullRefreshOLSFONDInfo();
		memset(this->marketDataSnapshotFullRefreshOLSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshOLSFONDInfo));

		this->marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataSnapshotFullRefreshOLSCURR = new FastMarketDataSnapshotFullRefreshOLSCURRInfo();
		memset(this->marketDataSnapshotFullRefreshOLSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshOLSCURRInfo));

		this->marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataSnapshotFullRefreshTLSFOND = new FastMarketDataSnapshotFullRefreshTLSFONDInfo();
		memset(this->marketDataSnapshotFullRefreshTLSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshTLSFONDInfo));

		this->marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataSnapshotFullRefreshTLSCURR = new FastMarketDataSnapshotFullRefreshTLSCURRInfo();
		memset(this->marketDataSnapshotFullRefreshTLSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshTLSCURRInfo));

		this->marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataSnapshotFullRefreshOBSFOND = new FastMarketDataSnapshotFullRefreshOBSFONDInfo();
		memset(this->marketDataSnapshotFullRefreshOBSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshOBSFONDInfo));

		this->marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataSnapshotFullRefreshOBSCURR = new FastMarketDataSnapshotFullRefreshOBSCURRInfo();
		memset(this->marketDataSnapshotFullRefreshOBSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshOBSCURRInfo));

		this->marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo));
		this->marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshMSRFOND = new FastMarketDataIncrementalRefreshMSRFONDInfo();
		memset(this->marketDataIncrementalRefreshMSRFOND, 0, sizeof(FastMarketDataIncrementalRefreshMSRFONDInfo));

		this->marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshMSRCURR = new FastMarketDataIncrementalRefreshMSRCURRInfo();
		memset(this->marketDataIncrementalRefreshMSRCURR, 0, sizeof(FastMarketDataIncrementalRefreshMSRCURRInfo));

		this->marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshOLRFOND = new FastMarketDataIncrementalRefreshOLRFONDInfo();
		memset(this->marketDataIncrementalRefreshOLRFOND, 0, sizeof(FastMarketDataIncrementalRefreshOLRFONDInfo));

		this->marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshOLRCURR = new FastMarketDataIncrementalRefreshOLRCURRInfo();
		memset(this->marketDataIncrementalRefreshOLRCURR, 0, sizeof(FastMarketDataIncrementalRefreshOLRCURRInfo));

		this->marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshOBRFOND = new FastMarketDataIncrementalRefreshOBRFONDInfo();
		memset(this->marketDataIncrementalRefreshOBRFOND, 0, sizeof(FastMarketDataIncrementalRefreshOBRFONDInfo));

		this->marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshOBRCURR = new FastMarketDataIncrementalRefreshOBRCURRInfo();
		memset(this->marketDataIncrementalRefreshOBRCURR, 0, sizeof(FastMarketDataIncrementalRefreshOBRCURRInfo));

		this->marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshTLRFOND = new FastMarketDataIncrementalRefreshTLRFONDInfo();
		memset(this->marketDataIncrementalRefreshTLRFOND, 0, sizeof(FastMarketDataIncrementalRefreshTLRFONDInfo));

		this->marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->marketDataIncrementalRefreshTLRCURR = new FastMarketDataIncrementalRefreshTLRCURRInfo();
		memset(this->marketDataIncrementalRefreshTLRCURR, 0, sizeof(FastMarketDataIncrementalRefreshTLRCURRInfo));

		this->marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo[1024];
		memset(this->marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo));
		this->marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->securityDefinition = new FastSecurityDefinitionInfo();
		memset(this->securityDefinition, 0, sizeof(FastSecurityDefinitionInfo));

		this->securityDefinitionGroupInstrAttribItems = new FastSecurityDefinitionGroupInstrAttribItemInfo[1024];
		memset(this->securityDefinitionGroupInstrAttribItems, 0, 1024 * sizeof(FastSecurityDefinitionGroupInstrAttribItemInfo));
		this->securityDefinitionGroupInstrAttribItemsMaxCount = 1024;

		this->securityDefinitionMarketSegmentGrpItems = new FastSecurityDefinitionMarketSegmentGrpItemInfo[1024];
		memset(this->securityDefinitionMarketSegmentGrpItems, 0, 1024 * sizeof(FastSecurityDefinitionMarketSegmentGrpItemInfo));
		this->securityDefinitionMarketSegmentGrpItemsMaxCount = 1024;

		this->securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo[1024];
		memset(this->securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems, 0, 1024 * sizeof(FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo));
		this->securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsMaxCount = 1024;

		this->securityStatus = new FastSecurityStatusInfo();
		memset(this->securityStatus, 0, sizeof(FastSecurityStatusInfo));

		this->tradingSessionStatus = new FastTradingSessionStatusInfo();
		memset(this->tradingSessionStatus, 0, sizeof(FastTradingSessionStatusInfo));

		this->heartbeat = new FastHeartbeatInfo();
		memset(this->heartbeat, 0, sizeof(FastHeartbeatInfo));

	}

	void ResetMessageInfoIndicies() {
		this->marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;
		this->marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshGenericGroupMDEntriesItems;
		this->marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;
		this->marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;
		this->marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;
		this->marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;
		this->marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;
		this->marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem = this->marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;
		this->marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;
		this->marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;
		this->marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;
		this->marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;
		this->marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;
		this->marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;
		this->marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;
		this->marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem = this->marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;
		this->securityDefinitionGroupInstrAttribItemsCurrentItem = this->securityDefinitionGroupInstrAttribItems;
		this->securityDefinitionMarketSegmentGrpItemsCurrentItem = this->securityDefinitionMarketSegmentGrpItems;
		this->securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem = this->securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}
#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
	FastDecodeMethodPointer* DecodeMethods_Generic;
	FastDecodeMethodPointer* DecodeMethods_OLS_FOND;
	FastDecodeMethodPointer* DecodeMethods_OLS_CURR;
	FastDecodeMethodPointer* DecodeMethods_TLS_FOND;
	FastDecodeMethodPointer* DecodeMethods_TLS_CURR;
	FastDecodeMethodPointer* DecodeMethods_OBS_FOND;
	FastDecodeMethodPointer* DecodeMethods_OBS_CURR;
	FastDecodeMethodPointer* DecodeMethods_MSR_FOND;
	FastDecodeMethodPointer* DecodeMethods_MSR_CURR;
	FastDecodeMethodPointer* DecodeMethods_OLR_FOND;
	FastDecodeMethodPointer* DecodeMethods_OLR_CURR;
	FastDecodeMethodPointer* DecodeMethods_OBR_FOND;
	FastDecodeMethodPointer* DecodeMethods_OBR_CURR;
	FastDecodeMethodPointer* DecodeMethods_TLR_FOND;
	FastDecodeMethodPointer* DecodeMethods_TLR_CURR;

	void InitializeDecodeMethodPointers() {
		int ptCount = 256;
		this->DecodeMethods_Generic = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_Generic, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_Generic[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_Generic[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_Generic[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshGeneric;
		this->DecodeMethods_Generic[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshGeneric;
		this->DecodeMethods_Generic[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_Generic[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_Generic[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_Generic[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLS_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLS_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OLS_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLS_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLS_FOND[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOLSFOND;
		this->DecodeMethods_OLS_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLS_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLS_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLS_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLS_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLS_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OLS_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLS_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLS_CURR[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOLSCURR;
		this->DecodeMethods_OLS_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLS_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLS_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLS_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLS_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLS_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_TLS_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLS_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLS_FOND[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshTLSFOND;
		this->DecodeMethods_TLS_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLS_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLS_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLS_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLS_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLS_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_TLS_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLS_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLS_CURR[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshTLSCURR;
		this->DecodeMethods_TLS_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLS_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLS_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLS_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBS_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBS_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OBS_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBS_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBS_FOND[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOBSFOND;
		this->DecodeMethods_OBS_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBS_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBS_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBS_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBS_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBS_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OBS_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBS_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBS_CURR[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOBSCURR;
		this->DecodeMethods_OBS_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBS_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBS_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBS_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_MSR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_MSR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_MSR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_MSR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_MSR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshMSRFOND;
		this->DecodeMethods_MSR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_MSR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_MSR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_MSR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_MSR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_MSR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_MSR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_MSR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_MSR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshMSRCURR;
		this->DecodeMethods_MSR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_MSR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_MSR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_MSR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OLR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOLRFOND;
		this->DecodeMethods_OLR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OLR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOLRCURR;
		this->DecodeMethods_OLR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OBR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOBRFOND;
		this->DecodeMethods_OBR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_OBR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOBRCURR;
		this->DecodeMethods_OBR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_TLR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshTLRFOND;
		this->DecodeMethods_TLR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		this->DecodeMethods_TLR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshTLRCURR;
		this->DecodeMethods_TLR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

	}

#pragma endregion

#pragma region Get_Free_Item_Methods_GeneratedCode
	inline FastLogonInfo* GetFreeLogonInfo() {
		return this->logon;
	}

	inline FastLogoutInfo* GetFreeLogoutInfo() {
		return this->logout;
	}

	inline FastMarketDataSnapshotFullRefreshGenericInfo* GetFreeMarketDataSnapshotFullRefreshGenericInfo() {
		return this->marketDataSnapshotFullRefreshGeneric;
	}

	inline FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshGenericInfo* GetFreeMarketDataIncrementalRefreshGenericInfo() {
		return this->marketDataIncrementalRefreshGeneric;
	}

	inline FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOLSFONDInfo* GetFreeMarketDataSnapshotFullRefreshOLSFONDInfo() {
		return this->marketDataSnapshotFullRefreshOLSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOLSCURRInfo* GetFreeMarketDataSnapshotFullRefreshOLSCURRInfo() {
		return this->marketDataSnapshotFullRefreshOLSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshTLSFONDInfo* GetFreeMarketDataSnapshotFullRefreshTLSFONDInfo() {
		return this->marketDataSnapshotFullRefreshTLSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshTLSCURRInfo* GetFreeMarketDataSnapshotFullRefreshTLSCURRInfo() {
		return this->marketDataSnapshotFullRefreshTLSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOBSFONDInfo* GetFreeMarketDataSnapshotFullRefreshOBSFONDInfo() {
		return this->marketDataSnapshotFullRefreshOBSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOBSCURRInfo* GetFreeMarketDataSnapshotFullRefreshOBSCURRInfo() {
		return this->marketDataSnapshotFullRefreshOBSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo() {
		return this->marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshMSRFONDInfo* GetFreeMarketDataIncrementalRefreshMSRFONDInfo() {
		return this->marketDataIncrementalRefreshMSRFOND;
	}

	inline FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshMSRCURRInfo* GetFreeMarketDataIncrementalRefreshMSRCURRInfo() {
		return this->marketDataIncrementalRefreshMSRCURR;
	}

	inline FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOLRFONDInfo* GetFreeMarketDataIncrementalRefreshOLRFONDInfo() {
		return this->marketDataIncrementalRefreshOLRFOND;
	}

	inline FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOLRCURRInfo* GetFreeMarketDataIncrementalRefreshOLRCURRInfo() {
		return this->marketDataIncrementalRefreshOLRCURR;
	}

	inline FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOBRFONDInfo* GetFreeMarketDataIncrementalRefreshOBRFONDInfo() {
		return this->marketDataIncrementalRefreshOBRFOND;
	}

	inline FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOBRCURRInfo* GetFreeMarketDataIncrementalRefreshOBRCURRInfo() {
		return this->marketDataIncrementalRefreshOBRCURR;
	}

	inline FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshTLRFONDInfo* GetFreeMarketDataIncrementalRefreshTLRFONDInfo() {
		return this->marketDataIncrementalRefreshTLRFOND;
	}

	inline FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshTLRCURRInfo* GetFreeMarketDataIncrementalRefreshTLRCURRInfo() {
		return this->marketDataIncrementalRefreshTLRCURR;
	}

	inline FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo() {
		return this->marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastSecurityDefinitionInfo* GetFreeSecurityDefinitionInfo() {
		return this->securityDefinition;
	}

	inline FastSecurityDefinitionGroupInstrAttribItemInfo* GetFreeSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->securityDefinitionGroupInstrAttribItemsCurrentItem;
	}

	inline FastSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->securityDefinitionMarketSegmentGrpItemsCurrentItem;
	}

	inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem;
	}

	inline FastSecurityStatusInfo* GetFreeSecurityStatusInfo() {
		return this->securityStatus;
	}

	inline FastTradingSessionStatusInfo* GetFreeTradingSessionStatusInfo() {
		return this->tradingSessionStatus;
	}

	inline FastHeartbeatInfo* GetFreeHeartbeatInfo() {
		return this->heartbeat;
	}

	inline void EncodeEncodeLogoutInfo(int msgSeqNumber, FastLogoutInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(msgSeqNumber);
		WriteString_Mandatory(info->MessageType, info->MessageTypeLength);
		WriteString_Mandatory(info->BeginString, info->BeginStringLength);
		WriteString_Mandatory(info->SenderCompID, info->SenderCompIDLength);
		WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteString_Optional(info->Text, info->TextLength);
	}
	inline void EncodeEncodeSecurityStatusInfo(int msgSeqNumber, FastSecurityStatusInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(msgSeqNumber);
		WriteString_Mandatory(info->MessageType, info->MessageTypeLength);
		WriteString_Mandatory(info->ApplVerID, info->ApplVerIDLength);
		WriteString_Mandatory(info->BeginString, info->BeginStringLength);
		WriteString_Mandatory(info->SenderCompID, info->SenderCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteString_Mandatory(info->Symbol, info->SymbolLength);
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
		WriteString_Optional(info->TradingSessionSubID, info->TradingSessionSubIDLength);
		WriteInt32_Optional(info->SecurityTradingStatus);
		WriteUInt32_Optional(info->AuctionIndicator);
	}
	inline void EncodeEncodeTradingSessionStatusInfo(int msgSeqNumber, FastTradingSessionStatusInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(msgSeqNumber);
		WriteString_Mandatory(info->MessageType, info->MessageTypeLength);
		WriteString_Mandatory(info->ApplVerID, info->ApplVerIDLength);
		WriteString_Mandatory(info->BeginString, info->BeginStringLength);
		WriteString_Mandatory(info->SenderCompID, info->SenderCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteInt32_Mandatory(info->TradSesStatus);
		WriteString_Optional(info->Text, info->TextLength);
		WriteString_Mandatory(info->TradingSessionID, info->TradingSessionIDLength);
	}
	inline void EncodeEncodeHeartbeatInfo(int msgSeqNumber, FastHeartbeatInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(msgSeqNumber);
		WriteString_Mandatory(info->MessageType, info->MessageTypeLength);
		WriteString_Mandatory(info->BeginString, info->BeginStringLength);
		WriteString_Mandatory(info->SenderCompID, info->SenderCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
	}
#pragma endregion

public:

#pragma region Core_Methods
	inline bool FastCompareString1(char *str1, char *str2) { return *str1 == *str2; }
	inline bool FastCompareString4(char *str1, char *str2) { return *((int*)str1) == *((int*)str2); }
	inline bool FastCompareString8(char *str1, char *str2) { return *((UINT64*)str1) == *((UINT64*)str2); }
	inline void ResetBuffer() { this->currentPos = this->buffer; }
	inline void SetNewBuffer(BYTE *buffer, int length) { 
		this->buffer = buffer;
		this->bufferLength = length;
		this->ResetBuffer();
	} 
	inline void ClearBuffer() { memset(this->buffer, 0, this->bufferLength); }
	inline char ReadMsgType() { throw; }
	inline bool CheckBuffer(BYTE *arrayToCompare, int length) {
		int lengthInt = length / 4;
		for (int i = 0; i < lengthInt; i++)
			if (((int*)this->buffer)[i] != ((int*)arrayToCompare)[i])
				return false;
		int length2 = length % 4;
		for (int i = lengthInt * 4; i < length; i++)
			if (this->buffer[i] != arrayToCompare[i])
				return false;
		return true;
	}
	inline bool CheckBufferFromCurrent(BYTE *arrayToCompare, int length) { 
		int lengthInt = length / 4;
		for (int i = 0; i < lengthInt; i++)
			if (((int*)this->currentPos)[i] != ((int*)arrayToCompare)[i])
				return false;
		int length2 = length % 4;
		for (int i = lengthInt * 4; i < length; i++)
			if (this->currentPos[i] != arrayToCompare[i])
				return false;
		return true;
	}
	
	inline void WriteMsgSeqNumber(int msgSeqNumber) {
		*((int*)this->currentPos) = msgSeqNumber;
		this->currentPos += 4;
	}

	inline int ReadMsgSeqNumber() {
		int result = *(int*)this->currentPos;
		this->currentPos += 4;
		return result;
	}

	inline bool IsNull() {  return *(this->currentPos) == 0x80; }

	inline bool CheckProcessNullInt32() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullUInt32() { 
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcesNullInt64() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullUint64() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullString() {
		WORD str = *((WORD*)this->currentPos);
		if (str == 0x0000)
			return false;
		if ((str & 0xFF) == 0x00) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullByteVector() {
		return CheckProcessNullUInt32();
	}
	inline bool CheckProcessNullDecimal() {
		return CheckProcessNullInt32();
	}

	inline void WriteInt32_Mandatory(INT32 value) { 
		int encoded = 0;
		if (value >= 0) {

			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos++;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					*(this->currentPos) = 0x00;
					this->currentPos++;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
			}

			if ((value & 0x40) != 0) { 
				*(this->currentPos) = 0x00;
				this->currentPos++;
			}

			*(this->currentPos) = value;
			this->currentPos++;

			*((int*)this->currentPos) = encoded;
			this->currentPos += 4;
		}
		else {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos++;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos += 2;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos += 3;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					*this->currentPos = 0x7f;
					this->currentPos++;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos += 4;
				return;
			}

			if ((value & 0x40) == 0) { 
				(*this->currentPos) = 0x7f;
				this->currentPos++;
			}
			*(this->currentPos) = (BYTE)(value & 0x7f);
			this->currentPos++;

			*((int*)this->currentPos) = encoded;
			this->currentPos += 4;
		}
	}
	inline void WriteInt32_Optional(INT32 value) {
		if (value > 0)
			value++;
		WriteInt32_Mandatory(value);
	}

	inline void WriteUInt32_Mandatory(UINT32 value) {
		UINT encoded = 0;

		encoded |= ((value & 0x7f) | 0x80);
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos++;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos += 2;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos += 3;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos += 4;
			return;
		}

		*(this->currentPos) = value;
		this->currentPos++;

		*((int*)this->currentPos) = encoded;
		this->currentPos += 4;
	}
	inline void WriteUInt32_Optional(UINT32 value) {
		value++;
		WriteUInt32_Mandatory(value);
	}

	inline INT32 ReadInt32_Optional() {
		INT32 result = ReadInt32_Mandatory();
		if (result > 0)
			return result - 1;
		return result;
	}
	inline INT32 ReadInt32_Mandatory() {
		INT32 result;
		INT32 memory = *((INT32*)(this->currentPos));

		INT32 valueMasked = memory & 0xff;

		if (valueMasked == 0x00) { // extended positive integer
			result = 0;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}
			this->currentPos += 4;

			result <<= 7;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 2;
			return result;
		}
		else if (valueMasked == 0x7f) { // extended negative integer
			result = 0;
			memory >>= 8;

			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			this->currentPos += 4;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;
			
			this->currentPos ++;
			return result;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer 
			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}
			this->currentPos += 4;
			result <<= 7;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;

			this->currentPos++;
			return result;
		}
		else {  // simple positive integer
			result = 0;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			this->currentPos += 4;

			result <<= 7;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;

			this->currentPos++;
			return result;
		}
	}
	
	inline UINT32 ReadUInt32_Mandatory() {
		INT32 result = 0;
		INT32 memory = *((INT32*)(this->currentPos));

		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos++;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 2;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 3;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 4;
			return result;
		}

		this->currentPos += 4;

		result <<= 7;
		memory = *((INT32*)(this->currentPos));
		result |= memory & 0x7f;

		this->currentPos++;
		return result;
	}
	inline UINT32 ReadUInt32_Optional() {
		INT32 result = ReadUInt32_Mandatory();
		return result - 1;
	}

	inline void WriteInt64_Optional(INT64 value) {
		if (value > 0)
			value++;
		WriteInt64_Mandatory(value);
	}
	inline void WriteInt64_Mandatory(INT64 value) { 
		INT64 encoded = 0;
		INT32 encoded2;
		if (value >= 0) {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos++;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					*((INT64*)this->currentPos) = 0x00;
					this->currentPos++;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 = value & 0x7f;
			value >>= 7;
			if (value == 0) {
				if ((encoded2 & 0x40) != 0) {
					encoded2 <<= 8;
					*((INT32*)(this->currentPos)) = encoded2;
					this->currentPos += 2;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT32*)(this->currentPos)) = encoded2;
					this->currentPos++;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 <<= 8;
			encoded2 |= value & 0x7f;

			*((INT32*)(this->currentPos)) = encoded2;
			this->currentPos += 2;

			*((INT64*)this->currentPos) = encoded;
			this->currentPos += 8;
		}
		else {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos++;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 2;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 3;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 4;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 5;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 6;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 7;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					(*this->currentPos) = 0x7f;
					this->currentPos++;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 8;
				return;
			}

			encoded2 = value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded2 & 0x40) == 0) {
					encoded2 <<= 8;
					encoded2 |= 0x7f;

					*((INT64*)this->currentPos) = encoded2;
					this->currentPos += 2;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded2;
					this->currentPos++;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 <<= 8;
			encoded2 |= value & 0x7f;

			*((INT64*)this->currentPos) = encoded2;
			this->currentPos += 2;

			*((INT64*)this->currentPos) = encoded;
			this->currentPos += 8;
			return;
		}
	}
	
	inline void WriteUInt64_Optional(UINT64 value) {
		value++;
		WriteUInt64_Mandatory(value);
	}
	inline void WriteUInt64_Mandatory(UINT64 value) {
		UINT64 encoded = 0;
		UINT encoded2;

		encoded |= ((value & 0x7f) | 0x80);
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos++;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 2;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 3;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 4;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 5;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 6;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 7;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 8;
			return;
		}

		encoded2 = value & 0x7f;
		value >>= 7;
		if (value == 0) { 
			*((UINT*)this->currentPos) = encoded2;
			this->currentPos ++;
			*((UINT64*)this->currentPos) = encoded;
			return;
		}
	
		encoded2 <<= 8;
		encoded2 |= value;

		*((UINT*)this->currentPos) = encoded2;
		this->currentPos +=2;
		*((UINT64*)this->currentPos) = encoded;
		return;
	}

	inline INT64 ReadInt64_Mandatory() {
		INT64 result;
		INT64 memory = *((INT64*)(this->currentPos));

		INT64 valueMasked = memory & 0xff;

		if (valueMasked == 0x00) { // extended positive integer
			result = 0;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}
			
			this->currentPos += 8;

			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 3;
			return result;
		}
		else if (valueMasked == 0x7f) { // extended negative integer
			result = 0;
			memory >>= 8;

			result = 0xffffffffffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}
			
			this->currentPos += 8;
			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;

			if ((memory & 0x80) != 0) {
				this->currentPos ++;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 3;
			return result;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer 
			result = 0xffffffffffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}

			this->currentPos += 8;
			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;

			if ((memory & 0x80) != 0) {
				this->currentPos ++;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 3;
			return result;
		}
		else {  // simple positive integer
			result = 0;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}

			this->currentPos += 8;

			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;

			if ((memory & 0x80) != 0) {
				this->currentPos ++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			this->currentPos += 3;
			return result;
		}
	}
	inline INT64 ReadInt64_Optional() {
		INT64 value = ReadInt64_Mandatory();
		if (value > 0)
			return value - 1;
		return value;
	}

	inline UINT64 ReadUInt64_Mandatory() {
		UINT64 result;
		UINT64 memory = *(UINT64*)this->currentPos;

		result = memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos++;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 2;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 3;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 4;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 5;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 6;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 7;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 8;
			return result;
		}

		this->currentPos += 8;

		result <<= 7;
		memory = *((INT64*)(this->currentPos));
		result |= memory & 0x7f;

		if ((memory & 0x80) != 0) {
			this->currentPos ++;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;

		this->currentPos +=2;
		return result;
	}
	inline UINT64 ReadUInt64_Optional() {
		return ReadUInt64_Mandatory() - 1;
	}

	inline void CopyToBuffer(BYTE *value, int length) { 
		memcpy(this->buffer, value, length);
	}

	inline void ReadDecimal_Optional(Decimal *value) { 
		value->Mantissa = ReadInt32_Mandatory();
		value->Exponent = ReadInt32_Optional();
	}

	inline void ReadDecimal_Mandatory(Decimal *value) { 
		value->Mantissa = ReadInt32_Mandatory();
		value->Exponent = ReadInt32_Mandatory();
	}

	inline void WriteDecimal_Optional(Decimal *value) { 
		WriteInt32_Optional(value->Exponent);
		WriteInt32_Mandatory(value->Mantissa);
		return;
	}
	inline void WriteDecimal_Mandatory(Decimal *value) { 
		WriteInt32_Mandatory(value->Exponent);
		WriteInt32_Mandatory(value->Mantissa);
		return;
	}

	inline void WriteString_Optional(char *str, int length) { 
		if (str == NULL) { 
			*(this->currentPos) = 0x80;
			this->currentPos++;
		}
		else if (length == 0) { 
			*((int*)this->currentPos) = 0x8000;
			this->currentPos += 2;
			return;
		}
		memcpy(this->currentPos, str, length);
		this->currentPos[length - 1] |= 0x80;
		this->currentPos += length;
	}
	inline void WriteString_Mandatory(char *str, int length) { 
		if (length == 0) {
			*((int*)this->currentPos) = 0x80;
			this->currentPos ++;
			return;
		}
		memcpy(this->currentPos, str, length);
		this->currentPos[length - 1] |= 0x80;
		this->currentPos += length;
	}

	inline void ReadString_Optional(char **strPtrAddress, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		int length = 0;
		if ((memory & 0xffff) == 0x8000) { 
			*strPtrAddress = (char*)this->currentPos;
			lengthAddress = 0;
			this->currentPos += 2;
			return;
		}
		*strPtrAddress = (char*)this->currentPos;
		while (true) {
			if ((memory & 0x8080808080808080) != 0) { 
				if ((memory & 0x0000000080808080) != 0) { 
					if ((memory & 0x8080) != 0) {
						if ((memory & 0x80) != 0) { 
							this->currentPos[0] &= 0x7f;
							length++;
							this->currentPos++;
							break;
						}
						else { 
							this->currentPos[1] &= 0x7f;
							length += 2;
							this->currentPos += 2;
							break;
						}
					}
					else { 
						if ((memory & 0x800000) != 0) { 
							this->currentPos[2] &= 0x7f;
							length += 3;
							this->currentPos += 3;
							break;
						}
						else {
							this->currentPos[3] &= 0x7f;
							length += 4;
							this->currentPos += 4;
							break;
						}
					}
				}
				else { 
					if ((memory & 0x0000808000000000) != 0) { 
						if ((memory & 0x0000008000000000) != 0) { 
							this->currentPos[4] &= 0x7f;
							length += 5;
							this->currentPos += 5;
							break;
						}
						else { 
							this->currentPos[5] &= 0x7f;
							length += 6;
							this->currentPos += 6;
							break;
						}
					}
					else { 
						if ((memory & 0x0080000000000000) != 0) {
							this->currentPos[6] &= 0x7f;
							length += 7;
							this->currentPos += 7;
							break;
						}
						else { 
							this->currentPos[7] &= 0x7f;
							length += 8;
							this->currentPos += 8;
							break;
						}
					}
				}
			}
			length += 8;
			this->currentPos += 8;
			memory = *((UINT64*)this->currentPos);
		}
		*lengthAddress = length;
	}
	inline void ReadString_Mandatory(char **strPtrAddress, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		int length = 0;
		if ((memory & 0xff) == 0x80) {
			*(this->currentPos) = 0;
			*strPtrAddress = (char*)this->currentPos;
			lengthAddress = 0;
			this->currentPos ++;
			return;
		}
		*strPtrAddress = (char*)this->currentPos;
		while (true) {
			if ((memory & 0x8080808080808080) != 0) {
				if ((memory & 0x0000000080808080) != 0) {
					if ((memory & 0x8080) != 0) {
						if ((memory & 0x80) != 0) {
							this->currentPos[0] &= 0x7f;
							length++;
							this->currentPos++;
							break;
						}
						else {
							this->currentPos[1] &= 0x7f;
							length += 2;
							this->currentPos += 2;
							break;
						}
					}
					else {
						if ((memory & 0x800000) != 0) {
							this->currentPos[2] &= 0x7f;
							length += 3;
							this->currentPos += 3;
							break;
						}
						else {
							this->currentPos[3] &= 0x7f;
							length += 4;
							this->currentPos += 4;
							break;
						}
					}
				}
				else {
					if ((memory & 0x0000808000000000) != 0) {
						if ((memory & 0x0000008000000000) != 0) {
							this->currentPos[4] &= 0x7f;
							length += 5;
							this->currentPos += 5;
							break;
						}
						else {
							this->currentPos[5] &= 0x7f;
							length += 6;
							this->currentPos += 6;
							break;
						}
					}
					else {
						if ((memory & 0x0080000000000000) != 0) {
							this->currentPos[6] &= 0x7f;
							length += 7;
							this->currentPos += 7;
							break;
						}
						else {
							this->currentPos[7] &= 0x7f;
							length += 8;
							this->currentPos += 8;
							break;
						}
					}
				}
			}
			length += 8;
			this->currentPos += 8;
			memory = *((UINT64*)this->currentPos);
		}
		*lengthAddress = length;
	}

	inline void ReadByteVector_Optional(BYTE **vecPtrAddress, int *lengthAddress) { 
		int length = ReadInt32_Optional();
		*vecPtrAddress = this->currentPos;
		this->currentPos += length;
		*lengthAddress = length;
	}
	inline void ReadByteVector_Mandatory(BYTE **vecPtrAddress, int *lengthAddress) { 
		int length = ReadInt32_Mandatory();
		*vecPtrAddress = this->currentPos;
		this->currentPos += length;
		*lengthAddress = length;
	}

	inline void WriteByteVector_Optional(BYTE *vecPtr, int length) { 
		if (vecPtr == NULL) { 
			*(this->currentPos) = 0x80;
			this->currentPos++;
			return;
		}
		WriteInt32_Optional(length);
		memcpy(this->currentPos, vecPtr, length);
		this->currentPos += length;
	}
	inline void WriteByteVector_Mandatory(BYTE *vecPtr, int length) {
		WriteInt32_Mandatory(length);
		memcpy(this->currentPos, vecPtr, length);
		this->currentPos += length;
	}

	inline void ParsePresenceMap(int *presenceMapBits, int maxBitsCount) { 
		int *pmap = (int*)this->currentPos;
		int value;
		int *intPmap = presenceMapBits;
		while (true) {
			value = *pmap;
			for (int i = 0; i < 7; i++) {
				*intPmap = (value & 0x01);
				intPmap++;
				value >>= 1;
			}
			this->currentPos++;
			if ((value & 0x01) == 1)
				return;
			value >>= 1;

			for (int i = 0; i < 7; i++) {
				*intPmap = (value & 0x01);
				intPmap++;
				value >>= 1;
			}
			this->currentPos++;
			if ((value & 0x01) == 1)
				return;
			value >>= 1;
			for (int i = 0; i < 7; i++) {
				*intPmap = (value & 0x01);
				intPmap++;
				value >>= 1;
			}
			this->currentPos++;
			if ((value & 0x01) == 1)
				return;
			value >>= 1;
			for (int i = 0; i < 7; i++) {
				*intPmap = (value & 0x01);
				intPmap++;
				value >>= 1;
			}
			this->currentPos++;
			if ((value & 0x01) == 1)
				return;
			pmap++;
		}
	}

	FastProtocolManager();
	~FastProtocolManager();

	inline BYTE* Buffer() { return this->buffer; }
	inline BYTE* CurrentPos() { return this->currentPos; }
	inline int BufferLength() { return this->bufferLength; }
	inline int UsedLength() { return this->currentPos - this->buffer; }
	inline void SetBufferLength(int value) { this->bufferLength = value; }
#pragma endregion

#pragma region Encode_Methods_Definition_GeneratedCode
#pragma endregion

#pragma region Decode_Methods_Definition_GeneratedCode
	void* DecodeLogon() {
		FastLogonInfo* info = GetFreeLogonInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->HeartBtInt = ReadInt32_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Username), &(info->UsernameLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Password), &(info->PasswordLength));
		ReadString_Mandatory(&(info->DefaultApplVerID), &(info->DefaultApplVerIDLength));
		return info;
	}
	void* DecodeLogout() {
		FastLogoutInfo* info = GetFreeLogoutInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshGeneric() {
		FastMarketDataSnapshotFullRefreshGenericInfo* info = GetFreeMarketDataSnapshotFullRefreshGenericInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->NetChgPrevDay));

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 2);

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[1])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshGeneric() {
		FastMarketDataIncrementalRefreshGenericInfo* info = GetFreeMarketDataIncrementalRefreshGenericInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 2);

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[1])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOLSFOND() {
		FastMarketDataSnapshotFullRefreshOLSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshOLSFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 1);

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOLSCURR() {
		FastMarketDataSnapshotFullRefreshOLSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshOLSCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 1);

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshTLSFOND() {
		FastMarketDataSnapshotFullRefreshTLSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshTLSFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshTLSCURR() {
		FastMarketDataSnapshotFullRefreshTLSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshTLSCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOBSFOND() {
		FastMarketDataSnapshotFullRefreshOBSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshOBSFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOBSCURR() {
		FastMarketDataSnapshotFullRefreshOBSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshOBSCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshMSRFOND() {
		FastMarketDataIncrementalRefreshMSRFONDInfo* info = GetFreeMarketDataIncrementalRefreshMSRFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 1);

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshMSRCURR() {
		FastMarketDataIncrementalRefreshMSRCURRInfo* info = GetFreeMarketDataIncrementalRefreshMSRCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 1);

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOLRFOND() {
		FastMarketDataIncrementalRefreshOLRFONDInfo* info = GetFreeMarketDataIncrementalRefreshOLRFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 1);

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOLRCURR() {
		FastMarketDataIncrementalRefreshOLRCURRInfo* info = GetFreeMarketDataIncrementalRefreshOLRCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			ParsePresenceMap(gmdeItemInfo->PresenceMap, 1);

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap[0])) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOBRFOND() {
		FastMarketDataIncrementalRefreshOBRFONDInfo* info = GetFreeMarketDataIncrementalRefreshOBRFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOBRCURR() {
		FastMarketDataIncrementalRefreshOBRCURRInfo* info = GetFreeMarketDataIncrementalRefreshOBRCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshTLRFOND() {
		FastMarketDataIncrementalRefreshTLRFONDInfo* info = GetFreeMarketDataIncrementalRefreshTLRFONDInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshTLRCURR() {
		FastMarketDataIncrementalRefreshTLRCURRInfo* info = GetFreeMarketDataIncrementalRefreshTLRCURRInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeSecurityDefinition() {
		FastSecurityDefinitionInfo* info = GetFreeSecurityDefinitionInfo();

		ParsePresenceMap(info->PresenceMap, 2);

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		if(CheckMandatoryFieldPresence(info->PresenceMap[0])) {
			info->MsgSeqNum = ReadUInt32_Mandatory();
		}
		else {
			info->MsgSeqNum++;
		}
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckMandatoryFieldPresence(info->PresenceMap[1])) {
			ReadString_Mandatory(&(info->MessageEncoding), &(info->MessageEncodingLength));
		}
		else {
			info->MessageEncoding = const_cast<char *>("UTF-8");
			info->MessageEncodingLength = 5;
		}
		if(!CheckProcessNullInt32())
			info->TotNumReports = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityID), &(info->SecurityIDLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityIDSource), &(info->SecurityIDSourceLength));
		if(!CheckProcessNullInt32())
			info->Product = ReadInt32_Optional();
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->CFICode), &(info->CFICodeLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityType), &(info->SecurityTypeLength));
		if(!CheckProcessNullUInt32())
			info->MaturityDate = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->SettlDate = ReadUInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->SettleType), &(info->SettleTypeLength));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->OrigIssueAmt));
		if(!CheckProcessNullUInt32())
			info->CouponPaymentDate = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->CouponRate));
		if(!CheckProcessNullUInt32())
			info->SettlFixingDate = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->DividendNetPx));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityDesc), &(info->SecurityDescLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->EncodedSecurityDesc), &(info->EncodedSecurityDescLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->QuoteText), &(info->QuoteTextLength));

		info->GroupInstrAttribCount = ReadUInt32_Mandatory();
		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;
		FastSecurityDefinitionGroupInstrAttribItemInfo** giaItemInfoList = info->GroupInstrAttrib;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = GetFreeSecurityDefinitionGroupInstrAttribItemInfo();
			(*giaItemInfoList) = giaItemInfo;
			giaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			if(!CheckProcessNullByteVector())
				ReadByteVector_Optional(&(giaItemInfo->InstrAttribValue), &(giaItemInfo->InstrAttribValueLength));
			giaItemInfoList++;
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Currency), &(info->CurrencyLength));

		info->MarketSegmentGrpCount = ReadUInt32_Mandatory();
		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;
		FastSecurityDefinitionMarketSegmentGrpItemInfo** msgItemInfoList = info->MarketSegmentGrp;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpItemInfo();
			(*msgItemInfoList) = msgItemInfo;
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(msgItemInfo->RoundLot));

			msgItemInfo->TradingSessionRulesGrpCount = ReadUInt32_Mandatory();
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo** tsrgItemInfoList = msgItemInfo->TradingSessionRulesGrp;

			for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
				tsrgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
				(*tsrgItemInfoList) = tsrgItemInfo;
				ReadString_Mandatory(&(tsrgItemInfo->TradingSessionID), &(tsrgItemInfo->TradingSessionIDLength));
				if(!CheckProcessNullString())
					ReadString_Optional(&(tsrgItemInfo->TradingSessionSubID), &(tsrgItemInfo->TradingSessionSubIDLength));
				if(!CheckProcessNullInt32())
					tsrgItemInfo->SecurityTradingStatus = ReadInt32_Optional();
				if(!CheckProcessNullInt32())
					tsrgItemInfo->OrderNote = ReadInt32_Optional();
				tsrgItemInfoList++;
			}

			msgItemInfoList++;
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->SettlCurrency), &(info->SettlCurrencyLength));
		if(!CheckProcessNullInt32())
			info->PriceType = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->StateSecurityID), &(info->StateSecurityIDLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->EncodedShortSecurityDesc), &(info->EncodedShortSecurityDescLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->MarketCode), &(info->MarketCodeLength));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MktShareLimit));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MktShareThreshold));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MaxOrdersVolume));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->PriceMvmLimit));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->FaceValue));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->BaseSwapPx));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->RepoToPx));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->BuyBackPx));
		if(!CheckProcessNullUInt32())
			info->BuyBackDate = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->NoSharesIssued));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->HighLimit));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->LowLimit));
		if(!CheckProcessNullInt32())
			info->NumOfDaysToMaturity = ReadInt32_Optional();
		return info;
	}
	void* DecodeSecurityStatus() {
		FastSecurityStatusInfo* info = GetFreeSecurityStatusInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionSubID), &(info->TradingSessionSubIDLength));
		if(!CheckProcessNullInt32())
			info->SecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		return info;
	}
	void* DecodeTradingSessionStatus() {
		FastTradingSessionStatusInfo* info = GetFreeTradingSessionStatusInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesStatus = ReadInt32_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		ReadString_Mandatory(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		return info;
	}
	void* DecodeHeartbeat() {
		FastHeartbeatInfo* info = GetFreeHeartbeatInfo();

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void Decode_Generic() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_Generic[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLS_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLS_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLS_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLS_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLS_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLS_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLS_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLS_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBS_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBS_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBS_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBS_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_MSR_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_MSR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_MSR_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_MSR_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLR_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLR_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLR_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBR_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBR_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBR_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLR_FOND() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLR_CURR() {
		char msgType = ReadMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLR_CURR[msgType];
		(this->*funcPtr)();
	}
#pragma endregion
};

