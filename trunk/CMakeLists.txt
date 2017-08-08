
cmake_minimum_required(VERSION 3.2.2)

project(cem_test CXX)

enable_testing()
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

message("source dir:" ${CMAKE_CURRENT_SOURCE_DIR})
message("binary dir:" ${CMAKE_BINARY_DIR})
message("current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})

#find the necessary modules
#
#HDF5
find_package (HDF5 COMPONENTS CXX)
message( "HDF5 Found: " ${HDF5_FOUND})

#FFTW
find_package (FFTW)
message("FFTW Found: " ${FFTW_FOUND})

add_subdirectory(yaml-cpp)
add_subdirectory(googletest)

set(YAMLCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include)
set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
set(GMOCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include)

message(GTEST_INCLUDE_DIR ${GTEST_INCLUDE_DIR})

#add the include directories
include_directories(${HDF5_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} {CMAKE_CURRENT_SOURCE_DIR})

#add the subdirectories
add_subdirectory(${SOURCE_DIRECTORY})

add_executable(cem_test ${SOURCE_DIRECTORY}/main.cpp)
target_link_libraries(cem_test ${HDF5_LIBRARIES} yaml-cpp DataLogger FDTD InputParser)
#target_link_libraries(cem_test ${HDF5_LIBRARIES} ${YAMLCPP_LIBRARY} DataLogger FDTD InputParser)

