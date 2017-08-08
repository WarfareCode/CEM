#ifndef InputParser_YAML_H
#define InputParser_YAML_H


#include "AbsInputParser.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
using namespace YAML;

class InputParserYAML: public AbsInputParser
{
	public:
	InputParserYAML();
	InputParserYAML(std::string fileName);
	~InputParserYAML();
	
	virtual InputParserError GetInput(std::string token);
	virtual InputParserError Initialize(std::string fileName);
	virtual InputParserError GetFileName(std::string &fileName);
	
	private:
	YAML::Node basenode_;
	
	std::string fileName_;
	bool fileLoaded_;

};

#endif