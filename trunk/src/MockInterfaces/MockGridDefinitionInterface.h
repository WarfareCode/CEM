/**
* @file MockGridDefinitionInterface.h
* @brief Google Mock Definition for GridDefinitionInterface
* @author Ben Frazier
* @date 08/18/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "GridDefinitionInterface.h"


namespace CEM
{
  class MockGridDefinition: public GridDefinitionInterface
  {
  public:
  
    MOCK_METHOD0(getGridNumDimensions, int());
    MOCK_METHOD0(getGridZLength, double());
    MOCK_METHOD0(getGridZStep, double());
    MOCK_METHOD0(getVectorZLength, int());
    MOCK_METHOD0(getGridXLength, double());
    MOCK_METHOD0(getGridXStep, double());
    MOCK_METHOD0(getVectorXLength, int());
    MOCK_METHOD0(getGridYLength, double());
    MOCK_METHOD0(getGridYStep, double());
    MOCK_METHOD0(getVectorYLength, int());
    MOCK_METHOD0(getTimeStep, double());
    MOCK_METHOD0(getStopTime, double());
    MOCK_METHOD0(getStartTime, double());
    MOCK_METHOD0(getTimeLength, double());  
    MOCK_METHOD0(getGridSpecificationType,std::string());
    MOCK_METHOD0(getDielectricFileName, std::string());
    MOCK_METHOD0(getDielectricConstant,double());
    MOCK_METHOD0(getDielectricSpecification,std::string());
    MOCK_METHOD0(getDielectricDatasetName,std::string()); 
    MOCK_METHOD0(getGridDefinition, std::shared_ptr<GridDefinitionInterface>());
  };

}




