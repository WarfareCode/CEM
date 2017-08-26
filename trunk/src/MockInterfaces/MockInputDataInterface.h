/**
* @file MockInputDataInterface.h
* @brief Google Mock Definition for InputDataInterface
* @author Ben Frazier
* @date 08/18/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "InputDataInterface.h"


namespace CEM
{
  class MockInputData : public InputDataInterface
  {
  public:
    MOCK_METHOD0(getInputFileName, std::string());
    MOCK_METHOD0(getComputationType, std::string());
    MOCK_METHOD0(getNumDimensions, int());
    MOCK_METHOD0(getZLength, double());
    MOCK_METHOD0(getZSamplingDistance, double());
    MOCK_METHOD0(getVectorZLength, int());
    MOCK_METHOD0(getAbsorbingBoundaryCondition, std::string());

    MOCK_METHOD0(getStopTime, double());
    MOCK_METHOD0(getStartTime, double());
    MOCK_METHOD0(getTemporalSamplingRate, double());
    
    MOCK_METHOD0(getDielectricFileName, std::string());
    MOCK_METHOD0(getDielectricConstant,double());
    MOCK_METHOD0(getDielectricSpecification,std::string());
    MOCK_METHOD0(getDielectricDatasetName,std::string());
    
    MOCK_METHOD0(getSourceType, std::string());
    MOCK_METHOD0(getSourceAmplitude, double());
    MOCK_METHOD0(getSourceDelay, double());
    MOCK_METHOD0(getPulseWidth, double());
    MOCK_METHOD0(getSpatialIndex, int());
    MOCK_METHOD0(getOutputFileName, std::string());
    MOCK_METHOD0(getOutputDataRate, double()); 
    MOCK_METHOD0(getInputData, std::shared_ptr<InputDataInterface>());
  };

}

    
    

   
