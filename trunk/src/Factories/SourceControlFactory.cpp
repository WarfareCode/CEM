/**
* @file SourceControlFactory.cpp
* @brief Implementation of the SourceControlFactory class
* @author Ben Frazier
* @date 08/25/2017 */

#include "SourceControlFactory.h"

namespace CEM
{
  SourceControlFactory::SourceControlFactory()
  {
  }

  std::shared_ptr<SourceControlInterface> SourceControlFactory::createSourceControl(std::shared_ptr<SourceDefinitionInterface> sourceDefinition)
   {
     std::shared_ptr<SourceControlInterface> sourceControl (new GaussianPulse(sourceDefinition));
     return sourceControl;
   }

}

