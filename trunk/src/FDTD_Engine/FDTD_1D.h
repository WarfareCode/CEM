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
#include "FDTDInterface.h"
#include "InputDataInterface.h"

namespace CEM
{
  class InputData;
  
  class FDTD_1D: public FDTDInterface
  {
  public:
    FDTD_1D(InputDataInterface* input);

    virtual void UpdateFields(double time);
    virtual std::vector<double> getEField(){return E;};
    virtual double getEField(int index);
    virtual std::vector<double> getHField(){return H;};
    virtual double getHField(int index);
    virtual int getDataSize(){return dataSize_;};
    virtual double getImpedance(){return imp;};
    
    //get functions
    AbsorbingBoundaryCondition getABC(){return ABC;};

  private:
    char HDirection, EDirection;

    std::vector<double> E; /*!< Electric Field Vector */
    std::vector<double> H; /*!< Magnetic Field Vector */
    double imp; /*!< Impedance Vector */
    int dataSize_;
    int sourceIndex_;

    double sourceAmplitude_;
    std::string sourceType_;
    double pulseWidth_;
    double pulseWidth2_;
    double sourceDelay_;

    bool initialized;
    AbsorbingBoundaryCondition ABC; /*!< Selection to use for absorbing boundary condition */

    void simpleABC_E();
    void simpleABC_H();

    void applyBC_E();
    void applyBC_H();

    void InitializeEngine(InputDataInterface * input);
    
    void SetEFieldSource(int index, double time);
    void SetEFieldSource(double time);

  };
}

#endif
