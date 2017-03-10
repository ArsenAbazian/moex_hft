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
typedef FastSnapshotInfo* (FastProtocolManager::*FastGetSnapshotInfoMethodPointer)();
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

    FastSnapshotInfo 			*m_astsSnapshotInfo;
	SpectraSnapshotInfo 		*m_spectraSnapshotInfo;
	void						*m_lastDecodedInfo;

	UINT32						m_skipTemplateId[8];
	int							m_skipTemplateIdCount;
	FastObjectsAllocationInfo	*m_allocationInfoFast;
    SpectraObjectsAllocationInfo *m_allocationInfoSpectra;

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
	AutoAllocatePointerList<FastLogonInfo>	*m_fastLogon;
	AutoAllocatePointerList<FastLogoutInfo>	*m_fastLogout;
	AutoAllocatePointerList<FastGenericItemInfo>	*m_fastGenericItems;
	AutoAllocatePointerList<FastGenericInfo>	*m_fastGeneric;
	AutoAllocatePointerList<FastIncrementalGenericInfo>	*m_fastIncrementalGeneric;
	AutoAllocatePointerList<FastOLSFONDItemInfo>	*m_fastOLSFONDItems;
	AutoAllocatePointerList<FastOLSFONDInfo>	*m_fastOLSFOND;
	AutoAllocatePointerList<FastOLSCURRItemInfo>	*m_fastOLSCURRItems;
	AutoAllocatePointerList<FastOLSCURRInfo>	*m_fastOLSCURR;
	AutoAllocatePointerList<FastTLSFONDItemInfo>	*m_fastTLSFONDItems;
	AutoAllocatePointerList<FastTLSFONDInfo>	*m_fastTLSFOND;
	AutoAllocatePointerList<FastTLSCURRItemInfo>	*m_fastTLSCURRItems;
	AutoAllocatePointerList<FastTLSCURRInfo>	*m_fastTLSCURR;
	AutoAllocatePointerList<FastIncrementalMSRFONDInfo>	*m_fastIncrementalMSRFOND;
	AutoAllocatePointerList<FastIncrementalMSRCURRInfo>	*m_fastIncrementalMSRCURR;
	AutoAllocatePointerList<FastIncrementalOLRFONDInfo>	*m_fastIncrementalOLRFOND;
	AutoAllocatePointerList<FastIncrementalOLRCURRInfo>	*m_fastIncrementalOLRCURR;
	AutoAllocatePointerList<FastIncrementalTLRFONDInfo>	*m_fastIncrementalTLRFOND;
	AutoAllocatePointerList<FastIncrementalTLRCURRInfo>	*m_fastIncrementalTLRCURR;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>	*m_fastSecurityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>	*m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>	*m_fastSecurityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionInfo>	*m_fastSecurityDefinition;
	AutoAllocatePointerList<FastSecurityStatusInfo>	*m_fastSecurityStatus;
	AutoAllocatePointerList<FastTradingSessionStatusInfo>	*m_fastTradingSessionStatus;
	AutoAllocatePointerList<FastHeartbeatInfo>	*m_fastHeartbeat;
	FastLogonInfo	*m_prevfastLogonInfo;
	FastLogoutInfo	*m_prevfastLogoutInfo;
	FastGenericItemInfo	*m_prevfastGenericItemInfo;
	FastGenericInfo	*m_prevfastGenericInfo;
	FastIncrementalGenericInfo	*m_prevfastIncrementalGenericInfo;
	FastOLSFONDItemInfo	*m_prevfastOLSFONDItemInfo;
	FastOLSFONDInfo	*m_prevfastOLSFONDInfo;
	FastOLSCURRItemInfo	*m_prevfastOLSCURRItemInfo;
	FastOLSCURRInfo	*m_prevfastOLSCURRInfo;
	FastTLSFONDItemInfo	*m_prevfastTLSFONDItemInfo;
	FastTLSFONDInfo	*m_prevfastTLSFONDInfo;
	FastTLSCURRItemInfo	*m_prevfastTLSCURRItemInfo;
	FastTLSCURRInfo	*m_prevfastTLSCURRInfo;
	FastIncrementalMSRFONDInfo	*m_prevfastIncrementalMSRFONDInfo;
	FastIncrementalMSRCURRInfo	*m_prevfastIncrementalMSRCURRInfo;
	FastIncrementalOLRFONDInfo	*m_prevfastIncrementalOLRFONDInfo;
	FastIncrementalOLRCURRInfo	*m_prevfastIncrementalOLRCURRInfo;
	FastIncrementalTLRFONDInfo	*m_prevfastIncrementalTLRFONDInfo;
	FastIncrementalTLRCURRInfo	*m_prevfastIncrementalTLRCURRInfo;
	FastSecurityDefinitionGroupInstrAttribItemInfo	*m_prevfastSecurityDefinitionGroupInstrAttribItemInfo;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo	*m_prevfastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;
	FastSecurityDefinitionMarketSegmentGrpItemInfo	*m_prevfastSecurityDefinitionMarketSegmentGrpItemInfo;
	FastSecurityDefinitionInfo	*m_prevfastSecurityDefinitionInfo;
	FastSecurityStatusInfo	*m_prevfastSecurityStatusInfo;
	FastTradingSessionStatusInfo	*m_prevfastTradingSessionStatusInfo;
	FastHeartbeatInfo	*m_prevfastHeartbeatInfo;

	void InitializeFastMessageInfo() {
		this->m_fastLogon = this->m_allocationInfoFast->GetFastLogonInfoPool();
		this->m_fastLogout = this->m_allocationInfoFast->GetFastLogoutInfoPool();
		this->m_fastGenericItems = this->m_allocationInfoFast->GetFastGenericItemInfoPool();
		this->m_fastGeneric = this->m_allocationInfoFast->GetFastGenericInfoPool();
		this->m_fastIncrementalGeneric = this->m_allocationInfoFast->GetFastIncrementalGenericInfoPool();
		this->m_fastOLSFONDItems = this->m_allocationInfoFast->GetFastOLSFONDItemInfoPool();
		this->m_fastOLSFOND = this->m_allocationInfoFast->GetFastOLSFONDInfoPool();
		this->m_fastOLSCURRItems = this->m_allocationInfoFast->GetFastOLSCURRItemInfoPool();
		this->m_fastOLSCURR = this->m_allocationInfoFast->GetFastOLSCURRInfoPool();
		this->m_fastTLSFONDItems = this->m_allocationInfoFast->GetFastTLSFONDItemInfoPool();
		this->m_fastTLSFOND = this->m_allocationInfoFast->GetFastTLSFONDInfoPool();
		this->m_fastTLSCURRItems = this->m_allocationInfoFast->GetFastTLSCURRItemInfoPool();
		this->m_fastTLSCURR = this->m_allocationInfoFast->GetFastTLSCURRInfoPool();
		this->m_fastIncrementalMSRFOND = this->m_allocationInfoFast->GetFastIncrementalMSRFONDInfoPool();
		this->m_fastIncrementalMSRCURR = this->m_allocationInfoFast->GetFastIncrementalMSRCURRInfoPool();
		this->m_fastIncrementalOLRFOND = this->m_allocationInfoFast->GetFastIncrementalOLRFONDInfoPool();
		this->m_fastIncrementalOLRCURR = this->m_allocationInfoFast->GetFastIncrementalOLRCURRInfoPool();
		this->m_fastIncrementalTLRFOND = this->m_allocationInfoFast->GetFastIncrementalTLRFONDInfoPool();
		this->m_fastIncrementalTLRCURR = this->m_allocationInfoFast->GetFastIncrementalTLRCURRInfoPool();
		this->m_fastSecurityDefinitionGroupInstrAttribItems = this->m_allocationInfoFast->GetFastSecurityDefinitionGroupInstrAttribItemInfoPool();
		this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = this->m_allocationInfoFast->GetFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool();
		this->m_fastSecurityDefinitionMarketSegmentGrpItems = this->m_allocationInfoFast->GetFastSecurityDefinitionMarketSegmentGrpItemInfoPool();
		this->m_fastSecurityDefinition = this->m_allocationInfoFast->GetFastSecurityDefinitionInfoPool();
		this->m_fastSecurityStatus = this->m_allocationInfoFast->GetFastSecurityStatusInfoPool();
		this->m_fastTradingSessionStatus = this->m_allocationInfoFast->GetFastTradingSessionStatusInfoPool();
		this->m_fastHeartbeat = this->m_allocationInfoFast->GetFastHeartbeatInfoPool();
		this->m_prevfastLogonInfo = this->GetFreeFastLogonInfo();
		this->m_prevfastLogonInfo->Used = true;
		this->m_prevfastLogoutInfo = this->GetFreeFastLogoutInfo();
		this->m_prevfastLogoutInfo->Used = true;
		this->m_prevfastGenericItemInfo = this->GetFreeFastGenericItemInfo();
		this->m_prevfastGenericItemInfo->Used = true;
		this->m_prevfastGenericInfo = this->GetFreeFastGenericInfo();
		this->m_prevfastGenericInfo->Used = true;
		this->m_prevfastIncrementalGenericInfo = this->GetFreeFastIncrementalGenericInfo();
		this->m_prevfastIncrementalGenericInfo->Used = true;
		this->m_prevfastOLSFONDItemInfo = this->GetFreeFastOLSFONDItemInfo();
		this->m_prevfastOLSFONDItemInfo->Used = true;
		this->m_prevfastOLSFONDInfo = this->GetFreeFastOLSFONDInfo();
		this->m_prevfastOLSFONDInfo->Used = true;
		this->m_prevfastOLSCURRItemInfo = this->GetFreeFastOLSCURRItemInfo();
		this->m_prevfastOLSCURRItemInfo->Used = true;
		this->m_prevfastOLSCURRInfo = this->GetFreeFastOLSCURRInfo();
		this->m_prevfastOLSCURRInfo->Used = true;
		this->m_prevfastTLSFONDItemInfo = this->GetFreeFastTLSFONDItemInfo();
		this->m_prevfastTLSFONDItemInfo->Used = true;
		this->m_prevfastTLSFONDInfo = this->GetFreeFastTLSFONDInfo();
		this->m_prevfastTLSFONDInfo->Used = true;
		this->m_prevfastTLSCURRItemInfo = this->GetFreeFastTLSCURRItemInfo();
		this->m_prevfastTLSCURRItemInfo->Used = true;
		this->m_prevfastTLSCURRInfo = this->GetFreeFastTLSCURRInfo();
		this->m_prevfastTLSCURRInfo->Used = true;
		this->m_prevfastIncrementalMSRFONDInfo = this->GetFreeFastIncrementalMSRFONDInfo();
		this->m_prevfastIncrementalMSRFONDInfo->Used = true;
		this->m_prevfastIncrementalMSRCURRInfo = this->GetFreeFastIncrementalMSRCURRInfo();
		this->m_prevfastIncrementalMSRCURRInfo->Used = true;
		this->m_prevfastIncrementalOLRFONDInfo = this->GetFreeFastIncrementalOLRFONDInfo();
		this->m_prevfastIncrementalOLRFONDInfo->Used = true;
		this->m_prevfastIncrementalOLRCURRInfo = this->GetFreeFastIncrementalOLRCURRInfo();
		this->m_prevfastIncrementalOLRCURRInfo->Used = true;
		this->m_prevfastIncrementalTLRFONDInfo = this->GetFreeFastIncrementalTLRFONDInfo();
		this->m_prevfastIncrementalTLRFONDInfo->Used = true;
		this->m_prevfastIncrementalTLRCURRInfo = this->GetFreeFastIncrementalTLRCURRInfo();
		this->m_prevfastIncrementalTLRCURRInfo->Used = true;
		this->m_prevfastSecurityDefinitionGroupInstrAttribItemInfo = this->GetFreeFastSecurityDefinitionGroupInstrAttribItemInfo();
		this->m_prevfastSecurityDefinitionGroupInstrAttribItemInfo->Used = true;
		this->m_prevfastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = this->GetFreeFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
		this->m_prevfastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo->Used = true;
		this->m_prevfastSecurityDefinitionMarketSegmentGrpItemInfo = this->GetFreeFastSecurityDefinitionMarketSegmentGrpItemInfo();
		this->m_prevfastSecurityDefinitionMarketSegmentGrpItemInfo->Used = true;
		this->m_prevfastSecurityDefinitionInfo = this->GetFreeFastSecurityDefinitionInfo();
		this->m_prevfastSecurityDefinitionInfo->Used = true;
		this->m_prevfastSecurityStatusInfo = this->GetFreeFastSecurityStatusInfo();
		this->m_prevfastSecurityStatusInfo->Used = true;
		this->m_prevfastTradingSessionStatusInfo = this->GetFreeFastTradingSessionStatusInfo();
		this->m_prevfastTradingSessionStatusInfo->Used = true;
		this->m_prevfastHeartbeatInfo = this->GetFreeFastHeartbeatInfo();
		this->m_prevfastHeartbeatInfo->Used = true;
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
		this->m_spectraDefaultIncrementalRefreshMessageMDEntriesItems = this->m_allocationInfoSpectra->GetSpectraDefaultIncrementalRefreshMessageMDEntriesItemInfoPool();
		this->m_spectraDefaultIncrementalRefreshMessage = this->m_allocationInfoSpectra->GetSpectraDefaultIncrementalRefreshMessageInfoPool();
		this->m_spectraDefaultSnapshotMessageMDEntriesItems = this->m_allocationInfoSpectra->GetSpectraDefaultSnapshotMessageMDEntriesItemInfoPool();
		this->m_spectraDefaultSnapshotMessage = this->m_allocationInfoSpectra->GetSpectraDefaultSnapshotMessageInfoPool();
		this->m_spectraSecurityDefinitionMDFeedTypesItems = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionMDFeedTypesItemInfoPool();
		this->m_spectraSecurityDefinitionUnderlyingsItems = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionUnderlyingsItemInfoPool();
		this->m_spectraSecurityDefinitionInstrumentLegsItems = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionInstrumentLegsItemInfoPool();
		this->m_spectraSecurityDefinitionInstrumentAttributesItems = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionInstrumentAttributesItemInfoPool();
		this->m_spectraSecurityDefinitionEvntGrpItems = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionEvntGrpItemInfoPool();
		this->m_spectraSecurityDefinition = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionInfoPool();
		this->m_spectraSecurityDefinitionUpdateReport = this->m_allocationInfoSpectra->GetSpectraSecurityDefinitionUpdateReportInfoPool();
		this->m_spectraSecurityStatus = this->m_allocationInfoSpectra->GetSpectraSecurityStatusInfoPool();
		this->m_spectraHeartbeat = this->m_allocationInfoSpectra->GetSpectraHeartbeatInfoPool();
		this->m_spectraSequenceReset = this->m_allocationInfoSpectra->GetSpectraSequenceResetInfoPool();
		this->m_spectraTradingSessionStatus = this->m_allocationInfoSpectra->GetSpectraTradingSessionStatusInfoPool();
		this->m_spectraNewsNewsTextItems = this->m_allocationInfoSpectra->GetSpectraNewsNewsTextItemInfoPool();
		this->m_spectraNews = this->m_allocationInfoSpectra->GetSpectraNewsInfoPool();
		this->m_spectraOrdersLogMDEntriesItems = this->m_allocationInfoSpectra->GetSpectraOrdersLogMDEntriesItemInfoPool();
		this->m_spectraOrdersLog = this->m_allocationInfoSpectra->GetSpectraOrdersLogInfoPool();
		this->m_spectraOrdersBookMDEntriesItems = this->m_allocationInfoSpectra->GetSpectraOrdersBookMDEntriesItemInfoPool();
		this->m_spectraOrdersBook = this->m_allocationInfoSpectra->GetSpectraOrdersBookInfoPool();
		this->m_spectraLogon = this->m_allocationInfoSpectra->GetSpectraLogonInfoPool();
		this->m_spectraLogout = this->m_allocationInfoSpectra->GetSpectraLogoutInfoPool();
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

	FastDecodeMethodPointer* m_fastDecodeMethods;
	FastReleaseMethodPointer* m_fastReleaseMethods;
	FastGetSnapshotInfoMethodPointer* m_fastGetSnapshotInfoMethods;

	void InitializeFastDecodeMethodPointers() {
		int ptCount = 1513;
		this->m_fastDecodeMethods = new FastDecodeMethodPointer[ptCount];
		this->m_fastReleaseMethods = new FastReleaseMethodPointer[ptCount];
		this->m_fastGetSnapshotInfoMethods = new FastGetSnapshotInfoMethodPointer[ptCount];

		for(int i = 0; i < 1513; i++) {
			this->m_fastDecodeMethods[i] = &FastProtocolManager::DecodeFastUnsupportedMessage;
			this->m_fastGetSnapshotInfoMethods[i] = &FastProtocolManager::GetFastSnapshotInfoUnsupported;
		}

		this->m_fastDecodeMethods[2101 - 2101] = &FastProtocolManager::DecodeFastLogon;
		this->m_fastDecodeMethods[2102 - 2101] = &FastProtocolManager::DecodeFastLogout;
		this->m_fastDecodeMethods[2103 - 2101] = &FastProtocolManager::DecodeFastGeneric;
		this->m_fastDecodeMethods[2104 - 2101] = &FastProtocolManager::DecodeFastIncrementalGeneric;
		this->m_fastDecodeMethods[2510 - 2101] = &FastProtocolManager::DecodeFastOLSFOND;
		this->m_fastDecodeMethods[3600 - 2101] = &FastProtocolManager::DecodeFastOLSCURR;
		this->m_fastDecodeMethods[2511 - 2101] = &FastProtocolManager::DecodeFastTLSFOND;
		this->m_fastDecodeMethods[3601 - 2101] = &FastProtocolManager::DecodeFastTLSCURR;
		this->m_fastDecodeMethods[2523 - 2101] = &FastProtocolManager::DecodeFastIncrementalMSRFOND;
		this->m_fastDecodeMethods[3613 - 2101] = &FastProtocolManager::DecodeFastIncrementalMSRCURR;
		this->m_fastDecodeMethods[2520 - 2101] = &FastProtocolManager::DecodeFastIncrementalOLRFOND;
		this->m_fastDecodeMethods[3610 - 2101] = &FastProtocolManager::DecodeFastIncrementalOLRCURR;
		this->m_fastDecodeMethods[2521 - 2101] = &FastProtocolManager::DecodeFastIncrementalTLRFOND;
		this->m_fastDecodeMethods[3611 - 2101] = &FastProtocolManager::DecodeFastIncrementalTLRCURR;
		this->m_fastDecodeMethods[2115 - 2101] = &FastProtocolManager::DecodeFastSecurityDefinition;
		this->m_fastDecodeMethods[2106 - 2101] = &FastProtocolManager::DecodeFastSecurityStatus;
		this->m_fastDecodeMethods[2107 - 2101] = &FastProtocolManager::DecodeFastTradingSessionStatus;
		this->m_fastDecodeMethods[2108 - 2101] = &FastProtocolManager::DecodeFastHeartbeat;
		this->m_fastReleaseMethods[2101 - 2101] = &FastProtocolManager::DecodeFastLogon;
		this->m_fastReleaseMethods[2102 - 2101] = &FastProtocolManager::DecodeFastLogout;
		this->m_fastReleaseMethods[2103 - 2101] = &FastProtocolManager::DecodeFastGeneric;
		this->m_fastReleaseMethods[2104 - 2101] = &FastProtocolManager::DecodeFastIncrementalGeneric;
		this->m_fastReleaseMethods[2510 - 2101] = &FastProtocolManager::DecodeFastOLSFOND;
		this->m_fastReleaseMethods[3600 - 2101] = &FastProtocolManager::DecodeFastOLSCURR;
		this->m_fastReleaseMethods[2511 - 2101] = &FastProtocolManager::DecodeFastTLSFOND;
		this->m_fastReleaseMethods[3601 - 2101] = &FastProtocolManager::DecodeFastTLSCURR;
		this->m_fastReleaseMethods[2523 - 2101] = &FastProtocolManager::DecodeFastIncrementalMSRFOND;
		this->m_fastReleaseMethods[3613 - 2101] = &FastProtocolManager::DecodeFastIncrementalMSRCURR;
		this->m_fastReleaseMethods[2520 - 2101] = &FastProtocolManager::DecodeFastIncrementalOLRFOND;
		this->m_fastReleaseMethods[3610 - 2101] = &FastProtocolManager::DecodeFastIncrementalOLRCURR;
		this->m_fastReleaseMethods[2521 - 2101] = &FastProtocolManager::DecodeFastIncrementalTLRFOND;
		this->m_fastReleaseMethods[3611 - 2101] = &FastProtocolManager::DecodeFastIncrementalTLRCURR;
		this->m_fastReleaseMethods[2115 - 2101] = &FastProtocolManager::DecodeFastSecurityDefinition;
		this->m_fastReleaseMethods[2106 - 2101] = &FastProtocolManager::DecodeFastSecurityStatus;
		this->m_fastReleaseMethods[2107 - 2101] = &FastProtocolManager::DecodeFastTradingSessionStatus;
		this->m_fastReleaseMethods[2108 - 2101] = &FastProtocolManager::DecodeFastHeartbeat;
		this->m_fastGetSnapshotInfoMethods[2103 - 2101] = &FastProtocolManager::GetFastSnapshotInfoGeneric;
		this->m_fastGetSnapshotInfoMethods[2510 - 2101] = &FastProtocolManager::GetFastSnapshotInfoOLSFOND;
		this->m_fastGetSnapshotInfoMethods[3600 - 2101] = &FastProtocolManager::GetFastSnapshotInfoOLSCURR;
		this->m_fastGetSnapshotInfoMethods[2511 - 2101] = &FastProtocolManager::GetFastSnapshotInfoTLSFOND;
		this->m_fastGetSnapshotInfoMethods[3601 - 2101] = &FastProtocolManager::GetFastSnapshotInfoTLSCURR;

	}

#pragma endregion

    inline FastSnapshotInfo* GetFreeFastSnapshotInfo() {
        this->m_astsSnapshotInfo->LastFragment = 0;
        this->m_astsSnapshotInfo->LastMsgSeqNumProcessed = -1;
        this->m_astsSnapshotInfo->RouteFirst = 0;
        this->m_astsSnapshotInfo->RptSeq = -1;
        return this->m_astsSnapshotInfo;
    }

	inline SpectraSnapshotInfo* GetFreeSpectraSnapshotInfo() {
		this->m_spectraSnapshotInfo->LastFragment = 0;
		this->m_spectraSnapshotInfo->LastMsgSeqNumProcessed = -1;
		this->m_spectraSnapshotInfo->RouteFirst = 0;
		this->m_spectraSnapshotInfo->RptSeq = -1;
		return this->m_spectraSnapshotInfo;
	}

#pragma region Get_Free_Item_Methods_GeneratedCode
public:
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
	inline FastLogonInfo* GetFreeFastLogonInfo() {
		return this->m_fastLogon->NewItem();
	}

	inline AutoAllocatePointerList<FastLogonInfo>* GetFastLogonInfoPool() {
		return this->m_fastLogon;
	}

	inline FastLogoutInfo* GetFreeFastLogoutInfo() {
		return this->m_fastLogout->NewItem();
	}

	inline AutoAllocatePointerList<FastLogoutInfo>* GetFastLogoutInfoPool() {
		return this->m_fastLogout;
	}

	inline FastGenericItemInfo* GetFreeFastGenericItemInfo() {
		return this->m_fastGenericItems->NewItem();
	}

	inline AutoAllocatePointerList<FastGenericItemInfo>* GetFastGenericItemInfoPool() {
		return this->m_fastGenericItems;
	}

	inline FastGenericInfo* GetFreeFastGenericInfo() {
		return this->m_fastGeneric->NewItem();
	}

	inline AutoAllocatePointerList<FastGenericInfo>* GetFastGenericInfoPool() {
		return this->m_fastGeneric;
	}

	inline FastIncrementalGenericInfo* GetFreeFastIncrementalGenericInfo() {
		return this->m_fastIncrementalGeneric->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalGenericInfo>* GetFastIncrementalGenericInfoPool() {
		return this->m_fastIncrementalGeneric;
	}

	inline FastOLSFONDItemInfo* GetFreeFastOLSFONDItemInfo() {
		return this->m_fastOLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSFONDItemInfo>* GetFastOLSFONDItemInfoPool() {
		return this->m_fastOLSFONDItems;
	}

	inline FastOLSFONDInfo* GetFreeFastOLSFONDInfo() {
		return this->m_fastOLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSFONDInfo>* GetFastOLSFONDInfoPool() {
		return this->m_fastOLSFOND;
	}

	inline FastOLSCURRItemInfo* GetFreeFastOLSCURRItemInfo() {
		return this->m_fastOLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSCURRItemInfo>* GetFastOLSCURRItemInfoPool() {
		return this->m_fastOLSCURRItems;
	}

	inline FastOLSCURRInfo* GetFreeFastOLSCURRInfo() {
		return this->m_fastOLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastOLSCURRInfo>* GetFastOLSCURRInfoPool() {
		return this->m_fastOLSCURR;
	}

	inline FastTLSFONDItemInfo* GetFreeFastTLSFONDItemInfo() {
		return this->m_fastTLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSFONDItemInfo>* GetFastTLSFONDItemInfoPool() {
		return this->m_fastTLSFONDItems;
	}

	inline FastTLSFONDInfo* GetFreeFastTLSFONDInfo() {
		return this->m_fastTLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSFONDInfo>* GetFastTLSFONDInfoPool() {
		return this->m_fastTLSFOND;
	}

	inline FastTLSCURRItemInfo* GetFreeFastTLSCURRItemInfo() {
		return this->m_fastTLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSCURRItemInfo>* GetFastTLSCURRItemInfoPool() {
		return this->m_fastTLSCURRItems;
	}

	inline FastTLSCURRInfo* GetFreeFastTLSCURRInfo() {
		return this->m_fastTLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastTLSCURRInfo>* GetFastTLSCURRInfoPool() {
		return this->m_fastTLSCURR;
	}

	inline FastIncrementalMSRFONDInfo* GetFreeFastIncrementalMSRFONDInfo() {
		return this->m_fastIncrementalMSRFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalMSRFONDInfo>* GetFastIncrementalMSRFONDInfoPool() {
		return this->m_fastIncrementalMSRFOND;
	}

	inline FastIncrementalMSRCURRInfo* GetFreeFastIncrementalMSRCURRInfo() {
		return this->m_fastIncrementalMSRCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalMSRCURRInfo>* GetFastIncrementalMSRCURRInfoPool() {
		return this->m_fastIncrementalMSRCURR;
	}

	inline FastIncrementalOLRFONDInfo* GetFreeFastIncrementalOLRFONDInfo() {
		return this->m_fastIncrementalOLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalOLRFONDInfo>* GetFastIncrementalOLRFONDInfoPool() {
		return this->m_fastIncrementalOLRFOND;
	}

	inline FastIncrementalOLRCURRInfo* GetFreeFastIncrementalOLRCURRInfo() {
		return this->m_fastIncrementalOLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalOLRCURRInfo>* GetFastIncrementalOLRCURRInfoPool() {
		return this->m_fastIncrementalOLRCURR;
	}

	inline FastIncrementalTLRFONDInfo* GetFreeFastIncrementalTLRFONDInfo() {
		return this->m_fastIncrementalTLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalTLRFONDInfo>* GetFastIncrementalTLRFONDInfoPool() {
		return this->m_fastIncrementalTLRFOND;
	}

	inline FastIncrementalTLRCURRInfo* GetFreeFastIncrementalTLRCURRInfo() {
		return this->m_fastIncrementalTLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<FastIncrementalTLRCURRInfo>* GetFastIncrementalTLRCURRInfoPool() {
		return this->m_fastIncrementalTLRCURR;
	}

	inline FastSecurityDefinitionGroupInstrAttribItemInfo* GetFreeFastSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_fastSecurityDefinitionGroupInstrAttribItems->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>* GetFastSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_fastSecurityDefinitionGroupInstrAttribItems;
	}

	inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_fastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}

	inline FastSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeFastSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_fastSecurityDefinitionMarketSegmentGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>* GetFastSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_fastSecurityDefinitionMarketSegmentGrpItems;
	}

	inline FastSecurityDefinitionInfo* GetFreeFastSecurityDefinitionInfo() {
		return this->m_fastSecurityDefinition->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityDefinitionInfo>* GetFastSecurityDefinitionInfoPool() {
		return this->m_fastSecurityDefinition;
	}

	inline FastSecurityStatusInfo* GetFreeFastSecurityStatusInfo() {
		return this->m_fastSecurityStatus->NewItem();
	}

	inline AutoAllocatePointerList<FastSecurityStatusInfo>* GetFastSecurityStatusInfoPool() {
		return this->m_fastSecurityStatus;
	}

	inline FastTradingSessionStatusInfo* GetFreeFastTradingSessionStatusInfo() {
		return this->m_fastTradingSessionStatus->NewItem();
	}

	inline AutoAllocatePointerList<FastTradingSessionStatusInfo>* GetFastTradingSessionStatusInfoPool() {
		return this->m_fastTradingSessionStatus;
	}

	inline FastHeartbeatInfo* GetFreeFastHeartbeatInfo() {
		return this->m_fastHeartbeat->NewItem();
	}

	inline AutoAllocatePointerList<FastHeartbeatInfo>* GetFastHeartbeatInfoPool() {
		return this->m_fastHeartbeat;
	}

private:
	void ReleaseFastLogonInfo() {
		((FastLogonInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastLogoutInfo() {
		((FastLogoutInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastGenericItemInfo() {
		((FastGenericItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastGenericInfo() {
		((FastGenericInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalGenericInfo() {
		((FastIncrementalGenericInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastOLSFONDItemInfo() {
		((FastOLSFONDItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastOLSFONDInfo() {
		((FastOLSFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastOLSCURRItemInfo() {
		((FastOLSCURRItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastOLSCURRInfo() {
		((FastOLSCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastTLSFONDItemInfo() {
		((FastTLSFONDItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastTLSFONDInfo() {
		((FastTLSFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastTLSCURRItemInfo() {
		((FastTLSCURRItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastTLSCURRInfo() {
		((FastTLSCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalMSRFONDInfo() {
		((FastIncrementalMSRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalMSRCURRInfo() {
		((FastIncrementalMSRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalOLRFONDInfo() {
		((FastIncrementalOLRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalOLRCURRInfo() {
		((FastIncrementalOLRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalTLRFONDInfo() {
		((FastIncrementalTLRFONDInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastIncrementalTLRCURRInfo() {
		((FastIncrementalTLRCURRInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastSecurityDefinitionGroupInstrAttribItemInfo() {
		((FastSecurityDefinitionGroupInstrAttribItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		((FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastSecurityDefinitionMarketSegmentGrpItemInfo() {
		((FastSecurityDefinitionMarketSegmentGrpItemInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastSecurityDefinitionInfo() {
		((FastSecurityDefinitionInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastSecurityStatusInfo() {
		((FastSecurityStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastTradingSessionStatusInfo() {
		((FastTradingSessionStatusInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFastHeartbeatInfo() {
		((FastHeartbeatInfo*)this->LastDecodeInfo())->ReleaseUnused();
	}
	inline void ResetFast() {
		FastReleaseMethodPointer funcPtr = this->m_fastReleaseMethods[this->m_templateId - 2101];
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

	FastProtocolManager(FastObjectsAllocationInfo *allocInfo);
	FastProtocolManager();
	~FastProtocolManager();

	inline BYTE* Buffer() { return this->buffer; }
	inline BYTE* CurrentPos() { return this->currentPos; }
	inline int BufferLength() { return this->bufferLength; }
	inline int MessageLength() { return this->currentPos - this->buffer; }
	inline void SetBufferLength(int value) { this->bufferLength = value; }

    void* DecodeFastUnsupportedMessage() {
        return 0;
    }

	void* DecodeSpectraUnsupportedMessage() {
		return 0;
	}

	FastSnapshotInfo* GetFastSnapshotInfoUnsupported() {
		return 0;
	}

	SpectraSnapshotInfo* GetSpectraSnapshotInfoUnsupported() {
		return 0;
	}
#pragma region Asts_Encode_Methods_Declaration_GeneratedCode
	void EncodeFastLogonInfo(FastLogonInfo* info);
	void EncodeFastLogoutInfo(FastLogoutInfo* info);
	void EncodeFastGenericInfo(FastGenericInfo* info);
	void EncodeFastIncrementalGenericInfo(FastIncrementalGenericInfo* info);
	void EncodeFastOLSFONDInfo(FastOLSFONDInfo* info);
	void EncodeFastOLSCURRInfo(FastOLSCURRInfo* info);
	void EncodeFastTLSFONDInfo(FastTLSFONDInfo* info);
	void EncodeFastTLSCURRInfo(FastTLSCURRInfo* info);
	void EncodeFastIncrementalMSRFONDInfo(FastIncrementalMSRFONDInfo* info);
	void EncodeFastIncrementalMSRCURRInfo(FastIncrementalMSRCURRInfo* info);
	void EncodeFastIncrementalOLRFONDInfo(FastIncrementalOLRFONDInfo* info);
	void EncodeFastIncrementalOLRCURRInfo(FastIncrementalOLRCURRInfo* info);
	void EncodeFastIncrementalTLRFONDInfo(FastIncrementalTLRFONDInfo* info);
	void EncodeFastIncrementalTLRCURRInfo(FastIncrementalTLRCURRInfo* info);
	void EncodeFastSecurityDefinitionInfo(FastSecurityDefinitionInfo* info);
	void EncodeFastSecurityStatusInfo(FastSecurityStatusInfo* info);
	void EncodeFastTradingSessionStatusInfo(FastTradingSessionStatusInfo* info);
	void EncodeFastHeartbeatInfo(FastHeartbeatInfo* info);
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

#pragma region Asts_Print_Methods_Declaration_GeneratedCode

#pragma endregion

#pragma region Spectra_Print_Methods_Declaration_GeneratedCode

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

#pragma region Asts_Decode_Methods_Definition_GeneratedCode
	inline void DecodeFastHeader() {

		this->ParsePresenceMap(&(this->m_presenceMap));
		this->m_templateId = ReadUInt32_Mandatory();
	}

	int GetFastTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Optional();
	}
	void* DecodeFastLogon() {
		FastLogonInfo* info = GetFreeFastLogonInfo();
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
		this->m_prevfastLogonInfo = info;
		return info;
	}
	void* DecodeFastLogout() {
		FastLogoutInfo* info = GetFreeFastLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		this->m_prevfastLogoutInfo = info;
		return info;
	}
	void* DecodeFastGeneric() {
		FastGenericInfo* info = GetFreeFastGenericInfo();
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
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastGenericItemInfo();
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
			this->m_prevfastGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevfastGenericInfo = info;
		return info;
	}
	void* DecodeFastIncrementalGeneric() {
		FastIncrementalGenericInfo* info = GetFreeFastIncrementalGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastGenericItemInfo();
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
			this->m_prevfastGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalGenericInfo = info;
		return info;
	}
	void* DecodeFastOLSFOND() {
		FastOLSFONDInfo* info = GetFreeFastOLSFONDInfo();
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
		FastOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevfastOLSFONDItemInfo->MDEntryType, m_prevfastOLSFONDItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevfastOLSFONDItemInfo->MDEntryTypeLength;
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
				gmdeItemInfo->MDEntryDate = this->m_prevfastOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevfastOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevfastOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevfastOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevfastOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevfastOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevfastOLSFONDItemInfo->OrderStatus, m_prevfastOLSFONDItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevfastOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrdType, m_prevfastOLSFONDItemInfo->OrdType, m_prevfastOLSFONDItemInfo->OrdTypeLength);
				gmdeItemInfo->OrdTypeLength = this->m_prevfastOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevfastOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevfastOLSFONDItemInfo->TradingSessionSubID, m_prevfastOLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevfastOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevfastOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevfastOLSFONDInfo = info;
		return info;
	}
	void* DecodeFastOLSCURR() {
		FastOLSCURRInfo* info = GetFreeFastOLSCURRInfo();
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
		FastOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevfastOLSCURRItemInfo->MDEntryType, m_prevfastOLSCURRItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevfastOLSCURRItemInfo->MDEntryTypeLength;
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
				gmdeItemInfo->MDEntryDate = this->m_prevfastOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevfastOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevfastOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevfastOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevfastOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevfastOLSCURRItemInfo->OrderStatus, m_prevfastOLSCURRItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevfastOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevfastOLSCURRItemInfo->TradingSessionSubID, m_prevfastOLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevfastOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevfastOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevfastOLSCURRInfo = info;
		return info;
	}
	void* DecodeFastTLSFOND() {
		FastTLSFONDInfo* info = GetFreeFastTLSFONDInfo();
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
		FastTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastTLSFONDItemInfo();
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
				gmdeItemInfo->MDEntryDate = this->m_prevfastTLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevfastTLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevfastTLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevfastTLSFONDItemInfo->OrderSide, m_prevfastTLSFONDItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevfastTLSFONDItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevfastTLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevfastTLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			}
			else {
				gmdeItemInfo->AccruedInterestAmt = this->m_prevfastTLSFONDItemInfo->AccruedInterestAmt;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevfastTLSFONDItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevfastTLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevfastTLSFONDItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevfastTLSFONDItemInfo->SettleType, m_prevfastTLSFONDItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevfastTLSFONDItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
			}
			else {
				gmdeItemInfo->Price = this->m_prevfastTLSFONDItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					gmdeItemInfo->PriceType = ReadInt32_Optional();
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevfastTLSFONDItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevfastTLSFONDItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevfastTLSFONDItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
				else
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevfastTLSFONDItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX16)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevfastTLSFONDItemInfo->TradingSessionSubID, m_prevfastTLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevfastTLSFONDItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX17)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
				else
					ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevfastTLSFONDItemInfo->RefOrderID, m_prevfastTLSFONDItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevfastTLSFONDItemInfo->RefOrderIDLength;
			}
			this->m_prevfastTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevfastTLSFONDInfo = info;
		return info;
	}
	void* DecodeFastTLSCURR() {
		FastTLSCURRInfo* info = GetFreeFastTLSCURRInfo();
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
		FastTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastTLSCURRItemInfo();
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
				gmdeItemInfo->MDEntryDate = this->m_prevfastTLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevfastTLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevfastTLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevfastTLSCURRItemInfo->OrderSide, m_prevfastTLSCURRItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevfastTLSCURRItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevfastTLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevfastTLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevfastTLSCURRItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevfastTLSCURRItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevfastTLSCURRItemInfo->SettleType, m_prevfastTLSCURRItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevfastTLSCURRItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
			}
			else {
				gmdeItemInfo->Price = this->m_prevfastTLSCURRItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					gmdeItemInfo->PriceType = ReadInt32_Optional();
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevfastTLSCURRItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevfastTLSCURRItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevfastTLSCURRItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevfastTLSCURRItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevfastTLSCURRItemInfo->TradingSessionSubID, m_prevfastTLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevfastTLSCURRItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
				else
					ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevfastTLSCURRItemInfo->RefOrderID, m_prevfastTLSCURRItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevfastTLSCURRItemInfo->RefOrderIDLength;
			}
			this->m_prevfastTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevfastTLSCURRInfo = info;
		return info;
	}
	void* DecodeFastIncrementalMSRFOND() {
		FastIncrementalMSRFONDInfo* info = GetFreeFastIncrementalMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastGenericItemInfo();
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
			this->m_prevfastGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalMSRFONDInfo = info;
		return info;
	}
	void* DecodeFastIncrementalMSRCURR() {
		FastIncrementalMSRCURRInfo* info = GetFreeFastIncrementalMSRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastGenericItemInfo();
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
			this->m_prevfastGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalMSRCURRInfo = info;
		return info;
	}
	void* DecodeFastIncrementalOLRFOND() {
		FastIncrementalOLRFONDInfo* info = GetFreeFastIncrementalOLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastOLSFONDItemInfo();
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
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevfastOLSFONDItemInfo->MDEntryType, m_prevfastOLSFONDItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevfastOLSFONDItemInfo->MDEntryTypeLength;
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
				this->CopyString(gmdeItemInfo->Symbol, m_prevfastOLSFONDItemInfo->Symbol, m_prevfastOLSFONDItemInfo->SymbolLength);
				gmdeItemInfo->SymbolLength = this->m_prevfastOLSFONDItemInfo->SymbolLength;
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
				gmdeItemInfo->MDEntryDate = this->m_prevfastOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevfastOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevfastOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevfastOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevfastOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevfastOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevfastOLSFONDItemInfo->OrderStatus, m_prevfastOLSFONDItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevfastOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrdType, m_prevfastOLSFONDItemInfo->OrdType, m_prevfastOLSFONDItemInfo->OrdTypeLength);
				gmdeItemInfo->OrdTypeLength = this->m_prevfastOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevfastOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionID, m_prevfastOLSFONDItemInfo->TradingSessionID, m_prevfastOLSFONDItemInfo->TradingSessionIDLength);
				gmdeItemInfo->TradingSessionIDLength = this->m_prevfastOLSFONDItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevfastOLSFONDItemInfo->TradingSessionSubID, m_prevfastOLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevfastOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevfastOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalOLRFONDInfo = info;
		return info;
	}
	void* DecodeFastIncrementalOLRCURR() {
		FastIncrementalOLRCURRInfo* info = GetFreeFastIncrementalOLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDUpdateAction = this->m_prevfastOLSCURRItemInfo->MDUpdateAction;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					ReadString_Optional(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevfastOLSCURRItemInfo->MDEntryType, m_prevfastOLSCURRItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevfastOLSCURRItemInfo->MDEntryTypeLength;
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
				this->CopyString(gmdeItemInfo->Symbol, m_prevfastOLSCURRItemInfo->Symbol, m_prevfastOLSCURRItemInfo->SymbolLength);
				gmdeItemInfo->SymbolLength = this->m_prevfastOLSCURRItemInfo->SymbolLength;
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
				gmdeItemInfo->MDEntryDate = this->m_prevfastOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevfastOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullUInt32())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevfastOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevfastOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevfastOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadString_Optional(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevfastOLSCURRItemInfo->OrderStatus, m_prevfastOLSCURRItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevfastOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionID, m_prevfastOLSCURRItemInfo->TradingSessionID, m_prevfastOLSCURRItemInfo->TradingSessionIDLength);
				gmdeItemInfo->TradingSessionIDLength = this->m_prevfastOLSCURRItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevfastOLSCURRItemInfo->TradingSessionSubID, m_prevfastOLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevfastOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevfastOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalOLRCURRInfo = info;
		return info;
	}
	void* DecodeFastIncrementalTLRFOND() {
		FastIncrementalTLRFONDInfo* info = GetFreeFastIncrementalTLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastTLSFONDItemInfo();
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
			this->m_prevfastTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalTLRFONDInfo = info;
		return info;
	}
	void* DecodeFastIncrementalTLRCURR() {
		FastIncrementalTLRCURRInfo* info = GetFreeFastIncrementalTLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeFastTLSCURRItemInfo();
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
			this->m_prevfastTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevfastIncrementalTLRCURRInfo = info;
		return info;
	}
	void* DecodeFastSecurityDefinition() {
		FastSecurityDefinitionInfo* info = GetFreeFastSecurityDefinitionInfo();
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
		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = GetFreeFastSecurityDefinitionGroupInstrAttribItemInfo();
			info->GroupInstrAttrib[i] = giaItemInfo;
			giaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			if(CheckProcessNullByteVector())
				giaItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadByteVector_Optional(giaItemInfo->InstrAttribValue, &(giaItemInfo->InstrAttribValueLength), 128);
			this->m_prevfastSecurityDefinitionGroupInstrAttribItemInfo = giaItemInfo;
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
		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeFastSecurityDefinitionMarketSegmentGrpItemInfo();
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
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

			for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
				tsrgItemInfo = GetFreeFastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
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
				this->m_prevfastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = tsrgItemInfo;
			}

			this->m_prevfastSecurityDefinitionMarketSegmentGrpItemInfo = msgItemInfo;
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
		this->m_prevfastSecurityDefinitionInfo = info;
		return info;
	}
	void* DecodeFastSecurityStatus() {
		FastSecurityStatusInfo* info = GetFreeFastSecurityStatusInfo();
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
		this->m_prevfastSecurityStatusInfo = info;
		return info;
	}
	void* DecodeFastTradingSessionStatus() {
		FastTradingSessionStatusInfo* info = GetFreeFastTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesStatus = ReadInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		ReadString_Mandatory(info->TradingSessionID, &(info->TradingSessionIDLength));
		this->m_prevfastTradingSessionStatusInfo = info;
		return info;
	}
	void* DecodeFastHeartbeat() {
		FastHeartbeatInfo* info = GetFreeFastHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevfastHeartbeatInfo = info;
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoLogon() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // TargetCompID
		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoLogout() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // TargetCompID
		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoGeneric() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalGeneric() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoOLSFOND() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoOLSCURR() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoTLSFOND() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoTLSCURR() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalMSRFOND() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalMSRCURR() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalOLRFOND() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalOLRCURR() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalTLRFOND() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoIncrementalTLRCURR() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoSecurityDefinition() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoSecurityStatus() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
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
	FastSnapshotInfo* GetFastSnapshotInfoTradingSessionStatus() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		SkipToNextField(); // TradSesStatus
		SkipToNextField(); // Text
		ReadString_Mandatory(info->TradingSessionID, &(info->TradingSessionIDLength));
		return info;
	}
	FastSnapshotInfo* GetFastSnapshotInfoHeartbeat() {
		FastSnapshotInfo *info = GetFreeFastSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void* DecodeFast() {
		this->DecodeFastHeader();
		FastDecodeMethodPointer funcPtr = this->m_fastDecodeMethods[this->m_templateId - 2101];
		this->m_lastDecodedInfo = (this->*funcPtr)();
		return this->m_lastDecodedInfo;
	}
	void PrintFast() {

		switch(this->m_templateId) {
			case 2101:
				PrintFastLogon((FastLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 2102:
				PrintFastLogout((FastLogoutInfo*)this->m_lastDecodedInfo);
				break;
			case 2103:
				PrintFastGeneric((FastGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2104:
				PrintFastIncrementalGeneric((FastIncrementalGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2510:
				PrintFastOLSFOND((FastOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3600:
				PrintFastOLSCURR((FastOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2511:
				PrintFastTLSFOND((FastTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3601:
				PrintFastTLSCURR((FastTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2523:
				PrintFastIncrementalMSRFOND((FastIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3613:
				PrintFastIncrementalMSRCURR((FastIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2520:
				PrintFastIncrementalOLRFOND((FastIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3610:
				PrintFastIncrementalOLRCURR((FastIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2521:
				PrintFastIncrementalTLRFOND((FastIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3611:
				PrintFastIncrementalTLRCURR((FastIncrementalTLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2115:
				PrintFastSecurityDefinition((FastSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 2106:
				PrintFastSecurityStatus((FastSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2107:
				PrintFastTradingSessionStatus((FastTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2108:
				PrintFastHeartbeat((FastHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	void PrintXmlFast() {

		switch(this->m_templateId) {
			case 2101:
				PrintXmlFastLogon((FastLogonInfo*)this->m_lastDecodedInfo);
				break;
			case 2102:
				PrintXmlFastLogout((FastLogoutInfo*)this->m_lastDecodedInfo);
				break;
			case 2103:
				PrintXmlFastGeneric((FastGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2104:
				PrintXmlFastIncrementalGeneric((FastIncrementalGenericInfo*)this->m_lastDecodedInfo);
				break;
			case 2510:
				PrintXmlFastOLSFOND((FastOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3600:
				PrintXmlFastOLSCURR((FastOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2511:
				PrintXmlFastTLSFOND((FastTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3601:
				PrintXmlFastTLSCURR((FastTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2523:
				PrintXmlFastIncrementalMSRFOND((FastIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3613:
				PrintXmlFastIncrementalMSRCURR((FastIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2520:
				PrintXmlFastIncrementalOLRFOND((FastIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3610:
				PrintXmlFastIncrementalOLRCURR((FastIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2521:
				PrintXmlFastIncrementalTLRFOND((FastIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3611:
				PrintXmlFastIncrementalTLRCURR((FastIncrementalTLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2115:
				PrintXmlFastSecurityDefinition((FastSecurityDefinitionInfo*)this->m_lastDecodedInfo);
				break;
			case 2106:
				PrintXmlFastSecurityStatus((FastSecurityStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2107:
				PrintXmlFastTradingSessionStatus((FastTradingSessionStatusInfo*)this->m_lastDecodedInfo);
				break;
			case 2108:
				PrintXmlFastHeartbeat((FastHeartbeatInfo*)this->m_lastDecodedInfo);
				break;
		}
	}
	inline FastSnapshotInfo* GetFastSnapshotInfo() {
		this->DecodeHeader();
		FastGetSnapshotInfoMethodPointer funcPtr = this->m_fastGetSnapshotInfoMethods[this->m_templateId - 2101];
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
	void* DecodeSpectraDefaultIncrementalRefreshMessage() {
		SpectraDefaultIncrementalRefreshMessageInfo* info = GetFreeFastDefaultIncrementalRefreshMessageInfo();
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

		this->m_prevfastDefaultIncrementalRefreshMessageInfo = info;
		return info;
	}
	void* DecodeSpectraDefaultSnapshotMessage() {
		SpectraDefaultSnapshotMessageInfo* info = GetFreeFastDefaultSnapshotMessageInfo();
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

		this->m_prevfastDefaultSnapshotMessageInfo = info;
		return info;
	}
	void* DecodeSpectraSecurityDefinition() {
		SpectraSecurityDefinitionInfo* info = GetFreeFastSecurityDefinitionInfo();
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
		this->m_prevfastSecurityDefinitionInfo = info;
		return info;
	}
	void* DecodeSpectraSecurityDefinitionUpdateReport() {
		SpectraSecurityDefinitionUpdateReportInfo* info = GetFreeFastSecurityDefinitionUpdateReportInfo();
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
		this->m_prevfastSecurityDefinitionUpdateReportInfo = info;
		return info;
	}
	void* DecodeSpectraSecurityStatus() {
		SpectraSecurityStatusInfo* info = GetFreeFastSecurityStatusInfo();
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
		this->m_prevfastSecurityStatusInfo = info;
		return info;
	}
	void* DecodeSpectraHeartbeat() {
		SpectraHeartbeatInfo* info = GetFreeFastHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevfastHeartbeatInfo = info;
		return info;
	}
	void* DecodeSpectraSequenceReset() {
		SpectraSequenceResetInfo* info = GetFreeFastSequenceResetInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->NewSeqNo = ReadUInt32_Mandatory();
		this->m_prevfastSequenceResetInfo = info;
		return info;
	}
	void* DecodeSpectraTradingSessionStatus() {
		SpectraTradingSessionStatusInfo* info = GetFreeFastTradingSessionStatusInfo();
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
		this->m_prevfastTradingSessionStatusInfo = info;
		return info;
	}
	void* DecodeSpectraNews() {
		SpectraNewsInfo* info = GetFreeFastNewsInfo();
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

		this->m_prevfastNewsInfo = info;
		return info;
	}
	void* DecodeSpectraOrdersLog() {
		SpectraOrdersLogInfo* info = GetFreeFastOrdersLogInfo();
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

		this->m_prevfastOrdersLogInfo = info;
		return info;
	}
	void* DecodeSpectraOrdersBook() {
		SpectraOrdersBookInfo* info = GetFreeFastOrdersBookInfo();
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

		this->m_prevfastOrdersBookInfo = info;
		return info;
	}
	void* DecodeSpectraLogon() {
		SpectraLogonInfo* info = GetFreeFastLogonInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		this->m_prevfastLogonInfo = info;
		return info;
	}
	void* DecodeSpectraLogout() {
		SpectraLogoutInfo* info = GetFreeFastLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		this->m_prevfastLogoutInfo = info;
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
		this->DecodeHeader();
		SpectraGetSnapshotInfoMethodPointer funcPtr = this->m_spectraGetSnapshotInfoMethods[this->m_templateId - 3];
		return (this->*funcPtr)();
	}
#pragma endregion
};

