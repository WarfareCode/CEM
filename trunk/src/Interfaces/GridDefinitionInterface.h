/**
* @file GridDefinitionInterface.h
* @brief Abstract virtual class for the Grid Definition class, defines the interface
* @detail The Grid definition interface contains information about the spatial and temporal sampling of the simulation
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
 * Converts a GridDefinitionInterface to a std::string
 * @param input Reference to the GridDefinitionInterface to convert
 */
 inline std::string InputData2String(std::shared_ptr<GridDefinitionInterface> input)
 {
   std::string dataString;
   dataString = "Grid Control Interface:\n";
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
