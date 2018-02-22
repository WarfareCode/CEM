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

using namespace H5;

  class DataLoggerHDF5: public DataLoggerInterface
  {
  public:
    DataLoggerHDF5();
    DataLoggerHDF5(std::string fileName);
    
    virtual void CreateFile(std::string fileName);

    //WriteData overloaded types
     virtual void WriteData(std::vector<double> data, std::string fileName, std::string datasetName);
     virtual void WriteData(std::vector<double>data, std::string datasetName);
     virtual void WriteData(std::vector<double> data, double time, std::string fileName, std::string datasetName);
     virtual void WriteData(std::vector<double>data, double time, std::string datasetName);
     
     virtual void WriteData(Eigen::MatrixXd data, std::string fileName, std::string datasetName);
     virtual void WriteData(Eigen::MatrixXd data, std::string datasetName);
     virtual void WriteData(Eigen::MatrixXd data, double time, std::string fileName, std::string datasetName );
     virtual void WriteData(Eigen::MatrixXd data, double time, std::string datasetName);  
    
     virtual std::vector<double> ReadVector(std::string fileName, std::string datasetName);
     virtual std::vector<double> ReadVector(std::string datasetName);
     virtual std::vector<double> ReadVector(int index, std::string fileName, std::string datasetName);
     virtual std::vector<double> ReadVector(int index, std::string datasetName);
    
     virtual Eigen::MatrixXd ReadMatrix(std::string fileName, std::string datasetName);
     virtual Eigen::MatrixXd ReadMatrix(std::string datasetName);
     virtual Eigen::MatrixXd ReadMatrix(int index, std::string fileName, std::string datasetName);
     virtual Eigen::MatrixXd ReadMatrix(int index, std::string datasetName);
    
     virtual std::string getFileName() {return fileName_;}  
     virtual bool getInitialized() {return initialized_;}

  private:

    H5File file_;
    std::string fileName_;
    bool initialized_;

  };

#endif
