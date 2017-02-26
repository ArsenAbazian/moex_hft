#pragma once
#include "Fix/FixTypes.h"
#include "FastTypes.h"
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

class FastProtocolManager;
class OrderTesterFond;
class OrderTesterCurr;
class TradeTesterFond;
class TradeTesterCurr;
class StatisticsTesterFond;
class StatisticsTesterCurr;
class FeedConnection;

#pragma region Decode_Method_Pointer_Definition_GeneratedCode
typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();
typedef void* (FastProtocolManager::*FastReleaseMethodPointer)();
typedef FastSnapshotInfo* (FastProtocolManager::*FastGetSnapshotInfoMethodPointer)();
#pragma endregion

#pragma region Checking_Presence_GeneratedCode
#define CheckMandatoryFieldPresence(map, field) ((map & field) != 0)
#define CheckOptionalFieldPresence(map, field) ((map & field) != 0)
#pragma endregion

class FastProtocolManager {
	friend class OrderTesterFond;
	friend class OrderTesterCurr;
	friend class TradeTesterFond;
	friend class TradeTesterCurr;
	friend class StatisticsTesterFond;
	friend class StatisticsTesterCurr;
	friend class FeedConnection;

	const int maxBufferLength = 16000;
	BYTE	        			*buffer;
	BYTE	        			*currentPos;
	int		        			bufferLength;
    UINT            			m_templateId;
    UINT64          			m_presenceMap;

    FILE            			*m_xmlFilePtr;

    FastSnapshotInfo 			*m_snapshotInfo;
	void						*m_lastDecodedInfo;

	UINT32						m_skipTemplateId[8];
	int							m_skipTemplateIdCount;
	FastObjectsAllocationInfo	*m_allocationInfo;

#pragma region String_Constant_Declaration_GeneratedCode
public:
	char	MessageEncodingConstString[6];
	const UINT	MessageEncodingConstStringLength = 5;
private:

	void InitializeConstantStrings() {
		sprintf(MessageEncodingConstString, "UTF-8");
	}
#pragma endregion

#pragma region Structure_Objects_Declaration_GeneratedCode
	AutoAllocatePointerList<FastLogonInfo>	*m_logon;
	AutoAllocatePointerList<FastLogoutInfo>	*m_logout;
	AutoAllocatePointerList<FastGenericItemInfo>	*m_genericItems;
	AutoAllocatePointerList<FastGenericInfo>	*m_generic;
	AutoAllocatePointerList<FastIncrementalGenericInfo>	*m_incrementalGeneric;
	AutoAllocatePointerList<FastOLSFONDItemInfo>	*m_oLSFONDItems;
	AutoAllocatePointerList<FastOLSFONDInfo>	*m_oLSFOND;
	AutoAllocatePointerList<FastOLSCURRItemInfo>	*m_oLSCURRItems;
	AutoAllocatePointerList<FastOLSCURRInfo>	*m_oLSCURR;
	AutoAllocatePointerList<FastTLSFONDItemInfo>	*m_tLSFONDItems;
	AutoAllocatePointerList<FastTLSFONDInfo>	*m_tLSFOND;
	AutoAllocatePointerList<FastTLSCURRItemInfo>	*m_tLSCURRItems;
	AutoAllocatePointerList<FastTLSCURRInfo>	*m_tLSCURR;
	AutoAllocatePointerList<FastIncrementalMSRFONDInfo>	*m_incrementalMSRFOND;
	AutoAllocatePointerList<FastIncrementalMSRCURRInfo>	*m_incrementalMSRCURR;
	AutoAllocatePointerList<FastIncrementalOLRFONDInfo>	*m_incrementalOLRFOND;
	AutoAllocatePointerList<FastIncrementalOLRCURRInfo>	*m_incrementalOLRCURR;
	AutoAllocatePointerList<FastIncrementalTLRFONDInfo>	*m_incrementalTLRFOND;
	AutoAllocatePointerList<FastIncrementalTLRCURRInfo>	*m_incrementalTLRCURR;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>	*m_securityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>	*m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>	*m_securityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionInfo>	*m_securityDefinition;
	AutoAllocatePointerList<FastSecurityStatusInfo>	*m_securityStatus;
	AutoAllocatePointerList<FastTradingSessionStatusInfo>	*m_tradingSessionStatus;
	AutoAllocatePointerList<FastHeartbeatInfo>	*m_heartbeat;
	FastLogonInfo	*m_prevLogonInfo;
	FastLogoutInfo	*m_prevLogoutInfo;
	FastGenericItemInfo	*m_prevGenericItemInfo;
	FastGenericInfo	*m_prevGenericInfo;
	FastIncrementalGenericInfo	*m_prevIncrementalGenericInfo;
	FastOLSFONDItemInfo	*m_prevOLSFONDItemInfo;
	FastOLSFONDInfo	*m_prevOLSFONDInfo;
	FastOLSCURRItemInfo	*m_prevOLSCURRItemInfo;
	FastOLSCURRInfo	*m_prevOLSCURRInfo;
	FastTLSFONDItemInfo	*m_prevTLSFONDItemInfo;
	FastTLSFONDInfo	*m_prevTLSFONDInfo;
	FastTLSCURRItemInfo	*m_prevTLSCURRItemInfo;
	FastTLSCURRInfo	*m_prevTLSCURRInfo;
	FastIncrementalMSRFONDInfo	*m_prevIncrementalMSRFONDInfo;
	FastIncrementalMSRCURRInfo	*m_prevIncrementalMSRCURRInfo;
	FastIncrementalOLRFONDInfo	*m_prevIncrementalOLRFONDInfo;
	FastIncrementalOLRCURRInfo	*m_prevIncrementalOLRCURRInfo;
	FastIncrementalTLRFONDInfo	*m_prevIncrementalTLRFONDInfo;
	FastIncrementalTLRCURRInfo	*m_prevIncrementalTLRCURRInfo;
	FastSecurityDefinitionGroupInstrAttribItemInfo	*m_prevSecurityDefinitionGroupInstrAttribItemInfo;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo	*m_prevSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;
	FastSecurityDefinitionMarketSegmentGrpItemInfo	*m_prevSecurityDefinitionMarketSegmentGrpItemInfo;
	FastSecurityDefinitionInfo	*m_prevSecurityDefinitionInfo;
	FastSecurityStatusInfo	*m_prevSecurityStatusInfo;
	FastTradingSessionStatusInfo	*m_prevTradingSessionStatusInfo;
	FastHeartbeatInfo	*m_prevHeartbeatInfo;

