#include "Random.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

namespace CEM
{

namespace Random_Test
{
namespace testing
{
double computeMean(std::vector<double> input)
{
	double temp = 0.0;
	for (int i = 0; i < input.size();i++)
	{
	temp += input[i];
	}
	temp /= (double)input.size();
	
	return temp;
}
	
double computeVariance(std::vector<double> input)
{
	double mean = computeMean(input);
	double temp = 0.0;

    for(int i = 0; i < input.size();i++)
    {
    	temp += (input[i] - mean) * (input[i] - mean);
    }
    temp /= (double)input.size();
    
    return temp;
}
    class RandomTest : public Test
    {
    protected:
        RandomTest(){}
        ~RandomTest(){}

    virtual void SetUp()
      {
      	random = new Random();
		initialSeed = 5643467;
		eps = 5e-3;
		nTrials = 1000000;
      }
      virtual void TearDown(){ delete random; }


      Random *random;
      long initialSeed;
	  double eps;
	  int nTrials;

    };

//Test 1 - normally distributed single elements with 0 mean, 1 variance
  TEST_F(RandomTest, normal1)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));

    std::vector<double> tempVec;
    double tempVal = 0;
    
    for(int i = 0; i < nTrials;i++)
    {
    	tempVec.push_back(random->normal());
    	tempVal += tempVec[i];
    }
    tempVal /= (double) nTrials;
    
    double var = computeVariance(tempVec);

    
    EXPECT_LE(std::fabs(var - 1.0), eps);
    EXPECT_LE(std::fabs(tempVal), eps);

  }
  
  //Test 2 - normally distributed single elements with specified mean, variance
    TEST_F(RandomTest, normal2)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    
    double meanTest = 5.0;
    double varTest = 3.5;

    std::vector<double> tempVec;
    double tempVal = 0;
    
    for(int i = 0; i < nTrials;i++)
    {
    	tempVec.push_back(random->normal(meanTest,varTest));
    	tempVal += tempVec[i];
    }
    tempVal = tempVal/(double)nTrials;
    
    double var = computeVariance(tempVec);
    

    EXPECT_LE(std::fabs(var - varTest), eps);
    EXPECT_LE(std::fabs(tempVal - meanTest), eps);

  }

  //Test 3 - normally distributed vectors with 0 mean, 1 variance
    TEST_F(RandomTest, normal3)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    

    std::vector<double> tempVec = random->normal(nTrials);
    
    double var = computeVariance(tempVec);
    double mean = computeMean(tempVec);

    EXPECT_LE(std::fabs(var - 1.0), eps);
    EXPECT_LE(std::fabs(mean - 0.0), eps);

  }
  
    //Test 4- normally distributed vectors with specified mean, variance
    TEST_F(RandomTest, normal4)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    
     double meanTest = 10.0;
    double varTest = 2.3;

    std::vector<double> tempVec = random->normal(nTrials,meanTest,varTest);
    
    double var = computeVariance(tempVec);
    double mean = computeMean(tempVec);

    EXPECT_LE(std::fabs(var - varTest), eps);
    EXPECT_LE(std::fabs(mean - meanTest), eps);

  }
  
} // namespace testing
} // namespace Random_Test
} //namespace CEM
