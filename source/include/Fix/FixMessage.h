//
// Created by root on 30.07.16.
//

#ifndef HFT_ROBOT_FIXMESSAGE_H
#define HFT_ROBOT_FIXMESSAGE_H

#include "FixTypes.h"
#include "Converters/ItoaConverter.h"
#include "Converters/DtoaConverter.h"
#include "Converters/UTCTimeConverter.h"

typedef struct _FixTag {
    union {
        char*   buffer;
        unsigned int*   ui_buffer;
    };
    char*   value;
    int     size;
    int     valueSize;
    int     tag;
    union {
        unsigned int    uintValue;
        int             intValue;
        bool            boolValue;
        char            charValue;
    };
}FixTag;

class FixProtocolMessage {
    const int                   m_tagsMaxCount = 256;

    FixHeaderInfo               *m_headerInfo;
    FixResendRequestInfo        *m_resendRequestInfo;
    int                         m_size;
    char*                       m_buffer;
    int                         m_tagsCount;
    FixTag*                     m_tags[256];
    ItoaConverter               *m_intConv;
    UTCTimeConverter            *m_timeConv;
    DtoaConverter               *m_doubleConv;
    int                         m_currentTag;
    FixRejectInfo               *m_rejectInfo;

public:
    FixProtocolMessage(ItoaConverter *intConv, UTCTimeConverter *timeConv, DtoaConverter *doubleConv, FixRejectInfo *rejectInfo) {
        this->m_headerInfo = new FixHeaderInfo;
        this->m_resendRequestInfo = new FixResendRequestInfo;
        this->m_size = 0;
        this->m_buffer = 0;
        this->m_tagsCount = 0;
        this->m_intConv = intConv;
        this->m_timeConv = timeConv;
        this->m_doubleConv = doubleConv;
        this->m_rejectInfo = rejectInfo;
        for(int i = 0; i < this->m_tagsMaxCount; i++)
            this->m_tags[i] = new FixTag();
    }
    ~FixProtocolMessage() {
        delete this->m_headerInfo;
        for(int i = 0; i < this->m_tagsMaxCount; i++)
            delete this->m_tags[i];
    }

    inline void Reset() {
        this->m_currentTag = 0;
        this->m_tagsCount = 0;
    }
    inline void Buffer(char *buffer) { this->m_buffer = buffer; }
    inline char* Buffer() { return this->m_buffer; }
    inline void Size(int size) { this->m_size = size; }
    inline int Size() { return this->m_size; }
    inline void AddTag(char *tagPtr, int size) {
        this->m_tags[this->m_tagsCount]->buffer = tagPtr;
        this->m_tags[this->m_tagsCount]->size = size;
        this->m_tagsCount++;
    }
    inline FixHeaderInfo* Header() { return this->m_headerInfo; }
    inline FixResendRequestInfo *ResendRequestInfo() { return this->m_resendRequestInfo; }
    inline FixTag* Tag(int index) { return this->m_tags[index]; }
    inline FixTag* CurrentTag() { return this->Tag(this->m_currentTag); }
    inline int TagsCount() { return this->m_tagsCount; }
    inline void MoveNext() { this->m_currentTag++; }

    inline void Error(int errorTagId, FixSessionRejectReason rejectReason) {
        this->m_rejectInfo->RefMsgSeqNum = this->m_headerInfo->msgSeqNum;
        this->m_rejectInfo->AllowRefMsgType = true;
        this->m_rejectInfo->RefMsgType = this->m_headerInfo->msgType;
        this->m_rejectInfo->RefTagId = errorTagId;
        this->m_rejectInfo->SessionRejectReason = rejectReason;
        this->m_rejectInfo->TextLength = 0;
    }

