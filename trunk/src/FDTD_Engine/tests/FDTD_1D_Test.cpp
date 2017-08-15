#include "FDTD_1D.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "src/Common/InputStruct.h"

namespace FDTD
{
namespace FDTD_1DTest
{
namespace testing
{
    class FDTD_1DTest : public Test
    {
    protected:
        FDTD_1DTest(){}
        ~FDTD_1DTest(){}

        virtual void SetUp()
      {
	input.fileName_ = "";
        input.computationType_ = "";
	input.startTime_ = 0;
        input.stopTime_ = 250;
        input.absorbingBoundaryCondition_ = "Simple";
        input.vectorLength_ = 200;
      }
        virtual void TearDown(){}


        FDTD_1D fdtd;
        InputStruct input;

    };

    TEST_F(FDTD_1DTest, constructor)
    {

      int s = fdtd.getDataSize();
      double imp = fdtd.getImpedance();

      EXPECT_THAT(s, Eq(0));
      EXPECT_THAT(imp, Eq(377.0));
    }

  TEST_F(FDTD_1DTest, initialization)
  {
      fdtd.InitializeEngine(input);
      int s = fdtd.getDataSize();
      EXPECT_THAT(s, Eq(200));

  }

  TEST_F(FDTD_1DTest, setField)
  {
    double E;
    fdtd.InitializeEngine(input);
    fdtd.SetEFieldSource(0,10);
     
  }

  TEST_F(FDTD_1DTest, run)
  {
   int SIZE = 200;
   fdtd.InitializeEngine(input);
        
   for(int time = input.startTime_; time < input.stopTime_; time++)
       {
         fdtd.UpdateFields(time);
         fdtd.SetEFieldSource(0,time);
       }
  }

} // namespace testing
} // namespace FDTD_1D_Test
} //namespace FDTD
