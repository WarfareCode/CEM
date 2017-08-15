/**
* @file SimManager.h
* @brief Header File for the Simulation Manager class *
* @author Ben Frazier*
* @date 08/14/2017 */

#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include "SimEngine/SimEngine.h"

#include <string>

class SimManager
{
 public:
	SimManager();
	SimManager(std::string inputFileName, std::string outputFileName);
	int Run();

 private:
	//member functions

	//member variables
	SimEngine engine_;
};

#endif
