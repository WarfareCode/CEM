#include "InputParser_YAML.h"

InputParserYAML::InputParserYAML():
fileLoaded_(false)
{
 
}

InputParserYAML::InputParserYAML(std::string fileName)
{
	input_.fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_.fileName_);
	fileLoaded_ = true;
	
}

InputParserYAML::~InputParserYAML()
{

}

InputParserError InputParserYAML::Initialize(std::string fileName)
{
	input_.fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_.fileName_);
	fileLoaded_ = true;

	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::GetFileName(std::string &fileName)
{
	fileName = input_.fileName_;
	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::ReadInputFile()
{
	InputParserError error = INPUT_PARSER_SUCCESS;
	
	input_.computationType_ = basenode_["Computation_Type"].as<std::string>();
	input_.startTime_ = basenode_["Start_Time"].as<double>();
	input_.stopTime_ = basenode_["Stop_Time"].as<double>();
	input_.absorbingBoundaryCondition_ = basenode_["Absorbing_Boundary_Condition"].as<std::string>();
	input_.vectorLength_ = basenode_["Vector_Length"].as<int>();
       	
	return error;
}

InputParserError InputParserYAML::ReadInputFile(std::string fileName)
{
	InputParserError error = INPUT_PARSER_SUCCESS;
	input_.fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_.fileName_);
	error = ReadInputFile();
	return error;
}
