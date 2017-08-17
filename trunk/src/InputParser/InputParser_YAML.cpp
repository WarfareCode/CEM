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
   * \brief read the input file
   *
   * This function reads the configuration into the input structure */
  InputParserError InputParserYAML::ReadInputFile()
  {	
    input_.setComputationType(basenode_["Computation_Type"].as<std::string>());
    input_.setStartTime(basenode_["Start_Time"].as<double>());
    input_.setStopTime(basenode_["Stop_Time"].as<double>());
    input_.setAbsorbingBoundaryCondition(basenode_["Absorbing_Boundary_Condition"].as<std::string>());
    input_.setVectorLength(basenode_["Vector_Length"].as<int>());
    input_.setSourceIndex(basenode_["Source_Index"].as<int>());

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
    if (fileLoaded_ == true)
      {
	error = INPUT_PARSER_FILE_ALREADY_LOADED;
	return error;
      }
    else
      {
	input_.setFileName(fileName);
	basenode_ = YAML::LoadFile(input_.getFileName());
	error = ReadInputFile();
	return error;
      }
  }
}