	void InitializeMessageInfo() {
		this->m_logon = new AutoAllocatePointerList<FastLogonInfo>(this->m_allocationInfo->m_logonCount, this->m_allocationInfo->m_logonAddCount, "FastLogonInfo");
		this->m_logout = new AutoAllocatePointerList<FastLogoutInfo>(this->m_allocationInfo->m_logoutCount, this->m_allocationInfo->m_logoutAddCount, "FastLogoutInfo");
		this->m_genericItems = new AutoAllocatePointerList<FastGenericItemInfo>(this->m_allocationInfo->m_genericItemsCount, this->m_allocationInfo->m_genericItemsAddCount, "FastGenericItemInfo");
		this->m_generic = new AutoAllocatePointerList<FastGenericInfo>(this->m_allocationInfo->m_genericCount, this->m_allocationInfo->m_genericAddCount, "FastGenericInfo");
		this->m_incrementalGeneric = new AutoAllocatePointerList<FastIncrementalGenericInfo>(this->m_allocationInfo->m_incrementalGenericCount, this->m_allocationInfo->m_incrementalGenericAddCount, "FastIncrementalGenericInfo");
		this->m_oLSFONDItems = new AutoAllocatePointerList<FastOLSFONDItemInfo>(this->m_allocationInfo->m_oLSFONDItemsCount, this->m_allocationInfo->m_oLSFONDItemsAddCount, "FastOLSFONDItemInfo");
		this->m_oLSFOND = new AutoAllocatePointerList<FastOLSFONDInfo>(this->m_allocationInfo->m_oLSFONDCount, this->m_allocationInfo->m_oLSFONDAddCount, "FastOLSFONDInfo");
		this->m_oLSCURRItems = new AutoAllocatePointerList<FastOLSCURRItemInfo>(this->m_allocationInfo->m_oLSCURRItemsCount, this->m_allocationInfo->m_oLSCURRItemsAddCount, "FastOLSCURRItemInfo");
		this->m_oLSCURR = new AutoAllocatePointerList<FastOLSCURRInfo>(this->m_allocationInfo->m_oLSCURRCount, this->m_allocationInfo->m_oLSCURRAddCount, "FastOLSCURRInfo");
		this->m_tLSFONDItems = new AutoAllocatePointerList<FastTLSFONDItemInfo>(this->m_allocationInfo->m_tLSFONDItemsCount, this->m_allocationInfo->m_tLSFONDItemsAddCount, "FastTLSFONDItemInfo");
		this->m_tLSFOND = new AutoAllocatePointerList<FastTLSFONDInfo>(this->m_allocationInfo->m_tLSFONDCount, this->m_allocationInfo->m_tLSFONDAddCount, "FastTLSFONDInfo");
		this->m_tLSCURRItems = new AutoAllocatePointerList<FastTLSCURRItemInfo>(this->m_allocationInfo->m_tLSCURRItemsCount, this->m_allocationInfo->m_tLSCURRItemsAddCount, "FastTLSCURRItemInfo");
		this->m_tLSCURR = new AutoAllocatePointerList<FastTLSCURRInfo>(this->m_allocationInfo->m_tLSCURRCount, this->m_allocationInfo->m_tLSCURRAddCount, "FastTLSCURRInfo");
		this->m_incrementalMSRFOND = new AutoAllocatePointerList<FastIncrementalMSRFONDInfo>(this->m_allocationInfo->m_incrementalMSRFONDCount, this->m_allocationInfo->m_incrementalMSRFONDAddCount, "FastIncrementalMSRFONDInfo");
		this->m_incrementalMSRCURR = new AutoAllocatePointerList<FastIncrementalMSRCURRInfo>(this->m_allocationInfo->m_incrementalMSRCURRCount, this->m_allocationInfo->m_incrementalMSRCURRAddCount, "FastIncrementalMSRCURRInfo");
		this->m_incrementalOLRFOND = new AutoAllocatePointerList<FastIncrementalOLRFONDInfo>(this->m_allocationInfo->m_incrementalOLRFONDCount, this->m_allocationInfo->m_incrementalOLRFONDAddCount, "FastIncrementalOLRFONDInfo");
		this->m_incrementalOLRCURR = new AutoAllocatePointerList<FastIncrementalOLRCURRInfo>(this->m_allocationInfo->m_incrementalOLRCURRCount, this->m_allocationInfo->m_incrementalOLRCURRAddCount, "FastIncrementalOLRCURRInfo");
		this->m_incrementalTLRFOND = new AutoAllocatePointerList<FastIncrementalTLRFONDInfo>(this->m_allocationInfo->m_incrementalTLRFONDCount, this->m_allocationInfo->m_incrementalTLRFONDAddCount, "FastIncrementalTLRFONDInfo");
		this->m_incrementalTLRCURR = new AutoAllocatePointerList<FastIncrementalTLRCURRInfo>(this->m_allocationInfo->m_incrementalTLRCURRCount, this->m_allocationInfo->m_incrementalTLRCURRAddCount, "FastIncrementalTLRCURRInfo");
		this->m_securityDefinitionGroupInstrAttribItems = new AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>(this->m_allocationInfo->m_securityDefinitionGroupInstrAttribItemsCount, this->m_allocationInfo->m_securityDefinitionGroupInstrAttribItemsAddCount, "FastSecurityDefinitionGroupInstrAttribItemInfo");
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(this->m_allocationInfo->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCount, this->m_allocationInfo->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsAddCount, "FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo");
		this->m_securityDefinitionMarketSegmentGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>(this->m_allocationInfo->m_securityDefinitionMarketSegmentGrpItemsCount, this->m_allocationInfo->m_securityDefinitionMarketSegmentGrpItemsAddCount, "FastSecurityDefinitionMarketSegmentGrpItemInfo");
		this->m_securityDefinition = new AutoAllocatePointerList<FastSecurityDefinitionInfo>(this->m_allocationInfo->m_securityDefinitionCount, this->m_allocationInfo->m_securityDefinitionAddCount, "FastSecurityDefinitionInfo");
		this->m_securityStatus = new AutoAllocatePointerList<FastSecurityStatusInfo>(this->m_allocationInfo->m_securityStatusCount, this->m_allocationInfo->m_securityStatusAddCount, "FastSecurityStatusInfo");
		this->m_tradingSessionStatus = new AutoAllocatePointerList<FastTradingSessionStatusInfo>(this->m_allocationInfo->m_tradingSessionStatusCount, this->m_allocationInfo->m_tradingSessionStatusAddCount, "FastTradingSessionStatusInfo");
		this->m_heartbeat = new AutoAllocatePointerList<FastHeartbeatInfo>(this->m_allocationInfo->m_heartbeatCount, this->m_allocationInfo->m_heartbeatAddCount, "FastHeartbeatInfo");
		this->m_prevLogonInfo = this->GetFreeLogonInfo();
		this->m_prevLogonInfo->Used = true;
		this->m_prevLogoutInfo = this->GetFreeLogoutInfo();
		this->m_prevLogoutInfo->Used = true;
		this->m_prevGenericItemInfo = this->GetFreeGenericItemInfo();
		this->m_prevGenericItemInfo->Used = true;
		this->m_prevGenericInfo = this->GetFreeGenericInfo();
		this->m_prevGenericInfo->Used = true;
		this->m_prevIncrementalGenericInfo = this->GetFreeIncrementalGenericInfo();
		this->m_prevIncrementalGenericInfo->Used = true;
		this->m_prevOLSFONDItemInfo = this->GetFreeOLSFONDItemInfo();
		this->m_prevOLSFONDItemInfo->Used = true;
		this->m_prevOLSFONDInfo = this->GetFreeOLSFONDInfo();
		this->m_prevOLSFONDInfo->Used = true;
		this->m_prevOLSCURRItemInfo = this->GetFreeOLSCURRItemInfo();
		this->m_prevOLSCURRItemInfo->Used = true;
		this->m_prevOLSCURRInfo = this->GetFreeOLSCURRInfo();
		this->m_prevOLSCURRInfo->Used = true;
		this->m_prevTLSFONDItemInfo = this->GetFreeTLSFONDItemInfo();
		this->m_prevTLSFONDItemInfo->Used = true;
		this->m_prevTLSFONDInfo = this->GetFreeTLSFONDInfo();
		this->m_prevTLSFONDInfo->Used = true;
		this->m_prevTLSCURRItemInfo = this->GetFreeTLSCURRItemInfo();
		this->m_prevTLSCURRItemInfo->Used = true;
		this->m_prevTLSCURRInfo = this->GetFreeTLSCURRInfo();
		this->m_prevTLSCURRInfo->Used = true;
		this->m_prevIncrementalMSRFONDInfo = this->GetFreeIncrementalMSRFONDInfo();
		this->m_prevIncrementalMSRFONDInfo->Used = true;
		this->m_prevIncrementalMSRCURRInfo = this->GetFreeIncrementalMSRCURRInfo();
		this->m_prevIncrementalMSRCURRInfo->Used = true;
		this->m_prevIncrementalOLRFONDInfo = this->GetFreeIncrementalOLRFONDInfo();
		this->m_prevIncrementalOLRFONDInfo->Used = true;
		this->m_prevIncrementalOLRCURRInfo = this->GetFreeIncrementalOLRCURRInfo();
		this->m_prevIncrementalOLRCURRInfo->Used = true;
		this->m_prevIncrementalTLRFONDInfo = this->GetFreeIncrementalTLRFONDInfo();
		this->m_prevIncrementalTLRFONDInfo->Used = true;
		this->m_prevIncrementalTLRCURRInfo = this->GetFreeIncrementalTLRCURRInfo();
		this->m_prevIncrementalTLRCURRInfo->Used = true;
		this->m_prevSecurityDefinitionGroupInstrAttribItemInfo = this->GetFreeSecurityDefinitionGroupInstrAttribItemInfo();
		this->m_prevSecurityDefinitionGroupInstrAttribItemInfo->Used = true;
		this->m_prevSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = this->GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
		this->m_prevSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo->Used = true;
		this->m_prevSecurityDefinitionMarketSegmentGrpItemInfo = this->GetFreeSecurityDefinitionMarketSegmentGrpItemInfo();
		this->m_prevSecurityDefinitionMarketSegmentGrpItemInfo->Used = true;
		this->m_prevSecurityDefinitionInfo = this->GetFreeSecurityDefinitionInfo();
		this->m_prevSecurityDefinitionInfo->Used = true;
		this->m_prevSecurityStatusInfo = this->GetFreeSecurityStatusInfo();
		this->m_prevSecurityStatusInfo->Used = true;
		this->m_prevTradingSessionStatusInfo = this->GetFreeTradingSessionStatusInfo();
		this->m_prevTradingSessionStatusInfo->Used = true;
		this->m_prevHeartbeatInfo = this->GetFreeHeartbeatInfo();
		this->m_prevHeartbeatInfo->Used = true;
	}

#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
	FastDecodeMethodPointer* DecodeMethods;
	FastReleaseMethodPointer* ReleaseMethods;
	FastGetSnapshotInfoMethodPointer* GetSnapshotInfoMethods;

