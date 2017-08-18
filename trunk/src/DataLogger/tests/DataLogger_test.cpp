#include "DataLogger_HDF5.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "MockInputDataInterface.h"
#include "CEMdefs.h"


namespace CEM
{
namespace DataLogger_Test
{
namespace testing
{
    class DataLogger_Test : public Test
    {
    protected:
       DataLogger_Test(){}
       ~DataLogger_Test(){}

      virtual void SetUp()
      {
       
	input = new MockInputData;
        EXPECT_CALL(*input, getVectorLength()).WillRepeatedly(::testing::Return(15));
	EXPECT_CALL(*input, getOutputFileName()).WillRepeatedly(::testing::Return("CEMTest.h5"));
	
	dl = new DataLoggerHDF5(input);

      }
      virtual void TearDown(){ delete dl; delete input;}

        DataLoggerHDF5* dl;
        MockInputData* input;
        std::string outputFileName;

    };


    TEST_F(DataLogger_Test, write_read_vector)
    {
      std::vector<double> in = {1,5.87,7.993,8,10.2,2.0190,30,50,100,150,-100,-20,-30.5, 3.4, 5.776};
      dl->WriteDataArray(in);
      std::vector<double> out = dl->ReadDataArray(input->getOutputFileName(),"/Ex", 0);

      EXPECT_THAT(in.size(),Eq(out.size()));
      
      for (int counter = 0; counter < in.size();counter++)
	{
	  EXPECT_THAT(in[counter], Eq(out[counter]));
	}
    
    }

} // namespace testing
} // namespace DataLogger_Test
} // namespace CEM
