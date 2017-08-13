/**
* @file FDTD_1D.cpp
* @brief Implementation of the FDTD_1D class *
* @author Ben Frazier*
* @date 08/12/2017 */

#include "FDTD_1D.h"
#include <math.h>

/** \brief FDTD_1D Constructor
 *
 *  Standard Constructor
 */
FDTD_1D::FDTD_1D():initialized(false)
{
  imp = 377.0;
  dataSize = 0;
}


/**
* \brief Initialize the FDTD_1D engine
*
* This function sets the size of the E and H vectors
* @param x The size along the X-dimension
* @param y The size along the Y-dimension
* @param z The size along the Z-dimension */

void FDTD_1D::InitializeEngine(int x, int y, int z)
{
  dataSize = x;
  H.resize(dataSize);
  E.resize(dataSize);

  initialized = true;
}

/**
* \brief Update the E and H fields
*
* This function updates the E and H fields by stepping to the specified time index
* @param time The next time step to update*/
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

/**
* \brief Return the E field at a specified index
*
* This function gets the E field at a given index and returns 0 if the requested
* index exceeds the size of the array
* @param index The index of the E field to retrieve*/
double FDTD_1D::getEField(int index)
{
  if (index < dataSize)
     return E[index];
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
  if (index < dataSize)
     return H[index];
  else
    return 0;
}
