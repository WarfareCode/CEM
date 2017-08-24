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
    virtual void  ReadInputFile(std::string fileName);

    //Input Data get functions
    virtual std::string getInputFileName(){return inputFileName_;}
    virtual std::string getComputationType(){return computationType_;}
    virtual std::string getAbsorbingBoundaryCondition(){return absorbingBoundaryCondition_;}
    virtual double getStopTime(){return stopTime_;}
    virtual double getStartTime(){return startTime_;}
    virtual int getNumDimensions(){return numberOfDimensions_;}
    virtual double getZLength(){return zLength_;}
    virtual double getZSamplingDistance(){return zSamplingDistance_;}
    virtual int getVectorZLength(){return vectorZLength_;}
    
    //source
    virtual std::string getSourceType(){return sourceType_;}
    virtual double getSourceAmplitude(){return sourceAmplitude_;}
    virtual double getSourceDelay(){return sourceDelay_;}
    virtual double getPulseWidth(){return pulseWidth_;}
    virtual int getSpatialIndex(){return spatialIndex_;}
    
    
    //datalogging
    virtual std::string getOutputFileName(){return outputFileName_;}
    virtual double getOutputDataRate(){return outputRate_;}

    //interface
    virtual InputDataInterface* getInputData();

  private:
    void ReadInputSourceInfo();
    void ReadDataLoggingInfo();
    void ReadTemporalDomainInfo();
    void ReadSpatialDomainInfo();
    void ReadInputFile();
	
  private:
    YAML::Node basenode_; /*!<YAML basenode to traverse through the file*/
	
    bool fileLoaded_;

    std::string inputFileName_;               /*!< Input file name that was read from*/
  
    std::string computationType_;             /*!< String containing the computation type to run (FDTD_1D, etc.)*/
    double startTime_;                        /*!< Start time for the simulation*/
    double stopTime_;                         /*!< Stop time for the simulation*/
    double temporalSamplingRate_;              /*!< Sampling Rate in Hz*/
    std::string absorbingBoundaryCondition_;  /*!< String containing the type of absorbing boundary condition to use (Simple, None, etc.)*/
    int vectorZLength_;                        /*!< Number of vector elements in the Z dimension*/
    int numberOfDimensions_;                  /*!< Number of dimensions for the spatial domain*/
    double zLength_;                          /*!< Length of the domain in Z*/
    double zSamplingDistance_;                /*!< Sampling distance in Z*/

     
    //source parameters
    std::string sourceType_;                  /*!< String defining the type of source*/
    double sourceAmplitude_;                  /*!< Variable for the amplitude of the source*/
    double sourceDelay_;                      /*!< Variable for the delay of the source*/
    double pulseWidth_;                       /*!< Variable for the pulse width of the source*/
    int spatialIndex_;                        /*!< Variable for the spatial index of the source*/

    //data logging parameters
    std::string outputFileName_;              /*!< Output file name to be written to*/
    double  outputRate_;                      /*!< Output rate to write to the file*/

     
  };
}

#endif
