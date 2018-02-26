#include "RandomVector.h"
#include <algorithm>

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

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
      	random = new RandomVector();
		initialSeed = 5643467;
		eps = 5e-3;
		nTrials = 1000000;
      }
      virtual void TearDown(){ delete random; }

      RandomVector *random;
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
    	tempVec.push_back(random->normal(meanTest,std::sqrt(varTest)));
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

	EXPECT_THAT(tempVec.size(), Eq(nTrials));
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

    std::vector<double> tempVec = random->normal(nTrials,meanTest,std::sqrt(varTest));
    
    double var = computeVariance(tempVec);
    double mean = computeMean(tempVec);

	EXPECT_THAT(tempVec.size(), Eq(nTrials));
    EXPECT_LE(std::fabs(var - varTest), eps);
    EXPECT_LE(std::fabs(mean - meanTest), eps);
  }
  
 //Test 5 - uniformly distributed single elements between 0 and 1
  TEST_F(RandomTest, uniform1)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));

    std::vector<double> tempVec;
    double maxVal = -99999999;
    double minVal = 99999999;
    
    for(int i = 0; i < nTrials;i++)
    {
    	tempVec.push_back(random->uniform());
    	if (tempVec[i] > maxVal)
    		maxVal = tempVec[i];
    	if (tempVec[i] < minVal)
    		minVal = tempVec[i];
    }
    
    EXPECT_LE(maxVal, 1.0);
    EXPECT_GE(minVal, 0.0);
  }
  
  //Test 6 - uniformly distributed single elements with specified mean, variance
    TEST_F(RandomTest, uniform2)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    
    double ubTest = 5.0;
    double lbTest = 3.5;

    std::vector<double> tempVec;
    double maxVal = -99999999;
    double minVal = 99999999;
    
    for(int i = 0; i < nTrials;i++)
    {
    	tempVec.push_back(random->uniform(lbTest,ubTest));
    	if (tempVec[i] > maxVal)
    		maxVal = tempVec[i];
    	if (tempVec[i] < minVal)
    		minVal = tempVec[i];
    }

    EXPECT_LE(maxVal, ubTest);
    EXPECT_GE(minVal, lbTest);
  }

  //Test 7 - uniformly distributed vectors with 0 mean, 1 variance
    TEST_F(RandomTest, uniform3)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    

    std::vector<double> tempVec = random->uniform(nTrials);
    
    auto result = std::minmax_element (tempVec.begin(),tempVec.end());
    
    double maxVal = *result.first;
    double minVal = *result.second;

	EXPECT_THAT(tempVec.size(), Eq(nTrials));
    EXPECT_LE(maxVal, 1.0);
    EXPECT_GE(minVal, 0.0);
  }
  
    //Test 8- uniformly distributed vectors with specified mean, variance
    TEST_F(RandomTest, uniform4)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    
    double ubTest = 5.0;
    double lbTest = 3.5;

    std::vector<double> tempVec = random->uniform(nTrials,lbTest,ubTest);
    
    auto result = std::minmax_element (tempVec.begin(),tempVec.end());
    
    double maxVal = *result.first;
    double minVal = *result.second;
    
    EXPECT_THAT(tempVec.size(), Eq(nTrials));
 	EXPECT_LE(maxVal, ubTest);
    EXPECT_GE(minVal, lbTest);
  } 
  
    //Test 9 - chi-squared distributed single numbers
    TEST_F(RandomTest, chisquare1)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    
	double testDegree = 4;
	
	std::vector<double> tempVec;
    double tempVal = 0;
    
    for(int i = 0; i < nTrials;i++)
    {
    	tempVec.push_back(random->chisquare(testDegree));
    }
	
	double mean = computeMean(tempVec);
	
	EXPECT_LE(std::fabs(mean - testDegree), eps);
  }
  
  //Test 10- chi-squared distributed vectors
    TEST_F(RandomTest, chisquare2)
  {
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));
    
    double testDegree = 4;

    std::vector<double> tempVec = random->chisquare(nTrials,testDegree);
    
    double mean = computeMean(tempVec);
	
	EXPECT_THAT(tempVec.size(), Eq(nTrials));
	EXPECT_LE(std::fabs(mean - testDegree), eps);
  } 
  
} // namespace testing
} // namespace Random_Test
