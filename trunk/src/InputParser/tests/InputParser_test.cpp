#include "InputParser_YAML.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "InputStruct.h"

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
      InputStruct input;
      InputParserError ipError;

    };

//Constructor - this should result in an empty file name
    TEST_F(InputParser_Test, constructor_emptyFileName)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        std::cout<<"Current Directory: " << cwd << std::endl;
        
        std::string fname = ip.GetFileName();
        
        EXPECT_THAT(fname, Eq(""));   
    }
   
    TEST_F(InputParser_Test, readTestFile)
    {
      ipError = ip.ReadInputFile(testFileName);

      ipError = ip.GetInputStruct(input);

      EXPECT_THAT(input.fileName_,Eq(testFileName));
      EXPECT_THAT(input.computationType_, Eq("FDTD_1D"));
      EXPECT_THAT(input.startTime_,Eq(0));
      EXPECT_THAT(input.stopTime_,Eq(250));
      EXPECT_THAT(input.absorbingBoundaryCondition_,Eq("None"));
      EXPECT_THAT(input.vectorLength_,Eq(200));
      EXPECT_THAT(ipError,Eq(INPUT_PARSER_SUCCESS));
    }

} // namespace testing
} // namespace InputParser_Test
