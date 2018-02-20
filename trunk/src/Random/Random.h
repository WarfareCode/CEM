/**
* @file Random.h
* @brief Header File for the Random Class
* @details Handles generation of Random numbers
* @author Ben Frazier
* @date 02/17/2018 */

#ifndef RANDOM_H
#define RANDOM_H

#include "RandomNumberInterface.h"
#include <Eigen/Dense>
#include <fftw3.h>

#include <random>

namespace RandomVector
{
class Random: public RandomNumberInterface
{
public:
	Random();
    virtual double normal();
    virtual double normal(double mean, double stdDev);
    virtual std::vector<double> normal(int size);
    virtual std::vector<double> normal(int size, double mean, double stdDev);
    
    virtual double uniform();
    virtual double uniform(double lowerBound, double upperBound);
    virtual std::vector<double> uniform(int size);
    virtual std::vector<double> uniform(int size, double lowerBound, double upperBound);

    virtual double chisquare(double degree);
    virtual std::vector<double> chisquare(int size, double degree);
    
    virtual void setSeed(long seed);
    virtual long getSeed(){return seed_;}
    
    virtual bool generatorInitialized(){return initialized_;}
    
    virtual std::vector<std::complex<double> > computeRandomSpectrum(int N, std::vector<double> S, double dk);
    
    
private:
    long seed_;
    std::default_random_engine generator_;
    bool initialized_;
    
    std::normal_distribution<double> normal_;
    std::uniform_real_distribution<double> uniform_;
    
};
}


#endif