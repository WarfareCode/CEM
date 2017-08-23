#Add the ComputeEngineFactory
add_library(ComputeEngineFactory ComputeEngineFactory.h ComputeEngineFactory.cpp )
target_link_libraries(ComputeEngineFactory FDTD ${GPERFTOOLS_LIBRARIES})

#Add the DataLoggerFactory
add_library(DataLoggerFactory DataLoggerFactory.h DataLoggerFactory.cpp )
target_link_libraries(DataLoggerFactory DataLogger ${GPERFTOOLS_LIBRARIES})

