/**
* @file ComputeEngineInterface.h
* @brief Virtual class definition for Computational Engines, defines the interface 
* @details Required Interface functions:
* @author Ben Frazier
* @date 08/12/2017 */

#ifndef COMPUTE_ENGINE_INTERFACE_H
#define COMPUTE_ENGINE_INTERFACE_H

#include <vector>
#include "CEMCommon.h"

struct InputStruct;

namespace CEM
{
  class SourceControlInterface;
  
  class ComputeEngineInterface
  {
  public:
    virtual void UpdateFields(double time, std::shared_ptr<SourceControlInterface> source) = 0;
    virtual double getEField(int index)=0;
    virtual double getHField(int index)=0;

    virtual Eigen::MatrixXd getEField()=0;
    virtual Eigen::MatrixXd getHField()=0;
	
  };
}

#endif
