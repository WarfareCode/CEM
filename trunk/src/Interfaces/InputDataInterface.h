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
*    getSpatialIndex
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
    virtual std::string getComputationType()=0;
    virtual std::string getAbsorbingBoundaryCondition()=0;
    virtual double getStopTime()=0;
    virtual double getStartTime()=0;
    virtual int getNumDimensions()=0;
    virtual double getZLength()=0;
    virtual double getZSamplingDistance()=0;
    virtual int getVectorZLength()=0;

    //source
    virtual std::string getSourceType()=0;
    virtual double getSourceAmplitude()=0;
    virtual double getSourceDelay()=0;
    virtual double getPulseWidth()=0;
    virtual int getSpatialIndex()=0;

    //dielectric
    virtual std::string getDielectricFileName()=0;
    virtual double getDielectricConstant()=0;
    virtual std::string getDielectricSpecification()=0;
    virtual std::string getDielectricDatasetName()=0;
    
    //datalogging
    virtual std::string getOutputFileName()=0;
    virtual double getOutputDataRate()=0;

    //interface
    virtual InputDataInterface* getInputData()=0;
  };


 /** \brief Overloaded << Operator
 *
 * @param input Reference to the InputDataInterface to make available to the ostream
 */ 
 inline std::ostream& operator<<(std::ostream& os, InputDataInterface& input)  
 {  
   os << "InputFileName: " << input.getInputFileName() << std::endl;
   os << "Spatial Domain: " << std::endl;
   os << "Computation Type: " << input.getComputationType() << std::endl;
   os << "Number of Dimensions: " << input.getNumDimensions() << std::endl;
   os << "Z Length: " << input.getZLength() << std::endl;
   os << "Z Sampling Distance: " << input.getZSamplingDistance() << std::endl;
   os << "Vector Z Length: " << input.getVectorZLength() << std::endl;
   os << "Absorbing Boundary Condition: " << input.getAbsorbingBoundaryCondition()<< std::endl;

   os << "Temporal Domain: " << std::endl;
   os << "Start Time: " << input.getStartTime() << std::endl;
   os << "Stop Time: " << input.getStopTime() << std::endl;
   
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
 
 /** \brief Converstion to std::string
 *
 * Converts an InputDataInterface to a std::string
 * @param input Reference to the InputDataInterface to convert
 */
 inline std::string InputData2String(InputDataInterface *input)
 {
   std::string dataString;
   dataString = "InputFileName: " + input->getInputFileName() + "\n";
   dataString += "Computation Type: " + input->getComputationType() + "\n";
   dataString += "Number of Dimensions: " + std::to_string(input->getNumDimensions()) + "\n";
   dataString += "Z Length: " + std::to_string(input->getZLength()) + "\n";
   dataString += "Z Sampling Distance: " + std::to_string(input->getZSamplingDistance()) + "\n";
   dataString += "Vector Z Length: " + std::to_string(input->getVectorZLength()) + "\n";
   dataString += "Absorbing Boundary Condition: " + input->getAbsorbingBoundaryCondition() + "\n";
 
   dataString += "Temporal Domain:\n"; 
   dataString += "Start Time: " + std::to_string(input->getStartTime()) + "\n";
   dataString += "Stop Time: " + std::to_string(input->getStopTime()) + "\n";
   
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
