add_library(FDTD FDTD_1D.h FDTD_1D.cpp)
target_link_libraries(FDTD HDF5IO ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
