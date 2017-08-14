Description
==========================================================================================
Computational Electromagnetics code

Author: Ben Frazier

Main GIT Repo: https://github.com/shockwavefraz/CEM.git

Getting Started
==========================================================================================
Before trying to build the code, there are some external libraries that should be installed.
These are called out below first for the Required libraries (without which the code will not
build) and Useful libraries (without which the code will still build but some testing features
will not be available)

Required:
	HDF5 - used for data logging and reading in binary input files
	CMake - handles generating the overall build process

Useful:
	gperftools - google performance tools suite, useful for memory and cpu profiling
	Doxygen/graphviz - used to generate documentation

Due to issues with conflicts, the YAML-CPP and GTEST libraries are included as part of the overall
code base.


Building
==========================================================================================
The standard command line build process is called out below
	1. Configure - In the root directory, run the configure.sh script to generate the build files.The options available can be determined by executing "./configure.sh --help"
	2. Build - cd to the build directory and type "make". This will build all the executable programs. Available targets can be determined by typing "make help". The most commonly used targets are "make test", "make doc", and "make pdfdoc".
