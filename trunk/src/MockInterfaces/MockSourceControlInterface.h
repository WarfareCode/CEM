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
    MOCK_METHOD2(getInputSource, double(double time, double shift));

  };

}
