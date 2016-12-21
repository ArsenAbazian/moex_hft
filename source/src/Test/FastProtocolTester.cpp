#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include <limits.h>
#include "FastProtocolManager.h"
#include "Test/FastProtocolTester.h"
#include <sys/time.h>
#include <Lib/StringIdComparer.h>

FastProtocolTester::FastProtocolTester()
{
}


FastProtocolTester::~FastProtocolTester()
{
}

void FastProtocolTester::TestMessages() {
    FastProtocolManager *manager = new FastProtocolManager();

    unsigned char *message = new unsigned char[182] {
            0x4f, 0x9f, 0x03, 0x00, 0xc0, 0x13, 0xdb, 0x0e, 0x3e, 0xcf,
            0x02, 0x15, 0x55, 0x15, 0x12, 0x1c, 0x55, 0x88, 0x83, 0x83,
            0xb1, 0x80, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30, 0x4a,
            0x56, 0x56, 0x4c, 0xb4, 0x15, 0x80, 0xfe, 0x00, 0x5b, 0xc5,
            0x81, 0x20, 0xf8, 0x80, 0x80, 0x80, 0xc3, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x45, 0x51, 0x44,
            0xc2, 0x80, 0x82, 0xf7, 0x80, 0x52, 0x55, 0x30, 0x30, 0x30,
            0x41, 0x30, 0x4a, 0x56, 0x56, 0x4c, 0xb4, 0x15, 0x81, 0x80,
            0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x45, 0x51, 0x44, 0xc2,
            0x80, 0x83, 0xea, 0x80, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41,
            0x30, 0x4a, 0x56, 0x56, 0x4c, 0xb4, 0x15, 0x82, 0xfe, 0x00,
            0x5b, 0xc5, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x45, 0x51, 0x44,
            0xc2, 0xce
    };

    manager->SetNewBuffer(message, 225);
    int msgSeqNo = manager->ReadMsgSeqNumber();
    FastIncrementalMSRFONDInfo *msr = (FastIncrementalMSRFONDInfo*)manager->Decode();
    manager->PrintIncrementalMSRFOND(msr);

    if(msr->GroupMDEntries[0]->MDUpdateAction != MDUpdateAction::mduaDelete)
        throw;
    if(msr->GroupMDEntries[0]->MDEntryType[0] != MDEntryType::mdetSellQuote)
        throw;
    if(msr->GroupMDEntries[0]->MDEntryID[0] != '\0')
        throw;
    if(!StringIdComparer::Equal(msr->GroupMDEntries[0]->Symbol, msr->GroupMDEntries[0]->SymbolLength, "RU000A0JVVL4", 12))
        throw;
    if(msr->GroupMDEntries[0]->RptSeq != 2687)
        throw;
    if(msr->GroupMDEntries[0]->QuoteCondition[0] != 'C')
        throw;
    if(msr->GroupMDEntries[0]->QuoteConditionLength != 1)
        throw;
    if(!StringIdComparer::Equal(msr->GroupMDEntries[0]->TradingSessionID, msr->GroupMDEntries[0]->TradingSessionIDLength, "EQDB", 4))
        throw;

    message = new unsigned char[18] {
            0x4c, 0x9f, 0x03, 0x00, 0xc0, 0x10, 0xbc, 0x0e, 0x3e, 0xcc,
            0x02, 0x15, 0x55, 0x15, 0x10, 0x77, 0x61, 0x90
    };
    manager->SetNewBuffer(message, 18);
    msgSeqNo = manager->ReadMsgSeqNumber();
    FastHeartbeatInfo *hb = (FastHeartbeatInfo*)manager->Decode();
    manager->PrintHeartbeat(hb);

    message = new unsigned char[225] {
            0x8d, 0x23, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x47, 0x8d, 0x23,
            0x68, 0x05, 0x17, 0x15, 0x66, 0x29, 0xad, 0x00, 0x5e, 0xed,
            0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30, 0x4a, 0x55, 0x36,
            0x4e, 0xb4, 0x8d, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30,
            0x4a, 0x55, 0x36, 0x4e, 0x34, 0x82, 0x34, 0x8c, 0x87, 0x44,
            0x42, 0x58, 0x58, 0x58, 0x58, 0x85, 0x4d, 0x55, 0x4e, 0x49,
            0x09, 0x4f, 0x5f, 0xc1, 0x09, 0x4e, 0x42, 0xb8, 0x80, 0x87,
            0x83, 0x09, 0x4e, 0x43, 0x95, 0xf0, 0x31, 0x4d, 0x76, 0x4e,
            0x13, 0x51, 0xba, 0x80, 0x80, 0x92, 0x4b, 0x6f, 0x73, 0x74,
            0x72, 0x6f, 0x6d, 0x61, 0x20, 0x72, 0x65, 0x67, 0x2e, 0x2d,
            0x30, 0x30, 0x37, 0xaa, 0xd0, 0x9a, 0xd0, 0xbe, 0xd1, 0x81,
            0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xbe, 0xd0, 0xbc, 0xd1, 0x81,
            0xd0, 0xba, 0xd0, 0xb0, 0xd1, 0x8f, 0x20, 0xd0, 0xbe, 0xd0,
            0xb1, 0xd0, 0xbb, 0x2e, 0x20, 0xd0, 0xb2, 0xd1, 0x8b, 0xd0,
            0xbf, 0x2e, 0x30, 0x30, 0x37, 0x80, 0x83, 0x9b, 0x82, 0x34,
            0x88, 0x83, 0x39, 0x31, 0x52, 0x55, 0xc2, 0x82, 0x81, 0x81,
            0x82, 0x52, 0x50, 0x4d, 0xcf, 0x4e, 0xc1, 0x93, 0x82, 0x52,
            0x55, 0xc2, 0x82, 0x52, 0x55, 0x33, 0x34, 0x30, 0x30, 0x37,
            0x4b, 0x4f, 0x53, 0xb0, 0x94, 0xd0, 0x9a, 0xd0, 0xbe, 0xd1,
            0x81, 0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xbe, 0xd0, 0xbc, 0xd0,
            0x9e, 0xd0, 0xb1, 0x37, 0x84, 0x52, 0x50, 0x53, 0xfc, 0x81,
            0x80, 0x80, 0x80, 0x80, 0x82, 0xb7, 0x80, 0x80, 0x80, 0x80,
            0x87, 0x84, 0x80, 0x80, 0x80
    };

    manager->SetNewBuffer(message, 225);
    msgSeqNo = manager->ReadMsgSeqNumber();
    FastSecurityDefinitionInfo *sd = (FastSecurityDefinitionInfo*)manager->Decode();
    manager->PrintSecurityDefinition(sd);
    if(manager->MessageLength() != 225)
        throw;
    if(!CompareStrings(sd->StateSecurityID, "RU34007KOS0"))
        throw;
    if(sd->SettlDate != 20160823)
        throw;

    if(sd->FaceValue.Mantissa != 55 || sd->FaceValue.Exponent != 1)
        throw;
    if(sd->NoSharesIssued.Mantissa != 4 || sd->NoSharesIssued.Exponent != 6)
        throw;
    manager->PrintSecurityDefinition(sd);

	message = new unsigned char[111] {0x04,0xa4,0x07,0x00,0xe0,0x1b,0xb8,0x1e,0x48,0x84,
                                                     0x23,0x68,0x05,0x07,0x7a,0x6e,0x66,0xdc,0x82,0x81,
                                                     0xb0,0x42,0x30,0x30,0x30,0x37,0x37,0x38,0x38,0x37,
                                                     0xb5,0x45,0x55,0x52,0x5f,0x52,0x55,0x42,0x5f,0x5f,
                                                     0x54,0x4f,0xcd,0x10,0x3e,0x8f,0xfc,0x2f,0x44,0xfb,
                                                     0x81,0x02,0xc8,0x43,0x6d,0x65,0xa1,0x29,0x56,0xfe,
                                                     0x43,0x45,0x54,0xd3,0x80,0x82,0xb1,0x53,0x30,0x30,
                                                     0x30,0x38,0x31,0x36,0x37,0x37,0xb5,0x45,0x55,0x52,
                                                     0x5f,0x52,0x55,0x42,0x5f,0x5f,0x54,0x4f,0xcd,0x10,
                                                     0x3e,0x90,0xfc,0x31,0x6d,0x87,0x81,0x09,0xf4,0x43,
                                                     0x6d,0x65,0xa1,0x2a,0x0a,0xb7,0x43,0x45,0x54,0xd3,0x80};


    manager->SetNewBuffer(message, 111);
    msgSeqNo = manager->ReadMsgSeqNumber();
    FastIncrementalOBRCURRInfo *info = (FastIncrementalOBRCURRInfo*)manager->Decode();
    manager->PrintIncrementalOBRCURR(info);

    if(info->MsgSeqNum != msgSeqNo)
        throw;
    if(info->SendingTime != 20160819142308700)
        throw;
    if(info->GroupMDEntriesCount != 2)
        throw;

    if(manager->MessageLength() != 111)
        throw;

    FastOBSCURRItemInfo *itemInfo1 = info->GroupMDEntries[0];
    FastOBSCURRItemInfo *itemInfo2 = info->GroupMDEntries[1];

    if(itemInfo1->MDUpdateAction != mduaAdd)
        throw;
    if(itemInfo1->MDEntryTypeLength != 1)
        throw;
    if(itemInfo1->MDEntryType[0] != mdetBuyQuote)
        throw;
    if(itemInfo1->MDEntryIDLength != 10)
        throw;
    if(!this->CompareStrings(itemInfo1->MDEntryID, "B000778875"))
        throw;
    if(itemInfo1->SymbolLength != 12)
        throw;
    if(!this->CompareStrings(itemInfo1->Symbol, "EUR_RUB__TOM"))
        throw;
    if(itemInfo1->RptSeq != 270094)
        throw;
    if(itemInfo1->MDEntryPx.Exponent != -4)
        throw;
    if(itemInfo1->MDEntryPx.Mantissa != 778875)
        throw;
    if(itemInfo1->MDEntrySize.Mantissa != 328)
        throw;
    if(itemInfo1->MDEntrySize.Exponent != 0)
        throw;
    if(itemInfo1->MDEntryTime != 142308000)
        throw;
    if(itemInfo1->OrigTime != 682877)
        throw;
    if(itemInfo1->TradingSessionIDLength != 4)
        throw;
    if(!this->CompareStrings(itemInfo1->TradingSessionID, "CETS"))
        throw;
    if(itemInfo1->TradingSessionSubIDLength != 1)
        throw;
    if(itemInfo1->TradingSessionSubID[0] != 0)
        throw;


    if(itemInfo2->MDUpdateAction != mduaChange)
        throw;
    if(itemInfo2->MDEntryTypeLength != 1)
        throw;
    if(itemInfo2->MDEntryType[0] != mdetSellQuote)
        throw;
    if(itemInfo2->MDEntryIDLength != 10)
        throw;
    if(!this->CompareStrings(itemInfo2->MDEntryID, "S000816775"))
        throw;
    if(itemInfo2->SymbolLength != 12)
        throw;
    if(!this->CompareStrings(itemInfo2->Symbol, "EUR_RUB__TOM"))
        throw;
    if(itemInfo2->RptSeq != 270095)
        throw;
    if(itemInfo2->MDEntryPx.Exponent != -4)
        throw;
    if(itemInfo2->MDEntryPx.Mantissa != 816775)
        throw;
    if(itemInfo2->MDEntrySize.Mantissa != 1268)
        throw;
    if(itemInfo2->MDEntrySize.Exponent != 0)
        throw;
    if(itemInfo2->MDEntryTime != 142308000)
        throw;
    if(itemInfo2->OrigTime != 689462)
        throw;
    if(itemInfo2->TradingSessionIDLength != 4)
        throw;
    if(!this->CompareStrings(itemInfo2->TradingSessionID, "CETS"))
        throw;
    if(itemInfo2->TradingSessionSubIDLength != 1)
        throw;
    if(itemInfo2->TradingSessionSubID[0] != 0)
        throw;


    message = new unsigned char[107] {0x05,0xa4,0x07,0x00,0xe0,0x1b,0xb8,0x1e,0x48,0x85,
                                   0x23,0x68,0x05,0x07,0x7a,0x6e,0x67,0x98,0x82,0x82,
                                   0xb1,0x53,0x30,0x30,0x30,0x37,0x36,0x34,0x30,0x30,
                                   0xb0,0x55,0x53,0x44,0x30,0x30,0x30,0x55,0x54,0x53,
                                   0x54,0x4f,0xcd,0x0f,0x0d,0x84,0xff,0x05,0xfc,0x81,
                                   0x0d,0xb4,0x43,0x6d,0x65,0xa1,0x2d,0x74,0xb1,0x43,
                                   0x45,0x54,0xd3,0x80,0x82,0xb0,0x42,0x30,0x30,0x30,
                                   0x37,0x31,0x39,0x38,0x35,0xb0,0x55,0x53,0x44,0x52,
                                   0x55,0x42,0x5f,0x53,0x50,0xd4,0x00,0x47,0x87,0xfd,
                                   0x04,0x32,0xb1,0x82,0xb0,0x43,0x6d,0x65,0xa1,0x2d,
                                   0x74,0xd1,0x43,0x45,0x54,0xd3,0x80};

    manager->SetNewBuffer(message, 107);

    msgSeqNo = manager->ReadMsgSeqNumber();
    info = (FastIncrementalOBRCURRInfo*)manager->Decode();

    manager->PrintIncrementalOBRCURR(info);

    if(info->MsgSeqNum != msgSeqNo)
        throw;
    if(info->SendingTime != 20160819142308760)
        throw;
    if(info->GroupMDEntriesCount != 2)
        throw;

    if(manager->MessageLength() != 107)
        throw;

    itemInfo1 = info->GroupMDEntries[0];
    itemInfo2 = info->GroupMDEntries[1];


    if(itemInfo1->MDUpdateAction != mduaChange)
        throw;
    if(itemInfo1->MDEntryTypeLength != 1)
        throw;
    if(itemInfo1->MDEntryType[0] != mdetSellQuote)
        throw;
    if(itemInfo1->MDEntryIDLength != 10)
        throw;
    if(!this->CompareStrings(itemInfo1->MDEntryID, "S000764000"))
        throw;
    if(itemInfo1->SymbolLength != 12)
        throw;
    if(!this->CompareStrings(itemInfo1->Symbol, "USD000UTSTOM"))
        throw;
    if(itemInfo1->RptSeq != 247427)
        throw;
    if(itemInfo1->MDEntryPx.Exponent != -1)
        throw;
    if(itemInfo1->MDEntryPx.Mantissa != 764)
        throw;
    if(itemInfo1->MDEntrySize.Mantissa != 1716)
        throw;
    if(itemInfo1->MDEntrySize.Exponent != 0)
        throw;
    if(itemInfo1->MDEntryTime != 142308000)
        throw;
    if(itemInfo1->OrigTime != 752176)
        throw;
    if(itemInfo1->TradingSessionIDLength != 4)
        throw;
    if(!this->CompareStrings(itemInfo1->TradingSessionID, "CETS"))
        throw;
    if(itemInfo1->TradingSessionSubIDLength != 1)
        throw;
    if(itemInfo1->TradingSessionSubID[0] != 0)
        throw;


    if(itemInfo2->MDUpdateAction != mduaChange)
        throw;
    if(itemInfo2->MDEntryTypeLength != 1)
        throw;
    if(itemInfo2->MDEntryType[0] != mdetBuyQuote)
        throw;
    if(itemInfo2->MDEntryIDLength != 10)
        throw;
    if(!this->CompareStrings(itemInfo2->MDEntryID, "B000719850"))
        throw;
    if(itemInfo2->SymbolLength != 10)
        throw;
    if(!this->CompareStrings(itemInfo2->Symbol, "USDRUB_SPT"))
        throw;
    if(itemInfo2->RptSeq != 9094)
        throw;
    if(itemInfo2->MDEntryPx.Exponent != -3)
        throw;
    if(itemInfo2->MDEntryPx.Mantissa != 71985)
        throw;
    if(itemInfo2->MDEntrySize.Mantissa != 48)
        throw;
    if(itemInfo2->MDEntrySize.Exponent != 1)
        throw;
    if(itemInfo2->MDEntryTime != 142308000)
        throw;
    if(itemInfo2->OrigTime != 752208)
        throw;
    if(itemInfo2->TradingSessionIDLength != 4)
        throw;
    if(!this->CompareStrings(itemInfo2->TradingSessionID, "CETS"))
        throw;
    if(itemInfo2->TradingSessionSubIDLength != 1)
        throw;
    if(itemInfo2->TradingSessionSubID[0] != 0)
        throw;

    message = new unsigned char[171] {
            0x46, 0x20, 0x00, 0x00, 0xe0, 0x10, 0xc3, 0x40, 0xc6, 0x23,
            0x68, 0x05, 0x17, 0x03, 0x01, 0x50, 0xd9, 0x00, 0x5e, 0xed,
            0x58, 0x53, 0x30, 0x39, 0x33, 0x35, 0x33, 0x31, 0x31, 0x32,
            0x34, 0xb0, 0x8d, 0x58, 0x53, 0x30, 0x39, 0x33, 0x35, 0x33,
            0x31, 0x31, 0x32, 0x34, 0x30, 0x82, 0x34, 0x84, 0x87, 0x44,
            0x42, 0x58, 0x58, 0x58, 0x58, 0x85, 0x43, 0x4f, 0x52, 0x50,
            0x09, 0x52, 0x62, 0xfc, 0x09, 0x4e, 0x42, 0xb8, 0x80, 0x80,
            0x09, 0x4e, 0x44, 0xe4, 0xfb, 0x14, 0xc1, 0x80, 0x80, 0x86,
            0x53, 0x42, 0x2d, 0x32, 0x33, 0x9e, 0x53, 0x42, 0x20, 0x43,
            0x41, 0x50, 0x49, 0x54, 0x41, 0x4c, 0x20, 0x53, 0x2e, 0x41,
            0x2e, 0x20, 0x35, 0x2e, 0x32, 0x35, 0x20, 0x32, 0x33, 0x2f,
            0x30, 0x35, 0x2f, 0x32, 0x33, 0x80, 0x83, 0x9b, 0x82, 0x36,
            0x88, 0x84, 0x31, 0x38, 0x34, 0x55, 0x53, 0xc4, 0x82, 0x81,
            0x81, 0x82, 0x52, 0x50, 0x45, 0xd5, 0xce, 0x92, 0x80, 0x55,
            0x53, 0xc4, 0x82, 0x80, 0x86, 0x53, 0x42, 0x2d, 0x32, 0x33,
            0x84, 0x52, 0x50, 0x53, 0xfa, 0x81, 0x80, 0x80, 0x80, 0x80,
            0x84, 0x81, 0x80, 0x80, 0x80, 0x80, 0x87, 0x81, 0x80, 0x80,
            0x80};


    manager->SetNewBuffer(message, 171);
    msgSeqNo = manager->ReadMsgSeqNumber();
    sd = (FastSecurityDefinitionInfo*)manager->Decode();
    manager->PrintSecurityDefinition(sd);
    if(manager->MessageLength() != 171)
        throw;

    message = new unsigned char[241] {
            0x7c, 0x2e, 0x00, 0x00, 0xe0, 0x12, 0xec, 0x5c, 0xfc, 0x23,
            0x68, 0x07, 0x6d, 0x66, 0x66, 0x4a, 0xe3, 0x11, 0x32, 0x86,
            0x03, 0x9c, 0x00, 0xe5, 0x54, 0x51, 0x49, 0xc6, 0x52, 0x55,
            0x30, 0x30, 0x30, 0x41, 0x30, 0x4a, 0x54, 0x38, 0x55, 0xb8,
            0x82, 0x82, 0x92, 0x80, 0x87, 0xb0, 0x42, 0x30, 0x30, 0x30,
            0x30, 0x31, 0x31, 0x30, 0x36, 0xb6, 0xff, 0x00, 0x56, 0xba,
            0x81, 0x00, 0xc5, 0x49, 0x3a, 0x3b, 0xd1, 0x04, 0x07, 0x97,
            0x80, 0x80, 0x80, 0x80, 0xb0, 0x42, 0x30, 0x30, 0x30, 0x30,
            0x31, 0x31, 0x30, 0x36, 0xb7, 0xff, 0x00, 0x56, 0xbb, 0x81,
            0xa6, 0x49, 0x51, 0x15, 0xf1, 0x1e, 0x34, 0x8f, 0x80, 0x80,
            0x80, 0x80, 0xb0, 0x42, 0x30, 0x30, 0x30, 0x30, 0x31, 0x31,
            0x30, 0x36, 0xb8, 0xff, 0x00, 0x56, 0xbc, 0x81, 0xb5, 0x48,
            0x1a, 0x46, 0xf1, 0x31, 0x57, 0xeb, 0x80, 0x80, 0x80, 0x80,
            0xb0, 0x42, 0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x36,
            0xb9, 0xff, 0x00, 0x56, 0xbd, 0x81, 0x83, 0x48, 0x76, 0x7b,
            0x81, 0x1b, 0x55, 0xb5, 0x80, 0x80, 0x80, 0x80, 0xb1, 0x53,
            0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x37, 0xb0, 0x81,
            0x08, 0xd3, 0x81, 0x9d, 0x49, 0x4d, 0x0a, 0xb9, 0x12, 0x7d,
            0xb6, 0x80, 0x80, 0x80, 0x80, 0xb1, 0x53, 0x30, 0x30, 0x30,
            0x30, 0x31, 0x31, 0x30, 0x37, 0xb1, 0xff, 0x00, 0x56, 0xbf,
            0x81, 0xac, 0x49, 0x40, 0x77, 0xe1, 0x1c, 0x51, 0x8a, 0x80,
            0x80, 0x80, 0x80, 0xb1, 0x53, 0x30, 0x30, 0x30, 0x30, 0x31,
            0x31, 0x30, 0x37, 0xb2, 0xff, 0x00, 0x56, 0xc0, 0x81, 0x97,
            0x49, 0x3e, 0x4e, 0xf1, 0x0d, 0x76, 0xf8, 0x80, 0x80, 0x80,
            0x80 };

    manager->SetNewBuffer(message, 241);
    msgSeqNo = manager->ReadMsgSeqNumber();
    FastSnapshotInfo *snap = (FastSnapshotInfo*)manager->GetSnapshotInfo();
    if(snap->LastMsgSeqNumProcessed != 284933)
        throw;

    message = new unsigned char[18] {
            0x00, 0x8d, 0x03, 0x00, 0xc0, 0x10, 0xbc, 0x0e, 0x1a, 0x80,
            0x23, 0x68, 0x08, 0x12, 0x7f, 0x4c, 0x4f, 0xfa
    };
    manager->SetNewBuffer(message, 18);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->Decode();
    manager->Print();

    message = new unsigned char[65] {
            0x05, 0x8d, 0x03, 0x00, 0xe0, 0x12, 0xf6, 0x0e, 0x1a, 0x85,
            0x23, 0x68, 0x08, 0x12, 0x7f, 0x4c, 0x66, 0xd1, 0x81, 0x83,
            0xb0, 0x42, 0x30, 0x30, 0x30, 0x30, 0x32, 0x37, 0x35, 0x37,
            0xb1, 0x52, 0x55, 0x30, 0x30, 0x30, 0x41, 0x30, 0x4a, 0x50,
            0x4b, 0x4a, 0xb3, 0x03, 0xb2, 0xff, 0x01, 0x57, 0xb3, 0x80,
            0x57, 0x6d, 0x1e, 0xd1, 0x1e, 0x28, 0xeb, 0x80, 0x80, 0x80,
            0x54, 0x51, 0x49, 0xc6, 0x80
    };
    manager->SetNewBuffer(message, 65);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->Decode();
    manager->Print();
    
    message = new unsigned char[55] {
            0x25, 0x29, 0x04, 0x00, 0xe0, 0x12, 0xf4, 0x10, 0x52, 0xa5,
            0x23, 0x68, 0x0b, 0x0f, 0x04, 0x7e, 0x58, 0xa2, 0x81, 0x80,
            0x83, 0xb1, 0x33, 0x35, 0x35, 0x31, 0x34, 0xb8, 0x42, 0x47,
            0x44, 0xc5, 0x26, 0xee, 0x80, 0x5f, 0x6d, 0x15, 0x91, 0x34,
            0x1d, 0xf4, 0xfe, 0x05, 0xc5, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x54, 0x51, 0x44, 0xc5, 0xce
    };

    manager->SetNewBuffer(message, 55);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->Decode();
    manager->Print();

    if(manager->TemplateId() != 2420)
        throw;

    FastIncrementalOLRFONDInfo *olrfondInfo = (FastIncrementalOLRFONDInfo*)manager->LastDecodeInfo();
    if(olrfondInfo->GroupMDEntriesCount != 1)
        throw;
    if(olrfondInfo->GroupMDEntries[0]->TradingSessionID == 0)
        throw;
    if(manager->MessageLength() != 55)
        throw;

    message = new unsigned char[57] {
            0x64, 0x0c, 0x04, 0x00, 0xe0, 0x12, 0xf4, 0x10, 0x18, 0xe4,
            0x23, 0x68, 0x0b, 0x12, 0x63, 0x2e, 0x2d, 0xc4, 0x81, 0x80,
            0x81, 0xb1, 0x33, 0x36, 0x30, 0x38, 0x36, 0xb0, 0x55, 0x54,
            0x53, 0xd9, 0x1d, 0xef, 0x80, 0x61, 0x31, 0x59, 0xb1, 0x1d,
            0x01, 0x9e, 0xfe, 0x03, 0xbc, 0x81, 0x0d, 0x9d, 0x80, 0xcf,
            0x80, 0x80, 0x54, 0x51, 0x44, 0xc5, 0xce
    };

    manager->SetNewBuffer(message, 57);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->Decode();
    manager->Print();

    olrfondInfo = (FastIncrementalOLRFONDInfo*)manager->LastDecodeInfo();
    if(olrfondInfo->GroupMDEntriesCount != 1)
        throw;
    if(olrfondInfo->GroupMDEntries[0]->TradingSessionID == 0)
        throw;
    if(manager->MessageLength() != 57)
        throw;

    message = new unsigned char[18] {
            0x32, 0x77, 0x03, 0x00, 0xe0, 0x12, 0xf4, 0x0d, 0x6e, 0xb2,
            0x23, 0x68, 0x0d, 0x26, 0x2f, 0x55, 0x09, 0x83
    };

    manager->SetNewBuffer(message, 18);
    manager->SetNewBuffer(message, 18);
    msgSeqNo = manager->ReadMsgSeqNumber();
    manager->Decode();
    manager->Print();
}

