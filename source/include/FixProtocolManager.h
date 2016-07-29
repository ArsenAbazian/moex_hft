#pragma once

#include "FixTypes.h"
#include "ItoaConverter.h"
#include "DtoaConverter.h"
#include "UTCTimeConverter.h"
#include "SocketBufferManager.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

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
	FixHeaderInfo		*m_headerInfo;
	FixTagValueInfo	    tagValueList[1024];
	int				    tagValueItemsCount;

	int                 receivedMessageLength;
	char                *messageBuffer;
	int                 messageBufferSize;
	char                *currentPos;
	int                 messageSequenceNumber;

	DtoaConverter       *doubleConverter;
	ItoaConverter       *intConverter;

	inline void AddSymbol(char symbol) { *(this->currentPos) = symbol; this->currentPos++; }
	inline void AddEqual() { *(this->currentPos) = '='; this->currentPos++; }
	inline void AddSeparator() { AddSymbol(0x01); }
	inline void AddTag(const char* tag, int length) { AddArray((char*)tag, length); AddSymbol('='); }

#pragma region Tags
	const char* FixProtocolVersion = "FIX.4.4";
	const int FixProtocolVersionLength = 7;
	const char* FastProtocolVersion = "FIXT.1.1";
	const int FastProtocolVersionLength = 8;
#pragma endregion
	
