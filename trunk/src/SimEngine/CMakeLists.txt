add_library(SimEngine SimEngine.h SimEngine.cpp )
target_link_libraries(SimEngine yaml-cpp DataLoggerFactory InputParser  FDTDFactory InputData ${GPERFTOOLS_LIBRARIES})
