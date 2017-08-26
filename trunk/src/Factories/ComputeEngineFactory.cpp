/**
* @file ComputeEngineFactory.cpp
* @brief Implementation of the Compute Engine Factory class
* @author Ben Frazier
* @date 08/15/2017 */

#include "ComputeEngineFactory.h"

namespace CEM
{
  ComputeEngineFactory::ComputeEngineFactory()
  {
  }

  std::shared_ptr<ComputeEngineInterface> ComputeEngineFactory::createComputationalEngine(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
   {
     std::shared_ptr<ComputeEngineInterface> computeEngine (new FDTD_1D(input, gridDefinition));
     return computeEngine;
   }

}

