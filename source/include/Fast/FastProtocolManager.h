#pragma once
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
#pragma endregion

#pragma region Asts_Decode_Method_Pointer_Definition_GeneratedCode
typedef AstsSnapshotInfo* (FastProtocolManager::*AstsGetSnapshotInfoMethodPointer)();
#pragma endregion

#pragma region Spectra_Decode_Method_Pointer_Definition_GeneratedCode
typedef SpectraSnapshotInfo* (FastProtocolManager::*SpectraGetSnapshotInfoMethodPointer)();
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

	void						*m_lastDecodedInfo;

	UINT32						m_skipTemplateId[8];
	int							m_skipTemplateIdCount;

#pragma region Asts_Declare_AllocationInfo_GeneratedCode
	AstsObjectsAllocationInfo *m_astsAllocationInfo;
	AstsSnapshotInfo *m_astsSnapshotInfo;
#pragma endregion
#pragma region Spectra_Declare_AllocationInfo_GeneratedCode
	SpectraObjectsAllocationInfo *m_spectraAllocationInfo;
	SpectraSnapshotInfo *m_spectraSnapshotInfo;
#pragma endregion

#pragma region String_Constant_Declaration_GeneratedCode
public:
	char	MessageEncodingConstString[6];
	const UINT	MessageEncodingConstStringLength = 5;
private:

	void InitializeConstantStrings() {
		sprintf(MessageEncodingConstString, "UTF-8");
	}
#pragma endregion

#pragma region Asts_Structure_Objects_Declaration_GeneratedCode
	AutoAllocatePointerList<AstsLogonInfo>	*m_astsLogon;
	AutoAllocatePointerList<AstsLogoutInfo>	*m_astsLogout;
	AutoAllocatePointerList<AstsGenericItemInfo>	*m_astsGenericItems;
	AutoAllocatePointerList<AstsGenericInfo>	*m_astsGeneric;
	AutoAllocatePointerList<AstsIncrementalGenericInfo>	*m_astsIncrementalGeneric;
	AutoAllocatePointerList<AstsOLSFONDItemInfo>	*m_astsOLSFONDItems;
	AutoAllocatePointerList<AstsOLSFONDInfo>	*m_astsOLSFOND;
	AutoAllocatePointerList<AstsOLSCURRItemInfo>	*m_astsOLSCURRItems;
	AutoAllocatePointerList<AstsOLSCURRInfo>	*m_astsOLSCURR;
	AutoAllocatePointerList<AstsTLSFONDItemInfo>	*m_astsTLSFONDItems;
	AutoAllocatePointerList<AstsTLSFONDInfo>	*m_astsTLSFOND;
	AutoAllocatePointerList<AstsTLSCURRItemInfo>	*m_astsTLSCURRItems;
	AutoAllocatePointerList<AstsTLSCURRInfo>	*m_astsTLSCURR;
	AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>	*m_astsIncrementalMSRFOND;
	AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>	*m_astsIncrementalMSRCURR;
	AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>	*m_astsIncrementalOLRFOND;
	AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>	*m_astsIncrementalOLRCURR;
	AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>	*m_astsIncrementalTLRFOND;
	AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>	*m_astsIncrementalTLRCURR;
	AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>	*m_astsSecurityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>	*m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>	*m_astsSecurityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<AstsSecurityDefinitionInfo>	*m_astsSecurityDefinition;
	AutoAllocatePointerList<AstsSecurityStatusInfo>	*m_astsSecurityStatus;
	AutoAllocatePointerList<AstsTradingSessionStatusInfo>	*m_astsTradingSessionStatus;
	AutoAllocatePointerList<AstsHeartbeatInfo>	*m_astsHeartbeat;
	AstsLogonInfo	*m_prevastsLogonInfo;
	AstsLogoutInfo	*m_prevastsLogoutInfo;
	AstsGenericItemInfo	*m_prevastsGenericItemInfo;
	AstsGenericInfo	*m_prevastsGenericInfo;
	AstsIncrementalGenericInfo	*m_prevastsIncrementalGenericInfo;
	AstsOLSFONDItemInfo	*m_prevastsOLSFONDItemInfo;
	AstsOLSFONDInfo	*m_prevastsOLSFONDInfo;
	AstsOLSCURRItemInfo	*m_prevastsOLSCURRItemInfo;
	AstsOLSCURRInfo	*m_prevastsOLSCURRInfo;
	AstsTLSFONDItemInfo	*m_prevastsTLSFONDItemInfo;
	AstsTLSFONDInfo	*m_prevastsTLSFONDInfo;
	AstsTLSCURRItemInfo	*m_prevastsTLSCURRItemInfo;
	AstsTLSCURRInfo	*m_prevastsTLSCURRInfo;
	AstsIncrementalMSRFONDInfo	*m_prevastsIncrementalMSRFONDInfo;
	AstsIncrementalMSRCURRInfo	*m_prevastsIncrementalMSRCURRInfo;
	AstsIncrementalOLRFONDInfo	*m_prevastsIncrementalOLRFONDInfo;
	AstsIncrementalOLRCURRInfo	*m_prevastsIncrementalOLRCURRInfo;
	AstsIncrementalTLRFONDInfo	*m_prevastsIncrementalTLRFONDInfo;
	AstsIncrementalTLRCURRInfo	*m_prevastsIncrementalTLRCURRInfo;
	AstsSecurityDefinitionGroupInstrAttribItemInfo	*m_prevastsSecurityDefinitionGroupInstrAttribItemInfo;
	AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo	*m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;
	AstsSecurityDefinitionMarketSegmentGrpItemInfo	*m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo;
	AstsSecurityDefinitionInfo	*m_prevastsSecurityDefinitionInfo;
	AstsSecurityStatusInfo	*m_prevastsSecurityStatusInfo;
	AstsTradingSessionStatusInfo	*m_prevastsTradingSessionStatusInfo;
	AstsHeartbeatInfo	*m_prevastsHeartbeatInfo;

	void InitializeAstsMessageInfo() {
		this->m_astsLogon = this->m_astsAllocationInfo->GetAstsLogonInfoPool();
		this->m_astsLogout = this->m_astsAllocationInfo->GetAstsLogoutInfoPool();
		this->m_astsGenericItems = this->m_astsAllocationInfo->GetAstsGenericItemInfoPool();
		this->m_astsGeneric = this->m_astsAllocationInfo->GetAstsGenericInfoPool();
		this->m_astsIncrementalGeneric = this->m_astsAllocationInfo->GetAstsIncrementalGenericInfoPool();
		this->m_astsOLSFONDItems = this->m_astsAllocationInfo->GetAstsOLSFONDItemInfoPool();
		this->m_astsOLSFOND = this->m_astsAllocationInfo->GetAstsOLSFONDInfoPool();
		this->m_astsOLSCURRItems = this->m_astsAllocationInfo->GetAstsOLSCURRItemInfoPool();
		this->m_astsOLSCURR = this->m_astsAllocationInfo->GetAstsOLSCURRInfoPool();
		this->m_astsTLSFONDItems = this->m_astsAllocationInfo->GetAstsTLSFONDItemInfoPool();
		this->m_astsTLSFOND = this->m_astsAllocationInfo->GetAstsTLSFONDInfoPool();
		this->m_astsTLSCURRItems = this->m_astsAllocationInfo->GetAstsTLSCURRItemInfoPool();
		this->m_astsTLSCURR = this->m_astsAllocationInfo->GetAstsTLSCURRInfoPool();
		this->m_astsIncrementalMSRFOND = this->m_astsAllocationInfo->GetAstsIncrementalMSRFONDInfoPool();
		this->m_astsIncrementalMSRCURR = this->m_astsAllocationInfo->GetAstsIncrementalMSRCURRInfoPool();
		this->m_astsIncrementalOLRFOND = this->m_astsAllocationInfo->GetAstsIncrementalOLRFONDInfoPool();
		this->m_astsIncrementalOLRCURR = this->m_astsAllocationInfo->GetAstsIncrementalOLRCURRInfoPool();
		this->m_astsIncrementalTLRFOND = this->m_astsAllocationInfo->GetAstsIncrementalTLRFONDInfoPool();
		this->m_astsIncrementalTLRCURR = this->m_astsAllocationInfo->GetAstsIncrementalTLRCURRInfoPool();
		this->m_astsSecurityDefinitionGroupInstrAttribItems = this->m_astsAllocationInfo->GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool();
		this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = this->m_astsAllocationInfo->GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool();
		this->m_astsSecurityDefinitionMarketSegmentGrpItems = this->m_astsAllocationInfo->GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool();
		this->m_astsSecurityDefinition = this->m_astsAllocationInfo->GetAstsSecurityDefinitionInfoPool();
		this->m_astsSecurityStatus = this->m_astsAllocationInfo->GetAstsSecurityStatusInfoPool();
		this->m_astsTradingSessionStatus = this->m_astsAllocationInfo->GetAstsTradingSessionStatusInfoPool();
		this->m_astsHeartbeat = this->m_astsAllocationInfo->GetAstsHeartbeatInfoPool();
		this->m_prevastsLogonInfo = this->GetFreeAstsLogonInfo();
		this->m_prevastsLogonInfo->Used = true;
		this->m_prevastsLogoutInfo = this->GetFreeAstsLogoutInfo();
		this->m_prevastsLogoutInfo->Used = true;
		this->m_prevastsGenericItemInfo = this->GetFreeAstsGenericItemInfo();
		this->m_prevastsGenericItemInfo->Used = true;
		this->m_prevastsGenericInfo = this->GetFreeAstsGenericInfo();
		this->m_prevastsGenericInfo->Used = true;
		this->m_prevastsIncrementalGenericInfo = this->GetFreeAstsIncrementalGenericInfo();
		this->m_prevastsIncrementalGenericInfo->Used = true;
		this->m_prevastsOLSFONDItemInfo = this->GetFreeAstsOLSFONDItemInfo();
		this->m_prevastsOLSFONDItemInfo->Used = true;
		this->m_prevastsOLSFONDInfo = this->GetFreeAstsOLSFONDInfo();
		this->m_prevastsOLSFONDInfo->Used = true;
		this->m_prevastsOLSCURRItemInfo = this->GetFreeAstsOLSCURRItemInfo();
		this->m_prevastsOLSCURRItemInfo->Used = true;
		this->m_prevastsOLSCURRInfo = this->GetFreeAstsOLSCURRInfo();
		this->m_prevastsOLSCURRInfo->Used = true;
		this->m_prevastsTLSFONDItemInfo = this->GetFreeAstsTLSFONDItemInfo();
		this->m_prevastsTLSFONDItemInfo->Used = true;
		this->m_prevastsTLSFONDInfo = this->GetFreeAstsTLSFONDInfo();
		this->m_prevastsTLSFONDInfo->Used = true;
		this->m_prevastsTLSCURRItemInfo = this->GetFreeAstsTLSCURRItemInfo();
		this->m_prevastsTLSCURRItemInfo->Used = true;
		this->m_prevastsTLSCURRInfo = this->GetFreeAstsTLSCURRInfo();
		this->m_prevastsTLSCURRInfo->Used = true;
		this->m_prevastsIncrementalMSRFONDInfo = this->GetFreeAstsIncrementalMSRFONDInfo();
		this->m_prevastsIncrementalMSRFONDInfo->Used = true;
		this->m_prevastsIncrementalMSRCURRInfo = this->GetFreeAstsIncrementalMSRCURRInfo();
		this->m_prevastsIncrementalMSRCURRInfo->Used = true;
		this->m_prevastsIncrementalOLRFONDInfo = this->GetFreeAstsIncrementalOLRFONDInfo();
		this->m_prevastsIncrementalOLRFONDInfo->Used = true;
		this->m_prevastsIncrementalOLRCURRInfo = this->GetFreeAstsIncrementalOLRCURRInfo();
		this->m_prevastsIncrementalOLRCURRInfo->Used = true;
		this->m_prevastsIncrementalTLRFONDInfo = this->GetFreeAstsIncrementalTLRFONDInfo();
		this->m_prevastsIncrementalTLRFONDInfo->Used = true;
		this->m_prevastsIncrementalTLRCURRInfo = this->GetFreeAstsIncrementalTLRCURRInfo();
		this->m_prevastsIncrementalTLRCURRInfo->Used = true;
		this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo = this->GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo();
		this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo->Used = true;
		this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = this->GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
		this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo->Used = true;
		this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo = this->GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo();
		this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo->Used = true;
		this->m_prevastsSecurityDefinitionInfo = this->GetFreeAstsSecurityDefinitionInfo();
		this->m_prevastsSecurityDefinitionInfo->Used = true;
		this->m_prevastsSecurityStatusInfo = this->GetFreeAstsSecurityStatusInfo();
		this->m_prevastsSecurityStatusInfo->Used = true;
		this->m_prevastsTradingSessionStatusInfo = this->GetFreeAstsTradingSessionStatusInfo();
		this->m_prevastsTradingSessionStatusInfo->Used = true;
		this->m_prevastsHeartbeatInfo = this->GetFreeAstsHeartbeatInfo();
		this->m_prevastsHeartbeatInfo->Used = true;
	}

#pragma endregion

