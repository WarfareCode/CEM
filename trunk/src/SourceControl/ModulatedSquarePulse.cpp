/**
* @file ModulatedSquarePulse.cpp
* @brief Implementation of the Modulated Square Pulse class 
* @author Ben Frazier
* @date 08/26/2017 */

#include "ModulatedSquarePulse.h"

namespace CEM
{
  
  ModulatedSquarePulse::ModulatedSquarePulse(std::shared_ptr<SourceDefinitionInterface> sourceDefinition)
  {
    sourceAmplitude_ = sourceDefinition->getSourceAmplitude();
    sourceType_ = sourceDefinition->getSourceType();
    pulseWidth_ = sourceDefinition->getPulseWidth();
    sourceDelay_ = sourceDefinition->getSourceDelay();
    sourceIndex_ = sourceDefinition->getSpatialIndex();
    frequency_ = sourceDefinition->getSourceFrequency();

    pulseWidth2_ = pulseWidth_ * pulseWidth_;
  }

  double ModulatedSquarePulse::getInputSource(double time, double shift)
  {
    return sourceAmplitude_  *exp(-(time - sourceDelay_ + shift) * (time - sourceDelay_ + shift) / pulseWidth2_)*sin(2*M_PI*frequency_*time);
  }

} //end namespace CEM
