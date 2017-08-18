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
  InputParserError InputParserYAML::ReadInputFile()
  {	
    computationType_ = basenode_["Computation_Type"].as<std::string>();
    startTime_ = basenode_["Start_Time"].as<double>();
    stopTime_ = basenode_["Stop_Time"].as<double>();
    absorbingBoundaryCondition_ = basenode_["Absorbing_Boundary_Condition"].as<std::string>();
    vectorLength_ = basenode_["Vector_Length"].as<int>();
    sourceIndex_ = basenode_["Source_Index"].as<int>();
    outputFileName_ = basenode_["Output_File_Name"].as<std::string>();

    fileLoaded_ = true;
    return INPUT_PARSER_SUCCESS;
  }

  /**
   * \brief read the input file
   *
   * This function reads the configuration into the input structure 
   * @param fileName Name of the file to read*/
  InputParserError InputParserYAML::ReadInputFile(std::string fileName)
  {
    InputParserError error = INPUT_PARSER_SUCCESS;
    inputFileName_ = fileName;
    basenode_ = YAML::LoadFile(inputFileName_);
    error = ReadInputFile();
    return error;
  }
}//end namespace CEM

