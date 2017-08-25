/**
* @file MockGridControlInterface.h
* @brief Google Mock Definition for GridControlInterface
* @author Ben Frazier
* @date 08/18/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "GridControlInterface.h"


namespace CEM
{
  class MockGridControl: public GridControlInterface
  {
  public:
  
    MOCK_METHOD0(getGridNumDimensions, int());
    MOCK_METHOD0(getGridZLength, double());
    MOCK_METHOD0(getGridZSamplingFrequency, double());
    MOCK_METHOD0(getVectorZLength, int());
    MOCK_METHOD0(getGridXLength, double());
    MOCK_METHOD0(getGridXSamplingFrequency, double());
    MOCK_METHOD0(getVectorXLength, int());
    MOCK_METHOD0(getGridYLength, double());
    MOCK_METHOD0(getGridYSamplingFrequency, double());
    MOCK_METHOD0(getVectorYLength, int());
    MOCK_METHOD0(getGridSpecificationType,std::string());
    MOCK_METHOD0(getDielectricFileName, std::string());
    MOCK_METHOD0(getDielectricConstant,double());
    MOCK_METHOD0(getDielectricSpecification,std::string());
    MOCK_METHOD0(getDielectricDatasetName,std::string());
    MOCK_METHOD0(getGridControl, std::shared_ptr<GridControlInterface>());
  };

}




