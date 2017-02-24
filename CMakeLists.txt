cmake_minimum_required(VERSION 3.5)
project(hft_robot)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(InstallRequiredSystemLibraries)
include(ExternalProject)
include(Colors)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelInfo;MinSize" CACHE
  STRING "Possible build types"
  FORCE
  )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_custom_target(clean-cmake
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/cmake/CleanCmake.cmake
)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "You don't define build type.\nPlease define like ${BoldYellow}-DCMAKE_BUILD_TYPE={Debug|Release|RelInfo|MinSize}${ColourReset}\nBy default building ${BoldGreen}DEBUG${ColourReset}")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE_UPPER}" CACHE
    STRING "Choose the type of build, options are: Debug, Release, RelInfo, MinSize"
    FORCE
    )

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
  message(STATUS "Building ${BoldRed}DEBUG${ColourReset} version")
elseif(CMAKE_BUILD_TYPE_LOWER MATCHES relinfo)
  message(STATUS "Building ${BoldGreen}Release with debug info${ColourReset} version")
  set(CMAKE_BUILD_TYPE RELEASE)
elseif(CMAKE_BUILD_TYPE_LOWER MATCHES minsize)
  message(STATUS "Building ${BoldGreen}Minimal size Release${ColourReset} version")
  set(CMAKE_BUILD_TYPE RELEASE)
else()
  message(STATUS "Building ${BoldGreen}${CMAKE_BUILD_TYPE}${ColourReset} version")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE_LOWER}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build/${CMAKE_BUILD_TYPE_LOWER})

find_package(CSharp)
include(GetPkgVariable)

# First add task to compile code generator

pkg_get_variable(mono-options Sources)
message(STATUS "${Green}Found Mono.Options in ${BoldBlue}${MONO_OPTIONS_SOURCES}${ColourReset}")

set(fast_generator ${EXECUTABLE_OUTPUT_PATH}/fast_generator)
file(MAKE_DIRECTORY ${fast_generator})
add_custom_command(OUTPUT ${fast_generator}
  COMMAND ${CSHARP_COMPILER} -sdk:4.0 -out:${fast_generator} ${CMAKE_CURRENT_LIST_DIR}/tools/Program.cs ${CMAKE_CURRENT_LIST_DIR}/tools/AssemblyInfo.cs ${MONO_OPTIONS_SOURCES}
  COMMENT "building fast_generator..."
        )

add_custom_target(fast_generate ALL
  DEPENDS ${fast_generator}
)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

set(common_params "-march=corei7 -msse4.2 -msse4.1 -m64 -mtune=corei7 -fpic -pthread -std=gnu++1z -fms-extensions -mcx16 -D__STDC_LIMIT_MACROS")
#set(common_params "${common_params} --target=x86_64-pc-linux-elf")
#set(CMAKE_CXX_FLAGS_DEBUG "${common_params} -g3 - O0")
#set(CMAKE_CXX_FLAGS_RELEASE "${common_params} -g0 -O3")

set(CMAKE_C_FLAGS "${common_flags}" CACHE STRING "contains options always passed to the C compiler." FORCE)
set(CMAKE_CXX_FLAGS "${common_flags}" CACHE STRING "contains options always passed to the C++ compiler." FORCE)
set(${PROJECT_NAME}_CFLAGS_ARE_CONFIGURED YES CACHE INTERNAL "indicates that the ${PROJECT_NAME} CFLAGS have been configured.")

set(dpdk_PREFIX "${CMAKE_CURRENT_LIST_DIR}/deps/dpdk")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${common_params}")

