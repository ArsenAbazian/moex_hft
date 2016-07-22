unset(CSHARP_COMPILER CACHE)
unset(CSHARP_INTERPRETER CACHE)
unset(CSHARP_TYPE CACHE)
unset(CSHARP_VERSION CACHE)
unset(CSHARP_FOUND CACHE)

set(CSHARP_PLATFORM "anycpu" CACHE STRING "C# target platform: x86, x64, anycpu, or itanium")
if(NOT ${CSHARP_PLATFORM} MATCHES "x86|x64|anycpu|itanium")
  message(FATAL_ERROR "The C# target platform ${Red}'${CSHARP_PLATFORM}'${ColourReset} is not valid. Please enter one of the following: x86, x64, anycpu, or itanium")
endif()

find_package(Mono)

if (CSHARP_MONO_FOUND)
  set(CSHARP_TYPE "Mono" CACHE STRING "Using the Mono compiler")
  set(CSHARP_VERSION ${CSHARP_MONO_VERSION} CACHE STRING "C# Mono compiler version" FORCE)
  set(CSHARP_COMPILER ${CSHARP_MONO_COMPILER_${CSHARP_MONO_VERSION}} CACHE STRING "Full path to Mono compiler" FORCE)
  set(CSHARP_INTERPRETER ${CSHARP_MONO_INTERPRETER_${CSHARP_MONO_VERSION}} CACHE STRING "Full path to Mono interpretor" FORCE)
  set(CSHARP_SDK "/sdk:2" CACHE STRING "C# Mono SDK commandline switch (e.g. /sdk:2, /sdk:4, /sdk:5)")
endif()

mark_as_advanced(CSHARP_TYPE CSHARP_VERSION CSHARP_COMPILER CSHARP_INTERPRETER CSHARP_PLATFORM CSHARP_SDK)

message(STATUS "${Green}Using C# ${BoldBlue}${CSHARP_MONO_COMPILER_${CSHARP_MONO_VERSION}}${ColourReset}")
