//
// Created by root on 11.03.17.
//

#ifndef HFT_ROBOT_FORTSMARKET_H
#define HFT_ROBOT_FORTSMARKET_H

#include "FortsMarketDataGroup.h"

class FortsFeedChannel {
    FortsMarketDataGroup    *m_futBook1;
    FortsMarketDataGroup    *m_futBook5;
    FortsMarketDataGroup    *m_futBook20;
    FortsMarketDataGroup    *m_futBook50;
    FortsMarketDataGroup    *m_futTrades;
    FortsMarketDataGroup    *m_futInfo;

    FortsMarketDataGroup    *m_indexes;
    FortsMarketDataGroup    *m_news;
    FortsMarketDataGroup    *m_newSkrin;

    FortsMarketDataGroup    *m_optBook1;
    FortsMarketDataGroup    *m_optBook5;
    FortsMarketDataGroup    *m_optBook20;
    FortsMarketDataGroup    *m_optBook50;
    FortsMarketDataGroup    *m_optTrades;
    FortsMarketDataGroup    *m_optInfo;

    FortsMarketDataGroup    *m_otcTrades;
    FortsMarketDataGroup    *m_otcIssues;

public:

    FortsFeedChannel();
    ~FortsFeedChannel();

    FortsMarketDataGroup* FutBook1() { return this->m_futBook1; }
    FortsMarketDataGroup* FutBook5() { return this->m_futBook5; }
    FortsMarketDataGroup* FutBook20() { return this->m_futBook20; }
    FortsMarketDataGroup* FutBook50() { return this->m_futBook50; }
    FortsMarketDataGroup* FutInfo() { return this->m_futInfo; }
    FortsMarketDataGroup* FutTrades() { return this->m_futTrades; }

    FortsMarketDataGroup* OptBook1() { return this->m_optBook1; }
    FortsMarketDataGroup* OptBook5() { return this->m_optBook5; }
    FortsMarketDataGroup* OptBook20() { return this->m_optBook20; }
    FortsMarketDataGroup* OptBook50() { return this->m_optBook50; }
    FortsMarketDataGroup* OptInfo() { return this->m_optInfo; }
    FortsMarketDataGroup* OptTrades() { return this->m_optTrades; }

    FortsMarketDataGroup* Index() { return this->m_indexes; }
    FortsMarketDataGroup* News() { return this->m_news; }
    FortsMarketDataGroup* NewsSkrin() { return this->m_newSkrin; }

    FortsMarketDataGroup* OtcIssues() { return this->m_otcIssues; }
    FortsMarketDataGroup* OtcTrades() { return this->m_otcTrades; }

    void FutBook1(FortsMarketDataGroup *group) { this->m_futBook1 = group; }
    void FutBook5(FortsMarketDataGroup *group) { this->m_futBook5 = group; }
    void FutBook20(FortsMarketDataGroup *group) { this->m_futBook20 = group; }
    void FutBook50(FortsMarketDataGroup *group) { this->m_futBook50 = group; }
    void FutInfo(FortsMarketDataGroup *group) {
        this->m_futInfo = group;
        this->m_futInfo->InstrReplay()->ChannelName("FUT");
    }
    void FutTrades(FortsMarketDataGroup *group) { this->m_futTrades = group; }

    void OptBook1(FortsMarketDataGroup *group) { this->m_optBook1 = group; }
    void OptBook5(FortsMarketDataGroup *group) { this->m_optBook5 = group; }
    void OptBook20(FortsMarketDataGroup *group) { this->m_optBook20 = group; }
    void OptBook50(FortsMarketDataGroup *group) { this->m_optBook50 = group; }
    void OptInfo(FortsMarketDataGroup *group) {
        this->m_optInfo = group;
        this->m_optInfo->InstrReplay()->ChannelName("OPT");
    }
    void OptTrades(FortsMarketDataGroup *group) { this->m_optTrades = group; }

    void Index(FortsMarketDataGroup *group) { this->m_indexes = group; }
    void News(FortsMarketDataGroup *group) { this->m_news = group; }
    void NewsSkrin(FortsMarketDataGroup *group) { this->m_newSkrin = group; }

    void OtcIssues(FortsMarketDataGroup *group) { this->m_otcIssues = group; }
    void OtcTrades(FortsMarketDataGroup *group) { this->m_otcTrades = group; }

    void AllowSaveSecurityDefinitions(FortsMarketDataGroup *group, bool value) {
        if(group != 0) group->AllowSaveSecurityDefinitions(value);
    }
    void AllowSaveSecurityDefinitions(bool value) {
        this->AllowSaveSecurityDefinitions(this->m_futInfo, value);
        this->AllowSaveSecurityDefinitions(this->m_optInfo, value);
    }
    inline bool AllowFutures() { return this->m_futInfo != 0; }
    inline bool AllowOptions() { return this->m_optInfo != 0; }
    inline bool LoadSecurityDefinitionFutures() {
        return this->m_futInfo->InstrReplay()->LoadSecurityDefinitions();
    }
    inline bool LoadSecurityDefinitionOptions() {
        return this->m_optInfo->InstrReplay()->LoadSecurityDefinitions();
    }
    inline bool OnAfterGenerateSecurityDefinitions(FortsMarketDataGroup *group) {
        for(int i = 0; i < group->InstrReplay()->ConnectionsToRecvSymbolsCount(); i++) {
            if(!group->InstrReplay()->ConnectionsToRecvSymbols()[i]->Start())
                return false;
        }
        return true;
    }
    inline bool OnAfterGenerateSecurityDefinitionsFut() {
        return this->OnAfterGenerateSecurityDefinitions(this->FutInfo());
    }
    inline bool OnAfterGenerateSecurityDefinitionsOpt() {
        return this->OnAfterGenerateSecurityDefinitions(this->OptInfo());
    }

    inline bool DoWorkFutures() {
        return true;
    }

    inline bool DoWorkOptions() {
        return true;
    }
};

#endif //HFT_ROBOT_FORTSMARKET_H
