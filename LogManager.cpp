#include "LogManager.h"


LogManager::LogManager()
{
}


LogManager::~LogManager()
{
}

LogManager* DefaultLogManager::Default = new ConsoleLogManager();
