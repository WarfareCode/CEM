add_library(FDTD AbsFDTD.h FDTD_1D.h FDTD_1D.cpp)

add_subdirectory(tests)
add_test(TestFDTD tests/FDTD_1DTest)