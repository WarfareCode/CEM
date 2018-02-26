/**
* @file FDTDBase.h
* @brief Header File for the FDTD  base class
* @author Ben Frazier
* @todo add various options for absorbing boundary conditions and interfaces
* @date 08/27/2017 */

#ifndef FDTD_BASE_H
#define FDTD_BASE_H

#include <iostream>
#include <vector>
#include "ComputeEngineInterface.h"
#include "InputDataInterface.h"
#include "SourceControlInterface.h"
#include "CEMCommon.h"

namespace CEM
{
  class InputData;
  
  class FDTDBase: public ComputeEngineInterface
  {
  public:
    FDTDBase(std::shared_ptr<InputDataInterface> input);

    virtual void UpdateFields(double time, std::shared_ptr<SourceControlInterface> source);
    virtual double getEField(int index);
    virtual double getHField(int index);
    virtual Eigen::MatrixXd getEField()=0;
    virtual Eigen::MatrixXd getHField()=0;
    
  private:
    char HDirection, EDirection;

    Eigen::MatrixXd E;/*!< Electric Field Vector */
    Eigen::MatrixXd H;/*!< Magnetic Field Vector */
    Eigen::MatrixXd Ca, Cb, Da, Db;
    
    int dataSize_;  /*!< Length of the E and H vectors*/
    
    int sourceIndex_;  /*!< Spatial index where the source is applied*/

    ABC::AbsorbingBoundaryCondition ABC; /*!< Selection to use for absorbing boundary condition */

    void simpleABC_E();
    void simpleABC_H();

    void applyBC_E();
    void applyBC_H();

    void InitializeEngine(std::shared_ptr<InputDataInterface>input);
    void computeConstants(std::shared_ptr<InputDataInterface> input);
    Eigen::MatrixXd getSigmaE(std::shared_ptr<InputDataInterface> input);
    Eigen::MatrixXd getSigmaH(std::shared_ptr<InputDataInterface> input);
    Eigen::MatrixXd getEpsR(std::shared_ptr<InputDataInterface> input);
    Eigen::MatrixXd getMuR(std::shared_ptr<InputDataInterface> input);

    
  };
}

#endif
