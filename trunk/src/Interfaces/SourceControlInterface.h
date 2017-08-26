/**
* @file SourceControlInterface.h
* @brief Abstract virtual class for the SourceControl class, defines the interface
* @author Ben Frazier
* @date 08/17/2017 */

#ifndef SOURCE_CONTROL_INTERFACE_H
#define SOURCE_CONTROL_INTERFACE_H
#include <iostream>

namespace CEM
{
  class SourceControlInterface
  {
  public:

    //source
    virtual std::string getSourceType()=0;
    virtual double getSourceAmplitude()=0;
    virtual double getSourceDelay()=0;
    virtual double getPulseWidth()=0;
    virtual int getSpatialIndex()=0;

    //interface
    virtual std::shared_ptr<SourceControlInterface> getSourceControl()=0;
  };


 /** \brief Overloaded << Operator
 *
 * @param input Reference to the SourceControlInterface to make available to the ostream
 */ 
 inline std::ostream& operator<<(std::ostream& os, SourceControlInterface& input)  
 {  
   os << "Source Parameters: " << std::endl;
   os << "Source Type: " <<  input.getSourceType() << std::endl;
   os << "Source Amplitude: " <<  input.getSourceAmplitude() << std::endl;
   os << "Source Delay: " <<  input.getSourceDelay() << std::endl;
   os << "Pulse Width: " <<  input.getPulseWidth() << std::endl;
   os << "Spatial Index: " << input.getSpatialIndex() << std::endl;

  return os;  
  }
 
 /** \brief Conversion to std::string
 *
 * Converts an SourceControlInterface to a std::string
 * @param input Reference to the SourceControlInterface to convert
 */
 inline std::string InputData2String(std::shared_ptr<SourceControlInterface> input)
 {
   std::string dataString;
   dataString += "Source Parameters:\n";
   dataString += "Source Type: " + input->getSourceType() + "\n";
   dataString += "Source Amplitude: " + std::to_string(input->getSourceAmplitude()) + "\n";
   dataString += "Source Delay: " + std::to_string(input->getSourceDelay()) + "\n";
   dataString += "Pulse Width: " + std::to_string(input->getPulseWidth()) + "\n";
   dataString += "Spatial Index: " + std::to_string(input->getSpatialIndex()) + "\n";
   return dataString;
 }
 
}//end namespace CEM

#endif
