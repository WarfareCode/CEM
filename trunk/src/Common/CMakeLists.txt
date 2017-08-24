#Add the HDF5ReaderFunctions
add_library(HDF5Reader HDF5ReaderFunctions.h HDF5ReaderFunctions.cpp )
target_link_libraries(HDF5Reader ${HDF5_LIBRARIES} ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
