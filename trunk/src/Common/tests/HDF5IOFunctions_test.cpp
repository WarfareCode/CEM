#include "CEMCommon.h"

#include <tuple>
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
  class HDF5IO_Test : public TestWithParam<std::tr1::tuple<int, int> >
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

    std::vector<double> data_out;
    data_out.resize(10);

    for(int i = 0; i < 10; i++)
      data_out[i] = i;
    
    HDF5IO::WriteVectorToFile(data_out,testFileName,dataSet);
    std::vector<double> data_in =  HDF5IO::ReadVectorFromFile(testFileName,"/" + dataSet);

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
      
     std::string testFileName = "dielectric1.h5";
     Eigen::MatrixXd er = HDF5IO::ReadMatrixFromFile(FILE::FindInputFile(testFileName),"/EpsR");

     EXPECT_THAT(er.rows(), Eq(1));
     EXPECT_THAT(er.cols(), Eq(200));

     for (int i = 0; i < 100; i++)
        {
	EXPECT_THAT(er(0,i), Eq(1));
      }
     for (int i = 100; i < 200; i++)
      {
	EXPECT_THAT(er(0,i), Eq(9));
      }
  }

  TEST_P(HDF5IO_Test, write_read_matrix_variable_sizes)
  {
    int const rows = std::tr1::get<0>(GetParam());
    int const cols = std::tr1::get<1>(GetParam());

    Eigen::MatrixXd wMatrix(rows,cols);
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
	wMatrix(i,j) = rand();

    HDF5IO::WriteMatrixToFile(wMatrix,"testmatrix.h5","matrix");
    Eigen::MatrixXd rMatrix = HDF5IO::ReadMatrixFromFile("testmatrix.h5","matrix");

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

 INSTANTIATE_TEST_CASE_P(TestWithParameters, HDF5IO_Test, ::testing::ValuesIn(FormulaTable));
 

} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
