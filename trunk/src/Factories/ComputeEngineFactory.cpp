/**
* @file ComputeEngineFactory.cpp
* @brief Implementation of the Compute Engine Factory class
* @author Ben Frazier
* @date 08/15/2017 */

#include "ComputeEngineFactory.h"
#include "Interfaces/ComputeEngineInterface.h"

namespace CEM
{
  ComputeEngineFactory::ComputeEngineFactory()
  {
  }

  std::unique_ptr<ComputeEngineInterface> ComputeEngineFactory::createComputationalEngine(std::shared_ptr<InputDataInterface> input)
   {
     std::unique_ptr<ComputeEngineInterface> computeEngine (new FDTD_1D(input));
     return computeEngine;
   }

}

