#get the current directory
THIS_SCRIPT="${BASH_SOURCE[0]}"
while([ -h "${THIS_SCRIPT}" ]) do 
  THIS_SCRIPT="$(readlink "$THIS_SCRIPT")"
done

#define the project root and the tool chains directory
PROJECT_ROOT="$(cd -P "$(dirname "$THIS_SCRIPT")" && pwd)"
TOOLCHAINS_DIR="${PROJECT_ROOT}/CMakeToolChains"

echo "Project Root Directory: ${PROJECT_ROOT}"

#initialize flags
VERBOSE=0
BUILD_MODE=Release
CLEAN_BUILD_DIRECTORY=0
CMAKE_ARGS=

#loop over input to set flags
for i in "$@"
do
case $i in
   -v|--verbose)
   VERBOSE=1
	;;
	
	-X|--use-xcode)
	CMAKE_ARGS="-G Xcode"
	;;
	
	-c|--clean-build-directory)
	CLEAN_BUILD_DIRECTORY=1
	;;
		
	-t|--enable-unit-tests)
	CMAKE_ARGS="-DENABLE_UNIT_TESTS=ON"
	;;
	
    --)
    shift
    while [ "$1" != ""];do
    	CMAKE_ARGS = "{CMAKE_ARGS} $1"
    	shift
    	done
    	;;  	
esac
done

if [ $VERBOSE -eq 1 ]
  then
    echo "verbose mode"
fi

#output the toolchain info
echo "Configuring ${BUILD_MODE} mode"
if [ "$CMAKE_ARGS" != "" ]; then
	echo "Additional CMake Arguments: ${CMAKE_ARGS}"
fi

if [ $CLEAN_BUILD_DIRECTORY -eq 1 ]
	then
		echo "Cleaning the build directory"
	if [ -d ${PROJECT_ROOT}/build ]; then
    	echo "Executing"
		rm -rf ${PROJECT_ROOT}/build
	fi
fi

#create the build directory if it doesn't already exist
if ! [ -d ${PROJECT_ROOT}/build ]; then
	mkdir ${PROJECT_ROOT}/build
fi

echo "cd to ${PROJECT_ROOT}/build"
cd "${PROJECT_ROOT}/build"

#set up the build directory and CMake root directory
BUILD_DIR="${PROJECT_ROOT}/build/gnu/Release"
CMAKE_ROOT_DIR="${PROJECT_ROOT}/trunk"

#run cmake
echo "Executing CMake command: cmake ${CMAKE_ROOT_DIR} ${CMAKE_ARGS}"
cmake ${CMAKE_ROOT_DIR} ${CMAKE_ARGS}