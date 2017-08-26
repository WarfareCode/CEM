/**
* @file HDF5IOFunctions.cpp
* @brief IO functions for HDF5
* @author Ben Frazier
* @date 08/23/2017 */

#include "H5Cpp.h"
#include "HDF5IOFunctions.h"
#include "FileUtilityFunctions.h"

using namespace H5;

namespace CEM
{
  namespace HDF5IO
  {
    /**
     * @brief Read an Input Array from a file
     * @details This function uses an "unchunked" layout to directly read in an input vector from a file
     * @param fileName The fileName to read from
     * @param datasetName The name of the dataset to read */
    std::vector<double> ReadVectorFromFile(std::string fileName, std::string datasetName)
    {
      std::vector<double> data_out;

      fileName = FILE::FindInputFile(fileName);

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

      /**
   * @brief Write an Output Array to a file
   * @details This function uses an "unchunked" layout to directly write an output vector to a file
   * @param data The data to be written
   * @param fileName The fileName to be written to
   * @param datasetName The name of the dataset to be written */
   void WriteVectorToFile(std::vector<double> data, std::string fileName, std::string datasetName)
   {
     //create the file
     H5File file( fileName, H5F_ACC_TRUNC );
     hsize_t msize = data.size();
     DataSpace mspace(1, &msize );
 
     DataSet dataset = file.createDataSet( datasetName, PredType::NATIVE_DOUBLE, mspace);
     dataset.write(&data[0], PredType::NATIVE_DOUBLE,mspace);  
    
   }    
  }//end namespace HDF5I0
} //end namespace CEM
