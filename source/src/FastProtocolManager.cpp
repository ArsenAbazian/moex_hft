#include "FastProtocolManager.h"


FastProtocolManager::FastProtocolManager() {
	this->m_recvMsgSeqNo = 1;
	this->m_sendMsgSeqNo = 1;
	this->InitializeConstantStrings();
	this->InitializeDecodeMethodPointers();
	this->InitializeMessageInfo();
}


FastProtocolManager::~FastProtocolManager() {
	delete[] this->buffer;
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
	PrintString("Username", info->Username, info->UsernameLength, 1);
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
	PrintString("Text", info->Text, info->TextLength, 1);
	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshGeneric(FastMarketDataSnapshotFullRefreshGenericInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshGenericInfo {\n");
	PrintInt32("TemplateId", 2103, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintDecimal("NetChgPrevDay", &(info->NetChgPrevDay), 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest, 2);
		PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshGeneric(FastMarketDataIncrementalRefreshGenericInfo *info) {

	printf("FastMarketDataIncrementalRefreshGenericInfo {\n");
	PrintInt32("TemplateId", 2104, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		PrintInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest, 2);
		PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshOLSFOND(FastMarketDataSnapshotFullRefreshOLSFONDInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshOLSFONDInfo {\n");
	PrintInt32("TemplateId", 2410, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshOLSCURR(FastMarketDataSnapshotFullRefreshOLSCURRInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshOLSCURRInfo {\n");
	PrintInt32("TemplateId", 3500, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshTLSFOND(FastMarketDataSnapshotFullRefreshTLSFONDInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshTLSFONDInfo {\n");
	PrintInt32("TemplateId", 2411, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshTLSCURR(FastMarketDataSnapshotFullRefreshTLSCURRInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshTLSCURRInfo {\n");
	PrintInt32("TemplateId", 3501, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshOBSFOND(FastMarketDataSnapshotFullRefreshOBSFONDInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshOBSFONDInfo {\n");
	PrintInt32("TemplateId", 2412, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataSnapshotFullRefreshOBSCURR(FastMarketDataSnapshotFullRefreshOBSCURRInfo *info) {

	printf("FastMarketDataSnapshotFullRefreshOBSCURRInfo {\n");
	PrintInt32("TemplateId", 3502, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintUInt32("LastFragment", info->LastFragment, 1);
	PrintUInt32("RouteFirst", info->RouteFirst, 1);
	PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshMSRFOND(FastMarketDataIncrementalRefreshMSRFONDInfo *info) {

	printf("FastMarketDataIncrementalRefreshMSRFONDInfo {\n");
	PrintInt32("TemplateId", 2423, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshMSRCURR(FastMarketDataIncrementalRefreshMSRCURRInfo *info) {

	printf("FastMarketDataIncrementalRefreshMSRCURRInfo {\n");
	PrintInt32("TemplateId", 3513, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshOLRFOND(FastMarketDataIncrementalRefreshOLRFONDInfo *info) {

	printf("FastMarketDataIncrementalRefreshOLRFONDInfo {\n");
	PrintInt32("TemplateId", 2420, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshOLRCURR(FastMarketDataIncrementalRefreshOLRCURRInfo *info) {

	printf("FastMarketDataIncrementalRefreshOLRCURRInfo {\n");
	PrintInt32("TemplateId", 3510, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength, 2);
		PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshOBRFOND(FastMarketDataIncrementalRefreshOBRFONDInfo *info) {

	printf("FastMarketDataIncrementalRefreshOBRFONDInfo {\n");
	PrintInt32("TemplateId", 2422, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshOBRCURR(FastMarketDataIncrementalRefreshOBRCURRInfo *info) {

	printf("FastMarketDataIncrementalRefreshOBRCURRInfo {\n");
	PrintInt32("TemplateId", 3512, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshTLRFOND(FastMarketDataIncrementalRefreshTLRFONDInfo *info) {

	printf("FastMarketDataIncrementalRefreshTLRFONDInfo {\n");
	PrintInt32("TemplateId", 2421, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintMarketDataIncrementalRefreshTLRCURR(FastMarketDataIncrementalRefreshTLRCURRInfo *info) {

	printf("FastMarketDataIncrementalRefreshTLRCURRInfo {\n");
	PrintInt32("TemplateId", 3511, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
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
	PrintInt32("TotNumReports", info->TotNumReports, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintByteVector("SecurityID", info->SecurityID, info->SecurityIDLength, 1);
	PrintByteVector("SecurityIDSource", info->SecurityIDSource, info->SecurityIDSourceLength, 1);
	PrintInt32("Product", info->Product, 1);
	PrintByteVector("CFICode", info->CFICode, info->CFICodeLength, 1);
	PrintByteVector("SecurityType", info->SecurityType, info->SecurityTypeLength, 1);
	PrintUInt32("MaturityDate", info->MaturityDate, 1);
	PrintUInt32("SettlDate", info->SettlDate, 1);
	PrintString("SettleType", info->SettleType, info->SettleTypeLength, 1);
	PrintDecimal("OrigIssueAmt", &(info->OrigIssueAmt), 1);
	PrintUInt32("CouponPaymentDate", info->CouponPaymentDate, 1);
	PrintDecimal("CouponRate", &(info->CouponRate), 1);
	PrintUInt32("SettlFixingDate", info->SettlFixingDate, 1);
	PrintDecimal("DividendNetPx", &(info->DividendNetPx), 1);
	PrintByteVector("SecurityDesc", info->SecurityDesc, info->SecurityDescLength, 1);
	PrintByteVector("EncodedSecurityDesc", info->EncodedSecurityDesc, info->EncodedSecurityDescLength, 1);
	PrintByteVector("QuoteText", info->QuoteText, info->QuoteTextLength, 1);
	PrintInt32("GroupInstrAttribCount", info->GroupInstrAttribCount, 1);

	FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

	for(int i = 0; i < info->GroupInstrAttribCount; i++) {
		giaItemInfo = info->GroupInstrAttrib[i];
		PrintItemBegin("item", i, 1);
		PrintInt32("InstrAttribType", giaItemInfo->InstrAttribType, 2);
		PrintByteVector("InstrAttribValue", giaItemInfo->InstrAttribValue, giaItemInfo->InstrAttribValueLength, 2);
		PrintItemEnd(1);
	}

	PrintString("Currency", info->Currency, info->CurrencyLength, 1);
	PrintInt32("MarketSegmentGrpCount", info->MarketSegmentGrpCount, 1);

	FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

	for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
		msgItemInfo = info->MarketSegmentGrp[i];
		PrintItemBegin("item", i, 1);
		PrintDecimal("RoundLot", &(msgItemInfo->RoundLot), 2);
		PrintInt32("TradingSessionRulesGrpCount", msgItemInfo->TradingSessionRulesGrpCount, 2);

		FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

		for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
			tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[i];
			PrintItemBegin("item", i, 2);
			PrintString("TradingSessionID", tsrgItemInfo->TradingSessionID, tsrgItemInfo->TradingSessionIDLength, 3);
			PrintString("TradingSessionSubID", tsrgItemInfo->TradingSessionSubID, tsrgItemInfo->TradingSessionSubIDLength, 3);
			PrintInt32("SecurityTradingStatus", tsrgItemInfo->SecurityTradingStatus, 3);
			PrintInt32("OrderNote", tsrgItemInfo->OrderNote, 3);
			PrintItemEnd(2);
		}

		PrintItemEnd(1);
	}

	PrintString("SettlCurrency", info->SettlCurrency, info->SettlCurrencyLength, 1);
	PrintInt32("PriceType", info->PriceType, 1);
	PrintString("StateSecurityID", info->StateSecurityID, info->StateSecurityIDLength, 1);
	PrintByteVector("EncodedShortSecurityDesc", info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength, 1);
	PrintByteVector("MarketCode", info->MarketCode, info->MarketCodeLength, 1);
	PrintDecimal("MinPriceIncrement", &(info->MinPriceIncrement), 1);
	PrintDecimal("MktShareLimit", &(info->MktShareLimit), 1);
	PrintDecimal("MktShareThreshold", &(info->MktShareThreshold), 1);
	PrintDecimal("MaxOrdersVolume", &(info->MaxOrdersVolume), 1);
	PrintDecimal("PriceMvmLimit", &(info->PriceMvmLimit), 1);
	PrintDecimal("FaceValue", &(info->FaceValue), 1);
	PrintDecimal("BaseSwapPx", &(info->BaseSwapPx), 1);
	PrintDecimal("RepoToPx", &(info->RepoToPx), 1);
	PrintDecimal("BuyBackPx", &(info->BuyBackPx), 1);
	PrintUInt32("BuyBackDate", info->BuyBackDate, 1);
	PrintDecimal("NoSharesIssued", &(info->NoSharesIssued), 1);
	PrintDecimal("HighLimit", &(info->HighLimit), 1);
	PrintDecimal("LowLimit", &(info->LowLimit), 1);
	PrintInt32("NumOfDaysToMaturity", info->NumOfDaysToMaturity, 1);
	printf("}\n");
}
void FastProtocolManager::PrintSecurityStatus(FastSecurityStatusInfo *info) {

	printf("FastSecurityStatusInfo {\n");
	PrintInt32("TemplateId", 2106, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("TradingSessionSubID", info->TradingSessionSubID, info->TradingSessionSubIDLength, 1);
	PrintInt32("SecurityTradingStatus", info->SecurityTradingStatus, 1);
	PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	printf("}\n");
}
void FastProtocolManager::PrintTradingSessionStatus(FastTradingSessionStatusInfo *info) {

	printf("FastTradingSessionStatusInfo {\n");
	PrintInt32("TemplateId", 2107, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
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
	PrintXmlString("Username", info->Username, info->UsernameLength);
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
	PrintXmlString("Text", info->Text, info->TextLength);
	PrintXmlItemEnd("FastLogoutInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshGeneric(FastMarketDataSnapshotFullRefreshGenericInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshGenericInfo");
	PrintXmlInt32("TemplateId", 2103);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlDecimal("NetChgPrevDay", &(info->NetChgPrevDay));
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest);
		PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshGenericInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshGeneric(FastMarketDataIncrementalRefreshGenericInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshGenericInfo");
	PrintXmlInt32("TemplateId", 2104);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		PrintXmlInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest);
		PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshGenericInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshOLSFOND(FastMarketDataSnapshotFullRefreshOLSFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshOLSFONDInfo");
	PrintXmlInt32("TemplateId", 2410);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshOLSFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshOLSCURR(FastMarketDataSnapshotFullRefreshOLSCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshOLSCURRInfo");
	PrintXmlInt32("TemplateId", 3500);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshOLSCURRInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshTLSFOND(FastMarketDataSnapshotFullRefreshTLSFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshTLSFONDInfo");
	PrintXmlInt32("TemplateId", 2411);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshTLSFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshTLSCURR(FastMarketDataSnapshotFullRefreshTLSCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshTLSCURRInfo");
	PrintXmlInt32("TemplateId", 3501);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshTLSCURRInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshOBSFOND(FastMarketDataSnapshotFullRefreshOBSFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshOBSFONDInfo");
	PrintXmlInt32("TemplateId", 2412);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshOBSFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataSnapshotFullRefreshOBSCURR(FastMarketDataSnapshotFullRefreshOBSCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataSnapshotFullRefreshOBSCURRInfo");
	PrintXmlInt32("TemplateId", 3502);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlUInt32("LastFragment", info->LastFragment);
	PrintXmlUInt32("RouteFirst", info->RouteFirst);
	PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataSnapshotFullRefreshOBSCURRInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshMSRFOND(FastMarketDataIncrementalRefreshMSRFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshMSRFONDInfo");
	PrintXmlInt32("TemplateId", 2423);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshMSRFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshMSRCURR(FastMarketDataIncrementalRefreshMSRCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshMSRCURRInfo");
	PrintXmlInt32("TemplateId", 3513);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshMSRCURRInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshOLRFOND(FastMarketDataIncrementalRefreshOLRFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshOLRFONDInfo");
	PrintXmlInt32("TemplateId", 2420);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshOLRFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshOLRCURR(FastMarketDataIncrementalRefreshOLRCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshOLRCURRInfo");
	PrintXmlInt32("TemplateId", 3510);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlString("DealNumber", gmdeItemInfo->DealNumber, gmdeItemInfo->DealNumberLength);
		PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshOLRCURRInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshOBRFOND(FastMarketDataIncrementalRefreshOBRFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshOBRFONDInfo");
	PrintXmlInt32("TemplateId", 2422);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshOBRFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshOBRCURR(FastMarketDataIncrementalRefreshOBRCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshOBRCURRInfo");
	PrintXmlInt32("TemplateId", 3512);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshOBRCURRInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshTLRFOND(FastMarketDataIncrementalRefreshTLRFONDInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshTLRFONDInfo");
	PrintXmlInt32("TemplateId", 2421);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshTLRFONDInfo");
}
void FastProtocolManager::PrintXmlMarketDataIncrementalRefreshTLRCURR(FastMarketDataIncrementalRefreshTLRCURRInfo *info) {

	PrintXmlItemBegin("FastMarketDataIncrementalRefreshTLRCURRInfo");
	PrintXmlInt32("TemplateId", 3511);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastMarketDataIncrementalRefreshTLRCURRInfo");
}
void FastProtocolManager::PrintXmlSecurityDefinition(FastSecurityDefinitionInfo *info) {

	PrintXmlItemBegin("FastSecurityDefinitionInfo");
	PrintXmlInt32("TemplateId", 2115);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlString("MessageEncoding", info->MessageEncoding, info->MessageEncodingLength);
	PrintXmlInt32("TotNumReports", info->TotNumReports);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlByteVector("SecurityID", info->SecurityID, info->SecurityIDLength);
	PrintXmlByteVector("SecurityIDSource", info->SecurityIDSource, info->SecurityIDSourceLength);
	PrintXmlInt32("Product", info->Product);
	PrintXmlByteVector("CFICode", info->CFICode, info->CFICodeLength);
	PrintXmlByteVector("SecurityType", info->SecurityType, info->SecurityTypeLength);
	PrintXmlUInt32("MaturityDate", info->MaturityDate);
	PrintXmlUInt32("SettlDate", info->SettlDate);
	PrintXmlString("SettleType", info->SettleType, info->SettleTypeLength);
	PrintXmlDecimal("OrigIssueAmt", &(info->OrigIssueAmt));
	PrintXmlUInt32("CouponPaymentDate", info->CouponPaymentDate);
	PrintXmlDecimal("CouponRate", &(info->CouponRate));
	PrintXmlUInt32("SettlFixingDate", info->SettlFixingDate);
	PrintXmlDecimal("DividendNetPx", &(info->DividendNetPx));
	PrintXmlByteVector("SecurityDesc", info->SecurityDesc, info->SecurityDescLength);
	PrintXmlByteVector("EncodedSecurityDesc", info->EncodedSecurityDesc, info->EncodedSecurityDescLength);
	PrintXmlByteVector("QuoteText", info->QuoteText, info->QuoteTextLength);
	PrintXmlInt32("GroupInstrAttribCount", info->GroupInstrAttribCount);

	FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

	for(int i = 0; i < info->GroupInstrAttribCount; i++) {
		giaItemInfo = info->GroupInstrAttrib[i];
		PrintXmlItemBegin("item", i);
		PrintXmlInt32("InstrAttribType", giaItemInfo->InstrAttribType);
		PrintXmlByteVector("InstrAttribValue", giaItemInfo->InstrAttribValue, giaItemInfo->InstrAttribValueLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlString("Currency", info->Currency, info->CurrencyLength);
	PrintXmlInt32("MarketSegmentGrpCount", info->MarketSegmentGrpCount);

	FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

	for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
		msgItemInfo = info->MarketSegmentGrp[i];
		PrintXmlItemBegin("item", i);
		PrintXmlDecimal("RoundLot", &(msgItemInfo->RoundLot));
		PrintXmlInt32("TradingSessionRulesGrpCount", msgItemInfo->TradingSessionRulesGrpCount);

		FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

		for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
			tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[i];
			PrintXmlItemBegin("item", i);
			PrintXmlString("TradingSessionID", tsrgItemInfo->TradingSessionID, tsrgItemInfo->TradingSessionIDLength);
			PrintXmlString("TradingSessionSubID", tsrgItemInfo->TradingSessionSubID, tsrgItemInfo->TradingSessionSubIDLength);
			PrintXmlInt32("SecurityTradingStatus", tsrgItemInfo->SecurityTradingStatus);
			PrintXmlInt32("OrderNote", tsrgItemInfo->OrderNote);
			PrintXmlItemEnd("item", i);
		}

		PrintXmlItemEnd("item", i);
	}

	PrintXmlString("SettlCurrency", info->SettlCurrency, info->SettlCurrencyLength);
	PrintXmlInt32("PriceType", info->PriceType);
	PrintXmlString("StateSecurityID", info->StateSecurityID, info->StateSecurityIDLength);
	PrintXmlByteVector("EncodedShortSecurityDesc", info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength);
	PrintXmlByteVector("MarketCode", info->MarketCode, info->MarketCodeLength);
	PrintXmlDecimal("MinPriceIncrement", &(info->MinPriceIncrement));
	PrintXmlDecimal("MktShareLimit", &(info->MktShareLimit));
	PrintXmlDecimal("MktShareThreshold", &(info->MktShareThreshold));
	PrintXmlDecimal("MaxOrdersVolume", &(info->MaxOrdersVolume));
	PrintXmlDecimal("PriceMvmLimit", &(info->PriceMvmLimit));
	PrintXmlDecimal("FaceValue", &(info->FaceValue));
	PrintXmlDecimal("BaseSwapPx", &(info->BaseSwapPx));
	PrintXmlDecimal("RepoToPx", &(info->RepoToPx));
	PrintXmlDecimal("BuyBackPx", &(info->BuyBackPx));
	PrintXmlUInt32("BuyBackDate", info->BuyBackDate);
	PrintXmlDecimal("NoSharesIssued", &(info->NoSharesIssued));
	PrintXmlDecimal("HighLimit", &(info->HighLimit));
	PrintXmlDecimal("LowLimit", &(info->LowLimit));
	PrintXmlInt32("NumOfDaysToMaturity", info->NumOfDaysToMaturity);
	PrintXmlItemEnd("FastSecurityDefinitionInfo");
}
void FastProtocolManager::PrintXmlSecurityStatus(FastSecurityStatusInfo *info) {

	PrintXmlItemBegin("FastSecurityStatusInfo");
	PrintXmlInt32("TemplateId", 2106);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("TradingSessionSubID", info->TradingSessionSubID, info->TradingSessionSubIDLength);
	PrintXmlInt32("SecurityTradingStatus", info->SecurityTradingStatus);
	PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlItemEnd("FastSecurityStatusInfo");
}
void FastProtocolManager::PrintXmlTradingSessionStatus(FastTradingSessionStatusInfo *info) {

	PrintXmlItemBegin("FastTradingSessionStatusInfo");
	PrintXmlInt32("TemplateId", 2107);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
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