bool FastProtocolTester::CompareStrings(char* str1, const char *str2) {
    int length = strlen(str2);
    for(int i = 0; i < length; i++) {
        if(str1[i] != str2[i])
            return false;
    }
    return true;
}

void FastProtocolTester::TestMessageSequenceNumber() { 
	FastProtocolManager *manager = new FastProtocolManager();
	
	*((int*)(manager->Buffer())) = 0x12345678;
	int seq = manager->ReadMsgSeqNumber();

	if (manager->CurrentPos() - manager->Buffer() != 4) { 
		printf("ReadMsgSeqNumber: expected 4 but was %ld", manager->CurrentPos() - manager->Buffer());
		throw;
	}
	if (seq != 0x12345678) { 
		printf("ReadMsgSeqNumber: expected 0x12345678 but was %x", seq);
		throw;
	}

	delete manager;
}

void FastProtocolTester::TestReadInt32_Mandatory() { 
	printf("Test FastProtocolTester::TestReadInt32_Mandatory\n");
	FastProtocolManager* manager = new FastProtocolManager();

	for (int i = 0; i > -2147483630; i -= 5) {
		manager->ResetBuffer();
		manager->WriteInt32_Mandatory(i);
		manager->ResetBuffer();
		INT32 value = manager->ReadInt32_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%d\n", i);
	}

	for (int i = 0; i < 0x7ffffff0; i+= 5) { 
		manager->ResetBuffer();
		manager->WriteInt32_Mandatory(i);
		manager->ResetBuffer();
		INT32 value = manager->ReadInt32_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%d\n", i);
	}

	delete manager;
}

