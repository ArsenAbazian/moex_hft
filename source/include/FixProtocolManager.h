#pragma once
#pragma once

#include "FixTypes.h"
#include "ItoaConverter.h"
#include "DtoaConverter.h"
#include "UTCTimeConverter.h"
#include "SocketBufferManager.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "FixMessage.h"
#include "WinSockManager.h"

#define AddTagValue(tagName, tagValue) tagName AddEqual(); AddValue(tagValue); AddSeparator();
#define AddTagSymbolValue(tagName, tagValue) tagName AddEqual(); AddSymbol(tagValue); AddSeparator();
#define AddTagString(tagName, tagValueString) tagName AddEqual(); AddArray(tagValueString); AddSeparator();
#define AddTagString2(tagName, tagValueString, length) tagName AddEqual(); AddArray(tagValueString, length); AddSeparator();
#define AddTagData(tagName, tagData, tagDataLen) tagName AddEqual(); AddArray(tagData, tagDataLen); AddSeparator();

class FixProtocolManager {

	char                            senderComputerId[100];
	char                            targetComputerId[100];
	int                             senderComputerIdLength;
	int                             targetComputerIdLength;

	const char 						*m_protocolVersion;
	int								m_protocolVersionLength;

	SYSTEMTIME		                *currentTime;

    int                             receivedMessageLength;
	unsigned char                   *m_sendMessageBuffer;
    int                             m_sendItemStartIndex;
    char                            *messageBuffer;
	int                             messageBufferSize;

    const int                       m_maxRecvMessageCount = 128;
    int                             m_recvMessageCount;
    FixProtocolMessage              *m_currMsg;
    FixProtocolMessage              *m_recvMessage[128];

    char                            *currentPos;
	int                             m_sendMsgSeqNo;
	int								m_recvMsgSeqNo;

	DtoaConverter                   *doubleConverter;
	ItoaConverter                   *intConverter;

    ISocketBufferProvider           *m_bufferProvider;
    SocketBuffer                    *m_sendBuffer;
    SocketBuffer                    *m_recvBuffer;
    FixRejectInfo                   *m_rejectInfo;

	inline void AddSymbol(char symbol) { *(this->currentPos) = symbol; this->currentPos++; }
	inline void AddEqual() { *(this->currentPos) = '='; this->currentPos++; }
	inline void AddSeparator() { AddSymbol(0x01); }
	inline void AddTag(const char* tag, int length) { AddArray((char*)tag, length); AddSymbol('='); }

public:
	FixProtocolManager(ISocketBufferProvider *provider) : FixProtocolManager(provider, FixProtocolVersion) { }
	FixProtocolManager(ISocketBufferProvider *provider, const char *protocolVersion);
	~FixProtocolManager();

    inline FixRejectInfo* RejectInfo() { return this->m_rejectInfo; }

	inline const char* SenderCompId() { return this->senderComputerId; }
	inline int SenderCompIdLength() { return this->senderComputerIdLength; }

	inline const char* TargetCompId() { return this->targetComputerId; }
	inline int TargetCompIdLength() { return this->targetComputerIdLength; }

	inline void PrintBufferFromCurrent() {
		int start = this->currentPos - this->messageBuffer;
		for(int i = 0; i < this->messageBufferSize - start; i++) {
			if(i == this->messageBufferSize - start - 1)
				printf("%02x", this->currentPos[i]);
			else
				printf("%02x ", this->currentPos[i]);
		}
	}

    inline void PrepareSendBuffer() {
        this->m_sendMessageBuffer = this->m_sendBuffer->CurrentPos();
        this->m_sendItemStartIndex = this->m_sendBuffer->CurrentItemIndex();
        this->SetMessageBuffer((char*)this->m_sendMessageBuffer);
    }

    inline void PrepareRecvBuffer() {
        this->SetMessageBuffer((char*)this->m_recvBuffer->CurrentPos());
    }

    inline bool FindSendMessageInHistory(int msgSeqNo, char **msgBuffer, int *msgSize) {
        if(msgSeqNo >= this->m_sendBuffer->ItemsCount())
            return false;
        *msgBuffer = (char*)this->m_sendBuffer->Item(msgSeqNo - 1);
        *msgSize = this->m_sendBuffer->ItemLength(msgSeqNo - 1);
        return true;
    }

    inline SocketBuffer* SendSocketBuffer() { return this->m_sendBuffer; }
    inline unsigned char* SendBuffer() { return this->m_sendMessageBuffer; }
    inline unsigned char* RecvBuffer() { return (unsigned char*)this->messageBuffer; }

