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

set(TinyXML_PREFIX "${CMAKE_CURRENT_LIST_DIR}/deps/tinyxml2")
set(dpdk_PREFIX "${CMAKE_CURRENT_LIST_DIR}/deps/dpdk")

#[[
set(ENV{RTE_TARGET} "x86_64-native-linuxapp-clang")
set(ENV{RTE_SDK} "${CMAKE_CURRENT_LIST_DIR}/opt/dpdk")
set(DPDK_ARCH "x86_64-native-linuxapp-clang")
find_package(DPDK)
if(DPDK_FOUND)
    include_directories("${DPDK_INCLUDE_DIR}")
    add_custom_target(dpdk)
else(DPDK_FOUND)
    ExternalProject_Add(dpdk PREFIX ${dpdk_PREFIX}
      GIT_REPOSITORY http://dpdk.org/git/dpdk
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/vendor/dpdk-2.1.0.patch
      CONFIGURE_COMMAND make config DESTDIR=${CMAKE_CURRENT_LIST_DIR}/opt T=${DPDK_ARCH}
      BUILD_COMMAND make install DESTDIR=${CMAKE_CURRENT_LIST_DIR}/opt/dpdk T=${DPDK_ARCH}
      INSTALL_COMMAND make install DESTDIR=${CMAKE_CURRENT_LIST_DIR}/opt/dpdk T=${DPDK_ARCH}
      INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/opt/dpdk"
    )
    ExternalProject_Get_Property(dpdk INSTALL_DIR)
    include_directories("${INSTALL_DIR}/${DPDK_ARCH}/include")
    link_directories("${INSTALL_DIR}/${DPDK_ARCH}/lib")
    set(DPDK_LIBRARIES "-lethdev -lrte_malloc -lrte_mbuf -lrte_distributor -lrte_mempool -lrte_ring -lrte_eal -lrte_pmd_ixgbe -lrte_hash -lrte_kvargs -lrte_pmd_pcap")
endif(DPDK_FOUND)
]]

find_package(TinyXML2)
message(STATUS "${Red} ${TINYXML_FOUND}${ColourReset}")
# set(TINYXML_FOUND FALSE)
if(TINYXML_FOUND)
    include_directories("${TINYXML_INCLUDE_DIR}")
    add_custom_target(tinyxml)
else(TINYXML_FOUND)
    message(STATUS "${Yellow}Building TinyXML2${ColourReset}")
    ExternalProject_Add(tinyxml PREFIX ${TinyXML_PREFIX}
      GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
      GIT_TAG 3.0.0
      BUILD_IN_SOURCE 1
      CMAKE_ARGS -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_STATIC_LIBS:BOOL=ON -DCMAKE_INSTALL_LIBDIR=${CMAKE_CURRENT_LIST_DIR}/opt/lib -DCMAKE_INSTALL_INCLUDEDIR=${CMAKE_CURRENT_LIST_DIR}/opt/include
#      BUILD_COMMAND make
#      CONFIGURE_COMMAND make
#      INSTALL_COMMAND make install DESTDIR=${CMAKE_CURRENT_LIST_DIR}/opt prefix=
      INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/opt"
    )
    ExternalProject_Get_Property(tinyxml INSTALL_DIR)
    include_directories("${INSTALL_DIR}/include")
    link_directories("${INSTALL_DIR}/lib")
    set(TINYXML_LIBRARY "-ltinyxml2")
endif(TINYXML_FOUND)

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

add_executable(hft_robot ${sources} source/src/Stopwatch.cpp source/include/Stopwatch.h source/src/Test/FixProtocolManagerTester.cpp source/include/Test/FixProtocolManagerTester.h source/include/FixProtocolMacros.h source/include/FixMessage.h source/include/FastTypes.h source/include/Lib/StringIdComparer.h source/include/Lib/PointerList.h source/include/Lib/AutoAllocatePointerList.h source/include/Test/HashTableTester.h source/include/MarketData/MarketDataTable.h source/include/Test/DecimalTester.h source/src/FixTypes.cpp source/include/Test/OrderTesterFond.h source/include/Test/FeedConnectionTester.h source/include/Test/TradeTesterFond.h source/include/Test/InstrumentDefinitionTester.h source/include/Test/TestTemplateInfo.h source/include/Test/TestMessagesHelper.h source/include/Test/StatisticsTesterFond.h source/include/MarketData/MarketDataEntryQueue.h source/include/MarketData/OrderInfo.h source/include/MarketData/TradeInfo.h source/include/MarketData/StatisticInfo.h source/include/MarketData/MarketSymbolInfo.h source/include/Test/OrderTesterCurr.h source/include/Test/TradeTesterCurr.h source/include/Test/StatisticsTesterCurr.h source/include/MarketData/QuoteInfo.h)
add_dependencies(hft_robot tinyxml fast_generate)
target_link_libraries(hft_robot ${TINYXML_LIBRARY} dl)

add_custom_command(TARGET fast_generate
  PRE_BUILD
  COMMAND ${CSHARP_MONO_INTERPRETER_} ${fast_generator} -d ${CMAKE_CURRENT_LIST_DIR}/test/data/ -s ${CMAKE_CURRENT_LIST_DIR}/source/ -f -fh ${CMAKE_CURRENT_LIST_DIR}/source/include/FastProtocolManager.h -fc ${CMAKE_CURRENT_LIST_DIR}/source/src/FastProtocolManager.cpp -ft ${CMAKE_CURRENT_LIST_DIR}/source/include/FastTypes.h -fx ${CMAKE_CURRENT_LIST_DIR}/test/data/FIX50SP2-2017-Mar.xml -fwe "Logon,Logout,Security Definition,Security Status,Trading Session Status,Hearthbeat"
        COMMENT "generating code...")

#target_link_libraries(hft_robot -Wl,--whole-archive ${TINYXML_LIBRARY} -Wl,--no-whole-archive dl)
#set_target_properties(hft_robot PROPERTIES LINKER_LANGUAGE CXX)
