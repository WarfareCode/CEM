#include "DataLogger_HDF5.h"
//
DataLoggerHDF5::DataLoggerHDF5()
{

}

//
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
    
    dataset_.write( tempData, PredType::NATIVE_DOUBLE, mspace, fspace);
    

    delete[] tempData;
    
}

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

//
void DataLoggerHDF5::CreateFile(std::string filename)
{
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