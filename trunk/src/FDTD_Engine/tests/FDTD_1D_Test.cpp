#include "FDTD_1D.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "MockInputDataInterface.h"
#include "CEMdefs.h"

namespace CEM
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
       
	input = new MockInputData;
	EXPECT_CALL(*input, getVectorLength()).WillRepeatedly(::testing::Return(200));
	EXPECT_CALL(*input, getStopTime()).WillRepeatedly(::testing::Return(250));
	
	fdtd = new FDTD_1D(input);
      }
      virtual void TearDown(){ delete fdtd; delete input;}


        FDTD_1D* fdtd;
        MockInputData* input;

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
        
   for(int time = input->getStartTime(); time < input->getStopTime(); time++)
       {
         fdtd->UpdateFields(time);
       }
  }

} // namespace testing
} // namespace FDTD_1D_Test
} //namespace CEM
