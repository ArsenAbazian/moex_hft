//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTESTER_H
#define HFT_ROBOT_FEEDCONNECTIONTESTER_H

#include "InstrumentDefinitionTester.h"
#include "OrderBookTester.h"
#include "OrderTester.h"
#include "TradeTester.h"

class TestFeedMessage{
public:
    AutoAllocatePointerList<TestFeedMessage>    *Allocator;
    LinkedPointer<TestFeedMessage>              *Pointer;
    bool                                        Used;
    char                                        Type[10];
    int                                         TemplateId;
    int                                         Count;

    unsigned char                               Bytes[1700];
    char                                        Text[1700];
};

class FeedConnectionTester {

    bool ReadNextQuote(FILE *fp) {
        while(!feof(fp)) {
            int chr = fgetc(fp);
            if(chr == '\'')
                return true;
        }
        return false;
    }
    const char* IsFeedName(const char *feed_abr) {
        static const char* feeds[6] {
                "OBR",
                "OBS",
                "TLR",
                "TLS",
                "OLS",
                "OLR"
        };

        for(int i = 0; i < 6; i++) {
            if(feeds[i][0] == feed_abr[0] && feeds[i][1] == feed_abr[1] && feeds[i][2] == feed_abr[2] && feed_abr[3] == '\'')
                return feeds[i];
        }
        return 0;
    }
    int AsciToValue(char ascii) {
        char asci_table[16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

        for(int i = 0; i < 16; i++) {
            if(ascii == asci_table[i])
                return i;
        }
        return 0;
    }
public:
    FeedConnectionTester() {
        RobotSettings::DefaultFeedConnectionSendBufferSize = 1 * 1024 * 1024;
        RobotSettings::DefaultFeedConnectionSendItemsCount = 100;
        RobotSettings::DefaultFeedConnectionRecvBufferSize = 2 * 1024 * 1024;
        RobotSettings::DefaultFeedConnectionRecvItemsCount = 500;
    }
    AutoAllocatePointerList<TestFeedMessage>* GetMessagesFromLog(const char *fileName) {
        FILE *fp = fopen(fileName, "rt");
        if(fp == 0)
            throw;

        AutoAllocatePointerList<TestFeedMessage> *res = new AutoAllocatePointerList<TestFeedMessage>(128, 128);
        FastProtocolManager manager;

        char feed_abr[4];
        char data[3];
        fseek(fp, 0, SEEK_SET);

        while(!feof(fp)) {
            if(!ReadNextQuote(fp))
                break;
            fread(feed_abr, 1, 4, fp);
            if(!IsFeedName(feed_abr))
                continue;
            if(!ReadNextQuote(fp))
                break;
            TestFeedMessage *msg = res->NewItem();
            if(msg == 0)
                throw;
            int index = 0;
            int textIndex = 0;
            UINT64 pmap[4];
            while(true) {
                fread((msg->Text + textIndex), 1, 3, fp);
                bool isEnd = msg->Text[textIndex + 2] == '\'';
                int value = this->AsciToValue(msg->Text[textIndex]) * 16 + this->AsciToValue(msg->Text[textIndex + 1]);
                msg->Bytes[index] = (unsigned char)value;
                msg->Count = index + 1;
                textIndex += 3;
                if(isEnd) {
                    msg->Text[textIndex] = '\0';
                    manager.SetNewBuffer(msg->Bytes, msg->Count);
                    manager.ReadMsgSeqNumber();
                    manager.ParsePresenceMap(pmap);
                    msg->TemplateId = manager.ReadUInt32_Mandatory();
                    break;
                }
                index++;
            }
        }
        fclose(fp);
        return res;
    }

    void TestLog(const char *fileName) {
        AutoAllocatePointerList<TestFeedMessage> *messages = GetMessagesFromLog(fileName);
        LinkedPointer<TestFeedMessage> *ptr = messages->ListCore()->Start();
        LinkedPointer<TestFeedMessage> *end = messages->ListCore()->End();

        FeedConnection_FOND_OBR *obr_fond = new FeedConnection_FOND_OBR();
        FeedConnection_CURR_OBR *obr_curr = new FeedConnection_CURR_OBR();
        FeedConnection_FOND_OBS *obs_fond = new FeedConnection_FOND_OBS();
        FeedConnection_CURR_OBS *obs_curr = new FeedConnection_CURR_OBS();
        FeedConnection_FOND_OLR *olr_fond = new FeedConnection_FOND_OLR();
        FeedConnection_CURR_OLR *olr_curr = new FeedConnection_CURR_OLR();
        FeedConnection_FOND_OLS *ols_fond = new FeedConnection_FOND_OLS();
        FeedConnection_CURR_OLS *ols_curr = new FeedConnection_CURR_OLS();
        FeedConnection_FOND_TLR *tlr_fond = new FeedConnection_FOND_TLR();
        FeedConnection_CURR_TLR *tlr_curr = new FeedConnection_CURR_TLR();
        FeedConnection_FOND_TLS *tls_fond = new FeedConnection_FOND_TLS();
        FeedConnection_CURR_TLS *tls_curr = new FeedConnection_CURR_TLS();

        int processedMsgCount = 0;
        while(true) {

            FeedConnection *fc = 0;
            TestFeedMessage *msg = ptr->Data();
            switch(msg->TemplateId) {
                case 2101:
                case 2102:
                case 2422:
                case 2108:
                    fc = obr_fond;
                    break;
                case 3512:
                    fc = obr_curr;
                    break;
                case 2412:
                    fc = obs_fond;
                    break;
                case 3502:
                    fc = obs_curr;
                    break;
                case 2410:
                    fc = ols_fond;
                    break;
                case 3500:
                    fc = ols_curr;
                    break;
                case 2420:
                    fc = olr_fond;
                    break;
                case 3510:
                    fc = olr_curr;
                    break;
                case 2411:
                    fc = tls_fond;
                    break;
                case 3501:
                    fc = tls_curr;
                    break;
                case 2421:
                    fc = tlr_fond;
                    break;
                case 3511:
                    fc = tlr_curr;
                    break;
            }
            if(!fc->ProcessIncrementalCore(msg->Bytes, msg->Count))
                throw;
            if(fc->m_fastProtocolManager->MessageLength() != msg->Count)
                throw;
            fc->m_fastProtocolManager->Print();
            if(ptr == end)
                break;
            ptr = ptr->Next();
            processedMsgCount++;
        }


        delete obr_fond;
        delete obr_curr;
        delete obs_fond;
        delete obs_curr;
        delete olr_fond;
        delete olr_curr;
        delete ols_fond;
        delete ols_curr;
        delete tlr_fond;
        delete tlr_curr;
        delete tls_fond;
        delete tls_curr;
    }

    void Test() {
        RobotSettings::MarketDataMaxSymbolsCount = 10;
        RobotSettings::MarketDataMaxSessionsCount = 5;
        RobotSettings::MarketDataMaxEntriesCount = 32;

        TradeTester tt;
        tt.Test();
        OrderTester ot;
        ot.Test();
        OrderBookTester obt;
        obt.Test();
        InstrumentDefinitionTester ids;
        ids.Test();
        //TestLog("/home/arsen/Documents/hft_robot/hft/test/log5");
        //TestLog("/home/arsen/Documents/hft_robot/hft/test/log6");

        RobotSettings::MarketDataMaxSymbolsCount = 128;
        RobotSettings::MarketDataMaxSessionsCount = 128;
        RobotSettings::MarketDataMaxEntriesCount = 256;
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTESTER_H
