#ifndef FDTD_1D_H
#define FDTD_1D_H

#include <iostream>
#include <vector>
#include "AbsFDTD.h"

class FDTD_1D: public AbsFDTD
{
	public:
	FDTD_1D();
	~FDTD_1D();
	virtual void InitializeEngine(int x, int y, int z);
	virtual void UpdateFields(double time);
	void SetEFieldSource(int index, double time);

	double * getEField();

	private:
	char HDirection, EDirection;
	double *H, *E;

	double imp;
	int dataSize;

};

#endif