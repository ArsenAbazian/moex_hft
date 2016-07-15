#include "Robot.h"
#include <tinyxml2.h>

Robot::Robot()
{
	this->channelsCount = 0;
	memset(this->channels, 0, sizeof(FeedChannel*) * MARKET_INFO_CAPACITY);
}

Robot::~Robot()
{
    DefaultLogManager::Default->StartLog("Robot::~Robot");

    bool result = DisconnectChannels();
    result &= DisconnectMarkets();
	delete this->protocolManager;

    DefaultLogManager::Default->EndLog(result);
}

bool Robot::ConnectChannels() { 
	DefaultLogManager::Default->StartLog("Robot::ConnectChannels");
	for (int i = 0; i < this->channelsCount; i++) { 
		if (!this->channels[i]->Connect()) {
			DefaultLogManager::Default->EndLog(false);
			return false;
		}
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool Robot::DisconnectChannels() { 
	bool success = true;
	for (int i = 0; i < this->channelsCount; i++) { 
		success &= this->channels[i]->Disconnect();
	}
	return success;
}

bool Robot::LogonChannels() { 
	bool success = true;
	for (int i = 0; i < this->channelsCount; i++) { 
		success &= this->channels[i]->Logon();
	}
	return success;
}

bool Robot::LogoutChannels() {
	bool success = true;
	for (int i = 0; i < this->channelsCount; i++) {
		success &= this->channels[i]->Logout();
	}
	return success;
}


bool Robot::ConnectMarkets() {
	
	DefaultLogManager::Default->StartLog("Robot::ConnectMarkets...");
	for (int i = 0; i < this->marketCount; i++) {
		if (!this->markets[i]->Connect()) {
			DefaultLogManager::Default->EndLog(false);
			return false;
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

bool Robot::LogonMarkets() {
	bool success = true;
	for (int i = 0; i < this->marketCount; i++) {
		success &= this->markets[i]->Logon();
	}
	return success;
}

bool Robot::LogoutMarkets() {
	bool success = true;
	for (int i = 0; i < this->marketCount; i++) {
		success &= this->markets[i]->Logout();
	}
	return success;
}

bool Robot::AddDefaultTestChannels() {
    DefaultLogManager::Default->StartLog("Robot::AddDefaultTestChannels");
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.LoadFile("/tmp/config_test.xml");

    if(res != tinyxml2::XMLError::XML_SUCCESS) {
        DefaultLogManager::Default->EndLog(false, strerror(errno));
        return false;
    }
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

                fconn = CreateConnectionCore(fc->Id(),
                                             connection->Attribute("id"),
                                             type->Attribute("feed-type"),
                                             type->FirstChild()->Value()[0],
                                             pt,
                                             srcIpA->Value(),
                                             ipA->Value(),
                                             atoi(portA->Value()),
                                             srcIpB->Value(),
                                             ipB->Value(),
                                             atoi(portB->Value()));
            }
            else {
                tinyxml2::XMLNode *ip = connection->FirstChildElement("ip")->FirstChild();
                tinyxml2::XMLNode *port = connection->FirstChildElement("port")->FirstChild();

                fconn = CreateConnectionCore(fc->Id(),
                                             connection->Attribute("id"),
                                             type->Attribute("feed-type"),
                                             type->FirstChild()->Value()[0],
                                             pt,
                                             "",
                                             ip->Value(),
                                             atoi(port->Value()),
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
    DefaultLogManager::Default->EndLog(true);
    return true;
}

FeedConnection* Robot::CreateConnectionCore(const char *feedChannelId, const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) {
    if (strcmp(feedChannelId, "CURR")) { // CURR
        if (strcmp(id, "OBR"))
            return new FeedConnection_CURR_OBR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "OBS"))
            return new FeedConnection_CURR_OBS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "MSR"))
            return new FeedConnection_CURR_MSR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "MSS"))
            return new FeedConnection_CURR_MSS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "OLR"))
            return new FeedConnection_CURR_OLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "OLS"))
            return new FeedConnection_CURR_OLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "TLR"))
            return new FeedConnection_CURR_TLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "TLS"))
            return new FeedConnection_CURR_TLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
    }
    else { // FOND
        if (strcmp(id, "OBR"))
            return new FeedConnection_FOND_OBR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "OBS"))
            return new FeedConnection_FOND_OBS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "MSR"))
            return new FeedConnection_FOND_MSR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "MSS"))
            return new FeedConnection_FOND_MSS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "OLR"))
            return new FeedConnection_FOND_OLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "OLS"))
            return new FeedConnection_FOND_OLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "TLR"))
            return new FeedConnection_FOND_TLR(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
        if (strcmp(id, "TLS"))
            return new FeedConnection_FOND_TLS(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
    }
    return new FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort);
}

bool Robot::Run() { 
    DefaultLogManager::Default->StartLog("Robot::Run");
	
	if(!this->AddDefaultTestMarkets()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if(!this->AddDefaultTestChannels()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if (!this->ConnectMarkets()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if (!this->ConnectChannels()) { 
		this->DisconnectMarkets();
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	DefaultLogManager::Default->EndLog(true);
	return true;
}

//bool Robot::Logon(MarketInfo *info) { 
//	bool success = true;
//	success &= this->Logon(info->Trade());
//	success &= this->Logon(info->TradeCapture());
//	success &= this->Logon(info->TradeDropCopy());
//
//	return success;
//}
//bool Robot::Logout(MarketInfo *info) {
//	bool success = true;
//	success &= this->Logout(info->Trade());
//	success &= this->Logout(info->TradeCapture());
//	success &= this->Logout(info->TradeDropCopy());
//
//	return success;
//}
//bool Robot::Logon(MarketServerInfo *info) { 
//	return info->Logon();
//}
//
//bool Robot::Logout(MarketServerInfo *info) { 
//	return info->Logout();
//}
