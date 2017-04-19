//
// Created by root on 19.04.17.
//

#ifndef HFT_ROBOT_COMMANDMANAGER_H
#define HFT_ROBOT_COMMANDMANAGER_H

#include "WinSockManager.h"
#include <string.h>
#include "../Lib/PointerList.h"
#include "../../../../../../../../usr/include/x86_64-linux-gnu/bits/socket.h"

typedef enum _CommandManagerCommand {
    hcNone = 0,
    hcCommonStatistic = 1,
} CommandManagerCommand;

typedef enum _CommandManagerState {
    cmsIdle = 0,
} CommandManagerState;

typedef enum _CommandMode {
    cmNone = 0,
    cmExecuteOnce = 1,
    cmExecuteUnlimit = 2,
    cmRemove = 3
} CommandMode;

class CommandInfo {
public:
    CommandManagerCommand   m_command;
    CommandMode             m_mode;
    struct sockaddr         *m_target;
    socklen_t               m_targetLength;
    int                     m_commandId;

    CommandInfo() :
            m_command(CommandManagerCommand::hcNone),
            m_mode(CommandMode::cmNone),
            m_target(0),
            m_targetLength(0),
            m_commandId(-1) {
        this->m_target = new struct sockaddr;
        memset(this->m_target, 0, sizeof(struct sockaddr));
    }
    ~CommandInfo() {
        delete this->m_target;
    }
    inline void Clear() {
        this->m_commandId = -1;
        this->m_command = CommandManagerCommand::hcNone;
        this->m_mode = CommandMode::cmNone;
    }
};

class CommandManager {
    const int                   m_bufferLength = 128;
    WinSockManager              *m_manager;
    int                         m_port;
    CommandManagerState         m_state;
    unsigned char               *m_buffer;
    PointerList<CommandInfo>    *m_commands;
public:
    CommandManager(int port) :
            m_state(CommandManagerState::cmsIdle),
            m_port(0),
            m_manager(0),
            m_buffer(0),
            m_commands(0) {
        this->m_manager = new WinSockManager();
        this->m_port = port;
        this->m_buffer = new unsigned char[this->m_bufferLength];
        this->m_commands = new PointerList<CommandInfo>(32, true, "CommandManager::Commands");
    }
    ~CommandManager() {
        this->m_manager->Disconnect();
        delete this->m_manager;
        delete this->m_buffer;
        delete this->m_commands;
    }

    inline bool SetUp() {
        if(!this->m_manager->ConnectUdp(this->m_port))
            return false;
    }

    inline bool TearDown() {
        return this->m_manager->Disconnect();
    }

    inline bool OnIdle() {
        return true;
    }

    inline void RemoveCommand(CommandManagerCommand command, int id) {
        LinkedPointer<CommandInfo> *node = this->m_commands->Start();
        while(node != 0) {

        }
    }

    inline bool ProcessCommands() {
        if(!this->m_manager->ShouldRecv())
            return true;
        LinkedPointer<CommandInfo> *ptr = this->m_commands->Pop();
        CommandInfo *command = ptr->Data();
        if(!this->m_manager->RecvFrom(this->m_buffer, command->m_target, &(command->m_targetLength))) {
            this->m_commands->Push(ptr);
            return true;
        }

        command->m_command = (CommandManagerCommand) *((unsigned short*)this->m_buffer);
        command->m_mode = (CommandMode) *(this->m_buffer + 2);
        if(command->m_mode == CommandMode::cmRemove) {
            this->m_commands->Push(ptr);
            int id = *((int*)this->m_buffer + 3);
            RemoveCommand(command->m_command, id);
            command->Clear();
            return true;
        }
        this->m_commands->Add(ptr);

        return true;
    }

    inline bool DoWorkAtom() {
        if(!this->ProcessCommands())
            return false;

        if(this->m_state == CommandManagerState::cmsIdle)
            return OnIdle();

        return true;
    }
};

#endif //HFT_ROBOT_COMMANDMANAGER_H
