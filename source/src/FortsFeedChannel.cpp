//
// Created by root on 11.03.17.
//

#include "../include/Feeds/Forts/FortsFeedChannel.h"

FortsFeedChannel::FortsFeedChannel() {
    this->m_futBook1 = 0;
    this->m_futBook5 = 0;
    this->m_futBook20 = 0;
    this->m_futBook50 = 0;
    this->m_futInfo = 0;
    this->m_futTrades = 0;

    this->m_optBook1 = 0;
    this->m_optBook5 = 0;
    this->m_optBook20 = 0;
    this->m_optBook50 = 0;
    this->m_optInfo = 0;
    this->m_optTrades = 0;

    this->m_otcIssues = 0;
    this->m_otcTrades = 0;

    this->m_news = 0;
    this->m_indexes = 0;
    this->m_newSkrin = 0;
}

FortsFeedChannel::~FortsFeedChannel() {
    if(this->m_futBook1 != 0)
        delete this->m_futBook1;
    if(this->m_futBook5 != 0)
        delete this->m_futBook5;
    if(this->m_futBook20 != 0)
        delete this->m_futBook20;
    if(this->m_futBook50 != 0)
        delete this->m_futBook50;
    if(this->m_futInfo != 0)
        delete this->m_futInfo;
    if(this->m_futTrades != 0)
        delete this->m_futTrades;

    if(this->m_optBook1 != 0)
        delete this->m_optBook1;
    if(this->m_optBook5 != 0)
        delete this->m_optBook5;
    if(this->m_optBook20 != 0)
        delete this->m_optBook20;
    if(this->m_optBook50 != 0)
        delete this->m_optBook50;
    if(this->m_optInfo != 0)
        delete this->m_optInfo;
    if(this->m_optTrades != 0)
        delete this->m_optTrades;

    if(this->m_indexes != 0)
        delete this->m_indexes;
    if(this->m_news != 0)
        delete this->m_news;
    if(this->m_newSkrin != 0)
        delete this->m_newSkrin;

    if(this->m_otcIssues != 0)
        delete this->m_otcIssues;
    if(this->m_otcTrades != 0)
        delete this->m_otcTrades;
}