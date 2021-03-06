/**
* @file ModulatedSquarePulse.h
* @brief Header File for the Modulated Square Pulse class 
* @author Ben Frazier
* @date 08/26/2017 */

#ifndef MODULATED_SQUARE_PULSE_H
#define MODULATED_SQUARE_PULSE_H

#include "SourceControlInterface.h"
#include "InputDataInterface.h"
#include "CEMCommon.h"

#include <math.h>
#include <string>

namespace CEM
{
  class ModulatedSquarePulse: public SourceControlInterface
  {
  public:
    
    ModulatedSquarePulse(std::shared_ptr<InputDataInterface> sourceDefinition);
 
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
