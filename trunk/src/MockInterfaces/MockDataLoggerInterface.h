/**
* @file MockDataLoggerInterface.h
* @brief Google Mock Definition for DataLoggerInterface
* @author Ben Frazier
* @date 08/23/2017 */

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

#include "DataLoggerInterface.h"


namespace CEM
{
  class MockDataLogger : public DataLoggerInterface
  {
  public:
    MOCK_METHOD1(WriteDataArray, void(std::vector<double> data));
    MOCK_METHOD2(WriteDataArray, void(double *data, int s));
    MOCK_METHOD3(WriteDataArray, void(std::vector<double> data, double time, std::string datasetName));
    MOCK_METHOD3(WriteVectorToFile, void(std::vector<double> data, std::string fileName, std::string datasetName));
    MOCK_METHOD3(WriteVectorToFile, void(Eigen::VectorXd data, std::string fileName, std::string datasetName));
    MOCK_METHOD2(ReadVectorFromFile, std::vector<double>(std::string fileName, std::string datasetName));
    MOCK_METHOD3(ReadDataArray, std::vector<double>(std::string fileName, std::string datasetName, int timeInde));
  };

}


