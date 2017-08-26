add_library(GridControl GridControl.h GridControl.cpp)
target_link_libraries(GridControl CEMCommon ${GPERFTOOLS_LIBRARIES})

#add_subdirectory(tests)
