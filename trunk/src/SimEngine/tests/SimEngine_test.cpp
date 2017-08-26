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

       }
      virtual void TearDown(){}

 
    };

    TEST_F(SimEngineTest, constructor_fileNotLoaded)
    {
 
    
    }



} // namespace testing
} // namespace SimEngineTest
} // namespace CEM
