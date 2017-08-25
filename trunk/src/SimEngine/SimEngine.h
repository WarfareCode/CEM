/**
* @file SimEngine.h
* @brief Header File for the Simulation Engine class 
* @details The SimEngine handles running the simulation
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include "InputParser/InputParser_YAML.h"
#include "Factories/ComputeEngineFactory.h"
#include "Factories/DataLoggerFactory.h"

#include <string>

namespace CEM
{
  class SimEngine
  {
  public:
    SimEngine(std::shared_ptr<InputDataInterface> input);
    void Initialize(std::shared_ptr<ComputeEngineInterface> compute, std::shared_ptr<DataLoggerInterface> dlogger);
    
    void Run();

  private:
    //member functions

    //member variables
    std::shared_ptr<ComputeEngineInterface> engine_ptr_;/*!< FDTD member variable pointer for handling FDTD computations.*/
    std::shared_ptr<DataLoggerInterface> dLogger_ptr_; /*!< DataLogger member variable pointer for handling writing out to a file */

    //the input parser type is known at compile time - only YAML is handled
    InputParserYAML ip_;  /*!< InputParserYAML member variable for reading the input configuration file */
    std::shared_ptr<InputDataInterface> input_;  /*!< InputData used to retrieve the input from the InputParserYAML class. */
    ComputeEngineFactory computeFactory_;  /*!< Factory to generate the FDTD type */
    DataLoggerFactory dlFactory_;  /*!< Factory to generate the Data Logger type */

    double timeSinceLastDataLogged_; /*!< Time tracking to handle data recording */
    double dataLogTime_; /*!< Time step to record data */
    double previousTime_; /*!< Last time the primary loop was executed */

    bool initialized_; /*!< Flag to indicate whether or not the engine has been initialized */

  };
}

#endif
