/**
* @file ComputeEngineInterface.h
* @brief Virtual class definition for Computational Engines, defines the interface 
* @details Required Interface functions:
* <pre>
*    InitializeEngine
*    UpdateFields
*    getEField (overloaded to return a single element or the entire std::vector)
*    getHField (overloaded to return a single element or the entire std::vector)
*    getDataSize
*    getImpedance
* </pre>
* @author Ben Frazier
* @date 08/12/2017 */

#ifndef COMPUTE_ENGINE_INTERFACE_H
#define COMPUTE_ENGINE_INTERFACE_H

#include <vector>

struct InputStruct;

namespace CEM
{
  class SourceControlInterface;
  
  class ComputeEngineInterface
  {
  public:
    virtual void UpdateFields(double time, std::shared_ptr<SourceControlInterface> source) = 0;

    virtual std::vector<double> getEField()=0;
    virtual double getEField(int index)=0;
	
    virtual std::vector<double> getHField()=0;
    virtual double getHField(int index)=0;
	
  };
}

#endif
