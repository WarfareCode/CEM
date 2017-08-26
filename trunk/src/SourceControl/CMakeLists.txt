add_library(SourceControl
            GaussianPulse.h
	    GaussianPulse.cpp
	    ModulatedGaussianPulse.h
	    ModulatedGaussianPulse.cpp
	    SquarePulse.h
	    SquarePulse.cpp
	    ModulatedSquarePulse.h
	    ModulatedSquarePulse.cpp)
	    
target_link_libraries(SourceControl CEMCommon ${GPERFTOOLS_LIBRARIES})

add_subdirectory(tests)
