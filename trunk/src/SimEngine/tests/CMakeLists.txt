if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

#create the SimEngine test suite

#first need to configure the executable test
#first need to configure the executable test
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(EXE_NAME dSimEngine_Test)
else()
  set(EXE_NAME SimEngine_Test)
endif()


include_directories( ${SOURCE_DIRECTORY}/SimEngine
                     ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (${EXE_NAME} SimEngine_test.cpp)
target_link_libraries (${EXE_NAME} CEMFactories InputParser yaml-cpp gmock_main  ${GPERFTOOLS_LIBRARIES})
#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

#now copy the needed input data files to the appropriate directory for running stand alone		      
add_custom_command(TARGET ${EXE_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
		   ${CMAKE_SOURCE_DIR}/src/InputParser/tests/Input_Data
                   ${BINARY_TEST_DIRECTORY}/Input_Data)
		   
#Now add the tests
#First is the Build Test
add_test(NAME Build_SimEngineTest
         COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --config $<CONFIGURATION> --target ${EXE_NAME})
         
#Next is the Run Tests
add_test(NAME Run_SimEngineTest 
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
	  --gtest_output=xml:${GPERF_TMP_DIRECTORY}/${EXE_NAME}_results.xml)

#Next is the Memory Test if gperftools were found
if(RUN_MEMCHECK)
if(${GPERFTOOLS_FOUND})
add_test(NAME MemCheck_SimEngineTest 
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})

set_property(
             TEST
	      MemCheck_SimEngineTest
	      PROPERTY
	      ENVIRONMENT HEAPPROFILE=${GPERF_TMP_DIRECTORY}/heapprof_simengine_test)
set_property(
             TEST
	      MemCheck_SimEngineTest
	      APPEND PROPERTY
	      ENVIRONMENT HEAPCHECK=1)
set_property(
             TEST
	      MemCheck_SimEngineTest
	      APPEND PROPERTY
	      ENVIRONMENT CPUPROFILE=${GPERF_TMP_DIRECTORY}/cpuprof_simengine_test)
set_property(
             TEST
	      MemCheck_SimEngineTest
	      APPEND PROPERTY
	      ENVIRONMENT MALLOCSTATS=4)
endif()
endif()
		   
#Finally we have the Valgrind test (if enabled)
if(RUN_VALGRIND)
	add_test(NAME Valgrind_SimEngineTest 
	         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	         COMMAND valgrind --leak-check=full
	         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})
endif()
