#pragma once
#include "FixTypes.h"
#include "FastTypes.h"
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

class FastProtocolManager;

#pragma region Decode_Method_Pointer_Definition_GeneratedCode
typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();
typedef FastSnapshotInfo* (FastProtocolManager::*FastGetSnapshotInfoMethodPointer)();
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

    FastSnapshotInfo *m_snapshotInfo;
	void			*m_lastDecodedInfo;

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
	AutoAllocatePointerList<FastGenericItemInfo>		*m_genericItems;
	FastGenericInfo*	m_generic;
	FastIncrementalGenericInfo*	m_incrementalGeneric;
	AutoAllocatePointerList<FastOLSFONDItemInfo>		*m_oLSFONDItems;
	FastOLSFONDInfo*	m_oLSFOND;
	AutoAllocatePointerList<FastOLSCURRItemInfo>		*m_oLSCURRItems;
	FastOLSCURRInfo*	m_oLSCURR;
	AutoAllocatePointerList<FastTLSFONDItemInfo>		*m_tLSFONDItems;
	FastTLSFONDInfo*	m_tLSFOND;
	AutoAllocatePointerList<FastTLSCURRItemInfo>		*m_tLSCURRItems;
	FastTLSCURRInfo*	m_tLSCURR;
	AutoAllocatePointerList<FastOBSFONDItemInfo>		*m_oBSFONDItems;
	FastOBSFONDInfo*	m_oBSFOND;
	AutoAllocatePointerList<FastOBSCURRItemInfo>		*m_oBSCURRItems;
	FastOBSCURRInfo*	m_oBSCURR;
	AutoAllocatePointerList<FastIncrementalMSRFONDItemInfo>		*m_incrementalMSRFONDItems;
	FastIncrementalMSRFONDInfo*	m_incrementalMSRFOND;
	AutoAllocatePointerList<FastIncrementalMSRCURRItemInfo>		*m_incrementalMSRCURRItems;
	FastIncrementalMSRCURRInfo*	m_incrementalMSRCURR;
	FastIncrementalOLRFONDInfo*	m_incrementalOLRFOND;
	FastIncrementalOLRCURRInfo*	m_incrementalOLRCURR;
	FastIncrementalOBRFONDInfo*	m_incrementalOBRFOND;
	FastIncrementalOBRCURRInfo*	m_incrementalOBRCURR;
	FastIncrementalTLRFONDInfo*	m_incrementalTLRFOND;
	FastIncrementalTLRCURRInfo*	m_incrementalTLRCURR;
	AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>		*m_securityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>		*m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>		*m_securityDefinitionMarketSegmentGrpItems;
	FastSecurityDefinitionInfo*	m_securityDefinition;
	FastSecurityStatusInfo*	m_securityStatus;
	FastTradingSessionStatusInfo*	m_tradingSessionStatus;
	FastHeartbeatInfo*	m_heartbeat;

	void InitializeMessageInfo() {
		this->m_logon = new FastLogonInfo();
		memset(this->m_logon, 0, sizeof(FastLogonInfo));

		this->m_logout = new FastLogoutInfo();
		memset(this->m_logout, 0, sizeof(FastLogoutInfo));

		this->m_genericItems = new AutoAllocatePointerList<FastGenericItemInfo>(2, 256);

		this->m_generic = new FastGenericInfo();
		memset(this->m_generic, 0, sizeof(FastGenericInfo));

		this->m_incrementalGeneric = new FastIncrementalGenericInfo();
		memset(this->m_incrementalGeneric, 0, sizeof(FastIncrementalGenericInfo));

		this->m_oLSFONDItems = new AutoAllocatePointerList<FastOLSFONDItemInfo>(2, 256);

		this->m_oLSFOND = new FastOLSFONDInfo();
		memset(this->m_oLSFOND, 0, sizeof(FastOLSFONDInfo));

		this->m_oLSCURRItems = new AutoAllocatePointerList<FastOLSCURRItemInfo>(2, 256);

		this->m_oLSCURR = new FastOLSCURRInfo();
		memset(this->m_oLSCURR, 0, sizeof(FastOLSCURRInfo));

		this->m_tLSFONDItems = new AutoAllocatePointerList<FastTLSFONDItemInfo>(2, 256);

		this->m_tLSFOND = new FastTLSFONDInfo();
		memset(this->m_tLSFOND, 0, sizeof(FastTLSFONDInfo));

		this->m_tLSCURRItems = new AutoAllocatePointerList<FastTLSCURRItemInfo>(2, 256);

		this->m_tLSCURR = new FastTLSCURRInfo();
		memset(this->m_tLSCURR, 0, sizeof(FastTLSCURRInfo));

		this->m_oBSFONDItems = new AutoAllocatePointerList<FastOBSFONDItemInfo>(2, 256);

		this->m_oBSFOND = new FastOBSFONDInfo();
		memset(this->m_oBSFOND, 0, sizeof(FastOBSFONDInfo));

		this->m_oBSCURRItems = new AutoAllocatePointerList<FastOBSCURRItemInfo>(2, 256);

		this->m_oBSCURR = new FastOBSCURRInfo();
		memset(this->m_oBSCURR, 0, sizeof(FastOBSCURRInfo));

		this->m_incrementalMSRFONDItems = new AutoAllocatePointerList<FastIncrementalMSRFONDItemInfo>(2, 256);

		this->m_incrementalMSRFOND = new FastIncrementalMSRFONDInfo();
		memset(this->m_incrementalMSRFOND, 0, sizeof(FastIncrementalMSRFONDInfo));

		this->m_incrementalMSRCURRItems = new AutoAllocatePointerList<FastIncrementalMSRCURRItemInfo>(2, 256);

		this->m_incrementalMSRCURR = new FastIncrementalMSRCURRInfo();
		memset(this->m_incrementalMSRCURR, 0, sizeof(FastIncrementalMSRCURRInfo));

		this->m_incrementalOLRFOND = new FastIncrementalOLRFONDInfo();
		memset(this->m_incrementalOLRFOND, 0, sizeof(FastIncrementalOLRFONDInfo));

		this->m_incrementalOLRCURR = new FastIncrementalOLRCURRInfo();
		memset(this->m_incrementalOLRCURR, 0, sizeof(FastIncrementalOLRCURRInfo));

		this->m_incrementalOBRFOND = new FastIncrementalOBRFONDInfo();
		memset(this->m_incrementalOBRFOND, 0, sizeof(FastIncrementalOBRFONDInfo));

		this->m_incrementalOBRCURR = new FastIncrementalOBRCURRInfo();
		memset(this->m_incrementalOBRCURR, 0, sizeof(FastIncrementalOBRCURRInfo));

		this->m_incrementalTLRFOND = new FastIncrementalTLRFONDInfo();
		memset(this->m_incrementalTLRFOND, 0, sizeof(FastIncrementalTLRFONDInfo));

		this->m_incrementalTLRCURR = new FastIncrementalTLRCURRInfo();
		memset(this->m_incrementalTLRCURR, 0, sizeof(FastIncrementalTLRCURRInfo));

		this->m_securityDefinitionGroupInstrAttribItems = new AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>(2, 256);

		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(2, 256);

		this->m_securityDefinitionMarketSegmentGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>(2, 256);

		this->m_securityDefinition = new FastSecurityDefinitionInfo();
		memset(this->m_securityDefinition, 0, sizeof(FastSecurityDefinitionInfo));

		this->m_securityStatus = new FastSecurityStatusInfo();
		memset(this->m_securityStatus, 0, sizeof(FastSecurityStatusInfo));

		this->m_tradingSessionStatus = new FastTradingSessionStatusInfo();
		memset(this->m_tradingSessionStatus, 0, sizeof(FastTradingSessionStatusInfo));

		this->m_heartbeat = new FastHeartbeatInfo();
		memset(this->m_heartbeat, 0, sizeof(FastHeartbeatInfo));

	}

