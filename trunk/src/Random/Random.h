/**
* @file Random.h
* @brief Header File for the Random Class
* @details Handles generation of Random numbers
* @author Ben Frazier
* @date 02/17/2018 */

#ifndef RANDOM_H
#define RANDOM_H

#include "RandomNumberInterface.h"
#include <random>

namespace CEM
{
class Random: public RandomNumberInterface
{
public:
	Random();
    virtual double normal();
    virtual double normal(double mean, double variance);
    virtual std::vector<double> normal(int size);
    virtual std::vector<double> normal(int size, double mean, double variance);
    
    virtual double uniform();
    virtual std::vector<double> uniform(int size);
    virtual double uniform(double mean, double variance);
    virtual std::vector<double> uniform(int size,double mean, double variance);
    
    virtual double chisquare(int degree);
    virtual std::vector<double> chisquare(int size, int degree);
    
    virtual void setSeed(long seed);
    virtual long getSeed(){return seed_;}
    
    virtual bool generatorInitialized(){return initialized_;}
    
private:
    long seed_;
    std::default_random_engine generator_;
    bool initialized_;
    
    std::normal_distribution<double> normal_;
    std::uniform_real_distribution<double> uniform_;
    std::chi_squared_distribution<double> chi_square_;
    
};
}


#endif