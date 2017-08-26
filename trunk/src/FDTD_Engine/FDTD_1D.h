/**
* @file FDTD_1D.h
* @brief Header File for the FDTD_1D class
* @author Ben Frazier
* @todo add various options for absorbing boundary conditions and interfaces
* @date 08/12/2017 */

#ifndef FDTD_1D_H
#define FDTD_1D_H

#include <iostream>
#include <vector>
#include "ComputeEngineInterface.h"
#include "InputDataInterface.h"
#include "GridDefinitionInterface.h"
#include "SourceControlInterface.h"
#include "CEMCommon.h"

namespace CEM
{
  class InputData;
  
  class FDTD_1D: public ComputeEngineInterface
  {
  public:
    FDTD_1D(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition);

    virtual void UpdateFields(double time, std::shared_ptr<SourceControlInterface> source);
    virtual double getEField(int index);
    virtual double getHField(int index);
    virtual Eigen::VectorXd getEField() {return E;}
    virtual Eigen::VectorXd getHField() {return H;}
    
    //get functions
    AbsorbingBoundaryCondition getABC(){return ABC;};

  private:
    char HDirection, EDirection;

    Eigen::VectorXd E;/*!< Electric Field Vector */
    Eigen::VectorXd H;/*!< Magnetic Field Vector */

    std::vector<double> dielectricConstant_;  /*!<Dielectric Constant Vector */
    double imp_; /*!< Impedance Vector */
    int dataSize_;  /*!< Length of the E and H vectors*/
    
    int sourceIndex_;  /*!< Spatial index where the source is applied*/

    bool initialized;
    AbsorbingBoundaryCondition ABC; /*!< Selection to use for absorbing boundary condition */

    void simpleABC_E();
    void simpleABC_H();

    void applyBC_E();
    void applyBC_H();

    void InitializeEngine(std::shared_ptr<InputDataInterface>input, std::shared_ptr<GridDefinitionInterface> gridDefinition);
    void InitializeDielectric(std::shared_ptr<InputDataInterface>input, std::shared_ptr<GridDefinitionInterface> gridDefinition);

    
  };
}

#endif
