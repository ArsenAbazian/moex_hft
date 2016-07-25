set(chsarp_mono_names )

find_program(csharp_mono_compiler
  NAMES "mcs" "mcs.exe" "dmcs" "dmcs.exe" "smcs" "smcs.exe" "gmcs" "gmcs.exe"
  PATHS /usr/bin /usr/local/bin /usr/lib/mono/2.0 /opt/mono/bin
)

if (EXISTS ${csharp_mono_compiler})
  find_program(csharp_mono_interpreter
    NAMES mono
    PATHS /usr/bin /usr/local/bin /usr/lib/mono/2.0 /opt/mono/bin
  )
  if (EXISTS ${csharp_mono_interpreter})
      execute_process(COMMAND ${csharp_mono_interpreter} -V
        OUTPUT_VARIABLE csharp_mono_version_string
      )
      string(REGEX MATCH "([0-9]*)([.])([0-9]*)([.]*)([0-9]*)" csharp_mono_version_temp ${csharp_mono_version_string})
      set(CSHARP_MONO_INTERPRETER_${CSHARP_MONO_VERSION} ${csharp_mono_interpreter} CACHE STRING "C# Mono interpreter ${csharp_mono_version_temp}" FORCE)
      mark_as_advanced(CSHARP_MONO_INTERPRETER_${CSHARP_MONO_VERSION})
  else()
    message(FATAL_ERROR "Can't find .NET Mono interpreter")
  endif()
  unset(csharp_mono_interpreter CACHE)
  set(CSHARP_MONO_VERSION ${csharp_mono_version_temp} CACHE STRING "C# Mono compiler version")
  mark_as_advanced(CSHARP_MONO_VERSION)
  set(CSHARP_MONO_COMPILER_${CSHARP_MONO_VERSION} ${csharp_mono_compiler} CACHE STRING "C# Mono compiler ${CSHARP_MONO_VERSION}" FORCE)
  mark_as_advanced(CSHARP_MONO_COMPILER_${CSHARP_MONO_VERSION})
  set(CSHARP_MONO_VERSIONS ${CSHARP_MONO_VERSION} CACHE STRING "Available C# Mono compiler versions" FORCE)
  mark_as_advanced(CSHARP_MONO_VERSIONS)
  set(CSHARP_MONO_FOUND 1 CACHE INTERNAL "Boolean indicating if C# Mono was found")
else()
  message(WARNING "Can't find C# compiler")
endif()

unset(csharp_mono_compiler CACHE)

if (CSHARP_MONO_FOUND)
  message(STATUS "${Green}Found the following C# Mono versions: ${BoldBlue}${CSHARP_MONO_VERSIONS}${ColourReset}")
endif()
