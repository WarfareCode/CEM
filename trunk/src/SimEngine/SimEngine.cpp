/**
* @file SimEngine.cpp
* @brief Implementation of the Simulation Engine class
* @author Ben Frazier*
* @date 08/15/2017 */
#include "SimEngine.h"

namespace CEM
{
  /**
   * @brief Constructor with file names
   *
   * @param input Pointer to the input data structure
   **/
  SimEngine::SimEngine(std::shared_ptr<InputDataInterface> input):
    initialized_(false)
  {
    input_ = input;
    dataLogTime_ = 1/input_->getOutputDataRate();
    timeSinceLastDataLogged_ = dataLogTime_; //force a write on start
    previousTime_ = 0;
  }

  void SimEngine::Initialize(std::shared_ptr<ComputeEngineInterface> compute, std::shared_ptr<DataLoggerInterface> dlogger)
  {

    compute_ptr_ = compute;
    dLogger_ptr_ = dlogger;
    
    initialized_ = true;
  }
  
  /**
   * @brief Run the simulation
   *
   **/
  void SimEngine::Run()
  {

    if (!initialized_)
      throw std::runtime_error("SimEngine::Run ... Simulation Engine has not been initialized");
 
    for(int time = input_->getStartTime(); time < input_->getStopTime(); time++)
      {
	compute_ptr_->UpdateFields(time);

	if (timeSinceLastDataLogged_ >= dataLogTime_)
	  {
	    dLogger_ptr_->WriteDataArray(compute_ptr_->getEField(),time,"/EField");
	    timeSinceLastDataLogged_ = 0;
	  }
	else
	  timeSinceLastDataLogged_ += time - previousTime_;

	 previousTime_ = time;
      }
  }
}//end namespace CEM

