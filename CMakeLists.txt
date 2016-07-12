cmake_minimum_required(VERSION 3.5)
project(hft_robot)

add_custom_target(clean-cmake
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/cmake/CleanCmake.cmake
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(InstallRequiredSystemLibraries)
include(ExternalProject)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

set(common_params "-march=corei7 -msse4.2 -msse4.1 -m64 -mtune=corei7 -fpic -pthread -std=gnu++1z -fms-extensions -mcx16 -D__STDC_LIMIT_MACROS")
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
if(TINYXML_FOUND)
    include_directories("${TINYXML_INCLUDE_DIR}")
    add_custom_target(tinyxml)
else(TINYXML_FOUND)
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

INCLUDE_DIRECTORIES(tinyxml2)
LINK_DIRECTORIES(tinyxml2)

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

add_executable(hft_robot ${sources})
add_dependencies(hft_robot tinyxml)
#set_target_properties(hft_robot PROPERTIES LINKER_LANGUAGE CXX)
