#include "FDTD_1D.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;


namespace FDTD_1DTest
{
namespace testing
{
    class FDTD_1DTest : public Test
    {
    protected:
        FDTD_1DTest(){}
        ~FDTD_1DTest(){}

        virtual void SetUp(){}
        virtual void TearDown(){}


        FDTD_1D fdtd;

        static const size_t taskCount = 3;
        static const string tasks[taskCount];
    };

    const string FDTD_1DTest::tasks[taskCount] = {"write code",
                                               "compile",
                                               "test"};


    TEST_F(FDTD_1DTest, constructor_createsEmptyList)
    {
    	double *E;
        fdtd.InitializeEngine(10,0,0);
        fdtd.SetEFieldSource(0,10);
       // E = fdtd.getEField();
        
        //EXPECT_THAT(list.size(), Eq(size_t(0)));
    }

} // namespace testing
} // namespace FDTD_1D_Test