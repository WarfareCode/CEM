/**
* @file DataLogger_HDF5_Matrix.cpp
* @brief Implementation of the Matrix Functions for the DataLogger_HDF5 class
* @author Ben Frazier
* @date 08/12/2017 */

#include "DataLogger_HDF5.h"

  //************************************************************************************************************
  /**
  * @brief Read an Eigen::Matrix from a file
  * @details This function uses an "unchunked" layout to directly read in an input vector from a file
  * @param fileName The fileName to read from
  * @param datasetName The name of the dataset to read */
  Eigen::MatrixXd  DataLoggerHDF5::ReadMatrix(std::string fileName, std::string datasetName)
  {
   
    Eigen::MatrixXd data_out;

   //open the file and get the requested dataset
   H5File file( fileName, H5F_ACC_RDONLY);
   DataSet dataset = file.openDataSet( datasetName);

   hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

   //get the dataspace and determine the size and rank
   DataSpace filespace = dataset.getSpace();
   int rank = filespace.getSimpleExtentNdims();

   hsize_t *dims = new hsize_t[rank];
   rank = filespace.getSimpleExtentDims( dims );

   DataSpace mspace( rank , dims);

   if (rank == 1)
    data_out.resize(1,dims[0]);
   else
    data_out.resize(dims[1],dims[0]);

   dataset.read( &data_out(0), PredType::NATIVE_DOUBLE, mspace, filespace );

   delete [] dims;
      
   return data_out;
  }

    //************************************************************************************************************
  /**
  * @brief Read an Eigen::Matrix from a file
  * @details This function uses an "unchunked" layout to directly read in an input vector from a file
  * @param fileName The fileName to read from
  * @param datasetName The name of the dataset to read */
  Eigen::MatrixXd  DataLoggerHDF5::ReadMatrix(std::string datasetName)
  {
   
    Eigen::MatrixXd data_out;

   //open the file and get the requested dataset
  // H5File file( fileName, H5F_ACC_RDONLY);
   DataSet dataset = file_.openDataSet( datasetName);

   hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

   //get the dataspace and determine the size and rank
   DataSpace filespace = dataset.getSpace();
   int rank = filespace.getSimpleExtentNdims();

   hsize_t *dims = new hsize_t[rank];
   rank = filespace.getSimpleExtentDims( dims );

   DataSpace mspace( rank , dims);

   if (rank == 1)
    data_out.resize(1,dims[0]);
   else
    data_out.resize(dims[1],dims[0]);

   dataset.read( &data_out(0), PredType::NATIVE_DOUBLE, mspace, filespace );

   delete [] dims;
      
   return data_out;
  }


 //************************************************************************************************************
 /**
 * @brief Read a Matrix from a file at a given time index
 * @details This function uses a "chunked" layout
 * @param fileName The fileName to read from
 * @param datasetName The name of the dataset to read
 * @param index The time index to read from */
Eigen::MatrixXd DataLoggerHDF5::ReadMatrix(int index, std::string fileName, std::string datasetName)
{
   Eigen::MatrixXd data_out;


  //open the file and get the requested dataset
  H5File file( fileName, H5F_ACC_RDONLY);
  DataSet dataset = file.openDataSet( datasetName);
  
  hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

  //get the dataspace and determine the size and rank
  DataSpace filespace = dataset.getSpace();
  int rank = filespace.getSimpleExtentNdims();

  DSetCreatPropList plist = dataset.getCreatePlist();
  
  //now get the memory size, the new dataset size, and the offset
   hsize_t dims[2];
   rank = filespace.getSimpleExtentDims( dims );
   rank = plist.getChunk(2,dims);

   hsize_t dsize[2];
   hsize_t offset[2];
   offset[0] = 0;
   offset[1] = index * dims[1];

   //create the memory space
   DataSpace mspace(rank, dims);
    
  if (rank == 1)
    data_out.resize(1,dims[0]);
  else
    data_out.resize(dims[1],dims[0]);

   //get the file space
   DataSpace fspace = dataset.getSpace();
   //select the hyperslabs
   fspace.selectHyperslab( H5S_SELECT_SET, dims,  offset);
    
  dataset.read( &data_out(0), PredType::NATIVE_DOUBLE, mspace, fspace );
    
  return data_out;
 }
 
 //************************************************************************************************************
 /**
 * @brief Read a Matrix from a file at a given time index
 * @details This function uses a "chunked" layout
 * @param fileName The fileName to read from
 * @param datasetName The name of the dataset to read
 * @param index The time index to read from */
