if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

include_directories( ${SOURCE_DIRECTORY}/InputParser
                     ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (InputParser_Test InputParser_test.cpp)
target_link_libraries (InputParser_Test InputParser yaml-cpp gmock_main)

#copy binary to bin directory
add_custom_command(TARGET InputParser_Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:InputParser_Test> ${BINARY_TEST_DIRECTORY})
