#include "InputParser.h"
#include "CEMCommon.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
#include <unistd.h>

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
	 char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        std::cout<<"Current Directory: " << cwd << std::endl;
	
	 ip = std::make_shared<InputParser>();
         testFileName = FILEUTILITIES::FindInputFile("CEMInputTestFile.yaml");
       }
      virtual void TearDown(){}

      std::string testFileName;
      std::shared_ptr<InputParser> ip;
      std::shared_ptr<InputDataInterface> input;
    };

    TEST_F(InputParser_Test, constructor_fileNotLoaded)
    {
      
      std::string eString = "";
      try
	{
	  input =  ip->getInputData();
	  
	}
      catch(std::runtime_error &e)
	{
	  eString = e.what();
	}

      EXPECT_THAT(eString,Eq("InputParser::getInputData()....Input File Not Loaded."));
      
    }

    TEST_F(InputParser_Test, readTestFile)
    {
      ip->ReadInputFile(testFileName);

      input = ip->getInputData();

      EXPECT_THAT(input->getInputFileName(),Eq(testFileName));
      EXPECT_THAT(input->getOutputFileName(),Eq("CEMOutput.h5"));
      EXPECT_THAT(input->getComputationType(), Eq("FDTD"));
      EXPECT_THAT(input->getStartTime(),Eq(0.0));
      EXPECT_THAT(input->getStopTime(),Eq( 1.665e-8));
      EXPECT_THAT(input->getAbsorbingBoundaryCondition(),Eq("None"));
      EXPECT_THAT(input->getVectorZLength(),Eq(200));
    }

} // namespace testing
} // namespace InputParser_Test
} // namespace CEM
