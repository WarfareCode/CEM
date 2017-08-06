# Locate yaml-cpp with API version 0.5
#
# This module defines
# YAMLCPP_FOUND, if false, do not try to link to yaml-cpp
# YAMLCPP_LIBRARY, where to find yaml-cpp
# YAMLCPP_INCLUDE_DIR, where to find yaml.h
#
# By default, the dynamic libraries of yaml-cpp will be found. To find the static ones instead,
# you must set the YAMLCPP_STATIC_LIBRARY variable to TRUE before calling find_package(YamlCpp ...).
#
# If yaml-cpp is not installed in a standard path, you can use the YAMLCPP_DIR CMake variable
# to tell CMake where yaml-cpp is.

include (${CMAKE_ROOT}/Modules/CheckIncludeFileCXX.cmake)
include (${CMAKE_ROOT}/Modules/CheckCXXSourceRuns.cmake)

# find the yaml-cpp include directory
find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
    PATH_SUFFIXES include
    PATHS
    ~/Library/Frameworks/yaml-cpp/include/
    /Library/Frameworks/yaml-cpp/include/
    /usr/local/include/yaml-cpp/
    /usr/local/include/
    /usr/include/yaml-cpp/
    /usr/include/
    /sw/yaml-cpp/ # Fink
    /opt/local/yaml-cpp/ # DarwinPorts
    /opt/csw/yaml-cpp/ # Blastwave
    /opt/yaml-cpp/
    ${YAMLCPP_DIR}/include/)

set(CMAKE_REQUIRED_INCLUDES ${YAMLCPP_INCLUDE_DIR})
set(CMAKE_REQUIRED_QUIET True)

# first look for outdated yaml-cpp0.3 include files
unset(YAMLCPP_FOUND_03 CACHE)

check_include_file_cxx("yaml-cpp/aliasmanager.h" YAMLCPP_FOUND_03)
if(${YAMLCPP_FOUND_03})
    message(WARNING "Found include file for libyaml-cpp0.3. Most probably this precludes libyaml-cpp0.5 from being properly installed")
endif()

# now look for needed yaml-cpp0.5 include files
unset(YAMLCPP_FOUND_05 CACHE)
check_include_file_cxx("yaml-cpp/node/detail/iterator_fwd.h" YAMLCPP_FOUND_05)
if(${YAMLCPP_FOUND_05})
else()
    message(FATAL_ERROR "Include file for libyaml-cpp0.5 not found")
endif()

# attempt to find static library first if this is set
if(YAMLCPP_STATIC_LIBRARY)
    set(YAMLCPP_STATIC libyaml-cpp.a)
endif()

# find the yaml-cpp library
find_library(YAMLCPP_LIBRARY
    NAMES ${YAMLCPP_STATIC} yaml-cpp
    PATH_SUFFIXES lib64 lib
    PATHS ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    ${YAMLCPP_DIR}/lib)

# try to compile, link, and run a test program
unset(YAMLCPP_RUNS CACHE)
set(CMAKE_REQUIRED_LIBRARIES yaml-cpp)
check_cxx_source_runs("#include \"yaml-cpp/yaml.h\"\n#include <assert.h>\nint main() {\n    YAML::Node node = YAML::Load(\"[1, 2, 3]\");\n    assert(node.IsSequence());\n}" YAMLCPP_RUNS)
if(${YAMLCPP_RUNS})
else()
    message(FATAL_ERROR "Test of libyaml-cpp0.5 failed")
endif()

# handle the QUIETLY and REQUIRED arguments and set YAMLCPP_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(YAMLCPP DEFAULT_MSG YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)
mark_as_advanced(YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)