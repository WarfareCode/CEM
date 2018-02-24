/**
* @file DataLoggerInterface.h
* @brief Virtual class definition for DataLogger, defines the interface
* @author Ben Frazier
* @date 08/12/2017 */

#ifndef DATALOGGER_INTERFACE_H
#define DATALOGGER_INTERFACE_H
#include <iostream>
#include <vector>
#include <Eigen/Dense>

  
class DataLoggerInterface
  {
  public:
  
  	//CreateFile
    virtual void CreateFile(std::string fileName) = 0;
    
    //WriteData overloaded types
     virtual void WriteData(std::vector<double>data, std::string datasetName) = 0;
     virtual void WriteData(Eigen::MatrixXd data, std::string datasetName)=0;

    //ReadData overloaded types
    virtual std::vector<double> ReadVector(std::string fileName, std::string datasetName)=0;
    virtual std::vector<double> ReadVector(std::string datasetName)=0;
    virtual std::vector<double> ReadVector(int index, std::string fileName, std::string datasetName)=0;
    virtual std::vector<double> ReadVector(int index, std::string datasetName)=0;
    
    virtual Eigen::MatrixXd ReadMatrix(std::string fileName, std::string datasetName)=0;
    virtual Eigen::MatrixXd ReadMatrix(std::string datasetName)=0;
    virtual Eigen::MatrixXd ReadMatrix(int index, std::string fileName, std::string datasetName)=0;
    virtual Eigen::MatrixXd ReadMatrix(int index, std::string datasetName)=0;
    
    //Get functions
    virtual bool getInitialized() = 0;
    virtual std::string getFileName() = 0;    
  };


#endif
