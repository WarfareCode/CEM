/**
* @file HDF5readerFunctions.cpp
* @brief Reader functions for HDF5
* @author Ben Frazier
* @date 08/23/2017 */

#include "H5Cpp.h"
#include "HDF5ReaderFunctions.h"

using namespace H5;

namespace CEM
{
  namespace HDF5Reader
  {
    /**
     * @brief Read an Input Array from a file
     * @details This function uses an "unchunked" layout to directly read in an input vector from a file
     * @param fileName The fileName to read from
     * @param datasetName The name of the dataset to read */
    std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName)
    {
      std::vector<double> data_out;

     
      //open the file and get the requested dataset
      H5File file( fileName, H5F_ACC_RDONLY);
      DataSet dataset = file.openDataSet( datasetName);

      hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

      //get the dataspace and determine the size and rank
      DataSpace filespace = dataset.getSpace();
      int rank = filespace.getSimpleExtentNdims();
      hsize_t dims;    // dataset dimensions
      rank = filespace.getSimpleExtentDims( &dims );

      DataSpace mspace( rank , &dims);

      data_out.resize(dims);
      dataset.read( &data_out[0], PredType::NATIVE_DOUBLE, mspace, filespace );

      return data_out;
  }
  }
}
