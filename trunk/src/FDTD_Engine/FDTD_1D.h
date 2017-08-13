/**
* @file FDTD_1D.h
* @brief Header File for the FDTD_1D class *
* @author Ben Frazier*
* @date 08/12/2017 */

#ifndef FDTD_1D_H
#define FDTD_1D_H

#include <iostream>
#include <vector>
#include "AbsFDTD.h"

class FDTD_1D: public AbsFDTD
{
	public:
	FDTD_1D();

	virtual void InitializeEngine(int x, int y, int z);
	virtual void UpdateFields(double time);
	void SetEFieldSource(int index, double time);

        virtual std::vector<double> getEField(){return E;};
	virtual double getEField(int index);
	virtual std::vector<double> getHField(){return H;};

	virtual double getHField(int index);

	virtual int getDataSize(){return dataSize;};
	virtual double getImpedance(){return imp;};

	private:
	char HDirection, EDirection;

	std::vector<double> E; /*!< Electric Field Vector */
	std::vector<double> H; /*!< Magnetic Field Vector */
	double imp; /*!< Impedance Vector */
	int dataSize;

	bool initialized;

};

#endif
