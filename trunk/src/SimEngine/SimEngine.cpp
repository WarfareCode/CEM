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
    //Read the input file and get the Input Data interface
    ip_.ReadInputFile(inputFileName);
    input_ = ip_.getInputData();

    dataLogTime_ = 1/input_->getOutputDataRate();
    timeSinceLastDataLogged_ = dataLogTime_; //force a write on start
    previousTime_ = 0;

    std::cout<< *input_ << std::endl;

    //create the pointers to the FDTD engine and the data logger
    fdtd_ptr_ = fdtdFactory_.createComputationalEngine(input_);
    dLogger_ptr_ = dlFactory_.createDataLogger(input_);
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

	if (timeSinceLastDataLogged_ >= dataLogTime_)
	  {
	    dLogger_ptr_->WriteDataArray(fdtd_ptr_->getEField(),time,"/EField");
	    timeSinceLastDataLogged_ = 0;
	  }
	else
	  timeSinceLastDataLogged_ += time - previousTime_;

	 previousTime_ = time;
      }
  }
}//end namespace CEM

