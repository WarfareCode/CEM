/**
* @file FDTDInterface.h
* @brief Virtual class definition for FDTD, defines the interface 
* @details Required Interface functions:
* <pre>
*    InitializeEngine
*    UpdateFields
*    getEField (overloaded to return a single element or the entire std::vector)
*    getHField (overloaded to return a single element or the entire std::vector)
*    getDataSize
*    getImpedance
* </pre>
* @todo Add support for 2D and 3D FDTD computations
* @author Ben Frazier
* @date 08/12/2017 */

#ifndef FDTD_INTERFACE_H
#define FDTD_INTERFACE_H

#include "CEMTypes.h"
#include <vector>

struct InputStruct;

namespace CEM
{
  class FDTDInterface
  {
  public:
    virtual void UpdateFields(double time) = 0;

    virtual std::vector<double> getEField()=0;
    virtual double getEField(int index)=0;
	
    virtual std::vector<double> getHField()=0;
    virtual double getHField(int index)=0;
	
    virtual int getDataSize()=0;
    virtual double getImpedance()=0;
  };
}

#endif
