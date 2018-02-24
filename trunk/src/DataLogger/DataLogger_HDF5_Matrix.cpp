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
   //open the file and get the requested dataset
   H5File file( fileName, H5F_ACC_RDONLY);
   Eigen::MatrixXd data_out = ReadMatrix(0, file,datasetName);;
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
   
   Eigen::MatrixXd data_out = ReadMatrix(0, file_,datasetName);
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
   //open the file and get the requested dataset
   H5File file( fileName, H5F_ACC_RDONLY);
   Eigen::MatrixXd data_out = ReadMatrix(index, file, datasetName);
   return data_out;
 }
 
 //************************************************************************************************************
 /**
 * @brief Read a Matrix from a file at a given index
 * @details This function uses a "chunked" layout
 * @param fileName The fileName to read from
 * @param datasetName The name of the dataset to read
 * @param index The index to read from */
Eigen::MatrixXd DataLoggerHDF5::ReadMatrix(int index, std::string datasetName)
{
   Eigen::MatrixXd data_out = ReadMatrix(index, file_,datasetName);
   return data_out;
 }

 //************************************************************************************************************
 /**
 * @brief Read a Matrix from a file at a given index
 * @details This function uses a "chunked" layout
 * @param fileName The fileName to read from
 * @param datasetName The name of the dataset to read
 * @param index The time index to read from */
Eigen::MatrixXd DataLoggerHDF5::ReadMatrix(int index, H5File file, std::string datasetName)
{
   Eigen::MatrixXd data_out;

  //open the file and get the requested dataset
  //H5File file( fileName, H5F_ACC_RDONLY);
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
 * @brief Write a Matrix to a file
 * @details This function uses a "chunked" layout
 * @param data The matrix to write
 * @param datasetName The name of the dataset to read*/
void DataLoggerHDF5::WriteData(Eigen::MatrixXd data, std::string datasetName)
{
 DataSet dataset;
     //check to see if the requested dataset currently exists
    if (file_.exists(datasetName))
	{
	 //open the dataset
     dataset = file_.openDataSet( datasetName);
     hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double values
	
	 hsize_t dims[2];
	 DataSpace filespace = dataset.getSpace();
	 int rank = filespace.getSimpleExtentDims( dims );
	 
	 hsize_t dsize[2];
     hsize_t offset[2];
     offset[0] = 0;
     offset[1] = currentSize/dims[0];
     dsize[0] = data.cols() + offset[0];
     dsize[1] = data.rows() + offset[1];
   	 
   	 DataSpace mspace( 2, dims);
   	 dataset.extend( dsize );
   	 
   	 //get the file space
    DataSpace fspace = dataset.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, dims, offset);
   
	//write the vector
    dataset.write( &data(0), PredType::NATIVE_DOUBLE, mspace, fspace);

   	}
   	else
   	{
   	 //need to create a new dataset with Unlimited size to allow extending
   	 hsize_t dims[2];
   	 //HDF5 treats data as X and Y rather than rows and columns
   	 dims[0] = data.cols();
   	 dims[1] = data.rows();

     hsize_t      maxdims[2];
     maxdims[0] = H5S_UNLIMITED;
     maxdims[1] = H5S_UNLIMITED;
     hsize_t msize = data.size();
     DataSpace mspace( 2, dims, maxdims);

     DSetCreatPropList cparms;
        
     hsize_t chunk_dims[2];
     chunk_dims[0] = dims[0];
     chunk_dims[1] = dims[1];
     cparms.setChunk( 2, chunk_dims);
        
     int fill_val = 0;
     cparms.setFillValue( PredType::NATIVE_DOUBLE, &fill_val);
       	
     dataset = file_.createDataSet( datasetName, PredType::NATIVE_DOUBLE, mspace,cparms);
	 dataset.write( &data(0), PredType::NATIVE_DOUBLE, mspace);
   	}
   

  }