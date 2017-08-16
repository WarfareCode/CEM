#Add the FDTDFactory
add_library(FDTDFactory FDTDFactory.h FDTDFactory.cpp )
target_link_libraries(FDTDFactory FDTD ${GPERFTOOLS_LIBRARIES})

#Add the DataLoggerFactory
add_library(DataLoggerFactory DataLoggerFactory.h DataLoggerFactory.cpp )
target_link_libraries(DataLoggerFactory DataLogger ${GPERFTOOLS_LIBRARIES})

