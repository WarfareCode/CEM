/**
* @file DataLogger_HDF5.h
* @brief Header File for the DataLogger_HDF5 class
* @author Ben Frazier
* @todo Add ReadDataInputArray
* @date 08/12/2017 */

#ifndef DATALOGGER_HDF5_H
#define DATALOGGER_HDF5_H

#include <vector>
#include <string>
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
