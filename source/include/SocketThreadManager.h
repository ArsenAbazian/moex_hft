//
// Created by root on 25.07.16.
//

#ifndef HFT_ROBOT_SOCKETTHREADMANAGER_H
#define HFT_ROBOT_SOCKETTHREADMANAGER_H

#include <list>
#include <thread>
#include <memory.h>
#include "WinSockManager.h"

class SocketThreadManager {
    std::thread*        m_threads[100];
    int                 m_threadsCount;
public:

    SocketThreadManager() {
        bzero(this->m_threads, sizeof(std::thread*) * 100);
        this->m_threadsCount = 0;
    }

    void OnWorkSendSingle(WinSockManager *manager) {
        while(true) {
            manager->WorkSend();
        }
    }

    void OnWorkRecvSingle(WinSockManager *manager) {
        while(true) {
            manager->WorkRecv();
        }
    }

    void OnWorkSend(WinSockManager **manager, int managersCount) {
        while(true) {
            for(int i = 0; i < managersCount; i++) {
                manager[i]->WorkSend();
            }
        }
    }

    void OnWorkRecv(WinSockManager **manager, int managersCount) {
        while(true) {
            for(int i = 0; i < managersCount; i++) {
                manager[i]->WorkRecv();
            }
        }
    }

    void AddSendThread(WinSockManager **manager, int managersCount) {
        if(managersCount == 0)
            this->m_threads[this->m_threadsCount] = new std::thread(&SocketThreadManager::OnWorkSendSingle, this, *manager);
        else
            this->m_threads[this->m_threadsCount] = new std::thread(&SocketThreadManager::OnWorkSend, this, manager, managersCount);
        this->m_threadsCount++;
    }

    void AddRecvThread(WinSockManager **manager, int managersCount) {
        if(managersCount == 0)
            this->m_threads[this->m_threadsCount] = new std::thread(&SocketThreadManager::OnWorkRecvSingle, this, *manager);
        else
            this->m_threads[this->m_threadsCount] = new std::thread(&SocketThreadManager::OnWorkRecv, this, manager, managersCount);
        this->m_threadsCount++;
    }
};

class DefaultSocketThreadManager {
public:
    static SocketThreadManager *Default;
};

#endif //HFT_ROBOT_SOCKETTHREADMANAGER_H
