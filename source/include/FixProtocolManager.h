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

#define AddTagValue(tagName, tagValue) tagName AddEqual(); AddValue(tagValue); AddSeparator();
#define AddTagString(tagName, tagValueString) tagName AddEqual(); AddArray(tagValueString); AddSeparator();
#define AddTagString2(tagName, tagValueString, length) tagName AddEqual(); AddArray(tagValueString, length); AddSeparator();
#define AddTagData(tagName, tagData, tagDataLen) tagName AddEqual(); AddArray(tagData, tagDataLen); AddSeparator();

class FixProtocolManager {

	char                senderComputerId[100];
	char                targetComputerId[100];
	int                 senderComputerIdLength;
	int                 targetComputerIdLength;

	SYSTEMTIME		    *currentTime;

    int                     receivedMessageLength;
	char                    *messageBuffer;
	int                     messageBufferSize;

    const int               m_maxRecvMessageCount = 128;
    int                     m_recvMessageCount;
    FixProtocolMessage      *m_currMsg;
    FixProtocolMessage      *m_recvMessage[128];

    char                *currentPos;
	int                 m_sendMsgSeqNumber;
    int                 m_recvMsgSeqNumber;
    
	DtoaConverter       *doubleConverter;
	ItoaConverter       *intConverter;

	inline void AddSymbol(char symbol) { *(this->currentPos) = symbol; this->currentPos++; }
	inline void AddEqual() { *(this->currentPos) = '='; this->currentPos++; }
	inline void AddSeparator() { AddSymbol(0x01); }
	inline void AddTag(const char* tag, int length) { AddArray((char*)tag, length); AddSymbol('='); }

public:
	FixProtocolManager();
	~FixProtocolManager();

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
                msgStart = tagStart;
                msgPtr++; msg = *msgPtr;
                msg->Reset();
                msg->Buffer(this->messageBuffer + tagStart);
                this->m_recvMessageCount++;
            }
            if(separatorIndex == this->messageBufferSize - 1) {
                this->m_recvMessageCount++;
                msg->Size(separatorIndex - msgStart + 1);
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
    
    inline void ResetSendMsgSeqNumber() { this->SetSendMsgSeqNumber(1); }
	inline void SetSendMsgSeqNumber(int value) { this->m_sendMsgSeqNumber = value; }
    inline void IncSendMsgSeqNumber() { this->m_sendMsgSeqNumber++; }

    inline void ResetRecvMsgSeqNumber() { this->SetRecvMsgSeqNumber(1); }
    inline void SetRecvMsgSeqNumber(int value) { this->m_recvMsgSeqNumber = value; }
    inline void IncRecvMsgSeqNumber() { this->m_recvMsgSeqNumber++; }

    inline bool ProcessCheckHeader() { return this->Message(0)->ProcessCheckHeader(); }
    inline FixHeaderInfo* Header() { return this->Message(0)->Header(); }
    inline bool CheckDetectCorrectMsgSeqNumber() {
		return this->Message(0)->CheckDetectCorrectMsgSeqNumber(&(this->m_sendMsgSeqNumber));
	}

	inline void AddArray(char *string, int length) {
		memcpy(this->currentPos, string, length);
		this->currentPos += length;
	}
	inline void AddArray(const char *string, int length) {
		memcpy(this->currentPos, string, length);
		this->currentPos += length;
	}
	inline void AddArray(char *string) {
		while (*string != '\0') { 
			*(this->currentPos) = *string;
			this->currentPos++;
			string++;
		}
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
		AddArray((char*)FixProtocolVersion, 7);
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

	inline void SetSenderComputerId(char *senderComputerId) {
		strcpy(this->senderComputerId, senderComputerId);
		this->senderComputerIdLength = strlen(senderComputerId);
	}

	inline void SetTargetComputerId(char *targetComputerId) {
		strcpy(this->targetComputerId, targetComputerId);
		this->targetComputerIdLength = strlen(targetComputerId);
	}

	inline void UpdateLengthTagValue() {
		const int HeaderTagLength = 10; // 8=FIX.4.4|
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
		AddMessageSeqNumber(this->m_sendMsgSeqNumber);
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

	inline void SetRecvMessageBuffer(char *buffer, int size) {
        this->messageBuffer = buffer;
        this->messageBufferSize = size;
        this->ProcessSplitRecvMessages();
    }

	inline void CreateHearthBeatMessage() {
		AddHeader(MsgTypeHearthBeat);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
	}

	inline void CreateHearthBeatMessage(int testRequestId) {
		AddHeader(MsgTypeHearthBeat);
		AddTestRequestId(testRequestId);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
	}

    inline void CreateTestRequestMessage() {
        AddHeader(MsgTypeTestRequest);
        UpdateLengthTagValue();
        AddTrail();
        AddStringZero();
    }

	inline void CreateTestRequestMessage(int testRequestId) {
		AddHeader(MsgTypeTestRequest);
		AddTestRequestId(testRequestId);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
	}

	inline void CreateResendRequestMessage(int start, int end) {
		AddHeader(MsgTypeResendRequest);
		AddTagValue(AddTagBeginSeqNo, start);
		AddTagValue(AddTagEndSeqNo, end);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
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
		if(info->RefMsgTypeLength != 0)
			AddTagString2(AddTagRefMsgType, info->RefMsgType, info->RefMsgTypeLength);
	    if(info->SessionRejectReason != FixSessionRejectReason::NoReason)
			AddTagValue(AddTagSessionRejectReason, (int)info->SessionRejectReason);
		if(info->TextLength != 0)
			AddTagString(AddTagText, info->Text);
		AddEncodedTextTag(info->EncodedText, info->EncodedTextLength);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
	}
	
	inline void CreateSequenceResetMessage(bool allowGapFillFlag, bool gapFill, int newSeqNumber) { 
		AddHeader(MsgTypeSequenceReset);
		if (allowGapFillFlag)
			AddTagValue(AddTagGapFillFlag, (gapFill ? 'Y' : 'N'));
		AddTagValue(AddTagNewSeqNo, newSeqNumber);
		UpdateLengthTagValue();
		AddTrail();
	}

	inline void CreateLogoutMessage(char *text, char *encodedText, int encodedTextLength) { 
		AddHeader(MsgTypeLogout);
		if (text != NULL)
			AddTagString(AddTagText, text);
		AddEncodedTextTag(encodedText, encodedTextLength);
		UpdateLengthTagValue();
		AddTrail();
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

    inline int SendMsgSeqNumber() { return this->m_sendMsgSeqNumber; }
    inline int RecvMsgSeqNumber() { return this->m_recvMsgSeqNumber; }

	inline void CreateLogonMessage(FixLogonInfo *logon) {
		this->m_sendMsgSeqNumber = logon->MsgStartSeqNo;
		this->SetSenderComputerId(logon->SenderCompID);
		AddHeader(MsgTypeLogon);
		AddGroupLogon(logon);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
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
		AddStringZero();
	}

	inline void CreateOrderStatusRequestMessage(FixOrderStatusRequestInfo *info) {
		AddHeader(MsgTypeOrderStatusRequest);
		AddTagString2(AddTagOrderID, info->OrderId, info->OrderIdLength);
		AddTagString2(AddTagClOrdID, info->CiOrdId, info->CiOrdIdLength);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
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
		AddStringZero();
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
		AddStringZero();
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
		AddStringZero();
	}

	inline void CreateSecurityDefinitionRequestMessage(char *securityReqId, int securityReqIdLength, FixSecurityRequestType requestType) {
		AddHeader(MsgTypeSecurityDefinitionRequest);

		AddTagString2(AddTagSecurityReqID, securityReqId, securityReqIdLength);
		AddTagValue(AddTagSecurityRequestType, (int)requestType);
		
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
	}

	inline void CreateSecurityListRequestMessage(char *securityReqId, int securityReqIdLength, FixSecurityListRequestType requestType) {
		AddHeader(MsgTypeSecurityListRequest);

		AddTagString2(AddTagSecurityReqID, securityReqId, securityReqIdLength);
		AddTagValue(AddTagSecurityListRequestType, (int)requestType);
		
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
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
		AddStringZero();
	}

};

