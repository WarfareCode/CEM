/**
* @file InputDataInterface.h
* @brief Abstract virtual class for the InputData class, defines the interface
* @details Required Interface functions:
* <pre>
*    getInputFileName
*    getOutputFileName
*    getComputationType
*    getAbsorbingBoundaryCondition
*    getStartTime
*    getStopTime
*    getVectorLength
*    getSourceIndex
*    getInputData
* </pre>
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
    virtual std::string getOutputFileName()=0;
    virtual std::string getComputationType()=0;
    virtual std::string getAbsorbingBoundaryCondition()=0;
    virtual double getStopTime()=0;
    virtual double getStartTime()=0;
    virtual int getVectorLength()=0;
    virtual int getSourceIndex()=0;

    virtual InputDataInterface* getInputData()=0;
  };


 /** \brief Overloaded << Operator
 *
 * @param input Reference to the InputDataInterface to make available to the ostream
 */ 
 inline std::ostream& operator<<(std::ostream& os, InputDataInterface& input)  
 {  
   os << "InputFileName: " << input.getInputFileName() << std::endl;
   os << "OutputFileName: " << input.getOutputFileName() << std::endl;
   os << "Computation Type: " << input.getComputationType() << std::endl;
   os << "Start Time: " << input.getStartTime() << std::endl;
   os << "Stop Time: " << input.getStopTime() << std::endl;
   os << "Absorbing Boundary Condition: " << input.getAbsorbingBoundaryCondition()<< std::endl;
   os << "Vector Length: " << input.getVectorLength() << std::endl;
   os << "Source Index: " << input.getSourceIndex() << std::endl;

  return os;  
  }
 
 /** \brief Converstion to std::string
 *
 * Converts an InputDataInterface to a std::string
 * @param input Reference to the InputDataInterface to convert
 */
 inline std::string InputData2String(InputDataInterface *input)
 {
   std::string dataString;
   dataString = "InputFileName: " + input->getInputFileName() + "\n";
   dataString = "OutputFileName: " + input->getOutputFileName() + "\n";
   dataString += "Computation Type: " + input->getComputationType() + "\n";
   dataString += "Start Time: " + std::to_string(input->getStartTime()) + "\n";
   dataString += "Stop Time: " + std::to_string(input->getStopTime()) + "\n";
   dataString += "Absorbing Boundary Condition: " + input->getAbsorbingBoundaryCondition() + "\n";
   dataString += "Vector Length: " + std::to_string(input->getVectorLength()) + "\n";
   dataString += "Source Index: " + std::to_string(input->getSourceIndex()) + "\n";

   return dataString;
 }
 
}//end namespace CEM

#endif
