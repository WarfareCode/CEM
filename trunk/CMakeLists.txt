
cmake_minimum_required(VERSION 3.2.2)

project(cem_test CXX)

enable_testing()

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#find the necessary modules
#
#HDF5
find_package (HDF5 COMPONENTS CXX)
message( "HDF5 Found: " ${HDF5_FOUND})
#
#YAMLCPP
find_package(YAMLCPP)
message("YAMLCPP Found: " ${YAMLCPP_FOUND})

#
#FFTW
find_package (FFTW)
message("FFTW Found: " ${FFTW_FOUND})

#add the include directories
include_directories(${HDF5_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR} {CMAKE_CURRENT_SOURCE_DIR})

#add the subdirectories
add_subdirectory(${SOURCE_DIRECTORY})

add_executable(cem_test ${SOURCE_DIRECTORY}/main.cpp)
target_link_libraries(cem_test ${HDF5_LIBRARIES} ${YAMLCPP_LIBRARY} DataLogger FDTD InputParser)