file(GLOB_RECURSE sources source/src/*.c*)
file(GLOB_RECURSE includes source/include/*.h)
get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)

foreach(it ${includes})
    get_filename_component(dir ${it} DIRECTORY)
    if(NOT ("${dir}" STREQUAL "${olddir}"))
        set(olddir ${dir})
        include_directories(${dir})
    endif(NOT ("${dir}" STREQUAL "${olddir}"))
endforeach(it)

set(include_path "")
foreach(inc_dir ${inc_dirs})
    set(include_path "${include_path} -I${inc_dir}")
endforeach(inc_dir)

add_executable(hft_robot
        source/src/Settings.cpp
        ${sources}
        source/src/Stopwatch.cpp
        source/include/Stopwatch.h
        source/src/Test/FixProtocolManagerTester.cpp
        source/include/Test/FixProtocolManagerTester.h
        source/include/Fix/FixProtocolMacros.h
        source/include/Fix/FixMessage.h
        source/include/Fast/FastTypes.h
        source/include/Lib/StringIdComparer.h
        source/include/Lib/PointerList.h
        source/include/Lib/AutoAllocatePointerList.h
        source/include/MarketData/MarketDataTable.h
        source/include/Test/DecimalTester.h
        source/src/Fix/FixTypes.cpp
        source/include/Test/OrderTesterFond.h
        source/include/Test/FeedConnectionTester.h
        source/include/Test/TradeTesterFond.h
        source/include/Test/SecurityDefinitionTester.h
        source/include/Test/TestTemplateInfo.h
        source/include/Test/TestMessagesHelper.h
        source/include/Test/StatisticsTesterFond.h
        source/include/MarketData/MarketDataEntryQueue.h
        source/include/MarketData/OrderInfo.h
        source/include/MarketData/TradeInfo.h
        source/include/MarketData/StatisticInfo.h
        source/include/MarketData/MarketSymbolInfo.h
        source/include/Test/OrderTesterCurr.h
        source/include/Test/TradeTesterCurr.h
        source/include/Test/StatisticsTesterCurr.h
        source/include/MarketData/QuoteInfo.h
        source/include/Test/SymbolManagerTester.h
        source/include/Lib/StringHash.h
        source/include/MarketData/SymbolManager.h
        source/include/Feeds/FeedConnections.h
        source/src/Test/TestMessagesHelper.cpp
        source/include/Test/PointerListTester.h
        source/src/Converters/DtoaConverter.cpp
        source/include/Test/SecurityStatusTester.h
        source/include/Feeds/FeedTypes.h
        source/src/MarketData/StatisticInfo.cpp
        source/include/Managers/DebugInfoManager.h
        source/src/Managers/DebugInfoManager.cpp
        source/include/Feeds/Fond/FondOlr.h
        source/include/Feeds/Fond/FondMsr.h
        source/include/Feeds/Fond/FondIsf.h
        source/include/Feeds/Curr/CurrHr.h
        source/include/Test/HistoricalReplayTester.h
        source/include/ProgramStatistics.h
        source/src/ProgramStatistics.cpp)
add_dependencies(hft_robot fast_generate)

add_custom_command(TARGET fast_generate
  PRE_BUILD
  COMMAND ${CSHARP_MONO_INTERPRETER_} ${fast_generator}
        -d ${CMAKE_CURRENT_LIST_DIR}/test/data/
        -s ${CMAKE_CURRENT_LIST_DIR}/source/
        -f
        -fh ${CMAKE_CURRENT_LIST_DIR}/source/include/Fast/FastProtocolManager.h
        -fc ${CMAKE_CURRENT_LIST_DIR}/source/src/Fast/FastProtocolManager.cpp
        -ft ${CMAKE_CURRENT_LIST_DIR}/source/include/Fast/FastTypes.h
        -fx ${CMAKE_CURRENT_LIST_DIR}/test/data/FIX50SP2-2017-Mar.xml
        -rb ${CMAKE_CURRENT_LIST_DIR}/source/src/Robot.cpp
        -fcfg ${CMAKE_CURRENT_LIST_DIR}/test/data/config_test.xml
        -fwe "Logon,Logout,Security Definition,Security Status,Trading Session Status,Hearthbeat"
        COMMENT "generating code...")

#target_link_libraries(hft_robot -Wl,--whole-archive -Wl,--no-whole-archive dl)
#set_target_properties(hft_robot PROPERTIES LINKER_LANGUAGE CXX)
