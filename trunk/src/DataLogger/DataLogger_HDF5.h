#ifndef DATALOGGER_HDF5_H
#define DATALOGGER_HDF5_H

#include <iostream>
#include <vector>
#include <array>
#include "AbsDataLogger.h"
#include "H5Cpp.h"
using namespace H5;

class DataLoggerHDF5: public AbsDataLogger
{
	public:
	DataLoggerHDF5();
	virtual void WriteDataArray(std::vector<double>data);
	virtual void WriteDataArray(double *data, int s);
	virtual void CreateFile(std::string fileName);
	
	private:
	DataSet dataset_;

};

#endif