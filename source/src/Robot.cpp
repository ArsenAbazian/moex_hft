#include "Robot.h"
#include "FeedChannel.h"
#include <cstdio>
#include "ProgramStatistics.h"

Robot::Robot() {
	this->channelsCount = 0;
	memset(this->channels, 0, sizeof(FeedChannel*) * MARKET_INFO_CAPACITY);
    this->m_allowCurrMarket = true;
    this->m_allowFondMarket = true;
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
	if(this->AllowCurrMarket()) {
		FeedChannel *curr = new FeedChannel("CURR", "Currency Exchange Market");

		if(this->AllowFeed("MSR")) {
			FeedConnection *msr_curr = new FeedConnection_CURR_MSR("MSR", "Statisctics Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.7", 9027, "10.50.129.200", "239.192.112.135", 9227);
			curr->SetConnection(msr_curr);
		}
		if(this->AllowFeed("MSS")) {
			FeedConnection *mss_curr = new FeedConnection_CURR_MSS("MSS", "Statisctics Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.8", 9028, "10.50.129.200", "239.192.112.136", 9228);
			curr->SetConnection(mss_curr);
		}
		if(this->AllowFeed("OLR")) {
			FeedConnection *olr_curr = new FeedConnection_CURR_OLR("OLR", "Orders Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.1", 9021, "10.50.129.200", "239.192.112.129", 9221);
			curr->SetConnection(olr_curr);
		}
		if(this->AllowFeed("OLS")) {
			FeedConnection *ols_curr = new FeedConnection_CURR_OLS("OLS", "Orders Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.2", 9022, "10.50.129.200", "239.192.112.130", 9222);
			curr->SetConnection(ols_curr);
		}
		if(this->AllowFeed("TLR")) {
			FeedConnection *tlr_curr = new FeedConnection_CURR_TLR("TLR", "Trades Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.5", 9025, "10.50.129.200", "239.192.112.133", 9225);
			curr->SetConnection(tlr_curr);
		}
		if(this->AllowFeed("TLS")) {
			FeedConnection *tls_curr = new FeedConnection_CURR_TLS("TLS", "Trades Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.6", 9026, "10.50.129.200", "239.192.112.134", 9226);
			curr->SetConnection(tls_curr);
		}
		if(this->AllowFeed("IDF")) {
			FeedConnection *idf_curr = new FeedConnection_CURR_IDF("IDF", "Instrument Replay", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.9", 9029, "10.50.129.200", "239.192.112.137", 9229);
			curr->SetConnection(idf_curr);
		}
		if(this->AllowFeed("ISF")) {
			FeedConnection *isf_curr = new FeedConnection_CURR_ISF("ISF", "Instrument Status", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.112.10", 9030, "10.50.129.200", "239.192.112.138", 9230);
			curr->SetConnection(isf_curr);
		}
		if(this->AllowFeed("H")) {
			FeedConnection *h_curr = new FeedConnection_CURR_H("H", "Historical Replay", 'H', FeedConnectionProtocol::TCP_IP, "1.1.7.200", 20000);
			curr->SetConnection(h_curr);
		}

		this->AddChannel(curr);
	}
	if(this->AllowFondMarket()) {
		FeedChannel *fond = new FeedChannel("FOND", "Stock Exchange Market");

		if(this->AllowFeed("MSR")) {
			FeedConnection *msr_fond = new FeedConnection_FOND_MSR("MSR", "Statisctics Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.7", 9117, "10.50.129.200", "239.192.113.135", 9317);
			fond->SetConnection(msr_fond);
		}
		if(this->AllowFeed("MSS")) {
			FeedConnection *mss_fond = new FeedConnection_FOND_MSS("MSS", "Statisctics Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.8", 9118, "10.50.129.200", "239.192.113.136", 9318);
			fond->SetConnection(mss_fond);
		}
		if(this->AllowFeed("OLR")) {
			FeedConnection *olr_fond = new FeedConnection_FOND_OLR("OLR", "Orders Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.1", 9111, "10.50.129.200", "239.192.113.129", 9311);
			fond->SetConnection(olr_fond);
		}
		if(this->AllowFeed("OLS")) {
			FeedConnection *ols_fond = new FeedConnection_FOND_OLS("OLS", "Orders Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.2", 9112, "10.50.129.200", "239.192.113.130", 9312);
			fond->SetConnection(ols_fond);
		}
		if(this->AllowFeed("TLR")) {
			FeedConnection *tlr_fond = new FeedConnection_FOND_TLR("TLR", "Trades Incremental", 'I', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.5", 9115, "10.50.129.200", "239.192.113.133", 9315);
			fond->SetConnection(tlr_fond);
		}
		if(this->AllowFeed("TLS")) {
			FeedConnection *tls_fond = new FeedConnection_FOND_TLS("TLS", "Trades Snapshot", 'S', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.6", 9116, "10.50.129.200", "239.192.113.134", 9316);
			fond->SetConnection(tls_fond);
		}
		if(this->AllowFeed("IDF")) {
			FeedConnection *idf_fond = new FeedConnection_FOND_IDF("IDF", "Instrument Replay", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.9", 9119, "10.50.129.200", "239.192.113.137", 9319);
			fond->SetConnection(idf_fond);
		}
		if(this->AllowFeed("ISF")) {
			FeedConnection *isf_fond = new FeedConnection_FOND_ISF("ISF", "Instrument Status", 'N', FeedConnectionProtocol::UDP_IP, "10.50.129.200", "239.192.113.10", 9120, "10.50.129.200", "239.192.113.138", 9320);
			fond->SetConnection(isf_fond);
		}
		if(this->AllowFeed("H")) {
			FeedConnection *h_fond = new FeedConnection_FOND_H("H", "Historical Replay", 'H', FeedConnectionProtocol::TCP_IP, "1.1.7.200", 10000);
			fond->SetConnection(h_fond);
		}

		this->AddChannel(fond);
	}
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

bool Robot::CollectSecurityDefinitions_FondOnly() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitions);

    if(!this->m_fondMarket->FeedChannel()->Idf()->LoadSecurityDefinitions()) {
        if(!this->m_fondMarket->FeedChannel()->Idf()->Start()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        // collect data first
        while (true) {
            if (!WinSockManager::UpdateManagersPollStatus())
                break;

            if (!this->m_fondMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if (this->m_fondMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_fondMarket->FeedChannel()->Idf()->Stop();
                break;
            }

            if (w->ElapsedMilliseconds() > 1000) {
                w->Reset();

                double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
                printf("CycleCount for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);

                printf("fond idf socket buffer usage = %g item usage = %g\n",
                       this->m_fondMarket->FeedChannel()->Idf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                       this->m_fondMarket->FeedChannel()->Idf()->RecvBuffer()->CalcItemsUsagePercentage());

                printf("Changes------------------------\n");
                ProgramStatistics::Current->Print();
                printf("Total---------------------------------\n");
                ProgramStatistics::Total->Print();
                printf("--------------------------------------\n");

                cycleCount = 0;
                ProgramStatistics::Current->Clear();
                //ProgramStatistics::Total->ResetFlags();
            }
            cycleCount++;
        }
    }
    DefaultLogManager::Default->EndLog(true);
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitions);
    this->m_fondMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    if(!this->m_fondMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::CollectSecurityDefinitions_CurrOnly() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitions);
    if(!this->m_currMarket->FeedChannel()->Idf()->LoadSecurityDefinitions()) {
        if(!this->m_currMarket->FeedChannel()->Idf()->Start()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        // collect data first
        while (true) {
            if (!WinSockManager::UpdateManagersPollStatus())
                break;
            if (!this->m_currMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if (this->m_currMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_currMarket->FeedChannel()->Idf()->Stop();
                break;
            }

            if (w->ElapsedMilliseconds() > 1000) {
                w->Reset();

                double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
                printf("cycle count for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);
                printf("curr idf socket buffer usage = %g item usage = %g\n",
                       this->m_currMarket->FeedChannel()->Idf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                       this->m_currMarket->FeedChannel()->Idf()->RecvBuffer()->CalcItemsUsagePercentage());

                printf("Changes------------------------\n");
                ProgramStatistics::Current->Print();
                printf("Total---------------------------------\n");
                ProgramStatistics::Total->Print();
                printf("--------------------------------------\n");

                cycleCount = 0;
                ProgramStatistics::Current->Clear();
                //ProgramStatistics::Total->ResetFlags();
            }
            cycleCount++;
        }
    }
    DefaultLogManager::Default->EndLog(true);

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitions);
    this->m_currMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    if(!this->m_currMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::CollectSecurityDefinitions() {
    Stopwatch *w = new Stopwatch();
    w->Start();
    unsigned int cycleCount = 0;

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_CollectSecurityDefinitions);

    bool collectedFond = false;
    bool collectedCurr = false;

    if(this->m_fondMarket->FeedChannel()->Idf()->LoadSecurityDefinitions())
        collectedFond = true;
    else if(!this->m_fondMarket->FeedChannel()->Idf()->Start()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(this->m_currMarket->FeedChannel()->Idf()->LoadSecurityDefinitions())
        collectedCurr = true;
    else if(!this->m_currMarket->FeedChannel()->Idf()->Start()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    // collect data first
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!collectedCurr) {
            if (!this->m_currMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(this->m_currMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_currMarket->FeedChannel()->Idf()->Stop();
                collectedCurr = true;
            }
        }
        if(!collectedFond) {
            if (!this->m_fondMarket->FeedChannel()->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(this->m_fondMarket->FeedChannel()->Idf()->IsIdfDataCollected()) {
                this->m_fondMarket->FeedChannel()->Idf()->Stop();
                collectedFond = true;
            }
        }

        if(collectedFond && collectedCurr)
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            w->Reset();

            double nanosecPerCycle = w->ElapsedMilliseconds() * 1000.0 * 1000.0 / cycleCount;
            printf("cycleCount for 1 sec = %d. %g nanosec per cycle\n", cycleCount, nanosecPerCycle);

            printf("fond idf socket buffer usage = %g item usage = %g\n",
                       this->m_fondMarket->FeedChannel()->Idf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                       this->m_fondMarket->FeedChannel()->Idf()->RecvBuffer()->CalcItemsUsagePercentage());

            printf("curr idf socket buffer usage = %g item usage = %g\n",
                       this->m_currMarket->FeedChannel()->Idf()->RecvBuffer()->CalcMemoryUsagePercentage(),
                       this->m_currMarket->FeedChannel()->Idf()->RecvBuffer()->CalcItemsUsagePercentage());

            printf("Changes------------------------\n");
            ProgramStatistics::Current->Print();
            printf("Total---------------------------------\n");
            ProgramStatistics::Total->Print();
            printf("--------------------------------------\n");

            cycleCount = 0;
            ProgramStatistics::Current->Clear();
            //ProgramStatistics::Total->ResetFlags();
        }
        cycleCount++;
    }
    DefaultLogManager::Default->EndLog(true);

    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_GenerateSecurityDefinitions);

    this->m_fondMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    this->m_currMarket->FeedChannel()->Idf()->GenerateSecurityDefinitions();
    if(!this->m_fondMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    if(!this->m_currMarket->FeedChannel()->OnAfterGenerateSecurityDefinitions()) {
        DefaultLogManager::Default->EndLog(false);
        return false;
    }
    DefaultLogManager::Default->EndLog(false);
    return true;
}

bool Robot::MainLoop_FondOnly() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if (!this->m_fondMarket->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if(!this->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            this->PrintStatistics(cycleCount, 1);

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::MainLoop_CurrOnly() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!this->m_currMarket->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        DebugInfoManager::Default->DebugCheckForDublicateItems(this->m_currMarket->FeedChannel());
        if(!this->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            this->PrintStatistics(cycleCount, 1);

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::MainLoop() {
    Stopwatch *w = new Stopwatch();
    unsigned int cycleCount = 0;

    w->Start();
    while(true) {
        if(!WinSockManager::UpdateManagersPollStatus())
            break;
        if(!this->m_currMarket->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if(!this->m_fondMarket->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if(!this->DoWorkAtom()) {
            DefaultLogManager::Default->EndLog(false);
            return false;
        }
        if(!this->Working())
            break;

        if(w->ElapsedMilliseconds() > 1000) {
            this->PrintStatistics(cycleCount, 1);

            w->Reset();
            cycleCount = 0;
        }
        cycleCount++;
    }

    DefaultLogManager::Default->EndLog(true);
    return true;
}

bool Robot::DoWork() {
    DefaultLogManager::Default->StartLog(LogMessageCode::lmcRobot_DoWork);

    if(!this->AllowCurrMarket() && !this->AllowFondMarket()) {
        printf("Error: no market enabled!\n");
        DefaultLogManager::Default->EndLog(false);
        return false;
    }

    if(this->AllowCurrMarket())
        this->m_currMarket->FeedChannel()->Idf()->AllowSaveSecurityDefinitions(true);
    if(this->AllowFondMarket())
        this->m_fondMarket->FeedChannel()->Idf()->AllowSaveSecurityDefinitions(true);

    while(true) {
        if(!this->AllowFondMarket()) {
            if(!this->CollectSecurityDefinitions_CurrOnly()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(!this->MainLoop_CurrOnly()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
        }
        else if(!this->AllowCurrMarket()) {
            if(!this->CollectSecurityDefinitions_FondOnly()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(!this->MainLoop_FondOnly()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
        }
        else {
            if(!this->CollectSecurityDefinitions()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
            if(!this->MainLoop()) {
                DefaultLogManager::Default->EndLog(false);
                return false;
            }
        }
    }
}