public:
	FixProtocolManager();
	~FixProtocolManager();

	inline void StartNewMessage() {
		this->currentPos = this->messageBuffer;
		*(this->currentPos) = '\0';
	}

	inline void ResetMessageSequenceNumber() { this->SetMessageSequenceNumber(1); }
	inline void SetMessageSequenceNumber(int value) { this->messageSequenceNumber = value; }
	inline void IncMessageSequenceNumber() { this->messageSequenceNumber++; }

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
		AddMessageSeqNumber(this->messageSequenceNumber);
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
        SetMessageBuffer(buffer, 10000);
    }

	inline void SetMessageBuffer(char *buffer, int size) {
        this->messageBuffer = buffer;
        this->messageBufferSize = size;
        this->currentPos = this->messageBuffer;
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
	
#pragma region Additional MOEX Tags
#define TagStrSessionStatus "1409"
#define TagSessionStatus 1409

#define AddTagSessionStatus *((unsigned int*)this->currentPos) = 0x39303431; this->currentPos += 4;

#define TagStrCancelOnDisconnect "6867"
#define TagCancelOnDisconnect 6867
#define AddTagCancelOnDisconnect *((unsigned int*)this->currentPos) = 0x37363836; this->currentPos += 4;

#define TagStrLanguageID "6936"
#define TagLanguageID 6936
#define AddTagTagLanguageID *((unsigned int*)this->currentPos) = 0x36333936; this->currentPos += 4;

#define TagStrTradeThruTime "5202"
#define TagTradeThruTime 5202
#define AddTagTradeThruTime *((unsigned int*)this->currentPos) = 0x32303235; this->currentPos += 4;

#define	TagStrMaxPriceLevels "1090"
#define TagMaxPriceLevels 1090
#define AddTagMaxPriceLevels *((unsigned int*)this->currentPos) = 0x30393031; this->currentPos += 4;

#define TagStrCancelOrigOnReject "9619"
#define TagCancelOrigOnReject 9619
#define AddTagCancelOrigOnReject *((unsigned int*)this->currentPos) = 0x39313639; this->currentPos += 4;

#pragma endregion

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
			AddTagTagLanguageID
			AddEqual();
			AddSymbol(info->LanguageId);
			AddSeparator();
		}
	}

    inline int MessageSequenceNumber() { return this->messageSequenceNumber; }

	inline void CreateLogonMessage(FixLogonInfo *logon) {
		this->messageSequenceNumber = logon->MsgStartSeqNo;
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
	inline void ResetTagValueList() { this->tagValueItemsCount = 0; }
	inline FixTagValueInfo* TagValueList() { return this->tagValueList; }
	inline int TagValuesCount() { return this->tagValueItemsCount; }
	inline int ReadValue(char *buffer, int *outValue, char stopSymbol) { 
		return this->intConverter->FromStringFast(buffer, outValue, stopSymbol);
	}
	inline void ReadValuePredict234(int *outValue) {
		this->currentPos += ReadValuePredict234(this->currentPos, outValue, FIX_SEPARATOR) + 1;
	}
	inline int ReadValuePredict234(char *buffer, int* outValue, char stopSymbol) {
		if (buffer[2] == stopSymbol) {
			*outValue = this->intConverter->From2SymbolUnsigned(buffer);
			return 2;
		}
		if (buffer[3] == stopSymbol) {
			*outValue = this->intConverter->From3SymbolUnsigned(buffer);
			return 3;
		}
		if (buffer[4] == stopSymbol) {
			*outValue = this->intConverter->From4SymbolUnsigned(buffer);
			return 4;
		}
		return this->intConverter->FromStringFast(buffer, outValue, stopSymbol);
	}
	inline void ReadValuePredict34(int* outValue) {
		this->currentPos += this->ReadValuePredict34(this->currentPos, outValue, FIX_SEPARATOR) + 1;
	}
	inline int ReadValuePredict34(char *buffer, int* outValue, char stopSymbol) { 
		if (buffer[3] == stopSymbol) {
			*outValue = this->intConverter->From3SymbolUnsigned(buffer);
			return 3;
		}
		if (buffer[4] == stopSymbol) {
			*outValue = this->intConverter->From4SymbolUnsigned(buffer);
			return 4;
		}
		return this->intConverter->FromStringFast(buffer, outValue, stopSymbol);
	}
	inline int ReadUTCDateTime(char *buffer, SYSTEMTIME *st, char stopSymbol) { 
		return this->timeConverter->FromString(buffer, st, stopSymbol);
	}
	inline int ReadUTCDate(char *buffer, SYSTEMTIME *st) { 
		return this->timeConverter->FromDateString(buffer, st);
	}
	inline int ReadTag(char *buffer, int *outValue) { 
		if (buffer[3] == '=') { 
			*outValue = this->intConverter->From3SymbolUnsigned(buffer);
			return 4;
		}
		else if (buffer[2] == '=') { 
			*outValue = this->intConverter->From2SymbolUnsigned(buffer);
			return 3;
		}
		else if (buffer[1] == '=') {
			*outValue = *buffer - 0x30;
			return 2;
		}
		else if (buffer[4] == '=') { 
			*outValue = this->intConverter->From4SymbolUnsigned(buffer);
			return 5;
		}
		return this->intConverter->FromStringFast(buffer, outValue, '=') + 1;
	}
	
	inline int Read1SymbolTag(char *buffer) { return *buffer - 0x30; }
	inline int Read2SymbolTag(char *buffer) { return this->intConverter->From2SymbolUnsigned(buffer); }
	inline int Read3SymbolTag(char *buffer) { return this->intConverter->From3SymbolUnsigned(buffer); }
	inline int Read4SymbolTag(char *buffer) { return this->intConverter->From4SymbolUnsigned(buffer); }

	inline bool ReadCheck1SymbolTag(int expectedTag) {
		if (this->Read1SymbolTag(this->currentPos) != expectedTag) {
			return false;
		}
		this->currentPos ++;
		if(*(this->currentPos) != '=') {
			return false;
		}
		this->currentPos++;
		return true;
	}

	inline bool ReadCheck2SymbolTag(int expectedTag) {
		if (this->Read2SymbolTag(this->currentPos) != expectedTag) {
			return false;
		}
		this->currentPos +=2;
		if(*(this->currentPos) != '=') {
			return false;
		}
		this->currentPos++;
		return true;
	}

	inline bool ReadCheckSkip2SymbolTag(int expectedTag, bool *checkFailed) {
		if (this->Read2SymbolTag(this->currentPos) != expectedTag) {
			*checkFailed = false;
			return false;
		}
		this->currentPos +=2;
		if(*(this->currentPos) != '=') {
			*checkFailed = true;
			return false;
		}
		this->currentPos++;
		return true;
	}

	inline bool Read2TagSymbol(int expectedTag, char *value) {
		if(!this->ReadCheck2SymbolTag(expectedTag))
			return false;
		*value = *(this->currentPos);
		this->currentPos++;
		if(*(this->currentPos) != FIX_SEPARATOR)
			return false;
		this->currentPos++;
		return true;
	}

    inline bool FindSymbol(char *str, int maxLength, char symb, int *length) {
        int len = 0;
        unsigned int *pack4 = (unsigned int*)str;
        unsigned int symb1 = symb;
        unsigned int symb2 = symb; symb2 <<= 8;
        unsigned int symb3 = symb2; symb3 <<= 8;
        unsigned int symb4 = symb3; symb4 <<= 8;
        while(len < maxLength) {
            if((*pack4 & 0x000000ff) == symb1) {
                break;
            }
            if((*pack4 & 0x0000ff00) == symb2) {
                len ++;
                break;
            }
            if((*pack4 & 0x00ff0000) == symb3) {
                len +=2;
                break;
            }
            if((*pack4 & 0xff000000) == symb4) {
                len +=3;
                break;
            }
            len += 4;
            pack4++;
        }
        *length = len;
        return len < maxLength;
    }

	inline bool ReadString(int *length) {
		const int MaxStringLength = 1500;
		int len = 0;
		unsigned int *pack4 = (unsigned int*)this->currentPos;
		while(len < MaxStringLength) {
			if((*pack4 & 0x000000ff) == FIX_SEPARATOR) {
				break;
			}
			if((*pack4 & 0x0000ff00) == FIX_SEPARATOR_SECOND_BYTE) {
				len ++;
				break;
			}
			if((*pack4 & 0x00ff0000) == FIX_SEPARATOR_THIRD_BYTE) {
				len +=2;
				break;
			}
			if((*pack4 & 0xff000000) == FIX_SEPARATOR_FORTH_BYTE) {
				len +=3;
				break;
			}
			len += 4;
			pack4++;
		}
		*length = len;
		this->currentPos += len + 1;
		return len < MaxStringLength;
	}

	inline bool Read2SymbolTagString(int expectedTag, char **strPtr, int *length) {
		if(!this->ReadCheck2SymbolTag(expectedTag))
			return false;
		*strPtr = this->currentPos;
		return this->ReadString(length);
	}

	inline bool ReadUtcTimeStamp(char **strPtr) {
		*strPtr = this->currentPos;
		if(this->currentPos[UTCTimeStampLength] != FIX_SEPARATOR)
			return false;
		this->currentPos += UTCTimeStampLength + 1;
		return true;
	}

	inline bool Read2SymbolTagTimeStamp(int expectedTag, char **strPtr) {
		if(!this->ReadCheck2SymbolTag(expectedTag))
			return false;
		return this->ReadUtcTimeStamp(strPtr);
	}

	inline bool Read2TagIntValuePredict234(int expectedTag, int *value) {
		if(!this->ReadCheck2SymbolTag(expectedTag))
			return false;
		ReadValuePredict234(value);
		return true;
	}

	inline bool ReadBooleanSymbol(bool *value) {
		*value = *(this->currentPos) == 'Y';
		this->currentPos++;
		return true;
	}

	inline bool CheckFixHeader() {
        // 8=FIX...
		if(this->currentPos[2 + this->FixProtocolVersionLength] != FIX_SEPARATOR)
			return false;
		this->currentPos += 2 + this->FixProtocolVersionLength + 1;
		/*
		if(!this->ReadCheck1SymbolTag(TagBeginString))
			return false;

		if (*((int*)this->currentPos) != *((int*)this->FixProtocolVersion))
			return false;

		this->currentPos += 4 + 3;
		if (*(this->currentPos) != FIX_SEPARATOR)
			return false;

		this->currentPos++;
		*outLength = 1 + 1 + 7 + 1;
		*/
		return true;
	}

	inline bool ProcessMessageLengthTag() {
		if(!this->ReadCheck1SymbolTag(TagBodyLength))
			return false;

		this->ReadValuePredict34(&this->m_headerInfo->bodyLength);
		return true;
	}

	inline FixHeaderInfo* HeaderInfo() { return this->m_headerInfo; }
	inline bool ProcessCheckHeader() {

		this->m_headerInfo->name = this->currentPos;
		if (!CheckFixHeader())
			return false;

		if (!ProcessMessageLengthTag())
			return false;

		if(!this->Read2TagSymbol(TagMsgType, &(this->m_headerInfo->msgType)))
			return false;

		if(!this->Read2SymbolTagString(TagSenderCompID, &(this->m_headerInfo->senderCompID), &(this->m_headerInfo->senderCompIDLength)))
			return false;

		if(!this->Read2SymbolTagString(TagTargetCompID, &(this->m_headerInfo->targetCompID), &(this->m_headerInfo->targetCompIDLength)))
			return false;

		if(!this->Read2TagIntValuePredict234(TagMsgSeqNum, &(this->m_headerInfo->msgSeqNum)))
			return false;

		bool checkFailed = false;
		if(this->ReadCheckSkip2SymbolTag(TagPossDupFlag, &checkFailed)) {
			this->ReadBooleanSymbol(&(this->m_headerInfo->possDupFlag));
		}
		else if(checkFailed)
			return false;
		if(this->ReadCheckSkip2SymbolTag(TagPossResend, &checkFailed)) {
			this->ReadBooleanSymbol(&(this->m_headerInfo->possResend));
		}
		else if(checkFailed)
			return false;
		if(!this->Read2SymbolTagTimeStamp(TagSendingTime, &(this->m_headerInfo->sendingTime)))
			return false;
		if(this->ReadCheckSkip2SymbolTag(TagOrigSendingTime, &checkFailed) &&
				!this->ReadUtcTimeStamp(&(this->m_headerInfo->origSendingTime))) {
			return false;
		}
		if(checkFailed)
			return false;

		return true;
	}

    inline bool CheckDetectCorrectMsgSeqNumber() {
        bool checkFailed = false;
        if (!this->ReadCheckSkip2SymbolTag(TagText, &checkFailed))
            return false;
        //The incoming message has a sequence number (
        char *msg = this->currentPos;
        int length = 0;
        if (!this->ReadString(&length))
            return false;

        int bIndex = -1;
        if (!this->FindSymbol(msg, length, '(', &bIndex))
            return false;

        msg += bIndex + 1;
        if (!this->FindSymbol(msg, length - bIndex - 1, '(', &bIndex))
            return false;

        msg += bIndex + 1;
        this->ReadValuePredict234(msg, &(this->messageSequenceNumber), ')');
        return true;
    }

	inline bool ProcessCheckLogonMessage() {
		printf("recv = %s", this->messageBuffer);
		return true;
	}

	inline bool CheckProcessHearthBeat(int testReqId) {
		int length = 0;
		this->currentPos = this->messageBuffer;
		if(!ProcessCheckHeader())
			return false;

		int tag = Read3SymbolTag(this->currentPos);
		this->currentPos += 3;

		if (*(this->currentPos) != '=' || tag != TagTestReqID)
			return false;

		int hearthBeat = ReadValuePredict34(this->currentPos, &length, FIX_SEPARATOR);
		this->currentPos ++;

		return true;
	}
};

