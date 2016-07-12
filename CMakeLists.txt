cmake_minimum_required(VERSION 3.5)
project(hft_robot)

set(common_params "-fpic -pthread -std=gnu++1z -fms-extensions -mcx16")
#set(CMAKE_CXX_FLAGS_DEBUG "${common_params} -g3 - O0")
#set(CMAKE_CXX_FLAGS_RELEASE "${common_params} -g0 -O3")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${common_params}")

INCLUDE_DIRECTORIES(tinyxml2)
LINK_DIRECTORIES(tinyxml2)


set(SOURCE_FILES
        tinyxml2.h
        tinyxml2.cpp
        ConnectionParameters.h
        ConsoleManager.cpp
        ConsoleManager.h
        DtoaConverter.h
        DtoaConverter.cpp
        FastProtocolManager.h
        FastProtocolManager.cpp
        FastProtocolTester.cpp
        FastProtocolTester.h
        FeedChannel.cpp
        FeedChannel.h
        FeedConnection.cpp
        FeedConnection.h
        FixProtocolManager.cpp
        FixProtocolManager.h
        FixTypes.h
        HftConsole.cpp
        ItoaConverter.cpp
        ItoaConverter.h
        ItoaTester.cpp
        ItoaTester.h
        LogManager.cpp
        LogManager.h
        MarketInfo.cpp
        MarketInfo.h
        MarketServerInfo.h
        MarketServerInfo.cpp
        ProtocolHistoryManager.cpp
        ProtocolHistoryManager.h
        Robot.cpp
        Robot.h
        Types.h
        UTCTimeConverter.cpp
        UTCTimeConverter.h
        UTCTimeConverterTester.h
        UTCTimeConverterTester.cpp
        WinSockManager.cpp
        WinSockManager.h)

add_executable(hft_robot ${SOURCE_FILES})
set_target_properties(hft_robot PROPERTIES LINKER_LANGUAGE CXX)