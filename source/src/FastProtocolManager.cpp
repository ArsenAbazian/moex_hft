#include "FastProtocolManager.h"


FastProtocolManager::FastProtocolManager() {
	this->InitializeConstantStrings();
	this->InitializeDecodeMethodPointers();
	this->InitializeMessageInfo();
	this->m_snapshotInfo = new FastSnapshotInfo();
	this->m_skipTemplateIdCount = 0;
}


FastProtocolManager::~FastProtocolManager() {

}

void FastProtocolManager::PrintTabs(int tabCount) {
	for(int i = 0; i < tabCount; i++)
		printf("\t");
}

void FastProtocolManager::PrintPresenceMap(UINT64 map, int count, int tabsCount) {
	this->PrintTabs(tabsCount);
	printf("PresenceMap = ");
	UINT64 values[56] = {
			PRESENCE_MAP_INDEX0,
			PRESENCE_MAP_INDEX1,
			PRESENCE_MAP_INDEX2,
			PRESENCE_MAP_INDEX3,
			PRESENCE_MAP_INDEX4,
			PRESENCE_MAP_INDEX5,
			PRESENCE_MAP_INDEX6,
			PRESENCE_MAP_INDEX7,
			PRESENCE_MAP_INDEX8,
			PRESENCE_MAP_INDEX9,
			PRESENCE_MAP_INDEX10,
			PRESENCE_MAP_INDEX11,
			PRESENCE_MAP_INDEX12,
			PRESENCE_MAP_INDEX13,
			PRESENCE_MAP_INDEX14,
			PRESENCE_MAP_INDEX15,
			PRESENCE_MAP_INDEX16,
			PRESENCE_MAP_INDEX17,
			PRESENCE_MAP_INDEX18,
			PRESENCE_MAP_INDEX19,
			PRESENCE_MAP_INDEX20,
			PRESENCE_MAP_INDEX21,
			PRESENCE_MAP_INDEX22,
			PRESENCE_MAP_INDEX23,
			PRESENCE_MAP_INDEX24,
			PRESENCE_MAP_INDEX25,
			PRESENCE_MAP_INDEX26,
			PRESENCE_MAP_INDEX27,
			PRESENCE_MAP_INDEX28,
			PRESENCE_MAP_INDEX29,
			PRESENCE_MAP_INDEX30,
			PRESENCE_MAP_INDEX31,
			PRESENCE_MAP_INDEX32,
			PRESENCE_MAP_INDEX33,
			PRESENCE_MAP_INDEX34,
			PRESENCE_MAP_INDEX35,
			PRESENCE_MAP_INDEX36,
			PRESENCE_MAP_INDEX37,
			PRESENCE_MAP_INDEX38,
			PRESENCE_MAP_INDEX39,
			PRESENCE_MAP_INDEX40,
			PRESENCE_MAP_INDEX41,
			PRESENCE_MAP_INDEX42,
			PRESENCE_MAP_INDEX43,
			PRESENCE_MAP_INDEX44,
			PRESENCE_MAP_INDEX45,
			PRESENCE_MAP_INDEX46,
			PRESENCE_MAP_INDEX47,
			PRESENCE_MAP_INDEX48,
			PRESENCE_MAP_INDEX49,
			PRESENCE_MAP_INDEX50,
			PRESENCE_MAP_INDEX51,
			PRESENCE_MAP_INDEX52,
			PRESENCE_MAP_INDEX53,
			PRESENCE_MAP_INDEX54,
			PRESENCE_MAP_INDEX55
	};
	for(int i = 0; i < count; i++) {
		if((map & values[i]) == 1)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

void FastProtocolManager::PrintXmlPresenceMap(UINT64 map, int count) {
	fprintf(this->m_xmlFilePtr, "<PresenceMap value=\"");
	UINT64 values[56] = {
			PRESENCE_MAP_INDEX0,
			PRESENCE_MAP_INDEX1,
			PRESENCE_MAP_INDEX2,
			PRESENCE_MAP_INDEX3,
			PRESENCE_MAP_INDEX4,
			PRESENCE_MAP_INDEX5,
			PRESENCE_MAP_INDEX6,
			PRESENCE_MAP_INDEX7,
			PRESENCE_MAP_INDEX8,
			PRESENCE_MAP_INDEX9,
			PRESENCE_MAP_INDEX10,
			PRESENCE_MAP_INDEX11,
			PRESENCE_MAP_INDEX12,
			PRESENCE_MAP_INDEX13,
			PRESENCE_MAP_INDEX14,
			PRESENCE_MAP_INDEX15,
			PRESENCE_MAP_INDEX16,
			PRESENCE_MAP_INDEX17,
			PRESENCE_MAP_INDEX18,
			PRESENCE_MAP_INDEX19,
			PRESENCE_MAP_INDEX20,
			PRESENCE_MAP_INDEX21,
			PRESENCE_MAP_INDEX22,
			PRESENCE_MAP_INDEX23,
			PRESENCE_MAP_INDEX24,
			PRESENCE_MAP_INDEX25,
			PRESENCE_MAP_INDEX26,
			PRESENCE_MAP_INDEX27,
			PRESENCE_MAP_INDEX28,
			PRESENCE_MAP_INDEX29,
			PRESENCE_MAP_INDEX30,
			PRESENCE_MAP_INDEX31,
			PRESENCE_MAP_INDEX32,
			PRESENCE_MAP_INDEX33,
			PRESENCE_MAP_INDEX34,
			PRESENCE_MAP_INDEX35,
			PRESENCE_MAP_INDEX36,
			PRESENCE_MAP_INDEX37,
			PRESENCE_MAP_INDEX38,
			PRESENCE_MAP_INDEX39,
			PRESENCE_MAP_INDEX40,
			PRESENCE_MAP_INDEX41,
			PRESENCE_MAP_INDEX42,
			PRESENCE_MAP_INDEX43,
			PRESENCE_MAP_INDEX44,
			PRESENCE_MAP_INDEX45,
			PRESENCE_MAP_INDEX46,
			PRESENCE_MAP_INDEX47,
			PRESENCE_MAP_INDEX48,
			PRESENCE_MAP_INDEX49,
			PRESENCE_MAP_INDEX50,
			PRESENCE_MAP_INDEX51,
			PRESENCE_MAP_INDEX52,
			PRESENCE_MAP_INDEX53,
			PRESENCE_MAP_INDEX54,
			PRESENCE_MAP_INDEX55
	};
	for(int i = 0; i < count; i++) {
		if((map & values[i]) == 1)
			fprintf(this->m_xmlFilePtr, "1");
		else
			fprintf(this->m_xmlFilePtr, "0");
	}
	fprintf(this->m_xmlFilePtr, "\"/>");
}

void FastProtocolManager::PrintXmlInt32(const char *name, int value) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"%d\"/>", name, value);
}
void FastProtocolManager::PrintXmlUInt32(const char *name, UINT value) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"%u\"/>", name, value);
}
void FastProtocolManager::PrintXmlInt64(const char *name, INT64 value) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"%" PRId64 "\"/>", name, value);
}
void FastProtocolManager::PrintXmlUInt64(const char *name, UINT64 value) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"%" PRIu64 "\"/>", name, value);
}
void FastProtocolManager::PrintXmlItemBegin(const char *name, int index) {
	fprintf(this->m_xmlFilePtr, "<%s%d>", name, index);
}
void FastProtocolManager::PrintXmlItemEnd(const char *name, int index) {
	fprintf(this->m_xmlFilePtr, "</%s%d>", name, index);
}
void FastProtocolManager::PrintXmlItemBegin(const char *name) {
    fprintf(this->m_xmlFilePtr, "<%s>", name);
}
void FastProtocolManager::PrintXmlItemEnd(const char *name) {
    fprintf(this->m_xmlFilePtr, "</%s>", name);
}
void FastProtocolManager::PrintXmlString(const char *name, char *str, int count) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"", name);
	for(int i = 0; i < count; i++)
		fprintf(this->m_xmlFilePtr, "%c", str[i]);
	fprintf(this->m_xmlFilePtr, "\"/>");
}
void FastProtocolManager::PrintXmlByteVector(const char *name, unsigned char *data, int count) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"", name);
	for(int i = 0; i < count; i++) {
		if(i == count - 1)
			fprintf(this->m_xmlFilePtr, "%02x", data[i]);
		else
			fprintf(this->m_xmlFilePtr, "%02x ", data[i]);
	}
	fprintf(this->m_xmlFilePtr, "\"/>");
}
void FastProtocolManager::PrintXmlDecimal(const char *name, Decimal *value) {
	fprintf(this->m_xmlFilePtr, "<%s value=\"", name);
	INT64 intVal = value->Mantissa;
	if(value->Exponent >= 0) {
		for(int i = 0; i < value->Exponent; i++) {
			intVal *= 10;
		}
		fprintf(this->m_xmlFilePtr, "%" PRId64, intVal);
	}
	if(value->Exponent < 0) {
		for(int i = value->Exponent; i < 0; i++) {
			intVal = intVal / 10;
		}
		fprintf(this->m_xmlFilePtr, "%" PRId64 ".", intVal);
		for(int i = value->Exponent; i < 0; i++) {
			intVal = intVal * 10;
		}
		intVal = value->Mantissa - intVal;
		fprintf(this->m_xmlFilePtr, "%" PRId64, intVal);
	}
	fprintf(this->m_xmlFilePtr, "\"/>");
}

