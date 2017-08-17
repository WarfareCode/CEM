#include "InputParser_YAML.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "InputData.h"

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
      InputData input;
      InputParserError ipError;

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

      TEST_F(InputParser_Test, constructor_tryLoadingMultipleFiles)
    {
	ipError = ip.ReadInputFile(testFileName);
        EXPECT_THAT(ipError,Eq(INPUT_PARSER_SUCCESS));
	
	ipError = ip.ReadInputFile(testFileName);
	EXPECT_THAT(ipError,Eq(INPUT_PARSER_FILE_ALREADY_LOADED));
    }
   
    TEST_F(InputParser_Test, readTestFile)
    {
      ipError = ip.ReadInputFile(testFileName);

      input = ip.getInputData();

      EXPECT_THAT(input.getFileName(),Eq(testFileName));
      EXPECT_THAT(input.getComputationType(), Eq("FDTD_1D"));
      EXPECT_THAT(input.getStartTime(),Eq(0));
      EXPECT_THAT(input.getStopTime(),Eq(250));
      EXPECT_THAT(input.getAbsorbingBoundaryCondition(),Eq("None"));
      EXPECT_THAT(input.getVectorLength(),Eq(200));
      EXPECT_THAT(ipError,Eq(INPUT_PARSER_SUCCESS));
    }

} // namespace testing
} // namespace InputParser_Test
} // namespace CEM
