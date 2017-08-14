#ifndef ABS_DATALOGGER_H
#define ABS_DATALOGGER_H
#include <iostream>

class AbsDataLogger
{
	public:
	virtual void WriteDataArray(std::vector<double>data) = 0;
	virtual void WriteDataArray(double *data, int s) = 0;
	virtual void CreateFile(std::string fileName) = 0;
	
};

#endif