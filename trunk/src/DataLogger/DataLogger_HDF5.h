#ifndef DATALOGGER_HDF5_H
#define DATALOGGER_HDF5_H

#include <iostream>
#include <vector>
#include <array>
#include "DataLoggerInterface.h"
#include "H5Cpp.h"
#include "InputStruct.h"

using namespace H5;

class DataLoggerHDF5: public DataLoggerInterface
{
	public:
	DataLoggerHDF5();
	virtual void WriteDataHeader(InputStruct input);
	virtual void WriteDataArray(std::vector<double>data);
	virtual void WriteDataArray(double *data, int s);
	virtual void CreateFile(std::string fileName);
	
	private:
	DataSet dataset_;
	H5File H5file_;
	std::string fileName_;

};

#endif
