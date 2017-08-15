add_library(SimEngine SimEngine.h SimEngine.cpp )

target_link_libraries(SimEngine yaml-cpp DataLogger FDTD InputParser  ${GPERFTOOLS_LIBRARIES})
