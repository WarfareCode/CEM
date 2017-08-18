/**
* @file InputParser_YAML.h
* @brief Header File for the InputParserYAML class
* @author Ben Frazier
* @date 08/14/2017 */

#ifndef InputParser_YAML_H
#define InputParser_YAML_H

#include "InputParserInterface.h"
#include "InputDataInterface.h"
#include "yaml-cpp/yaml.h"

#include <fstream>
using namespace YAML;
namespace CEM
{
  class InputParserYAML: public InputParserInterface, public InputDataInterface
  {
  public:
    InputParserYAML();

    //define the virtual functions
    virtual InputParserError ReadInputFile(std::string fileName);

    //Input Data get functions
    virtual std::string getInputFileName(){return inputFileName_;};
    virtual std::string getOutputFileName(){return outputFileName_;};
    virtual std::string getComputationType(){return computationType_;};
    virtual std::string getAbsorbingBoundaryCondition(){return absorbingBoundaryCondition_;};
    virtual double getStopTime(){return stopTime_;};
    virtual double getStartTime(){return startTime_;};
    virtual int getVectorLength(){return vectorLength_;};
    virtual int getSourceIndex(){return sourceIndex_;};
    virtual InputDataInterface* getInputData();
	
    //now define additional support functions
    InputParserError ReadInputFile();
	
  private:
    YAML::Node basenode_; /*!<YAML basenode to traverse through the file*/
	
    bool fileLoaded_;

    std::string inputFileName_;                    /*!< Input file name that was read from*/
    std::string outputFileName_;              /*!< Output file name to be written to*/
    std::string computationType_;             /*!< String containing the computation type to run (FDTD_1D, etc.)*/
    double startTime_;                        /*!< Start time for the simulation*/
    double stopTime_;                         /*!< Stop time for the simulation*/
    std::string absorbingBoundaryCondition_;  /*!< String containing the type of absorbing boundary condition to use (Simple, None, etc.)*/
    int vectorLength_;                        /*!< Variable for the length (number of points) for each spatial vector*/
    int sourceIndex_;   

  };
}

#endif
