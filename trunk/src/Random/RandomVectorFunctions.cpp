/**
* @file RandomVectorUtilities.cpp
* @brief Implementation of the Random Vector functions for the Random class
* @author Ben Frazier
* @date 02/17/2018 */

#include "Random.h"

namespace RandomVector
{

/**
   * \brief compute a random vector that follows a given spectrum
   *
   * This function returns a vector of random numbers with Hermitian symmetry that follows
   * a random spectrum in k-space
    * @param N The size of the vector, must be an even integer
    * @param S The input Spectrum to use (must be one sided and of size N/2 + 1 to contain both the 0 and N/2 elements in k-space
    * @param dk The incremental spacing in k-space (used to normalize the spectrum)*/
std::vector<std::complex<double> >  Random::computeRandomSpectrum(int N, std::vector<double> S, double dk)
{
		//need a complex 
		std::vector<std::complex<double> > V;
		std::vector<double> w = normal(N);
		std::vector<double> u = normal(N);

        //initialize the first element
		V.push_back(std::sqrt(S[0]*dk)*w[0]);
		
		//generate the first half of the sequence
		for (int i = 1; i < N/2; i ++)
		{
			V.push_back(0.5*std::sqrt(S[i]*dk)*std::complex<double>(w[i],u[i]));
		}
	
		V.push_back(std::complex<double>(std::sqrt(S[N/2]*dk)*u[0],0));
		
		for (int i = N/2 + 1; i < N; i++)
		{
			V.push_back(std::conj(V[N-i]));
		}

		return V;
}

}//end namespace Random