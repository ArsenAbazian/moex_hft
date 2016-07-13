#pragma once

#include "FixTypes.h"
#include "ItoaConverter.h"
#include "DtoaConverter.h"
#include "UTCTimeConverter.h"
#include "ProtocolHistoryManager.h"
#include <time.h>
#include <sys/time.h>

#define FIX_SEPARATOR 0x01

#pragma region SessionRejectReason
#define SrrInvalidTagNumber "0" // Invalid tag number
#define SrrRequiredTagMissing "1" // Required tag missing
#define SrrTagNotDefinedForThisMessageType "2" // Tag not defined for this MessageCore type
#define SrrUndefinedTag "3" // Undefined Tag
#define SrrTagSpecifiedWithoutAValue "4" // Tag specified without a value
#define SrrValueIsIncorrectForThisTag "5" // Value is incorrect(out of range) for this tag
#define SrrIncorrectDataFormatForValue "6" // Incorrect data format for value
#define SrrDecryptionProblem "7" // Decryption problem
#define SrrSignatureProblem "8" //Signature <89> problem
#define SrrCompIDProblem "9" //CompID problem
#define SrrSendingTimeProblem "10" //SendingTime <52> accuracy problem
#define SrrInvalidMsgType "11" //Invalid MsgType <35>
#pragma endregion

#pragma region MessageTypes
#define MsgTypeHearthBeat  '0'
#define MsgTypeTestRequest  '1'
#define MsgTypeResendRequest  '2'
#define MsgTypeReject  '3'
#define MsgTypeSequenceReset  '4'
#define MsgTypeLogout  '5'
#define MsgTypeIndicationOfInterest  '6'
#define MsgTypeAdvertisement  '7'
#define MsgTypeExecutionReport  '8'
#define MsgTypeOrderCancelReject  '9'
#define MsgTypeLogon  'A'
#define MsgTypeNews  'B'
#define MsgTypeEmail  'C'
#define MsgTypeOrderSingle  'D'
#define MsgTypeOrderList  'E'
#define MsgTypeOrderCancelRequest  'F'
#define MsgTypeOrderCancelReplaceRequest  'G'
#define MsgTypeOrderStatusRequest  'H'
#define MsgTypeAllocation  'J'
#define MsgTypeListCancelRequest  'K'
#define MsgTypeListExecute  'L'
#define MsgTypeListStatusRequest  'M'
#define MsgTypeListStatus  'N'
#define MsgTypeAllocationACK  'P'
#define MsgTypeDontKnowTrade  'Q'
#define MsgTypeQuoteRequest  'R'
#define MsgTypeQuote  'S'
#define MsgTypeSettlementInstructions  'T'
#define MsgTypeMarketDataRequest  'V'
#define MsgTypeMarketDataSnapshotFullRefresh 'W'
#define MsgTypeMarketDataIncrementalRefresh 'X'
#define MsgTypeMarketDataRequestReject  'Y'
#define MsgTypeQuoteCancel  'Z'
#define MsgTypeQuoteStatusRequest  'a'
#define MsgTypeQuoteAcknowledgement  'b'
#define MsgTypeSecurityDefinitionRequest  'c'
#define MsgTypeSecurityDefinition  'd'
#define MsgTypeSecurityStatusRequest  'e'
#define MsgTypeSecurityStatus  'f'
#define MsgTypeTradingSessionStatusRequest  'g'
#define MsgTypeTradingSessionStatus  'h'
#define MsgTypeMassQuote  'i'
#define MsgTypeBusinessMessageReject  'j'
#define MsgTypeBidRequest  'k'
#define MsgTypeBidResponse  'l'
#define MsgTypeListStrikePrice  'm'
#define MsgTypeOrderMassCancelRequest 'q'
#define MsgTypeSecurityListRequest 'x'
#pragma endregion

#define AddTagValue(tagName, tagValue) tagName(); AddEqual(); AddValue(tagValue); AddSeparator();
#define AddTagString(tagName, tagValueString) tagName(); AddEqual(); AddArray(tagValueString); AddSeparator();
#define AddTagString2(tagName, tagValueString, length) tagName(); AddEqual(); AddArray(tagValueString, length); AddSeparator();
#define AddTagData(tagName, tagData, tagDataLen) tagName(); AddEqual(); AddArray(tagData, tagDataLen); AddSeparator();

class FixProtocolManager {

	char senderComputerId[100];
	char targetComputerId[100];
	int senderComputerIdLength;
	int targetComputerIdLength;

	SYSTEMTIME		*currentTime;
	FixTagValueInfo	tagValueList[1024];
	int				tagValueItemsCount;

	FixDiagnosticCodes processingLog[2048];
	int processingLogLength = 0;
	int receivedMessageLength;
	FixProtocolHistoryManager *historyManager;
	char* messageBuffer;
	int messageLength;
	char* currentPos;
	int messageSequenceNumber;

	DtoaConverter *doubleConverter;
	ItoaConverter *intConverter;

	inline void AddSymbol(char symbol) { *(this->currentPos) = symbol; this->currentPos++; }
	inline void AddEqual() { *(this->currentPos) = '='; this->currentPos++; }
	inline void AddSeparator() { AddSymbol(0x01); }
	inline void AddTag(const char* tag, int length) { AddArray((char*)tag, length); AddSymbol('='); }

	inline void ClearLog() { this->processingLogLength = 0; }
	inline void AddDiagnosticCode(FixDiagnosticCodes code) { this->processingLog[this->processingLogLength] = code; this->processingLogLength++; }
	inline void AddLog(FixDiagnosticCodes operation, FixDiagnosticCodes result) { 
		AddDiagnosticCode(operation);
		AddDiagnosticCode(result);
	}

#pragma region Tags
	const char* FixProtocolVersion = "FIX.4.4";
	const char* FastProtocolVersion = "FIXT.1.1";
	const int FastProtocolVersionLength = 8;