Eigen::MatrixXd DataLoggerHDF5::ReadMatrix(int index, std::string datasetName)
{
   Eigen::MatrixXd data_out;


  //open the file and get the requested dataset
  //H5File file( fileName, H5F_ACC_RDONLY);
  DataSet dataset = file_.openDataSet( datasetName);
  
  hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

  //get the dataspace and determine the size and rank
  DataSpace filespace = dataset.getSpace();
  int rank = filespace.getSimpleExtentNdims();

  DSetCreatPropList plist = dataset.getCreatePlist();
  
  //now get the memory size, the new dataset size, and the offset
   hsize_t dims[2];
   rank = filespace.getSimpleExtentDims( dims );
   rank = plist.getChunk(2,dims);

   hsize_t dsize[2];
   hsize_t offset[2];
   offset[0] = 0;
   offset[1] = index * dims[1];

   //create the memory space
   DataSpace mspace(rank, dims);
    
  if (rank == 1)
    data_out.resize(1,dims[0]);
  else
    data_out.resize(dims[1],dims[0]);

   //get the file space
   DataSpace fspace = dataset.getSpace();
   //select the hyperslabs
   fspace.selectHyperslab( H5S_SELECT_SET, dims,  offset);
    
  dataset.read( &data_out(0), PredType::NATIVE_DOUBLE, mspace, fspace );
    
  return data_out;
 }


void DataLoggerHDF5::WriteData(Eigen::MatrixXd data, std::string datasetName)
{

}
  //************************************************************************************************************
  /**
  * @brief Write an Eigen::Matrix to a file
  * @details This function uses an "unchunked" layout to directly write a matrix t a file
  * @param data The data to write
  * @param fileName The name of the file to write to
  * @param datasetName The name of the dataset to write */
  void  DataLoggerHDF5::WriteData(Eigen::MatrixXd data, std::string fileName, std::string datasetName)
  {
   //create the file
   H5File file( fileName, H5F_ACC_TRUNC );
   hsize_t dims[2];
   //HDF5 treats data as X and Y rather than rows and columns
   dims[0] = data.cols();
   dims[1] = data.rows();
   hsize_t msize = data.size();
   DataSpace mspace(2, dims);
 
   DataSet dataset = file.createDataSet( datasetName, PredType::NATIVE_DOUBLE, mspace);
   dataset.write(&data(0), PredType::NATIVE_DOUBLE,mspace); 
  }

  //************************************************************************************************************
  /**
  * @brief Write an Eigen::Matrix to a file
  * @details This function uses an "unchunked" layout to directly write a matrix t a file
  * @param data The data to write
  * @param fileName The name of the file to write to
  * @param datasetName The name of the dataset to write */
    void DataLoggerHDF5::WriteData(Eigen::MatrixXd data, double time, std::string fileName, std::string datasetName)
    {

    }

  //************************************************************************************************************
  /**
  * @brief Write an Eigen::Matrix to a file
  * @details This function uses an "unchunked" layout to directly write a matrix t a file
  * @param data The data to write
  * @param fileName The name of the file to write to
  * @param datasetName The name of the dataset to write */
    void DataLoggerHDF5::WriteData(Eigen::MatrixXd data, double time, std::string datasetName)
    {
 /*    DataSet dataset;
    if (datasetName.compare("EField"))
      {
	dataset = datasetE_;
      }
    else if (datasetName.compare("HField"))
      {
        dataset = datasetH_;
      }
    else
      throw std::runtime_error("DataLoggerHDF5::WriteDataArray ... Invalid dataset name requested");
		 
     hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double values

     DataSpace filespace = dataset.getSpace();
     int rank = filespace.getSimpleExtentNdims();
      
    //now get the memory size, the new dataset size, and the offset
     hsize_t dims[2];
     hsize_t offset[2];
     hsize_t dsize[2];

     dims[0] = data.cols();
     dims[1] = data.rows();

     offset[0] = 0;
     offset[1] = std::round(currentSize/dims[0]);
     dsize[0] = offset[0] + data.cols();
     dsize[1] = offset[1] + data.rows();

    //create the memory space
    DataSpace mspace(rank, dims);

    //extend the data set
    dataset.extend( dsize );

    //get the file space
    DataSpace fspace = dataset.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, dims,  offset);
    dataset.write( &data(0), PredType::NATIVE_DOUBLE, mspace, fspace);

    //update the time vector
    hsize_t tSize = 1;
    hsize_t toffset = datasetT_.getStorageSize()/8;
    hsize_t dTsize = toffset + tSize;
    DataSpace mTspace( 1, &tSize);
    datasetT_.extend(&dTsize);

    DataSpace tspace = datasetT_.getSpace();
    tspace.selectHyperslab( H5S_SELECT_SET, &tSize, &toffset);
    datasetT_.write(&time, PredType::NATIVE_DOUBLE, mTspace,tspace);*/
    }



