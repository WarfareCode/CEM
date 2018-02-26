/**
* @file RandomVectorUtilities.cpp
* @brief Implementation of the Random Vector functions for the RandomVector class
* @author Ben Frazier
* @date 02/17/2018 */

#include "RandomVector.h"
#include "PowerSpectraFunctions.h"

/**
   * \brief compute a random vector that follows a given spectrum
   *
   * This function returns a vector of random numbers with Hermitian symmetry that follows
   * a random spectrum in k-space
    * @param N The size of the vector, must be an even integer
    * @param S The input Spectrum to use (must be one sided and of size N/2 + 1 to contain both the 0 and N/2 elements in k-space
    * @param dk The incremental spacing in k-space (used to normalize the spectrum)*/
std::vector<std::complex<double> >  RandomVector::computeRandomSpectrum(int N, std::vector<double> S, double dk)
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

/**
   * \brief compute a random sea surface
   *
   * This function returns a vector of random numbers with Hermitian symmetry that follows
   * a random spectrum in k-space
   *  @param L The spatial domain length to use
    * @param N The size of the vector, must be an even integer
    * @param U10 The wind speed at 10 m altitude
    * @param age The inverse age parameter to use
    * @param phi The angle relative to the downwind direction
    * @param x A reference to a standard vector containing the spatial points*/
std::vector<double> RandomVector::computeSeaSurface(int L, int N, double U10, double age, double phi, std::vector<double> &x)
{

    std::vector<double> output(N,0);
    x.resize(N);
	double dk = 2*M_PI/(double)L;
	std::vector<double> k;
	
		
	for(int i = 0; i < N/2 + 1; i++)
	{
		k.push_back(i*dk);
	}
	
	
	std::vector<double> S = PowerSpectra::Elfouhaily(k,U10,age,phi);
	std::vector<std::complex<double> > V = computeRandomSpectrum(N,S,dk);

	fftw_plan p = fftw_plan_dft_c2r_1d(N, reinterpret_cast<fftw_complex*>(&V[0]),
 						 &output[0],FFTW_ESTIMATE);

    fftw_execute(p);
    
    for (int i = 0; i < N; i++)
    	x[i] = i*(double)L/(double)N;
    	
    return output;
    
}