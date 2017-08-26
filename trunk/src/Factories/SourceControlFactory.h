/**
* @file SourceControlFactory.h
* @brief Header File for the SourceControlFactory class
* @author Ben Frazier
* @date 08/25/2017 */

#ifndef SOURCE_CONTROL_FACTORY_H
#define SOURCE_CONTROL_FACTORY_H

#include "GaussianSource.h"
#include "SourceControlInterface.h"
#include "InputDataInterface.h"

namespace CEM
{ 
  class SourceControlFactory
  {
  public:
    SourceControlFactory();

    std::unique_ptr<SourceControlInterface> createSourceControl(std::shared_ptr<InputDataInterface> input, std::shared_ptr<SourceDefinitionInterface> sourceDefinition);

  };
}

#endif
