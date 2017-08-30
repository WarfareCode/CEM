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
#include "TimeControlInterface.h"

#include <string>

namespace CEM
{
  class SimEngine
  {
  public:
    SimEngine();

    void Update(std::shared_ptr<TimeControlInterface> time, std::shared_ptr<ComputeEngineInterface> compute, std::shared_ptr<DataLoggerInterface> dlogger, std::shared_ptr<SourceControlInterface> source);
    
  private:
    //member functions

  };
}

#endif
