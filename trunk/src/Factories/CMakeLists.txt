#Add the CEMFactories
add_library(CEMFactories DataLoggerFactory.h DataLoggerFactory.cpp ComputeEngineFactory.h ComputeEngineFactory.cpp SourceControlFactory.h SourceControlFactory.cpp)
target_link_libraries(CEMFactories DataLogger FDTD SourceControl ${GPERFTOOLS_LIBRARIES})


