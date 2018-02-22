add_library(DataLogger DataLogger_HDF5.h
					   DataLogger_HDF5.cpp
					   DataLogger_HDF5_Matrix.cpp
					   DataLogger_HDF5_Vector.cpp)
					   
target_link_libraries(DataLogger CEMCommon ${HDF5_LIBRARIES} ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
