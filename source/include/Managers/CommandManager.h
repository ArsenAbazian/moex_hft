//
// Created by root on 19.04.17.
//

#ifndef HFT_ROBOT_COMMANDMANAGER_H
#define HFT_ROBOT_COMMANDMANAGER_H

#include "WinSockManager.h"
#include <string.h>
#include "../Lib/PointerList.h"
#include "../ProgramStatistics.h"
#include "../Stopwatch.h"

#define ALLOW_COMMAND_MANAGER

typedef enum _CommandManagerCommand {
    hcNone = 0,
    hcProgrammStatisticCurrent = 1,
    hcProgrammStatisticTotal = 2,
    hcRegMe = 3,
} CommandManagerCommand;

typedef enum _CommandManagerState {
    cmsIdle = 0,
    cmsStartExecuteCommand = 1,
    cmsSendData = 2,
    cmsRecvAnswer = 3,
} CommandManagerState;

typedef enum _CommandMode {
    cmNone = 0,
    cmExecuteOnce = 1,
    cmExecuteUnlimit = 2,
    cmRemove = 3,
    cmRemoveAll = 4
} CommandMode;

class CommandInfo {
public:
    struct sockaddr         *m_target;
    socklen_t               m_targetLength;
    int                     m_commandId;
    CommandManagerCommand   m_command;
    CommandMode             m_mode;
    bool                    m_shouldRemove;
    char                    m_paddingBytes[7];

    CommandInfo() :
            m_command(CommandManagerCommand::hcNone),
            m_mode(CommandMode::cmNone),
            m_target(0),
            m_targetLength(0),
            m_commandId(-1),
            m_shouldRemove(false) {
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
        this->m_shouldRemove = false;
    }
};

class CommandManager {
    static const int            m_bufferLength = 128;
    static const int            m_sendBufferMaxLength = 8192;
    static const int            m_spaceDataForPacketIndexLength = 2;
    WinSockManager              *m_manager;
    PointerList<CommandInfo>    *m_commands;
    LinkedPointer<CommandInfo>  *m_currentCommand;
    Stopwatch                   *m_timer;
    unsigned char               *m_buffer;
    unsigned short              *m_packetIndexPtr;
    unsigned char               *m_sendBuffer;
    int                         m_sendBufferLength;
    int                         m_packetIndex;
    int                         m_sendIndex;
    int                         m_sendSize;
    int                         m_port;

    CommandManagerState         m_state;
public:
    CommandManager(int port) :
            m_state(CommandManagerState::cmsIdle),
            m_port(0),
            m_manager(0),
            m_buffer(0),
            m_commands(0),
            m_currentCommand(0),
            m_sendBuffer(0),
            m_sendBufferLength(0),
            m_sendIndex(0),
            m_packetIndexPtr(0),
            m_packetIndex(0),
            m_timer(0),
            m_sendSize(0) {
        this->m_manager = new WinSockManager();
        this->m_port = port;
        this->m_buffer = new unsigned char[this->m_bufferLength];
        this->m_sendBuffer = new unsigned char[this->m_sendBufferMaxLength];
        this->m_packetIndexPtr = (unsigned short*) this->m_sendBuffer;
        this->m_commands = new PointerList<CommandInfo>(32, true, "CommandManager::Commands");
        this->m_timer = new Stopwatch();
    }
    ~CommandManager() {
        this->m_manager->Disconnect();
        delete this->m_manager;
        delete this->m_buffer;
        delete this->m_sendBuffer;
        delete this->m_commands;
        delete this->m_timer;
    }

