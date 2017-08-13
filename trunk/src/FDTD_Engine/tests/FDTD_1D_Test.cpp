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

    };

    TEST_F(FDTD_1DTest, constructor)
    {

      int s = fdtd.getDataSize();
      double imp = fdtd.getImpedance();

      EXPECT_THAT(s, Eq(0));
      EXPECT_THAT(imp, Eq(377.0));
    }

  TEST_F(FDTD_1DTest, initialization)
  {
      fdtd.InitializeEngine(10,0,0);
      int s = fdtd.getDataSize();
      EXPECT_THAT(s, Eq(10));

  }

  TEST_F(FDTD_1DTest, setField)
  {
    double E;
    fdtd.InitializeEngine(10,0,0);
    fdtd.SetEFieldSource(0,10);
    /*E = fdtd.getEField(10);
    EXPECT_THAT(E,Eq(0));

    fdtd.SetEFieldSource(117.53,10);
    E = fdtd.getEField(10);
    EXPECT_THAT(E,Eq(117.53));*/
     
  }

  TEST_F(FDTD_1DTest, run)
  {
   int SIZE = 200;
   fdtd.InitializeEngine(SIZE,0,0);
        
    for(int time = 0; time < 250; time++)
       {
         fdtd.UpdateFields(time);
         fdtd.SetEFieldSource(0,time);
       }
  }

} // namespace testing
} // namespace FDTD_1D_Test
