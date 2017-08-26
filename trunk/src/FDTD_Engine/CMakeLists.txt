add_library(FDTD FDTD_1D.h FDTD_1D.cpp)
target_link_libraries(FDTD CEMCommon ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
