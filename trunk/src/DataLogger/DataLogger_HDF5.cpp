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
  DataLoggerHDF5::DataLoggerHDF5(std::shared_ptr<InputDataInterface>input)
  {
    fileName_ = input->getOutputFileName();
    chunkSize_ = input->getVectorZLength(); //include room for the time index

    CreateFile();
    WriteDataHeader(input);
  }

       /**
     * @brief Read an Input Array from a file
     * @details This function uses an "unchunked" layout to directly read in an input vector from a file
     * @param fileName The fileName to read from
     * @param datasetName The name of the dataset to read */
     Eigen::MatrixXd  DataLoggerHDF5::ReadMatrixFromFile(std::string fileName, std::string datasetName)
     {
      Eigen::MatrixXd data_out;

      fileName = FILE::FindInputFile(fileName);

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

      data_out.resize(dims[1],dims[0]);
      dataset.read( &data_out(0), PredType::NATIVE_DOUBLE, mspace, filespace );

      delete [] dims;
      
      return data_out;
     }

  

  /**
     * @brief Read an Input Array from a file
     * @details This function uses an "unchunked" layout to directly read in an input vector from a file
     * @param fileName The fileName to read from
     * @param datasetName The name of the dataset to read
     * @param index The time index to read from */
    Eigen::MatrixXd DataLoggerHDF5::ReadMatrixFromFileAtTime(std::string fileName, std::string datasetName, int index)
    {
       Eigen::MatrixXd data_out;

      fileName = FILE::FindInputFile(fileName);

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

      data_out.resize(dims[1],dims[0]);
      dataset.read( &data_out(0), PredType::NATIVE_DOUBLE, mspace, filespace );

      delete [] dims;
      
      return data_out;
    }

    /**
     * @brief Write an Input Array from a file
     * @details This function uses an "unchunked" layout to directly write an input vector from a file
     * @param data The data to write
     * @param fileName The name of the file to write to
     * @param datasetName The name of the dataset to write */
   void  DataLoggerHDF5::WriteMatrixToFile(Eigen::MatrixXd data, std::string fileName, std::string datasetName)
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


    void DataLoggerHDF5::WriteMatrixToFileWithTime(Eigen::MatrixXd data, std::string fileName, std::string datasetName, double time)
    {

    }
  
    void DataLoggerHDF5::WriteMatrixToFileWithTime(Eigen::MatrixXd data, std::string datasetName, double time)
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
     
    //now get the memory size, the new dataset size, and the offset
      hsize_t dims[2];
     dims[0] = data.cols();
     dims[1] = data.rows();
     hsize_t msize = data.size();
    
    hsize_t offset = currentSize; 
    hsize_t dsize = offset + data.size();

    //create the memory space
    DataSpace mspace( 2, &msize);
    
    //extend the data set
    dataset.extend( &dsize );
	
    //get the file space
    DataSpace fspace = dataset.getSpace();
    //select the hyperslab
    fspace.selectHyperslab( H5S_SELECT_SET, &msize, &offset);

    dataset.write( &data(0), PredType::NATIVE_DOUBLE, mspace, fspace);

    //update the time vector
    hsize_t tSize = 1;
    hsize_t toffset = datasetT_.getStorageSize()/8;
    hsize_t dTsize = toffset + tSize;
    DataSpace mTspace( 1, &tSize);
    datasetT_.extend(&dTsize);

    DataSpace tspace = datasetT_.getSpace();
    tspace.selectHyperslab( H5S_SELECT_SET, &tSize, &toffset);
    datasetT_.write(&time, PredType::NATIVE_DOUBLE, mTspace,tspace);
    }
    
    std::vector<double> DataLoggerHDF5::ReadVectorFromFile(std::string fileName, std::string datasetName)
    {
      std::vector<double>data_out;

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
    std::vector<double> DataLoggerHDF5::ReadVectorFromFileAtTime(std::string fileName, std::string datasetName, double time)
    {
      std::vector<double> data_out;

      return data_out;
    }

   /**
   * \brief Write a std::vector to the File
   *
   * This function writes a data array from a std::vector of data and converts
   * the std::vector to an array of pointers first and then calls the overloaded WriteDataArray function
   * @param data The data to write*/
  void DataLoggerHDF5::WriteVectorToFile(std::vector<double>data, std::string fileName, std::string datasetName)
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
 
    
  }
  
    void DataLoggerHDF5::WriteVectorToFileWithTime(std::vector<double> data, std::string fileName, std::string datasetName, double time)
    {
      
    }
  
  
    /**
   * \brief Write a std::vector to the File
   *
   * This function writes a data array from a std::vector of data and converts
   * the std::vector to an array of pointers first and then calls the overloaded WriteDataArray function
   * @param data The data to write
   * @param time The time to append to the data vector
   * @param datasetName The dataset to write ("/EField" or "/HField")*/
  void  DataLoggerHDF5::WriteVectorToFileWithTime(std::vector<double>data, std::string datasetName, double time)
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

    //update the time vector
    hsize_t tSize = 1;
    hsize_t toffset = datasetT_.getStorageSize()/8;
    hsize_t dTsize = toffset + tSize;
    DataSpace mTspace( 1, &tSize);
    datasetT_.extend(&dTsize);

    DataSpace tspace = datasetT_.getSpace();
    tspace.selectHyperslab( H5S_SELECT_SET, &tSize, &toffset);
    datasetT_.write(&time, PredType::NATIVE_DOUBLE, mTspace,tspace);
  }
  
  /**
   * \brief Create an HDF5 file
   *
   * This function creates an HDF5 file with the datasets*/
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

    hsize_t dimsT_ = 1;
    DataSpace tspace(1, &dimsT_, &maxdims);
    DSetCreatPropList tparms;
    tparms.setChunk( 1, &dimsT_);
    tparms.setFillValue( PredType::NATIVE_DOUBLE, &fill_val);
   
    
    datasetT_ = file.createDataSet( "Time", PredType::NATIVE_DOUBLE, tspace, tparms);
  }

  /**
   * \brief write the header of the data file
   *
   * This function writes the input struct to the data file so that the inputs are captured
   * @param input The InputStruct to write out*/
  void DataLoggerHDF5::WriteDataHeader(std::shared_ptr<InputDataInterface> input)
  {

    std::string inputString = InputData2String(input);
    
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
