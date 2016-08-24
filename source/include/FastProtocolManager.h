#pragma once
#include "FixTypes.h"
#include "FastTypes.h"
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

class FastProtocolManager;

#pragma region Decode_Method_Pointer_Definition_GeneratedCode
typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();
#pragma endregion

#pragma region Checking_Presence_GeneratedCode
#define CheckMandatoryFieldPresence(map, field) ((map & field) != 0)
#define CheckOptionalFieldPresence(map, field) ((map & field) != 0)
#pragma endregion

class FastProtocolManager {
	const int maxBufferLength = 16000;
	BYTE	        *buffer;
	BYTE	        *currentPos;
	int		        bufferLength;
    UINT            m_templateId;
    UINT64          m_presenceMap;

    unsigned int    m_sendMsgSeqNo;
    unsigned int    m_recvMsgSeqNo;
    FILE            *m_xmlFilePtr;

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
	FastLogonInfo*	m_logon;
	FastLogoutInfo*	m_logout;
	FastMarketDataSnapshotFullRefreshGenericInfo*	m_marketDataSnapshotFullRefreshGeneric;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshGenericInfo*	m_marketDataIncrementalRefreshGeneric;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshGenericGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOLSFONDInfo*	m_marketDataSnapshotFullRefreshOLSFOND;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOLSCURRInfo*	m_marketDataSnapshotFullRefreshOLSCURR;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshTLSFONDInfo*	m_marketDataSnapshotFullRefreshTLSFOND;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshTLSCURRInfo*	m_marketDataSnapshotFullRefreshTLSCURR;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOBSFONDInfo*	m_marketDataSnapshotFullRefreshOBSFOND;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOBSCURRInfo*	m_marketDataSnapshotFullRefreshOBSCURR;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshMSRFONDInfo*	m_marketDataIncrementalRefreshMSRFOND;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshMSRCURRInfo*	m_marketDataIncrementalRefreshMSRCURR;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOLRFONDInfo*	m_marketDataIncrementalRefreshOLRFOND;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOLRCURRInfo*	m_marketDataIncrementalRefreshOLRCURR;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOBRFONDInfo*	m_marketDataIncrementalRefreshOBRFOND;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOBRCURRInfo*	m_marketDataIncrementalRefreshOBRCURR;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshTLRFONDInfo*	m_marketDataIncrementalRefreshTLRFOND;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshTLRCURRInfo*	m_marketDataIncrementalRefreshTLRCURR;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;
	FastSecurityDefinitionInfo*	m_securityDefinition;
	FastSecurityDefinitionGroupInstrAttribItemInfo*	m_securityDefinitionGroupInstrAttribItems;
	FastSecurityDefinitionMarketSegmentGrpItemInfo*	m_securityDefinitionMarketSegmentGrpItems;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*	m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	FastSecurityStatusInfo*	m_securityStatus;
	FastTradingSessionStatusInfo*	m_tradingSessionStatus;
	FastHeartbeatInfo*	m_heartbeat;
	int		m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsMaxCount;
	int		m_securityDefinitionGroupInstrAttribItemsMaxCount;
	int		m_securityDefinitionMarketSegmentGrpItemsMaxCount;
	int		m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsMaxCount;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo		*m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo		*m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem;
	FastSecurityDefinitionGroupInstrAttribItemInfo		*m_securityDefinitionGroupInstrAttribItemsCurrentItem;
	FastSecurityDefinitionMarketSegmentGrpItemInfo		*m_securityDefinitionMarketSegmentGrpItemsCurrentItem;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo		*m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem;

