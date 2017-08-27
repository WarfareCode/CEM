add_library(InputParser InputParser.h InputParser.cpp)
target_link_libraries (InputParser yaml-cpp CEMCommon ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
