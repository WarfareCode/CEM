/**
* @file SimManager.cpp
* @brief Implementation of the Simulation Manager class
* @author Ben Frazier
* @date 08/14/2017 */
#include "SimManager.h"

namespace CEM
{
/**
* @brief Constructor with a file name
*
* @param inputFileName Name of the file to read as input
* @param outputFileName Name of the file to be output
**/
SimManager::SimManager(std::string inputFileName, std::string outputFileName)
{
  inputFileName = CEM::FILE::FindInputFile(inputFileName);

  ip_ = std::make_shared<InputParser>();
     
  //Read the input file and get the interfaces
  ip_->ReadInputFile(inputFileName);
  input_ = ip_->getInputData();


  std::cout<<*input_ << std::endl;

  //create the pointers from the factories
  source_ptr_ = sourceFactory_.createSourceControl(input_);
  compute_ptr_ = computeFactory_.createComputationalEngine(input_);
  dLogger_ptr_ = dlFactory_.createDataLogger(input_);

  //get the unique pointer to the simulation engine
  engine_ptr_ = createSimEngine(input_);

  timeIncrement_ = input_->getTimeStep();  

}

 /**
* @brief Create the Simulation Engine
*
* @param input input data structure
**/
  std::unique_ptr<SimEngine>SimManager::createSimEngine(std::shared_ptr<InputDataInterface> input)
  {
    std::unique_ptr<SimEngine> simengine (new SimEngine(input));
    return simengine;
  }

/**
* @brief Run the simulation
*
**/
int SimManager::Run()
{
  try
    {
      bool done = false;
      double time = input_->getStartTime();

      int start = std::floor(time/input_->getTimeStep());
      int stop = std::round(input_->getStopTime()/input_->getTimeStep());
      for(int n = start; n < stop; n++)
	{
         engine_ptr_->Update(time, compute_ptr_, dLogger_ptr_, source_ptr_);
	 time += input_->getTimeStep();
        }
       
    }  // end of try block
    
    // catch failure caused by the H5File operations
    catch( FileIException error )
    {
        error.printError();
        return -1;
    }
    
    // catch failure caused by the DataSet operations
    catch( DataSetIException error )
    {
        error.printError();
        return -1;
    }
    
    // catch failure caused by the DataSpace operations
    catch( DataSpaceIException error )
    {
        error.printError();
        return -1;
    }
    
    // catch failure caused by the DataSpace operations
    catch( DataTypeIException error )
    {
        error.printError();
        return -1;
    }

    catch (std::runtime_error &error)
      {
	error.what();
	return -1;
      }

  return 0;

}

}//end namespace CEM
