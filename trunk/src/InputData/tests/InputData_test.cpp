#include "InputData.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;


namespace CEM
{
namespace InputData_Test
{
namespace testing
{
    class InputData_Test : public Test
    {
    protected:
       InputData_Test(){}
       ~InputData_Test(){}

      virtual void SetUp(){}
      virtual void TearDown(){}

      InputData input;

    };

    TEST_F(InputData_Test, constructor)
    {
      EXPECT_THAT(input.getFileName(),Eq(""));
      EXPECT_THAT(input.getComputationType(),Eq(""));
      EXPECT_THAT(input.getAbsorbingBoundaryCondition(), Eq(""));
      EXPECT_THAT(input.getStopTime(),Eq(0));
      EXPECT_THAT(input.getStartTime(),Eq(0));
      EXPECT_THAT(input.getVectorLength(),Eq(0));
      EXPECT_THAT(input.getSourceIndex(),Eq(0));
    }

      TEST_F(InputData_Test, set_get)
    {

      input.setFileName("test");
      input.setComputationType("FDTD");
      input.setAbsorbingBoundaryCondition("None");
      input.setStartTime(10);
      input.setStopTime(100);
      input.setVectorLength(1000);
      input.setSourceIndex(25);

      EXPECT_THAT(input.getFileName(),Eq("test"));
      EXPECT_THAT(input.getComputationType(),Eq("FDTD"));
      EXPECT_THAT(input.getAbsorbingBoundaryCondition(), Eq("None"));
      EXPECT_THAT(input.getStopTime(),Eq(100));
      EXPECT_THAT(input.getStartTime(),Eq(10));
      EXPECT_THAT(input.getVectorLength(),Eq(1000));
      EXPECT_THAT(input.getSourceIndex(),Eq(25));
    }
   


} // namespace testing
} // namespace InputData_Test
} // namespace CEM
