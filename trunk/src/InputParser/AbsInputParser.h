#ifndef ABS_INPUTPARSER_H
#define ABS_INPUTPARSER_H
#include <iostream>

//struct InputStruct;

enum InputParserError
{
	INPUT_PARSER_SUCCESS = 0,
	BAD_FILE = -1,
	FILE_ALREADY_LOADED = -2
};

class AbsInputParser
{
	public:
	virtual InputParserError Initialize(std::string fileName) = 0;
	virtual InputParserError GetFileName(std::string &fileName) = 0;
	//virtual InputStruct GetInput() = 0;
	virtual InputParserError ReadInputFile() = 0;
	virtual InputParserError ReadInputFile(std::string fileName) = 0;

};


#endif