    inline unsigned int SendBufferSize() { return (unsigned int)(this->currentPos - ((char*)this->m_sendMessageBuffer)); }
    inline bool SendFix(WinSockManager *manager) {
		DefaultLogManager::Default->WriteFix(LogMessageCode::lmcFixProtocolManager_SendFix, this->m_sendBuffer->BufferIndex(), this->m_sendItemStartIndex);
#ifdef TEST
        return true;
#else
        return manager->Send(this->SendBuffer(), this->SendBufferSize());
#endif
    }
    inline bool RecvFix(WinSockManager *manager) {
        this->PrepareRecvBuffer();
        bool res = manager->Recv(this->RecvBuffer());
        int size = manager->RecvSize();
		if(res && size > 0) {
            manager->RecvBytes()[size] = '\0';
            this->SetRecvBufferSize(size);
            this->m_recvBuffer->SetCurrentItemSize(size);
            DefaultLogManager::Default->WriteFix(LogMessageCode::lmcFixProtocolManager_RecvFix, this->m_recvBuffer->BufferIndex(), this->m_recvBuffer->CurrentItemIndex());
        }
        else {
            DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcFixProtocolManager_RecvFix, false);
        }
        return res;
    }

    inline void SaveSendMessage() {
        AddStringZero();
        this->m_sendBuffer->Next(this->MessageLength());
        DefaultLogManager::Default->WriteFix(LogMessageCode::lmcFixMessage, this->m_sendBuffer->BufferIndex(), this->m_sendBuffer->CurrentItemIndex() - 1);
    }

	inline void StartNewMessage() {
		this->currentPos = this->messageBuffer;
		*(this->currentPos) = '\0';
	}

    inline int FindSeparator(int start) {
        int len = start;
        unsigned int *pack4 = (unsigned int*)(this->messageBuffer + start);
        while(len < this->messageBufferSize) {
            unsigned int value = *pack4;
            if((value & 0x000000ff) == FIX_SEPARATOR)
                return len;
            if((value & 0x0000ff00) == FIX_SEPARATOR_SECOND_BYTE)
                return len + 1;
            if((value & 0x00ff0000) == FIX_SEPARATOR_THIRD_BYTE)
                return len + 2;
            if((value & 0xff000000) == FIX_SEPARATOR_FORTH_BYTE)
                return len + 3;
            len += 4;
            pack4++;
        }
        return -1;
    }

    inline void ProcessSplitRecvMessages() {
        FixProtocolMessage **msgPtr = this->m_recvMessage;
        FixProtocolMessage *msg = *msgPtr;
        int tagStart = 0;

        msg->Reset();
        msg->Buffer(this->messageBuffer);
        this->m_recvMessageCount = 0;

        int separatorIndex = FindSeparator(0);
        int msgStart = 0;
        while(separatorIndex != -1) {
            msg->AddTag(&this->messageBuffer[tagStart], separatorIndex - tagStart);
            tagStart = separatorIndex + 1;
            // 8= -> 0x3d38
            if(*((unsigned short*)&(this->messageBuffer[tagStart])) == 0x3d38 ) {
                msg->Size(separatorIndex - msgStart + 1);
                this->m_recvBuffer->Next(msg->Size());
                msgStart = tagStart;
                msgPtr++; msg = *msgPtr;
                msg->Reset();
                msg->Buffer(this->messageBuffer + tagStart);
                this->m_recvMessageCount++;
            }
            if(separatorIndex == this->messageBufferSize - 1) {
                this->m_recvMessageCount++;
                msg->Size(separatorIndex - msgStart + 1);
                this->m_recvBuffer->Next(msg->Size());
                break;
            }
            separatorIndex = FindSeparator(tagStart);
        }
    }

    inline void SelectRecvMessage(int index) {
        this->m_currMsg = this->m_recvMessage[index];
        this->messageBuffer = this->m_currMsg->Buffer();
        this->messageBufferSize = this->m_currMsg->Size();
        this->currentPos = this->messageBuffer;
    }
    inline FixProtocolMessage* RecvMessage(int index) { return this->m_recvMessage[index]; }
    inline int RecvMessageCount() { return this->m_recvMessageCount; }
	inline FixProtocolMessage* Message(int index) { return this->m_recvMessage[index]; }
    
    inline void ResetSendMsgSeqNo() { this->SetSendMsgSeqNo(1); }
	inline void SetSendMsgSeqNo(int value) { this->m_sendMsgSeqNo = value; }
    inline void IncSendMsgSeqNo() { this->m_sendMsgSeqNo++; }

	inline void ResetRecvMsgSeqNo() { this->SetRecvMsgSeqNo(1); }
	inline void SetRecvMsgSeqNo(int value) { this->m_recvMsgSeqNo = value; }
	inline void IncRecvMsgSeqNo() { this->m_recvMsgSeqNo++; }

    inline bool ProcessCheckHeader() { return this->Message(0)->ProcessCheckHeader(); }
    inline FixHeaderInfo* Header() { return this->Message(0)->Header(); }
    inline bool CheckDetectCorrectMsgSeqNumber() {
		return this->Message(0)->CheckDetectCorrectMsgSeqNumber(&(this->m_recvMsgSeqNo));
	}

	inline void AddArray(char *string, int length) {
		memcpy(this->currentPos, string, length);
		this->currentPos += length;
	}
	inline void AddArray(const char *string, int length) {
		memcpy(this->currentPos, string, length);
		this->currentPos += length;
	}
	inline int InToString(char *tempBuffer, int value) {
		return this->intConverter->Convert(tempBuffer, value);
	}
	int InToString(char *tempBuffer, int value, int minValueLen) {
		return this->intConverter->Convert(tempBuffer, value, minValueLen);
	}
	inline void AddValue(int value) { 
		this->currentPos += InToString(this->currentPos, value);
	}
	inline void AddValue(int value, int minDigitCount) {
		this->currentPos += InToString(this->currentPos, value, minDigitCount);
	}
	inline void AddValue(bool value) { 
		AddSymbol(value ? 'Y' : 'N');
	}
	inline void AddValue(char value) { 
		AddSymbol(value);
	}
	inline void AddFixHeader() {
		AddTagBeginString
		AddEqual();
		AddArray((char*)this->m_protocolVersion, this->m_protocolVersionLength);
		AddSeparator();
	}

	inline void AddBodyLength() {
		AddTagBodyLength
		AddEqual();
		AddZeroSymbols(3);
		AddSeparator();
	}

	inline void AddZeroSymbols(int count) {
		this->currentPos += count;
	}

	inline void AddMessageType(char messageType) {
		AddTagMsgType
		AddEqual();
		AddSymbol(messageType);
		AddSeparator();
	}

	inline void AddSenderComputerId() {
		AddTagSenderCompID
		AddEqual();
		AddArray(this->senderComputerId, this->senderComputerIdLength);
		AddSeparator();
	}

	inline void AddTargetComputerId() {
		AddTagTargetCompID
		AddEqual();
		AddArray(this->targetComputerId, this->targetComputerIdLength);
		AddSeparator();
	}

	inline void AddMessageSeqNumber(int messageSeqNumber) {
		AddTagMsgSeqNum
		AddEqual();
		AddValue(messageSeqNumber);
		AddSeparator();
	}

	private: UTCTimeConverter *timeConverter;

	public:
	inline int GetUTCTimeString(char *buf) {
		return this->timeConverter->GetCurrentTimeString(buf);
	}

	inline void AddFullDateTimeValue(SYSTEMTIME *st) {
		this->currentPos += this->timeConverter->ToString(this->currentPos, st);
	}

	inline void AddDateValue(SYSTEMTIME *st) {
		this->currentPos += this->timeConverter->ToDateString(this->currentPos, st);
	}

	inline void AddDateValue(int year, int month, int day) {
		this->currentPos += this->timeConverter->ToDateString(this->currentPos, year, month, day);
	}

	inline void     AddStringZero() { *(this->currentPos) = '\0'; }

