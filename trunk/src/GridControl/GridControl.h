/**
* @file GridControl.h
* @brief Header File for the Grid Control class 
* @author Ben Frazier
* @date 08/26/2017 */

#ifndef GRID_CONTROL_H
#define GRID_CONTROL_H

#include "GridDefinitionInterface.h"
#include "CEMCommon.h"

namespace CEM
{
  class GridControl
  {
  public:
    
    GridControl(std::shared_ptr<GridDefinitionInterface> gridDefinition);


  private:
    //member functions


  };
}

#endif
