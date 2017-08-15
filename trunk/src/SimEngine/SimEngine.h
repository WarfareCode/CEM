/**
* @file SimEngine.h
* @brief Header File for the Simulation Engine class *
* @author Ben Frazier*
* @date 08/15/2017 */

#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include "DataLogger/DataLogger_HDF5.h"
#include "InputParser/InputParser_YAML.h"
#include "FDTD_Engine/FDTD_1D.h"
//needed when factory is completed
//#include "FDTDInterface.h"
#include <string>

class SimEngine
{
 public:
	SimEngine();
	SimEngine(std::string inputFileName, std::string outputFileName);
	void Run();

 private:
	//member functions

	//member variables
	//pointer to engine interface 
	//std::unique_ptr<FDTDInterface> fdtd_;
	FDTD_1D fdtd_;

	//the data logger and input parser types are known at compile time
        DataLoggerHDF5 dLogger_;
	InputParserYAML ip_;

	InputStruct input_;
	InputParserError ipError_;

};

#endif
