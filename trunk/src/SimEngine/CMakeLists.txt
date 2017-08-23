add_library(SimEngine SimEngine.h SimEngine.cpp )
target_link_libraries(SimEngine yaml-cpp DataLoggerFactory InputParser  ComputeEngineFactory ${GPERFTOOLS_LIBRARIES})
