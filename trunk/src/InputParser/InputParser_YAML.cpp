#include "InputParser_YAML.h"
//
InputParserYAML::InputParserYAML():
fileLoaded_(false)
{
  input_ = new InputStruct();
}

InputParserYAML::InputParserYAML(std::string fileName)
{
	input_->fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_->fileName_);
	fileLoaded_ = true;
	
}

InputParserYAML::~InputParserYAML()
{
	delete input_;
}

InputParserError InputParserYAML::Initialize(std::string fileName)
{
	input_->fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_->fileName_);
	fileLoaded_ = true;

	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::GetInput(std::string token)
{
	
	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::GetFileName(std::string &fileName)
{
	fileName = input_->fileName_;
	return INPUT_PARSER_SUCCESS;
}

InputParserError InputParserYAML::ReadInputFile()
{
	InputParserError error = INPUT_PARSER_SUCCESS;
	
	input_->computationType_ = basenode_["Computation_Type"].as<std::string>();
	input_->startTime_ = basenode_["Start_Time"].as<double>();
	input_->stopTime_ = basenode_["Stop_Time"].as<double>();
	
	std::cout<<"Computation Type: " << input_->computationType_ << std::endl;
	std::cout<<"Start Time: " << input_->startTime_ << std::endl;
	std::cout<<"Stop Time: " << input_->stopTime_ << std::endl;
	
	return error;
}

InputParserError InputParserYAML::ReadInputFile(std::string fileName)
{
	InputParserError error = INPUT_PARSER_SUCCESS;
	input_->fileName_ = fileName;
	basenode_ = YAML::LoadFile(input_->fileName_);
	error = ReadInputFile();
	return error;
}