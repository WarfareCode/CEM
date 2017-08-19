/**
* @file FDTD_1D.cpp
* @brief Implementation of the FDTD_1D class
* @author Ben Frazier
* @date 08/12/2017 */

#include "FDTD_1D.h"
#include <math.h>

namespace CEM
{

 /** \brief FDTD_1D Overloaded Constructor
 *
 *  Standard Constructor
 */
  FDTD_1D::FDTD_1D(InputDataInterface * input):
    initialized(false),
    ABC(SimpleABC),
    imp(377.0),
    dataSize_(0)
  {
    InitializeEngine(input);
  }

  /**
   * \brief Initialize the FDTD_1D engine
   *
   * This function sets the size of the E and H vectors
   * @param input The input structure read in from the input file*/
  void FDTD_1D::InitializeEngine(InputDataInterface * input)
  {

    dataSize_ = input->getVectorLength();
    

    ABC = SimpleABC;

    H.resize(dataSize_);
    E.resize(dataSize_);

    sourceAmplitude_ = input->getSourceAmplitude();
    sourceType_ = input->getSourceType();
    pulseWidth_ = input->getPulseWidth();
    sourceDelay_ = input->getSourceDelay();
    sourceIndex_ = input->getSpatialIndex();

    pulseWidth2_ = pulseWidth_*pulseWidth_;
    
    
    initialized = true;
  }

  /**
   * \brief Update the E and H fields
   *
   * This function updates the E and H fields by stepping to the specified time index
   * @param time The next time step to update*/
  void FDTD_1D::UpdateFields(double time)
  {
    applyBC_H();
  
    //update the H Field
    for (int mm = 0; mm < dataSize_ - 1; mm++)
      H[mm] = H[mm] + (E[mm + 1] - E[mm]) / imp; 

    applyBC_E();
   
    //Now update the E Field
    for (int mm = 1; mm < dataSize_; mm++)
      E[mm] = E[mm] + (H[mm] - H[mm - 1]) * imp;

    //set the source
    SetEFieldSource(time);
  }

  void FDTD_1D::SetEFieldSource(double time)
  {
     E[sourceIndex_] = exp(-(time - sourceDelay_) * (time - sourceDelay_) / pulseWidth2_);
  }

  void FDTD_1D::SetEFieldSource(int index, double time)
  {
    E[index] = exp(-(time - sourceDelay_) * (time - sourceDelay_) / pulseWidth2_);
  }

  /**
   * \brief Return the E field at a specified index
   *
   * This function gets the E field at a given index and returns 0 if the requested
   * index exceeds the size of the array
   * @param index The index of the E field to retrieve*/
  double FDTD_1D::getEField(int index)
  {
    if (index < dataSize_)
      return E[index];
    else
      return 0;
  }

  /**
   * \brief Return the H field at a specified index
   *
   * This function gets the H field at a given index and returns 0 if the requested
   * index exceeds the size of the array
   * @param index The index of the H field to retrieve*/
  double FDTD_1D::getHField(int index)
  {
    if (index < dataSize_)
      return H[index];
    else
      return 0;
  }

  void FDTD_1D::simpleABC_E()
  {
    E[0] = E[1];
  }

  void FDTD_1D::simpleABC_H()
  {
    H[dataSize_-1] = H[dataSize_-2];
  }


  void FDTD_1D::applyBC_E()
  {
    switch (ABC)
      {
      case NoABC:
	break;
      
      case SimpleABC:
	simpleABC_E();
	break;
      
      case TFSF_ABC:
	break;
      default:
	break;
      }
  }

  void FDTD_1D::applyBC_H()
  {
    switch (ABC)
      {
      case NoABC:
	break;
      
      case SimpleABC:
	simpleABC_H();
	break;
      
      case TFSF_ABC:
	break;
      default:
	break;
      }
  }

}//end of namespace
