/**
* @file MockSourceControlInterface.h
* @brief Google Mock Definition for SourceControlInterface
* @author Ben Frazier
* @date 08/25/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "SourceControlInterface.h"


namespace CEM
{
  class MockSourceControl : public SourceControlInterface
  {
  public:
    MOCK_METHOD0(getSourceType, std::string());
    MOCK_METHOD0(getSourceAmplitude, double());
    MOCK_METHOD0(getSourceDelay, double());
    MOCK_METHOD0(getPulseWidth, double());
    MOCK_METHOD0(getSpatialIndex, int());
    MOCK_METHOD0(getSourceControl, std::shared_ptr<SourceControlInterface>());
  };

}

    
    

   
