#Primary CMakeLists.txt file for Ben's CEM project
#Currently Tested for Unix Makefiles and XCode Projects
cmake_minimum_required(VERSION 3.2.2)
project(cem CXX)
enable_testing()

#Ensure C++11 standard is used - may need to roll this into specific generators for other platforms
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

#set the source directory (trunk/src) and module path to the current directory (trunk)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#set the bin directory and set a command to create it during the build process
set(BINARY_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
add_custom_target(build-time-make-bin-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BINARY_DIRECTORY})

set(BINARY_TEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/tests)
add_custom_target(build-time-make-bin-test-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BINARY_TEST_DIRECTORY})
    
#find the additional libraries needed
#HDF5 - used for data logging
find_package (HDF5 COMPONENTS CXX)
message( "HDF5 Found: " ${HDF5_FOUND})

#Doxygen - used to generate code documentation
find_package(Doxygen)
message("Doxygen found: " ${DOXYGEN_FOUND})

#FFTW - placeholder, not currently used
#find_package (FFTW)
#message("FFTW Found: " ${FFTW_FOUND})

#External libraries contain YAML-CPP and GOOGLE_TEST, these are explicitly included in the
#repository due to conflicts when building/linking
add_subdirectory(External_Libraries)
message("YAMLCPP_INCLUDE_DIR: " ${YAMLCPP_INCLUDE_DIR})
message("GTEST_INCLUDE_DIR: " ${GTEST_INCLUDE_DIR})
message("GMOCK_INCLUDE_DIR: " ${GMOCK_INCLUDE_DIR})

#add the additional include directories
include_directories(${HDF5_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR} {CMAKE_CURRENT_SOURCE_DIR})

#add the src subdirectory
add_subdirectory(${SOURCE_DIRECTORY})

#redirect the runtime output directory to the desired location - this should occur after adding the src subdirectory so that the test binaries are not generated in the same folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIRECTORY})

#Add the main function and the link libraries
add_executable(cem ${SOURCE_DIRECTORY}/main.cpp)
target_link_libraries(cem ${HDF5_LIBRARIES} yaml-cpp DataLogger FDTD InputParser)

#make sure to include math defines for Windows Visual Studio
target_compile_definitions(cem PRIVATE "-D_USE_MATH_DEFINES")

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

  add_custom_command(TARGET pdfdoc POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_BINARY_DIR}/html
		   ${DOCS_DIRECTORY}/html)
		    
endif(DOXYGEN_FOUND)
