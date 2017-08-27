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
    virtual double getSourceFrequency()=0;

    //grid definitions
    virtual std::string getGridSpecificationType()=0;

    //spatial items
    virtual int getGridNumDimensions()=0;
    virtual double getGridZLength()=0;
    virtual double getGridZStep()=0;
    virtual double getGridYLength()=0;
    virtual double getGridYStep()=0;
    virtual double getGridXLength()=0;
    virtual double getGridXStep()=0;
    virtual int getVectorXLength()=0;
    virtual int getVectorYLength()=0;
    virtual int getVectorZLength()=0;

    //temporal items
    virtual double getTimeStep()=0;
    virtual double getStopTime()=0;
    virtual double getStartTime()=0;
    virtual double getTimeLength()=0;

    //dielectric
    virtual std::string getDielectricFileName()=0;
    virtual double getDielectricConstant()=0;
    virtual std::string getDielectricSpecification()=0;
    virtual std::string getDielectricDatasetName()=0;
    
    
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
   os << "Source Frequency: " << input.getSourceFrequency() << std::endl;
   os << "Data Logging Parameters: " << std::endl;
   os << "Output File Name: " << input.getOutputFileName() << std::endl;
   os << "Output Data Rate: " << input.getOutputDataRate() << std::endl;
   os << "Grid Parameters:" << std::endl;
   os << "Specification Type: " << input.getGridSpecificationType() << std::endl;
   os << "X Length (m): " << input.getGridXLength() << std::endl;
   os << "X Spatial Step (m): " << input.getGridXStep() << std::endl;
   os << "Y Length (m): " << input.getGridYLength() << std::endl;
   os << "Y Spatial Step (m): " << input.getGridYStep() << std::endl;
   os << "Z Length (m): " << input.getGridZLength() << std::endl;
   os << "Z Spatial Step (m): " << input.getGridZStep() << std::endl;
   os << "Vector X Length: " << input.getVectorXLength() << std::endl;
   os << "Vector Y Length: " << input.getVectorYLength() << std::endl;
   os << "Vector Z Length: " << input.getVectorZLength() << std::endl;
   os << "Temporal Domain: " << std::endl;
   os << "Start Time: " << input.getStartTime() << std::endl;
   os << "Stop Time: " << input.getStopTime() << std::endl;
   os << "Time Step: " << input.getTimeStep() << std::endl;
   os << " Time Length: " << input.getTimeLength() << std::endl;
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
   dataString += "Source Frequency: " + std::to_string(input->getSourceFrequency()) + "\n";
   dataString += "Data Logging Parameters:\n";
   dataString += "Output File Name: " + input->getOutputFileName() + "\n";
   dataString += "Output Data Rate: " + std::to_string(input->getOutputDataRate()) + "\n";
   dataString = "Grid Parameters:\n";
   dataString += "Specification Type: " + input->getGridSpecificationType() + "\n";
   dataString += "X Length (m): " + std::to_string(input->getGridXLength()) + "\n";
   dataString += "X Spatial Step (m): " + std::to_string(input->getGridXStep()) + "\n";
   dataString += "Y Length (m): " + std::to_string(input->getGridYLength()) + "\n";
   dataString += "Y Spatial Step (m): " + std::to_string(input->getGridYStep()) + "\n";
   dataString += "Z Length (m): " + std::to_string(input->getGridZLength()) + "\n";
   dataString +=  "Z Spatial Step (m): " + std::to_string(input->getGridZStep()) + "\n";
   dataString += "Vector X Length: " + std::to_string(input->getVectorXLength()) + "\n";
   dataString += "Vector Y Length: " + std::to_string(input->getVectorYLength()) + "\n";
   dataString += "Vector Z Length: " + std::to_string(input->getVectorZLength()) + "\n";
   dataString += "Temporal Domain:\n"; 
   dataString += "Start Time: " + std::to_string(input->getStartTime()) + "\n";
   dataString += "Stop Time: " + std::to_string(input->getStopTime()) + "\n";
   dataString += "Time Step: " + std::to_string(input->getTimeStep()) + "\n";
   dataString += "Time Length: " + std::to_string(input->getTimeLength()) + "\n";
   return dataString;
 }
 
}//end namespace CEM

#endif
