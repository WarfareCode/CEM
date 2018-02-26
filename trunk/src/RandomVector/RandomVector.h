/**
* @file RandomVector.h
* @brief Header File for the RandomVector Class
* @details Handles generation of Random Vectors
* @author Ben Frazier
* @date 02/17/2018 */

#ifndef RANDOM_VECTOR_H
#define RANDOM_VECTOR_H

#include "RandomVectorInterface.h"
#include <Eigen/Dense>
#include <fftw3.h>

#include <random>

class RandomVector: public RandomVectorInterface
{
public:
	RandomVector();
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
    
    virtual std::vector<double> computeSeaSurface(int L, int N, double U10, double age, double phi, std::vector<double> &x);
    
    
private:
    long seed_;
    std::default_random_engine generator_;
    bool initialized_;
    
    std::normal_distribution<double> normal_;
    std::uniform_real_distribution<double> uniform_;
    
};

#endif