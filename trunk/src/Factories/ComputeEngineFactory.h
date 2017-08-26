/**
* @file ComputeEngineFactory.h
* @brief Header File for the Compute Engine Factory class
* @todo Add support for 2D and 3D FDTD cases, extend to other computational engines
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef COMPUTE_ENGINE_FACTORY_H
#define COMPUTE_ENGINE_FACTORY_H

#include "FDTD_Engine/FDTD_1D.h"
#include "ComputeEngineInterface.h"

namespace CEM
{
  class ComputeEngineFactory
  {
  public:
    ComputeEngineFactory();

    // ComputeEngineInterface* createComputeEngine();

    std::unique_ptr<ComputeEngineInterface> createComputationalEngine(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridControlInterface> gridControl);

  };
}

#endif
