/**
* @file SquarePulse.cpp
* @brief Implementation of the Square Pulse class 
* @author Ben Frazier
* @date 08/25/2017 */

#include "SquarePulse.h"

namespace CEM
{
  
  SquarePulse::SquarePulse(std::shared_ptr<SourceDefinitionInterface> sourceDefinition)
  {
    sourceAmplitude_ = sourceDefinition->getSourceAmplitude();
    sourceType_ = sourceDefinition->getSourceType();
    pulseWidth_ = sourceDefinition->getPulseWidth();
    sourceDelay_ = sourceDefinition->getSourceDelay();
    sourceIndex_ = sourceDefinition->getSpatialIndex();
    frequency_ = sourceDefinition->getSourceFrequency();

    pulseWidth2_ = pulseWidth_ * pulseWidth_;
  }

  double SquarePulse::getInputSource(double time, double shift)
  {
    return sourceAmplitude_  *exp(-(time - sourceDelay_ + shift) * (time - sourceDelay_ + shift) / pulseWidth2_);
  }

} //end namespace CEM
