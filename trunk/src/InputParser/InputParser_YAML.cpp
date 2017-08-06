#include "InputParser_YAML.h"
//
InputParserYAML::InputParserYAML()
{
std::cout<<"Creating ... " << std::endl;
}

InputParserYAML::~InputParserYAML()
{
}

void InputParserYAML::GetInput(std::string token, std::string fileName)

{
    std::cout<<"loading the file: " << fileName << std::endl;
    YAML::Node config = YAML::LoadFile(fileName);


}