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
    
    //test the write and read for std::vectors using a single operation and only the dataset
    TEST_F(DataLogger_Test,write_read_vector1)
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
    
     //test the write and read for std::vectors using a single operation and both the dataset and file name
    TEST_F(DataLogger_Test,write_read_vector2)
    {
    	std::vector<double> wVector(size);
    	for(int i = 0; i < size; i++)
			wVector[i] = rand();

    	dl->WriteData(wVector,fileName,"vector");
    	
    	std::vector<double> rVector = dl->ReadVector(fileName,"vector");
	
    	EXPECT_THAT(wVector.size(), Eq(rVector.size()));
    	for(int i = 0; i < size; i++)
    		EXPECT_THAT(wVector[i], Eq(rVector[i]));
    }
    
   //test the write and read for std::vectors using two operations and only the dataset
   TEST_P(DataLogger_Test,write_read_vector_multiple1)
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

    //test the write and read for std::vectors using two operations and both the dataset and file name
   TEST_P(DataLogger_Test,write_read_vector_multiple2)
    {
    	std::vector<double> wVector1(size);
    	for(int i = 0; i < size; i++)
			wVector1[i] = rand();
    	dl->WriteData(wVector1,fileName,"vector");
    	
    	std::vector<double> wVector2(size);
    	for(int i = 0; i < size; i++)
			wVector2[i] = rand();
    	dl->WriteData(wVector2,fileName,"vector");
    	
    	std::vector<double> rVector1 = dl->ReadVector(0,fileName,"vector");
    	std::vector<double> rVector2 = dl->ReadVector(1,fileName,"vector");
	
    	EXPECT_THAT(wVector1.size(), Eq(rVector1.size()));
    	EXPECT_THAT(wVector2.size(), Eq(rVector2.size()));
    	for(int i = 0; i < size; i++)
    	{
    		EXPECT_THAT(wVector1[i], Eq(rVector1[i]));
    		EXPECT_THAT(wVector2[i], Eq(rVector2[i]));
    	}
    }
    
    TEST_P(DataLogger_Test, write_read_efield_2D)
    {
    /*  int const rows = std::tr1::get<0>(GetParam());
      int const cols = std::tr1::get<1>(GetParam());
      

      
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
	}*/
    
    }

   TEST_P(DataLogger_Test, write_read_efield_1D)
    {
    /*  int const rows = 1;
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
	}*/
    
    }

  TEST_P(DataLogger_Test, write_read_vector_variable_sizes)
  {
   /* int const size = std::tr1::get<0>(GetParam());

    std::vector<double> wVector(size);
    for(int i = 0; i < size; i++)
	wVector[i] = rand();

    dl->WriteData(wVector,"testvector.h5","vector");
    std::vector<double> rVector = dl->ReadVector("testvector.h5","vector");

    EXPECT_THAT(wVector.size(), Eq(rVector.size()));
    for(int i = 0; i < size; i++)
    EXPECT_THAT(wVector[i], Eq(rVector[i]));*/
  
  }

  TEST_P( DataLogger_Test, write_read_matrix_variable_sizes)
  {
  /*  int const rows = std::tr1::get<0>(GetParam());
    int const cols = std::tr1::get<1>(GetParam());

    Eigen::MatrixXd wMatrix(rows,cols);
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
	wMatrix(i,j) = rand();

    dl->WriteData(wMatrix,"testmatrix.h5","matrix");
    Eigen::MatrixXd rMatrix = dl->ReadMatrix("testmatrix.h5","matrix");

    EXPECT_THAT(wMatrix.rows(), Eq(rMatrix.rows()));
    EXPECT_THAT(wMatrix.cols(), Eq(rMatrix.cols()));
    for(int i = 0; i < rows; i++)
      for(int j = 0;j < cols ;j++)
        EXPECT_THAT(wMatrix(i,j), Eq(rMatrix(i,j)));*/

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
