/**
* @file MockComputeEngineInterface.h
* @brief Google Mock Definition for ComputeEngineInterface
* @author Ben Frazier
* @date 08/23/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "ComputeEngineInterface.h"


namespace CEM
{
  class MockComputeEngine : public ComputeEngineInterface
  {
  public:
    MOCK_METHOD1(UpdateFields, void(double time));
    MOCK_METHOD1(getEField, double(int index));
    MOCK_METHOD1(getHField, double(int index));
    MOCK_METHOD0(getEField, Eigen::VectorXd));
    MOCK_METHOD0(getHField, Eigen::VectorXd));
  };

}
