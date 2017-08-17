#include <iostream>
#include "InputData.h"

namespace CEM
{
  
 /** \brief Constructor
 *
 *  Standard Constructor
 */
  InputData::InputData():
    fileName_(""),
    computationType_(""),
    startTime_(0),
    stopTime_(0),
    absorbingBoundaryCondition_(""),
    vectorLength_(0),
    sourceIndex_(0)
  {
  }

}//end namespace CEM
