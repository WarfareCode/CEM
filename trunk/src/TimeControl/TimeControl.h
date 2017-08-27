/**
* @file TimeControl.h
* @brief Header File for the Time Control class 
* @author Ben Frazier
* @date 08/27/2017 */

#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H

#include "InputDataInterface.h"
#include "TimeControlInterface.h"

namespace CEM
{
  class TimeControl:public TimeControlInterface
  {
  public:
    
    TimeControl(std::shared_ptr<InputDataInterface> input);

    virtual double getCurrentTime(){return currentTime_;}
    virtual double getNextTimeStep(){return nextTime_;}
    virtual bool timeToLogData(){return timeToLogData_;}
    virtual void Update();
    virtual bool simComplete(){return simComplete_;}


  private:
    //member functions
    double currentTime_;
    double nextTime_;
    bool timeToLogData_;
    bool logEveryFrame_;

    double initialTime_;
    double finalTime_;

    double timeStep_;

    bool simComplete_;
    double dataLogTime_;
    
    double timeSinceLastDataLogged_;
    double previousTime_;

  };
}

#endif
