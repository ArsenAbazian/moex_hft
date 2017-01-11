#pragma once
#include "FixTypes.h"
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

	const int maxBufferLength = 16000;
	BYTE	        *buffer;
	BYTE	        *currentPos;
	int		        bufferLength;
    UINT            m_templateId;
    UINT64          m_presenceMap;

    FILE            *m_xmlFilePtr;

    FastSnapshotInfo *m_snapshotInfo;
	void			*m_lastDecodedInfo;

	UINT32			m_skipTemplateId[8];
	int				m_skipTemplateIdCount;

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

	void InitializeMessageInfo() {
		this->m_logon = new AutoAllocatePointerList<FastLogonInfo>(128, 256);
		this->m_logout = new AutoAllocatePointerList<FastLogoutInfo>(128, 256);
		this->m_genericItems = new AutoAllocatePointerList<FastGenericItemInfo>(128, 256);
		this->m_generic = new AutoAllocatePointerList<FastGenericInfo>(128, 256);
		this->m_incrementalGeneric = new AutoAllocatePointerList<FastIncrementalGenericInfo>(128, 256);
		this->m_oLSFONDItems = new AutoAllocatePointerList<FastOLSFONDItemInfo>(128, 256);
		this->m_oLSFOND = new AutoAllocatePointerList<FastOLSFONDInfo>(128, 256);
		this->m_oLSCURRItems = new AutoAllocatePointerList<FastOLSCURRItemInfo>(128, 256);
		this->m_oLSCURR = new AutoAllocatePointerList<FastOLSCURRInfo>(128, 256);
		this->m_tLSFONDItems = new AutoAllocatePointerList<FastTLSFONDItemInfo>(128, 256);
		this->m_tLSFOND = new AutoAllocatePointerList<FastTLSFONDInfo>(128, 256);
		this->m_tLSCURRItems = new AutoAllocatePointerList<FastTLSCURRItemInfo>(128, 256);
		this->m_tLSCURR = new AutoAllocatePointerList<FastTLSCURRInfo>(128, 256);
		this->m_incrementalMSRFOND = new AutoAllocatePointerList<FastIncrementalMSRFONDInfo>(128, 256);
		this->m_incrementalMSRCURR = new AutoAllocatePointerList<FastIncrementalMSRCURRInfo>(128, 256);
		this->m_incrementalOLRFOND = new AutoAllocatePointerList<FastIncrementalOLRFONDInfo>(128, 256);
		this->m_incrementalOLRCURR = new AutoAllocatePointerList<FastIncrementalOLRCURRInfo>(128, 256);
		this->m_incrementalTLRFOND = new AutoAllocatePointerList<FastIncrementalTLRFONDInfo>(128, 256);
		this->m_incrementalTLRCURR = new AutoAllocatePointerList<FastIncrementalTLRCURRInfo>(128, 256);
		this->m_securityDefinitionGroupInstrAttribItems = new AutoAllocatePointerList<FastSecurityDefinitionGroupInstrAttribItemInfo>(128, 256);
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(128, 256);
		this->m_securityDefinitionMarketSegmentGrpItems = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>(128, 256);
		this->m_securityDefinition = new AutoAllocatePointerList<FastSecurityDefinitionInfo>(128, 256);
		this->m_securityStatus = new AutoAllocatePointerList<FastSecurityStatusInfo>(128, 256);
		this->m_tradingSessionStatus = new AutoAllocatePointerList<FastTradingSessionStatusInfo>(128, 256);
		this->m_heartbeat = new AutoAllocatePointerList<FastHeartbeatInfo>(128, 256);
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
	inline FastLogonInfo* GetFreeLogonInfo() {
		return this->m_logon->NewItem();
	}

	inline FastLogoutInfo* GetFreeLogoutInfo() {
		return this->m_logout->NewItem();
	}

	inline FastGenericItemInfo* GetFreeGenericItemInfo() {
		return this->m_genericItems->NewItem();
	}

	inline FastGenericInfo* GetFreeGenericInfo() {
		return this->m_generic->NewItem();
	}

	inline FastIncrementalGenericInfo* GetFreeIncrementalGenericInfo() {
		return this->m_incrementalGeneric->NewItem();
	}

	inline FastOLSFONDItemInfo* GetFreeOLSFONDItemInfo() {
		return this->m_oLSFONDItems->NewItem();
	}

	inline FastOLSFONDInfo* GetFreeOLSFONDInfo() {
		return this->m_oLSFOND->NewItem();
	}

	inline FastOLSCURRItemInfo* GetFreeOLSCURRItemInfo() {
		return this->m_oLSCURRItems->NewItem();
	}

	inline FastOLSCURRInfo* GetFreeOLSCURRInfo() {
		return this->m_oLSCURR->NewItem();
	}

	inline FastTLSFONDItemInfo* GetFreeTLSFONDItemInfo() {
		return this->m_tLSFONDItems->NewItem();
	}

	inline FastTLSFONDInfo* GetFreeTLSFONDInfo() {
		return this->m_tLSFOND->NewItem();
	}

	inline FastTLSCURRItemInfo* GetFreeTLSCURRItemInfo() {
		return this->m_tLSCURRItems->NewItem();
	}

	inline FastTLSCURRInfo* GetFreeTLSCURRInfo() {
		return this->m_tLSCURR->NewItem();
	}

	inline FastIncrementalMSRFONDInfo* GetFreeIncrementalMSRFONDInfo() {
		return this->m_incrementalMSRFOND->NewItem();
	}

	inline FastIncrementalMSRCURRInfo* GetFreeIncrementalMSRCURRInfo() {
		return this->m_incrementalMSRCURR->NewItem();
	}

	inline FastIncrementalOLRFONDInfo* GetFreeIncrementalOLRFONDInfo() {
		return this->m_incrementalOLRFOND->NewItem();
	}

	inline FastIncrementalOLRCURRInfo* GetFreeIncrementalOLRCURRInfo() {
		return this->m_incrementalOLRCURR->NewItem();
	}

	inline FastIncrementalTLRFONDInfo* GetFreeIncrementalTLRFONDInfo() {
		return this->m_incrementalTLRFOND->NewItem();
	}

	inline FastIncrementalTLRCURRInfo* GetFreeIncrementalTLRCURRInfo() {
		return this->m_incrementalTLRCURR->NewItem();
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
		return this->m_securityDefinition->NewItem();
	}

	inline FastSecurityStatusInfo* GetFreeSecurityStatusInfo() {
		return this->m_securityStatus->NewItem();
	}

	inline FastTradingSessionStatusInfo* GetFreeTradingSessionStatusInfo() {
		return this->m_tradingSessionStatus->NewItem();
	}

	inline FastHeartbeatInfo* GetFreeHeartbeatInfo() {
		return this->m_heartbeat->NewItem();
	}

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
	inline bool CheckProcessNullUint64() {
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

	FastProtocolManager();
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
		if((info->AllowUsername = !CheckProcessNullString()))
			ReadString_Optional(&(info->Username), &(info->UsernameLength));
		if((info->AllowPassword = !CheckProcessNullString()))
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
		if((info->AllowText = !CheckProcessNullString()))
			ReadString_Optional(&(info->Text), &(info->TextLength));
		return info;
	}
	void* DecodeGeneric() {
		FastGenericInfo* info = GetFreeGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowTradingSessionID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		if((info->AllowTradSesStatus = !CheckProcessNullInt32()))
			info->TradSesStatus = ReadInt32_Optional();
		if((info->AllowMDSecurityTradingStatus = !CheckProcessNullInt32()))
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if((info->AllowAuctionIndicator = !CheckProcessNullUInt32()))
			info->AuctionIndicator = ReadUInt32_Optional();
		if((info->AllowNetChgPrevDay = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->NetChgPrevDay));

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if((gmdeItemInfo->AllowQuoteCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if((gmdeItemInfo->AllowTradeCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if((gmdeItemInfo->AllowOpenCloseSettlFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if((gmdeItemInfo->AllowOrdType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if((gmdeItemInfo->AllowEffectiveTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowStartTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowAccruedInterestAmt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if((gmdeItemInfo->AllowChgFromWAPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if((gmdeItemInfo->AllowChgOpenInterest = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if((gmdeItemInfo->AllowBidMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if((gmdeItemInfo->AllowAskMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if((gmdeItemInfo->AllowTotalNumOfTrades = !CheckProcessNullInt32()))
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if((gmdeItemInfo->AllowTotalVolume = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if((gmdeItemInfo->AllowOfferNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowBidNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowChgFromSettlmnt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if((gmdeItemInfo->AllowSumQtyOfBest = !CheckProcessNullInt32()))
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if((gmdeItemInfo->AllowOrderSide = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if((gmdeItemInfo->AllowOrderStatus = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if((gmdeItemInfo->AllowMinCurrPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if((gmdeItemInfo->AllowMinCurrPxChgTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowVolumeIndicator = !CheckProcessNullUInt32()))
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if((gmdeItemInfo->AllowPriceType = !CheckProcessNullInt32()))
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if((gmdeItemInfo->AllowNominalValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if((gmdeItemInfo->AllowRepoToPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if((gmdeItemInfo->AllowBuyBackPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if((gmdeItemInfo->AllowBuyBackDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowCXFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
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
			if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowEffectiveTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowStartTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if((gmdeItemInfo->AllowQuoteCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if((gmdeItemInfo->AllowTradeCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if((gmdeItemInfo->AllowOpenCloseSettlFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if((gmdeItemInfo->AllowOrdType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if((gmdeItemInfo->AllowNetChgPrevDay = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if((gmdeItemInfo->AllowAccruedInterestAmt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if((gmdeItemInfo->AllowChgFromWAPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if((gmdeItemInfo->AllowChgOpenInterest = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if((gmdeItemInfo->AllowBidMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if((gmdeItemInfo->AllowAskMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if((gmdeItemInfo->AllowTotalNumOfTrades = !CheckProcessNullInt32()))
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if((gmdeItemInfo->AllowTotalVolume = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if((gmdeItemInfo->AllowOfferNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowBidNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowChgFromSettlmnt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if((gmdeItemInfo->AllowSumQtyOfBest = !CheckProcessNullInt32()))
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if((gmdeItemInfo->AllowOrderSide = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if((gmdeItemInfo->AllowOrderStatus = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if((gmdeItemInfo->AllowMinCurrPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if((gmdeItemInfo->AllowMinCurrPxChgTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowVolumeIndicator = !CheckProcessNullUInt32()))
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if((gmdeItemInfo->AllowPriceType = !CheckProcessNullInt32()))
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if((gmdeItemInfo->AllowNominalValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if((gmdeItemInfo->AllowRepoToPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if((gmdeItemInfo->AllowBuyBackPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if((gmdeItemInfo->AllowBuyBackDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowCXFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
		}

		return info;
	}
	void* DecodeOLSFOND() {
		FastOLSFONDInfo* info = GetFreeOLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		if((info->AllowTradSesStatus = !CheckProcessNullInt32()))
			info->TradSesStatus = ReadInt32_Optional();
		if((info->AllowTradingSessionID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowMDSecurityTradingStatus = !CheckProcessNullInt32()))
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if((info->AllowAuctionIndicator = !CheckProcessNullUInt32()))
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTypePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else {
					gmdeItemInfo->CopyMDEntryType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowMDEntryType = false;
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryDatePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTimePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrigTimePresenceIndex)) {
				if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyOrigTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowOrigTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryPxPresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->CopyMDEntryPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntrySizePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->CopyMDEntrySize = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntrySize = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->YieldPresenceIndex)) {
				if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
				else
					gmdeItemInfo->CopyYield = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowYield = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrderStatusPresenceIndex)) {
				if((gmdeItemInfo->AllowOrderStatus = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else {
					gmdeItemInfo->CopyOrderStatus = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrderStatus = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrdTypePresenceIndex)) {
				if((gmdeItemInfo->AllowOrdType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
				else {
					gmdeItemInfo->CopyOrdType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrdType = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TotalVolumePresenceIndex)) {
				if((gmdeItemInfo->AllowTotalVolume = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
				else
					gmdeItemInfo->CopyTotalVolume = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowTotalVolume = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionSubIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionSubID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionSubID = false;
		}

		return info;
	}
	void* DecodeOLSCURR() {
		FastOLSCURRInfo* info = GetFreeOLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		if((info->AllowTradSesStatus = !CheckProcessNullInt32()))
			info->TradSesStatus = ReadInt32_Optional();
		if((info->AllowTradingSessionID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowMDSecurityTradingStatus = !CheckProcessNullInt32()))
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTypePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else {
					gmdeItemInfo->CopyMDEntryType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowMDEntryType = false;
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryDatePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTimePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrigTimePresenceIndex)) {
				if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyOrigTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowOrigTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryPxPresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->CopyMDEntryPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntrySizePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->CopyMDEntrySize = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntrySize = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrderStatusPresenceIndex)) {
				if((gmdeItemInfo->AllowOrderStatus = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else {
					gmdeItemInfo->CopyOrderStatus = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrderStatus = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionSubIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionSubID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionSubID = false;
		}

		return info;
	}
	void* DecodeTLSFOND() {
		FastTLSFONDInfo* info = GetFreeTLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		if((info->AllowTradSesStatus = !CheckProcessNullInt32()))
			info->TradSesStatus = ReadInt32_Optional();
		if((info->AllowTradingSessionID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowMDSecurityTradingStatus = !CheckProcessNullInt32()))
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if((info->AllowAuctionIndicator = !CheckProcessNullUInt32()))
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryDatePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTimePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrigTimePresenceIndex)) {
				if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyOrigTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowOrigTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrderSidePresenceIndex)) {
				if((gmdeItemInfo->AllowOrderSide = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
				else {
					gmdeItemInfo->CopyOrderSide = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrderSide = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryPxPresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->CopyMDEntryPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntrySizePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->CopyMDEntrySize = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntrySize = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->AccruedInterestAmtPresenceIndex)) {
				if((gmdeItemInfo->AllowAccruedInterestAmt = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
				else
					gmdeItemInfo->CopyAccruedInterestAmt = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowAccruedInterestAmt = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradeValuePresenceIndex)) {
				if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
				else
					gmdeItemInfo->CopyTradeValue = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowTradeValue = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->YieldPresenceIndex)) {
				if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
				else
					gmdeItemInfo->CopyYield = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowYield = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->SettlDatePresenceIndex)) {
				if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopySettlDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowSettlDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->SettleTypePresenceIndex)) {
				if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
				else {
					gmdeItemInfo->CopySettleType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowSettleType = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->PricePresenceIndex)) {
				if((gmdeItemInfo->AllowPrice = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
				else
					gmdeItemInfo->CopyPrice = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowPrice = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->PriceTypePresenceIndex)) {
				if((gmdeItemInfo->AllowPriceType = !CheckProcessNullInt32()))
					gmdeItemInfo->PriceType = ReadInt32_Optional();
				else
					gmdeItemInfo->CopyPriceType = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowPriceType = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->RepoToPxPresenceIndex)) {
				if((gmdeItemInfo->AllowRepoToPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
				else
					gmdeItemInfo->CopyRepoToPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowRepoToPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->BuyBackPxPresenceIndex)) {
				if((gmdeItemInfo->AllowBuyBackPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
				else
					gmdeItemInfo->CopyBuyBackPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowBuyBackPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->BuyBackDatePresenceIndex)) {
				if((gmdeItemInfo->AllowBuyBackDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyBuyBackDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowBuyBackDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionSubIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionSubID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionSubID = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->RefOrderIDPresenceIndex)) {
				if((gmdeItemInfo->AllowRefOrderID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
				else {
					gmdeItemInfo->CopyRefOrderID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowRefOrderID = false;
		}

		return info;
	}
	void* DecodeTLSCURR() {
		FastTLSCURRInfo* info = GetFreeTLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		if((info->AllowTradSesStatus = !CheckProcessNullInt32()))
			info->TradSesStatus = ReadInt32_Optional();
		if((info->AllowTradingSessionID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowMDSecurityTradingStatus = !CheckProcessNullInt32()))
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryDatePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTimePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrigTimePresenceIndex)) {
				if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyOrigTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowOrigTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrderSidePresenceIndex)) {
				if((gmdeItemInfo->AllowOrderSide = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
				else {
					gmdeItemInfo->CopyOrderSide = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrderSide = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryPxPresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->CopyMDEntryPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntrySizePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->CopyMDEntrySize = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntrySize = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradeValuePresenceIndex)) {
				if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
				else
					gmdeItemInfo->CopyTradeValue = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowTradeValue = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->SettlDatePresenceIndex)) {
				if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->SettlDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopySettlDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowSettlDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->SettleTypePresenceIndex)) {
				if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
				else {
					gmdeItemInfo->CopySettleType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowSettleType = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->PricePresenceIndex)) {
				if((gmdeItemInfo->AllowPrice = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
				else
					gmdeItemInfo->CopyPrice = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowPrice = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->PriceTypePresenceIndex)) {
				if((gmdeItemInfo->AllowPriceType = !CheckProcessNullInt32()))
					gmdeItemInfo->PriceType = ReadInt32_Optional();
				else
					gmdeItemInfo->CopyPriceType = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowPriceType = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->RepoToPxPresenceIndex)) {
				if((gmdeItemInfo->AllowRepoToPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
				else
					gmdeItemInfo->CopyRepoToPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowRepoToPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->BuyBackPxPresenceIndex)) {
				if((gmdeItemInfo->AllowBuyBackPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
				else
					gmdeItemInfo->CopyBuyBackPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowBuyBackPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->BuyBackDatePresenceIndex)) {
				if((gmdeItemInfo->AllowBuyBackDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyBuyBackDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowBuyBackDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionSubIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionSubID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionSubID = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->RefOrderIDPresenceIndex)) {
				if((gmdeItemInfo->AllowRefOrderID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
				else {
					gmdeItemInfo->CopyRefOrderID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowRefOrderID = false;
		}

		return info;
	}
	void* DecodeIncrementalMSRFOND() {
		FastIncrementalMSRFONDInfo* info = GetFreeIncrementalMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowStartTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowQuoteCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if((gmdeItemInfo->AllowTradeCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if((gmdeItemInfo->AllowOpenCloseSettlFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if((gmdeItemInfo->AllowNetChgPrevDay = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if((gmdeItemInfo->AllowAccruedInterestAmt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if((gmdeItemInfo->AllowChgFromWAPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if((gmdeItemInfo->AllowChgOpenInterest = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if((gmdeItemInfo->AllowBidMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if((gmdeItemInfo->AllowAskMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if((gmdeItemInfo->AllowTotalNumOfTrades = !CheckProcessNullInt32()))
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if((gmdeItemInfo->AllowOfferNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowBidNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowChgFromSettlmnt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if((gmdeItemInfo->AllowMinCurrPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if((gmdeItemInfo->AllowMinCurrPxChgTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowVolumeIndicator = !CheckProcessNullUInt32()))
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if((gmdeItemInfo->AllowCXFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
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
		FastGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowStartTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowQuoteCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if((gmdeItemInfo->AllowTradeCondition = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if((gmdeItemInfo->AllowOpenCloseSettlFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if((gmdeItemInfo->AllowNetChgPrevDay = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if((gmdeItemInfo->AllowChgFromWAPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if((gmdeItemInfo->AllowChgOpenInterest = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if((gmdeItemInfo->AllowBidMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if((gmdeItemInfo->AllowAskMarketSize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if((gmdeItemInfo->AllowTotalNumOfTrades = !CheckProcessNullInt32()))
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if((gmdeItemInfo->AllowOfferNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowBidNbOr = !CheckProcessNullInt32()))
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if((gmdeItemInfo->AllowChgFromSettlmnt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if((gmdeItemInfo->AllowCXFlag = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
			if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
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

			if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTypePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else {
					gmdeItemInfo->CopyMDEntryType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowMDEntryType = false;
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->SymbolPresenceIndex)) {
				if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
				else {
					gmdeItemInfo->CopySymbol = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowSymbol = false;
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryDatePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTimePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrigTimePresenceIndex)) {
				if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyOrigTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowOrigTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryPxPresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->CopyMDEntryPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntrySizePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->CopyMDEntrySize = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntrySize = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->YieldPresenceIndex)) {
				if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
				else
					gmdeItemInfo->CopyYield = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowYield = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrderStatusPresenceIndex)) {
				if((gmdeItemInfo->AllowOrderStatus = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else {
					gmdeItemInfo->CopyOrderStatus = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrderStatus = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrdTypePresenceIndex)) {
				if((gmdeItemInfo->AllowOrdType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
				else {
					gmdeItemInfo->CopyOrdType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrdType = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TotalVolumePresenceIndex)) {
				if((gmdeItemInfo->AllowTotalVolume = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
				else
					gmdeItemInfo->CopyTotalVolume = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowTotalVolume = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionID = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionSubIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionSubID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionSubID = false;
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

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDUpdateActionPresenceIndex)) {
				if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDUpdateAction = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDUpdateAction = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTypePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryType = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
				else {
					gmdeItemInfo->CopyMDEntryType = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowMDEntryType = false;
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->SymbolPresenceIndex)) {
				if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
				else {
					gmdeItemInfo->CopySymbol = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowSymbol = false;
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryDatePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryDate = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryDate = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryTimePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyMDEntryTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrigTimePresenceIndex)) {
				if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
					gmdeItemInfo->OrigTime = ReadUInt32_Optional();
				else
					gmdeItemInfo->CopyOrigTime = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowOrigTime = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntryPxPresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
				else
					gmdeItemInfo->CopyMDEntryPx = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntryPx = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->MDEntrySizePresenceIndex)) {
				if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
				else
					gmdeItemInfo->CopyMDEntrySize = true;
					gmdeItemInfo->CopyCount++;
			}
			else
				gmdeItemInfo-> AllowMDEntrySize = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->OrderStatusPresenceIndex)) {
				if((gmdeItemInfo->AllowOrderStatus = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
				else {
					gmdeItemInfo->CopyOrderStatus = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowOrderStatus = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionID = false;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, gmdeItemInfo->TradingSessionSubIDPresenceIndex)) {
				if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
				else {
					gmdeItemInfo->CopyTradingSessionSubID = true;
					gmdeItemInfo->CopyCount++;
				}
			}
			else
				gmdeItemInfo-> AllowTradingSessionSubID = false;
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
			if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowOrderSide = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if((gmdeItemInfo->AllowAccruedInterestAmt = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if((gmdeItemInfo->AllowYield = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if((gmdeItemInfo->AllowPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if((gmdeItemInfo->AllowPriceType = !CheckProcessNullInt32()))
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if((gmdeItemInfo->AllowRepoToPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if((gmdeItemInfo->AllowBuyBackPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if((gmdeItemInfo->AllowBuyBackDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			if((gmdeItemInfo->AllowRefOrderID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
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
			if((gmdeItemInfo->AllowMDUpdateAction = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if((gmdeItemInfo->AllowMDEntryID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if((gmdeItemInfo->AllowSymbol = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if((gmdeItemInfo->AllowRptSeq = !CheckProcessNullInt32()))
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowMDEntryTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowOrigTime = !CheckProcessNullUInt32()))
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowOrderSide = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if((gmdeItemInfo->AllowMDEntryPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if((gmdeItemInfo->AllowMDEntrySize = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if((gmdeItemInfo->AllowTradeValue = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if((gmdeItemInfo->AllowSettlDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowSettleType = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if((gmdeItemInfo->AllowPrice = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if((gmdeItemInfo->AllowPriceType = !CheckProcessNullInt32()))
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if((gmdeItemInfo->AllowRepoToPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if((gmdeItemInfo->AllowBuyBackPx = !CheckProcessNullDecimal()))
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if((gmdeItemInfo->AllowBuyBackDate = !CheckProcessNullUInt32()))
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if((gmdeItemInfo->AllowTradingSessionID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if((gmdeItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			if((gmdeItemInfo->AllowRefOrderID = !CheckProcessNullString()))
				ReadString_Optional(&(gmdeItemInfo->RefOrderID), &(gmdeItemInfo->RefOrderIDLength));
		}

		return info;
	}
	void* DecodeSecurityDefinition() {
		FastSecurityDefinitionInfo* info = GetFreeSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowTotNumReports = !CheckProcessNullInt32()))
			info->TotNumReports = ReadInt32_Optional();
		if((info->AllowSymbol = !CheckProcessNullString()))
			ReadString_Optional(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowSecurityID = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->SecurityID), &(info->SecurityIDLength));
		if((info->AllowSecurityIDSource = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->SecurityIDSource), &(info->SecurityIDSourceLength));
		if((info->AllowProduct = !CheckProcessNullInt32()))
			info->Product = ReadInt32_Optional();
		if((info->AllowCFICode = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->CFICode), &(info->CFICodeLength));
		if((info->AllowSecurityType = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->SecurityType), &(info->SecurityTypeLength));
		if((info->AllowMaturityDate = !CheckProcessNullUInt32()))
			info->MaturityDate = ReadUInt32_Optional();
		if((info->AllowSettlDate = !CheckProcessNullUInt32()))
			info->SettlDate = ReadUInt32_Optional();
		if((info->AllowSettleType = !CheckProcessNullString()))
			ReadString_Optional(&(info->SettleType), &(info->SettleTypeLength));
		if((info->AllowOrigIssueAmt = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->OrigIssueAmt));
		if((info->AllowCouponPaymentDate = !CheckProcessNullUInt32()))
			info->CouponPaymentDate = ReadUInt32_Optional();
		if((info->AllowCouponRate = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->CouponRate));
		if((info->AllowSettlFixingDate = !CheckProcessNullUInt32()))
			info->SettlFixingDate = ReadUInt32_Optional();
		if((info->AllowDividendNetPx = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->DividendNetPx));
		if((info->AllowSecurityDesc = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->SecurityDesc), &(info->SecurityDescLength));
		if((info->AllowEncodedSecurityDesc = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->EncodedSecurityDesc), &(info->EncodedSecurityDescLength));
		if((info->AllowQuoteText = !CheckProcessNullByteVector()))
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
			if((giaItemInfo->AllowInstrAttribValue = !CheckProcessNullByteVector()))
				ReadByteVector_Optional(&(giaItemInfo->InstrAttribValue), &(giaItemInfo->InstrAttribValueLength));
		}

		if((info->AllowCurrency = !CheckProcessNullString()))
			ReadString_Optional(&(info->Currency), &(info->CurrencyLength));

		if(!CheckProcessNullInt32())
			info->MarketSegmentGrpCount = ReadUInt32_Optional();
		else
			info->MarketSegmentGrpCount = 0;
		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpItemInfo();
			info->MarketSegmentGrp[i] = msgItemInfo;
			if((msgItemInfo->AllowRoundLot = !CheckProcessNullDecimal()))
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
				if((tsrgItemInfo->AllowTradingSessionSubID = !CheckProcessNullString()))
					ReadString_Optional(&(tsrgItemInfo->TradingSessionSubID), &(tsrgItemInfo->TradingSessionSubIDLength));
				if((tsrgItemInfo->AllowSecurityTradingStatus = !CheckProcessNullInt32()))
					tsrgItemInfo->SecurityTradingStatus = ReadInt32_Optional();
				if((tsrgItemInfo->AllowOrderNote = !CheckProcessNullInt32()))
					tsrgItemInfo->OrderNote = ReadInt32_Optional();
			}

		}

		if((info->AllowSettlCurrency = !CheckProcessNullString()))
			ReadString_Optional(&(info->SettlCurrency), &(info->SettlCurrencyLength));
		if((info->AllowPriceType = !CheckProcessNullInt32()))
			info->PriceType = ReadInt32_Optional();
		if((info->AllowStateSecurityID = !CheckProcessNullString()))
			ReadString_Optional(&(info->StateSecurityID), &(info->StateSecurityIDLength));
		if((info->AllowEncodedShortSecurityDesc = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->EncodedShortSecurityDesc), &(info->EncodedShortSecurityDescLength));
		if((info->AllowMarketCode = !CheckProcessNullByteVector()))
			ReadByteVector_Optional(&(info->MarketCode), &(info->MarketCodeLength));
		if((info->AllowMinPriceIncrement = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if((info->AllowMktShareLimit = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->MktShareLimit));
		if((info->AllowMktShareThreshold = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->MktShareThreshold));
		if((info->AllowMaxOrdersVolume = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->MaxOrdersVolume));
		if((info->AllowPriceMvmLimit = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->PriceMvmLimit));
		if((info->AllowFaceValue = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->FaceValue));
		if((info->AllowBaseSwapPx = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->BaseSwapPx));
		if((info->AllowRepoToPx = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->RepoToPx));
		if((info->AllowBuyBackPx = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->BuyBackPx));
		if((info->AllowBuyBackDate = !CheckProcessNullUInt32()))
			info->BuyBackDate = ReadUInt32_Optional();
		if((info->AllowNoSharesIssued = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->NoSharesIssued));
		if((info->AllowHighLimit = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->HighLimit));
		if((info->AllowLowLimit = !CheckProcessNullDecimal()))
			ReadDecimal_Optional(&(info->LowLimit));
		if((info->AllowNumOfDaysToMaturity = !CheckProcessNullInt32()))
			info->NumOfDaysToMaturity = ReadInt32_Optional();
		return info;
	}
	void* DecodeSecurityStatus() {
		FastSecurityStatusInfo* info = GetFreeSecurityStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if((info->AllowTradingSessionID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		if((info->AllowTradingSessionSubID = !CheckProcessNullString()))
			ReadString_Optional(&(info->TradingSessionSubID), &(info->TradingSessionSubIDLength));
		if((info->AllowSecurityTradingStatus = !CheckProcessNullInt32()))
			info->SecurityTradingStatus = ReadInt32_Optional();
		if((info->AllowAuctionIndicator = !CheckProcessNullUInt32()))
			info->AuctionIndicator = ReadUInt32_Optional();
		return info;
	}
	void* DecodeTradingSessionStatus() {
		FastTradingSessionStatusInfo* info = GetFreeTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesStatus = ReadInt32_Mandatory();
		if((info->AllowText = !CheckProcessNullString()))
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
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
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
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoOLSCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoTLSFOND() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
			info->RouteFirst = ReadUInt32_Optional();
		return info;
	}
	FastSnapshotInfo* GetSnapshotInfoTLSCURR() {
		FastSnapshotInfo *info = GetFreeSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		info->SendingTime = ReadUInt64_Mandatory();
		if((info->AllowLastMsgSeqNumProcessed = !CheckProcessNullUInt32()))
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if((info->AllowLastFragment = !CheckProcessNullUInt32()))
			info->LastFragment = ReadUInt32_Optional();
		if((info->AllowRouteFirst = !CheckProcessNullUInt32()))
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

