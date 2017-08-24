#include "HDF5ReaderFunctions.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;


namespace CEM
{
namespace HDF5ReaderFunction_Test
{
namespace testing
{
  class HDF5Reader_Test : public Test
    {
    protected:
       HDF5Reader_Test(){}
       ~HDF5Reader_Test(){}

      virtual void SetUp()
      {
	
      }
      virtual void TearDown(){}


    };


  TEST_F(HDF5Reader_Test, read_test_dielectric_file)
  {
     char cwd[1024];
     getcwd(cwd, sizeof(cwd));
     std::cout<<"Current Directory: " << cwd << std::endl;
      

     std::string testFileName = "../../Input_Data/dielectric1.h5";
     std::vector<double> er = HDF5Reader::ReadVectorFromFile(testFileName,"/EpsR");
     
     for (int i = 0; i < 100; i++)
      {
	EXPECT_THAT(er[i], Eq(1));
      }
     for (int i = 100; i < 200; i++)
      {
	EXPECT_THAT(er[i], Eq(9));
      }
  }

} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
