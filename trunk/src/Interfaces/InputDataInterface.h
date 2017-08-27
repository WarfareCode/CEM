/**
* @file InputDataInterface.h
* @brief Abstract virtual class for the InputData class, defines the interface
* @details Required Interface functions:
* @author Ben Frazier
* @date 08/17/2017 */

#ifndef INPUT_DATA_INTERFACE_H
#define INPUT_DATA_INTERFACE_H
#include <iostream>

namespace CEM
{
  class InputDataInterface
  {
  public:
 
    virtual std::string getInputFileName()=0;
    virtual std::string getComputationType()=0;
    virtual std::string getAbsorbingBoundaryCondition()=0;
   
    //source
    virtual std::string getSourceType()=0;
    virtual double getSourceAmplitude()=0;
    virtual double getSourceDelay()=0;
    virtual double getPulseWidth()=0;
    virtual int getSpatialIndex()=0;
    
    //datalogging
    virtual std::string getOutputFileName()=0;
    virtual double getOutputDataRate()=0;

    //interface
    virtual std::shared_ptr<InputDataInterface> getInputData()=0;
  };


 /** \brief Overloaded << Operator
 *
 * @param os Ouptut Stream
 * @param input Reference to the InputDataInterface to make available to the ostream
 */ 
 inline std::ostream& operator<<(std::ostream& os, InputDataInterface& input)  
 {  
   os << "InputFileName: " << input.getInputFileName() << std::endl;
   os << "Computation Type: " << input.getComputationType() << std::endl;
   os << "Absorbing Boundary Condition: " << input.getAbsorbingBoundaryCondition()<< std::endl;
   os << "Source Parameters: " << std::endl;
   os << "Source Type: " <<  input.getSourceType() << std::endl;
   os << "Source Amplitude: " <<  input.getSourceAmplitude() << std::endl;
   os << "Source Delay: " <<  input.getSourceDelay() << std::endl;
   os << "Pulse Width: " <<  input.getPulseWidth() << std::endl;
   os << "Spatial Index: " << input.getSpatialIndex() << std::endl;
   os << "Data Logging Parameters: " << std::endl;
   os << "Output File Name: " << input.getOutputFileName() << std::endl;
   os << "Output Data Rate: " << input.getOutputDataRate() << std::endl;
  return os;  
  }
 
 /** \brief Conversion to std::string
 *
 * Converts an InputDataInterface to a std::string
 * @param input Reference to the InputDataInterface to convert
 */
 inline std::string InputData2String(std::shared_ptr<InputDataInterface> input)
 {
   std::string dataString;
   dataString = "InputFileName: " + input->getInputFileName() + "\n";
   dataString += "Computation Type: " + input->getComputationType() + "\n";
   dataString += "Absorbing Boundary Condition: " + input->getAbsorbingBoundaryCondition() + "\n";
   dataString += "Source Parameters:\n";
   dataString += "Source Type: " + input->getSourceType() + "\n";
   dataString += "Source Amplitude: " + std::to_string(input->getSourceAmplitude()) + "\n";
   dataString += "Source Delay: " + std::to_string(input->getSourceDelay()) + "\n";
   dataString += "Pulse Width: " + std::to_string(input->getPulseWidth()) + "\n";
   dataString += "Spatial Index: " + std::to_string(input->getSpatialIndex()) + "\n";
   dataString += "Data Logging Parameters:\n";
   dataString += "Output File Name: " + input->getOutputFileName() + "\n";
   dataString += "Output Data Rate: " + std::to_string(input->getOutputDataRate()) + "\n";
   return dataString;
 }
 
}//end namespace CEM

#endif
