/**
* @file main.cpp
* @brief main executable *
* @author Ben Frazier*
* @date 08/14/2017 */

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#define PRINT_WORKING_DIRECTORY
#ifdef PRINT_WORKING_DIRECTORY
#include <unistd.h>
#endif

#include <string>
#include "SimManager/SimManager.h"

int main (int argc, char *argv[])
{

  std::string inputFileName;
  std::string outputFileName;

  //check the inputs
  if (argc == 3)
    {
      inputFileName = argv[1];
      outputFileName = argv[2];
    }
  else if (argc == 2)
    {
      inputFileName = argv[1];
      outputFileName = "CEMOutput.h5";
    }
  else if (argc == 1)
    {
      inputFileName = "../Input_Data/CEMInputFile.yaml";
      outputFileName = "CEMOutput.h5";
    }
  else
    {
      std::cout<< "ERROR: " << argc - 1 << " arguments, expecting 0, 1, or 2" << std::endl;
      exit(1);
    }
#ifdef PRINT_WORKING_DIRECTORY
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        std::cout<<"Current Directory: " << cwd << std::endl;
#endif
        
	//LOG(INFO) << "********************************************************************************************";
	// LOG(INFO) << "Executing ... Input File: " << inputFileName << " Output File: " << outputFileName << std::endl;

  CEM::SimManager Sim(inputFileName, outputFileName);
  Sim.Run();
        
  return 0;
}
