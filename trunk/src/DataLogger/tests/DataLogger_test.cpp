#include "DataLogger_HDF5.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;

#include "MockInputDataInterface.h"

#include "CEMCommon.h"


namespace CEM
{
namespace DataLogger_Test
{
namespace testing
{
  class DataLogger_Test : public TestWithParam<std::tr1::tuple<int, int> >
    {
    protected:
       DataLogger_Test(){}
       ~DataLogger_Test(){}

      virtual void SetUp()
      {
	input = std::make_shared<MockInputData>();

	EXPECT_CALL(*input, getOutputFileName()).WillRepeatedly(::testing::Return("CEMTest.h5"));
	EXPECT_CALL(*input, getVectorZLength()).WillRepeatedly(::testing::Return(15));
      dl = new DataLoggerHDF5(input);
	
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
      Eigen::MatrixXd in;
      in.resize(1,15);
      in << 1, 5.87, 7.993, 8, 10.2, 2.0190, 30, 50, 100, 150, -100, -20, -30.5, 3.4, 5.776;
      dl->WriteMatrixToFileWithTime(in,datasetname,1);
      Eigen::MatrixXd out = dl->ReadMatrixFromFile(input->getOutputFileName(),datasetname);

      EXPECT_THAT(in.size(),Eq(out.size()));
      
      for (int counter = 0; counter < in.size();counter++)
	{
	  EXPECT_THAT(in(counter), Eq(out(counter)));
	  }
    
    }

  TEST_P(DataLogger_Test, write_read_vector_variable_sizes)
  {
    int const size = std::tr1::get<0>(GetParam());

    std::vector<double> wVector(size);
    for(int i = 0; i < size; i++)
	wVector[i] = rand();

    dl->WriteVectorToFile(wVector,"testmatrix.h5","vector");
    std::vector<double> rVector = dl->ReadVectorFromFile("testmatrix.h5","vector");

    EXPECT_THAT(wVector.size(), Eq(rVector.size()));
    for(int i = 0; i < size; i++)
    EXPECT_THAT(wVector[i], Eq(rVector[i]));
  
  }

  TEST_P( DataLogger_Test, write_read_matrix_variable_sizes)
  {
    std::cout<<"testing ... " << std::endl;
    int const rows = std::tr1::get<0>(GetParam());
    int const cols = std::tr1::get<1>(GetParam());

    Eigen::MatrixXd wMatrix(rows,cols);
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
	wMatrix(i,j) = rand();

    dl->WriteMatrixToFile(wMatrix,"testmatrix.h5","matrix");
    Eigen::MatrixXd rMatrix = dl->ReadMatrixFromFile("testmatrix.h5","matrix");

    EXPECT_THAT(wMatrix.rows(), Eq(rMatrix.rows()));
    EXPECT_THAT(wMatrix.cols(), Eq(rMatrix.cols()));
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
        EXPECT_THAT(wMatrix(i,j), Eq(rMatrix(i,j)));

  }

    std::tr1::tuple<int,int> const FormulaTable[] = {
    std::tr1::make_tuple( 1, 10),
    std::tr1::make_tuple( 10,  1),
    std::tr1::make_tuple(5, 4),
    std::tr1::make_tuple(17, 27),
    std::tr1::make_tuple(50,50 ),
    std::tr1::make_tuple(500,750),
};

 INSTANTIATE_TEST_CASE_P(TestWithParameters, DataLogger_Test, ::testing::ValuesIn(FormulaTable));
 
  //INSTANTIATE_TEST_CASE_P(NewVectorSizes, DataLogger_Test,::testing::Values(5,7,10,30,50,100,250,500));

} // namespace testing
} // namespace DataLogger_Test
} // namespace CEM
