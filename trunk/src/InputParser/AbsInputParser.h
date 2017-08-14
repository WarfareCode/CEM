/**
* @file AbsInputParser.h
* @brief Abstract virtual class for the Input Parser*
* @author Ben Frazier*
* @date 08/14/2017 */


#ifndef ABS_INPUTPARSER_H
#define ABS_INPUTPARSER_H
#include <iostream>

enum InputParserError
{
	INPUT_PARSER_SUCCESS = 0,
	BAD_FILE = -1,
	FILE_ALREADY_LOADED = -2,
	FILE_NOT_LOADED = -3
};

class AbsInputParser
{
	public:
	virtual InputParserError Initialize(std::string fileName) = 0;
	virtual InputParserError ReadInputFile() = 0;
	virtual InputParserError ReadInputFile(std::string fileName) = 0;

};


#endif
