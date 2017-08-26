/**
* @file MockSourceDefinitionInterface.h
* @brief Google Mock Definition for SourceDefinitionInterface
* @author Ben Frazier
* @date 08/25/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "SourceDefinitionInterface.h"


namespace CEM
{
  class MockSourceDefinition : public SourceDefinitionInterface
  {
  public:
    MOCK_METHOD0(getSourceType, std::string());
    MOCK_METHOD0(getSourceAmplitude, double());
    MOCK_METHOD0(getSourceDelay, double());
    MOCK_METHOD0(getPulseWidth, double());
    MOCK_METHOD0(getSpatialIndex, int());
    MOCK_METHOD0(getSourceDefinition, std::shared_ptr<SourceDefinitionInterface>());
  };

}

    
    

   
