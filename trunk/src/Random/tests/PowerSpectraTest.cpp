#include "PowerSpectraFunctions.h"
#include <algorithm>
#include <iterator>
#include <math.h>

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

namespace RandomVector
{

namespace Power_Spectra_Test
{
namespace testing
{

	
    class PowerSpectraTest : public Test
    {
    protected:
        PowerSpectraTest(){}
        ~PowerSpectraTest(){}

    virtual void SetUp()
      {
	 	eps = 1e-10;
      }
      virtual void TearDown(){  }

	  double dk;
	  double eps;

    };

//Test 1 - Elfouhaily power spectra
  TEST_F(PowerSpectraTest, Elfouhaily)
  {
  
  	double L = 20000;
  	double N = 40000;
  	double phi = 0.0;
  	double age = 0.84;
  	double U10 = 10;
  	double dk = 2*M_PI/L;
	
	std::vector<double> k;
	
	for(int i = 0; i < N/2 + 1; i++)
	{
		k.push_back(i*dk);
	}
	
	double testKp = 9.81*age*age/(U10*U10);
	
	std::vector<double> S = Elfouhaily(k,U10,age,phi);
	
	auto maxVal = std::max_element(S.begin(),S.end());
	auto maxInd = std::distance(S.begin(),maxVal);
	
	
	EXPECT_LE(fabs(testKp - k[maxInd]),eps);
	
	std::cout<<"*************************" << std::endl;
	
	for(int i = 0; i < N/2 + 1; i++)
	std::cout<<k[i] << "          " << S[i] << std::endl;
	
	//std::cout<<maxInd << " " << *maxVal << " " << S[maxInd] << std::endl;
	//std::cout<<testKp << " " << k[maxInd] << " " << k[maxInd + 1] << std::endl;
	//std::cout<<"max: " << *maxVal << " ind: " << maxInd << std::endl;
	//
	
	//std::distance(sampleArray.begin(), std::max_element(sampleArray.begin(), sampleArray.end())
	//EXPECT_LE(std::fabs(testKp),eps);
	//for(int i = 0; i < N/2 + 1; i++)
	//std::cout<<"i: " << i << " k: " << k[i] << " S: " << S[i] << std::endl;


  }
  

  
} // namespace testing
} // namespace Power_Spectra_Test
} //namespace RandomVector
