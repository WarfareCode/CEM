#ifndef ABS_INPUTPARSER_H
#define ABS_INPUTPARSER_H
#include <iostream>

enum InputParserError
{
	INPUT_PARSER_SUCCESS = 0,
	BAD_FILE = -1,
	FILE_ALREADY_LOADED = -2
};

class AbsInputParser
{
	public:
	virtual InputParserError GetInput(std::string token) = 0;
	virtual InputParserError Initialize(std::string fileName) = 0;
	virtual InputParserError GetFileName(std::string &fileName) = 0;

};


#endif