/**
* @file SimEngine.h
* @brief Header File for the Simulation Engine class 
* @details The SimEngine handles running the simulation
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include "InputDataInterface.h"
#include "SourceControlInterface.h"
#include "ComputeEngineInterface.h"
#include "DataLoggerInterface.h"

#include <string>

namespace CEM
{
  class SimEngine
  {
  public:
    SimEngine(std::shared_ptr<InputDataInterface> input);

    void Update(double time, std::shared_ptr<ComputeEngineInterface> compute, std::shared_ptr<DataLoggerInterface> dlogger, std::shared_ptr<SourceControlInterface> source);
    
  private:
    //member functions
    double timeSinceLastDataLogged_; /*!< Time tracking to handle data recording */
    double dataLogTime_; /*!< Time step to record data */
    double previousTime_; /*!< Last time the primary loop was executed */
    bool logEveryFrame_; /*!< Flag to indicate if every time step is to be logged */
  };
}

#endif