	void InitializeDecodeMethodPointers() {
		int ptCount = 1513;
		this->DecodeMethods = new FastDecodeMethodPointer[ptCount];
		this->ReleaseMethods = new FastReleaseMethodPointer[ptCount];
		this->GetSnapshotInfoMethods = new FastGetSnapshotInfoMethodPointer[ptCount];

		for(int i = 0; i < 1513; i++) {
			this->DecodeMethods[i] = &FastProtocolManager::DecodeUnsupportedMessage;
			this->GetSnapshotInfoMethods[i] = &FastProtocolManager::GetSnapshotInfoUnsupported;
		}

		this->DecodeMethods[2101 - 2101] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods[2102 - 2101] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods[2103 - 2101] = &FastProtocolManager::DecodeGeneric;
		this->DecodeMethods[2104 - 2101] = &FastProtocolManager::DecodeIncrementalGeneric;
		this->DecodeMethods[2510 - 2101] = &FastProtocolManager::DecodeOLSFOND;
		this->DecodeMethods[3600 - 2101] = &FastProtocolManager::DecodeOLSCURR;
		this->DecodeMethods[2511 - 2101] = &FastProtocolManager::DecodeTLSFOND;
		this->DecodeMethods[3601 - 2101] = &FastProtocolManager::DecodeTLSCURR;
		this->DecodeMethods[2523 - 2101] = &FastProtocolManager::DecodeIncrementalMSRFOND;
		this->DecodeMethods[3613 - 2101] = &FastProtocolManager::DecodeIncrementalMSRCURR;
		this->DecodeMethods[2520 - 2101] = &FastProtocolManager::DecodeIncrementalOLRFOND;
		this->DecodeMethods[3610 - 2101] = &FastProtocolManager::DecodeIncrementalOLRCURR;
		this->DecodeMethods[2521 - 2101] = &FastProtocolManager::DecodeIncrementalTLRFOND;
		this->DecodeMethods[3611 - 2101] = &FastProtocolManager::DecodeIncrementalTLRCURR;
		this->DecodeMethods[2115 - 2101] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods[2106 - 2101] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods[2107 - 2101] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods[2108 - 2101] = &FastProtocolManager::DecodeHeartbeat;
		this->ReleaseMethods[2101 - 2101] = &FastProtocolManager::DecodeLogon;
		this->ReleaseMethods[2102 - 2101] = &FastProtocolManager::DecodeLogout;
		this->ReleaseMethods[2103 - 2101] = &FastProtocolManager::DecodeGeneric;
		this->ReleaseMethods[2104 - 2101] = &FastProtocolManager::DecodeIncrementalGeneric;
		this->ReleaseMethods[2510 - 2101] = &FastProtocolManager::DecodeOLSFOND;
		this->ReleaseMethods[3600 - 2101] = &FastProtocolManager::DecodeOLSCURR;
		this->ReleaseMethods[2511 - 2101] = &FastProtocolManager::DecodeTLSFOND;
		this->ReleaseMethods[3601 - 2101] = &FastProtocolManager::DecodeTLSCURR;
		this->ReleaseMethods[2523 - 2101] = &FastProtocolManager::DecodeIncrementalMSRFOND;
		this->ReleaseMethods[3613 - 2101] = &FastProtocolManager::DecodeIncrementalMSRCURR;
		this->ReleaseMethods[2520 - 2101] = &FastProtocolManager::DecodeIncrementalOLRFOND;
		this->ReleaseMethods[3610 - 2101] = &FastProtocolManager::DecodeIncrementalOLRCURR;
		this->ReleaseMethods[2521 - 2101] = &FastProtocolManager::DecodeIncrementalTLRFOND;
		this->ReleaseMethods[3611 - 2101] = &FastProtocolManager::DecodeIncrementalTLRCURR;
		this->ReleaseMethods[2115 - 2101] = &FastProtocolManager::DecodeSecurityDefinition;
		this->ReleaseMethods[2106 - 2101] = &FastProtocolManager::DecodeSecurityStatus;
		this->ReleaseMethods[2107 - 2101] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->ReleaseMethods[2108 - 2101] = &FastProtocolManager::DecodeHeartbeat;
		this->GetSnapshotInfoMethods[2103 - 2101] = &FastProtocolManager::GetSnapshotInfoGeneric;
		this->GetSnapshotInfoMethods[2510 - 2101] = &FastProtocolManager::GetSnapshotInfoOLSFOND;
		this->GetSnapshotInfoMethods[3600 - 2101] = &FastProtocolManager::GetSnapshotInfoOLSCURR;
		this->GetSnapshotInfoMethods[2511 - 2101] = &FastProtocolManager::GetSnapshotInfoTLSFOND;
		this->GetSnapshotInfoMethods[3601 - 2101] = &FastProtocolManager::GetSnapshotInfoTLSCURR;

	}

#pragma endregion

    inline FastSnapshotInfo* GetFreeSnapshotInfo() {
        this->m_snapshotInfo->LastFragment = 0;
        this->m_snapshotInfo->LastMsgSeqNumProcessed = -1;
        this->m_snapshotInfo->RouteFirst = 0;
        this->m_snapshotInfo->RptSeq = -1;
        return this->m_snapshotInfo;
    }

#pragma region Get_Free_Item_Methods_GeneratedCode
public:
	inline FastLogonInfo* GetFreeLogonInfo() {
		return this->m_logon->NewItem();
	}

	inline AutoAllocatePointerList<FastLogonInfo>* GetLogonInfoPool() {
		return this->m_logon;
	}

	inline FastLogoutInfo* GetFreeLogoutInfo() {
		return this->m_logout->NewItem();
	}

	inline AutoAllocatePointerList<FastLogoutInfo>* GetLogoutInfoPool() {
		return this->m_logout;
	}

	inline FastGenericItemInfo* GetFreeGenericItemInfo() {
		return this->m_genericItems->NewItem();
	}

	inline AutoAllocatePointerList<FastGenericItemInfo>* GetGenericItemInfoPool() {
		return this->m_genericItems;
	}

	inline FastGenericInfo* GetFreeGenericInfo() {
		return this->m_generic->NewItem();
	}

	inline AutoAllocatePointerList<FastGenericInfo>* GetGenericInfoPool() {
		return this->m_generic;
	}

