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
    //the data array is an N x 1 vector of doubles
    //get the size and copy over to a temporary pointer array
    int s = data.size();
    double *tempData = new double[s];
    
    for(int i = 0; i < s; i++)
      {
        tempData[i] = data[i];
      }

    WriteDataArray(tempData,s);

    delete[] tempData;
    
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
  void DataLoggerHDF5:: WriteDataHeader(InputData & input)
  {
    /*
    H5File file( fileName_, H5F_ACC_RDWR);

    CompType mtype (sizeof (input));

    hsize_t dim[] = {1};
    DataSpace space (1,dim);

    const H5std_string MEMBER1( "Start Time" );
    const H5std_string MEMBER2( "Stop Time" );
    const H5std_string MEMBER3( "Vector Length" );
    const H5std_string MEMBER4( "Source Index" );
    const H5std_string MEMBER5( "File Name" );
    const H5std_string MEMBER6( "Computation Type" );
    const H5std_string MEMBER7( "Absorbing Boundary Condition" );

    // write required size char array
    hid_t strtype = H5Tcopy (H5T_C_S1);
    H5Tset_size (strtype, H5T_VARIABLE);*/

    /* mtype.insertMember( MEMBER1, HOFFSET(InputStruct, startTime_), PredType::NATIVE_DOUBLE);
    mtype.insertMember( MEMBER2, HOFFSET(InputStruct, stopTime_), PredType::NATIVE_DOUBLE);
    mtype.insertMember( MEMBER3, HOFFSET(InputStruct, vectorLength_), PredType::NATIVE_INT);
    mtype.insertMember( MEMBER4, HOFFSET(InputStruct, sourceIndex_), PredType::NATIVE_INT);*/
 
    // DataSet headerDataSet =file.createDataSet("Header",mtype,space);
    //headerDataSet.write(, mtype);

    /*
      std::string fileName_;
      std::string computationType_;
      double startTime_;
      double stopTime_;
      std::string absorbingBoundaryCondition_;
      int vectorLength_;
    */
  
  }

}//end namespace CEM
