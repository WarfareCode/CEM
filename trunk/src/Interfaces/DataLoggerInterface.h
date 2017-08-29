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
    virtual Eigen::MatrixXd ReadMatrixFromFile(std::string fileName, std::string datasetName)=0;
    virtual Eigen::MatrixXd ReadMatrixFromFileAtTime(std::string fileName, std::string datasetName, int index)=0;

    virtual void WriteMatrixToFile(Eigen::MatrixXd data, std::string fileName, std::string datasetName)=0;
    virtual void WriteMatrixToFileWithTime(Eigen::MatrixXd data, std::string fileName, std::string datasetName, double time)=0;
    virtual void WriteMatrixToFileWithTime(Eigen::MatrixXd data, std::string datasetName, double time)=0;
    
    virtual std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName)=0;
    virtual std::vector<double> ReadVectorFromFileAtTime(std::string fileName, std::string datasetName, double time)=0;

    virtual void WriteVectorToFile(std::vector<double> data, std::string fileName, std::string datasetName)=0;
    virtual void WriteVectorToFileWithTime(std::vector<double> data, std::string fileName, std::string datasetName, double time)=0;
    virtual void WriteVectorToFileWithTime(std::vector<double> data, std::string datasetName, double time)=0;
  };
}

#endif
