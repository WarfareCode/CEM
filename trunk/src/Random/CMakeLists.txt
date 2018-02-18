add_library(Random Random.h Random.cpp )
target_link_libraries(Random ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
