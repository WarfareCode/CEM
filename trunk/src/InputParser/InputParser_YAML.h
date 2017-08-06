#ifndef InputParser_YAML_H
#define InputParser_YAML_H


#include "AbsInputParser.h"
#include "yaml-cpp/yaml.h"
#include <fstream>

class InputParserYAML: public AbsInputParser
{
	public:
	InputParserYAML();
	
	virtual void GetInput(std::string token, std::string fileName);


};

#endif