/**
* @file InputStruct.h
* @brief Header File for the InputStructure *
* @author Ben Frazier*
* @date 08/14/2017 */

#ifndef INPUTSTRUCT_H
#define INPUTSTRUCT_H

struct InputStruct
{
 std::string fileName_;
 std::string computationType_;
 double startTime_;
 double stopTime_;
 std::string absorbingBoundaryCondition_;
  int vectorLength_;
};

#endif