    inline unsigned int ReadValuePredict324Unsigned(FixTag *tag) {
        tag->uintValue = ReadValuePredict324Unsigned(tag->value, tag->valueSize);
        return tag->uintValue;
    }
    inline unsigned int ReadValuePredict324Unsigned(char *buffer, int length) {
        if (length == 3)
            return this->m_intConv->From3SymbolUnsigned(buffer);
        if (length == 2)
            return this->m_intConv->From2SymbolUnsigned(buffer);
        if (length == 4)
            return this->m_intConv->From4SymbolUnsigned(buffer);
        return this->m_intConv->FromStringFastUnsigned(buffer, length);
    }
    inline unsigned int ReadValuePredict324Unsigned(char *buffer, char stopSymb) {
        if (buffer[3] == stopSymb)
            return this->m_intConv->From3SymbolUnsigned(buffer);
        if (buffer[2] == stopSymb)
            return this->m_intConv->From2SymbolUnsigned(buffer);
        if (buffer[4] == stopSymb)
            return this->m_intConv->From4SymbolUnsigned(buffer);
        unsigned int outValue;
        this->m_intConv->FromStringFastUnsigned(buffer, (int*)&outValue, stopSymb);
        return outValue;
    }
    inline int ReadValuePredict34Unsigned(char *buffer, char stopSymb) {
        if (buffer[3] == stopSymb)
            return this->m_intConv->From3SymbolUnsigned(buffer);
        if (buffer[4] == stopSymb)
            return this->m_intConv->From4SymbolUnsigned(buffer);
        int outValue;
        this->m_intConv->FromStringFastUnsigned(buffer, &outValue, stopSymb);
        return outValue;
    }
    inline int ReadValuePredict34Unsigned(char *buffer, int length) {
        if (length == 3)
            return this->m_intConv->From3SymbolUnsigned(buffer);
        if (length == 4)
            return this->m_intConv->From4SymbolUnsigned(buffer);
        return this->m_intConv->FromStringFastUnsigned(buffer, length);
    }
    inline int ReadUTCDateTime(char *buffer, SYSTEMTIME *st, char stopSymbol) {
        return this->m_timeConv->FromString(buffer, st, stopSymbol);
    }
    inline int ReadUTCDate(char *buffer, SYSTEMTIME *st) {
        return this->m_timeConv->FromDateString(buffer, st);
    }
    inline int ReadTag(char *buffer, int *outValue) {
        unsigned int tagVal = *((unsigned int *)buffer);
        if ((tagVal & 0xff000000) == FIX_EQUAL_FORTH_BYTE) {
            *outValue = this->m_intConv->From3SymbolUnsigned(buffer);
            return 4;
        }
        else if ((tagVal & 0xff000000) == FIX_EQUAL_THIRD_BYTE) {
            *outValue = this->m_intConv->From2SymbolUnsigned(buffer);
            return 3;
        }
        else if ((tagVal & 0xff000000) == FIX_EQUAL_SECOND_BYTE) {
            *outValue = *buffer - 0x30;
            return 2;
        }
        else if(buffer[4] == '=') {
            *outValue = this->m_intConv->From4SymbolUnsigned(buffer);
            return 5;
        }
        *outValue = this->m_intConv->FromStringFastUnsigned(buffer, 5);
        return 6;
    }

    inline int Read1SymbolTag(FixTag *tag) {
        tag->tag = *(tag->buffer) - 0x30;
        tag->value = tag->buffer + 2;
        tag->valueSize = tag->size - 2;
        return tag->tag;
    }
    inline int Read2SymbolTag(FixTag *tag) {
        tag->tag = this->m_intConv->From2SymbolUnsigned(tag->buffer);
        tag->value = tag->buffer + 3;
        tag->valueSize = tag->size - 3;
        return tag->tag;
    }
    inline int Read3SymbolTag(FixTag *tag) {
        tag->tag = this->m_intConv->From3SymbolUnsigned(tag->buffer);
        tag->value = tag->buffer + 4;
        tag->valueSize = tag->size - 4;
        return tag->tag;
    }
    inline int Read4SymbolTag(FixTag *tag) {
        tag->tag = this->m_intConv->From4SymbolUnsigned(tag->buffer);
        tag->value = tag->buffer + 5;
        tag->valueSize = tag->size - 5;
        return tag->tag;
    }

    inline bool ReadCheck1SymbolTag(FixTag *tag, int expectedTag) {
        return this->Read1SymbolTag(tag) == expectedTag;
    }

    inline bool ReadCheck2SymbolTag(FixTag *tag, int expectedTag) {
        return this->Read2SymbolTag(tag) == expectedTag;
    }

    inline bool ReadCheck3SymbolTag(FixTag *tag, int expectedTag) {
        return this->Read3SymbolTag(tag) == expectedTag;
    }
    inline bool ReadCheck4SymbolTag(FixTag *tag, int expectedTag) {
        return this->Read4SymbolTag(tag) == expectedTag;
    }

    inline bool ReadCheck1SymbolTag(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if((*(tag->ui_buffer) & 0x0000ffff) == binaryExpectedTag) {
            tag->tag = expectedTag;
            tag->value = tag->buffer + 2;
            tag->valueSize = tag->size - 2;
            return true;
        }
        return false;
    }

    inline bool ReadCheck1SymbolTagFast(FixTag *tag) {
        tag->value = tag->buffer + 2;
        tag->valueSize = tag->size - 2;
        return true;
    }

