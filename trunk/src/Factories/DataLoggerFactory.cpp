/**
* @file DataLoggerFactory.cpp
* @brief Implementation of the DataLogger Factory class
* @author Ben Frazier
* @date 08/16/2017 */


#include "DataLoggerFactory.h"
#include "Interfaces/DataLoggerInterface.h"

DataLoggerFactory::DataLoggerFactory()
{
}

std::unique_ptr<DataLoggerInterface> DataLoggerFactory::createDataLogger(const InputStruct & input)
{
  std::unique_ptr<DataLoggerInterface> dataLogger (new DataLoggerHDF5);
  return dataLogger;
}



