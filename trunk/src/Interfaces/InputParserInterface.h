/**
* @file InputParserInterface.h
* @brief Abstract virtual class for the Input Parser, defines the interface*
* @author Ben Frazier*
* @date 08/14/2017 */


#ifndef INPUTPARSER_INTERFACE_H
#define INPUTPARSER_INTERFACE_H
#include "CEMTypes.h"
#include <iostream>

struct InputStruct;

class InputParserInterface
{
	public:
	virtual InputParserError ReadInputFile(std::string fileName) = 0;
	virtual InputParserError GetInputStruct(InputStruct &input) = 0;

};


#endif
