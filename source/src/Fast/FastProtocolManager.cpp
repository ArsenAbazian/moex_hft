#include "Fast/FastProtocolManager.h"
#include "../Managers/DebugInfoManager.h"

FastProtocolManager::FastProtocolManager(FastObjectsAllocationInfo *allocInfo) {
	this->m_allocationInfo = allocInfo;
	this->InitializeConstantStrings();
	this->InitializeDecodeMethodPointers();
	this->InitializeMessageInfo();
	this->m_snapshotInfo = new FastSnapshotInfo();
	this->m_skipTemplateIdCount = 0;
	DebugInfoManager::Default->PrintMemoryInfo("FastProtocolManager::FastProtocolManager");
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
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintString("Username", info->Username, info->UsernameLength, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
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
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintString("Text", info->Text, info->TextLength, 1);
	printf("}\n");
}
void FastProtocolManager::PrintGeneric(FastGenericInfo *info) {

	printf("FastGenericInfo {\n");
	PrintInt32("TemplateId", 2103, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	if((info->NullMap & NULL_MAP_INDEX7) != 0)
		PrintDecimal("NetChgPrevDay", &(info->NetChgPrevDay), 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX28) != 0)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX29) != 0)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX30) != 0)
			PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX31) != 0)
			PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX32) != 0)
			PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX33) != 0)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX34) != 0)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX35) != 0)
			PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX36) != 0)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX37) != 0)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX38) != 0)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX39) != 0)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX40) != 0)
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
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX28) != 0)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX29) != 0)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX30) != 0)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX31) != 0)
			PrintInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX32) != 0)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX33) != 0)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX34) != 0)
			PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX35) != 0)
			PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX36) != 0)
			PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX37) != 0)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX38) != 0)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX39) != 0)
			PrintDecimal("NominalValue", &(gmdeItemInfo->NominalValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX40) != 0)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX41) != 0)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX42) != 0)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX43) != 0)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX44) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX45) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintOLSFOND(FastOLSFONDInfo *info) {

	printf("FastOLSFONDInfo {\n");
	PrintInt32("TemplateId", 2510, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintOLSCURR(FastOLSCURRInfo *info) {

	printf("FastOLSCURRInfo {\n");
	PrintInt32("TemplateId", 3600, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintTLSFOND(FastTLSFONDInfo *info) {

	printf("FastTLSFONDInfo {\n");
	PrintInt32("TemplateId", 2511, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintTLSCURR(FastTLSCURRInfo *info) {

	printf("FastTLSCURRInfo {\n");
	PrintInt32("TemplateId", 3601, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed, 1);
	PrintInt32("RptSeq", info->RptSeq, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintUInt32("LastFragment", info->LastFragment, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintUInt32("RouteFirst", info->RouteFirst, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info) {

	printf("FastIncrementalMSRFONDInfo {\n");
	PrintInt32("TemplateId", 2523, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintUInt64("LastUpdateTime", info->LastUpdateTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX28) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX29) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX30) != 0)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX31) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX32) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info) {

	printf("FastIncrementalMSRCURRInfo {\n");
	PrintInt32("TemplateId", 3613, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintUInt64("LastUpdateTime", info->LastUpdateTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintUInt32("StartTime", gmdeItemInfo->StartTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintInt32("OfferNbOr", gmdeItemInfo->OfferNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintInt32("BidNbOr", gmdeItemInfo->BidNbOr, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info) {

	printf("FastIncrementalOLRFONDInfo {\n");
	PrintInt32("TemplateId", 2520, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info) {

	printf("FastIncrementalOLRCURRInfo {\n");
	PrintInt32("TemplateId", 3610, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalTLRFOND(FastIncrementalTLRFONDInfo *info) {

	printf("FastIncrementalTLRFONDInfo {\n");
	PrintInt32("TemplateId", 2521, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintDecimal("Yield", &(gmdeItemInfo->Yield), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength, 2);
		PrintItemEnd(1);
	}

	printf("}\n");
}
void FastProtocolManager::PrintIncrementalTLRCURR(FastIncrementalTLRCURRInfo *info) {

	printf("FastIncrementalTLRCURRInfo {\n");
	PrintInt32("TemplateId", 3611, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("GroupMDEntriesCount", info->GroupMDEntriesCount, 1);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintItemBegin("item", i, 1);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction, 2);
		PrintString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintInt32("RptSeq", gmdeItemInfo->RptSeq, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintUInt32("OrigTime", gmdeItemInfo->OrigTime, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintDecimal("TradeValue", &(gmdeItemInfo->TradeValue), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintUInt32("SettlDate", gmdeItemInfo->SettlDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintDecimal("Price", &(gmdeItemInfo->Price), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintInt32("PriceType", gmdeItemInfo->PriceType, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx), 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength, 2);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength, 2);
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
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintInt32("TotNumReports", info->TotNumReports, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintByteVector("SecurityID", info->SecurityID, info->SecurityIDLength, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintByteVector("SecurityIDSource", info->SecurityIDSource, info->SecurityIDSourceLength, 1);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintInt32("Product", info->Product, 1);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintByteVector("CFICode", info->CFICode, info->CFICodeLength, 1);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintByteVector("SecurityType", info->SecurityType, info->SecurityTypeLength, 1);
	if((info->NullMap & NULL_MAP_INDEX7) != 0)
		PrintUInt32("MaturityDate", info->MaturityDate, 1);
	if((info->NullMap & NULL_MAP_INDEX8) != 0)
		PrintUInt32("SettlDate", info->SettlDate, 1);
	if((info->NullMap & NULL_MAP_INDEX9) != 0)
		PrintString("SettleType", info->SettleType, info->SettleTypeLength, 1);
	if((info->NullMap & NULL_MAP_INDEX10) != 0)
		PrintDecimal("OrigIssueAmt", &(info->OrigIssueAmt), 1);
	if((info->NullMap & NULL_MAP_INDEX11) != 0)
		PrintUInt32("CouponPaymentDate", info->CouponPaymentDate, 1);
	if((info->NullMap & NULL_MAP_INDEX12) != 0)
		PrintDecimal("CouponRate", &(info->CouponRate), 1);
	if((info->NullMap & NULL_MAP_INDEX13) != 0)
		PrintUInt32("SettlFixingDate", info->SettlFixingDate, 1);
	if((info->NullMap & NULL_MAP_INDEX14) != 0)
		PrintDecimal("DividendNetPx", &(info->DividendNetPx), 1);
	if((info->NullMap & NULL_MAP_INDEX15) != 0)
		PrintByteVector("SecurityDesc", info->SecurityDesc, info->SecurityDescLength, 1);
	if((info->NullMap & NULL_MAP_INDEX16) != 0)
		PrintByteVector("EncodedSecurityDesc", info->EncodedSecurityDesc, info->EncodedSecurityDescLength, 1);
	if((info->NullMap & NULL_MAP_INDEX17) != 0)
		PrintByteVector("QuoteText", info->QuoteText, info->QuoteTextLength, 1);
	if((info->NullMap & NULL_MAP_INDEX18) != 0)
		PrintInt32("GroupInstrAttribCount", info->GroupInstrAttribCount, 1);

		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = info->GroupInstrAttrib[i];
			PrintItemBegin("item", i, 1);
			PrintInt32("InstrAttribType", giaItemInfo->InstrAttribType, 2);
			if((giaItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
				PrintByteVector("InstrAttribValue", giaItemInfo->InstrAttribValue, giaItemInfo->InstrAttribValueLength, 2);
			PrintItemEnd(1);
		}

	if((info->NullMap & NULL_MAP_INDEX19) != 0)
		PrintString("Currency", info->Currency, info->CurrencyLength, 1);
	if((info->NullMap & NULL_MAP_INDEX20) != 0)
		PrintInt32("MarketSegmentGrpCount", info->MarketSegmentGrpCount, 1);

		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = info->MarketSegmentGrp[i];
			PrintItemBegin("item", i, 1);
			if((msgItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
				PrintDecimal("RoundLot", &(msgItemInfo->RoundLot), 2);
			if((msgItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
				PrintInt32("TradingSessionRulesGrpCount", msgItemInfo->TradingSessionRulesGrpCount, 2);

				FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

				for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
					tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[i];
					PrintItemBegin("item", i, 2);
					PrintString("TradingSessionID", tsrgItemInfo->TradingSessionID, tsrgItemInfo->TradingSessionIDLength, 3);
					if((tsrgItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
						PrintString("TradingSessionSubID", tsrgItemInfo->TradingSessionSubID, tsrgItemInfo->TradingSessionSubIDLength, 3);
					if((tsrgItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
						PrintInt32("SecurityTradingStatus", tsrgItemInfo->SecurityTradingStatus, 3);
					if((tsrgItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
						PrintInt32("OrderNote", tsrgItemInfo->OrderNote, 3);
					PrintItemEnd(2);
				}

			PrintItemEnd(1);
		}

	if((info->NullMap & NULL_MAP_INDEX21) != 0)
		PrintString("SettlCurrency", info->SettlCurrency, info->SettlCurrencyLength, 1);
	if((info->NullMap & NULL_MAP_INDEX22) != 0)
		PrintInt32("PriceType", info->PriceType, 1);
	if((info->NullMap & NULL_MAP_INDEX23) != 0)
		PrintString("StateSecurityID", info->StateSecurityID, info->StateSecurityIDLength, 1);
	if((info->NullMap & NULL_MAP_INDEX24) != 0)
		PrintByteVector("EncodedShortSecurityDesc", info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength, 1);
	if((info->NullMap & NULL_MAP_INDEX25) != 0)
		PrintByteVector("MarketCode", info->MarketCode, info->MarketCodeLength, 1);
	if((info->NullMap & NULL_MAP_INDEX26) != 0)
		PrintDecimal("MinPriceIncrement", &(info->MinPriceIncrement), 1);
	if((info->NullMap & NULL_MAP_INDEX27) != 0)
		PrintDecimal("MktShareLimit", &(info->MktShareLimit), 1);
	if((info->NullMap & NULL_MAP_INDEX28) != 0)
		PrintDecimal("MktShareThreshold", &(info->MktShareThreshold), 1);
	if((info->NullMap & NULL_MAP_INDEX29) != 0)
		PrintDecimal("MaxOrdersVolume", &(info->MaxOrdersVolume), 1);
	if((info->NullMap & NULL_MAP_INDEX30) != 0)
		PrintDecimal("PriceMvmLimit", &(info->PriceMvmLimit), 1);
	if((info->NullMap & NULL_MAP_INDEX31) != 0)
		PrintDecimal("FaceValue", &(info->FaceValue), 1);
	if((info->NullMap & NULL_MAP_INDEX32) != 0)
		PrintDecimal("BaseSwapPx", &(info->BaseSwapPx), 1);
	if((info->NullMap & NULL_MAP_INDEX33) != 0)
		PrintDecimal("RepoToPx", &(info->RepoToPx), 1);
	if((info->NullMap & NULL_MAP_INDEX34) != 0)
		PrintDecimal("BuyBackPx", &(info->BuyBackPx), 1);
	if((info->NullMap & NULL_MAP_INDEX35) != 0)
		PrintUInt32("BuyBackDate", info->BuyBackDate, 1);
	if((info->NullMap & NULL_MAP_INDEX36) != 0)
		PrintDecimal("NoSharesIssued", &(info->NoSharesIssued), 1);
	if((info->NullMap & NULL_MAP_INDEX37) != 0)
		PrintDecimal("HighLimit", &(info->HighLimit), 1);
	if((info->NullMap & NULL_MAP_INDEX38) != 0)
		PrintDecimal("LowLimit", &(info->LowLimit), 1);
	if((info->NullMap & NULL_MAP_INDEX39) != 0)
		PrintInt32("NumOfDaysToMaturity", info->NumOfDaysToMaturity, 1);
	printf("}\n");
}
void FastProtocolManager::PrintSecurityStatus(FastSecurityStatusInfo *info) {

	printf("FastSecurityStatusInfo {\n");
	PrintInt32("TemplateId", 2106, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintString("Symbol", info->Symbol, info->SymbolLength, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength, 1);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintString("TradingSessionSubID", info->TradingSessionSubID, info->TradingSessionSubIDLength, 1);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintInt32("SecurityTradingStatus", info->SecurityTradingStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintUInt32("AuctionIndicator", info->AuctionIndicator, 1);
	printf("}\n");
}
void FastProtocolManager::PrintTradingSessionStatus(FastTradingSessionStatusInfo *info) {

	printf("FastTradingSessionStatusInfo {\n");
	PrintInt32("TemplateId", 2107, 1);
	PrintUInt32("MsgSeqNum", info->MsgSeqNum, 1);
	PrintUInt64("SendingTime", info->SendingTime, 1);
	PrintInt32("TradSesStatus", info->TradSesStatus, 1);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
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
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlString("Username", info->Username, info->UsernameLength);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
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
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlString("Text", info->Text, info->TextLength);
	PrintXmlItemEnd("FastLogoutInfo");
}
void FastProtocolManager::PrintXmlGeneric(FastGenericInfo *info) {

	PrintXmlItemBegin("FastGenericInfo");
	PrintXmlInt32("TemplateId", 2103);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	if((info->NullMap & NULL_MAP_INDEX7) != 0)
		PrintXmlDecimal("NetChgPrevDay", &(info->NetChgPrevDay));
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintXmlInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX28) != 0)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX29) != 0)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX30) != 0)
			PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX31) != 0)
			PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX32) != 0)
			PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX33) != 0)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX34) != 0)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX35) != 0)
			PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX36) != 0)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX37) != 0)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX38) != 0)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX39) != 0)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX40) != 0)
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
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlUInt32("EffectiveTime", gmdeItemInfo->EffectiveTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX28) != 0)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX29) != 0)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX30) != 0)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX31) != 0)
			PrintXmlInt32("SumQtyOfBest", gmdeItemInfo->SumQtyOfBest);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX32) != 0)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX33) != 0)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX34) != 0)
			PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX35) != 0)
			PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX36) != 0)
			PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX37) != 0)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX38) != 0)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX39) != 0)
			PrintXmlDecimal("NominalValue", &(gmdeItemInfo->NominalValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX40) != 0)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX41) != 0)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX42) != 0)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX43) != 0)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX44) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX45) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalGenericInfo");
}
void FastProtocolManager::PrintXmlOLSFOND(FastOLSFONDInfo *info) {

	PrintXmlItemBegin("FastOLSFONDInfo");
	PrintXmlInt32("TemplateId", 2510);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastOLSFONDInfo");
}
void FastProtocolManager::PrintXmlOLSCURR(FastOLSCURRInfo *info) {

	PrintXmlItemBegin("FastOLSCURRInfo");
	PrintXmlInt32("TemplateId", 3600);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastOLSCURRInfo");
}
void FastProtocolManager::PrintXmlTLSFOND(FastTLSFONDInfo *info) {

	PrintXmlItemBegin("FastTLSFONDInfo");
	PrintXmlInt32("TemplateId", 2511);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastTLSFONDInfo");
}
void FastProtocolManager::PrintXmlTLSCURR(FastTLSCURRInfo *info) {

	PrintXmlItemBegin("FastTLSCURRInfo");
	PrintXmlInt32("TemplateId", 3601);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlUInt32("LastMsgSeqNumProcessed", info->LastMsgSeqNumProcessed);
	PrintXmlInt32("RptSeq", info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlUInt32("LastFragment", info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlUInt32("RouteFirst", info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintXmlInt32("MDSecurityTradingStatus", info->MDSecurityTradingStatus);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastTLSCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalMSRFONDInfo");
	PrintXmlInt32("TemplateId", 2523);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlUInt64("LastUpdateTime", info->LastUpdateTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintXmlDecimal("MinCurrPx", &(gmdeItemInfo->MinCurrPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintXmlUInt32("MinCurrPxChgTime", gmdeItemInfo->MinCurrPxChgTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintXmlUInt32("VolumeIndicator", gmdeItemInfo->VolumeIndicator);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX28) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX29) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX30) != 0)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX31) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX32) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalMSRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalMSRCURRInfo");
	PrintXmlInt32("TemplateId", 3613);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlUInt64("LastUpdateTime", info->LastUpdateTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastGenericItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlUInt32("StartTime", gmdeItemInfo->StartTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlString("QuoteCondition", gmdeItemInfo->QuoteCondition, gmdeItemInfo->QuoteConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("TradeCondition", gmdeItemInfo->TradeCondition, gmdeItemInfo->TradeConditionLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlString("OpenCloseSettlFlag", gmdeItemInfo->OpenCloseSettlFlag, gmdeItemInfo->OpenCloseSettlFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("NetChgPrevDay", &(gmdeItemInfo->NetChgPrevDay));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlDecimal("ChgFromWAPrice", &(gmdeItemInfo->ChgFromWAPrice));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlDecimal("ChgOpenInterest", &(gmdeItemInfo->ChgOpenInterest));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlDecimal("BidMarketSize", &(gmdeItemInfo->BidMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlDecimal("AskMarketSize", &(gmdeItemInfo->AskMarketSize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlInt32("TotalNumOfTrades", gmdeItemInfo->TotalNumOfTrades);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintXmlInt32("OfferNbOr", gmdeItemInfo->OfferNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintXmlInt32("BidNbOr", gmdeItemInfo->BidNbOr);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintXmlDecimal("ChgFromSettlmnt", &(gmdeItemInfo->ChgFromSettlmnt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX23) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX24) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX25) != 0)
			PrintXmlString("CXFlag", gmdeItemInfo->CXFlag, gmdeItemInfo->CXFlagLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX26) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX27) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalMSRCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalOLRFONDInfo");
	PrintXmlInt32("TemplateId", 2520);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlString("OrdType", gmdeItemInfo->OrdType, gmdeItemInfo->OrdTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("TotalVolume", &(gmdeItemInfo->TotalVolume));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalOLRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalOLRCURRInfo");
	PrintXmlInt32("TemplateId", 3610);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastOLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlString("OrderStatus", gmdeItemInfo->OrderStatus, gmdeItemInfo->OrderStatusLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalOLRCURRInfo");
}
void FastProtocolManager::PrintXmlIncrementalTLRFOND(FastIncrementalTLRFONDInfo *info) {

	PrintXmlItemBegin("FastIncrementalTLRFONDInfo");
	PrintXmlInt32("TemplateId", 2521);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSFONDItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlDecimal("AccruedInterestAmt", &(gmdeItemInfo->AccruedInterestAmt));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlDecimal("Yield", &(gmdeItemInfo->Yield));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX21) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX22) != 0)
			PrintXmlString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength);
		PrintXmlItemEnd("item", i);
	}

	PrintXmlItemEnd("FastIncrementalTLRFONDInfo");
}
void FastProtocolManager::PrintXmlIncrementalTLRCURR(FastIncrementalTLRCURRInfo *info) {

	PrintXmlItemBegin("FastIncrementalTLRCURRInfo");
	PrintXmlInt32("TemplateId", 3611);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("GroupMDEntriesCount", info->GroupMDEntriesCount);

	FastTLSCURRItemInfo* gmdeItemInfo = NULL;

	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		gmdeItemInfo = info->GroupMDEntries[i];
		PrintXmlItemBegin("item", i);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
			PrintXmlUInt32("MDUpdateAction", gmdeItemInfo->MDUpdateAction);
		PrintXmlString("MDEntryType", gmdeItemInfo->MDEntryType, gmdeItemInfo->MDEntryTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
			PrintXmlString("MDEntryID", gmdeItemInfo->MDEntryID, gmdeItemInfo->MDEntryIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
			PrintXmlString("Symbol", gmdeItemInfo->Symbol, gmdeItemInfo->SymbolLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX3) != 0)
			PrintXmlInt32("RptSeq", gmdeItemInfo->RptSeq);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX4) != 0)
			PrintXmlUInt32("MDEntryDate", gmdeItemInfo->MDEntryDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX5) != 0)
			PrintXmlUInt32("MDEntryTime", gmdeItemInfo->MDEntryTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX6) != 0)
			PrintXmlUInt32("OrigTime", gmdeItemInfo->OrigTime);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX7) != 0)
			PrintXmlString("OrderSide", gmdeItemInfo->OrderSide, gmdeItemInfo->OrderSideLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX8) != 0)
			PrintXmlDecimal("MDEntryPx", &(gmdeItemInfo->MDEntryPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX9) != 0)
			PrintXmlDecimal("MDEntrySize", &(gmdeItemInfo->MDEntrySize));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX10) != 0)
			PrintXmlDecimal("TradeValue", &(gmdeItemInfo->TradeValue));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX11) != 0)
			PrintXmlUInt32("SettlDate", gmdeItemInfo->SettlDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX12) != 0)
			PrintXmlString("SettleType", gmdeItemInfo->SettleType, gmdeItemInfo->SettleTypeLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX13) != 0)
			PrintXmlDecimal("Price", &(gmdeItemInfo->Price));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX14) != 0)
			PrintXmlInt32("PriceType", gmdeItemInfo->PriceType);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX15) != 0)
			PrintXmlDecimal("RepoToPx", &(gmdeItemInfo->RepoToPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX16) != 0)
			PrintXmlDecimal("BuyBackPx", &(gmdeItemInfo->BuyBackPx));
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX17) != 0)
			PrintXmlUInt32("BuyBackDate", gmdeItemInfo->BuyBackDate);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX18) != 0)
			PrintXmlString("TradingSessionID", gmdeItemInfo->TradingSessionID, gmdeItemInfo->TradingSessionIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX19) != 0)
			PrintXmlString("TradingSessionSubID", gmdeItemInfo->TradingSessionSubID, gmdeItemInfo->TradingSessionSubIDLength);
		if((gmdeItemInfo->NullMap & NULL_MAP_INDEX20) != 0)
			PrintXmlString("RefOrderID", gmdeItemInfo->RefOrderID, gmdeItemInfo->RefOrderIDLength);
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
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlInt32("TotNumReports", info->TotNumReports);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlByteVector("SecurityID", info->SecurityID, info->SecurityIDLength);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlByteVector("SecurityIDSource", info->SecurityIDSource, info->SecurityIDSourceLength);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		PrintXmlInt32("Product", info->Product);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		PrintXmlByteVector("CFICode", info->CFICode, info->CFICodeLength);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		PrintXmlByteVector("SecurityType", info->SecurityType, info->SecurityTypeLength);
	if((info->NullMap & NULL_MAP_INDEX7) != 0)
		PrintXmlUInt32("MaturityDate", info->MaturityDate);
	if((info->NullMap & NULL_MAP_INDEX8) != 0)
		PrintXmlUInt32("SettlDate", info->SettlDate);
	if((info->NullMap & NULL_MAP_INDEX9) != 0)
		PrintXmlString("SettleType", info->SettleType, info->SettleTypeLength);
	if((info->NullMap & NULL_MAP_INDEX10) != 0)
		PrintXmlDecimal("OrigIssueAmt", &(info->OrigIssueAmt));
	if((info->NullMap & NULL_MAP_INDEX11) != 0)
		PrintXmlUInt32("CouponPaymentDate", info->CouponPaymentDate);
	if((info->NullMap & NULL_MAP_INDEX12) != 0)
		PrintXmlDecimal("CouponRate", &(info->CouponRate));
	if((info->NullMap & NULL_MAP_INDEX13) != 0)
		PrintXmlUInt32("SettlFixingDate", info->SettlFixingDate);
	if((info->NullMap & NULL_MAP_INDEX14) != 0)
		PrintXmlDecimal("DividendNetPx", &(info->DividendNetPx));
	if((info->NullMap & NULL_MAP_INDEX15) != 0)
		PrintXmlByteVector("SecurityDesc", info->SecurityDesc, info->SecurityDescLength);
	if((info->NullMap & NULL_MAP_INDEX16) != 0)
		PrintXmlByteVector("EncodedSecurityDesc", info->EncodedSecurityDesc, info->EncodedSecurityDescLength);
	if((info->NullMap & NULL_MAP_INDEX17) != 0)
		PrintXmlByteVector("QuoteText", info->QuoteText, info->QuoteTextLength);
	if((info->NullMap & NULL_MAP_INDEX18) != 0)
		PrintXmlInt32("GroupInstrAttribCount", info->GroupInstrAttribCount);

		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = info->GroupInstrAttrib[i];
			PrintXmlItemBegin("item", i);
			PrintXmlInt32("InstrAttribType", giaItemInfo->InstrAttribType);
			if((giaItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
				PrintXmlByteVector("InstrAttribValue", giaItemInfo->InstrAttribValue, giaItemInfo->InstrAttribValueLength);
			PrintXmlItemEnd("item", i);
		}

	if((info->NullMap & NULL_MAP_INDEX19) != 0)
		PrintXmlString("Currency", info->Currency, info->CurrencyLength);
	if((info->NullMap & NULL_MAP_INDEX20) != 0)
		PrintXmlInt32("MarketSegmentGrpCount", info->MarketSegmentGrpCount);

		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = info->MarketSegmentGrp[i];
			PrintXmlItemBegin("item", i);
			if((msgItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
				PrintXmlDecimal("RoundLot", &(msgItemInfo->RoundLot));
			if((msgItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
				PrintXmlInt32("TradingSessionRulesGrpCount", msgItemInfo->TradingSessionRulesGrpCount);

				FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

				for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
					tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[i];
					PrintXmlItemBegin("item", i);
					PrintXmlString("TradingSessionID", tsrgItemInfo->TradingSessionID, tsrgItemInfo->TradingSessionIDLength);
					if((tsrgItemInfo->NullMap & NULL_MAP_INDEX0) != 0)
						PrintXmlString("TradingSessionSubID", tsrgItemInfo->TradingSessionSubID, tsrgItemInfo->TradingSessionSubIDLength);
					if((tsrgItemInfo->NullMap & NULL_MAP_INDEX1) != 0)
						PrintXmlInt32("SecurityTradingStatus", tsrgItemInfo->SecurityTradingStatus);
					if((tsrgItemInfo->NullMap & NULL_MAP_INDEX2) != 0)
						PrintXmlInt32("OrderNote", tsrgItemInfo->OrderNote);
					PrintXmlItemEnd("item", i);
				}

			PrintXmlItemEnd("item", i);
		}

	if((info->NullMap & NULL_MAP_INDEX21) != 0)
		PrintXmlString("SettlCurrency", info->SettlCurrency, info->SettlCurrencyLength);
	if((info->NullMap & NULL_MAP_INDEX22) != 0)
		PrintXmlInt32("PriceType", info->PriceType);
	if((info->NullMap & NULL_MAP_INDEX23) != 0)
		PrintXmlString("StateSecurityID", info->StateSecurityID, info->StateSecurityIDLength);
	if((info->NullMap & NULL_MAP_INDEX24) != 0)
		PrintXmlByteVector("EncodedShortSecurityDesc", info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength);
	if((info->NullMap & NULL_MAP_INDEX25) != 0)
		PrintXmlByteVector("MarketCode", info->MarketCode, info->MarketCodeLength);
	if((info->NullMap & NULL_MAP_INDEX26) != 0)
		PrintXmlDecimal("MinPriceIncrement", &(info->MinPriceIncrement));
	if((info->NullMap & NULL_MAP_INDEX27) != 0)
		PrintXmlDecimal("MktShareLimit", &(info->MktShareLimit));
	if((info->NullMap & NULL_MAP_INDEX28) != 0)
		PrintXmlDecimal("MktShareThreshold", &(info->MktShareThreshold));
	if((info->NullMap & NULL_MAP_INDEX29) != 0)
		PrintXmlDecimal("MaxOrdersVolume", &(info->MaxOrdersVolume));
	if((info->NullMap & NULL_MAP_INDEX30) != 0)
		PrintXmlDecimal("PriceMvmLimit", &(info->PriceMvmLimit));
	if((info->NullMap & NULL_MAP_INDEX31) != 0)
		PrintXmlDecimal("FaceValue", &(info->FaceValue));
	if((info->NullMap & NULL_MAP_INDEX32) != 0)
		PrintXmlDecimal("BaseSwapPx", &(info->BaseSwapPx));
	if((info->NullMap & NULL_MAP_INDEX33) != 0)
		PrintXmlDecimal("RepoToPx", &(info->RepoToPx));
	if((info->NullMap & NULL_MAP_INDEX34) != 0)
		PrintXmlDecimal("BuyBackPx", &(info->BuyBackPx));
	if((info->NullMap & NULL_MAP_INDEX35) != 0)
		PrintXmlUInt32("BuyBackDate", info->BuyBackDate);
	if((info->NullMap & NULL_MAP_INDEX36) != 0)
		PrintXmlDecimal("NoSharesIssued", &(info->NoSharesIssued));
	if((info->NullMap & NULL_MAP_INDEX37) != 0)
		PrintXmlDecimal("HighLimit", &(info->HighLimit));
	if((info->NullMap & NULL_MAP_INDEX38) != 0)
		PrintXmlDecimal("LowLimit", &(info->LowLimit));
	if((info->NullMap & NULL_MAP_INDEX39) != 0)
		PrintXmlInt32("NumOfDaysToMaturity", info->NumOfDaysToMaturity);
	PrintXmlItemEnd("FastSecurityDefinitionInfo");
}
void FastProtocolManager::PrintXmlSecurityStatus(FastSecurityStatusInfo *info) {

	PrintXmlItemBegin("FastSecurityStatusInfo");
	PrintXmlInt32("TemplateId", 2106);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlString("Symbol", info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		PrintXmlString("TradingSessionID", info->TradingSessionID, info->TradingSessionIDLength);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		PrintXmlString("TradingSessionSubID", info->TradingSessionSubID, info->TradingSessionSubIDLength);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		PrintXmlInt32("SecurityTradingStatus", info->SecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		PrintXmlUInt32("AuctionIndicator", info->AuctionIndicator);
	PrintXmlItemEnd("FastSecurityStatusInfo");
}
void FastProtocolManager::PrintXmlTradingSessionStatus(FastTradingSessionStatusInfo *info) {

	PrintXmlItemBegin("FastTradingSessionStatusInfo");
	PrintXmlInt32("TemplateId", 2107);
	PrintXmlUInt32("MsgSeqNum", info->MsgSeqNum);
	PrintXmlUInt64("SendingTime", info->SendingTime);
	PrintXmlInt32("TradSesStatus", info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
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
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2101);
	WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteInt32_Mandatory(info->HeartBtInt);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->Username, info->UsernameLength);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->Password, info->PasswordLength);
	WriteString_Mandatory(info->DefaultApplVerID, info->DefaultApplVerIDLength);
}
void FastProtocolManager::EncodeLogoutInfo(FastLogoutInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2102);
	WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->Text, info->TextLength);
}
void FastProtocolManager::EncodeGenericInfo(FastGenericInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2103);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	if((info->NullMap & NULL_MAP_INDEX7) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->NetChgPrevDay));
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->EffectiveTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX19) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX20) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX21) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX22) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX23) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX24) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX25) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX26) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX27) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->SumQtyOfBest);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX28) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX29) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX30) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MinCurrPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX31) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MinCurrPxChgTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX32) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->VolumeIndicator);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX33) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX34) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX35) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NominalValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX36) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX37) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX38) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX39) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX40) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalGenericInfo(FastIncrementalGenericInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2104);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->EffectiveTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NetChgPrevDay));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX19) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX20) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX21) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX22) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX23) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX24) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX25) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX26) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX27) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX28) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX29) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX30) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX31) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->SumQtyOfBest);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX32) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX33) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX34) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MinCurrPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX35) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MinCurrPxChgTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX36) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->VolumeIndicator);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX37) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX38) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX39) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NominalValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX40) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX41) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX42) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX43) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX44) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX45) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeOLSFONDInfo(FastOLSFONDInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2510);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WritePresenceMap((*gmdeItemInfo)->PresenceMap); // Presence Map hack

		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX0)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
			}
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX1)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX2)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX3)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX4)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX5)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX6)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX7)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX8)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX9)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX10)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
			}
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeOLSCURRInfo(FastOLSCURRInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(3600);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WritePresenceMap((*gmdeItemInfo)->PresenceMap); // Presence Map hack

		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX0)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
			}
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX1)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX2)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX3)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX4)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX5)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX6)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX7)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
			}
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeTLSFONDInfo(FastTLSFONDInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2511);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WritePresenceMap((*gmdeItemInfo)->PresenceMap); // Presence Map hack

		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX0)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX1)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX2)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX3)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX4)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX5)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX6)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX7)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX8)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX9)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX10)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX11)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX12)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
				this->WriteNull();
			else
				WriteInt32_Optional((*gmdeItemInfo)->PriceType);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX13)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX14)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX15)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX16)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX17)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->RefOrderID, (*gmdeItemInfo)->RefOrderIDLength);
			}
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeTLSCURRInfo(FastTLSCURRInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(3601);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastMsgSeqNumProcessed);
	WriteInt32_Mandatory(info->RptSeq);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->LastFragment);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->RouteFirst);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->MDSecurityTradingStatus);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WritePresenceMap((*gmdeItemInfo)->PresenceMap); // Presence Map hack

		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX0)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX1)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX2)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX3)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX4)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX5)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX6)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX7)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX8)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX9)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX10)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
				this->WriteNull();
			else
				WriteInt32_Optional((*gmdeItemInfo)->PriceType);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX11)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX12)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX13)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX14)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX15)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->RefOrderID, (*gmdeItemInfo)->RefOrderIDLength);
			}
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalMSRFONDInfo(FastIncrementalMSRFONDInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2523);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteUInt64_Optional(info->LastUpdateTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NetChgPrevDay));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX19) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX20) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX21) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX22) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX23) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX24) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX25) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MinCurrPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX26) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MinCurrPxChgTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX27) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->VolumeIndicator);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX28) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX29) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX30) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX31) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX32) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalMSRCURRInfo(FastIncrementalMSRCURRInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(3613);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteUInt64_Optional(info->LastUpdateTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastGenericItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->StartTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->QuoteCondition, (*gmdeItemInfo)->QuoteConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradeCondition, (*gmdeItemInfo)->TradeConditionLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OpenCloseSettlFlag, (*gmdeItemInfo)->OpenCloseSettlFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->NetChgPrevDay));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromWAPrice));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgOpenInterest));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BidMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AskMarketSize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->TotalNumOfTrades);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX19) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX20) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->OfferNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX21) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->BidNbOr);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX22) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->ChgFromSettlmnt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX23) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX24) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX25) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->CXFlag, (*gmdeItemInfo)->CXFlagLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX26) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX27) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalOLRFONDInfo(FastIncrementalOLRFONDInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2520);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WritePresenceMap((*gmdeItemInfo)->PresenceMap); // Presence Map hack

		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX0)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
			}
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX1)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
			}
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX2)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX3)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX4)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX5)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX6)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX7)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX8)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX9)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrdType, (*gmdeItemInfo)->OrdTypeLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX10)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->TotalVolume));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX11)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX12)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
			}
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalOLRCURRInfo(FastIncrementalOLRCURRInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(3610);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastOLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		WritePresenceMap((*gmdeItemInfo)->PresenceMap); // Presence Map hack

		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX0)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX1)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
			}
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX2)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
			}
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX3)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX4)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX5)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
				this->WriteNull();
			else
				WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX6)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX7)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX8)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->OrderStatus, (*gmdeItemInfo)->OrderStatusLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX9)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
			}
		if(CheckOptionalFieldPresence((*gmdeItemInfo)->PresenceMap, PRESENCE_MAP_INDEX10)) {
			if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
				this->WriteNullString();
			else
				WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
			}
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalTLRFONDInfo(FastIncrementalTLRFONDInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2521);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSFONDItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->AccruedInterestAmt));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Yield));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX19) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX20) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX21) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX22) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->RefOrderID, (*gmdeItemInfo)->RefOrderIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeIncrementalTLRCURRInfo(FastIncrementalTLRCURRInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(3611);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteUInt32_Mandatory(info->GroupMDEntriesCount);
	FastTLSCURRItemInfo **gmdeItemInfo = info->GroupMDEntries;
	for(int i = 0; i < info->GroupMDEntriesCount; i++) {
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDUpdateAction);
		WriteString_Mandatory((*gmdeItemInfo)->MDEntryType, (*gmdeItemInfo)->MDEntryTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->MDEntryID, (*gmdeItemInfo)->MDEntryIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->Symbol, (*gmdeItemInfo)->SymbolLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX3) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->RptSeq);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX4) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX5) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->MDEntryTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX6) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->OrigTime);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX7) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->OrderSide, (*gmdeItemInfo)->OrderSideLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX8) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntryPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX9) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->MDEntrySize));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX10) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->TradeValue));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX11) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->SettlDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX12) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->SettleType, (*gmdeItemInfo)->SettleTypeLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX13) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->Price));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX14) != 0)
			this->WriteNull();
		else
			WriteInt32_Optional((*gmdeItemInfo)->PriceType);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX15) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->RepoToPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX16) != 0)
			this->WriteNull();
		else
			WriteDecimal_Optional(&((*gmdeItemInfo)->BuyBackPx));
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX17) != 0)
			this->WriteNull();
		else
			WriteUInt32_Optional((*gmdeItemInfo)->BuyBackDate);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX18) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionID, (*gmdeItemInfo)->TradingSessionIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX19) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->TradingSessionSubID, (*gmdeItemInfo)->TradingSessionSubIDLength);
		if(((*gmdeItemInfo)->NullMap & NULL_MAP_INDEX20) != 0)
			this->WriteNullString();
		else
			WriteString_Optional((*gmdeItemInfo)->RefOrderID, (*gmdeItemInfo)->RefOrderIDLength);
		gmdeItemInfo++;
	}
}
void FastProtocolManager::EncodeSecurityDefinitionInfo(FastSecurityDefinitionInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2115);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->TotNumReports);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityID, info->SecurityIDLength);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityIDSource, info->SecurityIDSourceLength);
	if((info->NullMap & NULL_MAP_INDEX4) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->Product);
	if((info->NullMap & NULL_MAP_INDEX5) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->CFICode, info->CFICodeLength);
	if((info->NullMap & NULL_MAP_INDEX6) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityType, info->SecurityTypeLength);
	if((info->NullMap & NULL_MAP_INDEX7) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->MaturityDate);
	if((info->NullMap & NULL_MAP_INDEX8) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->SettlDate);
	if((info->NullMap & NULL_MAP_INDEX9) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->SettleType, info->SettleTypeLength);
	if((info->NullMap & NULL_MAP_INDEX10) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->OrigIssueAmt));
	if((info->NullMap & NULL_MAP_INDEX11) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->CouponPaymentDate);
	if((info->NullMap & NULL_MAP_INDEX12) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->CouponRate));
	if((info->NullMap & NULL_MAP_INDEX13) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->SettlFixingDate);
	if((info->NullMap & NULL_MAP_INDEX14) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->DividendNetPx));
	if((info->NullMap & NULL_MAP_INDEX15) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->SecurityDesc, info->SecurityDescLength);
	if((info->NullMap & NULL_MAP_INDEX16) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->EncodedSecurityDesc, info->EncodedSecurityDescLength);
	if((info->NullMap & NULL_MAP_INDEX17) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->QuoteText, info->QuoteTextLength);
	if((info->NullMap & NULL_MAP_INDEX18) != 0)
		this->WriteNull();
	else {
		WriteUInt32_Optional(info->GroupInstrAttribCount);
		FastSecurityDefinitionGroupInstrAttribItemInfo **giaItemInfo = info->GroupInstrAttrib;
		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			WriteInt32_Mandatory((*giaItemInfo)->InstrAttribType);
			if(((*giaItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
				this->WriteNull();
			else
				WriteByteVector_Optional((*giaItemInfo)->InstrAttribValue, (*giaItemInfo)->InstrAttribValueLength);
			giaItemInfo++;
		}
	}
	if((info->NullMap & NULL_MAP_INDEX19) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->Currency, info->CurrencyLength);
	if((info->NullMap & NULL_MAP_INDEX20) != 0)
		this->WriteNull();
	else {
		WriteUInt32_Optional(info->MarketSegmentGrpCount);
		FastSecurityDefinitionMarketSegmentGrpItemInfo **msgItemInfo = info->MarketSegmentGrp;
		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			if(((*msgItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
				this->WriteNull();
			else
				WriteDecimal_Optional(&((*msgItemInfo)->RoundLot));
			if(((*msgItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
				this->WriteNull();
			else {
				WriteUInt32_Optional((*msgItemInfo)->TradingSessionRulesGrpCount);
				FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **tsrgItemInfo = (*msgItemInfo)->TradingSessionRulesGrp;
				for(int i = 0; i < (*msgItemInfo)->TradingSessionRulesGrpCount; i++) {
					WriteString_Mandatory((*tsrgItemInfo)->TradingSessionID, (*tsrgItemInfo)->TradingSessionIDLength);
					if(((*tsrgItemInfo)->NullMap & NULL_MAP_INDEX0) != 0)
						this->WriteNullString();
					else
						WriteString_Optional((*tsrgItemInfo)->TradingSessionSubID, (*tsrgItemInfo)->TradingSessionSubIDLength);
					if(((*tsrgItemInfo)->NullMap & NULL_MAP_INDEX1) != 0)
						this->WriteNull();
					else
						WriteInt32_Optional((*tsrgItemInfo)->SecurityTradingStatus);
					if(((*tsrgItemInfo)->NullMap & NULL_MAP_INDEX2) != 0)
						this->WriteNull();
					else
						WriteInt32_Optional((*tsrgItemInfo)->OrderNote);
					tsrgItemInfo++;
				}
			}
			msgItemInfo++;
		}
	}
	if((info->NullMap & NULL_MAP_INDEX21) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->SettlCurrency, info->SettlCurrencyLength);
	if((info->NullMap & NULL_MAP_INDEX22) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->PriceType);
	if((info->NullMap & NULL_MAP_INDEX23) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->StateSecurityID, info->StateSecurityIDLength);
	if((info->NullMap & NULL_MAP_INDEX24) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength);
	if((info->NullMap & NULL_MAP_INDEX25) != 0)
		this->WriteNull();
	else
		WriteByteVector_Optional(info->MarketCode, info->MarketCodeLength);
	if((info->NullMap & NULL_MAP_INDEX26) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MinPriceIncrement));
	if((info->NullMap & NULL_MAP_INDEX27) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MktShareLimit));
	if((info->NullMap & NULL_MAP_INDEX28) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MktShareThreshold));
	if((info->NullMap & NULL_MAP_INDEX29) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->MaxOrdersVolume));
	if((info->NullMap & NULL_MAP_INDEX30) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->PriceMvmLimit));
	if((info->NullMap & NULL_MAP_INDEX31) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->FaceValue));
	if((info->NullMap & NULL_MAP_INDEX32) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->BaseSwapPx));
	if((info->NullMap & NULL_MAP_INDEX33) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->RepoToPx));
	if((info->NullMap & NULL_MAP_INDEX34) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->BuyBackPx));
	if((info->NullMap & NULL_MAP_INDEX35) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->BuyBackDate);
	if((info->NullMap & NULL_MAP_INDEX36) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->NoSharesIssued));
	if((info->NullMap & NULL_MAP_INDEX37) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->HighLimit));
	if((info->NullMap & NULL_MAP_INDEX38) != 0)
		this->WriteNull();
	else
		WriteDecimal_Optional(&(info->LowLimit));
	if((info->NullMap & NULL_MAP_INDEX39) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->NumOfDaysToMaturity);
}
void FastProtocolManager::EncodeSecurityStatusInfo(FastSecurityStatusInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2106);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteString_Mandatory(info->Symbol, info->SymbolLength);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
	if((info->NullMap & NULL_MAP_INDEX1) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->TradingSessionSubID, info->TradingSessionSubIDLength);
	if((info->NullMap & NULL_MAP_INDEX2) != 0)
		this->WriteNull();
	else
		WriteInt32_Optional(info->SecurityTradingStatus);
	if((info->NullMap & NULL_MAP_INDEX3) != 0)
		this->WriteNull();
	else
		WriteUInt32_Optional(info->AuctionIndicator);
}
void FastProtocolManager::EncodeTradingSessionStatusInfo(FastTradingSessionStatusInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2107);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
	WriteInt32_Mandatory(info->TradSesStatus);
	if((info->NullMap & NULL_MAP_INDEX0) != 0)
		this->WriteNullString();
	else
		WriteString_Optional(info->Text, info->TextLength);
	WriteString_Mandatory(info->TradingSessionID, info->TradingSessionIDLength);
}
void FastProtocolManager::EncodeHeartbeatInfo(FastHeartbeatInfo* info) {
	WritePresenceMap(info->PresenceMap); // Presence Map hack
	WriteUInt32_Mandatory(2108);
	WriteUInt32_Mandatory(info->MsgSeqNum);
	WriteUInt64_Mandatory(info->SendingTime);
}
#pragma endregion
