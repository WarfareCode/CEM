/**
* @file CEMTypes.h
* @brief Contains enumerations and typedefs
* @author Ben Frazier
* @date 08/14/2017 */


#ifndef CEM_TYPES_H
#define CEM_TYPES_H

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
  
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args)
   {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
  

}// end namespace CEM

#endif
