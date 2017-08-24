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
#include "InputParser/InputParser_YAML.h"

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
    SimEngine *engine_;  /*!< Simulation engine member variable for running the simulation */
    std::shared_ptr<InputParserYAML> ip_;  /*!< InputParserYAML member variable for reading the input configuration file */
    std::shared_ptr<InputDataInterface> input_;  /*!< InputData used to retrieve the input from the InputParserYAML class. */
  };
}

#endif
