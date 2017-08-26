/**
* @file FileUtilityFunctions.cpp
* @brief Implementation of File Utility functions
* @author Ben Frazier
* @date 08/53/2017 */

#include "FileUtilityFunctions.h"
#include <fstream>
#include<iostream>
#include <vector>

namespace CEM
{
  namespace FILE
  {
      std::string FindInputFile(std::string requestedFileName)
      {
	std::string fileName;
	bool fileFound = false;
	std::fstream fs;

	std::vector<std::string>filepaths = {"Input_Data","../Input_Data/", "../../Input_Data/", "../../../Input_Data/", "../../../../Input_Data/"};

	for (int i = 0; i < filepaths.size();i++)
	  {
	    fileName = filepaths[i] + requestedFileName;

	    std::cout<<"Searching " << fileName << std::endl;
	    fs.open(fileName);

	    if(fs.is_open())
	      {
		fileFound = true;
		fs.close();
		i = filepaths.size();
	      }
	  }

	if (!fileFound)
	  {
	    std::string eString = "FILE::FindInputFile ... File: " + requestedFileName + " not found";
	    throw std::runtime_error(eString);
	  }
	
	return fileName;
      }

    
  }//end namespace FILE
}//end namespace CEM
