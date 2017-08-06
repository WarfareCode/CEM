#ifndef ABS_INPUTPARSER_H
#define ABS_INPUTPARSER_H
#include <iostream>

class AbsInputParser
{
	public:
	virtual void GetInput(std::string token, std::string fileName) = 0;

};

#endif