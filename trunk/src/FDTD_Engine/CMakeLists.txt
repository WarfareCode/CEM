add_library(FDTD AbsFDTD.h FDTD_1D.h FDTD_1D.cpp)

add_subdirectory(tests)
add_test(Test1 tests/FDTD_1DTest)