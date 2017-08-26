/**
* @file GaussianPulse.h
* @brief Header File for the Gaussian Pulse class 
* @author Ben Frazier
* @date 08/25/2017 */

#ifndef GAUSSIAN_PULSE_H
#define GAUSSIAN_PULSE_H

#include "SourceControlInterface.h"
#include "SourceDefinitionInterface.h"
#include "InputDataInterface.h"

#include <math.h>
#include <string>

namespace CEM
{
  class GaussianPulse: public SourceControlInterface
  {
  public:
    
    GaussianPulse(std::shared_ptr<SourceDefinitionInterface> sourceDefinition);
        //source
    virtual double getInputSource(double time, double shift);
    virtual std::string getSourceType(){return sourceType_;}

  private:
    //member functions

    //member variables 
    int sourceIndex_;  /*!< Spatial index where the source is applied*/
    double sourceAmplitude_;  /*!< Amplitude of the source*/
    std::string sourceType_;  /*!< Type of the source*/
    double frequency_;   /*!< Frequency of the source*/
    double pulseWidth_;  /*!< Pulsewidth of the source*/
    double pulseWidth2_;  /*!< Pulsewidth squared of the source*/
    double sourceDelay_;  /*!< Time delay of the source*/
    
  };
}

#endif