public:
	inline char*	Message() { return this->messageBuffer; }
	inline int		MessageLength() { return this->currentPos - this->messageBuffer; }

	inline void AddSendingTime() {
		AddTagSendingTime
        AddEqual();
		this->currentPos += GetUTCTimeString(this->currentPos);
		AddSeparator();
	}

	inline void SetSenderComputerId(const char *senderComputerId) {
		strcpy(this->senderComputerId, senderComputerId);
		this->senderComputerIdLength = strlen(senderComputerId);
	}

	inline void SetTargetComputerId(const char *targetComputerId) {
		strcpy(this->targetComputerId, targetComputerId);
		this->targetComputerIdLength = strlen(targetComputerId);
	}

	inline void UpdateLengthTagValue() {
		const int HeaderTagLength = 3 + this->m_protocolVersionLength; // 8=FIX.4.4|
		const int MessageLengthLength = 6;
		InToString(&(this->messageBuffer[HeaderTagLength + 2]), this->MessageLength() - HeaderTagLength - MessageLengthLength, 3);
	}

	inline void AddHeader(char messageType) {
		AddHeader(messageType, false);
	}

	inline void AddHeader(char messageType, bool possResend) {
		AddFixHeader();
		AddBodyLength();
		AddMessageType(messageType);
		AddSenderComputerId();
		AddTargetComputerId();
		AddMessageSeqNumber(this->m_sendMsgSeqNo);
		if (possResend) {
			AddTagPossResend
            AddEqual(); AddValue('Y');
		}
		AddSendingTime();
	}

	inline int CalcCheckSum() {
		int sum = 0;
		char *buf = this->messageBuffer;
		int length = this->currentPos - this->messageBuffer;
		*((int*)this->currentPos) = 0;
		for (int i = 0; i < length; i++, buf++)
			sum += (unsigned int)*buf;
		return sum & 0xff;
	}

	inline void AddCheckSum() {
		int checkSum = CalcCheckSum();
		AddTagCheckSum
		AddEqual();
		AddValue(checkSum, 3);
		AddSeparator();
	}

	inline void AddTrail() {
		AddCheckSum();
	}

	inline void AddTestRequestId(int testRequestId) {
		AddTagTestReqID
		AddEqual();
		AddValue(testRequestId);
	}

    inline void SetMessageBuffer(char *buffer) {
        this->messageBuffer = buffer;
        this->messageBufferSize = 10000;
        this->currentPos = this->messageBuffer;
    }

    inline void SetRecvBufferSize(int size) { this->messageBufferSize = size; }

	inline void CreateHearthBeatMessage() {
		AddHeader(MsgTypeHearthBeat);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateHearthBeatMessage(int testRequestId) {
		AddHeader(MsgTypeHearthBeat);
		AddTestRequestId(testRequestId);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

    inline void CreateTestRequestMessage() {
        AddHeader(MsgTypeTestRequest);
        UpdateLengthTagValue();
        AddTrail();
        SaveSendMessage();
    }

	inline void CreateTestRequestMessage(int testRequestId) {
		AddHeader(MsgTypeTestRequest);
		AddTestRequestId(testRequestId);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateResendRequestMessage(int start, int end) {
		AddHeader(MsgTypeResendRequest);
		AddTagValue(AddTagBeginSeqNo, start);
		AddTagValue(AddTagEndSeqNo, end);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void AddEncodedTextTag(char *encodedText, int encodedTextLength) { 
		if (encodedTextLength == 0)
			return;
		AddTagValue(AddTagEncodedTextLen, encodedTextLength);
		AddTagData(AddTagEncodedText, encodedText, encodedTextLength);
	}

	inline void CreateRejectMessage(FixRejectInfo *info) {
		AddHeader(MsgTypeReject);
		AddTagValue(AddTagRefSeqNum, info->RefMsgSeqNum);
		if(info->RefTagId != 0)
			AddTagValue(AddTagRefTagID, info->RefTagId);
		if(info->AllowRefMsgType)
            AddTagSymbolValue(AddTagRefMsgType, info->RefMsgType);
	    if(info->SessionRejectReason != FixSessionRejectReason::NoReason)
			AddTagValue(AddTagSessionRejectReason, (int)info->SessionRejectReason);
		if(info->TextLength != 0)
			AddTagString2(AddTagText, info->Text, info->TextLength);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}
	
	inline void CreateSequenceResetMessage(bool allowGapFillFlag, bool gapFill, int newSeqNumber) { 
		AddHeader(MsgTypeSequenceReset);
		if (allowGapFillFlag)
			AddTagValue(AddTagGapFillFlag, (gapFill ? 'Y' : 'N'));
		AddTagValue(AddTagNewSeqNo, newSeqNumber);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateLogoutMessage(char *text, int textLength, char *encodedText, int encodedTextLength) {
		AddHeader(MsgTypeLogout);
		if (text != NULL)
			AddTagString2(AddTagText, text, textLength);
		if(encodedText != NULL)
			AddEncodedTextTag(encodedText, encodedTextLength);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void AddGroupInstrument(FixInstrumentInfo *info) { 
		AddTagString2(AddTagSymbol, info->Symbol, info->SymbolLength);
		if (info->AllowProduct)
			AddTagValue(AddTagProduct, info->Product);
		if (info->AllowCFICode)
			AddTagString2(AddTagCFICode, info->CFICode, FixCFICodeLength);
		if (info->AllowSecurityType)
			AddTagString2(AddTagSecurityType, info->SecurityType, info->SecurityTypeLength);
	}

	inline void AddFloatValue(double value) {
		this->currentPos += this->doubleConverter->ToString(value, this->currentPos);
	}
	inline void AddValue(float value) { 
		AddFloatValue(value);
	}

	inline void AddGroupYield(float percentage) {
		AddTagYield
		AddEqual();
		AddFloatValue(percentage);
		AddSeparator();
	}

	inline void AddGroupParties(FixPartyListInfo *info) { 
		AddTagNoPartyIDs
		AddEqual();
		AddValue(info->Count);
		for (int i = 0; i < info->Count; i++) { 
			AddSeparator();
			AddTagPartyID
			AddEqual(); 
			AddArray(info->Parties[i].ID, info->Parties[i].IDLength);
			AddSeparator();
			AddTagPartyIDSource
			AddEqual();
			AddValue(info->Parties[i].IDSource);
			AddSeparator();
			AddTagPartyRole
			AddEqual();
			AddValue(info->Parties[i].Role);
		}
		AddSeparator();
	}

	inline void AddGroupCommisionData(FixCommisionData *data) { 
		AddTagValue(AddTagCommission, data->Commision);
		AddTagString2(AddTagCommType, data->Type, data->TypeLength);
	}

	inline void AddGroupOrderQty(FixOrderQtyData *data) {
		AddGroupOrderQty(data->Qty, data->CashQty);
	}

	inline void AddGroupOrderQty(float qty, float cashQty) {
		AddTagValue(AddTagOrderQty, qty);
		AddTagValue(AddTagCashOrderQty, cashQty);
	}

	inline void AddGroupTrdRegTimestamp(int count, SYSTEMTIME *st, int *type) { 
		AddTagNoTrdRegTimestamps
		AddEqual();
		AddValue(count);
		for (int i = 0; i < count; i++) {
			AddSeparator();
			AddTagTrdRegTimestamp
			AddEqual();
			AddFullDateTimeValue(&st[i]);
			AddSeparator();
			AddTagTrdRegTimestampType
			AddEqual();
			AddValue(type[i]);
		}
		AddSeparator();
	}

	inline void AddGroupFinancingDetails(SYSTEMTIME *start, SYSTEMTIME *end, int deliveryType) { 
		AddTagStartDate
		AddEqual();
		AddDateValue(start);
		AddSeparator();
		AddTagEndDate
		AddEqual();
		AddDateValue(end);
		AddSeparator();
		AddTagDeliveryType
		AddEqual();
		AddValue(deliveryType);
		AddSeparator();
	}

	inline void AddGroupUnderlyingInstrument(UnderlyingSymbolInfo *info) {
		if (info->SymbolLength != 0) {
			AddTagUnderlyingSymbol
			AddEqual();
			AddArray(info->Symbol, info->SymbolLength);
			AddSeparator();
		}
		if (info->SymbolSfxLength != 0) {
			AddTagUnderlyingSymbolSfx
			AddEqual();
			AddArray(info->SymbolSfx, info->SymbolSfxLength);
			AddSeparator();
		}
		if (info->SecurityIdLength != 0) {
			AddTagUnderlyingSecurityID
			AddEqual();
			AddArray(info->SecurityId, info->SecurityIdLength);
			AddSeparator();
		}
		if (info->SecurityIdSourceLength != 0) {
			AddTagString2(AddTagUnderlyingSecurityIDSource, info->SecurityIdSource, info->SecurityIdSourceLength);
		}
		if (info->NoSecurityAltId != 0) {
			AddTagValue(AddTagNoUnderlyingSecurityAltID, info->NoSecurityAltId);
			for (int i = 0; i < info->NoSecurityAltId; i++) {
				if (info->SecurityAltIdLength[i] != 0)
					AddTagString2(AddTagUnderlyingSecurityAltID, info->SecurityAltId[i], info->SecurityAltIdLength[i]);
				if (info->SecurityAltIdSourceLength[i] != 0)
					AddTagString2(AddTagUnderlyingSecurityAltIDSource, info->SecurityAltIdSource[i], info->SecurityAltIdSourceLength[i]);
			}
		}
		if (info->AllowProduct) { 
			AddTagValue(AddTagUnderlyingProduct, info->Product);
		}
		if (info->CfiCodeLength != 0) { 
			AddTagString2(AddTagUnderlyingCFICode, info->CfiCode, info->CfiCodeLength);
		}
		if (info->SecurityTypeLength != 0) {
			AddTagString2(AddTagUnderlyingSecurityType, info->SecurityType, info->SecurityTypeLength);
		}
		if (info->SecuritySubTypeLength != 0) {
			AddTagString2(AddTagUnderlyingSecuritySubType, info->SecuritySubType, info->SecuritySubTypeLength);
		}
		if (info->AllowMonthYear) { 
			AddTagString2(AddTagUnderlyingMaturityMonthYear, info->MonthYearString, 8);
		}
		if (info->AllowMaturityDate) {
			AddTagString2(AddTagUnderlyingMaturityDate, info->MaturityDateString, 8);
		}
		if (info->AllowCouponPaymentDate) {
			AddTagString2(AddTagUnderlyingCouponPaymentDate, info->CouponPaymentDateString, 8);
		}
		if (info->AllowIssueDate) { 
			AddTagString2(AddTagUnderlyingIssueDate, info->IssueDateString, 8);
		}
		if (info->AllowRepoCollateralSecurityType) { 
			AddTagValue(AddTagUnderlyingRepoCollateralSecurityType, info->RepoCollateralSecurityType);
		}
		if (info->AllowRepurchaseTerm) { 
			AddTagValue(AddTagUnderlyingRepurchaseTerm, info->RepurchaseTerm);
		}
		if (info->AllowRepurchaseRate) {
			AddTagValue(AddTagUnderlyingRepurchaseRate, info->RepurchaseRate);
		}
		if (info->AllowFactor) {
			AddTagValue(AddTagUnderlyingFactor, info->Factor);
		}
		if (info->CreditRatingLength != 0) { 
			AddTagString2(AddTagUnderlyingCreditRating, info->CreditRating, info->CreditRatingLength);
		}
		if (info->InstrRegistryLength != 0) {
			AddTagString2(AddTagUnderlyingInstrRegistry, info->InstrRegistry, info->InstrRegistryLength);
		}
		if (info->AllowCountry) {
			AddTagString2(AddTagUnderlyingCountryOfIssue, info->Country, 2);
		}
		if (info->StateOrProvinceOfIssueLength != 0) {
			AddTagString2(AddTagUnderlyingStateOrProvinceOfIssue, info->StateOrProvinceOfIssue, info->StateOrProvinceOfIssueLength);
		}
		if (info->LocaleOfIssueLength != 0) { 
			AddTagString2(AddTagUnderlyingLocaleOfIssue, info->LocaleOfIssue, info->LocaleOfIssueLength);
		}
		if (info->AllowRedemptionDate) { 
			AddTagString2(AddTagUnderlyingRedemptionDate, info->RedemptionDate, 8);
		}
		if (info->AllowStrikePrice) {
			AddTagValue(AddTagUnderlyingStrikePrice, info->StrikePrice);
		}
		if (info->AllowStrikeCurrency) {
			AddTagString2(AddTagUnderlyingStrikeCurrency, info->StrikeCurrency, 3);
		}
		if (info->AllowOptAttribute) { 
			AddTagValue(AddTagUnderlyingOptAttribute, info->OptAttribute);
		}
		if (info->AllowContractMultiplier) {
			AddTagValue(AddTagUnderlyingContractMultiplier, info->ContractMultiplier);
		}
		if (info->AllowCouponRate) { 
			AddTagValue(AddTagUnderlyingCouponRate, info->CouponRate);
		}
		if (info->SecurityExchangeLength != 0) {
			AddTagString2(AddTagUnderlyingSecurityExchange, info->SecurityExchange, info->SecurityExchangeLength);
		}
		if (info->IssuerLength != 0) { 
			AddTagString2(AddTagUnderlyingIssuer, info->Issuer, info->IssuerLength);
		}
		if (info->EncodedIssuerLength != 0) {
			AddTagValue(AddTagEncodedUnderlyingIssuerLen, info->EncodedIssuerLength);
			AddTagString2(AddTagEncodedUnderlyingIssuer, info->EncodedIssuer, info->EncodedIssuerLength);
		}
		if (info->SecurityDescriptionLength != 0) { 
			AddTagString2(AddTagUnderlyingSecurityDesc, info->SecurityDescription, info->SecurityDescriptionLength);
		}
		if (info->EncodedSecurityDescriptionLength != 0) { 
			AddTagValue(AddTagEncodedUnderlyingSecurityDescLen, info->EncodedSecurityDescriptionLength);
			AddTagString2(AddTagEncodedUnderlyingSecurityDesc, info->EncodedSecurityDescription, info->EncodedSecurityDescriptionLength);
		}
		if (info->CPProgrammLength != 0) { 
			AddTagString2(AddTagUnderlyingCPProgram, info->CPProgramm, info->CPProgrammLength);
		}
		if (info->CPRegTypeLength != 0) {
			AddTagString2(AddTagUnderlyingCPRegType, info->CPRegType, info->CPRegTypeLength);
		}
		if (info->AllowCurrency) { 
			AddTagString2(AddTagUnderlyingCurrency, info->Currency, 3);
		}
		if (info->AllowQty) {
			AddTagValue(AddTagUnderlyingQty, info->Qty);
		}
		if (info->AllowPx) {
			AddTagValue(AddTagUnderlyingPx, info->Px);
		}
		if (info->AllowDirtyPrice) {
			AddTagValue(AddTagUnderlyingDirtyPrice, info->DirtyPrice);
		}
		if (info->AllowEndPrice) {
			AddTagValue(AddTagUnderlyingEndPrice, info->EndPrice);
		}
		if (info->AllowStartValue) {
			AddTagValue(AddTagUnderlyingStartValue, info->StartValue);
		}
		if (info->AllowCurrentValue) {
			AddTagValue(AddTagUnderlyingCurrentValue, info->CurrentValue);
		}
		if (info->AllowEndValue) {
			AddTagValue(AddTagUnderlyingEndValue, info->EndValue);
		}
	}

	inline void AddGroupUnderlyingStipulations(int count, UnderlyingStipulation *list) { 
		AddTagNoUnderlyingStips
		AddEqual();
		AddValue(count);
		AddSeparator();
		for (int i = 0; i < count; i++) {
			AddSeparator();
			AddTagUnderlyingStipType
			AddEqual();
			AddArray(list->StipType, list->StipTypeLength);
			AddSeparator();
			AddTagUnderlyingStipValue
			AddEqual();
			AddArray(list->StipValue, list->StipValueLength);
			list++;
		}
		AddSeparator();
	}
	
	inline void AddGroupLogon(FixLogonInfo *info) {
		AddTagEncryptMethod
		AddEqual();
		AddValue(info->EncryptionType);	// must be zero not supported by MOEX
		AddSeparator();
		
		AddTagHeartBtInt
		AddEqual();
		AddValue(info->HearthBtInt);
		AddSeparator();
		
		AddTagResetSeqNumFlag
		AddEqual();
		AddValue(info->ShouldResetSeqNum);
		AddSeparator();

		AddTagPassword
		AddEqual();
		AddArray(info->Password, info->PassLength);
		AddSeparator();

		if (info->NewPassLength > 0) {
			AddTagNewPassword
			AddEqual();
			AddArray(info->NewPassword, info->NewPassLength);
			AddSeparator();
		}

		if (info->AllowSessionStatus) {
			AddTagSessionStatus
			AddEqual();
			AddValue((int)info->SessionStatus);
			AddSeparator();
		}

		if (info->CancelOnDisconnect) {
			AddTagCancelOnDisconnect
			AddEqual();
			AddSymbol('A');
			AddSeparator();
		}

		if (info->LanguageId != 0) {
			AddTagLanguageID
			AddEqual();
			AddSymbol(info->LanguageId);
			AddSeparator();
		}
	}

	inline void AddFastGroupLogon(FixLogonInfo *info) {
		AddTagEncryptMethod
		AddEqual();
		AddValue(info->EncryptionType);	// must be zero not supported by MOEX
		AddSeparator();

		AddTagHeartBtInt
		AddEqual();
		AddValue(info->HearthBtInt);
		AddSeparator();

		AddTagResetSeqNumFlag
		AddEqual();
		AddValue(info->ShouldResetSeqNum);
		AddSeparator();

		AddTagUsername
		AddEqual();
		AddArray(info->UserName, info->UserNameLength);
		AddSeparator();

		AddTagPassword
		AddEqual();
		AddArray(info->Password, info->PassLength);
		AddSeparator();

		if (info->NewPassLength > 0) {
			AddTagNewPassword
			AddEqual();
			AddArray(info->NewPassword, info->NewPassLength);
			AddSeparator();
		}

		if (info->AllowSessionStatus) {
			AddTagSessionStatus
			AddEqual();
			AddValue((int)info->SessionStatus);
			AddSeparator();
		}

		if (info->CancelOnDisconnect) {
			AddTagCancelOnDisconnect
			AddEqual();
			AddSymbol('A');
			AddSeparator();
		}

		if (info->LanguageId != 0) {
			AddTagLanguageID
			AddEqual();
			AddSymbol(info->LanguageId);
			AddSeparator();
		}
	}

    inline int SendMsgSeqNo() { return this->m_sendMsgSeqNo; }
	inline int RecvMsgSeqNo() { return this->m_recvMsgSeqNo; }

	inline void CreateLogonMessage(FixLogonInfo *logon) {
        this->m_sendMsgSeqNo = logon->MsgStartSeqNo;
		this->SetSenderComputerId(logon->SenderCompID);
		AddHeader(MsgTypeLogon);
		AddGroupLogon(logon);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateFastLogonMessage(FixLogonInfo *logon) {
		this->m_sendMsgSeqNo = logon->MsgStartSeqNo;
		AddHeader(MsgTypeLogon);
		AddFastGroupLogon(logon);
		UpdateLengthTagValue();
		AddTrail();
		SaveSendMessage();
	}

	inline void CreateLogoutMessage(const char *text) {
		CreateLogoutMessage(text, strlen(text));
	}
	inline void CreateLogoutMessage(const char *text, int textLength) {
		AddHeader(MsgTypeLogout);
		if (text != NULL) {
			AddTagText
			AddEqual();
			AddArray(text, textLength);
			AddSeparator();
		}
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateOrderStatusRequestMessage(FixOrderStatusRequestInfo *info) {
		AddHeader(MsgTypeOrderStatusRequest);
		AddTagString2(AddTagOrderID, info->OrderId, info->OrderIdLength);
		AddTagString2(AddTagClOrdID, info->CiOrdId, info->CiOrdIdLength);
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateNewOrderMessage(FixNewOrderInfo *info) {
		AddHeader(MsgTypeOrderSingle);
		
		AddTagString2(AddTagClOrdID, info->ClOrdID, info->ClOrdIDLength);
		
		AddGroupParties(&(info->Parties));
		
		AddTagString2(AddTagAccount, info->Account, info->AccountLength);
		
		if (info->AllowMaxFloor)
			AddTagValue(AddTagMaxFloor, info->MaxFloor);
		
		if (info->SecClOrdIDLength > 0)
			AddTagString2(AddTagSecondaryClOrdID, info->SecClOrdID, info->SecClOrdIDLength);
		
		AddTagValue(AddTagNoTradingSessions, 1);
		AddTagString2(AddTagTradingSessionID, info->TradingSessionID, info->TradingSessionIDLength);

		AddGroupInstrument(&(info->Instrument));
		
		AddTagValue(AddTagSide, info->Side);
		
		AddTagString2(AddTagTransactTime, info->TransactTimeString, UTCTimeStampLength);
		
		AddGroupOrderQty(&(info->OrderQtyData));

		AddTagValue(AddTagOrdType, info->OrderType);

		if (info->AllowPriceType)
			AddTagValue(AddTagPriceType, info->PriceType);

		if (info->AllowPrice)
			AddTagValue(AddTagPrice, info->Price);

		if (info->AllowTradeThruTime)
			AddTagValue(AddTagTradeThruTime, info->TradeThruTime);

		if (info->AllowTimeInForce)
			AddTagValue(AddTagTimeInForce, info->TimeInForce);

		if (info->AllowEffectiveTime)
			AddTagString2(AddTagEffectiveTime, info->EffectiveTimeString, UTCTimeStampLength);

		if (info->AllowOrderCapacity)
			AddTagValue(AddTagOrderCapacity, info->OrderCapacity);

		if (info->AllowOrderRestrictions)
			AddTagString2(AddTagOrderRestrictions, info->OrderRestrictions, info->OrderRestrictionsLength);

		if (info->AllowMaxPiceLevels)
			AddTagValue(AddTagMaxPriceLevels, info->MaxPriceLevels);

		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateOrderCancelRequest(FixOrderCancelRequestInfo *info) { 
		AddHeader(MsgTypeOrderCancelRequest);
		
		if (info->OrigClOrdIDLength > 0)
			AddTagString2(AddTagOrigClOrdID, info->OrigClOrdID, info->OrigClOrdIDLength);
		if (info->OrdIDLength > 0)
			AddTagString2(AddTagOrderID, info->OrdID, info->OrdIDLength);
		
		AddTagString2(AddTagClOrdID, info->ClOrdID, info->ClOrdIDLength);

		AddTagValue(AddTagSide, info->Side);

		AddTagString2(AddTagTransactTime, info->TransactTimeString, UTCTimeStampLength);

		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateOrderCancelReplaceRequest(FixOrderCancelRequestInfo *cinfo, FixNewOrderInfo *info) {
		AddHeader(MsgTypeOrderCancelReplaceRequest);

		AddTagString2(AddTagClOrdID, cinfo->ClOrdID, cinfo->ClOrdIDLength);

		if (cinfo->OrigClOrdIDLength > 0)
			AddTagString2(AddTagOrigClOrdID, cinfo->OrigClOrdID, cinfo->OrigClOrdIDLength);

		if (cinfo->OrdIDLength > 0)
			AddTagString2(AddTagOrderID, cinfo->OrdID, cinfo->OrdIDLength);

		AddTagString2(AddTagAccount, info->Account, info->AccountLength);

		if (info->Parties.Count > 0)
			AddGroupParties(&(info->Parties));

		AddGroupInstrument(&(info->Instrument));

		if (info->AllowPrice)
			AddTagValue(AddTagPrice, info->Price);

		AddTagValue(AddTagOrderQty, info->OrderQtyData.Qty);

		if (info->SecClOrdIDLength > 0)
			AddTagString2(AddTagSecondaryClOrdID, info->SecClOrdID, info->SecClOrdIDLength);

		if (info->AllowCancelOrigOnReject)
			AddTagValue(AddTagCancelOrigOnReject, info->CancelOrigOnReject ? 'Y' : 'N');

		AddTagValue(AddTagNoTradingSessions, 1);
		AddTagString2(AddTagTradingSessionID, info->TradingSessionID, info->TradingSessionIDLength);
		AddTagValue(AddTagOrdType, info->OrderType);
		AddTagValue(AddTagSide, info->Side);
		AddTagString2(AddTagTransactTime, info->TransactTimeString, UTCTimeStampLength);

		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateSecurityDefinitionRequestMessage(char *securityReqId, int securityReqIdLength, FixSecurityRequestType requestType) {
		AddHeader(MsgTypeSecurityDefinitionRequest);

		AddTagString2(AddTagSecurityReqID, securityReqId, securityReqIdLength);
		AddTagValue(AddTagSecurityRequestType, (int)requestType);
		
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateSecurityListRequestMessage(char *securityReqId, int securityReqIdLength, FixSecurityListRequestType requestType) {
		AddHeader(MsgTypeSecurityListRequest);

		AddTagString2(AddTagSecurityReqID, securityReqId, securityReqIdLength);
		AddTagValue(AddTagSecurityListRequestType, (int)requestType);
		
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void AddOrderMassCancelRequest(FixOrderMassCancelRequestInfo *info) {
		AddHeader(MsgTypeOrderMassCancelRequest);
		
		AddTagString2(AddTagClOrdID, info->ClOrdID, info->ClOrdIDLength);

		if (info->SecClOrdIDLength > 0)
			AddTagString2(AddTagSecondaryClOrdID, info->SecClOrdID, info->SecClOrdIDLength);

		AddTagValue(AddTagMassCancelRequestType, info->MassCancelRequestType);
		
		if (info->MassCancelRequestType == MassCancelRequestTypeByInstrument) {
			AddTagString2(AddTagTradingSessionID, info->TradingSessionID, info->TradingSessionIDLength);
			AddGroupInstrument(&(info->Instrument));
		}

		if (info->AllowSide)
			AddTagValue(AddTagSide, info->Side);

		AddTagString2(AddTagTransactTime, info->TransactTimeString, UTCTimeStampLength);

		if (info->AccountLength > 0)
			AddTagString2(AddTagAccount, info->Account, info->AccountLength);

		if (info->AllowParties)
			AddGroupParties(&(info->Parties));
		
		UpdateLengthTagValue();
		AddTrail();
        SaveSendMessage();
	}

	inline void CreateMarketDataRequest(const char *applFeedId, int applFeedIdLength, int msgStart, int msgEnd) {
		AddHeader(MsgTypeMarketDataRequest);

		AddTagString2(AddTagApplFeedId, applFeedId, applFeedIdLength);
		AddTagValue(AddTagApplBeginSeqNum, msgStart);
		AddTagValue(AddTagApplEndSeqNum, msgEnd);

		UpdateLengthTagValue();
		AddTrail();
		SaveSendMessage();
	}
};