	const int TagAccount = 1;
	const int TagAdvId = 2;
	const int TagAdvRefID = 3;
	const int TagAdvSide = 4;
	const int TagAdvTransType = 5;
	const int TagAvgPx = 6;
	const int TagBeginSeqNo = 7;
	const int TagBeginString = 8;
	const int TagBodyLength = 9;
	const int TagCheckSum = 10;
	const int TagClOrdID = 11;
	const int TagCommission = 12;
	const int TagCommType = 13;
	const int TagCumQty = 14;
	const int TagCurrency = 15;
	const int TagEndSeqNo = 16;
	const int TagExecID = 17;
	const int TagExecInst = 18;
	const int TagExecRefID = 19;
	const int TagExecTransType = 20;
	const int TagHandlInst = 21;
	const int TagSecurityIDSource = 22;
	const int TagIOIID = 23;
	const int TagIOIOthSvc = 24;
	const int TagIOIQltyInd = 25;
	const int TagIOIRefID = 26;
	const int TagIOIQty = 27;
	const int TagIOITransType = 28;
	const int TagLastCapacity = 29;
	const int TagLastMkt = 30;
	const int TagLastPx = 31;
	const int TagLastQty = 32;
	const int TagNoLinesOfText = 33;
	const int TagMsgSeqNum = 34;
	const int TagMsgType = 35;
	const int TagNewSeqNo = 36;
	const int TagOrderID = 37;
	const int TagOrderQty = 38;
	const int TagOrdStatus = 39;
	const int TagOrdType = 40;
	const int TagOrigClOrdID = 41;
	const int TagOrigTime = 42;
	const int TagPossDupFlag = 43;
	const int TagPrice = 44;
	const int TagRefSeqNum = 45;
	const int TagRelatdSym = 46;
	const int TagRule80A = 47;
	const int TagSecurityID = 48;
	const int TagSenderCompID = 49;
	const int TagSenderSubID = 50;
	const int TagSendingDate = 51;
	const int TagSendingTime = 52;
	const int TagQuantity = 53;
	const int TagSide = 54;
	const int TagSymbol = 55;
	const int TagTargetCompID = 56;
	const int TagTargetSubID = 57;
	const int TagText = 58;
	const int TagTimeInForce = 59;
	const int TagTransactTime = 60;
	const int TagUrgency = 61;
	const int TagValidUntilTime = 62;
	const int TagSettlType = 63;
	const int TagSettlDate = 64;
	const int TagSymbolSfx = 65;
	const int TagListID = 66;
	const int TagListSeqNo = 67;
	const int TagTotNoOrders = 68;
	const int TagListExecInst = 69;
	const int TagAllocID = 70;
	const int TagAllocTransType = 71;
	const int TagRefAllocID = 72;
	const int TagNoOrders = 73;
	const int TagAvgPxPrecision = 74;
	const int TagTradeDate = 75;
	const int TagExecBroker = 76;
	const int TagPositionEffect = 77;
	const int TagNoAllocs = 78;
	const int TagAllocAccount = 79;
	const int TagAllocQty = 80;
	const int TagProcessCode = 81;
	const int TagNoRpts = 82;
	const int TagRptSeq = 83;
	const int TagCxlQty = 84;
	const int TagNoDlvyInst = 85;
	const int TagDlvyInst = 86;
	const int TagAllocStatus = 87;
	const int TagAllocRejCode = 88;
	const int TagSignature = 89;
	const int TagSecureDataLen = 90;
	const int TagSecureData = 91;
	const int TagBrokerOfCredit = 92;
	const int TagSignatureLength = 93;
	const int TagEmailType = 94;
	const int TagRawDataLength = 95;
	const int TagRawData = 96;
	const int TagPossResend = 97;
	const int TagEncryptMethod = 98;
	const int TagStopPx = 99;
	const int TagExDestination = 100;
	const int TagCxlRejReason = 102;
	const int TagOrdRejReason = 103;
	const int TagIOIQualifier = 104;
	const int TagWaveNo = 105;
	const int TagIssuer = 106;
	const int TagSecurityDesc = 107;
	const int TagHeartBtInt = 108;
	const int TagClientID = 109;
	const int TagMinQty = 110;
	const int TagMaxFloor = 111;
	const int TagTestReqID = 112;
	const int TagReportToExch = 113;
	const int TagLocateReqd = 114;
	const int TagOnBehalfOfCompID = 115;
	const int TagOnBehalfOfSubID = 116;
	const int TagQuoteID = 117;
	const int TagNetMoney = 118;
	const int TagSettlCurrAmt = 119;
	const int TagSettlCurrency = 120;
	const int TagForexReq = 121;
	const int TagOrigSendingTime = 122;
	const int TagGapFillFlag = 123;
	const int TagNoExecs = 124;
	const int TagCxlType = 125;
	const int TagExpireTime = 126;
	const int TagDKReason = 127;
	const int TagDeliverToCompID = 128;
	const int TagDeliverToSubID = 129;
	const int TagIOINaturalFlag = 130;
	const int TagQuoteReqID = 131;
	const int TagBidPx = 132;
	const int TagOfferPx = 133;
	const int TagBidSize = 134;
	const int TagOfferSize = 135;
	const int TagNoMiscFees = 136;
	const int TagMiscFeeAmt = 137;
	const int TagMiscFeeCurr = 138;
	const int TagMiscFeeType = 139;
	const int TagPrevClosePx = 140;
	const int TagResetSeqNumFlag = 141;
	const int TagSenderLocationID = 142;
	const int TagTargetLocationID = 143;
	const int TagOnBehalfOfLocationID = 144;
	const int TagDeliverToLocationID = 145;
	const int TagNoRelatedSym = 146;
	const int TagSubject = 147;
	const int TagHeadline = 148;
	const int TagURLLink = 149;
	const int TagExecType = 150;
	const int TagLeavesQty = 151;
	const int TagCashOrderQty = 152;
	const int TagAllocAvgPx = 153;
	const int TagAllocNetMoney = 154;
	const int TagSettlCurrFxRate = 155;
	const int TagSettlCurrFxRateCalc = 156;
	const int TagNumDaysInterest = 157;
	const int TagAccruedInterestRate = 158;
	const int TagAccruedInterestAmt = 159;
	const int TagSettlInstMode = 160;
	const int TagAllocText = 161;
	const int TagSettlInstID = 162;
	const int TagSettlInstTransType = 163;
	const int TagEmailThreadID = 164;
	const int TagSettlInstSource = 165;
	const int TagSettlLocation = 166;
	const int TagSecurityType = 167;
	const int TagEffectiveTime = 168;
	const int TagStandInstDbType = 169;
	const int TagStandInstDbName = 170;
	const int TagStandInstDbID = 171;
	const int TagSettlDeliveryType = 172;
	const int TagSettlDepositoryCode = 173;
	const int TagSettlBrkrCode = 174;
	const int TagSettlInstCode = 175;
	const int TagSecuritySettlAgentName = 176;
	const int TagSecuritySettlAgentCode = 177;
	const int TagSecuritySettlAgentAcctNum = 178;
	const int TagSecuritySettlAgentAcctName = 179;
	const int TagSecuritySettlAgentContactName = 180;
	const int TagSecuritySettlAgentContactPhone = 181;
	const int TagCashSettlAgentName = 182;
	const int TagCashSettlAgentCode = 183;
	const int TagCashSettlAgentAcctNum = 184;
	const int TagCashSettlAgentAcctName = 185;
	const int TagCashSettlAgentContactName = 186;
	const int TagCashSettlAgentContactPhone = 187;
	const int TagBidSpotRate = 188;
	const int TagBidForwardPoints = 189;
	const int TagOfferSpotRate = 190;
	const int TagOfferForwardPoints = 191;
	const int TagOrderQty2 = 192;
	const int TagSettlDate2 = 193;
	const int TagLastSpotRate = 194;
	const int TagLastForwardPoints = 195;
	const int TagAllocLinkID = 196;
	const int TagAllocLinkType = 197;
	const int TagSecondaryOrderID = 198;
	const int TagNoIOIQualifiers = 199;
	const int TagMaturityMonthYear = 200;
	const int TagPutOrCall = 201;
	const int TagStrikePrice = 202;
	const int TagCoveredOrUncovered = 203;
	const int TagCustomerOrFirm = 204;
	const int TagMaturityDay = 205;
	const int TagOptAttribute = 206;
	const int TagSecurityExchange = 207;
	const int TagNotifyBrokerOfCredit = 208;
	const int TagAllocHandlInst = 209;
	const int TagMaxShow = 210;
	const int TagPegOffsetValue = 211;
	const int TagXmlDataLen = 212;
	const int TagXmlData = 213;
	const int TagSettlInstRefID = 214;
	const int TagNoRoutingIDs = 215;
	const int TagRoutingType = 216;
	const int TagRoutingID = 217;
	const int TagSpread = 218;
	const int TagBenchmark = 219;
	const int TagBenchmarkCurveCurrency = 220;
	const int TagBenchmarkCurveName = 221;
	const int TagBenchmarkCurvePoint = 222;
	const int TagCouponRate = 223;
	const int TagCouponPaymentDate = 224;
	const int TagIssueDate = 225;
	const int TagRepurchaseTerm = 226;
	const int TagRepurchaseRate = 227;
	const int TagFactor = 228;
	const int TagTradeOriginationDate = 229;
	const int TagExDate = 230;
	const int TagContractMultiplier = 231;
	const int TagNoStipulations = 232;
	const int TagStipulationType = 233;
	const int TagStipulationValue = 234;
	const int TagYieldType = 235;
	const int TagYield = 236;
	const int TagTotalTakedown = 237;
	const int TagConcession = 238;
	const int TagRepoCollateralSecurityType = 239;
	const int TagRedemptionDate = 240;
	const int TagUnderlyingCouponPaymentDate = 241;
	const int TagUnderlyingIssueDate = 242;
	const int TagUnderlyingRepoCollateralSecurityType = 243;
	const int TagUnderlyingRepurchaseTerm = 244;
	const int TagUnderlyingRepurchaseRate = 245;
	const int TagUnderlyingFactor = 246;
	const int TagUnderlyingRedemptionDate = 247;
	const int TagLegCouponPaymentDate = 248;
	const int TagLegIssueDate = 249;
	const int TagLegRepoCollateralSecurityType = 250;
	const int TagLegRepurchaseTerm = 251;
	const int TagLegRepurchaseRate = 252;
	const int TagLegFactor = 253;
	const int TagLegRedemptionDate = 254;
	const int TagCreditRating = 255;
	const int TagUnderlyingCreditRating = 256;
	const int TagLegCreditRating = 257;
	const int TagTradedFlatSwitch = 258;
	const int TagBasisFeatureDate = 259;
	const int TagBasisFeaturePrice = 260;
	const int TagMDReqID = 262;
	const int TagSubscriptionRequestType = 263;
	const int TagMarketDepth = 264;
	const int TagMDUpdateType = 265;
	const int TagAggregatedBook = 266;
	const int TagNoMDEntryTypes = 267;
	const int TagNoMDEntries = 268;
	const int TagMDEntryType = 269;
	const int TagMDEntryPx = 270;
	const int TagMDEntrySize = 271;
	const int TagMDEntryDate = 272;
	const int TagMDEntryTime = 273;
	const int TagTickDirection = 274;
	const int TagMDMkt = 275;
	const int TagQuoteCondition = 276;
	const int TagTradeCondition = 277;
	const int TagMDEntryID = 278;
	const int TagMDUpdateAction = 279;
	const int TagMDEntryRefID = 280;
	const int TagMDReqRejReason = 281;
	const int TagMDEntryOriginator = 282;
	const int TagLocationID = 283;
	const int TagDeskID = 284;
	const int TagDeleteReason = 285;
	const int TagOpenCloseSettlFlag = 286;
	const int TagSellerDays = 287;
	const int TagMDEntryBuyer = 288;
	const int TagMDEntrySeller = 289;
	const int TagMDEntryPositionNo = 290;
	const int TagFinancialStatus = 291;
	const int TagCorporateAction = 292;
	const int TagDefBidSize = 293;
	const int TagDefOfferSize = 294;
	const int TagNoQuoteEntries = 295;
	const int TagNoQuoteSets = 296;
	const int TagQuoteStatus = 297;
	const int TagQuoteCancelType = 298;
	const int TagQuoteEntryID = 299;
	const int TagQuoteRejectReason = 300;
	const int TagQuoteResponseLevel = 301;
	const int TagQuoteSetID = 302;
	const int TagQuoteRequestType = 303;
	const int TagTotNoQuoteEntries = 304;
	const int TagUnderlyingSecurityIDSource = 305;
	const int TagUnderlyingIssuer = 306;
	const int TagUnderlyingSecurityDesc = 307;
	const int TagUnderlyingSecurityExchange = 308;
	const int TagUnderlyingSecurityID = 309;
	const int TagUnderlyingSecurityType = 310;
	const int TagUnderlyingSymbol = 311;
	const int TagUnderlyingSymbolSfx = 312;
	const int TagUnderlyingMaturityMonthYear = 313;
	const int TagUnderlyingMaturityDay = 314;
	const int TagUnderlyingPutOrCall = 315;
	const int TagUnderlyingStrikePrice = 316;
	const int TagUnderlyingOptAttribute = 317;
	const int TagUnderlyingCurrency = 318;
	const int TagRatioQty = 319;
	const int TagSecurityReqID = 320;
	const int TagSecurityRequestType = 321;
	const int TagSecurityResponseID = 322;
	const int TagSecurityResponseType = 323;
	const int TagSecurityStatusReqID = 324;
	const int TagUnsolicitedIndicator = 325;
	const int TagSecurityTradingStatus = 326;
	const int TagHaltReason = 327;
	const int TagInViewOfCommon = 328;
	const int TagDueToRelated = 329;
	const int TagBuyVolume = 330;
	const int TagSellVolume = 331;
	const int TagHighPx = 332;
	const int TagLowPx = 333;
	const int TagAdjustment = 334;
	const int TagTradSesReqID = 335;
	const int TagTradingSessionID = 336;
	const int TagContraTrader = 337;
	const int TagTradSesMethod = 338;
	const int TagTradSesMode = 339;
	const int TagTradSesStatus = 340;
	const int TagTradSesStartTime = 341;
	const int TagTradSesOpenTime = 342;
	const int TagTradSesPreCloseTime = 343;
	const int TagTradSesCloseTime = 344;
	const int TagTradSesEndTime = 345;
	const int TagNumberOfOrders = 346;
	const int TagMessageEncoding = 347;
	const int TagEncodedIssuerLen = 348;
	const int TagEncodedIssuer = 349;
	const int TagEncodedSecurityDescLen = 350;
	const int TagEncodedSecurityDesc = 351;
	const int TagEncodedListExecInstLen = 352;
	const int TagEncodedListExecInst = 353;
	const int TagEncodedTextLen = 354;
	const int TagEncodedText = 355;
	const int TagEncodedSubjectLen = 356;
	const int TagEncodedSubject = 357;
	const int TagEncodedHeadlineLen = 358;
	const int TagEncodedHeadline = 359;
	const int TagEncodedAllocTextLen = 360;
	const int TagEncodedAllocText = 361;
	const int TagEncodedUnderlyingIssuerLen = 362;
	const int TagEncodedUnderlyingIssuer = 363;
	const int TagEncodedUnderlyingSecurityDescLen = 364;
	const int TagEncodedUnderlyingSecurityDesc = 365;
	const int TagAllocPrice = 366;
	const int TagQuoteSetValidUntilTime = 367;
	const int TagQuoteEntryRejectReason = 368;
	const int TagLastMsgSeqNumProcessed = 369;
	const int TagOnBehalfOfSendingTime = 370;
	const int TagRefTagID = 371;
	const int TagRefMsgType = 372;
	const int TagSessionRejectReason = 373;
	const int TagBidRequestTransType = 374;
	const int TagContraBroker = 375;
	const int TagComplianceID = 376;
	const int TagSolicitedFlag = 377;
	const int TagExecRestatementReason = 378;
	const int TagBusinessRejectRefID = 379;
	const int TagBusinessRejectReason = 380;
	const int TagGrossTradeAmt = 381;
	const int TagNoContraBrokers = 382;
	const int TagMaxMessageSize = 383;
	const int TagNoMsgTypes = 384;
	const int TagMsgDirection = 385;
	const int TagNoTradingSessions = 386;
	const int TagTotalVolumeTraded = 387;
	const int TagDiscretionInst = 388;
	const int TagDiscretionOffsetValue = 389;
	const int TagBidID = 390;
	const int TagClientBidID = 391;
	const int TagListName = 392;
	const int TagTotNoRelatedSym = 393;
	const int TagBidType = 394;
	const int TagNumTickets = 395;
	const int TagSideValue1 = 396;
	const int TagSideValue2 = 397;
	const int TagNoBidDescriptors = 398;
	const int TagBidDescriptorType = 399;
	const int TagBidDescriptor = 400;
	const int TagSideValueInd = 401;
	const int TagLiquidityPctLow = 402;
	const int TagLiquidityPctHigh = 403;
	const int TagLiquidityValue = 404;
	const int TagEFPTrackingError = 405;
	const int TagFairValue = 406;
	const int TagOutsideIndexPct = 407;
	const int TagValueOfFutures = 408;
	const int TagLiquidityIndType = 409;
	const int TagWtAverageLiquidity = 410;
	const int TagExchangeForPhysical = 411;
	const int TagOutMainCntryUIndex = 412;
	const int TagCrossPercent = 413;
	const int TagProgRptReqs = 414;
	const int TagProgPeriodInterval = 415;
	const int TagIncTaxInd = 416;
	const int TagNumBidders = 417;
	const int TagBidTradeType = 418;
	const int TagBasisPxType = 419;
	const int TagNoBidComponents = 420;
	const int TagCountry = 421;
	const int TagTotNoStrikes = 422;
	const int TagPriceType = 423;
	const int TagDayOrderQty = 424;
	const int TagDayCumQty = 425;
	const int TagDayAvgPx = 426;
	const int TagGTBookingInst = 427;
	const int TagNoStrikes = 428;
	const int TagListStatusType = 429;
	const int TagNetGrossInd = 430;
	const int TagListOrderStatus = 431;
	const int TagExpireDate = 432;
	const int TagListExecInstType = 433;
	const int TagCxlRejResponseTo = 434;
	const int TagUnderlyingCouponRate = 435;
	const int TagUnderlyingContractMultiplier = 436;
	const int TagContraTradeQty = 437;
	const int TagContraTradeTime = 438;
	const int TagClearingFirm = 439;
	const int TagClearingAccount = 440;
	const int TagLiquidityNumSecurities = 441;
	const int TagMultiLegReportingType = 442;
	const int TagStrikeTime = 443;
	const int TagListStatusText = 444;
	const int TagEncodedListStatusTextLen = 445;
	const int TagEncodedListStatusText = 446;
	const int TagPartyIDSource = 447;
	const int TagPartyID = 448;
	const int TagTotalVolumeTradedDate = 449;
	const int TagTotalVolumeTradedTime = 450;
	const int TagNetChgPrevDay = 451;
	const int TagPartyRole = 452;
	const int TagNoPartyIDs = 453;
	const int TagNoSecurityAltID = 454;
	const int TagSecurityAltID = 455;
	const int TagSecurityAltIDSource = 456;
	const int TagNoUnderlyingSecurityAltID = 457;
	const int TagUnderlyingSecurityAltID = 458;
	const int TagUnderlyingSecurityAltIDSource = 459;
	const int TagProduct = 460;
	const int TagCFICode = 461;
	const int TagUnderlyingProduct = 462;
	const int TagUnderlyingCFICode = 463;
	const int TagTestMessageIndicator = 464;
	const int TagQuantityType = 465;
	const int TagBookingRefID = 466;
	const int TagIndividualAllocID = 467;
	const int TagRoundingDirection = 468;
	const int TagRoundingModulus = 469;
	const int TagCountryOfIssue = 470;
	const int TagStateOrProvinceOfIssue = 471;
	const int TagLocaleOfIssue = 472;
	const int TagNoRegistDtls = 473;
	const int TagMailingDtls = 474;
	const int TagInvestorCountryOfResidence = 475;
	const int TagPaymentRef = 476;
	const int TagDistribPaymentMethod = 477;
	const int TagCashDistribCurr = 478;
	const int TagCommCurrency = 479;
	const int TagCancellationRights = 480;
	const int TagMoneyLaunderingStatus = 481;
	const int TagMailingInst = 482;
	const int TagTransBkdTime = 483;
	const int TagExecPriceType = 484;
	const int TagExecPriceAdjustment = 485;
	const int TagDateOfBirth = 486;
	const int TagTradeReportTransType = 487;
	const int TagCardHolderName = 488;
	const int TagCardNumber = 489;
	const int TagCardExpDate = 490;
	const int TagCardIssNum = 491;
	const int TagPaymentMethod = 492;
	const int TagRegistAcctType = 493;
	const int TagDesignation = 494;
	const int TagTaxAdvantageType = 495;
	const int TagRegistRejReasonText = 496;
	const int TagFundRenewWaiv = 497;
	const int TagCashDistribAgentName = 498;
	const int TagCashDistribAgentCode = 499;
	const int TagCashDistribAgentAcctNumber = 500;
	const int TagCashDistribPayRef = 501;
	const int TagCashDistribAgentAcctName = 502;
	const int TagCardStartDate = 503;
	const int TagPaymentDate = 504;
	const int TagPaymentRemitterID = 505;
	const int TagRegistStatus = 506;
	const int TagRegistRejReasonCode = 507;
	const int TagRegistRefID = 508;
	const int TagRegistDtls = 509;
	const int TagNoDistribInsts = 510;
	const int TagRegistEmail = 511;
	const int TagDistribPercentage = 512;
	const int TagRegistID = 513;
	const int TagRegistTransType = 514;
	const int TagExecValuationPoint = 515;
	const int TagOrderPercent = 516;
	const int TagOwnershipType = 517;
	const int TagNoContAmts = 518;
	const int TagContAmtType = 519;
	const int TagContAmtValue = 520;
	const int TagContAmtCurr = 521;
	const int TagOwnerType = 522;
	const int TagPartySubID = 523;
	const int TagNestedPartyID = 524;
	const int TagNestedPartyIDSource = 525;
	const int TagSecondaryClOrdID = 526;
	const int TagSecondaryExecID = 527;
	const int TagOrderCapacity = 528;
	const int TagOrderRestrictions = 529;
	const int TagMassCancelRequestType = 530;
	const int TagMassCancelResponse = 531;
	const int TagMassCancelRejectReason = 532;
	const int TagTotalAffectedOrders = 533;
	const int TagNoAffectedOrders = 534;
	const int TagAffectedOrderID = 535;
	const int TagAffectedSecondaryOrderID = 536;
	const int TagQuoteType = 537;
	const int TagNestedPartyRole = 538;
	const int TagNoNestedPartyIDs = 539;
	const int TagTotalAccruedInterestAmt = 540;
	const int TagMaturityDate = 541;
	const int TagUnderlyingMaturityDate = 542;
	const int TagInstrRegistry = 543;
	const int TagCashMargin = 544;
	const int TagNestedPartySubID = 545;
	const int TagScope = 546;
	const int TagMDImplicitDelete = 547;
	const int TagCrossID = 548;
	const int TagCrossType = 549;
	const int TagCrossPrioritization = 550;
	const int TagOrigCrossID = 551;
	const int TagNoSides = 552;
	const int TagUsername = 553;
	const int TagPassword = 554;
	const int TagNoLegs = 555;
	const int TagLegCurrency = 556;
	const int TagTotNoSecurityTypes = 557;
	const int TagNoSecurityTypes = 558;
	const int TagSecurityListRequestType = 559;
	const int TagSecurityRequestResult = 560;
	const int TagRoundLot = 561;
	const int TagMinTradeVol = 562;
	const int TagMultiLegRptTypeReq = 563;
	const int TagLegPositionEffect = 564;
	const int TagLegCoveredOrUncovered = 565;
	const int TagLegPrice = 566;
	const int TagTradSesStatusRejReason = 567;
	const int TagTradeRequestID = 568;
	const int TagTradeRequestType = 569;
	const int TagPreviouslyReported = 570;
	const int TagTradeReportID = 571;
	const int TagTradeReportRefID = 572;
	const int TagMatchStatus = 573;
	const int TagMatchType = 574;
	const int TagOddLot = 575;
	const int TagNoClearingInstructions = 576;
	const int TagClearingInstruction = 577;
	const int TagTradeInputSource = 578;
	const int TagTradeInputDevice = 579;
	const int TagNoDates = 580;
	const int TagAccountType = 581;
	const int TagCustOrderCapacity = 582;
	const int TagClOrdLinkID = 583;
	const int TagMassStatusReqID = 584;
	const int TagMassStatusReqType = 585;
	const int TagOrigOrdModTime = 586;
	const int TagLegSettlType = 587;
	const int TagLegSettlDate = 588;
	const int TagDayBookingInst = 589;
	const int TagBookingUnit = 590;
	const int TagPreallocMethod = 591;
	const int TagUnderlyingCountryOfIssue = 592;
	const int TagUnderlyingStateOrProvinceOfIssue = 593;
	const int TagUnderlyingLocaleOfIssue = 594;
	const int TagUnderlyingInstrRegistry = 595;
	const int TagLegCountryOfIssue = 596;
	const int TagLegStateOrProvinceOfIssue = 597;
	const int TagLegLocaleOfIssue = 598;
	const int TagLegInstrRegistry = 599;
	const int TagLegSymbol = 600;
	const int TagLegSymbolSfx = 601;
	const int TagLegSecurityID = 602;
	const int TagLegSecurityIDSource = 603;
	const int TagNoLegSecurityAltID = 604;
	const int TagLegSecurityAltID = 605;
	const int TagLegSecurityAltIDSource = 606;
	const int TagLegProduct = 607;
	const int TagLegCFICode = 608;
	const int TagLegSecurityType = 609;
	const int TagLegMaturityMonthYear = 610;
	const int TagLegMaturityDate = 611;
	const int TagLegStrikePrice = 612;
	const int TagLegOptAttribute = 613;
	const int TagLegContractMultiplier = 614;
	const int TagLegCouponRate = 615;
	const int TagLegSecurityExchange = 616;
	const int TagLegIssuer = 617;
	const int TagEncodedLegIssuerLen = 618;
	const int TagEncodedLegIssuer = 619;
	const int TagLegSecurityDesc = 620;
	const int TagEncodedLegSecurityDescLen = 621;
	const int TagEncodedLegSecurityDesc = 622;
	const int TagLegRatioQty = 623;
	const int TagLegSide = 624;
	const int TagTradingSessionSubID = 625;
	const int TagAllocType = 626;
	const int TagNoHops = 627;
	const int TagHopCompID = 628;
	const int TagHopSendingTime = 629;
	const int TagHopRefID = 630;
	const int TagMidPx = 631;
	const int TagBidYield = 632;
	const int TagMidYield = 633;
	const int TagOfferYield = 634;
	const int TagClearingFeeIndicator = 635;
	const int TagWorkingIndicator = 636;
	const int TagLegLastPx = 637;
	const int TagPriorityIndicator = 638;
	const int TagPriceImprovement = 639;
	const int TagPrice2 = 640;
	const int TagLastForwardPoints2 = 641;
	const int TagBidForwardPoints2 = 642;
	const int TagOfferForwardPoints2 = 643;
	const int TagRFQReqID = 644;
	const int TagMktBidPx = 645;
	const int TagMktOfferPx = 646;
	const int TagMinBidSize = 647;
	const int TagMinOfferSize = 648;
	const int TagQuoteStatusReqID = 649;
	const int TagLegalConfirm = 650;
	const int TagUnderlyingLastPx = 651;
	const int TagUnderlyingLastQty = 652;
	const int TagSecDefStatus = 653;
	const int TagLegRefID = 654;
	const int TagContraLegRefID = 655;
	const int TagSettlCurrBidFxRate = 656;
	const int TagSettlCurrOfferFxRate = 657;
	const int TagQuoteRequestRejectReason = 658;
	const int TagSideComplianceID = 659;
	const int TagAcctIDSource = 660;
	const int TagAllocAcctIDSource = 661;
	const int TagBenchmarkPrice = 662;
	const int TagBenchmarkPriceType = 663;
	const int TagConfirmID = 664;
	const int TagConfirmStatus = 665;
	const int TagConfirmTransType = 666;
	const int TagContractSettlMonth = 667;
	const int TagDeliveryForm = 668;
	const int TagLastParPx = 669;
	const int TagNoLegAllocs = 670;
	const int TagLegAllocAccount = 671;
	const int TagLegIndividualAllocID = 672;
	const int TagLegAllocQty = 673;
	const int TagLegAllocAcctIDSource = 674;
	const int TagLegSettlCurrency = 675;
	const int TagLegBenchmarkCurveCurrency = 676;
	const int TagLegBenchmarkCurveName = 677;
	const int TagLegBenchmarkCurvePoint = 678;
	const int TagLegBenchmarkPrice = 679;
	const int TagLegBenchmarkPriceType = 680;
	const int TagLegBidPx = 681;
	const int TagLegIOIQty = 682;
	const int TagNoLegStipulations = 683;
	const int TagLegOfferPx = 684;
	const int TagLegOrderQty = 685;
	const int TagLegPriceType = 686;
	const int TagLegQty = 687;
	const int TagLegStipulationType = 688;
	const int TagLegStipulationValue = 689;
	const int TagLegSwapType = 690;
	const int TagPool = 691;
	const int TagQuotePriceType = 692;
	const int TagQuoteRespID = 693;
	const int TagQuoteRespType = 694;
	const int TagQuoteQualifier = 695;
	const int TagYieldRedemptionDate = 696;
	const int TagYieldRedemptionPrice = 697;
	const int TagYieldRedemptionPriceType = 698;
	const int TagBenchmarkSecurityID = 699;
	const int TagReversalIndicator = 700;
	const int TagYieldCalcDate = 701;
	const int TagNoPositions = 702;
	const int TagPosType = 703;
	const int TagLongQty = 704;
	const int TagShortQty = 705;
	const int TagPosQtyStatus = 706;
	const int TagPosAmtType = 707;
	const int TagPosAmt = 708;
	const int TagPosTransType = 709;
	const int TagPosReqID = 710;
	const int TagNoUnderlyings = 711;
	const int TagPosMaintAction = 712;
	const int TagOrigPosReqRefID = 713;
	const int TagPosMaintRptRefID = 714;
	const int TagClearingBusinessDate = 715;
	const int TagSettlSessID = 716;
	const int TagSettlSessSubID = 717;
	const int TagAdjustmentType = 718;
	const int TagContraryInstructionIndicator = 719;
	const int TagPriorSpreadIndicator = 720;
	const int TagPosMaintRptID = 721;
	const int TagPosMaintStatus = 722;
	const int TagPosMaintResult = 723;
	const int TagPosReqType = 724;
	const int TagResponseTransportType = 725;
	const int TagResponseDestination = 726;
	const int TagTotalNumPosReports = 727;
	const int TagPosReqResult = 728;
	const int TagPosReqStatus = 729;
	const int TagSettlPrice = 730;
	const int TagSettlPriceType = 731;
	const int TagUnderlyingSettlPrice = 732;
	const int TagUnderlyingSettlPriceType = 733;
	const int TagPriorSettlPrice = 734;
	const int TagNoQuoteQualifiers = 735;
	const int TagAllocSettlCurrency = 736;
	const int TagAllocSettlCurrAmt = 737;
	const int TagInterestAtMaturity = 738;
	const int TagLegDatedDate = 739;
	const int TagLegPool = 740;
	const int TagAllocInterestAtMaturity = 741;
	const int TagAllocAccruedInterestAmt = 742;
	const int TagDeliveryDate = 743;
	const int TagAssignmentMethod = 744;
	const int TagAssignmentUnit = 745;
	const int TagOpenInterest = 746;
	const int TagExerciseMethod = 747;
	const int TagTotNumTradeReports = 748;
	const int TagTradeRequestResult = 749;
	const int TagTradeRequestStatus = 750;
	const int TagTradeReportRejectReason = 751;
	const int TagSideMultiLegReportingType = 752;
	const int TagNoPosAmt = 753;
	const int TagAutoAcceptIndicator = 754;
	const int TagAllocReportID = 755;
	const int TagNoNested2PartyIDs = 756;
	const int TagNested2PartyID = 757;
	const int TagNested2PartyIDSource = 758;
	const int TagNested2PartyRole = 759;
	const int TagNested2PartySubID = 760;
	const int TagBenchmarkSecurityIDSource = 761;
	const int TagSecuritySubType = 762;
	const int TagUnderlyingSecuritySubType = 763;
	const int TagLegSecuritySubType = 764;
	const int TagAllowableOneSidednessPct = 765;
	const int TagAllowableOneSidednessValue = 766;
	const int TagAllowableOneSidednessCurr = 767;
	const int TagNoTrdRegTimestamps = 768;
	const int TagTrdRegTimestamp = 769;
	const int TagTrdRegTimestampType = 770;
	const int TagTrdRegTimestampOrigin = 771;
	const int TagConfirmRefID = 772;
	const int TagConfirmType = 773;
	const int TagConfirmRejReason = 774;
	const int TagBookingType = 775;
	const int TagIndividualAllocRejCode = 776;
	const int TagSettlInstMsgID = 777;
	const int TagNoSettlInst = 778;
	const int TagLastUpdateTime = 779;
	const int TagAllocSettlInstType = 780;
	const int TagNoSettlPartyIDs = 781;
	const int TagSettlPartyID = 782;
	const int TagSettlPartyIDSource = 783;
	const int TagSettlPartyRole = 784;
	const int TagSettlPartySubID = 785;
	const int TagSettlPartySubIDType = 786;
	const int TagDlvyInstType = 787;
	const int TagTerminationType = 788;
	const int TagNextExpectedMsgSeqNum = 789;
	const int TagOrdStatusReqID = 790;
	const int TagSettlInstReqID = 791;
	const int TagSettlInstReqRejCode = 792;
	const int TagSecondaryAllocID = 793;
	const int TagAllocReportType = 794;
	const int TagAllocReportRefID = 795;
	const int TagAllocCancReplaceReason = 796;
	const int TagCopyMsgIndicator = 797;
	const int TagAllocAccountType = 798;
	const int TagOrderAvgPx = 799;
	const int TagOrderBookingQty = 800;
	const int TagNoSettlPartySubIDs = 801;
	const int TagNoPartySubIDs = 802;
	const int TagPartySubIDType = 803;
	const int TagNoNestedPartySubIDs = 804;
	const int TagNestedPartySubIDType = 805;
	const int TagNoNested2PartySubIDs = 806;
	const int TagNested2PartySubIDType = 807;
	const int TagAllocIntermedReqType = 808;
	const int TagUnderlyingPx = 810;
	const int TagPriceDelta = 811;
	const int TagApplQueueMax = 812;
	const int TagApplQueueDepth = 813;
	const int TagApplQueueResolution = 814;
	const int TagApplQueueAction = 815;
	const int TagNoAltMDSource = 816;
	const int TagAltMDSourceID = 817;
	const int TagSecondaryTradeReportID = 818;
	const int TagAvgPxIndicator = 819;
	const int TagTradeLinkID = 820;
	const int TagOrderInputDevice = 821;
	const int TagUnderlyingTradingSessionID = 822;
	const int TagUnderlyingTradingSessionSubID = 823;
	const int TagTradeLegRefID = 824;
	const int TagExchangeRule = 825;
	const int TagTradeAllocIndicator = 826;
	const int TagExpirationCycle = 827;
	const int TagTrdType = 828;
	const int TagTrdSubType = 829;
	const int TagTransferReason = 830;
	const int TagAsgnReqID = 831;
	const int TagTotNumAssignmentReports = 832;
	const int TagAsgnRptID = 833;
	const int TagThresholdAmount = 834;
	const int TagPegMoveType = 835;
	const int TagPegOffsetType = 836;
	const int TagPegLimitType = 837;
	const int TagPegRoundDirection = 838;
	const int TagPeggedPrice = 839;
	const int TagPegScope = 840;
	const int TagDiscretionMoveType = 841;
	const int TagDiscretionOffsetType = 842;
	const int TagDiscretionLimitType = 843;
	const int TagDiscretionRoundDirection = 844;
	const int TagDiscretionPrice = 845;
	const int TagDiscretionScope = 846;
	const int TagTargetStrategy = 847;
	const int TagTargetStrategyParameters = 848;
	const int TagParticipationRate = 849;
	const int TagTargetStrategyPerformance = 850;
	const int TagLastLiquidityInd = 851;
	const int TagPublishTrdIndicator = 852;
	const int TagShortSaleReason = 853;
	const int TagQtyType = 854;
	const int TagSecondaryTrdType = 855;
	const int TagTradeReportType = 856;
	const int TagAllocNoOrdersType = 857;
	const int TagSharedCommission = 858;
	const int TagConfirmReqID = 859;
	const int TagAvgParPx = 860;
	const int TagReportedPx = 861;
	const int TagNoCapacities = 862;
	const int TagOrderCapacityQty = 863;
	const int TagNoEvents = 864;
	const int TagEventType = 865;
	const int TagEventDate = 866;
	const int TagEventPx = 867;
	const int TagEventText = 868;
	const int TagPctAtRisk = 869;
	const int TagNoInstrAttrib = 870;
	const int TagInstrAttribType = 871;
	const int TagInstrAttribValue = 872;
	const int TagDatedDate = 873;
	const int TagInterestAccrualDate = 874;
	const int TagCPProgram = 875;
	const int TagCPRegType = 876;
	const int TagUnderlyingCPProgram = 877;
	const int TagUnderlyingCPRegType = 878;
	const int TagUnderlyingQty = 879;
	const int TagTrdMatchID = 880;
	const int TagSecondaryTradeReportRefID = 881;
	const int TagUnderlyingDirtyPrice = 882;
	const int TagUnderlyingEndPrice = 883;
	const int TagUnderlyingStartValue = 884;
	const int TagUnderlyingCurrentValue = 885;
	const int TagUnderlyingEndValue = 886;
	const int TagNoUnderlyingStips = 887;
	const int TagUnderlyingStipType = 888;
	const int TagUnderlyingStipValue = 889;
	const int TagMaturityNetMoney = 890;
	const int TagMiscFeeBasis = 891;
	const int TagTotNoAllocs = 892;
	const int TagLastFragment = 893;
	const int TagCollReqID = 894;
	const int TagCollAsgnReason = 895;
	const int TagCollInquiryQualifier = 896;
	const int TagNoTrades = 897;
	const int TagMarginRatio = 898;
	const int TagMarginExcess = 899;
	const int TagTotalNetValue = 900;
	const int TagCashOutstanding = 901;
	const int TagCollAsgnID = 902;
	const int TagCollAsgnTransType = 903;
	const int TagCollRespID = 904;
	const int TagCollAsgnRespType = 905;
	const int TagCollAsgnRejectReason = 906;
	const int TagCollAsgnRefID = 907;
	const int TagCollRptID = 908;
	const int TagCollInquiryID = 909;
	const int TagCollStatus = 910;
	const int TagTotNumReports = 911;
	const int TagLastRptRequested = 912;
	const int TagAgreementDesc = 913;
	const int TagAgreementID = 914;
	const int TagAgreementDate = 915;
	const int TagStartDate = 916;
	const int TagEndDate = 917;
	const int TagAgreementCurrency = 918;
	const int TagDeliveryType = 919;
	const int TagEndAccruedInterestAmt = 920;
	const int TagStartCash = 921;
	const int TagEndCash = 922;
	const int TagUserRequestID = 923;
	const int TagUserRequestType = 924;
	const int TagNewPassword = 925;
	const int TagUserStatus = 926;
	const int TagUserStatusText = 927;
	const int TagStatusValue = 928;
	const int TagStatusText = 929;
	const int TagRefCompID = 930;
	const int TagRefSubID = 931;
	const int TagNetworkResponseID = 932;
	const int TagNetworkRequestID = 933;
	const int TagLastNetworkResponseID = 934;
	const int TagNetworkRequestType = 935;
	const int TagNoCompIDs = 936;
	const int TagNetworkStatusResponseType = 937;
	const int TagNoCollInquiryQualifier = 938;
	const int TagTrdRptStatus = 939;
	const int TagAffirmStatus = 940;
	const int TagUnderlyingStrikeCurrency = 941;
	const int TagLegStrikeCurrency = 942;
	const int TagTimeBracket = 943;
	const int TagCollAction = 944;
	const int TagCollInquiryStatus = 945;
	const int TagCollInquiryResult = 946;
	const int TagStrikeCurrency = 947;
	const int TagNoNested3PartyIDs = 948;
	const int TagNested3PartyID = 949;
	const int TagNested3PartyIDSource = 950;
	const int TagNested3PartyRole = 951;
	const int TagNoNested3PartySubIDs = 952;
	const int TagNested3PartySubID = 953;
	const int TagNested3PartySubIDType = 954;
	const int TagLegContractSettlMonth = 955;
	const int TagLegInterestAccrualDate = 956;
	
