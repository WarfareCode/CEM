if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

include_directories( ${SOURCE_DIRECTORY}/FDTD_Engine
                     ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (FDTD_1DTest FDTD_1D_Test.cpp)
target_link_libraries (FDTD_1DTest FDTD gmock_main)

#copy binary to bin directory
add_custom_command(TARGET FDTD_1DTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:FDTD_1DTest> ${BINARY_TEST_DIRECTORY})
