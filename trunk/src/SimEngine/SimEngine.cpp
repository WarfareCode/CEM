/**
* @file SimEngine.cpp
* @brief Implementation of the Simulation Engine class *
* @author Ben Frazier*
* @date 08/15/2017 */
#include "SimEngine.h"
namespace CEM
{
  /**
   * @brief Constructor with file names
   *
   * @param inputFileName Name of the file to read as input
   * @param outputFileName Name of the file to be created as output
   **/
  SimEngine::SimEngine(std::string inputFileName, std::string outputFileName)
  {
    ipError_ = ip_.ReadInputFile(inputFileName);
    input_ = ip_.getInputData();
   
    fdtd_ptr_ = fdtdFactory_.createComputationalEngine(input_);

    dLogger_ptr_ = dlFactory_.createDataLogger(input_);
    dLogger_ptr_->CreateFile(outputFileName);
    dLogger_ptr_->WriteDataHeader(input_);
  }

  /**
   * @brief Run the simulation
   *
   **/
  void SimEngine::Run()
  {

    for(int time = input_->getStartTime(); time < input_->getStopTime(); time++)
      {
	fdtd_ptr_->UpdateFields(time);
	dLogger_ptr_->WriteDataArray(fdtd_ptr_->getEField());   
      }
  }
}//end namespace CEM

