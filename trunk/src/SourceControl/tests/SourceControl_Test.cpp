#include "CEMCommon.h"
#include "SourceControl.h"
#include "SourceControlInterface.h"

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
	tRate = 0.1;
	shift = 5;
	A = 1.0;
	pw = 10;
	delay = 0;
	f = 35e9;
	EXPECT_CALL(*sourceDefinition, getSourceAmplitude()).WillRepeatedly(::testing::Return(A));
	EXPECT_CALL(*sourceDefinition, getSourceDelay()).WillRepeatedly(::testing::Return(delay));
	EXPECT_CALL(*sourceDefinition, getPulseWidth()).WillRepeatedly(::testing::Return(pw));
	EXPECT_CALL(*sourceDefinition, getSourceFrequency()).WillRepeatedly(::testing::Return(f));

      }
      virtual void TearDown(){}

      std::vector<double> runTestCase(std::shared_ptr<SourceControlInterface> source);

      std::shared_ptr<MockSourceDefinition> sourceDefinition;
      double tRate;
      double shift;
      double pw;
      double delay;
      double f;
      double A;
    };

  std::vector<double>  Source_Test::runTestCase(std::shared_ptr<SourceControlInterface> source)
  {
    int length = 500;
    std::vector<double> testVec;
    testVec.resize(length);
    double time = 0;
    for (int i = 0; i < length; i++)
      {
	time = i*tRate;
	testVec[i] = source->getInputSource(time,shift);
      }

    return testVec;
  }

  TEST_F(Source_Test, gaussian_pulse_test)
  {
    std::shared_ptr<GaussianPulse> p = std::make_shared<GaussianPulse>(sourceDefinition);
    std::vector<double> testVec = runTestCase(p);

    double time = 0;
    double g = 0;
    for (int i = 0; i < testVec.size();i++)
      {
	time = i*tRate;

	g = A  *exp(-(time - delay + shift) * (time - delay + shift) / (pw*pw));
	
	EXPECT_THAT(testVec[i],Eq(g));
      }
  }

  
  TEST_F(Source_Test, modulated_gaussian_pulse_test)
  {
    std::shared_ptr<ModulatedGaussianPulse> p = std::make_shared<ModulatedGaussianPulse>(sourceDefinition);
    std::vector<double> testVec = runTestCase(p);

    double time = 0;
    double g = 0;
    for (int i = 0; i < testVec.size();i++)
      {
	time = i*tRate;

	g = A  *exp(-(time - delay + shift) * (time - delay + shift) / (pw*pw));
	EXPECT_THAT(testVec[i],Eq(g*sin(2*M_PI*f*time)));

      }
  }

  TEST_F(Source_Test, square_pulse_test)
  {
    std::shared_ptr<SquarePulse> p = std::make_shared<SquarePulse>(sourceDefinition);
    std::vector<double> testVec = runTestCase(p);

    double time = 0;
    for (int i = 0; i < testVec.size();i++)
      {
	time = i*tRate;

	
	if (time < delay + shift|| time > pw + delay + shift)
	  EXPECT_THAT(testVec[i],Eq(0));
	else
	EXPECT_THAT(testVec[i],Eq(A));
      }
  }

  TEST_F(Source_Test, modulated_square_pulse_test)
  {
    std::shared_ptr<ModulatedSquarePulse> p = std::make_shared<ModulatedSquarePulse>(sourceDefinition);
    std::vector<double> testVec = runTestCase(p);

    double time = 0;

    for (int i = 0; i < testVec.size();i++)
      {
	time = i*tRate;
	 
	if (time < delay + shift || time > pw + delay + shift)
	  EXPECT_THAT(testVec[i],Eq(0));
	else
	  EXPECT_THAT(testVec[i],Eq(A*sin(2*M_PI*f*time)));
      }
  }

} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
