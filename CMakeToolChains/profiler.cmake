#Profiler configuration file
message("Adding profiler build options")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -p -g"
    CACHE INTERNAL "" FORCE)
    
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -p -g"
    CACHE INTERNAL "" FORCE)
    
set(CMAKE_FORTRAN_FLAGS "${CMAKE_C_FLAGS} -p -g"
    CACHE INTERNAL "" FORCE)
    
message("CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
message("CMAKE_FORTRAN_FLAGS: " ${CMAKE_FORTRAN_FLAGS})