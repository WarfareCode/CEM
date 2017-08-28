#include "FDTD_1D.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "MockInputDataInterface.h"
#include "MockSourceControlInterface.h"
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
	input = std::make_shared<MockInputData>();
	source = std::make_shared<MockSourceControl>();
	EXPECT_CALL(*input, getVectorZLength()).WillRepeatedly(::testing::Return(200));
	EXPECT_CALL(*input, getStopTime()).WillRepeatedly(::testing::Return(250));
	EXPECT_CALL(*input, getDielectricSpecification()).WillRepeatedly(::testing::Return("Constant"));
	EXPECT_CALL(*input, getDielectricConstant()).WillRepeatedly(::testing::Return(1));
	
	fdtd = new FDTD_1D(input);
      }
      virtual void TearDown(){ delete fdtd;}


      FDTD_1D* fdtd;
      std::shared_ptr<MockInputData> input;
      std::shared_ptr<MockSourceControl> source;

    };

  TEST_F(FDTD_1DTest, run)
  {
        
   for(int time = input->getStartTime(); time < input->getStopTime(); time++)
       {
         fdtd->UpdateFields(time, source);
       }
  }

} // namespace testing
} // namespace FDTD_1D_Test
} //namespace CEM
