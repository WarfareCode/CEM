if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

#create the RandomVector test suite

#********************************** RandomVector Test Suite **********************
#first need to configure the executable test
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(EXE_NAME dRandomVectorTest)
else()
  set(EXE_NAME RandomVectorTest)
endif()

include_directories( ${SOURCE_DIRECTORY}/RandomVector
                     ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (${EXE_NAME} RandomVectorTest.cpp)
target_link_libraries (${EXE_NAME} RandomVector gmock_main ${GPERFTOOLS_LIBRARIES})

#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

		   
#Now add the tests
#First is the Build Test
add_test(NAME Build_RandomVectorTest
         COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --config $<CONFIGURATION> --target ${EXE_NAME})
         
#Next is the Run Tests
add_test(NAME Run_RandomVector_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
	  --gtest_output=xml:${GPERF_TMP_DIRECTORY}/${EXE_NAME}_results.xml)

#Next is the Memory Test if gperftools were found
if(RUN_MEMCHECK)
if(${GPERFTOOLS_FOUND})
add_test(NAME MemCheck_RandomVector_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})

set_property(
             TEST
	      MemCheck_RandomVector_Test
	      PROPERTY
	      ENVIRONMENT HEAPPROFILE=${GPERF_TMP_DIRECTORY}/heapprof_randomvector_test)
set_property(
             TEST
	      MemCheck_RandomVector_Test
	      APPEND PROPERTY
	      ENVIRONMENT HEAPCHECK=1)
set_property(
             TEST
	      MemCheck_RandomVector_Test
	      APPEND PROPERTY
	      ENVIRONMENT CPUPROFILE=${GPERF_TMP_DIRECTORY}/cpuprof_randomvector_test)
set_property(
             TEST
	      MemCheck_RandomVector_Test
	      APPEND PROPERTY
	      ENVIRONMENT MALLOCSTATS=4)

endif()
endif()

#********************************** Random Vector Functions Test Suite **********************
#first need to configure the executable test
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(EXE_NAME dRandomVectorFunctionsTest)
else()
  set(EXE_NAME RandomVectorFunctionsTest)
endif()

include_directories( ${SOURCE_DIRECTORY}/RandomVectorFunctions
                     ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (${EXE_NAME} RandomVectorFunctionsTest.cpp)
target_link_libraries (${EXE_NAME} RandomVector DataLogger gmock_main ${HDF5_LIBRARIES}  ${GPERFTOOLS_LIBRARIES})

#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

		   
#Now add the tests
#First is the Build Test
add_test(NAME Build_RandomVectorFunctionsTest
         COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --config $<CONFIGURATION> --target ${EXE_NAME})
         
#Next is the Run Tests
add_test(NAME Run_RandomVectorFunctions_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
	  --gtest_output=xml:${GPERF_TMP_DIRECTORY}/${EXE_NAME}_results.xml)

if(RUN_VALGRIND)
add_test(NAME Valgrind_RandomVectorFunctions_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND valgrind ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
         --leak-check=full --track-origins=yes)
endif()

#Next is the Memory Test if gperftools were found
if(RUN_MEMCHECK)
if(${GPERFTOOLS_FOUND})
add_test(NAME MemCheck_RandomVectorFunctions_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})
         
set_property(
             TEST
	      MemCheck_RandomVectorFunctions_Test
	      PROPERTY
	      ENVIRONMENT HEAPPROFILE=${GPERF_TMP_DIRECTORY}/heapprof_random_vector_functions_test)
set_property(
             TEST
	      MemCheck_RandomVectorFunctions_Test
	      PROPERTY
	      ENVIRONMENT HEAPCHECK=normal)
set_property(
             TEST
	      MemCheck_RandomVectorFunctions_Test
	      APPEND PROPERTY
	      ENVIRONMENT HEAPCHECK=1)
set_property(
             TEST
	      MemCheck_RandomVectorFunctions_Test
	      APPEND PROPERTY
	      ENVIRONMENT CPUPROFILE=${GPERF_TMP_DIRECTORY}/cpuprof_random_vector_functions_test)
set_property(
             TEST
	      MemCheck_RandomVectorFunctions_Test
	      APPEND PROPERTY
	      ENVIRONMENT MALLOCSTATS=4)

endif()
endif()

#********************************** Power Spectra Test Suite **********************
#first need to configure the executable test
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(EXE_NAME dPowerSpectraTest)
else()
  set(EXE_NAME PowerSpectraTest)
endif()

include_directories( ${SOURCE_DIRECTORY}/Random
                     ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (${EXE_NAME} PowerSpectraTest.cpp)
target_link_libraries (${EXE_NAME} PowerSpectra DataLogger gmock_main ${HDF5_LIBRARIES}  ${GPERFTOOLS_LIBRARIES})

#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

		   
#Now add the tests
#First is the Build Test
add_test(NAME Build_PowerSpectraTest
         COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --config $<CONFIGURATION> --target ${EXE_NAME})
         
#Next is the Run Tests
add_test(NAME Run_PowerSpectra_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
	  --gtest_output=xml:${GPERF_TMP_DIRECTORY}/${EXE_NAME}_results.xml)

if(RUN_VALGRIND)
add_test(NAME Valgrind_PowerSpectra_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND valgrind ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
         --leak-check=full --track-origins=yes)
endif()

#Next is the Memory Test if gperftools were found
if(RUN_MEMCHECK)
if(${GPERFTOOLS_FOUND})
add_test(NAME MemCheck_PowerSpectra_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})

set_property(
             TEST
	      MemCheck_PowerSpectra_Test
	      PROPERTY
	      ENVIRONMENT HEAPPROFILE=${GPERF_TMP_DIRECTORY}/heapprof_power_spectra_test)
set_property(
             TEST
	      MemCheck_PowerSpectra_Test
	      APPEND PROPERTY
	      ENVIRONMENT HEAPCHECK=1)
set_property(
             TEST
	      MemCheck_PowerSpectra_Test
	      APPEND PROPERTY
	      ENVIRONMENT CPUPROFILE=${GPERF_TMP_DIRECTORY}/cpuprof_power_spectra_test)
set_property(
             TEST
	      MemCheck_PowerSpectra_Test
	      APPEND PROPERTY
	      ENVIRONMENT MALLOCSTATS=4)

endif()
endif()


