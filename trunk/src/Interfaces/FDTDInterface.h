/**
* @file FDTDInterface.h
* @brief Virtual class definition for FDTD, defines the interface *
* @author Ben Frazier*
* @date 08/12/2017 */

#ifndef FDTD_INTERFACE_H
#define FDTD_INTERFACE_H

#include "CEMTypes.h"
#include <vector>

struct InputStruct;
class InputParserInterface;

class FDTDInterface
{
	public:
	virtual void InitializeEngine(InputStruct input)=0;
	virtual void UpdateFields(double time) = 0;

	virtual std::vector<double> getEField()=0;

	virtual double getEField(int index)=0;
        virtual std::vector<double> getHField()=0;

	virtual double getHField(int index)=0;
	virtual int getDataSize()=0;
	virtual double getImpedance()=0;
};

#endif
