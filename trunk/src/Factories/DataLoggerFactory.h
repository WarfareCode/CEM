/**
* @file DataLoggerFactory.h
* @brief Header File for the Data Logger Factory class
* @todo Add support for something other than HDF5
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef DATA_LOGGER_FACTORY_H
#define DATA_LOGGER_FACTORY_H

#include "DataLogger_HDF5.h"
#include "DataLoggerInterface.h"

namespace CEM
{
  //class InputDataInterface;
  //class GridControlInterface;
    
  class DataLoggerFactory
  {
  public:
    DataLoggerFactory();

    std::unique_ptr<DataLoggerInterface> createDataLogger(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridControlInterface> gridControl);

  };
}

#endif
