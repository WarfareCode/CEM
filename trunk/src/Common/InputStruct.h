/**
* @file InputStruct.h
* @brief Header File for the InputStructure
* @author Ben Frazier
* @date 08/14/2017 */

#ifndef INPUTSTRUCT_H
#define INPUTSTRUCT_H

struct InputStruct
{
 std::string fileName_;                    /*!< Input file name that was read from*/
 std::string computationType_;             /*!< String containing the computation type to run (FDTD_1D, etc.)*/
 double startTime_;                        /*!< Start time for the simulation*/
 double stopTime_;                         /*!< Stop time for the simulation*/
 std::string absorbingBoundaryCondition_;  /*!< String containing the type of absorbing boundary condition to use (Simple, None, etc.)*/
 int vectorLength_;                        /*!< Variable for the length (number of points) for each spatial vector*/
 int sourceIndex_;                        /*!< Index at which to apply the E-field source*/
};

#endif
