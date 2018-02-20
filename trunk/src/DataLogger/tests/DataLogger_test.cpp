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
        dl = new DataLoggerHDF5();
	
      }
      virtual void TearDown(){ delete dl;}

      DataLoggerHDF5* dl;
      std::shared_ptr<MockInputData> input;
      std::string outputFileName;

      int size;

    };

 
    TEST_P(DataLogger_Test, write_read_efield_2D)
    {
      int const rows = std::tr1::get<0>(GetParam());
      int const cols = std::tr1::get<1>(GetParam());
      
      EXPECT_CALL(*input, getGridNumDimensions()).WillRepeatedly(::testing::Return(2));
      EXPECT_CALL(*input, getVectorXLength()).WillRepeatedly(::testing::Return(cols));
      EXPECT_CALL(*input, getVectorYLength()).WillRepeatedly(::testing::Return(rows));
      
      dl->InitializeDataLogger(input);
      std::string datasetname = "/EField";
      double time = 0.1;

      Eigen::MatrixXd wMatrix(rows,cols);
      Eigen::MatrixXd rMatrix;
      int counter = 0;
      for (int t = 0; t < 10; t ++)
	{
    
        for(int i = 0; i < rows; i++)
          for(int j = 0;j < cols ;j++)
	    {
	    wMatrix(i,j) = rand();
	    counter++;
	    }
      
      dl->WriteMatrixToFileWithTime(wMatrix,datasetname,t*time);
      rMatrix = dl->ReadMatrixFromFileAtTime(input->getOutputFileName(),datasetname,t);

      EXPECT_THAT(wMatrix.rows(), Eq(rMatrix.rows()));
      EXPECT_THAT(wMatrix.cols(), Eq(rMatrix.cols()));
      for(int i = 0; i < rows; i++)
       for(int j = 0;j < cols ;j++)
         EXPECT_THAT(wMatrix(i,j), Eq(rMatrix(i,j)));
	}
    
    }

   TEST_P(DataLogger_Test, write_read_efield_1D)
    {
      int const rows = 1;
      int const cols = std::tr1::get<1>(GetParam());
      
      EXPECT_CALL(*input, getGridNumDimensions()).WillRepeatedly(::testing::Return(1));
      EXPECT_CALL(*input, getVectorZLength()).WillRepeatedly(::testing::Return(rows*cols));
      
      dl->InitializeDataLogger(input);
      std::string datasetname = "/EField";
      double time = 0.1;

      Eigen::MatrixXd wMatrix(rows,cols);
      Eigen::MatrixXd rMatrix;
      int counter = 0;
      for (int t = 0; t < 10; t ++)
	{
    
        for(int i = 0; i < rows; i++)
          for(int j = 0;j < cols ;j++)
	    {
	    wMatrix(i,j) = rand();
	    counter++;
	    }
      
      dl->WriteMatrixToFileWithTime(wMatrix,datasetname,t*time);
      rMatrix = dl->ReadMatrixFromFileAtTime(input->getOutputFileName(),datasetname,t);

      EXPECT_THAT(wMatrix.rows(), Eq(rMatrix.rows()));
      EXPECT_THAT(wMatrix.cols(), Eq(rMatrix.cols()));
      for(int i = 0; i < rows; i++)
       for(int j = 0;j < cols ;j++)
         EXPECT_THAT(wMatrix(i,j), Eq(rMatrix(i,j)));
	}
    
    }

  TEST_P(DataLogger_Test, write_read_vector_variable_sizes)
  {
    int const size = std::tr1::get<0>(GetParam());

    std::vector<double> wVector(size);
    for(int i = 0; i < size; i++)
	wVector[i] = rand();

    dl->WriteVectorToFile(wVector,"testvector.h5","vector");
    std::vector<double> rVector = dl->ReadVectorFromFile("testvector.h5","vector");

    EXPECT_THAT(wVector.size(), Eq(rVector.size()));
    for(int i = 0; i < size; i++)
    EXPECT_THAT(wVector[i], Eq(rVector[i]));
  
  }

  TEST_P( DataLogger_Test, write_read_matrix_variable_sizes)
  {
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


} // namespace testing
} // namespace DataLogger_Test
} // namespace CEM
