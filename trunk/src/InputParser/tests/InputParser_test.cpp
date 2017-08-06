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
    class Input_Test : public Test
    {
    protected:
        Input_Test(){}
        ~Input_Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}


        InputParserYAML ip;

        static const size_t taskCount = 3;
        static const string tasks[taskCount];
    };

    const string Input_Test::tasks[taskCount] = {"write code",
                                                 "compile",
                                                 "test"};


    TEST_F(Input_Test, constructor_createsEmptyList)
    {
    
    char buffer[256];
if (NULL == getcwd(buffer, sizeof(buffer))) {
    perror("can't get current dir");
    
}
    std::cout<<buffer<<std::endl;
    	std::string fileName = "Input_Data/test.yaml";
        ip.GetInput("TestToken",fileName);
        
        //EXPECT_THAT(list.size(), Eq(size_t(0)));
    }

} // namespace testing
} // namespace InputParser_Test