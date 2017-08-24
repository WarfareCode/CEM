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
     
  //Read the input file and get the Input Data interface
  ip_->ReadInputFile(inputFileName);
  input_ = ip_->getInputData();

  engine_ = new SimEngine(input_);
}
  

/**
* @brief Run the simulation
*
**/
int SimManager::Run()
{
  try
    {
      engine_->Run();
       
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
