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

	this->msr = NULL;
	this->mss = NULL;
	this->olr = NULL;
	this->ols = NULL;
	this->tlr = NULL;
	this->tls = NULL;
	this->idf = NULL;
	this->isf = NULL;
	this->hr = NULL;
}

FeedChannel::~FeedChannel() {
}

void FeedChannel::SetConnection(FeedConnection *conn) { 
	conn->SetSenderCompId(this->m_senderCompId);
	conn->ChannelName(this->id);

	if (strcmp(conn->IdName(), "MSR") == 0)
		this->msr = conn;
	if (strcmp(conn->IdName(), "MSS") == 0)
		this->mss = conn;
	if (strcmp(conn->IdName(), "OLR") == 0)
		this->olr = conn;
	if (strcmp(conn->IdName(), "OLS") == 0)
		this->ols = conn;
	if (strcmp(conn->IdName(), "TLR") == 0)
		this->tlr = conn;
	if (strcmp(conn->IdName(), "TLS") == 0)
		this->tls = conn;
	if (strcmp(conn->IdName(), "IDF") == 0)
		this->idf = conn;
	if (strcmp(conn->IdName(), "ISF") == 0)
		this->isf = conn;
	if (strcmp(conn->IdName(), "H") == 0)
		this->hr = conn;
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
//	if(this->olr->Type() != FeedConnectionType::Incremental)
//		return false;
//	if(this->msr->Type() != FeedConnectionType::Incremental)
//		return false;
//	if(this->tlr->Type() != FeedConnectionType::Incremental)
//		return false;
//
//	if(this->ols->Type() != FeedConnectionType::Snapshot)
//		return false;
//	if(this->mss->Type() != FeedConnectionType::Snapshot)
//		return false;
//	if(this->tls->Type() != FeedConnectionType::Snapshot)
//		return false;
//
//    if(this->idf->Type() != FeedConnectionType::InstrumentDefinition)
//        return false;
//	if(this->hr->Type() != FeedConnectionType::HistoricalReplay)
//		return false;

	return true;
}

bool FeedChannel::Connect() { 
	DefaultLogManager::Default->StartLog(this->m_nameLogIndex, LogMessageCode::lmcFeedChannel_Connect);

	if(this->msr != 0)
		this->msr->SetSnapshot(this->mss);
	if(this->tlr != 0)
		this->tlr->SetSnapshot(this->tls);
	if(this->olr != 0)
		this->olr->SetSnapshot(this->ols);
	if(this->isf != 0)
		this->isf->SetSecurityDefinition(this->idf);

	if(this->msr != 0)
		this->msr->SetHistoricalReplay(this->hr);
	if(this->tlr != 0)
		this->tlr->SetHistoricalReplay(this->hr);
	if(this->olr != 0)
		this->olr->SetHistoricalReplay(this->hr);
	if(this->isf != 0)
		this->isf->SetHistoricalReplay(this->hr);

	if(!this->CheckConnections()) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	if(this->msr != 0)
		this->idf->AddConnectionToRecvSymbol(this->msr);
	if(this->olr != 0)
		this->idf->AddConnectionToRecvSymbol(this->olr);
	if(this->tlr != 0)
		this->idf->AddConnectionToRecvSymbol(this->tlr);
	if(this->isf != 0)
		this->idf->AddConnectionToRecvSymbol(this->isf);

	this->m_state = FeedChannelState::fchCollectSymbols;

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedChannel::Disconnect() { 
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcFeedChannel_Disconnect);

	bool result = true;
	
	result &= this->Disconnect(this->msr);
	result &= this->Disconnect(this->mss);
	result &= this->Disconnect(this->olr);
	result &= this->Disconnect(this->ols);
	result &= this->Disconnect(this->tlr);
	result &= this->Disconnect(this->tls);
	result &= this->Disconnect(this->idf);
	result &= this->Disconnect(this->isf);
	result &= this->Disconnect(this->hr);

	this->m_state = FeedChannelState::fchSuspend;

	DefaultLogManager::Default->EndLog(result);
	return result;
}
