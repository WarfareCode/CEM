/**
* @file InputParser_YAML.cpp
* @brief Implementation of the InputParserYAML class
* @author Ben Frazier
* @date 08/14/2017 */

#include "InputParser_YAML.h"

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
	input_.computationType_ = basenode_["Computation_Type"].as<std::string>();
	input_.startTime_ = basenode_["Start_Time"].as<double>();
	input_.stopTime_ = basenode_["Stop_Time"].as<double>();
	input_.absorbingBoundaryCondition_ = basenode_["Absorbing_Boundary_Condition"].as<std::string>();
	input_.vectorLength_ = basenode_["Vector_Length"].as<int>();
	input_.sourceIndex_ = basenode_["Source_Index"].as<int>();

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
	input_.fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_.fileName_);
	error = ReadInputFile();
	return error;
    }
}

/**
* \brief get the input structure
*
* This function reads the configuration into the input structure 
* @param input Reference to the InputStruct*/
InputParserError InputParserYAML::GetInputStruct(InputStruct &input)
{
     if (fileLoaded_ == true)
       {
	 input = input_;
	 return INPUT_PARSER_SUCCESS;
       }
     else
       return INPUT_PARSER_FILE_NOT_LOADED;

}
