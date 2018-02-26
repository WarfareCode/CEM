message("Configuring Random Number Utilities ...")

add_library(PowerSpectra PowerSpectraFunctions.h Elfouhaily.cpp)
target_link_libraries(PowerSpectra ${GPERFTOOLS_LIBRARIES} Eigen3::Eigen fftw3)

add_library(RandomVector RandomVector.h RandomVector.cpp RandomVectorFunctions.cpp)
target_link_libraries(RandomVector PowerSpectra ${GPERFTOOLS_LIBRARIES} Eigen3::Eigen fftw3)


add_subdirectory(tests)

