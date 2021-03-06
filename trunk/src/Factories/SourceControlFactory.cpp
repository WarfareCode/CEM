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

  std::shared_ptr<SourceControlInterface> SourceControlFactory::createSourceControl(std::shared_ptr<InputDataInterface> input)
   {

     std::shared_ptr<SourceControlInterface> sourceControl;
     
     //check the source definition input for the type to return
     std::string type = input->getSourceType();
    
     if(type.compare("Gaussian Pulse") == 0)
	  sourceControl = std::make_shared<GaussianPulse>(input);
     else if(type.compare("Modulated Gaussian Pulse") == 0)
      sourceControl = std::make_shared<ModulatedGaussianPulse>(input);
     else if(type.compare("Square Pulse") == 0)
	  sourceControl = std::make_shared<SquarePulse>(input);
     else if(type.compare("Modulated Square Pulse") == 0)
       	sourceControl = std::make_shared<ModulatedSquarePulse>(input);
     else
       {
	 std::string eString = "SourceControlFactory::createSourceControl ... " + type + " is not a recognized Source Type";
	 throw std::runtime_error(eString);
       }
     return sourceControl;
   }

}