#pragma region Spectra_Structure_Objects_Declaration_GeneratedCode
	AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>	*m_spectraDefaultIncrementalRefreshMessageMDEntriesItems;
	AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageInfo>	*m_spectraDefaultIncrementalRefreshMessage;
	AutoAllocatePointerList<SpectraDefaultSnapshotMessageMDEntriesItemInfo>	*m_spectraDefaultSnapshotMessageMDEntriesItems;
	AutoAllocatePointerList<SpectraDefaultSnapshotMessageInfo>	*m_spectraDefaultSnapshotMessage;
	AutoAllocatePointerList<SpectraSecurityDefinitionMDFeedTypesItemInfo>	*m_spectraSecurityDefinitionMDFeedTypesItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionUnderlyingsItemInfo>	*m_spectraSecurityDefinitionUnderlyingsItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentLegsItemInfo>	*m_spectraSecurityDefinitionInstrumentLegsItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentAttributesItemInfo>	*m_spectraSecurityDefinitionInstrumentAttributesItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionEvntGrpItemInfo>	*m_spectraSecurityDefinitionEvntGrpItems;
	AutoAllocatePointerList<SpectraSecurityDefinitionInfo>	*m_spectraSecurityDefinition;
	AutoAllocatePointerList<SpectraSecurityDefinitionUpdateReportInfo>	*m_spectraSecurityDefinitionUpdateReport;
	AutoAllocatePointerList<SpectraSecurityStatusInfo>	*m_spectraSecurityStatus;
	AutoAllocatePointerList<SpectraHeartbeatInfo>	*m_spectraHeartbeat;
	AutoAllocatePointerList<SpectraSequenceResetInfo>	*m_spectraSequenceReset;
	AutoAllocatePointerList<SpectraTradingSessionStatusInfo>	*m_spectraTradingSessionStatus;
	AutoAllocatePointerList<SpectraNewsNewsTextItemInfo>	*m_spectraNewsNewsTextItems;
	AutoAllocatePointerList<SpectraNewsInfo>	*m_spectraNews;
	AutoAllocatePointerList<SpectraOrdersLogMDEntriesItemInfo>	*m_spectraOrdersLogMDEntriesItems;
	AutoAllocatePointerList<SpectraOrdersLogInfo>	*m_spectraOrdersLog;
	AutoAllocatePointerList<SpectraOrdersBookMDEntriesItemInfo>	*m_spectraOrdersBookMDEntriesItems;
	AutoAllocatePointerList<SpectraOrdersBookInfo>	*m_spectraOrdersBook;
	AutoAllocatePointerList<SpectraLogonInfo>	*m_spectraLogon;
	AutoAllocatePointerList<SpectraLogoutInfo>	*m_spectraLogout;
	SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo	*m_prevspectraDefaultIncrementalRefreshMessageMDEntriesItemInfo;
	SpectraDefaultIncrementalRefreshMessageInfo	*m_prevspectraDefaultIncrementalRefreshMessageInfo;
	SpectraDefaultSnapshotMessageMDEntriesItemInfo	*m_prevspectraDefaultSnapshotMessageMDEntriesItemInfo;
	SpectraDefaultSnapshotMessageInfo	*m_prevspectraDefaultSnapshotMessageInfo;
	SpectraSecurityDefinitionMDFeedTypesItemInfo	*m_prevspectraSecurityDefinitionMDFeedTypesItemInfo;
	SpectraSecurityDefinitionUnderlyingsItemInfo	*m_prevspectraSecurityDefinitionUnderlyingsItemInfo;
	SpectraSecurityDefinitionInstrumentLegsItemInfo	*m_prevspectraSecurityDefinitionInstrumentLegsItemInfo;
	SpectraSecurityDefinitionInstrumentAttributesItemInfo	*m_prevspectraSecurityDefinitionInstrumentAttributesItemInfo;
	SpectraSecurityDefinitionEvntGrpItemInfo	*m_prevspectraSecurityDefinitionEvntGrpItemInfo;
	SpectraSecurityDefinitionInfo	*m_prevspectraSecurityDefinitionInfo;
	SpectraSecurityDefinitionUpdateReportInfo	*m_prevspectraSecurityDefinitionUpdateReportInfo;
	SpectraSecurityStatusInfo	*m_prevspectraSecurityStatusInfo;
	SpectraHeartbeatInfo	*m_prevspectraHeartbeatInfo;
	SpectraSequenceResetInfo	*m_prevspectraSequenceResetInfo;
	SpectraTradingSessionStatusInfo	*m_prevspectraTradingSessionStatusInfo;
	SpectraNewsNewsTextItemInfo	*m_prevspectraNewsNewsTextItemInfo;
	SpectraNewsInfo	*m_prevspectraNewsInfo;
	SpectraOrdersLogMDEntriesItemInfo	*m_prevspectraOrdersLogMDEntriesItemInfo;
	SpectraOrdersLogInfo	*m_prevspectraOrdersLogInfo;
	SpectraOrdersBookMDEntriesItemInfo	*m_prevspectraOrdersBookMDEntriesItemInfo;
	SpectraOrdersBookInfo	*m_prevspectraOrdersBookInfo;
	SpectraLogonInfo	*m_prevspectraLogonInfo;
	SpectraLogoutInfo	*m_prevspectraLogoutInfo;

	void InitializeSpectraMessageInfo() {
		this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems = this->m_spectraAllocationInfo->GetSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfoPool();
		this->m_spectraDefaultIncrementalRefreshMessage = this->m_spectraAllocationInfo->GetSpectraDefaultIncrementalRefreshMessageInfoPool();
		this->m_spectraDefaultSnapshotMessageMDEntriesItems = this->m_spectraAllocationInfo->GetSpectraDefaultSnapshotMessageMDEntriesItemInfoPool();
		this->m_spectraDefaultSnapshotMessage = this->m_spectraAllocationInfo->GetSpectraDefaultSnapshotMessageInfoPool();
		this->m_spectraSecurityDefinitionMDFeedTypesItems = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionMDFeedTypesItemInfoPool();
		this->m_spectraSecurityDefinitionUnderlyingsItems = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionUnderlyingsItemInfoPool();
		this->m_spectraSecurityDefinitionInstrumentLegsItems = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionInstrumentLegsItemInfoPool();
		this->m_spectraSecurityDefinitionInstrumentAttributesItems = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionInstrumentAttributesItemInfoPool();
		this->m_spectraSecurityDefinitionEvntGrpItems = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionEvntGrpItemInfoPool();
		this->m_spectraSecurityDefinition = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionInfoPool();
		this->m_spectraSecurityDefinitionUpdateReport = this->m_spectraAllocationInfo->GetSpectraSecurityDefinitionUpdateReportInfoPool();
		this->m_spectraSecurityStatus = this->m_spectraAllocationInfo->GetSpectraSecurityStatusInfoPool();
		this->m_spectraHeartbeat = this->m_spectraAllocationInfo->GetSpectraHeartbeatInfoPool();
		this->m_spectraSequenceReset = this->m_spectraAllocationInfo->GetSpectraSequenceResetInfoPool();
		this->m_spectraTradingSessionStatus = this->m_spectraAllocationInfo->GetSpectraTradingSessionStatusInfoPool();
		this->m_spectraNewsNewsTextItems = this->m_spectraAllocationInfo->GetSpectraNewsNewsTextItemInfoPool();
		this->m_spectraNews = this->m_spectraAllocationInfo->GetSpectraNewsInfoPool();
		this->m_spectraOrdersLogMDEntriesItems = this->m_spectraAllocationInfo->GetSpectraOrdersLogMDEntriesItemInfoPool();
		this->m_spectraOrdersLog = this->m_spectraAllocationInfo->GetSpectraOrdersLogInfoPool();
		this->m_spectraOrdersBookMDEntriesItems = this->m_spectraAllocationInfo->GetSpectraOrdersBookMDEntriesItemInfoPool();
		this->m_spectraOrdersBook = this->m_spectraAllocationInfo->GetSpectraOrdersBookInfoPool();
		this->m_spectraLogon = this->m_spectraAllocationInfo->GetSpectraLogonInfoPool();
		this->m_spectraLogout = this->m_spectraAllocationInfo->GetSpectraLogoutInfoPool();
		this->m_prevspectraDefaultIncrementalRefreshMessageMDEntriesItemInfo = this->GetFreeSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo();
		this->m_prevspectraDefaultIncrementalRefreshMessageMDEntriesItemInfo->Used = true;
		this->m_prevspectraDefaultIncrementalRefreshMessageInfo = this->GetFreeSpectraDefaultIncrementalRefreshMessageInfo();
		this->m_prevspectraDefaultIncrementalRefreshMessageInfo->Used = true;
		this->m_prevspectraDefaultSnapshotMessageMDEntriesItemInfo = this->GetFreeSpectraDefaultSnapshotMessageMDEntriesItemInfo();
		this->m_prevspectraDefaultSnapshotMessageMDEntriesItemInfo->Used = true;
		this->m_prevspectraDefaultSnapshotMessageInfo = this->GetFreeSpectraDefaultSnapshotMessageInfo();
		this->m_prevspectraDefaultSnapshotMessageInfo->Used = true;
		this->m_prevspectraSecurityDefinitionMDFeedTypesItemInfo = this->GetFreeSpectraSecurityDefinitionMDFeedTypesItemInfo();
		this->m_prevspectraSecurityDefinitionMDFeedTypesItemInfo->Used = true;
		this->m_prevspectraSecurityDefinitionUnderlyingsItemInfo = this->GetFreeSpectraSecurityDefinitionUnderlyingsItemInfo();
		this->m_prevspectraSecurityDefinitionUnderlyingsItemInfo->Used = true;
		this->m_prevspectraSecurityDefinitionInstrumentLegsItemInfo = this->GetFreeSpectraSecurityDefinitionInstrumentLegsItemInfo();
		this->m_prevspectraSecurityDefinitionInstrumentLegsItemInfo->Used = true;
		this->m_prevspectraSecurityDefinitionInstrumentAttributesItemInfo = this->GetFreeSpectraSecurityDefinitionInstrumentAttributesItemInfo();
		this->m_prevspectraSecurityDefinitionInstrumentAttributesItemInfo->Used = true;
		this->m_prevspectraSecurityDefinitionEvntGrpItemInfo = this->GetFreeSpectraSecurityDefinitionEvntGrpItemInfo();
		this->m_prevspectraSecurityDefinitionEvntGrpItemInfo->Used = true;
		this->m_prevspectraSecurityDefinitionInfo = this->GetFreeSpectraSecurityDefinitionInfo();
		this->m_prevspectraSecurityDefinitionInfo->Used = true;
		this->m_prevspectraSecurityDefinitionUpdateReportInfo = this->GetFreeSpectraSecurityDefinitionUpdateReportInfo();
		this->m_prevspectraSecurityDefinitionUpdateReportInfo->Used = true;
		this->m_prevspectraSecurityStatusInfo = this->GetFreeSpectraSecurityStatusInfo();
		this->m_prevspectraSecurityStatusInfo->Used = true;
		this->m_prevspectraHeartbeatInfo = this->GetFreeSpectraHeartbeatInfo();
		this->m_prevspectraHeartbeatInfo->Used = true;
		this->m_prevspectraSequenceResetInfo = this->GetFreeSpectraSequenceResetInfo();
		this->m_prevspectraSequenceResetInfo->Used = true;
		this->m_prevspectraTradingSessionStatusInfo = this->GetFreeSpectraTradingSessionStatusInfo();
		this->m_prevspectraTradingSessionStatusInfo->Used = true;
		this->m_prevspectraNewsNewsTextItemInfo = this->GetFreeSpectraNewsNewsTextItemInfo();
		this->m_prevspectraNewsNewsTextItemInfo->Used = true;
		this->m_prevspectraNewsInfo = this->GetFreeSpectraNewsInfo();
		this->m_prevspectraNewsInfo->Used = true;
		this->m_prevspectraOrdersLogMDEntriesItemInfo = this->GetFreeSpectraOrdersLogMDEntriesItemInfo();
		this->m_prevspectraOrdersLogMDEntriesItemInfo->Used = true;
		this->m_prevspectraOrdersLogInfo = this->GetFreeSpectraOrdersLogInfo();
		this->m_prevspectraOrdersLogInfo->Used = true;
		this->m_prevspectraOrdersBookMDEntriesItemInfo = this->GetFreeSpectraOrdersBookMDEntriesItemInfo();
		this->m_prevspectraOrdersBookMDEntriesItemInfo->Used = true;
		this->m_prevspectraOrdersBookInfo = this->GetFreeSpectraOrdersBookInfo();
		this->m_prevspectraOrdersBookInfo->Used = true;
		this->m_prevspectraLogonInfo = this->GetFreeSpectraLogonInfo();
		this->m_prevspectraLogonInfo->Used = true;
		this->m_prevspectraLogoutInfo = this->GetFreeSpectraLogoutInfo();
		this->m_prevspectraLogoutInfo->Used = true;
	}

