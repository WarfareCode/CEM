#include "SimEngine.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

namespace CEM
{
namespace SimEngine_Test
{
namespace testing
{
    class SimEngineTest : public Test
    {
    protected:
       SimEngineTest(){}
       ~SimEngineTest(){}

      virtual void SetUp()
       {
	 ip = std::make_shared<InputParserYAML>();
         testFileName = "Input_Data/test.yaml";
       }
      virtual void TearDown(){}

      std::string testFileName;
      std::shared_ptr<InputParserYAML> ip;
      std::shared_ptr<InputDataInterface> input;
    };

    TEST_F(SimEngineTest, constructor_fileNotLoaded)
    {
      /* std::string eString = "";
      try
	{
	  input =  ip->getInputData();
	}
      catch(std::runtime_error &e)
	{
	  eString = e.what();
	}

	EXPECT_THAT(eString,Eq("InputParserYAML::getInputData()....Input File Not Loaded."));*/
    
    }



} // namespace testing
} // namespace SimEngineTest
} // namespace CEM
