/**
* @file DataLogger_HDF5.h
* @brief Header File for the DataLogger_HDF5 class
* @author Ben Frazier
* @todo Add ReadDataInputArray
* @date 08/12/2017 */

#ifndef DATALOGGER_HDF5_H
#define DATALOGGER_HDF5_H

#include <vector>
#include <string>
#include "DataLoggerInterface.h"
#include "H5Cpp.h"
#include "InputDataInterface.h"

using namespace H5;

namespace CEM
{
  class DataLoggerHDF5: public DataLoggerInterface
  {
  public:
    DataLoggerHDF5(InputDataInterface *input);
    
    virtual void WriteDataArray(std::vector<double>data);
    virtual void WriteDataArray(double *data, int s);
    virtual void WriteDataArray(std::vector<double>data, std::string datasetName);
    virtual std::vector<double> ReadDataArray(std::string fileName, std::string datasetName, int timeIndex);

  private:
    void WriteDataHeader(InputDataInterface *input);
    void CreateFile();
	
  private:
    DataSet datasetE_;
    DataSet datasetH_;
    std::string fileName_;
    int chunkSize_;

  };
}

#endif
