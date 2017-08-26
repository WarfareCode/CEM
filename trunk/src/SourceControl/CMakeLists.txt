add_library(SourceControl GaussianSource.h GaussianSource.cpp)
target_link_libraries(SourceControl CEMCommon ${GPERFTOOLS_LIBRARIES})

#add_subdirectory(tests)
