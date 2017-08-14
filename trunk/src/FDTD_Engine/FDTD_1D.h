/**
* @file FDTD_1D.h
* @brief Header File for the FDTD_1D class *
* @author Ben Frazier*
* @date 08/12/2017 */

#ifndef FDTD_1D_H
#define FDTD_1D_H

#include <iostream>
#include <vector>
#include "FDTDInterface.h"

struct InputStruct;

class FDTD_1D: public FDTDInterface
{
	public:
	FDTD_1D();

	virtual void InitializeEngine(InputStruct input);
	virtual void UpdateFields(double time);
	void SetEFieldSource(int index, double time);

        virtual std::vector<double> getEField(){return E;};
	virtual double getEField(int index);
	virtual std::vector<double> getHField(){return H;};

	virtual double getHField(int index);

	virtual int getDataSize(){return dataSize;};
	virtual double getImpedance(){return imp;};

	AbsorbingBoundaryCondition getABC(){return ABC;};

	private:
	char HDirection, EDirection;

	std::vector<double> E; /*!< Electric Field Vector */
	std::vector<double> H; /*!< Magnetic Field Vector */
	double imp; /*!< Impedance Vector */
	int dataSize;

	bool initialized;
	AbsorbingBoundaryCondition ABC; /*!< Selection to use for absorbing boundary condition */

	void simpleABC_E();
	void simpleABC_H();

	void applyBC_E();
	void applyBC_H();

        void InitializeEngine();

};

#endif
