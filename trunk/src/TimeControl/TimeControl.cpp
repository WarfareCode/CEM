/**
* @file TimeControl.cpp
* @brief Implementation of the Time Control class 
* @author Ben Frazier
* @date 08/27/2017 */

#include "TimeControl.h"

namespace CEM
{
   //********************************************************************************************
  /**
   * \brief Standard Constructor
   *
   */
  TimeControl::TimeControl(std::shared_ptr<InputDataInterface> input)
  {
    initialTime_ = input->getStartTime();
    finalTime_ = input->getStopTime();

    timeStep_ = input->getTimeStep();

    simComplete_ = false;

    timeToLogData_ = false;

    currentTime_ = initialTime_;
    nextTime_ = currentTime_ + timeStep_;

    dataLogTime_ = input->getOutputDataRate();
     if(dataLogTime_ == -1)
      logEveryFrame_ = true;
    else
      logEveryFrame_ = false;
    
    timeSinceLastDataLogged_ = dataLogTime_; //force a write on start
    previousTime_ = 0;
    
  }

     //********************************************************************************************
  /**
   * \brief Update the time controller
   *
   */
  void TimeControl::Update()
  {
    previousTime_ = currentTime_;
    currentTime_ = nextTime_;
    nextTime_ += timeStep_;

    if (logEveryFrame_ || timeSinceLastDataLogged_ >= dataLogTime_)
    {
      timeToLogData_ = true;
    }
    else
    {
      timeToLogData_ = false;
      timeSinceLastDataLogged_ += currentTime_ - previousTime_;
    }

    if (currentTime_ >= finalTime_)
      simComplete_ = true;

    
  }
} //end namespace CEM
