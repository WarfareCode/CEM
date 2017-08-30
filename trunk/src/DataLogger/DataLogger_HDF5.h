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
#include "H5Cpp.h"

#include "DataLoggerInterface.h"
#include "InputDataInterface.h"

#include "CEMCommon.h"

using namespace H5;

namespace CEM
{
  class DataLoggerHDF5: public DataLoggerInterface
  {
  public:
    DataLoggerHDF5();

    virtual void InitializeDataLogger(std::shared_ptr<InputDataInterface> input);
    
    virtual Eigen::MatrixXd ReadMatrixFromFile(std::string fileName, std::string datasetName);
    virtual Eigen::MatrixXd ReadMatrixFromFileAtTime(std::string fileName, std::string datasetName, int index);

    virtual void WriteMatrixToFile(Eigen::MatrixXd data, std::string fileName, std::string datasetName);
    virtual void WriteMatrixToFileWithTime(Eigen::MatrixXd data, std::string fileName, std::string datasetName, double time);
    virtual void WriteMatrixToFileWithTime(Eigen::MatrixXd data, std::string datasetName, double time);
    
    virtual std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName);
    virtual std::vector<double> ReadVectorFromFileAtTime(std::string fileName, std::string datasetName, double time);

    virtual void WriteVectorToFile(std::vector<double> data, std::string fileName, std::string datasetName);
    virtual void WriteVectorToFileWithTime(std::vector<double> data, std::string fileName, std::string datasetName, double time);
    virtual void WriteVectorToFileWithTime(std::vector<double> data, std::string datasetName, double time);
     

  private:
    void WriteDataHeader(std::shared_ptr<InputDataInterface> input);
    void CreateFile(std::shared_ptr<InputDataInterface> input);
	
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