#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
	FastDecodeMethodPointer* DecodeMethods;
	FastGetSnapshotInfoMethodPointer* GetSnapshotInfoMethods;

	void InitializeDecodeMethodPointers() {
		int ptCount = 1413;
		this->DecodeMethods = new FastDecodeMethodPointer[ptCount];
		this->GetSnapshotInfoMethods = new FastGetSnapshotInfoMethodPointer[ptCount];

		for(int i = 0; i < 1413; i++) {
			this->DecodeMethods[i] = &FastProtocolManager::DecodeUnsupportedMessage;
			this->GetSnapshotInfoMethods[i] = &FastProtocolManager::GetSnapshotInfoUnsupported;
		}

		this->DecodeMethods[2101 - 2101] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods[2102 - 2101] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods[2103 - 2101] = &FastProtocolManager::DecodeGeneric;
		this->DecodeMethods[2104 - 2101] = &FastProtocolManager::DecodeIncrementalGeneric;
		this->DecodeMethods[2410 - 2101] = &FastProtocolManager::DecodeOLSFOND;
		this->DecodeMethods[3500 - 2101] = &FastProtocolManager::DecodeOLSCURR;
		this->DecodeMethods[2411 - 2101] = &FastProtocolManager::DecodeTLSFOND;
		this->DecodeMethods[3501 - 2101] = &FastProtocolManager::DecodeTLSCURR;
		this->DecodeMethods[2412 - 2101] = &FastProtocolManager::DecodeOBSFOND;
		this->DecodeMethods[3502 - 2101] = &FastProtocolManager::DecodeOBSCURR;
		this->DecodeMethods[2423 - 2101] = &FastProtocolManager::DecodeIncrementalMSRFOND;
		this->DecodeMethods[3513 - 2101] = &FastProtocolManager::DecodeIncrementalMSRCURR;
		this->DecodeMethods[2420 - 2101] = &FastProtocolManager::DecodeIncrementalOLRFOND;
		this->DecodeMethods[3510 - 2101] = &FastProtocolManager::DecodeIncrementalOLRCURR;
		this->DecodeMethods[2422 - 2101] = &FastProtocolManager::DecodeIncrementalOBRFOND;
		this->DecodeMethods[3512 - 2101] = &FastProtocolManager::DecodeIncrementalOBRCURR;
		this->DecodeMethods[2421 - 2101] = &FastProtocolManager::DecodeIncrementalTLRFOND;
		this->DecodeMethods[3511 - 2101] = &FastProtocolManager::DecodeIncrementalTLRCURR;
		this->DecodeMethods[2115 - 2101] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods[2106 - 2101] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods[2107 - 2101] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods[2108 - 2101] = &FastProtocolManager::DecodeHeartbeat;

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
	inline FastLogonInfo* GetFreeLogonInfo() {
		return this->m_logon;
	}

	inline FastLogoutInfo* GetFreeLogoutInfo() {
		return this->m_logout;
	}

	inline FastGenericItemInfo* GetFreeGenericItemInfo() {
		return this->m_genericItems->NewItem();
	}

	inline FastGenericInfo* GetFreeGenericInfo() {
		return this->m_generic;
	}

	inline FastIncrementalGenericInfo* GetFreeIncrementalGenericInfo() {
		return this->m_incrementalGeneric;
	}

	inline FastOLSFONDItemInfo* GetFreeOLSFONDItemInfo() {
		return this->m_oLSFONDItems->NewItem();
	}

	inline FastOLSFONDInfo* GetFreeOLSFONDInfo() {
		return this->m_oLSFOND;
	}

	inline FastOLSCURRItemInfo* GetFreeOLSCURRItemInfo() {
		return this->m_oLSCURRItems->NewItem();
	}

	inline FastOLSCURRInfo* GetFreeOLSCURRInfo() {
		return this->m_oLSCURR;
	}

	inline FastTLSFONDItemInfo* GetFreeTLSFONDItemInfo() {
		return this->m_tLSFONDItems->NewItem();
	}

	inline FastTLSFONDInfo* GetFreeTLSFONDInfo() {
		return this->m_tLSFOND;
	}

	inline FastTLSCURRItemInfo* GetFreeTLSCURRItemInfo() {
		return this->m_tLSCURRItems->NewItem();
	}

	inline FastTLSCURRInfo* GetFreeTLSCURRInfo() {
		return this->m_tLSCURR;
	}

	inline FastOBSFONDItemInfo* GetFreeOBSFONDItemInfo() {
		return this->m_oBSFONDItems->NewItem();
	}

	inline FastOBSFONDInfo* GetFreeOBSFONDInfo() {
		return this->m_oBSFOND;
	}

	inline FastOBSCURRItemInfo* GetFreeOBSCURRItemInfo() {
		return this->m_oBSCURRItems->NewItem();
	}

	inline FastOBSCURRInfo* GetFreeOBSCURRInfo() {
		return this->m_oBSCURR;
	}

	inline FastIncrementalMSRFONDItemInfo* GetFreeIncrementalMSRFONDItemInfo() {
		return this->m_incrementalMSRFONDItems->NewItem();
	}

	inline FastIncrementalMSRFONDInfo* GetFreeIncrementalMSRFONDInfo() {
		return this->m_incrementalMSRFOND;
	}

	inline FastIncrementalMSRCURRItemInfo* GetFreeIncrementalMSRCURRItemInfo() {
		return this->m_incrementalMSRCURRItems->NewItem();
	}

	inline FastIncrementalMSRCURRInfo* GetFreeIncrementalMSRCURRInfo() {
		return this->m_incrementalMSRCURR;
	}

	inline FastIncrementalOLRFONDInfo* GetFreeIncrementalOLRFONDInfo() {
		return this->m_incrementalOLRFOND;
	}

	inline FastIncrementalOLRCURRInfo* GetFreeIncrementalOLRCURRInfo() {
		return this->m_incrementalOLRCURR;
	}

	inline FastIncrementalOBRFONDInfo* GetFreeIncrementalOBRFONDInfo() {
		return this->m_incrementalOBRFOND;
	}

	inline FastIncrementalOBRCURRInfo* GetFreeIncrementalOBRCURRInfo() {
		return this->m_incrementalOBRCURR;
	}

	inline FastIncrementalTLRFONDInfo* GetFreeIncrementalTLRFONDInfo() {
		return this->m_incrementalTLRFOND;
	}

	inline FastIncrementalTLRCURRInfo* GetFreeIncrementalTLRCURRInfo() {
		return this->m_incrementalTLRCURR;
	}

	inline FastSecurityDefinitionGroupInstrAttribItemInfo* GetFreeSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_securityDefinitionGroupInstrAttribItems->NewItem();
	}

	inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->NewItem();
	}

	inline FastSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_securityDefinitionMarketSegmentGrpItems->NewItem();
	}

	inline FastSecurityDefinitionInfo* GetFreeSecurityDefinitionInfo() {
		return this->m_securityDefinition;
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

	inline void Release(FastLogonInfo* info) {
	}

	inline void Release(FastLogoutInfo* info) {
	}

	inline void Release(FastGenericItemInfo* info) {
	}

	inline void Release(FastGenericInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastGenericItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastGenericItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalGenericInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastGenericItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastGenericItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastOLSFONDItemInfo* info) {
	}

	inline void Release(FastOLSFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOLSFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOLSFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastOLSCURRItemInfo* info) {
	}

	inline void Release(FastOLSCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOLSCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOLSCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastTLSFONDItemInfo* info) {
	}

	inline void Release(FastTLSFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastTLSFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastTLSFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastTLSCURRItemInfo* info) {
	}

	inline void Release(FastTLSCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastTLSCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastTLSCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastOBSFONDItemInfo* info) {
	}

	inline void Release(FastOBSFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOBSFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOBSFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastOBSCURRItemInfo* info) {
	}

	inline void Release(FastOBSCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOBSCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOBSCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalMSRFONDItemInfo* info) {
	}

	inline void Release(FastIncrementalMSRFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastIncrementalMSRFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastIncrementalMSRFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalMSRCURRItemInfo* info) {
	}

	inline void Release(FastIncrementalMSRCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastIncrementalMSRCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastIncrementalMSRCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalOLRFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOLSFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOLSFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalOLRCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOLSCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOLSCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalOBRFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOBSFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOBSFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalOBRCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastOBSCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastOBSCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalTLRFONDInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastTLSFONDItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastTLSFONDItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastIncrementalTLRCURRInfo* info) {
		if(info->GroupMDEntriesCount != 0) {
			PointerList<FastTLSCURRItemInfo> *list = info->GroupMDEntries[0]->Pointer->Owner();
			FastTLSCURRItemInfo **item = info->GroupMDEntries;
			for(int i = 0; i < info->GroupMDEntriesCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastSecurityDefinitionGroupInstrAttribItemInfo* info) {
	}

	inline void Release(FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* info) {
	}

	inline void Release(FastSecurityDefinitionMarketSegmentGrpItemInfo* info) {
		if(info->TradingSessionRulesGrpCount != 0) {
			PointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo> *list = info->TradingSessionRulesGrp[0]->Pointer->Owner();
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **item = info->TradingSessionRulesGrp;
			for(int i = 0; i < info->TradingSessionRulesGrpCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastSecurityDefinitionInfo* info) {
		if(info->GroupInstrAttribCount != 0) {
			PointerList<FastSecurityDefinitionGroupInstrAttribItemInfo> *list = info->GroupInstrAttrib[0]->Pointer->Owner();
			FastSecurityDefinitionGroupInstrAttribItemInfo **item = info->GroupInstrAttrib;
			for(int i = 0; i < info->GroupInstrAttribCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
		if(info->MarketSegmentGrpCount != 0) {
			PointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo> *list = info->MarketSegmentGrp[0]->Pointer->Owner();
			FastSecurityDefinitionMarketSegmentGrpItemInfo **item = info->MarketSegmentGrp;
			for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
				if(!(*item)->Used) {
					this->Release(*item);
					list->Push((*item)->Pointer);
				}
				item++;
			}
		}
	}

	inline void Release(FastSecurityStatusInfo* info) {
	}

	inline void Release(FastTradingSessionStatusInfo* info) {
	}

	inline void Release(FastHeartbeatInfo* info) {
	}

#pragma endregion

public:

    inline unsigned int SendMsgSeqNo() { return this->m_sendMsgSeqNo; }
    inline void IncSendMsgSeqNo() { this->m_sendMsgSeqNo++; }

    inline unsigned int RecvMsgSeqNo() { return this->m_recvMsgSeqNo; }
    inline void IncRecvMsgSeqNo() { this->m_recvMsgSeqNo++; }

	inline void* LastDecodeInfo() { return this->m_lastDecodedInfo; }

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

	FastSnapshotInfo* GetSnapshotInfoUnsupported() {
		return 0;
	}

#pragma region Print_Methods_Declaration_GeneratedCode
	void PrintLogon(FastLogonInfo *info);
	void PrintLogout(FastLogoutInfo *info);
	void PrintGeneric(FastGenericInfo *info);
	void PrintIncrementalGeneric(FastIncrementalGenericInfo *info);
	void PrintOLSFOND(FastOLSFONDInfo *info);
	void PrintOLSCURR(FastOLSCURRInfo *info);
	void PrintTLSFOND(FastTLSFONDInfo *info);
	void PrintTLSCURR(FastTLSCURRInfo *info);
	void PrintOBSFOND(FastOBSFONDInfo *info);
	void PrintOBSCURR(FastOBSCURRInfo *info);
	void PrintIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info);
	void PrintIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info);
	void PrintIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info);
	void PrintIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info);
	void PrintIncrementalOBRFOND(FastIncrementalOBRFONDInfo *info);
	void PrintIncrementalOBRCURR(FastIncrementalOBRCURRInfo *info);
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
	void PrintXmlOBSFOND(FastOBSFONDInfo *info);
	void PrintXmlOBSCURR(FastOBSCURRInfo *info);
	void PrintXmlIncrementalMSRFOND(FastIncrementalMSRFONDInfo *info);
	void PrintXmlIncrementalMSRCURR(FastIncrementalMSRCURRInfo *info);
	void PrintXmlIncrementalOLRFOND(FastIncrementalOLRFONDInfo *info);
	void PrintXmlIncrementalOLRCURR(FastIncrementalOLRCURRInfo *info);
	void PrintXmlIncrementalOBRFOND(FastIncrementalOBRFONDInfo *info);
	void PrintXmlIncrementalOBRCURR(FastIncrementalOBRCURRInfo *info);
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
	void* DecodeGeneric() {
		FastGenericInfo* info = GetFreeGenericInfo();
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
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
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
	void* DecodeOLSFOND() {
		FastOLSFONDInfo* info = GetFreeOLSFONDInfo();
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
		FastOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSFONDItemInfo();
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
	void* DecodeOLSCURR() {
		FastOLSCURRInfo* info = GetFreeOLSCURRInfo();
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
		FastOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSCURRItemInfo();
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
	void* DecodeTLSFOND() {
		FastTLSFONDInfo* info = GetFreeTLSFONDInfo();
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
		FastTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSFONDItemInfo();
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
	void* DecodeTLSCURR() {
		FastTLSCURRInfo* info = GetFreeTLSCURRInfo();
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
		FastTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSCURRItemInfo();
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
	void* DecodeOBSFOND() {
		FastOBSFONDInfo* info = GetFreeOBSFONDInfo();
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
		FastOBSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOBSFONDItemInfo();
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
	void* DecodeOBSCURR() {
		FastOBSCURRInfo* info = GetFreeOBSCURRInfo();
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
		FastOBSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOBSCURRItemInfo();
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
	void* DecodeIncrementalMSRFOND() {
		FastIncrementalMSRFONDInfo* info = GetFreeIncrementalMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastIncrementalMSRFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeIncrementalMSRFONDItemInfo();
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
	void* DecodeIncrementalMSRCURR() {
		FastIncrementalMSRCURRInfo* info = GetFreeIncrementalMSRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastIncrementalMSRCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeIncrementalMSRCURRItemInfo();
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
	void* DecodeIncrementalOBRFOND() {
		FastIncrementalOBRFONDInfo* info = GetFreeIncrementalOBRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOBSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOBSFONDItemInfo();
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
	void* DecodeIncrementalOBRCURR() {
		FastIncrementalOBRCURRInfo* info = GetFreeIncrementalOBRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOBSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOBSCURRItemInfo();
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
		SkipToNextField(); // TradingSessionID
		SkipToNextField(); // Symbol
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
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
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
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
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
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
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
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
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoOBSFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		SkipToNextField(); // TradSesStatus
		SkipToNextField(); // TradingSessionID
		SkipToNextField(); // Symbol
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoOBSCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		SkipToNextField(); // TradSesStatus
		SkipToNextField(); // TradingSessionID
		SkipToNextField(); // Symbol
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
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
	FastSnapshotInfo* GetSnapshotInfoIncrementalOBRFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoIncrementalOBRCURR() {
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
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoSecurityStatus() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoTradingSessionStatus() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
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
			case 2410:
				PrintOLSFOND((FastOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3500:
				PrintOLSCURR((FastOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2411:
				PrintTLSFOND((FastTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3501:
				PrintTLSCURR((FastTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2412:
				PrintOBSFOND((FastOBSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3502:
				PrintOBSCURR((FastOBSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2423:
				PrintIncrementalMSRFOND((FastIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3513:
				PrintIncrementalMSRCURR((FastIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2420:
				PrintIncrementalOLRFOND((FastIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3510:
				PrintIncrementalOLRCURR((FastIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2422:
				PrintIncrementalOBRFOND((FastIncrementalOBRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3512:
				PrintIncrementalOBRCURR((FastIncrementalOBRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2421:
				PrintIncrementalTLRFOND((FastIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3511:
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
			case 2410:
				PrintXmlOLSFOND((FastOLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3500:
				PrintXmlOLSCURR((FastOLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2411:
				PrintXmlTLSFOND((FastTLSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3501:
				PrintXmlTLSCURR((FastTLSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2412:
				PrintXmlOBSFOND((FastOBSFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3502:
				PrintXmlOBSCURR((FastOBSCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2423:
				PrintXmlIncrementalMSRFOND((FastIncrementalMSRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3513:
				PrintXmlIncrementalMSRCURR((FastIncrementalMSRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2420:
				PrintXmlIncrementalOLRFOND((FastIncrementalOLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3510:
				PrintXmlIncrementalOLRCURR((FastIncrementalOLRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2422:
				PrintXmlIncrementalOBRFOND((FastIncrementalOBRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3512:
				PrintXmlIncrementalOBRCURR((FastIncrementalOBRCURRInfo*)this->m_lastDecodedInfo);
				break;
			case 2421:
				PrintXmlIncrementalTLRFOND((FastIncrementalTLRFONDInfo*)this->m_lastDecodedInfo);
				break;
			case 3511:
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

