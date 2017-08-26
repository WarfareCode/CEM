#include "FileUtilityFunctions.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;


namespace CEM
{
namespace FileUtilityFunction_Test
{
namespace testing
{
  class FileUtility_Test : public Test
    {
    protected:
       FileUtility_Test(){}
       ~FileUtility_Test(){}

      virtual void SetUp()
      {
	
      }
      virtual void TearDown(){}


    };

  TEST_F(FileUtility_Test, findInvalidfile)
  {

    std::string requestedFileName = "InvalidName.xyz";
    std::string testString = "FILE::FindInputFile ... File: " + requestedFileName + " not found";
    try
      {

	std::string testName1 = FILE::FindInputFile(requestedFileName);
      }

    catch(std::runtime_error error)
      {
	EXPECT_THAT(error.what(),Eq(testString));
      }
    
  }

    TEST_F(FileUtility_Test, findValidfile)
  {

	std::string requestedFileName = "CEMInputFile.yaml";
	std::string testName1 = FILE::FindInputFile(requestedFileName);

  }


} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
