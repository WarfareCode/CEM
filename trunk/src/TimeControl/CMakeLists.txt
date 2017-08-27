add_library(TimeControl TimeControl.h TimeControl.cpp)
target_link_libraries(TimeControl ${GPERFTOOLS_LIBRARIES})

#add_subdirectory(tests)
