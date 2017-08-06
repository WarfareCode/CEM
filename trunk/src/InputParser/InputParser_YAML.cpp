#include "InputParser_YAML.h"
//
InputParserYAML::InputParserYAML()
{

}

void InputParserYAML::GetInput(std::string token, std::string fileName)

{
    std::ifstream fin(fileName);
    YAML::Parser parser(fin);

    YAML::Node doc;

}