#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
	FastDecodeMethodPointer* m_spectraDecodeMethods;
	FastReleaseMethodPointer* m_spectraReleaseMethods;
	SpectraGetSnapshotInfoMethodPointer* m_spectraGetSnapshotInfoMethods;

	void InitializeSpectraDecodeMethodPointers() {
		int ptCount = 999;
		this->m_spectraDecodeMethods = new FastDecodeMethodPointer[ptCount];
		this->m_spectraReleaseMethods = new FastReleaseMethodPointer[ptCount];
		this->m_spectraGetSnapshotInfoMethods = new SpectraGetSnapshotInfoMethodPointer[ptCount];

		for(int i = 0; i < 999; i++) {
			this->m_spectraDecodeMethods[i] = &FastProtocolManager::DecodeSpectraUnsupportedMessage;
			this->m_spectraGetSnapshotInfoMethods[i] = &FastProtocolManager::GetSpectraSnapshotInfoUnsupported;
		}

		this->m_spectraDecodeMethods[12 - 3] = &FastProtocolManager::DecodeSpectraDefaultIncrementalRefreshMessage;
		this->m_spectraDecodeMethods[13 - 3] = &FastProtocolManager::DecodeSpectraDefaultSnapshotMessage;
		this->m_spectraDecodeMethods[3 - 3] = &FastProtocolManager::DecodeSpectraSecurityDefinition;
		this->m_spectraDecodeMethods[4 - 3] = &FastProtocolManager::DecodeSpectraSecurityDefinitionUpdateReport;
		this->m_spectraDecodeMethods[5 - 3] = &FastProtocolManager::DecodeSpectraSecurityStatus;
		this->m_spectraDecodeMethods[6 - 3] = &FastProtocolManager::DecodeSpectraHeartbeat;
		this->m_spectraDecodeMethods[7 - 3] = &FastProtocolManager::DecodeSpectraSequenceReset;
		this->m_spectraDecodeMethods[8 - 3] = &FastProtocolManager::DecodeSpectraTradingSessionStatus;
		this->m_spectraDecodeMethods[9 - 3] = &FastProtocolManager::DecodeSpectraNews;
		this->m_spectraDecodeMethods[14 - 3] = &FastProtocolManager::DecodeSpectraOrdersLog;
		this->m_spectraDecodeMethods[15 - 3] = &FastProtocolManager::DecodeSpectraOrdersBook;
		this->m_spectraDecodeMethods[1000 - 3] = &FastProtocolManager::DecodeSpectraLogon;
		this->m_spectraDecodeMethods[1001 - 3] = &FastProtocolManager::DecodeSpectraLogout;
		this->m_spectraReleaseMethods[12 - 3] = &FastProtocolManager::DecodeSpectraDefaultIncrementalRefreshMessage;
		this->m_spectraReleaseMethods[13 - 3] = &FastProtocolManager::DecodeSpectraDefaultSnapshotMessage;
		this->m_spectraReleaseMethods[3 - 3] = &FastProtocolManager::DecodeSpectraSecurityDefinition;
		this->m_spectraReleaseMethods[4 - 3] = &FastProtocolManager::DecodeSpectraSecurityDefinitionUpdateReport;
		this->m_spectraReleaseMethods[5 - 3] = &FastProtocolManager::DecodeSpectraSecurityStatus;
		this->m_spectraReleaseMethods[6 - 3] = &FastProtocolManager::DecodeSpectraHeartbeat;
		this->m_spectraReleaseMethods[7 - 3] = &FastProtocolManager::DecodeSpectraSequenceReset;
		this->m_spectraReleaseMethods[8 - 3] = &FastProtocolManager::DecodeSpectraTradingSessionStatus;
		this->m_spectraReleaseMethods[9 - 3] = &FastProtocolManager::DecodeSpectraNews;
		this->m_spectraReleaseMethods[14 - 3] = &FastProtocolManager::DecodeSpectraOrdersLog;
		this->m_spectraReleaseMethods[15 - 3] = &FastProtocolManager::DecodeSpectraOrdersBook;
		this->m_spectraReleaseMethods[1000 - 3] = &FastProtocolManager::DecodeSpectraLogon;
		this->m_spectraReleaseMethods[1001 - 3] = &FastProtocolManager::DecodeSpectraLogout;
		this->m_spectraGetSnapshotInfoMethods[13 - 3] = &FastProtocolManager::GetSpectraSnapshotInfoDefaultSnapshotMessage;

	}

	FastDecodeMethodPointer* m_astsDecodeMethods;
	FastReleaseMethodPointer* m_astsReleaseMethods;
	AstsGetSnapshotInfoMethodPointer* m_astsGetSnapshotInfoMethods;

	void InitializeAstsDecodeMethodPointers() {
		int ptCount = 1513;
		this->m_astsDecodeMethods = new FastDecodeMethodPointer[ptCount];
		this->m_astsReleaseMethods = new FastReleaseMethodPointer[ptCount];
		this->m_astsGetSnapshotInfoMethods = new AstsGetSnapshotInfoMethodPointer[ptCount];

		for(int i = 0; i < 1513; i++) {
			this->m_astsDecodeMethods[i] = &FastProtocolManager::DecodeAstsUnsupportedMessage;
			this->m_astsGetSnapshotInfoMethods[i] = &FastProtocolManager::GetAstsSnapshotInfoUnsupported;
		}

		this->m_astsDecodeMethods[2101 - 2101] = &FastProtocolManager::DecodeAstsLogon;
		this->m_astsDecodeMethods[2102 - 2101] = &FastProtocolManager::DecodeAstsLogout;
		this->m_astsDecodeMethods[2103 - 2101] = &FastProtocolManager::DecodeAstsGeneric;
		this->m_astsDecodeMethods[2104 - 2101] = &FastProtocolManager::DecodeAstsIncrementalGeneric;
		this->m_astsDecodeMethods[2510 - 2101] = &FastProtocolManager::DecodeAstsOLSFOND;
		this->m_astsDecodeMethods[3600 - 2101] = &FastProtocolManager::DecodeAstsOLSCURR;
		this->m_astsDecodeMethods[2511 - 2101] = &FastProtocolManager::DecodeAstsTLSFOND;
		this->m_astsDecodeMethods[3601 - 2101] = &FastProtocolManager::DecodeAstsTLSCURR;
		this->m_astsDecodeMethods[2523 - 2101] = &FastProtocolManager::DecodeAstsIncrementalMSRFOND;
		this->m_astsDecodeMethods[3613 - 2101] = &FastProtocolManager::DecodeAstsIncrementalMSRCURR;
		this->m_astsDecodeMethods[2520 - 2101] = &FastProtocolManager::DecodeAstsIncrementalOLRFOND;
		this->m_astsDecodeMethods[3610 - 2101] = &FastProtocolManager::DecodeAstsIncrementalOLRCURR;
		this->m_astsDecodeMethods[2521 - 2101] = &FastProtocolManager::DecodeAstsIncrementalTLRFOND;
		this->m_astsDecodeMethods[3611 - 2101] = &FastProtocolManager::DecodeAstsIncrementalTLRCURR;
		this->m_astsDecodeMethods[2115 - 2101] = &FastProtocolManager::DecodeAstsSecurityDefinition;
		this->m_astsDecodeMethods[2106 - 2101] = &FastProtocolManager::DecodeAstsSecurityStatus;
		this->m_astsDecodeMethods[2107 - 2101] = &FastProtocolManager::DecodeAstsTradingSessionStatus;
		this->m_astsDecodeMethods[2108 - 2101] = &FastProtocolManager::DecodeAstsHeartbeat;
		this->m_astsReleaseMethods[2101 - 2101] = &FastProtocolManager::DecodeAstsLogon;
		this->m_astsReleaseMethods[2102 - 2101] = &FastProtocolManager::DecodeAstsLogout;
		this->m_astsReleaseMethods[2103 - 2101] = &FastProtocolManager::DecodeAstsGeneric;
		this->m_astsReleaseMethods[2104 - 2101] = &FastProtocolManager::DecodeAstsIncrementalGeneric;
		this->m_astsReleaseMethods[2510 - 2101] = &FastProtocolManager::DecodeAstsOLSFOND;
		this->m_astsReleaseMethods[3600 - 2101] = &FastProtocolManager::DecodeAstsOLSCURR;
		this->m_astsReleaseMethods[2511 - 2101] = &FastProtocolManager::DecodeAstsTLSFOND;
		this->m_astsReleaseMethods[3601 - 2101] = &FastProtocolManager::DecodeAstsTLSCURR;
		this->m_astsReleaseMethods[2523 - 2101] = &FastProtocolManager::DecodeAstsIncrementalMSRFOND;
		this->m_astsReleaseMethods[3613 - 2101] = &FastProtocolManager::DecodeAstsIncrementalMSRCURR;
		this->m_astsReleaseMethods[2520 - 2101] = &FastProtocolManager::DecodeAstsIncrementalOLRFOND;
		this->m_astsReleaseMethods[3610 - 2101] = &FastProtocolManager::DecodeAstsIncrementalOLRCURR;
		this->m_astsReleaseMethods[2521 - 2101] = &FastProtocolManager::DecodeAstsIncrementalTLRFOND;
		this->m_astsReleaseMethods[3611 - 2101] = &FastProtocolManager::DecodeAstsIncrementalTLRCURR;
		this->m_astsReleaseMethods[2115 - 2101] = &FastProtocolManager::DecodeAstsSecurityDefinition;
		this->m_astsReleaseMethods[2106 - 2101] = &FastProtocolManager::DecodeAstsSecurityStatus;
		this->m_astsReleaseMethods[2107 - 2101] = &FastProtocolManager::DecodeAstsTradingSessionStatus;
		this->m_astsReleaseMethods[2108 - 2101] = &FastProtocolManager::DecodeAstsHeartbeat;
		this->m_astsGetSnapshotInfoMethods[2103 - 2101] = &FastProtocolManager::GetAstsSnapshotInfoGeneric;
		this->m_astsGetSnapshotInfoMethods[2510 - 2101] = &FastProtocolManager::GetAstsSnapshotInfoOLSFOND;
		this->m_astsGetSnapshotInfoMethods[3600 - 2101] = &FastProtocolManager::GetAstsSnapshotInfoOLSCURR;
		this->m_astsGetSnapshotInfoMethods[2511 - 2101] = &FastProtocolManager::GetAstsSnapshotInfoTLSFOND;
		this->m_astsGetSnapshotInfoMethods[3601 - 2101] = &FastProtocolManager::GetAstsSnapshotInfoTLSCURR;

	}

#pragma endregion

