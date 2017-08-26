add_library(SimManager SimManager.h SimManager.cpp )

target_link_libraries(SimManager SimEngine CEMFactories InputParser yaml-cpp ${GPERFTOOLS_LIBRARIES})
