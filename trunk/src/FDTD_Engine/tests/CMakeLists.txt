if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

#create the FDTD_1D test suite

#first need to configure the executable test
set(EXE_NAME FDTD_1DTest)
include_directories( ${SOURCE_DIRECTORY}/FDTD_Engine
                     ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (${EXE_NAME} FDTD_1D_Test.cpp)
target_link_libraries (${EXE_NAME} FDTD gmock_main)

#make sure to include math defines for Windows Visual Studio
target_compile_definitions(${EXE_NAME} PRIVATE "-D_USE_MATH_DEFINES")

		   
#Now add the tests
#First is the Build Test
add_test(NAME Build_FDTD_1DTest
         COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --config $<CONFIGURATION> --target ${EXE_NAME})
         
#Next is the Run Tests
add_test(NAME Run_FDTD_1D_Test
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})

#Finally we have the Valgrind test (if enabled)
if(RUN_VALGRIND)
	add_test(NAME Valgrind_FDTD_1DTest
	         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	         COMMAND valgrind --leak-check=full
	         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME})
endif()

