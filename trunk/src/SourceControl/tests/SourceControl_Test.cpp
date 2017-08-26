#include "CEMCommon.h"
#include "SourceControl.h"
#include "SourceControlInterface.h"

#include <string>
  using std::string;
#include <iostream>
#include <vector>

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;

#include "MockSourceDefinitionInterface.h"


namespace CEM
{
namespace SourceControl_Test
{
namespace testing
{
  class Source_Test : public Test
    {
    protected:
       Source_Test(){}
       ~Source_Test(){}

      virtual void SetUp()
      {
        sourceDefinition = std::make_shared<MockSourceDefinition>();
	EXPECT_CALL(*sourceDefinition, getSourceAmplitude()).WillRepeatedly(::testing::Return(1200));
	EXPECT_CALL(*sourceDefinition, getSourceDelay()).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*sourceDefinition, getPulseWidth()).WillRepeatedly(::testing::Return(10));
	EXPECT_CALL(*sourceDefinition, getSourceFrequency()).WillRepeatedly(::testing::Return(35e9));

      }
      virtual void TearDown(){}

      void runTestCase(std::shared_ptr<SourceControlInterface> source);

      std::shared_ptr<MockSourceDefinition> sourceDefinition;

    };

  void Source_Test::runTestCase(std::shared_ptr<SourceControlInterface> source)
  {
    int length = 500;
    std::vector<double> testVec;
    testVec.resize(length);
    double tRate = 0.1;
    double time = 0;
    for (int i = 0; i < length; i++)
      {
	time = i*tRate;
	
	testVec[i] = source->getInputSource(time,0.0);
      }
      
  }

  TEST_F(Source_Test, gaussian_pulse_test)
  {
    std::shared_ptr<GaussianPulse> p = std::make_shared<GaussianPulse>(sourceDefinition);
    runTestCase(p);
  }

  
  TEST_F(Source_Test, modulated_gaussian_pulse_test)
  {
    std::shared_ptr<ModulatedGaussianPulse> p = std::make_shared<ModulatedGaussianPulse>(sourceDefinition);
    runTestCase(p);
  }

  TEST_F(Source_Test, square_pulse_test)
  {
    std::shared_ptr<SquarePulse> p = std::make_shared<SquarePulse>(sourceDefinition);
    runTestCase(p);
  }

  TEST_F(Source_Test, modulated_square_pulse_test)
  {
    std::shared_ptr<ModulatedSquarePulse> p = std::make_shared<ModulatedSquarePulse>(sourceDefinition);
    runTestCase(p);
  }

 

} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