bool FastProtocolManager::BeginExportXml(const char *fileName) {
	this->m_xmlFilePtr = fopen(fileName, "wt");
	if(this->m_xmlFilePtr == NULL)
		return false;
	fprintf(this->m_xmlFilePtr, "<messages>");
	return true;
}

void FastProtocolManager::EndExportXml() {
	fprintf(this->m_xmlFilePtr, "</messages>");
	fclose(this->m_xmlFilePtr);
}

void FastProtocolManager::PrintInt32(const char *name, int value, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = %d\n", name, value);
}
void FastProtocolManager::PrintUInt32(const char *name, UINT value, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = %u\n", name, value);
}
void FastProtocolManager::PrintInt64(const char *name, INT64 value, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = %" PRId64 "\n", name, value);
}
void FastProtocolManager::PrintUInt64(const char *name, UINT64 value, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = %" PRIu64 "\n", name, value);
}
void FastProtocolManager::PrintItemBegin(const char *name, int index, int tabsCount) {
	this->PrintTabs(tabsCount);
	printf("%s%d {\n", name, index);
}
void FastProtocolManager::PrintItemEnd(int tabsCount) {
	this->PrintTabs(tabsCount);
	printf("}\n");
}
void FastProtocolManager::PrintString(const char *name, char *str, int count, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = '", name);
	for(int i = 0; i < count; i++)
		printf("%c", str[i]);
	printf("'\n");
}
void FastProtocolManager::PrintByteVector(const char *name, unsigned char *data, int count, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = '", name);
	for(int i = 0; i < count; i++) {
		if(i == count - 1)
			printf("%02x", data[i]);
		else
			printf("%02x ", data[i]);
	}
	printf("' -> '");
	for(int i = 0; i < count; i++)
		printf("%c", data[i]);
	printf("'\n");
}
void FastProtocolManager::PrintDecimal(const char *name, Decimal *value, int tabCount) {
	this->PrintTabs(tabCount);
	printf("%s = ", name);
	INT64 intVal = value->Mantissa;
	if(value->Exponent >= 0) {
		for(int i = 0; i < value->Exponent; i++) {
			intVal *= 10;
		}
		printf("%" PRId64, intVal);
	}
	if(value->Exponent < 0) {
		for(int i = value->Exponent; i < 0; i++) {
			intVal = intVal / 10;
		}
		printf("%" PRId64 ".", intVal);
		for(int i = value->Exponent; i < 0; i++) {
			intVal = intVal * 10;
		}
		intVal = value->Mantissa - intVal;
		printf("%" PRId64, intVal);
	}
	printf("\n");
}

