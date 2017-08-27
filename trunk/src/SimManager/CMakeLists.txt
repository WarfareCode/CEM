add_library(SimManager SimManager.h SimManager.cpp )

target_link_libraries(SimManager SimEngine CEMFactories InputParser TimeControl yaml-cpp ${GPERFTOOLS_LIBRARIES})
