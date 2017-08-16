#include "FDTD_1D.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "InputStruct.h"
#include "CEMdefs.h"

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

	fdtd = new FDTD_1D(input);
      }
      virtual void TearDown(){ delete fdtd;}


        FDTD_1D* fdtd;
        InputStruct input;

    };

    TEST_F(FDTD_1DTest, constructor_initialization)
    {

      int s = fdtd->getDataSize();
      double imp = fdtd->getImpedance();

      EXPECT_THAT(s, Eq(200));
      EXPECT_THAT(imp, Eq(CEM::imp0));

    }


  TEST_F(FDTD_1DTest, run)
  {
   int SIZE = 200;
        
   for(int time = input.startTime_; time < input.stopTime_; time++)
       {
         fdtd->UpdateFields(time);
       }
  }

} // namespace testing
} // namespace FDTD_1D_Test
} //namespace FDTD
