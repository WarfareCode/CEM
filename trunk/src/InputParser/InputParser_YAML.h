#ifndef InputParser_YAML_H
#define InputParser_YAML_H


#include "AbsInputParser.h"
#include "yaml-cpp/yaml.h"
#include "InputStruct.h"

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

	InputParserError ReadInputFile();
	InputParserError ReadInputFile(std::string fileName);
	
	private:
	YAML::Node basenode_;
	
	bool fileLoaded_;
	InputStruct input_;

};

#endif
