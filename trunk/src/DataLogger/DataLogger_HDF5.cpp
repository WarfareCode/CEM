/**
* @file DataLogger_HDF5.cpp
* @brief Implementation of the DataLogger_HDF5 class
* @author Ben Frazier
* @date 08/12/2017 */

#include "DataLogger_HDF5.h"

namespace CEM
{
  /**
   * \brief Standard Constructor
   *
   */
  DataLoggerHDF5::DataLoggerHDF5(InputDataInterface *input)
  {
    fileName_ = input->getOutputFileName();
    chunkSize_ = input->getVectorLength() + 1; //include room for the time index

    CreateFile();
    WriteDataHeader(input);
  }

  /**
   * \brief Write a std::vector to the File
   *
   * This function writes a data array from a std::vector of data and converts
   * the std::vector to an array of pointers first and then calls the overloaded WriteDataArray function
   * @param data The data to write*/
  void DataLoggerHDF5::WriteDataArray(std::vector<double>data)
  {

    hsize_t currentSize = datasetE_.getStorageSize()/8; //Assume 64-bit double values
    //now get the memory size, the new dataset size, and the offset
    hsize_t msize = data.size();
    hsize_t offset = currentSize; 
    hsize_t dsize = offset + data.size();

    //create the memory space
    DataSpace mspace( 1, &msize);
    
    //extend the data set
    datasetE_.extend( &dsize );
	
    //get the file space
    DataSpace fspace = datasetE_.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, &msize, &offset);
    
    datasetE_.write( &data[0], PredType::NATIVE_DOUBLE, mspace, fspace);
    
