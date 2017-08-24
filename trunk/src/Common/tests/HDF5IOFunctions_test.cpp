#include "HDF5IOFunctions.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;


namespace CEM
{
namespace HDF5IOFunction_Test
{
namespace testing
{
  class HDF5IO_Test : public Test
    {
    protected:
       HDF5IO_Test(){}
       ~HDF5IO_Test(){}

      virtual void SetUp()
      {
	
      }
      virtual void TearDown(){}


    };

  TEST_F(HDF5IO_Test, write_read_test_file)
  {
    std::string testFileName = "tempOut.h5";
    std::string dataSet = "test";

    std::vector<double>data_out = {1,2,3,4,5,6,7,8,9,10};
    HDF5IO::WriteVectorToFile(data_out,testFileName,dataSet);
    std::vector<double>data_in =  HDF5IO::ReadVectorFromFile(testFileName,"/" + dataSet);

    EXPECT_THAT(data_in.size(), Eq(data_out.size()));

    for (int i = 0; i < data_out.size();i++)
      {
	EXPECT_THAT(data_in[i], Eq(data_out[i]));
      }
  }


  TEST_F(HDF5IO_Test, read_test_dielectric_file)
  {
     char cwd[1024];
     getcwd(cwd, sizeof(cwd));
     std::cout<<"Current Directory: " << cwd << std::endl;
      

     std::string testFileName = "../../Input_Data/dielectric1.h5";
     std::vector<double> er = HDF5IO::ReadVectorFromFile(testFileName,"/EpsR");
     
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
