/**
* @file CEMTypes.h
* @brief Contains enumerations and typedefs
* @author Ben Frazier
* @date 08/14/2017 */


#ifndef CEM_TYPES_H
#define CEM_TYPES_H

/**
* @brief enumeration for the Input Parser error
*/
enum InputParserError
{
  INPUT_PARSER_SUCCESS = 0,
  INPUT_PARSER_BAD_FILE = -1,
  INPUT_PARSER_FILE_ALREADY_LOADED = -2,
  INPUT_PARSER_FILE_NOT_LOADED = -3
};

/**
* @brief enumeration for the Absorbing Boundary Condition (ABC)
*/
enum AbsorbingBoundaryCondition
{
   NoABC = 0,
   SimpleABC,
   TFSF_ABC
};

#endif
