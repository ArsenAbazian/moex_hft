#include "Robot.h"
#include "FeedChannel.h"
#include <cstdio>
#include "ProgramStatistics.h"

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
    DefaultLogManager::Default->EndLog(true);
    return true;
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

    //this->m_fondMarket->Enable(false);
	Stopwatch *w = new Stopwatch();
	w->Start();
	unsigned int cycleCount = 0;

    // collect data first
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!this->m_currMarket->FeedChannel()->CollectSecurityDefinitions()) {
            DefaultLogManager::Default->EndLog(false);
            DefaultLogManager::Default->Print();
            return false;
        }
        if (!this->m_fondMarket->FeedChannel()->CollectSecurityDefinitions()) {
            DefaultLogManager::Default->EndLog(false);
            DefaultLogManager::Default->Print();
            return false;
        }

        if(this->m_currMarket->FeedChannel()->InstrumentDefinition()->IsIdfDataCollected())
            this->m_currMarket->FeedChannel()->InstrumentDefinition()->Stop();
        if(this->m_fondMarket->FeedChannel()->InstrumentDefinition()->IsIdfDataCollected())
            this->m_fondMarket->FeedChannel()->InstrumentDefinition()->Stop();

        if(this->m_currMarket->FeedChannel()->InstrumentDefinition()->IsIdfDataCollected() &&
                this->m_fondMarket->FeedChannel()->InstrumentDefinition()->IsIdfDataCollected()) {
            break;
        }
        if(w->ElapsedSeconds() > 3) {
            ProgramStatistics::Current->FondIdfProcessedCount(this->m_fondMarket->FeedChannel()->InstrumentDefinition()->MsgSeqNo());
            ProgramStatistics::Current->CurrIdfProcessedCount(this->m_currMarket->FeedChannel()->InstrumentDefinition()->MsgSeqNo());

            w->Reset();

            printf("3 sec. Changes------------------------\n");
            ProgramStatistics::Current->Print();
            printf("Total---------------------------------\n");
            ProgramStatistics::Total->Print();
            printf("--------------------------------------\n");

            cycleCount = 0;
            ProgramStatistics::Current->Clear();
            ProgramStatistics::Total->ResetFlags();
        }
        cycleCount++;
    }

    // generate security definitions
    this->m_fondMarket->FeedChannel()->InstrumentDefinition()->GenerateSecurityDefinitions();
    this->m_currMarket->FeedChannel()->InstrumentDefinition()->GenerateSecurityDefinitions();

    if(!this->m_fondMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        DefaultLogManager::Default->Print();
    }
    if(!this->m_currMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        DefaultLogManager::Default->Print();
    }

    w->Reset();

    // main cycle
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
		if(w->ElapsedSeconds() > 3) {
			double nanosecPerCycle = 3.0 * 1000.0 * 1000.0 * 1000.0 / cycleCount;
			printf("CycleCount for 3 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);


			if (this->m_fondMarket->FeedChannel()->OrdersSnapshot()->State() == FeedConnectionState::fcsListenSnapshot) {
				int foundSnapshotSymbolsCount = this->m_fondMarket->FeedChannel()->OrdersIncremental()->OrderFond()->SymbolsToRecvSnapshotCount();
				int foundQueEntries = this->m_fondMarket->FeedChannel()->OrdersIncremental()->OrderFond()->QueueEntriesCount();
				int msgSeqNumber = this->m_fondMarket->FeedChannel()->OrdersSnapshot()->MsgSeqNo();
				printf("fond olr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
			}
            else {
                printf("fond olr: start = %d end = %d\n",
                       this->m_fondMarket->FeedChannel()->OrdersIncremental()->MsgSeqNo(),
                       this->m_fondMarket->FeedChannel()->OrdersIncremental()->LastRecvMsgSeqNo());
            }
            if (this->m_fondMarket->FeedChannel()->TradesSnapshot()->State() == FeedConnectionState::fcsListenSnapshot) {
                int foundSnapshotSymbolsCount = this->m_fondMarket->FeedChannel()->TradesIncremental()->TradeFond()->SymbolsToRecvSnapshotCount();
                int foundQueEntries = this->m_fondMarket->FeedChannel()->TradesIncremental()->TradeFond()->QueueEntriesCount();
                int msgSeqNumber = this->m_fondMarket->FeedChannel()->TradesSnapshot()->MsgSeqNo();
                printf("fond tlr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
            }
            else {
                printf("fond tlr: start = %d end = %d\n",
                       this->m_fondMarket->FeedChannel()->TradesIncremental()->MsgSeqNo(),
                       this->m_fondMarket->FeedChannel()->TradesIncremental()->LastRecvMsgSeqNo());
            }
            if (this->m_fondMarket->FeedChannel()->StatisticsSnapshot()->State() == FeedConnectionState::fcsListenSnapshot) {
                int foundSnapshotSymbolsCount = this->m_fondMarket->FeedChannel()->StatisticsIncremental()->StatisticFond()->SymbolsToRecvSnapshotCount();
                int foundQueEntries = this->m_fondMarket->FeedChannel()->StatisticsIncremental()->StatisticFond()->QueueEntriesCount();
                int msgSeqNumber = this->m_fondMarket->FeedChannel()->StatisticsSnapshot()->MsgSeqNo();
                printf("fond msr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
            }
            else {
                printf("fond msr: start = %d end = %d\n",
                       this->m_fondMarket->FeedChannel()->StatisticsIncremental()->MsgSeqNo(),
                       this->m_fondMarket->FeedChannel()->StatisticsIncremental()->LastRecvMsgSeqNo());
            }
            printf("fond iss: start = %d end = %d\n",
                       this->m_fondMarket->FeedChannel()->InstrumentStatus()->MsgSeqNo(),
                       this->m_fondMarket->FeedChannel()->InstrumentStatus()->LastRecvMsgSeqNo());

            if(this->m_currMarket->FeedChannel()->OrdersSnapshot()->State() == FeedConnectionState::fcsListenSnapshot) {
				int currSnapshotSymbolsCount = this->m_currMarket->FeedChannel()->OrdersIncremental()->OrderCurr()->SymbolsToRecvSnapshotCount();
				int currQueEntries = this->m_currMarket->FeedChannel()->OrdersIncremental()->OrderCurr()->QueueEntriesCount();
				int msgSeqNumber = this->m_currMarket->FeedChannel()->OrdersSnapshot()->MsgSeqNo();
                printf("curr olr: %d que entries and  %d snapshot symbols to go. msg = %d\n", currQueEntries, currSnapshotSymbolsCount, msgSeqNumber);
			}
            else {
                printf("curr olr: start = %d end = %d\n",
                       this->m_currMarket->FeedChannel()->OrdersIncremental()->MsgSeqNo(),
                       this->m_currMarket->FeedChannel()->OrdersIncremental()->LastRecvMsgSeqNo());
            }

            if (this->m_currMarket->FeedChannel()->TradesSnapshot()->State() == FeedConnectionState::fcsListenSnapshot) {
                int foundSnapshotSymbolsCount = this->m_currMarket->FeedChannel()->TradesIncremental()->TradeCurr()->SymbolsToRecvSnapshotCount();
                int foundQueEntries = this->m_currMarket->FeedChannel()->TradesIncremental()->TradeCurr()->QueueEntriesCount();
                int msgSeqNumber = this->m_currMarket->FeedChannel()->TradesSnapshot()->MsgSeqNo();
                printf("curr tlr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
            }
            else {
                printf("curr tlr: start = %d end = %d\n",
                       this->m_currMarket->FeedChannel()->TradesIncremental()->MsgSeqNo(),
                       this->m_currMarket->FeedChannel()->TradesIncremental()->LastRecvMsgSeqNo());
            }
            if (this->m_currMarket->FeedChannel()->StatisticsSnapshot()->State() == FeedConnectionState::fcsListenSnapshot) {
                int foundSnapshotSymbolsCount = this->m_currMarket->FeedChannel()->StatisticsIncremental()->StatisticCurr()->SymbolsToRecvSnapshotCount();
                int foundQueEntries = this->m_currMarket->FeedChannel()->StatisticsIncremental()->StatisticCurr()->QueueEntriesCount();
                int msgSeqNumber = this->m_currMarket->FeedChannel()->StatisticsSnapshot()->MsgSeqNo();
                printf("curr msr: %d que entries and  %d snapshot symbols to go. msg = %d\n", foundQueEntries, foundSnapshotSymbolsCount, msgSeqNumber);
            }
            else {
                printf("curr msr: start = %d end = %d\n",
                       this->m_currMarket->FeedChannel()->StatisticsIncremental()->MsgSeqNo(),
                       this->m_currMarket->FeedChannel()->StatisticsIncremental()->LastRecvMsgSeqNo());
            }
            printf("curr iss: start = %d end = %d\n",
                   this->m_currMarket->FeedChannel()->InstrumentStatus()->MsgSeqNo(),
                   this->m_currMarket->FeedChannel()->InstrumentStatus()->LastRecvMsgSeqNo());

			w->Reset();

            printf("3 sec. Changes------------------------\n");
            ProgramStatistics::Current->Print();
            printf("Total Changes-------------------------\n");
            ProgramStatistics::Total->Print();
            printf("--------------------------------------\n");

            cycleCount = 0;
            ProgramStatistics::Current->Clear();
            ProgramStatistics::Total->ResetFlags();
		}
		cycleCount++;
    }

    DefaultLogManager::Default->Print();
    DefaultLogManager::Default->EndLog(true);
    return true;
}

