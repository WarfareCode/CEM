#include "InputParser_YAML.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;


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
        	testFileName = "test.yaml";
        }
        virtual void TearDown(){}

	   std::string testFileName;
       InputParserYAML ip;

    };

//Constructor - this should result in an empty file name
    TEST_F(InputParser_Test, constructor_emptyFileName)
    {
        std::string fname;
        ip.GetFileName(fname);
        
        EXPECT_THAT(fname, Eq(""));   
    }
   
//Initialize with a test input - verify the file name 
    TEST_F(InputParser_Test, initialize_getFileName)
    {
    	std::string fname;
    	
    	ip.Initialize(testFileName);
    	ip.GetFileName(fname);
    	
    	EXPECT_THAT(fname,Eq(testFileName));
    }
    
    TEST_F(InputParser_Test, readField)
    {
    	ip.Initialize(testFileName);
    	
    	
    }
    

} // namespace testing
} // namespace InputParser_Test