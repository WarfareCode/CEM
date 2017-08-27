/**
* @file TimeControlInterface.h
* @brief Abstract virtual class for the TimeControl class, defines the interface
* @author Ben Frazier
* @date 08/27/2017 */

#ifndef TIME_CONTROL_INTERFACE_H
#define TIME_CONTROL_INTERFACE_H


namespace CEM
{
  class TimeControlInterface
  {
  public:
    virtual double getCurrentTime()=0;
    virtual double getNextTimeStep()=0;
    virtual bool timeToLogData() = 0;
    virtual void Update() = 0;
    virtual bool simComplete()=0;
  };

}//end namespace CEM

#endif
