/**
* @file Elfouhaily.cpp
* @brief Implementation of the Elfouhaily Power Spectrum
* @author Ben Frazier
* @date 02/17/2018 */

#include "PowerSpectraFunctions.h"

namespace RandomVector
{

    /**
   * \brief generate the Elfouhaily wave spectrum
   *
   * This function returns a vector that follows the Elfouhaily spectrum 
   *
    * @param k The k-space vector to use for the spectrum, must be an odd length to allow both the 0 and N/2 elements to be computed*
    *@param U10 The wind speed in m/s at 10m above the sea surface 
    *@param age The inverse age parameter of the sea, can be 0.84 to 5.0 (0.84 is fully developed)
    *@param phi The angle in radians relative to downwind (0 is purely downwind, pi is purely crosswind)*/
std::vector<double> Elfouhaily(std::vector<double> k, double U10, double age, double phi)
{
	//protect against divide by zero if the first k value is 0
	double eps = 1e-10;
	if (k[0] == 0 && k[1] > eps)
		k[0] = eps;
		
	//initialize the constants
	double g = 9.81; //gravity acceleration
	double Cd10N = 0.00144; //drag coefficient
	double ustar = sqrt(Cd10N)*U10; //friction velocity at the water surface
	double km = 370.0; 
	double cm = 0.23; //minimum phase speed at wavenumber km
	double sigma = 0.08*(1+4*pow(age,-3));
	double alphap = 0.006*pow(age,0.55);//generalized Phillips-Kitaigorodskii equilibrium range parameter for long waves
	double k0 = g/(U10*U10);
	double kp = k0 * age*age; //wavenumber of the spectral peak
	double cp = sqrt(g/kp); //phase speed at the spectral peak cp = U10/age
	double alpham = 0;//alpham is the generalizaed Phillips-Kitaigorodskii equilibrium range parameter for short waves
	double gamma = 0;
	
	if (ustar <= cm) 
		alpham = 0.01*(1 + log(ustar/cm));
	else
		alpham = 0.01*(1 + 3*log(ustar/cm));

	if (age <= 1)
		gamma = 1.7;
	else
		gamma = 1.7 + 6*log(age);

	//allocate vectors
	std::vector<double> S(k.size());
	double c, Lpm, Gam, Jp, Fp, Fm, Bl, Bh, Delk, a0, am;
	double ap = 4.0;

	
    //now compute values that depend on k
    for (int i = 0; i < k.size(); i++)
    {
		c = sqrt((g/k[i])*(1 + (k[i]/km)*(k[i]/km)));//wave phase speed
		Lpm = exp(-5/4.0*(kp/k[i])*(kp/k[i]));  //Pierson-Moskowitz shape spectrum
		Gam = exp(-1/(2.0*sigma*sigma)*(sqrt(k[i]/kp) - 1 )*(sqrt(k[i]/kp) - 1 ) );
		Jp = pow(gamma,Gam); //JONSWAP peak enhancement or "overshoot" factor
		Fp = Lpm*Jp*exp(-age/sqrt(10.0)*(sqrt(k[i]/kp) - 1) ); //long-wave side effect function
		Fm = Lpm*Jp*exp(-0.25*(k[i]/km - 1)*(k[i]/km - 1)); //short-wave side effect function
		Bl = 0.5*alphap*(cp/c)*Fp;
		Bh = 0.5*alpham*(cm/c)*Fm;
		S[i] = (Bl + Bh)/pow(k[i],3);
		
		//compute the spreading function
		a0 = log(2)/2.0;
		am = 0.13*ustar/cm;
		Delk = tanh(a0 + ap*pow(c/cp,2.5) + am*pow(cm/c,2.5));
		//S[i]= 1*S[i]*1/(2.)*(1 + Delk*cos(2*phi));

	}
	
	return S;
}

}//end namespace RandomVector