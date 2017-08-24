#Add the HDF5IOFunctions
add_library(HDF5IO HDF5IOFunctions.h HDF5IOFunctions.cpp )
target_link_libraries(HDF5IO ${HDF5_LIBRARIES} ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
