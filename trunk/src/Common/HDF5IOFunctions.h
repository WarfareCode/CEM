/**
* @file HDF5IOFunctions.h
* @brief IO functions for HDF5
* @author Ben Frazier
* @date 08/23/2017 */

#ifndef HDF5_IO_FUNCTIONS_H
#define HDF5_IO_FUNCTIONS_H
 
#include <vector>
#include <string>
#include "CEMCommon.h"

namespace CEM
{
   namespace HDF5IO
   {
  
     //std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName);

     Eigen::VectorXd ReadVectorFromFile(std::string fileName, std::string datasetName);

     void WriteVectorToFile(Eigen::VectorXd data, std::string fileName, std::string datasetName);
   }
}

#endif
