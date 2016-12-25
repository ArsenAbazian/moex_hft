//
// Created by root on 11.12.16.
//

#ifndef HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
#define HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H

#include "../FeedConnection.h"
#include <stdio.h>

class InstrumentDefinitionTester{
    FeedConnection *olr;
    FeedConnection *ols;
    FeedConnection *tlr;
    FeedConnection *tls;
    FeedConnection *msr;
    FeedConnection *mss;
    FeedConnection *idf;

public:
    InstrumentDefinitionTester() {
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

        this->idf->AddConnectionToRecvSymbol(this->olr);
        this->idf->AddConnectionToRecvSymbol(this->ols);
        this->idf->AddConnectionToRecvSymbol(this->msr);
        this->idf->AddConnectionToRecvSymbol(this->mss);
        this->idf->AddConnectionToRecvSymbol(this->tlr);
        this->idf->AddConnectionToRecvSymbol(this->tls);
    }
    ~InstrumentDefinitionTester() {
        delete this->olr;
        delete this->ols;
        delete this->tlr;
        delete this->tls;
        delete this->msr;
        delete this->mss;
        delete this->idf;
    }

    void TestDefaults() {
        if(this->idf->ConnectionsToRecvSymbolsCount() != 6)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[0] != this->olr)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[1] != this->ols)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[2] != this->msr)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[3] != this->mss)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[4] != this->tlr)
            throw;
        if(this->idf->ConnectionsToRecvSymbols()[5] != this->tls)
            throw;
        if(this->idf->Type() != FeedConnectionType::InstrumentDefinition)
            throw;
    }

    void TestAddSymbol() {
        FastSecurityDefinitionInfo *info = new FastSecurityDefinitionInfo();
        if(!this->idf->ProcessSecurityDefinition(info))
            throw;
    }

    void Test() {
        TestDefaults();
        TestAddSymbol();
    }
};

#endif //HFT_ROBOT_INSTRUMENTDEFINITIONTESTER_H
