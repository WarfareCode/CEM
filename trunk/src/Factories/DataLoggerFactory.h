/**
* @file DataLoggerFactory.h
* @brief Header File for the Data Logger Factory class
* @todo Add support for something other than HDF5
* @author Ben Frazier
* @date 08/15/2017 */

#ifndef DATA_LOGGER_FACTORY_H
#define DATA_LOGGER_FACTORY_H

#include "DataLogger/DataLogger_HDF5.h"
#include "Interfaces/DataLoggerInterface.h"

#include "InputStruct.h"
class DataLoggerFactory
{
 public:
  DataLoggerFactory();

  std::unique_ptr<DataLoggerInterface> createDataLogger(const InputStruct &input);

};

#endif
