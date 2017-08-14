/**
* @file CEMTypes.h
* @brief Contains enumerations and typedefs *
* @author Ben Frazier*
* @date 08/14/2017 */


#ifndef CEM_TYPES_H
#define CEM_TYPES_H

enum InputParserError
{
	INPUT_PARSER_SUCCESS = 0,
	BAD_FILE = -1,
	FILE_ALREADY_LOADED = -2,
	FILE_NOT_LOADED = -3
};

enum AbsorbingBoundaryCondition
  {
    NoABC = 0,
    SimpleABC,
    TFSF_ABC
  };

#endif
