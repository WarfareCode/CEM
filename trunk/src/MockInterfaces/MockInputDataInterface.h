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
    MOCK_METHOD0(getOutputFileName, std::string());
    MOCK_METHOD0(getComputationType, std::string());
    MOCK_METHOD0(getAbsorbingBoundaryCondition, std::string());
    MOCK_METHOD0(getStopTime, double());
    MOCK_METHOD0(getStartTime, double());
    MOCK_METHOD0(getVectorLength, int());
    MOCK_METHOD0(getSourceIndex, int());
    MOCK_METHOD0(getInputData, InputDataInterface *());
  };

}
