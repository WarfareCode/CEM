/**
* @file GridDefinitionInterface.h
* @brief Abstract virtual class for the Grid Definition class, defines the interface
* @details Required Interface functions:
* @author Ben Frazier
* @date 08/25/2017 */

#ifndef GRID_DEFINITION_INTERFACE_H
#define GRID_DEFINITION_INTERFACE_H
#include <iostream>

namespace CEM
{
  class GridDefinitionInterface
  {
  public:

    //Grid Interface get functions
    virtual std::string getGridSpecificationType()=0;
    virtual int getGridNumDimensions()=0;
    virtual double getGridZLength()=0;
    virtual double getGridZSamplingFrequency()=0;
    virtual double getGridYLength()=0;
    virtual double getGridYSamplingFrequency()=0;
    virtual double getGridXLength()=0;
    virtual double getGridXSamplingFrequency()=0;
    virtual int getVectorXLength()=0;
    virtual int getVectorYLength()=0;
    virtual int getVectorZLength()=0;

    //dielectric
    virtual std::string getDielectricFileName()=0;
    virtual double getDielectricConstant()=0;
    virtual std::string getDielectricSpecification()=0;
    virtual std::string getDielectricDatasetName()=0;

    //interface
    virtual std::shared_ptr<GridDefinitionInterface> getGridDefinition()=0;
  };


 /** \brief Overloaded << Operator
 *
 * @param os Ouptut Stream
 * @param input Reference to the GridDefinitionInterface to make available to the ostream
 */ 
 inline std::ostream& operator<<(std::ostream& os, GridDefinitionInterface& input)  
 {  
   os << "Grid Control Interface:" << std::endl;
   os << "Specification Type: " << input.getGridSpecificationType() << std::endl;
   os << "X Length (m): " << input.getGridXLength() << std::endl;
   os << "X Sampling Frequency (m^-1): " << input.getGridXSamplingFrequency() << std::endl;
   os << "Y Length (m): " << input.getGridYLength() << std::endl;
   os << "Y Sampling Frequency (m^-1): " << input.getGridYSamplingFrequency() << std::endl;
   os << "Z Length (m): " << input.getGridZLength() << std::endl;
   os << "Z Sampling Frequency (m^-1): " << input.getGridZSamplingFrequency() << std::endl;
   os << "Vector X Length: " << input.getVectorXLength() << std::endl;
   os << "Vector Y Length: " << input.getVectorYLength() << std::endl;
   os << "Vector Z Length: " << input.getVectorZLength() << std::endl;
  return os;  
  }
 
 /** \brief Conversion to std::string
 *
 * Converts a GridDefinitionInterface to a std::string
 * @param input Reference to the GridDefinitionInterface to convert
 */
 inline std::string InputData2String(std::shared_ptr<GridDefinitionInterface> input)
 {
   std::string dataString;
   dataString = "Grid Control Interface:\n";
   dataString += "Specification Type: " + input->getGridSpecificationType() + "\n";
   dataString += "X Length (m): " + std::to_string(input->getGridXLength()) + "\n";
   dataString += "X Sampling Frequency (m^-1): " + std::to_string(input->getGridXSamplingFrequency()) + "\n";
   dataString += "Y Length (m): " + std::to_string(input->getGridYLength()) + "\n";
   dataString += "Y Sampling Frequency (m^-1): " + std::to_string(input->getGridYSamplingFrequency()) + "\n";
   dataString += "Z Length (m): " + std::to_string(input->getGridZLength()) + "\n";
   dataString += "Z Sampling Frequency (m^-1): " + std::to_string(input->getGridZSamplingFrequency()) + "\n";
   dataString += "Vector X Length: " + std::to_string(input->getVectorXLength()) + "\n";
   dataString += "Vector Y Length: " + std::to_string(input->getVectorYLength()) + "\n";
   dataString += "Vector Z Length: " + std::to_string(input->getVectorZLength()) + "\n";
   return dataString;
 }
 
}//end namespace CEM

#endif