    inline bool ReadCheck2SymbolTag(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if((*(tag->ui_buffer) & 0x00ffffff) == binaryExpectedTag) {
            tag->tag = expectedTag;
            tag->value = tag->buffer + 3;
            tag->valueSize = tag->size - 3;
            return true;
        }
        return false;
    }

    inline bool ReadCheck2SymbolTagFast(FixTag *tag) {
        tag->value = tag->buffer + 3;
        tag->valueSize = tag->size - 3;
        return true;
    }

    inline bool ReadCheck3SymbolTag(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if(*(tag->ui_buffer) == binaryExpectedTag) {
            tag->tag = expectedTag;
            tag->value = tag->buffer + 4;
            tag->valueSize = tag->size - 4;
            return true;
        }
        return false;
    }
    inline bool ReadCheck4SymbolTag(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if(*(tag->ui_buffer) == binaryExpectedTag && tag->buffer[4] == '=') {
            tag->tag = expectedTag;
            tag->value = tag->buffer + 5;
            tag->valueSize = tag->size - 5;
            return true;
        }
        return false;
    }

    inline bool Read2TagSymbol(FixTag *tag, int expectedTag) {
        if(!this->ReadCheck2SymbolTag(tag, expectedTag) || tag->valueSize != 1)
            return false;
        tag->charValue = *(tag->value);
        return true;
    }
    inline bool ReadCheck2SymbolBoolean(FixTag *tag, int expectedTag) {
        if(!this->ReadCheck2SymbolTag(tag, expectedTag))
            return false;
        this->ReadBooleanSymbol(tag);
        return true;
    }

    inline bool Read2TagSymbol(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if(!this->ReadCheck2SymbolTag(tag, binaryExpectedTag, expectedTag) || tag->valueSize != 1)
            return false;
        tag->charValue = *(tag->value);
        return true;
    }
    inline bool ReadCheck2SymbolBoolean(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if(!this->ReadCheck2SymbolTag(tag, binaryExpectedTag, expectedTag))
            return false;
        this->ReadBooleanSymbol(tag);
        return true;
    }
    inline bool ReadCheckSkip2SymbolBoolean(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if(!this->ReadCheck2SymbolTag(tag, binaryExpectedTag, expectedTag))
            return false;
        //this->ReadBooleanSymbol(tag);
        return true;
    }