#pragma region Get_Free_Item_Methods_GeneratedCode
public:
	inline SpectraSnapshotInfo* GetFreeSpectraSnapshotInfo() {
		this->m_spectraSnapshotInfo->LastFragment = 0;
		this->m_spectraSnapshotInfo->LastMsgSeqNumProcessed = -1;
		this->m_spectraSnapshotInfo->RouteFirst = 0;
		this->m_spectraSnapshotInfo->RptSeq = -1;
		return this->m_spectraSnapshotInfo;
	}
	inline SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo* GetFreeSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo() {
		return this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo>* GetSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfoPool() {
		return this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems;
	}

	inline SpectraDefaultIncrementalRefreshMessageInfo* GetFreeSpectraDefaultIncrementalRefreshMessageInfo() {
		return this->m_spectraDefaultIncrementalRefreshMessage->NewItem();
	}

	inline AutoAllocatePointerList<SpectraDefaultIncrementalRefreshMessageInfo>* GetSpectraDefaultIncrementalRefreshMessageInfoPool() {
		return this->m_spectraDefaultIncrementalRefreshMessage;
	}

	inline SpectraDefaultSnapshotMessageMDEntriesItemInfo* GetFreeSpectraDefaultSnapshotMessageMDEntriesItemInfo() {
		return this->m_spectraDefaultSnapshotMessageMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraDefaultSnapshotMessageMDEntriesItemInfo>* GetSpectraDefaultSnapshotMessageMDEntriesItemInfoPool() {
		return this->m_spectraDefaultSnapshotMessageMDEntriesItems;
	}

	inline SpectraDefaultSnapshotMessageInfo* GetFreeSpectraDefaultSnapshotMessageInfo() {
		return this->m_spectraDefaultSnapshotMessage->NewItem();
	}

	inline AutoAllocatePointerList<SpectraDefaultSnapshotMessageInfo>* GetSpectraDefaultSnapshotMessageInfoPool() {
		return this->m_spectraDefaultSnapshotMessage;
	}

	inline SpectraSecurityDefinitionMDFeedTypesItemInfo* GetFreeSpectraSecurityDefinitionMDFeedTypesItemInfo() {
		return this->m_spectraSecurityDefinitionMDFeedTypesItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionMDFeedTypesItemInfo>* GetSpectraSecurityDefinitionMDFeedTypesItemInfoPool() {
		return this->m_spectraSecurityDefinitionMDFeedTypesItems;
	}

	inline SpectraSecurityDefinitionUnderlyingsItemInfo* GetFreeSpectraSecurityDefinitionUnderlyingsItemInfo() {
		return this->m_spectraSecurityDefinitionUnderlyingsItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionUnderlyingsItemInfo>* GetSpectraSecurityDefinitionUnderlyingsItemInfoPool() {
		return this->m_spectraSecurityDefinitionUnderlyingsItems;
	}

	inline SpectraSecurityDefinitionInstrumentLegsItemInfo* GetFreeSpectraSecurityDefinitionInstrumentLegsItemInfo() {
		return this->m_spectraSecurityDefinitionInstrumentLegsItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentLegsItemInfo>* GetSpectraSecurityDefinitionInstrumentLegsItemInfoPool() {
		return this->m_spectraSecurityDefinitionInstrumentLegsItems;
	}

	inline SpectraSecurityDefinitionInstrumentAttributesItemInfo* GetFreeSpectraSecurityDefinitionInstrumentAttributesItemInfo() {
		return this->m_spectraSecurityDefinitionInstrumentAttributesItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionInstrumentAttributesItemInfo>* GetSpectraSecurityDefinitionInstrumentAttributesItemInfoPool() {
		return this->m_spectraSecurityDefinitionInstrumentAttributesItems;
	}

	inline SpectraSecurityDefinitionEvntGrpItemInfo* GetFreeSpectraSecurityDefinitionEvntGrpItemInfo() {
		return this->m_spectraSecurityDefinitionEvntGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionEvntGrpItemInfo>* GetSpectraSecurityDefinitionEvntGrpItemInfoPool() {
		return this->m_spectraSecurityDefinitionEvntGrpItems;
	}

	inline SpectraSecurityDefinitionInfo* GetFreeSpectraSecurityDefinitionInfo() {
		return this->m_spectraSecurityDefinition->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionInfo>* GetSpectraSecurityDefinitionInfoPool() {
		return this->m_spectraSecurityDefinition;
	}

	inline SpectraSecurityDefinitionUpdateReportInfo* GetFreeSpectraSecurityDefinitionUpdateReportInfo() {
		return this->m_spectraSecurityDefinitionUpdateReport->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityDefinitionUpdateReportInfo>* GetSpectraSecurityDefinitionUpdateReportInfoPool() {
		return this->m_spectraSecurityDefinitionUpdateReport;
	}

	inline SpectraSecurityStatusInfo* GetFreeSpectraSecurityStatusInfo() {
		return this->m_spectraSecurityStatus->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSecurityStatusInfo>* GetSpectraSecurityStatusInfoPool() {
		return this->m_spectraSecurityStatus;
	}

	inline SpectraHeartbeatInfo* GetFreeSpectraHeartbeatInfo() {
		return this->m_spectraHeartbeat->NewItem();
	}

	inline AutoAllocatePointerList<SpectraHeartbeatInfo>* GetSpectraHeartbeatInfoPool() {
		return this->m_spectraHeartbeat;
	}

	inline SpectraSequenceResetInfo* GetFreeSpectraSequenceResetInfo() {
		return this->m_spectraSequenceReset->NewItem();
	}

	inline AutoAllocatePointerList<SpectraSequenceResetInfo>* GetSpectraSequenceResetInfoPool() {
		return this->m_spectraSequenceReset;
	}

	inline SpectraTradingSessionStatusInfo* GetFreeSpectraTradingSessionStatusInfo() {
		return this->m_spectraTradingSessionStatus->NewItem();
	}

	inline AutoAllocatePointerList<SpectraTradingSessionStatusInfo>* GetSpectraTradingSessionStatusInfoPool() {
		return this->m_spectraTradingSessionStatus;
	}

	inline SpectraNewsNewsTextItemInfo* GetFreeSpectraNewsNewsTextItemInfo() {
		return this->m_spectraNewsNewsTextItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraNewsNewsTextItemInfo>* GetSpectraNewsNewsTextItemInfoPool() {
		return this->m_spectraNewsNewsTextItems;
	}

	inline SpectraNewsInfo* GetFreeSpectraNewsInfo() {
		return this->m_spectraNews->NewItem();
	}

	inline AutoAllocatePointerList<SpectraNewsInfo>* GetSpectraNewsInfoPool() {
		return this->m_spectraNews;
	}

	inline SpectraOrdersLogMDEntriesItemInfo* GetFreeSpectraOrdersLogMDEntriesItemInfo() {
		return this->m_spectraOrdersLogMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraOrdersLogMDEntriesItemInfo>* GetSpectraOrdersLogMDEntriesItemInfoPool() {
		return this->m_spectraOrdersLogMDEntriesItems;
	}

	inline SpectraOrdersLogInfo* GetFreeSpectraOrdersLogInfo() {
		return this->m_spectraOrdersLog->NewItem();
	}

	inline AutoAllocatePointerList<SpectraOrdersLogInfo>* GetSpectraOrdersLogInfoPool() {
		return this->m_spectraOrdersLog;
	}

	inline SpectraOrdersBookMDEntriesItemInfo* GetFreeSpectraOrdersBookMDEntriesItemInfo() {
		return this->m_spectraOrdersBookMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<SpectraOrdersBookMDEntriesItemInfo>* GetSpectraOrdersBookMDEntriesItemInfoPool() {
		return this->m_spectraOrdersBookMDEntriesItems;
	}

	inline SpectraOrdersBookInfo* GetFreeSpectraOrdersBookInfo() {
		return this->m_spectraOrdersBook->NewItem();
	}

	inline AutoAllocatePointerList<SpectraOrdersBookInfo>* GetSpectraOrdersBookInfoPool() {
		return this->m_spectraOrdersBook;
	}

	inline SpectraLogonInfo* GetFreeSpectraLogonInfo() {
		return this->m_spectraLogon->NewItem();
	}

	inline AutoAllocatePointerList<SpectraLogonInfo>* GetSpectraLogonInfoPool() {
		return this->m_spectraLogon;
	}

	inline SpectraLogoutInfo* GetFreeSpectraLogoutInfo() {
		return this->m_spectraLogout->NewItem();
	}

	inline AutoAllocatePointerList<SpectraLogoutInfo>* GetSpectraLogoutInfoPool() {
		return this->m_spectraLogout;
	}

private:
	void ReleaseSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo() {
		((SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraDefaultIncrementalRefreshMessageInfo() {
		((SpectraDefaultIncrementalRefreshMessageInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraDefaultSnapshotMessageMDEntriesItemInfo() {
		((SpectraDefaultSnapshotMessageMDEntriesItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraDefaultSnapshotMessageInfo() {
		((SpectraDefaultSnapshotMessageInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionMDFeedTypesItemInfo() {
		((SpectraSecurityDefinitionMDFeedTypesItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionUnderlyingsItemInfo() {
		((SpectraSecurityDefinitionUnderlyingsItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionInstrumentLegsItemInfo() {
		((SpectraSecurityDefinitionInstrumentLegsItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionInstrumentAttributesItemInfo() {
		((SpectraSecurityDefinitionInstrumentAttributesItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionEvntGrpItemInfo() {
		((SpectraSecurityDefinitionEvntGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionInfo() {
		((SpectraSecurityDefinitionInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityDefinitionUpdateReportInfo() {
		((SpectraSecurityDefinitionUpdateReportInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSecurityStatusInfo() {
		((SpectraSecurityStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraHeartbeatInfo() {
		((SpectraHeartbeatInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraSequenceResetInfo() {
		((SpectraSequenceResetInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraTradingSessionStatusInfo() {
		((SpectraTradingSessionStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraNewsNewsTextItemInfo() {
		((SpectraNewsNewsTextItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraNewsInfo() {
		((SpectraNewsInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraOrdersLogMDEntriesItemInfo() {
		((SpectraOrdersLogMDEntriesItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraOrdersLogInfo() {
		((SpectraOrdersLogInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraOrdersBookMDEntriesItemInfo() {
		((SpectraOrdersBookMDEntriesItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraOrdersBookInfo() {
		((SpectraOrdersBookInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraLogonInfo() {
		((SpectraLogonInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseSpectraLogoutInfo() {
		((SpectraLogoutInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	inline void ResetSpectra() {
		FastReleaseMethodPointer funcPtr = this->m_spectraReleaseMethods[this->m_templateId - 3];
		(this->*funcPtr)();
	}
public:
	inline AstsSnapshotInfo* GetFreeAstsSnapshotInfo() {
		this->m_astsSnapshotInfo->LastFragment = 0;
		this->m_astsSnapshotInfo->LastMsgSeqNumProcessed = -1;
		this->m_astsSnapshotInfo->RouteFirst = 0;
		this->m_astsSnapshotInfo->RptSeq = -1;
		return this->m_astsSnapshotInfo;
	}
	inline AstsLogonInfo* GetFreeAstsLogonInfo() {
		return this->m_astsLogon->NewItem();
	}

	inline AutoAllocatePointerList<AstsLogonInfo>* GetAstsLogonInfoPool() {
		return this->m_astsLogon;
	}

	inline AstsLogoutInfo* GetFreeAstsLogoutInfo() {
		return this->m_astsLogout->NewItem();
	}

	inline AutoAllocatePointerList<AstsLogoutInfo>* GetAstsLogoutInfoPool() {
		return this->m_astsLogout;
	}

	inline AstsGenericItemInfo* GetFreeAstsGenericItemInfo() {
		return this->m_astsGenericItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsGenericItemInfo>* GetAstsGenericItemInfoPool() {
		return this->m_astsGenericItems;
	}

	inline AstsGenericInfo* GetFreeAstsGenericInfo() {
		return this->m_astsGeneric->NewItem();
	}

	inline AutoAllocatePointerList<AstsGenericInfo>* GetAstsGenericInfoPool() {
		return this->m_astsGeneric;
	}

	inline AstsIncrementalGenericInfo* GetFreeAstsIncrementalGenericInfo() {
		return this->m_astsIncrementalGeneric->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalGenericInfo>* GetAstsIncrementalGenericInfoPool() {
		return this->m_astsIncrementalGeneric;
	}

	inline AstsOLSFONDItemInfo* GetFreeAstsOLSFONDItemInfo() {
		return this->m_astsOLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSFONDItemInfo>* GetAstsOLSFONDItemInfoPool() {
		return this->m_astsOLSFONDItems;
	}

	inline AstsOLSFONDInfo* GetFreeAstsOLSFONDInfo() {
		return this->m_astsOLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSFONDInfo>* GetAstsOLSFONDInfoPool() {
		return this->m_astsOLSFOND;
	}

	inline AstsOLSCURRItemInfo* GetFreeAstsOLSCURRItemInfo() {
		return this->m_astsOLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSCURRItemInfo>* GetAstsOLSCURRItemInfoPool() {
		return this->m_astsOLSCURRItems;
	}

	inline AstsOLSCURRInfo* GetFreeAstsOLSCURRInfo() {
		return this->m_astsOLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSCURRInfo>* GetAstsOLSCURRInfoPool() {
		return this->m_astsOLSCURR;
	}

	inline AstsTLSFONDItemInfo* GetFreeAstsTLSFONDItemInfo() {
		return this->m_astsTLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSFONDItemInfo>* GetAstsTLSFONDItemInfoPool() {
		return this->m_astsTLSFONDItems;
	}

	inline AstsTLSFONDInfo* GetFreeAstsTLSFONDInfo() {
		return this->m_astsTLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSFONDInfo>* GetAstsTLSFONDInfoPool() {
		return this->m_astsTLSFOND;
	}

	inline AstsTLSCURRItemInfo* GetFreeAstsTLSCURRItemInfo() {
		return this->m_astsTLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSCURRItemInfo>* GetAstsTLSCURRItemInfoPool() {
		return this->m_astsTLSCURRItems;
	}

	inline AstsTLSCURRInfo* GetFreeAstsTLSCURRInfo() {
		return this->m_astsTLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSCURRInfo>* GetAstsTLSCURRInfoPool() {
		return this->m_astsTLSCURR;
	}

	inline AstsIncrementalMSRFONDInfo* GetFreeAstsIncrementalMSRFONDInfo() {
		return this->m_astsIncrementalMSRFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>* GetAstsIncrementalMSRFONDInfoPool() {
		return this->m_astsIncrementalMSRFOND;
	}

	inline AstsIncrementalMSRCURRInfo* GetFreeAstsIncrementalMSRCURRInfo() {
		return this->m_astsIncrementalMSRCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>* GetAstsIncrementalMSRCURRInfoPool() {
		return this->m_astsIncrementalMSRCURR;
	}

	inline AstsIncrementalOLRFONDInfo* GetFreeAstsIncrementalOLRFONDInfo() {
		return this->m_astsIncrementalOLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>* GetAstsIncrementalOLRFONDInfoPool() {
		return this->m_astsIncrementalOLRFOND;
	}

	inline AstsIncrementalOLRCURRInfo* GetFreeAstsIncrementalOLRCURRInfo() {
		return this->m_astsIncrementalOLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>* GetAstsIncrementalOLRCURRInfoPool() {
		return this->m_astsIncrementalOLRCURR;
	}

	inline AstsIncrementalTLRFONDInfo* GetFreeAstsIncrementalTLRFONDInfo() {
		return this->m_astsIncrementalTLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>* GetAstsIncrementalTLRFONDInfoPool() {
		return this->m_astsIncrementalTLRFOND;
	}

	inline AstsIncrementalTLRCURRInfo* GetFreeAstsIncrementalTLRCURRInfo() {
		return this->m_astsIncrementalTLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>* GetAstsIncrementalTLRCURRInfoPool() {
		return this->m_astsIncrementalTLRCURR;
	}

	inline AstsSecurityDefinitionGroupInstrAttribItemInfo* GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>* GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems;
	}

	inline AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}

	inline AstsSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems;
	}

	inline AstsSecurityDefinitionInfo* GetFreeAstsSecurityDefinitionInfo() {
		return this->m_astsSecurityDefinition->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionInfo>* GetAstsSecurityDefinitionInfoPool() {
		return this->m_astsSecurityDefinition;
	}

	inline AstsSecurityStatusInfo* GetFreeAstsSecurityStatusInfo() {
		return this->m_astsSecurityStatus->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityStatusInfo>* GetAstsSecurityStatusInfoPool() {
		return this->m_astsSecurityStatus;
	}

	inline AstsTradingSessionStatusInfo* GetFreeAstsTradingSessionStatusInfo() {
		return this->m_astsTradingSessionStatus->NewItem();
	}

	inline AutoAllocatePointerList<AstsTradingSessionStatusInfo>* GetAstsTradingSessionStatusInfoPool() {
		return this->m_astsTradingSessionStatus;
	}

	inline AstsHeartbeatInfo* GetFreeAstsHeartbeatInfo() {
		return this->m_astsHeartbeat->NewItem();
	}

	inline AutoAllocatePointerList<AstsHeartbeatInfo>* GetAstsHeartbeatInfoPool() {
		return this->m_astsHeartbeat;
	}

private:
	void ReleaseAstsLogonInfo() {
		((AstsLogonInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsLogoutInfo() {
		((AstsLogoutInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsGenericItemInfo() {
		((AstsGenericItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsGenericInfo() {
		((AstsGenericInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalGenericInfo() {
		((AstsIncrementalGenericInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSFONDItemInfo() {
		((AstsOLSFONDItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSFONDInfo() {
		((AstsOLSFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSCURRItemInfo() {
		((AstsOLSCURRItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSCURRInfo() {
		((AstsOLSCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSFONDItemInfo() {
		((AstsTLSFONDItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSFONDInfo() {
		((AstsTLSFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSCURRItemInfo() {
		((AstsTLSCURRItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSCURRInfo() {
		((AstsTLSCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalMSRFONDInfo() {
		((AstsIncrementalMSRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalMSRCURRInfo() {
		((AstsIncrementalMSRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalOLRFONDInfo() {
		((AstsIncrementalOLRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalOLRCURRInfo() {
		((AstsIncrementalOLRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalTLRFONDInfo() {
		((AstsIncrementalTLRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalTLRCURRInfo() {
		((AstsIncrementalTLRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionGroupInstrAttribItemInfo() {
		((AstsSecurityDefinitionGroupInstrAttribItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		((AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		((AstsSecurityDefinitionMarketSegmentGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionInfo() {
		((AstsSecurityDefinitionInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityStatusInfo() {
		((AstsSecurityStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTradingSessionStatusInfo() {
		((AstsTradingSessionStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsHeartbeatInfo() {
		((AstsHeartbeatInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	inline void ResetAsts() {
		FastReleaseMethodPointer funcPtr = this->m_astsReleaseMethods[this->m_templateId - 2101];
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
	inline bool CheckProcessNullInt64() {
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
		if (value >= 0)
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

	inline void CopyString(char *dst, char *src, int count) {
		while(count >= 8) {
			*((UINT64*)dst) = *((UINT64*)src);
			count -= 8;
			dst += 8; src += 8;
		}
		if(count >= 4) {
			*((UINT32*)dst) = *((UINT32*)src);
			count -= 4;
			dst += 4; src += 4;
		}
		if(count >= 2) {
			*((unsigned short*)dst) = *((unsigned short*)src);
			count -= 2;
			dst += 2; src += 2;
		}
		if(count > 0)
			*dst = *src;
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

	inline void ReadString_Optional(char *str, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		int length = 0;
		if ((memory & 0xffff) == 0x8000) { 
			lengthAddress = 0;
			this->currentPos += 2;
			return;
		}
		while (true) {
			if ((memory & 0x8080808080808080) != 0) {
				if ((memory & 0x0000000080808080) != 0) {
					if ((memory & 0x8080) != 0) {
						if ((memory & 0x80) != 0) {
							*str = (char)(memory & 0x7f);
							length++;
							this->currentPos++;
							break;
						}
						else {
							*((unsigned short*)str) = (unsigned short)(memory & 0x7fff);
							length += 2;
							this->currentPos += 2;
							break;
						}
					}
					else {
						if ((memory & 0x800000) != 0) {

							*str = (char)memory;
							this->currentPos++; str++; memory >>= 8;
							*((unsigned short*)str) = (unsigned short)(memory & 0x7fff);

							length += 3;
							this->currentPos += 2;
							break;
						}
						else {
							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);
							length += 4;
							this->currentPos += 4;
							break;
						}
					}
				}
				else {
					if ((memory & 0x0000808000000000) != 0) {
						if ((memory & 0x0000008000000000) != 0) {

							*str = (char)memory;
							this->currentPos++; str++; memory >>= 8;
							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

							length += 5;
							this->currentPos += 4;
							break;
						}
						else {
							*((unsigned short*)str) = (unsigned short)memory;
							this->currentPos += 2; str += 2; memory >>= 16;
							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

							length += 6;
							this->currentPos += 4;
							break;
						}
					}
					else {
						if ((memory & 0x0080000000000000) != 0) {

							*str = (char)memory;
							this->currentPos++; str++; memory >>= 8;

							*((unsigned short*)str) = (unsigned short)memory;
							this->currentPos += 2; str += 2; memory >>= 16;

							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

							length += 7;
							this->currentPos += 4;
							break;
						}
						else {
							*((UINT64*)str) = memory & 0x7fffffffffffffff;

							length += 8;
							this->currentPos += 8;
							break;
						}
					}
				}
			}
            *((UINT64*)str) = memory;
            str += 8;

            length += 8;
			this->currentPos += 8;
			memory = *((UINT64*)this->currentPos);
		}
		*lengthAddress = length;
	}
	inline void ReadString_Mandatory(char *str, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		int length = 0;
		if ((memory & 0xff) == 0x80) {
			lengthAddress = 0;
			this->currentPos ++;
			return;
		}
		while (true) {
			if ((memory & 0x8080808080808080) != 0) {
				if ((memory & 0x0000000080808080) != 0) {
					if ((memory & 0x8080) != 0) {
						if ((memory & 0x80) != 0) {
							*str = (char)(memory & 0x7f);
							length++;
							this->currentPos++;
							break;
						}
						else {
							*((unsigned short*)str) = (unsigned short)(memory & 0x7fff);
							length += 2;
							this->currentPos += 2;
							break;
						}
					}
					else {
						if ((memory & 0x800000) != 0) {

							*str = (char)memory;
							this->currentPos++; str++; memory >>= 8;
							*((unsigned short*)str) = (unsigned short)(memory & 0x7fff);

							length += 3;
							this->currentPos += 2;
							break;
						}
						else {
							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);
							length += 4;
							this->currentPos += 4;
							break;
						}
					}
				}
				else {
					if ((memory & 0x0000808000000000) != 0) {
						if ((memory & 0x0000008000000000) != 0) {

							*str = (char)memory;
							this->currentPos++; str++; memory >>= 8;
							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

							length += 5;
							this->currentPos += 4;
							break;
						}
						else {
							*((unsigned short*)str) = (unsigned short)memory;
							this->currentPos += 2; str += 2; memory >>= 16;
							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

							length += 6;
							this->currentPos += 4;
							break;
						}
					}
					else {
						if ((memory & 0x0080000000000000) != 0) {

							*str = (char)memory;
							this->currentPos++; str++; memory >>= 8;

							*((unsigned short*)str) = (unsigned short)memory;
							this->currentPos += 2; str += 2; memory >>= 16;

							*((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

							length += 7;
							this->currentPos += 4;
							break;
						}
						else {
							*((UINT64*)str) = memory & 0x7fffffffffffffff;

							length += 8;
							this->currentPos += 8;
							break;
						}
					}
				}
			}
            *((UINT64*)str) = memory;
            str += 8;

            length += 8;
            this->currentPos += 8;
            memory = *((UINT64*)this->currentPos);
		}
		*lengthAddress = length;
	}

	inline void ReadByteVector_Optional(BYTE *vecPtrAddress, int *lengthAddress, int maxLength) {
		int length = ReadInt32_Optional();
		int copyLength = length > maxLength? maxLength: length;
		this->CopyString((char*)vecPtrAddress, (char*)(this->currentPos), copyLength);
		this->currentPos += length;
		*lengthAddress = copyLength;
	}
	inline void ReadByteVector_Mandatory(BYTE *vecPtrAddress, int *lengthAddress, int maxLength) {
		int length = ReadInt32_Mandatory();
		int copyLength = length > maxLength? maxLength: length;
		this->CopyString((char*)vecPtrAddress, (char*)(this->currentPos), copyLength);
		this->currentPos += length;
		*lengthAddress = copyLength;
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

	FastProtocolManager(AstsObjectsAllocationInfo *astsInfo, SpectraObjectsAllocationInfo *spectraInfo);
	FastProtocolManager();
	~FastProtocolManager();

	inline BYTE* Buffer() { return this->buffer; }
	inline BYTE* CurrentPos() { return this->currentPos; }
	inline int BufferLength() { return this->bufferLength; }
	inline int MessageLength() { return this->currentPos - this->buffer; }
	inline void SetBufferLength(int value) { this->bufferLength = value; }

#pragma region Asts_Encode_Methods_Declaration_GeneratedCode
	void EncodeAstsLogonInfo(AstsLogonInfo* info);
	void EncodeAstsLogoutInfo(AstsLogoutInfo* info);
	void EncodeAstsGenericInfo(AstsGenericInfo* info);
	void EncodeAstsIncrementalGenericInfo(AstsIncrementalGenericInfo* info);
	void EncodeAstsOLSFONDInfo(AstsOLSFONDInfo* info);
	void EncodeAstsOLSCURRInfo(AstsOLSCURRInfo* info);
	void EncodeAstsTLSFONDInfo(AstsTLSFONDInfo* info);
	void EncodeAstsTLSCURRInfo(AstsTLSCURRInfo* info);
	void EncodeAstsIncrementalMSRFONDInfo(AstsIncrementalMSRFONDInfo* info);
	void EncodeAstsIncrementalMSRCURRInfo(AstsIncrementalMSRCURRInfo* info);
	void EncodeAstsIncrementalOLRFONDInfo(AstsIncrementalOLRFONDInfo* info);
	void EncodeAstsIncrementalOLRCURRInfo(AstsIncrementalOLRCURRInfo* info);
	void EncodeAstsIncrementalTLRFONDInfo(AstsIncrementalTLRFONDInfo* info);
	void EncodeAstsIncrementalTLRCURRInfo(AstsIncrementalTLRCURRInfo* info);
	void EncodeAstsSecurityDefinitionInfo(AstsSecurityDefinitionInfo* info);
	void EncodeAstsSecurityStatusInfo(AstsSecurityStatusInfo* info);
	void EncodeAstsTradingSessionStatusInfo(AstsTradingSessionStatusInfo* info);
	void EncodeAstsHeartbeatInfo(AstsHeartbeatInfo* info);
#pragma endregion

#pragma region Spectra_Encode_Methods_Declaration_GeneratedCode
	void EncodeSpectraDefaultIncrementalRefreshMessageInfo(SpectraDefaultIncrementalRefreshMessageInfo* info);
	void EncodeSpectraDefaultSnapshotMessageInfo(SpectraDefaultSnapshotMessageInfo* info);
	void EncodeSpectraSecurityDefinitionInfo(SpectraSecurityDefinitionInfo* info);
	void EncodeSpectraSecurityDefinitionUpdateReportInfo(SpectraSecurityDefinitionUpdateReportInfo* info);
	void EncodeSpectraSecurityStatusInfo(SpectraSecurityStatusInfo* info);
	void EncodeSpectraHeartbeatInfo(SpectraHeartbeatInfo* info);
	void EncodeSpectraSequenceResetInfo(SpectraSequenceResetInfo* info);
	void EncodeSpectraTradingSessionStatusInfo(SpectraTradingSessionStatusInfo* info);
	void EncodeSpectraNewsInfo(SpectraNewsInfo* info);
	void EncodeSpectraOrdersLogInfo(SpectraOrdersLogInfo* info);
	void EncodeSpectraOrdersBookInfo(SpectraOrdersBookInfo* info);
	void EncodeSpectraLogonInfo(SpectraLogonInfo* info);
	void EncodeSpectraLogoutInfo(SpectraLogoutInfo* info);
#pragma endregion

#pragma region Asts_Print_Methods_Declaration_GeneratedCode
	void PrintAstsLogon(AstsLogonInfo *info);
	void PrintAstsLogout(AstsLogoutInfo *info);
	void PrintAstsGeneric(AstsGenericInfo *info);
	void PrintAstsIncrementalGeneric(AstsIncrementalGenericInfo *info);
	void PrintAstsOLSFOND(AstsOLSFONDInfo *info);
	void PrintAstsOLSCURR(AstsOLSCURRInfo *info);
	void PrintAstsTLSFOND(AstsTLSFONDInfo *info);
	void PrintAstsTLSCURR(AstsTLSCURRInfo *info);
	void PrintAstsIncrementalMSRFOND(AstsIncrementalMSRFONDInfo *info);
	void PrintAstsIncrementalMSRCURR(AstsIncrementalMSRCURRInfo *info);
	void PrintAstsIncrementalOLRFOND(AstsIncrementalOLRFONDInfo *info);
	void PrintAstsIncrementalOLRCURR(AstsIncrementalOLRCURRInfo *info);
	void PrintAstsIncrementalTLRFOND(AstsIncrementalTLRFONDInfo *info);
	void PrintAstsIncrementalTLRCURR(AstsIncrementalTLRCURRInfo *info);
	void PrintAstsSecurityDefinition(AstsSecurityDefinitionInfo *info);
	void PrintAstsSecurityStatus(AstsSecurityStatusInfo *info);
	void PrintAstsTradingSessionStatus(AstsTradingSessionStatusInfo *info);
	void PrintAstsHeartbeat(AstsHeartbeatInfo *info);
	void PrintXmlAstsLogon(AstsLogonInfo *info);
	void PrintXmlAstsLogout(AstsLogoutInfo *info);
	void PrintXmlAstsGeneric(AstsGenericInfo *info);
	void PrintXmlAstsIncrementalGeneric(AstsIncrementalGenericInfo *info);
	void PrintXmlAstsOLSFOND(AstsOLSFONDInfo *info);
	void PrintXmlAstsOLSCURR(AstsOLSCURRInfo *info);
	void PrintXmlAstsTLSFOND(AstsTLSFONDInfo *info);
	void PrintXmlAstsTLSCURR(AstsTLSCURRInfo *info);
	void PrintXmlAstsIncrementalMSRFOND(AstsIncrementalMSRFONDInfo *info);
	void PrintXmlAstsIncrementalMSRCURR(AstsIncrementalMSRCURRInfo *info);
	void PrintXmlAstsIncrementalOLRFOND(AstsIncrementalOLRFONDInfo *info);
	void PrintXmlAstsIncrementalOLRCURR(AstsIncrementalOLRCURRInfo *info);
	void PrintXmlAstsIncrementalTLRFOND(AstsIncrementalTLRFONDInfo *info);
	void PrintXmlAstsIncrementalTLRCURR(AstsIncrementalTLRCURRInfo *info);
	void PrintXmlAstsSecurityDefinition(AstsSecurityDefinitionInfo *info);
	void PrintXmlAstsSecurityStatus(AstsSecurityStatusInfo *info);
	void PrintXmlAstsTradingSessionStatus(AstsTradingSessionStatusInfo *info);
	void PrintXmlAstsHeartbeat(AstsHeartbeatInfo *info);
#pragma endregion

#pragma region Spectra_Print_Methods_Declaration_GeneratedCode
	void PrintSpectraDefaultIncrementalRefreshMessage(SpectraDefaultIncrementalRefreshMessageInfo *info);
	void PrintSpectraDefaultSnapshotMessage(SpectraDefaultSnapshotMessageInfo *info);
	void PrintSpectraSecurityDefinition(SpectraSecurityDefinitionInfo *info);
	void PrintSpectraSecurityDefinitionUpdateReport(SpectraSecurityDefinitionUpdateReportInfo *info);
	void PrintSpectraSecurityStatus(SpectraSecurityStatusInfo *info);
	void PrintSpectraHeartbeat(SpectraHeartbeatInfo *info);
	void PrintSpectraSequenceReset(SpectraSequenceResetInfo *info);
	void PrintSpectraTradingSessionStatus(SpectraTradingSessionStatusInfo *info);
	void PrintSpectraNews(SpectraNewsInfo *info);
	void PrintSpectraOrdersLog(SpectraOrdersLogInfo *info);
	void PrintSpectraOrdersBook(SpectraOrdersBookInfo *info);
	void PrintSpectraLogon(SpectraLogonInfo *info);
	void PrintSpectraLogout(SpectraLogoutInfo *info);
	void PrintXmlSpectraDefaultIncrementalRefreshMessage(SpectraDefaultIncrementalRefreshMessageInfo *info);
	void PrintXmlSpectraDefaultSnapshotMessage(SpectraDefaultSnapshotMessageInfo *info);
	void PrintXmlSpectraSecurityDefinition(SpectraSecurityDefinitionInfo *info);
	void PrintXmlSpectraSecurityDefinitionUpdateReport(SpectraSecurityDefinitionUpdateReportInfo *info);
	void PrintXmlSpectraSecurityStatus(SpectraSecurityStatusInfo *info);
	void PrintXmlSpectraHeartbeat(SpectraHeartbeatInfo *info);
	void PrintXmlSpectraSequenceReset(SpectraSequenceResetInfo *info);
	void PrintXmlSpectraTradingSessionStatus(SpectraTradingSessionStatusInfo *info);
	void PrintXmlSpectraNews(SpectraNewsInfo *info);
	void PrintXmlSpectraOrdersLog(SpectraOrdersLogInfo *info);
	void PrintXmlSpectraOrdersBook(SpectraOrdersBookInfo *info);
	void PrintXmlSpectraLogon(SpectraLogonInfo *info);
	void PrintXmlSpectraLogout(SpectraLogoutInfo *info);
#pragma endregion

#pragma region Asts_Decode_Methods_Definition_GeneratedCode
	inline void DecodeAstsHeader() {

		this->ParsePresenceMap(&(this->m_presenceMap));
		this->m_templateId = ReadUInt32_Mandatory();
	}

	int GetAstsTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Optional();
	}
	void* DecodeAstsUnsupportedMessage() { return 0; }
	AstsSnapshotInfo* GetAstsSnapshotInfoUnsupported() { return 0; }
	void* DecodeAstsLogon() {
		AstsLogonInfo* info = GetFreeAstsLogonInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->HeartBtInt = ReadInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Username, &(info->UsernameLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->Password, &(info->PasswordLength));
		ReadString_Mandatory(info->DefaultApplVerID, &(info->DefaultApplVerIDLength));
		this->m_prevastsLogonInfo = info;
		return info;
	}
	void* DecodeAstsLogout() {
		AstsLogoutInfo* info = GetFreeAstsLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		this->m_prevastsLogoutInfo = info;
		return info;
	}
	void* DecodeAstsGeneric() {
		AstsGenericInfo* info = GetFreeAstsGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->RouteFirst = ReadUInt32_Optional();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			info->TradSesStatus = ReadInt32_Optional();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			info->AuctionIndicator = ReadUInt32_Optional();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX7;
		else
			ReadDecimal_Optional(&(info->NetChgPrevDay));

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			else
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			else
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;
			else
				ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;
			else
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;
			else
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX33;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX34;
			else
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX35;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX36;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX37;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX38;
			else
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX39;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX40;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsGenericInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalGeneric() {
		AstsIncrementalGenericInfo* info = GetFreeAstsIncrementalGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;
			else
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;
			else
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;
			else
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX33;
			else
				ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX34;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX35;
			else
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX36;
			else
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX37;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX38;
			else
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX39;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX40;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX41;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX42;
			else
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX43;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX44;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX45;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalGenericInfo = info;
		return info;
	}
	void* DecodeAstsOLSFOND() {
		AstsOLSFONDInfo* info = GetFreeAstsOLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->TradSesStatus = ReadInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSFONDItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdTypeLength);
				gmdeItemInfo->OrdTypeLength = this->m_prevastsOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevastsOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsOLSFONDInfo = info;
		return info;
	}
	void* DecodeAstsOLSCURR() {
		AstsOLSCURRInfo* info = GetFreeAstsOLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->TradSesStatus = ReadInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSCURRItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsOLSCURRInfo = info;
		return info;
	}
	void* DecodeAstsTLSFOND() {
		AstsTLSFONDInfo* info = GetFreeAstsTLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->TradSesStatus = ReadInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsTLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsTLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsTLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevastsTLSFONDItemInfo->OrderSide, m_prevastsTLSFONDItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevastsTLSFONDItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsTLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsTLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			}
			else {
				gmdeItemInfo->AccruedInterestAmt = this->m_prevastsTLSFONDItemInfo->AccruedInterestAmt;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevastsTLSFONDItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsTLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevastsTLSFONDItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevastsTLSFONDItemInfo->SettleType, m_prevastsTLSFONDItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevastsTLSFONDItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
			}
			else {
				gmdeItemInfo->Price = this->m_prevastsTLSFONDItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					gmdeItemInfo->PriceType = ReadInt32_Optional();
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevastsTLSFONDItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevastsTLSFONDItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevastsTLSFONDItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
				else
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevastsTLSFONDItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX16)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsTLSFONDItemInfo->TradingSessionSubID, m_prevastsTLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsTLSFONDItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX17)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
				else
					ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevastsTLSFONDItemInfo->RefOrderID, m_prevastsTLSFONDItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevastsTLSFONDItemInfo->RefOrderIDLength;
			}
			this->m_prevastsTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsTLSFONDInfo = info;
		return info;
	}
	void* DecodeAstsTLSCURR() {
		AstsTLSCURRInfo* info = GetFreeAstsTLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->TradSesStatus = ReadInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsTLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsTLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsTLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevastsTLSCURRItemInfo->OrderSide, m_prevastsTLSCURRItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevastsTLSCURRItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsTLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsTLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevastsTLSCURRItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevastsTLSCURRItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevastsTLSCURRItemInfo->SettleType, m_prevastsTLSCURRItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevastsTLSCURRItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
			}
			else {
				gmdeItemInfo->Price = this->m_prevastsTLSCURRItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					gmdeItemInfo->PriceType = ReadInt32_Optional();
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevastsTLSCURRItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevastsTLSCURRItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevastsTLSCURRItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevastsTLSCURRItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsTLSCURRItemInfo->TradingSessionSubID, m_prevastsTLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsTLSCURRItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
				else
					ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevastsTLSCURRItemInfo->RefOrderID, m_prevastsTLSCURRItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevastsTLSCURRItemInfo->RefOrderIDLength;
			}
			this->m_prevastsTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsTLSCURRInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalMSRFOND() {
		AstsIncrementalMSRFONDInfo* info = GetFreeAstsIncrementalMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			else
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			else
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;
			else
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalMSRFONDInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalMSRCURR() {
		AstsIncrementalMSRCURRInfo* info = GetFreeAstsIncrementalMSRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			else
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalMSRCURRInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalOLRFOND() {
		AstsIncrementalOLRFONDInfo* info = GetFreeAstsIncrementalOLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSFONDItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			}
			else {
				this->CopyString(gmdeItemInfo->Symbol, m_prevastsOLSFONDItemInfo->Symbol, m_prevastsOLSFONDItemInfo->SymbolLength);
				gmdeItemInfo->SymbolLength = this->m_prevastsOLSFONDItemInfo->SymbolLength;
			}
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdTypeLength);
				gmdeItemInfo->OrdTypeLength = this->m_prevastsOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevastsOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionID, m_prevastsOLSFONDItemInfo->TradingSessionID, m_prevastsOLSFONDItemInfo->TradingSessionIDLength);
				gmdeItemInfo->TradingSessionIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalOLRFONDInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalOLRCURR() {
		AstsIncrementalOLRCURRInfo* info = GetFreeAstsIncrementalOLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDUpdateAction = this->m_prevastsOLSCURRItemInfo->MDUpdateAction;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSCURRItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			}
			else {
				this->CopyString(gmdeItemInfo->Symbol, m_prevastsOLSCURRItemInfo->Symbol, m_prevastsOLSCURRItemInfo->SymbolLength);
				gmdeItemInfo->SymbolLength = this->m_prevastsOLSCURRItemInfo->SymbolLength;
			}
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionID, m_prevastsOLSCURRItemInfo->TradingSessionID, m_prevastsOLSCURRItemInfo->TradingSessionIDLength);
				gmdeItemInfo->TradingSessionIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalOLRCURRInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalTLRFOND() {
		AstsIncrementalTLRFONDInfo* info = GetFreeAstsIncrementalTLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			this->m_prevastsTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalTLRFONDInfo = info;
		return info;
	}
	void* DecodeAstsIncrementalTLRCURR() {
		AstsIncrementalTLRCURRInfo* info = GetFreeAstsIncrementalTLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		AstsTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(CheckProcessNullInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(CheckProcessNullUInt32())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			this->m_prevastsTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalTLRCURRInfo = info;
		return info;
	}
	void* DecodeAstsSecurityDefinition() {
		AstsSecurityDefinitionInfo* info = GetFreeAstsSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->TotNumReports = ReadInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadByteVector_Optional(info->SecurityID, &(info->SecurityIDLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadByteVector_Optional(info->SecurityIDSource, &(info->SecurityIDSourceLength), 128);
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			info->Product = ReadInt32_Optional();
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadByteVector_Optional(info->CFICode, &(info->CFICodeLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			ReadByteVector_Optional(info->SecurityType, &(info->SecurityTypeLength), 128);
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX7;
		else
			info->MaturityDate = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX8;
		else
			info->SettlDate = ReadUInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX9;
		else
			ReadString_Optional(info->SettleType, &(info->SettleTypeLength));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX10;
		else
			ReadDecimal_Optional(&(info->OrigIssueAmt));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX11;
		else
			info->CouponPaymentDate = ReadUInt32_Optional();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX12;
		else
			ReadDecimal_Optional(&(info->CouponRate));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX13;
		else
			info->SettlFixingDate = ReadUInt32_Optional();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX14;
		else
			ReadDecimal_Optional(&(info->DividendNetPx));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX15;
		else
			ReadByteVector_Optional(info->SecurityDesc, &(info->SecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX16;
		else
			ReadByteVector_Optional(info->EncodedSecurityDesc, &(info->EncodedSecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX17;
		else
			ReadByteVector_Optional(info->QuoteText, &(info->QuoteTextLength), 128);

		if(CheckProcessNullInt32()) {
			info->GroupInstrAttribCount = 0;
			info->NullMap |= NULL_MAP_INDEX18;
		}
		else
			info->GroupInstrAttribCount = ReadUInt32_Optional();
		AstsSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo();
			info->GroupInstrAttrib[i] = giaItemInfo;
			giaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			if(CheckProcessNullByteVector())
				giaItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadByteVector_Optional(giaItemInfo->InstrAttribValue, &(giaItemInfo->InstrAttribValueLength), 128);
			this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo = giaItemInfo;
		}

		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX19;
		else
			ReadString_Optional(info->Currency, &(info->CurrencyLength));

		if(CheckProcessNullInt32()) {
			info->MarketSegmentGrpCount = 0;
			info->NullMap |= NULL_MAP_INDEX20;
		}
		else
			info->MarketSegmentGrpCount = ReadUInt32_Optional();
		AstsSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo();
			info->MarketSegmentGrp[i] = msgItemInfo;
			if(CheckProcessNullDecimal())
				msgItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadDecimal_Optional(&(msgItemInfo->RoundLot));

			if(CheckProcessNullInt32()) {
				msgItemInfo->TradingSessionRulesGrpCount = 0;
				msgItemInfo->NullMap |= NULL_MAP_INDEX1;
			}
			else
				msgItemInfo->TradingSessionRulesGrpCount = ReadUInt32_Optional();
			AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

			for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
				tsrgItemInfo = GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
				msgItemInfo->TradingSessionRulesGrp[i] = tsrgItemInfo;
				ReadString_Mandatory(tsrgItemInfo->TradingSessionID, &(tsrgItemInfo->TradingSessionIDLength));
				if(CheckProcessNullString())
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional(tsrgItemInfo->TradingSessionSubID, &(tsrgItemInfo->TradingSessionSubIDLength));
				if(CheckProcessNullInt32())
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					tsrgItemInfo->SecurityTradingStatus = ReadInt32_Optional();
				if(CheckProcessNullInt32())
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					tsrgItemInfo->OrderNote = ReadInt32_Optional();
				this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = tsrgItemInfo;
			}

			this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo = msgItemInfo;
		}

		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX21;
		else
			ReadString_Optional(info->SettlCurrency, &(info->SettlCurrencyLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX22;
		else
			info->PriceType = ReadInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX23;
		else
			ReadString_Optional(info->StateSecurityID, &(info->StateSecurityIDLength));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX24;
		else
			ReadByteVector_Optional(info->EncodedShortSecurityDesc, &(info->EncodedShortSecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX25;
		else
			ReadByteVector_Optional(info->MarketCode, &(info->MarketCodeLength), 128);
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX26;
		else
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX27;
		else
			ReadDecimal_Optional(&(info->MktShareLimit));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX28;
		else
			ReadDecimal_Optional(&(info->MktShareThreshold));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX29;
		else
			ReadDecimal_Optional(&(info->MaxOrdersVolume));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX30;
		else
			ReadDecimal_Optional(&(info->PriceMvmLimit));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX31;
		else
			ReadDecimal_Optional(&(info->FaceValue));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX32;
		else
			ReadDecimal_Optional(&(info->BaseSwapPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX33;
		else
			ReadDecimal_Optional(&(info->RepoToPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX34;
		else
			ReadDecimal_Optional(&(info->BuyBackPx));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX35;
		else
			info->BuyBackDate = ReadUInt32_Optional();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX36;
		else
			ReadDecimal_Optional(&(info->NoSharesIssued));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX37;
		else
			ReadDecimal_Optional(&(info->HighLimit));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX38;
		else
			ReadDecimal_Optional(&(info->LowLimit));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX39;
		else
			info->NumOfDaysToMaturity = ReadInt32_Optional();
		this->m_prevastsSecurityDefinitionInfo = info;
		return info;
	}
	void* DecodeAstsSecurityStatus() {
		AstsSecurityStatusInfo* info = GetFreeAstsSecurityStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->TradingSessionSubID, &(info->TradingSessionSubIDLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->SecurityTradingStatus = ReadInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->AuctionIndicator = ReadUInt32_Optional();
		this->m_prevastsSecurityStatusInfo = info;
		return info;
	}
	void* DecodeAstsTradingSessionStatus() {
		AstsTradingSessionStatusInfo* info = GetFreeAstsTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesStatus = ReadInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		ReadString_Mandatory(info->TradingSessionID, &(info->TradingSessionIDLength));
		this->m_prevastsTradingSessionStatusInfo = info;
		return info;
	}
	void* DecodeAstsHeartbeat() {
		AstsHeartbeatInfo* info = GetFreeAstsHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevastsHeartbeatInfo = info;
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoLogon() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // TargetCompID
		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoLogout() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // TargetCompID
		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoGeneric() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->RouteFirst = ReadUInt32_Optional();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalGeneric() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoOLSFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoOLSCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoTLSFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoTLSCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->RouteFirst = ReadUInt32_Optional();
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalMSRFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalMSRCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalOLRFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalOLRCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalTLRFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoIncrementalTLRCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoSecurityDefinition() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TotNumReports
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->Symbol, &(info->SymbolLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoSecurityStatus() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoTradingSessionStatus() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TradSesStatus
		SkipToNextField(); // Text
		ReadString_Mandatory(info->TradingSessionID, &(info->TradingSessionIDLength));
		return info;
	}
	AstsSnapshotInfo* GetAstsSnapshotInfoHeartbeat() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void* DecodeAsts() {
		this->DecodeAstsHeader();
		FastDecodeMethodPointer funcPtr = this->m_astsDecodeMethods[this->m_templateId - 2101];
		this->m_lastDecodedInfo = (this->*funcPtr)();
		return this->m_lastDecodedInfo;
	}
	void PrintAsts() {

		switch(this->m_templateId) {
			case 2101:
				PrintAstsLogon((AstsLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 2102:
				PrintAstsLogout((AstsLogoutInfo*)this->m_lastDecodedInfo);
				break;
			case 2103:
				PrintAstsGeneric((AstsGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2104:
				PrintAstsIncrementalGeneric((AstsIncrementalGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2510:
				PrintAstsOLSFOND((AstsOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3600:
				PrintAstsOLSCURR((AstsOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2511:
				PrintAstsTLSFOND((AstsTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3601:
				PrintAstsTLSCURR((AstsTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2523:
				PrintAstsIncrementalMSRFOND((AstsIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3613:
				PrintAstsIncrementalMSRCURR((AstsIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2520:
				PrintAstsIncrementalOLRFOND((AstsIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3610:
				PrintAstsIncrementalOLRCURR((AstsIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2521:
				PrintAstsIncrementalTLRFOND((AstsIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3611:
				PrintAstsIncrementalTLRCURR((AstsIncrementalTLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2115:
				PrintAstsSecurityDefinition((AstsSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 2106:
				PrintAstsSecurityStatus((AstsSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2107:
				PrintAstsTradingSessionStatus((AstsTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2108:
				PrintAstsHeartbeat((AstsHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	void PrintXmlAsts() {

		switch(this->m_templateId) {
			case 2101:
				PrintXmlAstsLogon((AstsLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 2102:
				PrintXmlAstsLogout((AstsLogoutInfo*)this->m_lastDecodedInfo);
				break;
			case 2103:
				PrintXmlAstsGeneric((AstsGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2104:
				PrintXmlAstsIncrementalGeneric((AstsIncrementalGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2510:
				PrintXmlAstsOLSFOND((AstsOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3600:
				PrintXmlAstsOLSCURR((AstsOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2511:
				PrintXmlAstsTLSFOND((AstsTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3601:
				PrintXmlAstsTLSCURR((AstsTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2523:
				PrintXmlAstsIncrementalMSRFOND((AstsIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3613:
				PrintXmlAstsIncrementalMSRCURR((AstsIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2520:
				PrintXmlAstsIncrementalOLRFOND((AstsIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3610:
				PrintXmlAstsIncrementalOLRCURR((AstsIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2521:
				PrintXmlAstsIncrementalTLRFOND((AstsIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3611:
				PrintXmlAstsIncrementalTLRCURR((AstsIncrementalTLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2115:
				PrintXmlAstsSecurityDefinition((AstsSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 2106:
				PrintXmlAstsSecurityStatus((AstsSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2107:
				PrintXmlAstsTradingSessionStatus((AstsTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2108:
				PrintXmlAstsHeartbeat((AstsHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfo() {
		this->DecodeAstsHeader();
		AstsGetSnapshotInfoMethodPointer funcPtr = this->m_astsGetSnapshotInfoMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
#pragma endregion

#pragma region Spectra_Decode_Methods_Definition_GeneratedCode
	inline void DecodeSpectraHeader() {

		this->ParsePresenceMap(&(this->m_presenceMap));
		this->m_templateId = ReadUInt32_Mandatory();
	}

	int GetSpectraTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Mandatory();
	}
	void* DecodeSpectraUnsupportedMessage() { return 0; }
	SpectraSnapshotInfo* GetSpectraSnapshotInfoUnsupported() { return 0; }
	void* DecodeSpectraDefaultIncrementalRefreshMessage() {
		SpectraDefaultIncrementalRefreshMessageInfo* info = GetFreeSpectraDefaultIncrementalRefreshMessageInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastFragment = ReadUInt32_Optional();

		info->MDEntriesCount = ReadUInt32_Mandatory();
		SpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			mdeItemInfo->MDUpdateAction = ReadUInt32_Mandatory();
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->SecurityID = ReadUInt64_Optional();
			mdeItemInfo->SecurityIDSource = ReadUInt32_Mandatory();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(mdeItemInfo->Symbol, &(mdeItemInfo->SymbolLength));
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(mdeItemInfo->SecurityGroup, &(mdeItemInfo->SecurityGroupLength));
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				mdeItemInfo->ExchangeTradingSessionID = ReadUInt32_Optional();
			mdeItemInfo->RptSeq = ReadUInt32_Mandatory();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				mdeItemInfo->MarketDepth = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDPriceLevel = ReadUInt32_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				mdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				mdeItemInfo->NumberOfOrders = ReadInt32_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(mdeItemInfo->MDEntryTradeType, &(mdeItemInfo->MDEntryTradeTypeLength));
			if(CheckProcessNullInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				mdeItemInfo->TrdType = ReadInt32_Optional();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(mdeItemInfo->LastPx));
			if(CheckProcessNullInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				mdeItemInfo->MDFlags = ReadInt32_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadString_Optional(mdeItemInfo->Currency, &(mdeItemInfo->CurrencyLength));
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				mdeItemInfo->Revision = ReadUInt64_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadString_Optional(mdeItemInfo->OrderSide, &(mdeItemInfo->OrderSideLength));
			this->m_prevspectraDefaultIncrementalRefreshMessageMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevspectraDefaultIncrementalRefreshMessageInfo = info;
		return info;
	}
	void* DecodeSpectraDefaultSnapshotMessage() {
		SpectraDefaultSnapshotMessageInfo* info = GetFreeSpectraDefaultSnapshotMessageInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastFragment = ReadUInt32_Optional();
		info->RptSeq = ReadUInt32_Mandatory();
		info->TotNumReports = ReadUInt32_Mandatory();
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional();
		info->SecurityIDSource = ReadUInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadString_Optional(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadString_Optional(info->SecurityGroup, &(info->SecurityGroupLength));

		info->MDEntriesCount = ReadUInt32_Mandatory();
		SpectraDefaultSnapshotMessageMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeSpectraDefaultSnapshotMessageMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->ExchangeTradingSessionID = ReadUInt32_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				mdeItemInfo->MarketDepth = ReadUInt32_Optional();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				mdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				mdeItemInfo->MDPriceLevel = ReadUInt32_Optional();
			if(CheckProcessNullInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				mdeItemInfo->NumberOfOrders = ReadInt32_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadString_Optional(mdeItemInfo->MDEntryTradeType, &(mdeItemInfo->MDEntryTradeTypeLength));
			if(CheckProcessNullInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				mdeItemInfo->TrdType = ReadInt32_Optional();
			if(CheckProcessNullInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				mdeItemInfo->MDFlags = ReadInt32_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(mdeItemInfo->Currency, &(mdeItemInfo->CurrencyLength));
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(mdeItemInfo->OrderSide, &(mdeItemInfo->OrderSideLength));
			this->m_prevspectraDefaultSnapshotMessageMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevspectraDefaultSnapshotMessageInfo = info;
		return info;
	}
	void* DecodeSpectraSecurityDefinition() {
		SpectraSecurityDefinitionInfo* info = GetFreeSpectraSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TotNumReports = ReadUInt32_Mandatory();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->SecurityDesc, &(info->SecurityDescLength));
		info->SecurityID = ReadUInt64_Mandatory();
		info->SecurityIDSource = ReadUInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->SecurityAltID, &(info->SecurityAltIDLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadString_Optional(info->SecurityAltIDSource, &(info->SecurityAltIDSourceLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadString_Optional(info->SecurityType, &(info->SecurityTypeLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->CFICode, &(info->CFICodeLength));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadDecimal_Optional(&(info->StrikePrice));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			ReadDecimal_Optional(&(info->ContractMultiplier));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX7;
		else
			info->SecurityTradingStatus = ReadUInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX8;
		else
			ReadString_Optional(info->Currency, &(info->CurrencyLength));
		ReadString_Mandatory(info->MarketID, &(info->MarketIDLength));
		ReadString_Mandatory(info->MarketSegmentID, &(info->MarketSegmentIDLength));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX9;
		else
			info->TradingSessionID = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX10;
		else
			info->ExchangeTradingSessionID = ReadUInt32_Optional();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX11;
		else
			ReadDecimal_Optional(&(info->Volatility));

		info->MDFeedTypesCount = ReadUInt32_Mandatory();
		SpectraSecurityDefinitionMDFeedTypesItemInfo* mdftItemInfo = NULL;

		for(int i = 0; i < info->MDFeedTypesCount; i++) {
			mdftItemInfo = GetFreeSpectraSecurityDefinitionMDFeedTypesItemInfo();
			info->MDFeedTypes[i] = mdftItemInfo;
			ReadString_Mandatory(mdftItemInfo->MDFeedType, &(mdftItemInfo->MDFeedTypeLength));
			if(CheckProcessNullUInt32())
				mdftItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdftItemInfo->MarketDepth = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				mdftItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				mdftItemInfo->MDBookType = ReadUInt32_Optional();
			this->m_prevspectraSecurityDefinitionMDFeedTypesItemInfo = mdftItemInfo;
		}


		if(CheckProcessNullInt32()) {
			info->UnderlyingsCount = 0;
			info->NullMap |= NULL_MAP_INDEX12;
		}
		else
			info->UnderlyingsCount = ReadUInt32_Optional();
		SpectraSecurityDefinitionUnderlyingsItemInfo* uItemInfo = NULL;

		for(int i = 0; i < info->UnderlyingsCount; i++) {
			uItemInfo = GetFreeSpectraSecurityDefinitionUnderlyingsItemInfo();
			info->Underlyings[i] = uItemInfo;
			ReadString_Mandatory(uItemInfo->UnderlyingSymbol, &(uItemInfo->UnderlyingSymbolLength));
			if(CheckProcessNullUInt64())
				uItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				uItemInfo->UnderlyingSecurityID = ReadUInt64_Optional();
			this->m_prevspectraSecurityDefinitionUnderlyingsItemInfo = uItemInfo;
		}

		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX13;
		else
			ReadDecimal_Optional(&(info->HighLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX14;
		else
			ReadDecimal_Optional(&(info->LowLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX15;
		else
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX16;
		else
			ReadDecimal_Optional(&(info->MinPriceIncrementAmount));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX17;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnBuy));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX18;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnSell));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX19;
		else
			ReadDecimal_Optional(&(info->InitialMarginSyntetic));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX20;
		else
			ReadString_Optional(info->QuotationList, &(info->QuotationListLength));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX21;
		else
			ReadDecimal_Optional(&(info->TheorPrice));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX22;
		else
			ReadDecimal_Optional(&(info->TheorPriceLimit));

		if(CheckProcessNullInt32()) {
			info->InstrumentLegsCount = 0;
			info->NullMap |= NULL_MAP_INDEX23;
		}
		else
			info->InstrumentLegsCount = ReadUInt32_Optional();
		SpectraSecurityDefinitionInstrumentLegsItemInfo* ilItemInfo = NULL;

		for(int i = 0; i < info->InstrumentLegsCount; i++) {
			ilItemInfo = GetFreeSpectraSecurityDefinitionInstrumentLegsItemInfo();
			info->InstrumentLegs[i] = ilItemInfo;
			ReadString_Mandatory(ilItemInfo->LegSymbol, &(ilItemInfo->LegSymbolLength));
			ilItemInfo->LegSecurityID = ReadUInt64_Mandatory();
			ReadDecimal_Mandatory(&(ilItemInfo->LegRatioQty));
			this->m_prevspectraSecurityDefinitionInstrumentLegsItemInfo = ilItemInfo;
		}


		if(CheckProcessNullInt32()) {
			info->InstrumentAttributesCount = 0;
			info->NullMap |= NULL_MAP_INDEX24;
		}
		else
			info->InstrumentAttributesCount = ReadUInt32_Optional();
		SpectraSecurityDefinitionInstrumentAttributesItemInfo* iaItemInfo = NULL;

		for(int i = 0; i < info->InstrumentAttributesCount; i++) {
			iaItemInfo = GetFreeSpectraSecurityDefinitionInstrumentAttributesItemInfo();
			info->InstrumentAttributes[i] = iaItemInfo;
			iaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			ReadString_Mandatory(iaItemInfo->InstrAttribValue, &(iaItemInfo->InstrAttribValueLength));
			this->m_prevspectraSecurityDefinitionInstrumentAttributesItemInfo = iaItemInfo;
		}

		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX25;
		else
			ReadDecimal_Optional(&(info->UnderlyingQty));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX26;
		else
			ReadString_Optional(info->UnderlyingCurrency, &(info->UnderlyingCurrencyLength));

		if(CheckProcessNullInt32()) {
			info->EvntGrpCount = 0;
			info->NullMap |= NULL_MAP_INDEX27;
		}
		else
			info->EvntGrpCount = ReadUInt32_Optional();
		SpectraSecurityDefinitionEvntGrpItemInfo* egItemInfo = NULL;

		for(int i = 0; i < info->EvntGrpCount; i++) {
			egItemInfo = GetFreeSpectraSecurityDefinitionEvntGrpItemInfo();
			info->EvntGrp[i] = egItemInfo;
			egItemInfo->EventType = ReadInt32_Mandatory();
			egItemInfo->EventDate = ReadUInt32_Mandatory();
			egItemInfo->EventTime = ReadUInt64_Mandatory();
			this->m_prevspectraSecurityDefinitionEvntGrpItemInfo = egItemInfo;
		}

		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX28;
		else
			info->MaturityDate = ReadUInt32_Optional();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX29;
		else
			info->MaturityTime = ReadUInt32_Optional();
		this->m_prevspectraSecurityDefinitionInfo = info;
		return info;
	}
	void* DecodeSpectraSecurityDefinitionUpdateReport() {
		SpectraSecurityDefinitionUpdateReportInfo* info = GetFreeSpectraSecurityDefinitionUpdateReportInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->SecurityID = ReadUInt64_Mandatory();
		info->SecurityIDSource = ReadUInt32_Mandatory();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadDecimal_Optional(&(info->Volatility));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadDecimal_Optional(&(info->TheorPrice));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadDecimal_Optional(&(info->TheorPriceLimit));
		this->m_prevspectraSecurityDefinitionUpdateReportInfo = info;
		return info;
	}
	void* DecodeSpectraSecurityStatus() {
		SpectraSecurityStatusInfo* info = GetFreeSpectraSecurityStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->SecurityID = ReadUInt64_Mandatory();
		info->SecurityIDSource = ReadUInt32_Mandatory();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->SecurityTradingStatus = ReadUInt32_Optional();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadDecimal_Optional(&(info->HighLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadDecimal_Optional(&(info->LowLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnBuy));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnSell));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadDecimal_Optional(&(info->InitialMarginSyntetic));
		this->m_prevspectraSecurityStatusInfo = info;
		return info;
	}
	void* DecodeSpectraHeartbeat() {
		SpectraHeartbeatInfo* info = GetFreeSpectraHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevspectraHeartbeatInfo = info;
		return info;
	}
	void* DecodeSpectraSequenceReset() {
		SpectraSequenceResetInfo* info = GetFreeSpectraSequenceResetInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->NewSeqNo = ReadUInt32_Mandatory();
		this->m_prevspectraSequenceResetInfo = info;
		return info;
	}
	void* DecodeSpectraTradingSessionStatus() {
		SpectraTradingSessionStatusInfo* info = GetFreeSpectraTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesOpenTime = ReadUInt64_Mandatory();
		info->TradSesCloseTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->TradSesIntermClearingStartTime = ReadUInt64_Optional();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->TradSesIntermClearingEndTime = ReadUInt64_Optional();
		info->TradingSessionID = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->ExchangeTradingSessionID = ReadUInt32_Optional();
		info->TradSesStatus = ReadUInt32_Mandatory();
		ReadString_Mandatory(info->MarketID, &(info->MarketIDLength));
		ReadString_Mandatory(info->MarketSegmentID, &(info->MarketSegmentIDLength));
		if(CheckProcessNullInt32())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			info->TradSesEvent = ReadInt32_Optional();
		this->m_prevspectraTradingSessionStatusInfo = info;
		return info;
	}
	void* DecodeSpectraNews() {
		SpectraNewsInfo* info = GetFreeSpectraNewsInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastFragment = ReadUInt32_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->NewsId, &(info->NewsIdLength));
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->OrigTime = ReadUInt64_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadString_Optional(info->LanguageCode, &(info->LanguageCodeLength));
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			info->Urgency = ReadUInt32_Optional();
		ReadString_Mandatory(info->Headline, &(info->HeadlineLength));
		ReadString_Mandatory(info->MarketID, &(info->MarketIDLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadString_Optional(info->MarketSegmentID, &(info->MarketSegmentIDLength));

		info->NewsTextCount = ReadUInt32_Mandatory();
		SpectraNewsNewsTextItemInfo* ntItemInfo = NULL;

		for(int i = 0; i < info->NewsTextCount; i++) {
			ntItemInfo = GetFreeSpectraNewsNewsTextItemInfo();
			info->NewsText[i] = ntItemInfo;
			ReadString_Mandatory(ntItemInfo->Text, &(ntItemInfo->TextLength));
			this->m_prevspectraNewsNewsTextItemInfo = ntItemInfo;
		}

		this->m_prevspectraNewsInfo = info;
		return info;
	}
	void* DecodeSpectraOrdersLog() {
		SpectraOrdersLogInfo* info = GetFreeSpectraOrdersLogInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->LastFragment = ReadUInt32_Mandatory();

		info->MDEntriesCount = ReadUInt32_Mandatory();
		SpectraOrdersLogMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeSpectraOrdersLogMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			mdeItemInfo->MDUpdateAction = ReadUInt32_Mandatory();
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->SecurityID = ReadUInt64_Optional();
			mdeItemInfo->SecurityIDSource = ReadUInt32_Mandatory();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				mdeItemInfo->RptSeq = ReadUInt32_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				mdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(mdeItemInfo->LastPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				mdeItemInfo->LastQty = ReadInt64_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				mdeItemInfo->TradeID = ReadInt64_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				mdeItemInfo->ExchangeTradingSessionID = ReadUInt32_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				mdeItemInfo->MDFlags = ReadInt64_Optional();
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				mdeItemInfo->Revision = ReadUInt64_Optional();
			this->m_prevspectraOrdersLogMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevspectraOrdersLogInfo = info;
		return info;
	}
	void* DecodeSpectraOrdersBook() {
		SpectraOrdersBookInfo* info = GetFreeSpectraOrdersBookInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->RptSeq = ReadUInt32_Optional();
		info->LastFragment = ReadUInt32_Mandatory();
		info->RouteFirst = ReadUInt32_Mandatory();
		info->ExchangeTradingSessionID = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional();
		info->SecurityIDSource = ReadUInt32_Mandatory();

		info->MDEntriesCount = ReadUInt32_Mandatory();
		SpectraOrdersBookMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeSpectraOrdersBookMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(CheckProcessNullUInt32())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				mdeItemInfo->TradeID = ReadInt64_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDFlags = ReadInt64_Optional();
			this->m_prevspectraOrdersBookMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevspectraOrdersBookInfo = info;
		return info;
	}
	void* DecodeSpectraLogon() {
		SpectraLogonInfo* info = GetFreeSpectraLogonInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevspectraLogonInfo = info;
		return info;
	}
	void* DecodeSpectraLogout() {
		SpectraLogoutInfo* info = GetFreeSpectraLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		this->m_prevspectraLogoutInfo = info;
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoDefaultIncrementalRefreshMessage() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastFragment = ReadUInt32_Optional();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoDefaultSnapshotMessage() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastFragment = ReadUInt32_Optional();
		info->RptSeq = ReadUInt32_Mandatory();
		SkipToNextField(); // TotNumReports
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		SkipToNextField(); // SecurityID
		SkipToNextField(); // SecurityIDSource
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadString_Optional(info->Symbol, &(info->SymbolLength));
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoSecurityDefinition() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TotNumReports
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		SkipToNextField(); // SecurityDesc
		SkipToNextField(); // SecurityID
		SkipToNextField(); // SecurityIDSource
		SkipToNextField(); // SecurityAltID
		SkipToNextField(); // SecurityAltIDSource
		SkipToNextField(); // SecurityType
		SkipToNextField(); // CFICode
		SkipToNextField(); // StrikePrice
		SkipToNextField(); // ContractMultiplier
		SkipToNextField(); // SecurityTradingStatus
		SkipToNextField(); // Currency
		SkipToNextField(); // MarketID
		SkipToNextField(); // MarketSegmentID
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX9;
		else
			info->TradingSessionID = ReadUInt32_Optional();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoSecurityDefinitionUpdateReport() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoSecurityStatus() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // SecurityID
		SkipToNextField(); // SecurityIDSource
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoHeartbeat() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoSequenceReset() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoTradingSessionStatus() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TradSesOpenTime
		SkipToNextField(); // TradSesCloseTime
		SkipToNextField(); // TradSesIntermClearingStartTime
		SkipToNextField(); // TradSesIntermClearingEndTime
		info->TradingSessionID = ReadUInt32_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoNews() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastFragment = ReadUInt32_Optional();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoOrdersLog() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		info->LastFragment = ReadUInt32_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoOrdersBook() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt32())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->RptSeq = ReadUInt32_Optional();
		info->LastFragment = ReadUInt32_Mandatory();
		info->RouteFirst = ReadUInt32_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoLogon() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	SpectraSnapshotInfo* GetSpectraSnapshotInfoLogout() {
		SpectraSnapshotInfo *info = GetFreeSpectraSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void* DecodeSpectra() {
		this->DecodeSpectraHeader();
		FastDecodeMethodPointer funcPtr = this->m_spectraDecodeMethods[this->m_templateId - 3];
		this->m_lastDecodedInfo = (this->*funcPtr)();
		return this->m_lastDecodedInfo;
	}
	void PrintSpectra() {

		switch(this->m_templateId) {
			case 12:
				PrintSpectraDefaultIncrementalRefreshMessage((SpectraDefaultIncrementalRefreshMessageInfo*)this->m_lastDecodedInfo);
				break;
			case 13:
				PrintSpectraDefaultSnapshotMessage((SpectraDefaultSnapshotMessageInfo*)this->m_lastDecodedInfo);
				break;
			case 3:
				PrintSpectraSecurityDefinition((SpectraSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 4:
				PrintSpectraSecurityDefinitionUpdateReport((SpectraSecurityDefinitionUpdateReportInfo*)this->m_lastDecodedInfo);
				break;
			case 5:
				PrintSpectraSecurityStatus((SpectraSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 6:
				PrintSpectraHeartbeat((SpectraHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
			case 7:
				PrintSpectraSequenceReset((SpectraSequenceResetInfo*)this->m_lastDecodedInfo);
				break;
			case 8:
				PrintSpectraTradingSessionStatus((SpectraTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 9:
				PrintSpectraNews((SpectraNewsInfo*)this->m_lastDecodedInfo);
				break;
			case 14:
				PrintSpectraOrdersLog((SpectraOrdersLogInfo*)this->m_lastDecodedInfo);
				break;
			case 15:
				PrintSpectraOrdersBook((SpectraOrdersBookInfo*)this->m_lastDecodedInfo);
				break;
			case 1000:
				PrintSpectraLogon((SpectraLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 1001:
				PrintSpectraLogout((SpectraLogoutInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	void PrintXmlSpectra() {

		switch(this->m_templateId) {
			case 12:
				PrintXmlSpectraDefaultIncrementalRefreshMessage((SpectraDefaultIncrementalRefreshMessageInfo*)this->m_lastDecodedInfo);
				break;
			case 13:
				PrintXmlSpectraDefaultSnapshotMessage((SpectraDefaultSnapshotMessageInfo*)this->m_lastDecodedInfo);
				break;
			case 3:
				PrintXmlSpectraSecurityDefinition((SpectraSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 4:
				PrintXmlSpectraSecurityDefinitionUpdateReport((SpectraSecurityDefinitionUpdateReportInfo*)this->m_lastDecodedInfo);
				break;
			case 5:
				PrintXmlSpectraSecurityStatus((SpectraSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 6:
				PrintXmlSpectraHeartbeat((SpectraHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
			case 7:
				PrintXmlSpectraSequenceReset((SpectraSequenceResetInfo*)this->m_lastDecodedInfo);
				break;
			case 8:
				PrintXmlSpectraTradingSessionStatus((SpectraTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 9:
				PrintXmlSpectraNews((SpectraNewsInfo*)this->m_lastDecodedInfo);
				break;
			case 14:
				PrintXmlSpectraOrdersLog((SpectraOrdersLogInfo*)this->m_lastDecodedInfo);
				break;
			case 15:
				PrintXmlSpectraOrdersBook((SpectraOrdersBookInfo*)this->m_lastDecodedInfo);
				break;
			case 1000:
				PrintXmlSpectraLogon((SpectraLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 1001:
				PrintXmlSpectraLogout((SpectraLogoutInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	inline SpectraSnapshotInfo* GetSpectraSnapshotInfo() {
		this->DecodeSpectraHeader();
		SpectraGetSnapshotInfoMethodPointer funcPtr = this->m_spectraGetSnapshotInfoMethods[this->m_templateId - 3];
		return (this->*funcPtr)();
	}
#pragma endregion
};

