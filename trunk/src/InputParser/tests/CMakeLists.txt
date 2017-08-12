if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

#create the InputParser test suite

#first need to configure the executable test
set(EXE_NAME InputParser_Test)
include_directories( ${SOURCE_DIRECTORY}/InputParser
                     ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (${EXE_NAME} InputParser_test.cpp)
target_link_libraries (${EXE_NAME} InputParser yaml-cpp gmock_main)
#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

#now copy the needed input data files to the appropriate directory for running stand alone		      
add_custom_command(TARGET ${EXE_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
		   ${CMAKE_SOURCE_DIR}/src/InputParser/tests/Input_Data
                   ${BINARY_TEST_DIRECTORY}/Input_Data)
		   
#Now add the tests
#First is the Build Test
add_test(NAME Build_InputParserTest
         COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --config $<CONFIGURATION> --target ${EXE_NAME})
         
#Next is the Run Tests
add_test(NAME Run_InputParserTest 
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})

#Finally we have the Valgrind test (if enabled)
if(RUN_VALGRIND)
	add_test(NAME Valgrind_InputParserTest 
	         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	         COMMAND valgrind --leak-check=full
	         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})
endif()
