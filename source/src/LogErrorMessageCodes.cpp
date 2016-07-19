//
// Created by root on 18.07.16.
//
#include "LogErrorMessageCodes.h"

void LogMessageProvider::InitializeLogMessageText() {
#pragma region LogMessagesProvider_InitArray_GeneratedCode
    this->LogMessageText = new const char*[100];
#pragma endregion

#pragma region LogMessagesProvider_InitializeLogMessageText_GeneratedCode
    this->LogMessageText[LogMessageCode::lmcNone] = "none";
    this->LogMessageText[LogMessageCode::lmcSuccess] = "success";
    this->LogMessageText[LogMessageCode::lmcFailed] = "failed";
#pragma endregion
}

LogMessageProvider::LogMessageProvider() {

}

LogMessageProvider::~LogMessageProvider() {

}


