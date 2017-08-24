/**
* @file HDF5readerFunctions.h
* @brief Reader functions for HDF5
* @author Ben Frazier
* @date 08/23/2017 */

#ifndef HDF5_READER_FUNCTIONS_H
#define HDF5_READER_FUNCTIONS_H
 
#include <vector>
#include <string>
namespace CEM
{
   namespace HDF5Reader
   {
  
     std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName);
   }
}

#endif