	inline void AddTagAccount() {
		*((DWORD*)this->currentPos) = 0x00000031; this->currentPos++; // 1
		return;
	}
	inline void AddTagAdvId() {
		*((DWORD*)this->currentPos) = 0x00000032; this->currentPos++; // 2
		return;
	}
	inline void AddTagAdvRefID() {
		*((DWORD*)this->currentPos) = 0x00000033; this->currentPos++; // 3
		return;
	}
	inline void AddTagAdvSide() {
		*((DWORD*)this->currentPos) = 0x00000034; this->currentPos++; // 4
		return;
	}
	inline void AddTagAdvTransType() {
		*((DWORD*)this->currentPos) = 0x00000035; this->currentPos++; // 5
		return;
	}
	inline void AddTagAvgPx() {
		*((DWORD*)this->currentPos) = 0x00000036; this->currentPos++; // 6
		return;
	}
	inline void AddTagBeginSeqNo() {
		*((DWORD*)this->currentPos) = 0x00000037; this->currentPos++; // 7
		return;
	}
	inline void AddTagBeginString() {
		*((DWORD*)this->currentPos) = 0x00000038; this->currentPos++; // 8
		return;
	}
	inline void AddTagBodyLength() {
		*((DWORD*)this->currentPos) = 0x00000039; this->currentPos++; // 9
		return;
	}
	inline void AddTagCheckSum() {
		*((DWORD*)this->currentPos) = 0x000003031; this->currentPos += 2; // 10
		return;
	}
	inline void AddTagClOrdID() {
		*((DWORD*)this->currentPos) = 0x000003131; this->currentPos += 2; // 11
		return;
	}
	inline void AddTagCommission() {
		*((DWORD*)this->currentPos) = 0x000003231; this->currentPos += 2; // 12
		return;
	}
	inline void AddTagCommType() {
		*((DWORD*)this->currentPos) = 0x000003331; this->currentPos += 2; // 13
		return;
	}
	inline void AddTagCumQty() {
		*((DWORD*)this->currentPos) = 0x000003431; this->currentPos += 2; // 14
		return;
	}
	inline void AddTagCurrency() {
		*((DWORD*)this->currentPos) = 0x000003531; this->currentPos += 2; // 15
		return;
	}
	inline void AddTagEndSeqNo() {
		*((DWORD*)this->currentPos) = 0x000003631; this->currentPos += 2; // 16
		return;
	}
	inline void AddTagExecID() {
		*((DWORD*)this->currentPos) = 0x000003731; this->currentPos += 2; // 17
		return;
	}
	inline void AddTagExecInst() {
		*((DWORD*)this->currentPos) = 0x000003831; this->currentPos += 2; // 18
		return;
	}
	inline void AddTagExecRefID() {
		*((DWORD*)this->currentPos) = 0x000003931; this->currentPos += 2; // 19
		return;
	}
	inline void AddTagExecTransType() {
		*((DWORD*)this->currentPos) = 0x000003032; this->currentPos += 2; // 20
		return;
	}
	inline void AddTagHandlInst() {
		*((DWORD*)this->currentPos) = 0x000003132; this->currentPos += 2; // 21
		return;
	}
	inline void AddTagSecurityIDSource() {
		*((DWORD*)this->currentPos) = 0x000003232; this->currentPos += 2; // 22
		return;
	}
	inline void AddTagIOIID() {
		*((DWORD*)this->currentPos) = 0x000003332; this->currentPos += 2; // 23
		return;
	}
	inline void AddTagIOIOthSvc() {
		*((DWORD*)this->currentPos) = 0x000003432; this->currentPos += 2; // 24
		return;
	}
	inline void AddTagIOIQltyInd() {
		*((DWORD*)this->currentPos) = 0x000003532; this->currentPos += 2; // 25
		return;
	}
	inline void AddTagIOIRefID() {
		*((DWORD*)this->currentPos) = 0x000003632; this->currentPos += 2; // 26
		return;
	}
	inline void AddTagIOIQty() {
		*((DWORD*)this->currentPos) = 0x000003732; this->currentPos += 2; // 27
		return;
	}
	inline void AddTagIOITransType() {
		*((DWORD*)this->currentPos) = 0x000003832; this->currentPos += 2; // 28
		return;
	}
	inline void AddTagLastCapacity() {
		*((DWORD*)this->currentPos) = 0x000003932; this->currentPos += 2; // 29
		return;
	}
	inline void AddTagLastMkt() {
		*((DWORD*)this->currentPos) = 0x000003033; this->currentPos += 2; // 30
		return;
	}
	inline void AddTagLastPx() {
		*((DWORD*)this->currentPos) = 0x000003133; this->currentPos += 2; // 31
		return;
	}
	inline void AddTagLastQty() {
		*((DWORD*)this->currentPos) = 0x000003233; this->currentPos += 2; // 32
		return;
	}
	inline void AddTagNoLinesOfText() {
		*((DWORD*)this->currentPos) = 0x000003333; this->currentPos += 2; // 33
		return;
	}
	inline void AddTagMsgSeqNum() {
		*((DWORD*)this->currentPos) = 0x000003433; this->currentPos += 2; // 34
		return;
	}
	inline void AddTagMsgType() {
		*((DWORD*)this->currentPos) = 0x000003533; this->currentPos += 2; // 35
		return;
	}
	inline void AddTagNewSeqNo() {
		*((DWORD*)this->currentPos) = 0x000003633; this->currentPos += 2; // 36
		return;
	}
	inline void AddTagOrderID() {
		*((DWORD*)this->currentPos) = 0x000003733; this->currentPos += 2; // 37
		return;
	}
	inline void AddTagOrderQty() {
		*((DWORD*)this->currentPos) = 0x000003833; this->currentPos += 2; // 38
		return;
	}
	inline void AddTagOrdStatus() {
		*((DWORD*)this->currentPos) = 0x000003933; this->currentPos += 2; // 39
		return;
	}
	inline void AddTagOrdType() {
		*((DWORD*)this->currentPos) = 0x000003034; this->currentPos += 2; // 40
		return;
	}
	inline void AddTagOrigClOrdID() {
		*((DWORD*)this->currentPos) = 0x000003134; this->currentPos += 2; // 41
		return;
	}
	inline void AddTagOrigTime() {
		*((DWORD*)this->currentPos) = 0x000003234; this->currentPos += 2; // 42
		return;
	}
	inline void AddTagPossDupFlag() {
		*((DWORD*)this->currentPos) = 0x000003334; this->currentPos += 2; // 43
		return;
	}
	inline void AddTagPrice() {
		*((DWORD*)this->currentPos) = 0x000003434; this->currentPos += 2; // 44
		return;
	}
	inline void AddTagRefSeqNum() {
		*((DWORD*)this->currentPos) = 0x000003534; this->currentPos += 2; // 45
		return;
	}
	inline void AddTagRelatdSym() {
		*((DWORD*)this->currentPos) = 0x000003634; this->currentPos += 2; // 46
		return;
	}
	inline void AddTagRule80A() {
		*((DWORD*)this->currentPos) = 0x000003734; this->currentPos += 2; // 47
		return;
	}
	inline void AddTagSecurityID() {
		*((DWORD*)this->currentPos) = 0x000003834; this->currentPos += 2; // 48
		return;
	}
	inline void AddTagSenderCompID() {
		*((DWORD*)this->currentPos) = 0x000003934; this->currentPos += 2; // 49
		return;
	}
	inline void AddTagSenderSubID() {
		*((DWORD*)this->currentPos) = 0x000003035; this->currentPos += 2; // 50
		return;
	}
	inline void AddTagSendingDate() {
		*((DWORD*)this->currentPos) = 0x000003135; this->currentPos += 2; // 51
		return;
	}
	inline void AddTagSendingTime() {
		*((DWORD*)this->currentPos) = 0x000003235; this->currentPos += 2; // 52
		return;
	}
	inline void AddTagQuantity() {
		*((DWORD*)this->currentPos) = 0x000003335; this->currentPos += 2; // 53
		return;
	}
	inline void AddTagSide() {
		*((DWORD*)this->currentPos) = 0x000003435; this->currentPos += 2; // 54
		return;
	}
	inline void AddTagSymbol() {
		*((DWORD*)this->currentPos) = 0x000003535; this->currentPos += 2; // 55
		return;
	}
	inline void AddTagTargetCompID() {
		*((DWORD*)this->currentPos) = 0x000003635; this->currentPos += 2; // 56
		return;
	}
	inline void AddTagTargetSubID() {
		*((DWORD*)this->currentPos) = 0x000003735; this->currentPos += 2; // 57
		return;
	}
	inline void AddTagText() {
		*((DWORD*)this->currentPos) = 0x000003835; this->currentPos += 2; // 58
		return;
	}
	inline void AddTagTimeInForce() {
		*((DWORD*)this->currentPos) = 0x000003935; this->currentPos += 2; // 59
		return;
	}
	inline void AddTagTransactTime() {
		*((DWORD*)this->currentPos) = 0x000003036; this->currentPos += 2; // 60
		return;
	}
	inline void AddTagUrgency() {
		*((DWORD*)this->currentPos) = 0x000003136; this->currentPos += 2; // 61
		return;
	}
	inline void AddTagValidUntilTime() {
		*((DWORD*)this->currentPos) = 0x000003236; this->currentPos += 2; // 62
		return;
	}
	inline void AddTagSettlType() {
		*((DWORD*)this->currentPos) = 0x000003336; this->currentPos += 2; // 63
		return;
	}
	inline void AddTagSettlDate() {
		*((DWORD*)this->currentPos) = 0x000003436; this->currentPos += 2; // 64
		return;
	}
	inline void AddTagSymbolSfx() {
		*((DWORD*)this->currentPos) = 0x000003536; this->currentPos += 2; // 65
		return;
	}
	inline void AddTagListID() {
		*((DWORD*)this->currentPos) = 0x000003636; this->currentPos += 2; // 66
		return;
	}
	inline void AddTagListSeqNo() {
		*((DWORD*)this->currentPos) = 0x000003736; this->currentPos += 2; // 67
		return;
	}
	inline void AddTagTotNoOrders() {
		*((DWORD*)this->currentPos) = 0x000003836; this->currentPos += 2; // 68
		return;
	}
	inline void AddTagListExecInst() {
		*((DWORD*)this->currentPos) = 0x000003936; this->currentPos += 2; // 69
		return;
	}
	inline void AddTagAllocID() {
		*((DWORD*)this->currentPos) = 0x000003037; this->currentPos += 2; // 70
		return;
	}
	inline void AddTagAllocTransType() {
		*((DWORD*)this->currentPos) = 0x000003137; this->currentPos += 2; // 71
		return;
	}
	inline void AddTagRefAllocID() {
		*((DWORD*)this->currentPos) = 0x000003237; this->currentPos += 2; // 72
		return;
	}
	inline void AddTagNoOrders() {
		*((DWORD*)this->currentPos) = 0x000003337; this->currentPos += 2; // 73
		return;
	}
	inline void AddTagAvgPxPrecision() {
		*((DWORD*)this->currentPos) = 0x000003437; this->currentPos += 2; // 74
		return;
	}
	inline void AddTagTradeDate() {
		*((DWORD*)this->currentPos) = 0x000003537; this->currentPos += 2; // 75
		return;
	}
	inline void AddTagExecBroker() {
		*((DWORD*)this->currentPos) = 0x000003637; this->currentPos += 2; // 76
		return;
	}
	inline void AddTagPositionEffect() {
		*((DWORD*)this->currentPos) = 0x000003737; this->currentPos += 2; // 77
		return;
	}
	inline void AddTagNoAllocs() {
		*((DWORD*)this->currentPos) = 0x000003837; this->currentPos += 2; // 78
		return;
	}
	inline void AddTagAllocAccount() {
		*((DWORD*)this->currentPos) = 0x000003937; this->currentPos += 2; // 79
		return;
	}
	inline void AddTagAllocQty() {
		*((DWORD*)this->currentPos) = 0x000003038; this->currentPos += 2; // 80
		return;
	}
	inline void AddTagProcessCode() {
		*((DWORD*)this->currentPos) = 0x000003138; this->currentPos += 2; // 81
		return;
	}
	inline void AddTagNoRpts() {
		*((DWORD*)this->currentPos) = 0x000003238; this->currentPos += 2; // 82
		return;
	}
	inline void AddTagRptSeq() {
		*((DWORD*)this->currentPos) = 0x000003338; this->currentPos += 2; // 83
		return;
	}
	inline void AddTagCxlQty() {
		*((DWORD*)this->currentPos) = 0x000003438; this->currentPos += 2; // 84
		return;
	}
	inline void AddTagNoDlvyInst() {
		*((DWORD*)this->currentPos) = 0x000003538; this->currentPos += 2; // 85
		return;
	}
	inline void AddTagDlvyInst() {
		*((DWORD*)this->currentPos) = 0x000003638; this->currentPos += 2; // 86
		return;
	}
	inline void AddTagAllocStatus() {
		*((DWORD*)this->currentPos) = 0x000003738; this->currentPos += 2; // 87
		return;
	}
	inline void AddTagAllocRejCode() {
		*((DWORD*)this->currentPos) = 0x000003838; this->currentPos += 2; // 88
		return;
	}
	inline void AddTagSignature() {
		*((DWORD*)this->currentPos) = 0x000003938; this->currentPos += 2; // 89
		return;
	}
	inline void AddTagSecureDataLen() {
		*((DWORD*)this->currentPos) = 0x000003039; this->currentPos += 2; // 90
		return;
	}
	inline void AddTagSecureData() {
		*((DWORD*)this->currentPos) = 0x000003139; this->currentPos += 2; // 91
		return;
	}
	inline void AddTagBrokerOfCredit() {
		*((DWORD*)this->currentPos) = 0x000003239; this->currentPos += 2; // 92
		return;
	}
	inline void AddTagSignatureLength() {
		*((DWORD*)this->currentPos) = 0x000003339; this->currentPos += 2; // 93
		return;
	}
	inline void AddTagEmailType() {
		*((DWORD*)this->currentPos) = 0x000003439; this->currentPos += 2; // 94
		return;
	}
	inline void AddTagRawDataLength() {
		*((DWORD*)this->currentPos) = 0x000003539; this->currentPos += 2; // 95
		return;
	}
	inline void AddTagRawData() {
		*((DWORD*)this->currentPos) = 0x000003639; this->currentPos += 2; // 96
		return;
	}
	inline void AddTagPossResend() {
		*((DWORD*)this->currentPos) = 0x000003739; this->currentPos += 2; // 97
		return;
	}
	inline void AddTagEncryptMethod() {
		*((DWORD*)this->currentPos) = 0x000003839; this->currentPos += 2; // 98
		return;
	}
	inline void AddTagStopPx() {
		*((DWORD*)this->currentPos) = 0x000003939; this->currentPos += 2; // 99
		return;
	}
	inline void AddTagExDestination() {
		*((DWORD*)this->currentPos) = 0x00303031; this->currentPos += 3; // 100
		return;
	}
	inline void AddTagCxlRejReason() {
		*((DWORD*)this->currentPos) = 0x00323031; this->currentPos += 3; // 102
		return;
	}
	inline void AddTagOrdRejReason() {
		*((DWORD*)this->currentPos) = 0x00333031; this->currentPos += 3; // 103
		return;
	}
	inline void AddTagIOIQualifier() {
		*((DWORD*)this->currentPos) = 0x00343031; this->currentPos += 3; // 104
		return;
	}
	inline void AddTagWaveNo() {
		*((DWORD*)this->currentPos) = 0x00353031; this->currentPos += 3; // 105
		return;
	}
	inline void AddTagIssuer() {
		*((DWORD*)this->currentPos) = 0x00363031; this->currentPos += 3; // 106
		return;
	}
	inline void AddTagSecurityDesc() {
		*((DWORD*)this->currentPos) = 0x00373031; this->currentPos += 3; // 107
		return;
	}
	inline void AddTagHeartBtInt() {
		*((DWORD*)this->currentPos) = 0x00383031; this->currentPos += 3; // 108
		return;
	}
	inline void AddTagClientID() {
		*((DWORD*)this->currentPos) = 0x00393031; this->currentPos += 3; // 109
		return;
	}
	inline void AddTagMinQty() {
		*((DWORD*)this->currentPos) = 0x00303131; this->currentPos += 3; // 110
		return;
	}
	inline void AddTagMaxFloor() {
		*((DWORD*)this->currentPos) = 0x00313131; this->currentPos += 3; // 111
		return;
	}
	inline void AddTagTestReqID() {
		*((DWORD*)this->currentPos) = 0x00323131; this->currentPos += 3; // 112
		return;
	}
	inline void AddTagReportToExch() {
		*((DWORD*)this->currentPos) = 0x00333131; this->currentPos += 3; // 113
		return;
	}
	inline void AddTagLocateReqd() {
		*((DWORD*)this->currentPos) = 0x00343131; this->currentPos += 3; // 114
		return;
	}
	inline void AddTagOnBehalfOfCompID() {
		*((DWORD*)this->currentPos) = 0x00353131; this->currentPos += 3; // 115
		return;
	}
	inline void AddTagOnBehalfOfSubID() {
		*((DWORD*)this->currentPos) = 0x00363131; this->currentPos += 3; // 116
		return;
	}
	inline void AddTagQuoteID() {
		*((DWORD*)this->currentPos) = 0x00373131; this->currentPos += 3; // 117
		return;
	}
	inline void AddTagNetMoney() {
		*((DWORD*)this->currentPos) = 0x00383131; this->currentPos += 3; // 118
		return;
	}
	inline void AddTagSettlCurrAmt() {
		*((DWORD*)this->currentPos) = 0x00393131; this->currentPos += 3; // 119
		return;
	}
	inline void AddTagSettlCurrency() {
		*((DWORD*)this->currentPos) = 0x00303231; this->currentPos += 3; // 120
		return;
	}
	inline void AddTagForexReq() {
		*((DWORD*)this->currentPos) = 0x00313231; this->currentPos += 3; // 121
		return;
	}
	inline void AddTagOrigSendingTime() {
		*((DWORD*)this->currentPos) = 0x00323231; this->currentPos += 3; // 122
		return;
	}
	inline void AddTagGapFillFlag() {
		*((DWORD*)this->currentPos) = 0x00333231; this->currentPos += 3; // 123
		return;
	}
	inline void AddTagNoExecs() {
		*((DWORD*)this->currentPos) = 0x00343231; this->currentPos += 3; // 124
		return;
	}
	inline void AddTagCxlType() {
		*((DWORD*)this->currentPos) = 0x00353231; this->currentPos += 3; // 125
		return;
	}
	inline void AddTagExpireTime() {
		*((DWORD*)this->currentPos) = 0x00363231; this->currentPos += 3; // 126
		return;
	}
	inline void AddTagDKReason() {
		*((DWORD*)this->currentPos) = 0x00373231; this->currentPos += 3; // 127
		return;
	}
	inline void AddTagDeliverToCompID() {
		*((DWORD*)this->currentPos) = 0x00383231; this->currentPos += 3; // 128
		return;
	}
	inline void AddTagDeliverToSubID() {
		*((DWORD*)this->currentPos) = 0x00393231; this->currentPos += 3; // 129
		return;
	}
	inline void AddTagIOINaturalFlag() {
		*((DWORD*)this->currentPos) = 0x00303331; this->currentPos += 3; // 130
		return;
	}
	inline void AddTagQuoteReqID() {
		*((DWORD*)this->currentPos) = 0x00313331; this->currentPos += 3; // 131
		return;
	}
	inline void AddTagBidPx() {
		*((DWORD*)this->currentPos) = 0x00323331; this->currentPos += 3; // 132
		return;
	}
	inline void AddTagOfferPx() {
		*((DWORD*)this->currentPos) = 0x00333331; this->currentPos += 3; // 133
		return;
	}
	inline void AddTagBidSize() {
		*((DWORD*)this->currentPos) = 0x00343331; this->currentPos += 3; // 134
		return;
	}
	inline void AddTagOfferSize() {
		*((DWORD*)this->currentPos) = 0x00353331; this->currentPos += 3; // 135
		return;
	}
	inline void AddTagNoMiscFees() {
		*((DWORD*)this->currentPos) = 0x00363331; this->currentPos += 3; // 136
		return;
	}
	inline void AddTagMiscFeeAmt() {
		*((DWORD*)this->currentPos) = 0x00373331; this->currentPos += 3; // 137
		return;
	}
	inline void AddTagMiscFeeCurr() {
		*((DWORD*)this->currentPos) = 0x00383331; this->currentPos += 3; // 138
		return;
	}
	inline void AddTagMiscFeeType() {
		*((DWORD*)this->currentPos) = 0x00393331; this->currentPos += 3; // 139
		return;
	}
	inline void AddTagPrevClosePx() {
		*((DWORD*)this->currentPos) = 0x00303431; this->currentPos += 3; // 140
		return;
	}
	inline void AddTagResetSeqNumFlag() {
		*((DWORD*)this->currentPos) = 0x00313431; this->currentPos += 3; // 141
		return;
	}
	inline void AddTagSenderLocationID() {
		*((DWORD*)this->currentPos) = 0x00323431; this->currentPos += 3; // 142
		return;
	}
	inline void AddTagTargetLocationID() {
		*((DWORD*)this->currentPos) = 0x00333431; this->currentPos += 3; // 143
		return;
	}
	inline void AddTagOnBehalfOfLocationID() {
		*((DWORD*)this->currentPos) = 0x00343431; this->currentPos += 3; // 144
		return;
	}
	inline void AddTagDeliverToLocationID() {
		*((DWORD*)this->currentPos) = 0x00353431; this->currentPos += 3; // 145
		return;
	}
	inline void AddTagNoRelatedSym() {
		*((DWORD*)this->currentPos) = 0x00363431; this->currentPos += 3; // 146
		return;
	}
	inline void AddTagSubject() {
		*((DWORD*)this->currentPos) = 0x00373431; this->currentPos += 3; // 147
		return;
	}
	inline void AddTagHeadline() {
		*((DWORD*)this->currentPos) = 0x00383431; this->currentPos += 3; // 148
		return;
	}
	inline void AddTagURLLink() {
		*((DWORD*)this->currentPos) = 0x00393431; this->currentPos += 3; // 149
		return;
	}
	inline void AddTagExecType() {
		*((DWORD*)this->currentPos) = 0x00303531; this->currentPos += 3; // 150
		return;
	}
	inline void AddTagLeavesQty() {
		*((DWORD*)this->currentPos) = 0x00313531; this->currentPos += 3; // 151
		return;
	}
	inline void AddTagCashOrderQty() {
		*((DWORD*)this->currentPos) = 0x00323531; this->currentPos += 3; // 152
		return;
	}
	inline void AddTagAllocAvgPx() {
		*((DWORD*)this->currentPos) = 0x00333531; this->currentPos += 3; // 153
		return;
	}
	inline void AddTagAllocNetMoney() {
		*((DWORD*)this->currentPos) = 0x00343531; this->currentPos += 3; // 154
		return;
	}
	inline void AddTagSettlCurrFxRate() {
		*((DWORD*)this->currentPos) = 0x00353531; this->currentPos += 3; // 155
		return;
	}
	inline void AddTagSettlCurrFxRateCalc() {
		*((DWORD*)this->currentPos) = 0x00363531; this->currentPos += 3; // 156
		return;
	}
	inline void AddTagNumDaysInterest() {
		*((DWORD*)this->currentPos) = 0x00373531; this->currentPos += 3; // 157
		return;
	}
	inline void AddTagAccruedInterestRate() {
		*((DWORD*)this->currentPos) = 0x00383531; this->currentPos += 3; // 158
		return;
	}
	inline void AddTagAccruedInterestAmt() {
		*((DWORD*)this->currentPos) = 0x00393531; this->currentPos += 3; // 159
		return;
	}
	inline void AddTagSettlInstMode() {
		*((DWORD*)this->currentPos) = 0x00303631; this->currentPos += 3; // 160
		return;
	}
	inline void AddTagAllocText() {
		*((DWORD*)this->currentPos) = 0x00313631; this->currentPos += 3; // 161
		return;
	}
	inline void AddTagSettlInstID() {
		*((DWORD*)this->currentPos) = 0x00323631; this->currentPos += 3; // 162
		return;
	}
	inline void AddTagSettlInstTransType() {
		*((DWORD*)this->currentPos) = 0x00333631; this->currentPos += 3; // 163
		return;
	}
	inline void AddTagEmailThreadID() {
		*((DWORD*)this->currentPos) = 0x00343631; this->currentPos += 3; // 164
		return;
	}
	inline void AddTagSettlInstSource() {
		*((DWORD*)this->currentPos) = 0x00353631; this->currentPos += 3; // 165
		return;
	}
	inline void AddTagSettlLocation() {
		*((DWORD*)this->currentPos) = 0x00363631; this->currentPos += 3; // 166
		return;
	}
	inline void AddTagSecurityType() {
		*((DWORD*)this->currentPos) = 0x00373631; this->currentPos += 3; // 167
		return;
	}
	inline void AddTagEffectiveTime() {
		*((DWORD*)this->currentPos) = 0x00383631; this->currentPos += 3; // 168
		return;
	}
	inline void AddTagStandInstDbType() {
		*((DWORD*)this->currentPos) = 0x00393631; this->currentPos += 3; // 169
		return;
	}
	inline void AddTagStandInstDbName() {
		*((DWORD*)this->currentPos) = 0x00303731; this->currentPos += 3; // 170
		return;
	}
	inline void AddTagStandInstDbID() {
		*((DWORD*)this->currentPos) = 0x00313731; this->currentPos += 3; // 171
		return;
	}
	inline void AddTagSettlDeliveryType() {
		*((DWORD*)this->currentPos) = 0x00323731; this->currentPos += 3; // 172
		return;
	}
	inline void AddTagSettlDepositoryCode() {
		*((DWORD*)this->currentPos) = 0x00333731; this->currentPos += 3; // 173
		return;
	}
	inline void AddTagSettlBrkrCode() {
		*((DWORD*)this->currentPos) = 0x00343731; this->currentPos += 3; // 174
		return;
	}
	inline void AddTagSettlInstCode() {
		*((DWORD*)this->currentPos) = 0x00353731; this->currentPos += 3; // 175
		return;
	}
	inline void AddTagSecuritySettlAgentName() {
		*((DWORD*)this->currentPos) = 0x00363731; this->currentPos += 3; // 176
		return;
	}
	inline void AddTagSecuritySettlAgentCode() {
		*((DWORD*)this->currentPos) = 0x00373731; this->currentPos += 3; // 177
		return;
	}
	inline void AddTagSecuritySettlAgentAcctNum() {
		*((DWORD*)this->currentPos) = 0x00383731; this->currentPos += 3; // 178
		return;
	}
	inline void AddTagSecuritySettlAgentAcctName() {
		*((DWORD*)this->currentPos) = 0x00393731; this->currentPos += 3; // 179
		return;
	}
	inline void AddTagSecuritySettlAgentContactName() {
		*((DWORD*)this->currentPos) = 0x00303831; this->currentPos += 3; // 180
		return;
	}
	inline void AddTagSecuritySettlAgentContactPhone() {
		*((DWORD*)this->currentPos) = 0x00313831; this->currentPos += 3; // 181
		return;
	}
	inline void AddTagCashSettlAgentName() {
		*((DWORD*)this->currentPos) = 0x00323831; this->currentPos += 3; // 182
		return;
	}
	inline void AddTagCashSettlAgentCode() {
		*((DWORD*)this->currentPos) = 0x00333831; this->currentPos += 3; // 183
		return;
	}
	inline void AddTagCashSettlAgentAcctNum() {
		*((DWORD*)this->currentPos) = 0x00343831; this->currentPos += 3; // 184
		return;
	}
	inline void AddTagCashSettlAgentAcctName() {
		*((DWORD*)this->currentPos) = 0x00353831; this->currentPos += 3; // 185
		return;
	}
	inline void AddTagCashSettlAgentContactName() {
		*((DWORD*)this->currentPos) = 0x00363831; this->currentPos += 3; // 186
		return;
	}
	inline void AddTagCashSettlAgentContactPhone() {
		*((DWORD*)this->currentPos) = 0x00373831; this->currentPos += 3; // 187
		return;
	}
	inline void AddTagBidSpotRate() {
		*((DWORD*)this->currentPos) = 0x00383831; this->currentPos += 3; // 188
		return;
	}
	inline void AddTagBidForwardPoints() {
		*((DWORD*)this->currentPos) = 0x00393831; this->currentPos += 3; // 189
		return;
	}
	inline void AddTagOfferSpotRate() {
		*((DWORD*)this->currentPos) = 0x00303931; this->currentPos += 3; // 190
		return;
	}
	inline void AddTagOfferForwardPoints() {
		*((DWORD*)this->currentPos) = 0x00313931; this->currentPos += 3; // 191
		return;
	}
	inline void AddTagOrderQty2() {
		*((DWORD*)this->currentPos) = 0x00323931; this->currentPos += 3; // 192
		return;
	}
	inline void AddTagSettlDate2() {
		*((DWORD*)this->currentPos) = 0x00333931; this->currentPos += 3; // 193
		return;
	}
	inline void AddTagLastSpotRate() {
		*((DWORD*)this->currentPos) = 0x00343931; this->currentPos += 3; // 194
		return;
	}
	inline void AddTagLastForwardPoints() {
		*((DWORD*)this->currentPos) = 0x00353931; this->currentPos += 3; // 195
		return;
	}
	inline void AddTagAllocLinkID() {
		*((DWORD*)this->currentPos) = 0x00363931; this->currentPos += 3; // 196
		return;
	}
	inline void AddTagAllocLinkType() {
		*((DWORD*)this->currentPos) = 0x00373931; this->currentPos += 3; // 197
		return;
	}
	inline void AddTagSecondaryOrderID() {
		*((DWORD*)this->currentPos) = 0x00383931; this->currentPos += 3; // 198
		return;
	}
	inline void AddTagNoIOIQualifiers() {
		*((DWORD*)this->currentPos) = 0x00393931; this->currentPos += 3; // 199
		return;
	}
	inline void AddTagMaturityMonthYear() {
		*((DWORD*)this->currentPos) = 0x00303032; this->currentPos += 3; // 200
		return;
	}
	inline void AddTagPutOrCall() {
		*((DWORD*)this->currentPos) = 0x00313032; this->currentPos += 3; // 201
		return;
	}
	inline void AddTagStrikePrice() {
		*((DWORD*)this->currentPos) = 0x00323032; this->currentPos += 3; // 202
		return;
	}
	inline void AddTagCoveredOrUncovered() {
		*((DWORD*)this->currentPos) = 0x00333032; this->currentPos += 3; // 203
		return;
	}
	inline void AddTagCustomerOrFirm() {
		*((DWORD*)this->currentPos) = 0x00343032; this->currentPos += 3; // 204
		return;
	}
	inline void AddTagMaturityDay() {
		*((DWORD*)this->currentPos) = 0x00353032; this->currentPos += 3; // 205
		return;
	}
	inline void AddTagOptAttribute() {
		*((DWORD*)this->currentPos) = 0x00363032; this->currentPos += 3; // 206
		return;
	}
	inline void AddTagSecurityExchange() {
		*((DWORD*)this->currentPos) = 0x00373032; this->currentPos += 3; // 207
		return;
	}
	inline void AddTagNotifyBrokerOfCredit() {
		*((DWORD*)this->currentPos) = 0x00383032; this->currentPos += 3; // 208
		return;
	}
	inline void AddTagAllocHandlInst() {
		*((DWORD*)this->currentPos) = 0x00393032; this->currentPos += 3; // 209
		return;
	}
	inline void AddTagMaxShow() {
		*((DWORD*)this->currentPos) = 0x00303132; this->currentPos += 3; // 210
		return;
	}
	inline void AddTagPegOffsetValue() {
		*((DWORD*)this->currentPos) = 0x00313132; this->currentPos += 3; // 211
		return;
	}
	inline void AddTagXmlDataLen() {
		*((DWORD*)this->currentPos) = 0x00323132; this->currentPos += 3; // 212
		return;
	}
	inline void AddTagXmlData() {
		*((DWORD*)this->currentPos) = 0x00333132; this->currentPos += 3; // 213
		return;
	}
	inline void AddTagSettlInstRefID() {
		*((DWORD*)this->currentPos) = 0x00343132; this->currentPos += 3; // 214
		return;
	}
	inline void AddTagNoRoutingIDs() {
		*((DWORD*)this->currentPos) = 0x00353132; this->currentPos += 3; // 215
		return;
	}
	inline void AddTagRoutingType() {
		*((DWORD*)this->currentPos) = 0x00363132; this->currentPos += 3; // 216
		return;
	}
	inline void AddTagRoutingID() {
		*((DWORD*)this->currentPos) = 0x00373132; this->currentPos += 3; // 217
		return;
	}
	inline void AddTagSpread() {
		*((DWORD*)this->currentPos) = 0x00383132; this->currentPos += 3; // 218
		return;
	}
	inline void AddTagBenchmark() {
		*((DWORD*)this->currentPos) = 0x00393132; this->currentPos += 3; // 219
		return;
	}
	inline void AddTagBenchmarkCurveCurrency() {
		*((DWORD*)this->currentPos) = 0x00303232; this->currentPos += 3; // 220
		return;
	}
	inline void AddTagBenchmarkCurveName() {
		*((DWORD*)this->currentPos) = 0x00313232; this->currentPos += 3; // 221
		return;
	}
	inline void AddTagBenchmarkCurvePoint() {
		*((DWORD*)this->currentPos) = 0x00323232; this->currentPos += 3; // 222
		return;
	}
	inline void AddTagCouponRate() {
		*((DWORD*)this->currentPos) = 0x00333232; this->currentPos += 3; // 223
		return;
	}
	inline void AddTagCouponPaymentDate() {
		*((DWORD*)this->currentPos) = 0x00343232; this->currentPos += 3; // 224
		return;
	}
	inline void AddTagIssueDate() {
		*((DWORD*)this->currentPos) = 0x00353232; this->currentPos += 3; // 225
		return;
	}
	inline void AddTagRepurchaseTerm() {
		*((DWORD*)this->currentPos) = 0x00363232; this->currentPos += 3; // 226
		return;
	}
	inline void AddTagRepurchaseRate() {
		*((DWORD*)this->currentPos) = 0x00373232; this->currentPos += 3; // 227
		return;
	}
	inline void AddTagFactor() {
		*((DWORD*)this->currentPos) = 0x00383232; this->currentPos += 3; // 228
		return;
	}
	inline void AddTagTradeOriginationDate() {
		*((DWORD*)this->currentPos) = 0x00393232; this->currentPos += 3; // 229
		return;
	}
	inline void AddTagExDate() {
		*((DWORD*)this->currentPos) = 0x00303332; this->currentPos += 3; // 230
		return;
	}
	inline void AddTagContractMultiplier() {
		*((DWORD*)this->currentPos) = 0x00313332; this->currentPos += 3; // 231
		return;
	}
	inline void AddTagNoStipulations() {
		*((DWORD*)this->currentPos) = 0x00323332; this->currentPos += 3; // 232
		return;
	}
	inline void AddTagStipulationType() {
		*((DWORD*)this->currentPos) = 0x00333332; this->currentPos += 3; // 233
		return;
	}
	inline void AddTagStipulationValue() {
		*((DWORD*)this->currentPos) = 0x00343332; this->currentPos += 3; // 234
		return;
	}
	inline void AddTagYieldType() {
		*((DWORD*)this->currentPos) = 0x00353332; this->currentPos += 3; // 235
		return;
	}
	inline void AddTagYield() {
		*((DWORD*)this->currentPos) = 0x00363332; this->currentPos += 3; // 236
		return;
	}
	inline void AddTagTotalTakedown() {
		*((DWORD*)this->currentPos) = 0x00373332; this->currentPos += 3; // 237
		return;
	}
	inline void AddTagConcession() {
		*((DWORD*)this->currentPos) = 0x00383332; this->currentPos += 3; // 238
		return;
	}
	inline void AddTagRepoCollateralSecurityType() {
		*((DWORD*)this->currentPos) = 0x00393332; this->currentPos += 3; // 239
		return;
	}
	inline void AddTagRedemptionDate() {
		*((DWORD*)this->currentPos) = 0x00303432; this->currentPos += 3; // 240
		return;
	}
	inline void AddTagUnderlyingCouponPaymentDate() {
		*((DWORD*)this->currentPos) = 0x00313432; this->currentPos += 3; // 241
		return;
	}
	inline void AddTagUnderlyingIssueDate() {
		*((DWORD*)this->currentPos) = 0x00323432; this->currentPos += 3; // 242
		return;
	}
	inline void AddTagUnderlyingRepoCollateralSecurityType() {
		*((DWORD*)this->currentPos) = 0x00333432; this->currentPos += 3; // 243
		return;
	}
	inline void AddTagUnderlyingRepurchaseTerm() {
		*((DWORD*)this->currentPos) = 0x00343432; this->currentPos += 3; // 244
		return;
	}
	inline void AddTagUnderlyingRepurchaseRate() {
		*((DWORD*)this->currentPos) = 0x00353432; this->currentPos += 3; // 245
		return;
	}
	inline void AddTagUnderlyingFactor() {
		*((DWORD*)this->currentPos) = 0x00363432; this->currentPos += 3; // 246
		return;
	}
	inline void AddTagUnderlyingRedemptionDate() {
		*((DWORD*)this->currentPos) = 0x00373432; this->currentPos += 3; // 247
		return;
	}
	inline void AddTagLegCouponPaymentDate() {
		*((DWORD*)this->currentPos) = 0x00383432; this->currentPos += 3; // 248
		return;
	}
	inline void AddTagLegIssueDate() {
		*((DWORD*)this->currentPos) = 0x00393432; this->currentPos += 3; // 249
		return;
	}
	inline void AddTagLegRepoCollateralSecurityType() {
		*((DWORD*)this->currentPos) = 0x00303532; this->currentPos += 3; // 250
		return;
	}
	inline void AddTagLegRepurchaseTerm() {
		*((DWORD*)this->currentPos) = 0x00313532; this->currentPos += 3; // 251
		return;
	}
	inline void AddTagLegRepurchaseRate() {
		*((DWORD*)this->currentPos) = 0x00323532; this->currentPos += 3; // 252
		return;
	}
	inline void AddTagLegFactor() {
		*((DWORD*)this->currentPos) = 0x00333532; this->currentPos += 3; // 253
		return;
	}
	inline void AddTagLegRedemptionDate() {
		*((DWORD*)this->currentPos) = 0x00343532; this->currentPos += 3; // 254
		return;
	}
	inline void AddTagCreditRating() {
		*((DWORD*)this->currentPos) = 0x00353532; this->currentPos += 3; // 255
		return;
	}
	inline void AddTagUnderlyingCreditRating() {
		*((DWORD*)this->currentPos) = 0x00363532; this->currentPos += 3; // 256
		return;
	}
	inline void AddTagLegCreditRating() {
		*((DWORD*)this->currentPos) = 0x00373532; this->currentPos += 3; // 257
		return;
	}
	inline void AddTagTradedFlatSwitch() {
		*((DWORD*)this->currentPos) = 0x00383532; this->currentPos += 3; // 258
		return;
	}
	inline void AddTagBasisFeatureDate() {
		*((DWORD*)this->currentPos) = 0x00393532; this->currentPos += 3; // 259
		return;
	}
	inline void AddTagBasisFeaturePrice() {
		*((DWORD*)this->currentPos) = 0x00303632; this->currentPos += 3; // 260
		return;
	}
	inline void AddTagMDReqID() {
		*((DWORD*)this->currentPos) = 0x00323632; this->currentPos += 3; // 262
		return;
	}
	inline void AddTagSubscriptionRequestType() {
		*((DWORD*)this->currentPos) = 0x00333632; this->currentPos += 3; // 263
		return;
	}
	inline void AddTagMarketDepth() {
		*((DWORD*)this->currentPos) = 0x00343632; this->currentPos += 3; // 264
		return;
	}
	inline void AddTagMDUpdateType() {
		*((DWORD*)this->currentPos) = 0x00353632; this->currentPos += 3; // 265
		return;
	}
	inline void AddTagAggregatedBook() {
		*((DWORD*)this->currentPos) = 0x00363632; this->currentPos += 3; // 266
		return;
	}
	inline void AddTagNoMDEntryTypes() {
		*((DWORD*)this->currentPos) = 0x00373632; this->currentPos += 3; // 267
		return;
	}
	inline void AddTagNoMDEntries() {
		*((DWORD*)this->currentPos) = 0x00383632; this->currentPos += 3; // 268
		return;
	}
	inline void AddTagMDEntryType() {
		*((DWORD*)this->currentPos) = 0x00393632; this->currentPos += 3; // 269
		return;
	}
	inline void AddTagMDEntryPx() {
		*((DWORD*)this->currentPos) = 0x00303732; this->currentPos += 3; // 270
		return;
	}
	inline void AddTagMDEntrySize() {
		*((DWORD*)this->currentPos) = 0x00313732; this->currentPos += 3; // 271
		return;
	}
	inline void AddTagMDEntryDate() {
		*((DWORD*)this->currentPos) = 0x00323732; this->currentPos += 3; // 272
		return;
	}
	inline void AddTagMDEntryTime() {
		*((DWORD*)this->currentPos) = 0x00333732; this->currentPos += 3; // 273
		return;
	}
	inline void AddTagTickDirection() {
		*((DWORD*)this->currentPos) = 0x00343732; this->currentPos += 3; // 274
		return;
	}
	inline void AddTagMDMkt() {
		*((DWORD*)this->currentPos) = 0x00353732; this->currentPos += 3; // 275
		return;
	}
	inline void AddTagQuoteCondition() {
		*((DWORD*)this->currentPos) = 0x00363732; this->currentPos += 3; // 276
		return;
	}
	inline void AddTagTradeCondition() {
		*((DWORD*)this->currentPos) = 0x00373732; this->currentPos += 3; // 277
		return;
	}
	inline void AddTagMDEntryID() {
		*((DWORD*)this->currentPos) = 0x00383732; this->currentPos += 3; // 278
		return;
	}
	inline void AddTagMDUpdateAction() {
		*((DWORD*)this->currentPos) = 0x00393732; this->currentPos += 3; // 279
		return;
	}
	inline void AddTagMDEntryRefID() {
		*((DWORD*)this->currentPos) = 0x00303832; this->currentPos += 3; // 280
		return;
	}
	inline void AddTagMDReqRejReason() {
		*((DWORD*)this->currentPos) = 0x00313832; this->currentPos += 3; // 281
		return;
	}
	inline void AddTagMDEntryOriginator() {
		*((DWORD*)this->currentPos) = 0x00323832; this->currentPos += 3; // 282
		return;
	}
	inline void AddTagLocationID() {
		*((DWORD*)this->currentPos) = 0x00333832; this->currentPos += 3; // 283
		return;
	}
	inline void AddTagDeskID() {
		*((DWORD*)this->currentPos) = 0x00343832; this->currentPos += 3; // 284
		return;
	}
	inline void AddTagDeleteReason() {
		*((DWORD*)this->currentPos) = 0x00353832; this->currentPos += 3; // 285
		return;
	}
	inline void AddTagOpenCloseSettlFlag() {
		*((DWORD*)this->currentPos) = 0x00363832; this->currentPos += 3; // 286
		return;
	}
	inline void AddTagSellerDays() {
		*((DWORD*)this->currentPos) = 0x00373832; this->currentPos += 3; // 287
		return;
	}
	inline void AddTagMDEntryBuyer() {
		*((DWORD*)this->currentPos) = 0x00383832; this->currentPos += 3; // 288
		return;
	}
	inline void AddTagMDEntrySeller() {
		*((DWORD*)this->currentPos) = 0x00393832; this->currentPos += 3; // 289
		return;
	}
	inline void AddTagMDEntryPositionNo() {
		*((DWORD*)this->currentPos) = 0x00303932; this->currentPos += 3; // 290
		return;
	}
	inline void AddTagFinancialStatus() {
		*((DWORD*)this->currentPos) = 0x00313932; this->currentPos += 3; // 291
		return;
	}
	inline void AddTagCorporateAction() {
		*((DWORD*)this->currentPos) = 0x00323932; this->currentPos += 3; // 292
		return;
	}
	inline void AddTagDefBidSize() {
		*((DWORD*)this->currentPos) = 0x00333932; this->currentPos += 3; // 293
		return;
	}
	inline void AddTagDefOfferSize() {
		*((DWORD*)this->currentPos) = 0x00343932; this->currentPos += 3; // 294
		return;
	}
	inline void AddTagNoQuoteEntries() {
		*((DWORD*)this->currentPos) = 0x00353932; this->currentPos += 3; // 295
		return;
	}
	inline void AddTagNoQuoteSets() {
		*((DWORD*)this->currentPos) = 0x00363932; this->currentPos += 3; // 296
		return;
	}
	inline void AddTagQuoteStatus() {
		*((DWORD*)this->currentPos) = 0x00373932; this->currentPos += 3; // 297
		return;
	}
	inline void AddTagQuoteCancelType() {
		*((DWORD*)this->currentPos) = 0x00383932; this->currentPos += 3; // 298
		return;
	}
	inline void AddTagQuoteEntryID() {
		*((DWORD*)this->currentPos) = 0x00393932; this->currentPos += 3; // 299
		return;
	}
	inline void AddTagQuoteRejectReason() {
		*((DWORD*)this->currentPos) = 0x00303033; this->currentPos += 3; // 300
		return;
	}
	inline void AddTagQuoteResponseLevel() {
		*((DWORD*)this->currentPos) = 0x00313033; this->currentPos += 3; // 301
		return;
	}
	inline void AddTagQuoteSetID() {
		*((DWORD*)this->currentPos) = 0x00323033; this->currentPos += 3; // 302
		return;
	}
	inline void AddTagQuoteRequestType() {
		*((DWORD*)this->currentPos) = 0x00333033; this->currentPos += 3; // 303
		return;
	}
	inline void AddTagTotNoQuoteEntries() {
		*((DWORD*)this->currentPos) = 0x00343033; this->currentPos += 3; // 304
		return;
	}
	inline void AddTagUnderlyingSecurityIDSource() {
		*((DWORD*)this->currentPos) = 0x00353033; this->currentPos += 3; // 305
		return;
	}
	inline void AddTagUnderlyingIssuer() {
		*((DWORD*)this->currentPos) = 0x00363033; this->currentPos += 3; // 306
		return;
	}
	inline void AddTagUnderlyingSecurityDesc() {
		*((DWORD*)this->currentPos) = 0x00373033; this->currentPos += 3; // 307
		return;
	}
	inline void AddTagUnderlyingSecurityExchange() {
		*((DWORD*)this->currentPos) = 0x00383033; this->currentPos += 3; // 308
		return;
	}
	inline void AddTagUnderlyingSecurityID() {
		*((DWORD*)this->currentPos) = 0x00393033; this->currentPos += 3; // 309
		return;
	}
	inline void AddTagUnderlyingSecurityType() {
		*((DWORD*)this->currentPos) = 0x00303133; this->currentPos += 3; // 310
		return;
	}
	inline void AddTagUnderlyingSymbol() {
		*((DWORD*)this->currentPos) = 0x00313133; this->currentPos += 3; // 311
		return;
	}
	inline void AddTagUnderlyingSymbolSfx() {
		*((DWORD*)this->currentPos) = 0x00323133; this->currentPos += 3; // 312
		return;
	}
	inline void AddTagUnderlyingMaturityMonthYear() {
		*((DWORD*)this->currentPos) = 0x00333133; this->currentPos += 3; // 313
		return;
	}
	inline void AddTagUnderlyingMaturityDay() {
		*((DWORD*)this->currentPos) = 0x00343133; this->currentPos += 3; // 314
		return;
	}
	inline void AddTagUnderlyingPutOrCall() {
		*((DWORD*)this->currentPos) = 0x00353133; this->currentPos += 3; // 315
		return;
	}
	inline void AddTagUnderlyingStrikePrice() {
		*((DWORD*)this->currentPos) = 0x00363133; this->currentPos += 3; // 316
		return;
	}
	inline void AddTagUnderlyingOptAttribute() {
		*((DWORD*)this->currentPos) = 0x00373133; this->currentPos += 3; // 317
		return;
	}
	inline void AddTagUnderlyingCurrency() {
		*((DWORD*)this->currentPos) = 0x00383133; this->currentPos += 3; // 318
		return;
	}
	inline void AddTagRatioQty() {
		*((DWORD*)this->currentPos) = 0x00393133; this->currentPos += 3; // 319
		return;
	}
	inline void AddTagSecurityReqID() {
		*((DWORD*)this->currentPos) = 0x00303233; this->currentPos += 3; // 320
		return;
	}
	inline void AddTagSecurityRequestType() {
		*((DWORD*)this->currentPos) = 0x00313233; this->currentPos += 3; // 321
		return;
	}
	inline void AddTagSecurityResponseID() {
		*((DWORD*)this->currentPos) = 0x00323233; this->currentPos += 3; // 322
		return;
	}
	inline void AddTagSecurityResponseType() {
		*((DWORD*)this->currentPos) = 0x00333233; this->currentPos += 3; // 323
		return;
	}
	inline void AddTagSecurityStatusReqID() {
		*((DWORD*)this->currentPos) = 0x00343233; this->currentPos += 3; // 324
		return;
	}
	inline void AddTagUnsolicitedIndicator() {
		*((DWORD*)this->currentPos) = 0x00353233; this->currentPos += 3; // 325
		return;
	}
	inline void AddTagSecurityTradingStatus() {
		*((DWORD*)this->currentPos) = 0x00363233; this->currentPos += 3; // 326
		return;
	}
	inline void AddTagHaltReason() {
		*((DWORD*)this->currentPos) = 0x00373233; this->currentPos += 3; // 327
		return;
	}
	inline void AddTagInViewOfCommon() {
		*((DWORD*)this->currentPos) = 0x00383233; this->currentPos += 3; // 328
		return;
	}
	inline void AddTagDueToRelated() {
		*((DWORD*)this->currentPos) = 0x00393233; this->currentPos += 3; // 329
		return;
	}
	inline void AddTagBuyVolume() {
		*((DWORD*)this->currentPos) = 0x00303333; this->currentPos += 3; // 330
		return;
	}
	inline void AddTagSellVolume() {
		*((DWORD*)this->currentPos) = 0x00313333; this->currentPos += 3; // 331
		return;
	}
	inline void AddTagHighPx() {
		*((DWORD*)this->currentPos) = 0x00323333; this->currentPos += 3; // 332
		return;
	}
	inline void AddTagLowPx() {
		*((DWORD*)this->currentPos) = 0x00333333; this->currentPos += 3; // 333
		return;
	}
	inline void AddTagAdjustment() {
		*((DWORD*)this->currentPos) = 0x00343333; this->currentPos += 3; // 334
		return;
	}
	inline void AddTagTradSesReqID() {
		*((DWORD*)this->currentPos) = 0x00353333; this->currentPos += 3; // 335
		return;
	}
	inline void AddTagTradingSessionID() {
		*((DWORD*)this->currentPos) = 0x00363333; this->currentPos += 3; // 336
		return;
	}
	inline void AddTagContraTrader() {
		*((DWORD*)this->currentPos) = 0x00373333; this->currentPos += 3; // 337
		return;
	}
	inline void AddTagTradSesMethod() {
		*((DWORD*)this->currentPos) = 0x00383333; this->currentPos += 3; // 338
		return;
	}
	inline void AddTagTradSesMode() {
		*((DWORD*)this->currentPos) = 0x00393333; this->currentPos += 3; // 339
		return;
	}
	inline void AddTagTradSesStatus() {
		*((DWORD*)this->currentPos) = 0x00303433; this->currentPos += 3; // 340
		return;
	}
	inline void AddTagTradSesStartTime() {
		*((DWORD*)this->currentPos) = 0x00313433; this->currentPos += 3; // 341
		return;
	}
	inline void AddTagTradSesOpenTime() {
		*((DWORD*)this->currentPos) = 0x00323433; this->currentPos += 3; // 342
		return;
	}
	inline void AddTagTradSesPreCloseTime() {
		*((DWORD*)this->currentPos) = 0x00333433; this->currentPos += 3; // 343
		return;
	}
	inline void AddTagTradSesCloseTime() {
		*((DWORD*)this->currentPos) = 0x00343433; this->currentPos += 3; // 344
		return;
	}
	inline void AddTagTradSesEndTime() {
		*((DWORD*)this->currentPos) = 0x00353433; this->currentPos += 3; // 345
		return;
	}
	inline void AddTagNumberOfOrders() {
		*((DWORD*)this->currentPos) = 0x00363433; this->currentPos += 3; // 346
		return;
	}
	inline void AddTagMessageEncoding() {
		*((DWORD*)this->currentPos) = 0x00373433; this->currentPos += 3; // 347
		return;
	}
	inline void AddTagEncodedIssuerLen() {
		*((DWORD*)this->currentPos) = 0x00383433; this->currentPos += 3; // 348
		return;
	}
	inline void AddTagEncodedIssuer() {
		*((DWORD*)this->currentPos) = 0x00393433; this->currentPos += 3; // 349
		return;
	}
	inline void AddTagEncodedSecurityDescLen() {
		*((DWORD*)this->currentPos) = 0x00303533; this->currentPos += 3; // 350
		return;
	}
	inline void AddTagEncodedSecurityDesc() {
		*((DWORD*)this->currentPos) = 0x00313533; this->currentPos += 3; // 351
		return;
	}
	inline void AddTagEncodedListExecInstLen() {
		*((DWORD*)this->currentPos) = 0x00323533; this->currentPos += 3; // 352
		return;
	}
	inline void AddTagEncodedListExecInst() {
		*((DWORD*)this->currentPos) = 0x00333533; this->currentPos += 3; // 353
		return;
	}
	inline void AddTagEncodedTextLen() {
		*((DWORD*)this->currentPos) = 0x00343533; this->currentPos += 3; // 354
		return;
	}
	inline void AddTagEncodedText() {
		*((DWORD*)this->currentPos) = 0x00353533; this->currentPos += 3; // 355
		return;
	}
	inline void AddTagEncodedSubjectLen() {
		*((DWORD*)this->currentPos) = 0x00363533; this->currentPos += 3; // 356
		return;
	}
	inline void AddTagEncodedSubject() {
		*((DWORD*)this->currentPos) = 0x00373533; this->currentPos += 3; // 357
		return;
	}
	inline void AddTagEncodedHeadlineLen() {
		*((DWORD*)this->currentPos) = 0x00383533; this->currentPos += 3; // 358
		return;
	}
	inline void AddTagEncodedHeadline() {
		*((DWORD*)this->currentPos) = 0x00393533; this->currentPos += 3; // 359
		return;
	}
	inline void AddTagEncodedAllocTextLen() {
		*((DWORD*)this->currentPos) = 0x00303633; this->currentPos += 3; // 360
		return;
	}
	inline void AddTagEncodedAllocText() {
		*((DWORD*)this->currentPos) = 0x00313633; this->currentPos += 3; // 361
		return;
	}
	inline void AddTagEncodedUnderlyingIssuerLen() {
		*((DWORD*)this->currentPos) = 0x00323633; this->currentPos += 3; // 362
		return;
	}
	inline void AddTagEncodedUnderlyingIssuer() {
		*((DWORD*)this->currentPos) = 0x00333633; this->currentPos += 3; // 363
		return;
	}
	inline void AddTagEncodedUnderlyingSecurityDescLen() {
		*((DWORD*)this->currentPos) = 0x00343633; this->currentPos += 3; // 364
		return;
	}
	inline void AddTagEncodedUnderlyingSecurityDesc() {
		*((DWORD*)this->currentPos) = 0x00353633; this->currentPos += 3; // 365
		return;
	}
	inline void AddTagAllocPrice() {
		*((DWORD*)this->currentPos) = 0x00363633; this->currentPos += 3; // 366
		return;
	}
	inline void AddTagQuoteSetValidUntilTime() {
		*((DWORD*)this->currentPos) = 0x00373633; this->currentPos += 3; // 367
		return;
	}
	inline void AddTagQuoteEntryRejectReason() {
		*((DWORD*)this->currentPos) = 0x00383633; this->currentPos += 3; // 368
		return;
	}
	inline void AddTagLastMsgSeqNumProcessed() {
		*((DWORD*)this->currentPos) = 0x00393633; this->currentPos += 3; // 369
		return;
	}
	inline void AddTagOnBehalfOfSendingTime() {
		*((DWORD*)this->currentPos) = 0x00303733; this->currentPos += 3; // 370
		return;
	}
	inline void AddTagRefTagID() {
		*((DWORD*)this->currentPos) = 0x00313733; this->currentPos += 3; // 371
		return;
	}
	inline void AddTagRefMsgType() {
		*((DWORD*)this->currentPos) = 0x00323733; this->currentPos += 3; // 372
		return;
	}
	inline void AddTagSessionRejectReason() {
		*((DWORD*)this->currentPos) = 0x00333733; this->currentPos += 3; // 373
		return;
	}
	inline void AddTagBidRequestTransType() {
		*((DWORD*)this->currentPos) = 0x00343733; this->currentPos += 3; // 374
		return;
	}
	inline void AddTagContraBroker() {
		*((DWORD*)this->currentPos) = 0x00353733; this->currentPos += 3; // 375
		return;
	}
	inline void AddTagComplianceID() {
		*((DWORD*)this->currentPos) = 0x00363733; this->currentPos += 3; // 376
		return;
	}
	inline void AddTagSolicitedFlag() {
		*((DWORD*)this->currentPos) = 0x00373733; this->currentPos += 3; // 377
		return;
	}
	inline void AddTagExecRestatementReason() {
		*((DWORD*)this->currentPos) = 0x00383733; this->currentPos += 3; // 378
		return;
	}
	inline void AddTagBusinessRejectRefID() {
		*((DWORD*)this->currentPos) = 0x00393733; this->currentPos += 3; // 379
		return;
	}
	inline void AddTagBusinessRejectReason() {
		*((DWORD*)this->currentPos) = 0x00303833; this->currentPos += 3; // 380
		return;
	}
	inline void AddTagGrossTradeAmt() {
		*((DWORD*)this->currentPos) = 0x00313833; this->currentPos += 3; // 381
		return;
	}
	inline void AddTagNoContraBrokers() {
		*((DWORD*)this->currentPos) = 0x00323833; this->currentPos += 3; // 382
		return;
	}
	inline void AddTagMaxMessageSize() {
		*((DWORD*)this->currentPos) = 0x00333833; this->currentPos += 3; // 383
		return;
	}
	inline void AddTagNoMsgTypes() {
		*((DWORD*)this->currentPos) = 0x00343833; this->currentPos += 3; // 384
		return;
	}
	inline void AddTagMsgDirection() {
		*((DWORD*)this->currentPos) = 0x00353833; this->currentPos += 3; // 385
		return;
	}
	inline void AddTagNoTradingSessions() {
		*((DWORD*)this->currentPos) = 0x00363833; this->currentPos += 3; // 386
		return;
	}
	inline void AddTagTotalVolumeTraded() {
		*((DWORD*)this->currentPos) = 0x00373833; this->currentPos += 3; // 387
		return;
	}
	inline void AddTagDiscretionInst() {
		*((DWORD*)this->currentPos) = 0x00383833; this->currentPos += 3; // 388
		return;
	}
	inline void AddTagDiscretionOffsetValue() {
		*((DWORD*)this->currentPos) = 0x00393833; this->currentPos += 3; // 389
		return;
	}
	inline void AddTagBidID() {
		*((DWORD*)this->currentPos) = 0x00303933; this->currentPos += 3; // 390
		return;
	}
	inline void AddTagClientBidID() {
		*((DWORD*)this->currentPos) = 0x00313933; this->currentPos += 3; // 391
		return;
	}
	inline void AddTagListName() {
		*((DWORD*)this->currentPos) = 0x00323933; this->currentPos += 3; // 392
		return;
	}
	inline void AddTagTotNoRelatedSym() {
		*((DWORD*)this->currentPos) = 0x00333933; this->currentPos += 3; // 393
		return;
	}
	inline void AddTagBidType() {
		*((DWORD*)this->currentPos) = 0x00343933; this->currentPos += 3; // 394
		return;
	}
	inline void AddTagNumTickets() {
		*((DWORD*)this->currentPos) = 0x00353933; this->currentPos += 3; // 395
		return;
	}
	inline void AddTagSideValue1() {
		*((DWORD*)this->currentPos) = 0x00363933; this->currentPos += 3; // 396
		return;
	}
	inline void AddTagSideValue2() {
		*((DWORD*)this->currentPos) = 0x00373933; this->currentPos += 3; // 397
		return;
	}
	inline void AddTagNoBidDescriptors() {
		*((DWORD*)this->currentPos) = 0x00383933; this->currentPos += 3; // 398
		return;
	}
	inline void AddTagBidDescriptorType() {
		*((DWORD*)this->currentPos) = 0x00393933; this->currentPos += 3; // 399
		return;
	}
	inline void AddTagBidDescriptor() {
		*((DWORD*)this->currentPos) = 0x00303034; this->currentPos += 3; // 400
		return;
	}
	inline void AddTagSideValueInd() {
		*((DWORD*)this->currentPos) = 0x00313034; this->currentPos += 3; // 401
		return;
	}
	inline void AddTagLiquidityPctLow() {
		*((DWORD*)this->currentPos) = 0x00323034; this->currentPos += 3; // 402
		return;
	}
	inline void AddTagLiquidityPctHigh() {
		*((DWORD*)this->currentPos) = 0x00333034; this->currentPos += 3; // 403
		return;
	}
	inline void AddTagLiquidityValue() {
		*((DWORD*)this->currentPos) = 0x00343034; this->currentPos += 3; // 404
		return;
	}
	inline void AddTagEFPTrackingError() {
		*((DWORD*)this->currentPos) = 0x00353034; this->currentPos += 3; // 405
		return;
	}
	inline void AddTagFairValue() {
		*((DWORD*)this->currentPos) = 0x00363034; this->currentPos += 3; // 406
		return;
	}
	inline void AddTagOutsideIndexPct() {
		*((DWORD*)this->currentPos) = 0x00373034; this->currentPos += 3; // 407
		return;
	}
	inline void AddTagValueOfFutures() {
		*((DWORD*)this->currentPos) = 0x00383034; this->currentPos += 3; // 408
		return;
	}
	inline void AddTagLiquidityIndType() {
		*((DWORD*)this->currentPos) = 0x00393034; this->currentPos += 3; // 409
		return;
	}
	inline void AddTagWtAverageLiquidity() {
		*((DWORD*)this->currentPos) = 0x00303134; this->currentPos += 3; // 410
		return;
	}
	inline void AddTagExchangeForPhysical() {
		*((DWORD*)this->currentPos) = 0x00313134; this->currentPos += 3; // 411
		return;
	}
	inline void AddTagOutMainCntryUIndex() {
		*((DWORD*)this->currentPos) = 0x00323134; this->currentPos += 3; // 412
		return;
	}
	inline void AddTagCrossPercent() {
		*((DWORD*)this->currentPos) = 0x00333134; this->currentPos += 3; // 413
		return;
	}
	inline void AddTagProgRptReqs() {
		*((DWORD*)this->currentPos) = 0x00343134; this->currentPos += 3; // 414
		return;
	}
	inline void AddTagProgPeriodInterval() {
		*((DWORD*)this->currentPos) = 0x00353134; this->currentPos += 3; // 415
		return;
	}
	inline void AddTagIncTaxInd() {
		*((DWORD*)this->currentPos) = 0x00363134; this->currentPos += 3; // 416
		return;
	}
	inline void AddTagNumBidders() {
		*((DWORD*)this->currentPos) = 0x00373134; this->currentPos += 3; // 417
		return;
	}
	inline void AddTagBidTradeType() {
		*((DWORD*)this->currentPos) = 0x00383134; this->currentPos += 3; // 418
		return;
	}
	inline void AddTagBasisPxType() {
		*((DWORD*)this->currentPos) = 0x00393134; this->currentPos += 3; // 419
		return;
	}
	inline void AddTagNoBidComponents() {
		*((DWORD*)this->currentPos) = 0x00303234; this->currentPos += 3; // 420
		return;
	}
	inline void AddTagCountry() {
		*((DWORD*)this->currentPos) = 0x00313234; this->currentPos += 3; // 421
		return;
	}
	inline void AddTagTotNoStrikes() {
		*((DWORD*)this->currentPos) = 0x00323234; this->currentPos += 3; // 422
		return;
	}
	inline void AddTagPriceType() {
		*((DWORD*)this->currentPos) = 0x00333234; this->currentPos += 3; // 423
		return;
	}
	inline void AddTagDayOrderQty() {
		*((DWORD*)this->currentPos) = 0x00343234; this->currentPos += 3; // 424
		return;
	}
	inline void AddTagDayCumQty() {
		*((DWORD*)this->currentPos) = 0x00353234; this->currentPos += 3; // 425
		return;
	}
	inline void AddTagDayAvgPx() {
		*((DWORD*)this->currentPos) = 0x00363234; this->currentPos += 3; // 426
		return;
	}
	inline void AddTagGTBookingInst() {
		*((DWORD*)this->currentPos) = 0x00373234; this->currentPos += 3; // 427
		return;
	}
	inline void AddTagNoStrikes() {
		*((DWORD*)this->currentPos) = 0x00383234; this->currentPos += 3; // 428
		return;
	}
	inline void AddTagListStatusType() {
		*((DWORD*)this->currentPos) = 0x00393234; this->currentPos += 3; // 429
		return;
	}
	inline void AddTagNetGrossInd() {
		*((DWORD*)this->currentPos) = 0x00303334; this->currentPos += 3; // 430
		return;
	}
	inline void AddTagListOrderStatus() {
		*((DWORD*)this->currentPos) = 0x00313334; this->currentPos += 3; // 431
		return;
	}
	inline void AddTagExpireDate() {
		*((DWORD*)this->currentPos) = 0x00323334; this->currentPos += 3; // 432
		return;
	}
	inline void AddTagListExecInstType() {
		*((DWORD*)this->currentPos) = 0x00333334; this->currentPos += 3; // 433
		return;
	}
	inline void AddTagCxlRejResponseTo() {
		*((DWORD*)this->currentPos) = 0x00343334; this->currentPos += 3; // 434
		return;
	}
	inline void AddTagUnderlyingCouponRate() {
		*((DWORD*)this->currentPos) = 0x00353334; this->currentPos += 3; // 435
		return;
	}
	inline void AddTagUnderlyingContractMultiplier() {
		*((DWORD*)this->currentPos) = 0x00363334; this->currentPos += 3; // 436
		return;
	}
	inline void AddTagContraTradeQty() {
		*((DWORD*)this->currentPos) = 0x00373334; this->currentPos += 3; // 437
		return;
	}
	inline void AddTagContraTradeTime() {
		*((DWORD*)this->currentPos) = 0x00383334; this->currentPos += 3; // 438
		return;
	}
	inline void AddTagClearingFirm() {
		*((DWORD*)this->currentPos) = 0x00393334; this->currentPos += 3; // 439
		return;
	}
	inline void AddTagClearingAccount() {
		*((DWORD*)this->currentPos) = 0x00303434; this->currentPos += 3; // 440
		return;
	}
	inline void AddTagLiquidityNumSecurities() {
		*((DWORD*)this->currentPos) = 0x00313434; this->currentPos += 3; // 441
		return;
	}
	inline void AddTagMultiLegReportingType() {
		*((DWORD*)this->currentPos) = 0x00323434; this->currentPos += 3; // 442
		return;
	}
	inline void AddTagStrikeTime() {
		*((DWORD*)this->currentPos) = 0x00333434; this->currentPos += 3; // 443
		return;
	}
	inline void AddTagListStatusText() {
		*((DWORD*)this->currentPos) = 0x00343434; this->currentPos += 3; // 444
		return;
	}
	inline void AddTagEncodedListStatusTextLen() {
		*((DWORD*)this->currentPos) = 0x00353434; this->currentPos += 3; // 445
		return;
	}
	inline void AddTagEncodedListStatusText() {
		*((DWORD*)this->currentPos) = 0x00363434; this->currentPos += 3; // 446
		return;
	}
	inline void AddTagPartyIDSource() {
		*((DWORD*)this->currentPos) = 0x00373434; this->currentPos += 3; // 447
		return;
	}
	inline void AddTagPartyID() {
		*((DWORD*)this->currentPos) = 0x00383434; this->currentPos += 3; // 448
		return;
	}
	inline void AddTagTotalVolumeTradedDate() {
		*((DWORD*)this->currentPos) = 0x00393434; this->currentPos += 3; // 449
		return;
	}
	inline void AddTagTotalVolumeTradedTime() {
		*((DWORD*)this->currentPos) = 0x00303534; this->currentPos += 3; // 450
		return;
	}
	inline void AddTagNetChgPrevDay() {
		*((DWORD*)this->currentPos) = 0x00313534; this->currentPos += 3; // 451
		return;
	}
	inline void AddTagPartyRole() {
		*((DWORD*)this->currentPos) = 0x00323534; this->currentPos += 3; // 452
		return;
	}
	inline void AddTagNoPartyIDs() {
		*((DWORD*)this->currentPos) = 0x00333534; this->currentPos += 3; // 453
		return;
	}
	inline void AddTagNoSecurityAltID() {
		*((DWORD*)this->currentPos) = 0x00343534; this->currentPos += 3; // 454
		return;
	}
	inline void AddTagSecurityAltID() {
		*((DWORD*)this->currentPos) = 0x00353534; this->currentPos += 3; // 455
		return;
	}
	inline void AddTagSecurityAltIDSource() {
		*((DWORD*)this->currentPos) = 0x00363534; this->currentPos += 3; // 456
		return;
	}
	inline void AddTagNoUnderlyingSecurityAltID() {
		*((DWORD*)this->currentPos) = 0x00373534; this->currentPos += 3; // 457
		return;
	}
	inline void AddTagUnderlyingSecurityAltID() {
		*((DWORD*)this->currentPos) = 0x00383534; this->currentPos += 3; // 458
		return;
	}
	inline void AddTagUnderlyingSecurityAltIDSource() {
		*((DWORD*)this->currentPos) = 0x00393534; this->currentPos += 3; // 459
		return;
	}
	inline void AddTagProduct() {
		*((DWORD*)this->currentPos) = 0x00303634; this->currentPos += 3; // 460
		return;
	}
	inline void AddTagCFICode() {
		*((DWORD*)this->currentPos) = 0x00313634; this->currentPos += 3; // 461
		return;
	}
	inline void AddTagUnderlyingProduct() {
		*((DWORD*)this->currentPos) = 0x00323634; this->currentPos += 3; // 462
		return;
	}
	inline void AddTagUnderlyingCFICode() {
		*((DWORD*)this->currentPos) = 0x00333634; this->currentPos += 3; // 463
		return;
	}
	inline void AddTagTestMessageIndicator() {
		*((DWORD*)this->currentPos) = 0x00343634; this->currentPos += 3; // 464
		return;
	}
	inline void AddTagQuantityType() {
		*((DWORD*)this->currentPos) = 0x00353634; this->currentPos += 3; // 465
		return;
	}
	inline void AddTagBookingRefID() {
		*((DWORD*)this->currentPos) = 0x00363634; this->currentPos += 3; // 466
		return;
	}
	inline void AddTagIndividualAllocID() {
		*((DWORD*)this->currentPos) = 0x00373634; this->currentPos += 3; // 467
		return;
	}
	inline void AddTagRoundingDirection() {
		*((DWORD*)this->currentPos) = 0x00383634; this->currentPos += 3; // 468
		return;
	}
	inline void AddTagRoundingModulus() {
		*((DWORD*)this->currentPos) = 0x00393634; this->currentPos += 3; // 469
		return;
	}
	inline void AddTagCountryOfIssue() {
		*((DWORD*)this->currentPos) = 0x00303734; this->currentPos += 3; // 470
		return;
	}
	inline void AddTagStateOrProvinceOfIssue() {
		*((DWORD*)this->currentPos) = 0x00313734; this->currentPos += 3; // 471
		return;
	}
	inline void AddTagLocaleOfIssue() {
		*((DWORD*)this->currentPos) = 0x00323734; this->currentPos += 3; // 472
		return;
	}
	inline void AddTagNoRegistDtls() {
		*((DWORD*)this->currentPos) = 0x00333734; this->currentPos += 3; // 473
		return;
	}
	inline void AddTagMailingDtls() {
		*((DWORD*)this->currentPos) = 0x00343734; this->currentPos += 3; // 474
		return;
	}
	inline void AddTagInvestorCountryOfResidence() {
		*((DWORD*)this->currentPos) = 0x00353734; this->currentPos += 3; // 475
		return;
	}
	inline void AddTagPaymentRef() {
		*((DWORD*)this->currentPos) = 0x00363734; this->currentPos += 3; // 476
		return;
	}
	inline void AddTagDistribPaymentMethod() {
		*((DWORD*)this->currentPos) = 0x00373734; this->currentPos += 3; // 477
		return;
	}
	inline void AddTagCashDistribCurr() {
		*((DWORD*)this->currentPos) = 0x00383734; this->currentPos += 3; // 478
		return;
	}
	inline void AddTagCommCurrency() {
		*((DWORD*)this->currentPos) = 0x00393734; this->currentPos += 3; // 479
		return;
	}
	inline void AddTagCancellationRights() {
		*((DWORD*)this->currentPos) = 0x00303834; this->currentPos += 3; // 480
		return;
	}
	inline void AddTagMoneyLaunderingStatus() {
		*((DWORD*)this->currentPos) = 0x00313834; this->currentPos += 3; // 481
		return;
	}
	inline void AddTagMailingInst() {
		*((DWORD*)this->currentPos) = 0x00323834; this->currentPos += 3; // 482
		return;
	}
	inline void AddTagTransBkdTime() {
		*((DWORD*)this->currentPos) = 0x00333834; this->currentPos += 3; // 483
		return;
	}
	inline void AddTagExecPriceType() {
		*((DWORD*)this->currentPos) = 0x00343834; this->currentPos += 3; // 484
		return;
	}
	inline void AddTagExecPriceAdjustment() {
		*((DWORD*)this->currentPos) = 0x00353834; this->currentPos += 3; // 485
		return;
	}
	inline void AddTagDateOfBirth() {
		*((DWORD*)this->currentPos) = 0x00363834; this->currentPos += 3; // 486
		return;
	}
	inline void AddTagTradeReportTransType() {
		*((DWORD*)this->currentPos) = 0x00373834; this->currentPos += 3; // 487
		return;
	}
	inline void AddTagCardHolderName() {
		*((DWORD*)this->currentPos) = 0x00383834; this->currentPos += 3; // 488
		return;
	}
	inline void AddTagCardNumber() {
		*((DWORD*)this->currentPos) = 0x00393834; this->currentPos += 3; // 489
		return;
	}
	inline void AddTagCardExpDate() {
		*((DWORD*)this->currentPos) = 0x00303934; this->currentPos += 3; // 490
		return;
	}
	inline void AddTagCardIssNum() {
		*((DWORD*)this->currentPos) = 0x00313934; this->currentPos += 3; // 491
		return;
	}
	inline void AddTagPaymentMethod() {
		*((DWORD*)this->currentPos) = 0x00323934; this->currentPos += 3; // 492
		return;
	}
	inline void AddTagRegistAcctType() {
		*((DWORD*)this->currentPos) = 0x00333934; this->currentPos += 3; // 493
		return;
	}
	inline void AddTagDesignation() {
		*((DWORD*)this->currentPos) = 0x00343934; this->currentPos += 3; // 494
		return;
	}
	inline void AddTagTaxAdvantageType() {
		*((DWORD*)this->currentPos) = 0x00353934; this->currentPos += 3; // 495
		return;
	}
	inline void AddTagRegistRejReasonText() {
		*((DWORD*)this->currentPos) = 0x00363934; this->currentPos += 3; // 496
		return;
	}
	inline void AddTagFundRenewWaiv() {
		*((DWORD*)this->currentPos) = 0x00373934; this->currentPos += 3; // 497
		return;
	}
	inline void AddTagCashDistribAgentName() {
		*((DWORD*)this->currentPos) = 0x00383934; this->currentPos += 3; // 498
		return;
	}
	inline void AddTagCashDistribAgentCode() {
		*((DWORD*)this->currentPos) = 0x00393934; this->currentPos += 3; // 499
		return;
	}
	inline void AddTagCashDistribAgentAcctNumber() {
		*((DWORD*)this->currentPos) = 0x00303035; this->currentPos += 3; // 500
		return;
	}
	inline void AddTagCashDistribPayRef() {
		*((DWORD*)this->currentPos) = 0x00313035; this->currentPos += 3; // 501
		return;
	}
	inline void AddTagCashDistribAgentAcctName() {
		*((DWORD*)this->currentPos) = 0x00323035; this->currentPos += 3; // 502
		return;
	}
	inline void AddTagCardStartDate() {
		*((DWORD*)this->currentPos) = 0x00333035; this->currentPos += 3; // 503
		return;
	}
	inline void AddTagPaymentDate() {
		*((DWORD*)this->currentPos) = 0x00343035; this->currentPos += 3; // 504
		return;
	}
	inline void AddTagPaymentRemitterID() {
		*((DWORD*)this->currentPos) = 0x00353035; this->currentPos += 3; // 505
		return;
	}
	inline void AddTagRegistStatus() {
		*((DWORD*)this->currentPos) = 0x00363035; this->currentPos += 3; // 506
		return;
	}
	inline void AddTagRegistRejReasonCode() {
		*((DWORD*)this->currentPos) = 0x00373035; this->currentPos += 3; // 507
		return;
	}
	inline void AddTagRegistRefID() {
		*((DWORD*)this->currentPos) = 0x00383035; this->currentPos += 3; // 508
		return;
	}
	inline void AddTagRegistDtls() {
		*((DWORD*)this->currentPos) = 0x00393035; this->currentPos += 3; // 509
		return;
	}
	inline void AddTagNoDistribInsts() {
		*((DWORD*)this->currentPos) = 0x00303135; this->currentPos += 3; // 510
		return;
	}
	inline void AddTagRegistEmail() {
		*((DWORD*)this->currentPos) = 0x00313135; this->currentPos += 3; // 511
		return;
	}
	inline void AddTagDistribPercentage() {
		*((DWORD*)this->currentPos) = 0x00323135; this->currentPos += 3; // 512
		return;
	}
	inline void AddTagRegistID() {
		*((DWORD*)this->currentPos) = 0x00333135; this->currentPos += 3; // 513
		return;
	}
	inline void AddTagRegistTransType() {
		*((DWORD*)this->currentPos) = 0x00343135; this->currentPos += 3; // 514
		return;
	}
	inline void AddTagExecValuationPoint() {
		*((DWORD*)this->currentPos) = 0x00353135; this->currentPos += 3; // 515
		return;
	}
	inline void AddTagOrderPercent() {
		*((DWORD*)this->currentPos) = 0x00363135; this->currentPos += 3; // 516
		return;
	}
	inline void AddTagOwnershipType() {
		*((DWORD*)this->currentPos) = 0x00373135; this->currentPos += 3; // 517
		return;
	}
	inline void AddTagNoContAmts() {
		*((DWORD*)this->currentPos) = 0x00383135; this->currentPos += 3; // 518
		return;
	}
	inline void AddTagContAmtType() {
		*((DWORD*)this->currentPos) = 0x00393135; this->currentPos += 3; // 519
		return;
	}
	inline void AddTagContAmtValue() {
		*((DWORD*)this->currentPos) = 0x00303235; this->currentPos += 3; // 520
		return;
	}
	inline void AddTagContAmtCurr() {
		*((DWORD*)this->currentPos) = 0x00313235; this->currentPos += 3; // 521
		return;
	}
	inline void AddTagOwnerType() {
		*((DWORD*)this->currentPos) = 0x00323235; this->currentPos += 3; // 522
		return;
	}
	inline void AddTagPartySubID() {
		*((DWORD*)this->currentPos) = 0x00333235; this->currentPos += 3; // 523
		return;
	}
	inline void AddTagNestedPartyID() {
		*((DWORD*)this->currentPos) = 0x00343235; this->currentPos += 3; // 524
		return;
	}
	inline void AddTagNestedPartyIDSource() {
		*((DWORD*)this->currentPos) = 0x00353235; this->currentPos += 3; // 525
		return;
	}
	inline void AddTagSecondaryClOrdID() {
		*((DWORD*)this->currentPos) = 0x00363235; this->currentPos += 3; // 526
		return;
	}
	inline void AddTagSecondaryExecID() {
		*((DWORD*)this->currentPos) = 0x00373235; this->currentPos += 3; // 527
		return;
	}
	inline void AddTagOrderCapacity() {
		*((DWORD*)this->currentPos) = 0x00383235; this->currentPos += 3; // 528
		return;
	}
	inline void AddTagOrderRestrictions() {
		*((DWORD*)this->currentPos) = 0x00393235; this->currentPos += 3; // 529
		return;
	}
	inline void AddTagMassCancelRequestType() {
		*((DWORD*)this->currentPos) = 0x00303335; this->currentPos += 3; // 530
		return;
	}
	inline void AddTagMassCancelResponse() {
		*((DWORD*)this->currentPos) = 0x00313335; this->currentPos += 3; // 531
		return;
	}
	inline void AddTagMassCancelRejectReason() {
		*((DWORD*)this->currentPos) = 0x00323335; this->currentPos += 3; // 532
		return;
	}
	inline void AddTagTotalAffectedOrders() {
		*((DWORD*)this->currentPos) = 0x00333335; this->currentPos += 3; // 533
		return;
	}
	inline void AddTagNoAffectedOrders() {
		*((DWORD*)this->currentPos) = 0x00343335; this->currentPos += 3; // 534
		return;
	}
	inline void AddTagAffectedOrderID() {
		*((DWORD*)this->currentPos) = 0x00353335; this->currentPos += 3; // 535
		return;
	}
	inline void AddTagAffectedSecondaryOrderID() {
		*((DWORD*)this->currentPos) = 0x00363335; this->currentPos += 3; // 536
		return;
	}
	inline void AddTagQuoteType() {
		*((DWORD*)this->currentPos) = 0x00373335; this->currentPos += 3; // 537
		return;
	}
	inline void AddTagNestedPartyRole() {
		*((DWORD*)this->currentPos) = 0x00383335; this->currentPos += 3; // 538
		return;
	}
	inline void AddTagNoNestedPartyIDs() {
		*((DWORD*)this->currentPos) = 0x00393335; this->currentPos += 3; // 539
		return;
	}
	inline void AddTagTotalAccruedInterestAmt() {
		*((DWORD*)this->currentPos) = 0x00303435; this->currentPos += 3; // 540
		return;
	}
	inline void AddTagMaturityDate() {
		*((DWORD*)this->currentPos) = 0x00313435; this->currentPos += 3; // 541
		return;
	}
	inline void AddTagUnderlyingMaturityDate() {
		*((DWORD*)this->currentPos) = 0x00323435; this->currentPos += 3; // 542
		return;
	}
	inline void AddTagInstrRegistry() {
		*((DWORD*)this->currentPos) = 0x00333435; this->currentPos += 3; // 543
		return;
	}
	inline void AddTagCashMargin() {
		*((DWORD*)this->currentPos) = 0x00343435; this->currentPos += 3; // 544
		return;
	}
	inline void AddTagNestedPartySubID() {
		*((DWORD*)this->currentPos) = 0x00353435; this->currentPos += 3; // 545
		return;
	}
	inline void AddTagScope() {
		*((DWORD*)this->currentPos) = 0x00363435; this->currentPos += 3; // 546
		return;
	}
	inline void AddTagMDImplicitDelete() {
		*((DWORD*)this->currentPos) = 0x00373435; this->currentPos += 3; // 547
		return;
	}
	inline void AddTagCrossID() {
		*((DWORD*)this->currentPos) = 0x00383435; this->currentPos += 3; // 548
		return;
	}
	inline void AddTagCrossType() {
		*((DWORD*)this->currentPos) = 0x00393435; this->currentPos += 3; // 549
		return;
	}
	inline void AddTagCrossPrioritization() {
		*((DWORD*)this->currentPos) = 0x00303535; this->currentPos += 3; // 550
		return;
	}
	inline void AddTagOrigCrossID() {
		*((DWORD*)this->currentPos) = 0x00313535; this->currentPos += 3; // 551
		return;
	}
	inline void AddTagNoSides() {
		*((DWORD*)this->currentPos) = 0x00323535; this->currentPos += 3; // 552
		return;
	}
	inline void AddTagUsername() {
		*((DWORD*)this->currentPos) = 0x00333535; this->currentPos += 3; // 553
		return;
	}
	inline void AddTagPassword() {
		*((DWORD*)this->currentPos) = 0x00343535; this->currentPos += 3; // 554
		return;
	}
	inline void AddTagNoLegs() {
		*((DWORD*)this->currentPos) = 0x00353535; this->currentPos += 3; // 555
		return;
	}
	inline void AddTagLegCurrency() {
		*((DWORD*)this->currentPos) = 0x00363535; this->currentPos += 3; // 556
		return;
	}
	inline void AddTagTotNoSecurityTypes() {
		*((DWORD*)this->currentPos) = 0x00373535; this->currentPos += 3; // 557
		return;
	}
	inline void AddTagNoSecurityTypes() {
		*((DWORD*)this->currentPos) = 0x00383535; this->currentPos += 3; // 558
		return;
	}
	inline void AddTagSecurityListRequestType() {
		*((DWORD*)this->currentPos) = 0x00393535; this->currentPos += 3; // 559
		return;
	}
	inline void AddTagSecurityRequestResult() {
		*((DWORD*)this->currentPos) = 0x00303635; this->currentPos += 3; // 560
		return;
	}
	inline void AddTagRoundLot() {
		*((DWORD*)this->currentPos) = 0x00313635; this->currentPos += 3; // 561
		return;
	}
	inline void AddTagMinTradeVol() {
		*((DWORD*)this->currentPos) = 0x00323635; this->currentPos += 3; // 562
		return;
	}
	inline void AddTagMultiLegRptTypeReq() {
		*((DWORD*)this->currentPos) = 0x00333635; this->currentPos += 3; // 563
		return;
	}
	inline void AddTagLegPositionEffect() {
		*((DWORD*)this->currentPos) = 0x00343635; this->currentPos += 3; // 564
		return;
	}
	inline void AddTagLegCoveredOrUncovered() {
		*((DWORD*)this->currentPos) = 0x00353635; this->currentPos += 3; // 565
		return;
	}
	inline void AddTagLegPrice() {
		*((DWORD*)this->currentPos) = 0x00363635; this->currentPos += 3; // 566
		return;
	}
	inline void AddTagTradSesStatusRejReason() {
		*((DWORD*)this->currentPos) = 0x00373635; this->currentPos += 3; // 567
		return;
	}
	inline void AddTagTradeRequestID() {
		*((DWORD*)this->currentPos) = 0x00383635; this->currentPos += 3; // 568
		return;
	}
	inline void AddTagTradeRequestType() {
		*((DWORD*)this->currentPos) = 0x00393635; this->currentPos += 3; // 569
		return;
	}
	inline void AddTagPreviouslyReported() {
		*((DWORD*)this->currentPos) = 0x00303735; this->currentPos += 3; // 570
		return;
	}
	inline void AddTagTradeReportID() {
		*((DWORD*)this->currentPos) = 0x00313735; this->currentPos += 3; // 571
		return;
	}
	inline void AddTagTradeReportRefID() {
		*((DWORD*)this->currentPos) = 0x00323735; this->currentPos += 3; // 572
		return;
	}
	inline void AddTagMatchStatus() {
		*((DWORD*)this->currentPos) = 0x00333735; this->currentPos += 3; // 573
		return;
	}
	inline void AddTagMatchType() {
		*((DWORD*)this->currentPos) = 0x00343735; this->currentPos += 3; // 574
		return;
	}
	inline void AddTagOddLot() {
		*((DWORD*)this->currentPos) = 0x00353735; this->currentPos += 3; // 575
		return;
	}
	inline void AddTagNoClearingInstructions() {
		*((DWORD*)this->currentPos) = 0x00363735; this->currentPos += 3; // 576
		return;
	}
	inline void AddTagClearingInstruction() {
		*((DWORD*)this->currentPos) = 0x00373735; this->currentPos += 3; // 577
		return;
	}
	inline void AddTagTradeInputSource() {
		*((DWORD*)this->currentPos) = 0x00383735; this->currentPos += 3; // 578
		return;
	}
	inline void AddTagTradeInputDevice() {
		*((DWORD*)this->currentPos) = 0x00393735; this->currentPos += 3; // 579
		return;
	}
	inline void AddTagNoDates() {
		*((DWORD*)this->currentPos) = 0x00303835; this->currentPos += 3; // 580
		return;
	}
	inline void AddTagAccountType() {
		*((DWORD*)this->currentPos) = 0x00313835; this->currentPos += 3; // 581
		return;
	}
	inline void AddTagCustOrderCapacity() {
		*((DWORD*)this->currentPos) = 0x00323835; this->currentPos += 3; // 582
		return;
	}
	inline void AddTagClOrdLinkID() {
		*((DWORD*)this->currentPos) = 0x00333835; this->currentPos += 3; // 583
		return;
	}
	inline void AddTagMassStatusReqID() {
		*((DWORD*)this->currentPos) = 0x00343835; this->currentPos += 3; // 584
		return;
	}
	inline void AddTagMassStatusReqType() {
		*((DWORD*)this->currentPos) = 0x00353835; this->currentPos += 3; // 585
		return;
	}
	inline void AddTagOrigOrdModTime() {
		*((DWORD*)this->currentPos) = 0x00363835; this->currentPos += 3; // 586
		return;
	}
	inline void AddTagLegSettlType() {
		*((DWORD*)this->currentPos) = 0x00373835; this->currentPos += 3; // 587
		return;
	}
	inline void AddTagLegSettlDate() {
		*((DWORD*)this->currentPos) = 0x00383835; this->currentPos += 3; // 588
		return;
	}
	inline void AddTagDayBookingInst() {
		*((DWORD*)this->currentPos) = 0x00393835; this->currentPos += 3; // 589
		return;
	}
	inline void AddTagBookingUnit() {
		*((DWORD*)this->currentPos) = 0x00303935; this->currentPos += 3; // 590
		return;
	}
	inline void AddTagPreallocMethod() {
		*((DWORD*)this->currentPos) = 0x00313935; this->currentPos += 3; // 591
		return;
	}
	inline void AddTagUnderlyingCountryOfIssue() {
		*((DWORD*)this->currentPos) = 0x00323935; this->currentPos += 3; // 592
		return;
	}
	inline void AddTagUnderlyingStateOrProvinceOfIssue() {
		*((DWORD*)this->currentPos) = 0x00333935; this->currentPos += 3; // 593
		return;
	}
	inline void AddTagUnderlyingLocaleOfIssue() {
		*((DWORD*)this->currentPos) = 0x00343935; this->currentPos += 3; // 594
		return;
	}
	inline void AddTagUnderlyingInstrRegistry() {
		*((DWORD*)this->currentPos) = 0x00353935; this->currentPos += 3; // 595
		return;
	}
	inline void AddTagLegCountryOfIssue() {
		*((DWORD*)this->currentPos) = 0x00363935; this->currentPos += 3; // 596
		return;
	}
	inline void AddTagLegStateOrProvinceOfIssue() {
		*((DWORD*)this->currentPos) = 0x00373935; this->currentPos += 3; // 597
		return;
	}
	inline void AddTagLegLocaleOfIssue() {
		*((DWORD*)this->currentPos) = 0x00383935; this->currentPos += 3; // 598
		return;
	}
	inline void AddTagLegInstrRegistry() {
		*((DWORD*)this->currentPos) = 0x00393935; this->currentPos += 3; // 599
		return;
	}
	inline void AddTagLegSymbol() {
		*((DWORD*)this->currentPos) = 0x00303036; this->currentPos += 3; // 600
		return;
	}
	inline void AddTagLegSymbolSfx() {
		*((DWORD*)this->currentPos) = 0x00313036; this->currentPos += 3; // 601
		return;
	}
	inline void AddTagLegSecurityID() {
		*((DWORD*)this->currentPos) = 0x00323036; this->currentPos += 3; // 602
		return;
	}
	inline void AddTagLegSecurityIDSource() {
		*((DWORD*)this->currentPos) = 0x00333036; this->currentPos += 3; // 603
		return;
	}
	inline void AddTagNoLegSecurityAltID() {
		*((DWORD*)this->currentPos) = 0x00343036; this->currentPos += 3; // 604
		return;
	}
	inline void AddTagLegSecurityAltID() {
		*((DWORD*)this->currentPos) = 0x00353036; this->currentPos += 3; // 605
		return;
	}
	inline void AddTagLegSecurityAltIDSource() {
		*((DWORD*)this->currentPos) = 0x00363036; this->currentPos += 3; // 606
		return;
	}
	inline void AddTagLegProduct() {
		*((DWORD*)this->currentPos) = 0x00373036; this->currentPos += 3; // 607
		return;
	}
	inline void AddTagLegCFICode() {
		*((DWORD*)this->currentPos) = 0x00383036; this->currentPos += 3; // 608
		return;
	}
	inline void AddTagLegSecurityType() {
		*((DWORD*)this->currentPos) = 0x00393036; this->currentPos += 3; // 609
		return;
	}
	inline void AddTagLegMaturityMonthYear() {
		*((DWORD*)this->currentPos) = 0x00303136; this->currentPos += 3; // 610
		return;
	}
	inline void AddTagLegMaturityDate() {
		*((DWORD*)this->currentPos) = 0x00313136; this->currentPos += 3; // 611
		return;
	}
	inline void AddTagLegStrikePrice() {
		*((DWORD*)this->currentPos) = 0x00323136; this->currentPos += 3; // 612
		return;
	}
	inline void AddTagLegOptAttribute() {
		*((DWORD*)this->currentPos) = 0x00333136; this->currentPos += 3; // 613
		return;
	}
	inline void AddTagLegContractMultiplier() {
		*((DWORD*)this->currentPos) = 0x00343136; this->currentPos += 3; // 614
		return;
	}
	inline void AddTagLegCouponRate() {
		*((DWORD*)this->currentPos) = 0x00353136; this->currentPos += 3; // 615
		return;
	}
	inline void AddTagLegSecurityExchange() {
		*((DWORD*)this->currentPos) = 0x00363136; this->currentPos += 3; // 616
		return;
	}
	inline void AddTagLegIssuer() {
		*((DWORD*)this->currentPos) = 0x00373136; this->currentPos += 3; // 617
		return;
	}
	inline void AddTagEncodedLegIssuerLen() {
		*((DWORD*)this->currentPos) = 0x00383136; this->currentPos += 3; // 618
		return;
	}
	inline void AddTagEncodedLegIssuer() {
		*((DWORD*)this->currentPos) = 0x00393136; this->currentPos += 3; // 619
		return;
	}
	inline void AddTagLegSecurityDesc() {
		*((DWORD*)this->currentPos) = 0x00303236; this->currentPos += 3; // 620
		return;
	}
	inline void AddTagEncodedLegSecurityDescLen() {
		*((DWORD*)this->currentPos) = 0x00313236; this->currentPos += 3; // 621
		return;
	}
	inline void AddTagEncodedLegSecurityDesc() {
		*((DWORD*)this->currentPos) = 0x00323236; this->currentPos += 3; // 622
		return;
	}
	inline void AddTagLegRatioQty() {
		*((DWORD*)this->currentPos) = 0x00333236; this->currentPos += 3; // 623
		return;
	}
	inline void AddTagLegSide() {
		*((DWORD*)this->currentPos) = 0x00343236; this->currentPos += 3; // 624
		return;
	}
	inline void AddTagTradingSessionSubID() {
		*((DWORD*)this->currentPos) = 0x00353236; this->currentPos += 3; // 625
		return;
	}
	inline void AddTagAllocType() {
		*((DWORD*)this->currentPos) = 0x00363236; this->currentPos += 3; // 626
		return;
	}
	inline void AddTagNoHops() {
		*((DWORD*)this->currentPos) = 0x00373236; this->currentPos += 3; // 627
		return;
	}
	inline void AddTagHopCompID() {
		*((DWORD*)this->currentPos) = 0x00383236; this->currentPos += 3; // 628
		return;
	}
	inline void AddTagHopSendingTime() {
		*((DWORD*)this->currentPos) = 0x00393236; this->currentPos += 3; // 629
		return;
	}
	inline void AddTagHopRefID() {
		*((DWORD*)this->currentPos) = 0x00303336; this->currentPos += 3; // 630
		return;
	}
	inline void AddTagMidPx() {
		*((DWORD*)this->currentPos) = 0x00313336; this->currentPos += 3; // 631
		return;
	}
	inline void AddTagBidYield() {
		*((DWORD*)this->currentPos) = 0x00323336; this->currentPos += 3; // 632
		return;
	}
	inline void AddTagMidYield() {
		*((DWORD*)this->currentPos) = 0x00333336; this->currentPos += 3; // 633
		return;
	}
	inline void AddTagOfferYield() {
		*((DWORD*)this->currentPos) = 0x00343336; this->currentPos += 3; // 634
		return;
	}
	inline void AddTagClearingFeeIndicator() {
		*((DWORD*)this->currentPos) = 0x00353336; this->currentPos += 3; // 635
		return;
	}
	inline void AddTagWorkingIndicator() {
		*((DWORD*)this->currentPos) = 0x00363336; this->currentPos += 3; // 636
		return;
	}
	inline void AddTagLegLastPx() {
		*((DWORD*)this->currentPos) = 0x00373336; this->currentPos += 3; // 637
		return;
	}
	inline void AddTagPriorityIndicator() {
		*((DWORD*)this->currentPos) = 0x00383336; this->currentPos += 3; // 638
		return;
	}
	inline void AddTagPriceImprovement() {
		*((DWORD*)this->currentPos) = 0x00393336; this->currentPos += 3; // 639
		return;
	}
	inline void AddTagPrice2() {
		*((DWORD*)this->currentPos) = 0x00303436; this->currentPos += 3; // 640
		return;
	}
	inline void AddTagLastForwardPoints2() {
		*((DWORD*)this->currentPos) = 0x00313436; this->currentPos += 3; // 641
		return;
	}
	inline void AddTagBidForwardPoints2() {
		*((DWORD*)this->currentPos) = 0x00323436; this->currentPos += 3; // 642
		return;
	}
	inline void AddTagOfferForwardPoints2() {
		*((DWORD*)this->currentPos) = 0x00333436; this->currentPos += 3; // 643
		return;
	}
	inline void AddTagRFQReqID() {
		*((DWORD*)this->currentPos) = 0x00343436; this->currentPos += 3; // 644
		return;
	}
	inline void AddTagMktBidPx() {
		*((DWORD*)this->currentPos) = 0x00353436; this->currentPos += 3; // 645
		return;
	}
	inline void AddTagMktOfferPx() {
		*((DWORD*)this->currentPos) = 0x00363436; this->currentPos += 3; // 646
		return;
	}
	inline void AddTagMinBidSize() {
		*((DWORD*)this->currentPos) = 0x00373436; this->currentPos += 3; // 647
		return;
	}
	inline void AddTagMinOfferSize() {
		*((DWORD*)this->currentPos) = 0x00383436; this->currentPos += 3; // 648
		return;
	}
	inline void AddTagQuoteStatusReqID() {
		*((DWORD*)this->currentPos) = 0x00393436; this->currentPos += 3; // 649
		return;
	}
	inline void AddTagLegalConfirm() {
		*((DWORD*)this->currentPos) = 0x00303536; this->currentPos += 3; // 650
		return;
	}
	inline void AddTagUnderlyingLastPx() {
		*((DWORD*)this->currentPos) = 0x00313536; this->currentPos += 3; // 651
		return;
	}
	inline void AddTagUnderlyingLastQty() {
		*((DWORD*)this->currentPos) = 0x00323536; this->currentPos += 3; // 652
		return;
	}
	inline void AddTagSecDefStatus() {
		*((DWORD*)this->currentPos) = 0x00333536; this->currentPos += 3; // 653
		return;
	}
	inline void AddTagLegRefID() {
		*((DWORD*)this->currentPos) = 0x00343536; this->currentPos += 3; // 654
		return;
	}
	inline void AddTagContraLegRefID() {
		*((DWORD*)this->currentPos) = 0x00353536; this->currentPos += 3; // 655
		return;
	}
	inline void AddTagSettlCurrBidFxRate() {
		*((DWORD*)this->currentPos) = 0x00363536; this->currentPos += 3; // 656
		return;
	}
	inline void AddTagSettlCurrOfferFxRate() {
		*((DWORD*)this->currentPos) = 0x00373536; this->currentPos += 3; // 657
		return;
	}
	inline void AddTagQuoteRequestRejectReason() {
		*((DWORD*)this->currentPos) = 0x00383536; this->currentPos += 3; // 658
		return;
	}
	inline void AddTagSideComplianceID() {
		*((DWORD*)this->currentPos) = 0x00393536; this->currentPos += 3; // 659
		return;
	}
	inline void AddTagAcctIDSource() {
		*((DWORD*)this->currentPos) = 0x00303636; this->currentPos += 3; // 660
		return;
	}
	inline void AddTagAllocAcctIDSource() {
		*((DWORD*)this->currentPos) = 0x00313636; this->currentPos += 3; // 661
		return;
	}
	inline void AddTagBenchmarkPrice() {
		*((DWORD*)this->currentPos) = 0x00323636; this->currentPos += 3; // 662
		return;
	}
	inline void AddTagBenchmarkPriceType() {
		*((DWORD*)this->currentPos) = 0x00333636; this->currentPos += 3; // 663
		return;
	}
	inline void AddTagConfirmID() {
		*((DWORD*)this->currentPos) = 0x00343636; this->currentPos += 3; // 664
		return;
	}
	inline void AddTagConfirmStatus() {
		*((DWORD*)this->currentPos) = 0x00353636; this->currentPos += 3; // 665
		return;
	}
	inline void AddTagConfirmTransType() {
		*((DWORD*)this->currentPos) = 0x00363636; this->currentPos += 3; // 666
		return;
	}
	inline void AddTagContractSettlMonth() {
		*((DWORD*)this->currentPos) = 0x00373636; this->currentPos += 3; // 667
		return;
	}
	inline void AddTagDeliveryForm() {
		*((DWORD*)this->currentPos) = 0x00383636; this->currentPos += 3; // 668
		return;
	}
	inline void AddTagLastParPx() {
		*((DWORD*)this->currentPos) = 0x00393636; this->currentPos += 3; // 669
		return;
	}
	inline void AddTagNoLegAllocs() {
		*((DWORD*)this->currentPos) = 0x00303736; this->currentPos += 3; // 670
		return;
	}
	inline void AddTagLegAllocAccount() {
		*((DWORD*)this->currentPos) = 0x00313736; this->currentPos += 3; // 671
		return;
	}
	inline void AddTagLegIndividualAllocID() {
		*((DWORD*)this->currentPos) = 0x00323736; this->currentPos += 3; // 672
		return;
	}
	inline void AddTagLegAllocQty() {
		*((DWORD*)this->currentPos) = 0x00333736; this->currentPos += 3; // 673
		return;
	}
	inline void AddTagLegAllocAcctIDSource() {
		*((DWORD*)this->currentPos) = 0x00343736; this->currentPos += 3; // 674
		return;
	}
	inline void AddTagLegSettlCurrency() {
		*((DWORD*)this->currentPos) = 0x00353736; this->currentPos += 3; // 675
		return;
	}
	inline void AddTagLegBenchmarkCurveCurrency() {
		*((DWORD*)this->currentPos) = 0x00363736; this->currentPos += 3; // 676
		return;
	}
	inline void AddTagLegBenchmarkCurveName() {
		*((DWORD*)this->currentPos) = 0x00373736; this->currentPos += 3; // 677
		return;
	}
	inline void AddTagLegBenchmarkCurvePoint() {
		*((DWORD*)this->currentPos) = 0x00383736; this->currentPos += 3; // 678
		return;
	}
	inline void AddTagLegBenchmarkPrice() {
		*((DWORD*)this->currentPos) = 0x00393736; this->currentPos += 3; // 679
		return;
	}
	inline void AddTagLegBenchmarkPriceType() {
		*((DWORD*)this->currentPos) = 0x00303836; this->currentPos += 3; // 680
		return;
	}
	inline void AddTagLegBidPx() {
		*((DWORD*)this->currentPos) = 0x00313836; this->currentPos += 3; // 681
		return;
	}
	inline void AddTagLegIOIQty() {
		*((DWORD*)this->currentPos) = 0x00323836; this->currentPos += 3; // 682
		return;
	}
	inline void AddTagNoLegStipulations() {
		*((DWORD*)this->currentPos) = 0x00333836; this->currentPos += 3; // 683
		return;
	}
	inline void AddTagLegOfferPx() {
		*((DWORD*)this->currentPos) = 0x00343836; this->currentPos += 3; // 684
		return;
	}
	inline void AddTagLegOrderQty() {
		*((DWORD*)this->currentPos) = 0x00353836; this->currentPos += 3; // 685
		return;
	}
	inline void AddTagLegPriceType() {
		*((DWORD*)this->currentPos) = 0x00363836; this->currentPos += 3; // 686
		return;
	}
	inline void AddTagLegQty() {
		*((DWORD*)this->currentPos) = 0x00373836; this->currentPos += 3; // 687
		return;
	}
	inline void AddTagLegStipulationType() {
		*((DWORD*)this->currentPos) = 0x00383836; this->currentPos += 3; // 688
		return;
	}
	inline void AddTagLegStipulationValue() {
		*((DWORD*)this->currentPos) = 0x00393836; this->currentPos += 3; // 689
		return;
	}
	inline void AddTagLegSwapType() {
		*((DWORD*)this->currentPos) = 0x00303936; this->currentPos += 3; // 690
		return;
	}
	inline void AddTagPool() {
		*((DWORD*)this->currentPos) = 0x00313936; this->currentPos += 3; // 691
		return;
	}
	inline void AddTagQuotePriceType() {
		*((DWORD*)this->currentPos) = 0x00323936; this->currentPos += 3; // 692
		return;
	}
	inline void AddTagQuoteRespID() {
		*((DWORD*)this->currentPos) = 0x00333936; this->currentPos += 3; // 693
		return;
	}
	inline void AddTagQuoteRespType() {
		*((DWORD*)this->currentPos) = 0x00343936; this->currentPos += 3; // 694
		return;
	}
	inline void AddTagQuoteQualifier() {
		*((DWORD*)this->currentPos) = 0x00353936; this->currentPos += 3; // 695
		return;
	}
	inline void AddTagYieldRedemptionDate() {
		*((DWORD*)this->currentPos) = 0x00363936; this->currentPos += 3; // 696
		return;
	}
	inline void AddTagYieldRedemptionPrice() {
		*((DWORD*)this->currentPos) = 0x00373936; this->currentPos += 3; // 697
		return;
	}
	inline void AddTagYieldRedemptionPriceType() {
		*((DWORD*)this->currentPos) = 0x00383936; this->currentPos += 3; // 698
		return;
	}
	inline void AddTagBenchmarkSecurityID() {
		*((DWORD*)this->currentPos) = 0x00393936; this->currentPos += 3; // 699
		return;
	}
	inline void AddTagReversalIndicator() {
		*((DWORD*)this->currentPos) = 0x00303037; this->currentPos += 3; // 700
		return;
	}
	inline void AddTagYieldCalcDate() {
		*((DWORD*)this->currentPos) = 0x00313037; this->currentPos += 3; // 701
		return;
	}
	inline void AddTagNoPositions() {
		*((DWORD*)this->currentPos) = 0x00323037; this->currentPos += 3; // 702
		return;
	}
	inline void AddTagPosType() {
		*((DWORD*)this->currentPos) = 0x00333037; this->currentPos += 3; // 703
		return;
	}
	inline void AddTagLongQty() {
		*((DWORD*)this->currentPos) = 0x00343037; this->currentPos += 3; // 704
		return;
	}
	inline void AddTagShortQty() {
		*((DWORD*)this->currentPos) = 0x00353037; this->currentPos += 3; // 705
		return;
	}
	inline void AddTagPosQtyStatus() {
		*((DWORD*)this->currentPos) = 0x00363037; this->currentPos += 3; // 706
		return;
	}
	inline void AddTagPosAmtType() {
		*((DWORD*)this->currentPos) = 0x00373037; this->currentPos += 3; // 707
		return;
	}
	inline void AddTagPosAmt() {
		*((DWORD*)this->currentPos) = 0x00383037; this->currentPos += 3; // 708
		return;
	}
	inline void AddTagPosTransType() {
		*((DWORD*)this->currentPos) = 0x00393037; this->currentPos += 3; // 709
		return;
	}
	inline void AddTagPosReqID() {
		*((DWORD*)this->currentPos) = 0x00303137; this->currentPos += 3; // 710
		return;
	}
	inline void AddTagNoUnderlyings() {
		*((DWORD*)this->currentPos) = 0x00313137; this->currentPos += 3; // 711
		return;
	}
	inline void AddTagPosMaintAction() {
		*((DWORD*)this->currentPos) = 0x00323137; this->currentPos += 3; // 712
		return;
	}
	inline void AddTagOrigPosReqRefID() {
		*((DWORD*)this->currentPos) = 0x00333137; this->currentPos += 3; // 713
		return;
	}
	inline void AddTagPosMaintRptRefID() {
		*((DWORD*)this->currentPos) = 0x00343137; this->currentPos += 3; // 714
		return;
	}
	inline void AddTagClearingBusinessDate() {
		*((DWORD*)this->currentPos) = 0x00353137; this->currentPos += 3; // 715
		return;
	}
	inline void AddTagSettlSessID() {
		*((DWORD*)this->currentPos) = 0x00363137; this->currentPos += 3; // 716
		return;
	}
	inline void AddTagSettlSessSubID() {
		*((DWORD*)this->currentPos) = 0x00373137; this->currentPos += 3; // 717
		return;
	}
	inline void AddTagAdjustmentType() {
		*((DWORD*)this->currentPos) = 0x00383137; this->currentPos += 3; // 718
		return;
	}
	inline void AddTagContraryInstructionIndicator() {
		*((DWORD*)this->currentPos) = 0x00393137; this->currentPos += 3; // 719
		return;
	}
	inline void AddTagPriorSpreadIndicator() {
		*((DWORD*)this->currentPos) = 0x00303237; this->currentPos += 3; // 720
		return;
	}
	inline void AddTagPosMaintRptID() {
		*((DWORD*)this->currentPos) = 0x00313237; this->currentPos += 3; // 721
		return;
	}
	inline void AddTagPosMaintStatus() {
		*((DWORD*)this->currentPos) = 0x00323237; this->currentPos += 3; // 722
		return;
	}
	inline void AddTagPosMaintResult() {
		*((DWORD*)this->currentPos) = 0x00333237; this->currentPos += 3; // 723
		return;
	}
	inline void AddTagPosReqType() {
		*((DWORD*)this->currentPos) = 0x00343237; this->currentPos += 3; // 724
		return;
	}
	inline void AddTagResponseTransportType() {
		*((DWORD*)this->currentPos) = 0x00353237; this->currentPos += 3; // 725
		return;
	}
	inline void AddTagResponseDestination() {
		*((DWORD*)this->currentPos) = 0x00363237; this->currentPos += 3; // 726
		return;
	}
	inline void AddTagTotalNumPosReports() {
		*((DWORD*)this->currentPos) = 0x00373237; this->currentPos += 3; // 727
		return;
	}
	inline void AddTagPosReqResult() {
		*((DWORD*)this->currentPos) = 0x00383237; this->currentPos += 3; // 728
		return;
	}
	inline void AddTagPosReqStatus() {
		*((DWORD*)this->currentPos) = 0x00393237; this->currentPos += 3; // 729
		return;
	}
	inline void AddTagSettlPrice() {
		*((DWORD*)this->currentPos) = 0x00303337; this->currentPos += 3; // 730
		return;
	}
	inline void AddTagSettlPriceType() {
		*((DWORD*)this->currentPos) = 0x00313337; this->currentPos += 3; // 731
		return;
	}
	inline void AddTagUnderlyingSettlPrice() {
		*((DWORD*)this->currentPos) = 0x00323337; this->currentPos += 3; // 732
		return;
	}
	inline void AddTagUnderlyingSettlPriceType() {
		*((DWORD*)this->currentPos) = 0x00333337; this->currentPos += 3; // 733
		return;
	}
	inline void AddTagPriorSettlPrice() {
		*((DWORD*)this->currentPos) = 0x00343337; this->currentPos += 3; // 734
		return;
	}
	inline void AddTagNoQuoteQualifiers() {
		*((DWORD*)this->currentPos) = 0x00353337; this->currentPos += 3; // 735
		return;
	}
	inline void AddTagAllocSettlCurrency() {
		*((DWORD*)this->currentPos) = 0x00363337; this->currentPos += 3; // 736
		return;
	}
	inline void AddTagAllocSettlCurrAmt() {
		*((DWORD*)this->currentPos) = 0x00373337; this->currentPos += 3; // 737
		return;
	}
	inline void AddTagInterestAtMaturity() {
		*((DWORD*)this->currentPos) = 0x00383337; this->currentPos += 3; // 738
		return;
	}
	inline void AddTagLegDatedDate() {
		*((DWORD*)this->currentPos) = 0x00393337; this->currentPos += 3; // 739
		return;
	}
	inline void AddTagLegPool() {
		*((DWORD*)this->currentPos) = 0x00303437; this->currentPos += 3; // 740
		return;
	}
	inline void AddTagAllocInterestAtMaturity() {
		*((DWORD*)this->currentPos) = 0x00313437; this->currentPos += 3; // 741
		return;
	}
	inline void AddTagAllocAccruedInterestAmt() {
		*((DWORD*)this->currentPos) = 0x00323437; this->currentPos += 3; // 742
		return;
	}
	inline void AddTagDeliveryDate() {
		*((DWORD*)this->currentPos) = 0x00333437; this->currentPos += 3; // 743
		return;
	}
	inline void AddTagAssignmentMethod() {
		*((DWORD*)this->currentPos) = 0x00343437; this->currentPos += 3; // 744
		return;
	}
	inline void AddTagAssignmentUnit() {
		*((DWORD*)this->currentPos) = 0x00353437; this->currentPos += 3; // 745
		return;
	}
	inline void AddTagOpenInterest() {
		*((DWORD*)this->currentPos) = 0x00363437; this->currentPos += 3; // 746
		return;
	}
	inline void AddTagExerciseMethod() {
		*((DWORD*)this->currentPos) = 0x00373437; this->currentPos += 3; // 747
		return;
	}
	inline void AddTagTotNumTradeReports() {
		*((DWORD*)this->currentPos) = 0x00383437; this->currentPos += 3; // 748
		return;
	}
	inline void AddTagTradeRequestResult() {
		*((DWORD*)this->currentPos) = 0x00393437; this->currentPos += 3; // 749
		return;
	}
	inline void AddTagTradeRequestStatus() {
		*((DWORD*)this->currentPos) = 0x00303537; this->currentPos += 3; // 750
		return;
	}
	inline void AddTagTradeReportRejectReason() {
		*((DWORD*)this->currentPos) = 0x00313537; this->currentPos += 3; // 751
		return;
	}
	inline void AddTagSideMultiLegReportingType() {
		*((DWORD*)this->currentPos) = 0x00323537; this->currentPos += 3; // 752
		return;
	}
	inline void AddTagNoPosAmt() {
		*((DWORD*)this->currentPos) = 0x00333537; this->currentPos += 3; // 753
		return;
	}
	inline void AddTagAutoAcceptIndicator() {
		*((DWORD*)this->currentPos) = 0x00343537; this->currentPos += 3; // 754
		return;
	}
	inline void AddTagAllocReportID() {
		*((DWORD*)this->currentPos) = 0x00353537; this->currentPos += 3; // 755
		return;
	}
	inline void AddTagNoNested2PartyIDs() {
		*((DWORD*)this->currentPos) = 0x00363537; this->currentPos += 3; // 756
		return;
	}
	inline void AddTagNested2PartyID() {
		*((DWORD*)this->currentPos) = 0x00373537; this->currentPos += 3; // 757
		return;
	}
	inline void AddTagNested2PartyIDSource() {
		*((DWORD*)this->currentPos) = 0x00383537; this->currentPos += 3; // 758
		return;
	}
	inline void AddTagNested2PartyRole() {
		*((DWORD*)this->currentPos) = 0x00393537; this->currentPos += 3; // 759
		return;
	}
	inline void AddTagNested2PartySubID() {
		*((DWORD*)this->currentPos) = 0x00303637; this->currentPos += 3; // 760
		return;
	}
	inline void AddTagBenchmarkSecurityIDSource() {
		*((DWORD*)this->currentPos) = 0x00313637; this->currentPos += 3; // 761
		return;
	}
	inline void AddTagSecuritySubType() {
		*((DWORD*)this->currentPos) = 0x00323637; this->currentPos += 3; // 762
		return;
	}
	inline void AddTagUnderlyingSecuritySubType() {
		*((DWORD*)this->currentPos) = 0x00333637; this->currentPos += 3; // 763
		return;
	}
	inline void AddTagLegSecuritySubType() {
		*((DWORD*)this->currentPos) = 0x00343637; this->currentPos += 3; // 764
		return;
	}
	inline void AddTagAllowableOneSidednessPct() {
		*((DWORD*)this->currentPos) = 0x00353637; this->currentPos += 3; // 765
		return;
	}
	inline void AddTagAllowableOneSidednessValue() {
		*((DWORD*)this->currentPos) = 0x00363637; this->currentPos += 3; // 766
		return;
	}
	inline void AddTagAllowableOneSidednessCurr() {
		*((DWORD*)this->currentPos) = 0x00373637; this->currentPos += 3; // 767
		return;
	}
	inline void AddTagNoTrdRegTimestamps() {
		*((DWORD*)this->currentPos) = 0x00383637; this->currentPos += 3; // 768
		return;
	}
	inline void AddTagTrdRegTimestamp() {
		*((DWORD*)this->currentPos) = 0x00393637; this->currentPos += 3; // 769
		return;
	}
	inline void AddTagTrdRegTimestampType() {
		*((DWORD*)this->currentPos) = 0x00303737; this->currentPos += 3; // 770
		return;
	}
	inline void AddTagTrdRegTimestampOrigin() {
		*((DWORD*)this->currentPos) = 0x00313737; this->currentPos += 3; // 771
		return;
	}
	inline void AddTagConfirmRefID() {
		*((DWORD*)this->currentPos) = 0x00323737; this->currentPos += 3; // 772
		return;
	}
	inline void AddTagConfirmType() {
		*((DWORD*)this->currentPos) = 0x00333737; this->currentPos += 3; // 773
		return;
	}
	inline void AddTagConfirmRejReason() {
		*((DWORD*)this->currentPos) = 0x00343737; this->currentPos += 3; // 774
		return;
	}
	inline void AddTagBookingType() {
		*((DWORD*)this->currentPos) = 0x00353737; this->currentPos += 3; // 775
		return;
	}
	inline void AddTagIndividualAllocRejCode() {
		*((DWORD*)this->currentPos) = 0x00363737; this->currentPos += 3; // 776
		return;
	}
	inline void AddTagSettlInstMsgID() {
		*((DWORD*)this->currentPos) = 0x00373737; this->currentPos += 3; // 777
		return;
	}
	inline void AddTagNoSettlInst() {
		*((DWORD*)this->currentPos) = 0x00383737; this->currentPos += 3; // 778
		return;
	}
	inline void AddTagLastUpdateTime() {
		*((DWORD*)this->currentPos) = 0x00393737; this->currentPos += 3; // 779
		return;
	}
	inline void AddTagAllocSettlInstType() {
		*((DWORD*)this->currentPos) = 0x00303837; this->currentPos += 3; // 780
		return;
	}
	inline void AddTagNoSettlPartyIDs() {
		*((DWORD*)this->currentPos) = 0x00313837; this->currentPos += 3; // 781
		return;
	}
	inline void AddTagSettlPartyID() {
		*((DWORD*)this->currentPos) = 0x00323837; this->currentPos += 3; // 782
		return;
	}
	inline void AddTagSettlPartyIDSource() {
		*((DWORD*)this->currentPos) = 0x00333837; this->currentPos += 3; // 783
		return;
	}
	inline void AddTagSettlPartyRole() {
		*((DWORD*)this->currentPos) = 0x00343837; this->currentPos += 3; // 784
		return;
	}
	inline void AddTagSettlPartySubID() {
		*((DWORD*)this->currentPos) = 0x00353837; this->currentPos += 3; // 785
		return;
	}
	inline void AddTagSettlPartySubIDType() {
		*((DWORD*)this->currentPos) = 0x00363837; this->currentPos += 3; // 786
		return;
	}
	inline void AddTagDlvyInstType() {
		*((DWORD*)this->currentPos) = 0x00373837; this->currentPos += 3; // 787
		return;
	}
	inline void AddTagTerminationType() {
		*((DWORD*)this->currentPos) = 0x00383837; this->currentPos += 3; // 788
		return;
	}
	inline void AddTagNextExpectedMsgSeqNum() {
		*((DWORD*)this->currentPos) = 0x00393837; this->currentPos += 3; // 789
		return;
	}
	inline void AddTagOrdStatusReqID() {
		*((DWORD*)this->currentPos) = 0x00303937; this->currentPos += 3; // 790
		return;
	}
	inline void AddTagSettlInstReqID() {
		*((DWORD*)this->currentPos) = 0x00313937; this->currentPos += 3; // 791
		return;
	}
	inline void AddTagSettlInstReqRejCode() {
		*((DWORD*)this->currentPos) = 0x00323937; this->currentPos += 3; // 792
		return;
	}
	inline void AddTagSecondaryAllocID() {
		*((DWORD*)this->currentPos) = 0x00333937; this->currentPos += 3; // 793
		return;
	}
	inline void AddTagAllocReportType() {
		*((DWORD*)this->currentPos) = 0x00343937; this->currentPos += 3; // 794
		return;
	}
	inline void AddTagAllocReportRefID() {
		*((DWORD*)this->currentPos) = 0x00353937; this->currentPos += 3; // 795
		return;
	}
	inline void AddTagAllocCancReplaceReason() {
		*((DWORD*)this->currentPos) = 0x00363937; this->currentPos += 3; // 796
		return;
	}
	inline void AddTagCopyMsgIndicator() {
		*((DWORD*)this->currentPos) = 0x00373937; this->currentPos += 3; // 797
		return;
	}
	inline void AddTagAllocAccountType() {
		*((DWORD*)this->currentPos) = 0x00383937; this->currentPos += 3; // 798
		return;
	}
	inline void AddTagOrderAvgPx() {
		*((DWORD*)this->currentPos) = 0x00393937; this->currentPos += 3; // 799
		return;
	}
	inline void AddTagOrderBookingQty() {
		*((DWORD*)this->currentPos) = 0x00303038; this->currentPos += 3; // 800
		return;
	}
	inline void AddTagNoSettlPartySubIDs() {
		*((DWORD*)this->currentPos) = 0x00313038; this->currentPos += 3; // 801
		return;
	}
	inline void AddTagNoPartySubIDs() {
		*((DWORD*)this->currentPos) = 0x00323038; this->currentPos += 3; // 802
		return;
	}
	inline void AddTagPartySubIDType() {
		*((DWORD*)this->currentPos) = 0x00333038; this->currentPos += 3; // 803
		return;
	}
	inline void AddTagNoNestedPartySubIDs() {
		*((DWORD*)this->currentPos) = 0x00343038; this->currentPos += 3; // 804
		return;
	}
	inline void AddTagNestedPartySubIDType() {
		*((DWORD*)this->currentPos) = 0x00353038; this->currentPos += 3; // 805
		return;
	}
	inline void AddTagNoNested2PartySubIDs() {
		*((DWORD*)this->currentPos) = 0x00363038; this->currentPos += 3; // 806
		return;
	}
	inline void AddTagNested2PartySubIDType() {
		*((DWORD*)this->currentPos) = 0x00373038; this->currentPos += 3; // 807
		return;
	}
	inline void AddTagAllocIntermedReqType() {
		*((DWORD*)this->currentPos) = 0x00383038; this->currentPos += 3; // 808
		return;
	}
	inline void AddTagUnderlyingPx() {
		*((DWORD*)this->currentPos) = 0x00303138; this->currentPos += 3; // 810
		return;
	}
	inline void AddTagPriceDelta() {
		*((DWORD*)this->currentPos) = 0x00313138; this->currentPos += 3; // 811
		return;
	}
	inline void AddTagApplQueueMax() {
		*((DWORD*)this->currentPos) = 0x00323138; this->currentPos += 3; // 812
		return;
	}
	inline void AddTagApplQueueDepth() {
		*((DWORD*)this->currentPos) = 0x00333138; this->currentPos += 3; // 813
		return;
	}
	inline void AddTagApplQueueResolution() {
		*((DWORD*)this->currentPos) = 0x00343138; this->currentPos += 3; // 814
		return;
	}
	inline void AddTagApplQueueAction() {
		*((DWORD*)this->currentPos) = 0x00353138; this->currentPos += 3; // 815
		return;
	}
	inline void AddTagNoAltMDSource() {
		*((DWORD*)this->currentPos) = 0x00363138; this->currentPos += 3; // 816
		return;
	}
	inline void AddTagAltMDSourceID() {
		*((DWORD*)this->currentPos) = 0x00373138; this->currentPos += 3; // 817
		return;
	}
	inline void AddTagSecondaryTradeReportID() {
		*((DWORD*)this->currentPos) = 0x00383138; this->currentPos += 3; // 818
		return;
	}
	inline void AddTagAvgPxIndicator() {
		*((DWORD*)this->currentPos) = 0x00393138; this->currentPos += 3; // 819
		return;
	}
	inline void AddTagTradeLinkID() {
		*((DWORD*)this->currentPos) = 0x00303238; this->currentPos += 3; // 820
		return;
	}
	inline void AddTagOrderInputDevice() {
		*((DWORD*)this->currentPos) = 0x00313238; this->currentPos += 3; // 821
		return;
	}
	inline void AddTagUnderlyingTradingSessionID() {
		*((DWORD*)this->currentPos) = 0x00323238; this->currentPos += 3; // 822
		return;
	}
	inline void AddTagUnderlyingTradingSessionSubID() {
		*((DWORD*)this->currentPos) = 0x00333238; this->currentPos += 3; // 823
		return;
	}
	inline void AddTagTradeLegRefID() {
		*((DWORD*)this->currentPos) = 0x00343238; this->currentPos += 3; // 824
		return;
	}
	inline void AddTagExchangeRule() {
		*((DWORD*)this->currentPos) = 0x00353238; this->currentPos += 3; // 825
		return;
	}
	inline void AddTagTradeAllocIndicator() {
		*((DWORD*)this->currentPos) = 0x00363238; this->currentPos += 3; // 826
		return;
	}
	inline void AddTagExpirationCycle() {
		*((DWORD*)this->currentPos) = 0x00373238; this->currentPos += 3; // 827
		return;
	}
	inline void AddTagTrdType() {
		*((DWORD*)this->currentPos) = 0x00383238; this->currentPos += 3; // 828
		return;
	}
	inline void AddTagTrdSubType() {
		*((DWORD*)this->currentPos) = 0x00393238; this->currentPos += 3; // 829
		return;
	}
	inline void AddTagTransferReason() {
		*((DWORD*)this->currentPos) = 0x00303338; this->currentPos += 3; // 830
		return;
	}
	inline void AddTagAsgnReqID() {
		*((DWORD*)this->currentPos) = 0x00313338; this->currentPos += 3; // 831
		return;
	}
	inline void AddTagTotNumAssignmentReports() {
		*((DWORD*)this->currentPos) = 0x00323338; this->currentPos += 3; // 832
		return;
	}
	inline void AddTagAsgnRptID() {
		*((DWORD*)this->currentPos) = 0x00333338; this->currentPos += 3; // 833
		return;
	}
	inline void AddTagThresholdAmount() {
		*((DWORD*)this->currentPos) = 0x00343338; this->currentPos += 3; // 834
		return;
	}
	inline void AddTagPegMoveType() {
		*((DWORD*)this->currentPos) = 0x00353338; this->currentPos += 3; // 835
		return;
	}
	inline void AddTagPegOffsetType() {
		*((DWORD*)this->currentPos) = 0x00363338; this->currentPos += 3; // 836
		return;
	}
	inline void AddTagPegLimitType() {
		*((DWORD*)this->currentPos) = 0x00373338; this->currentPos += 3; // 837
		return;
	}
	inline void AddTagPegRoundDirection() {
		*((DWORD*)this->currentPos) = 0x00383338; this->currentPos += 3; // 838
		return;
	}
	inline void AddTagPeggedPrice() {
		*((DWORD*)this->currentPos) = 0x00393338; this->currentPos += 3; // 839
		return;
	}
	inline void AddTagPegScope() {
		*((DWORD*)this->currentPos) = 0x00303438; this->currentPos += 3; // 840
		return;
	}
	inline void AddTagDiscretionMoveType() {
		*((DWORD*)this->currentPos) = 0x00313438; this->currentPos += 3; // 841
		return;
	}
	inline void AddTagDiscretionOffsetType() {
		*((DWORD*)this->currentPos) = 0x00323438; this->currentPos += 3; // 842
		return;
	}
	inline void AddTagDiscretionLimitType() {
		*((DWORD*)this->currentPos) = 0x00333438; this->currentPos += 3; // 843
		return;
	}
	inline void AddTagDiscretionRoundDirection() {
		*((DWORD*)this->currentPos) = 0x00343438; this->currentPos += 3; // 844
		return;
	}
	inline void AddTagDiscretionPrice() {
		*((DWORD*)this->currentPos) = 0x00353438; this->currentPos += 3; // 845
		return;
	}
	inline void AddTagDiscretionScope() {
		*((DWORD*)this->currentPos) = 0x00363438; this->currentPos += 3; // 846
		return;
	}
	inline void AddTagTargetStrategy() {
		*((DWORD*)this->currentPos) = 0x00373438; this->currentPos += 3; // 847
		return;
	}
	inline void AddTagTargetStrategyParameters() {
		*((DWORD*)this->currentPos) = 0x00383438; this->currentPos += 3; // 848
		return;
	}
	inline void AddTagParticipationRate() {
		*((DWORD*)this->currentPos) = 0x00393438; this->currentPos += 3; // 849
		return;
	}
	inline void AddTagTargetStrategyPerformance() {
		*((DWORD*)this->currentPos) = 0x00303538; this->currentPos += 3; // 850
		return;
	}
	inline void AddTagLastLiquidityInd() {
		*((DWORD*)this->currentPos) = 0x00313538; this->currentPos += 3; // 851
		return;
	}
	inline void AddTagPublishTrdIndicator() {
		*((DWORD*)this->currentPos) = 0x00323538; this->currentPos += 3; // 852
		return;
	}
	inline void AddTagShortSaleReason() {
		*((DWORD*)this->currentPos) = 0x00333538; this->currentPos += 3; // 853
		return;
	}
	inline void AddTagQtyType() {
		*((DWORD*)this->currentPos) = 0x00343538; this->currentPos += 3; // 854
		return;
	}
	inline void AddTagSecondaryTrdType() {
		*((DWORD*)this->currentPos) = 0x00353538; this->currentPos += 3; // 855
		return;
	}
	inline void AddTagTradeReportType() {
		*((DWORD*)this->currentPos) = 0x00363538; this->currentPos += 3; // 856
		return;
	}
	inline void AddTagAllocNoOrdersType() {
		*((DWORD*)this->currentPos) = 0x00373538; this->currentPos += 3; // 857
		return;
	}
	inline void AddTagSharedCommission() {
		*((DWORD*)this->currentPos) = 0x00383538; this->currentPos += 3; // 858
		return;
	}
	inline void AddTagConfirmReqID() {
		*((DWORD*)this->currentPos) = 0x00393538; this->currentPos += 3; // 859
		return;
	}
	inline void AddTagAvgParPx() {
		*((DWORD*)this->currentPos) = 0x00303638; this->currentPos += 3; // 860
		return;
	}
	inline void AddTagReportedPx() {
		*((DWORD*)this->currentPos) = 0x00313638; this->currentPos += 3; // 861
		return;
	}
	inline void AddTagNoCapacities() {
		*((DWORD*)this->currentPos) = 0x00323638; this->currentPos += 3; // 862
		return;
	}
	inline void AddTagOrderCapacityQty() {
		*((DWORD*)this->currentPos) = 0x00333638; this->currentPos += 3; // 863
		return;
	}
	inline void AddTagNoEvents() {
		*((DWORD*)this->currentPos) = 0x00343638; this->currentPos += 3; // 864
		return;
	}
	inline void AddTagEventType() {
		*((DWORD*)this->currentPos) = 0x00353638; this->currentPos += 3; // 865
		return;
	}
	inline void AddTagEventDate() {
		*((DWORD*)this->currentPos) = 0x00363638; this->currentPos += 3; // 866
		return;
	}
	inline void AddTagEventPx() {
		*((DWORD*)this->currentPos) = 0x00373638; this->currentPos += 3; // 867
		return;
	}
	inline void AddTagEventText() {
		*((DWORD*)this->currentPos) = 0x00383638; this->currentPos += 3; // 868
		return;
	}
	inline void AddTagPctAtRisk() {
		*((DWORD*)this->currentPos) = 0x00393638; this->currentPos += 3; // 869
		return;
	}
	inline void AddTagNoInstrAttrib() {
		*((DWORD*)this->currentPos) = 0x00303738; this->currentPos += 3; // 870
		return;
	}
	inline void AddTagInstrAttribType() {
		*((DWORD*)this->currentPos) = 0x00313738; this->currentPos += 3; // 871
		return;
	}
	inline void AddTagInstrAttribValue() {
		*((DWORD*)this->currentPos) = 0x00323738; this->currentPos += 3; // 872
		return;
	}
	inline void AddTagDatedDate() {
		*((DWORD*)this->currentPos) = 0x00333738; this->currentPos += 3; // 873
		return;
	}
	inline void AddTagInterestAccrualDate() {
		*((DWORD*)this->currentPos) = 0x00343738; this->currentPos += 3; // 874
		return;
	}
	inline void AddTagCPProgram() {
		*((DWORD*)this->currentPos) = 0x00353738; this->currentPos += 3; // 875
		return;
	}
	inline void AddTagCPRegType() {
		*((DWORD*)this->currentPos) = 0x00363738; this->currentPos += 3; // 876
		return;
	}
	inline void AddTagUnderlyingCPProgram() {
		*((DWORD*)this->currentPos) = 0x00373738; this->currentPos += 3; // 877
		return;
	}
	inline void AddTagUnderlyingCPRegType() {
		*((DWORD*)this->currentPos) = 0x00383738; this->currentPos += 3; // 878
		return;
	}
	inline void AddTagUnderlyingQty() {
		*((DWORD*)this->currentPos) = 0x00393738; this->currentPos += 3; // 879
		return;
	}
	inline void AddTagTrdMatchID() {
		*((DWORD*)this->currentPos) = 0x00303838; this->currentPos += 3; // 880
		return;
	}
	inline void AddTagSecondaryTradeReportRefID() {
		*((DWORD*)this->currentPos) = 0x00313838; this->currentPos += 3; // 881
		return;
	}
	inline void AddTagUnderlyingDirtyPrice() {
		*((DWORD*)this->currentPos) = 0x00323838; this->currentPos += 3; // 882
		return;
	}
	inline void AddTagUnderlyingEndPrice() {
		*((DWORD*)this->currentPos) = 0x00333838; this->currentPos += 3; // 883
		return;
	}
	inline void AddTagUnderlyingStartValue() {
		*((DWORD*)this->currentPos) = 0x00343838; this->currentPos += 3; // 884
		return;
	}
	inline void AddTagUnderlyingCurrentValue() {
		*((DWORD*)this->currentPos) = 0x00353838; this->currentPos += 3; // 885
		return;
	}
	inline void AddTagUnderlyingEndValue() {
		*((DWORD*)this->currentPos) = 0x00363838; this->currentPos += 3; // 886
		return;
	}
	inline void AddTagNoUnderlyingStips() {
		*((DWORD*)this->currentPos) = 0x00373838; this->currentPos += 3; // 887
		return;
	}
	inline void AddTagUnderlyingStipType() {
		*((DWORD*)this->currentPos) = 0x00383838; this->currentPos += 3; // 888
		return;
	}
	inline void AddTagUnderlyingStipValue() {
		*((DWORD*)this->currentPos) = 0x00393838; this->currentPos += 3; // 889
		return;
	}
	inline void AddTagMaturityNetMoney() {
		*((DWORD*)this->currentPos) = 0x00303938; this->currentPos += 3; // 890
		return;
	}
	inline void AddTagMiscFeeBasis() {
		*((DWORD*)this->currentPos) = 0x00313938; this->currentPos += 3; // 891
		return;
	}
	inline void AddTagTotNoAllocs() {
		*((DWORD*)this->currentPos) = 0x00323938; this->currentPos += 3; // 892
		return;
	}
	inline void AddTagLastFragment() {
		*((DWORD*)this->currentPos) = 0x00333938; this->currentPos += 3; // 893
		return;
	}
	inline void AddTagCollReqID() {
		*((DWORD*)this->currentPos) = 0x00343938; this->currentPos += 3; // 894
		return;
	}
	inline void AddTagCollAsgnReason() {
		*((DWORD*)this->currentPos) = 0x00353938; this->currentPos += 3; // 895
		return;
	}
	inline void AddTagCollInquiryQualifier() {
		*((DWORD*)this->currentPos) = 0x00363938; this->currentPos += 3; // 896
		return;
	}
	inline void AddTagNoTrades() {
		*((DWORD*)this->currentPos) = 0x00373938; this->currentPos += 3; // 897
		return;
	}
	inline void AddTagMarginRatio() {
		*((DWORD*)this->currentPos) = 0x00383938; this->currentPos += 3; // 898
		return;
	}
	inline void AddTagMarginExcess() {
		*((DWORD*)this->currentPos) = 0x00393938; this->currentPos += 3; // 899
		return;
	}
	inline void AddTagTotalNetValue() {
		*((DWORD*)this->currentPos) = 0x00303039; this->currentPos += 3; // 900
		return;
	}
	inline void AddTagCashOutstanding() {
		*((DWORD*)this->currentPos) = 0x00313039; this->currentPos += 3; // 901
		return;
	}
	inline void AddTagCollAsgnID() {
		*((DWORD*)this->currentPos) = 0x00323039; this->currentPos += 3; // 902
		return;
	}
	inline void AddTagCollAsgnTransType() {
		*((DWORD*)this->currentPos) = 0x00333039; this->currentPos += 3; // 903
		return;
	}
	inline void AddTagCollRespID() {
		*((DWORD*)this->currentPos) = 0x00343039; this->currentPos += 3; // 904
		return;
	}
	inline void AddTagCollAsgnRespType() {
		*((DWORD*)this->currentPos) = 0x00353039; this->currentPos += 3; // 905
		return;
	}
	inline void AddTagCollAsgnRejectReason() {
		*((DWORD*)this->currentPos) = 0x00363039; this->currentPos += 3; // 906
		return;
	}
	inline void AddTagCollAsgnRefID() {
		*((DWORD*)this->currentPos) = 0x00373039; this->currentPos += 3; // 907
		return;
	}
	inline void AddTagCollRptID() {
		*((DWORD*)this->currentPos) = 0x00383039; this->currentPos += 3; // 908
		return;
	}
	inline void AddTagCollInquiryID() {
		*((DWORD*)this->currentPos) = 0x00393039; this->currentPos += 3; // 909
		return;
	}
	inline void AddTagCollStatus() {
		*((DWORD*)this->currentPos) = 0x00303139; this->currentPos += 3; // 910
		return;
	}
	inline void AddTagTotNumReports() {
		*((DWORD*)this->currentPos) = 0x00313139; this->currentPos += 3; // 911
		return;
	}
	inline void AddTagLastRptRequested() {
		*((DWORD*)this->currentPos) = 0x00323139; this->currentPos += 3; // 912
		return;
	}
	inline void AddTagAgreementDesc() {
		*((DWORD*)this->currentPos) = 0x00333139; this->currentPos += 3; // 913
		return;
	}
	inline void AddTagAgreementID() {
		*((DWORD*)this->currentPos) = 0x00343139; this->currentPos += 3; // 914
		return;
	}
	inline void AddTagAgreementDate() {
		*((DWORD*)this->currentPos) = 0x00353139; this->currentPos += 3; // 915
		return;
	}
	inline void AddTagStartDate() {
		*((DWORD*)this->currentPos) = 0x00363139; this->currentPos += 3; // 916
		return;
	}
	inline void AddTagEndDate() {
		*((DWORD*)this->currentPos) = 0x00373139; this->currentPos += 3; // 917
		return;
	}
	inline void AddTagAgreementCurrency() {
		*((DWORD*)this->currentPos) = 0x00383139; this->currentPos += 3; // 918
		return;
	}
	inline void AddTagDeliveryType() {
		*((DWORD*)this->currentPos) = 0x00393139; this->currentPos += 3; // 919
		return;
	}
	inline void AddTagEndAccruedInterestAmt() {
		*((DWORD*)this->currentPos) = 0x00303239; this->currentPos += 3; // 920
		return;
	}
	inline void AddTagStartCash() {
		*((DWORD*)this->currentPos) = 0x00313239; this->currentPos += 3; // 921
		return;
	}
	inline void AddTagEndCash() {
		*((DWORD*)this->currentPos) = 0x00323239; this->currentPos += 3; // 922
		return;
	}
	inline void AddTagUserRequestID() {
		*((DWORD*)this->currentPos) = 0x00333239; this->currentPos += 3; // 923
		return;
	}
	inline void AddTagUserRequestType() {
		*((DWORD*)this->currentPos) = 0x00343239; this->currentPos += 3; // 924
		return;
	}
	inline void AddTagNewPassword() {
		*((DWORD*)this->currentPos) = 0x00353239; this->currentPos += 3; // 925
		return;
	}
	inline void AddTagUserStatus() {
		*((DWORD*)this->currentPos) = 0x00363239; this->currentPos += 3; // 926
		return;
	}
	inline void AddTagUserStatusText() {
		*((DWORD*)this->currentPos) = 0x00373239; this->currentPos += 3; // 927
		return;
	}
	inline void AddTagStatusValue() {
		*((DWORD*)this->currentPos) = 0x00383239; this->currentPos += 3; // 928
		return;
	}
	inline void AddTagStatusText() {
		*((DWORD*)this->currentPos) = 0x00393239; this->currentPos += 3; // 929
		return;
	}
	inline void AddTagRefCompID() {
		*((DWORD*)this->currentPos) = 0x00303339; this->currentPos += 3; // 930
		return;
	}
	inline void AddTagRefSubID() {
		*((DWORD*)this->currentPos) = 0x00313339; this->currentPos += 3; // 931
		return;
	}
	inline void AddTagNetworkResponseID() {
		*((DWORD*)this->currentPos) = 0x00323339; this->currentPos += 3; // 932
		return;
	}
	inline void AddTagNetworkRequestID() {
		*((DWORD*)this->currentPos) = 0x00333339; this->currentPos += 3; // 933
		return;
	}
	inline void AddTagLastNetworkResponseID() {
		*((DWORD*)this->currentPos) = 0x00343339; this->currentPos += 3; // 934
		return;
	}
	inline void AddTagNetworkRequestType() {
		*((DWORD*)this->currentPos) = 0x00353339; this->currentPos += 3; // 935
		return;
	}
	inline void AddTagNoCompIDs() {
		*((DWORD*)this->currentPos) = 0x00363339; this->currentPos += 3; // 936
		return;
	}
	inline void AddTagNetworkStatusResponseType() {
		*((DWORD*)this->currentPos) = 0x00373339; this->currentPos += 3; // 937
		return;
	}
	inline void AddTagNoCollInquiryQualifier() {
		*((DWORD*)this->currentPos) = 0x00383339; this->currentPos += 3; // 938
		return;
	}
	inline void AddTagTrdRptStatus() {
		*((DWORD*)this->currentPos) = 0x00393339; this->currentPos += 3; // 939
		return;
	}
	inline void AddTagAffirmStatus() {
		*((DWORD*)this->currentPos) = 0x00303439; this->currentPos += 3; // 940
		return;
	}
	inline void AddTagUnderlyingStrikeCurrency() {
		*((DWORD*)this->currentPos) = 0x00313439; this->currentPos += 3; // 941
		return;
	}
	inline void AddTagLegStrikeCurrency() {
		*((DWORD*)this->currentPos) = 0x00323439; this->currentPos += 3; // 942
		return;
	}
	inline void AddTagTimeBracket() {
		*((DWORD*)this->currentPos) = 0x00333439; this->currentPos += 3; // 943
		return;
	}
	inline void AddTagCollAction() {
		*((DWORD*)this->currentPos) = 0x00343439; this->currentPos += 3; // 944
		return;
	}
	inline void AddTagCollInquiryStatus() {
		*((DWORD*)this->currentPos) = 0x00353439; this->currentPos += 3; // 945
		return;
	}
	inline void AddTagCollInquiryResult() {
		*((DWORD*)this->currentPos) = 0x00363439; this->currentPos += 3; // 946
		return;
	}
	inline void AddTagStrikeCurrency() {
		*((DWORD*)this->currentPos) = 0x00373439; this->currentPos += 3; // 947
		return;
	}
	inline void AddTagNoNested3PartyIDs() {
		*((DWORD*)this->currentPos) = 0x00383439; this->currentPos += 3; // 948
		return;
	}
	inline void AddTagNested3PartyID() {
		*((DWORD*)this->currentPos) = 0x00393439; this->currentPos += 3; // 949
		return;
	}
	inline void AddTagNested3PartyIDSource() {
		*((DWORD*)this->currentPos) = 0x00303539; this->currentPos += 3; // 950
		return;
	}
	inline void AddTagNested3PartyRole() {
		*((DWORD*)this->currentPos) = 0x00313539; this->currentPos += 3; // 951
		return;
	}
	inline void AddTagNoNested3PartySubIDs() {
		*((DWORD*)this->currentPos) = 0x00323539; this->currentPos += 3; // 952
		return;
	}
	inline void AddTagNested3PartySubID() {
		*((DWORD*)this->currentPos) = 0x00333539; this->currentPos += 3; // 953
		return;
	}
	inline void AddTagNested3PartySubIDType() {
		*((DWORD*)this->currentPos) = 0x00343539; this->currentPos += 3; // 954
		return;
	}
	inline void AddTagLegContractSettlMonth() {
		*((DWORD*)this->currentPos) = 0x00353539; this->currentPos += 3; // 955
		return;
	}
	inline void AddTagLegInterestAccrualDate() {
		*((DWORD*)this->currentPos) = 0x00363539; this->currentPos += 3; // 956
		return;
	}
#pragma endregion
	
public:
	FixProtocolManager(FixProtocolHistoryManager *historyManager);
	~FixProtocolManager();

