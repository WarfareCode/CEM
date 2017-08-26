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
#include "CEMCommon.h"

namespace CEM
{
  class InputData;
  
  class FDTD_1D: public ComputeEngineInterface
  {
  public:
    FDTD_1D(std::shared_ptr<InputDataInterface> input, std::shared_ptr<GridDefinitionInterface> gridDefinition);

    virtual void UpdateFields(double time, std::shared_ptr<SourceControlInterface> source);
    virtual std::vector<double> getEField(){return E;};
    virtual double getEField(int index);
    virtual std::vector<double> getHField(){return H;};
    virtual double getHField(int index);
    
    //get functions
    AbsorbingBoundaryCondition getABC(){return ABC;};

  private:
    char HDirection, EDirection;

    std::vector<double> E; /*!< Electric Field Vector */
    std::vector<double> H; /*!< Magnetic Field Vector */
    std::vector<double> dielectricConstant_;  /*!<Dielectric Constant Vector */
    double imp_; /*!< Impedance Vector */
    int dataSize_;  /*!< Length of the E and H vectors*/
    
    int sourceIndex_;  /*!< Spatial index where the source is applied*/
    double sourceAmplitude_;  /*!< Amplitude of the source*/
    std::string sourceType_;  /*!< Type of the source*/
    double pulseWidth_;  /*!< Pulsewidth of the source*/
    double pulseWidth2_;  /*!< Pulsewidth squared of the source*/
    double sourceDelay_;  /*!< Time delay of the source*/

    bool initialized;
    AbsorbingBoundaryCondition ABC; /*!< Selection to use for absorbing boundary condition */

    void simpleABC_E();
    void simpleABC_H();

    void applyBC_E();
    void applyBC_H();

    void InitializeEngine(std::shared_ptr<InputDataInterface>input, std::shared_ptr<GridDefinitionInterface> gridDefinition);
    void InitializeSource(std::shared_ptr<InputDataInterface>input);
    void InitializeDielectric(std::shared_ptr<InputDataInterface>input, std::shared_ptr<GridDefinitionInterface> gridDefinition);
   
    double computeSourceAmplitude(double time, double shift);
    

  };
}

#endif