    //Old way by converting to an array of pointers - keep if needed for 2D
    //the data array is an N x 1 vector of doubles
    //get the size and copy over to a temporary pointer array
    /* int s = data.size();
    double *tempData = new double[s];
    
    for(int i = 0; i < s; i++)
      {
        tempData[i] = data[i];
      }

      WriteDataArray(tempData,s);

    delete[] tempData;*/
    
  }

    /**
   * \brief Write a std::vector to the File
   *
   * This function writes a data array from a std::vector of data and converts
   * the std::vector to an array of pointers first and then calls the overloaded WriteDataArray function
   * @param data The data to write
   * @param time The time to append to the data vector
   * @param datasetName The dataset to write ("/EField" or "/HField")*/
  void  DataLoggerHDF5::WriteDataArray(std::vector<double>data, double time, std::string datasetName)
  {
    DataSet dataset;
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

    //add the time to the data
     data.push_back(time);
     
    //now get the memory size, the new dataset size, and the offset
    hsize_t msize = data.size();
    hsize_t offset = currentSize; 
    hsize_t dsize = offset + data.size();

    //create the memory space
    DataSpace mspace( 1, &msize);
    
    //extend the data set
    dataset.extend( &dsize );
	
    //get the file space
    DataSpace fspace = dataset.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, &msize, &offset);

    dataset.write( &data[0], PredType::NATIVE_DOUBLE, mspace, fspace);
  }

  /**
   * \brief Write an array to the File
   *
   * This function writes a data array from an array of pointers
   * @param data The data to write
   * @param s The size of the data to write*/
  void DataLoggerHDF5::WriteDataArray(double *data, int s)
  {

    hsize_t currentSize = datasetE_.getStorageSize()/8; //Assume 64-bit double values
    //now get the memory size, the new dataset size, and the offset
    hsize_t msize = s;
    hsize_t offset = currentSize; 
    hsize_t dsize = offset + s; 

    //create the memory space
    DataSpace mspace( 1, &msize);
    
    //extend the data set
    datasetE_.extend( &dsize );
	
    //get the file space
    DataSpace fspace = datasetE_.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, &msize, &offset);
    
    datasetE_.write( data, PredType::NATIVE_DOUBLE, mspace, fspace);
  }

  /**
   * \brief Create an HDF5 file
   *
   * This function creates an HDF5 file with the datasets
   * @param filename The name of the file to create*/
  void DataLoggerHDF5::CreateFile()
  {
   
    hsize_t      dims = chunkSize_;  // dataset dimensions at creation
    hsize_t      maxdims = H5S_UNLIMITED;
    DataSpace mspace( 1, &dims, &maxdims);
   
    H5File file( fileName_, H5F_ACC_TRUNC );
    DSetCreatPropList cparms;
        
    hsize_t      chunk_dims = chunkSize_;
    cparms.setChunk( 1, &chunk_dims);
        
    int fill_val = 0;
    cparms.setFillValue( PredType::NATIVE_DOUBLE, &fill_val);

    datasetE_ = file.createDataSet( "EField", PredType::NATIVE_DOUBLE, mspace, cparms);
    datasetH_ = file.createDataSet( "HField", PredType::NATIVE_DOUBLE, mspace, cparms);
  }

  /**
   * \brief write the header of the data file
   *
   * This function writes the input struct to the data file so that the inputs are captured
   * @param input The InputStruct to write out*/
  void DataLoggerHDF5::WriteDataHeader(InputDataInterface * input)
  {

    std::string inputString = InputData2String(input);

    std::cout<<"inputString: " << inputString << std::endl;
    
    H5File file( fileName_, H5F_ACC_RDWR);

    hsize_t msize = inputString.length();
    DataSpace space (1,&msize);

    // write required size char array
    hid_t strtype = H5Tcopy (H5T_C_S1);
    H5Tset_size (strtype, H5T_VARIABLE);
 
    DataSet headerDataSet = file.createDataSet( "Header", PredType::NATIVE_CHAR, space);
    headerDataSet.write( inputString.c_str(),PredType::NATIVE_CHAR, space);
  
  }

    /**
   * \brief Read a Data array from a file
   *
   * @param fileName The fileName to read from
   * @param datasetName The name of the dataset to read
   * @param timeIndex the offset in time to read from */
  std::vector<double>  DataLoggerHDF5::ReadDataArray(std::string fileName, std::string datasetName, int timeIndex)
  {
    //open the file and get the requested dataset
    H5File file( fileName, H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet( datasetName);

    hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

    //get the dataspace and determine the size and rank
    DataSpace filespace = dataset.getSpace();
    int rank = filespace.getSimpleExtentNdims();
    hsize_t dims;    // dataset dimensions
    rank = filespace.getSimpleExtentDims( &dims );

    //get the dataset properties to look at the chunk size
    DSetCreatPropList cparms = dataset.getCreatePlist();

    //get the chunk size to determine how big the array is
    hsize_t cd;
    int rc;
    rc = cparms.getChunk( 1, &cd);
     
    //get the memory space to read in
    DataSpace mspace( rc, &cd );
    //determine the offset into the file  
    hsize_t offset = timeIndex*cd;
    
    //make sure the offset is within the file, otherwise throw and exception
    if (offset <= currentSize - cd)
      {
	//get the hyperslab to read
	filespace.selectHyperslab( H5S_SELECT_SET, &cd, &offset );
      
	std::vector<double>data_out;
	data_out.resize(cd);
	dataset.read( &data_out[0], PredType::NATIVE_DOUBLE, mspace, filespace );

	return data_out;
      }
    else
      throw std::runtime_error("DataLoggerHDF5::ReadDataArray ... Attempting to read beyond the max size of the file");
  }

   /**
   * @brief Read an Input Array from a file
   * @details This function uses an "unchunked" layout to directly read in an input vector from a file
   * @param fileName The fileName to read from
   * @param datasetName The name of the dataset to read */
  std::vector<double> DataLoggerHDF5::ReadInputDataArray(std::string fileName, std::string datasetName)
  {
    std::vector<double> data_out;

    //open the file and get the requested dataset
    H5File file( fileName, H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet( datasetName);

    hsize_t currentSize = dataset.getStorageSize()/8; //Assume 64-bit double value

    //get the dataspace and determine the size and rank
    DataSpace filespace = dataset.getSpace();
    int rank = filespace.getSimpleExtentNdims();
    std::cout<<"Rank: " << rank << std::endl;
    hsize_t dims;    // dataset dimensions
    rank = filespace.getSimpleExtentDims( &dims );

    DataSpace mspace( rank , &dims);

    data_out.resize(dims);
    dataset.read( &data_out[0], PredType::NATIVE_DOUBLE, mspace, filespace );

    return data_out;
  }

}//end namespace CEM
