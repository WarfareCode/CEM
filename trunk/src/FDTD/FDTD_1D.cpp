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
  FDTD_1D::FDTD_1D(std::shared_ptr<InputDataInterface> input):
    ABC(SimpleABC),
    dataSize_(0)
  {
    InitializeEngine(input);
  }

  /**
   * \brief Initialize the FDTD_1D engine
   *
   * This function sets the size of the E and H vectors
   * @param input The input structure read in from the input file
   * @param gridDefinition The input definition of the grid*/
  void FDTD_1D::InitializeEngine(std::shared_ptr<InputDataInterface> input)
  {
    dataSize_ = input->getVectorZLength();
		      
    ABC = SimpleABC;
    H.resize(1,dataSize_);
    E.resize(1,dataSize_);
    Ca.resize(1,dataSize_);
    Cb.resize(1,dataSize_);
    Da.resize(1,dataSize_);
    Db.resize(1,dataSize_);

    computeConstants(input);

    sourceIndex_ = input->getSpatialIndex();
     
  }

  void FDTD_1D::computeConstants(std::shared_ptr<InputDataInterface> input)
  {

    
    Eigen::MatrixXd sigmaE = getSigmaE(input);
    Eigen::MatrixXd sigmaH = getSigmaH(input);
    Eigen::MatrixXd epsR = getEpsR(input);
    Eigen::MatrixXd muR = getMuR(input);
    double deltaT = input->getTimeStep();
    double deltaZ = input->getGridZStep();

    double denE = 0;
    double denH = 0;
    
    for (int i = 0; i < dataSize_; i++)
      {
	denE = 1 + (sigmaE(0,i)*deltaT)/(2*epsilon0*epsR(0,i));
	Ca(0,i) = 1 - (sigmaE(0,i) * deltaT)/(2*epsilon0*epsR(0,i))/denE;
	Cb(0,i) = deltaT/(epsilon0*epsR(0,i)*deltaZ)/denE;

	denH = 1 + sigmaH(0,i)*deltaT/(2*mu0*muR(0,i));
	Da(0,i) = (1 - sigmaH(0,i)*deltaT/(2*mu0*muR(0,i)))/denH;
	Db(0,i) = (deltaT/(mu0*muR(0,i)*deltaZ))/denH;

      }
  }

  Eigen::MatrixXd FDTD_1D::getEpsR(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd epsR;
    
    if (input->getDielectricSpecification() == "File")
      {
	//epsR = HDF5IO::ReadMatrixFromFile(input->getDielectricFileName(),input->getDielectricDatasetName());

	//check the size
        if(epsR.cols() != dataSize_)
	  {
	    std::string eString = "FDTD_1D::getEpsR ... Dielectric read in from file invalid size: " + std::to_string(epsR.cols()) + " should be: " + std::to_string( dataSize_);
            throw std::runtime_error(eString);
	  }
      }
    else if (input->getDielectricSpecification() == "Constant")
      {
        epsR.resize(1,dataSize_);
	for (int i = 0; i < epsR.cols();i++)
	  epsR(0,i) = input->getDielectricConstant();
      }

    return epsR;

  }

  
  Eigen::MatrixXd FDTD_1D::getMuR(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd muR(1,dataSize_);

    for(int i = 0; i < dataSize_; i++)
      muR(0,i) =1;
    
    return muR;
  }
  
  Eigen::MatrixXd FDTD_1D::getSigmaH(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd sigmaH(1,dataSize_);

    for(int i = 0; i < dataSize_; i++)
      sigmaH(0,i) = 0;
    
    return sigmaH;
  }

    Eigen::MatrixXd FDTD_1D::getSigmaE(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd sigmaE(1,dataSize_);

    for(int i = 0; i < dataSize_; i++)
      sigmaE(0,i) = 0;
   
    return sigmaE;
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
      E(0,mm) = Ca(0,mm) * E(0,mm) + Cb(0,mm)*(H(0,mm - 1) - H(0,mm));

      //update the source
    E(0,sourceIndex_) -= source->getInputSource(time,0.0);
    
    //update the H Field
    for (int mm = 0; mm < dataSize_ - 1; mm++)
      H(0,mm) = Da(0,mm)*H(0,mm) + Db(0,mm)*(E(0,mm) - E(0,mm + 1));

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
      return E(0,index);
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
      return H(0,index);
    else
      return 0;
  }

  void FDTD_1D::simpleABC_E()
  {
    E(0,0) = E(0,1);
  }

  void FDTD_1D::simpleABC_H()
  {
    H(0,dataSize_-1) = H(0,dataSize_-2);
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
