/**
* @file FDTD_1D.cpp
* @brief Implementation of the FDTD_1D class
* @author Ben Frazier
* @date 08/12/2017 */

#include "FDTD_1D.h"
#include <math.h>
#include "CEMCommon.h"

namespace CEM
{

 /** \brief FDTD_1D Overloaded Constructor
 *
 *  Standard Constructor
 * @param input The input data structure
 * @param gridDefinition The input definition of the grid
 */
  FDTD_1D::FDTD_1D(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition):
    ABC(SimpleABC),
    dataSize_(0)
  {
    InitializeEngine(input,gridDefinition);
  }

  /**
   * \brief Initialize the FDTD_1D engine
   *
   * This function sets the size of the E and H vectors
   * @param input The input structure read in from the input file
   * @param gridDefinition The input definition of the grid*/
  void FDTD_1D::InitializeEngine(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {
    dataSize_ = gridDefinition->getVectorZLength();
		      
    ABC = SimpleABC;
    H.resize(dataSize_);
    E.resize(dataSize_);
    Ca.resize(dataSize_);
    Cb.resize(dataSize_);
    Da.resize(dataSize_);
    Db.resize(dataSize_);
    InitializeDielectric(input,gridDefinition);

    computeConstants(input, gridDefinition);

    sourceIndex_ = input->getSpatialIndex();
     
  }

  void FDTD_1D::computeConstants(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {

    Eigen::VectorXd sigmaE = getSigmaE(input, gridDefinition);
    Eigen::VectorXd sigmaH = getSigmaH(input, gridDefinition);
    Eigen::VectorXd epsR = getEpsR(input, gridDefinition);
    Eigen::VectorXd muR = getMuR(input, gridDefinition);
    double deltaT = input->getTimeStep();
    double deltaZ = gridDefinition->getGridZStep();

    double denE = 0;
    double denH = 0;
    
    for (int i = 0; i < dataSize_; i++)
      {
	denE = 1 + (sigmaE[i]*deltaT)/(2*epsilon0*epsR[i]);
	Ca[i] = 1 - (sigmaE[i] * deltaT)/(2*epsilon0*epsR[i])/denE;
	Cb[i] = deltaT/(epsilon0*epsR(i)*deltaZ)/denE;

	denH = 1 + sigmaH[i]*deltaT/(2*mu0*muR[i]);
	Da[i] = (1 - sigmaH[i]*deltaT/(2*mu0*muR[i]))/denH;
	Db[i] = (deltaT/(mu0*muR[i]*deltaZ))/denH;

      }
  }

  Eigen::VectorXd FDTD_1D::getEpsR(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {

    Eigen::VectorXd epsR;
    
    if (gridDefinition->getDielectricSpecification() == "File")
      {
	epsR = HDF5IO::ReadVectorFromFile(gridDefinition->getDielectricFileName(),gridDefinition->getDielectricDatasetName());

	//check the size
        if(dielectricConstant_.size() != dataSize_)
	  {
	    std::string eString = "FDTD_1D::Initialize Dielectric ... Dielectric read in from file invalid size: " + std::to_string(dielectricConstant_.size()) + " should be: " + std::to_string( dataSize_);
            throw std::runtime_error(eString);
	  }
      }
    else if (gridDefinition->getDielectricSpecification() == "Constant")
      {
        epsR.resize(dataSize_);
	for (int i = 0; i < dielectricConstant_.size();i++)
	 epsR[i] = gridDefinition->getDielectricConstant();
      }

    return epsR;

  }

  
  Eigen::VectorXd FDTD_1D::getMuR(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {

    Eigen::VectorXd muR(dataSize_);

    for(int i = 0; i < dataSize_; i++)
      muR[i] =1;
    
    return muR;
  }
  
  Eigen::VectorXd FDTD_1D::getSigmaH(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {

    Eigen::VectorXd sigmaH(dataSize_);

    for(int i = 0; i < dataSize_; i++)
      sigmaH[i] = 0;
    
    return sigmaH;
  }

    Eigen::VectorXd FDTD_1D::getSigmaE(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {

    Eigen::VectorXd sigmaE(dataSize_);

    for(int i = 0; i < dataSize_; i++)
      sigmaE[i] = 0;
    
    return sigmaE;
  }
  
    /**
   * \brief Initialize the Dielectric
   *
   * This function sets up the dielectric
   * @param input The input structure read in from the input file
   * @param gridDefinition The input definition of the grid*/
  void FDTD_1D::InitializeDielectric(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition)
  {

    if (gridDefinition->getDielectricSpecification() == "File")
      {
	dielectricConstant_ = HDF5IO::ReadVectorFromFile(gridDefinition->getDielectricFileName(),gridDefinition->getDielectricDatasetName());

	//check the size
        if(dielectricConstant_.size() != dataSize_)
	  {
	    std::string eString = "FDTD_1D::Initialize Dielectric ... Dielectric read in from file invalid size: " + std::to_string(dielectricConstant_.size()) + " should be: " + std::to_string( dataSize_);
            throw std::runtime_error(eString);
	  }
      }
    else if (gridDefinition->getDielectricSpecification() == "Constant")
      {
	dielectricConstant_.resize(dataSize_);
	for (int i = 0; i < dielectricConstant_.size();i++)
	  dielectricConstant_[i] = gridDefinition->getDielectricConstant();
      }

  }

  /**
   * \brief Update the E and H fields
   *
   * This function updates the E and H fields by stepping to the specified time index
   * @param time The next time step to update
   * @param source The Source Control*/
  void FDTD_1D::UpdateFields(double time, std::shared_ptr<SourceControlInterface> source)
  {
 
    //Now update the E Field
    for (int mm = 1; mm < dataSize_; mm++)
       E[mm] = Ca[mm] * E[mm] + Cb[mm]*(H[mm - 1] - H[mm]);

      //update the source
    E[sourceIndex_] -= source->getInputSource(time,0.0);
    
    //update the H Field
    for (int mm = 0; mm < dataSize_ - 1; mm++)
      H[mm] = Da[mm]*H[mm] + Db[mm]*(E[mm] - E[mm + 1]);

    //correct H field --> TFSF
    //H[sourceIndex_ -1] -= source->getInputSource(time,0);

    //applyBC_E();
    //applyBC_H();
  
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
