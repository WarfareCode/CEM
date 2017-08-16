/**
* @file FDTDFactory.h
* @brief Header File for the FDTD Factory class
* @todo Add support for 2D and 3D cases, extend to other computational engines
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef FDTD_FACTORY_H
#define FDTD_FACTORY_H

#include "FDTD_Engine/FDTD_1D.h"
#include "Interfaces/FDTDInterface.h"

#include "InputStruct.h"

namespace FDTD
{
  class FDTDFactory
  {
  public:
    FDTDFactory();

    FDTDInterface* createFDTDEngine();

    std::unique_ptr<FDTDInterface> createComputationalEngine(const InputStruct & input);

  };
}

#endif
