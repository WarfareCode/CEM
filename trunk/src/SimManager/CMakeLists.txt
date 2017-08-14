add_library(SimManager SimManager.h SimManager.cpp )

target_link_libraries(SimManager yaml-cpp DataLogger FDTD InputParser  ${GPERFTOOLS_LIBRARIES})
