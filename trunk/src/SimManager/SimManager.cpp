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
* @param fileName Name of the file to read as input
**/
SimManager::SimManager(std::string inputFileName, std::string outputFileName)
{
  ip_ = std::make_shared<InputParserYAML>();
     
  //Read the input file and get the interfaces
  ip_->ReadInputFile(inputFileName);
  input_ = ip_->getInputData();
  gridDefinition_ = ip_->getGridDefinition();
  sourceDefinition_ = ip_->getSourceDefinition();

  //create the pointers from the factories
  source_ptr_ = sourceFactory_.createSourceControl(sourceDefinition_);
  compute_ptr_ = computeFactory_.createComputationalEngine(input_, gridDefinition_);
  dLogger_ptr_ = dlFactory_.createDataLogger(input_, gridDefinition_);

  //get the unique pointer to the simulation engine
  engine_ptr_ = createSimEngine(input_);

  timeIncrement_ = 1/input_->getTemporalSamplingRate();

  std::cout<<*input_ << *gridDefinition_ << *sourceDefinition_<< std::endl;

}
  
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

      double printTime = 0.25;
      double timeSinceLastPrint = 0;
      
      while (!done)
	{
         engine_ptr_->Update(time, compute_ptr_, dLogger_ptr_, source_ptr_);
	 time += timeIncrement_;
	 timeSinceLastPrint +=timeIncrement_;

	 if (timeSinceLastPrint >= printTime)
	   {
	     std::cout<<"Time: " << time << std::endl;
	     timeSinceLastPrint = 0;
	   }

	 if (time >= input_->getStopTime())
	   done = true;
	 
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
