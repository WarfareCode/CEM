#include "InputParser_YAML.h"
//
InputParserYAML::InputParserYAML():
fileName_(""),
fileLoaded_(false)
{

}

InputParserYAML::InputParserYAML(std::string fileName)
{
	fileName_ = fileName;
	basenode_ = YAML::LoadFile(fileName_);
	fileLoaded_ = true;
	
}

InputParserYAML::~InputParserYAML()
{

}

InputParserError InputParserYAML::Initialize(std::string fileName)
{
	fileName_ = fileName;
	basenode_ = YAML::LoadFile(fileName_);
	fileLoaded_ = true;

	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::GetInput(std::string token)
{
	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::GetFileName(std::string &fileName)
{
	fileName = fileName_;
	return INPUT_PARSER_SUCCESS;
}