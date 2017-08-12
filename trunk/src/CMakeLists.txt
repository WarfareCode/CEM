#now set the runtime output directory for lower lever executables to the test directory - this should occur before adding additional subdirectories
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_TEST_DIRECTORY})
add_subdirectory(DataLogger)
add_subdirectory(FDTD_Engine)
add_subdirectory(InputParser)