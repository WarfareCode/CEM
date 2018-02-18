/**
* @file Random.cpp
* @brief Implementation of the Random class
* @author Ben Frazier
* @date 02/17/2018 */

#include "Random.h"

namespace CEM
{
 /** \brief Random Constructor
 *
 *  Standard Constructor

 */
  Random::Random():
    seed_(5789321),
    initialized_(false)
  {
 
  }

  /**
   * \brief set the random seed
   *
   * This function sets the random seed for the generator
   * @param seed The seed to use*/
  void Random::setSeed(long seed)
  {
    seed_ = seed;
    generator_.seed(seed_);
    initialized_ = true;
     
  }
  
  
  //Normal Distributions ....
    /**
   * \brief get a single normally distributed random number
   *
   * This function returns a single double value that is normally distributed between 0 
    * and 1*/
  double Random::normal()
  {
   double value =  normal_(generator_);
   
   return value;
  }

    /**
   * \brief get a vector of normally distributed random numbers
   *
   * This function returns a single double value that is normally distributed between 0 
    * and 1
    * @param size The length of the vector to return*/
  std::vector<double> Random::normal(int size)
  {
  	std::vector<double> value;
  	for (int i = 0; i < size; i++)
  	{
  	value.push_back(normal_(generator_));
  	}
  	return value;
  }

    /**
   * \brief get a single normally distributed random number
   *
   * This function returns a single double value that is normally distributed between the
   * specified mean and variance 
    * @param mean The mean of the distribution
    * @param variance The variance of the distribution*/
  double Random::normal(double mean, double variance)
  {
  	std::normal_distribution<double> distribution(mean,std::sqrt(variance));
  	double value = distribution(generator_);
  	
  	return value;
  	
  }

    /**
   * \brief get a vector of normally distributed random numbers
   *
   * This function returns a single double value that is normally distributed between the 
    * specified mean and variance 
    *@param size The length of the vector to return
     * @param mean The mean of the distribution
    * @param variance The variance of the distribution*/
  std::vector<double> Random::normal(int size,double mean, double variance)
  {
  std::normal_distribution<double> distribution(mean,std::sqrt(variance));
  std::vector<double> value;
   for (int i = 0; i < size; i++)
  	{
  	value.push_back(distribution(generator_));
  	}
  	return value;
  }

//Uniform Distributions ...
    /**
   * \brief get a single uniformly distributed random number
   *
   * This function returns a single double value that is uniformly distributed between 0 
    * and 1*/
  double Random::uniform()
  {
   return 0.0;
  }

    /**
   * \brief get a vector of uniformly distributed random numbers
   *
   * This function returns a single double value that is uniformly distributed between 0 
    * and 1
    * @param size The length of the vector to return*/
  std::vector<double> Random::uniform(int size)
  {
  std::vector<double> value(0);
  	return value;
  
  }

    /**
   * \brief get a single uniformly distributed random number
   *
   * This function returns a single double value that is uniformly distributed between the
   * specified mean and variance 
    * @param mean The mean of the distribution
    * @param variance The variance of the distribution*/
  double Random::uniform(double mean, double variance)
  {
  	return 0.0;
  }

    /**
   * \brief get a vector of normally distributed random numbers
   *
   * This function returns a single double value that is uniformly distributed between the 
    * specified mean and variance 
    *@param size The length of the vector to return
     * @param mean The mean of the distribution
    * @param variance The variance of the distribution*/
  std::vector<double> Random::uniform(int size,double mean, double variance)
  {
  std::vector<double> value(0);
  	return value;
  }
  
  //Chi-Square Distributions ...
  
      /**
   * \brief get a single uniformly distributed random number
   *
   * This function returns a single double value that follows a chi-square distribution
   * with the specified degree
    * @param degree The degree of the distribution*/
  double Random::chisquare(int degree)
  {
  return 0.0;
  }

    /**
   * \brief get a vector of chi-squqre distributed random numbers
   *
   * This function returns a vector of random numbers that follow a chi-square distribution 
   * with the specified degree
   @param size The length of the vector to return
     * @param degree The degree of the distribution*/
  std::vector<double> Random::chisquare(int size, int degree)
  {
  std::vector<double> value(0);
  	return value;
  }

}//end namespace CEM