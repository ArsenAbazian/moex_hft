#include "FeedChannel.h"
#include "Managers/LogManager.h"

FeedChannel::FeedChannel(const char *id, const char *name) {
	strcpy(this->id, id);
	strcpy(this->name, name);

    this->m_idLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->id);
    this->m_nameLogIndex = DefaultLogMessageProvider::Default->RegisterText(this->name);

	this->m_senderCompId = 0;
	this->m_password = 0;
	this->m_state = FeedChannelState::fchSuspend;

	this->statisticsIncremental = NULL;
	this->statisticsSnapshot = NULL;
	this->ordersIncremental = NULL;
	this->ordersSnapshot = NULL;
	this->tradesIncremental = NULL;
	this->tradesSnapshot = NULL;
	this->instrumentDefinition = NULL;
	this->instrumentStatus = NULL;
	this->historicalReplay = NULL;
}

FeedChannel::~FeedChannel() {
}

void FeedChannel::SetConnection(FeedConnection *conn) { 
	conn->SetSenderCompId(this->m_senderCompId);
	conn->ChannelName(this->id);

	if (strcmp(conn->IdName(), "MSR") == 0)
		this->statisticsIncremental = conn;
	if (strcmp(conn->IdName(), "MSS") == 0)
		this->statisticsSnapshot = conn;
	if (strcmp(conn->IdName(), "OLR") == 0)
		this->ordersIncremental = conn;
	if (strcmp(conn->IdName(), "OLS") == 0)
		this->ordersSnapshot = conn;
	if (strcmp(conn->IdName(), "TLR") == 0)
		this->tradesIncremental = conn;
	if (strcmp(conn->IdName(), "TLS") == 0)
		this->tradesSnapshot = conn;
	if (strcmp(conn->IdName(), "IDF") == 0)
		this->instrumentDefinition = conn;
	if (strcmp(conn->IdName(), "ISF") == 0)
		this->instrumentStatus = conn;
	if (strcmp(conn->IdName(), "H") == 0)
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
	if(this->ordersIncremental->Type() != FeedConnectionType::Incremental)
		return false;
	if(this->statisticsIncremental->Type() != FeedConnectionType::Incremental)
		return false;
	if(this->tradesIncremental->Type() != FeedConnectionType::Incremental)
		return false;

	if(this->ordersSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;
	if(this->statisticsSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;
	if(this->tradesSnapshot->Type() != FeedConnectionType::Snapshot)
		return false;

    if(this->instrumentDefinition->Type() != FeedConnectionType::InstrumentDefinition)
        return false;
	if(this->historicalReplay->Type() != FeedConnectionType::HistoricalReplay)
		return false;

	return true;
}

bool FeedChannel::Connect() { 
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcFeedChannel_Connect);

	this->statisticsIncremental->SetSnapshot(this->statisticsSnapshot);
	this->tradesIncremental->SetSnapshot(this->tradesSnapshot);
	this->ordersIncremental->SetSnapshot(this->ordersSnapshot);
	this->instrumentStatus->SetSecurityDefinition(this->instrumentDefinition);

	this->statisticsIncremental->SetHistoricalReplay(this->historicalReplay);
	this->tradesIncremental->SetHistoricalReplay(this->historicalReplay);
	this->ordersIncremental->SetHistoricalReplay(this->historicalReplay);
	this->instrumentStatus->SetHistoricalReplay(this->historicalReplay);

	this->statisticsSnapshot->SetHistoricalReplay(this->historicalReplay);
	this->tradesSnapshot->SetHistoricalReplay(this->historicalReplay);
	this->ordersSnapshot->SetHistoricalReplay(this->historicalReplay);
	this->instrumentDefinition->SetHistoricalReplay(this->historicalReplay);

	if(!this->CheckConnections()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	this->m_state = FeedChannelState::fchCollectSymbols;
	this->instrumentDefinition->AddConnectionToRecvSymbol(this->statisticsIncremental);
	this->instrumentDefinition->AddConnectionToRecvSymbol(this->ordersIncremental);
	this->instrumentDefinition->AddConnectionToRecvSymbol(this->tradesIncremental);
	//this->instrumentDefinition->AddConnectionToRecvSymbol(this->instrumentStatus);
	this->instrumentDefinition->Start();

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedChannel::Disconnect() { 
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcFeedChannel_Disconnect);

	bool result = true;
	
	result &= this->Disconnect(this->statisticsIncremental);
	result &= this->Disconnect(this->statisticsSnapshot);
	result &= this->Disconnect(this->ordersIncremental);
	result &= this->Disconnect(this->ordersSnapshot);
	result &= this->Disconnect(this->tradesIncremental);
	result &= this->Disconnect(this->tradesSnapshot);
	result &= this->Disconnect(this->instrumentDefinition);
	result &= this->Disconnect(this->instrumentStatus);
	result &= this->Disconnect(this->historicalReplay);

	this->m_state = FeedChannelState::fchSuspend;

	DefaultLogManager::Default->EndLog(result);
	return result;
}
