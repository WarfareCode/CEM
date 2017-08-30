/**
* @file SimManager.cpp
* @brief Implementation of the Simulation Manager class
* @author Ben Frazier
* @date 08/14/2017 */
#include "SimManager.h"

namespace CEM
{
//****************************************************************************************
/*
* @brief Constructor with a file name
* @param inputFileName Name of the file to read as input
* @param outputFileName Name of the file to be output
**/
SimManager::SimManager(std::string inputFileName, std::string outputFileName)
{
  //need to find the input file in the various paths
  inputFileName = CEM::FILE::FindInputFile(inputFileName);

  //get the shared pointer to the input parser
  ip_ = std::make_shared<InputParser>();
     
  //Read the input file and get the interfaces
  ip_->ReadInputFile(inputFileName);
  input_ = ip_->getInputData();

  //Log out the input data
  std::cout<<*input_ << std::endl;

  //create the pointers from the factories
  source_ptr_ = sourceFactory_.createSourceControl(input_);
  std::cout<<"Creating FDTD" << std::endl;
  compute_ptr_ = computeFactory_.createComputationalEngine(input_);
  std::cout<<"done ... " << std::endl;
  dLogger_ptr_ = dlFactory_.createDataLogger(input_);

  //get the unique pointer to the simulation engine
  engine_ptr_ = createSimEngine();
  time_ptr_ = std::make_shared<TimeControl> (input_);
}

//****************************************************************************************
/*
* @brief Initialize all the submodules
**/
void SimManager::Initialize()
{
  dLogger_ptr_->InitializeDataLogger(input_);

}
 

//****************************************************************************************
/**
* @brief Create the Simulation Engine
*
* @param input input data structure
**/
  std::unique_ptr<SimEngine>SimManager::createSimEngine()
  {
    std::unique_ptr<SimEngine> simengine (new SimEngine());
    return simengine;
  }

  //****************************************************************************************
/**
* @brief Update members
*
**/

  void SimManager::Update()
  {
    engine_ptr_->Update(time_ptr_, compute_ptr_, dLogger_ptr_, source_ptr_);
    time_ptr_->Update();
  }
  
//****************************************************************************************
/**
* @brief Run the simulation
*
**/
int SimManager::Run()
{
  try
    {

      while(time_ptr_->simComplete() == false)
	{
	  Update();
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
