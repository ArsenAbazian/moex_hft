#include "Robot.h"
#include <tinyxml2.h>
#include <cstdio>

Robot::Robot() {
	this->channelsCount = 0;
	memset(this->channels, 0, sizeof(FeedChannel*) * MARKET_INFO_CAPACITY);
}

Robot::~Robot() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_Robot);

    bool result = DisconnectMarkets();
	delete this->protocolManager;

    DefaultLogManager::Default->EndLog(result);
}

bool Robot::ConnectMarkets() {
	
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_ConnectMarkets);
	for (int i = 0; i < this->marketCount; i++) {
		if (!this->markets[i]->Connect()) {
			DefaultLogManager::Default->EndLog(false);
#ifdef ROBOT_WORK_ANYWAY
            continue;
#else
			return false;
#endif
		}
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool Robot::DisconnectMarkets() {
	bool success = true;
	for (int i = 0; i < this->marketCount; i++) {
		success &= this->markets[i]->Disconnect();
	}
	return success;
}

bool Robot::AddDefaultTestChannels() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_AddDefaultTestChannels);
#pragma region AddDefaultChannels_GeneratedCode
	FeedChannel *curr = new FeedChannel("CURR", "Currency Exchange Market");

	FeedConnection *msr_curr = new FeedConnection_CURR_MSR("MSR", "Statisctics Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.7", 9027, "10.50.129.200", "239.192.112.135", 9227);
	FeedConnection *mss_curr = new FeedConnection_CURR_MSS("MSS", "Statisctics Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.8", 9028, "10.50.129.200", "239.192.112.136", 9228);
	FeedConnection *olr_curr = new FeedConnection_CURR_OLR("OLR", "Orders Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.1", 9021, "10.50.129.200", "239.192.112.129", 9221);
	FeedConnection *ols_curr = new FeedConnection_CURR_OLS("OLS", "Orders Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.2", 9022, "10.50.129.200", "239.192.112.130", 9222);
	FeedConnection *tlr_curr = new FeedConnection_CURR_TLR("TLR", "Trades Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.5", 9025, "10.50.129.200", "239.192.112.133", 9225);
	FeedConnection *tls_curr = new FeedConnection_CURR_TLS("TLS", "Trades Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.6", 9026, "10.50.129.200", "239.192.112.134", 9226);
	FeedConnection *idf_curr = new FeedConnection_CURR_IDF("IDF", "Instrument Replay", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.9", 9029, "10.50.129.200", "239.192.112.137", 9229);
	FeedConnection *isf_curr = new FeedConnection_CURR_ISF("ISF", "Instrument Status", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.10", 9030, "10.50.129.200", "239.192.112.138", 9230);
	FeedConnection *h_curr = new FeedConnection_CURR_H("H", "Historical Replay", 'H', FeedConnectionProtocol::TCP_IP, "1.1.7.200", 20000);

	curr->SetConnection(msr_curr);
	curr->SetConnection(mss_curr);
	curr->SetConnection(olr_curr);
	curr->SetConnection(ols_curr);
	curr->SetConnection(tlr_curr);
	curr->SetConnection(tls_curr);
	curr->SetConnection(idf_curr);
	curr->SetConnection(isf_curr);
	curr->SetConnection(h_curr);

	this->AddChannel(curr);
	FeedChannel *fond = new FeedChannel("FOND", "Stock Exchange Market");

	FeedConnection *msr_fond = new FeedConnection_FOND_MSR("MSR", "Statisctics Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.7", 9117, "10.50.129.200", "239.192.113.135", 9317);
	FeedConnection *mss_fond = new FeedConnection_FOND_MSS("MSS", "Statisctics Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.8", 9118, "10.50.129.200", "239.192.113.136", 9318);
	FeedConnection *olr_fond = new FeedConnection_FOND_OLR("OLR", "Orders Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.1", 9111, "10.50.129.200", "239.192.113.129", 9311);
	FeedConnection *ols_fond = new FeedConnection_FOND_OLS("OLS", "Orders Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.2", 9112, "10.50.129.200", "239.192.113.130", 9312);
	FeedConnection *tlr_fond = new FeedConnection_FOND_TLR("TLR", "Trades Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.5", 9115, "10.50.129.200", "239.192.113.133", 9315);
	FeedConnection *tls_fond = new FeedConnection_FOND_TLS("TLS", "Trades Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.6", 9116, "10.50.129.200", "239.192.113.134", 9316);
	FeedConnection *idf_fond = new FeedConnection_FOND_IDF("IDF", "Instrument Replay", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.9", 9119, "10.50.129.200", "239.192.113.137", 9319);
	FeedConnection *isf_fond = new FeedConnection_FOND_ISF("ISF", "Instrument Status", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.10", 9120, "10.50.129.200", "239.192.113.138", 9320);
	FeedConnection *h_fond = new FeedConnection_FOND_H("H", "Historical Replay", 'H', FeedConnectionProtocol::TCP_IP, "1.1.7.200", 10000);

	fond->SetConnection(msr_fond);
	fond->SetConnection(mss_fond);
	fond->SetConnection(olr_fond);
	fond->SetConnection(ols_fond);
	fond->SetConnection(tlr_fond);
	fond->SetConnection(tls_fond);
	fond->SetConnection(idf_fond);
	fond->SetConnection(isf_fond);
	fond->SetConnection(h_fond);

	this->AddChannel(fond);
#pragma endregion
    /*
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.LoadFile("/tmp/config_test.xml");

    if(res != tinyxml2::XMLError::XML_SUCCESS) {
        DefaultLogManager::Default->EndLog(false, strerror(errno));
        return false;
    }
    Stopwatch *w = new Stopwatch();
    tinyxml2::XMLElement *cfgNode = doc.FirstChildElement("configuration");
    tinyxml2::XMLElement *channel = cfgNode->FirstChildElement("channel");
    while(channel != 0) {
        FeedChannel *fc = new FeedChannel(channel->Attribute("id"), channel->Attribute("label"));
        tinyxml2::XMLElement *connections = channel->FirstChildElement("connections");
        tinyxml2::XMLElement *connection = connections->FirstChildElement("connection");
        while(connection != 0) {
            FeedConnection *fconn = 0;

            tinyxml2::XMLElement *type = connection->FirstChildElement("type");
            tinyxml2::XMLElement *protocol = connection->FirstChildElement("protocol");
            FeedConnectionProtocol pt = strcmp(protocol->FirstChild()->Value(), "TCP/IP") == 0? FeedConnectionProtocol::TCP_IP: FeedConnectionProtocol::UDP_IP;

            tinyxml2::XMLElement *feedA = connection->FirstChildElement("feed");
            if(feedA != 0) {
                tinyxml2::XMLNode *srcIpA = feedA->FirstChildElement("src-ip")->FirstChild();
                tinyxml2::XMLNode *ipA = feedA->FirstChildElement("ip")->FirstChild();
                tinyxml2::XMLNode *portA = feedA->FirstChildElement("port")->FirstChild();

                tinyxml2::XMLElement *feedB = feedA->NextSiblingElement("feed");
                tinyxml2::XMLNode *srcIpB = feedB->FirstChildElement("src-ip")->FirstChild();
                tinyxml2::XMLNode *ipB = feedB->FirstChildElement("ip")->FirstChild();
                tinyxml2::XMLNode *portB = feedB->FirstChildElement("port")->FirstChild();

                const char *feedChannelId = fc->Id();
                const char *id = connection->Attribute("id");
                const char *feedType = type->Attribute("feed-type");
                char value = type->FirstChild()->Value()[0];
                const char *srcIpAString = srcIpA->Value();
                const char *ipAString = ipA->Value();
                int portAValue = atoi(portA->Value());
                const char *srcIpBString = srcIpB->Value();
                const char *ipBString = ipB->Value();
                int portBValue = atoi(portB->Value());

                w->Start();
                fconn = CreateConnectionCore(feedChannelId,
                                             id,
                                             feedType,
                                             value,
                                             pt,
                                             srcIpAString,
                                             ipAString,
                                             portAValue,
                                             srcIpBString,
                                             ipBString,
                                             portBValue);
            }
            else {
                tinyxml2::XMLNode *ip = connection->FirstChildElement("ip")->FirstChild();
                tinyxml2::XMLNode *port = connection->FirstChildElement("port")->FirstChild();

                const char *feedChannelId = fc->Id();
                const char *id = connection->Attribute("id");
                const char *feedType = type->Attribute("feed-type");
                char value = type->FirstChild()->Value()[0];
                const char *ipString = ip->Value();
                int portValue = atoi(port->Value());

                w->Start();
                fconn = CreateConnectionCore(feedChannelId,
                                             id,
                                             feedType,
                                             value,
                                             pt,
                                             "",
                                             ipString,
                                             portValue,
                                             "",
                                             "",
                                             0);
            }
            fc->SetConnection(fconn);
            connection = connection->NextSiblingElement("connection");
        }

        AddChannel(fc);
        channel = channel->NextSiblingElement("channel");
    }
    delete w;
     */
    DefaultLogManager::Default->EndLog(true);
    return true;
}

FeedConnection* Robot::CreateConnectionCore(const char *feedChannelId, const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) {
    if(strcmp(feedChannelId, "CURR") == 0) { // CURR
        if(strcmp(id, "MSR") == 0)
            return new FeedConnection_CURR_MSR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "MSS") == 0)
            return new FeedConnection_CURR_MSS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "OLR") == 0)
            return new FeedConnection_CURR_OLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "OLS") == 0)
            return new FeedConnection_CURR_OLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "TLR") == 0)
            return new FeedConnection_CURR_TLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "TLS") == 0)
            return new FeedConnection_CURR_TLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "IDF") == 0)
            return new FeedConnection_CURR_IDF(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "H") == 0)
            return new FeedConnection_CURR_H(id, name, value, protocol, aIp, aPort);
    }
    else { // FOND
        if(strcmp(id, "MSR") == 0)
            return new FeedConnection_FOND_MSR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "MSS") == 0)
            return new FeedConnection_FOND_MSS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "OLR") == 0)
            return new FeedConnection_FOND_OLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "OLS") == 0)
            return new FeedConnection_FOND_OLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "TLR") == 0)
            return new FeedConnection_FOND_TLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "TLS") == 0)
            return new FeedConnection_FOND_TLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "IDF") == 0)
            return new FeedConnection_FOND_IDF(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if(strcmp(id, "H") == 0)
            return new FeedConnection_FOND_H(id, name, value, protocol, aIp, aPort);
    }
    return new FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
}

bool Robot::Run() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_Run);
	
	if(!this->AddDefaultTestMarkets()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if(!this->AddDefaultTestChannels()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

    if(!this->SetFeedChannelsForMarkets()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    if(!this->ConnectMarkets()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    if(!this->DoWork()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool Robot::DoWork() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_DoWork);

    this->m_currMarket->Enable(false);
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!this->m_currMarket->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            DefaultLogManager::Default->Print();
            return false;
        }
        if (!this->m_fondMarket->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            DefaultLogManager::Default->Print();
            return false;
        }
        if(!this->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            DefaultLogManager::Default->Print();
            return false;
        }
        if(!this->Working())
            break;
    }

    DefaultLogManager::Default->Print();
    DefaultLogManager::Default->EndLog(true);
    return true;
}

