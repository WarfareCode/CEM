#include "FDTD_1D.h"
#include <math.h>

FDTD_1D::FDTD_1D()
{
  imp = 377.0;
  dataSize = 0;
}

FDTD_1D::~FDTD_1D()
{
 //delete [] H;
 //delete [] E;
}

void FDTD_1D::InitializeEngine(int x, int y, int z)
{
  dataSize = x;
  H = new double[dataSize];
  E = new double[dataSize];
}

void FDTD_1D::UpdateFields(double time)
{

//update the H Field
 for (int mm = 0; mm < dataSize - 1; mm++)
   H[mm] = H[mm] + (E[mm + 1] - E[mm]) / imp;
   
   //Now update the E Field
for (int mm = 1; mm < dataSize; mm++)
	E[mm] = E[mm] + (H[mm] - H[mm - 1]) * imp;
}

void FDTD_1D::SetEFieldSource(int index, double time)
{
  E[index] = exp(-(time - 30.) * (time - 30.) / 100.);
}

double FDTD_1D::getEField(int index)
{
  if (index < dataSize)
     return E[index];
  else
    return 0;
}

double FDTD_1D::getHField(int index)
{
  if (index < dataSize)
     return H[index];
  else
    return 0;
}
