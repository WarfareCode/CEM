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

  std::unique_ptr<SourceControlInterface> createSourceControl(std::shared_ptr<InputDataInterface> input, std::shared_ptr<SourceDefinitionInterface> sourceDefinition)
   {
     std::unique_ptr<SourceControlInterface> sourceControl (new GaussianSource(input,sourceDefinition));
     return sourceControl;
   }

}

