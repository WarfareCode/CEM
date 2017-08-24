add_library(SimManager SimManager.h SimManager.cpp )

target_link_libraries(SimManager SimEngine InputParser yaml-cpp ${GPERFTOOLS_LIBRARIES})