	void InitializeMessageInfo() {
		this->m_logon = new FastLogonInfo();
		memset(this->m_logon, 0, sizeof(FastLogonInfo));

		this->m_logout = new FastLogoutInfo();
		memset(this->m_logout, 0, sizeof(FastLogoutInfo));

		this->m_marketDataSnapshotFullRefreshGeneric = new FastMarketDataSnapshotFullRefreshGenericInfo();
		memset(this->m_marketDataSnapshotFullRefreshGeneric, 0, sizeof(FastMarketDataSnapshotFullRefreshGenericInfo));

		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshGeneric = new FastMarketDataIncrementalRefreshGenericInfo();
		memset(this->m_marketDataIncrementalRefreshGeneric, 0, sizeof(FastMarketDataIncrementalRefreshGenericInfo));

		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems = new FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems;

		this->m_marketDataSnapshotFullRefreshOLSFOND = new FastMarketDataSnapshotFullRefreshOLSFONDInfo();
		memset(this->m_marketDataSnapshotFullRefreshOLSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshOLSFONDInfo));

		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;

		this->m_marketDataSnapshotFullRefreshOLSCURR = new FastMarketDataSnapshotFullRefreshOLSCURRInfo();
		memset(this->m_marketDataSnapshotFullRefreshOLSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshOLSCURRInfo));

		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;

		this->m_marketDataSnapshotFullRefreshTLSFOND = new FastMarketDataSnapshotFullRefreshTLSFONDInfo();
		memset(this->m_marketDataSnapshotFullRefreshTLSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshTLSFONDInfo));

		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;

		this->m_marketDataSnapshotFullRefreshTLSCURR = new FastMarketDataSnapshotFullRefreshTLSCURRInfo();
		memset(this->m_marketDataSnapshotFullRefreshTLSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshTLSCURRInfo));

		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;

		this->m_marketDataSnapshotFullRefreshOBSFOND = new FastMarketDataSnapshotFullRefreshOBSFONDInfo();
		memset(this->m_marketDataSnapshotFullRefreshOBSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshOBSFONDInfo));

		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;

		this->m_marketDataSnapshotFullRefreshOBSCURR = new FastMarketDataSnapshotFullRefreshOBSCURRInfo();
		memset(this->m_marketDataSnapshotFullRefreshOBSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshOBSCURRInfo));

		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshMSRFOND = new FastMarketDataIncrementalRefreshMSRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshMSRFOND, 0, sizeof(FastMarketDataIncrementalRefreshMSRFONDInfo));

		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshMSRCURR = new FastMarketDataIncrementalRefreshMSRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshMSRCURR, 0, sizeof(FastMarketDataIncrementalRefreshMSRCURRInfo));

		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshOLRFOND = new FastMarketDataIncrementalRefreshOLRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshOLRFOND, 0, sizeof(FastMarketDataIncrementalRefreshOLRFONDInfo));

		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshOLRCURR = new FastMarketDataIncrementalRefreshOLRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshOLRCURR, 0, sizeof(FastMarketDataIncrementalRefreshOLRCURRInfo));

		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshOBRFOND = new FastMarketDataIncrementalRefreshOBRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshOBRFOND, 0, sizeof(FastMarketDataIncrementalRefreshOBRFONDInfo));

		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshOBRCURR = new FastMarketDataIncrementalRefreshOBRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshOBRCURR, 0, sizeof(FastMarketDataIncrementalRefreshOBRCURRInfo));

		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshTLRFOND = new FastMarketDataIncrementalRefreshTLRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshTLRFOND, 0, sizeof(FastMarketDataIncrementalRefreshTLRFONDInfo));

		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;

		this->m_marketDataIncrementalRefreshTLRCURR = new FastMarketDataIncrementalRefreshTLRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshTLRCURR, 0, sizeof(FastMarketDataIncrementalRefreshTLRCURRInfo));

		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsMaxCount = 1024;
		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;

		this->m_securityDefinition = new FastSecurityDefinitionInfo();
		memset(this->m_securityDefinition, 0, sizeof(FastSecurityDefinitionInfo));

		this->m_securityDefinitionGroupInstrAttribItems = new FastSecurityDefinitionGroupInstrAttribItemInfo[1024];
		memset(this->m_securityDefinitionGroupInstrAttribItems, 0, 1024 * sizeof(FastSecurityDefinitionGroupInstrAttribItemInfo));
		this->m_securityDefinitionGroupInstrAttribItemsMaxCount = 1024;
		this->m_securityDefinitionGroupInstrAttribItemsCurrentItem = this->m_securityDefinitionGroupInstrAttribItems;

		this->m_securityDefinitionMarketSegmentGrpItems = new FastSecurityDefinitionMarketSegmentGrpItemInfo[1024];
		memset(this->m_securityDefinitionMarketSegmentGrpItems, 0, 1024 * sizeof(FastSecurityDefinitionMarketSegmentGrpItemInfo));
		this->m_securityDefinitionMarketSegmentGrpItemsMaxCount = 1024;
		this->m_securityDefinitionMarketSegmentGrpItemsCurrentItem = this->m_securityDefinitionMarketSegmentGrpItems;

		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo[1024];
		memset(this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems, 0, 1024 * sizeof(FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo));
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsMaxCount = 1024;
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem = this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;

		this->m_securityStatus = new FastSecurityStatusInfo();
		memset(this->m_securityStatus, 0, sizeof(FastSecurityStatusInfo));

		this->m_tradingSessionStatus = new FastTradingSessionStatusInfo();
		memset(this->m_tradingSessionStatus, 0, sizeof(FastTradingSessionStatusInfo));

		this->m_heartbeat = new FastHeartbeatInfo();
		memset(this->m_heartbeat, 0, sizeof(FastHeartbeatInfo));

	}

	inline void ResetMessageInfoIndicies() {
		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;
		this->m_securityDefinitionGroupInstrAttribItemsCurrentItem = this->m_securityDefinitionGroupInstrAttribItems;
		this->m_securityDefinitionMarketSegmentGrpItemsCurrentItem = this->m_securityDefinitionMarketSegmentGrpItems;
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem = this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}
#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
	FastDecodeMethodPointer* DecodeMethods;

	void InitializeDecodeMethodPointers() {
		int ptCount = 1413;
		this->DecodeMethods = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 1413; i++)
			this->DecodeMethods[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods[2101 - 2101] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods[2102 - 2101] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods[2103 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshGeneric;
		this->DecodeMethods[2104 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshGeneric;
		this->DecodeMethods[2410 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOLSFOND;
		this->DecodeMethods[3500 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOLSCURR;
		this->DecodeMethods[2411 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshTLSFOND;
		this->DecodeMethods[3501 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshTLSCURR;
		this->DecodeMethods[2412 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOBSFOND;
		this->DecodeMethods[3502 - 2101] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOBSCURR;
		this->DecodeMethods[2423 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshMSRFOND;
		this->DecodeMethods[3513 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshMSRCURR;
		this->DecodeMethods[2420 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOLRFOND;
		this->DecodeMethods[3510 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOLRCURR;
		this->DecodeMethods[2422 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOBRFOND;
		this->DecodeMethods[3512 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOBRCURR;
		this->DecodeMethods[2421 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshTLRFOND;
		this->DecodeMethods[3511 - 2101] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshTLRCURR;
		this->DecodeMethods[2115 - 2101] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods[2106 - 2101] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods[2107 - 2101] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods[2108 - 2101] = &FastProtocolManager::DecodeHeartbeat;

	}

#pragma endregion

#pragma region Get_Free_Item_Methods_GeneratedCode
	inline FastLogonInfo* GetFreeLogonInfo() {
		return this->m_logon;
	}

	inline FastLogoutInfo* GetFreeLogoutInfo() {
		return this->m_logout;
	}

	inline FastMarketDataSnapshotFullRefreshGenericInfo* GetFreeMarketDataSnapshotFullRefreshGenericInfo() {
		return this->m_marketDataSnapshotFullRefreshGeneric;
	}

	inline FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshGenericInfo* GetFreeMarketDataIncrementalRefreshGenericInfo() {
		return this->m_marketDataIncrementalRefreshGeneric;
	}

	inline FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataSnapshotFullRefreshOLSFONDInfo* GetFreeMarketDataSnapshotFullRefreshOLSFONDInfo() {
		return this->m_marketDataSnapshotFullRefreshOLSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataSnapshotFullRefreshOLSCURRInfo* GetFreeMarketDataSnapshotFullRefreshOLSCURRInfo() {
		return this->m_marketDataSnapshotFullRefreshOLSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataSnapshotFullRefreshTLSFONDInfo* GetFreeMarketDataSnapshotFullRefreshTLSFONDInfo() {
		return this->m_marketDataSnapshotFullRefreshTLSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataSnapshotFullRefreshTLSCURRInfo* GetFreeMarketDataSnapshotFullRefreshTLSCURRInfo() {
		return this->m_marketDataSnapshotFullRefreshTLSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataSnapshotFullRefreshOBSFONDInfo* GetFreeMarketDataSnapshotFullRefreshOBSFONDInfo() {
		return this->m_marketDataSnapshotFullRefreshOBSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataSnapshotFullRefreshOBSCURRInfo* GetFreeMarketDataSnapshotFullRefreshOBSCURRInfo() {
		return this->m_marketDataSnapshotFullRefreshOBSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo() {
		FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo *res = this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshMSRFONDInfo* GetFreeMarketDataIncrementalRefreshMSRFONDInfo() {
		return this->m_marketDataIncrementalRefreshMSRFOND;
	}

	inline FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshMSRCURRInfo* GetFreeMarketDataIncrementalRefreshMSRCURRInfo() {
		return this->m_marketDataIncrementalRefreshMSRCURR;
	}

	inline FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshOLRFONDInfo* GetFreeMarketDataIncrementalRefreshOLRFONDInfo() {
		return this->m_marketDataIncrementalRefreshOLRFOND;
	}

	inline FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshOLRCURRInfo* GetFreeMarketDataIncrementalRefreshOLRCURRInfo() {
		return this->m_marketDataIncrementalRefreshOLRCURR;
	}

	inline FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshOBRFONDInfo* GetFreeMarketDataIncrementalRefreshOBRFONDInfo() {
		return this->m_marketDataIncrementalRefreshOBRFOND;
	}

	inline FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshOBRCURRInfo* GetFreeMarketDataIncrementalRefreshOBRCURRInfo() {
		return this->m_marketDataIncrementalRefreshOBRCURR;
	}

	inline FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshTLRFONDInfo* GetFreeMarketDataIncrementalRefreshTLRFONDInfo() {
		return this->m_marketDataIncrementalRefreshTLRFOND;
	}

	inline FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastMarketDataIncrementalRefreshTLRCURRInfo* GetFreeMarketDataIncrementalRefreshTLRCURRInfo() {
		return this->m_marketDataIncrementalRefreshTLRCURR;
	}

	inline FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo() {
		FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo *res = this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem;
		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem++;
		return res;
	}

	inline FastSecurityDefinitionInfo* GetFreeSecurityDefinitionInfo() {
		return this->m_securityDefinition;
	}

	inline FastSecurityDefinitionGroupInstrAttribItemInfo* GetFreeSecurityDefinitionGroupInstrAttribItemInfo() {
		FastSecurityDefinitionGroupInstrAttribItemInfo *res = this->m_securityDefinitionGroupInstrAttribItemsCurrentItem;
		this->m_securityDefinitionGroupInstrAttribItemsCurrentItem++;
		return res;
	}

	inline FastSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpItemInfo() {
		FastSecurityDefinitionMarketSegmentGrpItemInfo *res = this->m_securityDefinitionMarketSegmentGrpItemsCurrentItem;
		this->m_securityDefinitionMarketSegmentGrpItemsCurrentItem++;
		return res;
	}

	inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *res = this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem;
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem++;
		return res;
	}

	inline FastSecurityStatusInfo* GetFreeSecurityStatusInfo() {
		return this->m_securityStatus;
	}

	inline FastTradingSessionStatusInfo* GetFreeTradingSessionStatusInfo() {
		return this->m_tradingSessionStatus;
	}

	inline FastHeartbeatInfo* GetFreeHeartbeatInfo() {
		return this->m_heartbeat;
	}

#pragma endregion

public:

    inline unsigned int SendMsgSeqNo() { return this->m_sendMsgSeqNo; }
    inline void IncSendMsgSeqNo() { this->m_sendMsgSeqNo++; }

    inline unsigned int RecvMsgSeqNo() { return this->m_recvMsgSeqNo; }
    inline void IncRecvMsgSeqNo() { this->m_recvMsgSeqNo++; }

#pragma region Core_Methods
	inline bool FastCompareString1(char *str1, char *str2) { return *str1 == *str2; }
	inline bool FastCompareString4(char *str1, char *str2) { return *((int*)str1) == *((int*)str2); }
	inline bool FastCompareString8(char *str1, char *str2) { return *((UINT64*)str1) == *((UINT64*)str2); }
	inline void ResetBuffer() { this->currentPos = this->buffer; }
	inline void SetNewBuffer(BYTE *buffer, int length) { 
		this->buffer = buffer;
		this->bufferLength = length;
		this->ResetBuffer();
	    this->ResetMessageInfoIndicies();
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


    inline void WritePresenceMap1(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos++;
    }

    inline void WritePresenceMap2(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos+=2;
    }

    inline void WritePresenceMap3(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos+=3;
    }

    inline void WritePresenceMap4(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos+=4;
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
        value->Exponent = ReadInt32_Optional();
        value->Mantissa = ReadInt32_Mandatory();
	}

	inline void ReadDecimal_Mandatory(Decimal *value) {
        value->Exponent = ReadInt32_Mandatory();
        value->Mantissa = ReadInt32_Mandatory();
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

	FastProtocolManager();
	~FastProtocolManager();

	inline BYTE* Buffer() { return this->buffer; }
	inline BYTE* CurrentPos() { return this->currentPos; }
	inline int BufferLength() { return this->bufferLength; }
	inline int MessageLength() { return this->currentPos - this->buffer; }
	inline void SetBufferLength(int value) { this->bufferLength = value; }
#pragma endregion

#pragma region Encode_Methods_Definition_GeneratedCode
	inline void EncodeLogonInfo(FastLogonInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("A", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
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
	inline void EncodeLogoutInfo(FastLogoutInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("5", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		if(!info->AllowText)
			this->WriteNull();
		else
			WriteString_Optional(info->Text, info->TextLength);
	}
	inline void EncodeSecurityDefinitionInfo(FastSecurityDefinitionInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("d", 1);
		WriteString_Mandatory("9", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteString_Mandatory(info->MessageEncoding, info->MessageEncodingLength);
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
	inline void EncodeSecurityStatusInfo(FastSecurityStatusInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("f", 1);
		WriteString_Mandatory("9", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
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
	inline void EncodeTradingSessionStatusInfo(FastTradingSessionStatusInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("h", 1);
		WriteString_Mandatory("9", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteInt32_Mandatory(info->TradSesStatus);
		if(!info->AllowText)
			this->WriteNull();
		else
			WriteString_Optional(info->Text, info->TextLength);
		WriteString_Mandatory(info->TradingSessionID, info->TradingSessionIDLength);
	}
#pragma endregion

    void* DecodeUnsupportedMessage() {
        return NULL;
    }

#pragma region Print_Methods_Declaration_GeneratedCode
	void PrintLogon(FastLogonInfo *info);
	void PrintLogout(FastLogoutInfo *info);
	void PrintMarketDataSnapshotFullRefreshGeneric(FastMarketDataSnapshotFullRefreshGenericInfo *info);
	void PrintMarketDataIncrementalRefreshGeneric(FastMarketDataIncrementalRefreshGenericInfo *info);
	void PrintMarketDataSnapshotFullRefreshOLSFOND(FastMarketDataSnapshotFullRefreshOLSFONDInfo *info);
	void PrintMarketDataSnapshotFullRefreshOLSCURR(FastMarketDataSnapshotFullRefreshOLSCURRInfo *info);
	void PrintMarketDataSnapshotFullRefreshTLSFOND(FastMarketDataSnapshotFullRefreshTLSFONDInfo *info);
	void PrintMarketDataSnapshotFullRefreshTLSCURR(FastMarketDataSnapshotFullRefreshTLSCURRInfo *info);
	void PrintMarketDataSnapshotFullRefreshOBSFOND(FastMarketDataSnapshotFullRefreshOBSFONDInfo *info);
	void PrintMarketDataSnapshotFullRefreshOBSCURR(FastMarketDataSnapshotFullRefreshOBSCURRInfo *info);
	void PrintMarketDataIncrementalRefreshMSRFOND(FastMarketDataIncrementalRefreshMSRFONDInfo *info);
	void PrintMarketDataIncrementalRefreshMSRCURR(FastMarketDataIncrementalRefreshMSRCURRInfo *info);
	void PrintMarketDataIncrementalRefreshOLRFOND(FastMarketDataIncrementalRefreshOLRFONDInfo *info);
	void PrintMarketDataIncrementalRefreshOLRCURR(FastMarketDataIncrementalRefreshOLRCURRInfo *info);
	void PrintMarketDataIncrementalRefreshOBRFOND(FastMarketDataIncrementalRefreshOBRFONDInfo *info);
	void PrintMarketDataIncrementalRefreshOBRCURR(FastMarketDataIncrementalRefreshOBRCURRInfo *info);
	void PrintMarketDataIncrementalRefreshTLRFOND(FastMarketDataIncrementalRefreshTLRFONDInfo *info);
	void PrintMarketDataIncrementalRefreshTLRCURR(FastMarketDataIncrementalRefreshTLRCURRInfo *info);
	void PrintSecurityDefinition(FastSecurityDefinitionInfo *info);
	void PrintSecurityStatus(FastSecurityStatusInfo *info);
	void PrintTradingSessionStatus(FastTradingSessionStatusInfo *info);
	void PrintHeartbeat(FastHeartbeatInfo *info);
	void PrintXmlLogon(FastLogonInfo *info);
	void PrintXmlLogout(FastLogoutInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshGeneric(FastMarketDataSnapshotFullRefreshGenericInfo *info);
	void PrintXmlMarketDataIncrementalRefreshGeneric(FastMarketDataIncrementalRefreshGenericInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshOLSFOND(FastMarketDataSnapshotFullRefreshOLSFONDInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshOLSCURR(FastMarketDataSnapshotFullRefreshOLSCURRInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshTLSFOND(FastMarketDataSnapshotFullRefreshTLSFONDInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshTLSCURR(FastMarketDataSnapshotFullRefreshTLSCURRInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshOBSFOND(FastMarketDataSnapshotFullRefreshOBSFONDInfo *info);
	void PrintXmlMarketDataSnapshotFullRefreshOBSCURR(FastMarketDataSnapshotFullRefreshOBSCURRInfo *info);
	void PrintXmlMarketDataIncrementalRefreshMSRFOND(FastMarketDataIncrementalRefreshMSRFONDInfo *info);
	void PrintXmlMarketDataIncrementalRefreshMSRCURR(FastMarketDataIncrementalRefreshMSRCURRInfo *info);
	void PrintXmlMarketDataIncrementalRefreshOLRFOND(FastMarketDataIncrementalRefreshOLRFONDInfo *info);
	void PrintXmlMarketDataIncrementalRefreshOLRCURR(FastMarketDataIncrementalRefreshOLRCURRInfo *info);
	void PrintXmlMarketDataIncrementalRefreshOBRFOND(FastMarketDataIncrementalRefreshOBRFONDInfo *info);
	void PrintXmlMarketDataIncrementalRefreshOBRCURR(FastMarketDataIncrementalRefreshOBRCURRInfo *info);
	void PrintXmlMarketDataIncrementalRefreshTLRFOND(FastMarketDataIncrementalRefreshTLRFONDInfo *info);
	void PrintXmlMarketDataIncrementalRefreshTLRCURR(FastMarketDataIncrementalRefreshTLRCURRInfo *info);
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

	void* DecodeLogon() {
		FastLogonInfo* info = GetFreeLogonInfo();
		info->PresenceMap = this->m_presenceMap;

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
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshGeneric() {
		FastMarketDataSnapshotFullRefreshGenericInfo* info = GetFreeMarketDataSnapshotFullRefreshGenericInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
			else {
				gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
				gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else {
				gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
				gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshGeneric() {
		FastMarketDataIncrementalRefreshGenericInfo* info = GetFreeMarketDataIncrementalRefreshGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
			else {
				gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
				gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else {
				gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
				gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOLSFOND() {
		FastMarketDataSnapshotFullRefreshOLSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshOLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
				ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
			else {
				gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
				gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
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
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOLSCURR() {
		FastMarketDataSnapshotFullRefreshOLSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshOLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
				ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
			else {
				gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
				gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshTLSFOND() {
		FastMarketDataSnapshotFullRefreshTLSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshTLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshTLSCURR() {
		FastMarketDataSnapshotFullRefreshTLSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshTLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOBSFOND() {
		FastMarketDataSnapshotFullRefreshOBSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshOBSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOBSCURR() {
		FastMarketDataSnapshotFullRefreshOBSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshOBSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

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

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshMSRFOND() {
		FastMarketDataIncrementalRefreshMSRFONDInfo* info = GetFreeMarketDataIncrementalRefreshMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else {
				gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
				gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshMSRCURR() {
		FastMarketDataIncrementalRefreshMSRCURRInfo* info = GetFreeMarketDataIncrementalRefreshMSRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			else {
				gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
				gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOLRFOND() {
		FastMarketDataIncrementalRefreshOLRFONDInfo* info = GetFreeMarketDataIncrementalRefreshOLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
			else {
				gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
				gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
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
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOLRCURR() {
		FastMarketDataIncrementalRefreshOLRCURRInfo* info = GetFreeMarketDataIncrementalRefreshOLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

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
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
			else {
				gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
				gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOBRFOND() {
		FastMarketDataIncrementalRefreshOBRFONDInfo* info = GetFreeMarketDataIncrementalRefreshOBRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOBRCURR() {
		FastMarketDataIncrementalRefreshOBRCURRInfo* info = GetFreeMarketDataIncrementalRefreshOBRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshTLRFOND() {
		FastMarketDataIncrementalRefreshTLRFONDInfo* info = GetFreeMarketDataIncrementalRefreshTLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshTLRCURR() {
		FastMarketDataIncrementalRefreshTLRCURRInfo* info = GetFreeMarketDataIncrementalRefreshTLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
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
		}

		return info;
	}
	void* DecodeSecurityDefinition() {
		FastSecurityDefinitionInfo* info = GetFreeSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
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
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Currency), &(info->CurrencyLength));

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
				if(!CheckProcessNullInt32())
					tsrgItemInfo->SecurityTradingStatus = ReadInt32_Optional();
				if(!CheckProcessNullInt32())
					tsrgItemInfo->OrderNote = ReadInt32_Optional();
			}

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
		info->PresenceMap = this->m_presenceMap;

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
		info->PresenceMap = this->m_presenceMap;

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
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void* Decode_Generic() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OLS_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OLS_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_TLS_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_TLS_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OBS_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OBS_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_MSR_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_MSR_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OLR_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OLR_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OBR_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_OBR_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_TLR_FOND() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
	inline void* Decode_TLR_CURR() {
		this->DecodeHeader();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods[this->m_templateId - 2101];
		return (this->*funcPtr)();
	}
#pragma endregion
};

