#include "DataLogger_HDF5.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;


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
		fileName = "test.h5";
        dl = new DataLoggerHDF5(fileName);
        size = 10;
	
      }
      virtual void TearDown(){ delete dl;}

      DataLoggerHDF5* dl;
      std::string fileName;

      int size;

    };
    
    //creation and initialization test
    TEST_F(DataLogger_Test,create_init)
    {
    	EXPECT_THAT(dl->getInitialized(),Eq(true));
    	
    	DataLoggerHDF5 dl2;
    	EXPECT_THAT(dl2.getInitialized(),Eq(false));
    	dl2.CreateFile("test2.h5");
    	EXPECT_THAT(dl2.getInitialized(),Eq(true));
    }
    
    //test the write and read for std::vectors using a single operation
    TEST_F(DataLogger_Test,write_read_vector)
    {
    	std::vector<double> wVector(size);
    	for(int i = 0; i < size; i++)
			wVector[i] = rand();

    	dl->WriteData(wVector,"vector");
    	
    	std::vector<double> rVector = dl->ReadVector("vector");
	
    	EXPECT_THAT(wVector.size(), Eq(rVector.size()));
    	for(int i = 0; i < size; i++)
    		EXPECT_THAT(wVector[i], Eq(rVector[i]));
    }
    
   //test the write and read for std::vectors using two operations
   TEST_P(DataLogger_Test,write_read_vector_multiple)
    {
    	std::vector<double> wVector1(size);
    	for(int i = 0; i < size; i++)
			wVector1[i] = rand();
    	dl->WriteData(wVector1,"vector");
    	
    	std::vector<double> wVector2(size);
    	for(int i = 0; i < size; i++)
			wVector2[i] = rand();
    	dl->WriteData(wVector2,"vector");
    	
    	std::vector<double> rVector1 = dl->ReadVector(0,"vector");
    	std::vector<double> rVector2 = dl->ReadVector(1,"vector");
	
    	EXPECT_THAT(wVector1.size(), Eq(rVector1.size()));
    	EXPECT_THAT(wVector2.size(), Eq(rVector2.size()));
    	for(int i = 0; i < size; i++)
    	{
    		EXPECT_THAT(wVector1[i], Eq(rVector1[i]));
    		EXPECT_THAT(wVector2[i], Eq(rVector2[i]));
    	}
    	
    }

//test the write and read for std::vectors using different sizes
TEST_P(DataLogger_Test, write_read_vector_variable_sizes)
  {
    int const size = std::tr1::get<0>(GetParam());

    std::vector<double> wVector(size);
    for(int i = 0; i < size; i++)
		wVector[i] = rand();

    dl->WriteData(wVector,"vector");
    std::vector<double> rVector = dl->ReadVector("vector");

    EXPECT_THAT(wVector.size(), Eq(rVector.size()));
    for(int i = 0; i < size; i++)
    	EXPECT_THAT(wVector[i], Eq(rVector[i]));
  
  }
    
//test the write and read for Eigen matrices using a single operation
TEST_F(DataLogger_Test,write_read_matrix)
    {
    
    int rows = 10;
    int cols = 10;

    Eigen::MatrixXd wMatrix(rows,cols);
    
     for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
		wMatrix(i,j) = rand();

    	dl->WriteData(wMatrix,"matrix");
    	
    Eigen::MatrixXd rMatrix = dl->ReadMatrix("matrix");
	
    EXPECT_THAT(wMatrix.rows(), Eq(rMatrix.rows()));
    EXPECT_THAT(wMatrix.cols(), Eq(rMatrix.cols()));
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
        EXPECT_THAT(wMatrix(i,j), Eq(rMatrix(i,j)));
    }

//test the write and read for Eigen matrices using using two operations
TEST_F(DataLogger_Test,write_read_matrix_multiple)
    {
    
    int rows = 10;
    int cols = 5;

    Eigen::MatrixXd wMatrix1(rows,cols);
    Eigen::MatrixXd wMatrix2(rows,cols);
    
     for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
		wMatrix1(i,j) = rand();
	dl->WriteData(wMatrix1,"matrix");
		
		std::cout<<"wrote once .. " << std::endl;
	for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
		wMatrix2(i,j) = rand();
    dl->WriteData(wMatrix2,"matrix");	
    
    std::cout<<"done writing ... " << std::endl;
    
    Eigen::MatrixXd rMatrix1 = dl->ReadMatrix(0,"matrix");
    Eigen::MatrixXd rMatrix2 = dl->ReadMatrix(1,"matrix");
	
    EXPECT_THAT(wMatrix1.rows(), Eq(rMatrix1.rows()));
    EXPECT_THAT(wMatrix1.cols(), Eq(rMatrix1.cols()));
    EXPECT_THAT(wMatrix2.rows(), Eq(rMatrix2.rows()));
    EXPECT_THAT(wMatrix2.cols(), Eq(rMatrix2.cols()));
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
      {
        EXPECT_THAT(wMatrix1(i,j), Eq(rMatrix1(i,j)));
        EXPECT_THAT(wMatrix2(i,j), Eq(rMatrix2(i,j)));
      }
    }
         
   //test the write and read for Eigen matrices using different sizes   
  TEST_P( DataLogger_Test, write_read_matrix_variable_sizes)
  {
    int const rows = std::tr1::get<0>(GetParam());
    int const cols = std::tr1::get<1>(GetParam());

    Eigen::MatrixXd wMatrix(rows,cols);
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
	wMatrix(i,j) = rand();

    dl->WriteData(wMatrix,"matrix");
    
    Eigen::MatrixXd rMatrix = dl->ReadMatrix("matrix");

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
