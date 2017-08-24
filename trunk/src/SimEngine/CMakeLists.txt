add_library(SimEngine SimEngine.h SimEngine.cpp )
target_link_libraries(SimEngine DataLoggerFactory  ComputeEngineFactory ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
