/**
* @file SimManager.h
* @brief Header File for the Simulation Manager class
* @details The SimManager provides the top most interface to the underlying simulation. It controls the SimEngine and covers exception handling
* @author Ben Frazier
* @date 08/14/2017
**/

#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include "SimEngine/SimEngine.h"

#include <string>

namespace CEM
{
  class SimManager
  {
  public:
    SimManager(std::string inputFileName, std::string outputFileName);
    int Run();

  private:
    //member functions

    //member variables
    SimEngine engine_;  /*!< Simulation engine member variable for running the simulation */
  };
}

#endif
