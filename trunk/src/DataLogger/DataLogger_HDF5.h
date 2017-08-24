/**
* @file DataLogger_HDF5.h
* @brief Header File for the DataLogger_HDF5 class
* @author Ben Frazier
* @todo Clean up reading/writing for both EField and HField vectors
* @todo Add support for 2D and 3D data sets
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
    DataLoggerHDF5(std::shared_ptr<InputDataInterface> input);
    DataLoggerHDF5() = delete;
    
    virtual void WriteDataArray(std::vector<double>data);
    virtual void WriteDataArray(double *data, int s);
    virtual void WriteDataArray(std::vector<double>data, double time, std::string datasetName);
    virtual std::vector<double> ReadDataArray(std::string fileName, std::string datasetName, int timeIndex);
    virtual std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName);
    virtual void WriteVectorToFile(std::vector<double> data, std::string fileName, std::string datasetName);

  private:
    void WriteDataHeader(std::shared_ptr<InputDataInterface> input);
    void CreateFile();
	
  private:
    DataSet datasetE_;
    DataSet datasetH_;
    DataSet datasetT_;
    
    std::string fileName_;
    int chunkSize_;

    bool initialized_;

  };
}

#endif
