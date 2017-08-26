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
  SimEngine::SimEngine(std::shared_ptr<InputDataInterface> input)
  {
    dataLogTime_ = 1/input->getOutputDataRate();
    timeSinceLastDataLogged_ = dataLogTime_; //force a write on start
    previousTime_ = 0;
  }

    
  /**
   * @brief Update the simulation
   *
   **/
  void SimEngine::Update(double time, std::shared_ptr<ComputeEngineInterface> compute, std::shared_ptr<DataLoggerInterface> dlogger, std::shared_ptr<SourceControlInterface> source)
  {
    compute->UpdateFields(time, source);

    if (timeSinceLastDataLogged_ >= dataLogTime_)
    {
      dlogger->WriteDataArray(compute->getEField(),time,"/EField");
      timeSinceLastDataLogged_ = 0;
    }
    else
      timeSinceLastDataLogged_ += time - previousTime_;

   previousTime_ = time;
 }

}//end namespace CEM

