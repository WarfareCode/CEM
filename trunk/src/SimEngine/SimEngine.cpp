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
   * @param input Pointer to the input data structure
   **/
  SimEngine::SimEngine(std::shared_ptr<InputDataInterface> input)
  {
    input_ = input;
    dataLogTime_ = 1/input_->getOutputDataRate();
    timeSinceLastDataLogged_ = dataLogTime_; //force a write on start
    previousTime_ = 0;

    std::cout<< *input_ << std::endl;

    //create the pointers to the FDTD engine and the data logger
    engine_ptr_ = computeFactory_.createComputationalEngine(input_);
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
	engine_ptr_->UpdateFields(time);

	if (timeSinceLastDataLogged_ >= dataLogTime_)
	  {
	    dLogger_ptr_->WriteDataArray(engine_ptr_->getEField(),time,"/EField");
	    timeSinceLastDataLogged_ = 0;
	  }
	else
	  timeSinceLastDataLogged_ += time - previousTime_;

	 previousTime_ = time;
      }
  }
}//end namespace CEM

