/**
* @file SimEngine.h
* @brief Header File for the Simulation Engine class 
* @details The SimEngine handles running the simulation
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include "DataLogger/DataLogger_HDF5.h"
#include "InputParser/InputParser_YAML.h"
#include "FDTD_Engine/FDTD_1D.h"
#include "Factories/FDTDFactory.h"

//needed when factory is completed
#include "FDTDInterface.h"
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
	FDTD::FDTDInterface* fdtd_ptr_;/*!< FDTD_1D member variable pointer for handling FDTD computations. @todo Add Factory to generate the appropriate computational engine */

	//the data logger and input parser types are known at compile time
        DataLoggerHDF5 dLogger_; /*!< DataLoggerHDF5 member variable for writing output to an HDF5 file */
	InputParserYAML ip_;  /*!< InputParserYAML member variable for reading the input configuration file */

	InputStruct input_;  /*!< InputStruct  used to retrieve the input from the InputParserYAML class. @todo Rework InputParserInterface to keep the InputStruct private to the InputParserYAML class*/
	InputParserError ipError_;  /*!< InputParserError member variable for handling errors from the InputParserYAML class */
	FDTD::FDTDFactory fdtdFactory_;  /*!< Factory to generate the FDTD type */

};

#endif
