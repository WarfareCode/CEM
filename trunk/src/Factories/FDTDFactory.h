/**
* @file FDTDFactory.h
* @brief Header File for the FDTD Factory class
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef FDTD_FACTORY_H
#define FDTD_FACTORY_H

#include "FDTD_Engine/FDTD_1D.h"
#include "Interfaces/FDTDInterface.h"

namespace FDTD
{
  class FDTDFactory
  {
  public:
    FDTDFactory();

    FDTDInterface* createFDTDEngine();

  };
}

#endif