	inline FastIncrementalGenericInfo* GetFreeIncrementalGenericInfo() {
		return this->m_incrementalGeneric->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalGenericInfo>* GetIncrementalGenericInfoPool() {
		return this->m_incrementalGeneric;
	}

	inline FastOLSFONDItemInfo* GetFreeOLSFONDItemInfo() {
		return this->m_oLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSFONDItemInfo>* GetOLSFONDItemInfoPool() {
		return this->m_oLSFONDItems;
	}

	inline FastOLSFONDInfo* GetFreeOLSFONDInfo() {
		return this->m_oLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSFONDInfo>* GetOLSFONDInfoPool() {
		return this->m_oLSFOND;
	}

	inline FastOLSCURRItemInfo* GetFreeOLSCURRItemInfo() {
		return this->m_oLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSCURRItemInfo>* GetOLSCURRItemInfoPool() {
		return this->m_oLSCURRItems;
	}

	inline FastOLSCURRInfo* GetFreeOLSCURRInfo() {
		return this->m_oLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSCURRInfo>* GetOLSCURRInfoPool() {
		return this->m_oLSCURR;
	}

	inline FastTLSFONDItemInfo* GetFreeTLSFONDItemInfo() {
		return this->m_tLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSFONDItemInfo>* GetTLSFONDItemInfoPool() {
		return this->m_tLSFONDItems;
	}

	inline FastTLSFONDInfo* GetFreeTLSFONDInfo() {
		return this->m_tLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSFONDInfo>* GetTLSFONDInfoPool() {
		return this->m_tLSFOND;
	}

	inline FastTLSCURRItemInfo* GetFreeTLSCURRItemInfo() {
		return this->m_tLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSCURRItemInfo>* GetTLSCURRItemInfoPool() {
		return this->m_tLSCURRItems;
	}

	inline FastTLSCURRInfo* GetFreeTLSCURRInfo() {
		return this->m_tLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSCURRInfo>* GetTLSCURRInfoPool() {
		return this->m_tLSCURR;
	}

	inline FastIncrementalMSRFONDInfo* GetFreeIncrementalMSRFONDInfo() {
		return this->m_incrementalMSRFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalMSRFONDInfo>* GetIncrementalMSRFONDInfoPool() {
		return this->m_incrementalMSRFOND;
	}

	inline FastIncrementalMSRCURRInfo* GetFreeIncrementalMSRCURRInfo() {
		return this->m_incrementalMSRCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalMSRCURRInfo>* GetIncrementalMSRCURRInfoPool() {
		return this->m_incrementalMSRCURR;
	}

	inline FastIncrementalOLRFONDInfo* GetFreeIncrementalOLRFONDInfo() {
		return this->m_incrementalOLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalOLRFONDInfo>* GetIncrementalOLRFONDInfoPool() {
		return this->m_incrementalOLRFOND;
	}

	inline FastIncrementalOLRCURRInfo* GetFreeIncrementalOLRCURRInfo() {
		return this->m_incrementalOLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalOLRCURRInfo>* GetIncrementalOLRCURRInfoPool() {
		return this->m_incrementalOLRCURR;
	}

	inline FastIncrementalTLRFONDInfo* GetFreeIncrementalTLRFONDInfo() {
		return this->m_incrementalTLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalTLRFONDInfo>* GetIncrementalTLRFONDInfoPool() {
		return this->m_incrementalTLRFOND;
	}

	inline FastIncrementalTLRCURRInfo* GetFreeIncrementalTLRCURRInfo() {
		return this->m_incrementalTLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalTLRCURRInfo>* GetIncrementalTLRCURRInfoPool() {
		return this->m_incrementalTLRCURR;
	}

	inline FastSecurityDefinitionGroupInstrAttribItemInfo* GetFreeSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_securityDefinitionGroupInstrAttribItems->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>* GetSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_securityDefinitionGroupInstrAttribItems;
	}

	inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}

	inline FastSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_securityDefinitionMarketSegmentGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>* GetSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_securityDefinitionMarketSegmentGrpItems;
	}

	inline FastSecurityDefinitionInfo* GetFreeSecurityDefinitionInfo() {
		return this->m_securityDefinition->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionInfo>* GetSecurityDefinitionInfoPool() {
		return this->m_securityDefinition;
	}

	inline FastSecurityStatusInfo* GetFreeSecurityStatusInfo() {
		return this->m_securityStatus->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityStatusInfo>* GetSecurityStatusInfoPool() {
		return this->m_securityStatus;
	}

	inline FastTradingSessionStatusInfo* GetFreeTradingSessionStatusInfo() {
		return this->m_tradingSessionStatus->NewItem();
	}

	inline AutoAllocatePointerList<FastTradingSessionStatusInfo>* GetTradingSessionStatusInfoPool() {
		return this->m_tradingSessionStatus;
	}

	inline FastHeartbeatInfo* GetFreeHeartbeatInfo() {
		return this->m_heartbeat->NewItem();
	}

	inline AutoAllocatePointerList<FastHeartbeatInfo>* GetHeartbeatInfoPool() {
		return this->m_heartbeat;
	}

private:
	void ReleaseLogonInfo() {
		((FastLogonInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseLogoutInfo() {
		((FastLogoutInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseGenericItemInfo() {
		((FastGenericItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseGenericInfo() {
		((FastGenericInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalGenericInfo() {
		((FastIncrementalGenericInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseOLSFONDItemInfo() {
		((FastOLSFONDItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseOLSFONDInfo() {
		((FastOLSFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseOLSCURRItemInfo() {
		((FastOLSCURRItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseOLSCURRInfo() {
		((FastOLSCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseTLSFONDItemInfo() {
		((FastTLSFONDItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseTLSFONDInfo() {
		((FastTLSFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseTLSCURRItemInfo() {
		((FastTLSCURRItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseTLSCURRInfo() {
		((FastTLSCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalMSRFONDInfo() {
		((FastIncrementalMSRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalMSRCURRInfo() {
		((FastIncrementalMSRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalOLRFONDInfo() {
		((FastIncrementalOLRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalOLRCURRInfo() {
		((FastIncrementalOLRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalTLRFONDInfo() {
		((FastIncrementalTLRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseIncrementalTLRCURRInfo() {
		((FastIncrementalTLRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSecurityDefinitionGroupInstrAttribItemInfo() {
		((FastSecurityDefinitionGroupInstrAttribItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		((FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSecurityDefinitionMarketSegmentGrpItemInfo() {
		((FastSecurityDefinitionMarketSegmentGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSecurityDefinitionInfo() {
		((FastSecurityDefinitionInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSecurityStatusInfo() {
		((FastSecurityStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseTradingSessionStatusInfo() {
		((FastTradingSessionStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseHeartbeatInfo() {
		((FastHeartbeatInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	inline void Reset() {
		FastReleaseMethodPointer funcPtr = this->ReleaseMethods[this->m_templateId - 2101];
		(this->*funcPtr)();
	}
#pragma endregion

public:

	inline void SkipTemplateId(UINT32 templateId) {
		this->m_skipTemplateId[this->m_skipTemplateIdCount] = templateId;
		this->m_skipTemplateIdCount++;
	}

	inline bool ShouldSkipTemplate() {
		for (int i = 1; i < this->m_skipTemplateIdCount; i++) {
			if (this->m_skipTemplateId[i] == this->m_templateId)
				return true;
		}
		return false;
	}

	inline void* LastDecodeInfo() { return this->m_lastDecodedInfo; }
	inline void LastDecodeInfo(void *info) { this->m_lastDecodedInfo = info; }

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


    inline void WritePresenceMap1(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos++;
    }

    inline void WritePresenceMap2(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=2;
    }

    inline void WritePresenceMap3(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=3;
    }

    inline void WritePresenceMap4(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=4;
    }

	inline void WritePresenceMap5(UINT64 map) {
		*((UINT64*)this->currentPos) = map;
		this->currentPos+=5;
	}

	inline void WritePresenceMap6(UINT64 map) {
		*((UINT64*)this->currentPos) = map;
		this->currentPos+=6;
	}

	inline void WritePresenceMap7(UINT64 map) {
		*((UINT64*)this->currentPos) = map;
		this->currentPos+=7;
	}

	inline void WritePresenceMap8(UINT64 map) {
		*((UINT64*)this->currentPos) = map;
		this->currentPos+=8;
	}

	inline void WritePresenceMap(UINT64 map) {
		if(map < 0x0000000080000000) {
			if(map < 0x00008000) {
				if(map < 0x80) {
					map |= 0x80;
					WritePresenceMap1(map);
				}
				else {
					map |= 0x8000;
					WritePresenceMap2(map);
				}
			}
			else {
				if(map < 0x800000) {
					map |= 0x800000;
					WritePresenceMap3(map);
				}
				else {
					map |= 0x80000000;
					WritePresenceMap4(map);
				}
			}
		}
		else {
			if(map < 0x0000800000000000) {
				if(map < 0x0000008000000000) {
					map |= 0x0000008000000000;
					WritePresenceMap5(map);
				}
				else {
					map |= 0x0000800000000000;
					WritePresenceMap6(map);
				}
			}
			else {
				if(map < 0x0080000000000000) {
					map |= 0x0080000000000000;
					WritePresenceMap7(map);
				}
				else {
					map |= 0x8000000000000000;
					WritePresenceMap8(map);
				}
			}
		}
	}

	inline int ReadMsgSeqNumber() {
		int result = *(int*)this->currentPos;
		this->currentPos += 4;
		return result;
	}

    inline UINT TemplateId() { return this->m_templateId; }
    inline UINT64 PresenceMap() { return this->m_presenceMap; }

	inline bool IsNull() {  return *(this->currentPos) == 0x80; }

    void PrintTabs(int tabCount);
    void PrintPresenceMap(UINT64 map, int count, int tabsCount);
    void PrintXmlPresenceMap(UINT64 map, int count);
    void PrintXmlInt32(const char *name, int value);
    void PrintXmlUInt32(const char *name, UINT value);
    void PrintXmlInt64(const char *name, INT64 value);
    void PrintXmlUInt64(const char *name, UINT64 value);
    void PrintXmlItemBegin(const char *name);
    void PrintXmlItemEnd(const char *name);
    void PrintXmlItemBegin(const char *name, int index);
    void PrintXmlItemEnd(const char *name, int index);
    void PrintXmlString(const char *name, char *str, int count);
    void PrintXmlByteVector(const char *name, unsigned char *data, int count);
    void PrintXmlDecimal(const char *name, Decimal *value);
    bool BeginExportXml(const char *fileName);
    void EndExportXml();
    void PrintInt32(const char *name, int value, int tabCount);
    void PrintUInt32(const char *name, UINT value, int tabCount);
    void PrintInt64(const char *name, INT64 value, int tabCount);
    void PrintUInt64(const char *name, UINT64 value, int tabCount);
    void PrintItemBegin(const char *name, int index, int tabsCount);
    void PrintItemEnd(int tabsCount);
    void PrintString(const char *name, char *str, int count, int tabCount);
    void PrintByteVector(const char *name, unsigned char *data, int count, int tabCount);
    void PrintDecimal(const char *name, Decimal *value, int tabCount);

    inline void WriteNullString() {
        *(this->currentPos) = 0x00;
        *(this->currentPos + 1) = 0x80;
        this->currentPos += 2;
    }

    inline void WriteNull() {
        *(this->currentPos) = 0x80;
        this->currentPos++;
    }

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
	inline bool CheckProcessNullUInt64() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullString() {
		WORD str = *((WORD*)this->currentPos);
		//if (str == 0x0000)
		//	return false;
        if(str == 0x8000) {
            this->currentPos+=2;
            return true;
        }
		/*
		if ((str & 0xFF) == 0x00) {
			this->currentPos++;
			return true;
		}*/
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
        value->Exponent = ReadInt32_Optional();
        value->Mantissa = ReadInt64_Mandatory();
	}

	inline void ReadDecimal_Mandatory(Decimal *value) {
        value->Exponent = ReadInt32_Mandatory();
        value->Mantissa = ReadInt64_Mandatory();
	}

	inline void WriteDecimal_Optional(Decimal *value) { 
		WriteInt32_Optional(value->Exponent);
		WriteInt64_Mandatory(value->Mantissa);
		return;
	}

	inline void WriteDecimal_Mandatory(Decimal *value) {
		WriteInt32_Mandatory(value->Exponent);
		WriteInt64_Mandatory(value->Mantissa);
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

    inline void WriteString_Optional(const char *str, int length) {
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

    inline void WriteString_Mandatory(const char *str, int length) {
        if (length == 0) {
            *((int*)this->currentPos) = 0x80;
            this->currentPos ++;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }

    inline void SkipToNextField() {
        UINT64 memory = *((UINT64*)this->currentPos);
        while (true) {
            if ((memory & 0x8080808080808080) != 0) {
                if ((memory & 0x0000000080808080) != 0) {
                    if ((memory & 0x8080) != 0) {
                        if ((memory & 0x80) != 0) {
                            this->currentPos++;
                            break;
                        }
                        else {
                            this->currentPos += 2;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x800000) != 0) {
                            this->currentPos += 3;
                            break;
                        }
                        else {
                            this->currentPos += 4;
                            break;
                        }
                    }
                }
                else {
                    if ((memory & 0x0000808000000000) != 0) {
                        if ((memory & 0x0000008000000000) != 0) {
                            this->currentPos += 5;
                            break;
                        }
                        else {
                            this->currentPos += 6;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x0080000000000000) != 0) {
                            this->currentPos += 7;
                            break;
                        }
                        else {
                            this->currentPos += 8;
                            break;
                        }
                    }
                }
            }
            this->currentPos += 8;
            memory = *((UINT64*)this->currentPos);
        }
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

	inline void ParsePresenceMap(UINT64 *map) {
		UINT64 value = *((UINT*)this->currentPos);
		if((value & FAST_STOPBIT_FIRST_BYTE) != 0) {
			value &= 0x000000000000007f;
            *map = value;
			this->currentPos++;
			return;
		}
		if((value & FAST_STOPBIT_SECOND_BYTE) != 0) {
            value &= 0x0000000000007f7f;
            *map = value;
			this->currentPos += 2;
			return;
		}
		if((value & FAST_STOPBIT_THIRD_BYTE) != 0) {
            value &= 0x00000000007f7f7f;
            *map = value;
			this->currentPos += 3;
			return;
		}
        if((value & FAST_STOPBIT_FORTH_BYTE) != 0) {
            value &= 0x000000007f7f7f7f;
            *map = value;
            this->currentPos += 4;
            return;
        }
        if((value & FAST_STOPBIT_FIFTH_BYTE) != 0) {
            value &= 0x0000007f7f7f7f7f;
            *map = value;
            this->currentPos += 5;
            return;
        }
        if((value & FAST_STOPBIT_SIXSTH_BYTE) != 0) {
            value &= 0x00007f7f7f7f7f7f;
            *map = value;
            this->currentPos += 6;
            return;
        }
        if((value & FAST_STOPBIT_SEVENTH_BYTE) != 0) {
            value &= 0x007f7f7f7f7f7f7f;
            *map = value;
            this->currentPos += 7;
            return;
        }
        value &= 0x7f7f7f7f7f7f7f7f;
		*map = value;
		this->currentPos += 8;
		return;
	}

	FastProtocolManager(FastObjectsAllocationInfo *allocInfo);
	~FastProtocolManager();

	inline BYTE* Buffer() { return this->buffer; }
	inline BYTE* CurrentPos() { return this->currentPos; }
	inline int BufferLength() { return this->bufferLength; }
	inline int MessageLength() { return this->currentPos - this->buffer; }
	inline void SetBufferLength(int value) { this->bufferLength = value; }

    void* DecodeUnsupportedMessage() {
        return NULL;
    }

	FastSnapshotInfo* GetSnapshotInfoUnsupported() {
		return 0;
	}

#pragma region Encode_Methods_Declaration_GeneratedCode
	void EncodeLogonInfo(FastLogonInfo* info);
	void EncodeLogoutInfo(FastLogoutInfo* info);
	void EncodeGenericInfo(FastGenericInfo* info);
	void EncodeIncrementalGenericInfo(FastIncrementalGenericInfo* info);
	void EncodeOLSFONDInfo(FastOLSFONDInfo* info);
	void EncodeOLSCURRInfo(FastOLSCURRInfo* info);
	void EncodeTLSFONDInfo(FastTLSFONDInfo* info);
	void EncodeTLSCURRInfo(FastTLSCURRInfo* info);
	void EncodeIncrementalMSRFONDInfo(FastIncrementalMSRFONDInfo* info);
	void EncodeIncrementalMSRCURRInfo(FastIncrementalMSRCURRInfo* info);
	void EncodeIncrementalOLRFONDInfo(FastIncrementalOLRFONDInfo* info);
	void EncodeIncrementalOLRCURRInfo(FastIncrementalOLRCURRInfo* info);
	void EncodeIncrementalTLRFONDInfo(FastIncrementalTLRFONDInfo* info);
	void EncodeIncrementalTLRCURRInfo(FastIncrementalTLRCURRInfo* info);
	void EncodeSecurityDefinitionInfo(FastSecurityDefinitionInfo* info);
	void EncodeSecurityStatusInfo(FastSecurityStatusInfo* info);
	void EncodeTradingSessionStatusInfo(FastTradingSessionStatusInfo* info);
	void EncodeHeartbeatInfo(FastHeartbeatInfo* info);
#pragma endregion

#pragma region Print_Methods_Declaration_GeneratedCode
	void PrintLogon(FastLogonInfo *info);
	void PrintLogout(FastLogoutInfo *info);
	void PrintGeneric(FastGenericInfo *info);
	void PrintIncrementalGeneric(FastIncrementalGenericInfo *info);
	void PrintOLSFOND(FastOLSFONDInfo *info);
	void PrintOLSCURR(FastOLSCURRInfo *info);
	void PrintTLSFOND(FastTLSFONDInfo *info);
	void PrintTLSCURR(FastTLSCURRInfo *info);
	void PrintIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info);
	void PrintIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info);
	void PrintIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info);
	void PrintIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info);
	void PrintIncrementalTLRFOND(FastIncrementalTLRFONDInfo *info);
	void PrintIncrementalTLRCURR(FastIncrementalTLRCURRInfo *info);
	void PrintSecurityDefinition(FastSecurityDefinitionInfo *info);
	void PrintSecurityStatus(FastSecurityStatusInfo *info);
	void PrintTradingSessionStatus(FastTradingSessionStatusInfo *info);
	void PrintHeartbeat(FastHeartbeatInfo *info);
	void PrintXmlLogon(FastLogonInfo *info);
	void PrintXmlLogout(FastLogoutInfo *info);
	void PrintXmlGeneric(FastGenericInfo *info);
	void PrintXmlIncrementalGeneric(FastIncrementalGenericInfo *info);
	void PrintXmlOLSFOND(FastOLSFONDInfo *info);
	void PrintXmlOLSCURR(FastOLSCURRInfo *info);
	void PrintXmlTLSFOND(FastTLSFONDInfo *info);
	void PrintXmlTLSCURR(FastTLSCURRInfo *info);
	void PrintXmlIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info);
	void PrintXmlIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info);
	void PrintXmlIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info);
	void PrintXmlIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info);
	void PrintXmlIncrementalTLRFOND(FastIncrementalTLRFONDInfo *info);
	void PrintXmlIncrementalTLRCURR(FastIncrementalTLRCURRInfo *info);
	void PrintXmlSecurityDefinition(FastSecurityDefinitionInfo *info);
	void PrintXmlSecurityStatus(FastSecurityStatusInfo *info);
	void PrintXmlTradingSessionStatus(FastTradingSessionStatusInfo *info);
	void PrintXmlHeartbeat(FastHeartbeatInfo *info);
#pragma endregion

#pragma region Decode_Methods_Definition_GeneratedCode
	inline void DecodeHeader() {

		this->ParsePresenceMap(&(this->m_presenceMap));
		this->m_templateId = ReadUInt32_Mandatory();
	}

	int GetTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Optional();
	}
	void* DecodeLogon() {
		FastLogonInfo* info = GetFreeLogonInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->HeartBtInt = ReadInt32_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Username), &(info->UsernameLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Password), &(info->PasswordLength));
		else
			info->NullMap |= NULL_MAP_INDEX1;

		ReadString_Mandatory(&(info->DefaultApplVerID), &(info->DefaultApplVerIDLength));
		this->m_prevLogonInfo = info;
		return info;
	}
	void* DecodeLogout() {
		FastLogoutInfo* info = GetFreeLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		this->m_prevLogoutInfo = info;
		return info;
	}
	void* DecodeGeneric() {
		FastGenericInfo* info = GetFreeGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX4;

		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX5;

		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX6;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->NetChgPrevDay));
		else
			info->NullMap |= NULL_MAP_INDEX7;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX33;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX34;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX35;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX36;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX37;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX38;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX39;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX40;

			this->m_prevGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevGenericInfo = info;
		return info;
	}
	void* DecodeIncrementalGeneric() {
		FastIncrementalGenericInfo* info = GetFreeIncrementalGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX33;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX34;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX35;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX36;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX37;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX38;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX39;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX40;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX41;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX42;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX43;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX44;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX45;

			this->m_prevGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalGenericInfo = info;
		return info;
	}
	void* DecodeOLSFOND() {
		FastOLSFONDInfo* info = GetFreeOLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX5;

		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX6;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			}
			else {
				gmdeItemInfo->MDEntryType = this->m_prevOLSFONDItemInfo->MDEntryType;
				gmdeItemInfo->MDEntryTypeLength = this->m_prevOLSFONDItemInfo->MDEntryTypeLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			}
			else {
				gmdeItemInfo->Yield = this->m_prevOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			}
			else {
				gmdeItemInfo->OrderStatus = this->m_prevOLSFONDItemInfo->OrderStatus;
				gmdeItemInfo->OrderStatusLength = this->m_prevOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			}
			else {
				gmdeItemInfo->OrdType = this->m_prevOLSFONDItemInfo->OrdType;
				gmdeItemInfo->OrdTypeLength = this->m_prevOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			}
			else {
				gmdeItemInfo->TradingSessionSubID = this->m_prevOLSFONDItemInfo->TradingSessionSubID;
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevOLSFONDInfo = info;
		return info;
	}
	void* DecodeOLSCURR() {
		FastOLSCURRInfo* info = GetFreeOLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX5;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			}
			else {
				gmdeItemInfo->MDEntryType = this->m_prevOLSCURRItemInfo->MDEntryType;
				gmdeItemInfo->MDEntryTypeLength = this->m_prevOLSCURRItemInfo->MDEntryTypeLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			}
			else {
				gmdeItemInfo->OrderStatus = this->m_prevOLSCURRItemInfo->OrderStatus;
				gmdeItemInfo->OrderStatusLength = this->m_prevOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			}
			else {
				gmdeItemInfo->TradingSessionSubID = this->m_prevOLSCURRItemInfo->TradingSessionSubID;
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevOLSCURRInfo = info;
		return info;
	}
	void* DecodeTLSFOND() {
		FastTLSFONDInfo* info = GetFreeTLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX5;

		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX6;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevTLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevTLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevTLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			}
			else {
				gmdeItemInfo->OrderSide = this->m_prevTLSFONDItemInfo->OrderSide;
				gmdeItemInfo->OrderSideLength = this->m_prevTLSFONDItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevTLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevTLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			}
			else {
				gmdeItemInfo->AccruedInterestAmt = this->m_prevTLSFONDItemInfo->AccruedInterestAmt;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevTLSFONDItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			}
			else {
				gmdeItemInfo->Yield = this->m_prevTLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevTLSFONDItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			}
			else {
				gmdeItemInfo->SettleType = this->m_prevTLSFONDItemInfo->SettleType;
				gmdeItemInfo->SettleTypeLength = this->m_prevTLSFONDItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			}
			else {
				gmdeItemInfo->Price = this->m_prevTLSFONDItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(!CheckProcessNullInt32())
					gmdeItemInfo->PriceType = ReadInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			}
			else {
				gmdeItemInfo->PriceType = this->m_prevTLSFONDItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevTLSFONDItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevTLSFONDItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevTLSFONDItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX16)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			}
			else {
				gmdeItemInfo->TradingSessionSubID = this->m_prevTLSFONDItemInfo->TradingSessionSubID;
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevTLSFONDItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX17)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			}
			else {
				gmdeItemInfo->RefOrderID = this->m_prevTLSFONDItemInfo->RefOrderID;
				gmdeItemInfo->RefOrderIDLength = this->m_prevTLSFONDItemInfo->RefOrderIDLength;
			}
			this->m_prevTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevTLSFONDInfo = info;
		return info;
	}
	void* DecodeTLSCURR() {
		FastTLSCURRInfo* info = GetFreeTLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX5;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevTLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevTLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevTLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			}
			else {
				gmdeItemInfo->OrderSide = this->m_prevTLSCURRItemInfo->OrderSide;
				gmdeItemInfo->OrderSideLength = this->m_prevTLSCURRItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevTLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevTLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevTLSCURRItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevTLSCURRItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			}
			else {
				gmdeItemInfo->SettleType = this->m_prevTLSCURRItemInfo->SettleType;
				gmdeItemInfo->SettleTypeLength = this->m_prevTLSCURRItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			}
			else {
				gmdeItemInfo->Price = this->m_prevTLSCURRItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(!CheckProcessNullInt32())
					gmdeItemInfo->PriceType = ReadInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			}
			else {
				gmdeItemInfo->PriceType = this->m_prevTLSCURRItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevTLSCURRItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevTLSCURRItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevTLSCURRItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			}
			else {
				gmdeItemInfo->TradingSessionSubID = this->m_prevTLSCURRItemInfo->TradingSessionSubID;
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevTLSCURRItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			}
			else {
				gmdeItemInfo->RefOrderID = this->m_prevTLSCURRItemInfo->RefOrderID;
				gmdeItemInfo->RefOrderIDLength = this->m_prevTLSCURRItemInfo->RefOrderIDLength;
			}
			this->m_prevTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevTLSCURRInfo = info;
		return info;
	}
	void* DecodeIncrementalMSRFOND() {
		FastIncrementalMSRFONDInfo* info = GetFreeIncrementalMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt64())
			info->LastUpdateTime = ReadUInt64_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;

			this->m_prevGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalMSRFONDInfo = info;
		return info;
	}
	void* DecodeIncrementalMSRCURR() {
		FastIncrementalMSRCURRInfo* info = GetFreeIncrementalMSRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt64())
			info->LastUpdateTime = ReadUInt64_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;


		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;

			this->m_prevGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalMSRCURRInfo = info;
		return info;
	}
	void* DecodeIncrementalOLRFOND() {
		FastIncrementalOLRFONDInfo* info = GetFreeIncrementalOLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			}
			else {
				gmdeItemInfo->MDEntryType = this->m_prevOLSFONDItemInfo->MDEntryType;
				gmdeItemInfo->MDEntryTypeLength = this->m_prevOLSFONDItemInfo->MDEntryTypeLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			}
			else {
				gmdeItemInfo->Symbol = this->m_prevOLSFONDItemInfo->Symbol;
				gmdeItemInfo->SymbolLength = this->m_prevOLSFONDItemInfo->SymbolLength;
			}
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			}
			else {
				gmdeItemInfo->Yield = this->m_prevOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			}
			else {
				gmdeItemInfo->OrderStatus = this->m_prevOLSFONDItemInfo->OrderStatus;
				gmdeItemInfo->OrderStatusLength = this->m_prevOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			}
			else {
				gmdeItemInfo->OrdType = this->m_prevOLSFONDItemInfo->OrdType;
				gmdeItemInfo->OrdTypeLength = this->m_prevOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			}
			else {
				gmdeItemInfo->TradingSessionID = this->m_prevOLSFONDItemInfo->TradingSessionID;
				gmdeItemInfo->TradingSessionIDLength = this->m_prevOLSFONDItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			}
			else {
				gmdeItemInfo->TradingSessionSubID = this->m_prevOLSFONDItemInfo->TradingSessionSubID;
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalOLRFONDInfo = info;
		return info;
	}
	void* DecodeIncrementalOLRCURR() {
		FastIncrementalOLRCURRInfo* info = GetFreeIncrementalOLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			}
			else {
				gmdeItemInfo->MDUpdateAction = this->m_prevOLSCURRItemInfo->MDUpdateAction;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			}
			else {
				gmdeItemInfo->MDEntryType = this->m_prevOLSCURRItemInfo->MDEntryType;
				gmdeItemInfo->MDEntryTypeLength = this->m_prevOLSCURRItemInfo->MDEntryTypeLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			}
			else {
				gmdeItemInfo->Symbol = this->m_prevOLSCURRItemInfo->Symbol;
				gmdeItemInfo->SymbolLength = this->m_prevOLSCURRItemInfo->SymbolLength;
			}
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!CheckProcessNullUInt32())
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!CheckProcessNullDecimal())
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			}
			else {
				gmdeItemInfo->OrderStatus = this->m_prevOLSCURRItemInfo->OrderStatus;
				gmdeItemInfo->OrderStatusLength = this->m_prevOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			}
			else {
				gmdeItemInfo->TradingSessionID = this->m_prevOLSCURRItemInfo->TradingSessionID;
				gmdeItemInfo->TradingSessionIDLength = this->m_prevOLSCURRItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			}
			else {
				gmdeItemInfo->TradingSessionSubID = this->m_prevOLSCURRItemInfo->TradingSessionSubID;
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalOLRCURRInfo = info;
		return info;
	}
	void* DecodeIncrementalTLRFOND() {
		FastIncrementalTLRFONDInfo* info = GetFreeIncrementalTLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;

			this->m_prevTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalTLRFONDInfo = info;
		return info;
	}
	void* DecodeIncrementalTLRCURR() {
		FastIncrementalTLRCURRInfo* info = GetFreeIncrementalTLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;

			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;

			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;

			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
			else
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;

			this->m_prevTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevIncrementalTLRCURRInfo = info;
		return info;
	}
	void* DecodeSecurityDefinition() {
		FastSecurityDefinitionInfo* info = GetFreeSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullInt32())
			info->TotNumReports = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Symbol), &(info->SymbolLength));
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityID), &(info->SecurityIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityIDSource), &(info->SecurityIDSourceLength));
		else
			info->NullMap |= NULL_MAP_INDEX3;

		if(!CheckProcessNullInt32())
			info->Product = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX4;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->CFICode), &(info->CFICodeLength));
		else
			info->NullMap |= NULL_MAP_INDEX5;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityType), &(info->SecurityTypeLength));
		else
			info->NullMap |= NULL_MAP_INDEX6;

		if(!CheckProcessNullUInt32())
			info->MaturityDate = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX7;

		if(!CheckProcessNullUInt32())
			info->SettlDate = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX8;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->SettleType), &(info->SettleTypeLength));
		else
			info->NullMap |= NULL_MAP_INDEX9;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->OrigIssueAmt));
		else
			info->NullMap |= NULL_MAP_INDEX10;

		if(!CheckProcessNullUInt32())
			info->CouponPaymentDate = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX11;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->CouponRate));
		else
			info->NullMap |= NULL_MAP_INDEX12;

		if(!CheckProcessNullUInt32())
			info->SettlFixingDate = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX13;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->DividendNetPx));
		else
			info->NullMap |= NULL_MAP_INDEX14;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityDesc), &(info->SecurityDescLength));
		else
			info->NullMap |= NULL_MAP_INDEX15;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->EncodedSecurityDesc), &(info->EncodedSecurityDescLength));
		else
			info->NullMap |= NULL_MAP_INDEX16;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->QuoteText), &(info->QuoteTextLength));
		else
			info->NullMap |= NULL_MAP_INDEX17;


		if(!CheckProcessNullInt32())
			info->GroupInstrAttribCount = ReadUInt32_Optional();
		else
			info->GroupInstrAttribCount = 0;
		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = GetFreeSecurityDefinitionGroupInstrAttribItemInfo();
			info->GroupInstrAttrib[i] = giaItemInfo;
			giaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			if(!CheckProcessNullByteVector())
				ReadByteVector_Optional(&(giaItemInfo->InstrAttribValue), &(giaItemInfo->InstrAttribValueLength));
			else
				giaItemInfo->NullMap |= NULL_MAP_INDEX0;

			this->m_prevSecurityDefinitionGroupInstrAttribItemInfo = giaItemInfo;
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Currency), &(info->CurrencyLength));
		else
			info->NullMap |= NULL_MAP_INDEX19;


		if(!CheckProcessNullInt32())
			info->MarketSegmentGrpCount = ReadUInt32_Optional();
		else
			info->MarketSegmentGrpCount = 0;
		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpItemInfo();
			info->MarketSegmentGrp[i] = msgItemInfo;
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(msgItemInfo->RoundLot));
			else
				msgItemInfo->NullMap |= NULL_MAP_INDEX0;


			if(!CheckProcessNullInt32())
				msgItemInfo->TradingSessionRulesGrpCount = ReadUInt32_Optional();
			else
				msgItemInfo->TradingSessionRulesGrpCount = 0;
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

			for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
				tsrgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
				msgItemInfo->TradingSessionRulesGrp[i] = tsrgItemInfo;
				ReadString_Mandatory(&(tsrgItemInfo->TradingSessionID), &(tsrgItemInfo->TradingSessionIDLength));
				if(!CheckProcessNullString())
					ReadString_Optional(&(tsrgItemInfo->TradingSessionSubID), &(tsrgItemInfo->TradingSessionSubIDLength));
				else
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX0;

				if(!CheckProcessNullInt32())
					tsrgItemInfo->SecurityTradingStatus = ReadInt32_Optional();
				else
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX1;

				if(!CheckProcessNullInt32())
					tsrgItemInfo->OrderNote = ReadInt32_Optional();
				else
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX2;

				this->m_prevSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = tsrgItemInfo;
			}

			this->m_prevSecurityDefinitionMarketSegmentGrpItemInfo = msgItemInfo;
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->SettlCurrency), &(info->SettlCurrencyLength));
		else
			info->NullMap |= NULL_MAP_INDEX21;

		if(!CheckProcessNullInt32())
			info->PriceType = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX22;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->StateSecurityID), &(info->StateSecurityIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX23;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->EncodedShortSecurityDesc), &(info->EncodedShortSecurityDescLength));
		else
			info->NullMap |= NULL_MAP_INDEX24;

		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->MarketCode), &(info->MarketCodeLength));
		else
			info->NullMap |= NULL_MAP_INDEX25;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		else
			info->NullMap |= NULL_MAP_INDEX26;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MktShareLimit));
		else
			info->NullMap |= NULL_MAP_INDEX27;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MktShareThreshold));
		else
			info->NullMap |= NULL_MAP_INDEX28;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MaxOrdersVolume));
		else
			info->NullMap |= NULL_MAP_INDEX29;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->PriceMvmLimit));
		else
			info->NullMap |= NULL_MAP_INDEX30;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->FaceValue));
		else
			info->NullMap |= NULL_MAP_INDEX31;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->BaseSwapPx));
		else
			info->NullMap |= NULL_MAP_INDEX32;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->RepoToPx));
		else
			info->NullMap |= NULL_MAP_INDEX33;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->BuyBackPx));
		else
			info->NullMap |= NULL_MAP_INDEX34;

		if(!CheckProcessNullUInt32())
			info->BuyBackDate = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX35;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->NoSharesIssued));
		else
			info->NullMap |= NULL_MAP_INDEX36;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->HighLimit));
		else
			info->NullMap |= NULL_MAP_INDEX37;

		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->LowLimit));
		else
			info->NullMap |= NULL_MAP_INDEX38;

		if(!CheckProcessNullInt32())
			info->NumOfDaysToMaturity = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX39;

		this->m_prevSecurityDefinitionInfo = info;
		return info;
	}
	void* DecodeSecurityStatus() {
		FastSecurityStatusInfo* info = GetFreeSecurityStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionSubID), &(info->TradingSessionSubIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullInt32())
			info->SecurityTradingStatus = ReadInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		this->m_prevSecurityStatusInfo = info;
		return info;
	}
	void* DecodeTradingSessionStatus() {
		FastTradingSessionStatusInfo* info = GetFreeTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesStatus = ReadInt32_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		ReadString_Mandatory(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		this->m_prevTradingSessionStatusInfo = info;
		return info;
	}
	void* DecodeHeartbeat() {
		FastHeartbeatInfo* info = GetFreeHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevHeartbeatInfo = info;
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoLogon() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // TargetCompID
		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoLogout() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // TargetCompID
		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoGeneric() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX3;

		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalGeneric() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoOLSFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		SkipToNextField(); // TradSesStatus
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoOLSCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		SkipToNextField(); // TradSesStatus
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoTLSFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		SkipToNextField(); // TradSesStatus
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoTLSCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX0;

		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX1;

		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		else
			info->NullMap |= NULL_MAP_INDEX2;

		SkipToNextField(); // TradSesStatus
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX4;

		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalMSRFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalMSRCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalOLRFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalOLRCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalTLRFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalTLRCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoSecurityDefinition() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TotNumReports
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Symbol), &(info->SymbolLength));
		else
			info->NullMap |= NULL_MAP_INDEX1;

		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoSecurityStatus() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		else
			info->NullMap |= NULL_MAP_INDEX0;

		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoTradingSessionStatus() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TradSesStatus
		SkipToNextField(); // Text
		ReadString_Mandatory(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoHeartbeat() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void* Decode() {
		this->DecodeHeader();
		if(this->ShouldSkipTemplate())
			return 0;
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		this->m_lastDecodedInfo = (this->*funcPtr)();
		return this->m_lastDecodedInfo;
	}
	void Print() {

		switch(this->m_templateId) {
			case 2101:
				PrintLogon((FastLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 2102:
				PrintLogout((FastLogoutInfo*)this->m_lastDecodedInfo);
				break;
			case 2103:
				PrintGeneric((FastGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2104:
				PrintIncrementalGeneric((FastIncrementalGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2510:
				PrintOLSFOND((FastOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3600:
				PrintOLSCURR((FastOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2511:
				PrintTLSFOND((FastTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3601:
				PrintTLSCURR((FastTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2523:
				PrintIncrementalMSRFOND((FastIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3613:
				PrintIncrementalMSRCURR((FastIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2520:
				PrintIncrementalOLRFOND((FastIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3610:
				PrintIncrementalOLRCURR((FastIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2521:
				PrintIncrementalTLRFOND((FastIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3611:
				PrintIncrementalTLRCURR((FastIncrementalTLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2115:
				PrintSecurityDefinition((FastSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 2106:
				PrintSecurityStatus((FastSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2107:
				PrintTradingSessionStatus((FastTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2108:
				PrintHeartbeat((FastHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	void PrintXml() {

		switch(this->m_templateId) {
			case 2101:
				PrintXmlLogon((FastLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 2102:
				PrintXmlLogout((FastLogoutInfo*)this->m_lastDecodedInfo);
				break;
			case 2103:
				PrintXmlGeneric((FastGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2104:
				PrintXmlIncrementalGeneric((FastIncrementalGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2510:
				PrintXmlOLSFOND((FastOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3600:
				PrintXmlOLSCURR((FastOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2511:
				PrintXmlTLSFOND((FastTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3601:
				PrintXmlTLSCURR((FastTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2523:
				PrintXmlIncrementalMSRFOND((FastIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3613:
				PrintXmlIncrementalMSRCURR((FastIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2520:
				PrintXmlIncrementalOLRFOND((FastIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3610:
				PrintXmlIncrementalOLRCURR((FastIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2521:
				PrintXmlIncrementalTLRFOND((FastIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3611:
				PrintXmlIncrementalTLRCURR((FastIncrementalTLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2115:
				PrintXmlSecurityDefinition((FastSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 2106:
				PrintXmlSecurityStatus((FastSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2107:
				PrintXmlTradingSessionStatus((FastTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2108:
				PrintXmlHeartbeat((FastHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	inline FastSnapshotInfo* GetSnapshotInfo() {
		this->DecodeHeader();
		FastGetSnapshotInfoMethodPointer funcPtr = this->GetSnapshotInfoMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
#pragma endregion
};

