#include "DataLogger_HDF5.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;

#include "MockInputDataInterface.h"
#include "CEMdefs.h"


namespace CEM
{
namespace DataLogger_Test
{
namespace testing
{
  class DataLogger_Test : public TestWithParam<int>
    {
    protected:
       DataLogger_Test(){}
       ~DataLogger_Test(){}

      virtual void SetUp()
      {
	input = std::make_shared<MockInputData>();
	EXPECT_CALL(*input, getOutputFileName()).WillRepeatedly(::testing::Return("CEMTest.h5"));
	
      }
      virtual void TearDown(){ delete dl;}

      DataLoggerHDF5* dl;
      std::shared_ptr<MockInputData> input;
      std::string outputFileName;

      int size;

    };


    TEST_F(DataLogger_Test, write_read_efield_vector_fixed_size)
    {
      std::string datasetname = "/EField";
      EXPECT_CALL(*input, getVectorZLength()).WillRepeatedly(::testing::Return(15));
      dl = new DataLoggerHDF5(input);
      std::vector<double> in = {1,5.87,7.993,8,10.2,2.0190,30,50,100,150,-100,-20,-30.5, 3.4, 5.776};
      dl->WriteDataArray(in,1,datasetname);
      std::vector<double> out = dl->ReadDataArray(input->getOutputFileName(),datasetname, 0);

      EXPECT_THAT(in.size(),Eq(out.size()));
      
      for (int counter = 0; counter < in.size();counter++)
	{
	  EXPECT_THAT(in[counter], Eq(out[counter]));
	}
    
    }


  TEST_P(DataLogger_Test, write_read_vector_variable_sizes)
  {
     size = GetParam();
     EXPECT_CALL(*input, getVectorZLength()).WillRepeatedly(::testing::Return(size));
      dl = new DataLoggerHDF5(input);

     std::vector<double>(in);
     in.resize(size);
     for (int i = 0; i < size; i++)
       {
	 in[i] = rand();
       }

     dl->WriteDataArray(in, 1, "/EField");

     std::vector<double> out = dl->ReadDataArray(input->getOutputFileName(),"/EField", 0);

      EXPECT_THAT(in.size(),Eq(out.size()));
      
      for (int counter = 0; counter < in.size();counter++)
	{
	  EXPECT_THAT(in[counter], Eq(out[counter]));
	}
  
  }

    TEST_F(DataLogger_Test, read_test_dielectric_file)
  {
     char cwd[1024];
     getcwd(cwd, sizeof(cwd));
     std::cout<<"Current Directory: " << cwd << std::endl;

     EXPECT_CALL(*input, getVectorZLength()).WillRepeatedly(::testing::Return(15));
      
     dl = new DataLoggerHDF5(input);
      std::string testFileName = "../../Input_Data/dielectric1.h5";
     std::vector<double> er = dl->ReadVectorFromFile(testFileName,"/EpsR");
     for (int i = 0; i < 100; i++)
      {
	EXPECT_THAT(er[i], Eq(1));
      }
     for (int i = 100; i < 200; i++)
      {
	EXPECT_THAT(er[i], Eq(9));
      }
  }

  INSTANTIATE_TEST_CASE_P(NewVectorSizes, DataLogger_Test,::testing::Values(5,7,10,30,50,100,250,500));

} // namespace testing
} // namespace DataLogger_Test
} // namespace CEM