    inline int FindSeparator(char *buffer, int start, int size) {
        int len = start;
        unsigned int *pack4 = (unsigned int*)(buffer + start);
        while(len < size) {
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

    inline bool Read2TagIntValuePredict234(FixTag *tag, int binaryExpectedTag, int expectedTag) {
        if(!this->ReadCheck2SymbolTag(tag, binaryExpectedTag, expectedTag))
            return false;
        this->ReadValuePredict324Unsigned(tag);
        return true;
    }

    inline bool ReadBooleanSymbol(FixTag *tag) {
        if(tag->valueSize != 1)
            return false;
        tag->boolValue = *(tag->value) == 'Y';
        return true;
    }

    inline bool CheckFixHeader(FixTag *tag) {
        if(!this->ReadCheck1SymbolTag(tag, TagCheckBeginString, TagBeginString))
            return false;
        if(tag->valueSize != FixProtocolVersionLength)
            return false;
        // 8=FIX...
        this->m_headerInfo->name = tag->value; // 8=
        this->m_headerInfo->nameLength = tag->valueSize;

        return true;
    }

    inline bool ProcessMessageLengthTag(FixTag *tag) {
        if(!this->ReadCheck1SymbolTag(tag, TagCheckBodyLength, TagBodyLength))
            return false;

        ReadValuePredict324Unsigned(tag);
        return true;
    }

    inline FixHeaderInfo* HeaderInfo() { return this->m_headerInfo; }
    inline bool ProcessCheckHeader() {

        /* we dont check and read some tags
           because there is no need
        if (!CheckFixHeader(this->Tag(0)))
            return false;

        if (!ProcessMessageLengthTag(this->Tag(1)))
            return false;
        */

        FixTag *tag = this->Tag(2);
        if(!this->Read2TagSymbol(tag, TagCheckMsgType, TagMsgType))
            return false;
        this->m_headerInfo->msgType = tag->charValue;

        /*
        tag = this->Tag(3);
        if(!this->ReadCheck2SymbolTag(tag, TagCheckSenderCompID, TagSenderCompID))
            return false;
        this->m_headerInfo->senderCompID = tag->value;
        this->m_headerInfo->senderCompIDLength = tag->valueSize;

        tag = this->Tag(4);
        if(!this->ReadCheck2SymbolTag(tag, TagCheckTargetCompID, TagTargetCompID))
            return false;
        this->m_headerInfo->targetCompID = tag->value;
        this->m_headerInfo->targetCompIDLength = tag->valueSize;
        */

        // we just need MsgType nad MsgNumber
        tag = this->Tag(5);
        if(!this->Read2TagIntValuePredict234(tag, TagCheckMsgSeqNum, TagMsgSeqNum))
            return false;
        this->m_headerInfo->msgSeqNum = tag->intValue;

        this->m_currentTag = 6;
        tag = this->CurrentTag();
        if(this->ReadCheckSkip2SymbolBoolean(tag, TagCheckPossDupFlag, TagPossDupFlag)) {
            //this->m_headerInfo->possDupFlag = tag->boolValue;
            this->MoveNext();
        }
        tag = this->CurrentTag();
        if(this->ReadCheckSkip2SymbolBoolean(tag, TagCheckPossResend, TagPossResend)) {
            //this->m_headerInfo->possResend = tag->boolValue;
            this->MoveNext();
        }
        /*
        tag = this->CurrentTag();
        if(!this->ReadCheck2SymbolTag(tag, TagCheckSendingTime, TagSendingTime))
            return false;
        */
        this->MoveNext();
        //this->m_headerInfo->sendingTime = tag->value;
        tag = this->CurrentTag();
        if(this->ReadCheck2SymbolTag(tag, TagCheckOrigSendingTime, TagOrigSendingTime)) {
            //this->m_headerInfo->origSendingTime = tag->value;
            this->MoveNext();
        }
        return true;
    }

    inline bool CheckDetectCorrectMsgSeqNumber(int *outValue) {
        FixTag *tag = this->CurrentTag();
        if (!this->ReadCheck2SymbolTag(tag, TagCheckText, TagText))
            return false;
        //The incoming message has a sequence number (
        char *msg = tag->value;

        int bIndex = -1;
        if (!this->FindSymbol(msg, tag->valueSize, '(', &bIndex))
            return false;

        msg += bIndex + 1;
        if (!this->FindSymbol(msg, tag->valueSize - bIndex - 1, '(', &bIndex))
            return false;

        msg += bIndex + 1;
        *outValue = this->ReadValuePredict34Unsigned(msg, ')');
        return true;
    }

    inline bool CheckProcessHearthBeat(int testReqId) {
        /* just skip
        FixTag *tag = this->CurrentTag();
        if(!ReadCheck3SymbolTag(tag, TagCheckTestReqID, TagTestReqID))
            return false;

        this->ReadValuePredict324Unsigned(tag);
        this->MoveNext();
        */
        return true;
    }

    inline bool CheckProcessResendRequest() {
        FixTag *tag = this->CurrentTag();

        //if(!ReadCheck1SymbolTag(tag, TagCheckBeginSeqNo, TagBeginSeqNo))
        if(!ReadCheck1SymbolTagFast(tag))
            return false;
        this->m_resendRequestInfo->BeginSeqNo = this->ReadValuePredict324Unsigned(tag);
        this->MoveNext();

        tag = this->CurrentTag();
        //if(!ReadCheck2SymbolTag(tag, TagCheckEndSeqNo, TagEndSeqNo))
        if(!ReadCheck2SymbolTagFast(tag))
            return false;
        this->m_resendRequestInfo->EndSeqNo = this->ReadValuePredict324Unsigned(tag);
        //this->MoveNext();

        return true;
    }

    inline FixTag* Find2SymbolTagFromCurrent(int tagCheck, int tagId) {
        for(int i = this->m_currentTag; i < this->m_tagsCount; i++) {
            if(ReadCheck2SymbolTag(this->m_tags[i], tagCheck, tagId)) {
                this->m_currentTag = i;
                return this->m_tags[i];
            }
        }
        return NULL;
    }

    inline bool CheckProcessReject() {
        FixTag *tag = this->CurrentTag();

        this->ReadCheck2SymbolTagFast(tag);
        this->m_rejectInfo->RefMsgSeqNum = this->ReadValuePredict324Unsigned(tag);

        tag = this->Find2SymbolTagFromCurrent(TagCheckText, TagText);
        if(tag != NULL) {
            this->m_rejectInfo->Text = tag->value;
            this->m_rejectInfo->TextLength = tag->valueSize;
        }

        return true;
    }
};

#endif //HFT_ROBOT_FIXMESSAGE_H
