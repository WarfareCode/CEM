/**
* @file InputParser.h
* @brief Header File for the InputParser class
* @author Ben Frazier
* @date 08/27/2017 */

#ifndef InputParser_H
#define InputParser_H

#include "InputParserInterface.h"
#include "InputDataInterface.h"

#include "CEMCommon.h"

#include "yaml-cpp/yaml.h"
#include <memory>

#include <fstream>

namespace CEM
{
  
  class InputParser: public InputParserInterface,
                     public InputDataInterface,
                     public std::enable_shared_from_this<InputParser>
  {
  public:
    InputParser();

    //define the virtual functions
    virtual void  ReadInputFile(std::string fileName);

    //Input Data get functions
    virtual std::string getInputFileName(){return inputFileName_;}
    virtual std::string getComputationType(){return computationType_;}
    virtual std::string getAbsorbingBoundaryCondition(){return absorbingBoundaryCondition_;}
    virtual double getStopTime(){return stopTime_;}
    virtual double getStartTime(){return startTime_;}
    virtual double getTimeStep(){return timeStep_;}
    virtual double getTimeLength(){return timeLength_;}

    //Source Control Interface
    virtual std::string getSourceType(){return sourceType_;}
    virtual double getSourceAmplitude(){return sourceAmplitude_;}
    virtual double getSourceDelay(){return sourceDelay_;}
    virtual double getPulseWidth(){return pulseWidth_;}
    virtual int getSpatialIndex(){return spatialIndex_;}
    virtual double getSourceFrequency() {return sourceFrequency_;}
    
    //dielectric
    virtual std::string getDielectricFileName(){return dielectricFileName_;}
    virtual double getDielectricConstant(){return dielectricConstant_;}
    virtual std::string getDielectricSpecification(){return dielectricSpecification_;}
    virtual std::string getDielectricDatasetName(){return dielectricDatasetName_;}

    //Grid Interface
    virtual std::string getGridSpecificationType(){return gridSpecificationType_;}
    virtual int getGridNumDimensions(){return gridNumDimensions_;}
    virtual double getGridZLength(){return gridZLength_;}
    virtual double getGridZStep(){return gridZStep_;}
    virtual double getGridYLength(){return gridYLength_;}
    virtual double getGridYStep(){return gridYStep_;}
    virtual double getGridXLength(){return gridXLength_;}
    virtual double getGridXStep(){return gridXStep_;}
    virtual int getVectorZLength(){return vectorZLength_;}
    virtual int getVectorYLength(){return vectorYLength_;}
    virtual int getVectorXLength(){return vectorXLength_;}
     
    //datalogging
    virtual std::string getOutputFileName(){return outputFileName_;}
    virtual double getOutputDataRate(){return outputRate_;}

    //interface
    virtual std::shared_ptr<InputDataInterface> getInputData();

  private:
    void ReadInputSourceInfo();
    void ReadDataLoggingInfo();
    void ReadTemporalDomainInfo();
    void ReadSpatialDomainInfo();
    void ReadDielectricInfo(YAML::Node dNode);
    void ReadGridInfo();
    double GetYAMLTimeValue(std::string input, YAML::Node node);
	
  private:
    YAML::Node basenode_;
 	
    bool fileLoaded_;

    std::string inputFileName_;               /*!< Input file name that was read from*/
  
    std::string computationType_;             /*!< String containing the computation type to run (FDTD_1D, etc.)*/
    double startTime_;                        /*!< Start time for the simulation*/
    double stopTime_;                         /*!< Stop time for the simulation*/
    double timeStep_;              /*!< Sampling Rate in Hz*/
    int timeLength_;
    std::string absorbingBoundaryCondition_;  /*!< String containing the type of absorbing boundary condition to use (Simple, None, etc.)*/
    
   
    std::string dielectricFileName_;          /*!< Filename for the dielectric constant*/
    double dielectricConstant_;               /*!< Constant value of dielectric constant*/
    std::string dielectricSpecification_;    /*!< Indicates how the dielectric constant is specified*/
    std::string dielectricDatasetName_;      /*!< Name of the dataset to read in for the dielectric constant */
     
    //source parameters
    std::string sourceType_;                  /*!< String defining the type of source*/
    double sourceAmplitude_;                  /*!< Variable for the amplitude of the source*/
    double sourceDelay_;                      /*!< Variable for the delay of the source*/
    double pulseWidth_;                       /*!< Variable for the pulse width of the source*/
    double sourceFrequency_;                  /*!< Variable for the frequency of the source*/
    int spatialIndex_;                        /*!< Variable for the spatial index of the source*/

    //data logging parameters
    std::string outputFileName_;              /*!< Output file name to be written to*/
    double  outputRate_;                      /*!< Output rate to write to the file*/

    //grid parameters
    std::string gridSpecificationType_;     /*!< Indicates how the grid is specified*/
    int gridNumDimensions_;                 /*!< Number of dimensions in the grid*/
    double gridZLength_;                    /*!< Length of the grid along the Z axis in m*/
    double gridZStep_;         /*!< Sampling Frequency of the grid along the Z axis in m^-1*/
    double gridXLength_;                    /*!< Length of the grid along the X axis in m*/
    double gridXStep_;         /*!< Sampling Frequency of the grid along the X axis in m^-1*/
    double gridYLength_;                    /*!< Length of the grid along the Y axis in m*/
    double gridYStep_;         /*!< Sampling Frequency of the grid along the Y axis in m^-1*/
    int vectorXLength_;                        /*!< Number of vector elements in the X dimension*/
    int vectorYLength_;                        /*!< Number of vector elements in the Y dimension*/
    int vectorZLength_;                        /*!< Number of vector elements in the Z dimension*/
    std::string gridFileName_;               /*!< Filename for the grid info*/
     
  };

  //Helper functions to read YAML
  YAML::Node OpenYAMLFile(std::string fileName);
  YAML::Node FindYAMLSection(std::string inputString, YAML::Node basenode);
  template <typename T> T GetYAMLInput(std::string inputString, YAML::Node basenode);
  bool CheckYAMLInput(std::string inputString, YAML::Node basenode);
  
}

#endif
