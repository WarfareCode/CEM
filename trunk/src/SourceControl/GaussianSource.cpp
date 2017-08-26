/**
* @file GaussianSource.cpp
* @brief Implementation of the Gaussian Source class 
* @author Ben Frazier
* @date 08/25/2017 */

#include "GaussianSource.h"

namespace CEM
{
  
  GaussianSource::GaussianSource(std::shared_ptr<SourceDefinitionInterface> sourceDefinition)
  {
    sourceAmplitude_ = sourceDefinition->getSourceAmplitude();
    sourceType_ = sourceDefinition->getSourceType();
    pulseWidth_ = sourceDefinition->getPulseWidth();
    sourceDelay_ = sourceDefinition->getSourceDelay();
    sourceIndex_ = sourceDefinition->getSpatialIndex();
  }

  double GaussianSource::getInputSource(double time)
  {
    return sourceAmplitude_ *exp(-(time - sourceDelay_ ) * (time - sourceDelay_ ) / pulseWidth2_);
  }

} //end namespace CEM
