/**
* @file FDTDBase.cpp
* @brief Implementation of the FDTDBase class
* @author Ben Frazier
* @date 08/12/2017 */

#include "FDTDBase.h"
#include <math.h>
#include "CEMCommon.h"

namespace CEM
{

 /** \brief FDTDBase Overloaded Constructor
 *
 *  Standard Constructor
 * @param input The input data structure
 * @param gridDefinition The input definition of the grid
 */
  FDTDBase::FDTDBase(std::shared_ptr<InputDataInterface> input):
    ABC(SimpleABC),
    dataSize_(0)
  {
    InitializeEngine(input);
  }

  /**
   * \brief Initialize the FDTDBase engine
   *
   * This function sets the size of the E and H vectors
   * @param input The input structure read in from the input file
   * @param gridDefinition The input definition of the grid*/
  void FDTDBase::InitializeEngine(std::shared_ptr<InputDataInterface> input)
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

  void FDTDBase::computeConstants(std::shared_ptr<InputDataInterface> input)
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
	Cb(0,i) = deltaT/(epsilon0*epsR(1,i)*deltaZ)/denE;

	denH = 1 + sigmaH(0,i)*deltaT/(2*mu0*muR(0,i));
	Da(0,i) = (1 - sigmaH(0,i)*deltaT/(2*mu0*muR(0,i)))/denH;
	Db(0,i) = (deltaT/(mu0*muR(0,i)*deltaZ))/denH;

      }
	 
  }

  Eigen::MatrixXd FDTDBase::getEpsR(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd epsR;
    
    if (input->getDielectricSpecification() == "File")
      {
	//epsR = HDF5IO::ReadMatrixFromFile(input->getDielectricFileName(),input->getDielectricDatasetName());

	//check the size
        if(epsR.size() != dataSize_)
	  {
	    std::string eString = "FDTD_Base::Initialize Dielectric ... Dielectric read in from file invalid size: " + std::to_string(epsR.size()) + " should be: " + std::to_string( dataSize_);
            throw std::runtime_error(eString);
	  }
      }
    else if (input->getDielectricSpecification() == "Constant")
      {
        epsR.resize(1,dataSize_);
	for (int i = 0; i < epsR.cols();i++)
	  epsR(1,i) = input->getDielectricConstant();
      }

    return epsR;

  }

  
  Eigen::MatrixXd FDTDBase::getMuR(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd muR(1,dataSize_);

    for(int i = 0; i < dataSize_; i++)
      muR(1,i) =1;
    
    return muR;
  }
  
  Eigen::MatrixXd FDTDBase::getSigmaH(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd sigmaH(1,dataSize_);

    for(int i = 0; i < dataSize_; i++)
      sigmaH(1,i) = 0;
    
    return sigmaH;
  }

    Eigen::MatrixXd FDTDBase::getSigmaE(std::shared_ptr<InputDataInterface> input)
  {

    Eigen::MatrixXd sigmaE(1,dataSize_);

    for(int i = 0; i < dataSize_; i++)
      sigmaE(1,i) = 0;
    
    return sigmaE;
  }

  /**
   * \brief Update the E and H fields
   *
   * This function updates the E and H fields by stepping to the specified time index
   * @param time The next time step to update
   * @param source The Source Control*/
  void FDTDBase::UpdateFields(double time, std::shared_ptr<SourceControlInterface> source)
  {
 
    /*  //Now update the E Field
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
    //applyBC_H();*/
  
  }

  /**
   * \brief Return the E field at a specified index
   *
   * This function gets the E field at a given index and returns 0 if the requested
   * index exceeds the size of the array
   * @param index The index of the E field to retrieve*/
  double FDTDBase::getEField(int index)
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
  double FDTDBase::getHField(int index)
  {
    if (index < dataSize_)
      return H(0,index);
    else
      return 0;
  }

  void FDTDBase::simpleABC_E()
  {
    E(0,0) = E(0,1);
  }

  void FDTDBase::simpleABC_H()
  {
    H(0,dataSize_-1) = H(0,dataSize_-2);
  }


  void FDTDBase::applyBC_E()
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

  void FDTDBase::applyBC_H()
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
