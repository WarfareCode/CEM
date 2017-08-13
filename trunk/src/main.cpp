


#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>

#ifdef PRINT_WORKING_DIRECTORY
#include <unistd.h>
#endif

#include <string>
#include <math.h>
#include <algorithm>

#include "DataLogger/DataLogger_HDF5.h"
#include "FDTD_Engine/FDTD_1D.h"
#include "InputParser/InputParser_YAML.h"

#define SIZE 200
 
int main (int argc, char *argv[])
{
    /*
     * Try block to detect exceptions raised by any of the calls inside it
     */
    try
    {
       std::string inputFileName;
       std::string outputFileName;
       InputParserYAML ip;

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
	
       std::cout << "Executing ... Input File: " << inputFileName << " Output File: " << outputFileName << std::endl;
       DataLoggerHDF5 dLogger;
       dLogger.CreateFile(outputFileName);

       ip.ReadInputFile(inputFileName);
        
       FDTD_1D fdtd;
       fdtd.InitializeEngine(ip.GetInput());
        
       for(int time = ip.getStartTime(); time < ip.getStopTime(); time++)
       {
         fdtd.UpdateFields(time);
         fdtd.SetEFieldSource(0,time);
         dLogger.WriteDataArray(fdtd.getEField());   
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
    
    return 0;
}