void FastProtocolTester::TestReadInt32_Optional() {
	printf("Test FastProtocolTester::TestReadInt32_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->ResetBuffer();
	manager->WriteInt32_Optional(942755);
	if (manager->MessageLength() != 3)
		throw;
	if (manager->Buffer()[0] != 0x39) {
		throw std::runtime_error("buffer 0");
	}
	if (manager->Buffer()[1] != 0x45) {
		throw std::runtime_error("buffer 1");
	}
	if (manager->Buffer()[2] != 0xa4) {
		throw std::runtime_error("buffer 2");
	}

	manager->ResetBuffer();
	manager->WriteInt32_Optional(-942755);
	if (manager->MessageLength() != 3)
		throw;

	if (manager->Buffer()[0] != 0x46) {
		throw std::runtime_error("buffer 0");
	}
	if (manager->Buffer()[1] != 0x3a) {
		throw std::runtime_error("buffer 1");
	}
	if (manager->Buffer()[2] != 0xdd) {
		throw std::runtime_error("buffer 2");
	}

	manager->ResetBuffer();
	manager->Buffer()[0] = 0x46;
	manager->Buffer()[1] = 0x3a;
	manager->Buffer()[2] = 0xdd;

	int negValue = manager->ReadInt32_Optional();
	if (negValue != -942755)
		throw;
	
	delete manager;
}

void FastProtocolTester::TestReadUInt32_Optional() {
	printf("Test FastProtocolTester::TestReadUInt32_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	delete manager;
}

void FastProtocolTester::TestReadUInt32_Mandatory() {
	printf("Test FastProtocolTester::TestReadUInt32_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	for (UINT32 i = 0; i < 0xfffffff0; i += 5) {
		manager->ResetBuffer();
		manager->WriteUInt32_Mandatory(i);
		manager->ResetBuffer();
		UINT32 value = manager->ReadUInt32_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%u\n", i);
	}
}

void FastProtocolTester::TestReadString_Optional() { 
	printf("Test FastProtocolTester::TestReadString_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->WriteString_Optional((const char*)NULL, 0);
	if (manager->MessageLength() != 1)
		throw;
	if (manager->Buffer()[0] != 0x80)
		throw;

	manager->ResetBuffer();
	manager->WriteString_Optional((char*)"", 0);
	if (manager->MessageLength() != 2)
		throw;
	if (manager->Buffer()[0] != 0x00)
		throw;
	if (manager->Buffer()[1] != 0x80)
		throw;

	char *buffer = new char[60];
	char *buffer2 = new char[60];
	for (int i = 0; i < 60; i++) { 
		buffer[i] = (char)('A' + i);
	} 

	int length = 0;
	for (int i = 1; i < 60; i++) { 
		manager->ResetBuffer();
		manager->WriteString_Optional(buffer, i);
		if (manager->MessageLength() != i)
			throw;

		manager->ResetBuffer();
		manager->ReadString_Optional(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) { 
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadString_Mandatory() {
	printf("Test FastProtocolTester::TestReadString_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->WriteString_Mandatory((char*)"", 0);
	if (manager->MessageLength() != 1)
		throw;
	if (manager->Buffer()[0] != 0x80)
		throw;

	char *buffer = new char[60];
	char *buffer2 = new char[60];
	for (int i = 0; i < 60; i++) {
		buffer[i] = (char)('A' + i);
	}

	int length = 0;
	for (int i = 1; i < 60; i++) {
		manager->ResetBuffer();
		manager->WriteString_Mandatory(buffer, i);
		if (manager->MessageLength() != i)
			throw;

		manager->ResetBuffer();
		manager->ReadString_Mandatory(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) {
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadByteVector_Optional() { 
	printf("Test FastProtocolTester::TestReadByteVector_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	manager->WriteByteVector_Optional(NULL, 0);
	if (manager->MessageLength() != 1)
		throw;
	if (manager->Buffer()[0] != 0x80)
		throw;

	BYTE *buffer = new BYTE[1000];
	BYTE *buffer2;
	for (int i = 0; i < 1000; i++) {
		buffer[i] = (char)('A' + i % 60);
	}

	int length = 0;
	for (int i = 0; i < 1000; i++) {
		manager->ResetBuffer();
		manager->WriteByteVector_Optional(buffer, i);
		
		manager->ResetBuffer();
		manager->ReadByteVector_Optional(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) {
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadByteVector_Mandatory() {
	printf("Test FastProtocolTester::TestReadByteVector_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	BYTE *buffer = new BYTE[1000];
	BYTE *buffer2;
	for (int i = 0; i < 1000; i++) {
		buffer[i] = (char)('A' + i % 60);
	}

	int length = 0;
	for (int i = 0; i < 1000; i++) {
		manager->ResetBuffer();
		manager->WriteByteVector_Mandatory(buffer, i);

		manager->ResetBuffer();
		manager->ReadByteVector_Mandatory(&buffer2, &length);
		if (length != i)
			throw;
		for (int j = 0; j < i; j++) {
			if (buffer2[j] != buffer[j])
				throw;
		}
	}

	delete manager;
}

void FastProtocolTester::TestReadDecimal_Optional() { 
	printf("Test FastProtocolTester::TestReadDecimal_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	Decimal value(942755, 2);
	manager->WriteDecimal_Optional(&value);

	if (manager->MessageLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0x83, 0x39, 0x45, 0xa3 }, 4))
		throw;

	value.Set(-942755, -2);
	manager->ResetBuffer();
	manager->WriteDecimal_Optional(&value);

	if (manager->MessageLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0xfe, 0x46, 0x3a, 0xdd }, 4))
		throw;
	
	value.Set(-8193, -3);
	manager->ResetBuffer();
	manager->WriteDecimal_Optional(&value);

	if (manager->MessageLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0xfd, 0x7f, 0x3f, 0xff }, 4))
		throw;

	delete manager;
}

void FastProtocolTester::TestReadDecimal_Mandatory() {
	printf("Test FastProtocolTester::TestReadDecimal_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	Decimal value = { 942755, 2 };
	manager->WriteDecimal_Mandatory(&value);

	if (manager->MessageLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0x82, 0x39, 0x45, 0xa3 }, 4))
		throw;

	value = { 9427550, 1 };
	manager->ResetBuffer();
	manager->WriteDecimal_Mandatory(&value);

	if (manager->MessageLength() != 5)
		throw;
	if (!manager->CheckBuffer(new BYTE[5] { 0x81, 0x04, 0x3f, 0x34, 0xde }, 5))
		throw;

	value = { 942755, -2 };
	manager->ResetBuffer();
	manager->WriteDecimal_Mandatory(&value);

	if (manager->MessageLength() != 4)
		throw;
	if (!manager->CheckBuffer(new BYTE[4] { 0xfe, 0x39, 0x45, 0xa3 }, 4))
		throw;
	
	delete manager;
}

void FastProtocolTester::TestReadInt64_Optional() {
	printf("Test FastProtocolTester::TestReadInt64_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();
	
	BYTE buffer[12];
	for (int i = 1; i < 10; i++) { // extended positive
		memset(buffer, 0, 12);
		for (int j = 1; j <= i; j++) { 
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] |= 0x40;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);
		
		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	for (int i = 1; i < 10; i++) { // extended negative
		memset(buffer, 0, 12);
		buffer[0] = 0x7f;
		for (int j = 1; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // simple negative
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0) {
				buffer[j] |= 0x40;
				buffer[j] &= 0xfe;
			}
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Optional();
		if (value2 != value)
			throw;
	}

	delete manager;
}

void FastProtocolTester::TestReadInt64_Mandatory() {
	printf("Test FastProtocolTester::TestReadInt64_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	INT64 min = INT64_MIN + 10;

	for (INT64 i = 0; i > min; i -= 5) {
		manager->ResetBuffer();
		manager->WriteInt64_Mandatory(i);
		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%" PRIu64 "\n", i);
	}

	for (INT64 i = 0; i < 0x7ffffffffffffff0; i += 5) {
		manager->ResetBuffer();
		manager->WriteInt64_Mandatory(i);
		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		if (value != i)
			throw;
		if ((i % 1000000) == 0)
			printf("%" PRIu64 "\n", i);
	}


	BYTE buffer[12];
	for (int i = 1; i < 10; i++) { // extended positive
		memset(buffer, 0, 12);
		for (int j = 1; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] |= 0x40;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	for (int i = 1; i < 10; i++) { // extended negative
		memset(buffer, 0, 12);
		buffer[0] = 0x7f;
		for (int j = 1; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 1)
				buffer[j] &= 0xbf;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	for (int i = 0; i < 9; i++) { // simple negative
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0)
				buffer[j] |= 0x40;
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		INT64 value = manager->ReadInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		INT64 value2 = manager->ReadInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	INT64 value = 0x7fffffffffffffff;
	manager->ResetBuffer();
	manager->WriteInt64_Mandatory(value);
	manager->ResetBuffer();
	INT64 value2 = manager->ReadInt64_Mandatory();
	if (value != value2)
		throw;

	delete manager;
}

void FastProtocolTester::TestReadUInt64_Mandatory() {
	printf("Test FastProtocolTester::TestReadUInt64_Mandatory\n");
	FastProtocolManager *manager = new FastProtocolManager();

	BYTE buffer[12];

	//00 72 40 0d 6e 79 6c 21 ab
	buffer[0] = 0x01;
	buffer[1] = 0x72;
	buffer[2] = 0x0d;
	buffer[3] = 0x6e;
	buffer[4] = 0x79;
	buffer[5] = 0x6c;
	buffer[6] = 0x21;
	buffer[7] = 0xab;

	manager->ResetBuffer();
	manager->CopyToBuffer(buffer, 8);
	UINT64 v = manager->ReadUInt64_Mandatory();
	manager->ResetBuffer();
	manager->WriteUInt64_Mandatory(v);
	if (!manager->CheckBuffer(buffer, 8))
		throw;
	manager->ResetBuffer();
	UINT64 v2 = manager->ReadUInt64_Mandatory();
	if (v2 != v)
		throw;

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0) {
				buffer[j] &= 0xbf;
				buffer[j] |= 0x01;
			}
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		UINT64 value = manager->ReadUInt64_Mandatory();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteUInt64_Mandatory(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		UINT64 value2 = manager->ReadUInt64_Mandatory();
		if (value2 != value)
			throw;
	}

	UINT64 value = 0xffffffffffffffff;
	manager->ResetBuffer();
	manager->WriteUInt64_Mandatory(value);
	manager->ResetBuffer();
	UINT64 value2 = manager->ReadUInt64_Mandatory();
	if (value != value2)
		throw;

	delete manager;
}

void FastProtocolTester::TestReadUInt64_Optional() {
	printf("Test FastProtocolTester::TestReadUInt64_Optional\n");
	FastProtocolManager *manager = new FastProtocolManager();

	BYTE buffer[12];

	for (int i = 0; i < 9; i++) { // positive
		memset(buffer, 0, 12);
		for (int j = 0; j <= i; j++) {
			buffer[j] = (rand() % 0xff) & 0x7f;
			if (j == 0) {
				buffer[j] &= 0xbf;
				buffer[j] |= 0x01;
			}
		}
		buffer[i] |= 0x80;
		manager->CopyToBuffer(buffer, i + 1);

		manager->ResetBuffer();
		UINT64 value = manager->ReadUInt64_Optional();
		manager->ResetBuffer();

		manager->ClearBuffer();
		manager->WriteUInt64_Optional(value);

		if (!manager->CheckBuffer(buffer, i + 1))
			throw;

		manager->ResetBuffer();
		UINT64 value2 = manager->ReadUInt64_Optional();
		if (value2 != value)
			throw;
	}

	UINT64 value = 0xfffffffffffffffe;
	manager->ResetBuffer();
	manager->WriteUInt64_Optional(value);
	manager->ResetBuffer();
	UINT64 value2 = manager->ReadUInt64_Optional();
	if (value != value2)
		throw;

	delete manager;
}

void FastProtocolTester::TestParsePresenceMap() {
	/*FastProtocolManager *manager = new FastProtocolManager();
	
	*(manager->Buffer()) = 0x80;
	manager->ParsePresenceMap();

	if (manager->CurrentPos() - manager->Buffer() != 1) {
		printf_s("ParsePresenceMap: expected 1 but was %d", manager->CurrentPos() - manager->Buffer());
		throw;
	}
	for (int i = 0; i < 8; i++) { 
		if (manager->PresenceMap()[i] != 0) { 
			printf_s("ParsePresenceMap: expected 0 but was %d", manager->PresenceMap()[i]);
			throw;
		}
	}
	
	for (int j = 1; j < 100;  j++) {
		manager->ResetBuffer();
		for (int l = 0; l < j - 1; l++)  {
			manager->Buffer()[l] = 0x7f;
		}
		manager->Buffer()[j - 1] = 0xff;
		manager->ParsePresenceMap();
		
		if (manager->CurrentPos() - manager->Buffer() != j) {
			printf_s("ParsePresenceMap: expected %d but was %d", j, manager->CurrentPos() - manager->Buffer());
			throw;
		}

		for (int i = 0; i < 7 * j; i++) { 
			if (manager->PresenceMap()[i] != 1) {
				printf_s("ParsePresenceMap: expected 1 but was %d", manager->PresenceMap()[i]);
				throw;
			}
		}
	}
	
	delete manager;*/
}
