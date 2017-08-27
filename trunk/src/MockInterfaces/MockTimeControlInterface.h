/**
* @file MockTimeControlInterface.h
* @brief Google Mock Definition for TimeControlInterface
* @author Ben Frazier
* @date 08/27/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "TimeControlInterface.h"


namespace CEM
{
  class MockTimeControl : public TimeControlInterface
  {
  public:
    MOCK_METHOD0(getCurrentTime,double());
    MOCK_METHOD0(getNextTimeStep,double());
    MOCK_METHOD0(timeToLogData,bool());
    MOCK_METHOD0(Update,void());
    MOCK_METHOD0(simComplete,bool());
  };

}
