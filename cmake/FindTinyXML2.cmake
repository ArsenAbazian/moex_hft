include(Colors)
find_path(TINYXML_INCLUDE_DIR
    NAMES
    tinyxml2.h
    HINTS
    "${CMAKE_SOURCE_DIR}/opt/include"
    PATH_SUFFIXES
    include
    PATHS
    "${CMAKE_SOURCE_DIR}/opt/include"
    /usr/include
    /opt/local/include
    /usr/local/include
    NO_DEFAULT_PATH
)

find_library(TINYXML_LIBRARY
    NAMES tinyxml2
    HINTS
    "${CMAKE_SOURCE_DIR}/opt/lib"
    PATH_SUFFIXES
    lib
    PATHS
    "${CMAKE_SOURCE_DIR}/opt/lib"
    /usr/local/lib
    /opt/local/lib
    /usr/lib
    NO_DEFAULT_PATH
)

if (TINYXML_INCLUDE_DIR AND TINYXML_LIBRARY)
  set(TINYXML_FOUND TRUE)
  set( TINYXML_LIBRARIES ${TINYXML_LIBRARY} )
else ()
  set(TINYXML_FOUND FALSE)
  set( TINYXML_LIBRARIES )
endif ()

if (TINYXML_FOUND)
  message(STATUS "${Green}Found TinyXML: ${BoldBlue}${TINYXML_LIBRARY}${ColourReset}")
  mark_as_advanced(
    TINYXML_LIBRARY
    TINYXML_INCLUDE_DIR
  )
else ()
  message(STATUS "${Red}Not Found TinyXML library - trying to build on next run${ColourReset}")
endif ()
