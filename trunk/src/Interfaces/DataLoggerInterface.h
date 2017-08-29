/**
* @file DataLoggerInterface.h
* @brief Virtual class definition for DataLogger, defines the interface
* @details Required Interface functions:
* <pre>
*    WriteDataArray (overloaded to take either a std::vector or an array)
*    CreateFile
*    WriteDataHeader
* </pre>
* @author Ben Frazier
* @date 08/12/2017 */

#ifndef DATALOGGER_INTERFACE_H
#define DATALOGGER_INTERFACE_H
#include <iostream>
#include <vector>
#include "CEMCommon.h"

namespace CEM
{
  class InputDataInterface;
  
  class DataLoggerInterface
  {
  public:
    virtual void WriteDataArray(std::vector<double>data) = 0;
    virtual void WriteDataArray(double *data, int s) = 0;
    virtual void WriteDataArray(std::vector<double>data, double time, std::string datasetName) = 0;
    virtual void WriteDataArray(Eigen::MatrixXd data, double time, std::string datasetName) = 0;
    
    virtual void WriteVectorToFile(Eigen::VectorXd, std::string fileName, std::string datasetName) = 0;
    virtual Eigen::VectorXd ReadVectorFromFile(std::string fileName, std::string datasetName) = 0;
    
    virtual std::vector<double> ReadDataArray(std::string fileName, std::string datasetName, int timeIndex) = 0;
  };
}

#endif
