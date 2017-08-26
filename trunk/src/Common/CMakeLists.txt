#Add the HDF5IOFunctions
add_library(HDF5IO HDF5IOFunctions.h HDF5IOFunctions.cpp )
target_link_libraries(HDF5IO ${HDF5_LIBRARIES} ${GPERFTOOLS_LIBRARIES})

add_library(FileUtilities FileUtilityFunctions.h FileUtilityFunctions.cpp)
target_link_libraries(FileUtilities ${GPERFTOOLS_LIBRARIES})

add_library(CEMCommon HDF5IOFunctions.h HDF5IOFunctions.cpp FileUtilityFunctions.h FileUtilityFunctions.cpp)
target_link_libraries(CEMCommon ${HDF5_LIBRARIES} ${GPERFTOOLS_LIBRARIES})


add_subdirectory(tests)
