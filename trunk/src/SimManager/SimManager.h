/**
* @file SimManager.h
* @brief Header File for the Simulation Manager class *
* @author Ben Frazier*
* @date 08/14/2017 */

#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include "DataLogger/DataLogger_HDF5.h"
#include "InputParser/InputParser_YAML.h"
#include "FDTD_Engine/FDTD_1D.h"
//needed when factory is completed
//#include "FDTDInterface.h"
#include <string>

class SimManager
{
 public:
	SimManager();
	SimManager(std::string inputFileName, std::string outputFileName);
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