    inline bool SetUp() {
        if(!this->m_manager->StartUdpServer(this->m_port)) {
            DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcCommandManager_SetUp_46_147_193_130, false);
            return false;
        }
        DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcCommandManager_SetUp_46_147_193_130, true);
        return true;
    }

    inline bool TearDown() {
        if(!this->m_manager->Disconnect()) {
            DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcCommandManager_TearDown, false);
            return false;
        }
        DefaultLogManager::Default->WriteSuccess(LogMessageCode::lmcCommandManager_TearDown, true);
        return true;
    }

    inline void OnRemoveCommand(CommandInfo *command) {
        command->m_shouldRemove = true;
    }

    inline void RemoveCommand(CommandManagerCommand command, int id, CommandMode mode) {
        LinkedPointer<CommandInfo> *node = this->m_commands->Start();
        while(node != 0) {
            CommandInfo *info = node->Data();
            if(info->m_commandId == id || (id == -1 && info->m_command == command) || mode == CommandMode::cmRemoveAll)
                OnRemoveCommand(info);
            node = node->Next();
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
        command->m_commandId = *((int*)this->m_buffer + 3);

        if(command->m_mode == CommandMode::cmRemove || command->m_mode == CommandMode::cmRemoveAll) {
            this->m_commands->Push(ptr);
            RemoveCommand(command->m_command, command->m_commandId, command->m_mode);
            return true;
        }
        else if(command->m_mode == CommandMode::cmExecuteOnce || command->m_mode == CommandMode::cmExecuteUnlimit) {
            this->m_commands->Add(ptr);
        }

        return true;
    }

    inline bool OnIdle() {
        if(this->m_currentCommand == 0)
            this->m_currentCommand = this->m_commands->Start();
        while(this->m_currentCommand != 0) {
            CommandInfo *info = this->m_currentCommand->Data();
            if(info->m_shouldRemove) {
                LinkedPointer<CommandInfo> *newCommand = this->m_currentCommand->Next();
                this->m_commands->Remove(this->m_currentCommand);
                this->m_currentCommand = newCommand;
                continue;
            }
            this->m_state = CommandManagerState::cmsStartExecuteCommand;
            return true;
        }
        return true;
    }

    inline bool ExecuteProgrammStatisticCommand(CommandInfo *info) {
        ProgramStatistics *stat = info->m_command == CommandManagerCommand::hcProgrammStatisticTotal?
                                  ProgramStatistics::Total: ProgramStatistics::Current;
        this->m_packetIndex = 0;
        this->m_sendBufferLength = stat->WriteToBuffer(this->m_sendBuffer + this->m_spaceDataForPacketIndexLength) + this->m_spaceDataForPacketIndexLength;
        this->m_sendIndex = 0;
        this->m_state = CommandManagerState::cmsSendData;

        return true;
    }

    inline bool OnStartExecuteCommand() {
        CommandInfo *info = this->m_currentCommand->Data();
        if(info->m_command == CommandManagerCommand::hcProgrammStatisticCurrent ||
                info->m_command == CommandManagerCommand::hcProgrammStatisticTotal) {
            ExecuteProgrammStatisticCommand(info);
        }
        return true;
    }

    inline bool OnSendData() {
        CommandInfo *info = this->m_currentCommand->Data();
        int remain = this->m_sendBufferLength - this->m_sendIndex;
        this->m_sendSize = remain < 1000? remain: 1000;
        *(this->m_packetIndexPtr) = this->m_packetIndex;
        if(!this->m_manager->SendTo(info->m_target, info->m_targetLength, this->m_sendBuffer + this->m_sendIndex, this->m_sendSize))
            return false;
        this->m_state = CommandManagerState::cmsRecvAnswer;
        this->m_timer->StartFast();
        return true;
    }

    inline bool OnRecvAnswer() {
        if(!this->m_manager->ShouldRecv()) {
            if(this->m_timer->ElapsedSeconds() >= 2)
                this->m_state = CommandManagerState::cmsSendData;
            return true;
        }
        if(!this->m_manager->RecvUDP(this->m_buffer) || this->m_manager->RecvSize() != 2)
            return true;
        unsigned short index = *((unsigned short*)this->m_buffer);
        if(this->m_packetIndex != index) {
            this->m_state = CommandManagerState::cmsSendData;
            return true;
        }

        this->m_packetIndex++;
        this->m_sendIndex += this->m_sendSize;
        if(this->m_sendIndex < this->m_sendBufferLength) {
            this->m_state = CommandManagerState::cmsSendData;
            return true;
        }

        LinkedPointer<CommandInfo> *newCommand = this->m_currentCommand->Next();
        CommandInfo *info = this->m_currentCommand->Data();
        if(info->m_mode == CommandMode::cmExecuteOnce)
            this->m_commands->Remove(this->m_currentCommand);
        this->m_currentCommand = newCommand;
        this->m_state = CommandManagerState::cmsIdle;

        return true;
    }

    inline bool DoWorkAtom() {
        if(!this->ProcessCommands())
            return false;

        if(this->m_state == CommandManagerState::cmsIdle)
            return OnIdle();
        else if(this->m_state == CommandManagerState::cmsStartExecuteCommand)
            return OnStartExecuteCommand();
        else if(this->m_state == CommandManagerState::cmsSendData)
            return OnSendData();
        else if(this->m_state == CommandManagerState::cmsRecvAnswer)
            return OnRecvAnswer();

        return true;
    }
};

#endif //HFT_ROBOT_COMMANDMANAGER_H