	inline void StartNewMessage() {
		this->currentPos = this->MessageCore();
		*(this->currentPos) = '\0';
	}

	inline void ResetMessageSequenceNumber() { this->SetMessageSequenceNumber(1); }
	inline void SetMessageSequenceNumber(int value) { this->messageSequenceNumber = value; }
	inline void IncMessageSequenceNumber() { this->messageSequenceNumber++; }

	inline void AddArray(char *string, int length) {
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
		AddTagBeginString(); 
		AddEqual();
		AddArray((char*)FixProtocolVersion, 7);
		AddSeparator();
	}

	inline void AddBodyLength() {
		AddTagBodyLength(); 
		AddEqual();
		AddZeroSymbols(3);
		AddSeparator();
	}

	inline void AddZeroSymbols(int count) {
		this->currentPos += count;
	}

	inline void AddMessageType(char messageType) {
		AddTagMsgType();
		AddEqual();
		AddSymbol(messageType);
		AddSeparator();
	}

	inline void AddSenderComputerId() {
		AddTagSenderCompID();
		AddEqual();
		AddArray(this->senderComputerId, this->senderComputerIdLength);
		AddSeparator();
	}

	inline void AddTargetComputerId() {
		AddTagTargetCompID();
		AddEqual();
		AddArray(this->targetComputerId, this->targetComputerIdLength);
		AddSeparator();
	}

