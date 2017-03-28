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

    inline bool DoWorkInstr(FortsMarketDataGroup *g) {
        if(g == 0)
            return true;
        return g->InstrReplay()->DoWorkAtom() &&
                g->InstrInc()->DoWorkAtom();
    }

    inline bool DoWorkInc(FortsMarketDataGroup *g) {
        if(g == 0)
            return true;
        bool res = g->Inc()->DoWorkAtom();
        res &= g->Snap()->DoWorkAtom();
        return res;
    }

    inline bool DoWorkFutures() {
        bool res = true;

        res &= this->DoWorkInstr(this->FutInfo());
        res &= this->DoWorkInc(this->FutBook1());
        res &= this->DoWorkInc(this->FutBook5());
        res &= this->DoWorkInc(this->FutBook20());
        res &= this->DoWorkInc(this->FutBook50());
        res &= this->DoWorkInc(this->FutTrades());

        return res;
    }

    inline bool DoWorkOptions() {
        bool res = true;

        res &= this->DoWorkInstr(this->OptInfo());
        res &= this->DoWorkInc(this->OptBook1());
        res &= this->DoWorkInc(this->OptBook5());
        res &= this->DoWorkInc(this->OptBook20());
        res &= this->DoWorkInc(this->OptBook50());
        res &= this->DoWorkInc(this->OptTrades());

        return res;
    }

    void Prepare() {
        if(this->m_futInfo != 0 && this->m_futInfo->InstrInc() != 0)
            this->m_futInfo->InstrInc()->SetSecurityDefinition(this->m_futInfo->InstrReplay());
        if(this->m_optInfo != 0 && this->m_optInfo->InstrInc() != 0)
            this->m_optInfo->InstrInc()->SetSecurityDefinition(this->m_optInfo->InstrReplay());

        if(this->m_futInfo != 0) {
            if (this->m_futInfo->InstrReplay() != 0) {
                this->m_futInfo->InstrReplay()->AddConnectionToRecvSymbol(this->m_futInfo->InstrInc());
                if (this->FutBook1() != 0)
                    this->m_futInfo->InstrReplay()->AddConnectionToRecvSymbol(this->FutBook1()->Inc());
                if (this->FutBook5() != 0)
                    this->m_futInfo->InstrReplay()->AddConnectionToRecvSymbol(this->FutBook5()->Inc());
                if (this->FutBook20() != 0)
                    this->m_futInfo->InstrReplay()->AddConnectionToRecvSymbol(this->FutBook20()->Inc());
                if (this->FutBook50() != 0)
                    this->m_futInfo->InstrReplay()->AddConnectionToRecvSymbol(this->FutBook50()->Inc());
                if (this->FutTrades() != 0)
                    this->m_futInfo->InstrReplay()->AddConnectionToRecvSymbol(this->FutTrades()->Inc());
            }
        }

        if(this->m_optInfo != 0) {
            if (this->m_optInfo->InstrReplay() != 0) {
                this->m_optInfo->InstrReplay()->AddConnectionToRecvSymbol(this->m_optInfo->InstrInc());
                if (this->OptBook1() != 0)
                    this->m_optInfo->InstrReplay()->AddConnectionToRecvSymbol(this->OptBook1()->Inc());
                if (this->OptBook5() != 0)
                    this->m_optInfo->InstrReplay()->AddConnectionToRecvSymbol(this->OptBook5()->Inc());
                if (this->OptBook20() != 0)
                    this->m_optInfo->InstrReplay()->AddConnectionToRecvSymbol(this->OptBook20()->Inc());
                if (this->OptBook50() != 0)
                    this->m_optInfo->InstrReplay()->AddConnectionToRecvSymbol(this->OptBook50()->Inc());
                if (this->OptTrades() != 0)
                    this->m_optInfo->InstrReplay()->AddConnectionToRecvSymbol(this->OptTrades()->Inc());
            }
        }

        if(this->FutBook1() != 0) {
            this->FutBook1()->Prepare();
            this->FutBook1()->SetSecurityDefinition(this->FutInfo()->InstrReplay());
        }
        if(this->FutBook5() != 0) {
            this->FutBook5()->Prepare();
            this->FutBook5()->SetSecurityDefinition(this->FutInfo()->InstrReplay());
        }
        if(this->FutBook20() != 0) {
            this->FutBook20()->Prepare();
            this->FutBook20()->SetSecurityDefinition(this->FutInfo()->InstrReplay());
        }
        if(this->FutBook50() != 0) {
            this->FutBook50()->Prepare();
            this->FutBook50()->SetSecurityDefinition(this->FutInfo()->InstrReplay());
        }
        if(this->FutTrades() != 0) {
            this->FutTrades()->Prepare();
            this->FutTrades()->SetSecurityDefinition(this->FutInfo()->InstrReplay());
        }
        
        if(this->OptBook1() != 0) {
            this->OptBook1()->Prepare();
            this->OptBook1()->SetSecurityDefinition(this->OptInfo()->InstrReplay());
        }
        if(this->OptBook5() != 0) {
            this->OptBook5()->Prepare();
            this->OptBook5()->SetSecurityDefinition(this->OptInfo()->InstrReplay());
        }
        if(this->OptBook20() != 0) {
            this->OptBook20()->Prepare();
            this->OptBook20()->SetSecurityDefinition(this->OptInfo()->InstrReplay());
        }
        if(this->OptBook50() != 0) {
            this->OptBook50()->Prepare();
            this->OptBook50()->SetSecurityDefinition(this->OptInfo()->InstrReplay());
        }
        if(this->OptTrades() != 0) {
            this->OptTrades()->Prepare();
            this->OptTrades()->SetSecurityDefinition(this->OptInfo()->InstrReplay());
        }
    }
};

#endif //HFT_ROBOT_FORTSMARKET_H
