/**
* @file CEMTypes.h
* @brief Contains enumerations and typedefs
* @author Ben Frazier
* @date 08/14/2017 */

#ifndef CEM_TYPES_H
#define CEM_TYPES_H

#include <Eigen/Dense>
#include <vector>

namespace CEM
{
  /**
   * @brief enumeration for the Absorbing Boundary Condition (ABC)
   */
  enum AbsorbingBoundaryCondition
  {
    NoABC = 0,
    SimpleABC,
    TFSF_ABC
  };

}// end namespace CEM

#endif
