//
// Created by root on 25.02.17.
//

#include "MDEntryQueue.h"
#include "../Managers/DebugInfoManager.h"

AutoAllocatePointerList<MDEntryQueue>* MDEntryQueue::CreatePool() {
    AutoAllocatePointerList<MDEntryQueue>* res = new AutoAllocatePointerList<MDEntryQueue>(RobotSettings::Default->MDEntryQueueItemsCount, RobotSettings::Default->MDEntryQueueItemsAddCount, "Some of MDEntryQueuePool");
    DebugInfoManager::Default->PrintMemoryInfo("MDEntryQueue::CreatePool");
    return res;
}
AutoAllocatePointerList<MDEntryQueue>* MDEntryQueue::Pool = MDEntryQueue::CreatePool();