#pragma region Print_Methods_Definition_GeneratedCode
void FastProtocolManager::PrintLogon(FastLogonInfo *info) {

	printf("FastLogonInfo {\n");
	PrintInt32("TemplateId", 2101, 1);
	PrintString("TargetCompID", info->TargetCompID, info->TargetCompIDLength, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("HeartBtInt", info->HeartBtInt, 1);
	if(info->AllowUsername)
		PrintString("Username", info->Username, info->UsernameLength, 1);
	if(info->AllowPassword)
		PrintString("Password", info->Password, info->PasswordLength, 1);
	PrintString("DefaultApplVerID", info->DefaultApplVerID, info->DefaultApplVerIDLength, 1);
	printf("}\n");
}
void FastProtocolManager::PrintLogout(FastLogoutInfo *info) {

	printf("FastLogoutInfo {\n");
	PrintInt32("TemplateId", 2102, 1);
	PrintString("TargetCompID", info->TargetCompID, info->TargetCompIDLength, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowText)
		PrintString("Text", info->Text, info->TextLength, 1);
	printf("}\n");
}
void FastProtocolManager::PrintGeneric(FastGenericInfo *info) {

	printf("FastGenericInfo {\n");
	PrintInt32("TemplateId", 2103, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if(info->AllowAuctionIndicator)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	if(info->AllowNetChgPrevDay)
		PrintDecimal("NetChgPrevDay", &(info->NetChgPrevDay), 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if(gmdeItemInfo->AllowOrdType)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		if(gmdeItemInfo->AllowStartTime)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if(gmdeItemInfo->AllowBidMarketSize)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if(gmdeItemInfo->AllowAskMarketSize)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowTotalVolume)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowSumQtyOfBest)
			PrintInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest, 2);
		if(gmdeItemInfo->AllowOrderSide)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if(gmdeItemInfo->AllowMinCurrPx)
			PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		if(gmdeItemInfo->AllowMinCurrPxChgTime)
			PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		if(gmdeItemInfo->AllowVolumeIndicator)
			PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		if(gmdeItemInfo->AllowPrice)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if(gmdeItemInfo->AllowPriceType)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if(gmdeItemInfo->AllowNominalValue)
			PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if(gmdeItemInfo->AllowDealNumber)
			PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		if(gmdeItemInfo->AllowCXFlag)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalGeneric(FastIncrementalGenericInfo *info) {

	printf("FastIncrementalGenericInfo {\n");
	PrintInt32("TemplateId", 2104, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		if(gmdeItemInfo->AllowStartTime)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if(gmdeItemInfo->AllowOrdType)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if(gmdeItemInfo->AllowNetChgPrevDay)
			PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if(gmdeItemInfo->AllowBidMarketSize)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if(gmdeItemInfo->AllowAskMarketSize)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowTotalVolume)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if(gmdeItemInfo->AllowSumQtyOfBest)
			PrintInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest, 2);
		if(gmdeItemInfo->AllowOrderSide)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if(gmdeItemInfo->AllowMinCurrPx)
			PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		if(gmdeItemInfo->AllowMinCurrPxChgTime)
			PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		if(gmdeItemInfo->AllowVolumeIndicator)
			PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		if(gmdeItemInfo->AllowPrice)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if(gmdeItemInfo->AllowPriceType)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if(gmdeItemInfo->AllowNominalValue)
			PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if(gmdeItemInfo->AllowDealNumber)
			PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		if(gmdeItemInfo->AllowCXFlag)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintOLSFOND(FastOLSFONDInfo *info) {

	printf("FastOLSFONDInfo {\n");
	PrintInt32("TemplateId", 2410, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if(info->AllowAuctionIndicator)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowDealNumber)
			PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if(gmdeItemInfo->AllowOrdType)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if(gmdeItemInfo->AllowTotalVolume)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintOLSCURR(FastOLSCURRInfo *info) {

	printf("FastOLSCURRInfo {\n");
	PrintInt32("TemplateId", 3500, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowDealNumber)
			PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintTLSFOND(FastTLSFONDInfo *info) {

	printf("FastTLSFONDInfo {\n");
	PrintInt32("TemplateId", 2411, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if(info->AllowAuctionIndicator)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowOrderSide)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowPrice)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if(gmdeItemInfo->AllowPriceType)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintTLSCURR(FastTLSCURRInfo *info) {

	printf("FastTLSCURRInfo {\n");
	PrintInt32("TemplateId", 3501, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowOrderSide)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowPrice)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if(gmdeItemInfo->AllowPriceType)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintOBSFOND(FastOBSFONDInfo *info) {

	printf("FastOBSFONDInfo {\n");
	PrintInt32("TemplateId", 2412, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if(info->AllowAuctionIndicator)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOBSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		if(gmdeItemInfo->AllowNominalValue)
			PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintOBSCURR(FastOBSCURRInfo *info) {

	printf("FastOBSCURRInfo {\n");
	PrintInt32("TemplateId", 3502, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if(info->AllowTradSesStatus)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowLastFragment)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if(info->AllowRouteFirst)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if(info->AllowMDSecurityTradingStatus)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOBSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info) {

	printf("FastIncrementalMSRFONDInfo {\n");
	PrintInt32("TemplateId", 2423, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowStartTime)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if(gmdeItemInfo->AllowNetChgPrevDay)
			PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if(gmdeItemInfo->AllowBidMarketSize)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if(gmdeItemInfo->AllowAskMarketSize)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if(gmdeItemInfo->AllowMinCurrPx)
			PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		if(gmdeItemInfo->AllowMinCurrPxChgTime)
			PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		if(gmdeItemInfo->AllowVolumeIndicator)
			PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowCXFlag)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info) {

	printf("FastIncrementalMSRCURRInfo {\n");
	PrintInt32("TemplateId", 3513, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if(gmdeItemInfo->AllowNetChgPrevDay)
			PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowCXFlag)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info) {

	printf("FastIncrementalOLRFONDInfo {\n");
	PrintInt32("TemplateId", 2420, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowDealNumber)
			PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if(gmdeItemInfo->AllowOrdType)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if(gmdeItemInfo->AllowTotalVolume)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info) {

	printf("FastIncrementalOLRCURRInfo {\n");
	PrintInt32("TemplateId", 3510, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowDealNumber)
			PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalOBRFOND(FastIncrementalOBRFONDInfo *info) {

	printf("FastIncrementalOBRFONDInfo {\n");
	PrintInt32("TemplateId", 2422, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOBSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		if(gmdeItemInfo->AllowNominalValue)
			PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalOBRCURR(FastIncrementalOBRCURRInfo *info) {

	printf("FastIncrementalOBRCURRInfo {\n");
	PrintInt32("TemplateId", 3512, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOBSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalTLRFOND(FastIncrementalTLRFONDInfo *info) {

	printf("FastIncrementalTLRFONDInfo {\n");
	PrintInt32("TemplateId", 2421, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowOrderSide)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowYield)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowPrice)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if(gmdeItemInfo->AllowPriceType)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalTLRCURR(FastIncrementalTLRCURRInfo *info) {

	printf("FastIncrementalTLRCURRInfo {\n");
	PrintInt32("TemplateId", 3511, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if(gmdeItemInfo->AllowSymbol)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if(gmdeItemInfo->AllowRptSeq)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if(gmdeItemInfo->AllowOrigTime)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if(gmdeItemInfo->AllowOrderSide)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if(gmdeItemInfo->AllowTradeValue)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if(gmdeItemInfo->AllowSettlDate)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if(gmdeItemInfo->AllowSettleType)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if(gmdeItemInfo->AllowPrice)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if(gmdeItemInfo->AllowPriceType)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintSecurityDefinition(FastSecurityDefinitionInfo *info) {

	printf("FastSecurityDefinitionInfo {\n");
	PrintInt32("TemplateId", 2115, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintString("MessageEncoding", info->MessageEncoding, info->MessageEncodingLength, 1);
	if(info->AllowTotNumReports)
		PrintInt32("TotNumReports", info->TotNumReports, 1);
	if(info->AllowSymbol)
		PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowSecurityID)
		PrintByteVector("SecurityID", info->SecurityID, info->SecurityIDLength, 1);
	if(info->AllowSecurityIDSource)
		PrintByteVector("SecurityIDSource", info->SecurityIDSource, info->SecurityIDSourceLength, 1);
	if(info->AllowProduct)
		PrintInt32("Product", info->Product, 1);
	if(info->AllowCFICode)
		PrintByteVector("CFICode", info->CFICode, info->CFICodeLength, 1);
	if(info->AllowSecurityType)
		PrintByteVector("SecurityType", info->SecurityType, info->SecurityTypeLength, 1);
	if(info->AllowMaturityDate)
		PrintUInt32("MaturityDate", info->MaturityDate, 1);
	if(info->AllowSettlDate)
		PrintUInt32("SettlDate", info->SettlDate, 1);
	if(info->AllowSettleType)
		PrintString("SettleType", info->SettleType, info->SettleTypeLength, 1);
	if(info->AllowOrigIssueAmt)
		PrintDecimal("OrigIssueAmt", &(info->OrigIssueAmt), 1);
	if(info->AllowCouponPaymentDate)
		PrintUInt32("CouponPaymentDate", info->CouponPaymentDate, 1);
	if(info->AllowCouponRate)
		PrintDecimal("CouponRate", &(info->CouponRate), 1);
	if(info->AllowSettlFixingDate)
		PrintUInt32("SettlFixingDate", info->SettlFixingDate, 1);
	if(info->AllowDividendNetPx)
		PrintDecimal("DividendNetPx", &(info->DividendNetPx), 1);
	if(info->AllowSecurityDesc)
		PrintByteVector("SecurityDesc", info->SecurityDesc, info->SecurityDescLength, 1);
	if(info->AllowEncodedSecurityDesc)
		PrintByteVector("EncodedSecurityDesc", info->EncodedSecurityDesc, info->EncodedSecurityDescLength, 1);
	if(info->AllowQuoteText)
		PrintByteVector("QuoteText", info->QuoteText, info->QuoteTextLength, 1);
	if(info->AllowGroupInstrAttrib)
		PrintInt32("GroupInstrAttribCount", info->GroupInstrAttribCount, 1);

		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = info->GroupInstrAttrib[i];
			PrintItemBegin("item", i, 1);
			PrintInt32("InstrAttribType", giaItemInfo->InstrAttribType, 2);
			if(giaItemInfo->AllowInstrAttribValue)
				PrintByteVector("InstrAttribValue", giaItemInfo->InstrAttribValue, giaItemInfo->InstrAttribValueLength, 2);
			PrintItemEnd(1);
		}

	if(info->AllowCurrency)
		PrintString("Currency", info->Currency, info->CurrencyLength, 1);
	if(info->AllowMarketSegmentGrp)
		PrintInt32("MarketSegmentGrpCount", info->MarketSegmentGrpCount, 1);

		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = info->MarketSegmentGrp[i];
			PrintItemBegin("item", i, 1);
			if(msgItemInfo->AllowRoundLot)
				PrintDecimal("RoundLot", &(msgItemInfo->RoundLot), 2);
			if(msgItemInfo->AllowTradingSessionRulesGrp)
				PrintInt32("TradingSessionRulesGrpCount", msgItemInfo->TradingSessionRulesGrpCount, 2);

				FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

				for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
					tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[i];
					PrintItemBegin("item", i, 2);
					PrintString("TradingSessionID", tsrgItemInfo->TradingSessionID, tsrgItemInfo->TradingSessionIDLength, 3);
					if(tsrgItemInfo->AllowTradingSessionSubID)
						PrintString("TradingSessionSubID", tsrgItemInfo->TradingSessionSubID, tsrgItemInfo->TradingSessionSubIDLength, 3);
					if(tsrgItemInfo->AllowSecurityTradingStatus)
						PrintInt32("SecurityTradingStatus", tsrgItemInfo->SecurityTradingStatus, 3);
					if(tsrgItemInfo->AllowOrderNote)
						PrintInt32("OrderNote", tsrgItemInfo->OrderNote, 3);
					PrintItemEnd(2);
				}

			PrintItemEnd(1);
		}

	if(info->AllowSettlCurrency)
		PrintString("SettlCurrency", info->SettlCurrency, info->SettlCurrencyLength, 1);
	if(info->AllowPriceType)
		PrintInt32("PriceType", info->PriceType, 1);
	if(info->AllowStateSecurityID)
		PrintString("StateSecurityID", info->StateSecurityID, info->StateSecurityIDLength, 1);
	if(info->AllowEncodedShortSecurityDesc)
		PrintByteVector("EncodedShortSecurityDesc", info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength, 1);
	if(info->AllowMarketCode)
		PrintByteVector("MarketCode", info->MarketCode, info->MarketCodeLength, 1);
	if(info->AllowMinPriceIncrement)
		PrintDecimal("MinPriceIncrement", &(info->MinPriceIncrement), 1);
	if(info->AllowMktShareLimit)
		PrintDecimal("MktShareLimit", &(info->MktShareLimit), 1);
	if(info->AllowMktShareThreshold)
		PrintDecimal("MktShareThreshold", &(info->MktShareThreshold), 1);
	if(info->AllowMaxOrdersVolume)
		PrintDecimal("MaxOrdersVolume", &(info->MaxOrdersVolume), 1);
	if(info->AllowPriceMvmLimit)
		PrintDecimal("PriceMvmLimit", &(info->PriceMvmLimit), 1);
	if(info->AllowFaceValue)
		PrintDecimal("FaceValue", &(info->FaceValue), 1);
	if(info->AllowBaseSwapPx)
		PrintDecimal("BaseSwapPx", &(info->BaseSwapPx), 1);
	if(info->AllowRepoToPx)
		PrintDecimal("RepoToPx", &(info->RepoToPx), 1);
	if(info->AllowBuyBackPx)
		PrintDecimal("BuyBackPx", &(info->BuyBackPx), 1);
	if(info->AllowBuyBackDate)
		PrintUInt32("BuyBackDate", info->BuyBackDate, 1);
	if(info->AllowNoSharesIssued)
		PrintDecimal("NoSharesIssued", &(info->NoSharesIssued), 1);
	if(info->AllowHighLimit)
		PrintDecimal("HighLimit", &(info->HighLimit), 1);
	if(info->AllowLowLimit)
		PrintDecimal("LowLimit", &(info->LowLimit), 1);
	if(info->AllowNumOfDaysToMaturity)
		PrintInt32("NumOfDaysToMaturity", info->NumOfDaysToMaturity, 1);
	printf("}\n");
}
void FastProtocolManager::PrintSecurityStatus(FastSecurityStatusInfo *info) {

	printf("FastSecurityStatusInfo {\n");
	PrintInt32("TemplateId", 2106, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if(info->AllowTradingSessionID)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	if(info->AllowTradingSessionSubID)
		PrintString("TradingSessionSubID", info->TradingSessionSubID, info->TradingSessionSubIDLength, 1);
	if(info->AllowSecurityTradingStatus)
		PrintInt32("SecurityTradingStatus", info->SecurityTradingStatus, 1);
	if(info->AllowAuctionIndicator)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	printf("}\n");
}
void FastProtocolManager::PrintTradingSessionStatus(FastTradingSessionStatusInfo *info) {

	printf("FastTradingSessionStatusInfo {\n");
	PrintInt32("TemplateId", 2107, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if(info->AllowText)
		PrintString("Text", info->Text, info->TextLength, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	printf("}\n");
}
void FastProtocolManager::PrintHeartbeat(FastHeartbeatInfo *info) {

	printf("FastHeartbeatInfo {\n");
	PrintInt32("TemplateId", 2108, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	printf("}\n");
}
void FastProtocolManager::PrintXmlLogon(FastLogonInfo *info) {

	PrintXmlItemBegin("FastLogonInfo");
	PrintXmlInt32("TemplateId", 2101);
	PrintXmlString("TargetCompID", info->TargetCompID, info->TargetCompIDLength);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("HeartBtInt", info->HeartBtInt);
	if(info->AllowUsername)
		PrintXmlString("Username", info->Username, info->UsernameLength);
	if(info->AllowPassword)
		PrintXmlString("Password", info->Password, info->PasswordLength);
	PrintXmlString("DefaultApplVerID", info->DefaultApplVerID, info->DefaultApplVerIDLength);
	PrintXmlItemEnd("FastLogonInfo");
}
void FastProtocolManager::PrintXmlLogout(FastLogoutInfo *info) {

	PrintXmlItemBegin("FastLogoutInfo");
	PrintXmlInt32("TemplateId", 2102);
	PrintXmlString("TargetCompID", info->TargetCompID, info->TargetCompIDLength);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowText)
		PrintXmlString("Text", info->Text, info->TextLength);
	PrintXmlItemEnd("FastLogoutInfo");
}
void FastProtocolManager::PrintXmlGeneric(FastGenericInfo *info) {

	PrintXmlItemBegin("FastGenericInfo");
	PrintXmlInt32("TemplateId", 2103);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if(info->AllowAuctionIndicator)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	if(info->AllowNetChgPrevDay)
		PrintXmlDecimal("NetChgPrevDay", &(info->NetChgPrevDay));
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if(gmdeItemInfo->AllowOrdType)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		if(gmdeItemInfo->AllowStartTime)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if(gmdeItemInfo->AllowBidMarketSize)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if(gmdeItemInfo->AllowAskMarketSize)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowTotalVolume)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowSumQtyOfBest)
			PrintXmlInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest);
		if(gmdeItemInfo->AllowOrderSide)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if(gmdeItemInfo->AllowMinCurrPx)
			PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		if(gmdeItemInfo->AllowMinCurrPxChgTime)
			PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		if(gmdeItemInfo->AllowVolumeIndicator)
			PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		if(gmdeItemInfo->AllowPrice)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if(gmdeItemInfo->AllowPriceType)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if(gmdeItemInfo->AllowNominalValue)
			PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		if(gmdeItemInfo->AllowRepoToPx)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if(gmdeItemInfo->AllowDealNumber)
			PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		if(gmdeItemInfo->AllowCXFlag)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastGenericInfo");
}
void FastProtocolManager::PrintXmlIncrementalGeneric(FastIncrementalGenericInfo *info) {

	PrintXmlItemBegin("FastIncrementalGenericInfo");
	PrintXmlInt32("TemplateId", 2104);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		if(gmdeItemInfo->AllowStartTime)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if(gmdeItemInfo->AllowOrdType)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if(gmdeItemInfo->AllowNetChgPrevDay)
			PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if(gmdeItemInfo->AllowBidMarketSize)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if(gmdeItemInfo->AllowAskMarketSize)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowTotalVolume)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if(gmdeItemInfo->AllowSumQtyOfBest)
			PrintXmlInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest);
		if(gmdeItemInfo->AllowOrderSide)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if(gmdeItemInfo->AllowMinCurrPx)
			PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		if(gmdeItemInfo->AllowMinCurrPxChgTime)
			PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		if(gmdeItemInfo->AllowVolumeIndicator)
			PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		if(gmdeItemInfo->AllowPrice)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if(gmdeItemInfo->AllowPriceType)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if(gmdeItemInfo->AllowNominalValue)
			PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		if(gmdeItemInfo->AllowRepoToPx)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if(gmdeItemInfo->AllowDealNumber)
			PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		if(gmdeItemInfo->AllowCXFlag)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalGenericInfo");
}
void FastProtocolManager::PrintXmlOLSFOND(FastOLSFONDInfo *info) {

	PrintXmlItemBegin("FastOLSFONDInfo");
	PrintXmlInt32("TemplateId", 2410);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if(info->AllowAuctionIndicator)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowDealNumber)
			PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowOrderStatus)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if(gmdeItemInfo->AllowOrdType)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if(gmdeItemInfo->AllowTotalVolume)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastOLSFONDInfo");
}
void FastProtocolManager::PrintXmlOLSCURR(FastOLSCURRInfo *info) {

	PrintXmlItemBegin("FastOLSCURRInfo");
	PrintXmlInt32("TemplateId", 3500);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowDealNumber)
			PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastOLSCURRInfo");
}
void FastProtocolManager::PrintXmlTLSFOND(FastTLSFONDInfo *info) {

	PrintXmlItemBegin("FastTLSFONDInfo");
	PrintXmlInt32("TemplateId", 2411);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if(info->AllowAuctionIndicator)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowOrderSide)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowPrice)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if(gmdeItemInfo->AllowPriceType)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastTLSFONDInfo");
}
void FastProtocolManager::PrintXmlTLSCURR(FastTLSCURRInfo *info) {

	PrintXmlItemBegin("FastTLSCURRInfo");
	PrintXmlInt32("TemplateId", 3501);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowOrderSide)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowPrice)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if(gmdeItemInfo->AllowPriceType)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastTLSCURRInfo");
}
void FastProtocolManager::PrintXmlOBSFOND(FastOBSFONDInfo *info) {

	PrintXmlItemBegin("FastOBSFONDInfo");
	PrintXmlInt32("TemplateId", 2412);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if(info->AllowAuctionIndicator)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOBSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		if(gmdeItemInfo->AllowNominalValue)
			PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastOBSFONDInfo");
}
void FastProtocolManager::PrintXmlOBSCURR(FastOBSCURRInfo *info) {

	PrintXmlItemBegin("FastOBSCURRInfo");
	PrintXmlInt32("TemplateId", 3502);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if(info->AllowLastMsgSeqNumProcessed)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if(info->AllowTradSesStatus)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowLastFragment)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if(info->AllowRouteFirst)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if(info->AllowMDSecurityTradingStatus)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOBSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastOBSCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalMSRFONDInfo");
	PrintXmlInt32("TemplateId", 2423);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowStartTime)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if(gmdeItemInfo->AllowNetChgPrevDay)
			PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if(gmdeItemInfo->AllowBidMarketSize)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if(gmdeItemInfo->AllowAskMarketSize)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if(gmdeItemInfo->AllowMinCurrPx)
			PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		if(gmdeItemInfo->AllowMinCurrPxChgTime)
			PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		if(gmdeItemInfo->AllowVolumeIndicator)
			PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowCXFlag)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalMSRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalMSRCURRInfo");
	PrintXmlInt32("TemplateId", 3513);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowQuoteCondition)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if(gmdeItemInfo->AllowTradeCondition)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if(gmdeItemInfo->AllowOpenCloseSettlFlag)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if(gmdeItemInfo->AllowNetChgPrevDay)
			PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		if(gmdeItemInfo->AllowChgFromWAPrice)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if(gmdeItemInfo->AllowChgOpenInterest)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if(gmdeItemInfo->AllowTotalNumOfTrades)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowOfferNbOr)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if(gmdeItemInfo->AllowBidNbOr)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if(gmdeItemInfo->AllowChgFromSettlmnt)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowCXFlag)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalMSRCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalOLRFONDInfo");
	PrintXmlInt32("TemplateId", 2420);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowDealNumber)
			PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowOrderStatus)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if(gmdeItemInfo->AllowOrdType)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if(gmdeItemInfo->AllowTotalVolume)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalOLRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalOLRCURRInfo");
	PrintXmlInt32("TemplateId", 3510);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowDealNumber)
			PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		if(gmdeItemInfo->AllowOrderStatus)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalOLRCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalOBRFOND(FastIncrementalOBRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalOBRFONDInfo");
	PrintXmlInt32("TemplateId", 2422);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOBSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowEffectiveTime)
			PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		if(gmdeItemInfo->AllowNominalValue)
			PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalOBRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalOBRCURR(FastIncrementalOBRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalOBRCURRInfo");
	PrintXmlInt32("TemplateId", 3512);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOBSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if(gmdeItemInfo->AllowMDEntryType)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalOBRCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalTLRFOND(FastIncrementalTLRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalTLRFONDInfo");
	PrintXmlInt32("TemplateId", 2421);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowOrderSide)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowAccruedInterestAmt)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowYield)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowPrice)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if(gmdeItemInfo->AllowPriceType)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalTLRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalTLRCURR(FastIncrementalTLRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalTLRCURRInfo");
	PrintXmlInt32("TemplateId", 3511);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if(gmdeItemInfo->AllowMDUpdateAction)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if(gmdeItemInfo->AllowMDEntryID)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if(gmdeItemInfo->AllowSymbol)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if(gmdeItemInfo->AllowRptSeq)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if(gmdeItemInfo->AllowMDEntryDate)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if(gmdeItemInfo->AllowMDEntryTime)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if(gmdeItemInfo->AllowOrigTime)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if(gmdeItemInfo->AllowOrderSide)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if(gmdeItemInfo->AllowMDEntryPx)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if(gmdeItemInfo->AllowMDEntrySize)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if(gmdeItemInfo->AllowTradeValue)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if(gmdeItemInfo->AllowSettlDate)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if(gmdeItemInfo->AllowSettleType)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if(gmdeItemInfo->AllowPrice)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if(gmdeItemInfo->AllowPriceType)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if(gmdeItemInfo->AllowRepoToPx)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if(gmdeItemInfo->AllowBuyBackPx)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if(gmdeItemInfo->AllowBuyBackDate)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if(gmdeItemInfo->AllowTradingSessionID)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if(gmdeItemInfo->AllowTradingSessionSubID)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalTLRCURRInfo");
}
void FastProtocolManager::PrintXmlSecurityDefinition(FastSecurityDefinitionInfo *info) {

	PrintXmlItemBegin("FastSecurityDefinitionInfo");
	PrintXmlInt32("TemplateId", 2115);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlString("MessageEncoding", info->MessageEncoding, info->MessageEncodingLength);
	if(info->AllowTotNumReports)
		PrintXmlInt32("TotNumReports", info->TotNumReports);
	if(info->AllowSymbol)
		PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowSecurityID)
		PrintXmlByteVector("SecurityID", info->SecurityID, info->SecurityIDLength);
	if(info->AllowSecurityIDSource)
		PrintXmlByteVector("SecurityIDSource", info->SecurityIDSource, info->SecurityIDSourceLength);
	if(info->AllowProduct)
		PrintXmlInt32("Product", info->Product);
	if(info->AllowCFICode)
		PrintXmlByteVector("CFICode", info->CFICode, info->CFICodeLength);
	if(info->AllowSecurityType)
		PrintXmlByteVector("SecurityType", info->SecurityType, info->SecurityTypeLength);
	if(info->AllowMaturityDate)
		PrintXmlUInt32("MaturityDate", info->MaturityDate);
	if(info->AllowSettlDate)
		PrintXmlUInt32("SettlDate", info->SettlDate);
	if(info->AllowSettleType)
		PrintXmlString("SettleType", info->SettleType, info->SettleTypeLength);
	if(info->AllowOrigIssueAmt)
		PrintXmlDecimal("OrigIssueAmt", &(info->OrigIssueAmt));
	if(info->AllowCouponPaymentDate)
		PrintXmlUInt32("CouponPaymentDate", info->CouponPaymentDate);
	if(info->AllowCouponRate)
		PrintXmlDecimal("CouponRate", &(info->CouponRate));
	if(info->AllowSettlFixingDate)
		PrintXmlUInt32("SettlFixingDate", info->SettlFixingDate);
	if(info->AllowDividendNetPx)
		PrintXmlDecimal("DividendNetPx", &(info->DividendNetPx));
	if(info->AllowSecurityDesc)
		PrintXmlByteVector("SecurityDesc", info->SecurityDesc, info->SecurityDescLength);
	if(info->AllowEncodedSecurityDesc)
		PrintXmlByteVector("EncodedSecurityDesc", info->EncodedSecurityDesc, info->EncodedSecurityDescLength);
	if(info->AllowQuoteText)
		PrintXmlByteVector("QuoteText", info->QuoteText, info->QuoteTextLength);
	if(info->AllowGroupInstrAttrib)
		PrintXmlInt32("GroupInstrAttribCount", info->GroupInstrAttribCount);

		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = info->GroupInstrAttrib[i];
			PrintXmlItemBegin("item", i);
			PrintXmlInt32("InstrAttribType", giaItemInfo->InstrAttribType);
			if(giaItemInfo->AllowInstrAttribValue)
				PrintXmlByteVector("InstrAttribValue", giaItemInfo->InstrAttribValue, giaItemInfo->InstrAttribValueLength);
			PrintXmlItemEnd("item", i);
		}

	if(info->AllowCurrency)
		PrintXmlString("Currency", info->Currency, info->CurrencyLength);
	if(info->AllowMarketSegmentGrp)
		PrintXmlInt32("MarketSegmentGrpCount", info->MarketSegmentGrpCount);

		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = info->MarketSegmentGrp[i];
			PrintXmlItemBegin("item", i);
			if(msgItemInfo->AllowRoundLot)
				PrintXmlDecimal("RoundLot", &(msgItemInfo->RoundLot));
			if(msgItemInfo->AllowTradingSessionRulesGrp)
				PrintXmlInt32("TradingSessionRulesGrpCount", msgItemInfo->TradingSessionRulesGrpCount);

				FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

				for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
					tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[i];
					PrintXmlItemBegin("item", i);
					PrintXmlString("TradingSessionID", tsrgItemInfo->TradingSessionID, tsrgItemInfo->TradingSessionIDLength);
					if(tsrgItemInfo->AllowTradingSessionSubID)
						PrintXmlString("TradingSessionSubID", tsrgItemInfo->TradingSessionSubID, tsrgItemInfo->TradingSessionSubIDLength);
					if(tsrgItemInfo->AllowSecurityTradingStatus)
						PrintXmlInt32("SecurityTradingStatus", tsrgItemInfo->SecurityTradingStatus);
					if(tsrgItemInfo->AllowOrderNote)
						PrintXmlInt32("OrderNote", tsrgItemInfo->OrderNote);
					PrintXmlItemEnd("item", i);
				}

			PrintXmlItemEnd("item", i);
		}

	if(info->AllowSettlCurrency)
		PrintXmlString("SettlCurrency", info->SettlCurrency, info->SettlCurrencyLength);
	if(info->AllowPriceType)
		PrintXmlInt32("PriceType", info->PriceType);
	if(info->AllowStateSecurityID)
		PrintXmlString("StateSecurityID", info->StateSecurityID, info->StateSecurityIDLength);
	if(info->AllowEncodedShortSecurityDesc)
		PrintXmlByteVector("EncodedShortSecurityDesc", info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength);
	if(info->AllowMarketCode)
		PrintXmlByteVector("MarketCode", info->MarketCode, info->MarketCodeLength);
	if(info->AllowMinPriceIncrement)
		PrintXmlDecimal("MinPriceIncrement", &(info->MinPriceIncrement));
	if(info->AllowMktShareLimit)
		PrintXmlDecimal("MktShareLimit", &(info->MktShareLimit));
	if(info->AllowMktShareThreshold)
		PrintXmlDecimal("MktShareThreshold", &(info->MktShareThreshold));
	if(info->AllowMaxOrdersVolume)
		PrintXmlDecimal("MaxOrdersVolume", &(info->MaxOrdersVolume));
	if(info->AllowPriceMvmLimit)
		PrintXmlDecimal("PriceMvmLimit", &(info->PriceMvmLimit));
	if(info->AllowFaceValue)
		PrintXmlDecimal("FaceValue", &(info->FaceValue));
	if(info->AllowBaseSwapPx)
		PrintXmlDecimal("BaseSwapPx", &(info->BaseSwapPx));
	if(info->AllowRepoToPx)
		PrintXmlDecimal("RepoToPx", &(info->RepoToPx));
	if(info->AllowBuyBackPx)
		PrintXmlDecimal("BuyBackPx", &(info->BuyBackPx));
	if(info->AllowBuyBackDate)
		PrintXmlUInt32("BuyBackDate", info->BuyBackDate);
	if(info->AllowNoSharesIssued)
		PrintXmlDecimal("NoSharesIssued", &(info->NoSharesIssued));
	if(info->AllowHighLimit)
		PrintXmlDecimal("HighLimit", &(info->HighLimit));
	if(info->AllowLowLimit)
		PrintXmlDecimal("LowLimit", &(info->LowLimit));
	if(info->AllowNumOfDaysToMaturity)
		PrintXmlInt32("NumOfDaysToMaturity", info->NumOfDaysToMaturity);
	PrintXmlItemEnd("FastSecurityDefinitionInfo");
}
void FastProtocolManager::PrintXmlSecurityStatus(FastSecurityStatusInfo *info) {

	PrintXmlItemBegin("FastSecurityStatusInfo");
	PrintXmlInt32("TemplateId", 2106);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if(info->AllowTradingSessionID)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	if(info->AllowTradingSessionSubID)
		PrintXmlString("TradingSessionSubID", info->TradingSessionSubID, info->TradingSessionSubIDLength);
	if(info->AllowSecurityTradingStatus)
		PrintXmlInt32("SecurityTradingStatus", info->SecurityTradingStatus);
	if(info->AllowAuctionIndicator)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlItemEnd("FastSecurityStatusInfo");
}
void FastProtocolManager::PrintXmlTradingSessionStatus(FastTradingSessionStatusInfo *info) {

	PrintXmlItemBegin("FastTradingSessionStatusInfo");
	PrintXmlInt32("TemplateId", 2107);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if(info->AllowText)
		PrintXmlString("Text", info->Text, info->TextLength);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlItemEnd("FastTradingSessionStatusInfo");
}
void FastProtocolManager::PrintXmlHeartbeat(FastHeartbeatInfo *info) {

	PrintXmlItemBegin("FastHeartbeatInfo");
	PrintXmlInt32("TemplateId", 2108);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlItemEnd("FastHeartbeatInfo");
}
#pragma endregion

