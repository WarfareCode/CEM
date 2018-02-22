#add the Common library
add_library(CEMCommon FileUtilityFunctions.h FileUtilityFunctions.cpp)
target_link_libraries(CEMCommon ${GPERFTOOLS_LIBRARIES} Eigen3::Eigen)


add_subdirectory(tests)
