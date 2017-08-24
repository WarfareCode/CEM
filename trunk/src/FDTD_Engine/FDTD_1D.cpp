/**
* @file FDTD_1D.cpp
* @brief Implementation of the FDTD_1D class
* @author Ben Frazier
* @date 08/12/2017 */

#include "FDTD_1D.h"
#include <math.h>
#include "CEMdefs.h"
#include "HDF5IOFunctions.h"

namespace CEM
{

 /** \brief FDTD_1D Overloaded Constructor
 *
 *  Standard Constructor
 */
  FDTD_1D::FDTD_1D(std::shared_ptr<InputDataInterface> input):
    initialized(false),
    ABC(SimpleABC),
    imp_(CEM::imp0),
    dataSize_(0)
  {
    InitializeEngine(input);
  }

  /**
   * \brief Initialize the FDTD_1D engine
   *
   * This function sets the size of the E and H vectors
   * @param input The input structure read in from the input file*/
  void FDTD_1D::InitializeEngine(std::shared_ptr<InputDataInterface> input)
  {
    dataSize_ = input->getVectorZLength();
		      
    ABC = SimpleABC;
    H.resize(dataSize_);
    E.resize(dataSize_);

    InitializeSource(input);
    InitializeDielectric(input);
     
    initialized = true;
  }

    /**
   * \brief Initialize the Dielectric
   *
   * This function sets up the dielectric
   * @param input The input structure read in from the input file*/
  void FDTD_1D::InitializeDielectric(std::shared_ptr<InputDataInterface> input)
  {

    if (input->getDielectricSpecification() == "File")
      {
	dielectricConstant_ = HDF5IO::ReadVectorFromFile(input->getDielectricFileName(),input->getDielectricDatasetName());

	//check the size
        if(dielectricConstant_.size() != dataSize_)
	  {
	    std::string eString = "FDTD_1D::Initialize Dielectric ... Dielectric read in from file invalid size: " + std::to_string(dielectricConstant_.size()) + " should be: " + std::to_string( dataSize_);
            throw std::runtime_error(eString);
	  }
      }
    else if (input->getDielectricSpecification() == "Constant")
      {
	dielectricConstant_.resize(dataSize_);
	for (int i = 0; i < dielectricConstant_.size();i++)
	  dielectricConstant_[i] = input->getDielectricConstant();
      }

  }
  
    /**
   * \brief Initialize the Input Source
   *
   * This function sets up the input source
   * @param input The input structure read in from the input file*/
  void FDTD_1D::InitializeSource(std::shared_ptr<InputDataInterface> input)
  {
    sourceAmplitude_ = input->getSourceAmplitude();
    sourceType_ = input->getSourceType();
    pulseWidth_ = input->getPulseWidth();
    sourceDelay_ = input->getSourceDelay();
    sourceIndex_ = input->getSpatialIndex();

    pulseWidth2_ = pulseWidth_*pulseWidth_;
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
      H[mm] = H[mm] + (E[mm + 1] - E[mm]) / imp_;

    //correct H field --> TFSF
    H[sourceIndex_ -1] -= computeSourceAmplitude(time,0)/imp_;

    applyBC_E();
   
    //Now update the E Field
    for (int mm = 1; mm < dataSize_; mm++)
      E[mm] = E[mm] + (H[mm] - H[mm - 1]) * imp_/dielectricConstant_[mm];

    //update the source
    E[sourceIndex_] += computeSourceAmplitude(time,1.0);
  }

   /**
   * \brief Compute the amplitude of the source
   *
   * @param time The time to compute the source
  * @param shift The value to shift the time (TFSF)*/
  double FDTD_1D::computeSourceAmplitude(double time, double shift)
  {
    double val = sourceAmplitude_ *exp(-(time - sourceDelay_ + shift) * (time - sourceDelay_ + shift) / pulseWidth2_);
    return val;
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
