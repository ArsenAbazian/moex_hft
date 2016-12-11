//
// Created by root on 11.12.16.
//

#ifndef HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
#define HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H

#include "../FeedConnection.h"
#include <stdio.h>

class InstrumentDefinitionTester{
    FeedConnection *obr;
    FeedConnection *obs;
    FeedConnection *olr;
    FeedConnection *ols;
    FeedConnection *tlr;
    FeedConnection *tls;
    FeedConnection *msr;
    FeedConnection *mss;
    FeedConnection *idf;

public:
    InstrumentDefinitionTester() {
        this->obr = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->obs = new FeedConnection_FOND_OBS("OBS", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->olr = new FeedConnection_FOND_OLR("OLR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->ols = new FeedConnection_FOND_OLS("OLS", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->tlr = new FeedConnection_FOND_TLR("TSR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->tls = new FeedConnection_FOND_TLS("TSS", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->msr = new FeedConnection_FOND_MSR("MSR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->mss = new FeedConnection_FOND_MSS("MSS", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->idf = new FeedConnection_FOND_IDF("IDF", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);

    }
    ~InstrumentDefinitionTester() {
        delete this->obr;
        delete this->obs;
        delete this->olr;
        delete this->ols;
        delete this->tlr;
        delete this->tls;
        delete this->msr;
        delete this->mss;
        delete this->idf;
    }

    void TestDefaults() {
        if(this->idf->FeedObr() == 0)
            throw;
        if(this->idf->FeedObs() == 0)
            throw;
        if(this->idf->FeedOlr() == 0)
            throw;
        if(this->idf->FeedOls() == 0)
            throw;
        if(this->idf->FeedTlr() == 0)
            throw;
        if(this->idf->FeedTls() == 0)
            throw;
        if(this->idf->FeedMsr() == 0)
            throw;
        if(this->idf->FeedMss() == 0)
            throw;
    }

    void Test() {
        TestDefaults();
    }
};

#endif //HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
