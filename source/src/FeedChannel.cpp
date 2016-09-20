#include "FeedChannel.h"
#include "LogManager.h"

FeedChannel::FeedChannel(const char *id, const char *name) {
	strcpy(this->id, id);
	strcpy(this->name, name);

    this->m_idLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->id);
    this->m_nameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->name);

	this->orderBookIncremental = NULL;
	this->orderBookSnapshot = NULL;
	this->statisticsIncremental = NULL;
	this->statisticsSnapshot = NULL;
	this->ordersIncremental = NULL;
	this->ordersSnapshot = NULL;
	this->tradesIncremental = NULL;
	this->tradesSnapshot = NULL;
	this->instrumentReplay = NULL;
	this->instrumentStatus = NULL;
	this->historicalReplay = NULL;
}

FeedChannel::~FeedChannel() {
}

void FeedChannel::SetConnection(FeedConnection *conn) { 
	conn->SetSenderCompId(this->m_senderCompId);
	if (strcmp(conn->Id(), "OBR") == 0)
		this->orderBookIncremental = conn;
	if (strcmp(conn->Id(), "OBS") == 0)
		this->orderBookSnapshot = conn;
	if (strcmp(conn->Id(), "MSR") == 0)
		this->statisticsIncremental = conn;
	if (strcmp(conn->Id(), "MSS") == 0)
		this->statisticsSnapshot = conn;
	if (strcmp(conn->Id(), "OLR") == 0)
		this->ordersIncremental = conn;
	if (strcmp(conn->Id(), "OLS") == 0)
		this->ordersSnapshot = conn;
	if (strcmp(conn->Id(), "TLR") == 0)
		this->tradesIncremental = conn;
	if (strcmp(conn->Id(), "TLS") == 0)
		this->tradesSnapshot = conn;
	if (strcmp(conn->Id(), "IDF") == 0)
		this->instrumentReplay = conn;
	if (strcmp(conn->Id(), "ISF") == 0)
		this->instrumentStatus = conn;
	if (strcmp(conn->Id(), "H") == 0)
		this->historicalReplay = conn;
}

bool FeedChannel::Connect(FeedConnection *conn) {
	if (conn == NULL)
		return false;
	return conn->Connect();
}
bool FeedChannel::Disconnect(FeedConnection *conn) { 
	if (conn == NULL)
		return false;
	return conn->Disconnect();
}

bool FeedChannel::CheckConnections() {
	if(this->orderBookIncremental->Type() != FeedConnectionType::Incremental)
		return false;
	if(this->ordersIncremental->Type() != FeedConnectionType::Incremental)
		return false;
	if(this->statisticsIncremental->Type() != FeedConnectionType::Incremental)
		return false;
	if(this->tradesIncremental->Type() != FeedConnectionType::Incremental)
		return false;

	if(this->orderBookSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;
	if(this->ordersSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;
	if(this->statisticsSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;
	if(this->tradesSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;

	return true;
}

bool FeedChannel::Connect() { 
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcFeedChannel_Connect);

	if(!this->CheckConnections()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	this->orderBookIncremental->SetSnapshot(this->orderBookSnapshot);
	this->statisticsIncremental->SetSnapshot(this->statisticsSnapshot);
	this->tradesIncremental->SetSnapshot(this->tradesSnapshot);
	this->ordersIncremental->SetSnapshot(this->ordersSnapshot);
	this->instrumentReplay->SetSnapshot(this->instrumentStatus);

	if (!this->Connect(this->orderBookIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
    /*
	if (!this->Connect(this->statisticsIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->ordersIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->tradesIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->instrumentStatus)) { 
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
    */
    /*
    if(!this->Connect(this->orderBookSnapshot)) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!this->Connect(this->statisticsSnapshot)) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!this->Connect(this->ordersSnapshot)) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!this->Connect(this->tradesSnapshot)) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!this->Connect(this->instrumentReplay)) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    */

	this->orderBookIncremental->Start();
	//this->statisticsIncremental->Start();
	//this->ordersIncremental->Start();
	//this->tradesIncremental->Start();
	//this->instrumentStatus->Start();

	// not needed....
	//this->orderBookSnapshot->Start();
	//this->statisticsSnapshot->Start();
	//this->ordersSnapshot->Start();
	//this->tradesSnapshot->Start();
	//this->instrumentReplay->Start();

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedChannel::Disconnect() { 
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcFeedChannel_Disconnect);

	bool result = true;
	
	result &= this->Disconnect(this->orderBookIncremental);
	result &= this->Disconnect(this->orderBookSnapshot);
	result &= this->Disconnect(this->statisticsIncremental);
	result &= this->Disconnect(this->statisticsSnapshot);
	result &= this->Disconnect(this->ordersIncremental);
	result &= this->Disconnect(this->ordersSnapshot);
	result &= this->Disconnect(this->tradesIncremental);
	result &= this->Disconnect(this->tradesSnapshot);
	result &= this->Disconnect(this->instrumentReplay);
	result &= this->Disconnect(this->instrumentStatus);
	result &= this->Disconnect(this->historicalReplay);

	DefaultLogManager::Default->EndLog(result);
	return result;
}
