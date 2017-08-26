#add the Common library
add_library(CEMCommon HDF5IOFunctions.h HDF5IOFunctions.cpp FileUtilityFunctions.h FileUtilityFunctions.cpp)
target_link_libraries(CEMCommon ${HDF5_LIBRARIES} ${GPERFTOOLS_LIBRARIES})


add_subdirectory(tests)
