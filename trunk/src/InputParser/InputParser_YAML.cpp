/**
* @file InputParser_YAML.cpp
* @brief Implementation of the InputParserYAML class
* @author Ben Frazier
* @date 08/14/2017 */

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
   * \brief Get the Input Data Itnerface
   *
   */
 InputDataInterface* InputParserYAML::getInputData()
   {
     if (fileLoaded_)
       return this;
     else throw std::runtime_error("InputParserYAML::getInputData()....Input File Not Loaded.");
   }
  
  /**
   * \brief read the input file
   *
   * This function reads the configuration into the input structure */
  void InputParserYAML::ReadInputFile()
  {	
    computationType_ = basenode_["Computation_Type"].as<std::string>();
    startTime_ = basenode_["Start_Time"].as<double>();
    stopTime_ = basenode_["Stop_Time"].as<double>();
    absorbingBoundaryCondition_ = basenode_["Absorbing_Boundary_Condition"].as<std::string>();
    vectorLength_ = basenode_["Vector_Length"].as<int>();

    ReadInputSourceInfo();
    ReadDataLoggingInfo();

    fileLoaded_ = true;
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

