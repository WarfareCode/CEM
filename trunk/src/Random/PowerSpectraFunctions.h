/**
* @file PowerSpectraFunctions.h
* @brief Collection of Functions to generate Power Spectra
* @author Ben Frazier
* @date 02/19/2018 */

#include <vector>
#include <math.h>

namespace RandomVector
{
  std::vector<double> Elfouhaily(std::vector<double> k, double U10, double age, double phi);

}