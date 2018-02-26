#include "Random.h"
#include <algorithm>

#include "DataLogger_HDF5.h"

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
    class RandomTest : public Test
    {
    protected:
        RandomTest(){}
        ~RandomTest(){}

    virtual void SetUp()
      {
      	random = new Random();
		initialSeed = 5643467;
	    eps = 1e-10;
		N = 50000;
      }
      virtual void TearDown(){ delete random; }

      Random *random;
      long initialSeed;
	  int N;
	  double eps;

    };

//Test 1 - Hermitian symmetry for random spectra
TEST_F(RandomTest, HermitianSymmetry)
{
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));

	//create a test spectrum to use - exponential is simple and not constant
	double dk = 0.005;
	std::vector<double> S;
	for (int i = 0; i < N/2+1; i++)
	{
		S.push_back(exp(-i*dk));
	}

	std::vector<std::complex<double> > testVec = random->computeRandomSpectrum(N, S, dk);
	
	//make sure we have the expected size vector
	EXPECT_THAT(testVec.size(),Eq(N));
	
	//make sure that both the 0 and N/2 values are purely real
	EXPECT_LE(std::fabs(testVec[0].imag()),eps);
	EXPECT_LE(std::fabs(testVec[N/2].imag()),eps);
	
	for (int i = 1; i < N/2; i++)
	{
		EXPECT_THAT(testVec[i].real(),Eq(testVec[N-i].real()));
		EXPECT_THAT(testVec[i].imag(),Eq(-1*testVec[N-i].imag()));
	}
}
  
//Test 2 - generate random sea suface
TEST_F(RandomTest, sea_surface)
{
    random->setSeed(initialSeed);
    EXPECT_THAT(random->generatorInitialized(), Eq(true));
    EXPECT_THAT(random->getSeed(), Eq(initialSeed));

	int L = 20000;
	int N = 40000;
	double age = 0.84;
	double U10 = 10.0;
	double phi = 0.0;
	std::vector<double> x;
	std::vector<double> h = random->computeSeaSurface(L, N, U10, age, phi, x);
	DataLoggerHDF5 dl("SeaSurface.h5");
	dl.WriteData(h, "h");
	dl.WriteData(x, "x");
}
  
} // namespace testing
} // namespace Random_Test
