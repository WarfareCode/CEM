/**
* @file InputParser_YAML.cpp
* @brief Implementation of the InputParserYAML class
* @author Ben Frazier
* @date 08/14/2017 */
#include <math.h>

#include "InputParser_YAML.h"
namespace CEM
{
  /**
   * \brief Standard Constructor
   *
   */
  InputParserYAML::InputParserYAML():
    fileLoaded_(false) 
  {
 
  }

  /**
   * \brief Get the Input Data Interface
   *
   */
  std::shared_ptr<InputDataInterface> InputParserYAML::getInputData()
   {
     if (fileLoaded_)
       return shared_from_this();
     else throw std::runtime_error("InputParserYAML::getInputData()....Input File Not Loaded.");
   }

   /**
   * \brief Get the Grid Definition Itnerface
   *
   */
  std::shared_ptr<GridDefinitionInterface> InputParserYAML::getGridDefinition()
  {
     if (fileLoaded_)
       return shared_from_this();
     else throw std::runtime_error("InputParserYAML::getGridDefinition()....Input File Not Loaded.");
  }

   /**
   * \brief Get the Source Control Itnerface
   *
   */
  std::shared_ptr<SourceDefinitionInterface> InputParserYAML::getSourceDefinition()
  {
     if (fileLoaded_)
       return shared_from_this();
     else throw std::runtime_error("InputParserYAML::getSourceDefinition()....Input File Not Loaded.");
  }
  
  /**
   * \brief read the input file
   *
   * This function reads the configuration into the input structure */
  void InputParserYAML::ReadInputFile()
  {
    ReadSpatialDomainInfo();
    ReadTemporalDomainInfo();
    ReadInputSourceInfo();
    ReadDataLoggingInfo();
    ReadGridInfo();
    fileLoaded_ = true;
  }

  void InputParserYAML::ReadGridInfo()
  {
      YAML::Node gridnode = basenode_["Grid Control"];
     if (gridnode.IsNull())
       throw std::runtime_error("InputParserYAML::ReadGridInfo ... Gridnode is Null");
      
     gridSpecificationType_ = gridnode["Specification"].as<std::string>();
     gridNumDimensions_ = gridnode["Number of Dimensions"].as<int>();
     gridZLength_ = gridnode["Z Length in meters"].as<double>();
     gridZSamplingFrequency_ = gridnode["Z Spatial Sampling Frequency in meters^-1"].as<double>();

     vectorZLength_ = round(gridZLength_/gridZSamplingFrequency_);
      
     YAML::Node dielectricNode = gridnode["Dielectric Constant"];
     ReadDielectricInfo(dielectricNode);
      
  }

  void InputParserYAML::ReadTemporalDomainInfo()
  {
     YAML::Node timenode = basenode_["Simulation Temporal Domain"];
     if (timenode.IsNull())
       throw std::runtime_error("InputParserYAML::ReadTemporalDomainInfo ... Timenode is Null");

    startTime_ = timenode["Start Time"].as<double>();
    stopTime_ = timenode["Stop Time"].as<double>();
    temporalSamplingRate_ = timenode["Temporal Sampling Rate"].as<double>();
  }
  
  void InputParserYAML::ReadSpatialDomainInfo()
  {
     YAML::Node spatialNode = basenode_["Simulation Spatial Domain"];
     if (spatialNode.IsNull())
       throw std::runtime_error("InputParserYAML::ReadSpatialDomainInfo ... Spatialnode is Null");
     
     computationType_ = spatialNode["Computation Type"].as<std::string>();
     absorbingBoundaryCondition_ = spatialNode["Absorbing Boundary Condition"].as<std::string>();
  }

  void InputParserYAML::ReadDielectricInfo(YAML::Node dNode)
  {
    if(dNode.IsNull())
       throw std::runtime_error("InputParserYAML::ReadDielectricInfo ... dielectricNode is Null");

    dielectricSpecification_ = dNode["Specification"].as<std::string>();

    if(dielectricSpecification_ == "File")
      {
	dielectricFileName_ = dNode["File Name"].as<std::string>();
	dielectricFileName_ = "../Input_Data/" + dielectricFileName_;
	dielectricDatasetName_ = dNode["Dataset Name"].as<std::string>();
      }
    else if (dielectricSpecification_ == "Vector")
      {
      }
    else if (dielectricSpecification_ == "Constant")
     {
       dielectricConstant_ =  dNode["Value"].as<double>();
     }

  }

  void InputParserYAML::ReadInputSourceInfo()
  {
    YAML::Node sourceNode = basenode_["Source Info"];

     if (sourceNode.IsNull())
       throw std::runtime_error("InputParserYAML::ReadInputSourceInfo ... Sourcenode is Null");
     
     sourceType_ = sourceNode["Type"].as<std::string>();
     sourceAmplitude_ = sourceNode["Amplitude"].as<double>();
     sourceDelay_ = sourceNode["Delay in Seconds"].as<double>();
     pulseWidth_ = sourceNode["Pulse Width in Seconds"].as<double>();
     spatialIndex_ = sourceNode["Spatial Index"].as<int>();
     
  }

  void InputParserYAML::ReadDataLoggingInfo()
  {
    YAML::Node dataNode = basenode_["Data Logging Info"];
     if (dataNode.IsNull())
       throw std::runtime_error("InputParserYAML::ReadDataLoggingInfo ... Datanode is Null");
     
     outputFileName_ =  dataNode["Output File Name"].as<std::string>();
     outputRate_ = dataNode["Output Rate in Seconds"].as<double>();
  }

  /**
   * \brief read the input file
   *
   * This function reads the configuration into the input structure 
   * @param fileName Name of the file to read*/
  void InputParserYAML::ReadInputFile(std::string fileName)
  {
    inputFileName_ = fileName;
    basenode_ = YAML::LoadFile(inputFileName_);

    if (basenode_.IsNull())
      throw std::runtime_error("InputParserYAML::ReadInputFile ... Basenode is Null");

    ReadInputFile();
  }
}//end namespace CEM