#pragma region Encode_Methods_Definition_GeneratedCode
void FastProtocolManager::EncodeLogonInfo(FastLogonInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2101);
	WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteInt32_Mandatory(info->HeartBtInt);
	if(!info->AllowUsername)
		this->WriteNull();
	else
		WriteString_Optional(info->Username, info->UsernameLength);
	if(!info->AllowPassword)
		this->WriteNull();
	else
		WriteString_Optional(info->Password, info->PasswordLength);
	WriteString_Mandatory(info->DefaultApplVerID, info->DefaultApplVerIDLength);
}
void FastProtocolManager::EncodeLogoutInfo(FastLogoutInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2102);
	WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowText)
		this->WriteNull();
	else
		WriteString_Optional(info->Text, info->TextLength);
}
void FastProtocolManager::EncodeGenericInfo(FastGenericInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2103);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if(!info->AllowAuctionIndicator)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	if(!info->AllowNetChgPrevDay)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->NetChgPrevDay));
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowQuoteCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(!(*gmdeItemInfo)->AllowTradeCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(!(*gmdeItemInfo)->AllowOpenCloseSettlFlag)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(!(*gmdeItemInfo)->AllowOrdType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
		if(!(*gmdeItemInfo)->AllowEffectiveTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->EffectiveTime);
		if(!(*gmdeItemInfo)->AllowStartTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(!(*gmdeItemInfo)->AllowAccruedInterestAmt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(!(*gmdeItemInfo)->AllowChgFromWAPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(!(*gmdeItemInfo)->AllowChgOpenInterest)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(!(*gmdeItemInfo)->AllowBidMarketSize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(!(*gmdeItemInfo)->AllowAskMarketSize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(!(*gmdeItemInfo)->AllowTotalNumOfTrades)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowTotalVolume)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
		if(!(*gmdeItemInfo)->AllowOfferNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(!(*gmdeItemInfo)->AllowBidNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(!(*gmdeItemInfo)->AllowChgFromSettlmnt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(!(*gmdeItemInfo)->AllowSumQtyOfBest)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->SumQtyOfBest);
		if(!(*gmdeItemInfo)->AllowOrderSide)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(!(*gmdeItemInfo)->AllowOrderStatus)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(!(*gmdeItemInfo)->AllowMinCurrPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MinCurrPx));
		if(!(*gmdeItemInfo)->AllowMinCurrPxChgTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MinCurrPxChgTime);
		if(!(*gmdeItemInfo)->AllowVolumeIndicator)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->VolumeIndicator);
		if(!(*gmdeItemInfo)->AllowPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(!(*gmdeItemInfo)->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(!(*gmdeItemInfo)->AllowNominalValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NominalValue));
		if(!(*gmdeItemInfo)->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(!(*gmdeItemInfo)->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(!(*gmdeItemInfo)->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->DealNumberPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowDealNumber)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->DealNumber, (*gmdeItemInfo)->DealNumberLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->CXFlagPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowCXFlag)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
			}
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalGenericInfo(FastIncrementalGenericInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2104);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowEffectiveTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->EffectiveTime);
		if(!(*gmdeItemInfo)->AllowStartTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowQuoteCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(!(*gmdeItemInfo)->AllowTradeCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(!(*gmdeItemInfo)->AllowOpenCloseSettlFlag)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(!(*gmdeItemInfo)->AllowOrdType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
		if(!(*gmdeItemInfo)->AllowNetChgPrevDay)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NetChgPrevDay));
		if(!(*gmdeItemInfo)->AllowAccruedInterestAmt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(!(*gmdeItemInfo)->AllowChgFromWAPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(!(*gmdeItemInfo)->AllowChgOpenInterest)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(!(*gmdeItemInfo)->AllowBidMarketSize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(!(*gmdeItemInfo)->AllowAskMarketSize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(!(*gmdeItemInfo)->AllowTotalNumOfTrades)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowTotalVolume)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
		if(!(*gmdeItemInfo)->AllowOfferNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(!(*gmdeItemInfo)->AllowBidNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(!(*gmdeItemInfo)->AllowChgFromSettlmnt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(!(*gmdeItemInfo)->AllowSumQtyOfBest)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->SumQtyOfBest);
		if(!(*gmdeItemInfo)->AllowOrderSide)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(!(*gmdeItemInfo)->AllowOrderStatus)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(!(*gmdeItemInfo)->AllowMinCurrPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MinCurrPx));
		if(!(*gmdeItemInfo)->AllowMinCurrPxChgTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MinCurrPxChgTime);
		if(!(*gmdeItemInfo)->AllowVolumeIndicator)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->VolumeIndicator);
		if(!(*gmdeItemInfo)->AllowPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(!(*gmdeItemInfo)->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(!(*gmdeItemInfo)->AllowNominalValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NominalValue));
		if(!(*gmdeItemInfo)->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(!(*gmdeItemInfo)->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(!(*gmdeItemInfo)->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->DealNumberPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowDealNumber)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->DealNumber, (*gmdeItemInfo)->DealNumberLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->CXFlagPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowCXFlag)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
			}
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeOLSFONDInfo(FastOLSFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2410);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if(!info->AllowAuctionIndicator)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->DealNumberPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowDealNumber)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->DealNumber, (*gmdeItemInfo)->DealNumberLength);
			}
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowOrderStatus)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(!(*gmdeItemInfo)->AllowOrdType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
		if(!(*gmdeItemInfo)->AllowTotalVolume)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeOLSCURRInfo(FastOLSCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3500);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->DealNumberPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowDealNumber)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->DealNumber, (*gmdeItemInfo)->DealNumberLength);
			}
		if(!(*gmdeItemInfo)->AllowOrderStatus)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeTLSFONDInfo(FastTLSFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2411);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if(!info->AllowAuctionIndicator)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowOrderSide)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowAccruedInterestAmt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(!(*gmdeItemInfo)->AllowPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(!(*gmdeItemInfo)->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(!(*gmdeItemInfo)->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(!(*gmdeItemInfo)->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(!(*gmdeItemInfo)->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeTLSCURRInfo(FastTLSCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3501);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowOrderSide)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(!(*gmdeItemInfo)->AllowPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(!(*gmdeItemInfo)->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(!(*gmdeItemInfo)->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(!(*gmdeItemInfo)->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(!(*gmdeItemInfo)->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeOBSFONDInfo(FastOBSFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2412);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if(!info->AllowAuctionIndicator)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOBSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowEffectiveTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->EffectiveTime);
		if(!(*gmdeItemInfo)->AllowNominalValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NominalValue));
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeOBSCURRInfo(FastOBSCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3502);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowLastMsgSeqNumProcessed)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if(!info->AllowTradSesStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowLastFragment)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if(!info->AllowRouteFirst)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if(!info->AllowMDSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOBSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalMSRFONDInfo(FastIncrementalMSRFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2423);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowStartTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(!(*gmdeItemInfo)->AllowQuoteCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(!(*gmdeItemInfo)->AllowTradeCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(!(*gmdeItemInfo)->AllowOpenCloseSettlFlag)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(!(*gmdeItemInfo)->AllowNetChgPrevDay)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NetChgPrevDay));
		if(!(*gmdeItemInfo)->AllowAccruedInterestAmt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(!(*gmdeItemInfo)->AllowChgFromWAPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(!(*gmdeItemInfo)->AllowChgOpenInterest)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(!(*gmdeItemInfo)->AllowBidMarketSize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(!(*gmdeItemInfo)->AllowAskMarketSize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(!(*gmdeItemInfo)->AllowTotalNumOfTrades)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowOfferNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(!(*gmdeItemInfo)->AllowBidNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(!(*gmdeItemInfo)->AllowChgFromSettlmnt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(!(*gmdeItemInfo)->AllowMinCurrPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MinCurrPx));
		if(!(*gmdeItemInfo)->AllowMinCurrPxChgTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MinCurrPxChgTime);
		if(!(*gmdeItemInfo)->AllowVolumeIndicator)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->VolumeIndicator);
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->CXFlagPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowCXFlag)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
			}
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalMSRCURRInfo(FastIncrementalMSRCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3513);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowQuoteCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(!(*gmdeItemInfo)->AllowTradeCondition)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(!(*gmdeItemInfo)->AllowOpenCloseSettlFlag)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(!(*gmdeItemInfo)->AllowNetChgPrevDay)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NetChgPrevDay));
		if(!(*gmdeItemInfo)->AllowChgFromWAPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(!(*gmdeItemInfo)->AllowChgOpenInterest)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(!(*gmdeItemInfo)->AllowTotalNumOfTrades)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowOfferNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(!(*gmdeItemInfo)->AllowBidNbOr)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(!(*gmdeItemInfo)->AllowChgFromSettlmnt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->CXFlagPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowCXFlag)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
			}
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalOLRFONDInfo(FastIncrementalOLRFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2420);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->DealNumberPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowDealNumber)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->DealNumber, (*gmdeItemInfo)->DealNumberLength);
			}
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowOrderStatus)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(!(*gmdeItemInfo)->AllowOrdType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
		if(!(*gmdeItemInfo)->AllowTotalVolume)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalOLRCURRInfo(FastIncrementalOLRCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3510);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
	WriteUInt32_Mandatory(0); // Presence Map hack

		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, (*gmdeItemInfo)->DealNumberPresenceIndex)) {
			if(!(*gmdeItemInfo)->AllowDealNumber)
				this->WriteNull();
			else
				WriteString_Optional((*gmdeItemInfo)->DealNumber, (*gmdeItemInfo)->DealNumberLength);
			}
		if(!(*gmdeItemInfo)->AllowOrderStatus)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalOBRFONDInfo(FastIncrementalOBRFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2422);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOBSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowEffectiveTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->EffectiveTime);
		if(!(*gmdeItemInfo)->AllowNominalValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NominalValue));
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalOBRCURRInfo(FastIncrementalOBRCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3512);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOBSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(!(*gmdeItemInfo)->AllowMDEntryType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalTLRFONDInfo(FastIncrementalTLRFONDInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2421);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowOrderSide)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowAccruedInterestAmt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowYield)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(!(*gmdeItemInfo)->AllowPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(!(*gmdeItemInfo)->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(!(*gmdeItemInfo)->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(!(*gmdeItemInfo)->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(!(*gmdeItemInfo)->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalTLRCURRInfo(FastIncrementalTLRCURRInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(3511);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(!(*gmdeItemInfo)->AllowMDUpdateAction)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(!(*gmdeItemInfo)->AllowMDEntryID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(!(*gmdeItemInfo)->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(!(*gmdeItemInfo)->AllowRptSeq)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(!(*gmdeItemInfo)->AllowMDEntryDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(!(*gmdeItemInfo)->AllowMDEntryTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(!(*gmdeItemInfo)->AllowOrigTime)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(!(*gmdeItemInfo)->AllowOrderSide)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(!(*gmdeItemInfo)->AllowMDEntryPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(!(*gmdeItemInfo)->AllowMDEntrySize)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(!(*gmdeItemInfo)->AllowTradeValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(!(*gmdeItemInfo)->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(!(*gmdeItemInfo)->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(!(*gmdeItemInfo)->AllowPrice)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(!(*gmdeItemInfo)->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(!(*gmdeItemInfo)->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(!(*gmdeItemInfo)->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(!(*gmdeItemInfo)->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(!(*gmdeItemInfo)->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(!(*gmdeItemInfo)->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeSecurityDefinitionInfo(FastSecurityDefinitionInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2115);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if(!info->AllowTotNumReports)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TotNumReports);
	if(!info->AllowSymbol)
		this->WriteNull();
	else
		WriteString_Optional(info->Symbol, info->SymbolLength);
	if(!info->AllowSecurityID)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityID, info->SecurityIDLength);
	if(!info->AllowSecurityIDSource)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityIDSource, info->SecurityIDSourceLength);
	if(!info->AllowProduct)
		this->WriteNull();
	else
		WriteInt32_Optional(info->Product);
	if(!info->AllowCFICode)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->CFICode, info->CFICodeLength);
	if(!info->AllowSecurityType)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityType, info->SecurityTypeLength);
	if(!info->AllowMaturityDate)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->MaturityDate);
	if(!info->AllowSettlDate)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->SettlDate);
	if(!info->AllowSettleType)
		this->WriteNull();
	else
		WriteString_Optional(info->SettleType, info->SettleTypeLength);
	if(!info->AllowOrigIssueAmt)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->OrigIssueAmt));
	if(!info->AllowCouponPaymentDate)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->CouponPaymentDate);
	if(!info->AllowCouponRate)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->CouponRate));
	if(!info->AllowSettlFixingDate)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->SettlFixingDate);
	if(!info->AllowDividendNetPx)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->DividendNetPx));
	if(!info->AllowSecurityDesc)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityDesc, info->SecurityDescLength);
	if(!info->AllowEncodedSecurityDesc)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->EncodedSecurityDesc, info->EncodedSecurityDescLength);
	if(!info->AllowQuoteText)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->QuoteText, info->QuoteTextLength);
	if(!info->AllowGroupInstrAttrib)
		this->WriteNull();
	else {
		WriteUInt32_Mandatory(info->GroupInstrAttribCount);
		FastSecurityDefinitionGroupInstrAttribItemInfo **giaItemInfo = info->GroupInstrAttrib;
		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			WriteInt32_Mandatory((*giaItemInfo)->InstrAttribType);
			if(!(*giaItemInfo)->AllowInstrAttribValue)
				this->WriteNull();
			else
				WriteByteVector_Optional((*giaItemInfo)->InstrAttribValue, (*giaItemInfo)->InstrAttribValueLength);
			giaItemInfo++;
		}
	}
	if(!info->AllowCurrency)
		this->WriteNull();
	else
		WriteString_Optional(info->Currency, info->CurrencyLength);
	if(!info->AllowMarketSegmentGrp)
		this->WriteNull();
	else {
		WriteUInt32_Mandatory(info->MarketSegmentGrpCount);
		FastSecurityDefinitionMarketSegmentGrpItemInfo **msgItemInfo = info->MarketSegmentGrp;
		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			if(!(*msgItemInfo)->AllowRoundLot)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*msgItemInfo)->RoundLot));
			if(!(*msgItemInfo)->AllowTradingSessionRulesGrp)
				this->WriteNull();
			else {
				WriteUInt32_Mandatory((*msgItemInfo)->TradingSessionRulesGrpCount);
				FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **tsrgItemInfo = (*msgItemInfo)->TradingSessionRulesGrp;
				for(int i = 0; i < (*msgItemInfo)->TradingSessionRulesGrpCount; i++) {
					WriteString_Mandatory((*tsrgItemInfo)->TradingSessionID, (*tsrgItemInfo)->TradingSessionIDLength);
					if(!(*tsrgItemInfo)->AllowTradingSessionSubID)
						this->WriteNull();
					else
						WriteString_Optional((*tsrgItemInfo)->TradingSessionSubID, (*tsrgItemInfo)->TradingSessionSubIDLength);
					if(!(*tsrgItemInfo)->AllowSecurityTradingStatus)
						this->WriteNull();
					else
						WriteInt32_Optional((*tsrgItemInfo)->SecurityTradingStatus);
					if(!(*tsrgItemInfo)->AllowOrderNote)
						this->WriteNull();
					else
						WriteInt32_Optional((*tsrgItemInfo)->OrderNote);
					tsrgItemInfo++;
				}
			}
			msgItemInfo++;
		}
	}
	if(!info->AllowSettlCurrency)
		this->WriteNull();
	else
		WriteString_Optional(info->SettlCurrency, info->SettlCurrencyLength);
	if(!info->AllowPriceType)
		this->WriteNull();
	else
		WriteInt32_Optional(info->PriceType);
	if(!info->AllowStateSecurityID)
		this->WriteNull();
	else
		WriteString_Optional(info->StateSecurityID, info->StateSecurityIDLength);
	if(!info->AllowEncodedShortSecurityDesc)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength);
	if(!info->AllowMarketCode)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->MarketCode, info->MarketCodeLength);
	if(!info->AllowMinPriceIncrement)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MinPriceIncrement));
	if(!info->AllowMktShareLimit)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MktShareLimit));
	if(!info->AllowMktShareThreshold)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MktShareThreshold));
	if(!info->AllowMaxOrdersVolume)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MaxOrdersVolume));
	if(!info->AllowPriceMvmLimit)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->PriceMvmLimit));
	if(!info->AllowFaceValue)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->FaceValue));
	if(!info->AllowBaseSwapPx)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->BaseSwapPx));
	if(!info->AllowRepoToPx)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->RepoToPx));
	if(!info->AllowBuyBackPx)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->BuyBackPx));
	if(!info->AllowBuyBackDate)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->BuyBackDate);
	if(!info->AllowNoSharesIssued)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->NoSharesIssued));
	if(!info->AllowHighLimit)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->HighLimit));
	if(!info->AllowLowLimit)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->LowLimit));
	if(!info->AllowNumOfDaysToMaturity)
		this->WriteNull();
	else
		WriteInt32_Optional(info->NumOfDaysToMaturity);
}
void FastProtocolManager::EncodeSecurityStatusInfo(FastSecurityStatusInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2106);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if(!info->AllowTradingSessionID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	if(!info->AllowTradingSessionSubID)
		this->WriteNull();
	else
		WriteString_Optional(info->TradingSessionSubID, info->TradingSessionSubIDLength);
	if(!info->AllowSecurityTradingStatus)
		this->WriteNull();
	else
		WriteInt32_Optional(info->SecurityTradingStatus);
	if(!info->AllowAuctionIndicator)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
}
void FastProtocolManager::EncodeTradingSessionStatusInfo(FastTradingSessionStatusInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2107);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteInt32_Mandatory(info->TradSesStatus);
	if(!info->AllowText)
		this->WriteNull();
	else
		WriteString_Optional(info->Text, info->TextLength);
	WriteString_Mandatory(info->TradingSessionID, info->TradingSessionIDLength);
}
void FastProtocolManager::EncodeHeartbeatInfo(FastHeartbeatInfo* info) {
	ResetBuffer();
	WriteMsgSeqNumber(info->MsgSeqNum);
	WriteUInt32_Mandatory(0); // Presence Map hack
	WriteUInt32_Mandatory(2108);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
}
#pragma endregion
