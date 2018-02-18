/**
* @file RandomNumberInterface.h
* @brief Virtual class definition for Random, defines the interface
* @author Ben Frazier
* @date 02/17/2018 */

#ifndef RANDOM_NUMBER_INTERFACE_H
#define RANDOM_NUMBER_INTERFACE_H

#include <vector>

namespace CEM
{
  
  class RandomNumberInterface
  {
  public:
    virtual double normal()=0;
    virtual double normal(double mean, double variance) = 0;
    virtual std::vector<double> normal(int size)=0;
    virtual std::vector<double> normal(int size, double mean, double variance)=0;
    
    virtual double uniform()=0;
    virtual std::vector<double> uniform(int size) = 0;
    virtual double uniform(double mean, double variance)=0;
    virtual std::vector<double> uniform(int size,double mean, double variance)=0;
    
    virtual double chisquare(int degree)=0;
    virtual std::vector<double> chisquare(int size, int degree)=0;
    
    virtual void setSeed(long seed) = 0;
    virtual long getSeed() = 0;
    
    virtual bool generatorInitialized() = 0;
  };
}

#endif
