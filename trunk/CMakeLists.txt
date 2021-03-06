#Primary CMakeLists.txt file for Ben's CEM project
#Currently Tested for Unix Makefiles and XCode Projects
cmake_minimum_required(VERSION 3.2.2)
project(cem CXX)
enable_testing()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(EXE_NAME dcem)
else()
  set(EXE_NAME cem)
endif()

message("EXE_NAME: " ${EXE_NAME})
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

#Ensure C++11 standard is used - may need to roll this into specific generators for other platforms
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

#set the source directory (trunk/src) and module path to the current directory (trunk)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#set the bin directory and set a command to create it during the build process
set(BINARY_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
add_custom_target(build-time-make-bin-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BINARY_DIRECTORY})

#set the test directory and create it during the build process
set(BINARY_TEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/tests)
add_custom_target(build-time-make-bin-test-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BINARY_TEST_DIRECTORY})

#add the common and interface headers to the include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/Common ${CMAKE_CURRENT_SOURCE_DIR}/src/Interfaces ${CMAKE_CURRENT_SOURCE_DIR}/src/MockInterfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/SourceControl ${CMAKE_CURRENT_SOURCE_DIR}/src/DataLogger ${CMAKE_CURRENT_SOURCE_DIR}/src/FDTD ${CMAKE_CURRENT_SOURCE_DIR}/src/Factories )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/TimeControl)
    
#find the additional libraries needed
#HDF5 - used for data logging
find_package (HDF5 COMPONENTS CXX)
message( "HDF5 Found: " ${HDF5_FOUND})

find_package(Log4cplus)
message( "Log4cplus Found: " ${LOG4CPLUS_FOUND})

#Doxygen - used to generate code documentation
find_package(Doxygen)
message("Doxygen found: " ${DOXYGEN_FOUND})

#Eigen - matrix library
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
message("Eigen3 found: " ${EIGEN3_FOUND})
include_directories(${EIGEN3_INCLUDE_DIR})

#Gperftools
find_package(Gperftools)
message("GPerftools found: " ${GPERFTOOLS_FOUND})
if(${GPERFTOOLS_FOUND})
#set the tmp  directory and set a command to create it during the build process
set(GPERF_TMP_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/tests/tmp)
add_custom_target(build-time-make-gperf-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GPERF_TMP_DIRECTORY})   
else()
  set(GPERFTOOLS_LIBRARIES "")
endif()

#FFTW
find_package (FFTW)
message("FFTW Found: " ${FFTW_FOUND})

#External libraries contain YAML-CPP and GOOGLE_TEST, these are explicitly included in the
#repository due to conflicts when building/linking
add_subdirectory(External_Libraries)
message("YAMLCPP_INCLUDE_DIR: " ${YAMLCPP_INCLUDE_DIR})
message("GTEST_INCLUDE_DIR: " ${GTEST_INCLUDE_DIR})
message("GMOCK_INCLUDE_DIR: " ${GMOCK_INCLUDE_DIR})

#add the additional include directories
include_directories(${HDF5_INCLUDE_DIR} ${LOG4CPLUS_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

#add the src subdirectory
add_subdirectory(${SOURCE_DIRECTORY})

#redirect the runtime output directory to the desired location - this should occur after adding the src subdirectory so that the test binaries are not generated in the same folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})

#Add the main function and the link libraries
add_executable(${EXE_NAME} ${SOURCE_DIRECTORY}/main.cpp)
target_link_libraries(${EXE_NAME} ${HDF5_LIBRARIES} SimManager CEMCommon ${LOG4CPLUS_LIBRARIES})

#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

# add a target to generate API documentation with Doxygen
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
                    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM
                  )
   add_custom_target(pdfdoc
                     make
		     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
		     COMMENT "Generating PDF documentation" VERBATIM
                    )

   #set the bin directory and set a command to create it during the build process
   set(DOCS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../docs)
   add_custom_target(build-time-make-docs-directory ALL
    		   COMMAND ${CMAKE_COMMAND} -E make_directory ${DOCS_DIRECTORY})

  #copy docs to docs directory
  add_custom_command(
        TARGET pdfdoc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
                ${DOCS_DIRECTORY})

  add_custom_command(TARGET doc POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_BINARY_DIR}/html
		   ${DOCS_DIRECTORY}/html)
		    
endif(DOXYGEN_FOUND)


#add the run test
add_test(NAME Run_cem 
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
	 CEMInputTestFile.yaml)
	 
#Add the Memory Test if gperftools were found
if(RUN_MEMCHECK)
if(${GPERFTOOLS_FOUND})
add_test(NAME MemCheck_cem 
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
	 CEMInputTestFile.yaml)

set_property(
             TEST
	      MemCheck_cem
	      PROPERTY
	      ENVIRONMENT HEAPPROFILE=${GPERF_TMP_DIRECTORY}/heapprof_cem_test)
set_property(
             TEST
	      MemCheck_cem
	      APPEND PROPERTY
	      ENVIRONMENT HEAPCHECK=1)
set_property(
             TEST
	      MemCheck_cem
	      APPEND PROPERTY
	      ENVIRONMENT CPUPROFILE=${GPERF_TMP_DIRECTORY}/cpuprof_cem_test)
set_property(
             TEST
	      MemCheck_cem
	      APPEND PROPERTY
	      ENVIRONMENT MALLOCSTATS=4)
endif()
endif()



