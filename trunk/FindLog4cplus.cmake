#-------------------------------------------------------------------------------------
# Locate Log4cplus library
# This module defines
#    LOG4CPLUS_FOUND, if false, do not try to link to Log4cplus
#    LOG4CPLUS_LIBRARIES
#    LOG4CPLUS_INCLUDE_DIR, where to find log4cplus.hppa
#
# Original script was picked up here 
#    https://github.com/manvelavetisian/cmake-modules/blob/master/FindLog4cplus.cmake
#
# 2013 - snikulov
# And modified
#  Additional params which can be set to search for libs
#    Log4Cplus_USE_STATIC_LIBS
#    Log4Cplus_USE_UNICODE
#  Location hint can be provided through
#    environment var LOG4CPLUS_ROOT in addition to LOG4CPLUS_DIR
#    cmake vars LOG4CPLUS_DIR & LOG4CPLUS_ROOT
#-------------------------------------------------------------------------------------

if (LOG4CPLUS_INCLUDE_DIR)
  # Already in cache, be silent
  set(LOG4CPLUS_FIND_QUIETLY TRUE)
endif ()

find_path(LOG4CPLUS_INCLUDE_DIR logger.h NO_DEFAULT_PATH PATHS
  /opt/local/include
  /usr/local/include
  /usr/include
  PATH_SUFFIXES
  log4cplus
)

message("LOG4CPLUS_INCLUDE_DIR: " ${LOG4CPLUS_INCLUDE_DIR})

set(LOG4CPLUS_NAMES log4cplus)
find_library(LOG4CPLUS_LIBRARY NO_DEFAULT_PATH 
  NAMES ${LOG4CPLUS_NAMES}
  PATHS /usr/lib /usr/local/lib /opt/local/lib
)

if (LOG4CPLUS_INCLUDE_DIR AND LOG4CPLUS_LIBRARY)
  set(LOG4CPLUS_FOUND TRUE)
  set(LOG4CPLUS_LIBRARIES ${LOG4CPLUS_LIBRARY} CACHE INTERNAL "" FORCE)
  set(LOG4CPLUS_INCLUDE_DIRS ${LOG4CPLUS_INCLUDE_DIR} CACHE INTERNAL "" FORCE)
else ()
  set(LOG4CPLUS_FOUND FALSE CACHE INTERNAL "" FORCE)
  set(LOG4CPLUS_LIBRARY "" CACHE INTERNAL "" FORCE)
  set(LOG4CPLUS_LIBRARIES "" CACHE INTERNAL "" FORCE)
  set(LOG4CPLUS_INCLUDE_DIR "" CACHE INTERNAL "" FORCE)
  set(LOG4CPLUS_INCLUDE_DIRS "" CACHE INTERNAL "" FORCE)
endif ()

if (LOG4CPLUS_FOUND)
  if (NOT LOG4CPLUS_FIND_QUIETLY)
    message(STATUS "Found LOG4CPLUS: ${LOG4CPLUS_LIBRARIES}")
  endif ()
else ()
  if (LOG4CPLUS_FIND_REQUIRED)
    message(STATUS "Looked for LOG4CPLUS libraries named ${LOG4CPLUS_NAMES}.")
    message(FATAL_ERROR "Could NOT find LOG4CPLUS library")
  endif ()
endif ()

#mark_as_advanced(
#  LOG4CPLUS_LIBRARIES
#  LOG4CPLUS_INCLUDE_DIRS
#)

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set LOG4CPLUS_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Log4cplus DEFAULT_MSG LOG4CPLUS_LIBRARIES LOG4CPLUS_INCLUDE_DIR)

MARK_AS_ADVANCED(LOG4CPLUS_INCLUDE_DIR LOG4CPLUS_LIBRARIES)
