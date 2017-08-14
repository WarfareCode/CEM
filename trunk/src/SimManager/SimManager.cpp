/**
* @file SimManager.cpp
* @brief Implementation of the Simulation Manager class *
* @author Ben Frazier*
* @date 08/14/2017 */
#include "SimManager.h"

/**
* @brief Default Constructor
*
**/
SimManager::SimManager()
{
}

/**
* @brief Constructor with a file name
*
* @param fileName Name of the file to read as input
**/
SimManager::SimManager(std::string inputFileName, std::string outputFileName)
{
   ipError_ = ip_.ReadInputFile(inputFileName);
   ipError_ = ip_.GetInputStruct(input_);

   fdtd_.InitializeEngine(input_);
   
   dLogger_.CreateFile(outputFileName);
}

/**
* @brief Run the simulation
*
**/
void SimManager::Run()
{

for(int time = input_.startTime_; time < input_.stopTime_; time++)
  {
    fdtd_.UpdateFields(time);
    fdtd_.SetEFieldSource(0,time);
    dLogger_.WriteDataArray(fdtd_.getEField());   
  }
}

