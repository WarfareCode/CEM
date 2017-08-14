/**
* @file DataLoggerInterface.h
* @brief Virtual class definition for DataLogger, defines the interface *
* @author Ben Frazier*
* @date 08/12/2017 */

#ifndef DATALOGGER_INTERFACE_H
#define DATALOGGER_INTERFACE_H
#include <iostream>
#include <vector>

class DataLoggerInterface
{
	public:
	virtual void WriteDataArray(std::vector<double>data) = 0;
	virtual void WriteDataArray(double *data, int s) = 0;
	virtual void CreateFile(std::string fileName) = 0;
	
};

#endif
