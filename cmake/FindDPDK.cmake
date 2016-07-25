include(Colors)
set(DPDK_ROOT_DIR
    "${DPDK_ROOT_DIR}"
    CACHE
    PATH
    "Path to search for DPDK")

if(NOT "$ENV{RTE_SDK}" STREQUAL "")
    if(NOT "$ENV{RTE_TARGET}" STREQUAL "")
        if(NOT DPDK_ROOT_DIR)
            set(DPDK_ROOT_DIR "$ENV{RTE_SDK}/$ENV{RTE_TARGET}")
        endif()
    endif()
else()
    if(DPDK_ROOT_DIR)
        set(ENV{RTE_SDK} "${DPDK_ROOT_DIR}")
    endif()
endif()

MESSAGE(STATUS "DPDK root dir: " ${DPDK_ROOT_DIR})

find_path(DPDK_INCLUDE_DIR
    NAMES
    rte_config.h
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    include
    PATHS
    "${DPDK_ROOT_DIR}"
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_INCLUDE_DIR)

message(STATUS "DPDK include : " ${DPDK_INCLUDE_DIR})

find_library(DPDK_RTE_DISTR
    NAMES
    rte_distributor
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_DISTR)

find_library(DPDK_ETHDEV
    NAMES
    ethdev
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_ETHDEV)

find_library(DPDK_RTE_ACL
    NAMES
    rte_acl
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_ACL)

find_library(DPDK_RTE_CFG
    NAMES
    rte_cfgfile
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_CFG)

find_library(DPDK_RTE_CMD
    NAMES
    rte_cmdline
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_CMD)

find_library(DPDK_RTE_EAL
    NAMES
    rte_eal
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_EAL)

find_library(DPDK_RTE_HASH
    NAMES
    rte_hash
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_HASH)

find_library(DPDK_RTE_IPFRAG
    NAMES
    rte_ip_frag
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_IPFRAG)

find_library(DPDK_RTE_KNI
    NAMES
    rte_kni
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_KNI)

find_library(DPDK_RTE_KVA
    NAMES
    rte_kvargs
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_KVA)

find_library(DPDK_RTE_LPM
    NAMES
    rte_lpm
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_LPM)

find_library(DPDK_RTE_MALLOC
    NAMES
    rte_malloc
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_MALLOC)

find_library(DPDK_RTE_MBUF
    NAMES
    rte_mbuf
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_MBUF)

find_library(DPDK_RTE_MPOOL
    NAMES
    rte_mempool
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_MPOOL)

find_library(DPDK_RTE_METER
    NAMES
    rte_meter
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_METER)

find_library(DPDK_RTE_PIPE
    NAMES
    rte_pipeline
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_PIPE)

find_library(DPDK_RTE_AFP
    NAMES
    rte_pmd_af_packet
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_AFP)

find_library(DPDK_RTE_BOND
    NAMES
    rte_pmd_bond
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_BOND)

find_library(DPDK_RTE_E1000
    NAMES
    rte_pmd_e1000
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_E1000)

find_library(DPDK_RTE_ENIC
    NAMES
    rte_pmd_enic
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_ENIC)

find_library(DPDK_RTE_I40
    NAMES
    rte_pmd_i40e
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_I40)

find_library(DPDK_RTE_IXGBE
    NAMES
    rte_pmd_ixgbe
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_IXGBE)

find_library(DPDK_RTE_PCAP
    NAMES
    rte_pmd_pcap
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_PCAP)

find_library(DPDK_RTE_PMD_RING
    NAMES
    rte_pmd_ring
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_PMD_RING)

find_library(DPDK_RTE_VIRT
    NAMES
    rte_pmd_virtio_uio
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_VIRT)

find_library(DPDK_RTE_VMX
    NAMES
    rte_pmd_vmxnet3_uio
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_VMX)

find_library(DPDK_RTE_PORT
    NAMES
    rte_port
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_PORT)

find_library(DPDK_RTE_POWER
    NAMES
    rte_power
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_POWER)

find_library(DPDK_RTE_RING
    NAMES
    rte_ring
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_RING)

find_library(DPDK_RTE_SCHED
    NAMES
    rte_sched
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_SCHED)

find_library(DPDK_RTE_TABLE
    NAMES
    rte_table
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_TABLE)

find_library(DPDK_RTE_TIMER
    NAMES
    rte_timer
    HINTS
    "${DPDK_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    PATHS
    "${DPDK_ROOT_DIR}"
    /opt/intel/dpdk
    NO_DEFAULT_PATH
    NO_CMAKE_PATH)
mark_as_advanced(DPDK_RTE_TIMER)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(DPDK
    DEFAULT_MSG
#    DPDK_RTE_IXGBE
    DPDK_INCLUDE_DIR)

if(DPDK_FOUND)
    set(DPDK_INCLUDE_DIRS "${DPDK_INCLUDE_DIR}")
    set(DPDK_LIBRARIES "")#"${DPDK_ETHDEV}" "${DPDK_RTE_MALLOC}" "${DPDK_RTE_MBUF}" "${DPDK_RTE_DISTR}" "${DPDK_RTE_MPOOL}" "${DPDK_RTE_RING}" "${DPDK_RTE_EAL}" "${DPDK_RTE_IXGBE}" "${DPDK_RTE_HASH}" "${DPDK_RTE_KVA}" "${DPDK_RTE_PCAP}")
    mark_as_advanced(DPDK_ROOT_DIR)
endif()