	inline void AddMessageSeqNumber(int messageSeqNumber) {
		AddTagMsgSeqNum();
		AddEqual();
		AddValue(messageSeqNumber);
		AddSeparator();
	}

	private: UTCTimeConverter *timeConverter;

	public:
	inline int GetUTCTimeString(char *buf) {
		int length = 0;
		char *savedBuf = buf;

		//TODO

		return this->timeConverter->ToString(buf, this->currentTime);
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

	inline void AddStringZero() { *(this->currentPos) = '\0'; }
	
	inline int		MaxMessageLength() { return 4192; }
private:	
	inline int		MessageLengthCore() { return this->currentPos - this->MessageCore(); }
	inline char*	MessageCore() { return this->historyManager->Buffer(); }
public:
	inline char*	Message() { return this->messageBuffer; }
	inline int		MessageLength() { return this->messageLength; }
	

	inline void AddSendingTime() {
		AddTagSendingTime(); AddEqual();
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
		InToString(&this->MessageCore()[HeaderTagLength + 2], MessageLengthCore() - HeaderTagLength - MessageLengthLength, 3);
	}

	inline void AddHeader(char messageType) {
		AddHeader(messageType, false);
	}

	inline void AddHeader(char messageType, bool possResend) {
		ResetMessage();
		ResetTagValueList();
		AddFixHeader();
		AddBodyLength();
		AddMessageType(messageType);
		AddSenderComputerId();
		AddTargetComputerId();
		AddMessageSeqNumber(this->messageSequenceNumber);
		if (possResend) {
			AddTagPossResend(); AddEqual(); AddValue('Y');
		}
		AddSendingTime();
	}

	inline int CalcCheckSum() {
		int sum = 0;
		char *buf = this->MessageCore();
		int length = this->currentPos - this->MessageCore();
		*((int*)this->currentPos) = 0;
		for (int i = 0; i < length; i++, buf++)
			sum += (unsigned int)*buf;
		return sum & 0xff;
	}

	inline void AddCheckSum() {
		int checkSum = CalcCheckSum();
		AddTagCheckSum();
		AddEqual();
		AddValue(checkSum, 3);
		AddSeparator();
	}

	inline void AddTrail() {
		AddCheckSum();
	}

	inline void AddTestRequestId(int testRequestId) {
		AddTagTestReqID();
		AddEqual();
		AddValue(testRequestId);
	}

	inline void ResetMessage() { 
		this->messageBuffer = this->MessageCore();
		this->messageLength = 0;
		this->currentPos = this->MessageCore(); 
	}

	inline void IncrementBuffer() { 
		this->messageLength = this->MessageLengthCore();
		this->historyManager->Increment(this->MessageLengthCore() + 1, FixMessage);
	}

	inline void CreateHearthBeatMessage() {
		AddHeader(MsgTypeHearthBeat);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
	}

	inline void CreateHearthBeatMessage(int testRequestId) {
		AddHeader(MsgTypeHearthBeat);
		AddTestRequestId(testRequestId);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
	}

	inline void CreateTestRequestMessage(int testRequestId) {
		AddHeader(MsgTypeTestRequest);
		AddTestRequestId(testRequestId);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
	}

	inline void CreateResendRequestMessage(int start, int end) {
		AddHeader(MsgTypeResendRequest);
		AddTagValue(AddTagBeginSeqNo, start);
		AddTagValue(AddTagEndSeqNo, end);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
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
		IncrementBuffer();
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
		AddTagYield();
		AddEqual();
		AddFloatValue(percentage);
		AddSeparator();
	}

	inline void AddGroupParties(FixPartyListInfo *info) { 
		AddTagNoPartyIDs();
		AddEqual();
		AddValue(info->Count);
		for (int i = 0; i < info->Count; i++) { 
			AddSeparator();
			AddTagPartyID();
			AddEqual(); 
			AddArray(info->Parties[i].ID, info->Parties[i].IDLength);
			AddSeparator();
			AddTagPartyIDSource();
			AddEqual();
			AddValue(info->Parties[i].IDSource);
			AddSeparator();
			AddTagPartyRole();
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
		AddTagNoTrdRegTimestamps();
		AddEqual();
		AddValue(count);
		for (int i = 0; i < count; i++) {
			AddSeparator();
			AddTagTrdRegTimestamp();
			AddEqual();
			AddFullDateTimeValue(&st[i]);
			AddSeparator();
			AddTagTrdRegTimestampType();
			AddEqual();
			AddValue(type[i]);
		}
		AddSeparator();
	}

	inline void AddGroupFinancingDetails(SYSTEMTIME *start, SYSTEMTIME *end, int deliveryType) { 
		AddTagStartDate();	
		AddEqual();
		AddDateValue(start);
		AddSeparator();
		AddTagEndDate();
		AddEqual();
		AddDateValue(end);
		AddSeparator();
		AddTagDeliveryType();
		AddEqual();
		AddValue(deliveryType);
		AddSeparator();
	}

	inline void AddGroupUnderlyingInstrument(UnderlyingSymbolInfo *info) {
		if (info->SymbolLength != 0) {
			AddTagUnderlyingSymbol();
			AddEqual();
			AddArray(info->Symbol, info->SymbolLength);
			AddSeparator();
		}
		if (info->SymbolSfxLength != 0) {
			AddTagUnderlyingSymbolSfx();
			AddEqual();
			AddArray(info->SymbolSfx, info->SymbolSfxLength);
			AddSeparator();
		}
		if (info->SecurityIdLength != 0) {
			AddTagUnderlyingSecurityID();
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
		AddTagNoUnderlyingStips();
		AddEqual();
		AddValue(count);
		AddSeparator();
		for (int i = 0; i < count; i++) {
			AddSeparator();
			AddTagUnderlyingStipType();
			AddEqual();
			AddArray(list->StipType, list->StipTypeLength);
			AddSeparator();
			AddTagUnderlyingStipValue();
			AddEqual();
			AddArray(list->StipValue, list->StipValueLength);
			list++;
		}
		AddSeparator();
	}
	
#pragma region Additional MOEX Tags
	const char* TagSessionStatus = "1409";
	inline void AddTagSessionStatus() {
		*((DWORD*)this->currentPos) = 0x39303431; this->currentPos += 4; // 1409
		return;
	}
	const char* TagCancelOnDisconnect = "6867";
	inline void AddTagCancelOnDisconnect() {
		*((DWORD*)this->currentPos) = 0x37363836; this->currentPos += 4; // 6867
		return;
	}
	const char* TagLanguageID = "6936";
	inline void AddTagTagLanguageID() {
		*((DWORD*)this->currentPos) = 0x36333936; this->currentPos += 4; // 6936
		return;
	}

	const char* TagTradeThruTime = "5202";
	inline void AddTagTradeThruTime() {
		*((DWORD*)this->currentPos) = 0x32303235; this->currentPos += 4; // 5202
		return;
	}

	const char* TagMaxPriceLevels = "1090";
	inline void AddTagMaxPriceLevels() {
		*((DWORD*)this->currentPos) = 0x30393031; this->currentPos += 4; // 1090
		return;
	}

	const char* TagCancelOrigOnReject = "9619";
	inline void AddTagCancelOrigOnReject() {
		*((DWORD*)this->currentPos) = 0x39313639; this->currentPos += 4; // 9619
		return;
	}

#pragma endregion

	inline void AddGroupLogon(FixLogonInfo *info) {
		AddTagEncryptMethod();
		AddEqual();
		AddValue(info->EncryptionType);	// must be zero not supported by MOEX
		AddSeparator();
		
		AddTagHeartBtInt();
		AddEqual();
		AddValue(info->HearthBtInt);
		AddSeparator();
		
		AddTagResetSeqNumFlag();
		AddEqual();
		AddValue(info->ShouldResetSeqNum);
		AddSeparator();

		AddTagPassword();
		AddEqual();
		AddArray(info->Password, info->PassLength);
		AddSeparator();

		if (info->NewPassLength > 0) {
			AddTagNewPassword();
			AddEqual();
			AddArray(info->NewPassword, info->NewPassLength);
			AddSeparator();
		}

		if (info->AllowSessionStatus) {
			AddTagSessionStatus();
			AddEqual();
			AddValue((int)info->SessionStatus);
			AddSeparator();
		}

		if (info->CancelOnDisconnect) {
			AddTagCancelOnDisconnect();
			AddEqual();
			AddSymbol('A');
			AddSeparator();
		}

		if (info->LanguageId != 0) {
			AddTagTagLanguageID();
			AddEqual();
			AddSymbol(info->LanguageId);
			AddSeparator();
		}
	}

	inline void CreateLogonMessage(FixLogonInfo *logon) {
		this->messageSequenceNumber = logon->MsgStartSeqNo;
		this->SetSenderComputerId(logon->SenderCompID);
		AddHeader(MsgTypeLogon);
		AddGroupLogon(logon);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
	}

	inline void CreateLogoutMessage(char *text, int textLength) { 
		AddHeader(MsgTypeLogout);
		if (text != NULL) {
			AddTagText();
			AddEqual();
			AddArray(text, textLength);
			AddSeparator();
		}
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
	}

	inline void CreateOrderStatusRequestMessage(FixOrderStatusRequestInfo *info) {
		AddHeader(MsgTypeOrderStatusRequest);
		AddTagString2(AddTagOrderID, info->OrderId, info->OrderIdLength);
		AddTagString2(AddTagClOrdID, info->CiOrdId, info->CiOrdIdLength);
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
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
		IncrementBuffer();
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
		IncrementBuffer();
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
		IncrementBuffer();
	}

	inline void CreateSecurityDefinitionRequestMessage(char *securityReqId, int securityReqIdLength, FixSecurityRequestType requestType) {
		AddHeader(MsgTypeSecurityDefinitionRequest);

		AddTagString2(AddTagSecurityReqID, securityReqId, securityReqIdLength);
		AddTagValue(AddTagSecurityRequestType, (int)requestType);
		
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
	}

	inline void CreateSecurityListRequestMessage(char *securityReqId, int securityReqIdLength, FixSecurityListRequestType requestType) {
		AddHeader(MsgTypeSecurityListRequest);

		AddTagString2(AddTagSecurityReqID, securityReqId, securityReqIdLength);
		AddTagValue(AddTagSecurityListRequestType, (int)requestType);
		
		UpdateLengthTagValue();
		AddTrail();
		AddStringZero();
		IncrementBuffer();
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
		IncrementBuffer();
	}
	inline void ResetTagValueList() { this->tagValueItemsCount = 0; }
	inline FixTagValueInfo* TagValueList() { return this->tagValueList; }
	inline int TagValuesCount() { return this->tagValueItemsCount; }
	inline int ReadValue(char *buffer, int *outValue, char stopSymbol) { 
		return this->intConverter->FromStringFast(buffer, outValue, stopSymbol);
	}
	inline int ReadValuePredict34(char *buffer, int* outValue, char stopSymbol) { 
		if (buffer[4] == stopSymbol) {
			*outValue = this->intConverter->From3SymbolUnsigned(buffer);
			return 3;
		}
		if (buffer[5] == stopSymbol) { 
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

	inline bool CheckFixHeader(char *buffer, int *outLength) { 
		int tag = Read1SymbolTag(buffer); 
		buffer++;
		
		if (*buffer != '=' || tag != TagBeginString)
			return false;
		
		if (*((int*)buffer) != *((int*)this->FixProtocolVersion))
			return false;
		
		buffer += 4 + 3;
		if (*buffer != FIX_SEPARATOR)
			return false;

		*outLength = 1 + 1 + 7 + 1;
		return true;
	}

	inline bool ProcessMessageLengthTag(char *buffer, int *outLength) {
		int tag = Read1SymbolTag(buffer);
		buffer++;

		if (*buffer != '=' || tag != TagBodyLength)
			return false;
		
		int length = ReadValuePredict34(buffer, &this->receivedMessageLength, FIX_SEPARATOR);
		*outLength = length + 1;
		
		return true;
	}

	inline bool ProcessCheckHeader(char *buffer, int *outLength) { 
		int length = 0;
		if (!CheckFixHeader(buffer, &length)) {
			AddLog(FixDcCheckFixVersion, FixDcFailed);
			return false;
		}
		AddLog(FixDcCheckFixVersion, FixDcSuccess);
		buffer += length;
		*outLength = (*outLength) + length;
	
		if (!ProcessMessageLengthTag(buffer, &length)) { 
			AddLog(FixDcProcessMessageBodyLen, FixDcFailed);
			return false;
		}
		AddLog(FixDcProcessMessageBodyLen, FixDcSuccess);
		buffer += length;
		*outLength = (*outLength) + length;

		return true;
	}
};

