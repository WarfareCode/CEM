/**
* @file InputData.h
* @brief Header File for the InputData Class
* @details This file stores the information read in from the input file
* @author Ben Frazier
* @date 08/14/2017 */

#ifndef INPUT_DATA_H
#define INPUT_DATA_H

namespace CEM
{
  class InputData
  {
  public:
    InputData();
    
    //get functions
    std::string getFileName(){return fileName_;};
    std::string getComputationType(){return computationType_;};
    std::string getAbsorbingBoundaryCondition(){return absorbingBoundaryCondition_;};
    double getStopTime(){return stopTime_;};
    double getStartTime(){return startTime_;};
    int getVectorLength(){return vectorLength_;};
    int getSourceIndex(){return sourceIndex_;};

    //set functions
    void setFileName(std::string fName){fileName_ = fName;};
    void setComputationType(std::string cType){computationType_ = cType;};
    void setAbsorbingBoundaryCondition(std::string abc){absorbingBoundaryCondition_ = abc;};
    void setStopTime(double sTime){stopTime_ = sTime;};
    void setStartTime(double sTime){startTime_ = sTime;};
    void setVectorLength(int vLength){vectorLength_ = vLength;};
    void setSourceIndex(int sIndex){sourceIndex_ = sIndex;}; 
    

   private:
    std::string fileName_;                    /*!< Input file name that was read from*/
    std::string computationType_;             /*!< String containing the computation type to run (FDTD_1D, etc.)*/
    double startTime_;                        /*!< Start time for the simulation*/
    double stopTime_;                         /*!< Stop time for the simulation*/
    std::string absorbingBoundaryCondition_;  /*!< String containing the type of absorbing boundary condition to use (Simple, None, etc.)*/
    int vectorLength_;                        /*!< Variable for the length (number of points) for each spatial vector*/
    int sourceIndex_;                        /*!< Index at which to apply the E-field source*/
  };


  //Overloaded << Operator
 inline std::ostream& operator<<(std::ostream& os, InputData& input)  
 {  

   os << "FileName: " << input.getFileName() << std::endl;
   os << "Computation Type: " << input.getComputationType() << std::endl;
   os << "Start Time: " << input.getStartTime() << std::endl;
   os << "Stop Time: " << input.getStopTime() << std::endl;
   os << "Absorbing Boundary Condition: " << input.getAbsorbingBoundaryCondition()<< std::endl;
   os << "Vector Length: " << input.getVectorLength() << std::endl;
   os << "Source Index: " << input.getSourceIndex() << std::endl;

  return os;  
  }
}

#endif
