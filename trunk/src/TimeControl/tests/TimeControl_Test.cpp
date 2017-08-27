#include "CEMCommon.h"
#include "TimeControl.h"
#include "TimeControlInterface.h"

#include <string>
  using std::string;
#include <iostream>
#include <vector>
#include <math.h>

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;

#include "MockInputDataInterface.h"


namespace CEM
{
namespace TimeControl_Test
{
namespace testing
{
  class Time_Test : public Test
    {
    protected:
       Time_Test(){}
       ~Time_Test(){}

      virtual void SetUp()
      {
        input = std::make_shared<MockInputData>();
	tstart = 0;
	tfinal = 10;
	tstep = 0.5;
	nSteps = std::round(tfinal/tstep);

	EXPECT_CALL(*input, getStartTime()).WillRepeatedly(::testing::Return(tstart));
	EXPECT_CALL(*input, getStopTime()).WillRepeatedly(::testing::Return(tfinal));
	EXPECT_CALL(*input, getTimeStep()).WillRepeatedly(::testing::Return(tstep));
	EXPECT_CALL(*input, getOutputDataRate()).WillRepeatedly(::testing::Return(-1));
      }
      virtual void TearDown(){delete tc;}


      std::shared_ptr<MockInputData> input;

      double tstart;
      double tfinal;
      double tstep;
      int nSteps;

      TimeControl * tc;
 
    };


  TEST_F(Time_Test, time_control_basic_test)
  {
    tc = new TimeControl(input);
    double time = tc->getCurrentTime();

    EXPECT_THAT(tc->getCurrentTime(), Eq(tstart));
    EXPECT_THAT(tc->getNextTimeStep(), Eq(tstart + tstep));

    int finish = 100;
    for (int i = 0; i <= finish; i++)
      {
	tc->Update();
        if (tc->simComplete())
	  i = finish;
	
	EXPECT_THAT(tc->getCurrentTime(),Eq(time + tstep));
	EXPECT_THAT(tc->getNextTimeStep(),Eq(time + 2*tstep));
	if (tc->getCurrentTime() < tfinal)
	  EXPECT_THAT(tc->simComplete(),Eq(false));
	else
	  EXPECT_THAT(tc->simComplete(),Eq(true));

	time = tc->getCurrentTime();

      }

  }


} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
