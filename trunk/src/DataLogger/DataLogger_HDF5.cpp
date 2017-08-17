/**
* @file DataLogger_HDF5.cpp
* @brief Implementation of the DataLogger_HDF5 class
* @author Ben Frazier*
* @date 08/12/2017 */

#include "DataLogger_HDF5.h"

namespace CEM
{
  /**
   * \brief Standard Constructor
   *
   */
  DataLoggerHDF5::DataLoggerHDF5()
  {

  }

  /**
   * \brief Write a std::vector to the File
   *
   * This function writes a data array from a std::vector of data and converts
   * the std::vector to an array of pointers first and then calls the overloaded WriteDataArray function
   * @param data The data to write*/
  void DataLoggerHDF5::WriteDataArray(std::vector<double>data)
  {

    hsize_t currentSize = dataset_.getStorageSize()/8; //Assume 64-bit double values
    //now get the memory size, the new dataset size, and the offset
    hsize_t msize = data.size();
    hsize_t offset = currentSize; 
    hsize_t dsize = offset + data.size();

    //create the memory space
    DataSpace mspace( 1, &msize);
    
    //extend the data set
    dataset_.extend( &dsize );
	
    //get the file space
    DataSpace fspace = dataset_.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, &msize, &offset);
    
    dataset_.write( &data[0], PredType::NATIVE_DOUBLE, mspace, fspace);
    
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
   * \brief Write an array to the File
   *
   * This function writes a data array from an array of pointers
   * @param data The data to write
   * @param s The size of the data to write*/
  void DataLoggerHDF5::WriteDataArray(double *data, int s)
  {

    hsize_t currentSize = dataset_.getStorageSize()/8; //Assume 64-bit double values
    //now get the memory size, the new dataset size, and the offset
    hsize_t msize = s;
    hsize_t offset = currentSize; 
    hsize_t dsize = offset + s; 

    //create the memory space
    DataSpace mspace( 1, &msize);
    
    //extend the data set
    dataset_.extend( &dsize );
	
    //get the file space
    DataSpace fspace = dataset_.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, &msize, &offset);
    
    dataset_.write( data, PredType::NATIVE_DOUBLE, mspace, fspace);
  }

  /**
   * \brief Create an HDF5 file
   *
   * This function creates an HDF5 file with the datasets
   * @param filename The name of the file to create*/
  void DataLoggerHDF5::CreateFile(std::string filename)
  {
    fileName_ = filename;
    hsize_t      dims = 200;  // dataset dimensions at creation
    hsize_t      maxdims = H5S_UNLIMITED;
    DataSpace mspace( 1, &dims, &maxdims);
   
    H5File file( filename, H5F_ACC_TRUNC );
    DSetCreatPropList cparms;
        
    hsize_t      chunk_dims = 200;
    cparms.setChunk( 1, &chunk_dims);
        
    int fill_val = 0;
    cparms.setFillValue( PredType::NATIVE_DOUBLE, &fill_val);

    dataset_ = file.createDataSet( "Ex", PredType::NATIVE_DOUBLE, mspace, cparms);
  }

  /**
   * \brief write the header of the data file
   *
   * This function writes the input struct to the data file so that the inputs are captured
   * @param input The InputStruct to write out*/
  void DataLoggerHDF5:: WriteDataHeader(InputDataInterface * input)
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

}//end namespace CEM
