#include "InputParser_YAML.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

namespace CEM
{
namespace InputParser_Test
{
namespace testing
{
    class InputParser_Test : public Test
    {
    protected:
       InputParser_Test(){}
       ~InputParser_Test(){}

      virtual void SetUp()
       {
         testFileName = "Input_Data/test.yaml";
       }
      virtual void TearDown(){}

      std::string testFileName;
      InputParserYAML ip;
      InputDataInterface * input;
    };

    TEST_F(InputParser_Test, constructor_fileNotLoaded)
    {
      std::string eString = "";
      try
	{
	  input =  ip.getInputData();
	}
      catch(std::runtime_error &e)
	{
	  eString = e.what();
	}

      EXPECT_THAT(eString,Eq("InputParserYAML::getInputData()....Input File Not Loaded."));
    
    }

    TEST_F(InputParser_Test, readTestFile)
    {
      ip.ReadInputFile(testFileName);

      input = ip.getInputData();
      
      EXPECT_THAT(input->getInputFileName(),Eq(testFileName));
      EXPECT_THAT(input->getOutputFileName(),Eq("CEMOutput.h5"));
      EXPECT_THAT(input->getComputationType(), Eq("FDTD_1D"));
      EXPECT_THAT(input->getStartTime(),Eq(0.0));
      EXPECT_THAT(input->getStopTime(),Eq(250.0));
      EXPECT_THAT(input->getAbsorbingBoundaryCondition(),Eq("None"));
      EXPECT_THAT(input->getVectorLength(),Eq(200));
    }

} // namespace testing
} // namespace InputParser_Test
} // namespace CEM
